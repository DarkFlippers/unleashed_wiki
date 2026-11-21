---
title: Application GPIO
order: 20
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli]
sources: [flipper-docs, unleashed-src]
---
# Application GPIO

L'application **GPIO** intégrée (`Main Menu → GPIO`) comporte trois entrées :

| Entrée | Ce qu'elle fait |
|---|---|
| `USB-UART Bridge` | Transforme le Flipper en adaptateur USB-série sur les broches 13/14 ou 15/16 |
| `GPIO Manual Control` | Met les broches utilisateur à l'état haut pendant que vous maintenez <kbd>OK</kbd> |
| `5V on GPIO` | `OFF` / `ON` : la sortie 5 V sur la broche 1 |

![Menu de l'application GPIO : USB-UART Bridge, GPIO Manual Control, 5V on GPIO sur OFF](/screens/gpio/menu.png)

Les numéros de broches et les tensions figurent sur la page [brochage](/fr/gpio/pinout).

## USB-UART Bridge

Utilisez-le pour dialoguer depuis un ordinateur avec la console d'un routeur, une carte ESP32/ESP8266, un module GSM ou
GPS, ou tout appareil série en 3,3 V, le Flipper servant d'adaptateur.

1. Câblez l'appareil : **TX du Flipper → RX de l'appareil**, **RX du Flipper → TX de l'appareil**, et une masse commune
   (broche 8, 11 ou 18). Par défaut, TX est la broche 13 et RX la broche 14.
2. Connectez le Flipper à l'ordinateur en USB.
3. Ouvrez `Main Menu → GPIO → USB-UART Bridge`. L'écran affiche `USB Serial`, le numéro de `COM PORT`, les broches
   TX/RX, des compteurs d'octets et le débit en bauds actuel.
4. Appuyez sur <kbd>←</kbd> (`Config`) pour le configurer (tableau ci-dessous), puis sur <kbd>BACK</kbd> pour revenir à
   l'écran d'état.
5. Ouvrez le port dans un programme de terminal (PuTTY, minicom, screen, le moniteur série d'Arduino…).
6. Pour terminer, appuyez sur <kbd>BACK</kbd> et confirmez `Exit USB-UART?` avec `Exit` (ou choisissez `Stay`).

![Écran d'état du USB-UART Bridge : USB Serial, COM PORT 0, TX broche 13, RX broche 14, compteurs d'octets, Baud 115200](/screens/gpio/usb_uart.png)

Pendant la circulation des données, la LED clignote en **bleu sur TX** et en **vert sur RX**, et le rétroéclairage
reste allumé.

### Écran Config

![Config du USB-UART Bridge : USB Channel, Baudrate, UART Pins, RTS/DTR Pins, DE/RE Pin](/screens/gpio/usb_uart_config.png)

| Réglage | Valeurs | Signification |
|---|---|---|
| `USB Channel` | `0 (CLI)`, `1` | `0 (CLI)` : le pont prend le port série USB principal, le CLI est désactivé pendant son fonctionnement. `1` : le Flipper expose deux ports série ; le CLI reste sur le premier, le pont utilise le second |
| `Baudrate` | `Host`, 1200 … 921600 | `Host` suit le débit en bauds défini par le programme de terminal sur le port. Une valeur numérique impose un débit fixe (1200, 2400, 4800, 9600, 19200, 28800, 38400, 57600, 115200, 230400, 460800, 921600) |
| `UART Pins` | `13,14`, `15,16` | USART sur les broches 13 (TX) / 14 (RX), ou LPUART sur les broches 15 (TX) / 16 (RX) |
| `RTS/DTR Pins` | `None`, `2,3`, `6,7`, `16,15` | Recopie les lignes RTS et DTR de l'hôte (première broche RTS, seconde DTR, actives à l'état bas). `16,15` n'est pas proposé quand `UART Pins` vaut `15,16` |
| `DE/RE Pin` | `None`, `4` | Pilote la broche 4 comme signal de direction (driver enable) pour un émetteur-récepteur RS-485 |

::: tip Flasher des cartes ESP
La recopie RTS/DTR est exactement ce qu'attendent les circuits d'auto-reset/boot des cartes ESP8266/ESP32 et Arduino.
Câblez les deux broches vers la logique EN/RST et BOOT/GPIO0 de la carte (à travers la paire de transistors
habituelle) et esptool pourra la mettre en bootloader sans appuyer sur aucun bouton.
:::

### S'il affiche « Connection Is Active! »

Le pont ne peut pas démarrer tant que qFlipper, l'application mobile ou une autre session RPC occupe la connexion USB.
L'écran indique `Connection Is Active! Disconnect from PC or phone to use this function.` Fermez qFlipper /
déconnectez l'application et réessayez.

## GPIO Manual Control

Un moyen rapide de vérifier un câblage, une LED ou un relais sur une broche.

1. Ouvrez `Main Menu → GPIO → GPIO Manual Control`. L'écran affiche `GPIO Output Mode Test`.
2. Choisissez la broche avec <kbd>←</kbd> / <kbd>→</kbd> : `PA7` (2), `PA6` (3), `PA4` (4), `PB3` (5), `PB2` (6),
   `PC3` (7), `PC1` (15), `PC0` (16) ou `ALL`.
3. **Maintenez** <kbd>OK</kbd> : la broche (ou toutes) passe à l'état haut, 3,3 V, et la LED verte s'allume.
   Relâchez et la broche repasse à l'état bas.

Toutes les broches listées sont des sorties push-pull tant que cet écran est ouvert ; à la sortie, elles repassent en
haute impédance (mode analogique). Ne connectez rien qui pilote lui-même ces broches pendant le test.

## 5V on GPIO

Commute la sortie 5 V sur la broche 1. Sélectionnez l'entrée et modifiez-la avec <kbd>←</kbd> / <kbd>→</kbd>. Ce
réglage n'est pas un mode de l'application : le 5 V reste actif après la fermeture de l'application GPIO, jusqu'à ce
que vous le coupiez, que vous éteigniez le Flipper ou qu'un défaut de surcharge survienne. Voir
[brochage](/fr/gpio/pinout) pour les limites de courant.

## Outils en CLI

Deux commandes apparentées sont disponibles dans le [CLI](/fr/dev/cli) du Flipper :

```text
gpio mode <pin_name> <0|1>   # 0 - input, 1 - output
gpio set <pin_name> <0|1>    # set output low/high
gpio read <pin_name>         # read input level
power 5v <0|1>               # 5 V on pin 1 off/on
i2c                          # scan the external I2C bus
```

- Les noms de broches sont les noms de ports (`PA7`, `PC0`, …). Les broches de débogage (`PA13`, `PA14`, `PB6`, `PB7`,
  `PB14`) ne sont acceptées qu'avec le mode Debug activé, et le CLI demande d'abord
  `Changing this pin mode may damage hardware...`.
- `i2c` balaie les adresses sur **PC0 (SCL, broche 16) / PC1 (SDA, broche 15)** à 100 kHz, en adressage 7 bits, et
  affiche un tableau où `#` signale un appareil qui a répondu. La plupart des cartes de dérivation I2C possèdent déjà
  des résistances de tirage ; si rien n'apparaît, vérifiez que la vôtre en a.

::: tip Unleashed
Pour aller plus loin en I2C (sniffer, lecture et écriture de registres) et pour les capteurs, voir les plugins
`i2c Tools` et `Unitemp` des packs d'applications extra, listés sur
[Modules externes](/fr/gpio/external-modules).
:::

## Dépannage

- **Caractères incohérents dans le terminal :** le débit en bauds ne correspond pas. Mettez `Baudrate` au débit de
  l'appareil, ou laissez `Host` et réglez le débit dans le programme de terminal.
- **Aucune donnée du tout :** inversez TX et RX, vérifiez que GND est bien commune, vérifiez que `UART Pins`
  correspond à votre câblage.
- **Le CLI a disparu :** `USB Channel` est sur `0 (CLI)`. Quittez le pont, ou utilisez le canal `1`.
- **5V on GPIO ne reste pas activé :** la charge consomme trop (coupure sur défaut) ou un gros condensateur sur le
  module fait déclencher le convertisseur élévateur au démarrage. Éteignez le Flipper, connectez le module, puis
  rallumez.

## Pages liées

- [Brochage GPIO](/fr/gpio/pinout)
- [Modules externes](/fr/gpio/external-modules)
- [Dev board : débogage et logs](/fr/gpio/devboard-debug)
