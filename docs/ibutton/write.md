---
title: Writing to blanks
order: 20
original: [https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks]
sources: [unleashed-src, flipper-docs]
---
# Writing iButton keys to blanks

Original iButton keys have a factory ID that can't be changed. To copy one you need a **blank** — a rewritable key
whose ID can be programmed. Flipper Zero has two write modes:

- **Write ID** — writes the ID (ROM / code) to a blank. This is the usual "make a copy of my intercom key".
- **Full Write on Same Type** — for DS1992, DS1996 and DS1971 only: copies the **memory** contents onto another
  genuine key of the same type (DS1992 → DS1992). The target key keeps its own ID.

## Supported blanks

| Blank (as in Settings) | Writes | Notes |
|---|---|---|
| **RW1990.1** | DS1990, DS1420 IDs | RW1990-type blanks; this variant writes the bits inverted |
| **RW1990.2** | DS1990, DS1420 IDs | RW1990-type blanks, non-inverted variant |
| **TM2004** | IDs of DS1990, DS1420, DS1992, DS1996, DS1971 and generic 1-Wire | RW2004/TM2004 blanks; only the ID is written, even though the blank has memory |
| **TM01x** | DS1990 ID, **Cyfral**, **Metakom** | TM01/TM01x blanks |

Blanks sold as RW1990, TM1990 or TM08v2 are handled by the RW1990 variants; the Flipper tries both, so you don't need
to know which one you have.

::: tip Unleashed
- **Settings → Write Blanks** lets you switch blank types on and off (all are ON by default).
- The write screen shows which blank is being tried, and the success screen says *Written to TM2004!* etc.
- **Cyfral and Metakom** can be written to **TM01x** blanks.
:::

::: warning TM01x for Cyfral / Metakom is one-way
For Cyfral and Metakom the TM01x blank is written, read back and compared, and then **finalized** into Cyfral or
Metakom mode. Finalizing cannot be undone: the blank no longer answers as a 1-Wire device and can't be rewritten —
not even as a Dallas key. If verification fails, the blank is not finalized and stays writable. A Dallas ID written to
a TM01x is not finalized.

Metakom keys with bad parity are refused (*Refusing to write a key with odd parity*).
:::

## Write ID

1. Open the key: `Saved` → key → **Write ID** (or **More → Write ID** after reading).

   ![Saved key menu with Emulate, Write ID, Edit and Rename](/screens/ibutton/saved_menu.png)

2. The screen shows **Writing ID**, `[Protocol]`, the key name (or *Unsaved Key*) and, in parentheses, the blank type
   being tried — e.g. `(RW1990.1)`.

   ![Writing ID screen with the protocol [DS1990], the key name and the blank being tried, (RW1990.1)](/screens/ibutton/write.png)

3. Touch the blank to the **flat part** of the pad (left data pin + middle ground), like when reading. Hold still.
4. The Flipper tries every enabled blank that can carry this protocol and reads the result back.
5. **Written to RW1990.2!** (or *Successfully written!*) — done.

## Full Write on Same Type

1. `Saved` → DS1992 / DS1996 / DS1971 key → **Full Write on Same Type**.
2. The screen shows **Full Writing**. Touch a genuine key of the **same** type.
3. The memory is written; the target's own ID stays. This mode doesn't use the Write Blanks setting.

## Settings → Write Blanks

`Main Menu → iButton → Settings → Write Blanks` lists **RW1990.1**, **RW1990.2**, **TM2004**, **TM01x** with
**ON**/**OFF**. Toggle with <kbd>OK</kbd>/<kbd>←</kbd>/<kbd>→</kbd>; it is saved when you leave, to
`/ext/ibutton/.ibutton.settings`. The CLI `ikey write` uses the same setting.

If the page reports *Settings page missing. Update the SD resources*, reinstall the firmware with the SD card in.

## Errors

| Screen | Meaning |
|---|---|
| **Cannot Write** — *No blanks enabled. Enable one in Settings* | All blank types are OFF |
| **Cannot Write** — *No enabled blank can write this key* | E.g. only RW1990 enabled for a Metakom key |
| **Cannot Write** — *This key cannot be written* (or the protocol's reason) | The key's data is invalid for writing |
| Writing screen stays, LED blinking | No blank detected yet — check contact, or the blank type isn't supported |

## Troubleshooting

- **Contact.** The blank's centre must touch the data pin and its rim the ground pin.
- **Unknown blank type.** Try enabling all types. Some cheap blanks are of types the Flipper can't program.
- **"Success" but the reader refuses the copy.** Some readers filter blanks (check for writable-blank behaviour) —
  nothing the Flipper can do about that.
- **Spent TM01x.** A TM01x finalized as Cyfral/Metakom can't be reused.

## Related

- [Reading](/ibutton/read) · [Protocols](/ibutton/protocols) · [Add manually](/ibutton/add-manually)
