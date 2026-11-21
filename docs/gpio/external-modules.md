---
title: External modules
order: 30
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SIM800.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# External modules

Most add-on boards for the Flipper Zero plug straight into the GPIO header and talk to it over one of three buses:
**SPI** (pins 2–5), **UART** (pins 13/14 or 15/16) or **I2C** (pins 15/16). The tables below say what drives each
module and which pins it takes, so you can tell which ones can be used together.

## Module types

| Module | Bus / pins | Driven by | Page |
|---|---|---|---|
| External CC1101 (Sub-GHz) | SPI 2–5, GDO0 on 6, amp control on 7 | Built-in Sub-GHz app (`Radio Settings → Module → External`) | [External CC1101](/subghz/external-cc1101) |
| NRF24L01 (2.4 GHz) | SPI 2–5, CE on 6 | NRF24 Sniffer / Mouse Jacker plugins | [NRF24](/gpio/nrf24) |
| ESP32 / ESP8266 Wi-Fi boards, Wi-Fi Devboard | UART 13/14 (SWD 10/12 for debugging) | Marauder, Wi-Fi Scanner, Deauther plugins; Black Magic firmware | [ESP32](/gpio/esp32), [Devboard](/gpio/devboard) |
| SIM800C / SIM800L GSM | UART 13/14 or 15/16, power from pin 1 | Built-in SIM800 app | [SIM800](/gpio/sim800) |
| GPS (NMEA) | UART | `[NMEA] GPS` plugin | [GPS](/gpio/gps) |
| Video Game Module | UART 13/14, pins 2–7, power | Flipper firmware + module firmware | [Video Game Module](/gpio/video-game-module) |
| Expansion modules (protocol) | UART 13/14 or 15/16 | `Settings → Expansion Modules` | [Expansion modules](/gpio/expansion-modules) |
| External IR LED / IR booster | Pin 2 (PA7), 5 V on pin 1 | Built-in Infrared app (`GPIO Settings`) | see below |
| Temperature / humidity / pressure sensors | depends on the sensor (see README) | `Unitemp` plugin | [Unitemp README](https://github.com/quen0n/unitemp-flipperzero#readme) |
| Any I2C device | I2C 15/16 | `i2c Tools` plugin, CLI `i2c` | [GPIO app](/gpio/gpio-app) |
| ESP32-CAM | UART | Camera Suite plugin | [Camera Suite](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |
| Sentry Safe / Master Lock safes (two wires) | Pin 15 (C1) + GND 8 | SentrySafe plugin | [SentrySafe](/apps/sentry-safe) |

::: tip Unleashed
Unleashed adds support right in the firmware for:
- **External CC1101** over hardware SPI, with external amplifier / LED control (`Ext Amp & LEDs`, enabled by default) in
  `Sub-GHz → Radio Settings`.
- **External IR modules** in `Infrared → GPIO Settings` (auto-detection as in stock firmware).
- The **SIM800** GSM app (`Apps → GPIO → SIM800`).

External radio modules work on every firmware, not only Unleashed. @quen0n wrote the first CC1101 implementation,
for Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307)); the one in use today was written by **Skorp** in the official firmware, and Unleashed
uses that one.

Plugins for the rest (NRF24, Marauder, GPS, Unitemp, i2c Tools, Camera Suite…) are in the Base and Extra packs:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest). See
[SD card apps](/apps/sd-card-apps).
:::

## Pin conflicts

Modules that share a bus can't run at the same time without care. The common clashes:

| Pins | Taken by |
|---|---|
| 2, 3, 4, 5 | SPI: external CC1101, NRF24 (MOSI, MISO, CS, SCK) |
| 6 | CC1101 GDO0 / NRF24 CE |
| 7 | CC1101 amplifier control (E07 modules) |
| 13, 14 | USART: Wi-Fi boards, SIM800, expansion modules, Video Game Module, USB-UART bridge, log output |
| 15, 16 | LPUART or I2C (not both at once) |
| 10, 12 | SWD debugging (Devboard) |

If you use a "combo" board that carries several radios (for example CC1101 + NRF24 + ESP32 on one PCB), follow that
board's own documentation for which pins and plugin settings each radio uses.

## External IR modules

1. Connect the IR LED driver's input to **pin 2 (A7)**, GND to GND, and supply from pin 1 (5 V) if the module needs it.
2. Open `Main Menu → Infrared → GPIO Settings`.
3. Set `Signal Output`:
   - `Flipper` — the built-in IR LED;
   - `2 (A7)` — the external module on pin 2;
   - `Detect` — the firmware detects a connected module automatically.
4. With `2 (A7)` selected you can also switch `5V on GPIO` here. With `Detect` the 5 V item shows `Auto`.

See the [Infrared](/infrared/) section for using remotes.

## General rules

1. **Power off before plugging in.** Hot-plugging large capacitors can corrupt the SD card.
2. **3.3 V logic.** Don't drive Flipper outputs into 5 V logic; inputs are only 5 V tolerant while configured as
   inputs.
3. **Respect the current limits:** 1.2 A on pin 1 and pin 9, 20 mA per I/O pin. See [pinout](/gpio/pinout).
4. **Cross TX and RX** on UART modules: Flipper TX goes to the module's RX.
5. **Insert fully.** A half-inserted module makes intermittent contact.

## Related

- [GPIO pinout](/gpio/pinout)
- [GPIO app](/gpio/gpio-app)
- [Expansion modules](/gpio/expansion-modules)
- [Modules and their apps](/gpio/module-apps)
