---
title: NFC
author: gromovyna
original: [https://docs.flipper.net/zero/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://t.me/gromovyna/3]
sources: [flipper-docs, unleashed-readme, unleashed-src, gromovyna]
---
# NFC

Le Flipper Zero embarque un **module NFC 13,56 MHz** capable de **lire**, **enregistrer**, **émuler** et, pour
certains types de cartes, **écrire** des cartes haute fréquence : cartes et porte-clés d'accès, cartes de transport,
clés d'hôtel, autocollants NFC, jouets de type amiibo et cartes bancaires (données publiques uniquement). Les
données sont stockées sur la carte microSD dans `/ext/nfc/` sous forme de fichiers texte `.nfc`.

::: warning Insérez une carte microSD
L'application NFC conserve ses dictionnaires, ses analyseurs et ses cartes enregistrées sur la carte microSD
(`/ext/nfc/`). Mettez le firmware à jour avec la carte SD insérée, afin que les ressources (dictionnaires de clés,
`assets/*.nfc`, plugins d'analyse) soient bien installées.
:::

## Matériel

- Puce frontale NFC **ST25R3916**, responsable à la fois de la lecture et de l'émulation.
- Une **antenne 13,56 MHz** sur la carte d'antenne RFID bi-bande à l'arrière de l'appareil, à côté de l'antenne
  125 kHz. Tenez les cartes contre le **centre du dos** du Flipper.

## Le menu NFC

`Main Menu → NFC` ouvre ce menu (les libellés sont exactement ceux affichés sur l'appareil sous Unleashed) :

![Menu principal NFC : Read, Extract MFC Keys, Saved, Extra Actions](/screens/nfc/menu.png)

| Entrée | Rôle |
|---|---|
| **Read** | Détecte le type de carte et lit tout ce qu'il peut, y compris les attaques sur les clés MIFARE Classic. Voir [Lire des cartes](/fr/nfc/read). |
| **Extract MFC Keys** | Émule une carte MIFARE Classic pour collecter des nonces auprès d'un lecteur (MFKey32). Voir [MFKey32](/fr/nfc/mfkey). |
| **Saved** | Vos fichiers `.nfc` enregistrés : émuler, écrire, déverrouiller, renommer, supprimer. |
| **Extra Actions** | Lire un type de carte précis, gérer les dictionnaires de clés, déverrouiller les NTAG/Ultralight et les SLIX-L. |
| **Add Manually** | Génère une carte virtuelle vierge ou une carte NFC-A à partir d'un UID/ATQA/SAK connu. Voir [Ajouter des cartes manuellement](/fr/nfc/add-manually). |
| **Debug** | Visible uniquement avec le mode Debug activé (`Settings → System → Debug`). |

`Extra Actions` contient :

![Menu Extra Actions : Read Specific Card Type et les dictionnaires de clés](/screens/nfc/extra_actions.png)

- **Read Specific Card Type** : contourner la détection automatique, utile pour les cartes hybrides.
- **MIFARE Classic Keys**, **MIFARE Plus Keys**, **MIFARE Ultralight C Keys**, **MIFARE UL AES Keys** : consulter
  les compteurs des dictionnaires système/utilisateur, **Add** une clé, ou **List** (et supprimer) les clés
  utilisateur.
- **Unlock NTAG/Ultralight** : générer ou saisir un mot de passe avant la lecture. Voir
  [Déverrouiller des cartes](/fr/nfc/unlock-with-password).
- **Unlock SLIX-L** : déverrouillage par mot de passe pour les tags ICODE SLIX-L.

::: tip Unleashed
L'application NFC vient du firmware officiel — son lecteur, son émulateur et la plupart des analyseurs de cartes.
En plus, Unleashed ajoute notamment : un dictionnaire système MIFARE Classic étendu
(plus de 4000 clés), la lecture **MIFARE Plus SL3** avec des dictionnaires de clés AES, la prise en charge de
**MIFARE Ultralight AES**, les clés d'interphone **Texkom**, Add Manually pour MIFARE Classic avec un UID
personnalisé et pour MIFARE Plus, **Save Keys to Dictionary** depuis un dump, le dictionnaire CUID (par carte) avec
une barre de progression de chargement, et de nombreux analyseurs de cartes supplémentaires (Troika, Plantain,
Umarsh, Zolotaya Korona, Kazan, Metromoney, carte sociale de Moscou, tickets PPK et bien d'autres).
:::

## Les bases

| Terme | Signification |
|---|---|
| **UID** | Numéro de série de la carte, 4 ou 7 octets (10 sur certaines). Gravé en usine sur les cartes authentiques. |
| **ATQA / SAK** | Octets de réponse pendant l'anticollision, qui donnent une indication sur le type de carte (p. ex. SAK `08` = MIFARE Classic 1K). |
| **Secteur / bloc** | Unité de mémoire MIFARE Classic : 16 octets par bloc, 4 blocs par secteur (secteurs de 16 blocs à la fin d'une 4K). |
| **Page** | Unité de mémoire Ultralight/NTAG, 4 octets. |
| **Clé A / Clé B** | Clés Crypto-1 de 6 octets protégeant chaque secteur MIFARE Classic. |
| **Nonce** | Nombre aléatoire échangé pendant l'authentification. Les nonces collectés permettent de calculer les clés hors ligne. |
| **Carte magique** | Une carte vierge dont l'UID / le bloc 0 est inscriptible. Voir [Cartes magiques](/fr/nfc/magic-cards). |

## Les pages de cette section

### Usage quotidien

- [Lire des cartes](/fr/nfc/read) : lire, enregistrer, émuler ; quels types de cartes sont pris en charge et ce que
  chacun vous apporte.
- [Ajouter des cartes manuellement](/fr/nfc/add-manually) : générer des cartes virtuelles, créer une carte NFC-A à
  partir d'un UID/ATQA/SAK.
- [Cartes prises en charge (analyseurs)](/fr/nfc/supported-cards) : cartes de transport, d'accès et de jouets que le
  Flipper sait décoder.
- [Cartes bancaires (EMV)](/fr/nfc/emv) : ce qui est lu sur une carte bancaire et pourquoi elle ne peut pas être
  clonée.
- [Déverrouiller des cartes avec des mots de passe](/fr/nfc/unlock-with-password) : mots de passe NTAG/Ultralight,
  clés Ultralight C, SLIX-L.

### MIFARE Classic et récupération de clés

- [MIFARE Classic](/fr/nfc/mifare-classic) : dictionnaires, secteurs, le déroulé complet de la lecture, émulation et
  écriture.
- [MFKey32 : des clés depuis le lecteur](/fr/nfc/mfkey) : collecter des nonces auprès d'un lecteur, récupérer les
  clés.
- [Attaques nested et backdoors Fudan](/fr/nfc/nested-fudan) : les attaques carte seule intégrées à `Read`.
- [L'application MFKey](/fr/nfc/mfkey-app) : récupérer des clés sur le Flipper lui-même (MFKey 4.1).
- [Récupération rapide des clés avec qUnleashed](/fr/nfc/qunleashed) : toutes les attaques sur votre téléphone ou
  votre ordinateur.

### Cartes vierges et clonage

- [Cartes magiques MIFARE Classic](/fr/nfc/magic-cards) : Gen1/Gen2/Gen3/Gen4, CUID, FUID, USCUID, UMC et les
  appellations locales.
- [NFC Magic 2.0](/fr/nfc/nfc-magic) : écrire et effacer des cartes vierges magiques MIFARE Classic et
  Ultralight/NTAG.

### Autres familles de cartes

- [MIFARE Ultralight AES](/fr/nfc/ultralight-aes) : Ultralight protégé par AES (MF0AES20), clés, réécriture,
  messagerie sécurisée.
- [MIFARE Plus](/fr/nfc/mifare-plus) : comment les S/X/SE/EV1/EV2 et les niveaux de sécurité sont détectés, clés AES
  SL3.

### Systèmes d'accès (par @gromovyna)

- [Lecteurs Iron Logic](/fr/nfc/iron-logic)
- [Enrollment dynamique Iron Logic](/fr/nfc/iron-logic-enrollment)
- [Filtres des lecteurs Vizit](/fr/nfc/vizit-filters)
- [Cartes Moskvyonok](/fr/nfc/moskvyonok)

### Référence

- [Format de fichier NFC](/fr/nfc/file-format) : la structure du fichier `.nfc` et les formats de dictionnaires.

::: tip Légalité
Travaillez avec vos propres cartes ou avec une autorisation explicite. Copier des identifiants d'accès ou des titres
de transport qui ne vous appartiennent pas peut être illégal.
:::

MIFARE, MIFARE Classic, MIFARE Ultralight, MIFARE Plus, MIFARE DESFire, NTAG et ICODE sont des marques de NXP B.V.
FeliCa est une marque de Sony Corporation.
