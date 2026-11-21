---
title: Installing Unleashed
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-readme, unleashed-src, flipper-docs]
---
# Installing Unleashed

Every method below installs the same update package: the firmware, the updater and all assets (apps, IR libraries,
Sub-GHz settings and so on).

::: tip Before you start
- **First install only:** update to the **latest official release** first ([First start](/start/first-start)).
- **Already on Unleashed:** do not install anything in between. Install the new version over the current one.
- Make sure a **microSD card is inserted**. The update is unpacked to the card, and the apps live there.
- Charge the battery. A full update takes several minutes.
:::

## Which file to download {#which-file-to-download}

Release files are named `flipper-z-f7-update-(version)(e / c).tgz`:

| Part | Meaning |
|---|---|
| `flipper-z` | For the Flipper Zero device |
| `f7` | Hardware target. The same for every Flipper Zero |
| `update` | Self-update package: updater, firmware and all assets |
| `(version)` | Firmware version |
| suffix | App pack variant, see below |

| Suffix | [Base Apps](https://github.com/xMasterX/all-the-plugins#default-pack) | [Extra Apps](https://github.com/xMasterX/all-the-plugins#extra-pack) |
|---|:---:|:---:|
| `e` | ✅ | ✅ |
| *(none)* | ✅ | — |
| `c` | — | — |

- **`e`**: everything. Base pack plus the extra pack of community apps. Pick this if you are unsure.
- **No suffix**: the base pack of community apps only.
- **`c`** ("clean"): no community apps.

**Built-in system apps** (MFKey, T5577, Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit,
SIM800, FindMy Flipper, USB/BT remotes, Snake…) ship **with the firmware itself** and are in **every** variant,
`c` included. See [What Unleashed adds](/start/unleashed-features#built-in-apps).

Other release files:
- `flipper-z-any-scripts-(version).tgz`: the `scripts` folder for firmware and app development;
- `flipper-z-f7-sdk-(version).zip`: SDK for app development and uFBT.

## Method 1: qUnleashed (recommended)

[qUnleashed](/mobile/qunleashed-app) is the Unleashed team's own companion app. It downloads and installs the
firmware itself, so there is no file to choose. It runs on **Android, iOS, Windows, macOS and Linux** — over USB
on all of them except iOS, which connects over Bluetooth.

1. Install qUnleashed for your system from its
   [releases page](https://github.com/DarkFlippers/qUnleashed/releases).
2. Connect the Flipper over USB, or pair it over Bluetooth (on iOS, Bluetooth is the only way).
3. Open the **firmware updater** in the app.
4. Choose the **Unleashed** channel, **Release** or **Dev**.
5. Choose the build: **base**, **extra apps** or **compact** ([what they contain](#which-file-to-download)).
6. Start the installation and wait. The Flipper reboots into the updater and runs through all stages.

If the Flipper no longer boots, use **Repair from DFU mode** in the same app to re-flash it over USB. See
[Recovery](/start/recovery#firmware-recovery).

The methods below are alternatives. Use one if qUnleashed does not fit your setup.

## Method 2: Unleashed Web Installer

You need a **Chromium-based browser** (Chrome, Edge, Opera, Brave, Vivaldi) and a USB cable.

1. Close **qFlipper** and any other Flipper web pages. They hold the serial port.
2. Connect the Flipper over USB.
3. Open **[web.unleashedflip.com](https://web.unleashedflip.com)**.
4. Press **Connect** and pick your Flipper in the browser pop-up.
5. Select the **Release** or **Dev** branch.
6. Press **Install** and wait. The Flipper reboots into the updater and runs through all stages.
7. Done. All assets are installed.

## Method 3: Flipper Lab web updater

1. Open the [latest release page](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
2. Connect the Flipper and click the **Install via Web Updater** link.
3. On the web updater page press **Connect**, then **Install**.
4. Wait for the update to finish.

![Web updater](/img/remote/b803c9d8ec0350d6.png)

## Method 4: qFlipper (1.2.0 or newer)

1. Install [qFlipper](https://flipperzero.one/update) 1.2.0+ (older versions cannot install `.tgz` files).
2. Download `flipper-z-f7-update-(version).tgz` from the [releases](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
3. Launch qFlipper and connect the Flipper.
4. Click **Install from file** and select the downloaded `.tgz`.
5. The update starts. Wait until it finishes.

![qFlipper install from file](/img/remote/f1a3ede83085d040.png)

::: warning
Do **not** use the qFlipper **Update** button after installing Unleashed. It installs the **official** firmware over
Unleashed. Use **Install from file** instead.
:::

## Method 5: Flipper Mobile App

### Android, with a `.tgz` file
1. Download `flipper-z-f7-update-(version).tgz` to the phone.
2. In the Flipper app, tap **Update channel** and select **Custom**.
3. Select the downloaded `.tgz` and tap **Update**.
4. Wait until the update is finished.

### Android, with the web updater link
1. On the release page, tap **Install via Web Updater**.
2. When asked to open with a browser or the Flipper app, choose the **Flipper App**.
3. Continue the installation and wait.

### iOS
1. Download `flipper-z-f7-update-(version).tgz`.
2. Open it in the **Files** app. Tap **Share** and choose the **Flipper App**.
3. In the Flipper app, tap the green **Update** button. Check that the update channel shows
   `Custom flipper-z-f7-update...`.
4. Wait. **The iOS app may show an error at the end, but the Flipper is updated successfully.**

## Method 6: Offline update from the microSD card

No computer program needed. Works from a PC or a phone.

1. Unpack `flipper-z-f7-update-(version).tgz` (or `.zip`). Inside is a folder `f7-update-(version)` containing
   `update.fuf`, `resources.tar` and other files.
2. Put the card in a PC or phone, or upload the files with qFlipper.
3. Create a folder `update` in the **root** of the card and move `f7-update-(version)` into it:
   ```text
   /ext/update/f7-update-(version)/update.fuf
   /ext/update/f7-update-(version)/resources.tar
   ...
   ```
4. Check that **all** files are there. The default iOS Files app may show only 3 of the 6 files. Use another unpacking
   app, a PC or Android.
5. Insert the card back into the Flipper.
6. Open **Archive** (<kbd>↓</kbd> on the desktop), go to the **Browser** tab, navigate to
   `update/f7-update-(version)/` and open `update.fuf`.
7. The update starts. Wait for all stages to finish.

![Offline update](/img/remote/92717373349f3b7c.png)

## After installing

- The About screen (**Settings → About**) shows the Unleashed firmware and version info.
- On first boot after an update, the Flipper unpacks resources to the card. This is normal.
- Read [What Unleashed adds](/start/unleashed-features) and set up the device in [Settings](/start/settings).

## Troubleshooting

| Problem | Fix |
|---|---|
| Browser cannot connect | Close qFlipper and other Flipper Lab tabs. Use a Chromium browser. Try another cable or port |
| Update fails or hangs | Reboot with <kbd>←</kbd> + <kbd>BACK</kbd>, check the SD card, try another method |
| Mobile app does not connect after install | Forget the Flipper in the app and in phone Bluetooth settings. Then **Settings → Bluetooth → Unpair All Devices** on the Flipper and pair again |
| Backlight is off after install | See [FAQ](/start/faq#backlight-does-not-work) (RGB mod setting) |
| Device is dead / bricked | [Recovery](/start/recovery) |
