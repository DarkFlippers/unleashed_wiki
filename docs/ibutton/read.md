---
title: Reading keys
order: 10
original: [https://docs.flipper.net/zero/ibutton/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols]
sources: [unleashed-src, flipper-docs]
---
# Reading, saving and emulating iButton keys

Flipper Zero reads Dallas 1-Wire keys (ID and, for memory keys, their memory), Cyfral and Metakom keys, and can then
save and emulate them.

| Key | What is read |
|---|---|
| Dallas **DS1990** / **DS1420** | 8-byte ROM (ID) only — the key has no memory |
| Dallas **DS1992** | ROM + 128 bytes SRAM |
| Dallas **DS1996** | ROM + 8192 bytes SRAM |
| Dallas **DS1971** | ROM + 32 bytes EEPROM |
| Other 1-Wire devices | ROM only, shown as **Dallas (non-specific)** |
| **Cyfral** | 2-byte code |
| **Metakom** | 4-byte code |

## Reading a key

1. Go to `Main Menu → iButton → Read`. The screen shows **Reading — Connect key with pogo pins**.

   ![Reading screen with the prompt "Connect key with pogo pins"](/screens/ibutton/read.png)

2. Touch the key to the **flat part** of the iButton pad so that its centre touches the **left data pin** and its rim
   the **middle ground pin**. Hold it still.
3. When the key is read, the Flipper beeps and shows the protocol (e.g. **Dallas DS1990**) and its ID.

   ![Read result: Dallas DS1990 with its eight-byte ID and family code, Retry and More at the bottom](/screens/ibutton/read_success.png)

4. Buttons: <kbd>←</kbd> **Retry**, <kbd>→</kbd> **More**. <kbd>Back</kbd> asks *Exit to iButton Menu? All unsaved data
   will be lost!*

**More** offers (items depend on the protocol):

| Item | When shown | Action |
|---|---|---|
| **Save** | always | Name the key, saved to `/ext/ibutton/<name>.ibtn` |
| **Emulate** | always | Emulate right away |
| **Write ID** | writable protocols | Write the ID to a blank — [Writing](/ibutton/write) |
| **Full Write on Same Type** | DS1992, DS1996, DS1971 | Copy the memory to a key of the same type |
| **Data Info** | DS1992, DS1996, DS1971 | Show the memory dump |

## Read errors

If the data doesn't pass the protocol's check, the error screen explains why and still offers **Retry** and **More**:

- **CRC Error** (Dallas) — the 8th byte of the ROM is a CRC over the first seven; the screen shows the ROM with the
  bad byte highlighted and the *Expected CRC*. Usually a bad contact: clean the key and read again. If it repeats, you
  can still save and try emulating — some readers ignore CRC. If emulation fails, the error can't be fixed.
- **Invalid Metakom key: odd parity in byte N** — a Metakom byte failed its parity check; re-read it.

## Saved keys

`Main Menu → iButton → Saved` opens `/ext/ibutton/`. A key's menu:

| Item | Action |
|---|---|
| **Emulate** | Emulate to a reader |
| **Write ID** | Write the ID to a blank |
| **Full Write on Same Type** | DS1992/DS1996/DS1971 only — copy memory |
| **Edit** | Change the ID in hex, then save under a name |
| **Rename** / **Delete** | Manage the file |
| **Info** | Name, protocol, ID; <kbd>→</kbd> **More** shows memory data for memory keys |

## Emulating

1. Open a saved key → **Emulate** (or **More → Emulate** right after reading). The screen shows **Emulating**,
   `[Protocol]` and the key name (or *Unsaved Key*).

   ![Emulating screen showing "Emulating", the protocol [DS1990] and the key name](/screens/ibutton/emulate.png)

2. Press the **protruding part** of the pad against the reader: the **right data pin** must touch the reader's centre,
   the **middle ground pin** its rim.
3. If the ground pin can't reach the rim, connect two wires: GPIO **17** → reader centre, GPIO **8 / 11 / 18** (GND)
   → rim.

## CLI

```text
ikey read
ikey emulate <key_type> <key_data>
ikey write Dallas <key_data>
	<key_type>: Dallas (8 bytes), Cyfral (2 bytes), Metakom (4 bytes, must contain correct parity)
	<key_data> is hex
```

## Troubleshooting

- **Nothing happens.** The key is not touching both pins — tilt it so the rim touches the ground pin.
- **Unsupported key.** It may use an unsupported protocol (or be an RFID fob — try [125 kHz RFID](/rfid/read)).
- **Emulation rejected.** Check pin contact; some readers detect emulators or check things the Flipper can't fake. If
  you edited/added the key by hand, double-check the ID.

## Related

- [Writing](/ibutton/write) · [Add manually](/ibutton/add-manually) · [Protocols](/ibutton/protocols) ·
  [File format](/ibutton/file-format)
