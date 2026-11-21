---
title: Adding keys manually
order: 30
original: [https://docs.flipper.net/zero/ibutton/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# Adding iButton keys manually

You can create a virtual key from its ID without having the physical key — for example from a number engraved on the
key or written down earlier. It can be emulated and, for writable protocols, [written to a blank](/ibutton/write).

## Steps

1. Go to `Main Menu → iButton → Add Manually`.
2. Pick the protocol:

   | Menu label | ID to enter |
   |---|---|
   | **Dallas DS1990** | 8 bytes ROM |
   | **Dallas DS1992** | 8 bytes ROM |
   | **Dallas DS1996** | 8 bytes ROM |
   | **Dallas DS1971** | 8 bytes ROM |
   | **Dallas DS1420** | 8 bytes ROM |
   | **Dallas (non-specific)** | 8 bytes ROM — any 1-Wire device, no checks |
   | **Cyfral** | 2 bytes |
   | **Metakom** | 4 bytes (each byte must have correct parity) |

   ![Add Manually key type list: Dallas DS1990, DS1992, DS1996 and DS1971](/screens/ibutton/add_manually.png)

3. The screen **Enter the key** opens a hex editor. Type the bytes and press **Save**.
4. Enter a name (default prefix `iBtn`) and save. The key is stored in `/ext/ibutton/<name>.ibtn`.

## Editing a saved key

`Main Menu → iButton → Saved` → key → **Edit** → change the hex → **Save** → name → **Save**.

## Notes on Dallas IDs

A Dallas ROM is `family code` (1 byte) + `serial` (6 bytes) + `CRC` (1 byte):

```text
01 DE AD BE EF 00 00 ??
^^ family code (01 = DS1990, 81 = DS1420, 08 = DS1992, 0C = DS1996, 14 = DS1971)
                     ^^ CRC-8 over the first 7 bytes
```

- Most intercom keys are DS1990 with family code `01`.
- If the CRC is wrong, a reader may reject the key, and the Flipper reports a CRC error on reading it back.
- Need a key with a deliberately invalid family code or CRC? Use **Dallas (non-specific)** — it does no checks.
- A key added manually has **no memory data**; Full Write on Same Type needs a real read.

::: tip Byte editor
In Unleashed, pressing <kbd>↑</kbd> repeatedly in the byte input opens a mini nibble editor — handy for long IDs.
:::

## Related

- [Reading](/ibutton/read) · [Writing](/ibutton/write) · [Protocols](/ibutton/protocols) ·
  [File format](/ibutton/file-format)
