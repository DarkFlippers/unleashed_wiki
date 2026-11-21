---
title: Formato de los ficheros NFC
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc]
sources: [unleashed-docs, unleashed-src]
---
# Formato de los ficheros NFC

Las tarjetas guardadas son ficheros de texto en **Flipper Format** con la extensión `.nfc`, dentro de `/ext/nfc/`.
Se pueden abrir y editar en cualquier editor de texto, en qFlipper o en qUnleashed. Ficheros relacionados:

| Ruta | Contenido |
|---|---|
| `/ext/nfc/<nombre>.nfc` | Tarjeta guardada |
| `/ext/nfc/<nombre>.shd` | Fichero de sombra: estado de la tarjeta después de que un lector haya escrito en la tarjeta emulada |
| `/ext/nfc/.cache/<UID>.keys` | Caché de claves de MIFARE Classic (se escribe al guardar) |
| `/ext/nfc/.cache/<UID>.mfpkeys` | Caché de claves de MIFARE Plus |
| `/ext/nfc/.mfkey32.log` | Nonces de lector para MFKey32 |
| `/ext/nfc/.nested.log` | Nonces de tarjeta de los ataques anidados |
| `/ext/nfc/assets/mf_classic_dict.nfc` / `mf_classic_dict_user.nfc` | Diccionario de sistema y de usuario de MIFARE Classic |
| `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | Diccionario de candidatas por tarjeta (CUID) |
| `/ext/nfc/assets/mf_ultralight_c_dict.nfc` / `..._user.nfc` | Claves 3DES de Ultralight C |
| `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` / `..._user.nfc` | Claves de Ultralight AES |
| `/ext/nfc/assets/mf_plus_dict.nfc` / `..._user.nfc` | Claves AES de MIFARE Plus SL3 |
| `/ext/nfc/assets/aid.nfc`, `country_code.nfc`, `currency_code.nfc` | Tablas de consulta de EMV |

## Cabecera (común a todas las tarjetas)

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

La cabecera contiene el tipo de dispositivo y el UID; después vienen los datos específicos del protocolo. Versiones
del formato de fichero:

1. Versión inicial, obsoleta.
2. ATQA en LSB (por ejemplo, `4400` en lugar de `0044`).
3. ATQA en MSB.
4. El tipo de dispositivo «UID» sustituido por `ISO14443-3A` (la actual; el firmware sigue cargando ficheros desde
   la versión 2 en adelante).

Valores de `Device type` que usa el firmware de Unleashed: `ISO14443-3A`, `ISO14443-3B`, `ISO14443-4A`,
`ISO14443-4B`, `ISO15693-3`, `FeliCa`, `NTAG/Ultralight`, `Mifare Classic`, `Mifare Plus`, `Mifare DESFire`,
`SLIX`, `ST25TB`, `NTAG4xx`, `Type 4 Tag`, `EMV`, `Texkom`.

## ISO14443-3A

```text
Device type: ISO14443-3A
UID: 34 19 6D 41 14 56 E6
# ISO14443-3A specific data
ATQA: 00 44
SAK: 00
```

El UID es de 4 o 7 bytes, el ATQA de 2 bytes y el SAK de 1 byte.

## ISO14443-3B

```text
Device type: ISO14443-3B
UID: 30 1D B3 28
# ISO14443-3B specific data
Application data: 00 12 34 FF
Protocol info: 11 81 E1
```

UID de 4 bytes, datos de aplicación de 4 bytes e información de protocolo de 3 bytes.

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

Añade el Answer to Select (**ATS**), de 5 bytes como mínimo.

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

- `NTAG/Ultralight type`: uno de Mifare Ultralight, Mifare Ultralight 11, Mifare Ultralight 21, NTAG203, NTAG213,
  NTAG215, NTAG216, NTAG I2C 1K, NTAG I2C 2K, NTAG I2C Plus 1K, NTAG I2C Plus 2K (Unleashed usa además Mifare
  Ultralight C, Mifare Ultralight AES, NTAG210 y NTAG212).
- `Signature`: la respuesta a `READ_SIG`; `Mifare version`: la respuesta a `GET_VERSION` (no la versión del
  fichero). Véase la hoja de datos de NXP [MF0ULX1](https://www.nxp.com/docs/en/data-sheet/MF0ULX1.pdf), páginas 31
  y 21.
- Los contadores, los indicadores de tearing y las páginas son el estado interno en bruto de la tarjeta.
- **Ultralight AES** añade una línea `AES signature:` (48 bytes). Sus páginas de clave (`Page 48`–`51`) se guardan en
  el orden de la memoria de la etiqueta; véase [Ultralight AES](/es/nfc/ultralight-aes).
- Versiones del formato de datos: 1 = el tipo se guarda en `Device type`; 2 = la actual, con el tipo en su propio
  campo.

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

- `Mifare Classic type`: `MINI`, `1K` o `4K`.
- Los bloques se guardan sin agruparlos por sector. Los bytes desconocidos se escriben como `??`: así marca un
  volcado parcial los sectores no leídos, y así puedes ver qué claves faltan.
- Los sector trailers contienen las claves encontradas: `Clave A | bits de acceso | Clave B`.
- La versión 1 del formato de datos (antigua) usaba máscaras de bits `Key A map` / `Key B map` en lugar de `??`:

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

Los datos se guardan por aplicación y por fichero. La tarjeta del ejemplo se creó con estos comandos de Proxmark3:

```text
hf mfdes createapp --aid 123456 --fid 2345 --dfname astra
hf mfdes createfile --aid 123456 --fid 01 --isofid 0001 --size 000100
hf mfdes write --aid 123456 --fid 01 -d 1337
```

## Otros tipos (Unleashed)

Campos que escribe el firmware para los tipos que no cubre el documento original:

- **MIFARE Plus**: `Security Level`, `Card Type`, `Memory Size`; los volcados de SL3 añaden un
  `Data format version`, los bloques, las claves y `Signature`.
- **SLIX**: `Capabilities`, `Password Read`/`Write`/`Privacy`/`Destroy`/`EAS`, `Signature`, `Privacy Mode`,
  `Protection Pointer`, `Protection Condition`, `Lock EAS`, `Lock PPL` (además de los campos de ISO15693-3
  `DSFID`, `AFI`, `IC Reference`, `Block Count`, `Block Size`, `Data Content`, `Security Status`, `Lock DSFID`,
  `Lock AFI`).
- **Texkom**: `Texkom Type` y la trama (`Frame`) en bruto de 8 bytes (`FF FF <tipo> <uid 4 bytes> <crc>`).

## Diccionarios

### Diccionario de MIFARE Classic

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

Una clave por línea, con 12 caracteres hexadecimales. Las líneas que empiezan por `#` y las líneas vacías se
ignoran. Las mismas reglas se aplican al diccionario de usuario `mf_classic_dict_user.nfc`.

### Diccionario de MIFARE Ultralight C

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

Una clave de 16 bytes por línea (32 caracteres hexadecimales), con comentarios `#`. Los diccionarios de Ultralight
AES y de MIFARE Plus usan el mismo formato (32 caracteres hexadecimales = clave AES-128).

## Recursos EMV {#emv-resources}

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

Una lista de códigos de moneda, de códigos de país o de AID de EMV con sus nombres: un valor hexadecimal y un nombre
separados por dos puntos y un espacio.

## Relacionado

[Leer tarjetas](/es/nfc/read) · [MIFARE Classic](/es/nfc/mifare-classic) · [Tarjetas bancarias (EMV)](/es/nfc/emv)
