---
title: File formats
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/LfRfidFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/T5577FileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-docs, unleashed-src]
---
# 125 kHz RFID file formats

Three kinds of files live in `/ext/lfrfid/`:

| Extension | What it describes | Created by |
|---|---|---|
| `.rfid` | A **card**: protocol + ID | Read → Save, Add Manually |
| `.t5577` | A **chip**: every block of a T5577 | [T5577 app](/rfid/t5577-app) |
| `.ask.raw` / `.ask134.raw` / `.psk.raw` | A raw signal recording | [RAW](/rfid/raw) |

## `.rfid` — LF RFID key

```text
Filetype: Flipper RFID key
Version: 1
Key type: EM4100
Data: 01 23 45 67 89
```

The file stores one key of the type given by `Key type`.

| Field | Description |
|---|---|
| `Key type` | Protocol name, exactly as in the [protocol table](/rfid/protocols) |
| `Data` | Key data in hex; its length is fixed per protocol |

Valid `Key type` values in this firmware: `EM4100`, `EM4100/32`, `EM4100/16`, `Electra`, `H10301`, `Idteck`,
`Indala26`, `Indala224`, `IoProxXSF`, `AWID`, `FDX-A`, `FDX-B`, `HIDProx`, `HIDExt`, `Pyramid`, `Viking`,
`Jablotron`, `Paradox`, `PAC/Stanley`, `Keri`, `Gallagher`, `Nexwatch`, `Radio Key`, `GProxII`, `Noralsy`.

Version history: 1 — initial version. Legacy files with `Key type: I40134` (3 bytes) are converted to `Indala26` on
load.

::: tip
You can create a key on a computer: write the four lines above with the right `Key type` and the correct number of
`Data` bytes, copy it to `/ext/lfrfid/` and it shows up in **Saved**.
:::

## `.t5577` — T5577 dump

```text
Filetype: Flipper T5577 dump
Version: 1
# Block 0: ASK/Manchester, RF/64, 2 data blocks, password enabled
Page 0 blocks read: 0 1 2 7
Page 0 Block 0: 00 14 80 50
Page 0 Block 1: 12 34 56 78
Page 0 Block 2: 9A BC DE F0
Page 0 Block 3: 00 00 00 00
Page 0 Block 4: 00 00 00 00
Page 0 Block 5: 00 00 00 00
Page 0 Block 6: 00 00 00 00
Page 0 Block 7: 0C 0D 0E 0F
Page 1 blocks read: 0 1
Page 1 Block 0: E0 15 00 1A
Page 1 Block 1: 20 24 10 00
Page 1 Block 2: 00 00 00 00
Page 1 Block 3: 00 00 00 00
Password: 0C 0D 0E 0F
```

A `.t5577` file describes the **silicon**, a `.rfid` file describes the **card**. A T5577 configured as an EM4100 can
be saved either way, and the two are not interchangeable: `.t5577` includes the configuration that decides how the chip
talks and the password protecting it.

| Field | Description |
|---|---|
| `Page 0 blocks read` | Page 0 blocks whose values came from the chip, space-separated |
| `Page 0 Block 0..7` | Block contents, 4 hex bytes, MSB first. Block 0 = configuration, block 7 = password store |
| `Page 1 blocks read` | Page 1 blocks that were read |
| `Page 1 Block 0..3` | Block 0 repeats the configuration; 1–3 hold the factory traceability data |
| `Password` | Optional. A password **known to work** on the chip |

Key rules:

- **Every block has a key**, read or not. Only blocks named in `blocks read` are content; the rest is padding and
  must never be written to a tag. A file listing no blocks at all is rejected.
- A protected chip refuses the block-0 read that detection needs, so without the password you get no dump at all
  (not a partial one). A partial dump means the tag drifted out of the field.
- `Password` and `Page 0 Block 7` are different facts and may disagree: block 7 is what the block contained when
  read (ordinary storage if no password is enabled), `Password` is a credential that worked. Clearing a password only
  clears the bit in block 0, so block 7 keeps the old value.
- The comment line decoding block 0 is for humans only.

### Restore order

When writing a dump back (T5577 app → **Write to Tag**), the order matches Proxmark3:

1. Page 0 blocks 1–7. From block 7 on, writes must use the password now stored in block 7.
2. Page 1 blocks 1–3 (page 1 block 0 is never written). Genuine chips refuse to change blocks 1–2 — reported as
   *unchanged*, not as a failure.
3. Page 0 block 0 **last** — it changes how the chip talks.
4. Only blocks listed in `blocks read` are written.
5. A block 0 of zero is **never** written: a chip holding it answers nothing at all, and there is no way back.

Write frames get no answer, so success is known only by reading the blocks back.

## `.raw` — RAW recordings

Binary files written by RAW read. They start with a header:

| Field | Type | Value |
|---|---|---|
| magic | uint32 | `0x4C464952` |
| version | uint32 | `1` |
| frequency | float | carrier frequency, Hz (125000 or 134200) |
| duty_cycle | float | carrier duty cycle |
| max_buffer_size | uint32 | largest buffer in the file |

followed by buffers, each prefixed with its size, holding varint-encoded *(pulse, duration)* pairs. Use `rfid raw_analyze <filename>` in the CLI to
decode them.

## Related

- [Protocols](/rfid/protocols) · [T5577 app](/rfid/t5577-app) · [RAW](/rfid/raw)
