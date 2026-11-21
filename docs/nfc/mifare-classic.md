---
title: MIFARE Classic
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_classic, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, unleashed-readme, gromovyna]
---
# MIFARE Classic

MIFARE Classic is the most common card in access control, intercoms, hotels and older transport systems. It is also
the most "interesting" one for Flipper: its Crypto-1 cipher is broken, so with enough effort the keys of almost any
card can be recovered, then the card can be emulated or written to a [magic blank](/nfc/magic-cards).

## Memory layout

| Type | Sectors | Blocks | Keys to find | Typical SAK |
|---|---|---|---|---|
| MIFARE Mini | 5 | 20 | 10 | `09` |
| MIFARE Classic 1K | 16 | 64 | 32 | `08` |
| MIFARE Classic 4K | 40 (32 × 4 blocks + 8 × 16 blocks) | 256 | 80 | `18` |

- A **block** is 16 bytes. **Block 0** (manufacturer block) holds the UID and manufacturer data; on genuine cards it
  is read-only, which is exactly why magic cards exist.
- The last block of every sector is the **sector trailer**: `Key A (6 bytes) | access bits (4 bytes) | Key B (6 bytes)`,
  e.g. `FF FF FF FF FF FF FF 07 80 69 FF FF FF FF FF FF` on a blank card.
- Access bits decide which key may read/write which block. Often Key A reads and Key B writes; sometimes Key B is
  itself readable and then cannot be used as a key.

## Key dictionaries

Flipper never "knows" keys: it tries candidate keys from dictionaries. All are plain text files with one 12-hex-digit
key per line, `#` for comments (see [file format](/nfc/file-format)).

