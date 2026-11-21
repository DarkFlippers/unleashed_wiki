---
title: qUnleashed companion app
order: 30
original: [https://github.com/DarkFlippers/qUnleashed, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md]
sources: [unleashed-readme, unleashed-docs]
---
# qUnleashed companion app

::: tip Unleashed
**qUnleashed** is the Unleashed team's own companion app for phone and computer. It was written from
scratch in Flutter as an alternative to the official Flipper mobile app, so it is not a fork of
qFlipper. Licence GPL-3.0-or-later, source and builds at
[DarkFlippers/qUnleashed](https://github.com/DarkFlippers/qUnleashed).
:::

It is built for Unleashed but works with other firmware too. The current stable version is **0.17.2**.

## Will it run on your device?

| System | You need |
|---|---|
| Android | 10 (API 29) or newer |
| iOS | 15 or newer |
| macOS | 12 or newer |
| Windows | 10 or newer, 64-bit |
| Linux | GLib 2.72 and glibc 2.35 — Ubuntu 22.04, Debian 12, Mint 21 or newer |

An older Linux will not even start the binary.

## Install

Pick the build for your system on the
[releases page](https://github.com/DarkFlippers/qUnleashed/releases). There is no store listing and no
installer script.

## Connecting

Bluetooth works on all five systems. USB serial works on Android, Windows, macOS and Linux — on iOS
there is no USB option at all, because Apple does not let apps talk to a USB serial device.

The app remembers the Flippers you have used and reconnects by itself. If one is plugged in over USB,
it wins over the last Bluetooth device. On Android a foreground service keeps the Bluetooth link alive
while the app is in the background.

## Firmware

- **Updater** with release and dev channels and their changelogs. It downloads and installs from inside
  the app: the Unleashed base build, the extra-apps build, the compact build, and the official channels.
- **Repair from DFU mode** re-flashes the Flipper completely over USB. Same idea as qFlipper's Full
  Repair, for a device that no longer boots.
- **Release notifications** are optional, and the dev channel has its own separate switch.

## Device

- **Device info**: firmware version and build date, battery, storage.
- **GPS and internet sharing**: the phone hands its location to apps on the Flipper and carries the
  Flipper's network traffic. Your firmware needs the RPC GPS/network extension for this.
- **Remote desktop**: the Flipper's screen live on your phone or PC, with the buttons on screen. On a
  computer you can use the real keyboard. Screenshots can be exported, and the screen can be recorded as
  a GIF.
- **Command line**: the full Flipper CLI. USB only, so not on iOS.

## Archive

A copy of your keys lives on the phone, one archive per Flipper. Every file is marked **synced**,
**remote-only**, **local-only** or **deleted**, so you can see what is where, and a deleted file can be
restored. Files can be marked as favorites.

Categories: Sub-GHz, Wardriving (autosaves included), RFID 125, NFC, Infrared, iButton, Bad USB,
JavaScript.

You can run a file straight from the app. NFC, RFID and iButton are emulated over RPC; Sub-GHz,
Infrared, Bad USB and JavaScript open in the matching app on the Flipper.

There is also a text editor with highlighting for Flipper file formats, so you can fix a `.sub` or `.ir`
file without a computer.

## File manager

Browses `/ext` (the SD card) and `/int` (internal memory). Create, rename, delete, download, upload, and
edit text files.

## Apps

The app catalog, with search, categories, sorting, a details page and screenshots. Install, update and
delete apps. It also sees what is already on the Flipper, preinstalled apps included.

## Tools

- **Pixel Draw**: a pixel-art editor with a project manager and multi-frame animation. It can import
  dolphin animations and show a live preview on the Flipper.
- **Extract MIFARE Keys**: runs Mfkey32 on the phone from nonces the Flipper collected. The full
  workflow is on [Fast key recovery with qUnleashed](/nfc/qunleashed).
- **Remotes Library**: infrared remotes from the official source and from the public
  [Lucaslhm/Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) repository. Browse, search, edit the
  `.ir` file, then save it to the archive or straight to `/ext/infrared`.
- **Pulse Plotter**: draws raw pulse captures from Sub-GHz, infrared and RFID.
- **Saved Locations**: map pins built from the latitude and longitude stored in archive files.

## Seed recovery for Sub-GHz captures

Some KeeLoq-based remotes (FAAC SLH, Genius, Erreka, older BFT Mitto) use a secret **Seed** that is needed to decode
them. The Flipper only collects the data, using the [Seed Capturer](/subghz/seed-capturer) app; the actual search is a
brute force, so it runs in qUnleashed, not on the Flipper.

1. Capture the remote with `Apps → Sub-GHz → Seed Capturer`: press the **same button** repeatedly, one steady press at
   a time, and check that the `Hops` counter grows on every press.
2. Connect the Flipper to **qUnleashed** and open its **Seed recovery** tool.
3. Pick your capture from the list. qUnleashed reads the captures straight from the Flipper's
   `subghz_seed_captures` folder; the manufacturer, frequency, `Fix` and `Hop` values are already in the file. **You do
   not copy, move, rename or edit any files.**
4. Start the search and wait.
5. If the Seed is found, qUnleashed returns the Seed and the counter and can **save the complete clone remote** as a
   `.sub` file for you (the `Fix` already carries the serial and button). Put it back on the Flipper and send it, no
   `Add Manually` typing needed.
6. If nothing is found, the capture most likely had a gap. Capture again, holding the remote right next to the Flipper,
   and press `Reset` (<kbd>←</kbd>) to start over if a press does not register.

::: warning The Seed belongs to the installation
On FAAC SLH and Genius the Seed is **different for every button**, so capture the button you intend to use. On Erreka
the Seed is per remote (sometimes per installation). On BFT Mitto it is per remote, and only older remotes with a
unique Seed need a capture at all.
:::

The whole procedure, with programming the clone into a receiver, is in
[Programming rolling-code remotes](/subghz/remote-prog) and [KeeLoq](/subghz/keeloq).

Use this only on your own remotes and gates.

## Related pages

- [Fast key recovery with qUnleashed](/nfc/qunleashed)
- [Seed Capturer](/subghz/seed-capturer)
- [Flipper mobile app](/mobile/mobile-app)
- [qFlipper](/mobile/qflipper)
- [Web tools](/mobile/web-tools)
