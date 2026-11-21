---
title: Cartes magiques MIFARE Classic
order: 50
author: gromovyna
original: [https://telegra.ph/Mifare-Classic-Magic-Tags-11-16, https://t.me/gromovyna/6, https://docs.flipper.net/zero/nfc/magic-cards]
sources: [gromovyna, flipper-docs]
---
# Cartes magiques MIFARE Classic (cartes vierges)

Sur un tag MIFARE Classic, le **bloc 0**, qui contient l'UID et les données du fabricant, ne peut pas être réécrit.
Pour réaliser une copie complète d'un tel tag, des **cartes vierges** spéciales (« cartes magiques », « cartes à UID
réinscriptible ») ont été inventées, dans lesquelles le bloc 0 peut être écrit plusieurs fois, ou une seule fois.

Cette page, fondée sur l'article de **@gromovyna**, explique brièvement de quoi il s'agit : de la Gen1 à la Gen4, les
noms internationaux, les noms du marché local (ex-URSS), et quel comportement importe pour quel lecteur. Elle
mentionne des tags disponibles sans « danse rituelle » vers la Chine et que l'auteur a lui-même vérifiés ou vus. Pour
les écrire avec le Flipper, voir [NFC Magic 2.0](/fr/nfc/nfc-magic).

> Ci-dessous, « tag », « puce », « carte » et « porte-clés » sont synonymes : ce qui compte est la puce à l'intérieur
> et son comportement, pas le format physique.

Pour aller plus loin :

- les excellentes [notes sur les cartes magiques](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md)
  de la documentation Proxmark3 (en anglais), tenues à jour par des chercheurs, qui couvrent aussi d'autres
  protocoles et donnent les détails techniques et les commandes. Avec de l'expérience et un Proxmark3, vous pouvez
  économiser en achetant les cartes vierges les moins chères sur une puce donnée et en les reconfigurant (pour
  certaines puces) ;
- le [tableau Google Sheets](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
  de l'auteur, avec les tags ci-dessous, leur génération, leurs noms et la capacité du Flipper Zero à les écrire.

## Générations

![Générations de tags magiques](/img/remote/f659ade923b6ca4f.png)

La répartition en générations (« Gen ») n'a rien de formel : c'est une tentative de classer les puces par
comportement. Quatre générations se sont imposées. Une puce peut appartenir à plusieurs à la fois (p. ex. la
**M1-4K**). L'auteur suit la classification standard utilisée par Proxmark3, même s'il n'y adhère pas totalement
pour certaines puces.

| Gen | Surnom | Comment le bloc 0 est écrit | Remarques |
|---|---|---|---|
| **Gen1** | Backdoor | commandes de backdoor spéciales | La plus ancienne. Les commandes de backdoor autorisent toujours l'écriture, la lecture (et l'effacement, pour la Gen1a) du tag. Comme un filtre contre elles est trivial, **tout système qui se respecte les filtre**. |
| **Gen2** | Direct Write | le bloc 0 s'écrit comme n'importe quel autre bloc | Peuvent être écrites par des téléphones NFC (surtout Android) avec le bon logiciel. |
| **Gen3** | APDU | une commande APDU spéciale | Certaines permettent de changer l'UID indépendamment du bloc 0. Une bête rare. |
| **Gen4** | Configurable | bloc de configuration | Dispose d'une configuration et de mémoire, peut être paramétrée en différents formats MFC (et davantage). La plus flexible ; peut imiter le comportement Gen1/Gen2. |

## Gen1 (backdoor)

### Gen1a

Nécessitent les commandes de backdoor `40` (7 bits) et `43` pour l'écriture.

**UID** (nom RU : *Zero*). Existe à l'international avec un identifiant de 4 octets ; la société iKey LLC a
vraisemblablement produit aussi une variante à 7 octets (en attente de confirmation qu'il s'agit de la même puce).
Prend également en charge la lecture par backdoor (aucune clé nécessaire) et l'effacement.

