---
title: Attaques nested et backdoors Fudan
order: 35
author: gromovyna
original: [https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://t.me/gromovyna/4, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# Attaques nested et backdoors Fudan

Un guide pratique « sur quoi appuyer » de **@gromovyna** pour les attaques card-only contre MIFARE Classic intégrées
à `NFC → Read`. Elles sont arrivées dans le firmware officiel **1.1.2** (travail de
[@noproto](https://github.com/noproto)) et font partie d'Unleashed. Pendant leur développement, un chercheur de la
communauté a fait deux découvertes importantes : une attaque sur les **static encrypted nonces**, et des
**clés de backdoor** dans les puces fabriquées par **Fudan** (et d'autres) qui permettent de lire les secteurs d'un
tag MIFARE Classic sans connaître ses clés. Les deux ont été intégrées au firmware et à **MFKey 3** (aujourd'hui
[MFKey 4.1](/fr/nfc/mfkey-app)). L'article de recherche :
[eprint.iacr.org/2024/1275](https://eprint.iacr.org/2024/1275.pdf).

::: tip Méthode plus rapide (mise à jour, septembre 2026)
Si vous voulez simplement récupérer rapidement des clés MIFARE Classic, utilisez l'application compagnon
**qUnleashed**, qui exécute toutes ces attaques, y compris HardNested, sur votre téléphone ou votre ordinateur :
voir [Récupération rapide des clés avec qUnleashed](/fr/nfc/qunleashed).
:::

## L'idée en bref

Les **attaques nested** sont des attaques *card-only* (aucun lecteur nécessaire) : en connaissant au moins une clé
d'une carte, elles permettent de retrouver les clés inconnues. Conceptuellement, les tags se répartissent en quatre
groupes (à strictement parler il y a Nested et HardNested, mais cette répartition est plus facile à comprendre) :

| Le tag est vulnérable à | Type de nonce | Où la clé est calculée |
|---|---|---|
| **Nested** | PRNG faible | MFKey sur le Flipper, qUnleashed |
| **HardNested** | PRNG difficile | qUnleashed ou un ordinateur (pas sur le Flipper) |
| **Static Nested** | nonce statique | MFKey sur le Flipper, qUnleashed |
| **Static Encrypted Nested** (SEN) | static encrypted nonce | MFKey sur le Flipper (le plus lent), qUnleashed |

Les **clés de backdoor** sont des clés qui ouvrent les données d'un tag **sans** ses véritables clés.

Pour les exemples, l'auteur a utilisé un tag de chaque type, avec le secteur 0 chiffré par une paire de clés
générée : clé A `A3F92C8E7D3A`, clé B `4F6D91C5BA7E` (bits d'accès laissés par défaut). Sur un Proxmark3, la
vérification des clés par défaut a montré ces clés comme inconnues :

![Vérification des clés par défaut sur Proxmark3](/img/remote/86130b06142278a1.png)

## Étape 1. Lire le tag

Allez dans `Main Menu → NFC → Read` et maintenez le tag immobile.

### 1.1 Le tag a une backdoor

Vous verrez des écrans **Backdoor Read**, puis quelques autres avec **(Backdoor)** dans l'en-tête :

![Backdoor Read](/img/remote/1491507f521c09f5.png)

![Lecture via la backdoor](/img/remote/e9be977d84486794.png)

Cela signifie que la puce a une backdoor : le Flipper lit les données des secteurs à travers elle et collecte des
nonces afin que les clés puissent être récupérées. Le résultat typique est **tous les secteurs lus, mais moins de
clés que nécessaire** :

![Tous les secteurs, mais seulement 30 clés](/img/remote/9e7db33e51594779.png)

### 1.2 Le tag n'a pas de backdoor

C'est alors la recherche de clés classique qui s'exécute : d'abord le dictionnaire **utilisateur**, puis le
dictionnaire **système**.

![Dictionnaire utilisateur](/img/remote/fff8f5662df941b9.png)

![Dictionnaire système](/img/remote/0da64f609fc2c770.png)

Si au moins une clé a été trouvée, le Flipper passe à **PRNG Analysis**, puis parcourt le **Nested Dictionary** :

![PRNG Analysis](/img/remote/3e0e493fe7fcbd5f.png)

puis **Calibration** et **Nonce Collection** :

![Calibration et collecte de nonces](/img/remote/f5b036a96f5a0869.png)

Si le tag n'est vulnérable **qu'à HardNested**, la collecte de nonces prend plus de temps et l'en-tête reçoit un
suffixe **(Hard)** :

![Collecte de nonces pour un tag à PRNG difficile](/img/remote/fca9f1b2e4475631.png)

> Dans ce cas, allez directement à l'[étape 2.2](#_2-2-the-tag-is-vulnerable-to-hardnested).

Ici, le résultat est plus familier : le nombre de clés trouvées est proche du nombre de secteurs lus (selon les bits
d'accès).

![Résultat après la phase nested](/img/remote/d15656101dfafcc4.png)

Tous les nonces collectés sont ajoutés à `/ext/nfc/.nested.log`.

## Étape 2. Récupérer les clés

Allez dans `Main Menu → Apps → NFC → MFKey`.

::: warning Vérifiez la version de l'application
Assurez-vous que l'application MFKey est bien celle qui correspond à votre firmware et qu'elle n'a pas été écrasée
par une ancienne copie si vous avez installé des applications séparément. Unleashed livre **MFKey 4.1**.
:::

![Écran de démarrage de MFKey](/img/remote/195a1b6a411e7bf3.png)

Appuyez sur <kbd>OK</kbd> **Start** et…

### 2.1 Le tag est vulnérable à Nested, Static Nested ou Static Encrypted Nested

Le processus de cassage démarre. Vous pouvez laisser le Flipper tranquille et faire autre chose :

![Cassage en cours](/img/remote/a514db67a986ae2c.png)

Il ne reste plus qu'à attendre. Sur le matériel du Flipper, ce n'est pas rapide (bonjour le SPI) et cela dépend :

- du type d'attaque : Nested < Static Nested < Static Encrypted Nested (SEN est le plus lent) ;
- du nombre de clés inconnues (moins il y en a, plus c'est rapide) ;
- du degré d'unicité des clés : une clé réutilisée partout est trouvée plus vite qu'un tag partiellement diversifié
  (p. ex. Iron Logic), lui-même plus rapide qu'un tag entièrement diversifié (p. ex. les bobines de filament
  Bambu Lab).

L'interface n'est pas toujours réactive et « réfléchit » parfois. Le Flipper peut occasionnellement sembler figé ; ne
vous précipitez pas pour le redémarrer. La ligne **RAM** en haut continue de changer tant que le travail avance.

::: warning Static encrypted nonces
Avec les static encrypted nonces, en raison du fonctionnement de l'attaque, les nonces ne sont pas marqués comme
« résolus » ; MFKey ne construit que des **candidates** (des clés qui devront être vérifiées sur le tag plus tard), et
l'application peut sembler bloquée à la dernière étape (ou à une étape antérieure). Si suffisamment de temps s'est
écoulé, quittez et vérifiez le résultat (étape 3). Depuis MFKey 4.x, les candidates sont enregistrées dans un
**dictionnaire CUID** propre à la carte, `/ext/nfc/assets/mf_classic_dict_<UID>.nfc`, que `Read` essaie en premier.
:::

Quand le déchiffrement est terminé, vous obtenez un récapitulatif avec le nombre de clés ajoutées au dictionnaire
utilisateur (**Keys added to user dict: N**, et pour les tags SEN **SEN key candidates: N**) :

![MFKey terminé](/img/remote/c9ef77139b74cc89.png)

Continuez avec l'étape 3.

### 2.2 Le tag est vulnérable à HardNested {#_2-2-the-tag-is-vulnerable-to-hardnested}

Vous l'aviez deviné grâce à l'écran **(Hard)** pendant la collecte de nonces, ou bien MFKey affichera une erreur
indiquant qu'aucun nonce n'a été trouvé :

![MFKey : aucun nonce trouvé](/img/remote/2519c7dce0b881c9.png)

HardNested est la seule attaque qui ne peut pas être exécutée sur le Flipper. Les options :

- **qUnleashed** (recommandé, téléphone ou ordinateur) : `Tools → Recover MIFARE Keys`, voir
  [qUnleashed](/fr/nfc/qunleashed). Les clés vont directement dans le dictionnaire utilisateur.
- **Un ordinateur avec HardnestedRecovery**, comme dans le guide d'origine :
  1. Copiez `/ext/nfc/.nested.log` depuis la carte SD du Flipper vers l'ordinateur.
  2. Clonez et compilez [github.com/noproto/HardnestedRecovery](https://github.com/noproto/HardnestedRecovery) avec
     `make build` (sous Windows, utilisez WSL ou Docker).
  3. Lancez-le avec le journal en argument :

     ```bash
     ./hardnested_main .nested.log
     ```

  4. La clé apparaît dans la sortie :

     ```text
     [=] Hardnested attack starting...
     [=]    0 |    0 | Start using 32 threads                 |                 |
     [=]    0 |    0 | Brute force benchmark: 589 million (2^29.1) keys/s   | 140737488355328 |  3d
     [=]   16 |  256 | Loading nonces from file                |     24286058496 |  41s
     [=]   46 | 1891 | Apply Sum property. Sum(a0) = 128            |      1262183296 |  2s
     [=]   78 | 1894 | Brute force phase completed. Key found: A3F92C8E7D3A  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: A: a3f92c8e7d3a
     ...
     [=]   70 | 1218 | Brute force phase completed. Key found: 4F6D91C5BA7E  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: B: 4f6d91c5ba7e
     ```

::: danger Ajoutez les clés à la main
Contrairement au cas 2.1, les clés trouvées par HardnestedRecovery sur un ordinateur ne sont **pas** ajoutées
automatiquement. Ajoutez-les vous-même au dictionnaire utilisateur :
`NFC → Extra Actions → MIFARE Classic Keys → Add`, ou ajoutez-les à
`/ext/nfc/assets/mf_classic_dict_user.nfc`.
:::

## Étape 3. Relire le tag

Une fois les clés récupérées, relisez le tag via `NFC → Read`.

::: tip Astuce de pro
Si vous avez enregistré le tag après la première lecture, vous pouvez le déverrouiller directement depuis le menu de
la carte enregistrée : `Saved → <carte> → Unlock with Dictionary`.
:::

![Unlock with Dictionary depuis une carte enregistrée](/img/remote/8232d690446c70b6.png)

::: tip Astuce de pro
Pour de meilleures performances la prochaine fois, nettoyez `/ext/nfc/.nested.log` après avoir cassé les clés d'un
tag.
:::

## Voir aussi

[MIFARE Classic](/fr/nfc/mifare-classic) · [Application MFKey](/fr/nfc/mfkey-app) · [qUnleashed](/fr/nfc/qunleashed) ·
[MFKey32](/fr/nfc/mfkey) · [Lecteurs Iron Logic](/fr/nfc/iron-logic) · d'autres articles sur la chaîne de l'auteur
[@gromovyna](https://t.me/gromovyna)
