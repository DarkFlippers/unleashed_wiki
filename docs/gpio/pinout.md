---
title: GPIO pinout
order: 10
original: [https://docs.flipper.net/zero/gpio-and-modules, https://docs.flipper.net/zero/development/hardware/tech-specs, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/f7/furi_hal/furi_hal_resources.c]
sources: [flipper-docs, unleashed-src]
---
# GPIO pinout

The Flipper Zero has an 18-pin, 2.54 mm header on its top edge. It carries power outputs, ground, 13 I/O pins wired
to the STM32WB55 microcontroller, the SWD debug lines and the 1-Wire line shared with iButton.

![Flipper Zero GPIO pin functions](/img/remote/b75cf29833cf8de8.jpg)

## Pin table

Pin numbers count from **pin 1 (+5 V)**. Port names (`PA7`, `PC0`, …) are the names the firmware uses on screen and in
the CLI.

| Pin | Name | Main functions | Notes |
|---|---|---|---|
| 1 | +5V | 5 V power output | Off on battery until enabled, see below |
| 2 | PA7 | SPI MOSI, PWM (TIM1), ADC | External CC1101 / NRF24 MOSI |
| 3 | PA6 | SPI MISO, ADC | External CC1101 / NRF24 MISO |
| 4 | PA4 | SPI CS, PWM (LPTIM2), ADC | External CC1101 / NRF24 CS; USB-UART DE/RE pin |
| 5 | PB3 | SPI SCK | External CC1101 / NRF24 SCK |
| 6 | PB2 | GPIO | External CC1101 GDO0, NRF24 CE |
| 7 | PC3 | GPIO, ADC | External CC1101 amplifier control |
| 8 | GND | Ground | |
| 9 | 3V3 | 3.3 V power output | On by default |
| 10 | PA14 | SWCLK | Debug (SWD) |
| 11 | GND | Ground | |
| 12 | PA13 | SWDIO | Debug (SWD) |
| 13 | PB6 | USART TX | Default UART for the USB-UART bridge, logs, expansion modules |
| 14 | PB7 | USART RX | |
| 15 | PC1 | LPUART TX, I2C SDA, ADC | Second UART; external I2C data |
| 16 | PC0 | LPUART RX, I2C SCL, ADC | Second UART; external I2C clock |
| 17 | PB14 | 1-Wire | iButton line |
| 18 | GND | Ground | |

The firmware marks pins 10, 12, 13, 14 and 17 as **debug pins**: they are hidden from `GPIO Manual Control`, and the CLI
`gpio` command lists them only with Debug mode on (and asks for confirmation before changing them).

![Detailed Flipper Zero GPIO pinout](/img/remote/e77df2d4499cbbbc.jpg)

A printable PDF of the pinout is available on the
[official GPIO page](https://docs.flipper.net/zero/gpio-and-modules).

## Electrical limits

- **Logic level:** 3.3 V CMOS. Every I/O pin goes to the MCU through a 51 Ω resistor and is ESD-protected.
- **Current per pin:** up to 20 mA.
- **Total from I/O pins:** keep it under 5 W, otherwise the battery protection can trip and the Flipper shuts down.
- **5 V tolerance:** only for a pin configured as an **input**. A pin set as an output is not 5 V tolerant. Avoid 5 V
  logic peripherals unless you use a level shifter. Details: ST application note
  [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf).

### +3.3 V (pin 9)

- Enabled by default, maximum load **1.2 A**.
- The microSD card is powered from the same rail. Pin 9 is briefly switched off during firmware updates and when the
  card is mounted.

::: warning
Connect modules with a large capacitive load only while the Flipper is powered off, or you risk corrupting data on the
microSD card.
:::

### +5 V (pin 1)

- From USB: when a cable is plugged in, pin 1 is fed directly from USB. Never pull more than **1.2 A**.
- From the battery: the output is **off by default**. The boost converter (OTG) gives up to **1.2 A** when enabled.

To turn 5 V on while running on the battery:

1. Open `Main Menu → GPIO`.
2. Select `5V on GPIO` and switch it to `ON` with <kbd>→</kbd>.

Other ways to switch it:

- CLI: `power 5v 1` / `power 5v 0` (see [CLI](/dev/cli)).
- `Infrared → GPIO Settings → 5V on GPIO` for external IR modules.
- Apps such as Sub-GHz (external CC1101) and [SIM800](/gpio/sim800) request it automatically, and an
  [expansion module](/gpio/expansion-modules) can ask for it over its protocol.

::: tip How the firmware handles 5 V
If you request 5 V while USB power is present, the power service postpones enabling the boost converter and turns it
on by itself once USB is unplugged. If the charger reports an OTG fault (overload or short), 5 V is switched off and
the request is cleared, so you have to enable it again.
:::

## Pins in DFU mode

In DFU (bootloader) mode the I/O pins, except pin 17, change state according to STMicroelectronics
[AN2606](https://www.st.com/resource/en/application_note/cd00167594-stm32-microcontroller-system-memory-boot-mode-stmicroelectronics.pdf)
(table "STM32WB30xx/35xx/50xx/55xx configuration in system memory boot mode"). Keep that in mind if a module reacts to
pin levels while you [recover](/start/recovery) the Flipper.

## Inserting a module

- **Without a silicone case:** push the module all the way in so no pins are visible between the Flipper and the
  module. It may need some force.
- **In a silicone case:** push it in until there is no gap in the middle between the case and the module.

![Module inserted all the way](/img/remote/52e7045a797ed1c4.png)

## Related

- [GPIO app](/gpio/gpio-app)
- [External modules](/gpio/external-modules)
- [Flipper Zero schematics](https://docs.flipper.net/zero/development/hardware/schematic)
