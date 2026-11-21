---
title: NFC file format
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc]
sources: [unleashed-docs, unleashed-src]
---
# NFC file format

Saved cards are plain-text **Flipper Format** files with the `.nfc` extension in `/ext/nfc/`. You can open and edit
them in any text editor, qFlipper or qUnleashed. Related files:

| Path | Content |
|---|---|
| `/ext/nfc/<name>.nfc` | Saved card |
| `/ext/nfc/<name>.shd` | Shadow file: card state after a reader wrote to the emulated card |
| `/ext/nfc/.cache/<UID>.keys` | MIFARE Classic key cache (written on save) |
| `/ext/nfc/.cache/<UID>.mfpkeys` | MIFARE Plus key cache |
| `/ext/nfc/.mfkey32.log` | Reader nonces for MFKey32 |
| `/ext/nfc/.nested.log` | Card nonces from nested attacks |
| `/ext/nfc/assets/mf_classic_dict.nfc` / `mf_classic_dict_user.nfc` | MIFARE Classic system / user dictionary |
| `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | Per-card (CUID) candidate dictionary |
| `/ext/nfc/assets/mf_ultralight_c_dict.nfc` / `..._user.nfc` | Ultralight C 3DES keys |
| `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` / `..._user.nfc` | Ultralight AES keys |
| `/ext/nfc/assets/mf_plus_dict.nfc` / `..._user.nfc` | MIFARE Plus SL3 AES keys |
| `/ext/nfc/assets/aid.nfc`, `country_code.nfc`, `currency_code.nfc` | EMV lookup tables |

## Header (common to all cards)

```text
Filetype: Flipper NFC device
Version: 4
# Device type can be ISO14443-3A, ISO14443-3B, ISO14443-4A, NTAG/Ultralight, Mifare Classic, Mifare DESFire
Device type: ISO14443-4A
# UID is common for all formats
UID: 04 48 6A 32 33 58 80
-------------------------
(Device-specific data)
```

The header holds the device type and the UID; the protocol-specific data follows. File format versions:

1. Initial version, deprecated.
2. LSB ATQA (e.g. `4400` instead of `0044`).
3. MSB ATQA.
4. The "UID" device type replaced with `ISO14443-3A` (current; the firmware still loads files from version 2 on).

`Device type` values used by the Unleashed firmware: `ISO14443-3A`, `ISO14443-3B`, `ISO14443-4A`, `ISO14443-4B`,
`ISO15693-3`, `FeliCa`, `NTAG/Ultralight`, `Mifare Classic`, `Mifare Plus`, `Mifare DESFire`, `SLIX`, `ST25TB`,
`NTAG4xx`, `Type 4 Tag`, `EMV`, `Texkom`.

## ISO14443-3A

```text
Device type: ISO14443-3A
UID: 34 19 6D 41 14 56 E6
# ISO14443-3A specific data
ATQA: 00 44
SAK: 00
```

UID is 4 or 7 bytes, ATQA 2 bytes, SAK 1 byte.

## ISO14443-3B

```text
Device type: ISO14443-3B
UID: 30 1D B3 28
# ISO14443-3B specific data
Application data: 00 12 34 FF
Protocol info: 11 81 E1
```

UID 4 bytes, application data 4 bytes, protocol info 3 bytes.

## ISO14443-4A

```text
Device type: ISO14443-4A
UID: 04 48 6A 32 33 58 80
# ISO14443-3A specific data
ATQA: 03 44
SAK: 20
# ISO14443-4A specific data
ATS: 06 75 77 81 02 80
```

Adds the Answer to Select (**ATS**), at least 5 bytes.

## NTAG / Ultralight

```text
Device type: NTAG/Ultralight
UID: 04 85 90 54 12 98 23
# ISO14443-3A specific data
ATQA: 00 44
SAK: 00
# NTAG/Ultralight specific data
Data format version: 2
NTAG/Ultralight type: NTAG216
Signature: 1B 84 EB 70 BD 4C BD 1B 1D E4 98 0B 18 58 BD 7C 72 85 B4 E4 7B 38 8E 96 CF 88 6B EE A3 43 AD 90
Mifare version: 00 04 04 02 01 00 13 03
Counter 0: 0
Tearing 0: 00
Counter 1: 0
Tearing 1: 00
Counter 2: 0
Tearing 2: 00
Pages total: 231
Pages read: 231
Page 0: 04 85 92 9B
Page 1: 8A A0 61 81
Page 2: CA 48 0F 00
...
Page 226: 00 00 7F BD
Page 227: 04 00 00 E2
Page 228: 00 05 00 00
Page 229: 00 00 00 00
Page 230: 00 00 00 00
Failed authentication attempts: 0
```

- `NTAG/Ultralight type`: one of Mifare Ultralight, Mifare Ultralight 11, Mifare Ultralight 21, NTAG203, NTAG213,
  NTAG215, NTAG216, NTAG I2C 1K, NTAG I2C 2K, NTAG I2C Plus 1K, NTAG I2C Plus 2K (Unleashed also uses Mifare
  Ultralight C, Mifare Ultralight AES, NTAG210, NTAG212).
- `Signature`: the answer to `READ_SIG`; `Mifare version`: the answer to `GET_VERSION` (not the file version). See the
  NXP datasheet [MF0ULX1](https://www.nxp.com/docs/en/data-sheet/MF0ULX1.pdf), pages 31 and 21.
- Counters, tearing flags and pages are the card's raw internal state.
- **Ultralight AES** adds an `AES signature:` line (48 bytes). Its key pages (`Page 48`–`51`) are stored in
  tag-memory order, see [Ultralight AES](/nfc/ultralight-aes).
- Data format versions: 1 = type stored in `Device type`; 2 = current, type in its own field.

## MIFARE Classic

```text
Device type: Mifare Classic
UID: BA E2 7C 9D
# ISO14443-3A specific data
ATQA: 00 02
SAK: 18
# Mifare Classic specific data
Mifare Classic type: 4K
Data format version: 2
# Mifare Classic blocks, '??' means unknown data
Block 0: BA E2 7C 9D B9 18 02 00 46 44 53 37 30 56 30 31
Block 1: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Block 2: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Block 3: FF FF FF FF FF FF FF 07 80 69 FF FF FF FF FF FF
...
Block 255: FF FF FF FF FF FF FF 07 80 69 FF FF FF FF FF FF
```

- `Mifare Classic type`: `MINI`, `1K` or `4K`.
- Blocks are stored without grouping by sector. Unknown bytes are written as `??`: that's how a partial dump marks
  unread sectors, and how you can see which keys are missing.
- Sector trailers carry the found keys: `Key A | access bits | Key B`.
- Data format version 1 (old) used `Key A map` / `Key B map` bitmasks instead of `??`:

  ```text
  Data format version: 1
  # Key map is the bit mask indicating valid key in each sector
  Key A map: 000000000000FFFF
  Key B map: 000000000000FFFF
  ```

## MIFARE DESFire

```text
Device type: Mifare DESFire
UID: 04 2F 19 0A CD 66 80
# ISO14443-3A specific data
ATQA: 03 44
SAK: 20
# ISO14443-4A specific data
ATS: 06 75 77 81 02 80
# Mifare DESFire specific data
PICC Version: 04 01 01 12 00 1A 05 04 01 01 02 01 1A 05 04 2F 19 0A CD 66 80 CE ED D4 51 80 31 19
PICC Free Memory: 7520
PICC Change Key ID: 00
PICC Config Changeable: true
PICC Free Create Delete: true
PICC Free Directory List: true
PICC Key Changeable: true
PICC Max Keys: 01
PICC Key 0 Version: 00
Application Count: 1
Application IDs: 56 34 12
Application 563412 Change Key ID: 00
Application 563412 Config Changeable: true
Application 563412 Free Create Delete: true
Application 563412 Free Directory List: true
Application 563412 Key Changeable: true
Application 563412 Max Keys: 0E
Application 563412 Key 0 Version: 00
...
Application 563412 Key 13 Version: 00
Application 563412 File IDs: 01
Application 563412 File 1 Type: 00
Application 563412 File 1 Communication Settings: 00
Application 563412 File 1 Access Rights: EE EE
Application 563412 File 1 Size: 256
Application 563412 File 1: 13 37 00 00 ... 00
```

Data is stored per application and per file. The example card was created with these Proxmark3 commands:

```text
hf mfdes createapp --aid 123456 --fid 2345 --dfname astra
hf mfdes createfile --aid 123456 --fid 01 --isofid 0001 --size 000100
hf mfdes write --aid 123456 --fid 01 -d 1337
```

## Other types (Unleashed)

Fields written by the firmware for types not covered by the upstream document:

- **MIFARE Plus**: `Security Level`, `Card Type`, `Memory Size`; SL3 dumps add a `Data format version`, blocks,
  keys and `Signature`.
- **SLIX**: `Capabilities`, `Password Read`/`Write`/`Privacy`/`Destroy`/`EAS`, `Signature`, `Privacy Mode`,
  `Protection Pointer`, `Protection Condition`, `Lock EAS`, `Lock PPL` (on top of the ISO15693-3 fields `DSFID`, `AFI`,
  `IC Reference`, `Block Count`, `Block Size`, `Data Content`, `Security Status`, `Lock DSFID`, `Lock AFI`).
- **Texkom**: `Texkom Type` and the raw 8-byte `Frame` (`FF FF <type> <uid 4 bytes> <crc>`).

## Dictionaries

### MIFARE Classic dictionary

```text
# Key dictionary from https://github.com/ikarus23/MifareClassicTool.git

