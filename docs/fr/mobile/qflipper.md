---
title: qFlipper
order: 10
original: [https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/qflipper/windows-debug, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# qFlipper

**qFlipper** est l'application de bureau officielle du Flipper Zero : elle met à jour le firmware et les bases de
données, gère les fichiers de la carte microSD, sauvegarde et restaure l'appareil, répare un firmware endommagé et
affiche l'écran en miroir. Elle fonctionne sous Windows, macOS et Linux.

::: tip Unleashed
Les canaux de mise à jour de qFlipper (Release / RC / Dev) installent le firmware **officiel**. Pour installer
Unleashed, utilisez **Install from file** avec le `.tgz` d'Unleashed (qFlipper 1.2.0 ou plus récent), voir ci-dessous,
ou le [Web Installer](/fr/mobile/web-tools#unleashed-web-installer).
:::

## Installer qFlipper

Téléchargez-le depuis [flipperzero.one/update](https://flipperzero.one/update) et lancez l'installateur.

- **Windows** : Windows 10 et 11 uniquement. L'installateur installe également les pilotes.
- **macOS** : 10.14 ou plus récent, optimisé pour Apple Silicon.
- **Linux** : une AppImage. Rendez-la exécutable et mettez en place les règles udev :

```bash
chmod +x qFlipper-x86_64.AppImage
./qFlipper-x86_64.AppImage                 # run it
./qFlipper-x86_64.AppImage rules install   # udev rules, to use it as a normal user
```

(Depuis un gestionnaire de fichiers : Propriétés → Permissions → « Autoriser l'exécution du fichier comme un
programme » / « Est exécutable ».)

## Vue d'ensemble

Connectez le Flipper en USB, carte SD insérée, puis lancez qFlipper.

- **Device information** : informations matérielles et firmware, bouton de mise à jour, télécommande.
- **Advanced controls** : sauvegarde, restauration, réinitialisation d'usine, canal de mise à jour,
  **Install from file**.
- **File manager** : parcourir, envoyer, télécharger, renommer et supprimer les fichiers de la carte SD et du
  stockage interne.

## Installer Unleashed avec qFlipper

1. S'il s'agit de votre premier firmware personnalisé, commencez par passer à la dernière version **officielle**.
   Vérifiez que la carte SD est insérée.
2. Téléchargez `flipper-z-f7-update-(version).tgz` depuis les
   [releases d'Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) (choisissez la lettre de
   build souhaitée, voir [les variantes de build](/fr/apps/catalog#build-variants)).
3. Lancez qFlipper et connectez le Flipper.
4. Cliquez sur **Install from file** et sélectionnez le `.tgz`.
5. Attendez la fin de toutes les étapes. Le Flipper redémarre sous Unleashed avec toutes les ressources installées.

Déjà sous Unleashed ? Installez simplement la nouvelle version par-dessus, sans repasser par le firmware officiel.
Autres possibilités : [Installer Unleashed](/fr/start/install), [Mise à jour](/fr/start/updating).

## Envoyer et télécharger des fichiers

Dans le **File manager**, glissez des fichiers dans un dossier, ou faites un clic droit sur un dossier →
**Upload here**. Un clic droit sur un fichier ou un dossier → **Download** le copie sur l'ordinateur (une façon simple
de sauvegarder toute la carte SD).

| Commande | Windows / Linux | macOS |
|---|---|---|
| Entrer dans un dossier | Return | Return |
| Retour | Backspace | Backspace |
| Envoyer | Ctrl+L | Cmd+L |
| Télécharger | Ctrl+D | Cmd+D |
| Supprimer | Delete | Fn+Backspace |
| Supprimer immédiatement | Shift+Delete | Shift+Fn+Backspace |
| Nouveau dossier | Ctrl+N | Cmd+N |
| Renommer | Ctrl+E | Cmd+E |
| Rafraîchir | Ctrl+G | Cmd+G |

## Télécommande et captures d'écran

Dans **Device information**, cliquez sur l'image du Flipper, puis cliquez sur les boutons à l'écran ou utilisez le
clavier (ℹ️ affiche la correspondance des touches). **SAVE SCREENSHOT** enregistre l'écran courant sous forme
d'image.

## Journaux et rapports de bugs

- **LOGS → OPEN FULL LOG** affiche le journal de la session en cours ; enregistrez-le en `.txt`.
- qFlipper conserve les journaux des 100 dernières sessions : dans **LOGS**, faites un clic droit sur la zone de
  journal → **Browse all logs**.
- Signalez les problèmes du qFlipper officiel sur [forum.flipperzero.one](https://forum.flipperzero.one/) (section
  Firmware update / qFlipper). Les problèmes propres à Unleashed relèvent des discussions Unleashed ou des issues
  GitHub.

## Dépannage

### qFlipper ne voit pas le Flipper / Chrome n'arrive pas à se connecter

Un seul programme peut utiliser le port série. Si qFlipper est ouvert, Flipper Lab, le Web Installer et les autres
outils web ne peuvent pas se connecter, et inversement. Fermez qFlipper (et les onglets Flipper Lab superflus) avant
d'utiliser un outil dans le navigateur.

### Pilotes Windows

1. N'installez qFlipper que depuis les sources officielles : il installe les bons pilotes. Recherchez les mises à jour
   dans **Advanced controls → CHECK APP UPDATES**.
2. **Mode normal** (Flipper démarré) : le Flipper apparaît comme **USB Serial Device** dans
   `Gestionnaire de périphériques → Ports (COM & LPT)`, identifiant matériel **VID 0483, PID 5740**, pilote
   **Microsoft**. Si un autre pilote est installé, désinstallez-le et rebranchez l'appareil.
3. **Conflit de port COM** : deux périphériques série portent le même numéro de COM. Ouvrez l'un d'eux →
   **Paramètres du port → Avancé** et attribuez un **numéro de port COM** libre.
4. **Mode recovery (DFU)** : maintenez <kbd>←</kbd> + <kbd>Back</kbd>, relâchez <kbd>Back</kbd> et gardez
   <kbd>←</kbd> enfoncé jusqu'à ce que la LED devienne bleue. Le Flipper doit apparaître comme **DFU in FS Mode** sous
   `Périphériques Universal Serial Bus`, **VID 0483, PID DF11**, pilote **STMicroelectronics**.
5. Si vous voyez **STM Device in DFU mode** sous `Contrôleurs de bus USB`, c'est le mauvais pilote qui est installé :
   désinstallez qFlipper, réinstallez-le depuis le site officiel et vérifiez à nouveau.
6. Si **DFU in FS Mode** se trouve sous `Autres périphériques` avec un point d'exclamation : clic droit →
   **Mettre à jour le pilote → Parcourir mon poste de travail → Me laisser choisir** →
   **Périphériques Universal Serial Bus** → **WinUsb Device**.

Si le Flipper ne démarre pas du tout, voyez [Restauration](/fr/start/recovery).

## Pages liées

- [Installer Unleashed](/fr/start/install)
- [Application mobile Flipper](/fr/mobile/mobile-app)
- [Outils web](/fr/mobile/web-tools)
