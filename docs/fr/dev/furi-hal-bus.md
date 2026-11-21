---
title: API FuriHalBus
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalBus.md]
sources: [unleashed-docs]
---
# API FuriHalBus

Si votre application touche directement aux périphériques du MCU (timers, ADC, DMA, …), elle doit activer et
désactiver leurs horloges via **FuriHalBus**. Se tromper fait planter le Flipper volontairement : lisez donc ceci
avant d'écrire du code bas niveau.

## Les bases

Au démarrage du système, la plupart des périphériques sont maintenus **en reset et sans horloge**. Cela économise de
l'énergie et garantit qu'un périphérique est toujours dans un état connu avant utilisation. Quelques périphériques
essentiels sont activés immédiatement par le système ; les autres doivent être activés explicitement par celui qui
les utilise.

> Ici, *« système »* désigne tout code appartenant au système d'exploitation, aux pilotes matériels ou aux
> applications intégrées.

| Appel | Ce qu'il fait | Condition préalable — sinon **plantage** |
|---|---|---|
| `furi_hal_bus_enable()` | Fournit l'horloge au périphérique et le sort du reset | Le périphérique doit être **désactivé** (impossible de l'activer deux fois) |
| `furi_hal_bus_disable()` | Le remet en reset et arrête son horloge | Le périphérique doit être **activé** |
| `furi_hal_bus_reset()` | Remet tous ses registres aux valeurs par défaut sans le désactiver | Le périphérique doit être **activé** |

Utilisation typique :

```c
#include <furi_hal_bus.h>

furi_hal_bus_enable(FuriHalBusTIM1);
// ... configure and use TIM1 ...
furi_hal_bus_disable(FuriHalBusTIM1);
```

## Catégories de périphériques

Les périphériques intégrés se répartissent en trois groupes :

1. activés par le système au démarrage et jamais désactivés ;
2. activés et désactivés par le système à la demande ;
3. activés et désactivés par le code utilisateur.

### 1. Périphériques toujours actifs

Activés par le système. Le code utilisateur ne doit **jamais** les désactiver.

| Périphérique | Activé dans |
|:-:|:-:|
| DMA1, DMA2, DMAMUX | `furi_hal_dma.c` |
| GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH | `furi_hal_resources.c` |
| PKA, AES2, HSEM, IPCC | `furi_hal_bt.c` |
| FLASH | activé par le matériel |

### 2. Périphériques système à la demande

Activés et désactivés par le système. Ne les utilisez pas directement — passez par l'API correspondante. Si vous
contournez vraiment l'API, vous devez activer le périphérique vous-même et le désactiver quand vous avez terminé.

| Périphérique | En-tête de l'API |
|:-:|:-:|
| RNG | `furi_hal_random.h` |
| SPI1, SPI2 | `furi_hal_spi.h` |
| I2C1, I2C3 | `furi_hal_i2c.h` |
| USART1, LPUART1 | `furi_hal_serial.h` |
| USB | `furi_hal_usb.h` |

### 3. Périphériques partagés à la demande

Non activés par défaut. Le code utilisateur **doit** les activer chaque fois qu'il les utilise. Certains sont aussi
utilisés par le système pour certaines fonctionnalités — le système ne prend un tel périphérique que pendant que cette
fonctionnalité est active.

| Périphérique | Utilisé par le système | Rôle |
|:-:|:-:|:--|
| CRC | | |
| TSC | | |
| ADC | | |
| QUADSPI | | |
| TIM1 | oui | subghz, lfrfid, nfc, infrared, etc. |
| TIM2 | oui | subghz, infrared, etc. |
| TIM16 | oui | speaker |
| TIM17 | oui | cc1101_ext |
| LPTIM1 | oui | timer d'inactivité tickless |
| LPTIM2 | oui | pwm |
| SAI1 | | |
| LCD | | |

::: warning
Si votre application utilise par exemple TIM2 alors que Sub-GHz ou Infrared est actif (ou inversement),
`furi_hal_bus_enable()` plantera car le périphérique est déjà activé. Assurez-vous que la fonctionnalité en conflit
n'est pas en cours d'exécution.
:::

## Canaux DMA

`DMA1` et `DMA2` sont particuliers : chacun possède plusieurs canaux indépendants, et certains sont utilisés par le
système.

| DMA | Canal | Utilisé par le système | Rôle |
|:-:|:-:|:-:|:--|
| DMA1 | 1 | oui | signal numérique |
| DMA1 | 2 | oui | signal numérique |
| DMA1 | 3 | | |
| DMA1 | 4 | oui | pulse reader |
| DMA1 | 5 | | |
| DMA1 | 6 | oui | USART_Rx |
| DMA1 | 7 | oui | LPUART_Rx |
| DMA2 | 1 | oui | infrared, lfrfid, subghz |
| DMA2 | 2 | oui | infrared, lfrfid, subghz |
| DMA2 | 3 | oui | cc1101_ext |
| DMA2 | 4 | oui | cc1101_ext |
| DMA2 | 5 | oui | cc1101_ext |
| DMA2 | 6 | oui | SPI |
| DMA2 | 7 | oui | SPI |

Libres pour votre propre usage : **les canaux 3 et 5 de DMA1**.

## Pages liées

- [API Furi](/fr/dev/furi-api)
- [Cibles matérielles](/fr/dev/hardware-targets)
- [Déboguer les applications](/fr/dev/debugging)
