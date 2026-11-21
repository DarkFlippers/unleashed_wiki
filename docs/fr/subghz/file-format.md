---
title: Formats de fichiers
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/resources/subghz/assets, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md]
sources: [unleashed-docs, unleashed-src]
---
# Formats de fichiers Sub-GHz

Tous les fichiers Sub-GHz sont du texte brut au *Flipper File Format* (des lignes `Clé: valeur`), vous pouvez donc
les consulter et les modifier sur un ordinateur. Cette page décrit les fichiers de signaux (`.sub`) et les fichiers
de configuration de `/ext/subghz/assets/`.

| Chemin | Contenu |
|---|---|
| `/ext/subghz/*.sub` | Signaux enregistrés : clés, RAW et BinRAW |
| `/ext/subghz/assets/setting_user` | Vos fréquences, liste du hopper, presets personnalisés |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Vos clés constructeur KeeLoq |
| `/ext/subghz/assets/keeloq_mfcodes` | Clés constructeur KeeLoq intégrées (chiffrées, livrées avec le firmware) |
| `/ext/subghz/assets/nice_flor_s`, `alutech_at_4n` | Tables intégrées pour ces protocoles |
| `/ext/subghz/assets/dangerous_settings` | Interrupteur de la plage de fréquences étendue, voir [Fréquences](/fr/subghz/frequencies#extended-range) |

## Structure d'un fichier `.sub`

Un fichier `.sub` comporte trois parties :

1. **En-tête** — type de fichier, version, fréquence.
2. **Preset** — preset de modulation, ou une configuration CC1101 personnalisée complète.
3. **Données** — nom du protocole et ses champs, ou timings RAW.

### En-tête

| Champ | Type | Description |
|---|---|---|
| `Filetype` | chaîne | `Flipper SubGhz Key File` pour les clés, `Flipper SubGhz RAW File` pour les enregistrements RAW |
| `Version` | uint | Version du format de fichier, actuellement `1` |
| `Frequency` | uint | Fréquence en Hz, par exemple `433920000` |

### Preset

| Champ | Description |
|---|---|
| `Preset` | Nom du preset. Pour un preset personnalisé, il doit valoir `FuriHalSubGhzPresetCustom` |
| `Custom_preset_module` | Émetteur-récepteur, `CC1101` pour le Flipper Zero (preset personnalisé uniquement) |
| `Custom_preset_data` | Configuration de l'émetteur-récepteur (preset personnalisé uniquement) |

Presets intégrés :

| Valeur de `Preset` | Nom dans le menu | Signification |
|---|---|---|
| `FuriHalSubGhzPresetOok270Async` | `AM270` | OOK, bande passante de 270 kHz |
| `FuriHalSubGhzPresetOok650Async` | `AM650` | OOK, bande passante de 650 kHz |
| `FuriHalSubGhzPreset2FSKDev238Async` | `FM238` | 2-FSK, excursion de 2,38 kHz, bande passante de 270 kHz |
| `FuriHalSubGhzPreset2FSKDev12KAsync` | `FM12K` | 2-FSK, excursion de 12 kHz |
| `FuriHalSubGhzPreset2FSKDev476Async` | `FM476` | 2-FSK, excursion de 47,6 kHz, bande passante de 270 kHz |

Un preset personnalisé est intégré au fichier : un autre Flipper peut donc l'émettre même sans ce preset dans ses
réglages.

#### Données d'un preset personnalisé {#custom-preset-data}

Des octets hexadécimaux séparés par des espaces : `XX YY XX YY … 00 00 ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ`

- `XX` — adresse du registre CC1101, `YY` — valeur du registre (autant de paires que nécessaire) ;
- `00 00` — fin du bloc de registres ;
- `ZZ ×8` — la table PA de 8 octets (rampe de l'amplificateur de puissance).

Voir la [fiche technique du CC1101](https://www.ti.com/lit/ds/symlink/cc1101.pdf) pour la signification des
registres.

### Fichiers-clés

Les signaux décodés stockent le nom du protocole et ses champs :

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

| Champ | Description |
|---|---|
| `Protocol` | Nom du protocole exactement comme dans le registre de protocoles (p. ex. `Princeton`, `KeeLoq`, `Nice FloR-S`, `CAME Atomo`, `Security+ 2.0`) |
| `Bit` | Longueur de la charge utile en bits |
| `Key` | Charge utile, hexadécimal, 8 octets |
| `TE` | Durée d'impulsion de base (intervalle de quantification) en µs, pour les protocoles qui la stockent |

Les protocoles peuvent ajouter leurs propres champs. Ceux que vous rencontrerez dans Unleashed :

| Champ | Utilisé par | Signification |
|---|---|---|
| `Manufacture` | KeeLoq, FAAC SLH / Genius | Constructeur dont la clé décode le signal (p. ex. `DoorHan`, `BFT`, `Genius`) |
| `Seed` | BFT Mitto, Erreka, FAAC SLH, Genius, certains KeeLoq | Secret propre à la télécommande pour le secure learning |
| `CounterMode` | Nice Flor-S, CAME Atomo, Alutech AT-4N, KeeLoq, V2 Phoenix | Comportement expérimental du compteur, voir [Modes de compteur](/fr/subghz/counter-mode) |
| `Secplus_packet_1`, `Pin` | Security+ 2.0 | Second paquet ; PIN du clavier pour les paquets de 86 bits ([Security+ PIN](/fr/subghz/secplus-pin)) |
| `Cert` | Nice O-Code | Certificat du récepteur ([Nice O-Code](/fr/subghz/nice-o-code)) |

Exemple de preset personnalisé :

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetCustom
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

::: warning Modifier des fichiers à code tournant
Changer à la main le champ `Key` d'un protocole dynamique produit rarement un code valide. Pour modifier le numéro
de série, le bouton ou le compteur, utilisez
[Add Manually [Advanced]](/fr/subghz/add-manually) ou, en mode Debug,
`Saved → fichier → Signal Settings`.
:::

### Fichiers RAW

Enregistrements issus de [Read RAW](/fr/subghz/read-raw) :

```text
Filetype: Flipper SubGhz RAW File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: RAW
RAW_Data: 29262 361 -68 2635 -66 24113 -66 11 ...
RAW_Data: -424 205 -412 159 -412 381 -240 181 ...
```

- `Protocol` doit valoir `RAW`.
- `RAW_Data` — durées en µs : positive = porteuse active, négative = porteuse coupée. Les valeurs doivent être non
  nulles, commencer par un nombre positif et alterner de signe. Jusqu'à 512 valeurs par ligne ; la ligne peut se
  répéter autant de fois que nécessaire.

Les charges utiles longues sont lues depuis la carte SD pendant l'émission. Avec des timings très courts (moins de
10 µs), une carte lente peut ne pas suivre et l'émission s'arrête avant la fin.

### Fichiers BinRAW

`Bin RAW` dans `Read → Config` produit des fichiers **BinRAW**. Contrairement au RAW, ils ne stockent que la séquence
répétitive utile, avec le débit binaire reconstitué et sans le bruit : ils peuvent donc rejouer presque n'importe
quel protocole **statique**, connu ou non. Maintenez le bouton de la télécommande un peu plus longtemps lors de la
lecture, afin d'accumuler suffisamment de données.

| Champ | Description |
|---|---|
| `Protocol` | `BinRAW` |
| `Bit` | Longueur de la charge utile de tout le fichier en bits (max. 4096) |
| `TE` | Intervalle de quantification, µs |
| `Bit_RAW` | Longueur du bloc `Data_RAW` qui suit, en bits |
| `Data_RAW` | Durées encodées : chaque bit = un `TE` ; `1` = porteuse, `0` = pas de porteuse |

Exemple : `TE: 100`, `Bit_RAW: 8`, `Data_RAW: 37` → `0b00110111` → émet `-200 200 -100 300`.
Les paires `Bit_RAW` + `Data_RAW` forment des blocs répétés ; plusieurs blocs sont émis les uns après les autres.

```text
Protocol: BinRAW
Bit: 1572
TE: 597
Bit_RAW: 260
Data_RAW: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F 4A B5 55 4C B3 52 AC D5 2D 53 52 AD 4A D5 35 00
```

## `setting_user` {#setting-user}

Fréquences et presets supplémentaires, chargés au démarrage de l'application Sub-GHz. Renommez
`setting_user.example` en `setting_user`.

```text
Filetype: Flipper SubGhz Setting File
Version: 1

# Add standard frequencies included with firmware and place user frequencies after them
Add_standard_frequencies: true

# Default frequency for "Read" and "Read Raw"
Default_frequency: 433920000

# Frequencies for "Read", "Read Raw" and "Frequency Analyzer"
Frequency: 300000000
Frequency: 310000000

# Frequencies for hopping mode (keep this list small)
Hopper_frequency: 300000000
Hopper_frequency: 310000000

# Custom preset
Custom_preset_name: AM_1
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
```

| Clé | Signification |
|---|---|
| `Add_standard_frequencies` | `true` — liste du firmware + les vôtres (ajoutées à la suite) ; `false` — seulement les vôtres (il faut alors remplir à la fois `Frequency` et `Hopper_frequency`) |
| `Default_frequency` | Fréquence sur laquelle Read / Read RAW démarrent |
| `Frequency` | Ajoute une fréquence à la liste principale (9 chiffres, Hz). Répétable |
| `Hopper_frequency` | Ajoute une fréquence au hopping. En répéter une fait que le Flipper l'écoute plus souvent |
| `Custom_preset_name` / `_module` / `_data` | Un preset de modulation personnalisé, affiché dans la liste `Modulation` sous ce nom. Format des données : [ci-dessus](#custom-preset-data) |

Le fichier `.example` est livré avec des presets commentés que vous pouvez activer : `FM95`, `FM15k` (2-FSK,
200 kHz de bande passante / filtre à 135 kHz, excursion de 15,86 kHz), `Pagers`, `AM_1`, `AM_2`.

## `keeloq_mfcodes_user` {#keeloq-mfcodes-user}

Vos propres clés constructeur KeeLoq, chargées au démarrage de l'application en plus de la base intégrée (chiffrée).
Créez-le depuis `keeloq_mfcodes_user.example`, supprimez les clés d'exemple et **laissez une ligne vide à la fin**.

```text
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:2:Test2
```

Chaque ligne est de la forme `KEY:METHOD:NAME` :

- `KEY` — clé constructeur de 64 bits, 16 chiffres hexadécimaux ;
- `NAME` — nom sans espaces, jusqu'à 64 caractères (affiché comme constructeur dans Read) ;
- `METHOD` — type d'apprentissage :

| Valeur | Apprentissage |
|---|---|
| `0` | tout essayer : itère sur la clé précédente et sur la clé constructeur, en ordre d'octets direct et inversé |
| `1` | Simple Learning |
| `2` | Normal Learning |
| `3` | Secure Learning (nécessite un Seed) |
| `4` | Magic XOR type 1 |
| `5` | FAAC SLH |
| `6` | Magic Serial type 1 |
| `7` | Magic Serial type 2 |
| `8` | Magic Serial type 3 |

`Encryption: 0` signifie que le fichier est en texte clair — les fichiers utilisateur ne doivent pas être chiffrés.
Pour en savoir plus sur les types d'apprentissage : [KeeLoq](/fr/subghz/keeloq).

## Voir aussi

- [Read](/fr/subghz/read) · [Read RAW](/fr/subghz/read-raw) · [Fréquences](/fr/subghz/frequencies) · [Radio Settings](/fr/subghz/settings)
- [KeeLoq](/fr/subghz/keeloq) · [Modes de compteur](/fr/subghz/counter-mode) · [Fichiers de carte de Sub-GHz Remote](/fr/subghz/remote)
