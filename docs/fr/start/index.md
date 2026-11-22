---
title: Démarrage
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-readme, unleashed-docs, unleashed-src, flipper-docs]
---
# Démarrage

Cette section vous accompagne du Flipper Zero tout neuf jusqu'à un appareil entièrement configuré sous **Unleashed
Firmware**. Elle couvre les bases que toutes les autres sections du wiki considèrent comme acquises : les boutons, le
bureau, l'alimentation, la carte microSD, les réglages et la restauration.

## Qu'est-ce que le Flipper Zero ?

Le Flipper Zero est un multi-outil de poche conçu pour explorer les technologies radio et de contrôle d'accès. Son
matériel comprend :

- un **émetteur-récepteur Sub-GHz CC1101** pour les télécommandes de garage, les barrières, les capteurs et autres
  appareils en dessous de 1 GHz ;
- un module **NFC 13,56 MHz** et une antenne **RFID 125 kHz** pour les cartes, les porte-clés et les badges ;
- un émetteur et un récepteur **infrarouge** pour les téléviseurs, les climatiseurs et autres télécommandes ;
- une surface de contact **1-Wire (iButton)** pour les clés Dallas, Cyfral et Metakom ;
- l'**USB** et le **Bluetooth LE**, qui lui permettent de se faire passer pour un clavier (Bad USB), un jeton U2F ou
  une télécommande ;
- des broches **GPIO** pour les modules externes (CC1101 externe, NRF24, ESP32, SIM800 et bien d'autres) ;
- un écran monochrome 128×64, un pavé à 5 positions avec un bouton Back, et une batterie de 2100 mAh.

Un dauphin numérique de compagnie vit sur le bureau. Il monte de niveau à mesure que vous utilisez l'appareil.

## Qu'est-ce que le firmware Unleashed ?

[Unleashed](https://github.com/DarkFlippers/unleashed-firmware) est un fork du firmware officiel (OFW). Il reste
**entièrement compatible avec l'API et les applications de l'OFW** et ajoute des fonctions par-dessus. Les principaux
apports :

- **aucune restriction régionale d'émission en Sub-GHz**, des fréquences supplémentaires et une plage étendue
  facultative ;
- **beaucoup plus de protocoles Sub-GHz**, dont la possibilité d'enregistrer et d'envoyer de nombreux systèmes à code
  tournant, des boutons personnalisés, et `Add manually` pour créer de nouvelles télécommandes ;
- la prise en charge du module **CC1101 externe** ;
- des parseurs NFC supplémentaires, un parseur EMV, davantage de clés MIFARE Classic dans le dictionnaire système ;
- des fuzzers RFID et iButton, un outil T5577 et d'autres applications intégrées ;
- des améliorations du quotidien : nom de Flipper personnalisé, horloge sur le bureau, pourcentage de batterie,
  Night Shift, plus de jeux en Dummy Mode, BadKB (Bad USB par Bluetooth) et bien plus.

La liste complète avec les liens se trouve sur la page
[Les apports d'Unleashed](/fr/start/unleashed-features).

::: warning Sources officielles uniquement
`DarkFlippers/unleashed-firmware` est le seul dépôt officiel du projet. Toutes les versions sont gratuites et open
source. Il n'existe aucune version payante, « premium » ou à code fermé. Quiconque vous en propose une est un escroc.
:::

## Versions release et dev

| Build | De quoi il s'agit | Où l'obtenir |
|---|---|---|
| **Release** (stable) | Versions testées, recommandées pour un usage quotidien | [Web Installer](https://web.unleashedflip.com), [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), Telegram [@unleashed_fw](https://t.me/unleashed_fw) |
| **Dev** (test) | Compilations automatiques de la branche `dev` pour tester les nouvelles fonctions | [dev.unleashedflip.com](https://dev.unleashedflip.com), Telegram [@kotnehleb](https://t.me/kotnehleb), canal Discord `unleashed-development` |

Un nouveau build dev remplace le précédent sur le site web ; les anciens builds dev ne subsistent que sous forme de
fichiers dans le canal Telegram. Les builds dev reçoivent les nouveautés en premier mais **peuvent contenir des bugs**.
Si vous en trouvez un, signalez-le sur
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

Chaque version existe en trois variantes : `E` (base + applications supplémentaires), sans suffixe (applications de
base) et `C` (sans applications communautaires). Les détails figurent dans
[Installer Unleashed](/fr/start/install#which-file-to-download).

## Canaux communautaires

- Discussions Telegram : [anglais](https://t.me/flipperzero_unofficial), [russe](https://t.me/flipperzero_unofficial_ru), [ukrainien](https://t.me/flipperzero_unofficial_ua)
- Discord : [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Site web d'Unleashed : [flipperunleashed.com](https://flipperunleashed.com)

## Pages de cette section

**Premiers pas**
- [Premier démarrage](/fr/start/first-start) : allumage, insertion d'une carte microSD, installation d'Unleashed
- [Installer Unleashed](/fr/start/install) : Web Installer, qFlipper, applications mobiles, mise à jour hors ligne
  depuis la carte SD
- [Mise à jour](/fr/start/updating) : rester à jour, release ou dev, ce qui est conservé
- [Les apports d'Unleashed](/fr/start/unleashed-features) : toutes les fonctions d'Unleashed comparées au firmware
  d'origine

**Utiliser l'appareil**
- [Commandes](/fr/start/controls) : boutons, mode gaucher, raccourcis
- [Bureau](/fr/start/desktop) : barre d'état, raccourcis, Lock Menu, Quick Settings, Dummy Mode, Archive
- [Le dauphin](/fr/start/dolphin) : humeur, niveaux et expérience
- [Alimentation et batterie](/fr/start/power) : recharge, extinction, Auto PowerOff, Limit Charge
- [Carte microSD](/fr/start/sd-card) : choix, formatage, structure des dossiers
- [Réglages](/fr/start/settings) : chaque entrée du menu Settings, une par une
- [Nom personnalisé du Flipper](/fr/start/custom-name)

**Quand quelque chose ne va pas**
- [Combinaisons de touches](/fr/start/key-combos) : combinaisons de réinitialisation et de DFU
- [Restauration](/fr/start/recovery) : restauration du firmware, réinitialisation d'usine, réinitialisation du code PIN
- [Réglages dangereux](/fr/start/dangerous-settings) : plage Sub-GHz étendue (à lire avant d'y toucher)
- [FAQ](/fr/start/faq)

::: tip Cadre légal
Unleashed est destiné à l'expérimentation et à la recherche légale. Utilisez-le sur vos propres appareils ou avec
autorisation.
:::
