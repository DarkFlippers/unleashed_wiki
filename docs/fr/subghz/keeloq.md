---
title: KeeLoq
order: 70
author: gromovyna
original: [https://blog.li0ard.rest/wtfiskeeloq, https://t.me/gromovyna/24, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [li0ard, gromovyna, unleashed-docs, unleashed-src]
---
# KeeLoq

KeeLoq est le chiffrement qui se cache derrière un très grand nombre de télécommandes de portail, de porte de garage
et de barrière (DoorHan, Nice Smilo, FAAC RC, BFT, Came Space, Beninca, Hormann EcoStar…) et derrière d'anciennes
alarmes automobiles. Cette page explique son fonctionnement, ce que sont les « clés constructeur » et les « seeds »,
et comment Unleashed les gère.

La partie théorique s'appuie sur l'article **« KeeLoq и с чем его едят »** de
[@li0ard](https://blog.li0ard.rest/wtfiskeeloq), membre de l'équipe de recherche de @gromovyna, recommandé dans
[son canal](https://t.me/gromovyna/24) à quiconque souhaite comprendre ce chiffrement.

## Ce qu'est KeeLoq

KeeLoq est un chiffrement par blocs fondé sur un NLFSR (registre à décalage à rétroaction non linéaire), conçu par
Nanoteq Pty Ltd. et vendu à Microchip Technology Inc. Il chiffre des **blocs de 32 bits** avec une **clé de 64 bits**
en **528 rondes**. Il met en œuvre le *code hopping* : chaque émission est un paquet unique.

### Structure d'un paquet

Un paquet KeeLoq de 64 bits, par exemple `239B3DEBF16C47A6`, se compose de :

- **Fix** (les 4 premiers octets, `239B3DEB`) — émis en clair : l'identifiant du bouton (`2`) et le numéro de série
  de 28 bits de la télécommande (`39B3DEB`).
- **Hop** (les 4 derniers octets, `F16C47A6`) — chiffré avec la clé constructeur. Déchiffré, il ressemble à
  `21EB000A` : à nouveau l'identifiant du bouton (`2`), 12 bits de données de discrimination (souvent
  `serial & 0x3FF`) et le **compteur de 16 bits** (`000A`).

![Structure d'un paquet KeeLoq](/img/remote/167cc7293a53adb1.png)

C'est ce que le Flipper affiche après un [Read](/fr/subghz/read) : `Fix`, `Hop`, `Btn`, `Cnt`, et le nom du
constructeur.

### Logique du compteur

- Le compteur est égal à la valeur attendue par le récepteur → la commande est exécutée.
- Le compteur est **supérieur** à celui mémorisé → le récepteur se resynchronise sur lui et fonctionne normalement
  dès l'appui suivant.
- Le compteur est **inférieur** → ignoré ; certains récepteurs désapparient la télécommande après plusieurs valeurs
  « périmées ». *C'est le véritable danger lorsqu'on expérimente avec KeeLoq.* Voir
  [Codes tournants](/fr/subghz/rolling-codes).

## Modes d'apprentissage (dérivation de clé)

La clé qui chiffre réellement le hop est dérivée d'une **clé constructeur** (64 bits, la même pour toutes les
télécommandes d'une marque ou d'une gamme). La norme définit trois modes :

| Mode | Comment la clé propre à la télécommande est fabriquée |
|---|---|
| **Simple learning** | la clé constructeur est utilisée telle quelle (le plus faible) |
| **Normal learning** | la clé constructeur est mélangée avec le numéro de série de la télécommande |
| **Secure learning** | utilise une valeur supplémentaire — le **seed** — unique par télécommande et transmise uniquement lors de l'appariement (le mode standard le plus robuste) |

Les constructeurs inventent aussi leurs propres modes, par exemple **Magic XOR Type-1** (Beninca : numéro de série
XOR clé constructeur) ou **FAAC SLH (SPA)** — une série d'opérations sur les bits et de chiffrements, le plus
réfléchi d'entre eux selon li0ard.

::: tip Unleashed
Unleashed implémente tous les modes standard et de nombreux modes propriétaires
(`lib/subghz/protocols/keeloq_common.h`) : Simple, Normal, Secure, Magic XOR type 1, FAAC, Magic Serial types 1–3,
KingGates, Jarolift, Erreka, Pujol, AERF, JCM, JCM Gen2, Stagnoli et l'apprentissage Telcoma piloté par table. Plus
de 100 constructeurs sont listés dans [Systèmes pris en charge](/fr/subghz/supported-systems).
:::

## Les clés constructeur dans Unleashed

Pour décoder un signal KeeLoq, le Flipper doit connaître la clé constructeur. Unleashed les livre dans un magasin de
clés **chiffré** sur la carte SD :

| Fichier | Rôle |
|---|---|
| `/ext/subghz/assets/keeloq_mfcodes` | clés intégrées, chiffrées (`Encryption: 1`), mises à jour avec le firmware |
| `/ext/subghz/assets/keeloq_mfcodes_user` | **vos propres** clés, en clair (créez-le depuis `keeloq_mfcodes_user.example`) |

Lors du décodage d'un signal, toutes les clés sont essayées ; en cas de succès, le nom apparaît sous la forme
`KL: DoorHan`, `KL: Nice_Smilo`, etc. Les télécommandes KeeLoq demi-débit (half-rate) affichent également leur vrai
nom de constructeur (au lieu de `Crypt Key`), avec la mention `KL HR` dans la liste de lecture et `66b HR` dans les
infos du signal. Si aucune clé ne convient, le signal s'affiche comme **`KL: Unknown`** : il peut être enregistré,
mais pas émis ni utilisé pour générer le code suivant. Les commandes CLI `subghz` qui décodent des signaux affichent
`Load_keystore keeloq_mfcodes OK` et `Load_keystore keeloq_mfcodes_user OK` / `Absent` à leur démarrage — un moyen
rapide de vérifier le chargement des magasins de clés.

### Format du fichier de clés utilisateur

```text
# AABBCCDDEEFFAABB:X:NAME
# AABBCCDDEEFFAABB - manufacture key, 64 bit
# X - learning type: 1 - Simple, 2 - Normal, 3 - Secure, 4 - Magic_xor_type1,
#     5 - FAAC SLH, 6 - Magic Serial typ1, 7 - Magic Serial typ2, 8 - Magic Serial typ3,
#     0 - iterates over both previous and man in direct and reverse byte sequence
# NAME - name (no spaces), max 64 characters
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:1:Test2
```

Laissez une ligne vide à la fin du fichier. Le fichier `_user` n'est pas écrasé par les mises à jour.

### Les champs `Manufacture` et `Seed`

Un `.sub` KeeLoq enregistré stocke le constructeur par son nom :

```text
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: DoorHan
```

Les systèmes en secure learning stockent aussi `Seed: XX XX XX XX`. Ajouter à la main les lignes `Seed` +
`Manufacture` à un fichier qui apparaît comme `KL: Unknown` le rend décodable (voir BFT/Erreka ci-dessous).

## Les seeds : BFT Mitto, Erreka, FAAC SLH, Genius

Ces systèmes utilisent un **seed** propre à chaque télécommande (ou à chaque installation) ; sans lui, le signal
apparaît comme `KL: Unknown` (ou ne se décode pas) et aucune télécommande acceptée ne peut être fabriquée.

- **BFT Mitto** — les télécommandes récentes dérivent le seed du numéro de série et se décodent directement dans
  Read (`KL: BFT`). Les plus anciennes ont un seed unique. Mettez l'originale en mode programmation (trou d'épingle
  au dos ou boutons 1+2) : elle émet un paquet dont le `Fix` commence par `F` ; le **`Hop` de ce paquet est le seed**
  en clair.
- **Erreka IRIS** — pontez les broches `1` et `5` du connecteur à 5 voies sur le côté : à nouveau, le `Fix` commence
  par `F` et le `Hop` est le seed. Certaines installations donnent le **même** seed à **toutes** les télécommandes —
  une nouvelle télécommande doit alors le réutiliser.
- **FAAC SLH / Genius** — lisez le seed depuis une télécommande **maîtresse** en mode programmation ; le seed diffère
  **selon le bouton**.
- Pas de bouton de programmation disponible ? Utilisez l'application
  **[Seed Capturer](/fr/subghz/seed-capturer)** : elle collecte des paires Fix/Hop consécutives, et le seed est
  retrouvé dans l'application compagnon qUnleashed.

Avec le seed, créez la télécommande dans `Sub-GHz → Add Manually [Advanced]` (SERIAL → BUTTON → COUNTER → SEED),
voir [Add Manually](/fr/subghz/add-manually) et
[programmation d'une télécommande](/fr/subghz/remote-prog).

## Attaques connues (vue d'ensemble)

D'après l'article de li0ard, à titre de compréhension — ce ne sont pas des instructions.

**Théoriques :** attaque par glissement (slide attack) (~2³² paires clair/chiffré, donne les 32 premiers bits de la
clé), approche par corrélation (exploite un biais de 5/8 du NLFSR), étape linéaire (les 16 derniers bits de la clé
une fois le reste connu). Complexité totale ≈ 2⁵².

**Pratiques** (grâce aux travaux de Derek Jamison, « SubGHz Rolling Flaws ») :

| Attaque | Principe |
|---|---|
| Replay | réémettre un paquet capturé ; fonctionne sur les codes statiques et sur les récepteurs qui ne contrôlent pas le compteur |
| Clonage de télécommande | avec la clé constructeur, une copie fonctionnelle peut être fabriquée — mais elle entre en conflit avec le compteur de l'originale et peut la faire désapparier |
| Future | émettre un compteur très en avance (`0001` → `3E91`) ; le récepteur se resynchronise, l'originale est désynchronisée |
| Rollback | ramener le compteur en arrière après quelques utilisations ; de rares récepteurs se resynchronisent sur d'anciennes valeurs |
| RollJam | enregistrer en brouillant le récepteur, puis réutiliser plus tard. **Le brouillage est illégal** dans presque tous les pays |
| Clé constructeur (KGB) | le récepteur peut accepter plusieurs clés constructeur ; émettre le fix d'origine avec un compteur chiffré par une autre clé |
| Enc00 | remplacer le fix par celui d'une autre télécommande appariée et utiliser le hop d'origine ; l'autre télécommande est désynchronisée |
| Unknown | lorsqu'un récepteur ne parvient pas à décoder le hop, il utilise 0 ; les récepteurs universels peuvent ouvrir sur 0 |

Malgré tout cela, KeeLoq — comme Mifare Classic avec son Crypto-1 cassé — reste populaire dans les systèmes de
contrôle d'accès économiques ; certains fabricants (Beninca, Hormann) sont passés à l'AES.

::: warning
N'expérimentez qu'avec vos propres télécommandes et récepteurs. Une télécommande désynchronisée ou désappariée peut
nécessiter un réenregistrement auprès du récepteur.
:::

## Dépannage

- **`KL: Unknown`** — aucune clé correspondante. Vérifiez la modulation, mettez le firmware à jour (nouvelles clés),
  ou ajoutez une clé à `keeloq_mfcodes_user` si vous la détenez légitimement. Pour les systèmes à seed, récupérez le
  seed.
- **Ça décode mais le récepteur ignore le Flipper** — vous émettez un clone ; voir
  [Codes tournants](/fr/subghz/rolling-codes) et [Modes de compteur](/fr/subghz/counter-mode).
- **`Function requires an SD card with fresh databases.`** dans Add Manually — le magasin de clés est absent ;
  réinstallez le firmware avec la carte SD en place.

## Voir aussi

- [Systèmes pris en charge](/fr/subghz/supported-systems) · [Add Manually](/fr/subghz/add-manually)
- [Seed Capturer](/fr/subghz/seed-capturer) · [Programmation d'une télécommande](/fr/subghz/remote-prog)
- [Modes de compteur](/fr/subghz/counter-mode) · [Format de fichier .sub](/fr/subghz/file-format)
