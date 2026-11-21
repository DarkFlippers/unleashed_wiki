---
title: Security+ PIN
order: 180
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/secplus_pin, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Security+ PIN

**Security+ PIN** (par @xMasterX) travaille sur un signal capturé de **clavier Security+ 2.0** — le paquet de 86 bits émis par les claviers sans fil Chamberlain / LiftMaster. Le code PIN du clavier se trouve à l'intérieur de ce paquet. L'application permet de saisir un PIN à la main ou de balayer `0000`–`9999`, émet chaque candidat, puis réécrit le PIN dans le fichier une fois le bon trouvé.

::: tip Unleashed
Security+ 2.0 Keypad (86 bits, 315 / 390 / 868 MHz) est décodé par l'application Sub-GHz d'Unleashed, et cette application système intégrée édite son PIN. Les télécommandes Security+ 2.0 ordinaires (62 bits) ne sont pas des paquets de clavier et sont refusées.
:::

::: warning
Uniquement pour votre propre motorisation de porte de garage et son clavier.
:::

## Avant de commencer

1. Capturez votre clavier avec `Sub-GHz → Read` sur sa fréquence (voir [Read](/fr/subghz/read)) et enregistrez-le. Le fichier enregistré doit indiquer `Security+ 2.0` avec `Bit: 86`.
2. Le fichier se trouve dans `/ext/subghz/`.

## Utiliser l'application

1. Ouvrez `Main Menu → Apps → Sub-GHz → Security+ PIN`.
2. Choisissez `Open .sub file` et sélectionnez la capture du clavier. Au chargement, l'état affiche la fréquence et `ready` (par exemple `315MHz  ready`). Si le fichier contient déjà un champ `Pin`, celui-ci est affiché.
3. Les quatre chiffres du PIN sont à l'écran, un cadre entourant le chiffre actif :
   - <kbd>←</kbd> / <kbd>→</kbd> — se déplacer entre les chiffres
   - <kbd>↑</kbd> / <kbd>↓</kbd> — modifier le PIN
   - <kbd>OK</kbd> (`Send`) — émettre le PIN courant (`Sending 1234...` → `Sent 1234`)
   - maintien de <kbd>OK</kbd> — **balayage** : émettre tous les PIN à partir du PIN courant ; une barre de progression affiche `N of 9999`. Un appui court sur <kbd>OK</kbd> ou sur <kbd>←</kbd> (Back) l'interrompt avec `Stopped at NNNN`
   - maintien de <kbd>←</kbd> — **enregistrer** le PIN courant dans le fichier (`Saved PIN NNNN`)
   - <kbd>Back</kbd> — retour au menu

La ligne d'aide à l'écran résume tout cela : `hold OK sweep   < save`.

L'enregistrement met à jour le fichier ouvert sur place : il écrit les champs `Pin`, `Key` et `Secplus_packet_1`. Le fichier peut ensuite être émis normalement depuis `Sub-GHz → Saved`.

## Messages

| Message | Signification |
|---|---|
| `Not Security+ 2.0: …` | le fichier correspond à un autre protocole |
| `Not an 86-bit keypad` | une télécommande Security+ 2.0, pas un paquet de clavier |
| `Missing packet 1` / `No Key value` | capture incomplète — relisez le clavier |
| `Unsupported preset …` / `Bad custom preset` | le preset du fichier ne peut pas être utilisé |
| `NNNMHz TX blocked` / `TX blocked, sweep stopped` | l'émission sur cette fréquence n'est pas autorisée (voir [Fréquences](/fr/subghz/frequencies)) |
| `TX failed` | la radio n'a pas réussi à émettre |

## Dépannage

- **Le balayage est lent** — chaque PIN est une émission séparée suivie d'une courte pause ; un balayage complet prend beaucoup de temps. Démarrez-le depuis une valeur plausible et arrêtez-le dès que la porte réagit.
- **La porte a réagi mais vous avez manqué le PIN** — le balayage s'arrête sur le numéro affiché ; revenez en arrière avec <kbd>↓</kbd> et émettez des PIN un par un avec <kbd>OK</kbd> pour confirmer, puis maintenez <kbd>←</kbd> pour enregistrer.
- **Mauvais fichier refusé** — capturez le clavier lui-même, pas une télécommande portative.

## Pages liées

- [Read](/fr/subghz/read) · [Systèmes pris en charge](/fr/subghz/supported-systems)
- [Codes tournants](/fr/subghz/rolling-codes)
