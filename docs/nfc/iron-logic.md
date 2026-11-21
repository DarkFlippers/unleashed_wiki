---
title: Iron Logic readers
order: 100
author: gromovyna
original: [https://telegra.ph/Schityvateli-Iron-Logic-i-chto-s-nimi-delat-03-13, https://t.me/gromovyna/14]
sources: [gromovyna]
---
# Iron Logic readers (CP-Z-2 "3 stripes" / "4 stripes")

Iron Logic readers ("plugs") are popular in intercoms and access control across the former USSR. They protect MIFARE Classic fobs with per-card keys and anti-clone filters, so reading, emulating and copying **your own** fob with a Flipper Zero takes more than one pass.

::: tip Scope
For your own credentials and lawful research only. Based on the article by @gromovyna (2025-03-13).
:::

## How these systems defend against cloning

Iron Logic builds on cheap MIFARE Classic and layers defences on top of it:

- **Key diversification.** Sector keys are derived per card from the card UID and the reader's "object map" (a constant loaded into the reader). A dictionary attack therefore usually finds nothing on a configured system.
- **Filters** against magic cards and emulators (for example "IL-30 only", OTP1, OTP2), depending on reader firmware.
- **Dynamic mode** ("only first", see [Iron Logic dynamic enrollment](/nfc/iron-logic-enrollment)) where data on the card changes on every pass.

## Which reader do you have

| Variant | Notes |
|---|---|
| CP-Z-2 ("3 stripes") | Older, discontinued, still common. |
| CP-Z-2 (mod. MF-I) ("4 stripes") | Current model, supported by firmware releases. The article is written for this one, but works for the older one too. |

Identification by case is not 100 % reliable (an installer can put new electronics into an old case) but works in practice almost always. The readers are also used inside panels from other vendors (Eltis, Metakom and others); this does not matter, because the goal is to recover all sectors of the MIFARE Classic card.

## Check whether you are out of luck

### SmartMX card (IL-30)

If a "4 stripes" reader is used and the Flipper shows the "unsupported card" style screen, check the card: **SAK = 28** and **ATQA = 0004** means a **SmartMX** card, and the reader may have the **"IL-30 only"** filter enabled. You can still try the steps below in case the filter is off and the reader is in mixed mode (new SmartMX and old MIFARE Classic keys). If nothing works and you need a copy, the author suggests a workshop equipped with iKey devices, which write the data to original chips (iMF+) using a logic flaw in Iron Logic.

### Dynamic intercoms ("Sokol" by Petrunya)

Sokol intercoms (usually built on an Eltis 5000 panel) use Iron Logic readers **with dynamics**: data in the key changes on every pass and old copies become invalid. Emulating or writing a blank can **corrupt your original**. Details: [dynamic enrollment](/nfc/iron-logic-enrollment).

## Step 1: dump all sectors

You need all sectors and all keys of the card. Do not wait for the dictionary attack to finish: with diversified keys it makes no sense.

1. Read the card (`Main Menu → NFC → Read`). See [Reading cards](/nfc/read).
2. If the result is **16/16 sectors read but 0/32 keys found**, the card has a backdoor. Go straight to the [Nested / Fudan backdoor guide](/nfc/nested-fudan).
3. If you have no keys at all, collect nonces from the reader (see below), then recover keys with [MFKey](/nfc/mfkey).
4. Recover the remaining keys with Nested ([guide](/nfc/nested-fudan)).

### Collecting nonces from the reader

Until recently it was believed that the Flipper cannot work with 4-stripe readers at all. Thanks to @blowtreez it turned out to be possible, though it needs precision and practice. The Flipper collects nonces from **all** reader versions, regardless of the number of stripes or firmware.

- Find the position where the Flipper interacts with the reader. Empirically: the **"FLI"** text on the Flipper case should be **above the reader**.
- Keep it as close as possible, touching the reader.
- Sometimes (as in the author's case) it does not work in a case; take the Flipper out and try bare.

Then follow the official article [Recovering MIFARE Classic keys](https://docs.flipper.net/nfc/mfkey32).

::: tip Author's notes
- In most cases the keys and fully read sectors **0, 1 and 14** are enough, but some systems keep data in custom sectors (for example 8). Always make a full copy and decrypt all sectors.
- The author mentions having a private API that computes the sector 14 key from a card UID, to continue with Nested (offered in the Unleashed community chat).
:::

## Step 2: emulation

- Works on all "3 stripes" readers (rare exceptions) and on "4 stripes" readers unless they run the latest firmware (**7.28**, as stated in the channel post).
- On older versions such as **7.20** (the current factory firmware) emulation works, but you must find the exact Flipper position relative to the reader, as with nonce collection.
- Filters OTP1 and OTP2 do **not** affect emulation.
- Chameleon Ultra behaves the same way.
- With the "IL-30 only" filter on, emulation will not work.

## Step 3: copying to a blank

The universal choice is a **CUID static nonce (aka MF-3.2)** blank (see [Magic cards](/nfc/magic-cards)). At the time of writing it worked on all firmware versions and filter settings for both reader types. For "3 stripes" an ordinary **CUID** works, and some people even succeeded with **Zero**.

The author recommends not hunting for the minimal working blank unless you enjoy experiments: the price difference between CUID static nonce and plain CUID is small, and you avoid the "casino factor". He also found several plain CUID chips (newer revisions) that work on all 4-stripe firmware versions, and earlier community reports of success with plain CUID blanks, which he could not reliably reproduce until recently.

## Not covered

The author lists topics that are out of scope or still under research: how OTP1/OTP2 filters are implemented, the KDF for key A of sector 14 from the UID, and the role of the object map in sector encryption.

## Related

- [Nested and Fudan backdoor](/nfc/nested-fudan) · [MFKey](/nfc/mfkey) · [Magic cards](/nfc/magic-cards)
- [Iron Logic dynamic enrollment](/nfc/iron-logic-enrollment) · [Vizit filters](/nfc/vizit-filters)
