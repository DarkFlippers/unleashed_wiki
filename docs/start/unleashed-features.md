---
title: What Unleashed adds
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings]
sources: [unleashed-readme, unleashed-src]
---
# What Unleashed adds

Unleashed is built on the official firmware (OFW) and stays **fully compatible with its API and apps**. Everything the
stock firmware does still works. Below are the changes and additions compared to the official firmware (OFW), grouped by area.

## Sub-GHz: radio library and hardware

- **Regional TX restrictions removed.** Every frequency the CC1101 chip supports can transmit with no extra steps.
- **Extra frequencies** in the default list and a user-editable frequency list: [Frequencies and presets](/subghz/frequencies).
- **Optional extended frequency range** beyond the chip specification. It can damage the hardware:
  [Dangerous settings](/start/dangerous-settings).
- **Large set of additional protocols**, with the ability to **save and send many rolling-code systems**:
  [Supported systems](/subghz/supported-systems), [Rolling codes](/subghz/rolling-codes), [KeeLoq](/subghz/keeloq).
- **External CC1101 module** support over hardware SPI, with amplifier/LED control: [External CC1101](/subghz/external-cc1101).
- **Special counter modes** for rolling codes to avoid desync: [Counter mode](/subghz/counter-mode).

## Sub-GHz: main app

- **Last used settings are remembered** (frequency, modulation…).
- **Frequency Analyzer improvements**: core functionality matches the official firmware, plus Unleashed lets <kbd>OK</kbd>
  send the detected frequency to Read and long <kbd>OK</kbd> jump straight to Read: [Frequency Analyzer](/subghz/frequency-analyzer).
- **Read improvements**: shows when each signal was received. Hold <kbd>→</kbd> in the list to delete a signal.
  Multi-system protocols show the decoded system name (CAME, Nice FloR-S, FAAC SLH, KeeLoq): [Read](/subghz/read).
- **Protocol names in file names**: `Radio Settings → Protocol Names = ON` names saved files with a timestamp plus the
  protocol.
- **Custom buttons** for KeeLoq, Alutech AT4N, Nice Flor S, Somfy Telis, Security+ 2.0, CAME Atomo, BelKorn and others.
  Use the D-pad arrow buttons to send another button code: [Using as a remote](/subghz/remote).
- **Extended `Add manually`**: one entry per system, band picker, advanced mode with TE, guard time and other fields.
  Create FAAC SLH, BFT Mitto, Somfy Telis, Nice Flor S, CAME Atomo and other remotes and pair them with a receiver:
  [Add manually](/subghz/add-manually), [Programming a new remote](/subghz/remote-prog).
- **Read RAW → More → Edit** opens a RAW file straight in Sub-GHz RAW Edit: [RAW editor](/subghz/raw-editor).
- **Ignore filters** for noisy protocols (alarms, sensors, doorbells, key finders, Feron lights…) and debug options
  (counter increment step, debug pin output): [Sub-GHz settings](/subghz/settings).

## Sub-GHz apps

| App | What it does | Page |
|---|---|---|
| Sub-GHz Remote | Bind up to 5 `.sub` files to the buttons, with a built-in configurator | [Remote](/subghz/remote) |
| Sub-GHz Bruteforcer | Static-code brute force, custom files, delay and repeats | [Bruteforce](/subghz/bruteforce) |
| Remote Analyzer | Decode one remote at a time, with a built-in frequency analyzer | [Remote Analyzer](/subghz/remote-analyzer) |
| Nice O-Code | Recover the installer code of a Nice O-Code remote | [Nice O-Code](/subghz/nice-o-code) |
| Security+ PIN | Find the keypad PIN of a Security+ 2.0 signal | [Security+ PIN](/subghz/secplus-pin) |
| Seed Capturer | Collect Fix + Hop pairs (FAAC SLH, Genius, Erreka, BFT Mitto) for seed recovery | [Seed Capturer](/subghz/seed-capturer) |
| Sub-GHz RAW Edit | Trim, merge and decode RAW captures | [RAW editor](/subghz/raw-editor) |

## NFC, RFID and iButton

- **Extra MIFARE Classic keys** in the system dictionary: [MIFARE Classic](/nfc/mifare-classic). Key recovery guides:
  [Nested & Fudan](/nfc/nested-fudan), [MFKey](/nfc/mfkey).
- **MFKey** on the device: [MFKey app](/nfc/mfkey-app).
- **EMV protocol and public-data parser**: [Bank cards (EMV)](/nfc/emv).
- **NFC `Add manually` → MIFARE Classic with a custom UID**: [Add manually](/nfc/add-manually).
- **Many extra card parsers** (transport and city cards: Troika, Umarsh, Zolotaya Korona, Kazan, Metromoney, Moscow
  Social Card and more): [Supported cards](/nfc/supported-cards).
