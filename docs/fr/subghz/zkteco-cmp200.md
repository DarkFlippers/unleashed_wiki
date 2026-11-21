---
title: Télécommande de barrière ZKTeco CMP200
order: 210
author: gromovyna
original: [https://telegra.ph/ZKTeco-CMP200---Princeton-v-kitajskoj-obyortke-03-09, https://t.me/gromovyna/28, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md]
sources: [gromovyna, unleashed-src, unleashed-docs]
---
# ZKTeco CMP200 — du Princeton dans un emballage chinois

*Un court retour d'expérience de @gromovyna sur la télécommande des barrières ZKTeco, et comment la manipuler sous Unleashed.*

![Télécommande ZKTeco CMP200](/img/remote/a2cb668ab24d6625.png)

## Introduction

Il y a quelque temps, une clinique privée a ouvert près de chez gromovyna et a installé une barrière levante **ZKTeco**. Il était curieux, mais le trafic était faible et il n'y avait pas grand-chose pour justifier d'y creuser : l'affaire est donc partie dans la file d'attente mentale.

![Barrière ZKTeco (photo trouvée sur internet)](/img/remote/4cfaf6cbf4b21db6.png)

Puis, en sortant d'un rendez-vous, il a vu le porte-clés posé sur le comptoir d'accueil d'un étage supérieur, l'a photographié, a identifié le modèle avec Google Lens et l'a ajouté à sa liste d'achats. Avant d'acheter, il a demandé à MMX (xMasterX) — et il s'est avéré que le mystère était déjà résolu.

## Comment les Chinois ont emballé du Princeton

Tout est assez prosaïque, et c'est pris en charge dans **Unleashed** (grâce à MMX) depuis plus d'un an. Sous le capot, c'est un **Princeton** ordinaire avec un code de bouton de 8 bits — et les codes de boutons sont bien connus, **les mêmes pour toutes les télécommandes** :

| Paramètre | Valeur |
|---|---|
| Fréquence | **430.50 MHz** |
| Modulation | **AM650** |
| Bouton UP | `0x30` |
| Bouton STOP | `0x03` |
| Bouton DOWN | `0x0C` |

Et le meilleur : dans Unleashed, ces codes de boutons sont **déjà associés aux touches fléchées**, de sorte qu'un seul signal enregistré fait rapidement office de télécommande complète.

::: tip Unleashed
ZKTeco figure dans la liste des systèmes pris en charge par Unleashed sous la forme `ZKTeco 430.5MHz AM650 (24 bits, Static - Princeton based)` et possède sa propre entrée dans `Add Manually`. 430.50 MHz fait partie de la liste de fréquences par défaut.
:::

## Comment l'utiliser avec le Flipper

Comme le code est statique, une copie est identique à l'originale — les deux continuent de fonctionner, dans n'importe quel ordre.

### Option 1 — lire votre télécommande

1. `Main Menu → Sub-GHz → Read`.
2. <kbd>←</kbd> `Config` → **Frequency** `430.50`, **Modulation** `AM650`. Retour.
3. Appuyez sur un bouton de la CMP200 près du Flipper. Un signal `Princeton` apparaît.
4. <kbd>OK</kbd> → `Save`, nommez le fichier.
5. Ouvrez-le dans `Sub-GHz → Saved` → `Emulate`. <kbd>OK</kbd> émet le bouton capturé ; les touches fléchées émettent les autres boutons (UP / STOP / DOWN).

### Option 2 — créer une télécommande

1. `Main Menu → Sub-GHz → Add Manually → ZKTeco`.
2. Choisissez la bande `430.50 AM650` (elle est listée en premier pour cette entrée).
3. Nommez et enregistrez. Le Flipper crée une clé Princeton 24 bits avec un code aléatoire, TE 357 µs, bouton `0x30` (UP).

Une télécommande créée ainsi a son propre code — la barrière ne réagira qu'après son enregistrement dans le récepteur de la barrière (suivez le manuel de celle-ci). Pour agir comme une télécommande existante, lisez-la plutôt (option 1).

::: warning
Uniquement pour les barrières que vous possédez ou que vous administrez.
:::

## C'est tout ?

Pour l'instant — oui. Comme le note gromovyna, cette prise en charge est arrivée discrètement, et la plupart de la communauté ne l'a jamais remarquée ; il l'a testée et a partagé ses résultats.

## Dépannage

- **Rien n'est reçu** — vérifiez que la fréquence est bien 430.50 et non 433.92 ; contrôlez avec le [Frequency Analyzer](/fr/subghz/frequency-analyzer).
- **`Ignore Princeton` est sur ON** dans le `Config` de Read — les télécommandes basées sur Princeton comme celle-ci sont alors masquées ; désactivez ce filtre.
- **Les touches fléchées n'émettent rien** — ouvrez le signal depuis `Saved → Emulate` ; les boutons personnalisés ne fonctionnent que sur l'écran d'émission.

## Pages liées

- [Read](/fr/subghz/read) · [Add manually](/fr/subghz/add-manually) · [Systèmes pris en charge](/fr/subghz/supported-systems)
- [Codes tournants](/fr/subghz/rolling-codes) — les boutons personnalisés expliqués
