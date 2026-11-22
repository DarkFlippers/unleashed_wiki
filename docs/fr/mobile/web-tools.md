---
title: Outils web
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/apps]
sources: [unleashed-readme, unleashed-docs, flipper-docs]
---
# Outils web

Plusieurs outils pour le Flipper fonctionnent directement dans le navigateur, sans rien à installer. Les outils qui
dialoguent avec le Flipper en USB ont besoin de l'**API Web Serial** : utilisez donc **Chrome, Edge ou un autre
navigateur basé sur Chromium**.

::: warning Fermez d'abord qFlipper
Un outil web ne peut pas se connecter tant que qFlipper (ou un second onglet Flipper Lab) occupe le port série du
Flipper. C'est la raison la plus fréquente du « Chrome ne voit pas le Flipper ».
:::

## Outils Unleashed

| Outil | Adresse | Ce qu'il fait |
|---|---|---|
| Unleashed Web Installer | [web.unleashedflip.com](https://web.unleashedflip.com) | installer ou mettre à jour Unleashed (Release ou Dev) en USB |
| Dev builds | [dev.unleashedflip.com](https://dev.unleashedflip.com) | builds de test automatiques de la branche dev avec les nouvelles fonctions |
| Sub-GHz & Coordinates Map | [map.unleashedflip.com](https://map.unleashedflip.com) | afficher sur une carte les fichiers de wardriving Sub-GHz et tout autre fichier contenant des coordonnées |
| Wi-Fi Wardriving Map | [wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) | combiner et afficher plusieurs captures au format WiGLE (ESP32 Marauder et autres) |
| ESP32 Web Flasher | [espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) | flasher les modules ESP32 courants depuis le navigateur |

### Unleashed Web Installer

La méthode recommandée pour installer Unleashed.

1. Assurez-vous qu'une **carte microSD** est insérée.
2. Fermez qFlipper. Connectez le Flipper avec un câble USB de données.
3. Ouvrez [web.unleashedflip.com](https://web.unleashedflip.com) dans un navigateur Chromium.
4. Appuyez sur **Connect** et choisissez votre Flipper dans la fenêtre du navigateur.
5. Sélectionnez la branche **Release** ou **Dev**.
6. Appuyez sur **Install** et patientez. À la fin, tous les assets sont installés et le Flipper démarre sous
   Unleashed.

Autre possibilité : chaque [release GitHub](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) propose
un lien **Install via Web Updater** qui ouvre la release dans le web updater de Flipper Lab : appuyez sur **Connect**,
puis sur **Install**. Guide complet : [Installer Unleashed](/fr/start/install).

### Sub-GHz & Coordinates Map

[map.unleashedflip.com](https://map.unleashedflip.com) place sur une carte vos captures Sub-GHz contenant des
coordonnées (par exemple issues du wardriving Sub-GHz avec un module GPS) ainsi que tout autre fichier contenant des
coordonnées.

### Wi-Fi Wardriving Map

[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) fusionne plusieurs captures **au format WiGLE**, produites
par ESP32 Marauder et des outils similaires, et affiche les points d'accès sur une seule carte. Voir
[ESP32 et modules Wi-Fi](/fr/gpio/esp32).

### ESP32 Web Flasher

[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) est un outil de flashage simple d'emploi pour les
modules ESP32 courants, qui fonctionne entièrement dans le navigateur, sans installer d'outil de flashage. Voir
[ESP32](/fr/gpio/esp32) et [Dev board](/fr/gpio/devboard).

## Flipper Lab (officiel)

[lab.flipper.net](https://lab.flipper.net) est la boîte à outils web officielle. Elle fonctionne avec Unleashed :

- [Apps](https://lab.flipper.net/apps) : le catalogue d'applications officiel, installation / mise à jour /
  suppression d'applications en USB, voir [Applications sur la carte SD](/fr/apps/sd-card-apps).
- [CLI](https://lab.flipper.net/cli) : un terminal pour la ligne de commande du Flipper, voir [CLI](/fr/dev/cli).
- [Pulse Plotter](https://lab.flipper.net/pulse-plotter) : visualiser les signaux Sub-GHz RAW, utile pour analyser une
  télécommande inconnue.
- Le **web updater** utilisé par les liens « Install via Web Updater ».

## Autres liens

- Page d'accueil d'Unleashed : [flipperunleashed.com](https://flipperunleashed.com)
- Liens de mise à jour `.tgz` directs : [unleashedflip.com](https://unleashedflip.com)
- JSON de répertoire pour les builds uFBT : [up.unleashedflip.com/directory.json](https://up.unleashedflip.com/directory.json)

::: danger Attention aux contrefaçons
[DarkFlippers/unleashed-firmware](https://github.com/DarkFlippers/unleashed-firmware) est la seule page officielle du
projet. Il n'existe aucune version payante, premium ou à code fermé ; quiconque en propose une est un escroc.
:::

## Pages liées

- [Installer Unleashed](/fr/start/install)
- [qFlipper](/fr/mobile/qflipper)
- [Application compagnon qUnleashed](/fr/mobile/qunleashed-app)
