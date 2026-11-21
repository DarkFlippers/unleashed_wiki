---
title: Restauration
order: 130
original: [https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://docs.flipper.net/zero/basics/firmware-update/storage-repair, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings]
sources: [flipper-docs, unleashed-docs, unleashed-src]
---
# Restauration

Que faire lorsque le Flipper se fige, refuse de se mettre à jour, n'affiche plus rien, ou que vous avez oublié le code
PIN. Suivez les étapes dans l'ordre, de la plus douce à la plus radicale.

## 1. Commencez par redémarrer

- **Figé :** maintenez <kbd>←</kbd> + <kbd>BACK</kbd> pendant environ 5 secondes.
- **Toujours figé :** débranchez l'USB et maintenez <kbd>BACK</kbd> pendant 30 secondes (coupure d'alimentation).
- **Batterie vide :** chargez quelques minutes (ou une heure) puis réessayez.
- Depuis un Flipper fonctionnel : **Settings → Power → Reboot → Reboot Flipper**.

Toutes les combinaisons : [Combinaisons de touches](/fr/start/key-combos).

## 2. Restauration du firmware depuis le mode DFU {#firmware-recovery}

À utiliser lorsque le firmware est corrompu : la mise à jour échoue, l'écran affiche n'importe quoi ou rien du tout, ou
les boutons ne répondent plus. Le bootloader USB DFU flashe le firmware sans passer par le système de l'appareil.

### Étape 1 : passer le Flipper en mode DFU (restauration)

**Si le Flipper fonctionne encore mais ne se met pas à jour correctement :**
1. **Main Menu → Settings → Power → Reboot → Firmware Upgrade**.
2. Confirmez `Reboot to DFU Mode?` avec <kbd>→</kbd> **Reboot**.

*ou :* maintenez <kbd>←</kbd> + <kbd>BACK</kbd> pendant 5 s, relâchez <kbd>BACK</kbd>, et gardez <kbd>←</kbd> enfoncé
jusqu'à ce que la **LED bleue** s'allume.

**Si l'écran n'affiche rien et que les boutons ne répondent pas :**
1. **Débranchez le câble USB.**
2. Maintenez <kbd>OK</kbd> + <kbd>BACK</kbd> pendant **30 secondes**. Un écran vide est normal à ce stade.

Connectez ensuite le Flipper à l'ordinateur avec un câble USB.

### Étape 2 : vérifier que l'ordinateur voit un appareil DFU

| Système | Où regarder | Nom |
|---|---|---|
| Windows | Gestionnaire de périphériques | **DFU in FS Mode** |
| macOS | Menu Pomme → À propos de ce Mac → Rapport système → Matériel → USB (ou `system_profiler SPUSBDataType`) | **DFU in FS Mode** |
| Linux | `lsusb` | **STMicroelectronics STM Device in DFU Mode** |

Pas détecté ? Essayez un autre câble. Branchez directement sur un port USB de la carte mère, pas sur un hub ni un
adaptateur. Ou retirez la carte SD, chargez pendant une heure et connectez l'appareil sans la carte.

### Étape 3 : réparer

L'une ou l'autre application convient. Toutes deux reflashent entièrement le Flipper par USB.

**[qUnleashed](/fr/mobile/qunleashed-app)** — Android, Windows, macOS et Linux (iOS n'a pas d'USB) :

1. Connectez le Flipper en mode DFU par USB.
2. Ouvrez **Repair from DFU mode** et lancez l'opération.

**qFlipper** — Windows, macOS et Linux :

1. Lancez **qFlipper**. Il détecte l'appareil DFU.
2. Cliquez sur **Repair**. qFlipper installe intégralement le firmware **officiel**.

Réinstallez ensuite Unleashed : [Installer Unleashed](/fr/start/install).

::: tip Unleashed
Le bouton **Repair** de qFlipper restaure toujours le firmware officiel. Ce n'est pas un problème : vous repartez d'une
base propre. Après la réparation, réinstallez Unleashed avec qUnleashed, avec le Web Installer ou avec
**Install from file**. La réparation ne touche pas aux fichiers de votre carte SD.
:::

### Si qFlipper n'arrive pas à réparer

