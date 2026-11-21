---
title: Apps that ship with Unleashed
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, unleashed-src]
---
# Apps that ship with Unleashed

An Unleashed install has three layers of apps:

1. **System (built-in) apps.** They are built from the firmware repository and installed with every firmware update,
   whatever build you pick.
2. **The Base Apps pack.** A set of community apps, preinstalled in the default build.
3. **The Extra Apps pack.** Many more community apps, preinstalled only in the `e` build.

On top of that you can install anything else yourself, see [Apps on the SD card](/apps/sd-card-apps).

## Build variants

Release files are named `flipper-z-f7-update-(version)(e / c).tgz`:

| Part | Meaning |
|---|---|
| `flipper-z` | for Flipper Zero |
| `f7` | hardware target, the same for every Flipper Zero |
| `update` | update package: updater, assets (apps, IR libraries and so on) and the firmware itself |
| `(version)` | firmware version |
| suffix | which app packs are included (below) |

| Suffix | Base Apps | Extra Apps |
|---|:---:|:---:|
| none (` `) | yes | no |
| `c` | no | no |
| `e` | yes | yes |

- **` ` (no letter)** is the default: firmware, system apps and the Base pack.
- **`c`**: firmware and system apps only, no app pack. Choose it if you want to put together your own set of apps.
- **`e`**: firmware, system apps, Base pack and Extra pack.

The recommended way to install any of these is the [Web Installer](/mobile/web-tools), see also
[Installing Unleashed](/start/install).

::: tip Unleashed
Built-in apps are **not** part of the Base or Extra packs. A firmware update writes them into the `apps/` folder on
the SD card, so installing an app pack can never overwrite or downgrade a system app.
:::

## System apps: shown in the main menu

| App | What it does | Author / origin |
|---|---|---|
| GPIO | GPIO pin control, USB-UART bridge and the 1-Wire/iButton tools | OFW |
| iButton | read, save and emulate Dallas / Cyfral / Metakom keys | OFW |
| Infrared | learn, save and send IR signals, universal remotes | OFW |
| NFC | read, save, emulate and parse NFC cards | OFW |
| 125 kHz RFID | read, save, emulate and write LF RFID tags | OFW |
| Bad USB | Ducky Script payloads over USB, and BadKB over Bluetooth | OFW + BadKB by Willy-JL, ClaraCrazy and XFW contributors |
| U2F | FIDO U2F security token over USB, see [U2F](/apps/u2f) | OFW |
| Clock | clock with screen brightness control, alarm and a basic timer, see [Clock](/apps/clock) | @nymda, with @Willy-JL, @mishamyte and @xMasterX |
| Sub-GHz Remote | bind up to 5 saved `.sub` files to the buttons and send them, see [Sub-GHz Remote](/subghz/remote) | @gid9798 and @xMasterX |

Sub-GHz, Archive, Settings and the system services are compiled into the firmware binary itself.

## System apps: in the Apps folder

These are `.fap` files under `Main Menu → Apps`, sorted into category folders.

| App | Folder | What it does | Author / origin |
|---|---|---|---|
| MFKey | NFC | recover MIFARE Classic keys from nonces collected by Detect Reader, see [MFKey app](/nfc/mfkey-app) | @noproto |
| T5577 | RFID | read, edit and write T5577 blocks, wipe or clear the password, sniff a password, see [T5577 app](/rfid/t5577-app) | @mishamyte |
| Nice O-Code | Sub-GHz | recover the installer code of a Nice O-Code remote and save it as `.sub`, see [Nice O-Code](/subghz/nice-o-code) | @xMasterX |
| Security+ PIN | Sub-GHz | find the keypad PIN in a captured Security+ 2.0 signal, see [Security+ PIN](/subghz/secplus-pin) | @xMasterX |
| Seed Capturer | Sub-GHz | collect Fix + Hop pairs from FAAC SLH, Genius, Erreka and BFT Mitto remotes for offline Seed recovery, see [Seed Capturer](/subghz/seed-capturer) | @xMasterX |
| Remote Analyzer | Sub-GHz | decode one remote at a time on the internal CC1101, with a built-in frequency analyzer, see [Remote Analyzer](/subghz/remote-analyzer) | @xMasterX |
| Sub-GHz RAW Edit | Sub-GHz | open a RAW `.sub` capture, find the signal, trim, merge and decode, see [RAW editor](/subghz/raw-editor) | Lechnio |
| SIM800 | GPIO | drive a SIM800C/SIM800L GSM module: calls, SMS, phonebook, USSD, DTMF, AT terminal, see [SIM800](/gpio/sim800) | @xMasterX |
| FindMy Flipper | Bluetooth | BLE location beacon for Apple Find My / Google Find My Device and others, see [FindMy Flipper](/apps/find-my-flipper) | @MatthewKuKanich |
| USB Keyboard & Mouse | USB | the HID remote over USB, see [HID remote](/apps/hid-remote) | OFW |
| Bluetooth Remote | Bluetooth | the HID remote over Bluetooth, see [HID remote](/apps/hid-remote) | OFW |
| Snake Game | Games | Snake, see [Snake](/apps/snake) | OFW |

