---
title: Supported protocols
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks, https://docs.flipper.net/zero/ibutton/read, https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Supported iButton protocols

Built from `lib/ibutton/protocols/` of the Unleashed firmware. The firmware groups protocols into **Dallas** (1-Wire)
and **misc** (Cyfral, Metakom).

| Protocol (file name) | Menu label | Family code | Memory | Emulate | Write ID to | Full Write on Same Type |
|---|---|---|---|---|---|---|
| `DS1990` | Dallas DS1990 | `01` | — | ✓ | RW1990.1, RW1990.2, TM2004, TM01x | — |
| `DS1420` | Dallas DS1420 | `81` | — | ✓ | RW1990.1, RW1990.2, TM2004 | — |
| `DS1992` | Dallas DS1992 | `08` | 128 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1996` | Dallas DS1996 | `0C` | 8192 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1971` | Dallas DS1971 | `14` | 32 B EEPROM (`Eeprom Data`) | ✓ | TM2004 | ✓ |
| `(non-specific)` | Dallas (non-specific) | any | — (ROM only) | ✓ | TM2004 | — |
| `Cyfral` | Cyfral | — | 2-byte code | ✓ | TM01x | — |
| `Metakom` | Metakom | — | 4-byte code | ✓ | TM01x | — |

## Dallas 1-Wire

Dallas Semiconductor (now Analog Devices) "touch memory". Every device has an 8-byte ROM: family code, 48-bit serial
and CRC-8. The Flipper checks the CRC and identifies the type by family code.

- **DS1990 (DS1990A)** — the classic ID-only key used by most intercoms.
- **DS1420** — fully compatible with DS1990, only the family code differs (`81` instead of `01`).
- **DS1992 / DS1996** — memory keys with SRAM; DS1971 — with EEPROM. The Flipper reads the memory, can show it
  (**Data Info**), emulate it, and copy it to a key of the same type.
- **Dallas (non-specific)** — catch-all for any other 1-Wire device: only the ROM is read, nothing is checked. Also
  useful to make a key with an intentionally wrong family code or CRC.

## Cyfral

An intercom key protocol common in Russia and the CIS; it is not 1-Wire. The code is stored as 2 bytes. Can be emulated and written to a TM01x blank.

## Metakom

Another CIS intercom protocol. The code is 4 bytes, every byte carries a parity bit — a key with wrong parity is
reported as invalid and is not written. Can be emulated and written to a TM01x blank.

## Blanks

| Blank | Accepts | Behaviour |
|---|---|---|
| **RW1990.1** | Dallas ROM (8 bytes) | Unlock, write (bits inverted), lock |
| **RW1990.2** | Dallas ROM (8 bytes) | Unlock, write, lock |
| **TM2004** | Dallas ROM (8 bytes) | Writes from address 0 with a read-back check of each byte |
| **TM01x** | Dallas ROM, Cyfral, Metakom | Cyfral/Metakom are written as a 36-bit frame (4-bit prefix + 32 code bits), verified, then **finalized** (one-way). Dallas IDs are not finalized |

See [Writing](/ibutton/write) for usage.

::: tip Unleashed
The official docs don't list DS1420, the Write Blanks setting, or TM01x writing for Cyfral/Metakom.
:::

## Related

- [Reading](/ibutton/read) · [Writing](/ibutton/write) · [File format](/ibutton/file-format)
