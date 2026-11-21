---
title: Appairer la télécommande HID
order: 60
original: [https://docs.flipper.net/zero/apps/controllers, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app]
sources: [flipper-docs, unleashed-src]
---
# Appairer la télécommande HID

L'application de télécommande HID permet au Flipper de piloter des présentations, de saisir du texte, de déplacer la
souris et de contrôler le lecteur multimédia d'un ordinateur ou d'un téléphone. Cette page traite de la **connexion** ;
le détail de chaque mode se trouve sur [Télécommande USB / Bluetooth (HID)](/fr/apps/hid-remote).

La connexion est possible de deux façons :

| | USB | Bluetooth LE |
|---|---|---|
| Application | `Apps → USB → USB Keyboard & Mouse` | `Apps → Bluetooth → Bluetooth Remote` |
| Appairage | aucun, il suffit de brancher | une fois par hôte |
| Compatible avec | ordinateurs, téléphones avec USB-C/OTG | ordinateurs, Android, iPhone/iPad |

::: tip Unleashed
Dans Unleashed, les deux variantes s'appellent **USB Keyboard & Mouse** et **Bluetooth Remote**, et elles résident
dans les dossiers d'applications `USB` et `Bluetooth` (la documentation officielle appelle les deux « Remote »).
:::

## En USB

1. Connectez le Flipper à l'ordinateur avec un câble USB de données. Fermez d'abord qFlipper : la télécommande a
   besoin du port USB.
2. Ouvrez `Main Menu → Apps → USB → USB Keyboard & Mouse`.
3. Choisissez un mode (Keynote, Keyboard, Mouse...). L'ordinateur voit un nouveau clavier/souris, aucun pilote n'est
   nécessaire.

En quittant l'application, l'USB du Flipper revient à son mode normal (série).

## En Bluetooth

1. Activez le Bluetooth sur l'ordinateur ou le téléphone.
2. Sur le Flipper : `Main Menu → Settings → Bluetooth`, puis mettez **Bluetooth** sur **ON**.
3. Ouvrez `Main Menu → Apps → Bluetooth → Bluetooth Remote` et choisissez un mode.
4. Sur l'ordinateur ou le téléphone, ouvrez les réglages Bluetooth et connectez-vous à
   **Control &lt;nom du Flipper&gt;** (sur un téléphone, touchez **Pair**).
5. Si le Flipper affiche une confirmation d'appairage, appuyez sur <kbd>OK</kbd>.

Les fois suivantes, l'hôte se reconnecte automatiquement dès que vous ouvrez Bluetooth Remote.

::: tip Nom personnalisé
`Bluetooth Remote → Bluetooth Remote Name` change le nom diffusé, pratique si vous avez plusieurs télécommandes
Flipper ou si vous voulez qu'elle ressemble à un clavier ordinaire.
:::

### Si l'appairage échoue

- Vérifiez que le Bluetooth est sur ON dans `Settings → Bluetooth`.
- Supprimez l'ancienne entrée « Control ... » dans les réglages Bluetooth de l'hôte, puis, sur le Flipper, exécutez
  `Bluetooth Remote → Bluetooth Unpairing → Unpair` et refaites l'appairage.
- Déconnectez le Flipper des autres appareils (par exemple l'application mobile).
- Redémarrez le Flipper : maintenez <kbd>←</kbd> + <kbd>Back</kbd> pendant environ 5 secondes.
- Mettez le firmware à jour.

La télécommande conserve ses propres appairages (`/ext/apps_data/hid_ble/.bt_hid.keys`), séparés du Bluetooth
principal du Flipper utilisé par l'application mobile. **Bluetooth Unpairing** dans la télécommande n'efface que les
hôtes de la télécommande. L'option globale `Settings → Bluetooth → Unpair All Devices` efface tout : l'appairage de
l'application mobile ainsi que ceux de la télécommande (et de BadKB).

### iPhone / iPad : le mode TikTok ne réagit pas

1. Sur l'iPhone, ouvrez `Settings → Accessibility → Touch → AssistiveTouch`.
2. Activez **AssistiveTouch**.
3. Dans **Pointer Devices**, allez dans **Devices → Bluetooth Devices** et sélectionnez votre Flipper.

## Pages liées

- [Télécommande USB / Bluetooth (HID)](/fr/apps/hid-remote)
- [Paramètres](/fr/start/settings)
- [Application mobile Flipper](/fr/mobile/mobile-app)
