---
title: FuriHalBus-API
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalBus.md]
sources: [unleashed-docs]
---
# FuriHalBus-API

Wenn deine App direkt auf MCU-Peripherie zugreift (Timer, ADC, DMA, …), muss sie deren Takte über **FuriHalBus**
ein- und ausschalten. Macht man das falsch, stürzt der Flipper absichtlich ab — lies das also, bevor du
Low-Level-Code schreibst.

## Grundlagen

Beim Systemstart wird die meiste Peripherie **im Reset und ohne Takt** gehalten. Das spart Energie und garantiert,
dass eine Peripherieeinheit vor der Verwendung immer in einem bekannten Zustand ist. Einige unverzichtbare
Peripherieeinheiten aktiviert das System sofort; andere müssen ausdrücklich von dem aktiviert werden, der sie
benutzt.

> *"System"* bedeutet hier jeden Code, der zum Betriebssystem, zu den Hardwaretreibern oder zu den eingebauten Apps
> gehört.

| Aufruf | Funktion | Vorbedingung — sonst **Crash** |
|---|---|---|
| `furi_hal_bus_enable()` | Taktet die Peripherieeinheit und nimmt sie aus dem Reset | Die Peripherieeinheit muss **deaktiviert** sein (du kannst sie nicht zweimal aktivieren) |
| `furi_hal_bus_disable()` | Setzt sie zurück in den Reset und stoppt den Takt | Die Peripherieeinheit muss **aktiviert** sein |
| `furi_hal_bus_reset()` | Setzt alle ihre Register auf die Standardwerte zurück, ohne sie zu deaktivieren | Die Peripherieeinheit muss **aktiviert** sein |

Typische Verwendung:

```c
#include <furi_hal_bus.h>

furi_hal_bus_enable(FuriHalBusTIM1);
// ... configure and use TIM1 ...
furi_hal_bus_disable(FuriHalBusTIM1);
```

## Peripherie-Kategorien

Die eingebaute Peripherie teilt sich in drei Gruppen:

1. vom System beim Start aktiviert und nie deaktiviert;
2. vom System bei Bedarf aktiviert und deaktiviert;
3. von Benutzercode aktiviert und deaktiviert.

### 1. Dauerhaft aktive Peripherie

Vom System aktiviert. Benutzercode darf sie **niemals** deaktivieren.

| Peripherieeinheit | Aktiviert in |
|:-:|:-:|
| DMA1, DMA2, DMAMUX | `furi_hal_dma.c` |
| GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH | `furi_hal_resources.c` |
| PKA, AES2, HSEM, IPCC | `furi_hal_bt.c` |
| FLASH | von der Hardware aktiviert |

### 2. Systemperipherie bei Bedarf

Vom System aktiviert und deaktiviert. Verwende sie nicht direkt — nimm stattdessen die jeweilige API. Wenn du die
API wirklich umgehst, musst du die Peripherieeinheit selbst aktivieren und nach der Nutzung wieder deaktivieren.

| Peripherieeinheit | API-Header |
|:-:|:-:|
| RNG | `furi_hal_random.h` |
| SPI1, SPI2 | `furi_hal_spi.h` |
| I2C1, I2C3 | `furi_hal_i2c.h` |
| USART1, LPUART1 | `furi_hal_serial.h` |
| USB | `furi_hal_usb.h` |

### 3. Gemeinsam genutzte Peripherie bei Bedarf

Standardmäßig nicht aktiviert. Benutzercode **muss** sie jedes Mal aktivieren, wenn er sie verwendet. Einige werden
für bestimmte Funktionen auch vom System genutzt — das System belegt eine solche Peripherieeinheit nur, solange die
jeweilige Funktion aktiv ist.

| Peripherieeinheit | Vom System genutzt | Zweck |
|:-:|:-:|:--|
| CRC | | |
| TSC | | |
| ADC | | |
| QUADSPI | | |
| TIM1 | ja | subghz, lfrfid, nfc, infrared usw. |
| TIM2 | ja | subghz, infrared usw. |
| TIM16 | ja | speaker |
| TIM17 | ja | cc1101_ext |
| LPTIM1 | ja | Tickless-Idle-Timer |
| LPTIM2 | ja | pwm |
| SAI1 | | |
| LCD | | |

::: warning
Wenn deine App z. B. TIM2 nutzt, während Sub-GHz oder Infrared aktiv ist (oder umgekehrt), stürzt
`furi_hal_bus_enable()` ab, weil die Peripherieeinheit bereits aktiviert ist. Vergewissere dich, dass die
konfliktträchtige Funktion nicht läuft.
:::

## DMA-Kanäle

`DMA1` und `DMA2` sind besonders: jeder hat mehrere unabhängige Kanäle, und einige werden vom System genutzt.

| DMA | Kanal | Vom System genutzt | Zweck |
|:-:|:-:|:-:|:--|
| DMA1 | 1 | ja | digital signal |
| DMA1 | 2 | ja | digital signal |
| DMA1 | 3 | | |
| DMA1 | 4 | ja | pulse reader |
| DMA1 | 5 | | |
| DMA1 | 6 | ja | USART_Rx |
| DMA1 | 7 | ja | LPUART_Rx |
| DMA2 | 1 | ja | infrared, lfrfid, subghz |
| DMA2 | 2 | ja | infrared, lfrfid, subghz |
| DMA2 | 3 | ja | cc1101_ext |
| DMA2 | 4 | ja | cc1101_ext |
| DMA2 | 5 | ja | cc1101_ext |
| DMA2 | 6 | ja | SPI |
| DMA2 | 7 | ja | SPI |

Frei für die eigene Verwendung: **DMA1, Kanäle 3 und 5**.

## Verwandte Seiten

- [Furi-API](/de/dev/furi-api)
- [Hardware-Targets](/de/dev/hardware-targets)
- [Apps debuggen](/de/dev/debugging)
