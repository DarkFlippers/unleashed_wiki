---
title: Lecteurs Iron Logic
order: 100
author: gromovyna
original: [https://telegra.ph/Schityvateli-Iron-Logic-i-chto-s-nimi-delat-03-13, https://t.me/gromovyna/14]
sources: [gromovyna]
---
# Les lecteurs Iron Logic (CP-Z-2 « 3 bandes » / « 4 bandes »)

Les lecteurs Iron Logic (« prises ») sont très répandus dans les interphones et le contrôle d'accès dans l'ex-URSS. Cette page explique comment ils protègent les porte-clés MIFARE Classic, comment déterminer à quelle variante vous avez affaire, et ce que dit la recherche publiée sur la lecture, l'émulation et la copie de **votre propre** porte-clés avec un Flipper Zero.

::: tip Cadre
Uniquement pour vos propres identifiants et pour de la recherche licite. D'après l'article de @gromovyna (2025-03-13).
:::

## Comment ces systèmes se défendent contre le clonage

Iron Logic s'appuie sur du MIFARE Classic peu coûteux et empile des défenses par-dessus :

- **Diversification des clés.** Les clés de secteur sont dérivées, pour chaque carte, de l'UID de la carte et de la
  « carte d'objet » du lecteur (une constante chargée dans le lecteur). Une attaque par dictionnaire ne trouve donc
  généralement rien sur un système configuré.
- Des **filtres** contre les cartes magiques et les émulateurs (par exemple « IL-30 only », OTP1, OTP2), selon le
  firmware du lecteur.
- Le **mode dynamique** (« only first », voir
  [Enrollment dynamique Iron Logic](/fr/nfc/iron-logic-enrollment)), où les données de la carte changent à chaque
  passage.

Comprendre cela permet de saisir pourquoi un simple « lire, puis écrire sur une carte vierge » échoue souvent, et
quoi faire à la place.

## Quel lecteur avez-vous

| Variante | Remarques |
|---|---|
| CP-Z-2 (« 3 bandes ») | Plus ancien, arrêté, encore courant. |
| CP-Z-2 (mod. MF-I) (« 4 bandes ») | Modèle actuel, pris en charge par les versions de firmware. L'article est écrit pour celui-ci, mais fonctionne aussi pour l'ancien. |

L'identification par le boîtier n'est pas fiable à 100 % (un installateur peut mettre de l'électronique neuve dans un
ancien boîtier) mais fonctionne presque toujours en pratique. Ces lecteurs sont aussi utilisés à l'intérieur de
platines d'autres fabricants (Eltis, Metakom et d'autres) ; cela n'a pas d'importance, car l'objectif est de
récupérer tous les secteurs de la carte MIFARE Classic.

## Vérifiez si vous n'avez pas de chance

### Carte SmartMX (IL-30)

Si un lecteur « 4 bandes » est utilisé et que le Flipper affiche l'écran de type « carte non prise en charge »,
examinez la carte : **SAK = 28** et **ATQA = 0004** signifie une carte **SmartMX**, et le lecteur peut avoir le filtre
**« IL-30 only »** activé. Vous pouvez tout de même essayer les étapes ci-dessous, au cas où le filtre serait
désactivé et le lecteur en mode mixte (nouvelles clés SmartMX et anciennes clés MIFARE Classic). Si rien ne
fonctionne et que vous avez besoin d'une copie, l'auteur suggère un atelier équipé d'appareils iKey, qui écrivent les
données sur des puces d'origine (iMF+) en exploitant une faille de logique d'Iron Logic.

### Interphones dynamiques (« Sokol » de Petrunya)

Les interphones Sokol (généralement construits sur une platine Eltis 5000) utilisent des lecteurs Iron Logic
**avec la dynamique** : les données du badge changent à chaque passage et les anciennes copies deviennent invalides.
Émuler ou écrire une carte vierge peut **corrompre votre original**. Détails :
[enrollment dynamique](/fr/nfc/iron-logic-enrollment).

## Étape 1 : extraire tous les secteurs

Il vous faut tous les secteurs et toutes les clés de la carte. N'attendez pas la fin de l'attaque par dictionnaire :
avec des clés diversifiées, elle n'a aucun sens.

1. Lisez la carte (`Main Menu → NFC → Read`). Voir [Lire des cartes](/fr/nfc/read).
2. Si le résultat est **16/16 secteurs lus mais 0/32 clés trouvées**, la carte possède une backdoor. Allez
   directement au [guide Nested / backdoor Fudan](/fr/nfc/nested-fudan).
