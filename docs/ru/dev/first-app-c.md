---
title: Первое приложение на C
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_your_first_app_in_c.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md]
sources: [unleashed-docs]
---
# Первое приложение на C

Приложения на C — это файлы `.fap` (Flipper App Package). Они лежат на microSD-карте и загружаются по запросу,
поэтому пересобирать прошивку не нужно. Собирать их будем через **uFBT**.

## 1. Настройка окружения

Понадобятся Flipper Zero, USB-кабель и на Windows / macOS / Linux:

- [**uFBT**](https://github.com/flipperdevices/flipperzero-ufbt) («micro Flipper Build Tool») — версия
  [fbt](/ru/dev/fbt) со всем необходимым для разработки приложений. Ставится командой `pip install ufbt` (подробности
  в README uFBT).
- [**Visual Studio Code**](https://code.visualstudio.com/) — рекомендуемая IDE. Другие тоже подойдут, но для
  интеграции с uFBT их придётся настраивать вручную.

::: tip Unleashed
По умолчанию uFBT качает **официальный** SDK. Чтобы собирать под Unleashed, выполните один раз (и используйте те же
флаги при каждом следующем обновлении):

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Если на Флиппере релизная сборка, используйте `--channel=release`. Версия SDK должна совпадать с прошивкой на
устройстве — см. [шаг 5](#_5-build-and-run-the-app).
:::

## 2. Генерация шаблона приложения

1. Создайте папку для приложения, например `test_app`.
2. Откройте в этой папке терминал и выполните:

   ```sh
   ufbt create APPID=test_app
   ```

   uFBT сгенерирует структуру файлов.
3. Выполните:

   ```sh
   ufbt vscode_dist
   ```

   Это настроит VS Code для сборки и отладки приложения прямо из IDE.

::: warning
`APPID` может содержать только строчные латинские буквы `a-z`, цифры `0-9` и `_`.
:::

Получится такая структура:

```
test_app/
├── application.fam
├── test_app.c
├── test_app.png
├── .github/
│   └── workflows/
|       └── build.yml
└── images/
    └── .gitkeep
```

| Файл | Назначение |
|---|---|
| `application.fam` | Манифест, по которому uFBT понимает, как собирать приложение — см. [Манифесты приложений](/ru/dev/app-manifests) |
| `test_app.c` | Основной исходник с точкой входа |
| `test_app.png` | Иконка приложения (10×10, 1 бит) |
| `.github/workflows/build.yml` | Конфигурация GitHub Actions — [подробнее](https://github.com/marketplace/actions/build-flipper-application-package-fap) |
| `images/` | Ваши графические ресурсы |
| `images/.gitkeep` | Заглушка, чтобы Git отслеживал пустую папку `images/` |

## 3. Код шаблона

```c
#include <furi.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm test_app!");

    return 0;
}
```

Что здесь что:

- `#include <furi.h>` — главный заголовок **Furi**, ядра прошивки Флиппера ([Furi API](/ru/dev/furi-api)).
- `#include <test_app_icons.h>` — нужен, если приложение использует картинки. uFBT сам конвертирует PNG из `images/`
  во внутренний формат Флиппера и генерирует этот заголовок.
- `int32_t` — обычный тип возвращаемого значения главной функции приложения.
- `UNUSED(p);` — макрос, глушащий предупреждение о неиспользуемом параметре.
- `FURI_LOG_I` — пишет сообщение уровня `info` в лог Флиппера. Смотреть через `ufbt cli` → `log info`.
- `return 0;` — успешное завершение, по соглашению C.

## 4. Добавляем GUI

Откройте папку приложения в VS Code (**File → Open Folder…**). Когда предложат, поставьте рекомендуемые расширения.

Выведем на экран две строки: `Hello world` и `I'm test_app!`. Замените содержимое `test_app.c` на:

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);
    DialogMessage* message = dialog_message_alloc();
    dialog_message_set_header(message, "Hello world", 64, 20, AlignCenter, AlignTop);
    dialog_message_set_text(message, "I'm test_app!", 64, 32, AlignCenter, AlignTop);
    dialog_message_show(dialogs, message);
    dialog_message_free(message);
    furi_record_close(RECORD_DIALOGS);

    return 0;
}
```

Здесь используется GUI-сервис **Dialogs** — самый простой GUI API. Другие подходы описаны в
[GUI в приложениях](/ru/dev/gui).

## 5. Сборка и запуск приложения {#_5-build-and-run-the-app}

**Быстрый способ:**

1. Подключите Флиппер к компьютеру USB-кабелем.
2. Закройте qFlipper и любые другие программы, занимающие serial-порт Флиппера.
3. Выполните:

   ```sh
   ufbt launch
   ```

   Команда соберёт приложение, загрузит его и запустит на Флиппере.

**Вручную:**

1. Соберите через <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (Windows/Linux) или <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>
   (macOS), либо командой `ufbt` в терминале. Самодостаточный `.fap` (со всеми ресурсами) появится в `dist/`.
2. В qFlipper откройте **File Manager → SD Card → apps → Examples** (создайте папку, если её нет) и перетащите туда
   `.fap`.
3. На Флиппере: `Main Menu → Apps → Examples → ваше приложение`.

**Ожидаемый результат:** экран с заголовком «Hello world» и строкой «I'm test_app!» под ним. Любая кнопка закрывает
его.

::: warning Версия SDK должна совпадать
Версия SDK (API) прошивки на устройстве должна совпадать с SDK, под который собирал uFBT. Если при запуске
приложения появляется ошибка несовпадения API, либо обновите SDK uFBT под вашу прошивку, либо прошейте подходящую
прошивку командой `ufbt flash_usb`. На Unleashed убедитесь, что uFBT использует индекс Unleashed (см. совет в шаге 1)
— иначе `ufbt flash_usb` поставит **официальную** прошивку.
:::

Чтобы увидеть вывод `FURI_LOG_I`: запустите `ufbt cli`, затем `log` (или `log info`, если вы меняли уровень логов
по умолчанию).

## Решение проблем

| Проблема | Решение |
|---|---|
| `ufbt create` не принимает APPID | Только `a-z`, `0-9`, `_` |
| Несовпадение API / SDK при запуске | Обновите SDK uFBT под свою прошивку (индекс Unleashed!) и пересоберите |
| `ufbt launch` не находит устройство | Закройте qFlipper / Lab / любой serial-терминал; переподключите кабель |
| Приложения нет в меню | Оно должно лежать в папке категории внутри `/ext/apps/`, например `/ext/apps/Examples/` |
| В `log` пусто | Запускайте `log` **до** запуска приложения; проверьте уровень логов |

## Что дальше?

- Если C подзабылся, классика — *Язык программирования C* Б. Кернигана и Д. Ритчи.
- [Отладка приложений](/ru/dev/debugging) — пошаговое выполнение под отладчиком.
- [GUI в приложениях](/ru/dev/gui) — ViewPort, Views и Scenes.
- [Манифесты приложений](/ru/dev/app-manifests) — все опции `application.fam`.
- Нет ПК? [Сборка приложений на Android](/ru/dev/android-build).
- Хотите скрипты? [JavaScript на Флиппере](/ru/dev/js-about).
