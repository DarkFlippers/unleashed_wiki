---
title: Writing to blanks
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/rfid/write-data, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29]
sources: [unleashed-src, flipper-docs, gromovyna]
---
# Writing 125 kHz keys to blanks

Original 125 kHz cards and fobs are almost always read-only. To make a physical copy you need a **writable blank** — a
"magic" chip that can be programmed to behave like a card of another protocol. Flipper Zero can write any saved, read
or manually added key to such a blank.

## Which blanks can be written

| Chip (as shown on screen) | Typical market names | Writes | Default |
|---|---|---|---|
| **T5577** | T5577, ATA5577, "5577" cards/fobs/stickers | every protocol | ON |
| **EM4305** | EM4305 / EM4205 blanks | EM4100 family, Electra, FDX-B, Gallagher, GProxII, Jablotron, Radio Key (Securakey), Viking | ON |
| **8265** | ID8265 / H5 (Hitag Micro clone, default password) | EM4100 family | ON |
| **8210** | ID8210 (same chip, password of the FURUI cloner) | EM4100 family | ON |
| **H5.5** | iKey H5.5 (same chip, iKey password) | EM4100 family | ON |
| **8268** | ID8268 (Hitag S magic chip) | EM4100 at RF/64 only | **OFF** |

::: tip Unleashed
The official docs only talk about T5577. Hitag Micro support for **8265/H5, H5.5 and 8210** was added to Unleashed
by **@gromovyna** — the chips differ only by the login password, so the Flipper tries each known password in turn
instead of asking you. Background and story: [T5577 and Hitag Micro](/rfid/t5577-hitag).
:::

::: warning 8268 is opt-in
The **8268** (Hitag S) target is off by default. Unlike the other writers it selects whatever Hitag S tag answers, and
on a genuine Hitag S pages 4 and 5 hold application data — the Flipper cannot tell a genuine tag from a clone. Enable
it only when you know an 8268 blank is on the coil.
:::

## Writing a key

1. Read a tag (`Read` → **More** → **Write**) or open a saved one (`Saved` → key → **Write**).
2. Put the blank against the Flipper's back and **don't move it**. The LED blinks magenta.
3. The screen shows **Writing**, the protocol in brackets, the file name (or *Unsaved Tag*) and, in parentheses, the
   **chip currently being tried**, for example:

   ```text
   Writing
   [EM4100]
   Office
   (T5577)
   ```

   ![Writing screen with the protocol [EM4100], the key name and the chip being tried, (T5577), in parentheses](/screens/lfrfid/write.png)

4. The Flipper writes each enabled chip type in turn and **reads the tag back** after each attempt. As soon as the
   read-back matches, it stops.
5. On success you see **Success!** with the name of the chip that actually took the data (e.g. `T5577`, `EM4305`,
   `H5.5`), and the app returns to the key menu.

![Write in progress, showing the chip being tried](/img/remote/34b72cbd8417d74e.png)

![Write result with the chip name](/img/remote/3ca59457a78dad5b.png)

::: tip Why the chip name?
With several chip types to try (and three passwords for Hitag Micro), a write can take noticeably longer, and it was
unclear what had been written. Showing the attempted and the final chip was @gromovyna's UX fix: technically it is the
market name of the blank variant, not a protocol.
:::

## Settings → Write Chips

`Main Menu → 125 kHz RFID → Settings → Write Chips` lists all targets: **T5577**, **EM4305**, **8265**, **8210**,
**H5.5**, **8268**, each **ON** / **OFF**.

- <kbd>OK</kbd>, <kbd>←</kbd> or <kbd>→</kbd> toggles the highlighted chip.
- The choice is saved when you leave the page (<kbd>Back</kbd>) to `/ext/lfrfid/.lfrfid.settings`.
- Turning off chips you never use makes writes faster (each enabled, non-matching chip costs one write + verify).
- The CLI `rfid write` honours the same setting.

If the page fails to open, you see *Settings plugin failed to load* — update the SD resources (the page is a separate
plugin file). Writes still use whatever is stored in the settings file.

## Write and set password

`Saved` → key → **Write and set password** writes the key to a **T5577** and turns on its password protection, so
nobody can rewrite the tag without the password.

1. Enter the 4-byte password in hex. If none was set yet, the field is pre-filled with a random word from the T5577
   dictionary.
2. Hold the blank still. The screen shows **Writing with password**, `[Protocol]` and the current step.
3. The key is written and read back first, then the password goes to block 7 and is read back, and only then is the
   password bit set in block 0. **Write down the password** — a T5577 locked with an unknown password cannot be
   reused.

Possible results:

| Screen | Meaning |
|---|---|
| **Success!** | Key written, password stored and protection on |
| **Error** — *This protocol cannot be written with a password* | The protocol needs all 7 data blocks, block 7 can't hold a password |
| **Has a password** — *Clear it first: the T5577 app, Clear Password* | The tag is already protected |
| **Cannot read it** | Something is on the coil but its blocks can't be read — wipe it or clear its password first |
| **Not written** | A block refused the key; the tag holds part of it and no password |
| **Not protected** | The password didn't land in block 7, or the tag refused to turn protection on |
| **Not confirmed** | The password is on the tag, but whether protection is active could not be read back |
| **Still trying to write...** | No tag answers — check that it is a writable T5577 |

## Error messages of a normal write

| Message | What to do |
|---|---|
| *This protocol cannot be written* | No chip encoding exists for it |
| *No write chips enabled. Enable one in Settings* | All targets are OFF |
| *No enabled chip can write this protocol* | E.g. only EM4305 enabled for an HID key — enable T5577 |
| **Still Trying to Write...** *Make sure this card is writable and not protected* | Shown after ~10 s or several failed verifies. The tag is read-only, protected with a password, an unsupported chip, or badly positioned. The Flipper keeps trying until you press <kbd>Back</kbd>. |

## Troubleshooting

- **The blank has a password.** Many cheap cloners lock T5577 blanks. Use the [T5577 app](/rfid/t5577-app) →
  **Clear Password** (tries your password, then the dictionary).
- **A T5577 got a garbage configuration** (doesn't read as anything). Use the T5577 app → **Wipe Tag**.
- **Hitag Micro (8265/8210/H5.5) needs good positioning.** Writing these takes longer and is sensitive to placement; the
  Flipper only has TX on LF, so success is confirmed only by reading the tag back.
- **"Success" on a read-only card.** If a non-writable tag already carries the same ID, the read-back matches and the
  write is reported as successful.
- **Fobs with metal / thick housings.** Try different spots; key fobs often have the coil off-centre.

## Related

- [T5577 and Hitag Micro](/rfid/t5577-hitag) · [T5577 app](/rfid/t5577-app) · [Protocols](/rfid/protocols) ·
  [Reading](/rfid/read)
