---
title: GPIO app
order: 20
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli]
sources: [flipper-docs, unleashed-src]
---
# GPIO app

The built-in **GPIO** app (`Main Menu → GPIO`) has three items:

| Item | What it does |
|---|---|
| `USB-UART Bridge` | Turns the Flipper into a USB-to-serial adapter on pins 13/14 or 15/16 |
| `GPIO Manual Control` | Drives the user pins high while you hold <kbd>OK</kbd> |
| `5V on GPIO` | `OFF` / `ON`: the 5 V output on pin 1 |

![GPIO app menu: USB-UART Bridge, GPIO Manual Control, 5V on GPIO set to OFF](/screens/gpio/menu.png)

Pin numbers and voltages are on the [pinout](/gpio/pinout) page.

## USB-UART Bridge

Use it to talk to a router console, an ESP32/ESP8266 board, a GSM or GPS module, or any 3.3 V serial device from a
computer, with the Flipper as the adapter.

1. Wire the device: **Flipper TX → device RX**, **Flipper RX → device TX**, and a common GND (pin 8, 11 or 18).
   By default TX is pin 13 and RX is pin 14.
2. Connect the Flipper to the computer with USB.
3. Open `Main Menu → GPIO → USB-UART Bridge`. The screen shows `USB Serial`, the `COM PORT` number, the TX/RX pins,
   byte counters and the current baud rate.
4. Press <kbd>←</kbd> (`Config`) to set it up (table below), then <kbd>BACK</kbd> to return to the status screen.
5. Open the port in a terminal program (PuTTY, minicom, screen, the Arduino serial monitor…).
6. To finish, press <kbd>BACK</kbd> and confirm `Exit USB-UART?` with `Exit` (or choose `Stay`).

![USB-UART Bridge status screen: USB Serial, COM PORT 0, TX pin 13, RX pin 14, byte counters, Baud 115200](/screens/gpio/usb_uart.png)

While data flows the LED blinks **blue on TX** and **green on RX**, and the backlight stays on.

### Config screen

![USB-UART Bridge Config: USB Channel, Baudrate, UART Pins, RTS/DTR Pins, DE/RE Pin](/screens/gpio/usb_uart_config.png)

| Setting | Values | Meaning |
|---|---|---|
| `USB Channel` | `0 (CLI)`, `1` | `0 (CLI)`: the bridge takes over the main USB serial port, the CLI is disabled while it runs. `1`: the Flipper exposes two serial ports; the CLI stays on the first, the bridge uses the second |
| `Baudrate` | `Host`, 1200 … 921600 | `Host` follows whatever baud rate the terminal program sets on the port. A number forces a fixed rate (1200, 2400, 4800, 9600, 19200, 28800, 38400, 57600, 115200, 230400, 460800, 921600) |
| `UART Pins` | `13,14`, `15,16` | USART on pins 13 (TX) / 14 (RX), or LPUART on pins 15 (TX) / 16 (RX) |
| `RTS/DTR Pins` | `None`, `2,3`, `6,7`, `16,15` | Outputs the host's RTS and DTR lines (first pin RTS, second DTR, active low). `16,15` is not offered when `UART Pins` is `15,16` |
| `DE/RE Pin` | `None`, `4` | Drives pin 4 as a direction (driver enable) signal for an RS-485 transceiver |

::: tip Flashing ESP boards
RTS/DTR output is what auto-reset/boot circuits on ESP8266/ESP32 and Arduino boards expect. Wire the two pins to the
board's EN/RST and BOOT/GPIO0 logic (through the usual transistor pair) and esptool can put it into the bootloader
without pressing buttons.
:::

### If it says "Connection Is Active!"

The bridge cannot start while qFlipper, the mobile app or another RPC session holds the USB connection. The screen
reads `Connection Is Active! Disconnect from PC or phone to use this function.` Close qFlipper / disconnect the app and
try again.

## GPIO Manual Control

A quick way to check wiring or an LED / relay on a pin.

1. Open `Main Menu → GPIO → GPIO Manual Control`. The screen shows `GPIO Output Mode Test`.
2. Choose the pin with <kbd>←</kbd> / <kbd>→</kbd>: `PA7` (2), `PA6` (3), `PA4` (4), `PB3` (5), `PB2` (6), `PC3` (7),
   `PC1` (15), `PC0` (16) or `ALL`.
3. **Hold** <kbd>OK</kbd>: the pin (or all of them) goes high, 3.3 V, and the green LED lights. Release it and the pin
   goes low again.

All listed pins are push-pull outputs while this screen is open; on exit they go back to high-impedance (analog) mode.
Don't connect anything that drives these pins itself while testing.

## 5V on GPIO

Switches the 5 V output on pin 1. Select the item and change it with <kbd>←</kbd> / <kbd>→</kbd>. The setting is not a
mode of the app: 5 V stays on after you leave the GPIO app, until you switch it off, power the Flipper down, or an
overload fault occurs. See [pinout](/gpio/pinout) for the current limits.

## CLI tools

Two related commands are available in the Flipper [CLI](/dev/cli):

```text
gpio mode <pin_name> <0|1>   # 0 - input, 1 - output
gpio set <pin_name> <0|1>    # set output low/high
gpio read <pin_name>         # read input level
power 5v <0|1>               # 5 V on pin 1 off/on
i2c                          # scan the external I2C bus
```

- Pin names are the port names (`PA7`, `PC0`, …). Debug pins (`PA13`, `PA14`, `PB6`, `PB7`, `PB14`) are accepted only
  with Debug mode on, and the CLI asks `Changing this pin mode may damage hardware...` first.
- `i2c` scans addresses on **PC0 (SCL, pin 16) / PC1 (SDA, pin 15)** at 100 kHz, 7-bit addressing, and prints a table
  where `#` marks a device that answered. Most I2C breakout boards already have pull-ups; if nothing shows up, check
  that yours does.

::: tip Unleashed
For more I2C work (sniffer, reading and writing registers) and sensors, see the `i2c Tools` and `Unitemp` plugins in
the extra app packs, listed on [External modules](/gpio/external-modules).
:::

## Troubleshooting

- **Garbage characters in the terminal:** the baud rate doesn't match. Set `Baudrate` to the device's rate, or keep
  `Host` and set the rate in the terminal program.
- **No data at all:** swap TX and RX, check that GND is shared, check `UART Pins` matches your wiring.
- **CLI disappeared:** `USB Channel` is `0 (CLI)`. Exit the bridge, or use channel `1`.
- **5V on GPIO won't stay on:** the load draws too much (fault shutdown) or a large capacitor on the module trips the
  boost converter at start-up. Power the Flipper off, connect the module, then power on.

## Related

- [GPIO pinout](/gpio/pinout)
- [External modules](/gpio/external-modules)
- [Devboard: debugging and logs](/gpio/devboard-debug)
