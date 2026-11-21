---
title: "JavaScript: using modules"
sidebarTitle: "JS: using modules"
order: 230
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_using_js_modules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules]
sources: [unleashed-docs, unleashed-src]
---
# Using JavaScript modules

The [built-in functions](/dev/js-builtin) are deliberately few. Hardware and system features live in **JS modules**, for example:

- `serial` sends and receives data over UART;
- `badusb` emulates a USB keyboard;
- `math` provides mathematical functions.

Modules are written in C, so they are fast. They ship with the firmware and are stored on the SD card in compiled form as **FAL (Flipper Application File)** plugins. Module sources: [`applications/system/js_app/modules`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules). The list of modules is on [JavaScript overview](/dev/js-about).

## Loading a module

You **must** load a module with `require()` before calling its methods. This loads the module into RAM.

- Load only what you use, to save RAM. (`math`, for example, takes about 21 KB of RAM once loaded.)
- All loaded modules are unloaded automatically when the script ends.
- A module can only be loaded once per script; a second `require()` of the same name fails with `"... module is already installed"`.
- Some modules depend on others and must be loaded after them: `gpio` and `gui` need `event_loop`, and each `gui/*` view needs `gui`.

Pass the module name in quotes:

```js
let notify = require("notification");
```

Then call its methods through the variable:

```js
let notify = require("notification");

notify.success();
print("success notification");
```

The firmware also accepts the SDK-style name `require("@flipperdevices/fz-sdk/notification")`: the prefix is stripped automatically. Names with a slash, like `gui/submenu`, map to the plugin file `js_gui__submenu`.

## What's next

- Browse the module pages in this section, starting with [Event loop](/dev/js-event-loop) and [GUI](/dev/js-gui).
- Study the example scripts in `/ext/apps/Scripts/js_examples/`.
