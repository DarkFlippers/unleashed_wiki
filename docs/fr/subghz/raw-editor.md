---
title: Sub-GHz RAW Edit
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/subghz_raw_editor, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/Lechnio/SubGHz-RAW-Edit]
sources: [unleashed-src, unleashed-readme]
---
# Sub-GHz RAW Edit

**Sub-GHz RAW Edit** (par Lechnio, v1.9) est un petit éditeur de forme d'onde fonctionnant sur l'appareil, destiné aux captures RAW `.sub`. Un enregistrement [Read RAW](/fr/subghz/read-raw) contient généralement plusieurs secondes de bruit autour de la courte salve qui vous intéresse. Avec RAW Edit, vous localisez le vrai signal, vous le marquez et vous n'enregistrez que cette portion — et vous pouvez aussi fusionner plusieurs fichiers, en découper des morceaux et décoder une sélection avec les décodeurs Sub-GHz du firmware.

::: tip Unleashed
RAW Edit est livré avec Unleashed en tant qu'application système, et l'application Sub-GHz l'ouvre directement : `Sub-GHz → Read RAW` (ou `Saved`) → ouvrir un fichier RAW → <kbd>→</kbd> `More` → `Edit`. L'entrée `Edit` n'apparaît que si RAW Edit est installé. En quittant l'éditeur, vous revenez dans Sub-GHz.
:::

**Quand l'utiliser :** rogner une longue capture RAW avant de la partager ou de l'émettre, séparer un enregistrement en plusieurs boutons distincts, coller plusieurs captures bout à bout, ou découvrir quel protocole se cache dans un fichier RAW.

## Menu principal

`Main Menu → Apps → Sub-GHz → Sub-GHz RAW Edit` :

- `Select .sub file` — ouvrir un fichier de `/ext/subghz` dans l'éditeur
- `Merge .sub files` — assembler plusieurs fichiers en un seul
- `Config` — options de chargement et de fusion
- `About` — version et lien vers le projet

Outre les fichiers RAW, l'application peut charger tout signal que le firmware sait encoder (il est converti en RAW via l'encodeur interne). Pour les protocoles à boutons personnalisés, elle propose d'abord un sélecteur de bouton.

## L'éditeur

L'écran affiche la forme d'onde avec une barre de vue d'ensemble en haut, et deux lignes en dessous : `View:` (zoom) et `Marked:` (longueur de la sélection A..B). La plage sélectionnée est mise en évidence par une ligne pointillée ; de petites marques signalent qu'il y a encore du signal au-delà du bord de l'écran.

| Bouton | Action |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | déplacer le marqueur actif (A ou B) ; maintenir pour aller plus vite |
| <kbd>↑</kbd> / <kbd>↓</kbd> | zoomer / dézoomer |
| <kbd>OK</kbd> | basculer le marqueur actif entre A et B |
| maintien de <kbd>OK</kbd> | ouvrir le menu d'actions |
| <kbd>Back</kbd> | fermer l'éditeur |

Le menu d'actions (<kbd>↑</kbd> / <kbd>↓</kbd>, <kbd>OK</kbd> pour exécuter, <kbd>Back</kbd> pour fermer) :

- **Save** — écrire uniquement la plage A..B dans un nouveau fichier RAW. Le nom proposé est `<nom>_edit1`, `_edit2`, … Enregistrer sous un nom existant demande `Name exists, overwrite?` ; le fichier ouvert lui-même n'est jamais écrasé.
- **Decode** — décoder la plage A..B avec les décodeurs Sub-GHz du firmware, regrouper les paquets identiques (`Decoded: N`) et enregistrer celle choisie comme fichier-clé, nommé par défaut d'après le protocole et le constructeur (par exemple `KeeLoq_Verex`). `No known protocol` signifie que rien n'a été décodé.
- **Cut** — supprimer la plage A..B du signal (refusé si cela laisserait le signal vide).
- **Undo** — annuler la dernière coupe (barré quand il n'y a rien à annuler).

## Rogner une capture — pas à pas

1. Enregistrez la télécommande dans [Read RAW](/fr/subghz/read-raw) et sauvegardez le fichier.
2. Ouvrez-le dans RAW Edit (via `More → Edit` ou `Select .sub file`).
3. Dézoomez avec <kbd>↓</kbd> pour voir où se situent les salves.
4. Amenez le marqueur **A** juste avant la salve avec <kbd>←</kbd>/<kbd>→</kbd>, appuyez sur <kbd>OK</kbd>, puis amenez le marqueur **B** juste après.
5. Maintenez <kbd>OK</kbd> → `Save`, acceptez ou modifiez le nom.
6. Testez le fichier enregistré depuis `Sub-GHz → Saved`.

## Fusionner des fichiers

1. `Merge .sub files` → choisissez un fichier ; la boîte de dialogue affiche `Added N file(s)` et le nombre d'échantillons. Choisissez `Add more` ou `Done`.
2. Tous les fichiers doivent être sur la même fréquence, sinon vous obtenez `Frequency mismatch`.
3. Le résultat s'ouvre dans l'éditeur sous le nom `merged` ; enregistrez-le depuis le menu d'actions.

## Config

| Entrée | Rôle |
|---|---|
| Normalize jitter | `OFF`/`ON` — nettoyer la gigue et la dérive temporelles au chargement |
| Merge gap | silence inséré entre les fichiers fusionnés, 0–1000 ms (100 par défaut) ; <kbd>OK</kbd> ouvre une saisie numérique |
| Repeat | répéter chaque signal chargé / fusionné 1 à 64 fois |

## Limites et dépannage

- Un fichier contient jusqu'à **24 000 échantillons** ; la RAM disponible peut abaisser cette limite. `Out of memory` / `Not enough free RAM to load this capture` — redémarrez le Flipper et ouvrez l'application en premier.
- `Unsupported protocol or file is empty` — le fichier n'est pas un signal que le firmware sait encoder.
- `Nothing in A..B` / `Range too small` — écartez davantage les marqueurs.
- Les longues pauses conservent leur durée réelle dans le fichier enregistré.

## Pages liées

- [Read RAW](/fr/subghz/read-raw) · [Format de fichier](/fr/subghz/file-format)
- [Remote Analyzer](/fr/subghz/remote-analyzer)
