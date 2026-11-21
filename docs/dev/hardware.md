---
title: Hardware
order: 140
original: [https://docs.flipper.net/zero/development/hardware, https://docs.flipper.net/zero/development/hardware/tech-specs, https://docs.flipper.net/zero/development/hardware/schematic, https://docs.flipper.net/zero/development/hardware/flipper-blueprints, https://docs.flipper.net/zero/development/hardware/modules-blueprints, https://docs.flipper.net/zero/development/hardware/vgm-blueprints, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Hardware

Technical specifications of Flipper Zero, plus where to find its schematics, drawings and 3D models — useful for
building external modules, cases, and for low-level debugging.

![Flipper Zero tech specs overview](/img/remote/629725f9f16a5946.png)

## Tech specs

### Body, size and weight

| | |
|---|---|
| Materials | PC, ABS, PMMA |
| Height | 40.1 mm (1.58 in) |
| Width | 100.3 mm (3.95 in) |
| Depth | 25.6 mm (1.01 in) |
| Weight | 102 g (3.6 oz) |

### Display

| | |
|---|---|
| Type | Monochrome LCD |
| Resolution | 128×64 pixels |
| Controller | ST7567 |
| Interface | SPI |
| Diagonal | 1.4″ |

### Microcontroller

| | |
|---|---|
| Model | [STM32WB55RG](https://www.st.com/en/microcontrollers-microprocessors/stm32wb55rg.html) |
| Application core | Arm Cortex-M4, 32-bit, 64 MHz |
| Radio core | Arm Cortex-M0+, 32-bit, 32 MHz |
| Radio | Bluetooth LE 5.4, 802.15.4, proprietary |
| Flash | 1024 KB (shared between application and radio) |
| SRAM | 256 KB (shared between application and radio) |

### Sub-1 GHz

| | |
|---|---|
| Transceiver | [CC1101](https://www.ti.com/product/CC1101) |
| TX power | −20 dBm max (per official specs) |
| Frequency bands | 315 MHz, 433 MHz, 868 MHz, 915 MHz (depends on region) |

The CC1101 tunes in the ranges 299.999755–348 MHz, 386.999938–464 MHz and 778.999847–928 MHz.

::: tip Unleashed
Unleashed removes the regional TX restrictions and adds extra frequencies (350 MHz and 467 MHz are added to the
default range). The range can be extended further to 281–361, 378–481 and 749–962 MHz via the
`subghz/assets/dangerous_settings` file — this is outside the CC1101 specs and **can damage the hardware**
([dangerous settings](/start/dangerous-settings)). An [external CC1101 module](/subghz/external-cc1101) is also
supported. Respect the radio regulations of your country.
:::

### NFC

| | |
|---|---|
| Transceiver | [ST25R3916](https://www.st.com/en/nfc/st25r3916.html) |
| Frequency | 13.56 MHz |
| Cards | ISO-14443A/B; NXP MIFARE Classic®, Ultralight®, DESFire® etc.; FeliCa™; HID iClass (Picopass); NFC Forum protocols |

### 125 kHz RFID

| | |
|---|---|
| Frequency | 125 kHz |
| Modulation | AM, OOK |
| Coding | ASK, PSK |
| Cards (official list) | EM-Micro EM4100, HID H10301, IDTECK Idteck, Motorola Indala 26, Kantech IoProx XSF, AWID, FECAVA FDX-A, ISO FDX-B, Generic HID Prox, Generic HID Ext, Farpointe Pyramid, Viking, Jablotron, Paradox, PAC Stanley, Keri, Gallagher, Honeywell Nexwatch, Electra, Securakey |

See [RFID → Read](/rfid/read) for the protocols the Unleashed firmware actually supports.

### Infrared

| | |
|---|---|
| RX wavelength | 950 nm (±100 nm) |
| RX carrier | 38 kHz (±5%) |
| TX wavelength | 940 nm |
| TX carrier | 0–2 MHz |
| TX power | 300 mW |
| Protocols | NEC family, Kaseikyo, RCA, RC5, RC6, Samsung, SIRC |

### iButton (1-Wire)

Dallas DS199x, DS1971, CYFRAL, Metakom, TM2004, RW1990.

### GPIO

- 13 I/O pins available on external 2.54 mm headers
- 3.3 V CMOS levels
- Inputs 5 V tolerant (see ST [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf))
- Up to 20 mA per digital pin

Pin map: [GPIO pinout](/gpio/pinout).

### Battery and power

| | |
|---|---|
| Type | Lithium polymer (LiPo) |
| Capacity | 2100 mAh |
| Battery life | Up to 28 days |
| Operating temperature | 0…40 °C (32…104 °F) |

### microSD card

| | |
|---|---|
| Maximum capacity | Up to 256 GB |
| Recommended capacity | 2–32 GB |
| Interface | SPI |
| Read/write speed | Up to 5 Mbps |

The Flipper doesn't come with a microSD card — buy one separately. See [SD card](/start/sd-card).

### USB

| | |
|---|---|
| Connector | Type-C |
| Standard | USB 2.0 |
| Data rate | 12 Mbps |
| Max charging current | 1 A |

### Bluetooth LE 5.4

| | |
|---|---|
| TX power | 4 dBm max |
| RX sensitivity | −96 dBm |
| Data rate | 2 Mbps |

### Buzzer and vibration

| | |
|---|---|
| Buzzer frequency | 100–2500 Hz |
| Buzzer output | 87 dB |
| Buzzer type | Coin |
| Vibration force | 30 N |
| Vibration motor speed | 13500 rpm |

### In the box

Flipper Zero, USB-C to USB-A cable, documentation, sticker.

## Schematics

Schematics of all Flipper Zero PCBs are published by Flipper Devices "for educational purposes" — useful for
hardware module development and low-level debugging. The interactive Altium viewers and PDF downloads are on the
official page: **[Schematics of Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)**.

![Flipper Zero PCBs](/img/remote/db285947a71be613.png)

| PCB | Available documents |
|---|---|
| **Main PCB** (rev. 12.1.F7B9C6) | Assembly drawing; main blocks overview; Power; Peripherals; MCU STM32WB55; LCD display; Sub-1 GHz CC1101; Buttons |
| **iButton PCB** (rev. 12.F7B9C6) — also carries the piezo speaker and IR | Assembly drawing; iButton schematic |
| **NFC RFID PCB** (rev. 12.F7B9C6) — 125 kHz RFID and NFC | Assembly drawing; NFC blocks overview; NFC; Power and vibro; RFID |
| **Antenna PCB** | Board image |

::: info
In revision 13.F7B9C6 of the iButton PCB the pogo pin footprints changed: through-hole pogo pins replaced SMD ones.
The footprint diameters are the same as in 12.F7B9C6.
:::

## Blueprints and 3D models

All files are downloadable from the official pages:

| What | Files | Page |
|---|---|---|
| Flipper Zero body | 2D drawing (`.pdf`, `.dwg`), 3D model (`.stl`) | [Blueprints of Flipper Zero](https://docs.flipper.net/zero/development/hardware/flipper-blueprints) |
| Regular external module | Drawing (`.pdf`), PCB 3D model (`.stp`, plain and assembled), PCB outline (`.dwg`, `.dxf`) | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Small external module | Same set as the regular module | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Video Game Module | Drawing (`.pdf`, `.dwg.zip`), 3D model (`.stp`) | [Blueprints of Video Game Module](https://docs.flipper.net/zero/development/hardware/vgm-blueprints) |

![Drawing of Flipper Zero](/img/remote/c91e01d61829df8e.png)

The external module drawings give the recommended geometry for boards that plug into the GPIO header — start there
if you design your own module (see also [Expansion modules](/gpio/expansion-modules)).

## Developer boards

### Wi-Fi Developer Board

Based on **ESP32-S2-WROVER-N4R2**. Published documents: PCB view, assembly drawing (`Wi-Fi Module_V1_Assembly.pdf`),
ESP32-S2 schematic, Power schematic, Connectors schematic —
[Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).
Usage: [Dev Board](/gpio/devboard), [Debugging apps](/dev/debugging).

### ST-Link V3 Developer Board

For advanced developers who need in-circuit debugging. It's based on the
[ST-Link V3 Mods](https://www.st.com/en/development-tools/stlink-v3mods.html) module and differs only in form factor
and ease of connection.

- ST-Link V3 Mods for flashing and in-circuit debugging.
- Built-in UART-to-USB, connected to the Flipper's UART (GPIO pins 13 and 14).
- Unused Flipper Zero and ST-Link pins exposed for debugging and prototyping.

Altium Designer project: [github.com/Flipper-Zero/flipperzero-devboard-stlinkv3](https://github.com/Flipper-Zero/flipperzero-devboard-stlinkv3).
Schematic and BOM: [ST-Link V3 Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3).

::: info You don't need it to update or develop
Firmware updates, development and uploading your own firmware all work over plain USB. A debug board is only needed
to debug firmware while it runs (GDB, OpenOCD, …).
:::

## Related pages

- [GPIO pinout](/gpio/pinout)
- [Furi API](/dev/furi-api) — hardware block diagram
- [Debugging apps](/dev/debugging)
- [OTA updates](/dev/ota)

MIFARE, MIFARE Ultralight, MIFARE Classic and DESFire are registered trademarks of NXP B.V. FeliCa is a trademark of
Sony Corporation.
