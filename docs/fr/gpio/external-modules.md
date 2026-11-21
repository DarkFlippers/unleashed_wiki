---
title: Modules externes
order: 30
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SIM800.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# Modules externes

La plupart des cartes additionnelles pour le Flipper Zero se branchent directement sur le connecteur GPIO et
dialoguent avec lui via l'un des trois bus suivants : **SPI** (broches 2 à 5), **UART** (broches 13/14 ou 15/16) ou
**I2C** (broches 15/16). Cette page sert de carte : quels types de modules existent, quel firmware ou quelle
application les pilote, et quelles broches ils occupent, afin de savoir lesquels peuvent être utilisés ensemble.

## Types de modules

| Module | Bus / broches | Piloté par | Page |
|---|---|---|---|
| CC1101 externe (Sub-GHz) | SPI 2–5, GDO0 sur 6, commande d'ampli sur 7 | Application Sub-GHz intégrée (`Radio Settings → Module → External`) | [CC1101 externe](/fr/subghz/external-cc1101) |
| NRF24L01 (2,4 GHz) | SPI 2–5, CE sur 6 | Plugins NRF24 Sniffer / Mouse Jacker | [NRF24](/fr/gpio/nrf24) |
| Cartes Wi-Fi ESP32 / ESP8266, Wi-Fi Devboard | UART 13/14 (SWD 10/12 pour le débogage) | Plugins Marauder, Wi-Fi Scanner, Deauther ; firmware Black Magic | [ESP32](/fr/gpio/esp32), [Devboard](/fr/gpio/devboard) |
| GSM SIM800C / SIM800L | UART 13/14 ou 15/16, alimentation depuis la broche 1 | Application SIM800 intégrée | [SIM800](/fr/gpio/sim800) |
| GPS (NMEA) | UART | Plugin `[NMEA] GPS` | [GPS](/fr/gpio/gps) |
| Video Game Module | UART 13/14, broches 2–7, alimentation | Firmware du Flipper + firmware du module | [Video Game Module](/fr/gpio/video-game-module) |
| Modules d'extension (protocole) | UART 13/14 ou 15/16 | `Settings → Expansion Modules` | [Modules d'extension](/fr/gpio/expansion-modules) |
| LED IR externe / amplificateur IR | Broche 2 (PA7), 5 V sur la broche 1 | Application Infrared intégrée (`GPIO Settings`) | voir ci-dessous |
| Capteurs de température / humidité / pression | dépend du capteur (voir le README) | Plugin `Unitemp` | [README d'Unitemp](https://github.com/quen0n/unitemp-flipperzero#readme) |
| N'importe quel périphérique I2C | I2C 15/16 | Plugin `i2c Tools`, commande CLI `i2c` | [Application GPIO](/fr/gpio/gpio-app) |
| ESP32-CAM | UART | Plugin Camera Suite | [Camera Suite](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |
| Coffres-forts Sentry Safe / Master Lock (deux fils) | Broche 15 (C1) + GND 8 | Plugin SentrySafe | [SentrySafe](/fr/apps/sentry-safe) |

::: tip Unleashed
Unleashed prend en charge directement dans le firmware :
- le **CC1101 externe** via le SPI matériel, avec commande de l'amplificateur et des LED externes (`Ext Amp & LEDs`,
  activée par défaut) dans `Sub-GHz → Radio Settings` ;
- les **modules IR externes** dans `Infrared → GPIO Settings` (détection automatique, comme sur le firmware
  d'origine) ;
- l'application GSM **SIM800** (`Apps → GPIO → SIM800`).

Les modules radio externes fonctionnent sur tous les firmwares, pas seulement sur Unleashed. La première
implémentation du CC1101 est celle de @quen0n pour Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307)) ; celle utilisée aujourd'hui a été
écrite par **Skorp** dans le firmware officiel, et c'est celle-là qu'Unleashed reprend.

Les plugins pour le reste (NRF24, Marauder, GPS, Unitemp, i2c Tools, Camera Suite…) se trouvent dans les packs Base et
Extra : [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest). Voir
[Applications sur carte SD](/fr/apps/sd-card-apps).
:::

## Conflits de broches

Les modules qui partagent un bus ne peuvent pas fonctionner en même temps sans précautions. Les conflits courants :

| Broches | Occupées par |
|---|---|
| 2, 3, 4, 5 | SPI : CC1101 externe, NRF24 (MOSI, MISO, CS, SCK) |
| 6 | CC1101 GDO0 / NRF24 CE |
| 7 | Commande de l'amplificateur du CC1101 (modules E07) |
| 13, 14 | USART : cartes Wi-Fi, SIM800, modules d'extension, Video Game Module, pont USB-UART, sortie des logs |
| 15, 16 | LPUART ou I2C (jamais les deux à la fois) |
| 10, 12 | Débogage SWD (Devboard) |

Si vous utilisez une carte « combo » qui embarque plusieurs radios (par exemple CC1101 + NRF24 + ESP32 sur un même
PCB), suivez la documentation propre à cette carte pour savoir quelles broches et quels réglages de plugin chaque
radio utilise.

## Modules IR externes

1. Reliez l'entrée du driver de LED IR à la **broche 2 (A7)**, le GND au GND, et l'alimentation à la broche 1 (5 V) si
   le module en a besoin.
2. Ouvrez `Main Menu → Infrared → GPIO Settings`.
3. Réglez `Signal Output` :
   - `Flipper` — la LED IR intégrée ;
   - `2 (A7)` — le module externe sur la broche 2 ;
   - `Detect` — le firmware détecte automatiquement un module connecté.
4. Avec `2 (A7)` sélectionné, vous pouvez aussi basculer `5V on GPIO` depuis cet écran. Avec `Detect`, l'entrée 5 V
   affiche `Auto`.

Pour l'utilisation des télécommandes, voyez la section [Infrarouge](/fr/infrared/).

## Règles générales

1. **Éteignez l'appareil avant de brancher.** Le branchement à chaud de grosses capacités peut corrompre la carte SD.
2. **Logique 3,3 V.** Ne raccordez pas les sorties du Flipper à de la logique 5 V ; les entrées ne tolèrent le 5 V que
   lorsqu'elles sont configurées en entrée.
3. **Respectez les limites de courant :** 1,2 A sur la broche 1 et sur la broche 9, 20 mA par broche d'E/S. Voir le
   [brochage](/fr/gpio/pinout).
4. **Croisez TX et RX** sur les modules UART : le TX du Flipper va sur le RX du module.
5. **Enfoncez le module à fond.** Un module à moitié inséré provoque des contacts intermittents.

## Pages liées

- [Brochage GPIO](/fr/gpio/pinout)
- [Application GPIO](/fr/gpio/gpio-app)
- [Modules d'extension](/fr/gpio/expansion-modules)
- [Les modules et leurs apps](/fr/gpio/module-apps)
