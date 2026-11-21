---
title: API FuriHalBus
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalBus.md]
sources: [unleashed-docs]
---
# API FuriHalBus

Se la tua app accede direttamente alle periferiche dell'MCU (timer, ADC, DMA, …), deve attivarne e disattivarne i
clock tramite **FuriHalBus**. Sbagliare questa operazione fa andare il Flipper in crash volutamente, quindi leggi
questa pagina prima di scrivere codice di basso livello.

## Nozioni di base

All'avvio del sistema la maggior parte delle periferiche è mantenuta **in reset e senza clock**. Questo riduce il
consumo e garantisce che una periferica sia sempre in uno stato noto prima dell'uso. Alcune periferiche essenziali
vengono abilitate subito dal sistema; le altre devono essere abilitate esplicitamente da chi le usa.

> Qui *"sistema"* indica qualunque codice che appartenga al sistema operativo, ai driver hardware o alle app
> integrate.

| Chiamata | Cosa fa | Condizione preliminare — altrimenti **crash** |
|---|---|---|
| `furi_hal_bus_enable()` | Fornisce il clock alla periferica e la porta fuori dal reset | La periferica deve essere **disabilitata** (non la si può abilitare due volte) |
| `furi_hal_bus_disable()` | La riporta in reset e ne ferma il clock | La periferica deve essere **abilitata** |
| `furi_hal_bus_reset()` | Riporta tutti i suoi registri ai valori predefiniti senza disabilitarla | La periferica deve essere **abilitata** |

Uso tipico:

```c
#include <furi_hal_bus.h>

furi_hal_bus_enable(FuriHalBusTIM1);
// ... configure and use TIM1 ...
furi_hal_bus_disable(FuriHalBusTIM1);
```

## Categorie di periferiche

Le periferiche integrate si dividono in tre gruppi:

1. abilitate dal sistema all'avvio e mai disabilitate;
2. abilitate e disabilitate dal sistema su richiesta;
3. abilitate e disabilitate dal codice utente.

### 1. Periferiche sempre attive

Abilitate dal sistema. Il codice utente **non deve mai** disabilitarle.

| Periferica | Abilitata in |
|:-:|:-:|
| DMA1, DMA2, DMAMUX | `furi_hal_dma.c` |
| GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH | `furi_hal_resources.c` |
| PKA, AES2, HSEM, IPCC | `furi_hal_bt.c` |
| FLASH | abilitata dall'hardware |

### 2. Periferiche di sistema su richiesta

Abilitate e disabilitate dal sistema. Non usarle direttamente — usa invece la rispettiva API. Se davvero aggiri
l'API, devi abilitare tu stesso la periferica e disabilitarla quando hai finito.

| Periferica | Intestazione dell'API |
|:-:|:-:|
| RNG | `furi_hal_random.h` |
| SPI1, SPI2 | `furi_hal_spi.h` |
| I2C1, I2C3 | `furi_hal_i2c.h` |
| USART1, LPUART1 | `furi_hal_serial.h` |
| USB | `furi_hal_usb.h` |

### 3. Periferiche condivise su richiesta

Non abilitate per impostazione predefinita. Il codice utente **deve** abilitarle ogni volta che le usa. Alcune sono
usate anche dal sistema per certe funzionalità — il sistema occupa una periferica di questo tipo solo per il tempo in
cui quella funzionalità è attiva.

| Periferica | Usata dal sistema | Scopo |
|:-:|:-:|:--|
| CRC | | |
| TSC | | |
| ADC | | |
| QUADSPI | | |
| TIM1 | sì | subghz, lfrfid, nfc, infrared, ecc. |
| TIM2 | sì | subghz, infrared, ecc. |
| TIM16 | sì | speaker |
| TIM17 | sì | cc1101_ext |
| LPTIM1 | sì | timer di idle tickless |
| LPTIM2 | sì | pwm |
| SAI1 | | |
| LCD | | |

::: warning
Se la tua app usa per esempio TIM2 mentre Sub-GHz o Infrared è attivo (o viceversa), `furi_hal_bus_enable()` andrà in
crash perché la periferica è già abilitata. Assicurati che la funzionalità in conflitto non sia in esecuzione.
:::

## Canali DMA

`DMA1` e `DMA2` sono un caso particolare: ciascuno ha diversi canali indipendenti e alcuni sono usati dal sistema.

| DMA | Canale | Usato dal sistema | Scopo |
|:-:|:-:|:-:|:--|
| DMA1 | 1 | sì | digital signal |
| DMA1 | 2 | sì | digital signal |
| DMA1 | 3 | | |
| DMA1 | 4 | sì | pulse reader |
| DMA1 | 5 | | |
| DMA1 | 6 | sì | USART_Rx |
| DMA1 | 7 | sì | LPUART_Rx |
| DMA2 | 1 | sì | infrared, lfrfid, subghz |
| DMA2 | 2 | sì | infrared, lfrfid, subghz |
| DMA2 | 3 | sì | cc1101_ext |
| DMA2 | 4 | sì | cc1101_ext |
| DMA2 | 5 | sì | cc1101_ext |
| DMA2 | 6 | sì | SPI |
| DMA2 | 7 | sì | SPI |

Liberi per usi propri: **i canali 3 e 5 di DMA1**.

## Pagine correlate

- [API Furi](/it/dev/furi-api)
- [Target hardware](/it/dev/hardware-targets)
- [Debug delle app](/it/dev/debugging)
