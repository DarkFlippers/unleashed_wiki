---
title: GPIO et modules
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# GPIO et modules

Le connecteur à 18 broches sur le dessus du Flipper Zero en fait un outil matériel : il peut alimenter des modules
externes et dialoguer avec eux, servir d'adaptateur USB-UART, piloter des broches à la main pour faire des tests, et
jouer le rôle de cible pour un débogueur matériel.

![Connecteur GPIO du Flipper Zero](/img/remote/f9f4fe12522d6f9d.png)

## Les bases

| Page | Contenu |
|---|---|
| [Brochage GPIO](/fr/gpio/pinout) | Les 18 broches, tensions, limites de courant, 5 V sur la broche 1, tolérance 3,3 V / 5 V |
| [Application GPIO](/fr/gpio/gpio-app) | `Main Menu → GPIO` : USB-UART Bridge, GPIO Manual Control, 5V on GPIO ; commandes CLI `gpio` et `i2c` |
| [Modules externes](/fr/gpio/external-modules) | Panorama des types de modules et des broches utilisées par chacun |
| [Modules d'extension](/fr/gpio/expansion-modules) | `Settings → Expansion Modules` et le protocole Expansion Module |
| [Les modules et leurs apps](/fr/gpio/module-apps) | Tous les modules pris en charge par les packs d'apps, et ce que fait chaque app |

## Modules

| Page | Module |
|---|---|
| [CC1101 externe](/fr/subghz/external-cc1101) | Radio Sub-GHz avec un étage d'entrée plus performant (traité dans la section Sub-GHz) |
| [ESP32 / Wi-Fi](/fr/gpio/esp32) | Wi-Fi Devboard, ESP32 Marauder, le flasher web Unleashed et la carte de wardriving |
| [NRF24](/fr/gpio/nrf24) | Sniffer nRF24L01 2,4 GHz et MouseJack |
| [SIM800](/fr/gpio/sim800) | Module GSM : appels, SMS, répertoire, USSD (application Unleashed intégrée) |
| [GPS](/fr/gpio/gps) | Position depuis le téléphone compagnon (service GPS) et modules GPS NMEA sur l'UART |
| [Video Game Module](/fr/gpio/video-game-module) | Module RP2040 avec sortie vidéo et capteur de mouvement |

## Wi-Fi Developer Board

| Page | Contenu |
|---|---|
| [Dev board : prise en main](/fr/gpio/devboard) | Préparer le Flipper, brancher la carte, connexion USB et Wi-Fi |
| [Dev board : débogage et logs](/fr/gpio/devboard-debug) | Black Magic / DAPLink, débogage dans VS Code, lecture des logs UART |
| [Dev board : mise à jour du firmware](/fr/gpio/devboard-firmware) | Flasher le firmware propre à la carte avec uFBT |

::: tip Unleashed
Unleashed fournit des outils GPIO supplémentaires dès l'installation : l'application [SIM800](/fr/gpio/sim800)
(`Apps → GPIO → SIM800`), la prise en charge du CC1101 externe avec contrôle de l'amplificateur dans Sub-GHz, la sortie
vers un module IR externe dans `Infrared → GPIO Settings`, et un large éventail de plugins GPIO dans les packs
d'applications extra. Voir [Modules externes](/fr/gpio/external-modules).
:::

::: warning Avant de brancher quoi que ce soit
Éteignez le Flipper avant de connecter un module, et enfoncez le module à fond dans le connecteur. Brancher à chaud un
module présentant une forte charge capacitive peut corrompre la carte microSD, car la carte et la broche 9 partagent
le même rail 3,3 V.
:::