- Vérifiez que qFlipper est correctement installé. Sous Windows, consultez le guide de dépannage des pilotes de
  qFlipper.
- Débranchez l'USB, redémarrez avec <kbd>←</kbd> + <kbd>BACK</kbd>, et recommencez.
- Faites une coupure d'alimentation (<kbd>BACK</kbd> 30 s, USB débranché) et recommencez.
- Lancez qFlipper en tant qu'administrateur.
- Utilisez un port USB directement sur la carte mère.
- En dernier recours : flashez en SWD avec un ST-Link (voir
  [Combinaisons de touches](/fr/start/key-combos#if-nothing-helps)).

## 3. Réparation du stockage interne / réinitialisation d'usine {#factory-reset}

Si les mises à jour échouent parce que le stockage interne est plein ou corrompu, remettez le Flipper à l'état d'usine.
Cette opération efface le **stockage interne** : réglages, appairages Bluetooth, code PIN, niveau du dauphin.
**Les fichiers de la carte SD sont conservés.**

::: info Le stockage interne dans le firmware actuel
Dans le firmware actuel, le stockage interne (`/int`) est **virtuel** et réside dans le dossier caché `/ext/.int/` de
la carte SD. **Settings → Storage → About Internal Storage** affiche `Type: Virtual (/.int on SD)`.
:::

### Faites d'abord une sauvegarde (facultatif)

qFlipper → **Advanced controls** → **BACKUP** → choisissez un dossier → **BACKUP**. Cela enregistre le stockage interne
sous forme de `.tgz`. La carte SD n'est pas incluse : copiez-la séparément.

### Réinitialiser depuis l'appareil

1. **Main Menu → Settings → Storage → Factory Reset**.
2. L'écran demande `Confirm Factory Reset?` : *« Internal storage will be erased, data and settings will be lost! »*
3. Appuyez sur <kbd>→</kbd> **Erase** **5 fois**. L'écran décompte les appuis restants.
4. Le Flipper redémarre et formate le stockage interne.

### Réinitialiser avec qFlipper

**Advanced controls** → **ERASE** → **ERASE** → **CONTINUE** une fois terminé.

### Restaurer

qFlipper → **Advanced controls** → **RESTORE** → sélectionnez le `.tgz` de sauvegarde → **RESTORE** → **CONTINUE**.

Si la mise à jour échoue encore après une réinitialisation, recommencez **sans** restaurer la sauvegarde, ou faites une
[restauration du firmware](#firmware-recovery).

## 4. Réinitialiser un code PIN oublié {#reset-pin}

Si le Flipper est verrouillé par un code PIN dont vous ne vous souvenez plus :

1. **Débranchez le câble USB.**
2. Éteignez le Flipper : maintenez <kbd>BACK</kbd> → **Power Off**. Si vous n'y arrivez pas, passez à l'étape suivante
   mais maintenez les boutons 30 à 40 secondes.
3. Maintenez <kbd>↑</kbd> + <kbd>BACK</kbd> pendant environ 5 secondes. Le Flipper démarre avec <kbd>↑</kbd> enfoncé et
   affiche l'**écran de réinitialisation du PIN**.
4. **Maintenez <kbd>→</kbd>** jusqu'à ce que la barre de progression se remplisse pour confirmer la réinitialisation.
   Appuyez sur <kbd>↓</kbd> pour quitter sans rien réinitialiser.
5. Le Flipper redémarre.

Cette opération remet la configuration utilisateur (registres RTC, stockage interne avec les réglages et le code PIN) à
l'état d'usine. **Les fichiers utilisateur de la carte microSD sont conservés.**

## 5. Toujours mort ?

- Chargez pendant une heure, puis réessayez.
- Débranchez puis rebranchez la batterie (il faut ouvrir le boîtier).
- Flashez en SWD avec un ST-Link ou un autre programmateur.

Si rien de tout cela ne fonctionne, le problème est matériel, pas logiciel.

## Pages liées

- [Combinaisons de touches](/fr/start/key-combos)
- [Installer Unleashed](/fr/start/install)
- [Application compagnon qUnleashed](/fr/mobile/qunleashed-app)
- [qFlipper](/fr/mobile/qflipper)