3. Si vous n'avez aucune clé du tout, collectez des nonces auprès du lecteur (voir ci-dessous), puis récupérez les
   clés avec [MFKey](/fr/nfc/mfkey).
4. Récupérez les clés restantes avec Nested ([guide](/fr/nfc/nested-fudan)).

### Collecter des nonces auprès du lecteur

On a longtemps cru que le Flipper ne pouvait pas travailler du tout avec les lecteurs à 4 bandes. Grâce à
@blowtreez, il s'est avéré que c'était possible, même si cela demande de la précision et de la pratique. Le Flipper
collecte des nonces sur **toutes** les versions de lecteurs, quel que soit le nombre de bandes ou le firmware.

- Trouvez la position dans laquelle le Flipper interagit avec le lecteur. Empiriquement : le texte **« FLI »** sur le
  boîtier du Flipper doit être **au-dessus du lecteur**.
- Gardez-le le plus près possible, au contact du lecteur.
- Parfois (comme dans le cas de l'auteur), cela ne fonctionne pas dans un étui ; sortez le Flipper et essayez nu.

Suivez ensuite l'article officiel
[Recovering MIFARE Classic keys](https://docs.flipper.net/nfc/mfkey32).

::: tip Notes de l'auteur
- Dans la plupart des cas, les clés et les secteurs entièrement lus **0, 1 et 14** suffisent, mais certains systèmes
  conservent des données dans des secteurs personnalisés (le 8, par exemple). Faites toujours une copie complète et
  déchiffrez tous les secteurs.
- L'auteur mentionne disposer d'une API privée qui calcule la clé du secteur 14 à partir de l'UID d'une carte, afin
  de poursuivre avec Nested (proposée dans la discussion communautaire Unleashed).
:::

## Étape 2 : l'émulation

- Fonctionne sur tous les lecteurs « 3 bandes » (rares exceptions) et sur les lecteurs « 4 bandes », sauf s'ils
  exécutent le firmware le plus récent (**7.28**, comme indiqué dans la publication du canal).
- Sur les versions plus anciennes comme la **7.20** (le firmware d'usine actuel), l'émulation fonctionne, mais vous
  devez trouver la position exacte du Flipper par rapport au lecteur, comme pour la collecte de nonces.
- Les filtres OTP1 et OTP2 **n'affectent pas** l'émulation.
- Le Chameleon Ultra se comporte de la même manière.
- Avec le filtre « IL-30 only » activé, l'émulation ne fonctionnera pas.

## Étape 3 : copier sur une carte vierge

Le choix universel est une carte vierge **CUID static nonce (alias MF-3.2)** (voir
[Cartes magiques](/fr/nfc/magic-cards)). Au moment de la rédaction, elle fonctionnait sur toutes les versions de
firmware et tous les réglages de filtres, pour les deux types de lecteurs. Pour les « 3 bandes », une **CUID**
ordinaire fonctionne, et certains ont même réussi avec une **Zero**.

L'auteur recommande de ne pas chercher la carte vierge minimale qui fonctionne, à moins d'aimer les expériences : la
différence de prix entre une CUID static nonce et une CUID ordinaire est faible, et vous évitez le « facteur
casino ». Il a aussi trouvé plusieurs puces CUID ordinaires (révisions plus récentes) qui fonctionnent sur toutes les
versions de firmware des lecteurs 4 bandes, et il existait des retours antérieurs de la communauté faisant état de
succès avec des cartes vierges CUID ordinaires, qu'il n'avait pas pu reproduire de manière fiable jusqu'à récemment.

## Ce qui n'est pas traité

L'auteur liste les sujets hors périmètre ou encore à l'étude : la manière dont les filtres OTP1/OTP2 sont
implémentés, la KDF de la clé A du secteur 14 à partir de l'UID, et le rôle de la carte d'objet dans le chiffrement
des secteurs.

## Voir aussi

- [Nested et backdoor Fudan](/fr/nfc/nested-fudan) · [MFKey](/fr/nfc/mfkey) · [Cartes magiques](/fr/nfc/magic-cards)
- [Enrollment dynamique Iron Logic](/fr/nfc/iron-logic-enrollment) · [Filtres Vizit](/fr/nfc/vizit-filters)
