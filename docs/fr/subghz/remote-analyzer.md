---
title: Remote Analyzer
order: 160
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/remote_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Remote Analyzer

**Remote Analyzer** (par @xMasterX) décode une télécommande à la fois sur le CC1101 interne et affiche tous les champs qu'il parvient à déterminer. Contrairement à `Sub-GHz → Read`, il ne conserve **aucun historique** — seul le dernier signal est à l'écran — et il **n'enregistre jamais** de fichier `.sub`. C'est un outil pour répondre à la question « qu'est-ce que c'est que cette télécommande ? ».

::: tip Unleashed
Remote Analyzer est une application système intégrée d'Unleashed. En plus de tous les protocoles connus de l'application Sub-GHz, il possède ses propres protocoles décodés uniquement : **Crypt**, **Crypt Lite**, **Hormann BiSecur**, **KCE6xxx**, **Life Fido**, **Nero Intro II** et **PC4**.
:::

**Quand l'utiliser :** vous voulez identifier rapidement une télécommande inconnue, voir s'il s'agit d'un code fixe ou tournant, ou examiner une télécommande que l'application principale ne décode pas. Pour capturer et rejouer, utilisez [Read](/fr/subghz/read) ou [Read RAW](/fr/subghz/read-raw).

## Menu principal

`Main Menu → Apps → Sub-GHz → Remote Analyzer` :

- `Read` — décodage en direct
- `Decode RAW File` — passer une capture RAW enregistrée dans les mêmes décodeurs
- `Frequency Analyzer` — trouver la fréquence de la télécommande
- `How to use` — le manuel intégré

## Lire une télécommande

1. Ouvrez `Read`. L'écran affiche `Waiting for a signal`.
2. Appuyez sur <kbd>←</kbd> (`Config`) et réglez **Frequency** et **Modulation** (ou activez **Hopping**).
3. Tenez la télécommande près du Flipper et appuyez sur son bouton.
4. La lecture apparaît :
   - l'icône en haut à gauche indique un code **fixe** ou **tournant** ;
   - la ligne sous le nom du protocole et le nombre de bits indique si l'application Sub-GHz connaît aussi ce protocole, ou s'il est **analyzer only** (reconnu par l'analyseur seulement) ;
   - `xN` en haut à droite compte le nombre de fois où ce code a été reçu ;
   - la barre sous la ligne représente la puissance du signal.
5. <kbd>↑</kbd> / <kbd>↓</kbd> font défiler une lecture qui ne tient pas à l'écran, <kbd>→</kbd> (`Reset`) l'effacent.

**La LED :** violet — en écoute ; jaune — quelque chose passe sur l'air mais rien ne l'a décodé ; vert — un code est passé.

## Config

| Entrée | Rôle |
|---|---|
| Frequency | fréquence de réception (ignorée quand Hopping est actif) |
| Modulation | preset : AM270, AM650, FM238, FM476, FM12K et tous les presets personnalisés |
| Hopping | `OFF` ou un niveau de `-90dB` à `-40dB` |
| Sound | jouer le signal démodulé sur le haut-parleur |
| Mod. sweep | essayer d'autres modulations quand rien ne se décode |
| Notify | vibrer une fois sur un code différent du précédent |
| Reset to default | restaurer les valeurs par défaut |

**Hopping.** Avec un niveau défini, l'application parcourt **315, 390, 430.5, 433.92, 434.42 et 868.35 MHz** tant que l'air est calme, et s'arrête sur la première bande où la porteuse atteint ce niveau. Un décodage maintient la bande pendant deux secondes avant que le balayage ne reprenne. Choisir une fréquence dans le Frequency Analyzer désactive le hopping. Ce niveau est aussi ce que le balayage de modulation et la LED considèrent comme « un signal », il compte donc même avec Hopping sur `OFF`.

**Mod. sweep.** Quand une télécommande émet manifestement mais que rien ne la décode, l'application parcourt les autres modulations, environ une seconde chacune. Un `~` à côté de la modulation signifie qu'elle cherche encore — **gardez le bouton de la télécommande enfoncé**. Le premier décodage réussi fixe la modulation et le `~` disparaît ; après deux secondes sans aucun décodage, le balayage reprend à partir de là. `Unknown remote` signifie qu'un tour complet n'a rien trouvé ; il recommence tant que le bouton est maintenu.

**Notify.** Une télécommande maintenue répète un seul code, ce qui ne fait donc que clignoter la LED ; un code nouveau et différent déclenche aussi la vibration.

## Decode RAW File

1. Choisissez `Decode RAW File` et sélectionnez un `.sub` RAW dans `/ext/subghz`.
2. Une barre de progression indique où l'on en est dans le fichier.
3. Chaque code distinct trouvé est listé ; appuyez sur <kbd>OK</kbd> sur l'un d'eux pour la lecture complète.

Seule une capture RAW contient des échantillons — un fichier-clé enregistré est refusé. Si rien n'est décodé (ou si le fichier est refusé), un bip d'erreur retentit et la LED reste rouge.

## Frequency Analyzer

Maintenez le bouton de la télécommande près du Flipper, puis **maintenez** <kbd>OK</kbd> pour reporter la fréquence détectée vers `Read`. <kbd>←</kbd> / <kbd>→</kbd> déplacent le seuil de déclenchement. Il fonctionne comme [l'analyseur de l'application principale](/fr/subghz/frequency-analyzer).

## Dépannage

- **Toujours `Waiting for a signal`** — mauvaise fréquence ; lancez le Frequency Analyzer ou activez le Hopping.
- **LED jaune mais aucun décodage** — activez `Mod. sweep` et maintenez le bouton, ou enregistrez le signal avec [Read RAW](/fr/subghz/read-raw) et essayez `Decode RAW File`.
- **Protocole reconnu par l'analyseur seulement** — l'application Sub-GHz principale ne peut ni l'enregistrer ni l'émettre ; Remote Analyzer se contente de l'identifier.
- **Vous voulez enregistrer le signal** — utilisez [Read](/fr/subghz/read) ; cette application n'écrit pas de fichiers.

## Pages liées

- [Read](/fr/subghz/read) · [Read RAW](/fr/subghz/read-raw) · [Frequency Analyzer](/fr/subghz/frequency-analyzer)
- [Systèmes pris en charge](/fr/subghz/supported-systems)
