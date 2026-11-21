---
title: FuriHalBus API
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalBus.md]
sources: [unleashed-docs]
---
# FuriHalBus API

If your app touches MCU peripherals directly (timers, ADC, DMA, …), it must switch their clocks on and off through
**FuriHalBus**. Getting this wrong crashes the Flipper on purpose, so read this before writing low-level code.

## Basics

At system startup most peripherals are held **in reset and unclocked**. This saves power and guarantees that a
peripheral is always in a known state before use. Some essential peripherals are enabled by the system right away;
others must be enabled explicitly by whoever uses them.

> Here, *"system"* means any code that belongs to the operating system, hardware drivers or built-in apps.

| Call | What it does | Precondition — otherwise **crash** |
|---|---|---|
| `furi_hal_bus_enable()` | Clock the peripheral and take it out of reset | Peripheral must be **disabled** (you can't enable it twice) |
| `furi_hal_bus_disable()` | Put it back in reset and stop the clock | Peripheral must be **enabled** |
| `furi_hal_bus_reset()` | Reset all its registers to defaults without disabling it | Peripheral must be **enabled** |

Typical usage:

```c
#include <furi_hal_bus.h>

furi_hal_bus_enable(FuriHalBusTIM1);
// ... configure and use TIM1 ...
furi_hal_bus_disable(FuriHalBusTIM1);
```

## Peripheral categories

Built-in peripherals fall into three groups:

1. enabled by the system at startup and never disabled;
2. enabled and disabled by the system on demand;
3. enabled and disabled by user code.

### 1. Always-on peripherals

Enabled by the system. User code must **never** disable them.

| Peripheral | Enabled in |
|:-:|:-:|
| DMA1, DMA2, DMAMUX | `furi_hal_dma.c` |
| GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH | `furi_hal_resources.c` |
| PKA, AES2, HSEM, IPCC | `furi_hal_bt.c` |
| FLASH | enabled by hardware |

### 2. On-demand system peripherals

Enabled and disabled by the system. Don't use them directly — use the respective API instead. If you really bypass
the API, you must enable the peripheral yourself and disable it when you're done.

| Peripheral | API header |
|:-:|:-:|
| RNG | `furi_hal_random.h` |
| SPI1, SPI2 | `furi_hal_spi.h` |
| I2C1, I2C3 | `furi_hal_i2c.h` |
| USART1, LPUART1 | `furi_hal_serial.h` |
| USB | `furi_hal_usb.h` |

### 3. On-demand shared peripherals

Not enabled by default. User code **must** enable them every time it uses them. Some are also used by the system
for certain features — the system takes such a peripheral only while that feature is active.

| Peripheral | Used by system | Purpose |
|:-:|:-:|:--|
| CRC | | |
| TSC | | |
| ADC | | |
| QUADSPI | | |
| TIM1 | yes | subghz, lfrfid, nfc, infrared, etc. |
| TIM2 | yes | subghz, infrared, etc. |
| TIM16 | yes | speaker |
| TIM17 | yes | cc1101_ext |
| LPTIM1 | yes | tickless idle timer |
| LPTIM2 | yes | pwm |
| SAI1 | | |
| LCD | | |

::: warning
If your app uses e.g. TIM2 while Sub-GHz or Infrared is active (or vice-versa), `furi_hal_bus_enable()` will crash
because the peripheral is already enabled. Make sure the conflicting feature isn't running.
:::

## DMA channels

`DMA1` and `DMA2` are special: each has several independent channels, and some are used by the system.

| DMA | Channel | Used by system | Purpose |
|:-:|:-:|:-:|:--|
| DMA1 | 1 | yes | digital signal |
| DMA1 | 2 | yes | digital signal |
| DMA1 | 3 | | |
| DMA1 | 4 | yes | pulse reader |
| DMA1 | 5 | | |
| DMA1 | 6 | yes | USART_Rx |
| DMA1 | 7 | yes | LPUART_Rx |
| DMA2 | 1 | yes | infrared, lfrfid, subghz |
| DMA2 | 2 | yes | infrared, lfrfid, subghz |
| DMA2 | 3 | yes | cc1101_ext |
| DMA2 | 4 | yes | cc1101_ext |
| DMA2 | 5 | yes | cc1101_ext |
| DMA2 | 6 | yes | SPI |
| DMA2 | 7 | yes | SPI |

Free for your own use: **DMA1 channels 3 and 5**.

## Related pages

- [Furi API](/dev/furi-api)
- [Hardware targets](/dev/hardware-targets)
- [Debugging apps](/dev/debugging)