| Dictionary | Path | Who writes it |
|---|---|---|
| **System** | `/ext/nfc/assets/mf_classic_dict.nfc` | Ships with the firmware (overwritten on update). In Unleashed it has **4000+ keys**. |
| **User** | `/ext/nfc/assets/mf_classic_dict_user.nfc` | You, MFKey, qUnleashed, *Save Keys to Dictionary*. Survives updates. |
| **CUID** (per card) | `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | MFKey / qUnleashed for cards with *static encrypted* nonces: a large list of key candidates for one UID. |
| **Key cache** | `/ext/nfc/.cache/<UID>.keys` | Written automatically when you **save** a card; used first on the next read of the same UID. |

::: tip Unleashed
The Unleashed system dictionary contains a large set of extra keys collected by the community ("Extra Mifare Classic
keys in system dict" in the ReadMe). The CUID dictionary loading screen with a progress bar (*"CUID dictionary is
loading"*) appeared in dev build 1437 / release 094.
:::

### Manage the user dictionary on the device

1. Go to `Main Menu → NFC → Extra Actions → MIFARE Classic Keys`.

   ![Extra Actions menu with MIFARE Classic Keys among the dictionary entries](/screens/nfc/extra_actions.png)

2. The screen shows **System dict: N** and **User dict: N**.
3. <kbd>OK</kbd> **Add**: enter a 6-byte key in hex and save. A duplicate key triggers a warning.
4. <kbd>→</kbd> **List** (only if the user dictionary isn't empty): pick a key to delete it (*"Select key to delete:"*).

You can also edit `mf_classic_dict_user.nfc` on a computer (qFlipper, qUnleashed, or the SD card directly).

### Save Keys to Dictionary

Every saved or freshly read MIFARE Classic dump with at least one known key has **Save Keys to Dictionary** in its
menu. It copies all keys from that dump into the user dictionary, skipping duplicates, and reports *"New keys: N,
Already known: M"*. This matters most for cards whose keys were recovered from a CUID dictionary: those keys
otherwise live only in that per-UID file and in the dump, while [NFC Magic](/nfc/nfc-magic) only looks at the key
cache and the user/system dictionaries (this is the "automatic saving of keys with a duplicate check" @gromovyna
mentions in his [qUnleashed article](/nfc/qunleashed)).

## What happens when you read a MIFARE Classic card

`Main Menu → NFC → Read`, hold the card still. The firmware goes through these stages; the header of the attack
screen shows which one is running.

1. **Key cache.** If you saved this UID before, the cached keys are used and the card is read immediately.
2. **Dictionary attack**, in this order:
   - **MF Classic CUID Dictionary**: only if a per-UID file exists (before it, *"CUID dictionary is loading"* with a
     progress bar; a large file takes minutes to load).
   - **MF Classic User Dictionary**: if the user file exists and isn't empty.
   - **MF Classic System Dictionary**.

   The screen shows `Keys found: X/Y`, `Sectors Read: X/Y`, the current key number and *"Unlocking sector: N"* /
   *"Reuse key check for sector: N"*.

   ![System dictionary attack: unlocking sector 9, key 1244 of 2271, 19 of 32 keys found](/screens/nfc/dict_attack.png)

3. **Backdoor read.** If the chip has a known **backdoor key** (Fudan and some others), the header shows **Backdoor
   Read** / **(Backdoor)** and the sectors are read without real keys. Nonces are collected at the same time.
4. **Nested attacks** (once at least one key is known): **PRNG Analysis**, **Nested Dictionary**, **Calibration**,
   **Nonce Collection** (*"Collecting from sector: N"*). A **(Hard)** suffix means the card has a hard PRNG.
   Collected nonces are appended to `/ext/nfc/.nested.log`.
5. The result screen opens. A green LED / success sound means the card is fully read, a short "semi-success"
   means some sectors are still missing.

Press <kbd>OK</kbd> **Skip** to jump to the next stage (CUID → User → System → result). <kbd>←</kbd> asks *"Exit to NFC
Menu? All unsaved data will be lost"*. If the card is pulled away you get **"Lost the tag! Make sure the tag is
positioned correctly."**; put it back and the attack continues.

A detailed walk-through with screenshots of each phase is on [Nested attacks and Fudan backdoors](/nfc/nested-fudan).

### After reading

The read menu (`More`) for a MIFARE Classic card contains:

| Item | When | What it does |
|---|---|---|
| **Save** | always | Save the dump to `/ext/nfc/`. Also fills the key cache. |
| **Emulate** | always | Full emulation of the dump. |
| **Extract MFC Keys** | card not fully read | Asks *"Save the Key?"* (Save/Skip), then collects nonces from a reader. See [MFKey32](/nfc/mfkey). |
| **Unlock with Dictionary** | card not fully read | Runs the dictionary/nested attack again (e.g. after you added keys). |
| **Crack nonces in MFKey32** | card not fully read | Offers to save the card, then launches the [MFKey app](/nfc/mfkey-app) (**Run**). |
| **Show Keys** | always | *"Found MFC Keys"*: per sector access bits, Key A, Key B and totals. |
| **Save Keys to Dictionary** | at least one key known | See above. |
| **Info** | always | UID, ATQA, SAK, keys/sectors summary; **More** shows the hex dump (`??` = unknown bytes). |

On a **saved** card you additionally get **Write to Initial Card**, **Update from Initial Card**, **Restore to
Original State** (if a shadow file exists), **Rename** and **Delete**.

## Getting the missing keys

If not all sectors were read, pick the method that matches your situation:

| Situation | Method |
|---|---|
| You have the card **and** access to the reader | [MFKey32](/nfc/mfkey): Flipper emulates the card, the reader reveals its keys. |
| You have the card, at least one key is known or the chip has a backdoor | Nested attacks run automatically in `Read`; then compute keys with the [MFKey app](/nfc/mfkey-app) or, much faster, [qUnleashed](/nfc/qunleashed). |
| Card has a **hard PRNG** | HardNested: computed by qUnleashed or on a PC, see [Nested attacks](/nfc/nested-fudan). |
| No card, only the reader | [MFKey32](/nfc/mfkey) via `Extract MFC Keys` from the main NFC menu: the keys go to the user dictionary for later. |
| Keys are diversified per card (e.g. [Iron Logic](/nfc/iron-logic)) | Every card has its own keys: recover them for each card individually. |

After new keys are added, read the card again (or open the saved file → **Unlock with Dictionary**).

## Emulation

1. `Main Menu → NFC → Saved → <card> → Emulate`.
2. Hold the Flipper to the reader.

Sectors that were never read are emulated as unknown: a reader that needs them will reject the card. If the reader
writes to the card (balance, counters, "dynamic" systems), the changes go to the [shadow file](/nfc/read#shadow-files).

::: warning Dynamic systems
Some systems rewrite data on the card at every pass (e.g. [Iron Logic in dynamic mode](/nfc/iron-logic-enrollment)).
An emulated copy and the original then go out of sync; using both can block the original.
:::

## Writing

- **Write to Initial Card** writes the dump back **to the same card** (UID must match). Any other card gives
  *"Use source card! To write blanks use NFC Magic app"*. If not every block could be written: *"Not all sectors were
  written correctly"*.
- To clone onto a blank use the [NFC Magic](/nfc/nfc-magic) app and a suitable [magic card](/nfc/magic-cards).
  Choose the blank carefully: many readers filter Gen1 cards.

## Troubleshooting

- **Keys found but some sectors still not read**: access bits may forbid reading with the found key type; recover the
  other key (A or B).
- **The read starts with a long "CUID dictionary is loading"**: a large per-UID candidate list exists for this card.
  That's expected after a static-encrypted-nonce attack. Delete `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` once the
  card is fully recovered and its keys are saved to the user dictionary.
- **MFKey says "Nonces already cracked" / nothing new**: clean `/ext/nfc/.nested.log` and `/ext/nfc/.mfkey32.log`
  after successful recovery; old nonces slow everything down.
- **Recovered keys don't seem to be used**: check that they really landed in `mf_classic_dict_user.nfc`
  (`Extra Actions → MIFARE Classic Keys → List`). Keys found by HardNested on a PC must be added by hand.

## Related

[Reading cards](/nfc/read) · [MFKey32](/nfc/mfkey) · [Nested attacks](/nfc/nested-fudan) ·
[MFKey app](/nfc/mfkey-app) · [qUnleashed](/nfc/qunleashed) · [Magic cards](/nfc/magic-cards) ·
[MIFARE Plus](/nfc/mifare-plus)
