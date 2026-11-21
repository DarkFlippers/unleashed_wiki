---
title: Applications
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, flipper-docs, unleashed-src]
---
# Applications

Au-delà des grands outils intégrés (Sub-GHz, NFC, RFID, Infrarouge, iButton, Bad USB, GPIO), le Flipper Zero exécute
des **applications** : de petits programmes empaquetés en fichiers `.fap` qui résident sur la carte microSD. Unleashed
fournit son propre jeu d’applications système avec chaque build, propose deux packs d’applications facultatifs (Base et
Extra) et reste compatible avec le catalogue d’applications officiel.

::: tip Unleashed
Unleashed reste compatible au niveau de l’API avec le firmware officiel : les applications du catalogue officiel
(Flipper Lab ou l’application mobile) fonctionnent donc généralement aussi. En plus de cela, chaque release d’Unleashed
dispose d’un build `e` qui préinstalle le pack **Extra Apps** d’applications communautaires. Voir
[Applications fournies avec Unleashed](/fr/apps/catalog).
:::

## Obtenir et lancer des applications

- [Applications fournies avec Unleashed](/fr/apps/catalog) : les applications intégrées, les packs Base et Extra, et la
  signification des lettres de build `e`, ` ` et `c`.
- [Applications sur la carte SD (.fap)](/fr/apps/sd-card-apps) : où résident les applications, comment les installer à
  la main ou depuis le catalogue, et comment le chargeur vérifie la version de l’API.
- [Archive (navigateur de fichiers)](/fr/apps/archive) : parcourir, lancer, épingler, renommer, déplacer et supprimer
  les fichiers enregistrés.
- [Dépannage des applications](/fr/apps/troubleshoot) : ce que signifie chaque erreur du chargeur et comment la
  corriger.

## Applications intégrées

- [Clé de sécurité U2F](/fr/apps/u2f) : utiliser le Flipper comme second facteur FIDO U2F.
- [Horloge](/fr/apps/clock) : horloge de nuit avec réglage de la luminosité, chronomètre et alarme quotidienne.
- [Télécommande USB / Bluetooth (HID)](/fr/apps/hid-remote) : tous les modes de l’application de télécommande HID,
  bouton par bouton.
- [Appairer la télécommande HID](/fr/apps/controllers) : connecter la télécommande en Bluetooth ou en USB et résoudre
  les problèmes d’appairage.
- [FindMy Flipper](/fr/apps/find-my-flipper) : rendre le Flipper visible dans Apple Find My, Samsung SmartThings, Tile
  ou Google Find My Device.
- [Styles du menu principal](/fr/apps/menu-styles) : changer l’apparence du menu principal (PS4, Wii, DSi, C64,
  CoverFlow, Grid et d’autres).
- [Snake](/fr/apps/snake) : le jeu classique.

## Applications des packs

- [Barcode Generator](/fr/apps/barcode)
- [Multi Converter](/fr/apps/multi-converter)
- [Sentry Safe](/fr/apps/sentry-safe)

Les applications auxiliaires Sub-GHz, NFC et RFID (Seed Capturer, Remote Analyzer, MFKey, T5577 et d’autres) sont
traitées dans leurs sections respectives, par exemple [Seed Capturer](/fr/subghz/seed-capturer),
[Application MFKey](/fr/nfc/mfkey-app) et [Application T5577](/fr/rfid/t5577-app).
