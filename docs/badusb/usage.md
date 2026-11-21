---
title: Using Bad USB
order: 10
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Using Bad USB

Menu labels and messages below are exactly as they appear in the firmware.

::: warning
Only run scripts on computers you own or are allowed to test. Read a script before running it: it will do whatever
it says, with your user's rights.
:::

## Before you start

- A microSD card with the firmware resources is required. Without it the app shows *"No SD card or app data found.
  This app will not work without required files."*
- Put your script (`.txt`) into `/ext/badusb/` (subfolders are fine).
- **USB mode takes over the Flipper's USB port.** If qFlipper or the [CLI](/dev/cli) is connected over USB, the app shows
  *"Connection Is Active! Disconnect from PC or phone to use this function."* Close qFlipper first.

## The main screen

1. Open `Main Menu → Bad USB`.
2. Pick a script in the file browser. The script screen opens.

The top line shows the script name, below it the keyboard layout in brackets, `(default)` or e.g. `(de-DE)`, and the
elapsed time, or in BLE mode the pairing PIN. The picture in the middle shows a USB plug or a Bluetooth symbol.

![Bad USB script screen: demo_windows loaded, 0/34 lines, Config / Run / BLE hints](/screens/badusb/script_ready.png)

| State | Screen text | <kbd>OK</kbd> | <kbd>←</kbd> | <kbd>→</kbd> |
|---|---|---|---|---|
| Idle / Done / not connected | progress or *Connect to device* | **Run** | **Config** | switch to **BLE** / **USB** |
| Waiting for connection after Run | *Will run on connect* | **Cancel** | | |
| Running or in a `DELAY` | `line/total`, percent, `Delay Ns` | **Stop** | | **Pause** |
| Paused | *Paused* | **End** | | **Resume** |
| Waiting at `WAIT_FOR_BUTTON_PRESS` | | **Press to continue** | | |
| Error | *ERROR:* + `line N` + message | | | |

If you press **Run** before the host has recognised the Flipper, the app waits (*"Will run on connect"*) and starts
the script automatically **1.5 s after the connection** is up, so the host has time to install the keyboard.

While no host is connected, the hourglass and *Connect to device* replace the progress:

![Bad USB waiting for a USB host, the screen shows Connect to device](/screens/badusb/not_connected.png)

<kbd>Back</kbd> leaves the script screen and returns to the file browser.

## Run over USB

1. Close qFlipper on the computer.
2. `Main Menu → Bad USB` → select the script.
3. Make sure the screen shows the **USB** picture; if not, press <kbd>→</kbd> **USB**.
4. Optional: <kbd>←</kbd> **Config → Keyboard Layout (global)** to match the computer's layout (default `en-US`).
5. Connect the Flipper to the computer with a USB cable.
6. Press <kbd>OK</kbd> **Run**. The progress `line/total` runs to 100 %.

![Bad USB running a script: 32 %, line 12 of 34, Stop and Pause hints](/screens/badusb/script_running.png)

![Bad USB in USB mode](/img/remote/d49323518c0b4b18.jpg)

## Run over Bluetooth (BLE)

1. Make sure Bluetooth is enabled on the Flipper (`Settings → Bluetooth`).
2. `Main Menu → Bad USB` → select the script.
3. Press <kbd>→</kbd> **BLE**; the Bluetooth picture appears. The Flipper starts advertising as a keyboard.
4. On the computer/phone open Bluetooth settings and connect to **`BadUSB <your Flipper name>`** (the default name).
5. Confirm the pairing on both devices. With the default pairing mode the same PIN is shown on both screens; confirm
   it matches. The PIN is also shown on the script screen.
6. Press <kbd>OK</kbd> **Run**.
7. To remove the pairing later: <kbd>←</kbd> **Config → Remove BLE Pairing**, then forget the device on the host too.

![Bad USB in BLE mode](/img/remote/083420027c3f836c.jpg)

