---
title: Iron Logic dynamic enrollment
order: 110
author: gromovyna
original: [https://telegra.ph/Enrollment-ataka-na-dinamiku-ot-Iron-Logic-06-05, https://t.me/gromovyna/14, https://t.me/gromovyna/19, https://t.me/gromovyna/20, https://t.me/gromovyna/25]
sources: [gromovyna]
---
# Iron Logic "dynamics" and the enrollment logic flaw

A research write-up on how Iron Logic readers implement anti-clone "dynamics" (the "ТП" / "first only" mode), and on a logic flaw in reader firmware 7.29 that was **fixed in 7.30**. Educational reading for owners and researchers.

::: tip Scope
For your own credentials and lawful research only. The flaw described here is patched in current firmware (7.30). Based on @gromovyna's article (2025-06-05) and channel posts.
:::

## How these systems defend against cloning

A static MIFARE Classic fob can be copied by anyone with the keys. Vendors answer in two ways:

1. **Filters**, which detect magic blanks and emulators (see [Iron Logic readers](/nfc/iron-logic), [Vizit filters](/nfc/vizit-filters)).
2. **Dynamics**: some data on the card is synchronised with the reader memory on every pass (a "counter"). A copy made earlier no longer matches and is rejected. Variants of this are used by Intratone, Hexact, Comelit, Noralsy and Urmet in France, Belgium and Luxembourg (where a detected desync can disable all of a user's tags), and was seen on some Eltis intercoms in Russia.

## The "ТП" ("Только первый" / "first only") mode

From the vendor's announcement quoted on the channel (post 20): on every access the reader writes a **new password** to the card. On the next access the card number plus password are checked against what the reader stored; if they match, the card is accepted and a new password is written. Result: however many copies exist, only one card keeps working. Supported at first only by **CP-Z2 MF-I**, with firmware 7.29 (announced as not fully tested). The vendor warns that every pass now **writes to the card**, so you should check your cards' write endurance before switching.

Why it is a headache: the market is full of counterfeit Chinese MIFARE Classic tags, which may not survive the number of rewrites, and an interrupted write (bad position, power loss) can leave the card out of sync. This is also why emulating or cloning on such systems can **ruin your original**.

## Firmware 7.29: no filters, dynamics as the main mode

Firmware 7.29 (open test) disabled all filters and made dynamics the main mode. The research team found vulnerabilities in this release; a logic bug was fixed in **7.30**, after which the author published the description.

## Enrollment: how a card becomes dynamic

To move thousands of existing static cards to dynamics without making users reissue them, Iron Logic introduced **enrollment**. Metadata is written to **sector 14** of the card. Simplified reader logic:

1. The reader checks the card metadata.
2. If the card is **not yet in dynamic mode**, the reader enrolls it and stores a counter value. It does **not** check whether this card ID is already in its memory.
3. If the card is already enrolled, strict counter checks apply.

The ID/counter pairs are stored in the reader's non-volatile memory.

## The flaw (patched in 7.30)

The weakness follows from step 2: a reader that is presented with a card that still looks "static" simply enrolls it again. The only hurdle for an attacker is having a dump of the card from **before** its first enrollment. Cards old enough to lack metadata are not accepted by the reader, so converting dynamic data back to a "static" state was only superficially explored.

The author describes two practical ways to present a "static" card each time:

- **GDM (GDMIC) tags**, a USCUID variant with a shadow mode: data is written to temporary memory and rolls back to permanent memory when the reader field turns off, so the original (already enrolled) and unlimited copies can co-exist. The author notes this is simple but beyond most locksmiths, and can be countered by the earlier filters or smarter RF-field handling.
- **Flipper Zero, manual**: read the static card, emulate it, use `Return to Initial State`, repeat. Fine for tests, impractical daily.

The team has other theoretical and practical attacks, and shared some ideas with iKey.

## What owners should do

- Update readers to **7.30 or newer**.
- Test your card write endurance before enabling dynamics.
- Prefer modern card families (MIFARE Plus, DESFire and similar) where you can; MIFARE Classic is considered obsolete by its own vendor.

## Related

- [Iron Logic readers](/nfc/iron-logic) · [Magic cards](/nfc/magic-cards) · [Vizit filters](/nfc/vizit-filters)
