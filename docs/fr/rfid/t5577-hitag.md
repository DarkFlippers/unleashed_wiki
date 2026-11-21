---
title: T5577 et Hitag Micro (par @gromovyna)
order: 60
author: gromovyna
original: [https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577]
sources: [gromovyna, unleashed-src]
---
# Écriture Hitag Micro, ergonomie de l’écriture et effacement du T5577

D’après l’article de @gromovyna *« Aperçu des fonctions LF (RFID) que j’ai préparées pour Unleashed »* (juin 2026),
mis à jour avec l’apparence actuelle de ces fonctions dans le firmware.

![](/img/remote/2e30c69f7eded901.png)

## Introduction

Après une longue pause, @gromovyna est revenu à la recherche et s’est penché sur les supports vierges **H5.5** vendus
par *iKey*. Le Discord d’Iceman avait déjà établi que le H5.5 est le même clone chinois de **Hitag Micro**, sur lequel
iKey a simplement posé son propre mot de passe. La situation côté dénominations :

| Nom | De quoi il s’agit |
|---|---|
| **8265 / H5** | la puce avec le mot de passe par défaut |
| **H5.5** | la même puce avec le mot de passe **iKey** |
| **8210** | la même puce avec le mot de passe du cloneur chinois **FURUI** |

Il a retrouvé le mot de passe iKey (au deuxième jour d’essais), l’a partagé avec la communauté et a
[mis à jour les notes Proxmark3 sur les cartes magiques](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md#id8265).
Il a ensuite implémenté ces fonctions pour le Flipper — sous forme de pull requests vers **Unleashed**, en espérant les
porter aussi dans l’OFW dès que celui-ci redeviendra activement développé.

Les mots de passe que le firmware utilise pour les trois variantes :

| Variante | Mot de passe |
|---|---|
| 8265 / H5 | `00000000` |
| 8210 | `9AC4999C` |
| H5.5 | `496B0E59` |

## Prise en charge du Hitag Micro

Le Flipper sait désormais **écrire** sur les clones Hitag Micro — **8265/H5**, **H5.5** et **8210** — sous forme de
clés EM4100 (la puce est configurée pour émettre la trame EM4100 d’elle-même, en mode « transponder talks first »).

Limites de l’architecture actuelle :
- le matériel LF du Flipper ne fait qu’**émettre** pendant une écriture, la réussite ne peut donc être vérifiée qu’en
  **relisant le tag** ;
- beaucoup de temps a été consacré au calibrage des constantes, mais l’écriture de ces puces exige toujours un **bon
  positionnement**.

### Pourquoi l’écriture est devenue plus lente

L’ajout de cette prise en charge a dégradé l’ergonomie, car la logique d’écriture est maintenant une boucle qui essaie,
l’un après l’autre :

- le **T5577**
- l’**EM4305**
- le **Hitag Micro** — et là, trois variantes, une par mot de passe d’usine connu ; ces opérations sont en plus
  intrinsèquement plus lentes

Pour le Hitag Micro, le Flipper essaie le mot de passe de chaque variante connue à tour de rôle, afin de ne pas avoir à
le demander à l’utilisateur — le lui demander ruinerait l’une des idées maîtresses du Flipper Zero : la simplicité. Le
prix à payer, c’est la vitesse d’écriture. Un mauvais mot de passe est simplement rejeté par la puce et laisse le tag
intact ; la variante dont la relecture est correcte est celle qui est présente.

Vu de l’utilisateur, c’était catastrophique — comme si rien ne se passait — et on ne savait pas avec quel protocole le
tag avait été écrit. D’où la fonction suivante.

## Ergonomie : avec quoi écrit-on, qu’a-t-on écrit ?

Pendant une écriture, l’écran affiche désormais **quelle puce est en cours d’essai** :

![Écriture en cours](/img/remote/34b72cbd8417d74e.png)

Techniquement, ce n’est pas un protocole mais le nom commercial de la variante de support — mais l’idée est là. Après
l’écriture, le résultat est affiché avec le même niveau de détail :

![Résultat de l’écriture](/img/remote/3ca59457a78dad5b.png)

::: tip Dans le firmware actuel
- Les puces à essayer sont configurables : `125 kHz RFID → Settings → Write Chips` — T5577, EM4305, 8265, 8210, H5.5
  (toutes sur ON) et **8268** (ID8268 / puce magique Hitag S, OFF par défaut). Désactivez ce que vous n’utilisez pas
  pour accélérer les écritures.
- La cible 8268 n’écrit que de l’EM4100 en RF/64 et doit être activée explicitement, car sur un véritable Hitag S elle
  écraserait des données utilisateur.
- Le format de l’écran d’écriture est `[Protocol]`, nom de fichier, `(chip)` ; **Success!** affiche la puce qui a
  accepté les données. Détails : [Écriture sur supports vierges](/fr/rfid/write).
:::

## Remettre un T5577 à l’état d’usine

Une fonction qui manquait depuis longtemps à @gromovyna sur le Flipper : réinitialiser un T5577 à l’état vierge. Une
première tentative pour l’ajouter à Unleashed avait été bloquée ; plus tard, des fonctions comme *clear T5577 password*
ont été fusionnées avec les mêmes problèmes d’architecture, de sorte qu’un vrai correctif devrait être global.

Comportement (aligné sur le Proxmark3) :

- avant de démarrer, vous êtes averti que **toutes les données seront effacées** et que le tag **ne sera plus lisible
  par Read** tant que vous n’y aurez pas écrit de nouvelles données ;
- l’effacement **ne supprime pas de mot de passe** — si le tag est protégé, supprimez d’abord le mot de passe avec la
  fonction dédiée ;
- une barre de progression est affichée. L’essentiel du temps n’est pas consacré à l’effacement lui-même mais à sa
  **vérification** : à cause de l’API LF, le Flipper contrôle que le tag est vierge en essayant de le lire et en
  attendant que cette lecture échoue ;
- à la fin, vous obtenez un message de réussite ou d’échec.

![Avertissement avant effacement](/img/remote/f5ed0aa91bfcae98.png)

![Effacement en cours](/img/remote/153b85d1fede96d9.png)

![Vérification](/img/remote/0f2f4e240a35940d.png)

![Réussite](/img/remote/312494f343dd8b21.png)

::: tip Unleashed — où la trouver aujourd’hui
Dans l’article, l’effacement se trouvait dans `125 kHz RFID → Extra Actions`. Dans le firmware actuel, il a été déplacé
(avec Clear Password) vers l’application **T5577** intégrée : `Apps → RFID → T5577 → Wipe Tag`. L’avertissement indique
*Wipe T5577 — Erases all data. The tag stops working as a key. Hold still while running* ; le résultat est **Wiped!** ou
**Not wiped** (par exemple *No answer. Protected? Try Clear Password*). L’effacement écrit des blocs de données à zéro
et une configuration par défaut, de sorte que l’application T5577 peut encore lire la puce ensuite. Voir
[Application T5577](/fr/rfid/t5577-app).
:::

## « C’est du vibe coding ! »

Selon les mots de l’auteur, il s’agissait d’une expérience : peut-on écrire du code correct pour de tels systèmes avec
un LLM ? Le processus a été méticuleux : datasheets, code du firmware Unleashed pour comprendre l’architecture, code du
Proxmark3. Chaque étape a été validée, testée sur du matériel réel et affinée. Ces fonctions ont donc été *écrites par
Claude Code*, mais *créées par @gromovyna*.

## Pull requests

- [[RFID]: Support of Hitag Micro chips (8265/8210/H5.5)](https://github.com/DarkFlippers/unleashed-firmware/pull/1002)
- [[RFID]: Wipe T5577 (reset to blank, with read-back verification)](https://github.com/DarkFlippers/unleashed-firmware/pull/1003)

Autres articles et recherches : [@gromovyna](https://t.me/gromovyna).

## Voir aussi

- [Écriture sur supports vierges](/fr/rfid/write) · [Application T5577](/fr/rfid/t5577-app) ·
  [Protocoles](/fr/rfid/protocols)
