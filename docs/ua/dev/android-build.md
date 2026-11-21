---
title: Збірка застосунків на Android
order: 15
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md, https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX]
sources: [unleashed-docs, unleashed-readme]
---
# Збірка застосунків на Android (Termux + uFBT)

Налаштуйте `ufbt` у [Termux](https://termux.dev/) на звичайному телефоні з Android без root і компілюйте застосунки
для Flipper Zero (`.fap`) просто на телефоні — без ПК, без proot і без віртуальної машини.

::: info Авторство
Усе це розібрав [@CamsShaft](https://github.com/CamsShaft) методом багатьох спроб і помилок на Samsung Galaxy S22
(SM-S901W, aarch64). Оригінальний посібник (MIT):
[BUILD-FLIPPER-FAPS-IN-TERMUX](https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX). Він входить до
документації Unleashed.
:::

**Межі застосування:** так збираються **застосунки**, а не прошивка. Про саму прошивку — у статті
[Збірка прошивки](/ua/dev/build).

Шляхи нижче розраховані на пристрій **aarch64** і типовий префікс Termux
(`$PREFIX` = `/data/data/com.termux/files/usr`). На вашому пристрої вони можуть відрізнятися — найчастіші збої
розібрані в розділі [Усунення проблем](#troubleshooting).

## Чому потрібні додаткові кроки

uFBT завантажує готовий кросплатформний тулчейн `arm-none-eabi-gcc`, зібраний для звичайного Linux із **glibc**.
Termux працює на **Bionic** libc Android із нестандартним розташуванням файлової системи, а кожен ELF-бінарник
тулчейна просить як динамічний компонувальник `/lib/ld-linux-aarch64.so.1`, якого в Android просто немає.

Рішення: встановити шар сумісності з glibc для Termux, а потім запускати кожен бінарник тулчейна через власний
компонувальник glibc — за допомогою невеликого скрипта-обгортки.

::: danger Не запускайте `patchelf` на бінарниках тулчейна
Він псує розташування ELF-сегментів, і ви отримуєте segfault у `cc1`. Описані нижче обгортки залишають бінарники
байт-у-байт недоторканими.
:::

## Що знадобиться

- Пристрій з Android на aarch64.
- [Termux](https://f-droid.org/en/packages/com.termux/), встановлений **із F-Droid** — збірка з Google Play
  застаріла й не працюватиме.
- Інтернет і кілька вільних ГБ під тулчейн, SDK та glibc.

## 1. Базові пакети

```sh
pkg update && pkg upgrade -y
pkg install python python-pip git file -y
```

`file` **не** є необов’язковим: цикл створення обгорток на кроці 6 саме ним відрізняє ELF-бінарники від усього
іншого.

## 2. Шар сумісності з glibc

```sh
pkg install glibc-repo -y
pkg install glibc-runner -y
```

Це мають бути **дві окремі команди**: `glibc-repo` додає репозиторій, з якого встановлюється `glibc-runner`. Разом
вони кладуть повноцінний glibc у `$PREFIX/glibc/`, включно з динамічним компонувальником. Перевірка:

```sh
ls $PREFIX/glibc/lib/ld-linux-aarch64.so.1
```

::: warning
**Ніколи не прописуйте `LD_PRELOAD` на `libc.so.6` з glibc глобально.** Це неочевидним чином ламає власні
Bionic-бінарники Termux, зокрема Python. Обгортки з кроку 6 роблять це непотрібним.
:::

## 3. Встановлення uFBT і Python-залежностей збірки

```sh
pip install ufbt colorlog heatshrink2 pyelftools scons pillow
```

| Пакет | Для чого потрібен |
|---|---|
| `colorlog` | Журналювання скриптів збірки |
| `heatshrink2` | Стиснення піктограм і ресурсів |
| `pyelftools` | Крок постобробки `FASTFAP` |
| `scons` | Система збірки — потрібна окрема установка; копія, що йде з тулчейном, тут непридатна |
| `pillow` | Конвертація піктограм; без неї єдина помилка — лаконічне `convert: No such file or directory` |

Якщо колесо `pillow` не збирається, скористайтеся пакетом Termux: `pkg install python-pillow`.

## 4. Спрямування uFBT на SDK Unleashed {#_4-point-ufbt-at-the-unleashed-sdk}

**Типово uFBT бере SDK офіційної прошивки.** Щоб збирати під Unleashed, передайте індекс оновлень Unleashed:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Канали: `dev` і `release`. **Ті самі прапорці потрібні під час кожного наступного `ufbt update`**, інакше ви тихо
повернетеся до офіційного SDK і будете збирати проти неправильного API.

Якщо `~/.ufbt/toolchain/` досі порожній, будь-який виклик uFBT підтягне тулчейн:

```sh
ufbt -h
```

Помилка зі згадкою `python3` на цьому етапі очікувана — крок 5 її виправляє. Перевірте, що тулчейн з’явився:

```sh
ls ~/.ufbt/toolchain/aarch64-linux/bin/arm-none-eabi-gcc
ls ~/.ufbt/toolchain/aarch64-linux/arm-none-eabi/bin/as
ls ~/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*/cc1
```

## 5. Перенаправлення Python тулчейна

Тулчейн постачається з власним Python, зв’язаним із glibc, а він тут не запускається. Спрямуйте всі записи
`python3*` на Python з Termux:

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"

for py in "$TOOLCHAIN"/bin/python3*; do
    [ -e "$py" ] || [ -L "$py" ] || continue
    ln -sf "$PREFIX/bin/python3" "$py"
done
```

## 6. Обгортки для бінарників тулчейна

Усе інше залежить від цього кроку. Кожна обгортка запускає справжній бінарник через динамічний компонувальник glibc
з явним `--library-path`, тому сам бінарник ніколи не змінюється.

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"
GLIBC_LIB="$PREFIX/glibc/lib"

wrap() {
    for f in "$@"; do
        [ -f "$f" ] || continue
        case "$f" in *.real | *.so | *.so.*) continue ;; esac
        [ -e "$f.real" ] && continue
        file -b "$f" | grep -q '^ELF' || continue

        mv "$f" "$f.real"
        cat > "$f" <<WRAPPER
#!$PREFIX/bin/bash
exec "$GLIBC_LIB/ld-linux-aarch64.so.1" --library-path "$GLIBC_LIB:$TOOLCHAIN/lib" "$f.real" "\$@"
WRAPPER
        chmod +x "$f"
        echo "wrapped $f"
    done
}

wrap "$TOOLCHAIN"/bin/arm-none-eabi-*
wrap "$TOOLCHAIN"/arm-none-eabi/bin/*
wrap "$TOOLCHAIN"/libexec/gcc/arm-none-eabi/*/*
```

Три шаблони — це три окремі каталоги з ELF-бінарниками. Якщо пропустити один, отримаєте характерну помилку:

| Каталог | Що містить | Помилка без обгортки |
|---|---|---|
| `bin/` | `arm-none-eabi-gcc`, `-g++`, … | `cannot execute` / `No such file or directory` |
| `arm-none-eabi/bin/` | `as`, `ld`, `ar`, `objcopy`, … | `cannot execute as` |
| `libexec/gcc/arm-none-eabi/<gcc-version>/` | `cc1`, `cc1plus`, `collect2`, `lto1` | `cannot execute cc1` |

Чому важливі перевірки в коді (особливо під час повторного запуску):

- `*.so` пропускається, бо `liblto_plugin.so` у `libexec/` — це спільна бібліотека, а не виконуваний файл;
  обгортка для неї дає `invalid ELF header`.
- `*.real` і перевірка `$f.real` роблять функцію ідемпотентною: повторний запуск після оновлення тулчейна не зможе
  обернути обгортку.
- У `bin/` навмисно обертається лише `arm-none-eabi-*`: `bin/python3` тепер указує на Bionic-Python із Termux і
  **не має** проходити через компонувальник glibc.

::: warning
`ufbt update` може замінити весь тулчейн — **повторюйте кроки 5 і 6 після кожного оновлення.**
:::

## 7. Збірка

```sh
git clone https://github.com/<owner>/<some-flipper-app>.git
cd <some-flipper-app>
ufbt
```

Успішна збірка завершується так:

```
scons: Entering directory '...'
        CC      ...
        LINK    ...
        FAP     ...
        FASTFAP ...
        APPCHK  dist/some_app.fap
                Target: 7, API: 88.2
```

Файл `.fap` лежить у `dist/`. Порівняйте показану версію API з прошивкою свого Фліппера — якщо вони не збігаються,
застосунок відмовиться завантажуватися.

## 8. Перенесення .fap на Фліппер

`ufbt launch` і `ufbt flash_usb` потребують послідовного з’єднання (`/dev/ttyACM*`). **На стоковому Android без root
це не працює** — Android не показує Termux вузли пристроїв USB CDC-ACM. Скористатися цими командами можна лише на
пристрої з root і працездатним драйвером CDC-ACM.

Натомість просто скопіюйте файл. FAP-и лежать на картці microSD у `/ext/apps/<Category>/`:

```sh
termux-setup-storage                        # one-time: grants Termux access to shared storage
cp dist/some_app.fap ~/storage/downloads/
```

З папки `Downloads` файл видно іншим застосункам, тож перенесіть його на Фліппер звичним способом — мобільним
застосунком Flipper або USB-C-зчитувачем карток microSD.

## Усунення проблем {#troubleshooting}

### `cannot execute cc1` / `cannot execute as`

Один із трьох каталогів на кроці 6 не отримав обгорток. Повторіть виклики `wrap` — їх безпечно запускати знову.

### `liblto_plugin.so: invalid ELF header`

Обгортку отримала спільна бібліотека. Відновіть її:

```sh
LIBEXEC="$(echo "$HOME"/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*)"
mv "$LIBEXEC/liblto_plugin.so.real" "$LIBEXEC/liblto_plugin.so"
```

### `Segmentation fault` у cc1

Бінарник зіпсований, і майже завжди це наслідок `patchelf`. Завантажте тулчейн заново:

```sh
rm -rf ~/.ufbt/toolchain
ufbt -h
```

Потім повторіть кроки 5 і 6. **Ніколи не застосовуйте `patchelf` до цих бінарників.**

### `No module named 'colorlog'` / `'heatshrink2'` / `'elftools'`

```sh
pip install colorlog heatshrink2 pyelftools
```

### `convert: No such file or directory`

Немає `pillow`: `pip install pillow` або `pkg install python-pillow`.

### `python3: No such file or directory`

Символьне посилання на Python у тулчейні зламане або його відновило оновлення. Повторіть крок 5.

### `CANNOT LINK EXECUTABLE "python3": library "ld-linux-aarch64.so.1" not found`

`LD_PRELOAD` указує на `libc.so.6` з glibc, а це ламає Bionic-бінарники Termux. Приберіть його:

```sh
unset LD_PRELOAD
unset -f ufbt          # in case a shell function is shadowing ufbt
```

Потім перевірте стартові файли оболонки на залишки:

```sh
grep -r "glibc\|LD_PRELOAD" ~/.bashrc ~/.profile ~/.bash_profile ~/.zshrc 2>/dev/null
```

### `ufbt update` пише, що SDK актуальний, а тулчейна немає

uFBT відслідковує SDK і тулчейн окремо. Примусово оновіть обидва:

```sh
rm -rf ~/.ufbt/current ~/.ufbt/toolchain
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
ufbt -h
```

Потім повторіть кроки 5 і 6.

### Застосунок збирається, але показує не ту версію API

Якийсь `ufbt update` виконався без `--index-url`, тому uFBT повернувся до офіційного SDK. Повторіть команду з
[кроку 4](#_4-point-ufbt-at-the-unleashed-sdk).

### Обгортки зникли після оновлення

Так і має бути — `ufbt update` може замінити весь каталог тулчейна. Повторіть кроки 5 і 6.

## Що насправді відбувається

Кожна обгортка запускає свій справжній бінарник через динамічний компонувальник glibc, у якому `--library-path`
указує на бібліотеки glibc. Коли `arm-none-eabi-gcc` викликає `cc1`, він натрапляє на скрипт оболонки, який через
компонувальник доходить до недоторканого бінарника `.real`. На результат кроскомпіляції це не впливає — він
призначений для bare-metal Cortex-M, а не для Linux.

```
ufbt (Python, Bionic)
  └─ arm-none-eabi-gcc (wrapper)
       └─ ld-linux-aarch64.so.1 → arm-none-eabi-gcc.real (glibc)
            ├─ cc1 (wrapper)      → ld-linux-aarch64.so.1 → cc1.real
            ├─ as (wrapper)       → ld-linux-aarch64.so.1 → as.real
            └─ collect2 → ld (wrapper) → ld-linux-aarch64.so.1 → ld.real
                 └─ output: some_app.fap (ARM Cortex-M4, for the Flipper Zero)
```

## Пов’язані сторінки

- [Перший застосунок на C](/ua/dev/first-app-c)
- [Збірка прошивки](/ua/dev/build)
- [Застосунки на SD-карті](/ua/apps/sd-card-apps)
- [Мобільний застосунок Flipper](/ua/mobile/mobile-app)
