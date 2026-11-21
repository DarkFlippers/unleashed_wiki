---
title: Mise à jour
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Mise à jour

Unleashed est mis à jour souvent. La mise à jour fonctionne exactement comme l'installation : la nouvelle version
s'installe **par-dessus** l'actuelle. Il n'est pas nécessaire de revenir au firmware officiel ni d'installer quoi que
ce soit entre les deux.

## Comment mettre à jour

**Recommandé : [qUnleashed](/fr/mobile/qunleashed-app)**, l'application compagnon Unleashed pour **Android, iOS,
Windows, macOS et Linux** (USB sur tous sauf iOS, qui passe par le Bluetooth). Elle télécharge le nouveau firmware
elle-même.

1. Installez ou mettez à jour qUnleashed depuis sa
   [page des releases](https://github.com/DarkFlippers/qUnleashed/releases).
2. Connectez le Flipper en USB ou en Bluetooth.
3. Ouvrez la **mise à jour du firmware**, choisissez le canal **Unleashed** (**Release** ou **Dev**) et la build que
   vous utilisez : **de base**, **avec les applications supplémentaires** ou **compacte**.
4. Lancez l'installation et attendez que le Flipper ait terminé toutes les étapes.

Si le Flipper ne démarre plus, **Repair from DFU mode** dans la même application le reflashe par USB
([Restauration](/fr/start/recovery#firmware-recovery)).

Les alternatives, toutes décrites dans les [méthodes d'installation](/fr/start/install) :

1. **[Web Installer](https://web.unleashedflip.com)** : Connect → choisir Release ou Dev → Install.
2. **qFlipper** : **Install from file** avec le nouveau `flipper-z-f7-update-(version).tgz`.
3. **Application mobile** : canal de mise à jour personnalisé avec le `.tgz`.
4. **Hors ligne** : copiez `f7-update-(version)` dans `/ext/update/` et ouvrez `update.fuf` depuis l'`Archive`.

::: warning N'appuyez pas sur « Update » dans qFlipper ni dans l'application officielle
Le bouton **Update** intégré à qFlipper et à la Flipper Mobile App utilise le serveur de mise à jour **officiel**. Il
remplace Unleashed par le firmware d'origine. Pour Unleashed, passez par la mise à jour de qUnleashed, par
**Install from file**, par le canal personnalisé ou par le Web Installer.
:::

## Release ou dev ?

| | Release | Dev |
|---|---|---|
| Stabilité | Testée | Peut contenir des bugs |
| Nouvelles fonctions | À chaque version | Dès qu'elles sont fusionnées |
| Où l'obtenir | Web Installer → Release, [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), [@unleashed_fw](https://t.me/unleashed_fw) | Web Installer → Dev, [dev.unleashedflip.com](https://dev.unleashedflip.com), [@kotnehleb](https://t.me/kotnehleb) |

Les builds dev sont compilés automatiquement à partir des derniers commits. Le build dev précédent est supprimé du site
dès qu'un nouveau est mis en ligne. Signalez les bugs sur
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

## Ce qui est conservé lors d'une mise à jour

- **Vos fichiers sur la carte microSD** : les clés, cartes, télécommandes et scripts enregistrés ne sont pas touchés.
- **Votre nom personnalisé** : stocké sur la carte dans `/ext/dolphin/name.settings`
  ([Nom personnalisé du Flipper](/fr/start/custom-name)).
- **Les réglages** : conservés en général. **Exception :** lorsqu'une version modifie la structure d'un fichier de
  réglages, ce fichier est réinitialisé une fois aux valeurs par défaut. Cela n'arrive que sur certaines versions. Si
  vos réglages de bureau (code PIN, favoris…) sont réinitialisés après une mise à jour, refaites-les et consultez le
  changelog.
- **Les applications intégrées** dans `/ext/apps/` sont remplacées par les versions du nouveau firmware. Les packs
  d'applications ne peuvent jamais les écraser ni les faire revenir à une version antérieure.

## Vérifier sa version

- **Main Menu → Settings → About** : version du firmware, date de compilation, branche et commit ;
- ou maintenez <kbd>↓</kbd> sur le bureau pour afficher l'écran de debug/informations.

## Où lire ce qui a changé

- [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases) : changelog de chaque version ;
- [CHANGELOG.md](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md) sur la branche dev : ce qui
  arrivera dans la prochaine version ;
- mises à jour des applications : [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/commits/dev).

## Le serveur de mise à jour Unleashed

Unleashed exploite son propre serveur de mise à jour, au même format que le serveur officiel :
`https://up.unleashedflip.com/directory.json`. Les applications officielles ne peuvent pas être redirigées vers lui
sans être recompilées. **uFBT** accepte cette URL en argument pour compiler des applications contre le SDK Unleashed
(voir [Compiler le firmware](/fr/dev/build)).

## Si une mise à jour échoue

1. Redémarrez avec <kbd>←</kbd> + <kbd>BACK</kbd> et réessayez.
2. Essayez une autre méthode (qUnleashed ↔ Web Installer ↔ qFlipper ↔ hors ligne).
3. Vérifiez la carte SD (**Settings → Storage → About SD Card**), ou formatez-la après une sauvegarde.
4. Toujours en échec : [Restauration](/fr/start/recovery).
