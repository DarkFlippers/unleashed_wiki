---
title: File format
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-docs, unleashed-src]
---
# iButton key file format (`.ibtn`)

Saved keys are stored in `/ext/ibutton/` with the extension `.ibtn`. One file holds one key with all data its
protocol needs.

## Example

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1992
Rom Data: 08 DE AD BE EF FA CE 4E
Sram Data: 4E 65 76 65 72 47 6F 6E 6E 61 47 69 76 65 59 6F 75 55 70 4E 65 76 65 72 47 6F 6E 6E 61 4C 65 74 59 6F 75 44 6F 77 6E 4E 65 76 65 72 47 6F 6E 6E 61 52 75 6E 41 72 6F 75 6E 64 41 6E 64 44 65 73 65 72 74 59 6F 75 4E 65 76 65 72 47 6F 6E 6E 61 4D 61 6B 65 59 6F 75 43 72 79 4E 65 76 65 72 47 6F 6E 6E 61 53 61 79 47 6F 6F 64 62 79 65 4E 65 76 65 72 47 6F 6E 6E 61 54 65 6C 6C 41 4C 69 65
```

A DS1990 key (the bytes are an example; a real ROM ends with a valid CRC):

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1990
Rom Data: 01 23 45 67 89 AB CD EF
```

A Cyfral key:

```text
Filetype: Flipper iButton key
Version: 2
Protocol: Cyfral
Data: A1 B2
```

## Version 2 (current)

Fields after `Protocol` depend on the protocol.

| Field | Type | Description |
|---|---|---|
| `Protocol` | string | `DS1990`, `DS1992`, `DS1996`, `DS1971`, `DS1420`, `(non-specific)`, `Cyfral`, `Metakom` |
| `Rom Data` | hex | 8-byte ROM (Dallas protocols only) |
| `Sram Data` | hex | SRAM contents (DS1992: 128 bytes, DS1996: 8192 bytes) |
| `Eeprom Data` | hex | EEPROM contents (DS1971: 32 bytes) |
| `Data` | hex | Key code (Cyfral: 2 bytes, Metakom: 4 bytes) |

Notes:
- **(non-specific)** is the catch-all for unknown 1-Wire devices (menu label *Dallas (non-specific)*). It holds only
  the ROM and performs no checks — use it for keys with a deliberately invalid family code or CRC. The firmware saves it
  as `Protocol: (non-specific)`; the name `DSGeneric` used by the official doc and older files is still accepted.
- **DS1420** is fully compatible with DS1990; only the family code differs (`0x81` vs `0x01`).
- New protocols don't require a format version bump — each protocol defines its own fields.

## Version 1 (deprecated)

```text
Filetype: Flipper iButton key
Version: 1
Key type: Dallas
Data: 01 23 45 67 89 AB CD EF
```

| Field | Type | Description |
|---|---|---|
| `Key type` | string | `Cyfral`, `Dallas`, `Metakom` |
| `Data` | hex | Key data |

Version 1 files are still loaded (`Dallas` is read as DS1990) and are converted to version 2 when you
save them.

## Related

- [Protocols](/ibutton/protocols) · [Add manually](/ibutton/add-manually) · [Reading](/ibutton/read)
