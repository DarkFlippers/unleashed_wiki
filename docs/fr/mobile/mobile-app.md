---
title: Application mobile Flipper
order: 20
original: [https://docs.flipper.net/zero/mobile-app, https://docs.flipper.net/zero/mobile-app/bug-report, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# Application mobile Flipper

La **Flipper Mobile App** officielle ([App Store](https://apps.apple.com/us/app/flipper-mobile-app/id1534655259),
[Google Play](https://play.google.com/store/apps/details?id=com.flipperdevices.app)) se connecte au Flipper par
Bluetooth. Elle permet de mettre à jour le firmware, de parcourir et de partager les clés enregistrées, d'installer
des applications depuis le catalogue, de piloter le Flipper à distance et de sauvegarder vos données.

::: tip Unleashed
L'application mobile officielle fonctionne avec Unleashed. Elle peut installer un `.tgz` Unleashed en tant que mise à
jour **Custom** (voir ci-dessous). Si l'application cesse de se connecter après l'installation d'Unleashed ou après un
changement de nom du Flipper, refaites l'appairage, voir [Problèmes de connexion](#connection-problems).
:::

## Se connecter au Flipper

1. Sur le Flipper : `Main Menu → Settings → Bluetooth`, réglez **Bluetooth** sur **ON**.
2. Dans l'application, appuyez sur **Connect**, puis sur **Connect** à côté du nom de votre Flipper.
3. Saisissez le **code d'appairage** affiché sur l'écran du Flipper et appuyez sur **Pair**.
4. Attendez la fin de la synchronisation.

## Ce que contient l'application

- **Main Menu** (onglet de l'appareil) : mise à jour par Bluetooth, **Device Info** (détails matériels et firmware),
  **Options** (sauvegarde, journaux, gestionnaire de fichiers, redémarrage, rapport de bug ; l'ensemble disponible
  dépend d'iOS ou d'Android), synchronisation manuelle, émission d'un son pour retrouver le Flipper.
- **Archive** : tous les fichiers Sub-GHz, RFID 125, NFC, Infrared et iButton enregistrés. Favoris, recherche et
  restauration des éléments supprimés. Appuyez sur une clé pour ouvrir **Key Info** : émuler ou envoyer, ajouter aux
  favoris, renommer, ajouter une note, consulter les détails, supprimer, partager.
- **Apps** : le catalogue officiel d'applications, installées par Bluetooth LE, voir
  [Applications sur la carte SD](/fr/apps/sd-card-apps).
- **Tools** : **Mfkey32** (Extract MF Keys) pour calculer les clés MIFARE Classic à partir des nonces collectés, et la
  **Remotes Library** de télécommandes infrarouges (voir [L'infrarouge depuis le téléphone](/fr/infrared/mobile)).
- **Widget** : émuler des télécommandes et des cartes enregistrées depuis l'écran d'accueil du téléphone sans ouvrir
  l'application (sur iOS : vue Aujourd'hui → Modifier → Ajouter un widget → Flipper ; sur Android, ajoutez-le comme
  n'importe quel widget et appuyez dessus pour le configurer).

## Installer Unleashed depuis le téléphone

::: warning Première installation
S'il s'agit de votre premier firmware personnalisé, commencez par passer à la dernière version **officielle**, et
vérifiez que la carte SD est insérée. Déjà sous Unleashed ? Installez la nouvelle version par-dessus.
:::

### iOS

1. Ouvrez la [dernière version d'Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) et
   téléchargez `flipper-z-f7-update-(version).tgz`.
2. Dans l'application **Fichiers**, sélectionnez le `.tgz` téléchargé, appuyez sur **Partager** et choisissez
   l'application **Flipper**.
3. Dans l'application Flipper, vérifiez que l'Update Channel affiche `Custom flipper-z-f7-update...`, puis appuyez sur
   le bouton vert **Update**.
4. Attendez la fin de la mise à jour. L'application iOS peut afficher une erreur à la fin, alors que le Flipper est
   bien mis à jour.

### Android, avec le fichier `.tgz`

1. Téléchargez `flipper-z-f7-update-(version).tgz` depuis la page de release.
2. Dans l'application Flipper, appuyez sur **Update channel** → **Custom** et sélectionnez le fichier téléchargé.
3. Appuyez sur **Update** et patientez.

### Android, via le lien de l'updater web

1. Sur la page de release, appuyez sur **Install via Web Updater**.
2. Lorsqu'Android demande avec quoi ouvrir le lien, choisissez l'application **Flipper**.
3. Poursuivez l'installation et patientez.

Une mise à jour par Bluetooth peut prendre une dizaine de minutes. Autres méthodes :
[Installer Unleashed](/fr/start/install).

### Si la mise à jour échoue

- Vérifiez que le Flipper est allumé et toujours connecté en Bluetooth.
- Redémarrez le Flipper (<kbd>←</kbd> + <kbd>Back</kbd>) et relancez la mise à jour.
- Si l'échec persiste, le stockage interne est peut-être plein ou corrompu : installez plutôt avec
  [qFlipper](/fr/mobile/qflipper) ou avec le [Web Installer](/fr/mobile/web-tools#unleashed-web-installer), voir
  [Restauration](/fr/start/recovery).

## Sauvegarder vos clés

1. Dans l'onglet de l'appareil, appuyez sur **Options → Backup Keys**.
2. Choisissez où enregistrer ou partager le `.zip` contenant vos clés, vos cartes et vos télécommandes.

Pour restaurer, décompressez l'archive et envoyez les fichiers avec [qFlipper](/fr/mobile/qflipper). Pour une
sauvegarde complète de la carte SD, téléchargez toute la carte depuis le **File manager** de qFlipper.

## Problèmes de connexion {#connection-problems}

**Après l'installation d'Unleashed ou le renommage du Flipper, l'application ne se connecte plus :**

1. Dans l'application, appuyez sur **Forget flipper**.
2. Dans les réglages Bluetooth du téléphone, trouvez le Flipper, ouvrez ses options et choisissez **Oublier cet
   appareil**.
3. Sur le Flipper : `Settings → Bluetooth → Unpair All Devices`, puis confirmez avec **Unpair**.
4. Assurez-vous que le Bluetooth est sur ON sur le Flipper, puis refaites l'appairage depuis l'application.

**Le Flipper n'est pas détecté :** vérifiez que le Bluetooth est activé des deux côtés, déconnectez le Flipper des
autres appareils (par exemple l'hôte d'une [télécommande Bluetooth](/fr/apps/controllers)), mettez à jour
l'application et le firmware, redémarrez le Flipper.

**La synchronisation échoue :** supprimez l'appairage et refaites-le, redémarrez les deux appareils, et essayez
`Settings → System → Sleep Method → Legacy` sur le Flipper.

## Signaler des bugs de l'application

Pour les bugs de l'application officielle : **Options → Report Bug**, renseignez un titre et les étapes de
reproduction, laissez les journaux attachés, appuyez sur **Submit**, et publiez éventuellement l'identifiant de
l'issue sur [forum.flipperzero.one](https://forum.flipperzero.one/) (section Mobile App). Pour capturer les journaux
du Flipper destinés à un rapport : réglez `Settings → System → Log Level` sur **Debug**, connectez l'appareil en USB,
ouvrez un terminal série à **230400** bauds (ou [lab.flipper.net/cli](https://lab.flipper.net/cli)), lancez
`info device` puis `log`, reproduisez le bug, et supprimez les lignes `hardware.uid` et `hardware.name` avant de
publier.

## Pages liées

- [qFlipper](/fr/mobile/qflipper)
- [Application compagnon qUnleashed](/fr/mobile/qunleashed-app)
- [Installer Unleashed](/fr/start/install)
