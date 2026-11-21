---
title: Modes de compteur
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-docs, unleashed-src]
---
# Modes de compteur (expérimental)

Le **Counter Mode** modifie la manière dont le compteur tournant avance quand le Flipper émet un signal à code
tournant enregistré. L'objectif : un clone de votre télécommande d'origine qui **n'entre pas en conflit** avec elle,
afin que le Flipper et l'originale puissent être utilisés avec le même récepteur sans désynchronisation.
(Pour le contexte : [Codes tournants](/fr/subghz/rolling-codes).)

::: tip Unleashed
Les modes de compteur sont une fonction propre à Unleashed. Protocoles pris en charge : **Nice FloR-S, CAME Atomo,
Alutech AT-4N, KeeLoq, V2 Phoenix**.
:::

::: danger À lire avant toute utilisation
N'expérimentez pas avec du matériel auquel vous n'avez pas accès. Si vous n'êtes pas sûr du mode qui fonctionne pour
votre système et que vous **ne pouvez pas reprogrammer votre télécommande d'origine** dans le récepteur — n'utilisez
pas ces modes. Ils peuvent désynchroniser ou exclure votre télécommande. Si vous pouvez tester sur votre propre
récepteur, faites savoir à l'équipe Unleashed ce qui fonctionne (issues GitHub / discussions communautaires).
:::

## Comment définir un mode

### Option 1 — éditer le fichier `.sub`

1. Copiez le fichier depuis `/ext/subghz/` vers un ordinateur (qFlipper, application mobile ou lecteur de cartes).
2. Ajoutez une ligne à la fin :
   ```text
   CounterMode: X
   ```
   où `X` est le numéro du mode. Attention à l'espace après les deux-points.
