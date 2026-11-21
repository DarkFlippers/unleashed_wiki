---
title: Збірка прошивки
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToBuild.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Збірка прошивки

Збирати Unleashed Firmware з джерельного коду варто тоді, коли потрібно змінити саму прошивку, вкомпілювати в неї
власні застосунки або перевірити найсвіжіший код із гілки `dev` до офіційного релізу.

Якщо потрібно лише написати застосунок (`.fap`), уся прошивка не знадобиться — скористайтеся
[uFBT](/ua/dev/first-app-c) і переходьте одразу до
[збірки застосунків під Unleashed SDK](#build-apps-against-the-unleashed-sdk-with-ufbt).

## Що потрібно

- **Git** — [завантажити](https://git-scm.com/downloads) для Windows; у Linux/macOS встановлюється менеджером
  пакетів (`brew`, `apt`, …).
- **VS Code** (рекомендований для розробки, для простої збірки не обов’язковий).
- Кілька ГБ на диску. Більше нічого: `fbt` сам завантажує власний ARM-тулчейн під час першого запуску й не чіпає
  системний `PATH` (див. [fbt → Оточення](/ua/dev/fbt#environment)).

## 1. Клонування репозиторію

Клонуйте завжди **разом із сабмодулями**:

```shell
git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
cd unleashed-firmware
```

Якщо репозиторій уже склоновано без `--recursive`, ініціалізуйте сабмодулі:

```shell
git submodule update --init --recursive
```

## 2. Збірка в Linux / macOS

Зібрати все та отримати пакет оновлення, який можна встановити з картки microSD:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

Зібрати один застосунок з `applications_user/` і запустити його на Фліппері, під’єднаному через USB:

```sh
./fbt COMPACT=1 DEBUG=0 launch_app APPSRC=applications_user/yourplugin
```

## 3. Збірка у Windows

Використовуйте `fbt.cmd` у PowerShell або `cmd`:

```powershell
./fbt.cmd COMPACT=1 DEBUG=0 updater_package
```

::: warning
У Windows, залежно від оболонки, може знадобитися запис `.\fbt.cmd` (зі зворотним слешем) замість `./fbt.cmd`.
:::

## 4. Де взяти результат і як його встановити

Усі результати збірки потрапляють до `dist/`. Встановлювати потрібно пакет оновлення:

```
dist/f7-C/flipper-z-f7-update-local.tgz
```

Шаблон назви — `flipper-z-{target}-update-{suffix}.tgz`. Типовий суфікс — `local` (задається параметром
`DIST_SUFFIX` у `fbt_options.py` або змінною оточення `DIST_SUFFIX`).

Способи встановлення:

- відкрити `.tgz` у **qFlipper** (*Install from file*) або у Web Installer Unleashed;
- доручити це `fbt` через USB: `./fbt COMPACT=1 DEBUG=0 flash_usb_full` (збирає, завантажує і встановлює);
- прошити через SWD за допомогою SWD-зонда: `./fbt flash` (див. [цілі fbt](/ua/dev/fbt#high-level-targets)).

::: tip Навіщо `DEBUG=0`?
У файлі `fbt_options.py` Unleashed типово стоять `COMPACT=1` і **`DEBUG=1`**. Образ із налагоджувальною інформацією
більший і може не вміститися під радіостеком у флеш-пам’яті — тоді пакування обривається повідомленням
`Firmware image overlaps C2 region and is not programmable!`. Для будь-якої збірки, яку плануєте встановлювати,
явно вказуйте `DEBUG=0`. Зверніть увагу: `DEBUG=0` також вирізає з коду `furi_assert()`.
:::

## Інтеграція з VS Code

`fbt` постачає готову конфігурацію для VS Code:

```sh
./fbt vscode_dist
```

Команда копіює конфігурацію до `.vscode/`. Далі відкрийте корінь прошивки у VS Code через
**File → Open Folder**, погодьтеся на рекомендовані розширення й користуйтеся
<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> для задач збірки. Докладніше — у [fbt → VS Code](/ua/dev/fbt#vs-code-integration).

## Збірка застосунків під Unleashed SDK через uFBT {#build-apps-against-the-unleashed-sdk-with-ufbt}

uFBT (micro-fbt) збирає окремі застосунки проти завантаженого SDK, а не проти повного дерева джерельного коду.
**Типово він завантажує SDK офіційної прошивки.** Щоб збирати під Unleashed, спрямуйте його на індекс оновлень
Unleashed:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Доступні канали — `dev` і `release`. Ті самі прапорці потрібно передавати під час **кожного** наступного
`ufbt update`, інакше uFBT тихо повернеться до офіційного SDK, і зібраний застосунок повідомить неправильну версію
API.

::: tip Unleashed
Unleashed зберігає офіційний API, тому більшість офіційних застосунків працюють без змін. Застосунок відмовляється
завантажуватися лише тоді, коли major-версія його API не збігається з прошивкою — достатньо перезібрати його проти
відповідного SDK.
:::

## Збірка застосунків на Android

Застосунки (не прошивку) можна збирати просто на телефоні з Android за допомогою uFBT у Termux — див.
[Збірка застосунків на Android](/ua/dev/android-build).

## Усунення проблем

| Проблема | Що робити |
|---|---|
| Збірка падає через відсутні файли або помилки сабмодулів | `git submodule update --init --recursive` |
| `Firmware image overlaps C2 region and is not programmable!` | Додайте до команди `DEBUG=0` |
| `./fbt` не знаходиться у Windows | Використовуйте `fbt.cmd` / `.\fbt.cmd` |
| Застосунок, зібраний uFBT, не запускається: невідповідність API | Повторіть `ufbt update` з `--index-url` Unleashed і перезберіть |
| Потрібна чиста перезбірка | Додайте `-c`, щоб очистити вказані цілі, наприклад `./fbt -c fw_dist` |

## Пов’язані сторінки

- [Flipper Build Tool (fbt)](/ua/dev/fbt) — усі цілі та параметри
- [Перший застосунок на C](/ua/dev/first-app-c)
- [OTA-оновлення](/ua/dev/ota) — що міститься в пакеті оновлення
- [Апаратні цілі](/ua/dev/hardware-targets)