- **NFC Magic 2.0** for magic cards, including Ultralight: [NFC Magic](/nfc/nfc-magic).
- **T5577 app**: read, edit and write blocks, wipe or clear the password, password sniffer (`Sniff Password`): [T5577 app](/rfid/t5577-app).
- **EM4100 DEZ 8** display format: [Reading RFID](/rfid/read).
- **RFID and iButton fuzzers**: [RFID Fuzzer](/rfid/fuzzer), [iButton Fuzzer](/ibutton/fuzzer).

## Infrared

- The TV universal remote is rebuilt to cover **all buttons**.
- **Large collection of universal remotes for projectors, fans, air conditioners and audio** (soundbars…), regularly
  updated, verified and expanded by the team.
- **RCA** protocol and external IR module support (auto-detected): [Universal remotes](/infrared/universal-remotes).
- How to make good captures for inclusion in the universal remote database: [IR captures](/infrared/captures).

## Bad USB and USB/Bluetooth

- **BadKB**: run Bad USB scripts over **Bluetooth**, integrated into the Bad USB app: [Bad USB](/badusb/usage).
- **Keyboard layouts**, and the `DUCKY_LANG` command that lets a script pick its own layout: [Script format](/badusb/script-format).

## Desktop, settings and quality of life

- **Custom Flipper name** in **Settings → Desktop → Change Flipper Name**: [Custom name](/start/custom-name).
- **Clock on the desktop** (`Settings → Desktop → Show Clock`) and **battery styles** (`Battery View`: Bar, %, Inv. %,
  Retro 3, Retro 5, Bar %): [Desktop](/start/desktop).
- **Lock by holding <kbd>↑</kbd>** on the desktop: with the PIN if one is set, a regular lock otherwise.
- **More games in Dummy Mode**: each arrow (short and long press) and <kbd>OK</kbd> can launch its own app.
- **[RGB backlight mod](https://github.com/quen0n/flipperzero-firmware-rgb#readme)** support in **LCD and Notifications → RGB Mod Settings** (only for hardware-modded Flippers).
- **Text input cursor**, and a **byte input mini-editor** (press <kbd>↑</kbd> repeatedly until the nibble editor appears).
- **Archive** with extra tabs (SubRem for Sub-GHz Remote maps, Phone for the SIM800 phonebook).

All Settings items are described in [Settings](/start/settings).

## Built-in apps {#built-in-apps}

These apps are built from the firmware repository and installed into `/ext/apps/` by every update, in **every** build
variant (`e`, no suffix, `c`). The app packs do not contain them, so a pack can never overwrite or downgrade them.

**In the main menu:** GPIO, iButton, Infrared, NFC, 125 kHz RFID, Bad USB (with BadKB), U2F, **Clock** (brightness
controls, alarm, timer), **Sub-GHz Remote**. Sub-GHz, Archive and Settings are part of the firmware binary.

**In Apps:**

| App | Category | Page |
|---|---|---|
| MFKey | NFC | [MFKey app](/nfc/mfkey-app) |
| T5577 | RFID | [T5577 app](/rfid/t5577-app) |
| Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit | Sub-GHz | see the table above |
| SIM800 (calls, SMS, phonebook, USSD, AT terminal) | GPIO | [SIM800](/gpio/sim800) |
| FindMy Flipper (Apple FindMy / Google Find My Device beacon) | Bluetooth | [App catalog](/apps/catalog) |
| USB Keyboard & Mouse, Bluetooth Remote | USB / Bluetooth | [Controllers](/apps/controllers) |
| Snake Game | Games | — |

## Community app packs

- **Base pack** (in builds without suffix and `e`) and **Extra pack** (only `e`): source and full list at
  [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev). The latest packs are on
  [GitHub releases](https://github.com/xMasterX/all-the-plugins/releases/latest).
- The official catalog also works: [lab.flipper.net/apps](https://lab.flipper.net/apps) or the mobile app.
- More: [App catalog](/apps/catalog), [Apps on the SD card](/apps/sd-card-apps).

## Companion apps and web tools

- **qUnleashed**: companion app for phone and PC: [qUnleashed](/mobile/qunleashed-app).
- **Web tools**: [Web Installer](https://web.unleashedflip.com), Sub-GHz map ([map.unleashedflip.com](https://map.unleashedflip.com)),
  Wi-Fi wardriving map ([wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)), ESP32 web flasher
  ([espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)): [Web tools](/mobile/web-tools).
