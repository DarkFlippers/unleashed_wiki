---
title: Formato dei file NFC
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc]
sources: [unleashed-docs, unleashed-src]
---
# Formato dei file NFC

Le carte salvate sono file **Flipper Format** in testo semplice con estensione `.nfc` in `/ext/nfc/`. Puoi aprirli e
modificarli in qualsiasi editor di testo, in qFlipper o in qUnleashed. File correlati:

| Percorso | Contenuto |
|---|---|
| `/ext/nfc/<name>.nfc` | Carta salvata |
| `/ext/nfc/<name>.shd` | File shadow: stato della carta dopo che un lettore ha scritto sulla carta emulata |
| `/ext/nfc/.cache/<UID>.keys` | Cache delle chiavi MIFARE Classic (scritta al salvataggio) |
| `/ext/nfc/.cache/<UID>.mfpkeys` | Cache delle chiavi MIFARE Plus |
| `/ext/nfc/.mfkey32.log` | Nonce del lettore per MFKey32 |
| `/ext/nfc/.nested.log` | Nonce della carta dagli attacchi nested |
| `/ext/nfc/assets/mf_classic_dict.nfc` / `mf_classic_dict_user.nfc` | Dizionario MIFARE Classic di sistema / utente |
| `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | Dizionario di candidate per singola carta (CUID) |
| `/ext/nfc/assets/mf_ultralight_c_dict.nfc` / `..._user.nfc` | Chiavi 3DES Ultralight C |
| `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` / `..._user.nfc` | Chiavi AES Ultralight |
| `/ext/nfc/assets/mf_plus_dict.nfc` / `..._user.nfc` | Chiavi AES MIFARE Plus SL3 |
| `/ext/nfc/assets/aid.nfc`, `country_code.nfc`, `currency_code.nfc` | Tabelle di consultazione EMV |

## Intestazione (comune a tutte le carte)

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

L'intestazione contiene il tipo di dispositivo e l'UID; seguono i dati specifici del protocollo. Versioni del formato
di file:

1. Versione iniziale, deprecata.
2. ATQA in LSB (per esempio `4400` invece di `0044`).
3. ATQA in MSB.
4. Il tipo di dispositivo "UID" sostituito da `ISO14443-3A` (attuale; il firmware carica comunque i file dalla
   versione 2 in poi).

Valori di `Device type` usati dal firmware Unleashed: `ISO14443-3A`, `ISO14443-3B`, `ISO14443-4A`, `ISO14443-4B`,
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

L'UID è di 4 o 7 byte, l'ATQA di 2 byte, il SAK di 1 byte.

## ISO14443-3B

```text
Device type: ISO14443-3B
UID: 30 1D B3 28
# ISO14443-3B specific data
Application data: 00 12 34 FF
Protocol info: 11 81 E1
```

UID 4 byte, dati applicativi 4 byte, info di protocollo 3 byte.

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

Aggiunge l'Answer to Select (**ATS**), almeno 5 byte.

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

- `NTAG/Ultralight type`: uno tra Mifare Ultralight, Mifare Ultralight 11, Mifare Ultralight 21, NTAG203, NTAG213,
  NTAG215, NTAG216, NTAG I2C 1K, NTAG I2C 2K, NTAG I2C Plus 1K, NTAG I2C Plus 2K (Unleashed usa anche Mifare
  Ultralight C, Mifare Ultralight AES, NTAG210, NTAG212).
- `Signature`: la risposta a `READ_SIG`; `Mifare version`: la risposta a `GET_VERSION` (non la versione del file). Vedi
  il datasheet NXP [MF0ULX1](https://www.nxp.com/docs/en/data-sheet/MF0ULX1.pdf), pagine 31 e 21.
- Contatori, flag di tearing e pagine sono lo stato interno grezzo della carta.
- **Ultralight AES** aggiunge una riga `AES signature:` (48 byte). Le sue pagine della chiave (`Page 48`–`51`) sono
  memorizzate nell'ordine della memoria del tag, vedi [Ultralight AES](/it/nfc/ultralight-aes).
- Versioni del formato dei dati: 1 = tipo memorizzato in `Device type`; 2 = attuale, tipo in un campo proprio.

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

- `Mifare Classic type`: `MINI`, `1K` oppure `4K`.
- I blocchi sono memorizzati senza raggruppamento per settore. I byte sconosciuti sono scritti come `??`: è così che
  un dump parziale segnala i settori non letti, e così puoi vedere quali chiavi mancano.
- I sector trailer contengono le chiavi trovate: `Key A | bit di accesso | Key B`.
- La versione 1 del formato dei dati (vecchia) usava le bitmask `Key A map` / `Key B map` invece di `??`:

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

I dati sono memorizzati per applicazione e per file. La carta dell'esempio è stata creata con questi comandi
Proxmark3:

```text
hf mfdes createapp --aid 123456 --fid 2345 --dfname astra
hf mfdes createfile --aid 123456 --fid 01 --isofid 0001 --size 000100
hf mfdes write --aid 123456 --fid 01 -d 1337
```

## Altri tipi (Unleashed)

Campi scritti dal firmware per i tipi non trattati nel documento upstream:

- **MIFARE Plus**: `Security Level`, `Card Type`, `Memory Size`; i dump SL3 aggiungono un `Data format version`, i
  blocchi, le chiavi e la `Signature`.
- **SLIX**: `Capabilities`, `Password Read`/`Write`/`Privacy`/`Destroy`/`EAS`, `Signature`, `Privacy Mode`,
  `Protection Pointer`, `Protection Condition`, `Lock EAS`, `Lock PPL` (in aggiunta ai campi ISO15693-3 `DSFID`,
  `AFI`, `IC Reference`, `Block Count`, `Block Size`, `Data Content`, `Security Status`, `Lock DSFID`, `Lock AFI`).
- **Texkom**: `Texkom Type` e il `Frame` grezzo da 8 byte (`FF FF <type> <uid 4 bytes> <crc>`).

## Dizionari

### Dizionario MIFARE Classic

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

Una chiave per riga, come 12 caratteri esadecimali. Le righe che iniziano con `#` e le righe vuote vengono ignorate.
Le stesse regole valgono per il dizionario utente `mf_classic_dict_user.nfc`.

### Dizionario MIFARE Ultralight C

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

Una chiave da 16 byte per riga (32 caratteri esadecimali), commenti con `#`. I dizionari Ultralight AES e MIFARE Plus
usano lo stesso formato (32 caratteri esadecimali = chiave AES-128).

## Risorse EMV {#emv-resources}

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

Un elenco di codici valuta, codici paese o AID EMV con i rispettivi nomi: un valore esadecimale e un nome separati da
due punti e uno spazio.

## Pagine correlate

[Leggere le carte](/it/nfc/read) · [MIFARE Classic](/it/nfc/mifare-classic) · [Carte bancarie (EMV)](/it/nfc/emv)
