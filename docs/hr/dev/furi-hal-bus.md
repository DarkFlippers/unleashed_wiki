---
title: FuriHalBus API
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalBus.md]
sources: [unleashed-docs]
---
# FuriHalBus API

Ako vaša aplikacija izravno pristupa periferijama mikrokontrolera (tajmeri, ADC, DMA, …), mora uključivati i isključivati njihov takt putem **FuriHalBus**. Pogrešna upotreba namjerno ruši Flipper, stoga pročitajte ovo prije pisanja koda niske razine.

## Osnove

Pri pokretanju sustava većina je periferija **u stanju resetiranja i bez takta**. Time se štedi energija i jamči da je periferija uvijek u poznatom stanju prije upotrebe. Neke ključne periferije sustav uključuje odmah; ostale mora izričito uključiti onaj tko ih koristi.

> Ovdje *"sustav"* označava sav kôd koji pripada operacijskom sustavu, upravljačkim programima hardvera ili ugrađenim aplikacijama.

| Poziv | Što radi | Preduvjet — inače **rušenje** |
|---|---|---|
| `furi_hal_bus_enable()` | Dovodi takt periferiji i izvodi je iz resetiranja | Periferija mora biti **onemogućena** (ne možete je uključiti dvaput) |
| `furi_hal_bus_disable()` | Vraća je u resetiranje i zaustavlja takt | Periferija mora biti **omogućena** |
| `furi_hal_bus_reset()` | Vraća sve njezine registre na zadane vrijednosti bez isključivanja | Periferija mora biti **omogućena** |

Uobičajena upotreba:

```c
#include <furi_hal_bus.h>

furi_hal_bus_enable(FuriHalBusTIM1);
// ... konfiguriranje i upotreba TIM1 ...
furi_hal_bus_disable(FuriHalBusTIM1);
```

## Kategorije periferija

Ugrađene periferije dijele se u tri skupine:

1. uključene od strane sustava pri pokretanju i nikad se ne isključuju;
2. sustav ih uključuje i isključuje prema potrebi;
3. uključuje i isključuje ih korisnički kôd.

### 1. Uvijek uključene periferije

Uključene od strane sustava. Korisnički kôd ih **nikada** ne smije isključiti.

| Periferija | Uključena u |
|:-:|:-:|
| DMA1, DMA2, DMAMUX | `furi_hal_dma.c` |
| GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH | `furi_hal_resources.c` |
| PKA, AES2, HSEM, IPCC | `furi_hal_bt.c` |
| FLASH | uključeno hardverom |

### 2. Sustavne periferije na zahtjev

Sustav ih uključuje i isključuje. Ne koristite ih izravno — umjesto toga upotrijebite odgovarajući API. Ako doista zaobilazite API, morate sami uključiti periferiju i isključiti je kada završite.

| Periferija | Zaglavlje API-ja |
|:-:|:-:|
| RNG | `furi_hal_random.h` |
| SPI1, SPI2 | `furi_hal_spi.h` |
| I2C1, I2C3 | `furi_hal_i2c.h` |
| USART1, LPUART1 | `furi_hal_serial.h` |
| USB | `furi_hal_usb.h` |

### 3. Dijeljene periferije na zahtjev

Nisu uključene prema zadanim postavkama. Korisnički kôd **mora** ih uključiti svaki put kad ih koristi. Neke koristi i sustav za određene funkcije — sustav zauzima takvu periferiju samo dok je ta funkcija aktivna.

| Periferija | Koristi sustav | Svrha |
|:-:|:-:|:--|
| CRC | | |
| TSC | | |
| ADC | | |
| QUADSPI | | |
| TIM1 | da | subghz, lfrfid, nfc, infrared itd. |
| TIM2 | da | subghz, infrared itd. |
| TIM16 | da | zvučnik |
| TIM17 | da | cc1101_ext |
| LPTIM1 | da | tickless idle timer |
| LPTIM2 | da | pwm |
| SAI1 | | |
| LCD | | |

::: warning
Ako vaša aplikacija koristi npr. TIM2 dok je aktivan Sub-GHz ili Infrared (ili obrnuto), `furi_hal_bus_enable()` će srušiti sustav jer je periferija već uključena. Provjerite da suprotstavljena funkcija nije pokrenuta.
:::

## DMA kanali

`DMA1` i `DMA2` su posebni: svaki ima nekoliko neovisnih kanala, a neke koristi sustav.

| DMA | Kanal | Koristi sustav | Svrha |
|:-:|:-:|:-:|:--|
| DMA1 | 1 | da | digitalni signal |
| DMA1 | 2 | da | digitalni signal |
| DMA1 | 3 | | |
| DMA1 | 4 | da | čitač impulsa |
| DMA1 | 5 | | |
| DMA1 | 6 | da | USART_Rx |
| DMA1 | 7 | da | LPUART_Rx |
| DMA2 | 1 | da | infrared, lfrfid, subghz |
| DMA2 | 2 | da | infrared, lfrfid, subghz |
| DMA2 | 3 | da | cc1101_ext |
| DMA2 | 4 | da | cc1101_ext |
| DMA2 | 5 | da | cc1101_ext |
| DMA2 | 6 | da | SPI |
| DMA2 | 7 | da | SPI |

Slobodni za vašu upotrebu: **DMA1 kanali 3 i 5**.

## Povezane stranice

- [Furi API](/hr/dev/furi-api)
- [Hardverske mete](/hr/dev/hardware-targets)
- [Otklanjanje pogrešaka u aplikacijama](/hr/dev/debugging)
