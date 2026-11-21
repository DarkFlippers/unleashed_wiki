---
title: Сборка приложений на Android
order: 15
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md, https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX]
sources: [unleashed-docs, unleashed-readme]
---
# Сборка приложений на Android (Termux + uFBT)

Настраиваем `ufbt` внутри [Termux](https://termux.dev/) на обычном Android-телефоне без root и компилируем приложения
Flipper Zero (`.fap`) прямо на телефоне — без ПК, без proot, без виртуальных машин.

::: info Авторство
Способ найден [@CamsShaft](https://github.com/CamsShaft) методом долгих проб и ошибок на Samsung Galaxy S22
(SM-S901W, aarch64). Оригинальный гайд (MIT):
[BUILD-FLIPPER-FAPS-IN-TERMUX](https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX). Входит в документацию
Unleashed.
:::

**Область применения:** так собираются **приложения**, а не прошивка. Про сборку самой прошивки — в
[Сборке прошивки](/ru/dev/build).

Пути ниже рассчитаны на устройство **aarch64** и стандартный префикс Termux
(`$PREFIX` = `/data/data/com.termux/files/usr`). На вашем устройстве что-то может отличаться — типичные ошибки
разобраны в разделе [Решение проблем](#troubleshooting).

## Почему нужны лишние телодвижения

uFBT скачивает готовый кросс-тулчейн `arm-none-eabi-gcc`, собранный для обычного Linux с **glibc**. Termux работает
на **Bionic** libc от Android с нестандартной структурой файловой системы, а каждый ELF-бинарник тулчейна требует в
качестве динамического линкера `/lib/ld-linux-aarch64.so.1`, которого на Android нет.

Решение: поставить слой совместимости glibc для Termux и запускать каждый бинарник тулчейна через собственный
линкер glibc с помощью небольшого скрипта-обёртки.

::: danger Не запускайте `patchelf` на бинарниках тулчейна
Он портит раскладку ELF-сегментов, и `cc1` начинает падать с segfault. Обёртки ниже оставляют бинарники нетронутыми
байт в байт.
:::

## Что понадобится

- Android-устройство на aarch64.
- [Termux](https://f-droid.org/en/packages/com.termux/), установленный **из F-Droid** — версия из Google Play
  устарела и работать не будет.
- Интернет и пара ГБ свободного места под тулчейн, SDK и glibc.

## 1. Базовые пакеты

```sh
pkg update && pkg upgrade -y
pkg install python python-pip git file -y
```

`file` **обязателен** — цикл-обёртка на шаге 6 с его помощью отличает ELF-бинарники от всего остального.

## 2. Слой совместимости glibc

```sh
pkg install glibc-repo -y
pkg install glibc-runner -y
```

Это должны быть **две отдельные команды**: `glibc-repo` добавляет репозиторий, из которого ставится `glibc-runner`.
Вместе они устанавливают полноценную glibc в `$PREFIX/glibc/`, включая динамический линкер. Проверьте:

```sh
ls $PREFIX/glibc/lib/ld-linux-aarch64.so.1
```

::: warning
**Никогда не прописывайте глобально `LD_PRELOAD` на `libc.so.6` из glibc.** Это ломает собственные Bionic-бинарники
Termux, включая Python, причём неочевидным образом. Обёртки из шага 6 делают это ненужным.
:::

## 3. Ставим uFBT и Python-зависимости сборки

```sh
pip install ufbt colorlog heatshrink2 pyelftools scons pillow
```

| Пакет | Для чего |
|---|---|
| `colorlog` | Логирование скриптов сборки |
| `heatshrink2` | Сжатие иконок и ресурсов |
| `pyelftools` | Этап постобработки `FASTFAP` |
| `scons` | Система сборки — нужна отдельная установка, встроенная в тулчейн копия здесь неработоспособна |
| `pillow` | Конвертация иконок; без него единственная ошибка — голое `convert: No such file or directory` |

Если wheel `pillow` не собирается, поставьте пакет Termux: `pkg install python-pillow`.

## 4. Направляем uFBT на SDK Unleashed {#_4-point-ufbt-at-the-unleashed-sdk}

**По умолчанию uFBT использует SDK официальной прошивки.** Чтобы собирать под Unleashed, укажите индекс обновлений
Unleashed:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Каналы: `dev` и `release`. **Каждый следующий `ufbt update` должен быть с теми же флагами**, иначе вы молча
откатитесь на официальный SDK и будете собирать под чужой API.

Если `~/.ufbt/toolchain/` после этого всё ещё пуст, тулчейн подтянет любой вызов uFBT:

```sh
ufbt -h
```

Ошибка про `python3` на этом этапе ожидаема — её исправит шаг 5. Проверьте, что тулчейн на месте:

```sh
ls ~/.ufbt/toolchain/aarch64-linux/bin/arm-none-eabi-gcc
ls ~/.ufbt/toolchain/aarch64-linux/arm-none-eabi/bin/as
ls ~/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*/cc1
```

## 5. Переключаем Python тулчейна

Тулчейн несёт свой Python, слинкованный с glibc, — здесь он не запустится. Направьте все `python3*` на Python из
Termux:

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"

for py in "$TOOLCHAIN"/bin/python3*; do
    [ -e "$py" ] || [ -L "$py" ] || continue
    ln -sf "$PREFIX/bin/python3" "$py"
done
```

## 6. Оборачиваем бинарники тулчейна

От этого шага зависит всё остальное. Каждая обёртка запускает настоящий бинарник через динамический линкер glibc с
явным `--library-path`, так что сам бинарник не меняется.

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

Три маски — это три разных каталога с ELF-бинарниками. Пропуск любого даёт свою ошибку:

| Каталог | Содержит | Ошибка, если не обёрнут |
|---|---|---|
| `bin/` | `arm-none-eabi-gcc`, `-g++`, … | `cannot execute` / `No such file or directory` |
| `arm-none-eabi/bin/` | `as`, `ld`, `ar`, `objcopy`, … | `cannot execute as` |
| `libexec/gcc/arm-none-eabi/<gcc-version>/` | `cc1`, `cc1plus`, `collect2`, `lto1` | `cannot execute cc1` |

Зачем нужны проверки (особенно при повторном запуске):

- `*.so` пропускается, потому что `liblto_plugin.so` в `libexec/` — разделяемая библиотека, а не исполняемый файл;
  если её обернуть, получите `invalid ELF header`.
- `*.real` и проверка `$f.real` делают функцию идемпотентной: повторный запуск после обновления тулчейна не обернёт
  обёртку.
- В `bin/` намеренно оборачиваются только `arm-none-eabi-*`: `bin/python3` теперь указывает на Bionic-Python из
  Termux и **не должен** идти через линкер glibc.

::: warning
`ufbt update` может заменить тулчейн целиком — **повторяйте шаги 5 и 6 после каждого обновления.**
:::

## 7. Сборка

```sh
git clone https://github.com/<owner>/<some-flipper-app>.git
cd <some-flipper-app>
ufbt
```

Успешная сборка заканчивается так:

```
scons: Entering directory '...'
        CC      ...
        LINK    ...
        FAP     ...
        FASTFAP ...
        APPCHK  dist/some_app.fap
                Target: 7, API: 88.2
```

`.fap` лежит в `dist/`. Сверьте показанную версию API с прошивкой Флиппера — при несовпадении приложение не
запустится.

## 8. Переносим .fap на Флиппер

`ufbt launch` и `ufbt flash_usb` требуют serial-подключения (`/dev/ttyACM*`). **На стоковом Android без root это не
работает** — Android не отдаёт Termux узлы устройств USB CDC-ACM. Эти команды доступны только на рутованном
устройстве с рабочим драйвером CDC-ACM.

Поэтому просто скопируйте файл. FAP-файлы лежат на microSD-карте в `/ext/apps/<Category>/`:

```sh
termux-setup-storage                        # one-time: grants Termux access to shared storage
cp dist/some_app.fap ~/storage/downloads/
```

Из `Downloads` файл виден другим приложениям, так что перенесите его на Флиппер как обычно — через мобильное
приложение Flipper или USB-C картридер для microSD.

## Решение проблем {#troubleshooting}

### `cannot execute cc1` / `cannot execute as`

Один из трёх каталогов шага 6 не обёрнут. Повторите вызовы `wrap` — это безопасно.

### `liblto_plugin.so: invalid ELF header`

Обернули разделяемую библиотеку. Верните её:

```sh
LIBEXEC="$(echo "$HOME"/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*)"
mv "$LIBEXEC/liblto_plugin.so.real" "$LIBEXEC/liblto_plugin.so"
```

### `Segmentation fault` в cc1

Бинарник испорчен, почти всегда — `patchelf`. Скачайте тулчейн заново:

```sh
rm -rf ~/.ufbt/toolchain
ufbt -h
```

Затем повторите шаги 5 и 6. **Никогда не используйте `patchelf` на этих бинарниках.**

### `No module named 'colorlog'` / `'heatshrink2'` / `'elftools'`

```sh
pip install colorlog heatshrink2 pyelftools
```

### `convert: No such file or directory`

Нет `pillow`: `pip install pillow` или `pkg install python-pillow`.

### `python3: No such file or directory`

Симлинк Python тулчейна сломан или восстановлен обновлением. Повторите шаг 5.

### `CANNOT LINK EXECUTABLE "python3": library "ld-linux-aarch64.so.1" not found`

`LD_PRELOAD` указывает на `libc.so.6` из glibc, что ломает Bionic-бинарники Termux. Сбросьте его:

```sh
unset LD_PRELOAD
unset -f ufbt          # in case a shell function is shadowing ufbt
```

Затем проверьте файлы инициализации оболочки на остатки:

```sh
grep -r "glibc\|LD_PRELOAD" ~/.bashrc ~/.profile ~/.bash_profile ~/.zshrc 2>/dev/null
```

### `ufbt update` пишет, что SDK актуален, а тулчейна нет

uFBT отслеживает SDK и тулчейн раздельно. Принудительно обновите оба:

```sh
rm -rf ~/.ufbt/current ~/.ufbt/toolchain
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
ufbt -h
```

Затем повторите шаги 5 и 6.

### Приложение собирается, но показывает не ту версию API

Был запущен `ufbt update` без `--index-url`, и uFBT вернулся на официальный SDK. Повторите команду из
[шага 4](#_4-point-ufbt-at-the-unleashed-sdk).

### Обёртки пропали после обновления

Так и должно быть — `ufbt update` может заменить весь каталог тулчейна. Повторите шаги 5 и 6.

## Что происходит на самом деле

Каждая обёртка запускает свой настоящий бинарник через динамический линкер glibc с `--library-path`, указывающим на
библиотеки glibc. Когда `arm-none-eabi-gcc` вызывает `cc1`, он попадает в shell-скрипт, который через линкер передаёт
управление нетронутому бинарнику `.real`. На результат кросс-компиляции это не влияет — он предназначен для
bare-metal Cortex-M, а не для Linux.

```
ufbt (Python, Bionic)
  └─ arm-none-eabi-gcc (wrapper)
       └─ ld-linux-aarch64.so.1 → arm-none-eabi-gcc.real (glibc)
            ├─ cc1 (wrapper)      → ld-linux-aarch64.so.1 → cc1.real
            ├─ as (wrapper)       → ld-linux-aarch64.so.1 → as.real
            └─ collect2 → ld (wrapper) → ld-linux-aarch64.so.1 → ld.real
                 └─ output: some_app.fap (ARM Cortex-M4, for the Flipper Zero)
```

## Связанные страницы

- [Первое приложение на C](/ru/dev/first-app-c)
- [Сборка прошивки](/ru/dev/build)
- [Приложения на SD-карте](/ru/apps/sd-card-apps)
- [Мобильное приложение Flipper](/ru/mobile/mobile-app)
