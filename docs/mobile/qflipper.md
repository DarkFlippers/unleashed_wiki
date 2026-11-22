---
title: qFlipper
order: 10
original: [https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/qflipper/windows-debug, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# qFlipper

**qFlipper** is the official desktop app for Flipper Zero: it updates firmware and databases, manages files on the
microSD card, backs up and restores the device, repairs broken firmware and mirrors the screen. It runs on Windows,
macOS and Linux.

::: tip Unleashed
qFlipper's update channels (Release / RC / Dev) install the **official** firmware. To install Unleashed use
**Install from file** with the Unleashed `.tgz` (qFlipper 1.2.0 or newer), see below, or the
[Web Installer](/mobile/web-tools#unleashed-web-installer).
:::

## Installing qFlipper

Download it from [flipperzero.one/update](https://flipperzero.one/update) and run the installer.

- **Windows**: Windows 10 and 11 only. The installer also installs the drivers.
- **macOS**: 10.14 or later, Apple Silicon optimised.
- **Linux**: an AppImage. Make it executable and set up the udev rules:

```bash
chmod +x qFlipper-x86_64.AppImage
./qFlipper-x86_64.AppImage                 # run it
./qFlipper-x86_64.AppImage rules install   # udev rules, to use it as a normal user
```

(In a file manager: Properties → Permissions → "Allow executing file as program" / "Is executable".)

## Overview

Connect the Flipper with the SD card inserted over USB and start qFlipper.

- **Device information**: hardware and firmware info, update button, remote control.
- **Advanced controls**: backup, restore, factory reset, update channel, **Install from file**.
- **File manager**: browse, upload, download, rename and delete files on the SD card and internal storage.

## Installing Unleashed with qFlipper

1. Make sure a **microSD card** is inserted.
2. Download `flipper-z-f7-update-(version).tgz` from the
   [Unleashed releases](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) (pick the build letter you
   want, see [build variants](/apps/catalog#build-variants)).
3. Start qFlipper and connect the Flipper.
4. Click **Install from file** and select the `.tgz`.
5. Wait for all stages to finish. The Flipper reboots into Unleashed with all assets installed.

Already on Unleashed? Install the new version on top; you don't need to go back to the official firmware.
More options: [Installing Unleashed](/start/install), [Updating](/start/updating).

## Uploading and downloading files

In **File manager** drag files into a folder, or right-click a folder → **Upload here**. Right-click a file or folder
→ **Download** to copy it to the computer (a simple way to back up the whole SD card).

| Command | Windows / Linux | macOS |
|---|---|---|
| Enter folder | Return | Return |
| Back | Backspace | Backspace |
| Upload | Ctrl+L | Cmd+L |
| Download | Ctrl+D | Cmd+D |
| Delete | Delete | Fn+Backspace |
| Delete immediately | Shift+Delete | Shift+Fn+Backspace |
| New folder | Ctrl+N | Cmd+N |
| Rename | Ctrl+E | Cmd+E |
| Refresh | Ctrl+G | Cmd+G |

## Remote control and screenshots

In **Device information** click the Flipper image, then click the on-screen buttons or use the keyboard (ℹ️ shows
the key map). **SAVE SCREENSHOT** saves the current screen as an image.

## Logs and bug reports

- **LOGS → OPEN FULL LOG** shows the current session's log; save it as `.txt`.
- qFlipper keeps logs of the last 100 sessions: in **LOGS** right-click the log area → **Browse all logs**.
- Report official qFlipper problems on [forum.flipperzero.one](https://forum.flipperzero.one/) (Firmware update /
  qFlipper section). Problems with Unleashed itself belong in the Unleashed chats or GitHub issues.

## Troubleshooting

### qFlipper does not see the Flipper / Chrome cannot connect

Only one program can use the serial port. If qFlipper is open, Flipper Lab, the Web Installer and other web tools
cannot connect, and vice versa. Close qFlipper (and extra Flipper Lab tabs) before using a browser tool.

### Windows drivers

1. Install qFlipper only from official sources; it installs the right drivers. Check for updates in
   **Advanced controls → CHECK APP UPDATES**.
2. **Normal mode** (Flipper running): the Flipper is a **USB Serial Device** in
   `Device Manager → Ports (COM & LPT)`, hardware ID **VID 0483, PID 5740**, driver from **Microsoft**. If another
   driver is installed, uninstall it and reconnect.
3. **COM port conflict**: two serial devices on the same COM number. Open one of them →
   **Port Settings → Advanced** and assign an unused **COM Port Number**.
4. **Recovery (DFU) mode**: hold <kbd>←</kbd> + <kbd>Back</kbd>, release <kbd>Back</kbd> and keep <kbd>←</kbd> until
   the LED turns blue. The Flipper must appear as **DFU in FS Mode** under `Universal Serial Bus devices`,
   **VID 0483, PID DF11**, driver **STMicroelectronics**.
5. If you see **STM Device in DFU mode** under `Universal Serial Bus controllers`, the wrong driver is installed:
   uninstall qFlipper, reinstall it from the official site and check again.
6. If **DFU in FS Mode** sits under `Other devices` with an exclamation mark: right-click → **Update driver →
   Browse my computer → Let me pick** → **Universal serial bus devices** → **WinUsb Device**.

If the Flipper does not start at all, see [Recovery](/start/recovery).

## Related pages

- [Installing Unleashed](/start/install)
- [Flipper mobile app](/mobile/mobile-app)
- [Web tools](/mobile/web-tools)
