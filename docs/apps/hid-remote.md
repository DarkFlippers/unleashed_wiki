---
title: USB / Bluetooth remote (HID)
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app, https://docs.flipper.net/zero/apps/controllers]
sources: [unleashed-src, flipper-docs]
---
# USB / Bluetooth remote (HID)

The HID app makes the Flipper look like a keyboard, mouse or media remote (a USB **H**uman **I**nterface **D**evice)
to a computer, phone or tablet. The same app is built twice:

| App | Where on the Flipper | Connection |
|---|---|---|
| **USB Keyboard & Mouse** | `Main Menu → Apps → USB → USB Keyboard & Mouse` | USB cable |
| **Bluetooth Remote** | `Main Menu → Apps → Bluetooth → Bluetooth Remote` | Bluetooth LE |

How to connect it is on [Pairing the HID remote](/apps/controllers). This page describes every mode.

## Modes

The start menu lists:

`Keynote` · `Keynote Vertical` · `Keyboard` · `Numpad` · `Media` · `Apple Music macOS` · `Movie` · `Mouse` ·
`TikTok / YT Shorts` · `Mouse Clicker` · `Mouse Jiggler` · `Mouse Jiggler Stealth` · `PushToTalk`

The Bluetooth version also has `Bluetooth Remote Name` and `Bluetooth Unpairing`.

::: tip Unleashed
The official docs describe Keynote, Keyboard, Media, Mouse, TikTok, Mouse Jiggler and Mouse Clicker. The Unleashed
build of the app also has **Numpad**, **Apple Music macOS**, **Movie**, **Mouse Jiggler Stealth**, **PushToTalk**,
and **Bluetooth Remote Name** to change the name the remote advertises.
:::

In almost every mode, **hold <kbd>Back</kbd> to exit** back to the mode list; all keys are released on exit.

### Keynote and Keynote Vertical

A presentation clicker. Keynote Vertical is the same, rotated for holding the Flipper upright.

| Button | Sends |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | arrow keys (next / previous slide) |
| <kbd>OK</kbd> | Space |
| <kbd>Back</kbd> | Backspace + "AC Back" (leaves slideshow mode in most apps) |
| hold <kbd>Back</kbd> | exit |

### Keyboard

An on-screen QWERTY keyboard with digits, symbols, F1-F12, Esc, Tab, Enter, Backspace, Delete and the modifiers
Ctrl, Alt, Shift and Cmd (Win).

1. Move with the arrows, press <kbd>OK</kbd> to type the selected key.
2. Select the ⬆ (Shift) key to type uppercase and the second row of symbols.
3. For a shortcut press the modifier (Ctrl, Alt or Cmd) first, then the key.
4. Hold <kbd>Back</kbd> to exit.

### Numpad

A number pad: `0`-`9`, `.`, `+`, `-`, `*`, `/`, `En` (keypad Enter), `NL` (Num Lock) and Backspace. Arrows select,
<kbd>OK</kbd> presses the key, hold <kbd>Back</kbd> to exit.

### Media

| Button | Sends |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | previous / next track |
| <kbd>↑</kbd> / <kbd>↓</kbd> | volume up / down |
| hold <kbd>Back</kbd> | exit |

On phones the volume keys also work as a camera shutter: open the camera and press <kbd>↑</kbd> or <kbd>↓</kbd>
to take a photo or start/stop a video.

### Apple Music macOS

| Button | Sends |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | previous / next track |
| <kbd>↑</kbd> / <kbd>↓</kbd> | <kbd>Cmd</kbd>+<kbd>↑</kbd> / <kbd>Cmd</kbd>+<kbd>↓</kbd> (volume in Apple Music) |
| hold <kbd>Back</kbd> | exit |

### Movie

| Button | Sends |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | Left / Right arrow (seek in most players) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | volume up / down |
| hold <kbd>Back</kbd> | exit |

### Mouse

| Button | Action |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | move the cursor; holding accelerates |
| <kbd>OK</kbd> | left click |
| hold <kbd>OK</kbd> | hold the left button (drag, "Selecting...") |
| <kbd>Back</kbd> | right click |
| hold <kbd>Back</kbd> | exit |

### TikTok / YT Shorts

For short-video apps on a phone or tablet.

| Button | Action |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | scroll to the previous / next video |
| <kbd>OK</kbd> | double tap (like) |
| <kbd>←</kbd> / <kbd>→</kbd> | volume down / up |
| <kbd>Back</kbd> | single tap (pause) |
| hold <kbd>Back</kbd> | exit |

::: tip iPhone / iPad
If the TikTok mode does nothing on iOS, enable `Settings → Accessibility → Touch → AssistiveTouch`, then in
**Pointer Devices → Devices → Bluetooth Devices** select your Flipper.
:::

### Mouse Clicker

Clicks automatically at a set rate.

| Button | Action |
|---|---|
| <kbd>OK</kbd> | Start / Stop |
| <kbd>↑</kbd> / <kbd>↓</kbd> | clicks per second, up to 100 (default 1) |
| <kbd>←</kbd> / <kbd>→</kbd> | which button: left, right or wheel (middle) |
| <kbd>Back</kbd> | exit |

### Mouse Jiggler

Moves the cursor a little at a fixed interval, so the computer does not go to sleep or show you as "away".

1. Before starting, choose the interval with <kbd>←</kbd> / <kbd>→</kbd>: 500, 2000, 5000, 10000, 30000 or 60000 ms
   (default 5000 ms).
2. Press <kbd>OK</kbd> to **Start**, again to **Stop**. Until the host connects the screen says
   `Waiting for Connection...`.
3. <kbd>Back</kbd> quits.

### Mouse Jiggler Stealth

Like the jiggler, but moves at random intervals between a minimum and a maximum you set in minutes (1 to 30), which
looks less like a machine. While stopped, <kbd>↑</kbd> / <kbd>↓</kbd> change the minimum and <kbd>→</kbd> / <kbd>←</kbd>
raise / lower the maximum; <kbd>OK</kbd> starts or stops.

### PushToTalk

A mute / push-to-talk button for video calls.

1. Pick your OS list (**macOS** or **Win/Linux**), then the app: Google Meet, Google Meet Global, Google Hangouts,
   Discord, FaceTime, Gather, Jamulus, Signal, Skype, Slack Call, Slack Huddle, TeamSpeak, Teams, Webex, Zoom or
   Zoom Global.
2. Long-press <kbd>OK</kbd> on an entry in the list to read its help (some apps need a setting or an extension, for
   example a global shortcut for Google Meet or binding the keys in TeamSpeak).
3. In the call: <kbd>Back</kbd> toggles the mic, **hold <kbd>OK</kbd>** for push-to-talk (the mic goes off when you
   release), hold <kbd>→</kbd> to change the Flipper's mic status if it got out of sync with the computer. For Zoom,
   long-press <kbd>←</kbd> sends Enter.
4. Hold <kbd>Back</kbd> to exit.

### Bluetooth Remote Name and Bluetooth Unpairing (Bluetooth only)

- **Bluetooth Remote Name**: type a name in `Bluetooth Name`; the remote advertises under it. By default it shows up as
  `Control <Flipper name>`.
- **Bluetooth Unpairing**: asks `Unpair All Devices? All previous pairings will be lost!`; press **Unpair** to forget
  every host paired with the remote. The remote keeps its own pairing keys (`/ext/apps_data/hid_ble/.bt_hid.keys`),
  separate from the main Bluetooth pairings of the Flipper.

## Related pages

- [Pairing the HID remote](/apps/controllers)
- [Bad USB](/badusb/usage)
- [Apps that ship with Unleashed](/apps/catalog)