# More well known keys!
# Standard keys
FFFFFFFFFFFF
A0A1A2A3A4A5
D3F7D3F7D3F7
000000000000

# Keys from mfoc
B0B1B2B3B4B5
4D3A99C351DD
1A982C7E459A
AABBCCDDEEFF
...
```

One key per line as 12 hex characters. Lines starting with `#` and empty lines are ignored. The same rules apply to
the user dictionary `mf_classic_dict_user.nfc`.

### MIFARE Ultralight C dictionary

```text
# Hexadecimal-Reversed Sample Key
12E4143455F495649454D4B414542524
# Byte-Reversed Sample Key (!NACUOYFIEMKAERB)
214E4143554F594649454D4B41455242
# Sample Key (BREAKMEIFYOUCAN!)
425245414B4D454946594F5543414E21
# Semnox Key (IEMKAERB!NACUOY )
49454D4B41455242214E4143554F5900
# Modified Semnox Key (IEMKAERB!NACUOYF)
49454D4B41455242214E4143554F5946
...
```

One 16-byte key per line (32 hex characters), `#` comments. The Ultralight AES and MIFARE Plus dictionaries use the
same format (32 hex characters = AES-128 key).

## EMV resources

```text
Filetype: Flipper EMV resources
Version: 1
# EMV currency code: currency name
0997: USN
0994: XSU
0990: CLF
0986: BRL
0985: PLN
0984: BOV
...
```

A list of EMV currency codes, country codes or AIDs with their names: a hex value and a name separated by a colon and
a space.

## Related

[Reading cards](/nfc/read) · [MIFARE Classic](/nfc/mifare-classic) · [Bank cards (EMV)](/nfc/emv)
