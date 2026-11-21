---
title: ESP32 & Wi-Fi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-readme, unleashed-docs, unleashed-src]
---
# ESP32 & Wi-Fi

The Flipper Zero has no Wi-Fi of its own. Wi-Fi tools come from an **ESP32** (or ESP8266) board on the GPIO header,
which does the radio work and talks to a Flipper app over the UART.

## Which board

| Board | Typical use |
|---|---|
| **Official Wi-Fi Developer Board** (ESP32-S2) | Ships with Black Magic debug-probe firmware for [debugging](/gpio/devboard). Can be reflashed with Marauder |
| **ESP32 Marauder boards** (various ESP32 / ESP32-S2 / ESP32-S3 boards, combo boards) | Wi-Fi and BLE scanning, packet capture, wardriving |
| **ESP8266 boards** | Wi-Fi Scanner and Deauther firmware |
| **ESP32-CAM** | Camera Suite (camera image on the Flipper screen) |

## Apps

Each of these is only the Flipper side: the board needs the matching firmware on it first.

| App | Pack | What it does |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Front end for Marauder firmware: Wi-Fi and BLE scanning, packet capture, wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Lists nearby Wi-Fi networks, for the ESP8266 Scanner firmware |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Front end for the DSTIKE Deauther firmware |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Live image from an ESP32-CAM on the Flipper screen, with photo capture |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | A second ESP32-CAM app: live feed and photo capture |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Front end for the Ghost ESP firmware |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Runs a captive-portal access point on the ESP32 |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | For Deauther v2 firmware by @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Flashes firmware onto an ESP board from the Flipper, over UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Fires an IFTTT webhook through an ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Wi-Fi mapping with an ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Shows a Pwnagotchi face and status on the Flipper, over UART |

Full list of module apps: [Modules and their apps](/gpio/module-apps).

## ESP32 Marauder

[ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder) by justcallmekoko is firmware for ESP32 boards. On the
Flipper it is used through the **WiFi Marauder** app from the extra app packs, which sends commands to the board and shows
its output.

Typical workflow:

1. **Flash Marauder** onto the ESP32 board (see the flasher below).
2. Power the Flipper off, plug the board into the GPIO header, power on.
3. Open the Marauder app under `Apps → GPIO` and choose a command (scan access points, sniff, wardrive, etc.).
4. Results are shown in the app; captures and wardriving logs are stored according to the board and app settings
   (see the Marauder documentation for your board).

Full usage guide for the Wi-Fi Devboard with Marauder (by UberGuidoZ):
[UberGuidoZ/Flipper → Wifi_DevBoard](https://github.com/UberGuidoZ/Flipper/tree/main/Wifi_DevBoard).

::: warning Legal
Scanning is passive, but deauthentication and other active Wi-Fi attacks are illegal against networks you don't own
or have no permission to test.
:::

## ESP32 Web Flasher

::: tip Unleashed
The Unleashed team runs a browser-based flasher for popular ESP32 modules:
**[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)**. It works fully in the browser, so
you don't need to install esptool. Use a browser with Web Serial support (Chromium-based browsers).
:::

General steps:

1. Unplug the ESP32 board from the Flipper and connect it to the computer with USB.
2. If the board doesn't enter flashing mode by itself, hold **BOOT**, tap **RESET**, release **BOOT**.
3. Open the flasher, pick the board and firmware, click connect and select the board's serial port.
4. Wait for the flash to finish, reset the board, plug it back into the Flipper (Flipper powered off).

Other ways to flash an ESP board:

- **ESP flasher** Flipper app — flashes a `.bin` from the Flipper's SD card through the GPIO UART:
  [0xchocolate/flipperzero-esp-flasher](https://github.com/0xchocolate/flipperzero-esp-flasher).
- Windows guide for esptool / Flash Download Tool:
  [SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32).
- The [GPIO app's USB-UART Bridge](/gpio/gpio-app) with `RTS/DTR Pins` can act as the USB adapter for boards
  without their own USB port.

::: tip Going back to the debug firmware
If you put Marauder on the official Wi-Fi Devboard and want the Black Magic debugger back, reflash it with
`ufbt devboard_flash` as described in [Devboard: firmware update](/gpio/devboard-firmware).
:::

## Wi-Fi Wardriving Map

::: tip Unleashed
**[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)** combines and displays several WiGLE-format wardriving
captures from ESP32 Marauder and other tools on one map.
:::

1. Run a wardrive with Marauder (wardriving needs a GPS module connected to the ESP32 board).
2. Copy the WiGLE-format CSV logs to your computer.
3. Open the map and load one or more files; the networks are plotted together.

For Sub-GHz captures and other files with coordinates there is a separate map,
[map.unleashedflip.com](https://map.unleashedflip.com).

## Other ESP firmware

| Firmware | Board | Links |
|---|---|---|
| Wi-Fi Scanner | ESP8266 / ESP32 | [How to use](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/) |
| ESP8266 Deauther | ESP8266 | [How to use](https://github.com/SequoiaSan/FlipperZero-Wifi-ESP8266-Deauther-Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-Wifi-ESP8266-Deauther-Module/) |
| Camera Suite | ESP32-CAM | [How to use](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |

The matching Flipper apps are in the Base/Extra packs:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest).

## Troubleshooting

- **App shows no response from the board:** the board isn't flashed with the firmware the app expects, TX/RX are on the
  wrong UART, or the board isn't fully inserted.
- **Strange behaviour on the UART:** another feature listens on the same pins. Check
  `Settings → Expansion Modules → Listen UART` (see [Expansion modules](/gpio/expansion-modules)) and
  `Settings → System → Log Device`.
- **Board not found by the web flasher:** use a data-capable USB cable, enter bootloader mode manually, try another USB
  port or browser.

## Related

- [Wi-Fi Devboard](/gpio/devboard)
- [External modules](/gpio/external-modules)
- [GPS](/gpio/gps)
