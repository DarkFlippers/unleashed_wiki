---
title: Filtres des lecteurs Vizit
order: 120
author: gromovyna
original: [https://telegra.ph/Filtry-schityvatelej-Vizit-dlya-zashchity-ot-klonov-metok-Vizit-RF-31-05-15]
sources: [gromovyna]
---
# Les filtres des lecteurs Vizit contre les clones de Vizit RF 3.1

Comment les lecteurs Vizit tentent de détecter les clés **Vizit RF 3.1** (MIFARE Ultralight EV1) clonées, et ce que cherche chaque filtre. D'après l'article de @gromovyna (2025-05-15).

::: tip Cadre
Uniquement pour vos propres identifiants et pour de la recherche licite.
:::

## Contexte

Vizit est un fabricant russe de contrôle d'accès (depuis 1996, selon ses propres dires). Les anciens lecteurs utilisaient des clés **Dallas**, puis **EM Marine** ; les plus récents utilisent les **Vizit RF 3.1** (= MIFARE Ultralight, UID commençant par `34`) ; les clés les plus récentes **Vizit RF 7.1** sont des **MIFARE Ultralight C** (authentification 3DES). Le firmware minimum pour les RF 7.1 est indiqué sur le site du fabricant. L'auteur note que la dérivation de clé des clés 7.1 est connue d'iKey et que des chercheurs occidentaux travaillent sur la récupération des clés 3DES (sans détails divulgués).

## Comment ces systèmes se défendent contre le clonage

Contrairement à Iron Logic, les filtres Vizit que l'auteur connaît sont **logiciels** et non matériels : ils sont donc visibles dans le trafic capturé avec un Proxmark3. Ils ont été trouvés dans le lecteur **RD-5F, firmware 212** ; d'autres platines les embarquent aussi, mais la version dans laquelle chaque filtre est apparu est inconnue.

### Filtre 1 : la backdoor Gen1

Le lecteur envoie la fameuse commande de backdoor `40(7)` et attend une réponse. Un tag authentique ne répond pas. Cela cible les premières cartes vierges (UL-0116 / UL-0416), qui étaient écrites via la backdoor, UID compris.

### Filtre 2 : EV1 VERSION

Le lecteur envoie `EV1 VERSION` et compare le **second octet du résultat** avec le **premier octet de l'UID du tag**. Les tags Vizit RF 3.1 déclarent le fabricant **Micron Russia** (octet `34`), et leurs UID commencent par `34`. Cela met en échec les variantes USCUID-UL (les « UL-21 » chinoises, « UL-2 » sur le marché russe). La réponse du marché a été les tags « ULtra », des USCUID-UL avec la même version que les 3.1 (qui peut se configurer à la main avec deux commandes Proxmark3 si la configuration est ouverte). Après 2022 en Ukraine, le matériel compatible Vizit (lecteurs Grazhda, platines Mriya) utilise des puces NXP d'origine avec la bonne version : les copies ULtra peuvent donc ne pas y fonctionner.

### Filtre 3 : l'OTP

La page 3 d'une Ultralight est de type OTP : à zéro en sortie d'usine, ses bits ne peuvent passer qu'à 1, jamais revenir en arrière (voir la section 8.5.4 de la fiche technique du MF0ULX1). Sur les tags USCUID-UL ordinaires, elle est librement réinscriptible. Le lecteur tente d'écrire des zéros sur cette page puis la relit ; si elle a changé, le tag est une copie, le lecteur restaure la valeur « d'origine » et le rejette. Un tag authentique répond **NACK** et cesse de répondre jusqu'au prochain SELECT, ce qui est la machine à états correcte.

D'autres implémentations présentaient le même défaut : le Flipper Zero est correct depuis la refonte NFC, et l'émulation Proxmark3 avait ce défaut jusqu'à ce que l'auteur le signale ([issue 2790](https://github.com/RfidResearchGroup/proxmark3/issues/2790)) et qu'il soit corrigé.

La réponse d'iKey a été la carte vierge **UL-5**, inscriptible une seule fois ; une fois la page 0 modifiée, elle se verrouille et se comporte comme une originale. Elle est livrée de Chine avec une version autre que Micron Russia. L'auteur soupçonne qu'il s'agit d'une USCUID-UL spécialement configurée. Ce même filtre peut aussi être franchi sur une USCUID-UL ordinaire (par exemple en configuration ULtra) en modifiant correctement le bloc de configuration, s'il est ouvert.

## Ce qu'il faut en retenir pour les propriétaires

Les Vizit RF 7.1 (Ultralight C) répondent aux standards de sécurité modernes et mettent fin à ce jeu du chat et de la souris.

## Voir aussi

- [Lecteurs Iron Logic](/fr/nfc/iron-logic) · [Cartes magiques](/fr/nfc/magic-cards) · [Lire des cartes](/fr/nfc/read)
