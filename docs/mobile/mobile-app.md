---
title: Flipper mobile app
order: 20
original: [https://docs.flipper.net/zero/mobile-app, https://docs.flipper.net/zero/mobile-app/bug-report, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# Flipper mobile app

The official **Flipper Mobile App** ([App Store](https://apps.apple.com/us/app/flipper-mobile-app/id1534655259),
[Google Play](https://play.google.com/store/apps/details?id=com.flipperdevices.app)) connects to the Flipper over
Bluetooth. With it you can update the firmware, browse and share saved keys, install apps from the catalog, control
the Flipper remotely and back up your data.

::: tip Unleashed
The official mobile app works with Unleashed. It can install an Unleashed `.tgz` as a **Custom** update (below). If
the app stops connecting after you install Unleashed or change the Flipper's name, re-pair it, see
[Connection problems](#connection-problems).
:::

## Connecting to the Flipper

1. On the Flipper: `Main Menu → Settings → Bluetooth`, set **Bluetooth** to **ON**.
2. In the app tap **Connect**, then **Connect** next to your Flipper's name.
3. Enter the **pairing code** shown on the Flipper's screen and tap **Pair**.
4. Wait until the app finishes synchronising.

## What is in the app

- **Main Menu** (device tab): update over Bluetooth, **Device Info** (hardware and firmware details), **Options**
  (backup, logs, file manager, reboot, bug report; set depends on iOS/Android), manual sync, play a sound to find
  the Flipper.
- **Archive**: all saved Sub-GHz, RFID 125, NFC, Infrared and iButton files. Favorites, search, and restoring deleted
  items. Tap a key for **Key Info**: emulate or send, add to favorites, rename, add a note, view details, delete,
  share.
- **Apps**: the official app catalog, installed over Bluetooth LE, see [Apps on the SD card](/apps/sd-card-apps).
- **Tools**: **Mfkey32** (Extract MF Keys) to compute MIFARE Classic keys from collected nonces, and the
  **Remotes Library** of infrared remotes (see [Infrared from the phone](/infrared/mobile)).
- **Widget**: emulate saved remotes and cards from the phone's home screen without opening the app (iOS Today View
  → Edit → Add Widget → Flipper; on Android add it like any widget and tap to configure).

## Installing Unleashed from the phone

::: warning First install
If this is your first custom firmware, update to the latest **official** release first, and make sure the SD card is
inserted. Already on Unleashed? Install the new version on top.
:::

### iOS

1. Open the [latest Unleashed release](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) and
   download `flipper-z-f7-update-(version).tgz`.
2. In the **Files** app select the downloaded `.tgz`, tap **Share** and choose the **Flipper** app.
3. In the Flipper app check that the Update Channel shows `Custom flipper-z-f7-update...`, then tap the green
   **Update**.
4. Wait until the update finishes. The iOS app may show an error at the end, but the Flipper is updated.

### Android, with the `.tgz` file

1. Download `flipper-z-f7-update-(version).tgz` from the release page.
2. In the Flipper app tap **Update channel** → **Custom** and pick the downloaded file.
3. Tap **Update** and wait.

### Android, via the web updater link

1. On the release page tap **Install via Web Updater**.
2. When Android asks how to open it, choose the **Flipper** app.
3. Continue the installation and wait.

An update over Bluetooth can take around 10 minutes. Other ways: [Installing Unleashed](/start/install).

### If the update fails

- Check that the Flipper is on and still connected over Bluetooth.
- Reboot the Flipper (<kbd>←</kbd> + <kbd>Back</kbd>) and start the update again.
- If it keeps failing, the internal storage may be full or broken: install with [qFlipper](/mobile/qflipper) or the
  [Web Installer](/mobile/web-tools#unleashed-web-installer) instead, see [Recovery](/start/recovery).

## Backing up your keys

1. On the device tab tap **Options → Backup Keys**.
2. Choose where to save or share the `.zip` with your keys, cards and remotes.

To restore, unzip the archive and upload the files with [qFlipper](/mobile/qflipper). For a full SD card backup,
download the whole card in qFlipper's **File manager**.

## Connection problems

**After installing Unleashed or renaming the Flipper the app does not connect:**

1. In the app tap **Forget flipper**.
2. In the phone's Bluetooth settings find the Flipper, open its options and choose **Forget device**.
3. On the Flipper: `Settings → Bluetooth → Unpair All Devices` and confirm with **Unpair**.
4. Make sure Bluetooth is ON on the Flipper, then pair again from the app.

**The Flipper is not found:** check that Bluetooth is ON on both, disconnect the Flipper from other devices (for
example a [Bluetooth remote](/apps/controllers) host), update the app and the firmware, reboot the Flipper.

**Synchronisation fails:** unpair and pair again, restart both devices, and try
`Settings → System → Sleep Method → Legacy` on the Flipper.

## Reporting app bugs

Bugs in the official app: **Options → Report Bug**, fill in a title and steps to reproduce, keep the logs attached,
tap **Submit**, and optionally post the issue ID on [forum.flipperzero.one](https://forum.flipperzero.one/) (Mobile
App section). To capture Flipper logs for a report: set `Settings → System → Log Level` to **Debug**, connect over USB,
open a serial terminal at **230400** baud (or [lab.flipper.net/cli](https://lab.flipper.net/cli)), run `info device`
and then `log`, reproduce the bug, and remove the `hardware.uid` and `hardware.name` lines before posting.

## Related pages

- [qFlipper](/mobile/qflipper)
- [qUnleashed companion app](/mobile/qunleashed-app)
- [Installing Unleashed](/start/install)
