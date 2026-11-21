---
title: MIFARE Plus
order: 75
author: gromovyna
original: ["https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/nfc/MIFARE%20Plus%20Detection.md", https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_plus, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [unleashed-docs, unleashed-src, gromovyna]
---
# MIFARE Plus

**MIFARE Plus** est le successeur de MIFARE Classic chez NXP. Elle peut fonctionner à plusieurs **niveaux de
sécurité** :

| Niveau | Comportement | Ce que fait le Flipper |
|---|---|---|
| **SL0** | État usine / personnalisation | Identifie la carte, émulation de l'UID |
| **SL1** | **Compatible MIFARE Classic** (Crypto-1) | Lecture **comme une MIFARE Classic** : dictionnaires, attaques nested, MFKey, qUnleashed s'appliquent tous |
| **SL2** | Données de type Classic avec AES (absent des références EV) | Identifie la carte, émulation de l'UID |
| **SL3** | ISO14443-4, authentification AES-128 et messagerie sécurisée | Attaque par dictionnaire de clés AES, dump complet, émulation complète, réécriture sur la carte source |

Variantes de produit : **Plus S**, **Plus X**, **Plus SE**, **Plus EV1**, **Plus EV2** (et une « Plus » générique) ;
tailles 1K (SE), 2K et 4K.

::: tip Unleashed
L'identification des MIFARE Plus par produit/niveau/taille, la **lecture SL3 avec des dictionnaires AES**,
*Show Keys*, l'émulation, *Write to Initial Card* / *Update from Initial Card*, un cache de clés par UID et les
générateurs MIFARE Plus dans *Add Manually* sont des fonctions d'Unleashed.
:::

## Lecture

1. `Main Menu → NFC → Read`, présentez la carte.
2. Les cartes **SL1** sont lues comme des MIFARE Classic (voir [MIFARE Classic](/fr/nfc/mifare-classic)). La
   récupération des clés en SL1 fonctionne exactement comme pour une Classic ; le
   [guide qUnleashed](/fr/nfc/qunleashed) de @gromovyna précise qu'il ne s'applique qu'aux MIFARE Plus **SL1**.
3. Cartes **SL3** : l'attaque par dictionnaire AES démarre automatiquement (en-tête **« MF Plus Dictionary »**). Les
   clés utilisateur sont essayées d'abord, puis le dictionnaire système ; une clé mise en cache lors d'un
   enregistrement antérieur du même UID est essayée avant les deux. L'écran affiche *Keys Found* / *Sectors Read*. Il
   n'y a pas d'entrée « Unlock with Dictionary » séparée : l'attaque fait partie de `Read`.
4. Enregistrez la carte. Les clés sont mises en cache dans `/ext/nfc/.cache/<UID>.mfpkeys`, de sorte que la lecture
   suivante de la même carte s'authentifie dès le premier essai.

Dictionnaires : système `/ext/nfc/assets/mf_plus_dict.nfc` (33 clés AES-128 issues des valeurs par défaut de
Proxmark3), utilisateur `/ext/nfc/assets/mf_plus_dict_user.nfc`. Gérez-les dans
`NFC → Extra Actions → MIFARE Plus Keys` (**Add** pour une clé de 16 octets, **List** pour supprimer).

### Les menus d'une carte SL3

- Après la lecture : **Save**, **Emulate**, **Show Keys** (*« Found MFP Keys »* : clés A/B par secteur et clés
  d'administration comme la Card Master Key, plus les totaux), **Info**.
- Carte enregistrée : **Emulate**, **Write to Initial Card** (réécrit le dump sur la même carte),
  **Update from Initial Card** (relit la carte source avec les clés enregistrées ; *« Use the source card only »*
  pour les autres), **Show Keys**, **Rename**, **Delete**, **Info**.
- `Info → More` ouvre un hub avec **View Dump** (blocs, clés d'administration, blocs de configuration, signature) et
  **ISO14443-4 Data** (ATS, etc.) → **More** (champs GetVersion : fabricant matériel/logiciel, type, version, taille,
  lot, semaine/année de production).

Pour les autres niveaux, seule l'identité est conservée et **Emulate UID** est proposé.

## Comment une MIFARE Plus est identifiée

Le firmware combine trois signaux :

1. Le **SAK** : `08` = 2K SL1, `18` = 4K SL1, `10` / `11` = 2K / 4K SL2, `20` = ISO14443-4 (SL3, mais aussi SL0 et
   DESFire).
2. Les **octets historiques de l'ATS** de la forme `C1 05 …` : ils identifient les Plus S / X / SE sans aucune clé.
3. **GetVersion** et une sonde de niveau de sécurité sur les références EV1/EV2, qui donnent le type et la taille
   faisant foi.

Comme le SAK `20` est partagé avec DESFire, une carte n'est déclarée Plus que lorsque la sonde ou l'empreinte ATS le
confirme.

### Référence : comment NXP TagInfo procède

La documentation Unleashed inclut une analyse de l'application **NFC TagInfo** de NXP elle-même (v6.2.0), prise comme
référence. Sa procédure de décision :

```text
NFC tag presented
├─ SAK ∈ {01,08,09,18,19,28,38,88,98,B8} → "Classic lane" (MifareClassic, SL1)
│   ├─ RATS (E0 80) → ATS, then DESELECT (C2)
│   │   match ATS historical bytes → S | X | SE | Engineering
│   ├─ Read-Signature (3C 00), status 90 → EV generation → EV1
│   ├─ security level = SL1 (answers Classic block auth)
│   └─ size = Plus AES First-Auth probe to increasing key-block addresses
└─ SAK == 20 → "ISO-DEP lane" (IsoDep, SL3/EV)
    ├─ SELECT VCA applet (00 A4 04 00 10 A0 00 00 03 96 56 43 41 …) succeeds → SL3
    ├─ GET_VERSION (60 … AF) → EV1 | EV2 (+ storage size)
    └─ size = GET_VERSION storage byte (22 = 2K, 42 = 4K)
```

Empreintes ATS (octets historiques, à l'octet près) :

| Octets historiques de l'ATS | Sous-type | Code produit |
|---|---|---|
| `C1 05 2F 2F 00 35 C7` | Plus **S** | `MF1SPLUS` |
| `C1 05 2F 2F 01 BC D6` | Plus **X** | `MF1PLUS` |
| `C1 05 21 30 00 77 C1` | Plus **SE** | `MF1SEP10` |
| `C1 05 20 30 00 AB 9B` | Plus **SE** (variante) | `MF1SEP10` |
| `4D 46 50 5F 45 4E 47` (`"MFP_ENG"`) | Échantillon d'ingénierie | — |
| aucune correspondance | Plus **X** (par défaut) | `MF1PLUS` |

Dans la famille `C1 05 2F 2F …`, l'octet 4 distingue la S (`00`) de la X (`01`). Les références EV1/EV2 répondent à
**Read-Signature** (`3C`), les Plus S/X non. Dans GetVersion, l'octet fabricant vaut `04` (NXP) et l'octet de
capacité `22` = 2K, `42` = 4K.

Interprétation du SAK utilisée par TagInfo :

| SAK | Signification |
|---|---|
| `08` | Classic 1K / Plus 2K SL1 |
| `18` | Classic 4K / Plus 4K SL1 |
| `09` | MIFARE Mini |
| `19` | Classic 2K / variante Plus 2K |
| `28`, `38` | SmartMX avec Classic 1K / 4K |
| `88` | NXP Classic 1K (bit 0x80) |
| `98`, `B8` | Variantes SmartMX / Pro |
| `01` | marqueur legacy / TNP |
| `20` | ISO14443-4 → Plus SL3 / EV, DESFire |

La taille mémoire en SL1 est sondée avec des trames Plus AES **First-Auth** `70 XX 40 01 00` vers les blocs de clés
`0x4010`, `0x4020`, `0x4040`, `0x4064` : le plus élevé qui répond borne le nombre de secteurs (base / 2K / 4K /
étendu). Codes produit émis : `MF1SPLUS60`/`80` (S 2K/4K), `MF1PLUS60`/`80` (X 2K/4K), `MF1SEP10xx` (SE),
`MF1P2101` (EV1 2K).

## Créer une MIFARE Plus manuellement

`NFC → Add Manually` propose les Plus SE (UID de 4/7 octets), Plus S, X, EV1 et EV2 en 2K/4K avec un UID de 4 ou
7 octets. La carte générée reçoit les octets historiques d'ATS correspondants, voir
[Ajouter des cartes manuellement](/fr/nfc/add-manually).

## Voir aussi

[MIFARE Classic](/fr/nfc/mifare-classic) · [Lire des cartes](/fr/nfc/read) · [qUnleashed](/fr/nfc/qunleashed) ·
[Format de fichier NFC](/fr/nfc/file-format)
