---
title: GUI in apps
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules]
sources: [unleashed-docs, unleashed-src]
---
# GUI in apps

This page explains the basic GUI concepts of the Flipper firmware and compares the three ways to build an app's
interface, from the simplest to the most capable:

1. [Dialogs](#using-dialogs) — a few message boxes, no custom drawing.
2. [ViewPort](#using-a-viewport) — one full-screen area you draw yourself; ideal for games.
3. [Views & Scenes](#using-views-and-scenes) — multi-screen apps with menus and navigation (most built-in apps).

## Basic concepts

### Event loop

An asynchronous event-handling mechanism. Instead of polling or blocking while waiting for events (button presses,
received packets, timers), you register handler functions that are called when the event happens, so the main loop
is free for other work.

### Canvas

The **canvas** is a raw drawing area with no abstractions. Drawing directly on it is useful for custom visual
elements (e.g. in games), but most apps don't need it.

### ViewPort

A **ViewPort** defines how a screen area of a given position and size is drawn and how it reacts to input.
Several ViewPorts form a *drawing stack* rendered bottom to top, so they can overlap. A ViewPort can be enabled or
disabled after creation.

### Model, View and View Dispatcher

These separate the GUI from the data, which makes apps easier to develop, maintain and test.

- **Model** — the data; technically a structure in memory.
- **View** — rendering and input handling. It reads the Model for drawing and modifies it when handling events.
- **View Dispatcher** — holds references to all Views the app needs and switches between them on request.

### View modules

Ready-made full-screen templates (View + Model) for typical Flipper UIs, included in the firmware
(`applications/services/gui/modules/`):

| Module | Typical use |
|---|---|
| `button_menu` | Menu of large buttons |
| `button_panel` | Grid of selectable buttons |
| `byte_input` | Enter hex bytes |
| `date_time_input` | Enter date and time |
| `dialog_ex` | Dialog with header, text, icon and up to three buttons |
| `empty_screen` | Blank screen |
| `file_browser` | Pick a file on the SD card |
| `loading` | "Loading…" animation |
| `menu` | Main-menu-style list with icons |
| `number_input` | Enter a number |
| `popup` | Temporary message with timeout |
| `submenu` | Simple vertical list of items |
| `text_box` | Scrollable text |
| `text_input` | On-screen keyboard |
| `variable_item_list` | Settings list with ◀ ▶ values |
| `widget` | Free composition of text, icons and buttons |

| | | |
|---|---|---|
| ![submenu](/img/dev/submenu.png) `submenu` | ![dialog](/img/dev/dialog.png) `dialog_ex` | ![text_input](/img/dev/text_input.png) `text_input` |
| ![byte_input](/img/dev/byte_input.png) `byte_input` | ![text_box](/img/dev/text_box.png) `text_box` | ![widget](/img/dev/widget.png) `widget` |
| ![loading](/img/dev/loading.png) `loading` | ![empty](/img/dev/empty.png) `empty_screen` | |

Source code: [applications/services/gui/modules](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules).

### Scene and Scene Manager

A **Scene** controls the app's behaviour on one screen. For example, the GPIO app declares these scenes in
`applications/main/gpio/scenes/gpio_scene_config.h`:

| Scene | Screen |
|---|---|
| `gpio_scene_start` | Start menu |
| `gpio_scene_usb_uart` | USB-UART bridge interface |
| `gpio_scene_usb_uart_cfg` | USB-UART bridge settings (file `gpio_scene_usb_uart_config.c`) |
| `gpio_scene_usb_uart_close_rpc` | "Connection Is Active! Disconnect from PC or phone to use this function." — shown when you open the USB-UART bridge while qFlipper or the mobile app is connected |
| `gpio_scene_test` | Manual GPIO control |

From the start menu you go to manual control or to USB-UART bridge mode, and from the bridge to its settings.

Each scene implements three functions:

- `on_enter` — initialise the scene's views;
- `on_exit` — de-initialise and free resources;
- `on_event` — handle incoming events.

An event handler can switch to another scene — e.g. selecting a menu item goes to the matching scene. The
**Scene Manager** performs these transitions and keeps the navigation history, which makes complex navigation flows
manageable.

## Approaches to GUI development

The more complex your interface, the more GUI abstractions you need.

### Using Dialogs

The simplest approach — suitable when the whole interface is just dialog boxes. API:
[`dialogs.h`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/dialogs/dialogs.h).

![Dialogs approach](/img/dev/app_dev_gui_dialogs.jpg)

**Pros:** simple and easy.
**Cons:** only dialogs, no complex GUIs; dialogs are **synchronous** — no other app code runs until the user presses
a button.

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

### Using a ViewPort

You create a single full-screen ViewPort that draws the display and handles all input.

![ViewPort approach](/img/dev/app_dev_gui_viewport.png)

**Pros:** easy — one ViewPort, no other abstractions; fast and game-friendly; full control over the screen.
**Cons:** no navigation helpers; no reusable Views.

Examples:

- many of the [debug tools](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug)
- the [BLE pairing dialog](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/bt/bt_service/bt.c)
- [Dolphin Passport](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/settings/dolphin_passport/passport.c)
- most games, e.g. [Snake](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/snake_game)
  shipped with Unleashed

### Using Views and Scenes

The main approach for apps with complex, hierarchical UIs — used by most Flipper apps.

![Views and Scenes approach](/img/dev/app_dev_gui_views_and_scenes.jpg)

**Pros:** supports complex navigation; views are reused; many ready view modules.
**Cons:** takes time to sink in; more complex implementation.

Examples (Unleashed source):

- [Desktop](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop)
- [iButton](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton)
- [Infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared)
- [GPIO](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio)
- [NFC](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc)
- [RFID](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid)
- [Sub-GHz](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz)

::: tip
In scene-based apps the list of scenes is in `scenes/<app>_scene_config.h`, and each `scenes/*.c` file implements
one screen. Reading these is the fastest way to understand how an app's menus are built.
:::

## Choosing an approach

| You want… | Use |
|---|---|
| Show a message or ask yes/no | Dialogs |
| A game, visualiser, or one custom screen | ViewPort |
| Menus, settings, file selection, several screens | Views & Scenes |

## Learn more (external)

- [A Visual Guide to Flipper Zero GUI Modules](https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/) by Christopher Hranj
- [Scenes Demo Application Tutorial](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes#scenes-demo-application-tutorial) by Derek Jamison
- YouTube tutorials by Derek Jamison:
  [Using ViewPort](https://www.youtube.com/watch?v=5QwwihbxkC8) ·
  [Creating UI using Scenes](https://www.youtube.com/watch?v=YbskaB6caqk&list=PLM1cyTMe-PYJaMQ6TWeK1mAWxORdjYJZ5&index=8) ·
  [SceneManager Best Practice](https://www.youtube.com/watch?v=vQAk7fC_no4)

## Related pages

- [Your first app in C](/dev/first-app-c)
- [Furi API](/dev/furi-api)
- [JavaScript on Flipper](/dev/js-about) — JS scripts can use many of the same view modules
