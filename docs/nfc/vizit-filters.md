---
title: Vizit reader filters
order: 120
author: gromovyna
original: [https://telegra.ph/Filtry-schityvatelej-Vizit-dlya-zashchity-ot-klonov-metok-Vizit-RF-31-05-15]
sources: [gromovyna]
---
# Vizit reader filters against Vizit RF 3.1 clones

How Vizit readers try to detect cloned **Vizit RF 3.1** (MIFARE Ultralight EV1) keys, and what each filter looks for. Based on @gromovyna's article (2025-05-15).

::: tip Scope
For your own credentials and lawful research only.
:::

## Background

Vizit is a Russian access control maker (since 1996 by its own account). Old readers used **Dallas** keys, then **EM Marine**; newer ones use **Vizit RF 3.1** (= MIFARE Ultralight, UID starts with `34`); the newest keys **Vizit RF 7.1** are **MIFARE Ultralight C** (3DES authentication). Minimum firmware for RF 7.1 is listed on the vendor site. The author notes that the key derivation for 7.1 keys is known to iKey and that Western researchers are working on 3DES key recovery (no details disclosed).

## How these systems defend against cloning

Unlike Iron Logic, the Vizit filters the author knows are **software**, not hardware, so they are visible in traffic captured with a Proxmark3. They were found in reader **RD-5F, firmware 212**; other panels carry them too, but the version in which each filter appeared is unknown.

### Filter 1: Gen1 backdoor

The reader sends the well-known backdoor command `40(7)` and waits for an answer. A genuine tag does not respond. It targets the earliest blanks (UL-0116 / UL-0416), which were written through the backdoor including the UID.

### Filter 2: EV1 VERSION

The reader sends `EV1 VERSION` and compares the **second byte of the result** with the **first byte of the tag UID**. Vizit RF 3.1 tags report manufacturer **Micron Russia** (byte `34`), and their UIDs start with `34`. This defeats USCUID-UL variants (Chinese "UL-21", Russian market "UL-2"). The market answer was "ULtra" tags, USCUID-UL with the same version as 3.1 (which can be configured by hand with two Proxmark3 commands if the config is open). After 2022 in Ukraine, equipment compatible with Vizit (Grazhda readers, Mriya panels) uses original NXP chips with the correct version, so ULtra copies may not work there.

### Filter 3: OTP

Page 3 of an Ultralight is OTP: zeros from factory, bits can only be set to 1, never back (see section 8.5.4 of the MF0ULX1 datasheet). In normal USCUID-UL tags it is freely rewritable. The reader tries to write zeros to this page and reads it back; if it changed, the tag is a copy, the reader restores the "original" value and rejects it. A genuine tag answers **NACK** and stops responding until the next SELECT, which is the correct state machine.

Other implementations had the same fault: Flipper Zero is correct after the NFC refactor, and Proxmark3 emulation had it until the author reported it ([issue 2790](https://github.com/RfidResearchGroup/proxmark3/issues/2790)) and it was fixed.

iKey's answer was the **UL-5** blank, writable once; after page 0 is changed it locks and behaves like an original. It ships from China with a non-Micron-Russia version. The author suspects it is a specially configured USCUID-UL. The same filter can also be passed on regular USCUID-UL (for example in ULtra configuration) by correctly changing the config block, if it is open.

## Takeaway for owners

Vizit RF 7.1 (Ultralight C) meets modern security standards and ends this cat-and-mouse game.

## Related

- [Iron Logic readers](/nfc/iron-logic) · [Magic cards](/nfc/magic-cards) · [Reading cards](/nfc/read)