**OTP 2.0** (RU ; vendue aussi sous le nom **MF** pour le marché ukrainien). Selon iKey LLC, c'est leur propre
conception. **One time programmable** : après la première écriture (via la backdoor), la puce se verrouille et se
comporte comme une véritable MFC. Possède un **PRNG difficile**.

::: tip Note de l'auteur
Le tag ne correspond pas totalement à une véritable MFC et se comporte différemment sous contrainte, ce qui a permis
à Iron Logic de construire un filtre contre lui. Le fonctionnement de ce filtre était inconnu de l'auteur au moment
de la rédaction.
:::

**MF-4** (RU). Une OTP 2.0 améliorée. Également **one time programmable** après la première écriture par backdoor,
**PRNG difficile**. D'après la description, elle peut :

- basculer la longueur de l'UID entre 4 et 7 octets ;
- définir des ATQA/SAK et un ATS arbitraires ;
- prendre en charge la commande PPS (qui, pour autant que l'auteur le sache, ne fait pas du tout partie du protocole
  MFC).

### Gen1b

Comme la Gen1, mais fonctionne dès la commande `40` (7 bits). L'auteur n'a pas personnellement vu de puces UID Gen1b
pour MFC 1K.

**M1-4K** : une puce destinée à copier les **MIFARE Classic 4K**. Se comporte à la fois comme **Gen1b et Gen2 CUID**.
Possède un **nonce statique `f17e64cd`**.

## Gen2 (direct write)

Le bloc 0 peut être écrit directement. Elles peuvent être écrites depuis Android avec l'application
*Mifare Classic Tool*.

### CUID

Noms RU : **MF-3**, **MF3-2**, **MF-8**.

La puce principale, universelle (dans la plupart des cas) et très répandue. Elle contourne les filtres Gen1 simples,
est réinscriptible plusieurs fois et peut être écrite depuis un téléphone : c'est ce qui en a fait la favorite du
public.

::: tip Note de l'auteur
Dans l'ex-URSS, l'intérêt pour cette puce, et les détails de son comportement, importent pour les lecteurs
**Iron Logic**, qui disposent de filtres contre les cartes vierges. Ces lecteurs sont peu chers et donc partout.
Voir [Lecteurs Iron Logic](/fr/nfc/iron-logic).
:::

Beaucoup de puces sont vendues comme des « CUID », et elles peuvent différer dans leur comportement aux limites. Les
plus récentes sont les **CUID à nonce statique (MF-3.2)** : au moment de la rédaction, elles contournent tous les
filtres connus de l'ex-URSS (y compris les Iron Logic « 4 bandes »).

Noms locaux :

