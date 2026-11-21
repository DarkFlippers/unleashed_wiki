---
title: Apps
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, flipper-docs, unleashed-src]
---
# Apps

Besides the big built-in tools (Sub-GHz, NFC, RFID, Infrared, iButton, Bad USB, GPIO), Flipper Zero runs **apps**:
small programs packed as `.fap` files that live on the microSD card. Unleashed ships a set of its own system apps
with every build, offers two optional app packs (Base and Extra), and stays compatible with the official
Apps Catalog.

::: tip Unleashed
Unleashed stays API-compatible with the official firmware, so apps from the official catalog (Flipper Lab or
the mobile app) generally work too. On top of that every Unleashed release has an `e` build that preinstalls the
**Extra Apps** pack of community apps. See [Apps that ship with Unleashed](/apps/catalog).
:::

## Getting and running apps

- [Apps that ship with Unleashed](/apps/catalog): built-in apps, the Base and Extra packs, and what the `e`, ` ` and `c` build letters mean.
- [Apps on the SD card (.fap)](/apps/sd-card-apps): where apps live, how to install them by hand or from the catalog, and how the loader checks the API version.
- [Archive (file browser)](/apps/archive): browse, run, pin, rename, move and delete saved files.
- [Troubleshooting apps](/apps/troubleshoot): what each loader error means and how to fix it.

## Built-in apps

- [U2F security key](/apps/u2f): use the Flipper as a FIDO U2F second factor.
- [Clock](/apps/clock): night clock with brightness control, stopwatch and daily alarm.
- [USB / Bluetooth remote (HID)](/apps/hid-remote): every mode of the HID remote app, button by button.
- [Pairing the HID remote](/apps/controllers): connect the remote over Bluetooth or USB and fix pairing problems.
- [FindMy Flipper](/apps/find-my-flipper): make the Flipper visible in Apple Find My, Samsung SmartThings, Tile or Google Find My Device.
- [Main menu styles](/apps/menu-styles): change how the main menu looks (PS4, Wii, DSi, C64, CoverFlow, Grid and others).
- [Snake](/apps/snake): the classic game.

## Apps from the packs

- [Barcode Generator](/apps/barcode)
- [Multi Converter](/apps/multi-converter)
- [Sentry Safe](/apps/sentry-safe)

Sub-GHz, NFC and RFID helper apps (Seed Capturer, Remote Analyzer, MFKey, T5577 and others) are covered in their own
sections, for example [Seed Capturer](/subghz/seed-capturer), [MFKey app](/nfc/mfkey-app) and
[T5577 app](/rfid/t5577-app).
