---
title: API FuriHalBus
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalBus.md]
sources: [unleashed-docs]
---
# API FuriHalBus

Si tu app toca directamente los periféricos del MCU (temporizadores, ADC, DMA, …), debe activar y desactivar sus
relojes a través de **FuriHalBus**. Hacerlo mal provoca un fallo intencionado del Flipper, así que lee esto antes de
escribir código de bajo nivel.

## Conceptos básicos

Al arrancar el sistema, la mayoría de los periféricos se mantienen **en reset y sin reloj**. Esto ahorra energía y
garantiza que un periférico esté siempre en un estado conocido antes de usarlo. Algunos periféricos esenciales los
activa el sistema de inmediato; los demás debe activarlos explícitamente quien los use.

> Aquí, *«sistema»* significa cualquier código que pertenezca al sistema operativo, a los controladores de hardware o
> a las apps integradas.

| Llamada | Qué hace | Condición previa — en caso contrario, **fallo** |
|---|---|---|
| `furi_hal_bus_enable()` | Da reloj al periférico y lo saca del reset | El periférico debe estar **desactivado** (no se puede activar dos veces) |
| `furi_hal_bus_disable()` | Lo vuelve a poner en reset y detiene su reloj | El periférico debe estar **activado** |
| `furi_hal_bus_reset()` | Devuelve todos sus registros a los valores por defecto sin desactivarlo | El periférico debe estar **activado** |

Uso típico:

```c
#include <furi_hal_bus.h>

furi_hal_bus_enable(FuriHalBusTIM1);
// ... configure and use TIM1 ...
furi_hal_bus_disable(FuriHalBusTIM1);
```

## Categorías de periféricos

Los periféricos integrados se dividen en tres grupos:

1. los que el sistema activa al arrancar y nunca desactiva;
2. los que el sistema activa y desactiva según la demanda;
3. los que activa y desactiva el código de usuario.

### 1. Periféricos siempre activos

Los activa el sistema. El código de usuario **nunca** debe desactivarlos.

| Periférico | Se activa en |
|:-:|:-:|
| DMA1, DMA2, DMAMUX | `furi_hal_dma.c` |
| GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH | `furi_hal_resources.c` |
| PKA, AES2, HSEM, IPCC | `furi_hal_bt.c` |
| FLASH | lo activa el hardware |

### 2. Periféricos del sistema bajo demanda

Los activa y desactiva el sistema. No los uses directamente — usa la API correspondiente. Si de verdad te saltas la
API, debes activar el periférico tú mismo y desactivarlo al terminar.

| Periférico | Cabecera de la API |
|:-:|:-:|
| RNG | `furi_hal_random.h` |
| SPI1, SPI2 | `furi_hal_spi.h` |
| I2C1, I2C3 | `furi_hal_i2c.h` |
| USART1, LPUART1 | `furi_hal_serial.h` |
| USB | `furi_hal_usb.h` |

### 3. Periféricos compartidos bajo demanda

No están activados por defecto. El código de usuario **debe** activarlos cada vez que los use. Algunos los usa también
el sistema para determinadas funciones — el sistema toma ese periférico solo mientras la función esté activa.

| Periférico | Lo usa el sistema | Finalidad |
|:-:|:-:|:--|
| CRC | | |
| TSC | | |
| ADC | | |
| QUADSPI | | |
| TIM1 | sí | subghz, lfrfid, nfc, infrared, etc. |
| TIM2 | sí | subghz, infrared, etc. |
| TIM16 | sí | speaker |
| TIM17 | sí | cc1101_ext |
| LPTIM1 | sí | temporizador de inactividad sin tick |
| LPTIM2 | sí | pwm |
| SAI1 | | |
| LCD | | |

::: warning
Si tu app usa, por ejemplo, TIM2 mientras Sub-GHz o Infrared están activos (o al contrario),
`furi_hal_bus_enable()` provocará un fallo porque el periférico ya está activado. Asegúrate de que la función
conflictiva no esté en marcha.
:::

## Canales de DMA

`DMA1` y `DMA2` son especiales: cada uno tiene varios canales independientes y algunos los usa el sistema.

| DMA | Canal | Lo usa el sistema | Finalidad |
|:-:|:-:|:-:|:--|
| DMA1 | 1 | sí | señal digital |
| DMA1 | 2 | sí | señal digital |
| DMA1 | 3 | | |
| DMA1 | 4 | sí | lector de pulsos |
| DMA1 | 5 | | |
| DMA1 | 6 | sí | USART_Rx |
| DMA1 | 7 | sí | LPUART_Rx |
| DMA2 | 1 | sí | infrared, lfrfid, subghz |
| DMA2 | 2 | sí | infrared, lfrfid, subghz |
| DMA2 | 3 | sí | cc1101_ext |
| DMA2 | 4 | sí | cc1101_ext |
| DMA2 | 5 | sí | cc1101_ext |
| DMA2 | 6 | sí | SPI |
| DMA2 | 7 | sí | SPI |

Libres para tu propio uso: **los canales 3 y 5 de DMA1**.

## Páginas relacionadas

- [API Furi](/es/dev/furi-api)
- [Objetivos de hardware](/es/dev/hardware-targets)
- [Depurar apps](/es/dev/debugging)
