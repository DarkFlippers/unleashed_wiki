---
title: Sub-GHz RAW Edit
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/subghz_raw_editor, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/Lechnio/SubGHz-RAW-Edit]
sources: [unleashed-src, unleashed-readme]
---
# Sub-GHz RAW Edit

**Sub-GHz RAW Edit** (par Lechnio) est un petit éditeur de forme d'onde fonctionnant sur l'appareil, destiné aux captures RAW `.sub`. Un enregistrement [Read RAW](/fr/subghz/read-raw) contient généralement plusieurs secondes de bruit autour de la courte salve qui vous intéresse. Avec RAW Edit, vous localisez le vrai signal, vous le marquez et vous n'enregistrez que cette portion — et vous pouvez aussi fusionner plusieurs fichiers, en découper des morceaux et décoder une sélection avec les décodeurs Sub-GHz du firmware.

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

Le menu d'actions (<kbd>↑</kbd> / <kbd>↓</kbd>, <kbd>OK</kbd> pour exécuter, <kbd>Back</kbd> pour fermer) s'affiche à gauche, accompagné à côté d'un panneau d'information en lecture seule indiquant le nombre d'échantillons de A..B, le `TE` et le codage en ligne détecté (`PWM`, `PPM`, `Manchester`, `NRZ` ou `1:1`) :

- **Save** — écrire uniquement la plage A..B dans un nouveau fichier RAW. Le nom proposé est `<nom>_edit1`, `_edit2`, … Enregistrer sous un nom existant demande `Name exists, overwrite?` ; le fichier ouvert lui-même n'est jamais écrasé.
- **Decode** — décoder la plage A..B avec les décodeurs Sub-GHz du firmware (en essayant chaque constructeur sur chaque trame KeeLoq ; ignore BinRAW), regrouper les trames identiques (`Decoded: N`) et enregistrer celle choisie comme fichier-clé, nommé par défaut d'après le protocole et le constructeur (par exemple `KeeLoq_Verex`). Chaque entrée décodée dispose aussi d'un bouton **Locate** qui cale A..B sur sa trame (la première en cas de répétition). `No known protocol` signifie que rien n'a été décodé.
- **Cut** / **Copy** / **Paste** — appuyez sur <kbd>←</kbd> / <kbd>→</kbd> sur `Cut` pour basculer entre **Cut** (supprimer A..B et le placer dans le presse-papiers ; refusé si cela laisserait le signal vide), **Copy** (copier A..B dans le fichier presse-papiers) et **Paste** (insérer le presse-papiers au niveau du marqueur actif et le sélectionner).
- **Undo** — historique sur carte SD des **32** dernières coupes et collages (ne consomme pas de RAM). S'il y a plus d'une modification, il les liste de la plus récente à la plus ancienne avec le nombre d'échantillons et les positions, puis revient à l'état précédant celle que vous choisissez. Barré quand il n'y a rien à annuler.

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

Une ligne en lecture seule en bas de `Config` indique également si les boutons personnalisés et la conservation du compteur tournant sont disponibles dans la version actuelle du firmware.

## Limites et dépannage

- **Aucune limite de longueur (v2.0) :** les signaux et les fusions sont conservés dans un fichier de travail sur la carte SD, tandis que la RAM ne garde qu'une fenêtre glissante de la capture (jusqu'à ~38 000 échantillons après un démarrage à froid), laissant de la place pour Decode et Save. Pousser le marqueur A ou B au-delà du bord de la fenêtre la fait glisser d'un quart plus loin ; le dézoom s'arrête à la limite de la fenêtre avec `No RAM to zoom out`.
- **Invite `Low RAM`** — affichée lorsque la RAM libre peut contenir moins de 15 000 échantillons d'un signal plus grand ; propose `Reboot` ou `Continue`. `Decode` vérifie aussi qu'il reste ~8 Ko de RAM libre et signale `Low memory` au lieu de planter.
- `Unsupported protocol or file is empty` — le fichier n'est pas un signal que le firmware sait encoder.
- `Nothing in A..B` / `Range too small` — écartez davantage les marqueurs.
- Les longues pauses conservent leur durée réelle dans le fichier enregistré.

## Pages liées

- [Read RAW](/fr/subghz/read-raw) · [Format de fichier](/fr/subghz/file-format)
- [Remote Analyzer](/fr/subghz/remote-analyzer)