The firmware also carries **main menu styles**, small plugins you switch in `Settings → Desktop → Menu Style`,
see [Main menu styles](/apps/menu-styles), and the JavaScript runner used for `.js` scripts (see [JavaScript](/dev/js-about)).

::: info Recent changes
As of the 20 Nov 2026 build, Sub-GHz RAW Edit ships with the firmware and is no longer part of the Extra pack, and
SIM800 is a new built-in app (`Apps → GPIO → SIM800`).
:::

## Base and Extra packs

The community apps are collected by @xMasterX in
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev): that repository holds the full list
and source code, and its [Releases](https://github.com/xMasterX/all-the-plugins/releases/latest) page has the Base and
Extra packs as separate downloads, in case you want to add a pack to a `c` build or update apps between firmware
releases.

To add a pack by hand: download the `.zip` from the [releases page](https://github.com/xMasterX/all-the-plugins/releases/latest), unpack it, and copy the app folders into
the `apps` folder on the SD card (`/ext/apps/`). The pack's API version has to match the firmware's (`Current API:`
at the top of every changelog).

Apps the Unleashed ReadMe points to (each one is in one of the packs):

| App | Where to read more |
|---|---|
| TOTP (Authenticator) | [config file description](https://github.com/akopachov/flipper-zero_authenticator/blob/master/docs/conf-file_description.md) |
| Barcode Generator | [Barcode Generator](/apps/barcode) |
| Multi Converter | [Multi Converter](/apps/multi-converter) |
| WAV Player | [sample files and how to convert](https://github.com/UberGuidoZ/Flipper/tree/main/Wav_Player#readme) |
| Sub-GHz Playlist | [generator script](https://github.com/darmiel/flipper-scripts/blob/main/playlist/playlist_creator_by_chunk.py) |
| Sub-GHz Bruteforcer | [Sub-GHz bruteforce](/subghz/bruteforce) |
| LF RFID / iButton Fuzzer | [RFID fuzzer](/rfid/fuzzer), [iButton fuzzer](/ibutton/fuzzer) |
| Unitemp (temperature sensors) | [how to use and supported sensors](https://github.com/quen0n/unitemp-flipperzero#readme) |
| [NMEA] GPS | [how to use](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md) |
| i2c Tools | [how to use](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/flipper_i2ctools/README.md) |
| NRF24 apps | [NRF24](/gpio/nrf24) |
| [WiFi] Scanner, [ESP8266] Deauther, [ESP32] WiFi Marauder, [ESP32-CAM] Camera Suite | [ESP32 and Wi-Fi modules](/gpio/esp32) |
| ESP flasher | [FAP "ESP flasher"](https://github.com/0xchocolate/flipperzero-esp-flasher) |
| Sentry Safe | [Sentry Safe](/apps/sentry-safe) |

::: warning
Pack contents change between releases. The build tag of the current packs is printed at the top of every
Unleashed changelog (for example `Apps: Build tag (20nov2026)`), with a link to the latest app commits.
:::

## Official catalog

The official Flipper Zero Apps Catalog is available in [Flipper Lab](https://lab.flipper.net/apps) and in the
[Flipper mobile app](/mobile/mobile-app). Installing from it is described in
[Apps on the SD card](/apps/sd-card-apps#installing-from-the-official-catalog).

## Related pages

- [Apps on the SD card (.fap)](/apps/sd-card-apps)
- [Troubleshooting apps](/apps/troubleshoot)
- [Installing Unleashed](/start/install)
