---
title: Nom personnalisé du Flipper
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/CustomFlipperName.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/namechanger, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-docs, unleashed-src]
---
# Nom personnalisé du Flipper

Chaque Flipper porte un nom d'usine. Il apparaît dans le Passport, dans **About**, dans les listes d'appareils
Bluetooth et dans qFlipper. Unleashed permet de le remplacer par le nom de votre choix.

::: tip Unleashed
Le firmware d'origine ne propose aucun menu pour renommer l'appareil. Sur Unleashed, l'option se trouve dans
**Settings → Desktop → Change Flipper Name**, et le nom **survit aux mises à jour du firmware** puisqu'il est stocké
sur la carte microSD.
:::

## Définir un nom

1. Allez dans **Main Menu → Settings → Desktop → Change Flipper Name**.
2. Saisissez le nouveau nom. L'en-tête du clavier indique `Leave empty for default`.
   - **2 à 8 caractères** ;
   - **uniquement des lettres latines et des chiffres** (`A–Z`, `a–z`, `0–9`). Tout autre caractère déclenche le
     message *« Please only enter letters and numbers! »*.
3. Sélectionnez **Save**.
4. Le message **`Name is set!`** / *« Your Flipper will be restarted on exit. »* apparaît.
5. Quittez Settings avec <kbd>BACK</kbd>. Le Flipper **redémarre automatiquement**.
6. Après le redémarrage, le nouveau nom s'affiche dans le Passport, dans **Settings → About** et en Bluetooth.

## Revenir au nom d'usine

1. Ouvrez **Settings → Desktop → Change Flipper Name**.
2. Supprimez tous les caractères et laissez le champ **vide**.
3. Sélectionnez **Save** et quittez Settings. Le Flipper redémarre avec son nom d'origine.

## Fonctionnement

- Le nom est enregistré dans **`/ext/dolphin/name.settings`** sur la carte SD :
  ```text
  Filetype: Flipper Name File
  Version: 1
  Name: MyFlip
  ```
- Au démarrage, le service `namechanger` attend la carte SD, lit ce fichier et applique le nom s'il est valide :
  en-tête et version corrects, 2 à 8 caractères, lettres et chiffres uniquement. Il redémarre ensuite les profils
  USB série et Bluetooth pour qu'ils utilisent le nouveau nom.
- Enregistrer un nom vide supprime le fichier.
- Le service ne s'exécute qu'au démarrage normal, pas dans l'updater ni en DFU.

Comme le nom réside sur la carte, il est conservé après les mises à jour. Il est perdu si vous formatez ou remplacez
la carte, ou si vous supprimez le fichier.

## Dépannage

| Problème | Solution |
|---|---|
| Le nom n'a pas changé | Avez-vous bien quitté Settings (c'est le redémarrage qui applique le nom) ? La carte SD est-elle insérée ? Le nom compte-t-il 2 à 8 lettres ou chiffres ? Un nom d'un seul caractère est enregistré mais ignoré au démarrage |
| L'application mobile ne se connecte plus | Le nom Bluetooth a changé. Oubliez le Flipper dans l'application **et** dans les réglages Bluetooth du téléphone, lancez **Settings → Bluetooth → Unpair All Devices** sur le Flipper, puis appairez à nouveau |
| Un fichier de nom copié depuis ailleurs est ignoré | Vérifiez l'en-tête `Flipper Name File`, `Version: 1` et les règles de nommage |
