---
title: NFC-Dateiformat
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc]
sources: [unleashed-docs, unleashed-src]
---
# NFC-Dateiformat

Gespeicherte Karten sind reine Textdateien im **Flipper Format** mit der Endung `.nfc` in `/ext/nfc/`. Du kannst sie
in jedem Texteditor, in qFlipper oder in qUnleashed öffnen und bearbeiten. Verwandte Dateien:

| Pfad | Inhalt |
|---|---|
| `/ext/nfc/<name>.nfc` | Gespeicherte Karte |
| `/ext/nfc/<name>.shd` | Schattendatei: Kartenzustand, nachdem ein Lesegerät auf die emulierte Karte geschrieben hat |
| `/ext/nfc/.cache/<UID>.keys` | Schlüsselcache für MIFARE Classic (beim Speichern geschrieben) |
| `/ext/nfc/.cache/<UID>.mfpkeys` | Schlüsselcache für MIFARE Plus |
| `/ext/nfc/.mfkey32.log` | Lesegerät-Nonces für MFKey32 |
| `/ext/nfc/.nested.log` | Karten-Nonces aus den Nested-Angriffen |
| `/ext/nfc/assets/mf_classic_dict.nfc` / `mf_classic_dict_user.nfc` | MIFARE-Classic-System- / -Benutzerwörterbuch |
| `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | Kandidatenwörterbuch pro Karte (CUID) |
| `/ext/nfc/assets/mf_ultralight_c_dict.nfc` / `..._user.nfc` | 3DES-Schlüssel für Ultralight C |
| `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` / `..._user.nfc` | AES-Schlüssel für Ultralight AES |
| `/ext/nfc/assets/mf_plus_dict.nfc` / `..._user.nfc` | AES-Schlüssel für MIFARE Plus SL3 |
| `/ext/nfc/assets/aid.nfc`, `country_code.nfc`, `currency_code.nfc` | EMV-Nachschlagetabellen |

## Kopf (für alle Karten gleich)

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

Der Kopf enthält den Gerätetyp und die UID; danach folgen die protokollspezifischen Daten. Versionen des
Dateiformats:

1. Erste Version, veraltet.
2. ATQA als LSB (z. B. `4400` statt `0044`).
3. ATQA als MSB.
4. Der Gerätetyp „UID" durch `ISO14443-3A` ersetzt (aktuell; die Firmware lädt noch Dateien ab Version 2).

`Device type`-Werte, die die Unleashed-Firmware nutzt: `ISO14443-3A`, `ISO14443-3B`, `ISO14443-4A`, `ISO14443-4B`,
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

Die UID ist 4 oder 7 Byte lang, ATQA 2 Byte, SAK 1 Byte.

## ISO14443-3B

```text
Device type: ISO14443-3B
UID: 30 1D B3 28
# ISO14443-3B specific data
Application data: 00 12 34 FF
Protocol info: 11 81 E1
```

UID 4 Byte, Application Data 4 Byte, Protocol Info 3 Byte.

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

Ergänzt das Answer to Select (**ATS**), mindestens 5 Byte.

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

- `NTAG/Ultralight type`: einer von Mifare Ultralight, Mifare Ultralight 11, Mifare Ultralight 21, NTAG203, NTAG213,
  NTAG215, NTAG216, NTAG I2C 1K, NTAG I2C 2K, NTAG I2C Plus 1K, NTAG I2C Plus 2K (Unleashed nutzt zusätzlich Mifare
  Ultralight C, Mifare Ultralight AES, NTAG210, NTAG212).
- `Signature`: die Antwort auf `READ_SIG`; `Mifare version`: die Antwort auf `GET_VERSION` (nicht die Dateiversion).
  Siehe das NXP-Datenblatt [MF0ULX1](https://www.nxp.com/docs/en/data-sheet/MF0ULX1.pdf), Seite 31 und 21.
- Zähler, Tearing-Flags und Pages sind der rohe interne Zustand der Karte.
- **Ultralight AES** ergänzt eine Zeile `AES signature:` (48 Byte). Seine Schlüssel-Pages (`Page 48`–`51`) werden in
  der Reihenfolge des Tag-Speichers abgelegt, siehe [Ultralight AES](/de/nfc/ultralight-aes).
- Datenformatversionen: 1 = Typ in `Device type` gespeichert; 2 = aktuell, Typ in einem eigenen Feld.

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

- `Mifare Classic type`: `MINI`, `1K` oder `4K`.
- Blöcke werden ohne Gruppierung nach Sektoren gespeichert. Unbekannte Bytes werden als `??` geschrieben: so
  markiert ein Teildump ungelesene Sektoren, und so siehst du, welche Schlüssel fehlen.
- Die Sector Trailer enthalten die gefundenen Schlüssel: `Key A | Access Bits | Key B`.
- Datenformatversion 1 (alt) nutzte die Bitmasken `Key A map` / `Key B map` statt `??`:

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

Die Daten werden pro Anwendung und pro Datei gespeichert. Die Beispielkarte wurde mit diesen Proxmark3-Befehlen
erzeugt:

```text
hf mfdes createapp --aid 123456 --fid 2345 --dfname astra
hf mfdes createfile --aid 123456 --fid 01 --isofid 0001 --size 000100
hf mfdes write --aid 123456 --fid 01 -d 1337
```

## Weitere Typen (Unleashed)

Felder, die die Firmware für Typen schreibt, die das Upstream-Dokument nicht abdeckt:

- **MIFARE Plus**: `Security Level`, `Card Type`, `Memory Size`; SL3-Dumps ergänzen eine `Data format version`,
  Blöcke, Schlüssel und `Signature`.
- **SLIX**: `Capabilities`, `Password Read`/`Write`/`Privacy`/`Destroy`/`EAS`, `Signature`, `Privacy Mode`,
  `Protection Pointer`, `Protection Condition`, `Lock EAS`, `Lock PPL` (zusätzlich zu den ISO15693-3-Feldern `DSFID`,
  `AFI`, `IC Reference`, `Block Count`, `Block Size`, `Data Content`, `Security Status`, `Lock DSFID`, `Lock AFI`).
- **Texkom**: `Texkom Type` und der rohe 8 Byte lange `Frame` (`FF FF <type> <uid 4 bytes> <crc>`).

## Wörterbücher

### MIFARE-Classic-Wörterbuch

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

Ein Schlüssel pro Zeile als 12 Hex-Zeichen. Zeilen, die mit `#` beginnen, und leere Zeilen werden ignoriert. Für das
Benutzerwörterbuch `mf_classic_dict_user.nfc` gelten die gleichen Regeln.

### MIFARE-Ultralight-C-Wörterbuch

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

Ein 16 Byte langer Schlüssel pro Zeile (32 Hex-Zeichen), `#` für Kommentare. Die Wörterbücher für Ultralight AES und
MIFARE Plus nutzen dasselbe Format (32 Hex-Zeichen = AES-128-Schlüssel).

## EMV-Ressourcen {#emv-resources}

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

Eine Liste von EMV-Währungscodes, Ländercodes oder AIDs mit ihren Namen: ein Hex-Wert und ein Name, getrennt durch
einen Doppelpunkt und ein Leerzeichen.

## Verwandte Seiten

[Karten lesen](/de/nfc/read) · [MIFARE Classic](/de/nfc/mifare-classic) · [Bankkarten (EMV)](/de/nfc/emv)
