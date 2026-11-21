---
title: Cartes « Moskvyonok »
order: 130
author: gromovyna
original: [https://telegra.ph/Karty-braslety-brelki-Moskvyonok-i-s-chem-ih-kushat-12-16]
sources: [gromovyna]
---
# Cartes, bracelets et porte-clés Moskvyonok

Comment sont construites les cartes scolaires moscovites « Moskvyonok » et comment copier **votre propre** carte vers un format plus pratique (bracelet, porte-clés). D'après l'article de @gromovyna (2024-12-16), avec l'aide technique de @Aleksei_Pashaev et d'un membre anonyme de la communauté Unleashed.

::: warning
Article technique ; la réglementation varie selon les pays. N'utilisez que vos propres cartes, gardez en tête qu'elles s'apparentent à un instrument de paiement, et assumez vous-même les conséquences.
:::

## Comment ces systèmes se défendent contre le clonage

Presque pas. Le système utilise **MIFARE Classic** avec des clés standard, sans diversification : les clés se
trouvent donc avec un dictionnaire ordinaire. Copier revient donc à une simple
[lecture MIFARE Classic](/fr/nfc/mifare-classic) suivie d'une écriture sur une
[carte magique](/fr/nfc/magic-cards).

## Identifier votre carte

| Type | UID | Bloc 0 | ATQA | SAK |
|---|---|---|---|---|
| UID de 4 octets | 4 octets | commence par l'UID | `00 04` | `08` |
| UID de 7 octets | 7 octets | commence par l'UID | `00 44` | `08` |
| 7 octets, personnalisée en 4 | 4 octets | ne commence pas par l'UID, ressemble à n'importe quoi | `00 44` | `08` |

### UID de 4 octets

Tags standard, écrits tels quels. Les cartes vierges **Gen2 (CUID)** sont recommandées ; les **Gen1 (UID/Zero)**,
moins chères, fonctionnent aussi, même si certains retours indiquent qu'elles ont été filtrées.

### UID de 7 octets

Tags plus récents, écrits tels quels sur des cartes vierges **Zero 7 bytes** comme des tags Gen1 ordinaires, y
compris avec le Flipper Zero ; ou sur des tags à base d'USCUID avec des duplicateurs chinois ou un Proxmark3
(comprenez la structure de la mémoire et de la configuration, sous peine de bloquer logiciellement le tag).

::: tip Unleashed
L'écriture de cartes vierges Zero 7 octets sur le Flipper Zero est disponible sous Unleashed à partir de la version
079, ou avec une application NFC Magic compilée avant la refonte NFC.
:::

### UID de 7 octets personnalisé en 4 octets

Il s'agit de MIFARE Classic EV1 en **mode personnalisation** : un mode de rétrocompatibilité dans lequel la carte
possède un identifiant de 7 octets mais répond à chaque SELECT avec un identifiant de 4 octets calculé à partir de
celui-ci (fiche technique MF1S50YYX_V1 section 10.1.1 ; algorithme dans la note NXP AN10927, page 14). L'écrire tel
quel ne donne que du n'importe quoi. Un bloc 0 typique de Moskvyonok commence par `34 00...`, mais cela dépend du
lot. Sur Proxmark3, le calcul s'obtient avec `analyse nuid`.

Copier vers une carte vierge à UID de 4 octets (CUID) :

1. Faites une copie du dump d'origine.
2. Calculez le nouvel UID (exemple : `3400060000DBDC` devient `2FEDA2F1`).
3. Calculez l'octet de somme de contrôle BCC (`2FEDA2F1` donne `0x91`).
4. Réécrivez le bloc 0 de la copie ainsi : l'identifiant de 4 octets calculé, le BCC, `08`, `04`, `00`, le reste
   inchangé (`2F ED A2 F1 91 08 04 00 FF FF FF FF FF FF FF FF`).
5. Changez l'ATQA dans l'en-tête du fichier `.nfc` en `00 04` (la plupart des cartes vierges ont un ATQA fixe, mais
   faites-le par souci d'exactitude).
6. Écrivez le dump sur la carte vierge.

Les tags à base d'USCUID peuvent écrire le dump tel quel et émuler ce comportement, mais cela demande de connaître la
configuration de la puce et n'est pas traité ici.

## Ce qui n'a pas fonctionné

L'équipe a essayé de tronquer les octets de poids fort, de poids faible et du milieu de l'UID, d'inverser l'ordre des
octets et de calculer le NUID à partir des 7 octets face à des systèmes à 7 octets ; aucune de ces approches n'a
abouti.

## Voir aussi

- [MIFARE Classic](/fr/nfc/mifare-classic) · [Cartes magiques](/fr/nfc/magic-cards) · [Lire des cartes](/fr/nfc/read)
