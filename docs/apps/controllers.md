---
title: Pairing the HID remote
order: 60
original: [https://docs.flipper.net/zero/apps/controllers, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app]
sources: [flipper-docs, unleashed-src]
---
# Pairing the HID remote

The HID remote app lets the Flipper control presentations, type text, move the mouse and control media on a computer
or phone. This page covers **connecting** it; what each mode does is on
[USB / Bluetooth remote (HID)](/apps/hid-remote).

You can connect in two ways:

| | USB | Bluetooth LE |
|---|---|---|
| App | `Apps → USB → USB Keyboard & Mouse` | `Apps → Bluetooth → Bluetooth Remote` |
| Pairing | none, just plug in | once per host |
| Works with | computers, phones with USB-C/OTG | computers, Android, iPhone/iPad |

::: tip Unleashed
In Unleashed the two variants are called **USB Keyboard & Mouse** and **Bluetooth Remote**, and they live in the
`USB` and `Bluetooth` app folders (the official docs call both "Remote").
:::

## Via USB

1. Connect the Flipper to the computer with a USB data cable. Close qFlipper first, the remote needs the USB port.
2. Open `Main Menu → Apps → USB → USB Keyboard & Mouse`.
3. Pick a mode (Keynote, Keyboard, Mouse...). The computer sees a new keyboard/mouse, no driver is needed.

When you exit the app the Flipper's USB returns to normal (serial) mode.

## Via Bluetooth

1. Turn Bluetooth on on the computer or phone.
2. On the Flipper: `Main Menu → Settings → Bluetooth` and set **Bluetooth** to **ON**.
3. Open `Main Menu → Apps → Bluetooth → Bluetooth Remote` and pick a mode.
4. On the computer or phone open the Bluetooth settings and connect to **Control &lt;Flipper name&gt;** (on a phone,
   tap **Pair**).
5. If the Flipper shows a pairing confirmation, press <kbd>OK</kbd>.

Next time the host reconnects automatically when you open Bluetooth Remote.

::: tip Custom name
`Bluetooth Remote → Bluetooth Remote Name` changes the advertised name, handy if you have several Flipper remotes or
want it to look like an ordinary keyboard.
:::

### If pairing fails

- Make sure Bluetooth is ON in `Settings → Bluetooth`.
- Remove the old "Control ..." entry in the host's Bluetooth settings, then on the Flipper run
  `Bluetooth Remote → Bluetooth Unpairing → Unpair`, and pair again.
- Disconnect the Flipper from other devices (for example the mobile app).
- Reboot the Flipper: hold <kbd>←</kbd> + <kbd>Back</kbd> for about 5 seconds.
- Update the firmware.

The remote keeps its own pairings (`/ext/apps_data/hid_ble/.bt_hid.keys`), separate from the main Flipper Bluetooth
used by the mobile app. **Bluetooth Unpairing** inside the remote only clears the remote's hosts. The global
`Settings → Bluetooth → Unpair All Devices` clears everything: the mobile app pairing and the remote's (and BadKB's)
pairings too.

### iPhone / iPad: TikTok mode does not react

1. On the iPhone open `Settings → Accessibility → Touch → AssistiveTouch`.
2. Turn **AssistiveTouch** on.
3. In **Pointer Devices** go to **Devices → Bluetooth Devices** and select your Flipper.

## Related pages

- [USB / Bluetooth remote (HID)](/apps/hid-remote)
- [Settings](/start/settings)
- [Flipper mobile app](/mobile/mobile-app)
