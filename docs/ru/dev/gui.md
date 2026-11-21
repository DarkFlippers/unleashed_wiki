---
title: GUI в приложениях
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules]
sources: [unleashed-docs, unleashed-src]
---
# GUI в приложениях

Интерфейс приложения строят тремя способами, от самого простого к самому гибкому:

1. [Dialogs](#using-dialogs) — несколько окон-сообщений, без собственной отрисовки.
2. [ViewPort](#using-a-viewport) — одна полноэкранная область, которую вы рисуете сами; идеально для игр.
3. [Views и Scenes](#using-views-and-scenes) — многоэкранные приложения с меню и навигацией (большинство встроенных
   приложений).

## Базовые понятия

### Event loop

Механизм асинхронной обработки событий. Вместо опроса или блокирующего ожидания событий (нажатий кнопок, принятых
пакетов, таймеров) вы регистрируете функции-обработчики, которые вызываются при наступлении события, и главный цикл
свободен для другой работы.

### Canvas

**Canvas** — «сырая» область рисования без абстракций. Рисовать прямо на нём полезно для нестандартных визуальных
элементов (например, в играх), но большинству приложений это не нужно.

### ViewPort

**ViewPort** определяет, как отрисовывается область экрана заданного положения и размера и как она реагирует на ввод.
Несколько ViewPort образуют *стек отрисовки*, рисуемый снизу вверх, поэтому они могут перекрываться. ViewPort можно
включать и выключать после создания.

### Model, View и View Dispatcher

Они отделяют GUI от данных — так приложение проще писать и тестировать.

- **Model** — данные; технически это структура в памяти.
- **View** — отрисовка и обработка ввода. Читает Model при отрисовке и меняет её при обработке событий.
- **View Dispatcher** — хранит ссылки на все View приложения и переключает их по запросу.

### View-модули

Готовые полноэкранные шаблоны (View + Model) для типичных интерфейсов Флиппера, входящие в прошивку
(`applications/services/gui/modules/`):

| Модуль | Типичное применение |
|---|---|
| `button_menu` | Меню из крупных кнопок |
| `button_panel` | Сетка выбираемых кнопок |
| `byte_input` | Ввод hex-байтов |
| `date_time_input` | Ввод даты и времени |
| `dialog_ex` | Диалог с заголовком, текстом, иконкой и до трёх кнопок |
| `empty_screen` | Пустой экран |
| `file_browser` | Выбор файла на SD-карте |
| `loading` | Анимация «Loading…» |
| `menu` | Список с иконками в стиле главного меню |
| `number_input` | Ввод числа |
| `popup` | Временное сообщение с таймаутом |
| `submenu` | Простой вертикальный список пунктов |
| `text_box` | Прокручиваемый текст |
| `text_input` | Экранная клавиатура |
| `variable_item_list` | Список настроек со значениями ◀ ▶ |
| `widget` | Свободная композиция из текста, иконок и кнопок |

| | | |
|---|---|---|
| ![submenu](/img/dev/submenu.png) `submenu` | ![dialog](/img/dev/dialog.png) `dialog_ex` | ![text_input](/img/dev/text_input.png) `text_input` |
| ![byte_input](/img/dev/byte_input.png) `byte_input` | ![text_box](/img/dev/text_box.png) `text_box` | ![widget](/img/dev/widget.png) `widget` |
| ![loading](/img/dev/loading.png) `loading` | ![empty](/img/dev/empty.png) `empty_screen` | |

Исходный код: [applications/services/gui/modules](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules).

### Scene и Scene Manager

**Scene** (сцена) управляет поведением приложения на одном экране. Например, приложение GPIO объявляет такие сцены в
`applications/main/gpio/scenes/gpio_scene_config.h`:

| Сцена | Экран |
|---|---|
| `gpio_scene_start` | Стартовое меню |
| `gpio_scene_usb_uart` | Интерфейс моста USB-UART |
| `gpio_scene_usb_uart_cfg` | Настройки моста USB-UART (файл `gpio_scene_usb_uart_config.c`) |
| `gpio_scene_usb_uart_close_rpc` | «Connection Is Active! Disconnect from PC or phone to use this function.» — показывается, если открыть мост USB-UART, пока подключены qFlipper или мобильное приложение |
| `gpio_scene_test` | Ручное управление GPIO |

Из стартового меню можно перейти в ручное управление или в режим моста USB-UART, а из моста — в его настройки.

Каждая сцена реализует три функции:

- `on_enter` — инициализация view сцены;
- `on_exit` — деинициализация и освобождение ресурсов;
- `on_event` — обработка входящих событий.

Обработчик событий может переключить приложение на другую сцену — например, выбор пункта меню ведёт в
соответствующую сцену. Эти переходы выполняет **Scene Manager**, он же хранит историю навигации, что делает сложную
навигацию управляемой.

## Подходы к разработке GUI

Чем сложнее интерфейс, тем больше GUI-абстракций понадобится.

### Dialogs {#using-dialogs}

Самый простой подход — подходит, когда весь интерфейс сводится к диалоговым окнам. API:
[`dialogs.h`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/dialogs/dialogs.h).

![Подход с Dialogs](/img/dev/app_dev_gui_dialogs.jpg)

**Плюсы:** минимум кода.
**Минусы:** только диалоги, сложный GUI не построить; диалоги **синхронные** — пока пользователь не нажмёт кнопку,
никакой другой код приложения не выполняется.

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app(void* p) {
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

### ViewPort {#using-a-viewport}

Вы создаёте один полноэкранный ViewPort, который рисует экран и обрабатывает весь ввод.

![Подход с ViewPort](/img/dev/app_dev_gui_viewport.png)

**Плюсы:** просто — один ViewPort, никаких других абстракций; быстро и удобно для игр; полный контроль над экраном.
**Минусы:** нет помощников навигации; нет переиспользуемых View.

Примеры:

- многие [отладочные утилиты](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug)
- [диалог BLE-сопряжения](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/bt/bt_service/bt.c)
- [Dolphin Passport](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/settings/dolphin_passport/passport.c)
- большинство игр, например [Snake](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/snake_game),
  входящая в Unleashed

### Views и Scenes {#using-views-and-scenes}

Основной подход для приложений со сложным иерархическим интерфейсом — так устроено большинство приложений Флиппера.

![Подход с Views и Scenes](/img/dev/app_dev_gui_views_and_scenes.jpg)

**Плюсы:** поддержка сложной навигации; переиспользование view; много готовых view-модулей.
**Минусы:** нужно время, чтобы вникнуть; более сложная реализация.

Примеры (исходники Unleashed):

- [Desktop](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop)
- [iButton](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton)
- [Infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared)
- [GPIO](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio)
- [NFC](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc)
- [RFID](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid)
- [Sub-GHz](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz)

::: tip
В приложениях на сценах список сцен лежит в `scenes/<app>_scene_config.h`, а каждый файл `scenes/*.c` реализует
один экран. Чтение этих файлов — самый быстрый способ понять, как устроены меню приложения.
:::

## Какой подход выбрать

| Нужно… | Используйте |
|---|---|
| Показать сообщение или спросить да/нет | Dialogs |
| Игра, визуализатор или один нестандартный экран | ViewPort |
| Меню, настройки, выбор файлов, несколько экранов | Views и Scenes |

## Почитать ещё (внешние ресурсы)

- [A Visual Guide to Flipper Zero GUI Modules](https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/) — Christopher Hranj
- [Scenes Demo Application Tutorial](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes#scenes-demo-application-tutorial) — Derek Jamison
- YouTube-туториалы Derek Jamison:
  [Using ViewPort](https://www.youtube.com/watch?v=5QwwihbxkC8) ·
  [Creating UI using Scenes](https://www.youtube.com/watch?v=YbskaB6caqk&list=PLM1cyTMe-PYJaMQ6TWeK1mAWxORdjYJZ5&index=8) ·
  [SceneManager Best Practice](https://www.youtube.com/watch?v=vQAk7fC_no4)

## Связанные страницы

- [Первое приложение на C](/ru/dev/first-app-c)
- [Furi API](/ru/dev/furi-api)
- [JavaScript на Флиппере](/ru/dev/js-about) — JS-скрипты могут использовать многие из этих view-модулей
