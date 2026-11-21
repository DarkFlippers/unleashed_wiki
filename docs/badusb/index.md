---
title: Bad USB
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Bad USB

The **Bad USB** app turns the Flipper into a keyboard (and mouse) that types a prepared script into a computer. The
computer sees an ordinary Human Interface Device (HID), so no drivers are needed. Scripts are written in an extended
**DuckyScript** (the language of the USB Rubber Ducky) and stored as plain `.txt` files on the microSD card.

![Bad USB](/img/remote/2a3485aa02031f3f.png)

Typical legitimate uses: automating repetitive setup on your own machines, typing long passwords or configs,
installing software on a fresh PC, demos and security awareness training.

::: danger Legal
A keystroke-injection device can do anything a person at the keyboard can. Only run scripts on computers you own
or are explicitly allowed to test.
:::

The app works over **USB** cable or over **Bluetooth (BLE)**, the latter appears to the host as a Bluetooth keyboard.

::: tip Unleashed
Unleashed integrates **BadKB** (by Willy-JL, ClaraCrazy and XFW contributors) right into the Bad USB app:
- **BLE mode** with configurable device name, MAC address, pairing mode and persistent pairing, plus the `BLE_ID` /
  `BT_ID` script commands;
- **USB identity** settings: manufacturer and product name, VID/PID, randomisation;
- **keyboard layouts** for many languages ([by rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl));
- the **`DUCKY_LANG`** command, so a script can choose its own keyboard layout (new in the current release, PR #1224 by @ANTONiO-eagle).
:::

## Files

| Path | Content |
|---|---|
| `/ext/badusb/` | Your scripts (`.txt`). The app's file browser opens here. |
| `/ext/badusb/examples/` | Demo scripts shipped with the firmware (Windows, macOS, GNOME, ChromeOS, mouse test, qFlipper installers). |
| `/ext/badusb/assets/layouts/` | Keyboard layout files (`.kl`). See [Keyboard layouts](/badusb/layouts). |
| `/ext/badusb/.badusb.settings` | App settings: global layout, USB/BLE mode, USB and BLE identity. |

Upload scripts with [qFlipper](/mobile/qflipper), the [mobile app](/mobile/mobile-app) or by copying them to the SD
card. A file with the same name is overwritten without warning.

## Pages in this section

| Page | What you learn |
|---|---|
| [Using Bad USB](/badusb/usage) | Running scripts over USB and BLE, the Config menu, all settings |
| [Script format](/badusb/script-format) | Full command reference: STRING, DELAY, HOLD/RELEASE, ALTCHAR, MEDIA, mouse, ID, DUCKY_LANG… |
| [Examples](/badusb/examples) | Safe example scripts to start with |
| [Keyboard layouts](/badusb/layouts) | Which layouts exist, how they work, choosing one per script |
