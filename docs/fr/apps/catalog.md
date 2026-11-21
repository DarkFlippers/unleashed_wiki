---
title: Applications fournies avec Unleashed
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, unleashed-src]
---
# Applications fournies avec Unleashed

Une installation d'Unleashed comporte trois couches d'applications :

1. **Les applications système (intégrées).** Elles sont compilées depuis le dépôt du firmware et installées à chaque
   mise à jour du firmware, quel que soit le build choisi.
2. **Le pack Base Apps.** Un ensemble d'applications communautaires, préinstallé dans le build par défaut.
3. **Le pack Extra Apps.** Beaucoup plus d'applications communautaires, préinstallées seulement dans le build `e`.

En plus de cela, vous pouvez installer vous-même tout ce que vous voulez, voir
[Applications sur la carte SD](/fr/apps/sd-card-apps).

## Variantes de build {#build-variants}

Les fichiers de release sont nommés `flipper-z-f7-update-(version)(e / c).tgz` :

| Partie | Signification |
|---|---|
| `flipper-z` | pour le Flipper Zero |
| `f7` | cible matérielle, identique pour tous les Flipper Zero |
| `update` | paquet de mise à jour : updater, assets (applications, bibliothèques IR, etc.) et le firmware lui-même |
| `(version)` | version du firmware |
| suffixe | quels packs d'applications sont inclus (ci-dessous) |

| Suffixe | Base Apps | Extra Apps |
|---|:---:|:---:|
| aucun (` `) | oui | non |
| `c` | non | non |
| `e` | oui | oui |

- **` ` (aucune lettre)** est le choix par défaut : firmware, applications système et pack Base.
- **`c`** : firmware et applications système uniquement, aucun pack d'applications. Choisissez-le si vous voulez
  composer votre propre sélection d'applications.
- **`e`** : firmware, applications système, pack Base et pack Extra.

La méthode recommandée pour installer l'un ou l'autre est le [Web Installer](/fr/mobile/web-tools), voir aussi
[Installer Unleashed](/fr/start/install).

::: tip Unleashed
Les applications intégrées ne font **pas** partie des packs Base ou Extra. Une mise à jour du firmware les écrit dans
le dossier `apps/` de la carte SD : installer un pack d'applications ne peut donc jamais écraser une application
système ni la ramener à une version antérieure.
:::

## Applications système : affichées dans le menu principal

| Application | Ce qu'elle fait | Auteur / origine |
|---|---|---|
| GPIO | contrôle des broches GPIO, pont USB-UART et outils 1-Wire/iButton | OFW |
| iButton | lire, enregistrer et émuler les clés Dallas / Cyfral / Metakom | OFW |
| Infrared | apprendre, enregistrer et émettre des signaux IR, télécommandes universelles | OFW |
| NFC | lire, enregistrer, émuler et analyser les cartes NFC | OFW |
| 125 kHz RFID | lire, enregistrer, émuler et écrire les badges RFID LF | OFW |
| Bad USB | charges Ducky Script en USB, et BadKB en Bluetooth | OFW + BadKB par Willy-JL, ClaraCrazy et les contributeurs XFW |
| U2F | jeton de sécurité FIDO U2F en USB, voir [U2F](/fr/apps/u2f) | OFW |
| Clock | horloge avec réglage de la luminosité de l'écran, alarme et minuteur simple, voir [Horloge](/fr/apps/clock) | @nymda, avec @Willy-JL, @mishamyte et @xMasterX |
| Sub-GHz Remote | associer jusqu'à 5 fichiers `.sub` enregistrés aux boutons et les émettre, voir [Sub-GHz Remote](/fr/subghz/remote) | @gid9798 et @xMasterX |

Sub-GHz, Archive, Settings et les services système sont compilés dans le binaire du firmware lui-même.

## Applications système : dans le dossier Apps

Il s'agit de fichiers `.fap` accessibles via `Main Menu → Apps`, répartis dans des dossiers de catégorie.

| Application | Dossier | Ce qu'elle fait | Auteur / origine |
|---|---|---|---|
| MFKey | NFC | retrouver les clés MIFARE Classic à partir des nonces collectés par Detect Reader, voir [Application MFKey](/fr/nfc/mfkey-app) | @noproto |
| T5577 | RFID | lire, modifier et écrire les blocs T5577, effacer ou supprimer le mot de passe, sniffer un mot de passe, voir [Application T5577](/fr/rfid/t5577-app) | @mishamyte |
| Nice O-Code | Sub-GHz | retrouver le code installateur d'une télécommande Nice O-Code et l'enregistrer en `.sub`, voir [Nice O-Code](/fr/subghz/nice-o-code) | @xMasterX |
| Security+ PIN | Sub-GHz | trouver le PIN du clavier dans un signal Security+ 2.0 capturé, voir [Security+ PIN](/fr/subghz/secplus-pin) | @xMasterX |
| Seed Capturer | Sub-GHz | collecter des paires Fix + Hop des télécommandes FAAC SLH, Genius, Erreka et BFT Mitto pour une récupération du Seed hors ligne, voir [Seed Capturer](/fr/subghz/seed-capturer) | @xMasterX |
| Remote Analyzer | Sub-GHz | décoder une télécommande à la fois sur le CC1101 interne, avec un analyseur de fréquence intégré, voir [Remote Analyzer](/fr/subghz/remote-analyzer) | @xMasterX |
| Sub-GHz RAW Edit | Sub-GHz | ouvrir une capture RAW `.sub`, trouver le signal, le rogner, le fusionner et le décoder, voir [Éditeur RAW](/fr/subghz/raw-editor) | Lechnio |
| SIM800 | GPIO | piloter un module GSM SIM800C/SIM800L : appels, SMS, répertoire, USSD, DTMF, terminal AT, voir [SIM800](/fr/gpio/sim800) | @xMasterX |
| FindMy Flipper | Bluetooth | balise de localisation BLE pour Apple Find My / Google Find My Device et d'autres, voir [FindMy Flipper](/fr/apps/find-my-flipper) | @MatthewKuKanich |
| USB Keyboard & Mouse | USB | la télécommande HID en USB, voir [Télécommande HID](/fr/apps/hid-remote) | OFW |
| Bluetooth Remote | Bluetooth | la télécommande HID en Bluetooth, voir [Télécommande HID](/fr/apps/hid-remote) | OFW |
| Snake Game | Games | Snake, voir [Snake](/fr/apps/snake) | OFW |

