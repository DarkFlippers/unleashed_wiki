---
title: "JavaScript : présentation"
sidebarTitle: "JS : présentation"
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_about.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app]
sources: [unleashed-docs, unleashed-src]
---
# JavaScript sur le Flipper Zero

Écrire une application pour le Flipper Zero signifiait autrefois du C, une chaîne d'outils complète et beaucoup de
lecture du code source d'autres applications. Le firmware embarque désormais un **moteur JavaScript intégré** : vous
pouvez écrire un simple fichier `.js`, le copier sur la carte SD et l'exécuter directement depuis l'appareil. Aucune
compilation sur un PC n'est nécessaire, et les scripts se partagent facilement.

- Les scripts résident dans `/ext/apps/Scripts/` et se lancent depuis `Main Menu → Apps → Scripts`, ou depuis le CLI
  avec `js <path>`.
- Le moteur est basé sur [mJS](https://github.com/cesanta/mjs), un interpréteur JavaScript conçu pour les
  microcontrôleurs : il nécessite moins de 50 Ko de flash et environ 2 Ko de RAM. Le Flipper conserve le cœur de mJS
  et y ajoute des extras comme les tableaux binaires compacts (`ArrayBuffer`, tableaux typés).
- Les scripts peuvent utiliser l'interface graphique, les boutons, l'USB HID (BadUSB), le GPIO, l'UART, le système de
  fichiers et davantage, au travers de **modules** chargés avec `require()`.

::: warning mJS n'est pas un moteur de navigateur
mJS ne prend en charge qu'un sous-ensemble de JavaScript. Surtout, il n'y a **pas de fermetures** (une fonction ne peut
pas utiliser les variables de la portée environnante ; voir [Boucle d'événements](/fr/dev/js-event-loop) pour la
solution de contournement), les chaînes sont codées sur un octet sans prise en charge de l'UTF-8, et beaucoup d'objets
de la bibliothèque standard sont absents. Voir le [README de mJS](https://github.com/cesanta/mjs) pour la liste
complète des limites.
:::

## Pour commencer

1. [Votre première application JS](/fr/dev/js-first-app) : écrire un script, le copier sur le Flipper, l'exécuter
   depuis le menu ou le CLI.
2. [SDK JavaScript](/fr/dev/js-sdk) : TypeScript, complétion de code et envoi en une seule commande avec
   `npm start`.
3. [Utiliser les modules JS](/fr/dev/js-modules) : comment fonctionne `require()`.

## Référence du langage

- [Types de données](/fr/dev/js-data-types)
- [Fonctions intégrées](/fr/dev/js-builtin) : `print`, `delay`, `require`, `load`, méthodes de chaînes et de tableaux,
  contrôles de compatibilité du SDK.

## Référence des modules

| Module | Nom pour `require()` | Page |
|---|---|---|
| Boucle d'événements | `event_loop` | [Boucle d'événements](/fr/dev/js-event-loop) |
| Interface graphique | `gui`, `gui/*` | [GUI](/fr/dev/js-gui), [Vues GUI](/fr/dev/js-gui-views) |
| BadUSB (clavier USB HID) | `badusb` | [BadUSB](/fr/dev/js-badusb) |
| Informations sur l'appareil | `flipper` | [Flipper](/fr/dev/js-flipper) |
| GPIO, ADC, PWM | `gpio` | [GPIO](/fr/dev/js-gpio) |
| Mathématiques | `math` | [Math](/fr/dev/js-math) |
| Notifications LED / vibreur / son | `notification` | [Notification](/fr/dev/js-notification) |
| UART | `serial` | [Serial](/fr/dev/js-serial) |
| Fichiers et dossiers | `storage` | [Storage](/fr/dev/js-storage) |

Des scripts d'exemple pour chaque module sont installés avec le firmware dans `/ext/apps/Scripts/js_examples/` (par
exemple `gui.js`, `badusb_demo.js`, `gpio.js`, `storage.js`). Les lire est la façon la plus rapide d'apprendre l'API.

## Extras Unleashed : les modules sans documentation dédiée {#unleashed-extras}

::: tip Unleashed
Unleashed renvoie `flipper.firmwareVendor === "unleashed"` et fournit des **modules JS supplémentaires** absents du
firmware d'origine. Ils ne sont pas couverts par la documentation JS officielle ; les signatures ci-dessous sont
extraites des sources du firmware (`applications/system/js_app/modules/`) et des typages TypeScript de
`packages/fz-sdk/`. Chaque module est aussi une « fonctionnalité » du SDK : testez-la avec `doesSdkSupport([...])` ou
`checkSdkFeatures([...])` (voir [Fonctions intégrées](/fr/dev/js-builtin#sdk-compatibility)) pour que votre script
continue de fonctionner sur d'autres firmwares.
:::

La liste complète des fonctionnalités supplémentaires annoncées par Unleashed est : `baseline`, `gpio-pwm`,
`gui-widget`, `serial-framing`, `gui-widget-extras`, `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`,
`usbdisk-createimage`, `vgm`.

| Module | Nom de la fonctionnalité | Ce qu'il fait | Page |
|---|---|---|---|
| `subghz` | `subghz` | Piloter la radio Sub-GHz (CC1101 interne ou externe) : RX, RSSI, fréquence, émission de fichiers `.sub` | [JS : subghz](/fr/dev/js-subghz) |
| `infrared` | `infrared-send` | Émettre des signaux IR par protocole ou sous forme de timings bruts | [JS : infrared](/fr/dev/js-infrared) |
| `blebeacon` | `blebeacon` | Diffuser des paquets d'annonce BLE personnalisés (balise supplémentaire) | [JS : blebeacon](/fr/dev/js-blebeacon) |
| `usbdisk` | `usbdisk` | Émuler un périphérique de stockage de masse USB à partir d'une image disque | [JS : usbdisk](/fr/dev/js-usbdisk) |
| `i2c` | `i2c` | Dialoguer avec les périphériques I2C du connecteur GPIO | [JS : i2c](/fr/dev/js-i2c) |
| `spi` | `spi` | Dialoguer avec les périphériques SPI du bus SPI externe | [JS : spi](/fr/dev/js-spi) |
| `vgm` | `vgm` | Lire l'IMU (pitch/roll/yaw) du Video Game Module | [JS : vgm](/fr/dev/js-vgm) |

Le module GUI possède aussi des vues absentes de la documentation officielle : `button_menu`, `button_panel`, `menu`,
`number_input`, `popup`, `vi_list`. Elles sont décrites sur [Vues GUI](/fr/dev/js-gui-views).

Les API du firmware que ce wiki ne couvre pas sont listées dans la [référence API Doxygen officielle](https://developer.flipper.net/flipperzero/doxygen/).

## Pages liées

- [Écrire des applications en C](/fr/dev/first-app-c), lorsque le JS n'est pas assez rapide ou assez souple.
- [Format des scripts BadUSB](/fr/badusb/script-format), l'alternative DuckyScript classique au module JS `badusb`.
