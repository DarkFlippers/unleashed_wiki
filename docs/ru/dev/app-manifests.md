---
title: Манифесты приложений (.fam)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppManifests.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/scripts/ufbt/project_template/app_template]
sources: [unleashed-docs, unleashed-src]
---
# Манифесты приложений (.fam)

Каждый компонент прошивки — сервисы, пользовательские приложения, страницы настроек — разрабатывается независимо, а
его файл-манифест `application.fam` описывает базовые свойства компонента и его связи с остальной системой.

При сборке `fbt` собирает все манифесты, разрешает зависимости и собирает **только** те компоненты, на которые
ссылается текущая конфигурация сборки (см. [fbt → наборы приложений](/ru/dev/fbt#firmware-app-sets)).

## Описание приложения

Манифест — это фрагмент на Python с вызовом `App()` и именованными аргументами. Обязательны только **`appid`** и
**`apptype`**; часть остальных имеет смысл только для определённых типов приложений.

### Типы приложений (`apptype`)

`apptype` — член перечисления `FlipperAppType`:

| Значение | Тип компонента |
|---|---|
| `SERVICE` | Системный сервис, создаётся на раннем этапе загрузки |
| `SYSTEM` | Не показывается в меню; запускается другими приложениями или из CLI |
| `APP` | Обычное приложение в главном меню |
| `PLUGIN` | Собирается в составе прошивки и помещается в меню Plugins |
| `DEBUG` | Видно только в меню Debug при включённом режиме отладки |
| `ARCHIVE` | Единственное приложение Archive |
| `SETTINGS` | Помещается в системное меню Settings |
| `STARTUP` | Колбэк, вызываемый при старте системы; отдельного приложения не создаёт |
| `EXTERNAL` | Собирается как приложение `.fap` |
| `METAPACKAGE` | Без кода; служит для объявления зависимостей и наборов приложений |

### Общие параметры

| Параметр | Значение |
|---|---|
| `appid` | Строковый ID приложения в системе сборки. Используется в конфигурациях сборки и при разрешении зависимостей и конфликтов |
| `apptype` | См. таблицу выше |
| `name` | Имя, отображаемое в меню |
| `entry_point` | C-функция — точка входа. Имена C++ манглируются — оборачивайте функцию в `extern "C"` |
| `flags` | Внутренние флаги системных приложений. **Не используйте** |
| `cdefines` | Define препроцессора, объявляемые глобально для других приложений, если это приложение есть в сборке. Для внешних приложений — используются при сборке самого приложения |
| `requires` | App ID, которые добавляются в сборку всякий раз, когда собирается это приложение |
| `conflicts` | App ID, с которыми приложение конфликтует; если любой из них есть в сборке, `fbt` прерывает сборку |
| `provides` | Функционально идентичен `requires` |
| `stack_size` | Размер стека в байтах, выделяемый при запуске. Слишком мало — падение из-за переполнения стека; слишком много — меньше кучи для приложения |
| `icon` | Анимированная иконка из встроенных ресурсов, используется, когда приложение встроено в прошивку |
| `order` | Порядок внутри группы (меньше — раньше). Используется для startup-хуков и пунктов меню |
| `sdk_headers` | Заголовки C этого приложения, включаемые в API для внешних приложений |
| `targets` | Совместимые [аппаратные таргеты](/ru/dev/hardware-targets). По умолчанию `["all"]` |
| `resources` | Папка в исходниках приложения, упаковываемая как ресурсы для SD-карты (только если приложение в сборке). По умолчанию `""` — ничего |

::: tip
Чтобы подобрать `stack_size`, профилируйте потребление памяти приложением [командами CLI](/ru/dev/cli) `top` и
`free`.
:::

### Параметры для внешних приложений (FAP)

| Параметр | Значение |
|---|---|
| `sources` | Маски файлов для сбора исходников в папке приложения. По умолчанию `["*.c*"]` (C и C++). Папка `lib` зарезервирована под `fap_private_libs`. Маски, начинающиеся с `!`, исключают файлы; маски без подстановочных символов (`*`, `?`) считаются буквальными путями. Пример: `["*.c*", "!plugins"]` |
| `fap_version` | Строка версии, по умолчанию `"0.1"`. Можно и кортежем `(x, y)`. Дополнительные части через точку допустимы, но в `.fap` сохраняются только major и minor |
| `fap_icon` | Файл `.png`, 1 бит на пиксель, 10×10 px, встраивается в `.fap` |
| `fap_libs` | Дополнительные библиотеки для линковки — дают доступ к функциям, не экспортируемым прошивкой, ценой большего размера `.fap` и расхода RAM |
| `fap_category` | Подкатегория приложения; также определяет папку внутри `apps/` на SD-карте |
| `fap_description` | Краткое описание (может быть пустым) |
| `fap_author` | Автор (может быть пустым) |
| `fap_weburl` | Домашняя страница (может быть пустой) |
| `fap_icon_assets` | Папка с графическими ресурсами, которые обрабатываются и собираются вместе с приложением |
| `fap_extbuild` | Части исходников, собираемые внешними инструментами: список `ExtFile(path="file name", command="shell command")` |
| `fal_embedded` | Boolean, по умолчанию `False`. Только для типа `PLUGIN`: встроить плагин в `.fap` хост-приложения как ресурс; при запуске он распаковывается в `apps_assets/APPID` |
| `fap_private_libs` | Библиотеки, поставляемые исходниками вместе с приложением — см. ниже |

#### Внешние команды сборки (`fap_extbuild`)

Команды выполняются из корня прошивки. Промежуточные файлы должны попадать во временную папку сборки приложения.
`fbt` раскрывает такие переменные (и другие внутренние):

- `${FAP_WORK_DIR}` — временная папка сборки приложения
- `${FAP_SRC_DIR}` — папка с исходниками приложения

Пример — сборка приложения из исходников на Rust:

```python
    sources=["target/thumbv7em-none-eabihf/release/libhello_rust.a"],
    fap_extbuild=(
        ExtFile(
            path="${FAP_WORK_DIR}/target/thumbv7em-none-eabihf/release/libhello_rust.a",
            command="cargo build --release --verbose --target thumbv7em-none-eabihf --target-dir ${FAP_WORK_DIR}/target --manifest-path ${FAP_SRC_DIR}/Cargo.toml",
        ),
    ),
```

#### Приватные библиотеки (`fap_private_libs`)

Исходники библиотек кладутся в подпапку `lib/` внутри папки приложения. Каждая библиотека — вызов `Lib()`:

| Параметр `Lib()` | Значение | По умолчанию |
|---|---|---|
| `name` | Имя папки библиотеки (**обязателен**) | — |
| `fap_include_paths` | Пути (относительно библиотеки), добавляемые в include-путь приложения | `["."]` |
| `sources` | Маски файлов исходников библиотеки относительно её корня | `["*.c*"]` |
| `cflags` | Дополнительные флаги компилятора | `[]` |
| `cdefines` | Дополнительные define препроцессора | `[]` |
| `cincludes` | Дополнительные include-пути относительно корня **приложения** (например, для конфигурационных заголовков) | `[]` |

Пример:

```python
    fap_private_libs=[
            Lib(
                name="mbedtls",
                fap_include_paths=["include"],
                sources=[
                    "library/des.c",
                    "library/sha1.c",
                    "library/platform_util.c",
                ],
                cdefines=["MBEDTLS_ERROR_C"],
            ),
            Lib(
                name="loclass",
                cflags=["-Wno-error"],
            ),
        ],
```

Что с этим делает `fbt`:

- **mbedtls** — собирается из `lib/mbedtls`; `lib/mbedtls/include` добавляется в include-путь приложения;
  компилируются только три перечисленных файла; для её исходников определяется `MBEDTLS_ERROR_C`.
- **loclass** — собираются все исходники из `lib/loclass`; `lib/loclass` добавляется в include-путь; предупреждения
  **не** считаются ошибками (`-Wno-error`) — удобно для большого стороннего кода.

Обе библиотеки линкуются с приложением.

## Полный файл `.fam`

Один файл может описывать несколько приложений. Вот часть `applications/services/bt/application.fam`:

```python
App(
    appid="bt_start",
    apptype=FlipperAppType.STARTUP,
    entry_point="bt_on_system_start",
    order=70,
)

App(
    appid="bt_settings",
    name="Bluetooth",
    apptype=FlipperAppType.SETTINGS,
    entry_point="bt_settings_app",
    stack_size=1 * 1024,
    requires=[
        "bt",
        "gui",
    ],
    order=10,
)
```

Манифест собственного внешнего приложения в том виде, как его генерирует `ufbt create APPID=test_app` (из
`scripts/ufbt/project_template/app_template/application.fam`):

```python
# For details & more options, see documentation/AppManifests.md in firmware repo

App(
    appid="test_app",  # Must be unique
    name="App test_app",  # Displayed in menus
    apptype=FlipperAppType.EXTERNAL,
    entry_point="test_app_app",
    stack_size=2 * 1024,
    fap_category="Examples",
    # Optional values
    # fap_version="0.1",
    fap_icon="test_app.png",  # 10x10 1-bit PNG
    # fap_description="A simple app",
    # fap_author="J. Doe",
    # fap_weburl="https://github.com/user/test_app",
    fap_icon_assets="images",  # Image assets to compile for this application
)
```

Больше примеров — в файлах `.fam` по всей прошивке, например `applications/system/*/application.fam` для
дополнительных приложений Unleashed.

## Связанные страницы

- [Первое приложение на C](/ru/dev/first-app-c)
- [Flipper Build Tool (fbt)](/ru/dev/fbt)
- [Аппаратные таргеты](/ru/dev/hardware-targets)
