---
title: Applications sur la carte SD (.fap)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Applications sur la carte SD (.fap)

Presque toutes les applications que vous lancez depuis `Main Menu → Apps` sont des **FAP** (Flipper App Package) : un
exécutable `.elf` accompagné de métadonnées supplémentaires (nom, icône, catégorie, version d'API requise) et,
éventuellement, de ressources embarquées. Les FAP résident sur la carte microSD : les **applications ont donc besoin
d'une carte SD** pour fonctionner.

## Où résident les applications

| Chemin | Ce qui s'y trouve |
|---|---|
| `/ext/apps/<Category>/*.fap` | les applications installées, un dossier par catégorie (`Sub-GHz`, `NFC`, `RFID`, `GPIO`, `USB`, `Bluetooth`, `Games`, `Tools`, ...) |
| `/ext/apps_data/<appid>/` | les données et réglages que chaque application enregistre pour elle-même |
| `/ext/apps_data/loader/plugins/` | les plugins du loader, par exemple les [styles du menu principal](/fr/apps/menu-styles) |

`Main Menu → Apps` affiche simplement les dossiers présents sous `/ext/apps`. L'onglet **Apps** de
l'[Archive](/fr/apps/archive) liste le même dossier et affiche en plus les scripts `.js`.

## Comment le Flipper exécute un FAP

Le microcontrôleur ne peut pas exécuter du code directement depuis un stockage externe. Lorsque vous lancez une
application, l'**App Loader** :

1. lit le FAP sur la carte SD et vérifie son intégrité ainsi que son manifeste ;
2. vérifie que la **version majeure d'API** de l'application correspond à la version majeure d'API du firmware ;
3. copie les sections de code et de données en RAM et corrige les adresses pour le nouvel emplacement (relocation) ;
4. résout chaque fonction importée par l'application via la **table de symboles** du firmware ;
5. démarre l'application.

Comme l'application s'exécute depuis la RAM, une grosse application laisse moins de tas disponible pour le reste. Seuls
le code et les données sont chargés : la RAM utilisée est donc inférieure à la taille du fichier `.fap`.

::: tip Unleashed
Unleashed conserve l'API officielle (la version d'API actuelle est indiquée en haut de chaque changelog, par exemple
`Current API: 88.27`), de sorte que la plupart des applications du catalogue officiel fonctionnent telles quelles. Si
la version majeure de l'API diffère, Unleashed ne refuse pas d'emblée : il affiche **App Too Old** ou **App Too New**
avec les deux versions (par exemple `APP:86 < FW:88`) et un bouton **Continue**, pour que vous puissiez tenter de
l'exécuter malgré tout. Voir [Dépannage des applications](/fr/apps/troubleshoot).
:::

## Installer des applications

### Depuis les packs d'applications

Le plus simple est de choisir un build de firmware qui inclut déjà un pack (build par défaut ou build `e`), voir
[Applications fournies avec Unleashed](/fr/apps/catalog).