::: tip Separate identity and pairing
In BLE mode the Flipper uses its **own MAC address** (derived from the Flipper's MAC) and its own pairing storage,
separate from the normal Bluetooth profile. Pairing a computer with Bad USB therefore doesn't break the pairing with
Flipper Mobile App. When you leave the app, the normal Bluetooth profile is restored.
:::

## Scripts that switch the mode themselves

If the **first line** of a script is an `ID` command (USB) or `BLE_ID` / `BT_ID` (Bluetooth), the app switches to that
mode automatically when the script is opened and applies the given identity. You can still switch manually with
<kbd>→</kbd>. See [Script format → Device ID](/badusb/script-format#device-id).

## Config menu

<kbd>←</kbd> **Config** is available only while the script isn't running. The content depends on the current
connection mode.

### Common

| Item | Values | What it does |
|---|---|---|
| **Keyboard Layout (global)** | file browser | Selects a `.kl` file from `/ext/badusb/assets/layouts/`. Applies to every script that doesn't set its own with `DUCKY_LANG`. See [Keyboard layouts](/badusb/layouts). |
| **Connection** | `USB` / `BLE` | Same as <kbd>→</kbd> on the main screen. The list below changes accordingly. |

### BLE mode

| Item | Values | What it does |
|---|---|---|
| **Persist Pairing** | `ON` / `OFF` | ON (default): bond with the host and remember it, so it reconnects without pairing again. OFF: pair every time. |
| **Pairing Mode** | `YesNo`, `PIN Type`, `PIN Y/N` | `YesNo`: pair without a PIN. `PIN Type`: the Flipper shows a PIN that you type on the host. `PIN Y/N` (default): both show a PIN; confirm it matches. |
| **Set Device Name** | text | Bluetooth name (*"Set BLE device name"*). Empty = `BadUSB <Flipper name>`. |
| **Set MAC Address** | 6 bytes | *"Set BLE MAC address"*. |
| **Randomize MAC Address** | action | Generates a random static MAC, shows **Done**. Useful to appear as a "new" keyboard. |
| **Restore BLE Defaults** | action | Clears name and MAC, Persist Pairing ON, Pairing Mode `PIN Y/N`. |
| **Remove BLE Pairing** | action | *"Unpair the Device?"* → **Unpair** forgets all hosts bonded with Bad USB. |

### USB mode

| Item | Values | What it does |
|---|---|---|
| **Set Manufacturer Name** | text | USB manufacturer string (*"Set USB manufacturer name"*). |
| **Set Product Name** | text | USB product string (*"Set USB product name"*). |
| **Set VID and PID** | 4 bytes | *"Set USB VID:PID"*. Lets the Flipper present itself with a given vendor/product ID. |
| **Randomize VID and PID** | action | Random VID and PID, shows **Done**. |
| **Restore USB Defaults** | action | Clears VID/PID and names: the Flipper's default keyboard identity is used. |

All of this, plus the chosen layout and mode, is saved to `/ext/badusb/.badusb.settings`. An `ID` / `BLE_ID` line in a
script overrides the identity for that script only.

## Troubleshooting

| Problem | What to try |
|---|---|
| Typed text is garbage (`z` and `y` swapped, wrong symbols) | The host's keyboard layout doesn't match the app's. Choose the right layout in Config, or add `DUCKY_LANG` to the script. On a PC with several input languages, switch the host to the language of the layout before running (e.g. English, not Russian). |
| Characters are missing | The host is too slow. Add `DEFAULT_STRING_DELAY 10` (or more) and longer `DELAY`s after opening windows. |
| Script starts before the window is open | Increase the `DELAY` after `GUI r`, `ENTER` and similar. |
| *ERROR: line N* | The line has an unknown command, a typo, a bad number or non-ASCII text. Commands are **case-sensitive** (`STRING`, not `string`). See [Script format](/badusb/script-format). |
| *Native .kl supports ASCII, not UTF-8* | `STRING` contains non-ASCII characters (accents, Cyrillic…). Use `ALTSTRING`/`ALTCHAR` on Windows, or type such text another way. |
| *Connection Is Active!* | Disconnect qFlipper / CLI from the USB port. |
| macOS opens *Keyboard Setup Assistant* | Use an `ID` line with the VID/PID of an Apple keyboard (see the `demo_macos.txt` example) or close the assistant. |
| BLE host doesn't find the Flipper | Enable Bluetooth on the Flipper, stay in the script screen in BLE mode, remove old pairings on both sides (`Remove BLE Pairing`). |

## Related pages

- [Script format](/badusb/script-format)
- [Examples](/badusb/examples)
- [Keyboard layouts](/badusb/layouts)
