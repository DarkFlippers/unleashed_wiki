---
title: Flipper comme nouvelle télécommande
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually]
sources: [unleashed-docs, unleashed-src]
---
# Utiliser le Flipper comme nouvelle télécommande Sub-GHz

Cette page explique comment transformer le Flipper en **télécommande entièrement neuve** et l'enregistrer dans le récepteur de votre portail, de votre garage ou de vos volets, exactement comme vous enregistreriez une télécommande de rechange achetée en magasin. Il **ne s'agit pas** de clonage.

::: warning
N'utilisez ceci que sur des récepteurs que vous possédez ou que vous êtes autorisé à gérer.
:::

## Clone ou nouvelle télécommande ? {#clone-or-new}

- **Télécommandes à code tournant (dynamique)** : BFT, Erreka, FAAC, Nice, CAME Atomo, Somfy, KeeLoq et tout le reste de cette page. Chaque appui émet un nouveau code construit à partir d'un compteur, et le récepteur n'accepte qu'un compteur qui a avancé. Un clone partage le compteur de l'originale : les deux se le disputent donc, celle sur laquelle vous avez appuyé en dernier fonctionne et l'autre a besoin de plusieurs appuis pour rattraper son retard (voir [Codes tournants](/fr/subghz/rolling-codes)). C'est pourquoi on fabrique une **nouvelle** télécommande. Elle obtient son propre numéro de série et son propre compteur, et cohabite avec vos télécommandes d'origine.
- **Télécommandes à code statique (fixe)** : CAME 12/24 bit, Nice Flo, Princeton, Marantec, Holtek, Roger, Gate TX et les autres protocoles statiques. Il n'y a pas de compteur, donc **le clonage ne pose aucun problème** : la copie est identique et les deux continuent de fonctionner, dans n'importe quel ordre. Utilisez simplement `Sub-GHz → Read` et enregistrez (voir [Lire des signaux](/fr/subghz/read)). Vous n'avez besoin de cette page que si vous voulez une télécommande avec son propre code distinct.

## À lire d'abord {#read-first}

**Ce que fait Add Manually.** `Main Menu → Sub-GHz → Add Manually` construit une nouvelle télécommande avec un numéro de série généré aléatoirement et l'enregistre dans un fichier. Rien n'est émis avant que vous ouvriez ce fichier et appuyiez sur une touche. Vos télécommandes d'origine ne sont pas touchées.

::: tip Unleashed : Add Manually en deux étapes
Dans le firmware Unleashed actuel, le menu se fait en deux étapes :
1. Choisissez le **système** dans la liste, par exemple `BFT Mitto`, `KL: DoorHan` ou `Somfy Telis`.
2. Choisissez la **bande** (fréquence + modulation). Les bandes propres au système sont en haut, par exemple `433.92 AM650` ou `868.35 AM650`. Toutes les autres bandes sont listées en dessous, pour les installations qui en utilisent une inhabituelle : `433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`, `868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`, `430.50 AM650`.

Vous nommez ensuite le fichier et il est enregistré dans `/ext/subghz/`. Les guides plus anciens écrivent des choses comme « BFT Mitto 433MHz » en une seule entrée de menu. Aujourd'hui, c'est `BFT Mitto` → `433.92 AM650`.
:::

**Si votre système n'est pas sur cette page, le Flipper peut malgré tout le prendre en charge.** Parcourez la liste `Add Manually`. Si votre marque y figure, créez une télécommande et suivez les étapes de programmation du *manuel de votre récepteur*. La liste complète des protocoles est dans [Systèmes pris en charge](/fr/subghz/supported-systems), et chaque entrée du menu est décrite dans [Add Manually](/fr/subghz/add-manually).

**Read et Add Manually sont deux tâches différentes.** `Read` capture et rejoue une télécommande que vous possédez déjà. `Add Manually` crée une nouvelle télécommande qui peut être enregistrée dans le récepteur. Beaucoup de protocoles ne prennent en charge que `Read`.

**Les touches du Flipper sont les boutons de la télécommande d'origine.** Quand un fichier de télécommande est ouvert (`Saved → fichier → Emulate`) :

| Touche du Flipper | Ce qu'elle émet |
|---|---|
| <kbd>OK</kbd> (affichée comme `Send`) | le bouton principal de la télécommande |
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | les autres boutons de la télécommande (boutons personnalisés) |

L'association entre flèche et bouton dépend du protocole. Un bouton *caché* ou *de programmation* de la télécommande d'origine (un trou d'épingle en retrait, deux boutons maintenus ensemble, des pastilles à ponter à l'intérieur du boîtier) devient **un seul appui de touche** sur le Flipper. Chaque section ci-dessous indique de quelle touche il s'agit, et le [tableau de référence](#programming-hidden-button-reference) les liste toutes.

L'application [Sub-GHz Remote](/fr/subghz/remote) émet ces mêmes boutons : chaque emplacement d'une carte possède un réglage `Button` (`Default`, `Up`, `Down`, `Left`, `Right`), un bouton caché peut donc occuper une touche à lui seul.

**Maintenez la touche enfoncée.** Le Flipper n'émet que tant qu'une touche est maintenue. Un appui rapide émet souvent un code incomplet. Maintenez-la 1 à 3 secondes, sauf si une étape indique autre chose.

**Le minutage compte.** La plupart des récepteurs ouvrent une fenêtre de programmation de 5, 10 ou 30 secondes. Lisez toute la procédure avant de commencer.

::: danger
Sur de nombreux récepteurs, maintenir le bouton de programmation **trop longtemps** efface toutes les télécommandes qu'il connaît, et pas seulement une. Il faut alors réenregistrer toutes vos télécommandes d'origine. Quand une étape dit « environ 1 seconde », ne maintenez pas pendant cinq.
:::

::: info Done! / Done?
Une procédure se terminant par **Done!** a été confirmée comme fonctionnelle. **Done?** signifie qu'elle provient du manuel du fabricant mais que personne n'a encore confirmé. Elle devrait fonctionner. Si ce n'est pas le cas, signalez-le à l'équipe Unleashed dans les issues GitHub.
:::

**Add Manually [Advanced]** est l'entrée de menu juste en dessous de `Add Manually`. Utilisez-la lorsque vous devez saisir des valeurs à la main au lieu d'obtenir un numéro de série aléatoire. Après le système et la bande, elle demande, en hexadécimal, `Enter SERIAL in hex`, `Enter BUTTON in hex`, `Enter COUNTER in hex` et, sur les protocoles qui en utilisent un, `Enter SEED in hex`. Nice O-Code demande `IC` (et `CERT`) à la place. FAAC FIX, Monarch, Phantom/Hiland et DEA Mio demandent `DISC.` (discriminateur) au lieu de SEED.

## Trouvez votre système {#find-your-system}