Le firmware embarque également les **styles du menu principal**, de petits plugins que l'on change dans
`Settings → Desktop → Menu Style`, voir [Styles du menu principal](/fr/apps/menu-styles), ainsi que le moteur
d'exécution JavaScript utilisé pour les scripts `.js` (voir [JavaScript](/fr/dev/js-about)).

::: info Changements récents
Depuis le build du 20 novembre 2026, Sub-GHz RAW Edit est fourni avec le firmware et ne fait plus partie du pack
Extra, et SIM800 est une nouvelle application intégrée (`Apps → GPIO → SIM800`).
:::

## Packs Base et Extra {#base-and-extra-packs}

Les applications communautaires sont rassemblées par @xMasterX dans
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev) : ce dépôt contient la liste complète
et le code source, et sa page [Releases](https://github.com/xMasterX/all-the-plugins/releases/latest) propose les packs
Base et Extra en téléchargements séparés, au cas où vous voudriez ajouter un pack à un build `c` ou mettre à jour des
applications entre deux releases du firmware.

Pour installer un pack à la main : téléchargez le `.zip` depuis la [page des releases](https://github.com/xMasterX/all-the-plugins/releases/latest), décompressez-le et
copiez les dossiers d'applications dans le dossier `apps` de la carte SD (`/ext/apps/`). La version d'API du pack
doit correspondre à celle du firmware (`Current API:` en haut de chaque changelog).

Les applications vers lesquelles pointe le ReadMe d'Unleashed (chacune figure dans l'un des packs) :

| Application | Pour en savoir plus |
|---|---|
| TOTP (Authenticator) | [description du fichier de configuration](https://github.com/akopachov/flipper-zero_authenticator/blob/master/docs/conf-file_description.md) |
| Barcode Generator | [Barcode Generator](/fr/apps/barcode) |
| Multi Converter | [Multi Converter](/fr/apps/multi-converter) |
| WAV Player | [fichiers d'exemple et comment convertir](https://github.com/UberGuidoZ/Flipper/tree/main/Wav_Player#readme) |
| Sub-GHz Playlist | [script de génération](https://github.com/darmiel/flipper-scripts/blob/main/playlist/playlist_creator_by_chunk.py) |
| Sub-GHz Bruteforcer | [Force brute Sub-GHz](/fr/subghz/bruteforce) |
| LF RFID / iButton Fuzzer | [Fuzzer RFID](/fr/rfid/fuzzer), [Fuzzer iButton](/fr/ibutton/fuzzer) |
| Unitemp (capteurs de température) | [utilisation et capteurs pris en charge](https://github.com/quen0n/unitemp-flipperzero#readme) |
| [NMEA] GPS | [utilisation](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md) |
| i2c Tools | [utilisation](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/flipper_i2ctools/README.md) |
| Applications NRF24 | [NRF24](/fr/gpio/nrf24) |
| [WiFi] Scanner, [ESP8266] Deauther, [ESP32] WiFi Marauder, [ESP32-CAM] Camera Suite | [ESP32 et modules Wi-Fi](/fr/gpio/esp32) |
| ESP flasher | [FAP « ESP flasher »](https://github.com/0xchocolate/flipperzero-esp-flasher) |
| Sentry Safe | [Sentry Safe](/fr/apps/sentry-safe) |

::: warning
Le contenu des packs change d'une release à l'autre. Le tag de build des packs actuels est indiqué en haut de chaque
changelog Unleashed (par exemple `Apps: Build tag (20nov2026)`), avec un lien vers les derniers commits des
applications.
:::

## Catalogue officiel

Le catalogue d'applications officiel du Flipper Zero est disponible dans [Flipper Lab](https://lab.flipper.net/apps)
et dans l'[application mobile Flipper](/fr/mobile/mobile-app). L'installation depuis ce catalogue est décrite dans
[Applications sur la carte SD](/fr/apps/sd-card-apps#installing-from-the-official-catalog).

## Pages liées

- [Applications sur la carte SD (.fap)](/fr/apps/sd-card-apps)
- [Dépannage des applications](/fr/apps/troubleshoot)
- [Installer Unleashed](/fr/start/install)
