---
title: NFC Magic 2.0
order: 55
author: gromovyna
original: [https://telegra.ph/NFC-Magic-20---magiya-teper-i-dlya-Ultralight-06-25, https://t.me/gromovyna/31, https://docs.flipper.net/zero/nfc/magic-cards, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# NFC Magic 2.0 : écrire et effacer des cartes vierges magiques

**NFC Magic** est l'application qui permet d'écrire, de cloner et d'effacer des
[cartes vierges magiques](/fr/nfc/magic-cards) directement depuis le Flipper. Elle a commencé comme une application
officielle du Flipper Zero ; la version décrite ici vit dans le pack
[all-the-plugins](https://github.com/xMasterX/all-the-plugins) de **xMasterX** et est maintenue par l'équipe
**Unleashed** (qui l'a forkée et continue de la développer). La version **2.0** a été écrite par **@gromovyna** : le
cycle complet, de la recherche sur le transport jusqu'au dernier bouton de l'interface.

Avant la 2.0, l'application gérait les **MIFARE Classic** magiques (Gen1a, Gen2) et la **Gen4** universelle
(UMC/GTU), une puce configurable non liée à MFC. La 2.0 ajoute les cartes vierges magiques **Ultralight/NTAG** et des
résultats honnêtes.

![Nouvelle version, nouvelle icône](/img/remote/dafa43486592335f.png)

::: tip Où se la procurer
NFC Magic **ne fait pas partie du binaire du firmware** : c'est une application externe du pack d'applications
supplémentaires. La 2.0 est disponible dans les **builds de développement Unleashed à partir de 1307**. Mettez
l'application à jour via le catalogue, ou mettez le firmware à jour vers un build de développement récent (avec le
pack d'applications supplémentaires). Chemin sur l'appareil : `Main Menu → Apps → NFC → NFC Magic`.
:::

## Avant de commencer

1. [Lisez](/fr/nfc/read) la carte originale et **enregistrez-la**. Assurez-vous que **tous** les secteurs (MIFARE
   Classic) ou toutes les pages (Ultralight/NTAG) ont été lus : un dump partiel donne une copie partielle.
2. Pour les cartes vierges MIFARE Classic, NFC Magic s'authentifie avec les clés du **cache de clés** et des
   **dictionnaires utilisateur et système**, rien d'autre. Si les clés de votre carte proviennent d'un dictionnaire
   CUID, exécutez d'abord **Save Keys to Dictionary** sur le dump (voir
   [MIFARE Classic](/fr/nfc/mifare-classic#save-keys-to-dictionary)).

## Étape 1. Détection

Tout commence quand vous posez la carte vierge sur le Flipper (`Check Magic Tag`). Premier grand changement :
l'application n'est plus obnubilée par MIFARE Classic. Le scanner travaille **par famille d'abord** : il détermine
d'abord la famille (**MFC** ou **Ultralight/NTAG**) et ne creuse qu'ensuite jusqu'à la variante exacte.

Pour les **USCUID-UL** (cartes vierges magiques de la famille Ultralight), tout le zoo principal est reconnu, plus un
peu de cirque local russe : **UL11**, **UL21** (y compris ce qui est vendu sous le nom d'**« Ultra »** sur le marché
de l'ex-URSS), **NTAG213/215/216**, **UL-C**, **UL-5**, et les tags déjà en mode **backdoor** (les deux séquences de
réveil sont testées).

![USCUID-UL détectée](/img/remote/557fa5d47ebeb0a6.png)

Si vous avez un preset que l'application ne connaît pas, elle n'abandonne pas : elle affiche la **configuration
brute**, pour que vous puissiez la voir et l'analyser vous-même. Pratique pour les chercheurs.

![Configuration brute 1](/img/remote/7c3f38df0079d8fa.png)

![Configuration brute 2](/img/remote/c16eb844763ef4fa.png)

![Configuration brute 3](/img/remote/30f2a4b10d4be98a.png)

Pour une carte **Gen4** protégée par mot de passe : `Gen4 Actions → Auth with password`, saisissez le mot de passe,
puis vérifiez le tag.

## Étape 2. Écrire une Ultralight / NTAG

Une fois le tag reconnu, vous pouvez écrire et cloner intégralement des **UL/NTAG**. Ce à quoi vous n'avez **pas**
besoin de penser, c'est le transport : l'application le choisit d'après le résultat de la détection.

- **Direct** : une écriture ISO14443-3 normale avec la commande **`A2`**, pour les tags qui acceptent les écritures
  de front (p. ex. les configurations d'usine **USCUID-UL**, la même **UL21**, alias **« Ultra »**).
- **Backdoor** : si la puce a une backdoor exposée, l'application l'utilise (réveil brut plus commandes de
  backdoor). Logique simple : backdoor exposée → on l'utilise ; aucune → écriture directe.

Vos décisions :

- **Vous écrivez sur un tag sans backdoor dont vous connaissez le mot de passe ?** Fournissez-le via **PWD-AUTH** :
  l'application s'authentifie auprès du tag avant d'écrire ou d'effacer.
- **Le tag n'a pas été confirmé comme magique mais vous savez qu'il l'est ?** Appuyez sur **Write anyway** et
  assumez-en la responsabilité.

Le processus d'écriture a été rendu aussi peu angoissant que possible :

- **Progression en direct « Writing X/N »** à l'écran, pour que vous ne restiez pas devant un écran figé à vous
  demander si quelque chose se passe.

  ![Progression de l'écriture (c'est rapide : il a fallu une NTAG216 pour attraper la capture d'écran)](/img/remote/9914d55ba866082e.png)

- L'**ordre des pages** est réglé selon le type de tag (p. ex. **UL-5**) et il est **différent pour l'écriture et
  pour l'effacement**, à cause des bits de verrouillage. À l'écriture, les pages de service (y compris l'UID)
  passent en **dernier** : écrivez le verrouillage/la protection trop tôt et le tag se verrouille avant que le dump
  ne soit complet. Un effacement se fait par ordre croissant, pour retirer d'abord le verrouillage statique et
  nettoyer le reste seulement ensuite.
- L'écriture est **ACK-only avec poursuite en cas d'erreur** : l'application ne s'arrête pas à la première page
  échouée, elle pousse tout ce qu'elle peut.
- Si quelque chose n'est pas passé, vous obtenez **Partial Write** avec une liste **Details** indiquant exactement
  les pages qui ont échoué, et non un joyeux « c'est fait ». Vous avez retiré le tag de l'antenne en cours de route ?
  Remettez-le et l'écriture reprend au même endroit.

![Écriture partielle](/img/remote/a50fa90dff60cdd8.png)

![Details](/img/remote/71b6fa77e1914b76.png)

Et **Wipe** ramène le tag à son état d'usine en une seule pression.

## Étape 3. Écrire une MIFARE Classic

1. Dans NFC Magic, sélectionnez **Check Magic Tag** et présentez la carte vierge au dos du Flipper.
2. Quand la carte vierge est reconnue (Gen1a, Gen2, Gen4…), allez dans **More** pour les options de ce type de carte
   vierge.
3. **Write** : choisissez la carte originale dans le navigateur de fichiers, présentez la carte vierge au Flipper.
4. **Wipe** formate la carte vierge : UID remis par défaut, données des secteurs/pages effacées.

### Un retour honnête : Success / Partial / Fail

Ce point concerne la bonne vieille **MIFARE Classic (Gen2)** et compte autant pour l'auteur que les nouvelles
fonctions.

Avant, l'effacement et le clonage MFC rapportaient **toujours** « Success ». Toujours, même quand pas un seul octet
n'avait été écrit. Ce n'est pas seulement un bug, c'est un mensonge : vous repartez persuadé que votre copie
fonctionne, et ce n'est pas le cas.

Désormais, les opérations sont suivies **bloc par bloc** et vous obtenez un verdict honnête :
**Success / Partial / Fail**. Sur **Partial**, vous voyez **Details** : quels blocs n'ont pas été écrits ou effacés.
Le bloc 0 en lecture seule ne fait plus échouer tout le secteur 0 dans le rapport (comme c'était le cas dans la
conception d'origine), ce qui est également pratique quand le tag est fermé par des **bits d'accès**.

![Résultat](/img/remote/9e9d84e664f7da06.png)

![Détails d'un résultat partiel](/img/remote/525faf18552333d1.png)

Ce qui rend la vie plus sereine :

- À l'effacement, le bloc 0 **conserve les vrais SAK/ATQA** du tag. Cas classique : la **Perfect CUID** (répond à
  RATS / possède un ATS). Le firmware la détectait comme une 4K et l'effacement estampillait le bloc 0 comme une 4K.
  Corrigé : une 1K reste une 1K, et l'UID est mis à zéro.
- Pas de clé fonctionnelle pour l'effacement ? Au lieu d'une tentative d'écriture vouée à l'échec, vous voyez
  immédiatement **« No keys found »**.
- Chaque écran d'échec (Wipe / Write / Dump) comporte **Exit → menu**, pour que vous ne vous sentiez pas pris au
  piège.
- Un vilain bug a disparu : les clés du tag précédent **ne sont plus reportées** sur l'opération suivante. L'attaque
  par dictionnaire relit désormais le tag à chaque fois au lieu de réutiliser les clés du tag précédent (ce qui
  pouvait donner un faux sentiment de succès et une rapidité factice).

## Garde-fous

Dès la version précédente, l'application avait reçu des protections concernant les tags MFC magiques et les
différentes longueurs d'**UID**. La 2.0 vérifie si le dump peut réellement être écrit sur la variante
**USCUID-UL** donnée :

![Vérification de compatibilité dump/carte vierge](/img/remote/a4dc82f2b66b73b5.png)

et, pour les plus doués, elle bloque les tentatives d'associer des **familles différentes** (un dump MFC sur une
carte vierge Ultralight et inversement ; ces cas apparaissent régulièrement sur les forums et dans les discussions) :

![Familles incompatibles](/img/remote/83e6e6cf1f0d9da6.png)

## C'est moins trivial qu'il n'y paraît

Derrière la liste des fonctions, il y a près de **3 000 lignes** de modifications : un poller USCUID-UL écrit de
zéro, la logique Gen2 réécrite et une pile de bugs corrigés. Tout cela a été **validé sur du matériel réel** avec une
**matrice de QA de près de 100 cas** :

- **environ 15 tags de test** : des variantes USCUID-UL achetées ou fabriquées (UL11, UL21 (NXP et « Ultra » de
  Mikron), NTAG213/215/216, UL-C, UL-5, plusieurs variantes UL-Y pour les cas limites), des tags en mode backdoor
  (les deux réveils), plus de véritables tags non magiques et entièrement verrouillés pour des échecs honnêtes, et un
  tas de tags pour la régression ;
- **catégories** : détection (17 cas), transport direct/backdoor, intégrité des données et ordre des pages,
  scénarios d'expérience utilisateur, PWD-AUTH, effacement, un gros bloc pour l'effacement Gen2/MFC (19 cas) et la
  régression de tous les anciens protocoles (Gen1a 4/7 octets, Gen2, Gen4, MFC ordinaire).

Cette campagne a fait apparaître et éliminé de nombreux bugs : de faux « Success », des boutons morts, une fuite
mémoire, un indicateur d'attente qui tournait indéfiniment sur une véritable Ultralight. Les limitations connues (y
compris une subtilité de détection 1K/4K au niveau du firmware) sont documentées.

Prochainement au programme : la prise en charge de l'écriture **UL-C** pour USCUID-UL et, peut-être, des exotismes
propres à certaines régions.

## Dépannage

- **Tag non reconnu** : ce n'est peut-être pas un tag magique, ou bien c'est un preset inconnu : regardez la
  configuration brute. Pour une Gen4 avec mot de passe, authentifiez-vous d'abord.
- **« No keys found »** lors d'un effacement MFC : les clés actuelles de la carte vierge ne sont pas dans vos
  dictionnaires. Ajoutez-les (`NFC → Extra Actions → MIFARE Classic Keys → Add`).
- **Écriture partielle** : remettez le tag en place et continuez ; consultez **Details**. Les bits de verrouillage
  ou d'accès du dump source peuvent rendre certains blocs/pages non inscriptibles.
- **Le lecteur rejette la copie** : le lecteur filtre peut-être votre type de carte vierge. Voir
  [Cartes magiques](/fr/nfc/magic-cards), [Iron Logic](/fr/nfc/iron-logic),
  [Filtres Vizit](/fr/nfc/vizit-filters).

## Voir aussi

[Cartes magiques](/fr/nfc/magic-cards) · [MIFARE Classic](/fr/nfc/mifare-classic) · [qUnleashed](/fr/nfc/qunleashed) ·
[Déverrouillage par mot de passe](/fr/nfc/unlock-with-password)
