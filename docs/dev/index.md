---
title: Development
original: [https://docs.flipper.net/zero/development, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Development

This section is for people who want to go beyond using the Flipper: build Unleashed Firmware from source, write
their own apps in C or JavaScript, debug them on real hardware, talk to the device over the command line, or
understand how updates and the hardware work under the hood.

::: tip Unleashed
Unleashed is a fork of the official firmware that stays **fully compatible with the official API and apps**. Almost
everything in the official developer documentation applies as-is. The main things to remember:

- clone `https://github.com/DarkFlippers/unleashed-firmware` instead of the official repo;
- when building apps with **uFBT**, point it at the Unleashed SDK
  (`--index-url=https://up.unleashedflip.com/directory.json`), otherwise your app is built against the official
  SDK and may refuse to load ([details](/dev/build#build-apps-against-the-unleashed-sdk-with-ufbt));
- the firmware origin is reported as `Unleashed`, the current API version on `dev` is **88.27**.
:::

## Building the firmware

| Page | What you get |
|---|---|
| [Building the firmware](/dev/build) | Clone, build and flash Unleashed on Linux, macOS and Windows |
| [Flipper Build Tool (fbt)](/dev/fbt) | Every `fbt` target, option and environment variable |
| [Hardware targets](/dev/hardware-targets) | How `targets/` and `target.json` describe hardware variants (f7, f18) |
| [Building apps on Android](/dev/android-build) | Compile `.fap` apps on a phone with Termux + uFBT, no PC |

## Writing apps

| Page | What you get |
|---|---|
| [Your first app in C](/dev/first-app-c) | uFBT, app template, "Hello world" with a dialog, build and run |
| [App manifests (.fam)](/dev/app-manifests) | All `application.fam` fields, external-app options, private libraries |
| [Furi API](/dev/furi-api) | Hardware and software architecture, Furi core, `furi_assert` / `furi_check` |
| [GUI in apps](/dev/gui) | Dialogs, ViewPort, Views & Scenes, view modules |
| [Debugging apps](/dev/debugging) | SWD probes, VS Code debugging, Furi HAL debug signals |
| [FuriHalBus API](/dev/furi-hal-bus) | Enabling/disabling MCU peripherals correctly, DMA channel map |
| [JavaScript on Flipper](/dev/js-about) | Write scripts in JavaScript instead of C (separate group of pages) |
| Unleashed-only JS modules | [subghz](/dev/js-subghz), [infrared](/dev/js-infrared), [blebeacon](/dev/js-blebeacon), [usbdisk](/dev/js-usbdisk), [i2c](/dev/js-i2c), [spi](/dev/js-spi), [vgm](/dev/js-vgm) — not in stock firmware, not in the official docs |

## Working with the device

| Page | What you get |
|---|---|
| [Command-line interface (CLI)](/dev/cli) | Connect over USB serial; every CLI command with arguments |
| [OTA updates](/dev/ota) | How the updater works, manifest fields, `[XX-YY]` error codes, building packages |
| [Heatshrink tarball format](/dev/tar-heatshrink) | The `.tar.hs` container used for resources in update packages |
| [Hardware](/dev/hardware) | Tech specs, schematics, 3D models, module and devboard drawings |

## Testing

| Page | What you get |
|---|---|
| [Unit tests](/dev/unit-tests) | Build and run the on-device `unit_tests` app, add your own tests |
| [Integration testing](/dev/testing) | The manual test plan used before merging PRs and releases |

## Other useful resources

- Official developer documentation (Doxygen): [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen/) — the place to look up firmware APIs this wiki does not cover, with sections on system programming, app development, JavaScript, expansion modules and file formats
- CLion workspace setup — [guide by Savely Krasovsky](https://krasovs.ky/2022/11/01/flipper-zero-clion.html)
- "Hello world!" plugin tutorials: [English (DroomOne)](https://github.com/DroomOne/Flipper-Plugin-Tutorial),
  [Russian (Pavel Yakovlev)](https://yakovlev.me/hello-flipper-zero)
- [How to write your own app](https://flipper.atmanos.com/docs/overview/intro)

### Project structure of the firmware repository

| Folder | Contents |
|---|---|
| `applications` | Applications and services used in the firmware |
| `assets` | Assets used by applications and services |
| `furi` | Furi Core: OS-level primitives and helpers |
| `debug` | Debug tools: GDB plugins, SVD file, etc. |
| `documentation` | Documentation sources and generator configs |
| `firmware` | Firmware source code |
| `lib` | Own and third-party libraries, drivers |
| `site_scons` | Build helpers |
| `scripts` | Supplementary scripts and Python libraries |
| `targets` | Hardware target definitions (`f7`, `f18`) |

Many of these folders have their own `ReadMe.md` — worth reading.
