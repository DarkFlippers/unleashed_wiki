---
title: Формат файлов NFC
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc]
sources: [unleashed-docs, unleashed-src]
---
# Формат файлов NFC

Сохранённые метки — текстовые файлы **Flipper Format** с расширением `.nfc` в `/ext/nfc/`. Их можно открыть и
поправить в любом текстовом редакторе, qFlipper или qUnleashed. Связанные файлы:

| Путь | Содержимое |
|---|---|
| `/ext/nfc/<name>.nfc` | Сохранённая метка |
| `/ext/nfc/<name>.shd` | Shadow-файл: состояние метки после записи считывателем в эмулируемую метку |
| `/ext/nfc/.cache/<UID>.keys` | Кеш ключей MIFARE Classic (пишется при сохранении) |
| `/ext/nfc/.cache/<UID>.mfpkeys` | Кеш ключей MIFARE Plus |
| `/ext/nfc/.mfkey32.log` | Нонсы считывателя для MFKey32 |
| `/ext/nfc/.nested.log` | Нонсы метки из nested-атак |
| `/ext/nfc/assets/mf_classic_dict.nfc` / `mf_classic_dict_user.nfc` | Системный / пользовательский словарь MIFARE Classic |
| `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | Словарь кандидатов для одной метки (CUID) |
| `/ext/nfc/assets/mf_ultralight_c_dict.nfc` / `..._user.nfc` | Ключи 3DES Ultralight C |
| `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` / `..._user.nfc` | Ключи Ultralight AES |
| `/ext/nfc/assets/mf_plus_dict.nfc` / `..._user.nfc` | AES-ключи MIFARE Plus SL3 |
| `/ext/nfc/assets/aid.nfc`, `country_code.nfc`, `currency_code.nfc` | Справочники EMV |

## Заголовок (общий для всех меток)

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

В заголовке — тип устройства и UID, дальше идут данные протокола. Версии формата файла:

1. Первая версия, устарела.
2. ATQA в порядке LSB (например `4400` вместо `0044`).
3. ATQA в порядке MSB.
4. Тип устройства «UID» заменён на `ISO14443-3A` (текущая; прошивка по-прежнему загружает файлы начиная с версии 2).

Значения `Device type`, которые использует прошивка Unleashed: `ISO14443-3A`, `ISO14443-3B`, `ISO14443-4A`, `ISO14443-4B`,
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

UID — 4 или 7 байт, ATQA — 2 байта, SAK — 1 байт.

## ISO14443-3B

```text
Device type: ISO14443-3B
UID: 30 1D B3 28
# ISO14443-3B specific data
Application data: 00 12 34 FF
Protocol info: 11 81 E1
```

UID — 4 байта, application data — 4 байта, protocol info — 3 байта.

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

Добавляется Answer to Select (**ATS**), не меньше 5 байт.

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

- `NTAG/Ultralight type` — одно из: Mifare Ultralight, Mifare Ultralight 11, Mifare Ultralight 21, NTAG203, NTAG213,
  NTAG215, NTAG216, NTAG I2C 1K, NTAG I2C 2K, NTAG I2C Plus 1K, NTAG I2C Plus 2K (в Unleashed также Mifare
  Ultralight C, Mifare Ultralight AES, NTAG210, NTAG212).
- `Signature` — ответ на `READ_SIG`; `Mifare version` — ответ на `GET_VERSION` (это не версия файла). См. даташит NXP
  [MF0ULX1](https://www.nxp.com/docs/en/data-sheet/MF0ULX1.pdf), страницы 31 и 21.
- Счётчики, флаги tearing и страницы — сырое внутреннее состояние метки.
- **Ultralight AES** добавляет строку `AES signature:` (48 байт). Страницы ключа (`Page 48`–`51`) хранятся в порядке
  памяти метки, см. [Ultralight AES](/ru/nfc/ultralight-aes).
- Версии формата данных: 1 — тип хранится в `Device type`; 2 — текущая, тип в отдельном поле.

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

- `Mifare Classic type` — `MINI`, `1K` или `4K`.
- Блоки хранятся без группировки по секторам. Неизвестные байты записываются как `??`: так частичный дамп отмечает
  непрочитанные сектора, и по ним видно, каких ключей не хватает.
- В трейлерах секторов — найденные ключи: `Key A | биты доступа | Key B`.
- Версия формата данных 1 (старая) вместо `??` использовала битовые маски `Key A map` / `Key B map`:

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

Данные хранятся по приложениям и файлам. Метка из примера создана такими командами Proxmark3:

```text
hf mfdes createapp --aid 123456 --fid 2345 --dfname astra
hf mfdes createfile --aid 123456 --fid 01 --isofid 0001 --size 000100
hf mfdes write --aid 123456 --fid 01 -d 1337
```

## Другие типы (Unleashed)

Поля, которые прошивка пишет для типов, не описанных в исходном документе:

- **MIFARE Plus**: `Security Level`, `Card Type`, `Memory Size`; дампы SL3 добавляют `Data format version`, блоки,
  ключи и `Signature`.
- **SLIX**: `Capabilities`, `Password Read`/`Write`/`Privacy`/`Destroy`/`EAS`, `Signature`, `Privacy Mode`,
  `Protection Pointer`, `Protection Condition`, `Lock EAS`, `Lock PPL` (в дополнение к полям ISO15693-3 `DSFID`, `AFI`,
  `IC Reference`, `Block Count`, `Block Size`, `Data Content`, `Security Status`, `Lock DSFID`, `Lock AFI`).
- **Texkom**: `Texkom Type` и сырой 8-байтный `Frame` (`FF FF <тип> <uid 4 байта> <crc>`).

## Словари

### Словарь MIFARE Classic

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

По одному ключу в строке, 12 hex-символов. Строки, начинающиеся с `#`, и пустые строки игнорируются. Те же правила
для пользовательского словаря `mf_classic_dict_user.nfc`.

### Словарь MIFARE Ultralight C

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

По одному 16-байтному ключу в строке (32 hex-символа), `#` — комментарий. Словари Ultralight AES и MIFARE Plus — в
том же формате (32 hex-символа = ключ AES-128).

## Справочники EMV {#emv-resources}

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

Список кодов валют, кодов стран или AID EMV с названиями: hex-значение и название через двоеточие и пробел.

## См. также

[Чтение меток](/ru/nfc/read) · [MIFARE Classic](/ru/nfc/mifare-classic) · [Банковские карты (EMV)](/ru/nfc/emv)
