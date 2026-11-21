---
title: "JavaScript: overview"
sidebarTitle: "JS: overview"
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_about.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app]
sources: [unleashed-docs, unleashed-src]
---
# JavaScript on Flipper Zero

Writing a Flipper Zero app used to mean C, a full toolchain and a lot of reading of other apps' source code. The firmware now ships with a **built-in JavaScript engine**, so you can write a plain `.js` file, copy it to the SD card and run it straight from the device. No compiling on a PC is needed, and scripts are easy to share.

- Scripts live in `/ext/apps/Scripts/` and are launched from `Main Menu → Apps → Scripts`, or from the CLI with `js <path>`.
- The engine is based on [mJS](https://github.com/cesanta/mjs), a JavaScript interpreter designed for microcontrollers: it needs less than 50 KB of flash and about 2 KB of RAM. Flipper keeps mJS's core and adds extras such as compact binary arrays (`ArrayBuffer`, typed arrays).
- Scripts can use the GUI, buttons, USB HID (BadUSB), GPIO, UART, the filesystem and more through **modules** loaded with `require()`.

::: warning mJS is not a browser engine
mJS supports a subset of JavaScript. Most notably, there are **no closures** (a function cannot use variables from the surrounding scope; see [Event loop](/dev/js-event-loop) for the workaround), strings are single-byte without UTF-8 support, and many standard library objects are missing. See the [mJS README](https://github.com/cesanta/mjs) for the full list of limits.
:::

## Getting started

1. [Your first JS app](/dev/js-first-app): write a script, copy it to Flipper, run it from the menu or CLI.
2. [JavaScript SDK](/dev/js-sdk): TypeScript, code completion and one-command upload with `npm start`.
3. [Using JS modules](/dev/js-modules): how `require()` works.

## Language reference

- [Data types](/dev/js-data-types)
- [Built-in functions](/dev/js-builtin): `print`, `delay`, `require`, `load`, string/array methods, SDK compatibility checks.

## Module reference

| Module | `require()` name | Page |
|---|---|---|
| Event loop | `event_loop` | [Event loop](/dev/js-event-loop) |
| GUI | `gui`, `gui/*` | [GUI](/dev/js-gui), [GUI views](/dev/js-gui-views) |
| BadUSB (USB HID keyboard) | `badusb` | [BadUSB](/dev/js-badusb) |
| Device info | `flipper` | [Flipper](/dev/js-flipper) |
| GPIO, ADC, PWM | `gpio` | [GPIO](/dev/js-gpio) |
| Math | `math` | [Math](/dev/js-math) |
| LED / vibro / sound notifications | `notification` | [Notification](/dev/js-notification) |
| UART | `serial` | [Serial](/dev/js-serial) |
| Files and folders | `storage` | [Storage](/dev/js-storage) |

Example scripts for every module are installed with the firmware in `/ext/apps/Scripts/js_examples/` (for example `gui.js`, `badusb_demo.js`, `gpio.js`, `storage.js`). Reading them is the fastest way to learn the API.

## Unleashed extras: modules without official docs {#unleashed-extras}

::: tip Unleashed
Unleashed reports `flipper.firmwareVendor === "unleashed"` and ships **extra JS modules** that stock firmware does not have. The official JS documentation does not cover them, so the pages below were written from the firmware sources (`applications/system/js_app/modules/`) and the TypeScript typings in `packages/fz-sdk/`. Each module is also an SDK "feature", so check for it with `doesSdkSupport([...])` or `checkSdkFeatures([...])` (see [Built-in functions](/dev/js-builtin#sdk-compatibility)) to keep your script working on other firmwares.
:::

The full list of extra features reported by Unleashed is: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`.

| Module | Feature name | What it does | Page |
|---|---|---|---|
| `subghz` | `subghz` | Control the Sub-GHz radio (internal or external CC1101): RX, RSSI, frequency, transmit `.sub` files | [JS: subghz](/dev/js-subghz) |
| `infrared` | `infrared-send` | Send IR signals by protocol or as raw timings | [JS: infrared](/dev/js-infrared) |
| `blebeacon` | `blebeacon` | Broadcast custom BLE advertisement packets (extra beacon) | [JS: blebeacon](/dev/js-blebeacon) |
| `usbdisk` | `usbdisk` | Emulate a USB mass storage device from a disk image | [JS: usbdisk](/dev/js-usbdisk) |
| `i2c` | `i2c` | Talk to I2C devices on the GPIO header | [JS: i2c](/dev/js-i2c) |
| `spi` | `spi` | Talk to SPI devices on the external SPI bus | [JS: spi](/dev/js-spi) |
| `vgm` | `vgm` | Read the IMU (pitch/roll/yaw) of the Video Game Module | [JS: vgm](/dev/js-vgm) |

The GUI module also has views that are missing from the official docs: `button_menu`, `button_panel`, `menu`, `number_input`, `popup`, `vi_list`. They are described on [GUI views](/dev/js-gui-views).

Firmware APIs that this wiki does not cover are listed in the official [Doxygen API reference](https://developer.flipper.net/flipperzero/doxygen/).

## Related

- [Writing apps in C](/dev/first-app-c), for when JS is not fast or flexible enough.
- [BadUSB script format](/badusb/script-format), the classic DuckyScript alternative to the JS `badusb` module.