- **MF-3** : CUID qui contourne les filtres Iron Logic « 3 bandes ».
- **MF-8** : CUID qui ne contourne **pas** les filtres Iron Logic OTP 1.0 (un « lot défectueux » dont le numéro,
  huit, vient d'une simple modification du trois).
- **MF-3.2** : CUID à nonce statique, contourne tous les filtres Iron Logic contre les MFC.

La Chine propose aussi une **« Perfect CUID »** qui répond à la commande RATS (l'auteur n'y a trouvé aucune utilité
pratique).

## Gen3 (APDU)

Tags pilotés par des commandes APDU. Actuellement la catégorie la moins étudiée. Potentiellement configurables par
type, mais cela n'a pas été démontré. Pas de nom RU.

Vendues pour différentes variantes de MFC, selon diverses combinaisons :

- par mémoire : **MFC 1K**, **MFC 4K**, **MIFARE Mini** ;
- par longueur d'identifiant : **4 octets**, **7 octets**.

L'auteur possède les variantes MFC 1K 7b, MFC 4K 4b, MFC 4K 7b, MF Mini (S20) 4b et MF Mini (S20) 7b (la MFC 1K 4b
existe très probablement aussi) et les a utilisées à quelques reprises pour tester des hypothèses avec des
identifiants de 7 octets, avant de découvrir à quel point les puces USCUID sont configurables. Cette variété (et son
expérience avec d'autres tags) l'a amené à penser que ces puces *pourraient* être configurables par type, longueur
d'UID et taille de mémoire.

## Gen4 (configurable)

Les puces les plus avancées : un bloc de configuration contrôle le tag et son comportement.

### USCUID (GDM dans les commandes Proxmark3)

Une puce puissante et peu chère, avec la mémoire d'une MFC 1K plus des blocs cachés utilisés par certaines
configurations. Selon la configuration, elle prend en charge trois sortes de commandes de backdoor et le Direct
Write. Elle peut porter des identifiants de 4 ou 7 octets, peut renvoyer une signature MFC EV1, possède un mode
fantôme (shadow) et bien d'autres fonctions utiles.

Variantes de backdoor :

- réveil magique **Gen1a** (`40`/`43`) ;
- réveil magique **GDM** (`20`/`23`) : exactement comme la Gen1, mais avec d'autres commandes. Aucun lecteur doté
  d'un filtre contre cette backdoor n'a été observé jusqu'ici (contrairement à la Gen1a) ;
- **Magic Authentication** (sélection du tag, `8000` + CRC, authentification Crypto-1 avec la clé `000000000000`).

En connaissant les principes de configuration, vous pouvez ajuster finement la puce à des besoins précis. Avec les
backdoors Gen1a/GDM activées et des commandes de style Gen1, l'écriture ou l'effacement s'est révélé peu fiable. Les
utilisateurs de Proxmark3 devraient lire la documentation de la puce liée plus haut : comparée à l'Ultimate Magic
Card, elle coûte peu et offre beaucoup.

Configurations commerciales de l'USCUID :

| Nom | Nom RU | Comportement |
|---|---|---|
| **FUID** | *OTP* | **One time programmable** : Direct Write du bloc 0, puis le bloc se verrouille. Était commercialisée dans l'ex-URSS comme l'« OTP » d'iKey LLC, mais s'est révélée être une puce chinoise. Dans sa configuration par défaut, elle possède une backdoor **GDM**, de sorte que l'identifiant peut être changé plus d'une fois et les données lues sans clés. Début novembre 2024, des chercheurs ont signalé sur le marché chinois des versions à backdoor **verrouillée**, ce qui supprime la réutilisation. |
| **UFUID** | — | Vendue par les Chinois comme une « UID scellable ». La configuration d'origine comporte une backdoor **Gen1a**, réinscriptible plusieurs fois. Le « scellage » : les duplicateurs chinois (CopyKey, etc.) vérifient le bloc de configuration après l'écriture, puis envoient une commande qui le modifie et désactive la backdoor, transformant le tag en une MFC ordinaire. Une USCUID allégée : elle n'accepte qu'une partie de la configuration. |
| **ZUID** | — | Un tag UID réalisé sur une USCUID allégée. Au vu du prix des puces, l'intérêt de cette variante n'est pas clair. N'accepte qu'une partie de la configuration. |
| **GDM (GDMIC)** | — | A donné à l'USCUID l'un de ses premiers noms. Fonction clé : le **mode fantôme** (shadow) : dans le champ, toutes les modifications vont dans une mémoire temporaire perdue à la disparition du champ ; la fois suivante, les données proviennent de la mémoire permanente. Les Chinois la mettent en avant pour les cartes à « trajets restants » (p. ex. les remontées mécaniques). Elle n'aide **pas** face aux lecteurs utilisant des données dynamiques (p. ex. les interphones Eltis avec leurs porte-clés). |
| **GDCUID** | — | Une CUID implémentée sur une USCUID. Pas vendue séparément, mais peut apparaître lors de l'achat de CUID. |
| **M1-7B** | — | Pour écrire des MIFARE Classic 1K avec un identifiant de **7 octets**. Possède une backdoor **GDM**. En mode 7 octets, elle lit l'identifiant dans un **bloc caché** : écrire simplement un dump dans la mémoire principale peut « briquer » le tag (de façon réversible). |

Les noms **ZUID** et **GDCUID** ont été proposés par l'auteur lui-même, pendant qu'il rédigeait la documentation des
puces magiques pour Proxmark3.

### Ultimate Magic Card (GTU)

La puce la plus chère à l'heure actuelle : sa grande mémoire et ses configurations lui permettent de se faire passer
non seulement pour différents formats MIFARE Classic / Mini, mais aussi pour des MIFARE Ultralight, NTAG et autres
(même si son implémentation Ultralight est assez limitée). La configuration permet :

- de changer les **ATQA/SAK** et l'**ATS** ;
- une longueur d'**identifiant** de 4, 7 ou 10 octets ;
- le **mode fantôme** (shadow) et ses réglages ;
- d'activer/désactiver le **Direct Write** du bloc 0 ;
- de changer le **mot de passe de la backdoor** (utilisé par toutes les commandes) ;
- de définir **Version** et **Signature** ;
- de passer en **mode Ultralight** et de le configurer.

Avant l'apparition des CUID à nonce statique, l'UMC était la seule carte vierge à contourner les filtres Iron Logic
« 4 bandes ».

## Tableau récapitulatif

![Tableau comparatif](/img/remote/a29bf09269c612bb.jpg)

La version complète et tenue à jour se trouve dans le
[tableau Google Sheets](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
de l'auteur.

Si vous craignez d'acheter la mauvaise puce en Chine, l'auteur recommande la boutique
[FlipperMarket](https://flipper.market/catalog#services-3), où les principaux tags nécessaires dans la CEI (et
inscriptibles par le Flipper) sont sélectionnés et vendus par un vendeur expérimenté.

## Ce que le Flipper peut écrire

D'après la documentation officielle, le Flipper Zero (via l'application **NFC Magic**) écrit les cartes magiques
**Gen1**, **Gen2** et **Gen4**, ainsi que les cartes **MIFARE Classic ordinaires** (sans changer l'UID) :

| Carte vierge | Peut être configurée en |
|---|---|
| Gen1 | MIFARE Classic 1K |
| Gen2 | MIFARE Classic 1K, MIFARE Classic 4K (une carte Gen2 compatible est requise) |
| Gen4 (Ultimate) | n'importe quelle MIFARE Classic, MIFARE Ultralight EV1/EV2, NTAG203, NTAG213, NTAG215, NTAG216 |

::: tip Unleashed
La version Unleashed de **NFC Magic 2.0** détecte et écrit en plus les cartes vierges Ultralight/NTAG **USCUID-UL**
(UL11, UL21 / « Ultra », NTAG213/215/216, UL-C, UL-5) et rapporte des résultats honnêtes
*Success / Partial / Fail*. Voir [NFC Magic 2.0](/fr/nfc/nfc-magic).
:::

### Cloner une carte en bref

1. [Lisez](/fr/nfc/read) et enregistrez l'originale. Assurez-vous que **tous** les secteurs/pages ont été lus
   (récupérez les clés avec [MFKey32](/fr/nfc/mfkey), les [attaques nested](/fr/nfc/nested-fudan) ou
   [qUnleashed](/fr/nfc/qunleashed) si nécessaire).
2. Choisissez une carte vierge que le lecteur cible accepte (voir ci-dessus : la Gen1 est filtrée presque partout).
3. Écrivez-la avec [NFC Magic](/fr/nfc/nfc-magic).

::: tip Légal
Ne copiez que vos propres identifiants, ou avec une autorisation explicite.
:::

## Voir aussi

[NFC Magic 2.0](/fr/nfc/nfc-magic) · [MIFARE Classic](/fr/nfc/mifare-classic) · [Lecteurs Iron Logic](/fr/nfc/iron-logic) ·
[Filtres des lecteurs Vizit](/fr/nfc/vizit-filters)
