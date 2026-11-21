---
title: "Devboard: firmware update"
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md]
sources: [unleashed-docs]
---
# Devboard: firmware update

How to update (or restore) the firmware of the Wi-Fi Developer Board itself, using **uFBT**. This is not the Flipper's
firmware: for that see [Updating](/start/updating).

## Step 1. Install uFBT

[uFBT (micro Flipper Build Tool)](https://pypi.org/project/ufbt/) builds and debugs apps, flashes firmware, creates VS Code
configs and flashes the Wi-Fi Devboard.

**Linux & macOS**

1. Install `pipx` ([instructions](https://pipx.pypa.io/stable/installation/)) and restart the terminal.
2. Install uFBT:

   ```bash
   pipx install ufbt
   ```

**Windows**

1. Install the latest [Python](https://www.python.org/downloads/windows/).
2. In PowerShell:

   ```powershell
   py -m pip install --user pipx
   py -m pipx ensurepath
   ```

3. Restart PowerShell, then:

   ```powershell
   pipx install ufbt
   ```

## Step 2. Put the board in bootloader mode

1. List serial devices: macOS `ls /dev/cu.*`, Linux `ls /dev/tty*`, Windows Device Manager → **Ports (COM & LPT)**.
2. Connect the Devboard to the computer with a USB-C cable.
3. Enter bootloader mode:
   1. press and hold **BOOT**;
   2. press and release **RESET** while holding **BOOT**;
   3. release **BOOT**.
4. List devices again and note the new one.

![Devboard bootloader buttons](/img/remote/060af5decf4b567c.jpg)

## Step 3. Flash

Linux & macOS:

```bash
python3 -m ufbt devboard_flash
```

Windows (PowerShell):

```powershell
py -m ufbt devboard_flash
```

Success message: `WiFi board flashed successfully`.

### If flashing fails

Errors such as

```text
A fatal error occurred: Serial data stream stopped: Possible serial noise or corruption.
```

or

```text
FileNotFoundError: [Errno 2] No such file or directory: '/dev/cu.usbmodem01'
```

are usually fixed by:

- unplugging and reconnecting the board, then entering bootloader mode again;
- another USB port;
- another USB-C cable.

## Step 4. Finish

1. Press **RESET** on the board.
2. Unplug and reconnect the USB-C cable.

The board now runs the latest official Black Magic firmware. This is also how you restore it after flashing other
firmware (e.g. [Marauder](/gpio/esp32)). Continue with [plugging it into the Flipper](/gpio/devboard).
