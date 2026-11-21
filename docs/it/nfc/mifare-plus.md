---
title: MIFARE Plus
order: 75
author: gromovyna
original: ["https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/nfc/MIFARE%20Plus%20Detection.md", https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_plus, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [unleashed-docs, unleashed-src, gromovyna]
---
# MIFARE Plus

**MIFARE Plus** è il successore di MIFARE Classic prodotto da NXP. Può operare in diversi **livelli di sicurezza**:

| Livello | Comportamento | Cosa fa il Flipper |
|---|---|---|
| **SL0** | Stato di fabbrica/personalizzazione | Identifica la carta, emulazione dell'UID |
| **SL1** | **Compatibile MIFARE Classic** (Crypto-1) | Lettura **come MIFARE Classic**: dizionari, attacchi nested, MFKey, qUnleashed sono tutti applicabili |
| **SL2** | Dati in stile Classic con AES (non sulle versioni EV) | Identifica la carta, emulazione dell'UID |
| **SL3** | ISO14443-4, autenticazione AES-128 e secure messaging | Attacco a dizionario sulle chiavi AES, dump completo, emulazione completa, riscrittura sulla carta di origine |

Varianti di prodotto: **Plus S**, **Plus X**, **Plus SE**, **Plus EV1**, **Plus EV2** (più un "Plus" generico);
dimensioni 1K (SE), 2K e 4K.

::: tip Unleashed
L'identificazione MIFARE Plus per prodotto/livello/dimensione, la **lettura SL3 con i dizionari AES**, *Show Keys*,
l'emulazione, *Write to Initial Card* / *Update from Initial Card*, una cache di chiavi per UID e i generatori MIFARE
Plus in *Add Manually* sono funzioni di Unleashed.
:::

## Lettura

1. `Main Menu → NFC → Read`, appoggia la carta.
2. Le carte **SL1** vengono lette come MIFARE Classic (vedi [MIFARE Classic](/it/nfc/mifare-classic)). Il recupero
   delle chiavi per SL1 funziona esattamente come per Classic; la [guida a qUnleashed](/it/nfc/qunleashed) di
   @gromovyna segnala che vale **solo** per MIFARE Plus **SL1**.
3. Carte **SL3**: l'attacco a dizionario AES parte automaticamente (intestazione **"MF Plus Dictionary"**). Vengono
   provate prima le chiavi utente, poi il dizionario di sistema; una chiave in cache da un salvataggio precedente dello
   stesso UID viene provata prima di entrambi. La schermata mostra *Keys Found* / *Sectors Read*. Non esiste una voce
   "Unlock with Dictionary" separata: l'attacco fa parte di `Read`.
4. Salva la carta. Le chiavi vengono messe in cache in `/ext/nfc/.cache/<UID>.mfpkeys`, così la lettura successiva della
   stessa carta si autentica al primo tentativo.

Dizionari: di sistema `/ext/nfc/assets/mf_plus_dict.nfc` (33 chiavi AES-128 prese dai valori predefiniti di
Proxmark3), utente `/ext/nfc/assets/mf_plus_dict_user.nfc`. Si gestiscono in
`NFC → Extra Actions → MIFARE Plus Keys` (**Add** per una chiave da 16 byte, **List** per eliminarle).

### Menu di una carta SL3

- Dopo la lettura: **Save**, **Emulate**, **Show Keys** (*"Found MFP Keys"*: chiavi A/B per settore e chiavi
  amministrative come la Card Master Key, più i totali), **Info**.
- Carta salvata: **Emulate**, **Write to Initial Card** (riscrive il dump sulla stessa carta), **Update from Initial
  Card** (rilegge la carta di origine con le chiavi salvate; *"Use the source card only"* per le altre),
  **Show Keys**, **Rename**, **Delete**, **Info**.
- `Info → More` apre un hub con **View Dump** (blocchi, chiavi amministrative, blocchi di configurazione, firma) e
  **ISO14443-4 Data** (ATS ecc.) → **More** (campi di GetVersion: vendor hardware/software, tipo, versione,
  dimensione, lotto, settimana/anno di produzione).

Per gli altri livelli viene conservata solo l'identità e viene proposta **Emulate UID**.

## Come viene identificata una MIFARE Plus

Il firmware combina tre segnali:

1. **SAK**: `08` = 2K SL1, `18` = 4K SL1, `10` / `11` = 2K / 4K SL2, `20` = ISO14443-4 (SL3, ma anche SL0 e DESFire).
2. **Byte storici dell'ATS** nella forma `C1 05 …`: identificano Plus S / X / SE senza alcuna chiave.
3. **GetVersion** e una sonda del livello di sicurezza sulle versioni EV1/EV2, che forniscono tipo e dimensione in modo
   autorevole.

Poiché il SAK `20` è condiviso con DESFire, una carta viene dichiarata Plus solo quando la sonda o l'impronta dell'ATS
lo confermano.

### Riferimento: come fa NXP TagInfo

La documentazione di Unleashed include un'analisi dell'app **NFC TagInfo** di NXP (v6.2.0) usata come riferimento. La
sua procedura decisionale:

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

Impronte ATS (byte storici, esatti al byte):

| Byte storici dell'ATS | Sottotipo | Codice prodotto |
|---|---|---|
| `C1 05 2F 2F 00 35 C7` | Plus **S** | `MF1SPLUS` |
| `C1 05 2F 2F 01 BC D6` | Plus **X** | `MF1PLUS` |
| `C1 05 21 30 00 77 C1` | Plus **SE** | `MF1SEP10` |
| `C1 05 20 30 00 AB 9B` | Plus **SE** (alternativo) | `MF1SEP10` |
| `4D 46 50 5F 45 4E 47` (`"MFP_ENG"`) | Campione di ingegneria | — |
| nessuna corrispondenza | Plus **X** (predefinito) | `MF1PLUS` |

Nella famiglia `C1 05 2F 2F …` il byte 4 distingue S (`00`) da X (`01`). Le versioni EV1/EV2 rispondono a
**Read-Signature** (`3C`), Plus S/X no. In GetVersion il byte del vendor è `04` (NXP) e il byte della memoria `22` =
2K, `42` = 4K.

Interpretazione del SAK usata da TagInfo:

| SAK | Significato |
|---|---|
| `08` | Classic 1K / Plus 2K SL1 |
| `18` | Classic 4K / Plus 4K SL1 |
| `09` | MIFARE Mini |
| `19` | Classic 2K / variante Plus 2K |
| `28`, `38` | SmartMX con Classic 1K / 4K |
| `88` | NXP Classic 1K (bit 0x80) |
| `98`, `B8` | Varianti SmartMX / Pro |
| `01` | marcatore legacy / TNP |
| `20` | ISO14443-4 → Plus SL3 / EV, DESFire |

La dimensione della memoria su SL1 viene sondata con frame Plus AES **First-Auth** `70 XX 40 01 00` verso i blocchi
chiave `0x4010`, `0x4020`, `0x4040`, `0x4064`: il più alto che risponde delimita il numero di settori (base / 2K / 4K /
estesa). Codici prodotto emessi: `MF1SPLUS60`/`80` (S 2K/4K), `MF1PLUS60`/`80` (X 2K/4K), `MF1SEP10xx` (SE),
`MF1P2101` (EV1 2K).

## Creare una MIFARE Plus manualmente

`NFC → Add Manually` offre Plus SE (UID da 4/7 byte), Plus S, X, EV1 ed EV2 in 2K/4K con UID da 4 o 7 byte. La carta
generata riceve i byte storici dell'ATS corrispondenti, vedi
[Aggiungere carte manualmente](/it/nfc/add-manually).

## Pagine correlate

[MIFARE Classic](/it/nfc/mifare-classic) · [Leggere le carte](/it/nfc/read) · [qUnleashed](/it/nfc/qunleashed) ·
[Formato dei file NFC](/it/nfc/file-format)
