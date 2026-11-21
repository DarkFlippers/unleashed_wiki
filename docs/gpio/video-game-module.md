---
title: Video Game Module
order: 90
original: [https://docs.flipper.net/zero/video-game-module, https://docs.flipper.net/zero/video-game-module/quick-start, https://docs.flipper.net/zero/video-game-module/firmware-update, https://docs.flipper.net/zero/video-game-module/custom-firmware, https://docs.flipper.net/zero/video-game-module/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [flipper-docs, unleashed-src]
---
# Video Game Module

The **Video Game Module** (VGM) is an official add-on built around the **Raspberry Pi RP2040**. It plugs into the GPIO
header and adds:

- **Video Out** — mirrors the Flipper screen to a TV or monitor (DVI-D signal, 640×480);
- a **6-axis motion sensor** (TDK ICM-42688-P: 3-axis gyroscope + accelerometer) for gyro controls;
- a **USB-C port** wired to the RP2040 (flashing, or used by custom firmware);
- a **14-pin GPIO breakout** of the RP2040;
- **BOOT / RESET buttons** (press with a paper clip) for UF2 flash mode and reset;
- an RGB LED on top.

It can also work as a standalone RP2040 board, compatible with Raspberry Pi Pico projects.

![Video Game Module buttons and connectors](/img/remote/b24db83aa0fa8a69.jpg)

## Install and connect to a TV

1. **Fit the module.** It comes with a silicone bumper made for a Flipper *without* a case. If your Flipper is in a
   silicone case, take the bumper off the module (or the case off the Flipper).
2. **Firmware.** The module needs Flipper firmware 0.98.3 or later; current Unleashed releases qualify.
3. **Check the UART setting:** `Main Menu → Settings → Expansion Modules → Listen UART` must be **`USART`**. With any
   other value the module is not detected. (See [Expansion modules](/gpio/expansion-modules).)
4. Plug the module in (Flipper off), power on. The Flipper detects the module and prepares it automatically.
5. Connect the TV cable to the module's **Video Out** port and select that input on the TV.

### "Video Game Module not initialized"

This text on the TV means the module isn't talking to a Flipper: the firmware is too old, `Listen UART` isn't `USART`,
or the module is powered (e.g. over USB) without a Flipper attached.

## Games and apps

The motion sensor is used by apps from the Flipper Apps Catalog, for example
[Air Arkanoid](https://lab.flipper.net/apps/air_arkanoid) and [Air Mouse](https://lab.flipper.net/apps/vgm_air_mouse)
(gyro mouse for a computer).

::: tip Unleashed
The Unleashed JavaScript engine includes a `vgm` module (JS feature `vgm`): `getPitch()`, `getRoll()`, `getYaw()` and
`deltaYaw(angle, timeout)` read the module's orientation from a script, returning `undefined` if no VGM is present.
See the [Development](/dev/) section for JavaScript apps.
:::

## Updating the module firmware

Updates are installed with the **Video Game Module Tool** app (from the Flipper Apps Catalog). Its menu:

- `Install Official Firmware` — the latest official module firmware, bundled with the app;
- `Install Firmware from File` — a custom `.uf2` from the SD card.

To update:

1. Install (or **first update**) Video Game Module Tool: in the Flipper mobile app go to **Apps**, search for
   *Video Game Module Tool*, tap **INSTALL** / **UPDATE**. A new module firmware arrives with a new version of the app,
   so always update the app before updating the module.
2. Connect the module to the Flipper.
3. Open `Main Menu → Apps → Tools → Video Game Module Tool`.
4. Select `Install Official Firmware`, confirm with `Install` (<kbd>→</kbd>).
5. Wait for **Video Game Module Updated**.

## Custom firmware

The module can run your own RP2040 firmware.

### From Flipper Zero

Lets you keep several module firmwares on the SD card and switch without a computer.

1. Copy the `.uf2` file to the Flipper's SD card (e.g. with [qFlipper](/mobile/qflipper): `File manager → SD Card`,
   create a folder, upload the file).
2. Connect the module, open `Apps → Tools → Video Game Module Tool → Install Firmware from File`.
3. Select the file and confirm with `Install` (<kbd>→</kbd>). Wait for **Video Game Module Updated**.

::: warning UF2 limitations when installing via Flipper
- Non-flash blocks are not supported.
- Block payloads must be exactly 256 bytes.
- Payload target addresses must be 256-byte aligned, with no gaps.
- File containers and extension tags are not supported.
:::

### From a computer

1. Disconnect the module from the Flipper and from USB.
2. Hold the module's **BOOT** button with a paper clip.
3. Connect the module to the computer with USB-C. It mounts as a USB drive named **RPI-RP2**. Release **BOOT**.
4. Drag the `.uf2` file onto **RPI-RP2**. The module reboots and unmounts by itself.

## Hardware details (for standalone use)

### RP2040 GPIO

- GPIO **8–15** and **18–20** are used for video out and are not available on the connectors.
- GPIO **0–7, 16, 17, 21, 22, 26–28** are on the connectors (as on a Raspberry Pi Pico). GPIO **2–7** are also wired
  to the motion sensor.
- GPIO **23–25 and 29** (used internally on a Pico) are free on the VGM and exposed on the 14-pin breakout.

![Video Game Module 14-pin breakout pinout](/img/remote/b030c6a0375c6254.png)

![Video Game Module and Raspberry Pi Pico pinouts](/img/remote/9e55d40b6c557fa8.jpg)

### Peripherals available to the RP2040

- **Video Out:** video and sound to a TV/monitor, plus data exchange over the
  [Display Data Channel](https://en.wikipedia.org/wiki/Display_Data_Channel).
- **USB-C:** USB device or host (no USB Power Delivery).
- **IMU:** TDK ICM-42688-P.
- **GPIO breakout:** 11 GPIO pins with ESD protection.
- **Connector to Flipper Zero:** Flipper pins 13 and 14 fully functional; pins 2–7 with limited functionality (shared
  with the IMU). ESD-protected.
- **RGB LED**, controlled from RP2040 GPIO.

### Power

- 5 V over USB-C when standalone;
- 3.3 V (pin 9) or 5 V (pin 1) from the Flipper.

Powering from USB-C and the Flipper at the same time is safe for the module and both sources.

Schematics, PCB assembly drawings and PDF pinouts are on the official
[GPIO on Video Game Module](https://docs.flipper.net/zero/video-game-module/gpio) page.

## Related

- [Expansion modules](/gpio/expansion-modules)
- [GPIO pinout](/gpio/pinout)
- [External modules](/gpio/external-modules)
