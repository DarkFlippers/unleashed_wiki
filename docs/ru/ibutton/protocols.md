---
title: Поддерживаемые протоколы
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks, https://docs.flipper.net/zero/ibutton/read, https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Поддерживаемые протоколы iButton

Составлено по `lib/ibutton/protocols/` прошивки Unleashed. Прошивка делит протоколы на группы **Dallas** (1-Wire) и
**misc** (Cyfral, Metakom).

| Протокол (в файле) | Пункт меню | Family code | Память | Эмуляция | Write ID на | Full Write on Same Type |
|---|---|---|---|---|---|---|
| `DS1990` | Dallas DS1990 | `01` | — | ✓ | RW1990.1, RW1990.2, TM2004, TM01x | — |
| `DS1420` | Dallas DS1420 | `81` | — | ✓ | RW1990.1, RW1990.2, TM2004 | — |
| `DS1992` | Dallas DS1992 | `08` | 128 Б SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1996` | Dallas DS1996 | `0C` | 8192 Б SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1971` | Dallas DS1971 | `14` | 32 Б EEPROM (`Eeprom Data`) | ✓ | TM2004 | ✓ |
| `(non-specific)` | Dallas (non-specific) | любой | — (только ROM) | ✓ | TM2004 | — |
| `Cyfral` | Cyfral | — | 2-байтный код | ✓ | TM01x | — |
| `Metakom` | Metakom | — | 4-байтный код | ✓ | TM01x | — |

## Dallas 1-Wire

«Touch memory» от Dallas Semiconductor (сейчас Analog Devices). У каждого устройства 8-байтный ROM: family code,
48-битный серийный номер и CRC-8. Флиппер проверяет CRC и определяет тип по family code.

- **DS1990 (DS1990A)** — классический ключ «только ID», который используют большинство домофонов.
- **DS1420** — полностью совместим с DS1990, отличается только family code (`81` вместо `01`).
- **DS1992 / DS1996** — ключи с памятью SRAM; DS1971 — с EEPROM. Флиппер читает память, может её показать
  (**Data Info**), эмулировать и скопировать на ключ того же типа.
- **Dallas (non-specific)** — «всё остальное» 1-Wire: читается только ROM, ничего не проверяется. Удобно и для ключа с
  намеренно неверным family code или CRC.

## Cyfral

Протокол домофонных ключей, распространённый в России и СНГ; это не 1-Wire. Код хранится как 2 байта. Эмулируется и
пишется на болванку TM01x.

## Metakom

Ещё один протокол домофонов СНГ. Код — 4 байта, каждый байт несёт бит чётности: ключ с неверной чётностью считается
недействительным и не пишется. Эмулируется и пишется на болванку TM01x.

## Болванки

| Болванка | Принимает | Как пишется |
|---|---|---|
| **RW1990.1** | ROM Dallas (8 байт) | Разблокировка, запись (биты инвертированы), блокировка |
| **RW1990.2** | ROM Dallas (8 байт) | Разблокировка, запись, блокировка |
| **TM2004** | ROM Dallas (8 байт) | Запись с адреса 0 с проверкой каждого байта обратным чтением |
| **TM01x** | ROM Dallas, Cyfral, Metakom | Cyfral/Metakom пишутся 36-битным кадром (4-битный префикс + 32 бита кода), проверяются и **финализируются** (необратимо). ID Dallas не финализируется |

Как пользоваться — в разделе [Запись](/ru/ibutton/write).

::: tip Unleashed
В официальной документации нет DS1420, настройки Write Blanks и записи Cyfral/Metakom на TM01x.
:::

## Связанные страницы

- [Чтение](/ru/ibutton/read) · [Запись](/ru/ibutton/write) · [Формат файла](/ru/ibutton/file-format)
