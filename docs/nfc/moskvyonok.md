---
title: Moskvyonok cards
order: 130
author: gromovyna
original: [https://telegra.ph/Karty-braslety-brelki-Moskvyonok-i-s-chem-ih-kushat-12-16]
sources: [gromovyna]
---
# Moskvyonok cards, bracelets and fobs

How the Moscow student/child "Moskvyonok" cards are built and how to copy **your own** card to a more convenient form factor (bracelet, fob). Based on @gromovyna's article (2024-12-16), with technical help from @Aleksei_Pashaev and an anonymous Unleashed community member.

::: warning
Technical article; legal regulation varies. Use only your own cards, remember they resemble a payment instrument, and bear the consequences yourself.
:::

## How these systems defend against cloning

They barely do. The system uses **MIFARE Classic** with standard keys, no diversification, so the keys can be found with an ordinary dictionary. Copying is therefore a normal [MIFARE Classic read](/nfc/mifare-classic) plus a write to a [magic card](/nfc/magic-cards).

## Identify your card

| Type | UID | Block 0 | ATQA | SAK |
|---|---|---|---|---|
| 4-byte UID | 4 bytes | starts with the UID | `00 04` | `08` |
| 7-byte UID | 7 bytes | starts with the UID | `00 44` | `08` |
| 7-byte, personalised to 4 | 4 bytes | does not start with the UID, looks like nonsense | `00 44` | `08` |

### 4-byte UID

Standard tags, written as is. **Gen2 (CUID)** blanks recommended; cheaper **Gen1 (UID/Zero)** also work, though some reports say they were filtered.

### 7-byte UID

Newer tags, written as is to **Zero 7 bytes** blanks like ordinary Gen1 tags, including with Flipper Zero; or to USCUID-based tags with Chinese duplicators or Proxmark3 (understand the memory and config structure, or you can soft-brick the tag).

::: tip Unleashed
Writing Zero 7-byte blanks on Flipper Zero is available on Unleashed starting from version 079, or with an NFC Magic app built before the NFC refactor.
:::

### 7-byte UID personalised to 4 bytes

This is MIFARE Classic EV1 in **personalisation mode**: backward compatible mode where the card has a 7-byte ID but answers every SELECT with a 4-byte ID computed from it (datasheet MF1S50YYX_V1 section 10.1.1; algorithm in NXP AN10927, page 14). Writing as is gives garbage. A typical Moskvyonok block 0 begins `34 00...`, but this depends on the batch. On Proxmark3 the calculation is `analyse nuid`.

Copy to a 4-byte (CUID) blank:

1. Make a copy of the original dump.
2. Compute the new UID (example `3400060000DBDC` becomes `2FEDA2F1`).
3. Compute the BCC checksum byte (`2FEDA2F1` becomes `0x91`).
4. Rewrite block 0 of the copy as: computed 4-byte ID, BCC, `08`, `04`, `00`, rest unchanged (`2F ED A2 F1 91 08 04 00 FF FF FF FF FF FF FF FF`).
5. Change ATQA in the `.nfc` file header to `00 04` (most blanks have a fixed ATQA, but do it for correctness).
6. Write the dump to the blank.

USCUID-based tags can write the dump as is and emulate this behaviour, but that needs knowledge of the chip config and is not covered.

## Things that did not work

The team tried truncating high, low and middle UID bytes, reversed byte order and NUID from the 7 bytes against 7-byte systems; none succeeded.

## Related

- [MIFARE Classic](/nfc/mifare-classic) · [Magic cards](/nfc/magic-cards) · [Reading cards](/nfc/read)
