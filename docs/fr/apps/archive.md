---
title: Archive (navigateur de fichiers)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Archive (navigateur de fichiers)

**Archive** est le navigateur de fichiers du Flipper. Il liste les clés, cartes, télécommandes et scripts que vous
avez enregistrés, permet de les lancer immédiatement et assure la gestion de fichiers de base : épingler dans les
favoris, renommer, copier, déplacer, créer des dossiers et supprimer.

**Pour l'ouvrir :** depuis le bureau, appuyez sur <kbd>↓</kbd>.

![Archive sur l'onglet Sub-GHz : un dossier Garage et des signaux .sub enregistrés, Barrier étant sélectionné](/screens/apps/archive.png)

## Onglets

Appuyez sur <kbd>←</kbd> / <kbd>→</kbd> pour changer d'onglet. Chaque onglet affiche un dossier, filtré par type de
fichier :

| Onglet | Dossier | Fichiers affichés |
|---|---|---|
| Favorites | vos fichiers épinglés | tout ce que vous avez épinglé (`/ext/favorites.txt`) |
| Sub-GHz | `/ext/subghz` | `.sub` |
| SubRem | `/ext/subghz_remote` | `.txt` (configurations [Sub-GHz Remote](/fr/subghz/remote)) |
| RFID LF | `/ext/lfrfid` | `.rfid` et dumps T5577 |
| NFC | `/ext/nfc` | `.nfc` |
| Infrared | `/ext/infrared` | `.ir` |
| iButton | `/ext/ibutton` | `.ibtn` |
| Bad USB | `/ext/badusb` | `.txt` |
| Phone | `/ext/phonebook` | `.phone` (répertoire [SIM800](/fr/gpio/sim800)) |
| U2F | interne | l'entrée de l'application U2F |
| Apps | `/ext/apps` | `.fap` et `.js` |
| Internal | mémoire flash interne | tout (uniquement avec le mode Debug activé) |
| Browser | toute la carte SD | tout |

L'Archive s'ouvre sur **Favorites**.

::: tip Unleashed
Unleashed ajoute l'onglet **SubRem** pour les configurations Sub-GHz Remote, l'onglet **Phone** pour le répertoire
SIM800 (une entrée `.phone` s'ouvre directement dans l'application SIM800), affiche les dumps T5577 à côté des clés
dans **RFID LF**, et liste les scripts `.js` dans **Apps**.
:::

## Boutons dans la liste

| Bouton | Action |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | se déplacer dans la liste (maintenez pour défiler plus vite) |
| <kbd>←</kbd> / <kbd>→</kbd> | onglet précédent / suivant |
| <kbd>OK</kbd> sur un fichier | ouvrir son menu |
| <kbd>OK</kbd> sur un dossier | entrer dans le dossier |
| maintenir <kbd>OK</kbd> sur un dossier | ouvrir le menu du dossier |
| <kbd>OK</kbd> dans Favorites | lancer le fichier immédiatement |
| maintenir <kbd>OK</kbd> dans Favorites | ouvrir le menu |
| maintenir <kbd>OK</kbd> dans un dossier vide | ouvrir le menu (Paste / NewDir) |
| <kbd>Back</kbd> | remonter d'un dossier, ou quitter |

## Le menu du fichier : Actions et Manage

Le menu comporte deux pages. Son titre indique laquelle est ouverte : **Actions** ou **Manage**. Appuyez sur
<kbd>←</kbd> ou <kbd>→</kbd> dans le menu pour passer de l'une à l'autre (pas dans l'onglet Favorites).
<kbd>↑</kbd> / <kbd>↓</kbd> sélectionnent une entrée, <kbd>OK</kbd> l'exécute, <kbd>Back</kbd> ferme le menu.

**Actions** (pour un fichier que le firmware sait ouvrir) :

- **Run** : ouvrir le fichier dans son application (émuler une clé, émettre un signal, exécuter un script...).
- **Pin** / **Unpin** : ajouter aux favoris ou en retirer.
- **Info** : nom et taille du fichier.
- **Show** : afficher le fichier en texte (pour les formats texte).

Pour un type de fichier inconnu, Actions ne propose que **Info** et, pour les fichiers texte, **Show**.

**Manage :**

- **Cut** / **Copy**, puis **Paste** dans le dossier de destination.
- **NewDir** : créer un dossier.
- **Rename** : saisir un nouveau nom.
- **Delete** : demande d'abord confirmation.

Dans l'onglet **Favorites**, le menu propose **Run**, **Unpin**, **Show** (le cas échéant) et **Move**. Move permet de
réordonner les favoris : appuyez sur <kbd>↑</kbd> / <kbd>↓</kbd> pour déplacer l'entrée et sur <kbd>OK</kbd> pour
enregistrer la nouvelle position (<kbd>Back</kbd> annule).

## Tâches courantes

### Épingler un fichier dans les favoris

1. Bureau → <kbd>↓</kbd> pour ouvrir l'Archive.
2. Allez dans le bon onglet avec <kbd>←</kbd> / <kbd>→</kbd> et sélectionnez le fichier.
3. Appuyez sur <kbd>OK</kbd> → **Pin**. Le fichier apparaît désormais dans l'onglet Favorites.

### Renommer une clé ou un signal enregistré

1. Sélectionnez le fichier et appuyez sur <kbd>OK</kbd>.
2. Appuyez sur <kbd>→</kbd> pour basculer le menu sur **Manage**.
3. Choisissez **Rename**, saisissez le nom, validez.

### Supprimer des fichiers pour libérer de l'espace

1. Sélectionnez le fichier, <kbd>OK</kbd>, <kbd>→</kbd> vers **Manage**.
2. Choisissez **Delete** et confirmez.

Pour nettoyer un dossier entier, utilisez l'onglet **Browser** : sélectionnez le dossier, maintenez <kbd>OK</kbd>,
**Manage → Delete**.

### Déplacer un fichier dans un autre dossier

1. Sélectionnez le fichier, <kbd>OK</kbd>, **Manage → Cut**.
2. Allez dans le dossier de destination (l'onglet **Browser** donne accès à tous les dossiers de la carte).
3. Appuyez sur <kbd>OK</kbd> sur n'importe quel fichier (ou maintenez <kbd>OK</kbd> dans un dossier vide) →
   **Paste**.

## Dépannage

- **« Empty »** signifie que le dossier ne contient aucun fichier du type de cet onglet. Vérifiez l'extension du
  fichier : un fichier `.ir` placé dans `/ext/nfc` n'apparaîtra dans aucun des deux onglets, mais l'onglet Browser
  l'affiche.
- **L'onglet Internal est absent** : il n'est visible que lorsque `Settings → System → Debug` est sur ON.
- **Un favori a disparu** : les favoris dont le fichier n'existe plus (déplacé, renommé ou supprimé en dehors de
  l'Archive) sont retirés de la liste. Épinglez de nouveau le fichier à son nouvel emplacement.
- **Delete** demande toujours `Delete <name>?` avec les boutons **Cancel** / **Delete** : rien n'est supprimé par un
  appui malencontreux.

## Pages liées

- [Carte microSD](/fr/start/sd-card)
- [Applications sur la carte SD](/fr/apps/sd-card-apps)
- [Bureau](/fr/start/desktop)
