---
title: External IR modules
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/furi_hal_include/furi_hal_infrared.h, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/infrared]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# External IR modules (GPIO)

The three built-in IR LEDs are fine for a living room, but range is limited. For more power you can connect an
**external IR transmitter** (a board with stronger LEDs and a driver transistor) to the GPIO header. The Infrared app
then sends through it instead of the built-in LEDs. Universal remotes, saved remotes, the mobile app and the
"Send" button on the capture screen all use the selected output.

::: tip Unleashed
External IR module support with automatic detection is listed among Unleashed features; the detection logic itself
comes from the official firmware, so the behaviour described here is the same on both.
:::

## Wiring

| Module pin | Flipper GPIO pin |
|---|---|
| Signal / IN | **2 (A7)** |
| VCC | **1 (5V)**, powered when "5V on GPIO" is ON, or 9 (3V3) for 3.3 V modules |
| GND | 8, 11 or 18 (GND) |

Pin 2 carries the **same modulated signal** (carrier included, typically 38 kHz) that normally drives the internal
LEDs, so the module only needs a driver stage and LEDs, no own modulator. See [GPIO pinout](/gpio/pinout) for the
header layout.

::: warning
Learning (receiving) always uses the built-in receiver. The external module is transmit-only.
:::

## GPIO Settings

Go to `Main Menu → Infrared → GPIO Settings`. There are two options:

| Option | Values | Meaning |
|---|---|---|
| **Signal Output** | `Flipper` | Built-in IR LEDs (default). |
| | `2 (A7)` | Always transmit on GPIO pin 2. |
| | `Detect` | Auto-detect an external module on pin 2 each time the Infrared app starts. |
| **5V on GPIO** | `OFF` / `ON` | Switches 5 V on GPIO pin 1 to power the module. With `Detect` it shows **`Auto`** and is controlled automatically. |

Settings are saved when you leave the screen, to `/ext/infrared/.infrared.settings`, and applied every time the
Infrared app starts. When you exit the Infrared app, the output returns to the built-in LEDs and 5 V is switched off
again, so the module doesn't drain the battery in other apps.

### Step by step

1. Connect the module (Signal → pin 2, VCC → pin 1, GND → pin 8/11/18).
2. Open `Infrared → GPIO Settings`.
3. Set **Signal Output** to `Detect` (or `2 (A7)` if detection doesn't work with your module).
4. With `2 (A7)`, set **5V on GPIO** to `ON` if the module is powered from pin 1.
5. Press <kbd>Back</kbd>. Send any saved button or a universal remote; the module's LEDs should now transmit.

## How auto-detection works

When `Detect` is selected, the firmware briefly enables a **weak pull-up** on pin 2 and reads it back:

- if the pin stays **low**, something with a pull-down is attached, so an external module is assumed. Output goes to
  pin 2 and **5 V on GPIO is switched on automatically**;
- if the pin reads **high**, nothing is connected and the built-in LEDs are used.

This works best with modules whose LED driver is a **MOSFET with a strong pull-down** on the gate, or a **BJT**
to drive the IR LEDs. The module **must pull the pin down to 0.9 V or lower** to be
detected. If your module has no pull-down, choose `2 (A7)` manually and switch 5 V on yourself.

Detection happens when the Infrared app starts (and when you select `Detect`). If you plug the module in while the
app is open, re-select `Detect` or restart the app.

## Troubleshooting

| Problem | What to try |
|---|---|
| `Detect` always uses the built-in LEDs | The module doesn't pull pin 2 low enough (≤ 0.9 V). Use `2 (A7)` and turn `5V on GPIO` ON manually. |
| Module LED doesn't light up | Check VCC: with `2 (A7)` 5 V must be ON. Check GND. Look at the LEDs through a phone camera while sending. |
| Battery drains fast | A powerful module draws a lot from 5 V. Disconnect it when not used. |

## Related pages

- [GPIO pinout](/gpio/pinout)
- [GPIO modules](/gpio/external-modules)
- [Learning and sending signals](/infrared/read)
- [Universal remotes](/infrared/universal-remotes)
