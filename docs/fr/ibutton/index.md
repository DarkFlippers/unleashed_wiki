---
title: iButton
original: [https://docs.flipper.net/zero/ibutton, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# iButton

Une clé iButton (« touch memory », souvent appelée *таблетка*, « pastille », dans les pays de la CEI) est une clé
logée dans un petit boîtier en acier que l’on présente au contact d’un lecteur. La plupart parlent le protocole
Dallas **1-Wire** ; les interphones utilisent aussi des clés **Cyfral** et **Metakom**. Le Flipper Zero sait lire,
enregistrer, émuler et écrire ces clés.

## Matériel

Le module iButton est une plage de contact à trois pogo pins à ressort, montée sur le PCB iButton.

- Les deux broches extérieures portent les données (reliées à la **broche GPIO 17**), celle du milieu est la **masse**.
- **Lecture / écriture d’une clé** : la clé touche la **partie plate** de la plage — broche de données de gauche +
  broche de masse du milieu.
- **Émulation vers un lecteur** : la **partie saillante** de la plage touche le lecteur — broche de données de droite
  + masse du milieu.
- Si la masse n’arrive pas à toucher la couronne du lecteur, utilisez deux fils : GPIO **17** (données) et
  GPIO **8, 11 ou 18** (masse).

## Menu principal

`Main Menu → iButton` :

![Le menu iButton avec Read, Saved, Add Manually et Settings](/screens/ibutton/menu.png)

| Élément | Rôle | Page |
|---|---|---|
| **Read** | Détecte le type de clé et lit son ID (et la mémoire pour DS1992/1996/1971) | [Lecture](/fr/ibutton/read) |
| **Saved** | Parcourt `/ext/ibutton/` — émuler, écrire, modifier, renommer, supprimer | [Lecture](/fr/ibutton/read), [Écriture](/fr/ibutton/write) |
| **Add Manually** | Crée une clé à partir du protocole + de l’ID en hexadécimal | [Ajout manuel](/fr/ibutton/add-manually) |
| **Settings** | **Write Blanks** — les types de supports vierges autorisés à l’écriture | [Écriture](/fr/ibutton/write) |

::: tip Unleashed
Par rapport à la documentation officielle, Unleashed ajoute une page **Settings → Write Blanks** (RW1990.1, RW1990.2,
TM2004, TM01x), affiche quel support vierge est tenté pendant une écriture et lequel l’a acceptée, écrit les clés
**Cyfral et Metakom** sur des supports **TM01x** et prend en charge le **DS1420**. Le ReadMe mentionne également un
plugin iButton Fuzzer.
:::

## Pages de cette section

- [Lecture des clés](/fr/ibutton/read) — lire, enregistrer, émuler, erreurs de CRC.
- [Écriture sur supports vierges](/fr/ibutton/write) — RW1990, TM2004, TM01x ; Write ID contre Full Write on Same Type.
- [Ajout manuel](/fr/ibutton/add-manually) — créer des clés à partir d’un ID.
- [Protocoles pris en charge](/fr/ibutton/protocols) — Dallas DS1990/1992/1996/1971/1420, 1-Wire générique, Cyfral, Metakom.
- [Fuzzer](/fr/ibutton/fuzzer) — ce que le firmware fournit pour l’application de fuzzing iButton.
- [Format de fichier](/fr/ibutton/file-format) — les fichiers `.ibtn`.

## Fichiers

| Chemin | Contenu |
|---|---|
| `/ext/ibutton/*.ibtn` | Clés enregistrées (préfixe de nom par défaut `iBtn`) |
| `/ext/ibutton/.ibutton.settings` | Réglage Write Blanks |

::: warning
Ne copiez et n’émulez que les clés qui vous appartiennent ou que vous êtes autorisé à tester.
:::
