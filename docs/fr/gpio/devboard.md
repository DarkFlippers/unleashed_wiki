---
title: "Dev board : prise en main"
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/USB%20connection%20to%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Wi-Fi%20connection%20to%20the%20Devboard.md, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3]
sources: [unleashed-docs, flipper-docs]
---
# Wi-Fi Devboard : prise en main

La **Wi-Fi Developer Board** officielle est un module ESP32-S2 (ESP32-S2-WROVER-N4R2) destiné au connecteur GPIO. À la
sortie de la boîte, elle exécute le firmware **Black Magic Probe** et se comporte comme une **sonde de débogage** :
elle relie le débogueur de votre ordinateur au STM32 du Flipper en SWD, par USB ou par Wi-Fi. Elle peut aussi
retransmettre les logs UART du Flipper.

![Wi-Fi Developer Board](/img/remote/7a7349f75be87abb.jpg)

::: tip Elle n'est pas nécessaire pour flasher un firmware
La mise à jour, la compilation et l'envoi de votre propre firmware fonctionnent tous en USB simple. La dev board n'est
nécessaire que pour le débogage en direct (GDB, points d'arrêt) et pour lire les logs indépendamment du système du
Flipper. Pour utiliser la même carte comme outil Wi-Fi (Marauder), voir [ESP32 et Wi-Fi](/fr/gpio/esp32).
:::

## Étape 1. Activer le mode Debug sur le Flipper

1. Ouvrez `Main Menu → Settings → System`.
2. Mettez `Debug` sur `ON`.

Le mode Debug est nécessaire pour déboguer des applications et déverrouille des options de débogage dans les
applications et dans le [CLI](/fr/dev/cli). Réactivez-le après chaque mise à jour du firmware.

## Étape 2. Mettre à jour le firmware de la carte

La carte est livrée avec un firmware ancien. Mettez-le d'abord à jour :
[Dev board : mise à jour du firmware](/fr/gpio/devboard-firmware).

## Étape 3. Brancher la dev board sur le Flipper

1. **Éteignez d'abord le Flipper.** La carte et la carte microSD partagent le rail 3,3 V du Flipper ; brancher à chaud
   une forte charge capacitive peut corrompre la carte mémoire.
2. **Enfoncez-la à fond.** Sans coque : aucun jeu entre le Flipper et la carte (il faut parfois forcer un peu). Avec
   une coque en silicone : aucun jeu au milieu entre la coque et la carte.
3. Maintenez <kbd>BACK</kbd> pour allumer le Flipper.

![Dev board insérée, Flipper sans coque](/img/remote/4eb1e40120ff42bb.jpg)

## Étape 4. Se connecter à un ordinateur

### En USB

Utilisez l'USB pour déboguer en mode **Black Magic** ou **DAPLink** et pour lire les logs.

1. Listez les périphériques série sur l'ordinateur :
   - **macOS :** `ls /dev/cu.*`
   - **Linux :** `ls /dev/tty*`
   - **Windows :** Gestionnaire de périphériques → **Ports (COM et LPT)**
2. Connectez le port USB-C de la **dev board** à l'ordinateur.
3. Listez de nouveau les périphériques : **deux nouveaux ports** apparaissent, tous deux appartiennent à la dev board.

Si rien n'apparaît, essayez un autre câble (il doit transporter des données), un autre port USB ou un autre
ordinateur.

### En Wi-Fi : mode point d'accès (par défaut)

La carte crée son propre réseau. Votre ordinateur perd sa connexion Wi-Fi habituelle tant qu'il y est connecté.

1. Sur votre ordinateur ou votre téléphone, connectez-vous au réseau Wi-Fi :
   - Nom : `blackmagic`
   - Mot de passe : `iamwitcher`
2. Ouvrez <http://192.168.4.1> ou <http://blackmagic.local> pour accéder à l'interface web de la carte.

Si le réseau `blackmagic` n'apparaît pas :

- réinitialisez la connexion Wi-Fi sur l'ordinateur ;
- la carte est peut-être configurée en mode client (STA). Maintenez le bouton **BOOT** de la carte pendant
  **10 secondes** pour réinitialiser ses réglages ; après son redémarrage, elle redevient point d'accès.

### En Wi-Fi : mode client (STA)

La carte rejoint votre réseau 2,4 GHz existant, ce qui vous permet de conserver l'accès à Internet.

1. Connectez-vous à la carte en mode point d'accès (ci-dessus) et ouvrez <http://192.168.4.1>.
2. Sélectionnez le mode **STA**, saisissez le **SSID** et le **mot de passe** de votre réseau. Le bouton **+** liste
   les réseaux 2,4 GHz voisins (le 5 GHz n'est pas pris en charge).
3. Enregistrez et redémarrez la carte.
4. Désormais, ouvrez <http://blackmagic.local> depuis votre réseau habituel.

En Wi-Fi, seul le débogage **Black Magic** est disponible.

## Matériel

- MCU : ESP32-S2-WROVER-N4R2.
- SWD vers le Flipper sur la **broche 10 (SWCLK)** et la **broche 12 (SWDIO)** ; logs UART sur les broches USART 13/14
  du Flipper.
- Schémas (PCB, ESP32-S2, alimentation, connecteurs) et plan d'assemblage :
  [schémas de la Wi-Fi Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-schematics).

## Étapes suivantes

- [Dev board : débogage et logs](/fr/gpio/devboard-debug)
- [Dev board : mise à jour du firmware](/fr/gpio/devboard-firmware)
- Communauté : [Discord](https://discord.com/invite/flipper) (canal #wifi-devboard), [Reddit](https://www.reddit.com/r/flipperzero/)
