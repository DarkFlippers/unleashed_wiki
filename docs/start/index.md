---
title: Getting Started
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-readme, unleashed-docs, unleashed-src, flipper-docs]
---
# Getting Started

From a new Flipper Zero to a fully set up device running **Unleashed Firmware**: buttons, desktop, power, the microSD
card, settings and recovery. The rest of the wiki assumes you know these.

## What is Flipper Zero?

Flipper Zero is a pocket multi-tool for exploring radio and access-control technology. Its hardware includes:

- a **CC1101 Sub-GHz transceiver** for garage remotes, barriers, sensors and other sub-1 GHz devices;
- a **13.56 MHz NFC** module and a **125 kHz RFID** antenna for cards, fobs and tags;
- an **infrared** transmitter and receiver for TVs, air conditioners and other remotes;
- a **1-Wire (iButton)** contact pad for Dallas, Cyfral and Metakom keys;
- **USB** and **Bluetooth LE**, so it can act as a keyboard (Bad USB), a U2F token or a remote;
- **GPIO** pins for external modules (external CC1101, NRF24, ESP32, SIM800 and more);
- a 128×64 monochrome screen, a 5-way pad with a Back button, and a 2100 mAh battery.

A digital pet dolphin lives on the desktop. It levels up as you use the device.

## What is Unleashed Firmware?

[Unleashed](https://github.com/DarkFlippers/unleashed-firmware) is a fork of the official firmware (OFW). It stays
**fully compatible with the OFW API and apps** and adds features on top. The main additions:

- **No regional Sub-GHz TX restrictions**, extra frequencies, and an optional extended range;
- **many more Sub-GHz protocols**, including the ability to save and send many rolling-code systems, custom buttons,
  and `Add manually` for new remotes;
- **external CC1101** module support;
- extra NFC parsers, an EMV parser, more MIFARE Classic keys in the system dictionary;
- RFID and iButton fuzzers, a T5577 tool and other built-in apps;
- quality-of-life features: custom Flipper name, desktop clock, battery percentage, Night Shift, more Dummy Mode games,
  BadKB (Bad USB over Bluetooth) and more.

See [What Unleashed adds](/start/unleashed-features) for the full list with links.

::: warning Official sources only
`DarkFlippers/unleashed-firmware` is the only official home of the project. Every build is free and open source.
There are no paid, "premium" or closed-source versions. Anyone who offers you one is a scammer.
:::

## Release and dev builds

| Build | What it is | Where to get it |
|---|---|---|
| **Release** (stable) | Tested releases, recommended for everyday use | [Web Installer](https://web.unleashedflip.com), [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), Telegram [@unleashed_fw](https://t.me/unleashed_fw) |
| **Dev** (unstable) | Built automatically from every new commit on the `dev` branch | [dev.unleashedflip.com](https://dev.unleashedflip.com), Telegram [@kotnehleb](https://t.me/kotnehleb), Discord channel `unleashed-development` |

A new dev build replaces the previous one on the web site; old dev builds survive only as files in the Telegram
channel. Dev builds get new features first but **may contain bugs**. If you find one, report it on
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

Each release comes in three variants: `e` (base + extra apps), no suffix (base apps) and `c` (no community apps).
See [Installing Unleashed](/start/install#which-file-to-download) for details.

## Community channels

- Telegram chats: [English](https://t.me/flipperzero_unofficial), [Russian](https://t.me/flipperzero_unofficial_ru), [Ukrainian](https://t.me/flipperzero_unofficial_ua)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Unleashed web page: [flipperunleashed.com](https://flipperunleashed.com)

## Pages in this section

**First steps**
- [First start](/start/first-start): power on, insert a microSD card, first update
- [Installing Unleashed](/start/install): Web Installer, qFlipper, mobile apps, offline update from the SD card
- [Updating](/start/updating): staying current, release vs dev, what survives an update
- [What Unleashed adds](/start/unleashed-features): every Unleashed feature compared with stock firmware

**Using the device**
- [Controls](/start/controls): buttons, left-handed mode, hotkeys
- [Desktop](/start/desktop): status bar, shortcuts, Lock Menu, Quick Settings, Dummy Mode, Archive
- [Pet dolphin](/start/dolphin): mood, levels and XP
- [Power and battery](/start/power): charging, power off, Auto PowerOff, Limit Charge
- [microSD card](/start/sd-card): choosing, formatting, folder layout
- [Settings](/start/settings): every Settings menu item, one by one
- [Custom Flipper name](/start/custom-name)

**When something goes wrong**
- [Key combos](/start/key-combos): reset and DFU button combinations
- [Recovery](/start/recovery): firmware recovery, factory reset, PIN reset
- [Dangerous settings](/start/dangerous-settings): extended Sub-GHz range (read before you touch it)
- [FAQ](/start/faq)

::: tip Legal
Unleashed is meant for experiments and lawful research. Use it on your own devices or with permission.
:::
