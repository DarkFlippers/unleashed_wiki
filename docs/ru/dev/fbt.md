---
title: Flipper Build Tool (fbt)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Flipper Build Tool (fbt)

`fbt` — единая точка входа для сборки, прошивки, отладки и линтинга прошивки. Запускается как `./fbt`
(или `fbt.cmd` на Windows) из корня репозитория. Внутри это обёртка над системой сборки [SCons](https://scons.org/).

Если нужно собрать и отладить **одно приложение**, полное дерево прошивки не требуется — используйте
[uFBT](https://pypi.org/project/ufbt/) (см. [Первое приложение на C](/ru/dev/first-app-c)).

## Окружение {#environment}

Из инструментов нужен только `git`. При первом запуске `fbt` скачивает и распаковывает готовый тулчейн
и настраивает переменные окружения **только для себя** — глобальный `PATH` не меняется.

Чтобы пользоваться тулчейном вне `fbt` (например, вручную вызвать `arm-none-eabi-gdb`), откройте *fbt shell*:

- Windows: запустите `scripts/toolchain/fbtenv.cmd`
- Linux / macOS: выполните `source scripts/toolchain/fbtenv.sh` в новой оболочке
- или наберите `` . `./fbt -s env` `` в своей оболочке (точку в начале не убирайте)

Переменные окружения, влияющие на поведение `fbt`:

| Переменная | Эффект |
|---|---|
| `FBT_NOENV=1` | Не скачивать/настраивать тулчейн; все инструменты должны уже быть в `PATH` (на Windows недоступно) |
| `FBT_TOOLCHAIN_PATH=…` | Куда распаковывать тулчейн (по умолчанию `toolchain/` в корне репозитория) |
| `FBT_VERBOSE=1` | Подробный отладочный вывод `fbt` и скриптов тулчейна |
| `FBT_NO_SYNC=1` | Не выполнять `git submodule update --init` при каждом запуске |

Как задать переменную на один запуск:

```sh
# Linux / macOS
FBT_NO_SYNC=1 ./fbt ...
```

```bat
:: Windows (cmd)
set "FBT_NO_SYNC=1"
```

Остальные переменные описаны в исходниках скриптов `fbt` и `fbtenv`.

## Запуск fbt

Передайте опции конфигурации и нужные цели:

```sh
./fbt COMPACT=1 DEBUG=0 VERBOSE=1 updater_package copro_dist
```

Чтобы очистить (аналог `make clean`) указанные цели, добавьте `-c`.

`fbt` отслеживает зависимости, поэтому достаточно указать самую верхнеуровневую нужную цель — всё, от чего она
зависит, пересоберётся автоматически.

## Каталоги сборки

Прошивка и апдейтер собираются в отдельных подкаталогах `build/`, названных по настройкам оптимизации
(`COMPACT`, `DEBUG`). Для IDE последний собранный вариант всегда доступен по ссылке `build/latest` вместе с
`compile_commands.json` для автодополнения.

::: info
`build/latest` и база компиляции обновляются только **целями сборки прошивки**. Прошивка устройства или сборка
пакетов обновления для *другой* конфигурации debug/release или другого таргета `build/latest` не переключает.
:::

## Интеграция с VS Code {#vs-code-integration}

```sh
./fbt vscode_dist
```

копирует готовую конфигурацию окружения в `.vscode/`. Откройте корень прошивки через **File → Open Folder**.

- Чтобы использовать другой language server вместо `cpptools` по умолчанию, выполните
  `./fbt vscode_dist LANG_SERVER=<language-server>`. Поддерживаются `cpptools` (по умолчанию) и `clangd`.
- При первом открытии предложат рекомендуемые расширения (список в `.vscode/extensions.json`) — поставьте их.
- Задачи сборки — в меню <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
- Для отладки нужен поддерживаемый отладчик: Wi-Fi Devboard со стоковой (Blackmagic) прошивкой, ST-Link и
  совместимые, либо J-Link (только в VS Code; утилиты J-Link в тулчейн не входят —
  [скачайте](https://www.segger.com/downloads/jlink/) их и добавьте в `PATH`).
- Без отладчика прошивку всё равно можно поставить по USB.

## Основные цели {#high-level-targets}

Цели, которые нужны чаще всего.

| Цель | Что делает |
|---|---|
| `fw_dist` | Собрать прошивку и выложить в `dist/`. **Цель по умолчанию**, если ничего не указано |
| `fap_dist` | Собрать внешние приложения (FAP) и выложить в `dist/` |
| `updater_package` | Полный пакет самообновления: DFU прошивки + радиостек + ресурсы для SD-карты |
| `updater_minpackage` | Минимальный пакет обновления: только DFU прошивки |
| `copro_dist` | Собрать бинарники FUS + радиостека Core2 для qFlipper |
| `flash` | Прошить по SWD поддерживаемым отладчиком (определяется автоматически; переопределить — `SWD_TRANSPORT=...`, выбрать один из нескольких — `SWD_TRANSPORT_SERIAL=...`) |
| `flash_usb`, `flash_usb_full` | Собрать, загрузить и установить пакет обновления по USB (минимальный / полный) |
| `debug` | Собрать и прошить, затем подключить GDB с загруженным `.elf` прошивки |
| `debug_other`, `debug_other_blackmagic` | Подключить GDB без `.elf`; внешние `.elf` добавляются через `add-symbol-file` |
| `updater_debug` | Подключить GDB с `.elf` апдейтера |
| `devboard_flash` | Обновить Wi-Fi Devboard; доп. аргументы через `ARGS="..."`, например `ARGS="-c dev"` |
| `blackmagic` | Отладка через Blackmagic (Wi-Fi Devboard) |
| `openocd` | Просто запустить OpenOCD; доп. аргументы через `ARGS="..."` |
| `get_blackmagic` | Вывести адрес Blackmagic в формате GDB remote (для интеграции с IDE) |
| `get_stlink` | Вывести серийные номера подключённых ST-Link (для `SWD_TRANSPORT_SERIAL=...`) |
| `lint`, `format` | Проверка / форматирование C-кода clang-format (`.clang-format`); доп. аргументы через `ARGS="..."` |
| `lint_py`, `format_py` | Проверка / форматирование Python, файлов сборки и манифестов через [black](https://black.readthedocs.io/en/stable/index.html) |
| `lint_img`, `format_img` | Проверка / исправление графических ресурсов (глубина цвета, удаление метаданных) |
| `lint_all`, `format_all` | Все линтеры / форматтеры разом |
| `firmware_pvs` | Отчёт PVS-Studio (PVS-Studio должен быть в `PATH`) |
| `doxygen` | Сгенерировать документацию Doxygen; `doxy` ещё и открывает её в браузере |
| `cli` | Открыть сессию [CLI](/ru/dev/cli) Флиппера по USB |

## Цели прошивки

| Цель | Что делает |
|---|---|
| `faps` | Собрать все внешние приложения и плагины как `.fap` |
| `fap_<appid>` | Собрать одно приложение как `.fap` по его app ID, например `fap_snake_game` |
| `fap_<appid>_list` | Листинг исходников + ассемблера для `.fap` этого приложения |
| `flash`, `firmware_flash` | Прошить текущую сборку по SWD |
| `jflash` | Прошить через JFlash с J-Link (JFlash должен быть в `PATH`) |
| `firmware_all`, `updater_all` | Собрать базовый набор бинарников |
| `firmware_list`, `updater_list` | Листинги исходников + ассемблера |
| `firmware_cdb`, `updater_cdb` | Сгенерировать `compilation_database.json` для IDE — работает без полной сборки |

Чтобы принудительно добавить приложения во внешнюю сборку, используйте `--extra-ext-apps` (ниже).

## Цели ресурсов

| Цель | Что делает |
|---|---|
| `resources` | Собрать ресурсы для SD-карты и их манифесты |
| `dolphin_ext` | Обработать анимации дельфина для SD-карты |
| `icons` | Сгенерировать `.c` + `.h` для иконок из PNG |
| `proto` | Сгенерировать `.pb.c` + `.pb.h` из `.proto` |
| `proto_ver` | Сгенерировать `.h` с версией protobuf |
| `dolphin_internal`, `dolphin_blocking` | Сгенерировать `.c` + `.h` для соответствующих ресурсов дельфина |

## Параметры командной строки

| Параметр | Значение |
|---|---|
| `--options optionfile.py` | Загрузить файл с настройками (по умолчанию `fbt_options.py`) |
| `--extra-int-apps=app1,app2,appN` | Принудительно встроить перечисленные приложения **в** прошивку (цель `firmware`) |
| `--extra-ext-apps=app1,app2,appN` | Принудительно собрать перечисленные приложения как **внешние** (цель `firmware_extapps`) |
| `--extra-define=A --extra-define=B=C` | Дополнительные глобальные define для C/C++; можно повторять |
| `--proxy-env=VAR1,VAR2` | Дополнительные переменные окружения для дочерних процессов. По умолчанию `fbt` очищает окружение; список всегда пробрасываемых переменных — в `environ.scons` |

## Конфигурация

Значения по умолчанию задаются в `fbt_options.py`. Значения из командной строки имеют приоритет. Для **постоянных
личных переопределений** создайте рядом `fbt_options_local.py` — он выполняется при загрузке настроек по умолчанию,
так что отслеживаемый файл править не придётся. Все опции — `./fbt -h`.

Заметные значения по умолчанию в `fbt_options.py` Unleashed:

| Опция | По умолчанию | Примечание |
|---|---|---|
| `FIRMWARE_ORIGIN` | `"Unleashed"` | Показывается в информации об устройстве |
| `TARGET_HW` | `7` | Flipper Zero (f7); см. [аппаратные таргеты](/ru/dev/hardware-targets) |
| `COMPACT` | `1` | Оптимизация по размеру |
| `DEBUG` | `1` | Для устанавливаемых сборок указывайте `DEBUG=0` |
| `DIST_SUFFIX` | `"local"` | Суффикс в именах выходных файлов |
| `COPRO_STACK_TYPE` | `"ble_light"` | `ble_full` поддерживается, но может не влезть в отладочную сборку |
| `FIRMWARE_APP_SET` | `"default"` | См. ниже |

### Наборы приложений прошивки {#firmware-app-sets}

Какие приложения попадают в прошивку, задаёт `FIRMWARE_APPS` — словарь *имя конфигурации → кортеж app ID*. Нужный
набор выбирается через `FIRMWARE_APP_SET`. В Unleashed определены два набора:

```python
FIRMWARE_APPS = {
    "default": [
        # Svc
        "basic_services",
        # Apps
        "main_apps",
        "system_apps",
        # Settings
        "settings_apps",
    ],
    "unit_tests": [
        "basic_services",
        "updater_app",
        "radio_device_cc1101_ext",
        "unit_tests",
        "infrared",
        "archive",
    ],
}
```

Например, собрать образ с юнит-тестами:

```sh
./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests
```

Почему для этой сборки нужен `DEBUG=0` — см. [Юнит-тесты](/ru/dev/unit-tests).

## Связанные страницы

- [Сборка прошивки](/ru/dev/build)
- [Манифесты приложений (.fam)](/ru/dev/app-manifests)
- [Отладка приложений](/ru/dev/debugging)
- [OTA-обновления](/ru/dev/ota)
