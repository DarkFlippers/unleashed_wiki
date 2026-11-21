---
title: Key combos
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://docs.flipper.net/zero/basics/reboot, https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src]
sources: [unleashed-docs, flipper-docs, unleashed-src]
---
# Key combos

Sometimes the Flipper stops responding because of a software problem. These button combinations reset it at the
hardware level or start it in DFU (firmware update) mode, without the help of the frozen firmware.

## Quick reference

| Goal | Combo | USB |
|---|---|---|
| Reboot a frozen Flipper | <kbd>←</kbd> + <kbd>BACK</kbd>, ~2–5 s | any |
| Power reset | <kbd>BACK</kbd>, 30 s | **unplugged** |
| DFU via Flipper bootloader (with indication) | <kbd>←</kbd> + <kbd>BACK</kbd>, release <kbd>BACK</kbd>, hold <kbd>←</kbd> until blue LED | any |
| DFU via ST bootloader (no indication) | <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd>, release <kbd>BACK</kbd> and <kbd>←</kbd> | any |
| PIN / settings reset screen | hold <kbd>↑</kbd> while the Flipper boots | — |

## Basic combos

### Hardware reset

1. Press and hold <kbd>←</kbd> and <kbd>BACK</kbd> for a couple of seconds.
2. Release both.

This pulls the MCU reset line down. Path: keys → DD8 (NC7SZ32M5X, OR gate) → DD1 (STM32WB55, MCU).

**Doesn't work if:** the MCU debug block is active and holds the reset line from inside.

### Hardware power reset

1. Disconnect the USB cable and any external power supply. Double-check that USB really is unplugged.
2. Press and hold <kbd>BACK</kbd> for **30 seconds**. This only works with USB disconnected.
3. Release <kbd>BACK</kbd>.

This switches the SYS power line off and on through the charger chip DD6 (bq25896).

**Doesn't work if:** power is connected to USB or 5V_ext.

### Software DFU

Hold <kbd>←</kbd> while the Flipper boots. It enters DFU mode through the **Flipper bootloader**.

**Doesn't work if:** the Flipper bootloader is damaged or missing.

### Hardware DFU

Hold <kbd>OK</kbd> while the Flipper boots. It enters DFU mode through the **ST bootloader** built into the MCU.

**Doesn't work if:** the Option Bytes are damaged or set to ignore the <kbd>OK</kbd> key.

## DFU combos

### Hardware reset + software DFU

1. Hold <kbd>←</kbd> + <kbd>BACK</kbd> for a couple of seconds.
2. Release <kbd>BACK</kbd>.
3. The device enters DFU **with indication**: blue LED and the DFU screen.
4. Release <kbd>←</kbd>.

**Doesn't work if:** the MCU debug block holds the reset line, or the Flipper bootloader is damaged or missing.

### Hardware reset + hardware DFU

1. Hold <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd> for a couple of seconds.
2. Release <kbd>BACK</kbd> and <kbd>←</kbd>.
3. The device enters DFU **without indication**. The screen stays blank. This is normal.

**Doesn't work if:** the MCU debug block holds the reset line, or the Option Bytes are damaged or set to ignore <kbd>OK</kbd>.

### Hardware power reset + software DFU

1. Disconnect USB and any external power.
2. Hold <kbd>BACK</kbd> + <kbd>←</kbd> for 30 seconds.
3. Release <kbd>BACK</kbd>.
4. The device enters DFU with indication (blue LED + DFU screen).
5. Release <kbd>←</kbd>.
6. Plug in USB.

**Doesn't work if:** power is connected to USB or 5V_ext, or the Flipper bootloader is damaged or missing.

### Hardware power reset + hardware DFU

1. Disconnect USB and any external power.
2. Hold <kbd>BACK</kbd> + <kbd>OK</kbd> for 30 seconds.
3. Release <kbd>BACK</kbd> and <kbd>OK</kbd>.
4. The device enters DFU without indication.
5. Plug in USB.

**Doesn't work if:** power is connected to USB or 5V_ext, or the Option Bytes are damaged or set to ignore <kbd>OK</kbd>.

## What to do in DFU mode

Connect the Flipper to a computer. It shows up as **DFU in FS Mode** (Windows/macOS) or
**STMicroelectronics STM Device in DFU Mode** (`lsusb` on Linux). Then repair the firmware with qFlipper:
[Recovery](/start/recovery#firmware-recovery).

## If nothing helps

- Make sure the battery is charged: leave it on a charger for an hour.
- Disconnect the battery and connect it again (requires opening the case).
- Flash the device with an ST-Link or another SWD programmer.

If the device still doesn't work after all this, the problem is **not software**.
