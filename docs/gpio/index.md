---
title: GPIO & Modules
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# GPIO & Modules

The 18-pin header on top of the Flipper Zero turns it into a hardware tool: it can power and talk to external
modules, act as a USB-UART adapter, flip pins by hand for testing, and serve as a target for a hardware debugger.

![Flipper Zero GPIO header](/img/remote/f9f4fe12522d6f9d.png)

## Basics

| Page | What's inside |
|---|---|
| [GPIO pinout](/gpio/pinout) | All 18 pins, voltages, current limits, 5 V on pin 1, 3.3 V / 5 V tolerance |
| [GPIO app](/gpio/gpio-app) | `Main Menu → GPIO`: USB-UART Bridge, GPIO Manual Control, 5V on GPIO; CLI `gpio` and `i2c` |
| [External modules](/gpio/external-modules) | Overview of module types and which pins each one uses |
| [Expansion modules](/gpio/expansion-modules) | `Settings → Expansion Modules` and the Expansion Module Protocol |
| [Modules and their apps](/gpio/module-apps) | Every module the app packs support, and what each app does |

## Modules

| Page | Module |
|---|---|
| [External CC1101](/subghz/external-cc1101) | Sub-GHz radio with a stronger front end (covered in the Sub-GHz section) |
| [ESP32 / Wi-Fi](/gpio/esp32) | Wi-Fi Devboard, ESP32 Marauder, the Unleashed web flasher and wardriving map |
| [NRF24](/gpio/nrf24) | 2.4 GHz nRF24L01 sniffer and MouseJack |
| [SIM800](/gpio/sim800) | GSM module: calls, SMS, phonebook, USSD (built-in Unleashed app) |
| [GPS](/gpio/gps) | Location from the companion phone (GPS service) and NMEA GPS modules on UART |
| [Video Game Module](/gpio/video-game-module) | RP2040 module with video out and a motion sensor |

## Wi-Fi Developer Board

| Page | What's inside |
|---|---|
| [Devboard: getting started](/gpio/devboard) | Preparing the Flipper, plugging in, USB and Wi-Fi connection |
| [Devboard: debugging and logs](/gpio/devboard-debug) | Black Magic / DAPLink, VS Code debugging, reading UART logs |
| [Devboard: firmware update](/gpio/devboard-firmware) | Flashing the board's own firmware with uFBT |

::: tip Unleashed
Unleashed ships extra GPIO tooling out of the box: the [SIM800](/gpio/sim800) app (`Apps → GPIO → SIM800`), external
CC1101 support with amplifier control in Sub-GHz, external IR module output in `Infrared → GPIO Settings`, and a large
set of GPIO plugins in the extra app packs. See [External modules](/gpio/external-modules).
:::

::: warning Before plugging anything in
Power the Flipper off before connecting a module, and push the module all the way into the header. Hot-plugging a
module with a large capacitive load can corrupt the microSD card, because the card and pin 9 share the same 3.3 V rail.
:::
