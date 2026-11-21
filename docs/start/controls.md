---
title: Controls
order: 50
original: [https://docs.flipper.net/zero/basics/control, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/input_settings_app]
sources: [flipper-docs, unleashed-src]
---
# Controls

Flipper Zero has a 5-way directional pad and a separate <kbd>BACK</kbd> button.

| Button | What it does |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | Move through menus and virtual keyboards. <kbd>←</kbd>/<kbd>→</kbd> change the value of the selected option |
| <kbd>OK</kbd> | Launch an app, confirm a choice. Long press often opens extra actions |
| <kbd>BACK</kbd> | Go back or quit the app. Long press on the desktop opens the power-off screen |

In a list, the arrows move the frame around the selected item and <kbd>OK</kbd> opens it:

![Main menu with the frame on Sub-GHz](/screens/mainmenu/subghz.png)

In this wiki, "hold" or "long press" means pressing a button for about a second. The button hints at the bottom of a
screen (for example `◀ Cancel` or `Save ▶`) show what <kbd>←</kbd>, <kbd>OK</kbd> and <kbd>→</kbd> do on that screen.

## Left-handed mode

**Main Menu → Settings → System → Hand Orient → `Lefty`**

The screen flips 180° and the pad is remapped, so you can hold the Flipper in your left hand.

## Hotkeys

| Action | How |
|---|---|
| Power on | Hold <kbd>BACK</kbd> about 3 s |
| Power off | Hold <kbd>BACK</kbd> on the desktop → **Power Off** (<kbd>→</kbd>) |
| Reboot (frozen device) | Hold <kbd>←</kbd> + <kbd>BACK</kbd> about 5 s |
| Hard reboot (power reset) | Unplug USB, hold <kbd>BACK</kbd> about 30 s |
| Reboot to DFU (recovery) | Hold <kbd>←</kbd> + <kbd>BACK</kbd>, release <kbd>BACK</kbd>, keep <kbd>←</kbd> until the blue LED lights up |

All reset and DFU combinations, and when each one fails, are in [Key combos](/start/key-combos).

## Desktop shortcuts

| Button | Short press | Long press |
|---|---|---|
| <kbd>OK</kbd> | Main Menu | Favorite app (OK Long) |
| <kbd>↑</kbd> | Lock Menu | **Lock the Flipper** (with PIN if one is set) |
| <kbd>↓</kbd> | Archive | Device info / debug screen |
| <kbd>←</kbd> | Favorite app (Left Short), Apps menu by default | Favorite app (Left Long) |
| <kbd>→</kbd> | Passport (or the assigned app) | Favorite app (Right Long) |
| <kbd>BACK</kbd> | — | Power-off screen |

Assign apps in **Settings → Desktop → Favorite App - …**. Details are on the [Desktop](/start/desktop) page.

::: tip Unleashed
Holding <kbd>↑</kbd> on the desktop locks the device right away (with the PIN if one is set). In stock firmware, you
lock from the Lock Menu.
:::

A short <kbd>↑</kbd> opens the Lock Menu:

![Lock Menu: Turn Bluetooth On selected, with Mute and Dummy Mode below it](/screens/desktop/lock_menu.png)

If a PIN is set, the Flipper asks for it before it unlocks. The arrows type the code, <kbd>BACK</kbd> clears it and
<kbd>OK</kbd> confirms:

![Enter PIN: four entered digits shown as stars, an empty fifth cell, the clear hint and the OK button](/screens/desktop/pin_input.png)

A long <kbd>↓</kbd> opens the device info screen - uptime, hardware revision, Flipper name, firmware version and build
date, commit, API version and the Debug flag. A long <kbd>OK</kbd> there switches Debug on or off:

![Device info screen: Uptime 1h23m45s, hardware 13.F7B9C6 R00, firmware unlshd-080 built 21-11-2026 and D:ON](/screens/desktop/debug.png)

## Button feedback

**Main Menu → Settings → Input**

| Item | Values | Meaning |
|---|---|---|
| Buttons Vibro | `OFF`, `1`…`9` | Short vibration on each button event. Higher numbers vibrate longer |
| Vibro Trigger | `Press`, `Release`, `Both` | When the vibration fires |

## Text input

On the virtual keyboard, move with the arrows and press <kbd>OK</kbd> to type the selected character. Hold
<kbd>OK</kbd> on a letter to type it in upper case. Select the `⏎` / **Save** key to confirm. <kbd>BACK</kbd>
deletes the last character or leaves the keyboard.

::: tip Unleashed
The text input has a **cursor**, so you can edit in the middle of the text. In the hex **byte input** (for example when
adding a key manually), press <kbd>↑</kbd> several times until the **nibble mini-editor** appears. It lets you change
one half-byte at a time.
:::
