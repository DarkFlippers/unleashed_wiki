---
title: Сборка прошивки
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToBuild.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Сборка прошивки

Собирать Unleashed Firmware из исходников стоит, если вы хотите изменить саму прошивку, встроить в сборку свои
приложения или потестить свежий код из `dev` до официального релиза.

Если нужно только написать приложение (`.fap`), вся прошивка не нужна — используйте
[uFBT](/ru/dev/first-app-c) и переходите сразу к разделу
[сборка приложений под Unleashed SDK](#build-apps-against-the-unleashed-sdk-with-ufbt).

## Что понадобится

- **Git** — [скачать](https://git-scm.com/downloads) для Windows; на Linux/macOS ставится пакетным менеджером
  (`brew`, `apt`, …).
- **VS Code** (рекомендуется для разработки, для простой сборки не обязателен).
- Несколько ГБ свободного места. Больше ничего: при первом запуске `fbt` сам скачивает ARM-тулчейн и не трогает
  системный `PATH` (см. [fbt → Окружение](/ru/dev/fbt#environment)).

## 1. Клонируем репозиторий

Клонируйте всегда **с сабмодулями**:

```shell
git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
cd unleashed-firmware
```

Если уже склонировали без `--recursive`, инициализируйте сабмодули:

```shell
git submodule update --init --recursive
```

## 2. Сборка на Linux / macOS

Собрать всё и получить пакет обновления, который ставится с microSD-карты:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

Собрать одно приложение из `applications_user/` и запустить его на Флиппере, подключённом по USB:

```sh
./fbt COMPACT=1 DEBUG=0 launch_app APPSRC=applications_user/yourplugin
```

## 3. Сборка на Windows

Используйте `fbt.cmd` в PowerShell или `cmd`:

```powershell
./fbt.cmd COMPACT=1 DEBUG=0 updater_package
```

::: warning
На Windows, в зависимости от оболочки, может понадобиться писать `.\fbt.cmd` (с обратным слэшем) вместо `./fbt.cmd`.
:::

## 4. Где результат и как прошить

Все результаты сборки попадают в `dist/`. Ставить нужно пакет обновления:

```
dist/f7-C/flipper-z-f7-update-local.tgz
```

Шаблон имени — `flipper-z-{target}-update-{suffix}.tgz`. Суффикс по умолчанию — `local` (задаётся `DIST_SUFFIX` в
`fbt_options.py` или одноимённой переменной окружения).

Способы установки:

- открыть `.tgz` в **qFlipper** (*Install from file*) или в веб-установщике Unleashed;
- поручить это `fbt` по USB: `./fbt COMPACT=1 DEBUG=0 flash_usb_full` (собирает, загружает и устанавливает);
- прошить по SWD через отладчик: `./fbt flash` (см. [цели fbt](/ru/dev/fbt#high-level-targets)).

::: tip Зачем `DEBUG=0`?
В `fbt_options.py` Unleashed по умолчанию стоят `COMPACT=1` и **`DEBUG=1`**. Отладочный образ больше и может не
влезть во флеш ниже радиостека — тогда упаковка останавливается с ошибкой
`Firmware image overlaps C2 region and is not programmable!`. Для всего, что вы собираетесь ставить, явно указывайте
`DEBUG=0`. Учтите, что с `DEBUG=0` вырезаются и проверки `furi_assert()`.
:::

## Интеграция с VS Code

`fbt` поставляет готовую конфигурацию VS Code:

```sh
./fbt vscode_dist
```

Она копируется в `.vscode/`. Затем откройте корень прошивки в VS Code через **File → Open Folder**, согласитесь
поставить рекомендуемые расширения и запускайте задачи сборки через <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
Подробнее — в [fbt → VS Code](/ru/dev/fbt#vs-code-integration).

## Сборка приложений под Unleashed SDK через uFBT {#build-apps-against-the-unleashed-sdk-with-ufbt}

uFBT (micro-fbt) собирает отдельные приложения под скачанный SDK, без полного дерева исходников. **По умолчанию он
качает SDK официальной прошивки.** Чтобы собирать под Unleashed, укажите индекс обновлений Unleashed:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Каналы — `dev` и `release`. Используйте те же флаги при **каждом** следующем `ufbt update`, иначе uFBT молча
переключится обратно на официальный SDK, и собранное приложение покажет не ту версию API.

::: tip Unleashed
Unleashed сохраняет официальный API, поэтому большинство официальных приложений работают как есть. Приложение
отказывается запускаться, только если мажорная версия его API не совпадает с прошивкой — пересборка под нужный SDK
это лечит.
:::

## Сборка приложений на Android

Приложения (не прошивку) можно собирать прямо на Android-телефоне с uFBT внутри Termux — см.
[Сборка приложений на Android](/ru/dev/android-build).

## Решение проблем

| Проблема | Решение |
|---|---|
| Сборка падает из-за отсутствующих файлов / ошибок сабмодулей | `git submodule update --init --recursive` |
| `Firmware image overlaps C2 region and is not programmable!` | Добавьте `DEBUG=0` в команду |
| На Windows не находится `./fbt` | Используйте `fbt.cmd` / `.\fbt.cmd` |
| Приложение, собранное uFBT, не запускается: API mismatch | Повторите `ufbt update` с `--index-url` Unleashed и пересоберите |
| Нужна чистая пересборка | Добавьте `-c`, чтобы очистить указанные цели, например `./fbt -c fw_dist` |

## Связанные страницы

- [Flipper Build Tool (fbt)](/ru/dev/fbt) — все цели и опции
- [Первое приложение на C](/ru/dev/first-app-c)
- [OTA-обновления](/ru/dev/ota) — что внутри пакета обновления
- [Аппаратные таргеты](/ru/dev/hardware-targets)