| | | |
|---|---|---|
| [Alutech AT4N](#alutech-at4n-an-motors) | [AN-Motors AT4](#an-motors-at4) | [Aprimatic TR](#aprimatic-tr) |
| [Beninca ARC (TO.GO)](#beninca-arc-to-go) | [BFT Mitto](#bft-mitto) | [CAME Atomo](#came-atomo) |
| [Cardin S449](#cardin-s449) | [DEA Mio](#dea-mio) | [Ditec GOL4](#ditec-gol4) |
| [DoorHan](#doorhan) | [Erreka IRIS](#erreka-iris) | [FAAC RC, XT](#faac-rc-xt) |
| [FAAC SLH](#faac-slh) | [Genius (SLH)](#genius-slh) | [Genius TX4RC](#genius-tx4rc-bravo-echo) |
| [Hormann EcoStar](#hormann-ecostar) | [Jarolift](#jarolift) | [KingGates Stylo 4k](#kinggates-stylo-4k) |
| [Mhouse](#mhouse) | [Nice Flor S](#nice-flor-s) | [Nice One](#nice-one) |
| [Nice O-Code](#nice-o-code) | [Nice Smilo](#nice-smilo) | [Security+ 1.0 / 2.0](#security-1-0-2-0-chamberlain-liftmaster-craftsman) |
| [Somfy Keytis](#somfy-keytis) | [Somfy Telis](#somfy-telis) | [Sommer](#sommer) |
| [V2 Phoenix (Phox)](#v2-phoenix-phox) | | |

Pas dans la liste ? Voir le [tableau de référence](#programming-hidden-button-reference). Il couvre toutes les autres entrées du menu `Add Manually`.

---

## Alutech AT4N (AN-Motors) {#alutech-at4n-an-motors}

- **Créez-la :** `Sub-GHz → Add Manually → Alutech AT4N → 433.92 AM650`

À utiliser pour les cartes avec un afficheur et les boutons `F`, `CL`, `+`, `-`. Si votre carte a un bouton `Learn` à la place, utilisez [AN-Motors AT4](#an-motors-at4).

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Ouvrez le boîtier du récepteur, trouvez le bouton `F` et maintenez-le environ 3 s. L'afficheur indique `Pr`.
3. Appuyez encore quelques fois sur `F` jusqu'à ce que l'afficheur indique `Lr`.
4. Choisissez un numéro de télécommande libre avec `+` / `-`. Un numéro déjà attribué à une télécommande affiche un point rouge dans le coin inférieur droit.
5. Appuyez une fois sur <kbd>OK</kbd> (`Send`) sur le Flipper. L'afficheur clignote et un point rouge apparaît à côté de ce numéro.
6. Maintenez `F` sur la carte environ 3 s pour quitter le mode programmation.
7. Done!

[Tutoriel vidéo, montre aussi d'autres types de cartes (en russe)](https://www.youtube.com/watch?v=XrOVVYhFXDg)

## AN-Motors AT4 {#an-motors-at4}

- **Créez-la :** `Sub-GHz → Add Manually → AN-Motors AT4 → 433.92 AM650`
- **Touche de programmation :** <kbd>→</kbd> = `0xC`

À utiliser pour les cartes plus anciennes avec un bouton `Learn`. Si votre carte a `F`, `CL`, `+`, `-` à la place, utilisez [Alutech AT4N](#alutech-at4n-an-motors).

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Ouvrez le boîtier du récepteur et appuyez une fois sur `Learn`. La LED s'allume.
3. Appuyez une fois sur `Send` sur le Flipper. La LED de la carte s'éteint.
4. Appuyez de nouveau sur `Send`. La LED se met à clignoter. Attendez quelques secondes qu'elle s'éteigne.
5. Done!

[Tutoriel vidéo (en russe)](https://www.youtube.com/watch?v=URVMtTELcnU)

## Aprimatic TR {#aprimatic-tr}

- **Créez-la :** `Sub-GHz → Add Manually → KL: Aprimatic → 433.92 AM650`
- **Touche de programmation :** <kbd>→</kbd> = `0xF` (sur l'originale, les 4 boutons maintenus ensemble)

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Sur une télécommande existante qui fonctionne déjà avec le récepteur, appuyez simultanément sur les 4 boutons.
3. Le récepteur émet un bip continu.
4. Appuyez sur `Send` sur le Flipper et maintenez environ 2 s.
5. Attendez que le récepteur cesse de biper.
6. Done?

## Beninca ARC (TO.GO) {#beninca-arc-to-go}

- **Vendue aussi sous le nom de :** TO.GO 2VA / 4VA (auparavant TO.GO 2WV / 4WV). Récepteurs WB, WI et récepteurs intégrés à l'armoire de commande.
- **Créez-la :** `Sub-GHz → Add Manually → Beninca ARC → 433.92 AM650`
- **Touche de programmation :** **<kbd>↓</kbd>** = `0x0`, le bouton caché

Sur une originale à 2 boutons, le bouton caché correspond au maintien simultané des deux boutons, ce qui est difficile à réussir de façon fiable. Sur le Flipper, c'est simplement <kbd>↓</kbd>.

### Avec une télécommande fonctionnelle : récepteurs WB / WI {#beninca-wb-wi}

1. Tenez-vous près du récepteur.
2. Ouvrez le fichier de la télécommande qui fonctionne déjà. Appuyez sur <kbd>↓</kbd> et maintenez environ 3 s. La fonction cachée est maintenant active (sur une télécommande d'origine, la LED clignote à ce moment-là).
3. Dans les 5 s, appuyez sur `Send` sur cette même télécommande pour le canal que vous voulez partager.
4. Dans les 5 s, ouvrez le fichier de votre nouvelle télécommande et appuyez sur `Send`. Ce bouton commandera ce canal.
5. Le récepteur quitte le mode programmation. Testez la nouvelle télécommande.
6. Done?

### Avec une télécommande fonctionnelle : récepteur intégré à l'armoire de commande {#beninca-panel}

Ici, le bouton caché doit être émis depuis **les deux** télécommandes :

1. Télécommande fonctionnelle : <kbd>↓</kbd>, puis `Send` dans les 5 s.
2. Nouvelle télécommande : <kbd>↓</kbd>, puis `Send` dans les 5 s.
3. Done?

::: info
Les télécommandes ARC et HCS (code tournant) ne peuvent pas partager un même récepteur. La première télécommande que vous enregistrez détermine le type que le récepteur acceptera ensuite. En changer nécessite une réinitialisation complète du récepteur.
:::

## BFT Mitto {#bft-mitto}

- **Créez-la :** `Sub-GHz → Add Manually → BFT Mitto → 433.92 AM650`
- **Touche de programmation :** <kbd>→</kbd> = `0xF` (sur l'originale, le trou d'épingle au dos ou les boutons 1+2 maintenus ensemble)

::: info Seed
**Les télécommandes BFT Mitto récentes dérivent leur Seed du numéro de série** : un simple `Sub-GHz → Read` les décode donc à la volée. Elles apparaissent immédiatement comme `KL: BFT`.
**Les modèles plus anciens ont un Seed unique** et apparaissent comme `KL: Unknown` jusqu'à ce que vous l'ayez. Il y a deux façons de le récupérer :
- Maintenir 2 boutons et lire la valeur `Hop`. La télécommande émet son Seed en clair (voir [Fabriquer un clone complet](#making-a-full-clone-reads-the-seed-off-your-original)).
- [Seed Capturer](/fr/subghz/seed-capturer) + qUnleashed.
:::

### Avec une télécommande fonctionnelle {#bft-with-remote}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Tenez-vous à au moins 3 m du récepteur.
3. **Télécommande d'origine :** appuyez avec une épingle sur le bouton caché au dos, ou appuyez simultanément sur les boutons 1 et 2, jusqu'à ce que la LED de la télécommande s'allume.
4. **Télécommande d'origine :** appuyez brièvement sur le bouton qui ouvre l'appareil.
5. Sur le Flipper, faites un appui long sur <kbd>→</kbd> (`0xF`, affiché comme `Btn:F`) pendant 3 à 5 s.
6. Appuyez sur la touche du Flipper que vous voulez utiliser pour ouvrir l'appareil.
7. Appuyez de nouveau sur <kbd>→</kbd>.
8. Done?

### Avec accès au boîtier du récepteur {#bft-with-receiver}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Ouvrez le boîtier de la carte du récepteur.
3. [Regardez d'abord cette vidéo](https://www.youtube.com/watch?v=5QXMBKI_-Ls). Elle montre la procédure du côté de la carte.
4. Sur le Flipper, faites un appui long sur <kbd>→</kbd> (`0xF`) pendant 3 à 5 s. Cela fait exactement ce que fait le maintien des boutons 1 et 2 sur la télécommande d'origine dans la vidéo.
5. Done?

### Fabriquer un clone complet (lit le Seed sur votre originale) {#making-a-full-clone-reads-the-seed-off-your-original}

::: danger
Cela crée une copie qui **entre en conflit avec votre télécommande d'origine** sur le compteur. Votre originale peut même cesser de fonctionner jusqu'à ce qu'elle soit réenregistrée. Ne faites cela que si l'originale est cassée ou usée et que le Flipper est censé la remplacer.
:::

1. Ouvrez `Sub-GHz → Read`.
2. **Sur la télécommande d'origine uniquement :** maintenez tous les boutons à la fois (les deux sur une télécommande à 2 boutons, les deux de la rangée du haut sur une télécommande à 4 boutons), ou appuyez sur le bouton caché avec une épingle.
3. Vous recevez un signal. Ouvrez-le et regardez `Fix:`. Il commence par `F`, par exemple `F00F1C9B`. Le `F` de tête est le code de bouton signifiant « bouton de programmation appuyé ».
4. La valeur `Hop:` de ce même signal est votre Seed.
5. Notez la valeur `Hop` et remplacez son premier chiffre `F` par `0`.
6. Appuyez maintenant sur le bouton de votre télécommande que vous voulez réellement cloner, et lisez ce signal.
7. Notez son `Fix:`. Son premier chiffre correspond au `Btn:` affiché pour le signal.
8. Créez la télécommande avec `Sub-GHz → Add Manually [Advanced] → BFT Mitto → 433.92 AM650` et saisissez :
   - `SERIAL` : le `Fix` de l'étape 7 avec son **premier** chiffre remplacé par `0`
   - `BUTTON` : le premier chiffre de ce `Fix`
   - `COUNTER` : `FF F9`
   - `SEED` : la valeur de l'étape 5
9. Un compteur élevé comme `FF F9` dépasse celui de votre originale. Cela fait fonctionner le clone immédiatement, et c'est aussi ce qui désynchronise l'originale.

**Ou éditez plutôt un fichier enregistré.** Enregistrez le signal de votre télécommande d'origine (une ancienne apparaît comme `KL: Unknown`), copiez le fichier sur un ordinateur et ajoutez ces deux lignes après la ligne `Key: ...` :

```text
Seed: 0X XX XX XX
Manufacture: BFT
```

Remplacez les `X` par les chiffres du Seed de l'étape 4 et recopiez le fichier. Vous avez désormais un clone exact avec le même compteur.

### Pas de bouton caché, ou il n'émet pas le Seed {#bft-no-hidden-button}

Ceci ne s'applique qu'aux télécommandes à Seed unique. Une télécommande qui apparaît déjà comme `KL: BFT` n'a rien à récupérer. Si vous ne parvenez pas à mettre l'originale en mode programmation, utilisez l'application [Seed Capturer](/fr/subghz/seed-capturer) : choisissez `BFT Mitto` à 433.92 MHz, appuyez à répétition sur un bouton, puis récupérez le Seed dans qUnleashed.

## CAME Atomo {#came-atomo}

- **Vendue aussi sous le nom de :** TOP42R / TOP44R / TOP44RGR (806TS-0130)
- **Créez-la :** `Sub-GHz → Add Manually → CAME Atomo → 433.92 AM650` (ou `868.35 AM650`)

::: warning
Avec CAME Atomo, maintenez toujours `Send` pendant **au moins 2 secondes**. Le protocole a besoin de ce temps pour émettre le code en entier.
:::

### Avec une télécommande fonctionnelle (ou sa copie sur le Flipper) {#atomo-with-remote}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Tenez-vous à au moins 3 m du récepteur.
3. **Télécommande d'origine :** appuyez et maintenez le bouton associé à ce récepteur pendant environ 10 s.
4. Vous avez maintenant environ 20 s pour ajouter la nouvelle télécommande.
5. Faites un appui long sur `Send` dans le fichier de la nouvelle télécommande pendant 3 à 4 s, puis relâchez. Cela l'enregistre.
6. Attendez 20 s, puis appuyez de nouveau sur `Send` et maintenez. Elle devrait maintenant commander le récepteur.
7. Done!

### Avec accès au boîtier du récepteur {#atomo-with-receiver}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Ouvrez le boîtier du récepteur et trouvez le bouton de programmation du canal dont vous avez besoin. Certains récepteurs ont plusieurs canaux. Un RE432M / RE862M, par exemple, en a deux, chacun avec ses propres télécommandes et boutons. Appuyez sur `1` ou `2` sur la carte pour entrer en mode programmation pour ce canal.
3. Faites un appui long sur `Send` sur le Flipper pendant 3 à 4 s, puis relâchez.
4. Appuyez une fois sur `CLEAR` pour quitter le mode programmation, ou attendez environ 20 s.
5. Done!

::: info
Les télécommandes CAME statiques 12/24 bits et CAME TWEE ne peuvent pas ouvrir le mode programmation, et elles ne peuvent pas être enregistrées dans une fenêtre ouverte par une télécommande Atomo. Seules les télécommandes Atomo peuvent le faire.
:::

[Tutoriel vidéo (en russe)](https://www.youtube.com/watch?v=XeHUwfcSS30)

## Cardin S449 {#cardin-s449}

- **Vendue aussi sous le nom de :** S449 QZ1 / QZ2 / QZ4, TXQ449100 / TXQ449200. Récepteurs RCQ449.
- **À lire avec :** la modulation `FM12K`, **et non** AM650
- **Créez-la :** `Sub-GHz → Add Manually → KL: Cardin S449 → 433.92 FM12K`
- **Touche de programmation :** <kbd>→</kbd> = `0xD` (sur l'originale, le bouton dans le petit trou sous les touches)

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Tenez-vous à 1–2 m du récepteur.
3. Ouvrez le fichier de la télécommande qui fonctionne déjà. Appuyez sur <kbd>→</kbd> et relâchez-la quand le récepteur émet un bip court.
4. Appuyez une fois sur `Send` sur cette même télécommande. Le récepteur émet un autre bip court.
5. Ouvrez le fichier de votre nouvelle télécommande et appuyez sur `Send`. Le récepteur émet deux bips d'affilée.
6. Relâchez la touche. Le récepteur émet un bip plus long.
7. Attendez au moins 10 s, puis essayez la nouvelle télécommande.
8. Done?

**En cas d'échec**, ou si vous entendez un bip long avant l'étape 5, attendez 20 s et reprenez à l'étape 3.

## DEA Mio {#dea-mio}

- **Créez-la :** `Sub-GHz → Add Manually → KL: DEA Mio → 433.92 AM650`
- **Touche de programmation :** <kbd>→</kbd> = `0xF`, le bouton caché

1. Ouvrez le fichier de votre nouvelle télécommande.
2. `Send` agit comme l'un des boutons normaux. C'est celui que vous enregistrez.
3. <kbd>→</kbd> agit comme le bouton caché de la télécommande d'origine.
4. Suivez les instructions de votre fabricant pour ajouter une télécommande, en utilisant ces deux touches à la place des boutons de l'originale.

## Ditec GOL4 {#ditec-gol4}

- **Vendue aussi sous le nom de :** GOL4 / GOL4C. Récepteurs BIXLG4, BIXLP2, BIXLS2, BIXR2.
- **Créez-la :** `Sub-GHz → Add Manually → Ditec GOL4 → 433.92 AM650`
- **Touche de programmation :** <kbd>→</kbd> = `0x0`, le bouton caché

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Ouvrez le boîtier du récepteur. Appuyez puis relâchez `PRG`. La LED `SIG` s'allume et reste allumée.
3. Appuyez sur `Send` sur le Flipper pour le canal que vous voulez mémoriser.
4. `SIG` clignote pendant la mémorisation. Quand elle est de nouveau fixe, vous pouvez ajouter une autre télécommande.
5. La mémorisation se termine 10 s après la dernière télécommande, ou appuyez de nouveau sur `PRG` pour quitter immédiatement.
6. Done?

::: info
Sur certaines cartes, un cavalier du récepteur doit être positionné pour que la programmation fonctionne du tout. Consultez le manuel de votre récepteur.
:::

## DoorHan {#doorhan}

- **Créez-la :** `Sub-GHz → Add Manually → KL: DoorHan → 433.92 AM650` (ou `315.00 AM650`)

### Trouver d'abord votre fréquence {#doorhan-frequency}

DoorHan utilise soit 315.00, soit 433.92 MHz. Créez une télécommande sur l'une des deux, ouvrez-la et appuyez sur `Send` en observant le récepteur. Si vous avez deviné juste, le voyant du récepteur s'allume tant que vous maintenez la touche et s'éteint quand vous relâchez. Si rien ne se produit, essayez l'autre bande. Vous pouvez aussi simplement lire votre télécommande existante avec `Sub-GHz → Read`.

### Avec accès au boîtier du récepteur {#doorhan-with-receiver}

Retirez le capot de protection et regardez les boutons :

- **4 boutons (`Radio`, `Reverse`, `Auto`, …) :** maintenez `Radio` jusqu'à ce que la LED s'allume, puis appuyez 2 fois sur `Send` sur le Flipper. La LED s'éteint.
- **4 boutons (`R`, `P`, `+`, `-`) et un afficheur :** appuyez sur `R`, appuyez 2 fois sur `Send`, attendez environ 10 s.
- **4 boutons (`+`, `-`, `F`, `TR`) et un afficheur :** appuyez sur `TR`, appuyez 2 fois sur `Send`, attendez environ 10 s.
- **Tout autre cas :** maintenez `P` environ 2 s jusqu'à ce que la LED clignote, puis appuyez 2 fois sur `Send`. La LED s'éteint.

Dans tous les cas, attendez que le récepteur revienne en mode normal avant de tester.

### Avec une télécommande d'origine en main {#doorhan-with-original}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Tenez-vous à 1–2 m de la carte du récepteur.
3. Sur l'ancienne télécommande, appuyez et maintenez le deuxième bouton (du bas), puis appuyez également sur le premier (du haut). Maintenez les deux pendant 1 s et relâchez.
4. Appuyez sur le bouton qui fonctionne de l'ancienne télécommande (celui qui ouvre le portail). Maintenez-le 1 s et relâchez.
5. Les étapes 3 et 4 doivent être réalisées à moins de 5 s l'une de l'autre. Ne maintenez pas trop longtemps, et ne vous précipitez pas.
6. Le récepteur bipe. Vous avez alors 10 s : appuyez 2 fois sur `Send` sur la nouvelle télécommande, en maintenant au moins 1 s à chaque fois.
7. Le récepteur bipe de nouveau. La nouvelle télécommande est enregistrée.
8. Done!

### Avec une copie de votre télécommande d'origine sur le Flipper {#doorhan-with-copy}

1. Ouvrez le fichier de votre télécommande **existante (originale)**.
2. Tenez-vous à 1–2 m de la carte du récepteur.
3. Appuyez sur <kbd>←</kbd> (`0x8`), maintenez 1 s, relâchez. Puis appuyez sur <kbd>→</kbd> (`0xA`), maintenez 1 s, relâchez.
4. Appuyez sur le bouton qui fonctionne (<kbd>OK</kbd>, `Send`), maintenez 1 s, relâchez.
5. Les étapes 3 et 4 doivent être réalisées à moins de 5 s l'une de l'autre.
6. Le récepteur bipe. Appuyez sur <kbd>Back</kbd> et ouvrez le fichier de votre **nouvelle** télécommande. Dans les 10 s, appuyez 2 fois sur `Send`, en maintenant au moins 1 s à chaque fois.
7. Le récepteur bipe de nouveau. La nouvelle télécommande est enregistrée.
8. Done!

[Tutoriel vidéo (en russe)](https://www.youtube.com/watch?v=wZ5121HYv50) et [un second](https://www.youtube.com/watch?v=1ucrDKF3vWc)

::: tip
Si un récepteur DoorHan s'est désynchronisé de votre fichier, Unleashed propose des modes de compteur à resynchronisation forcée pour DoorHan. Voir [Modes de compteur](/fr/subghz/counter-mode).
:::

## Erreka IRIS {#erreka-iris}

- **Vendue aussi sous le nom de :** IRIS IR02 / IR04 sur 433.92 MHz, IR02/868 / IR04/868 sur 868.35 MHz
- **Créez-la :** `Sub-GHz → Add Manually → Erreka → 433.92 AM650` pour les IR02 / IR04, ou `868.35 AM650` pour les modèles /868
- **Touche de programmation :** <kbd>→</kbd> = `0xF` (sur l'originale, en pontant les broches `1` et `5` du connecteur à 5 voies accessible sur le flanc de la télécommande)

Erreka IRIS est une télécommande à code tournant : du KeeLoq avec un Seed secret. Les deux méthodes d'enregistrement du fabricant fonctionnent depuis le Flipper.

### Avec accès au boîtier du récepteur {#erreka-with-receiver}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Activez le mode programmation sur le récepteur, généralement avec un bouton sur la carte.
3. Appuyez une fois sur `Send` sur le Flipper. Le récepteur bipe **deux fois** si la télécommande a été mémorisée.
4. Répétez l'étape 3 pour les autres télécommandes.
5. Désactivez le mode programmation.
6. Done!

### Avec une télécommande fonctionnelle {#erreka-with-remote}

L'IRIS d'origine ouvre la fenêtre de programmation quand on ponte les broches `1` et `5`. Elle émet alors son Seed en clair, et le récepteur répond par un bip. Sur le Flipper, c'est simplement <kbd>→</kbd>.

La télécommande qui ouvre la fenêtre doit être une que le récepteur connaît déjà : soit la première télécommande Flipper que vous avez enregistrée via le bouton du récepteur, soit votre télécommande d'origine dont le Seed a été récupéré (voir ci-dessous).

1. Ouvrez le fichier de la télécommande Erreka enregistrée.
2. Faites un appui long sur <kbd>→</kbd> (`0xF`) pendant environ 2 s. Le récepteur bipe **une fois** et est prêt à mémoriser des codes.
3. Dans les 10 s, appuyez sur <kbd>Back</kbd> et ouvrez le fichier de votre nouvelle télécommande.
4. Appuyez sur `Send`. Le récepteur bipe **deux fois** si la télécommande a été mémorisée.
5. Si 10 s passent sans rien mémoriser, le récepteur quitte le mode programmation. Reprenez à l'étape 2.
6. Done?

### Si la nouvelle télécommande ne s'enregistre pas {#erreka-shared-seed}

Certaines installations donnent **le même Seed à toutes les télécommandes** parce que l'installateur les a programmées comme un ensemble. Dans ce cas, une télécommande avec un Seed aléatoire n'est jamais acceptée. La solution consiste à conserver le Seed existant et à ne changer que le numéro de série :

1. Récupérez le Seed sur une télécommande qui fonctionne déjà (voir ci-dessous).
2. Créez une télécommande avec `Sub-GHz → Add Manually [Advanced] → Erreka → 433.92 AM650` (ou `868.35 AM650`) et saisissez :
   - `SERIAL` : `0X XX XX XX`, n'importe quelle valeur qui ne soit pas celle d'une de vos télécommandes existantes. **Conservez le `0` de tête.** Ce quartet est le bouton, qui est demandé séparément.
   - `BUTTON` : `02`
   - `COUNTER` : `00 02`
   - `SEED` : le Seed de l'étape 1
3. Relancez l'une ou l'autre des procédures d'enregistrement.

::: tip Conservez les zéros de tête
Certains systèmes n'utilisent que les 3 ou 4 derniers chiffres du numéro de série, de sorte que leurs télécommandes ressemblent à `00 00 0A BC`. Sur ceux-là, un long numéro de série aléatoire peut être refusé. Lisez une de vos télécommandes fonctionnelles, reproduisez la forme de son numéro de série (même nombre de chiffres significatifs, zéros de tête conservés) et ne changez que les derniers chiffres. Si deux de vos télécommandes d'origine affichent le même Seed une fois récupéré, vous avez affaire à ce type d'installation, et réutiliser le Seed est la bonne approche.
:::

### Récupérer le Seed sur votre télécommande IRIS d'origine {#erreka-get-seed}

Une télécommande Erreka apparaît comme `KL: Unknown` jusqu'à ce que le Seed soit connu.

**Option 1 : ponter les broches et lire.** C'est la méthode rapide. Les broches sont à l'extérieur du boîtier.

1. Ouvrez `Sub-GHz → Read`. Dans `Config`, réglez la fréquence sur 433.92 ou 868.35 et la modulation sur `AM650`.
2. Pontez les broches `1` et `5` du connecteur à 5 voies de la télécommande d'origine.
3. Vous recevez un signal. Le constructeur apparaît comme **Unknown**. C'est normal, car le Flipper ne connaît pas encore le Seed.
4. Ouvrez le signal. `Fix:` commence par `F`, le code « bouton de programmation appuyé ».
5. **La valeur `Hop:` de ce signal est votre Seed**, en clair.
6. Soit vous la saisissez dans `Add Manually [Advanced]` comme ci-dessus, soit vous enregistrez le signal, le copiez sur un ordinateur et ajoutez ces lignes après `Key: ...` :

```text
Seed: 0X XX XX XX
Manufacture: Erreka
```

Le fichier se décode alors, et vous pouvez l'utiliser pour ouvrir la fenêtre de programmation destinée à de nouvelles télécommandes.

**Option 2 : [Seed Capturer](/fr/subghz/seed-capturer)**, quand vous ne pouvez pas ponter les broches. Choisissez `Erreka` et votre fréquence, appuyez à répétition sur un bouton, puis récupérez le Seed dans qUnleashed.

## FAAC RC, XT {#faac-rc-xt}

- **Vendue aussi sous le nom de :** XT2 / XT4 433 RC / 868 RC, et l'ancien codage RC
- **Créez-la :** `Sub-GHz → Add Manually → KL: FAAC RC,XT → 433.92 AM650` (ou `868.35 AM650`)
- **Touche de programmation :** <kbd>→</kbd> = `0xB` (sur l'originale, les boutons 1+2 maintenus ensemble, l'appui « master »)

::: warning
Il s'agit de KeeLoq, pas de SLH. Lisez d'abord votre télécommande. Si le Flipper l'appelle `KL: FAAC_RC,XT`, vous êtes au bon endroit. S'il indique `FAAC SLH`, allez à [FAAC SLH](#faac-slh).
:::

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Tenez-vous près du récepteur.
3. Ouvrez le fichier de la télécommande qui fonctionne déjà. Appuyez sur <kbd>→</kbd> et maintenez environ 1 à 2 s (jusqu'au moment où la LED de l'originale se mettrait à clignoter), puis relâchez.
4. Pendant que la fenêtre est ouverte, appuyez sur `Send` sur cette même télécommande pour le bouton que vous voulez copier.
5. Ouvrez le fichier de votre nouvelle télécommande et appuyez sur `Send`.
6. Répétez les étapes 3 à 5 pour chacun des autres boutons.
7. Done?

::: info
Seule une télécommande **master** peut transmettre son code système. Sur une télécommande d'origine, observez la LED quand vous appuyez sur un bouton. Un bref clignotement avant qu'elle ne devienne fixe signifie master. Fixe d'emblée signifie slave. Avec une slave, enregistrez plutôt la nouvelle télécommande sur le récepteur.
:::

## FAAC SLH {#faac-slh}

- **Créez-la :** `Sub-GHz → Add Manually → FAAC SLH → 433.92 AM650` (ou `868.35 AM650`)
- **Touche de programmation :** **<kbd>↑</kbd>** émet le signal de programmation

### Avec accès au boîtier du récepteur {#faac-slh-with-receiver}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Ouvrez le boîtier du récepteur et trouvez le bouton de programmation sur la carte.
3. Maintenez <kbd>↑</kbd> sur le Flipper et, en même temps, appuyez et maintenez le bouton de programmation sur la carte.
4. La LED de la carte s'allume, s'éteint, s'allume, s'éteint, puis s'allume de nouveau.
5. Relâchez tout.
6. Appuyez deux ou trois fois sur `Send` sur le Flipper, en maintenant chaque appui 1 à 3 s.
7. Done!

[Tutoriel vidéo](https://www.youtube.com/watch?v=NfZmMy37XUs)

### Avec une télécommande master, sans ouvrir le boîtier {#faac-slh-with-master}

FAAC peut enregistrer de nouvelles télécommandes depuis une télécommande master existante, et le Flipper peut y prendre part. Lisez d'abord le Seed sur la master :

1. Ouvrez `Sub-GHz → Read`. Réglez la fréquence sur 868.35 ou 433.92 et la modulation sur `AM650`.
2. Maintenez deux boutons de la télécommande master d'origine jusqu'à ce que sa LED s'allume.
3. Cliquez sur l'unique bouton dont vous voulez le Seed. **Le Seed est différent pour chaque bouton.**
4. Vous recevez un signal. Ouvrez-le et notez le Seed.
5. Créez la télécommande avec `Sub-GHz → Add Manually [Advanced] → FAAC SLH → 433.92 AM650` (ou 868.35) et saisissez :
   - `SERIAL` : `0A 0R RR RR`, en remplaçant chaque `R` par n'importe quel chiffre
   - `BUTTON` : `06`
   - `COUNTER` : `00 00 00 02`
   - `SEED` : le Seed de l'étape 4
6. Le Flipper agit maintenant comme une nouvelle télécommande. Appuyez deux ou trois fois sur `Send` près du récepteur pour l'enregistrer.
7. Done!

### Si aucune des deux options n'est possible {#if-neither-of-those-is-possible}

- **La programmation radio du récepteur est désactivée.** Certains installateurs la coupent, et plus rien ne s'enregistre.
- **Votre télécommande est une slave, pas une master.** Seule une master peut émettre le code de programmation.

Dans les deux cas, la seule voie restante est un **clone** d'une télécommande que le récepteur connaît déjà, ce qui nécessite le Seed. Obtenez-le avec [Seed Capturer](/fr/subghz/seed-capturer), puis construisez le clone avec le `SERIAL` et le `BUTTON` de la **télécommande d'origine**.

::: tip Où se trouvent SERIAL et BUTTON à l'intérieur de Fix
- **FAAC SLH et Genius :** `BUTTON` est le **dernier** chiffre du `Fix`. `SERIAL` est le reste, avec un `0` devant.
- **KeeLoq** (BFT, Erreka, DoorHan, Cardin et les autres entrées `KL:`) : `BUTTON` est le **premier** chiffre du `Fix`. `SERIAL` est le même `Fix` avec son premier chiffre remplacé par `0`.
:::

## Genius (SLH) {#genius-slh}

- **Vendue aussi sous le nom de :** Echo TX2 433 SLH / Echo TX4 433 SLH / KILO TX2 / TX4 / JLC / Amigo
- **Créez-la :** `Sub-GHz → Add Manually → Genius → 433.92 AM650` (ou `868.35 AM650`)
- **Touche de programmation :** **<kbd>↑</kbd>** émet le signal de programmation

Genius SLH est le même paquet que FAAC SLH avec sa propre clé constructeur (une ligne `Manufacture: Genius` dans le fichier) : **[les procédures FAAC SLH](#faac-slh) s'appliquent donc exactement telles quelles**. Si la programmation est désactivée ou si votre télécommande est une slave, capturez le Seed avec [Seed Capturer](/fr/subghz/seed-capturer) (choisissez `Genius`) et construisez un clone comme décrit sous FAAC SLH.

::: warning
Ne confondez pas ceci avec `KL: Genius TX4RC`. Les modèles RC sont du KeeLoq, pas du SLH, et ont [leur propre section](#genius-tx4rc-bravo-echo). En cas de doute, lisez d'abord la télécommande.
:::

## Genius TX4RC (Bravo / Echo) {#genius-tx4rc-bravo-echo}

- **Vendue aussi sous le nom de :** Echo TX2 433 RC / Echo TX4 433 RC / TE443H Bravo
- **Créez-la :** `Sub-GHz → Add Manually → KL: Genius TX4RC → 433.92 AM650`
- **Touche de programmation :** <kbd>→</kbd> = `0xB`

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Ouvrez le boîtier du récepteur et appuyez sur `SW1` pour le canal 1 ou `SW2` pour le canal 2. `LED1` / `LED2` s'allume et reste allumée. C'est le mode apprentissage.
3. Dans les 10 s, appuyez sur `Send` sur le Flipper et maintenez au moins 1 s.
4. La LED clignote deux fois. La télécommande est mémorisée.
5. Le récepteur reste en mode apprentissage : vous pouvez donc ajouter d'autres télécommandes en répétant l'étape 3. Appuyez de nouveau sur `SW1` / `SW2` pour quitter, ou il quitte tout seul 10 s après la dernière télécommande.
6. Done?

## Hormann EcoStar {#hormann-ecostar}

- **Vendue aussi sous le nom de :** RSC2 / RSE2 / RSZ1 sur 433.92 MHz. Motorisations EcoStar Liftronic / Portronic.
- **Créez-la :** `Sub-GHz → Add Manually → KL: Hor. EcoStar → 433.92 AM650`
- **Touche de programmation :** **<kbd>↓</kbd>** = `0x6` (celle-ci est sur Bas, pas sur Droite)

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Trouvez le bouton d'effacement / programmation sur la motorisation, généralement sous le moteur, et maintenez-le environ 1 s. La LED du moteur se met à clignoter lentement.
3. Appuyez sur `Send` et maintenez environ 2 s. La LED du moteur accélère.
4. Appuyez de nouveau sur `Send` et maintenez environ 2 s. La LED clignote très vite, puis s'éteint. La télécommande est programmée.
5. Done?

::: danger
Maintenir ce bouton d'effacement environ 5 s efface **toutes** les télécommandes connues de la motorisation.
:::

## Jarolift {#jarolift}

- **Vendue aussi sous le nom de :** moteurs tubulaires radio TDEF avec télécommandes TDRC / TDRCE
- **Créez-la :** `Sub-GHz → Add Manually → Jarolift → 433.92 AM650`

Les touches sont déjà associées aux boutons de la télécommande d'origine :

| Touche du Flipper | Bouton Jarolift |
|---|---|
| <kbd>OK</kbd> (`Send`) | Down |
| <kbd>←</kbd> | Up |
| <kbd>↓</kbd> | Stop |
| **<kbd>↑</kbd>** | **Learn** (`0x1`) |

Sur l'originale, `Learn` signifie maintenir Up + Down ensemble puis appuyer sur Stop. Sur le Flipper, c'est un seul appui de touche.

### Avec accès à la tête du moteur {#jarolift-motor}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Appuyez sur le bouton d'apprentissage de la tête du moteur. Le moteur vibre brièvement et reste en mode apprentissage pendant 5 s.
3. Si vous ne pouvez pas atteindre ce bouton, débranchez le moteur du secteur et rebranchez-le. Il passe tout seul en mode apprentissage pendant 5 s.
4. Pendant ces 5 s, appuyez sur <kbd>↑</kbd> (`Learn`).
5. Le moteur vibre de nouveau. Le code a été appris.
6. Done!

### Avec une télécommande fonctionnelle {#jarolift-with-remote}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Sur la télécommande fonctionnelle, maintenez Up + Down ensemble, puis appuyez 8 fois sur Stop. Le moteur vibre brièvement.
3. Dans les 5 s, appuyez sur <kbd>↑</kbd> (`Learn`) sur le Flipper.
4. Le moteur vibre de nouveau.
5. Done?

::: tip
Si la télécommande fonctionnelle est aussi sur votre Flipper, l'étape 2 consiste simplement à appuyer sur <kbd>↑</kbd> (`Learn`) dans le fichier de cette télécommande.
:::

## KingGates Stylo 4k {#kinggates-stylo-4k}

- **Vendue aussi sous le nom de :** Stylo 2K / Stylo 4K (10S001). Récepteurs Fred, Myo.
- **Créez-la :** `Sub-GHz → Add Manually → KingGates Stylo4k → 433.92 AM650`

Il n'y a pas de bouton de programmation distinct. Les quatre touches sont les quatre canaux de l'originale :

| Touche du Flipper | Code de canal |
|---|---|
| <kbd>OK</kbd> (`Send`) | `0xE` |
| <kbd>↑</kbd> | `0xD` |
| <kbd>↓</kbd> | `0xB` |
| <kbd>←</kbd> | `0x7` |

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Ouvrez le boîtier du récepteur. Sur un `Fred` à 2 canaux, la couleur de la LED indique le canal : vert pour le canal 1, rouge pour le canal 2.
3. Appuyez une fois sur le bouton du récepteur pour le canal 1 (vert) ou deux fois pour le canal 2 (rouge). Cela lance le mode apprentissage.
4. Dans les 5 s, appuyez sur `Send` sur le Flipper pendant environ 1 s.
5. La LED s'éteint puis se rallume. La télécommande a été apprise.
6. L'apprentissage se termine après 5 s sans signal, ou appuyez de nouveau sur le bouton du récepteur.
7. Done?

## Mhouse {#mhouse}

- **Vendue aussi sous le nom de :** GTX4 / GTX4C / TX3 / TX4, ainsi que Moovo et Nice Home ECCO
- **Créez-la :** `Sub-GHz → Add Manually → KL: Mhouse → 433.92 AM650`
- **Touche de programmation :** <kbd>→</kbd> = `0xF`, le bouton supplémentaire (caché)

### Avec accès au boîtier du récepteur {#mhouse-with-receiver}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Appuyez et maintenez `P1` sur le récepteur jusqu'à ce que la LED `P1` reste allumée, puis relâchez.
3. Appuyez sur `Send` et maintenez jusqu'à ce que la LED `P1` clignote 3 fois.
4. Relâchez. Cela enregistre tous les boutons de la télécommande d'un coup (« mode 1 » de Nice).
5. Attendez 10 s avant de tester.
6. Done?

### Avec une télécommande fonctionnelle {#mhouse-with-remote}

Mhouse appartient à la même famille de récepteurs Nice que [Nice Smilo](#nice-smilo) :

1. Tenez-vous près du récepteur.
2. Ouvrez le fichier de votre nouvelle télécommande. Appuyez et maintenez `Send` pendant au moins 5 s, puis relâchez.
3. Sur la télécommande fonctionnelle, appuyez puis relâchez lentement son bouton 3 fois.
4. Ouvrez de nouveau le fichier de la nouvelle télécommande, appuyez sur `Send` pendant 1 s et relâchez.
5. Attendez 10 s avant de tester.
6. Done?

## Nice Flor S {#nice-flor-s}

- **Créez-la :** `Sub-GHz → Add Manually → Nice FloR-S → 433.92 AM650`

### Avec une télécommande fonctionnelle {#nice-flor-s-with-remote}

Vous n'avez pas besoin du boîtier du récepteur, mais **la toute première télécommande doit toujours être enregistrée avec le bouton du récepteur**. Ci-dessous, `OLD` est la télécommande autorisée et `NEW` est le Flipper. Tenez-vous à moins de 3 m du récepteur.

1. Ouvrez le fichier de votre nouvelle télécommande. Appuyez et maintenez `Send` pendant au moins 5 s (7 s sur un récepteur OXIBD), puis relâchez.
2. Sur `OLD`, appuyez 3 fois lentement sur son bouton.
3. Appuyez lentement sur `Send` sur le Flipper, puis relâchez.
4. Attendez 10 s, puis appuyez sur `Send` pour tester.
5. Done?

### Avec accès au boîtier du récepteur {#nice-flor-s-with-receiver}

Enregistrez-la comme le décrit le manuel de votre télécommande d'origine. Pour un récepteur NICE FLOX2R typique :

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Appuyez sur le bouton d'apprentissage du récepteur pendant 1 à 2 s. La LED s'allume pendant 5 s. Effectuez l'étape suivante pendant ces 5 s.
3. Appuyez sur `Send` jusqu'à ce que la LED du récepteur s'éteigne.
4. Relâchez et attendez 2 s.
5. Appuyez de nouveau sur `Send`. La LED clignote 3 fois et la télécommande est enregistrée. Sinon, reprenez à l'étape 2.
6. Attendez 5 s, puis appuyez sur `Send` pour tester.
7. Done!

::: tip
Des variantes de compteur Nice Flor-S pour des récepteurs spécifiques (floxi2r, ox2) sont disponibles sous forme de [modes de compteur](/fr/subghz/counter-mode).
:::

## Nice One {#nice-one}

- **Créez-la :** `Sub-GHz → Add Manually → Nice One → 433.92 AM650`

Nice One appartient à la famille Nice FloR-S avec un codage différent, et le côté récepteur est identique. **[Les deux procédures Nice Flor S](#nice-flor-s) s'appliquent exactement telles quelles.** Si votre télécommande est lue comme une FloR-S mais que le compteur semble incorrect, il peut s'agir d'une Nice O-Code.

## Nice O-Code {#nice-o-code}

- **Créez-la :** `Sub-GHz → Add Manually → Nice O-Code → 433.92 AM650` (ou `Nice O-Code One` pour le codage Nice One)
- **Créez-la pour une installation existante :** `Sub-GHz → Add Manually [Advanced] → Nice O-Code → 433.92 AM650`, qui demande `SERIAL`, `BUTTON`, `COUNTER` et le code installateur (`Enter IC in hex`)
- **Créez-la avec un certificat :** `Sub-GHz → Add Manually → Nice O-Code+Crt → 433.92 AM650`, qui demande toujours le numéro de série, le bouton, le compteur, le code installateur **et** le certificat du récepteur (`Enter CERT in hex`)

O-Code est du Nice FloR-S clé par un **code installateur (IC)** de 16 bits partagé par toutes les télécommandes d'une même installation. Le côté récepteur est identique à FloR-S, donc [les deux procédures Nice Flor S](#nice-flor-s) s'appliquent, mais une télécommande ne peut atteindre qu'un récepteur configuré avec le même code installateur.

- **Pour une installation qui vous appartient**, `Nice O-Code` simple invente un code installateur en même temps que le numéro de série. Un récepteur sortant d'usine ne l'acceptera pas via son bouton : enregistrez donc d'abord une télécommande [Nice One](#nice-one) ordinaire.
- **Pour une installation existante**, récupérez le code installateur depuis une télécommande fonctionnelle avec l'[application Nice O-Code](/fr/subghz/nice-o-code) (`Apps → Sub-GHz → Nice O-Code`). Appuyez 4 fois ou plus sur le bouton de la télécommande (sans le maintenir). Sur l'écran de résultat, <kbd>→</kbd> (`New`) écrit une nouvelle télécommande avec le même code installateur et le même bouton, mais son propre numéro de série et son propre compteur. C'est celle-là qu'il faut enregistrer. `Save` écrit un simple clone destiné aux essais.

::: info Testé sur un OXIBD sortant d'usine
En mode I, le récepteur **ignore complètement les paquets O-Code**, quel que soit le code installateur qu'ils portent, alors qu'une télécommande `Nice One` ordinaire est mémorisée immédiatement. Seule une O-Box écrit le code installateur dans le récepteur. Sur un récepteur jamais configuré, utilisez les entrées Nice Flor S / Nice One ordinaires.
:::

::: tip COUNTER
Ne laissez **pas** `COUNTER` près de zéro. Le récepteur refuse un compte en retard sur celui qu'il a mémorisé, et refuse également un compte situé de façon invraisemblable loin derrière les télécommandes qu'il connaît, même pour un nouveau numéro de série. Positionnez-le un peu en dessous du compte de votre télécommande fonctionnelle (le `New` de l'application le fait pour vous). Si vous avez déjà émis des paquets depuis ce numéro de série, utilisez une valeur légèrement supérieure à la plus haute que vous avez émise.
:::

**Enrôlement par certificat.** Une télécommande portant le certificat du récepteur émet des paquets de 112 bits pendant ses **vingt** premières utilisations, et le récepteur l'enrôle tout seul. Ouvrez le fichier à portée du portail et appuyez sur la touche environ une fois par seconde, **dix à quinze fois en une seule session**. Le portail s'ouvre vers le dixième appui, et après cela la télécommande est enregistrée définitivement. Si les vingt utilisations passent sans que le portail s'ouvre, supprimez le fichier et créez-en un nouveau. Les certificats, les cinq voies d'enregistrement Nice, les codes de LED du récepteur et la fenêtre du compteur sont traités en détail sur la page [Nice O-Code](/fr/subghz/nice-o-code).

## Nice Smilo {#nice-smilo}

- **Vendue aussi sous le nom de :** SM2 / SM4. Récepteurs SMXI, SMXIS, et OXI réglé sur le codage Smilo.
- **Créez-la :** `Sub-GHz → Add Manually → KL: Nice Smilo → 433.92 AM650`
- **Touche de programmation :** <kbd>→</kbd> = `0xB`, le bouton supplémentaire (caché)

Les récepteurs Nice mémorisent une télécommande dans un de deux modes. Le **mode I** attribue à chaque bouton de la télécommande la sortie correspondante du récepteur. Le **mode II** vous laisse choisir quelle sortie un bouton unique commande.

### Avec accès au boîtier du récepteur : mode I {#smilo-mode-1}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Appuyez et maintenez le bouton du récepteur pendant au moins 3 s.
3. Relâchez-le quand la LED s'allume.
4. Dans les 10 s, appuyez sur `Send` et maintenez au moins 2 s.
5. La LED du récepteur clignote 3 fois. La télécommande est mémorisée.
6. Pour en ajouter d'autres, répétez l'étape 4 dans les 10 s suivantes.
7. Done!

### Avec accès au boîtier du récepteur : mode II {#smilo-mode-2}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Appuyez sur le bouton du récepteur autant de fois que le numéro de la sortie (deux fois pour la sortie 2).
3. Vérifiez que la LED clignote le même nombre de fois.
4. Dans les 10 s, appuyez sur la touche du Flipper que vous voulez pour cette sortie et maintenez au moins 2 s.
5. La LED clignote 3 fois. La télécommande est mémorisée.
6. Done!

### Avec une télécommande fonctionnelle {#smilo-with-remote}

La première télécommande doit toujours être enregistrée avec le bouton du récepteur. La nouvelle télécommande **hérite du mode** de l'ancienne : avec le mode II, vous appuyez donc sur les boutons correspondants sur les deux.

1. Tenez-vous près du récepteur.
2. Ouvrez le fichier de votre nouvelle télécommande. Appuyez et maintenez `Send` pendant au moins 5 s, puis relâchez.
3. Sur la télécommande fonctionnelle, appuyez puis relâchez lentement son bouton 3 fois.
4. Ouvrez de nouveau le nouveau fichier, puis appuyez et relâchez lentement `Send` une fois.
5. Done?

::: info
Ces récepteurs ne peuvent pas supprimer une seule télécommande, uniquement toutes à la fois.
:::

## Security+ 1.0 / 2.0 (Chamberlain, LiftMaster, Craftsman) {#security-1-0-2-0-chamberlain-liftmaster-craftsman}

- **Créez-la :** `Sub-GHz → Add Manually → Security+2.0` ou `Security+1.0`, puis la bande. Par défaut, c'est `433.92 AM650`. Security+ 1.0 propose aussi `315.00 AM650` et `390.00 AM650`. Security+ 2.0 propose `310.00`, `315.00` et `390.00 AM650`.

**Laquelle avez-vous ?** Regardez la couleur du bouton `Learn` sur la motorisation :

| Bouton Learn | À créer |
|---|---|
| Jaune | `Security+2.0` |
| Violet | `Security+1.0` → `315.00 AM650` |
| Vert | `Security+1.0` → `390.00 AM650` |
| Rouge / orange | Billion Code, pas du Security+ |
| Gris / blanc | télécommande à interrupteurs DIP, pas du Security+ |

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Trouvez `Learn` sur la motorisation : généralement au dos ou sur le panneau latéral, parfois derrière le cache de l'éclairage.
3. Appuyez puis relâchez une fois. La LED d'apprentissage reste allumée en continu pendant 30 s.
4. Pendant ces 30 s, appuyez sur `Send` sur le Flipper et maintenez.
5. Relâchez quand les éclairages de la motorisation clignotent ou que vous entendez deux clics. La télécommande est programmée.
6. Appuyez de nouveau sur `Send` pour vérifier que la porte bouge.
7. Done?

::: tip
Si le bouton de la motorisation ne coopère pas, certains systèmes permettent de programmer depuis le boîtier mural. Pour les paquets de clavier Security+ 2.0, voir [Security+ PIN](/fr/subghz/secplus-pin).
:::

## Somfy Keytis {#somfy-keytis}

- **Vendue aussi sous le nom de :** Keytis NS 2 RTS / KeyGo 4 RTS
- **Créez-la :** `Sub-GHz → Add Manually → Somfy Keytis → 433.42 AM650` (c'est bien **433.42 MHz**, pas 433.92)
- **Touche de programmation :** **<kbd>↑</kbd>** = `0x3`, `Prog` (`Send` est `Key_1`)

Une Keytis d'origine n'a pas de touche `Prog` en façade. Vous pontez les deux pastilles `PROG` au dos de la carte avec un tournevis. Le Flipper n'a besoin que de <kbd>↑</kbd>.

### Avec accès au récepteur {#keytis-with-receiver}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Appuyez et maintenez `PROG` sur le récepteur pendant environ 3 s, jusqu'à ce qu'il clignote.
3. Appuyez sur <kbd>↑</kbd> (`Prog`) sur le Flipper.
4. Le volet ou le portail bouge brièvement de haut en bas. La télécommande est enregistrée.
5. Done?

### Avec une télécommande fonctionnelle {#keytis-with-remote}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Mettez la télécommande enregistrée en mode programmation jusqu'à ce que le volet ou le portail bouge brièvement. Sur une Keytis d'origine, pontez les pastilles `PROG`. Sur le Flipper, appuyez sur <kbd>↑</kbd> dans le fichier de cette télécommande.
3. Ouvrez le fichier de votre nouvelle télécommande et appuyez sur <kbd>↑</kbd> (`Prog`) jusqu'à ce que le volet ou le portail bouge brièvement de nouveau.
4. Done?

::: danger
Sur de nombreux récepteurs Somfy, maintenir le bouton de programmation plus d'environ 7 s efface toutes les télécommandes et tous les capteurs connus.
:::

::: info
Keytis utilise le protocole radio `NS`, plus récent. Un ancien récepteur RTS non-NS ne l'acceptera pas tant que le protocole de la télécommande n'aura pas été basculé. Consultez la documentation Somfy de votre récepteur.
:::

## Somfy Telis {#somfy-telis}

- **Créez-la :** `Sub-GHz → Add Manually → Somfy Telis → 433.42 AM650` (c'est bien **433.42 MHz**, pas 433.92)
- **Touche de programmation :** **<kbd>←</kbd>** = `0x8`, `Prog`

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Faites un appui long sur `Prog` d'une télécommande déjà enregistrée sur l'appareil, jusqu'à ce que les volets bougent brièvement de haut en bas.
3. Appuyez et maintenez <kbd>←</kbd> (`Prog`) sur le Flipper jusqu'à ce que les volets bougent de nouveau brièvement de haut en bas.
4. Done?

## Sommer {#sommer}

- **Vendue aussi sous le nom de :** TX03-868-4 / TX03-868-2 (SOMloq). Motorisations Pearl, Duo, Sprint, Marathon.
- **À lire avec :** la modulation `FM12K` ou `FM476`, celle qui décode votre télécommande
- **Créez-la :** `Sub-GHz → Add Manually → KL: Sommer`, puis choisissez la bande correspondant à la façon dont votre télécommande a été lue : `434.42 FM12K` (par défaut), `868.80 FM12K`, `434.42 FM476` ou `868.80 FM476`
- **Touche de programmation :** <kbd>→</kbd> = `0x6`

::: tip Unleashed
Les guides plus anciens listent quatre entrées Sommer distinctes (`fm2` et simple). Le firmware actuel n'a qu'une seule ligne `KL: Sommer`, et le sélecteur de bande choisit à la fois la fréquence et la variante de modulation.
:::

### Avec accès au récepteur {#sommer-with-receiver}

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Trouvez le bouton `learn` / `code` du récepteur. Sur une Duo, il est sous le cache de l'éclairage ; sur une Sprint, derrière le capot du boîtier d'interrupteurs ; et sur une Marathon, sous un couvercle en plastique transparent à côté du bouton de code.
3. Appuyez brièvement dessus. La LED du récepteur s'allume.
4. Appuyez sur `Send` et maintenez. Quand la LED du récepteur se met à clignoter rapidement, relâchez.
5. La LED du récepteur s'éteint. La télécommande est programmée.
6. Done?

### Sur une motorisation de portail coulissant {#sommer-sliding-gate}

Appuyez plutôt sur le bouton `Radio` de l'unité de commande. Une LED rouge confirme le mode programmation. Appuyez de nouveau dessus pour choisir le canal, puis maintenez `Send` jusqu'à ce que la LED du canal clignote et s'éteigne. Le récepteur quitte tout seul le mode programmation après environ 30 s sans signal.

## V2 Phoenix (Phox) {#v2-phoenix-phox}

- **Vendue aussi sous le nom de :** Phoenix 2/4, Phox 2/4, Handy 2/4, TXC2-4, TRC2-4, TSC2-4. Récepteurs RXP, MR2.
- **Créez-la :** `Sub-GHz → Add Manually → V2 Phoenix → 433.92 AM650`
- **Touche de programmation :** <kbd>→</kbd> = `0x3` (sur l'originale, les boutons 1+2 ou 1+3 maintenus ensemble)

::: warning
Cette correspondance **n'est pas encore confirmée**. Si elle ne fonctionne pas, enregistrez via le bouton du récepteur et signalez-le dans les issues Unleashed.
:::

1. Ouvrez le fichier de votre nouvelle télécommande.
2. Ouvrez le fichier de la télécommande enregistrée. Appuyez sur <kbd>→</kbd> et maintenez au moins 5 s, puis relâchez.
3. Dans les 5 s, ouvrez le fichier de la nouvelle télécommande et appuyez sur `Send`.
4. Relâchez. Répétez pour les autres boutons.
5. Done?

La télécommande qui ouvre la fenêtre doit déjà être mémorisée dans le récepteur, et tout ce qui est mémorisé ainsi hérite de sa logique. Si seul le bouton 1 était mémorisé, les nouvelles télécommandes ne peuvent être mémorisées que sur le bouton 1. Certains récepteurs V2 peuvent être basculés en mode `Static`, qui ignore la partie tournante de la clé.

---

## Récupérer un Seed {#recovering-a-seed}

**FAAC SLH**, **Genius**, **Erreka** et **BFT Mitto** construisent leur code tournant à partir d'un **Seed** secret. Sans lui, le Flipper ne peut pas décoder ces télécommandes (elles apparaissent comme `KL: Unknown`, ou pas du tout) et ne peut pas fabriquer une télécommande que le récepteur accepte. Vous avez besoin du Seed quand :

- la programmation radio du récepteur est désactivée, donc seul un clone fonctionne ;
- votre télécommande FAAC/Genius est une slave et ne peut pas émettre le code de programmation ;
- vous ne pouvez pas accéder au récepteur ;
- une installation Erreka partage un même Seed entre toutes les télécommandes ;
- une BFT Mitto ancienne refuse de passer en mode programmation.

L'application [Seed Capturer](/fr/subghz/seed-capturer) (`Apps → Sub-GHz → Seed Capturer`) collecte des paires `Fix` + `Hop` consécutives issues d'un même bouton. Elle n'émet jamais, et les enregistre dans `/ext/apps_data/subghz_seed_captures/`. L'application compagnon qUnleashed (voir [Application qUnleashed](/fr/mobile/qunleashed-app)) attaque ensuite le Seed par force brute et peut écrire pour vous le fichier de clone fini.

Une fois que vous avez le Seed :

- **Nouvelle télécommande** (le récepteur doit accepter de nouvelles télécommandes) : `Add Manually [Advanced]` → votre système → bande, votre propre `SERIAL`, et le `SEED` récupéré.
- **Clone** (fonctionne sans programmation, car le récepteur connaît déjà ce numéro de série) : laissez qUnleashed l'enregistrer, ou saisissez le `SERIAL` et le `BUTTON` de l'**originale**, le `SEED`, et un `COUNTER` légèrement supérieur à la valeur actuelle de l'originale.

::: danger
Un clone partage le compteur avec l'originale et les deux vont se le disputer. Ne clonez que lorsque créer une nouvelle télécommande est impossible.
:::

## Référence des boutons de programmation et cachés {#programming-hidden-button-reference}

Trouvez l'étape « mettre le récepteur en mode programmation » dans le manuel de votre fabricant. Partout où il vous dit d'appuyer sur quelque chose sur la télécommande d'origine, appuyez à la place sur la touche indiquée dans ce tableau.

::: info
Il s'agit des touches d'une télécommande telle que `Add Manually` la crée. Si vous changez le code du bouton à la main, les touches suivent.
:::

| Système (entrée Add Manually) | Code | Touche sur le Flipper | Sur la télécommande d'origine |
|---|---|---|---|
| `FAAC SLH`, `Genius` | – | **<kbd>↑</kbd>** | le signal de programmation |
| `BFT Mitto` | `0xF` | <kbd>→</kbd> | trou d'épingle au dos, ou boutons 1+2 maintenus |
| `Erreka` | `0xF` | <kbd>→</kbd> | broches 1 et 5 du connecteur à 5 voies pontées |
| `KL: DEA Mio` | `0xF` | <kbd>→</kbd> | bouton caché |
| `KL: Aprimatic` | `0xF` | <kbd>→</kbd> | les 4 boutons maintenus ensemble |
| `KL: Mhouse` | `0xF` | <kbd>→</kbd> | bouton supplémentaire / caché |
| `KL: Nice Smilo` | `0xB` | <kbd>→</kbd> | bouton supplémentaire / caché |
| `KL: FAAC RC,XT` | `0xB` | <kbd>→</kbd> | boutons 1+2 maintenus (appui master) |
| `KL: Genius TX4RC` | `0xB` | <kbd>→</kbd> | bouton du mode programmation |
| `KL: Monarch` | `0xB` | *aucune flèche ne l'émet* | définissez le code du bouton à la main dans les réglages du signal |
| `KL: FAAC FIX` | `0x9` | <kbd>→</kbd> | bouton supplémentaire / caché *(non confirmé)* |
| `KL: Novoferm` | `0x9` | <kbd>→</kbd> | bouton supplémentaire / caché |
| `KL: Stilmatic` | `0x9` | <kbd>→</kbd> | bouton supplémentaire / caché |
| `KL: Sommer` (toutes bandes) | `0x6` | <kbd>→</kbd> | bouton supplémentaire / caché |
| `KL: Hor. EcoStar` | `0x6` | **<kbd>↓</kbd>** | bouton supplémentaire / caché |
| `KL: Cardin S449` | `0xD` | <kbd>→</kbd> | bouton dans le trou sous les touches |
| `AN-Motors AT4` | `0xC` | <kbd>→</kbd> | bouton supplémentaire / caché |
| `Beninca ARC` | `0x0` | **<kbd>↓</kbd>** | bouton caché (boutons 1+2 maintenus) |
| `Ditec GOL4` | `0x0` | <kbd>→</kbd> | bouton caché |
| `Jarolift` | `0x1` | **<kbd>↑</kbd>** | `Learn` : Up+Down maintenus, puis Stop |
| `Somfy Telis` | `0x8` | **<kbd>←</kbd>** | bouton `Prog` |
| `Somfy Keytis` | `0x3` | **<kbd>↑</kbd>** | pastilles `Prog` au dos de la carte |
| `V2 Phoenix` | `0x3` | <kbd>→</kbd> | boutons 1+2 ou 1+3 maintenus *(non confirmé)* |
| `Nice FloR-S` / `Nice One` / `Nice O-Code` | `0x3` | <kbd>→</kbd> | bouton 3 *(non confirmé comme bouton de programmation)* |

### Tout le reste du menu {#everything-else}

Toute entrée qui n'est pas dans ce tableau et qui n'a pas de section ci-dessus s'enregistre de la façon ordinaire : **mettez le récepteur en mode apprentissage avec son propre bouton, puis appuyez sur `Send` sur le Flipper dans la fenêtre de temps indiquée par votre fabricant.**

Cela couvre la plupart des systèmes KeeLoq (Comunello, Allmatic, Motorline, Centurion, Phantom/Hiland, KEY, Jolly Motors, IronLogic, DTM Neo, Gibidi, GSN, HomeGate, Elmes, Normstahl, JCM Tech, Pujol, ET Blue, ATA PTX4, Seav, Wisniowski, Fadini, Mc Garcia, Clemsa Mutancode, Doormatic, Elvox, Verex, CAME Space, Beninca KeeLoq, Superrollo, HCS101) et tous les protocoles statiques, comme CAME, Nice Flo, Marantec, Princeton, Prastel, Roger, Telcoma EDGE, Gate TX, BETT, Nord ICE, Revers RB2, Linear, Nero et [ZKTeco](/fr/subghz/zkteco-cmp200).

## Quand ça ne fonctionne pas {#troubleshooting}

- **Rien ne se passe du tout.** Vérifiez d'abord la fréquence. C'est l'erreur la plus fréquente. Lisez votre télécommande d'origine avec `Sub-GHz → Read` et comparez. Certaines marques vendent la même télécommande sur deux fréquences : DoorHan en 315 et 433.92, FAAC et Genius en 433.92 et 868.35. Utilisez le [Frequency Analyzer](/fr/subghz/frequency-analyzer) en cas de doute.
- **Mauvaise modulation.** La plupart des systèmes décrits ici utilisent `AM650`, mais Cardin S449 est en `FM12K` et Sommer en `FM12K` ou `FM476`. Réglez-la dans `Sub-GHz → Read → Config`, et choisissez la bande correspondante dans Add Manually.
- **Le récepteur réagit mais ne mémorise jamais la télécommande.** Vous manquez probablement la fenêtre de temps. Relisez les étapes et ouvrez le fichier de la télécommande avant de toucher le bouton du récepteur.
- **Il a mémorisé la télécommande mais rien ne s'ouvre.** Maintenez `Send` plus longtemps. Plusieurs protocoles ont besoin de 1 à 3 s pour émettre un code complet, et CAME Atomo a besoin d'au moins 2 s à chaque fois.
- **Ça a fonctionné une fois puis plus du tout.** Sur un système à code tournant, c'est un problème de compteur : vous avez cloné une télécommande au lieu d'en créer une nouvelle. Appuyez quelques fois de plus sur `Send` d'affilée, car le récepteur accepte un compteur qui a pris de l'avance dans une certaine fenêtre. Pour garder les deux télécommandes fonctionnelles, créez plutôt une nouvelle télécommande (voir [Codes tournants](/fr/subghz/rolling-codes)). Une télécommande statique n'a pas de compteur : si elle cesse de fonctionner, vérifiez la pile, la fréquence ou le récepteur.
- **Toutes vos télécommandes ont cessé de fonctionner.** Vous avez très probablement maintenu un bouton de programmation assez longtemps pour déclencher la fonction d'effacement du récepteur. Réenregistrez toutes les télécommandes, originales incluses.

## Sources et manuels {#sources}

- [FAAC SLH : tutoriel vidéo](https://www.youtube.com/watch?v=NfZmMy37XUs)
- [Analyse du protocole Somfy RTS](https://pushstack.wordpress.com/somfy-rts-protocol/)
- [Somfy Universal Receiver RTS : instructions d'installation](https://service.somfy.com/downloads/nam_v5/universalreceiver_rts.pdf)
- [Enregistrement d'une Somfy Keytis NS 2 RTS (forum Somfy)](https://forum.somfy.fr/questions/1792206-programmer-telecommande-keitis-ns2-rts-recepteur-somfy-axorn-50)
- [Manuel BFT Mitto](https://www.retroremotes.com.au/wp-content/uploads/2017/03/BFT-MITTO-2-4-19-6-17.pdf)
- [Programmation du récepteur NICE FLOX2R](https://apollogateopeners.com/store/pdf/apollo-flor-s-receiver-programming-guide.pdf)
- [Programmation Nice Flor S](https://motepro.com.au/Instructions/Nice.pdf)
- [Manuel Nice Smilo SM2/SM4 et récepteur SMXI](https://www.habitat-automatisme.com/blog/wp-content/uploads/2010/02/SMILO.pdf)
- Nice O-Code : manuels installateur de [niceforyou.com](https://www.niceforyou.com/) (OXI/A `IS0242A00MM`, OXI/OXIT/OX2/OX4T `IST236R02`, OXIBD `idv0603a01it`, O-Box `IST225`, récepteur FLOR `IS0063A00MM`, émetteurs Era One `IS0102A01MM`)
- [Programmation Mhouse GTX4 / TX4 / Nice Home ECCO5](https://www.allotelecommande.com/wp-content/uploads/2019/06/Notice-de-programmation-MHOUSE-GTX4-%E2%80%93-TX4-%E2%80%93-MT4-%E2%80%93-NICE-HOME-ECCO5-.pdf)
- Erreka IRIS : `Guia rapida mando IRIS` (MSR-044/03), depuis [erreka.com](https://www.erreka.com/)
- [Manuel du moteur Jarolift TDEF](https://www.jarolift.de/wp-content/themes/jarolift/manuals/motoren/en/Jarolift_TDEF_EN.pdf)
- [Programmation de l'émetteur Beninca TO.GO](https://www.allotelecommande.com/wp-content/uploads/2023/05/BENINCA-TO.GO_.pdf)
- [Manuel des récepteurs Ditec BIX L / BIX A](https://www.allotelecommande.com/wp-content/uploads/2023/03/DITEC-BIX-L-DITEC-BIX-A.pdf)
- [Notice de programmation Cardin S449 QZ2](https://www.allotelecommande.com/wp-content/uploads/2024/02/CARDIN-S449-QZ2.pdf)
- [Manuel du récepteur Cardin RCQ449](https://www.allotelecommande.com/wp-content/uploads/2023/02/Recepteur-Radio-CARDIN-RCQ449-ND00.pdf)
- [Manuel de l'émetteur portatif Hormann RSC2](https://www.hoermann.de/fileadmin/_country/dok/Handsender_RSC2_%28H%C3%B6rmann%29_TR20L001-A.pdf)
- [Sommer : apprendre un émetteur à une motorisation de portail coulissant](https://www.sommer.eu/en/magazine/programming-a-handheld-transmitter-to-a-sommer-sliding-gate-operator.html)
- [Manuel du récepteur V2 RXP4 : apprentissage radio](https://manualslib.mx/manual/401640/V2-Rxp4.html?page=9)
- [Programmation du récepteur KingGates Fred](https://tecnoparking.com/tienda/gb/receptors/2096-outer-receiver-kinggates-fred-2-channels-rollingcode-is-433-mhz.html)

## Pages liées {#related}

- [Add Manually](/fr/subghz/add-manually)
- [Codes tournants](/fr/subghz/rolling-codes)
- [KeeLoq](/fr/subghz/keeloq)
- [Modes de compteur](/fr/subghz/counter-mode)
- [Systèmes pris en charge](/fr/subghz/supported-systems)
- [Seed Capturer](/fr/subghz/seed-capturer) · [Nice O-Code](/fr/subghz/nice-o-code)
