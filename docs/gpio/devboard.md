---
title: "Devboard: getting started"
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/USB%20connection%20to%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Wi-Fi%20connection%20to%20the%20Devboard.md, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3]
sources: [unleashed-docs, flipper-docs]
---
# Wi-Fi Devboard: getting started

The official **Wi-Fi Developer Board** is an ESP32-S2 (ESP32-S2-WROVER-N4R2) module for the GPIO header. Out of the
box it runs **Black Magic Probe** firmware and acts as a **debug probe**: it connects your computer's debugger to the
Flipper's STM32 over SWD, via USB or Wi-Fi. It can also forward the Flipper's UART logs.

![Wi-Fi Developer Board](/img/remote/7a7349f75be87abb.jpg)

::: tip You don't need it to flash firmware
Updating, building and uploading your own firmware all work over plain USB. The Devboard is needed only for live
debugging (GDB, breakpoints) and for reading logs independently of the Flipper's OS. For using the same board as a
Wi-Fi tool (Marauder), see [ESP32 & Wi-Fi](/gpio/esp32).
:::

## Step 1. Enable Debug mode on the Flipper

1. Open `Main Menu → Settings → System`.
2. Set `Debug` to `ON`.

Debug mode is needed for debugging apps and unlocks debug options in apps and the [CLI](/dev/cli). Re-enable it
after every firmware update.

## Step 2. Update the board's firmware

The board ships with older firmware. Update it first: [Devboard: firmware update](/gpio/devboard-firmware).

## Step 3. Plug the Devboard into the Flipper

1. **Power the Flipper off first.** The board and the microSD card share the Flipper's 3.3 V rail; hot-plugging a
   large capacitive load can corrupt the card.
2. **Insert it all the way.** Without a case: no gap between Flipper and board (may need some force). In a silicone
   case: no gap in the middle between case and board.
3. Hold <kbd>BACK</kbd> to power the Flipper on.

![Devboard inserted, Flipper without a case](/img/remote/4eb1e40120ff42bb.jpg)

## Step 4. Connect to a computer

### Over USB

Use USB for debugging in **Black Magic** or **DAPLink** mode and for reading logs.

1. List serial devices on the computer:
   - **macOS:** `ls /dev/cu.*`
   - **Linux:** `ls /dev/tty*`
   - **Windows:** Device Manager → **Ports (COM & LPT)**
2. Connect the **Devboard's** USB-C port to the computer.
3. List devices again: **two new ports** appear, both belong to the Devboard.

If nothing appears, try another cable (it must carry data), USB port or computer.

### Over Wi-Fi: access point mode (default)

The board creates its own network. Your computer loses its normal Wi-Fi connection while connected to it.

1. On your computer or phone, connect to the Wi-Fi network:
   - Name: `blackmagic`
   - Password: `iamwitcher`
2. Open <http://192.168.4.1> or <http://blackmagic.local> for the board's web interface.

If the `blackmagic` network doesn't show up:

- reset the Wi-Fi connection on the computer;
- the board may be configured as a client (STA). Hold the board's **BOOT** button for **10 seconds** to reset its
  settings; after it reboots it is an access point again.

### Over Wi-Fi: client mode (STA)

The board joins your existing 2.4 GHz network, so you keep internet access.

1. Connect to the board in access point mode (above) and open <http://192.168.4.1>.
2. Select **STA** mode, enter your network's **SSID** and **password**. The **+** button lists nearby 2.4 GHz networks
   (5 GHz is not supported).
3. Save and reboot the board.
4. From now on open <http://blackmagic.local> over your normal network.

Over Wi-Fi only **Black Magic** debugging is available.

## Hardware

- MCU: ESP32-S2-WROVER-N4R2.
- SWD to the Flipper on **pin 10 (SWCLK)** and **pin 12 (SWDIO)**; UART logs on the Flipper's USART pins 13/14.
- Schematics (PCB, ESP32-S2, power, connectors) and the assembly drawing:
  [Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).

## Next steps

- [Devboard: debugging and logs](/gpio/devboard-debug)
- [Devboard: firmware update](/gpio/devboard-firmware)
- Community: [Discord](https://discord.com/invite/flipper) (#wifi-devboard channel), [Reddit](https://www.reddit.com/r/flipperzero/)
