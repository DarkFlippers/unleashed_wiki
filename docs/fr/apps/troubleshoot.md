---
title: Dépannage des applications
order: 140
original: [https://docs.flipper.net/zero/apps/troubleshoot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# Dépannage des applications

Lorsqu'une application ne peut pas démarrer, le Flipper affiche `Error: <name>` avec une indication courte et un lien
`r.flipper.net/err_0X`. Cette page explique chaque message tel qu'il apparaît dans Unleashed.

::: tip Unleashed
Unleashed ne bloque pas les applications compilées pour une autre version de l'API. À la place des erreurs
**Outdated App** / **Outdated Firmware** du firmware d'origine, il affiche un avertissement et vous laisse décider,
voir [App Too Old / App Too New](#app-too-old-app-too-new).
:::

## App Too Old / App Too New {#app-too-old-app-too-new}

```
App Too Old
APP:86 < FW:88
This app might not work
Continue anyways?
```

La **version majeure de l'API** de l'application diffère de celle du firmware : **App Too Old** signifie que
l'application a été compilée pour une API plus ancienne, **App Too New** pour une plus récente.

- Appuyez sur **Continue** (<kbd>→</kbd>) pour essayer malgré tout. Beaucoup d'applications fonctionnent, mais une
  application qui appelle une fonction modifiée peut planter.
- Appuyez sur <kbd>Back</kbd> pour annuler.
- La vraie solution : mettre l'application à jour (prenez-la dans le pack Unleashed actuel, ou recompilez-la pour le
  SDK actuel) ou, pour **App Too New**, mettre le firmware à jour.

## Error: App Not Found (err_01)

`Update firmware or app`

| Cause | Solution |
|---|---|
| le fichier de l'application a été supprimé de la carte SD | réinstallez l'application, ou réinstallez le firmware (pour les applications système) |
| une application mobile ancienne ou bêta a ouvert une application du catalogue absente de la carte | installez l'application mobile Flipper officielle depuis l'App Store / Google Play et réinstallez l'application |

Un message apparenté, **SD card needed** / `Install SD card to run this app`, signifie qu'une application du menu
réside sur la carte SD et qu'aucune carte n'est insérée. **Update needed** / `Update firmware to run this app`
signifie que la carte est bien là mais que le fichier de l'application manque : réinstallez le firmware avec la carte
insérée.

## Error: Invalid File (err_02)

`Update the app`. Le `.fap` est endommagé : en-tête ELF corrompu, fichier incomplet (copie interrompue) ou sections
impossibles à charger. Copiez ou installez de nouveau l'application.

## Error: Invalid Manifest (err_03)

`Update firmware or app`. Le manifeste (une section ELF spéciale contenant la version de l'API et les informations de
l'application) ne peut pas être lu. Le fichier est corrompu, ou l'application et le firmware sont trop éloignés. Mettez
l'application à jour ; si elle est plus récente que votre firmware, mettez le firmware à jour.

## Error: Missing Imports (err_04)

`Update firmware or app`. L'application appelle des fonctions que votre firmware n'exporte pas.

| Cause | Solution |
|---|---|
| l'application a été compilée pour un firmware plus récent | mettez Unleashed à jour |
| l'application a été compilée pour un autre fork (elle utilise les fonctions propres à ce fork) | trouvez un build de l'application pour Unleashed, ou recompilez-la avec le SDK Unleashed |

## Error: HW Target Mismatch (err_05)

`App not supported`. L'application a été compilée pour une cible matérielle Flipper différente. Elle ne peut pas
fonctionner sur cet appareil.

## Error: Out of Memory

`Not enough RAM to run the app. Please reboot the device`. Un FAP est chargé en RAM ; si le tas est fragmenté ou si
trop de choses tournent (par exemple une balise BLE en arrière-plan ou une grosse application), il n'y a pas la place.
Appuyez sur **Reboot** et relancez l'application juste après le démarrage.

## Toujours rien

1. Mettez à jour vers la dernière release Unleashed, voir [Mise à jour](/fr/start/updating).
2. Réinstallez l'application depuis le [pack d'applications](/fr/apps/catalog#base-and-extra-packs) actuel ou depuis le
   catalogue ([Applications sur la carte SD](/fr/apps/sd-card-apps)).
3. Si une application fait planter le Flipper, redémarrez avec <kbd>←</kbd> + <kbd>Back</kbd> ; voir
   [Restauration](/fr/start/recovery) s'il ne démarre plus.
4. Posez la question dans les discussions communautaires, voir [FAQ](/fr/start/faq).

## Pages liées

- [Applications sur la carte SD (.fap)](/fr/apps/sd-card-apps)
- [Applications fournies avec Unleashed](/fr/apps/catalog)