Les deux packs viennent de [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Pour en ajouter un à la main :

1. Téléchargez le `.zip` depuis la [page des releases](https://github.com/xMasterX/all-the-plugins/releases/latest).
2. Décompressez-le.
3. Copiez les dossiers d'applications dans le dossier `apps` de la carte SD (`/ext/apps/`), en conservant leurs
   dossiers de catégorie.
4. Vérifiez que la version d'API du pack correspond à celle de votre firmware (`Current API:` en haut du changelog).

### Depuis le catalogue officiel {#installing-from-the-official-catalog}

Le catalogue d'applications officiel se trouve dans [Flipper Lab](https://lab.flipper.net/apps) (Chrome, Edge et les
autres navigateurs Chromium dotés de Web Serial) et dans l'onglet **Apps** de
l'[application mobile Flipper](/fr/mobile/mobile-app).

1. Fermez qFlipper et tout autre onglet Flipper Lab (un seul programme peut occuper le port série USB).
2. Connectez le Flipper en USB (Flipper Lab) ou en Bluetooth (application mobile).
3. Ouvrez **Apps**, trouvez l'application par catégorie ou par recherche.
4. Appuyez sur **Install** sur la vignette de l'application ou sur sa page et attendez la fin de l'envoi.
5. Sur le Flipper, ouvrez `Main Menu → Apps → <category> → <app>`.

Pour mettre à jour ou supprimer les applications du catalogue, ouvrez **Apps → Installed** et appuyez sur **Update** ou
sur l'icône de suppression (corbeille).

Si l'installation échoue : vérifiez la connexion, libérez de l'espace sur la carte SD (supprimez des fichiers dans
l'[Archive](/fr/apps/archive)) et assurez-vous que le firmware est à jour.

### À la main (n'importe quel `.fap`)

1. Téléchargez le `.fap` compilé pour votre firmware (un build Unleashed, ou un build OFW d'une version d'API
   compatible).
2. Copiez-le dans `/ext/apps/<Category>/` avec [qFlipper](/fr/mobile/qflipper), le gestionnaire de fichiers de
   l'application mobile ou un lecteur de cartes.
3. Lancez-le depuis `Main Menu → Apps`, ou ouvrez le fichier dans l'[Archive](/fr/apps/archive) et choisissez **Run**.

::: warning
Les applications compilées pour un autre fork de firmware peuvent importer des fonctions qu'Unleashed n'exporte pas ;
elles échouent alors avec **Missing Imports**. Prenez les applications dans les packs Unleashed ou recompilez-les avec
le SDK Unleashed.
:::

## Compiler votre propre FAP

Les FAP se développent exactement comme les applications intégrées. En résumé :

1. Placez le dossier de votre application dans `applications_user/` d'une copie des sources du firmware.
2. Dans son `application.fam`, mettez `apptype=FlipperAppType.EXTERNAL` (voir
   [Manifestes d'application](/fr/dev/app-manifests)).
3. Compilez avec l'une de ces commandes :

```bash
./fbt fap_{APPID}                                     # build one app
./fbt launch APPSRC=applications_user/path/to/app     # build, upload over USB and run
./fbt build APPSRC=applications_user/path/to/app      # build without uploading
./fbt faps                                            # build all FAPs (or ./fbt fap_dist)
```

Dans le profil VS Code par défaut, `launch` correspond à l'action **Launch App on Flipper**
(<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>).

**Assets.** Placez les images dans un sous-dossier de l'application et nommez-le dans `fap_icon_assets` ; ensuite,
faites `#include "{APPID}_icons.h"` et utilisez-les comme les icônes de `assets_icons.h`.

**Versionnement de l'API.** Toutes les fonctions du firmware ne sont pas accessibles aux applications : l'ensemble
exporté est listé dans le fichier `api_symbols.csv` de la cible matérielle. La version majeure augmente lors de
changements cassants (fonction ou variable supprimée, signature modifiée), la version mineure lors d'ajouts. `fbt`
gère cela automatiquement : les nouveaux symboles apparaissent avec un `?`, et vous devez marquer chacun d'eux `+`
(exporté) ou `-` (masqué) avant que le firmware ne se compile.

**Débogage.** `fbt` charge `debug/flipperapps.py` dans gdb, ce qui permet de déboguer un FAP comme du code du
firmware. Compilez et flashez le firmware (`./fbt`, `./fbt flash`), lancez votre FAP, puis attachez-vous avec
`./fbt debug`. Le firmware s'arrête sur un point d'arrêt juste après le chargement du FAP, ce qui vous permet d'y
placer vos propres points d'arrêt. Le type de build du firmware et de l'application (debug/release) doit correspondre,
et le build correspondant doit être lié en tant que `build/latest`.

Pour aller plus loin : [Compiler le firmware](/fr/dev/build), [fbt](/fr/dev/fbt) et
[Votre première application en C](/fr/dev/first-app-c).

## Pages liées

- [Applications fournies avec Unleashed](/fr/apps/catalog)
- [Dépannage des applications](/fr/apps/troubleshoot)
- [Archive (navigateur de fichiers)](/fr/apps/archive)
