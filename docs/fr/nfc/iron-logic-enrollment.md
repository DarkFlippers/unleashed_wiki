---
title: Enrollment dynamique Iron Logic
order: 110
author: gromovyna
original: [https://telegra.ph/Enrollment-ataka-na-dinamiku-ot-Iron-Logic-06-05, https://t.me/gromovyna/14, https://t.me/gromovyna/19, https://t.me/gromovyna/20, https://t.me/gromovyna/25]
sources: [gromovyna]
---
# La « dynamique » Iron Logic et la faille de logique de l'enrollment

Une étude sur la façon dont les lecteurs Iron Logic implémentent la « dynamique » anti-clone (le mode « ТП » / « premier seulement »), et sur une faille de logique du firmware 7.29 des lecteurs, **corrigée en 7.30**. Lecture pédagogique pour les propriétaires et les chercheurs.

::: tip Cadre
Uniquement pour vos propres identifiants et pour de la recherche licite. La faille décrite ici est corrigée dans le firmware actuel (7.30). D'après l'article de @gromovyna (2025-06-05) et ses publications sur son canal.
:::

## Comment ces systèmes se défendent contre le clonage

Un porte-clés MIFARE Classic statique peut être copié par quiconque possède les clés. Les fabricants répondent de
deux façons :

1. Des **filtres**, qui détectent les cartes vierges magiques et les émulateurs (voir
   [Lecteurs Iron Logic](/fr/nfc/iron-logic), [Filtres Vizit](/fr/nfc/vizit-filters)).
2. La **dynamique** : certaines données de la carte sont synchronisées avec la mémoire du lecteur à chaque passage
   (un « compteur »). Une copie réalisée auparavant ne correspond plus et est rejetée. Des variantes de ce principe
   sont utilisées par Intratone, Hexact, Comelit, Noralsy et Urmet en France, en Belgique et au Luxembourg (où une
   désynchronisation détectée peut désactiver tous les badges d'un utilisateur), et ont été observées sur certains
   interphones Eltis en Russie.

## Le mode « ТП » (« Только первый » / « premier seulement »)

D'après l'annonce du fabricant citée sur le canal (publication 20) : à chaque accès, le lecteur écrit un **nouveau
mot de passe** sur la carte. À l'accès suivant, le numéro de carte et le mot de passe sont comparés à ce que le
lecteur a mémorisé ; s'ils correspondent, la carte est acceptée et un nouveau mot de passe est écrit. Résultat :
quel que soit le nombre de copies existantes, une seule carte continue de fonctionner. Pris en charge au début
uniquement par le **CP-Z2 MF-I**, avec le firmware 7.29 (annoncé comme pas entièrement testé). Le fabricant
avertit que chaque passage **écrit désormais sur la carte** : vous devriez donc vérifier l'endurance en écriture de
vos cartes avant de basculer.

Pourquoi c'est problématique : le marché est rempli de contrefaçons chinoises de MIFARE Classic, qui peuvent ne pas
survivre au nombre de réécritures, et une écriture interrompue (mauvais positionnement, coupure d'alimentation) peut
laisser la carte désynchronisée. C'est aussi la raison pour laquelle émuler ou cloner sur de tels systèmes peut
**détruire votre original**.

## Firmware 7.29 : plus de filtres, la dynamique comme mode principal

Le firmware 7.29 (test ouvert) a désactivé tous les filtres et fait de la dynamique le mode principal. L'équipe de
recherche a trouvé des vulnérabilités dans cette version ; un bug de logique a été corrigé en **7.30**, après quoi
l'auteur a publié sa description.

## Enrollment : comment une carte devient dynamique

Pour faire passer des milliers de cartes statiques existantes à la dynamique sans obliger les utilisateurs à les
faire rééditer, Iron Logic a introduit l'**enrollment**. Des métadonnées sont écrites dans le **secteur 14** de la
carte. Logique simplifiée du lecteur :

1. Le lecteur vérifie les métadonnées de la carte.
2. Si la carte n'est **pas encore en mode dynamique**, le lecteur l'enrôle et mémorise une valeur de compteur. Il
   **ne vérifie pas** si cet identifiant de carte est déjà dans sa mémoire.
3. Si la carte est déjà enrôlée, des contrôles de compteur stricts s'appliquent.

Les paires identifiant/compteur sont stockées dans la mémoire non volatile du lecteur.

## La faille (corrigée en 7.30)

La faiblesse découle de l'étape 2 : un lecteur à qui l'on présente une carte qui a toujours l'air « statique » se
contente de l'enrôler à nouveau. Le seul obstacle pour un attaquant est de disposer d'un dump de la carte **antérieur**
à son premier enrollment. Les cartes suffisamment anciennes pour ne pas avoir de métadonnées ne sont pas acceptées par
le lecteur ; la conversion de données dynamiques vers un état « statique » n'a donc été explorée que superficiellement.

L'auteur décrit deux façons pratiques de présenter chaque fois une carte « statique » :

- Les **tags GDM (GDMIC)**, une variante USCUID dotée d'un mode fantôme : les données sont écrites en mémoire
  temporaire et reviennent en arrière vers la mémoire permanente lorsque le champ du lecteur s'éteint, de sorte que
  l'originale (déjà enrôlée) et un nombre illimité de copies peuvent coexister. L'auteur note que c'est simple mais
  hors de portée de la plupart des serruriers, et que cela peut être contré par les filtres mentionnés plus haut ou
  par une gestion plus fine du champ RF.
- **Flipper Zero, en manuel** : lire la carte statique, l'émuler, utiliser `Return to Initial State`, et répéter.
  Convient pour des tests, impraticable au quotidien.

L'équipe a d'autres attaques, théoriques et pratiques, et a partagé certaines idées avec iKey.

## Ce que les propriétaires devraient faire

- Mettre à jour les lecteurs en **7.30 ou plus récent**.
- Tester l'endurance en écriture de vos cartes avant d'activer la dynamique.
- Privilégier les familles de cartes modernes (MIFARE Plus, DESFire et similaires) quand c'est possible ; MIFARE
  Classic est considéré comme obsolète par son propre fabricant.

## Voir aussi

- [Lecteurs Iron Logic](/fr/nfc/iron-logic) · [Cartes magiques](/fr/nfc/magic-cards) · [Filtres Vizit](/fr/nfc/vizit-filters)
