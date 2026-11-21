---
title: MIFARE Plus
order: 75
author: gromovyna
original: ["https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/nfc/MIFARE%20Plus%20Detection.md", https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_plus, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [unleashed-docs, unleashed-src, gromovyna]
---
# MIFARE Plus

**MIFARE Plus** is NXP's successor to MIFARE Classic. It can run in several **security levels**:

| Level | Behaviour | What Flipper does |
|---|---|---|
| **SL0** | Factory/personalisation state | Identifies the card, UID emulation |
| **SL1** | **MIFARE Classic compatible** (Crypto-1) | Read **as MIFARE Classic**: dictionaries, nested attacks, MFKey, qUnleashed all apply |
| **SL2** | Classic-style data with AES (not on EV parts) | Identifies the card, UID emulation |
| **SL3** | ISO14443-4, AES-128 authentication and secure messaging | AES key dictionary attack, full dump, full emulation, write-back to the source card |

Product variants: **Plus S**, **Plus X**, **Plus SE**, **Plus EV1**, **Plus EV2** (and a generic "Plus"); sizes
1K (SE), 2K and 4K.

::: tip Unleashed
MIFARE Plus identification by product/level/size, **SL3 reading with AES dictionaries**, *Show Keys*, emulation,
*Write to Initial Card* / *Update from Initial Card*, a per-UID key cache and MIFARE Plus generators in
*Add Manually* are Unleashed features.
:::

## Reading

1. `Main Menu → NFC → Read`, hold the card.
2. **SL1** cards are read as MIFARE Classic (see [MIFARE Classic](/nfc/mifare-classic)). Key recovery for SL1 works
   exactly like for Classic; @gromovyna's [qUnleashed guide](/nfc/qunleashed) notes it applies to MIFARE Plus **SL1
   only**.
3. **SL3** cards: the AES dictionary attack starts automatically (header **"MF Plus Dictionary"**). User keys are tried
   first, then the system dictionary; a key cached from a previous save of the same UID is tried before both. The
   screen shows *Keys Found* / *Sectors Read*. There is no separate "Unlock with Dictionary" entry: the attack is part
   of `Read`.
4. Save the card. Keys are cached in `/ext/nfc/.cache/<UID>.mfpkeys`, so the next read of the same card authenticates
   at the first try.

Dictionaries: system `/ext/nfc/assets/mf_plus_dict.nfc` (33 AES-128 keys from the Proxmark3 defaults), user
`/ext/nfc/assets/mf_plus_dict_user.nfc`. Manage them in `NFC → Extra Actions → MIFARE Plus Keys` (**Add** a 16-byte
key, **List** to delete).

### Menus for an SL3 card

- After reading: **Save**, **Emulate**, **Show Keys** (*"Found MFP Keys"*: per sector A/B keys and admin keys such as
  the Card Master Key, plus totals), **Info**.
- Saved card: **Emulate**, **Write to Initial Card** (writes the dump back to the same card), **Update from Initial
  Card** (re-reads the source card with the saved keys; *"Use the source card only"* for others), **Show Keys**,
  **Rename**, **Delete**, **Info**.
- `Info → More` opens a hub with **View Dump** (blocks, admin keys, config blocks, signature) and
  **ISO14443-4 Data** (ATS etc.) → **More** (GetVersion fields: hardware/software vendor, type, version, size, batch,
  production week/year).

For other levels only the identity is kept and **Emulate UID** is offered.

## How a MIFARE Plus is identified

The firmware combines three signals:

1. **SAK**: `08` = 2K SL1, `18` = 4K SL1, `10` / `11` = 2K / 4K SL2, `20` = ISO14443-4 (SL3, but also SL0 and DESFire).
2. **ATS historical bytes** of the form `C1 05 …`: identify Plus S / X / SE without any key.
3. **GetVersion** and a security-level probe on EV1/EV2 parts, which give the authoritative type and size.

Since SAK `20` is shared with DESFire, a card is only claimed as Plus when the probe or the ATS fingerprint confirms
it.

### Reference: how NXP TagInfo does it

The Unleashed docs include an analysis of NXP's own **NFC TagInfo** app (v6.2.0) used as a reference. Its decision
procedure:

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

ATS fingerprints (historical bytes, byte-exact):

| ATS historical bytes | Sub-type | Product code |
|---|---|---|
| `C1 05 2F 2F 00 35 C7` | Plus **S** | `MF1SPLUS` |
| `C1 05 2F 2F 01 BC D6` | Plus **X** | `MF1PLUS` |
| `C1 05 21 30 00 77 C1` | Plus **SE** | `MF1SEP10` |
| `C1 05 20 30 00 AB 9B` | Plus **SE** (alt) | `MF1SEP10` |
| `4D 46 50 5F 45 4E 47` (`"MFP_ENG"`) | Engineering sample | — |
| no match | Plus **X** (default) | `MF1PLUS` |

On the `C1 05 2F 2F …` family, byte 4 tells S (`00`) from X (`01`). EV1/EV2 parts answer **Read-Signature** (`3C`),
Plus S/X don't. In GetVersion the vendor byte is `04` (NXP) and the storage byte `22` = 2K, `42` = 4K.

SAK interpretation used by TagInfo:

| SAK | Meaning |
|---|---|
| `08` | Classic 1K / Plus 2K SL1 |
| `18` | Classic 4K / Plus 4K SL1 |
| `09` | MIFARE Mini |
| `19` | Classic 2K / Plus 2K variant |
| `28`, `38` | SmartMX with Classic 1K / 4K |
| `88` | NXP Classic 1K (0x80 bit) |
| `98`, `B8` | SmartMX / Pro variants |
| `01` | legacy / TNP marker |
| `20` | ISO14443-4 → Plus SL3 / EV, DESFire |

Memory size on SL1 is probed with Plus AES **First-Auth** frames `70 XX 40 01 00` to key blocks `0x4010`, `0x4020`,
`0x4040`, `0x4064`: the highest one that answers bounds the sector count (base / 2K / 4K / extended). Product codes
emitted: `MF1SPLUS60`/`80` (S 2K/4K), `MF1PLUS60`/`80` (X 2K/4K), `MF1SEP10xx` (SE), `MF1P2101` (EV1 2K).

## Creating a MIFARE Plus manually

`NFC → Add Manually` offers Plus SE (4/7-byte UID), Plus S, X, EV1 and EV2 in 2K/4K with 4- or 7-byte UID. The
generated card gets the matching ATS historical bytes, see [Adding cards manually](/nfc/add-manually).

## Related

[MIFARE Classic](/nfc/mifare-classic) · [Reading cards](/nfc/read) · [qUnleashed](/nfc/qunleashed) ·
[NFC file format](/nfc/file-format)