3. Recopiez le fichier sur le Flipper.

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Nice FloR-S
Bit: 52
Key: AA AA AA AA AA AA AA
CounterMode: 1
```

### Option 2 — Signal Settings sur le Flipper

Avec **Debug** activé, le menu d'un signal enregistré gagne une entrée supplémentaire :
`Sub-GHz → Saved → <fichier> → Signal Settings`. Sa ligne `Counter Mode` propose `System` (mode 0) et `Mode 1` …
jusqu'au dernier mode dont dispose le protocole, et écrit votre choix dans le fichier aussitôt. Le même écran permet
aussi de modifier le compteur et le code du bouton : voir [Signal Settings](/fr/subghz/signal-settings).

## Modes par protocole {#modes-by-protocol}

Le mode 0 est toujours celui par défaut : il se comporte comme une télécommande ordinaire, le compteur croît de la
valeur globale [Counter Incr.](/fr/subghz/settings) (+1 par défaut) et repasse à 0 après `0xFFFF`.

### Nice FloR-S

| Mode | Compteur | Remarques |
|---|---|---|
| 0 | +multiplicateur | par défaut |
| 1 | `0x0001 / 0xFFFE` | récepteur **floxi2r** |
| 2 | `0x0000 / 0x0001` | récepteur **ox2** |

### CAME Atomo

| Mode | Compteur | Remarques |
|---|---|---|
| 0 | +multiplicateur | par défaut |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | fonctionne avec le CAME **RE432** externe, peut-être d'autres |
| 2 | `0x807B / 0x807C / 0x007B / 0x007C` | fonctionne avec le CAME **RE432** externe, peut-être d'autres |
| 3 | figé | le compteur n'est pas incrémenté |

### Alutech AT-4N

| Mode | Compteur | Remarques |
|---|---|---|
| 0 | +multiplicateur | par défaut |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | récepteur **MCSW-3.3M** |
| 2 | `0x0000 … 0x0005` | autres cartes de récepteur |

### KeeLoq

| Mode | Compteur | Remarques |
|---|---|---|
| 0 | +multiplicateur | par défaut |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | peut fonctionner avec certains systèmes |
| 2 | `+0x3333` par émission (13107) | p. ex. DoorHan |
| 3 | `0x8006 / 0x8007 / 0x0006 / 0x0007` | p. ex. Hormann EcoStar |
| 4 | `0x807B / 0x807C / 0x007B / 0x007C` | p. ex. Nice Smilo |
| 5 | `0x0000 / 0xFFFF` | alterne entre 0 et 65535 |
| 6 | figé | le compteur n'est pas incrémenté |
| 7–10 | lots de resynchronisation forcée | DoorHan, Phantom / Hiland, voir ci-dessous |

#### Modes 7–10 : lots de resynchronisation forcée (DoorHan, Phantom / Hiland)

Ces modes ne font pas avancer le compteur ; chaque appui émet un **lot fixe** de codes. Un récepteur ne se
resynchronise que s'il entend deux émissions avec des compteurs **consécutifs** ; le lot est donc construit à partir
de paires consécutives, espacées de telle sorte que chaque saut reste dans la fenêtre de resynchronisation du
récepteur et que les paires couvrent ensemble tout l'espace du compteur. Cela ramène le récepteur depuis n'importe
quel état. Le compteur de votre fichier n'est pas modifié : chaque appui émet donc le même lot et le fichier reste
utilisable.

Chaque lot reproduit, code pour code, ce qu'une télécommande clone émet pour cette famille de cartes. Les modes 7–9
= clone DoorHan Smart, le mode 10 = clone Phantom / Hiland. `X` = le compteur de votre fichier.

| Mode | Pour | Lot | Durée par appui |
|---|---|---|---|
| 7 | les plus anciennes cartes DoorHan | 12 codes : `X / X+1`, quatre paires avançant par pas de 15998 (bouton 0), puis `X-2 / X-1` ; la première et la dernière paire portent votre bouton | ~1,3 s |
| 8 | DHRE, la plupart des cartes récentes, clones de portails battants | 12 codes : `X / X+1`, quatre paires espacées de `+0x3334`, puis retour à votre compteur où tombe `X+1` avec votre bouton | ~1,3 s |
| 9 | cartes de volets roulants CV01, autres cartes anciennes | 3 codes avec votre bouton : `X + 0x8000`, `X-1`, `X+1`, chacun émis deux fois | ~0,65 s |
| 10 | Phantom / Hiland | 2 codes avec votre bouton : `0xFFFE` et `0xFFFF` en absolu, chacun émis trois fois | ~0,4 s |

::: warning Le mode 7 a changé
Le mode 8 correspond exactement à ce que faisait `CounterMode: 7` dans les versions antérieures. Si vous avez un
fichier avec `CounterMode: 7` qui fonctionnait, passez-le en `CounterMode: 8`.
:::

Détails :

- Dans les lots longs (7 et 8), chaque code est émis **une seule fois** (la télécommande clone d'origine émet chacun
  deux ou trois fois) — tout le lot est construit en mémoire, et le tripler nécessiterait 20 Ko au lieu de 8 Ko.
  Réémettre le lot n'est pas un substitut : un récepteur qui s'est déjà resynchronisé lit un second passage comme un
  nouveau parcours et actionne le portail une deuxième fois, tandis qu'une répétition immédiate d'un même code est
  ignorée comme un doublon.
- Le mode 10 ignore le compteur de votre fichier. Sans parcours, un seul appui resynchronise un récepteur se
  trouvant sur n'importe laquelle des 32768 valeurs en dessous de `0xFFFE` — là où se situe un récepteur ayant
  dérivé en avant de votre télécommande. Si cela ne prend pas, émettez encore une fois.
- **Maintenir** Send répète le lot tant que vous maintenez ; un récepteur qui s'est resynchronisé au premier passage
  interprète cela comme un nouvel appui. Appuyer de nouveau sur Send pendant l'émission d'un lot **l'interrompt**.

### V2 Phoenix (Phox)

| Mode | Compteur | Remarques |
|---|---|---|
| 0 | +multiplicateur | par défaut |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` (« ofex like ») | vérifié fonctionnel |
| 2 | `0x0000 … 0x0004` | peut fonctionner |

## Exemple : KeeLoq DoorHan avec +0x3333

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: Doorhan
CounterMode: 2
```

## Dépannage et FAQ

- **Le fichier ne fonctionne plus après l'ajout de `CounterMode`** — vérifiez la syntaxe `CounterMode: X` (espace
  après les deux-points) et que le numéro est valide pour le protocole.
- **Numéro de mode invalide ?** Le dernier mode de la liste du protocole est utilisé.
- **Faut-il l'ajouter dans tous les fichiers ?** Non. Sans `CounterMode`, le mode 0 est utilisé.
- **Cela peut-il abîmer ma télécommande / mon récepteur ?** Cela peut désynchroniser votre télécommande, selon le
  récepteur. Ne l'utilisez pas si vous ne pouvez pas réapparier l'originale.
- **Quel mode utiliser ?** Si vous n'êtes pas sûr — aucun. Préférez plutôt une
  [nouvelle télécommande](/fr/subghz/add-manually).

## Voir aussi

- [Signal Settings](/fr/subghz/signal-settings) — définir un mode, le compteur et le bouton sur le Flipper
- [Codes tournants](/fr/subghz/rolling-codes) · [KeeLoq](/fr/subghz/keeloq)
- [Radio Settings : Counter Incr.](/fr/subghz/settings) · [Format de fichier .sub](/fr/subghz/file-format)
