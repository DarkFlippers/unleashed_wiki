---
title: Matériel
order: 140
original: [https://docs.flipper.net/zero/development/hardware, https://docs.flipper.net/zero/development/hardware/tech-specs, https://docs.flipper.net/zero/development/hardware/schematic, https://docs.flipper.net/zero/development/hardware/flipper-blueprints, https://docs.flipper.net/zero/development/hardware/modules-blueprints, https://docs.flipper.net/zero/development/hardware/vgm-blueprints, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Matériel

Les caractéristiques techniques du Flipper Zero, ainsi que l'endroit où trouver ses schémas, plans et modèles 3D —
utile pour construire des modules externes, des coques, et pour le débogage bas niveau.

![Aperçu des caractéristiques techniques du Flipper Zero](/img/remote/629725f9f16a5946.png)

## Caractéristiques techniques

### Boîtier, dimensions et poids

| | |
|---|---|
| Matériaux | PC, ABS, PMMA |
| Hauteur | 40,1 mm (1,58 po) |
| Largeur | 100,3 mm (3,95 po) |
| Épaisseur | 25,6 mm (1,01 po) |
| Poids | 102 g (3,6 oz) |

### Écran

| | |
|---|---|
| Type | LCD monochrome |
| Résolution | 128×64 pixels |
| Contrôleur | ST7567 |
| Interface | SPI |
| Diagonale | 1,4″ |

### Microcontrôleur

| | |
|---|---|
| Modèle | [STM32WB55RG](https://www.st.com/en/microcontrollers-microprocessors/stm32wb55rg.html) |
| Cœur applicatif | Arm Cortex-M4, 32 bits, 64 MHz |
| Cœur radio | Arm Cortex-M0+, 32 bits, 32 MHz |
| Radio | Bluetooth LE 5.4, 802.15.4, propriétaire |
| Flash | 1024 Ko (partagée entre l'application et la radio) |
| SRAM | 256 Ko (partagée entre l'application et la radio) |

### Sub-1 GHz

| | |
|---|---|
| Émetteur-récepteur | [CC1101](https://www.ti.com/product/CC1101) |
| Puissance d'émission | −20 dBm maximum (selon les spécifications officielles) |
| Bandes de fréquences | 315 MHz, 433 MHz, 868 MHz, 915 MHz (selon la région) |

Le CC1101 se règle dans les plages 299,999755–348 MHz, 386,999938–464 MHz et 778,999847–928 MHz.

::: tip Unleashed
Unleashed supprime les restrictions régionales d'émission et ajoute des fréquences supplémentaires (350 MHz et
467 MHz sont ajoutées à la plage par défaut). La plage peut être étendue davantage à 281–361, 378–481 et
749–962 MHz via le fichier `subghz/assets/dangerous_settings` — cela sort des spécifications du CC1101 et
**peut endommager le matériel** ([réglages dangereux](/fr/start/dangerous-settings)). Un
[module CC1101 externe](/fr/subghz/external-cc1101) est également pris en charge. Respectez la réglementation radio de
votre pays.
:::

### NFC

| | |
|---|---|
| Émetteur-récepteur | [ST25R3916](https://www.st.com/en/nfc/st25r3916.html) |
| Fréquence | 13,56 MHz |
| Cartes | ISO-14443A/B ; NXP MIFARE Classic®, Ultralight®, DESFire®, etc. ; FeliCa™ ; HID iClass (Picopass) ; protocoles du NFC Forum |

### RFID 125 kHz

| | |
|---|---|
| Fréquence | 125 kHz |
| Modulation | AM, OOK |
| Codage | ASK, PSK |
| Cartes (liste officielle) | EM-Micro EM4100, HID H10301, IDTECK Idteck, Motorola Indala 26, Kantech IoProx XSF, AWID, FECAVA FDX-A, ISO FDX-B, Generic HID Prox, Generic HID Ext, Farpointe Pyramid, Viking, Jablotron, Paradox, PAC Stanley, Keri, Gallagher, Honeywell Nexwatch, Electra, Securakey |

Voir [RFID → Lecture](/fr/rfid/read) pour les protocoles réellement pris en charge par le firmware Unleashed.

### Infrarouge

| | |
|---|---|
| Longueur d'onde RX | 950 nm (±100 nm) |
| Porteuse RX | 38 kHz (±5 %) |
| Longueur d'onde TX | 940 nm |
| Porteuse TX | 0–2 MHz |
| Puissance d'émission | 300 mW |
| Protocoles | famille NEC, Kaseikyo, RCA, RC5, RC6, Samsung, SIRC |

### iButton (1-Wire)

Dallas DS199x, DS1971, CYFRAL, Metakom, TM2004, RW1990.

### GPIO

- 13 broches d'entrée/sortie disponibles sur des connecteurs externes au pas de 2,54 mm
- Niveaux CMOS 3,3 V
- Entrées tolérantes au 5 V (voir la note ST [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf))
- Jusqu'à 20 mA par broche numérique

Carte des broches : [Brochage GPIO](/fr/gpio/pinout).

### Batterie et alimentation

| | |
|---|---|
| Type | Lithium polymère (LiPo) |
| Capacité | 2100 mAh |
| Autonomie | Jusqu'à 28 jours |
| Température de fonctionnement | 0…40 °C (32…104 °F) |

### Carte microSD

| | |
|---|---|
| Capacité maximale | Jusqu'à 256 Go |
| Capacité recommandée | 2–32 Go |
| Interface | SPI |
| Vitesse de lecture/écriture | Jusqu'à 5 Mbit/s |

Le Flipper n'est pas livré avec une carte microSD — achetez-en une séparément. Voir
[Carte microSD](/fr/start/sd-card).

### USB

| | |
|---|---|
| Connecteur | Type-C |
| Norme | USB 2.0 |
| Débit de données | 12 Mbit/s |
| Courant de charge maximal | 1 A |

### Bluetooth LE 5.4

| | |
|---|---|
| Puissance d'émission | 4 dBm maximum |
| Sensibilité en réception | −96 dBm |
| Débit de données | 2 Mbit/s |

### Buzzer et vibration

| | |
|---|---|
| Fréquence du buzzer | 100–2500 Hz |
| Niveau sonore du buzzer | 87 dB |
| Type de buzzer | Pastille |
| Force de vibration | 30 N |
| Vitesse du moteur de vibration | 13500 tr/min |

### Contenu de la boîte

Flipper Zero, câble USB-C vers USB-A, documentation, autocollant.

## Schémas

Les schémas de tous les circuits imprimés du Flipper Zero sont publiés par Flipper Devices « à des fins
éducatives » — utiles pour le développement de modules matériels et le débogage bas niveau. Les visionneuses Altium
interactives et les téléchargements PDF se trouvent sur la page officielle :
**[Schematics of Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)**.

![Circuits imprimés du Flipper Zero](/img/remote/db285947a71be613.png)

| Circuit imprimé | Documents disponibles |
|---|---|
| **Carte principale** (rév. 12.1.F7B9C6) | Plan d'assemblage ; vue d'ensemble des blocs principaux ; alimentation ; périphériques ; MCU STM32WB55 ; écran LCD ; Sub-1 GHz CC1101 ; boutons |
| **Carte iButton** (rév. 12.F7B9C6) — porte aussi le haut-parleur piézo et l'IR | Plan d'assemblage ; schéma iButton |
| **Carte NFC RFID** (rév. 12.F7B9C6) — RFID 125 kHz et NFC | Plan d'assemblage ; vue d'ensemble des blocs NFC ; NFC ; alimentation et vibreur ; RFID |
| **Carte d'antenne** | Image de la carte |

::: info
Dans la révision 13.F7B9C6 de la carte iButton, les empreintes des pogo pins ont changé : des pogo pins traversants
ont remplacé les modèles CMS. Les diamètres des empreintes sont les mêmes que dans la 12.F7B9C6.
:::

## Plans et modèles 3D

Tous les fichiers sont téléchargeables depuis les pages officielles :

| Objet | Fichiers | Page |
|---|---|---|
| Boîtier du Flipper Zero | Plan 2D (`.pdf`, `.dwg`), modèle 3D (`.stl`) | [Blueprints of Flipper Zero](https://docs.flipper.net/zero/development/hardware/flipper-blueprints) |
| Module externe standard | Plan (`.pdf`), modèle 3D du PCB (`.stp`, nu et assemblé), contour du PCB (`.dwg`, `.dxf`) | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Petit module externe | Même ensemble que le module standard | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Video Game Module | Plan (`.pdf`, `.dwg.zip`), modèle 3D (`.stp`) | [Blueprints of Video Game Module](https://docs.flipper.net/zero/development/hardware/vgm-blueprints) |

![Plan du Flipper Zero](/img/remote/c91e01d61829df8e.png)

Les plans des modules externes donnent la géométrie recommandée pour les cartes qui se branchent sur le connecteur
GPIO — commencez par là si vous concevez votre propre module (voir aussi
[Modules d'extension](/fr/gpio/expansion-modules)).

## Cartes de développement

### Wi-Fi Developer Board

Basée sur l'**ESP32-S2-WROVER-N4R2**. Documents publiés : vue du PCB, plan d'assemblage
(`Wi-Fi Module_V1_Assembly.pdf`), schéma de l'ESP32-S2, schéma d'alimentation, schéma des connecteurs —
[Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).
Utilisation : [Dev board](/fr/gpio/devboard), [Déboguer les applications](/fr/dev/debugging).

### Dev board ST-Link V3 {#st-link-v3-developer-board}

Pour les développeurs avancés qui ont besoin de débogage in-circuit. Elle est basée sur le module
[ST-Link V3 Mods](https://www.st.com/en/development-tools/stlink-v3mods.html) et n'en diffère que par son facteur de
forme et sa facilité de connexion.

- ST-Link V3 Mods pour le flashage et le débogage in-circuit.
- UART vers USB intégré, relié à l'UART du Flipper (broches GPIO 13 et 14).
- Broches non utilisées du Flipper Zero et du ST-Link exposées pour le débogage et le prototypage.

Projet Altium Designer : [github.com/Flipper-Zero/flipperzero-devboard-stlinkv3](https://github.com/Flipper-Zero/flipperzero-devboard-stlinkv3).
Schéma et nomenclature : [ST-Link V3 Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3).

::: info Elle n'est pas nécessaire pour mettre à jour ni pour développer
Les mises à jour du firmware, le développement et l'envoi de votre propre firmware fonctionnent tous en USB simple.
Une carte de débogage n'est nécessaire que pour déboguer le firmware pendant son exécution (GDB, OpenOCD, …).
:::

## Pages liées

- [Brochage GPIO](/fr/gpio/pinout)
- [API Furi](/fr/dev/furi-api) — schéma des blocs matériels
- [Déboguer les applications](/fr/dev/debugging)
- [Mises à jour OTA](/fr/dev/ota)

MIFARE, MIFARE Ultralight, MIFARE Classic et DESFire sont des marques déposées de NXP B.V. FeliCa est une marque de
Sony Corporation.
