---
title: Recovery
order: 130
original: [https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://docs.flipper.net/zero/basics/firmware-update/storage-repair, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings]
sources: [flipper-docs, unleashed-docs, unleashed-src]
---
# Recovery

What to do when the Flipper freezes, won't update, shows nothing, or you forgot the PIN. Work through the steps in
order, from the gentlest to the most drastic.

## 1. Reboot first

- **Frozen:** hold <kbd>←</kbd> + <kbd>BACK</kbd> for about 5 seconds.
- **Still frozen:** unplug USB and hold <kbd>BACK</kbd> for 30 seconds (power reset).
- **Drained battery:** charge for several minutes (or an hour) and try again.
- From a working Flipper: **Settings → Power → Reboot → Reboot Flipper**.

All combos: [Key combos](/start/key-combos).

## 2. Firmware recovery from DFU mode {#firmware-recovery}

Use this when the firmware is corrupted: the update fails, the screen shows garbage or nothing, or buttons don't react.
The USB DFU bootloader flashes the firmware without the device's own OS.

### Step 1: put the Flipper into DFU (recovery) mode

**If the Flipper still works but won't update properly:**
1. **Main Menu → Settings → Power → Reboot → Firmware Upgrade**.
2. Confirm `Reboot to DFU Mode?` with <kbd>→</kbd> **Reboot**.

*or:* hold <kbd>←</kbd> + <kbd>BACK</kbd> for 5 s, release <kbd>BACK</kbd>, and keep holding <kbd>←</kbd> until the
**blue LED** lights up.

**If the screen shows nothing and buttons don't react:**
1. **Unplug the USB cable.**
2. Hold <kbd>OK</kbd> + <kbd>BACK</kbd> for **30 seconds**. A blank screen is normal here.

Then connect the Flipper to the computer with a USB cable.

### Step 2: check that the computer sees a DFU device

| OS | Where to look | Name |
|---|---|---|
| Windows | Device Manager | **DFU in FS Mode** |
| macOS | Apple menu → About This Mac → System Report → Hardware → USB (or `system_profiler SPUSBDataType`) | **DFU in FS Mode** |
| Linux | `lsusb` | **STMicroelectronics STM Device in DFU Mode** |

Not detected? Try another cable. Plug directly into the motherboard's USB port, not a hub or adapter. Or remove the SD
card, charge for an hour and connect without the card.

### Step 3: repair

Either app will do. Both re-flash the Flipper completely over USB.

**[qUnleashed](/mobile/qunleashed-app)** — Android, Windows, macOS and Linux (iOS has no USB):

1. Connect the Flipper in DFU mode over USB.
2. Open **Repair from DFU mode** and start it.

**qFlipper** — Windows, macOS and Linux:

1. Run **qFlipper**. It detects the DFU device.
2. Click **Repair**. qFlipper installs the **official** firmware completely.

Then install Unleashed again: [Installing Unleashed](/start/install).

::: tip Unleashed
qFlipper's **Repair** always restores official firmware. That's fine: it gives you a clean base. After repair, reinstall
Unleashed with qUnleashed, the Web Installer or **Install from file**. Your SD card files are not touched by the repair.
:::

### If qFlipper can't repair

- Check that qFlipper is installed correctly. On Windows, see qFlipper's driver troubleshooting.
- Disconnect USB, reboot with <kbd>←</kbd> + <kbd>BACK</kbd>, and repeat.
- Do a power reset (<kbd>BACK</kbd> 30 s, USB unplugged) and repeat.
- Run qFlipper as administrator.
- Use a USB port directly on the motherboard.
- Last resort: flash over SWD with an ST-Link (see [Key combos](/start/key-combos#if-nothing-helps)).

## 3. Internal storage repair / factory reset {#factory-reset}

If updates fail because internal storage is full or broken, reset the Flipper to factory state. This erases the
**internal storage**: settings, Bluetooth pairings, PIN, dolphin level. **Files on the SD card stay.**

::: info Internal storage in current firmware
In current firmware, the internal storage (`/int`) is **virtual** and lives in the hidden `/ext/.int/` folder on the SD
card. **Settings → Storage → About Internal Storage** shows `Type: Virtual (/.int on SD)`.
:::

### Back up first (optional)

qFlipper → **Advanced controls** → **BACKUP** → choose a folder → **BACKUP**. This saves the internal storage as a
`.tgz`. The SD card is not included, so copy it separately.

### Reset on the device

1. **Main Menu → Settings → Storage → Factory Reset**.
2. The screen asks `Confirm Factory Reset?`: *"Internal storage will be erased, data and settings will be lost!"*
3. Press <kbd>→</kbd> **Erase** **5 times**. The screen counts the presses left.
4. The Flipper reboots and formats the internal storage.

### Reset with qFlipper

**Advanced controls** → **ERASE** → **ERASE** → **CONTINUE** when done.

### Restore

qFlipper → **Advanced controls** → **RESTORE** → select the backup `.tgz` → **RESTORE** → **CONTINUE**.

If updating still fails after a reset, reset again **without** restoring the backup, or do the
[firmware recovery](#firmware-recovery).

## 4. Reset a forgotten PIN {#reset-pin}

If the Flipper is locked with a PIN you don't remember:

1. **Unplug the USB cable.**
2. Turn the Flipper off: hold <kbd>BACK</kbd> → **Power Off**. If you can't, use the next step but hold the buttons
   for 30–40 seconds instead.
3. Hold <kbd>↑</kbd> + <kbd>BACK</kbd> for about 5 seconds. The Flipper starts with <kbd>↑</kbd> held and shows the
   **PIN reset screen**.
4. **Hold <kbd>→</kbd>** until the progress bar fills to confirm the reset. Press <kbd>↓</kbd> instead to exit without
   resetting.
5. The Flipper reboots.

This resets the user configuration (RTC registers, internal storage with settings and PIN) to factory state.
**User files on the microSD card stay.**

## 5. Still dead?

- Charge for an hour, then try again.
- Disconnect and reconnect the battery (requires opening the case).
- Flash over SWD with an ST-Link or another programmer.

If none of this works, the problem is hardware, not software.

## Related

- [Key combos](/start/key-combos)
- [Installing Unleashed](/start/install)
- [qUnleashed companion app](/mobile/qunleashed-app)
- [qFlipper](/mobile/qflipper)
