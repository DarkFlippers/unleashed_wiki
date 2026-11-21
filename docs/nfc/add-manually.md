---
title: Adding cards manually
order: 60
original: [https://docs.flipper.net/zero/nfc/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Adding NFC cards manually

`Add Manually` creates a virtual card without reading one. Two use cases:

- **Generate a card of a standard type** with a random UID and default (blank) contents, as if you had a fresh
  physical card. Then emulate it to "enroll" it in an access system or let a phone write NDEF data (a link, a vCard)
  onto it.
- **Create an NFC-A card from known values**: UID, ATQA and SAK. Enough for simple systems that only check the UID.

## Generate a card of a standard type

1. Go to `Main Menu → NFC → Add Manually`.
2. Pick the card type (list below).

   ![Add Manually: card type list with NFC-A 7-bytes UID selected](/screens/nfc/add_manually.png)

3. A screen with the generated **UID** opens. Press <kbd>→</kbd> **More**.
4. In the menu choose **Save** (you may also **Change UID** first, or **Emulate** right away).
5. Enter a name and confirm. The card is saved to `/ext/nfc/`.

Available types (exact names as in the menu):

| Group | Types |
|---|---|
| Ultralight | Mifare Ultralight, Mifare Ultralight EV1 11, Mifare Ultralight EV1 H11, Mifare Ultralight EV1 21, Mifare Ultralight EV1 H21, Mifare Ultralight C, Mifare Ultralight AES |
| NTAG | NTAG203, NTAG213, NTAG215, NTAG216, NTAG I2C 1k, NTAG I2C 2k, NTAG I2C Plus 1k, NTAG I2C Plus 2k |
| MIFARE Classic | Mifare Mini, Mifare Classic 1k 4byte UID, Mifare Classic 1k 7byte UID, Mifare Classic 4k 4byte UID, Mifare Classic 4k 7byte UID |
| MIFARE Plus | Mifare Plus SE 4byte / 7byte UID; Mifare Plus S 2K / 4K, 4byte / 7byte UID; Mifare Plus X 2K / 4K, 4byte / 7byte UID; Mifare Plus EV1 2K / 4K, 4b. / 7b. UID; Mifare Plus EV2 2K / 4K, 4b. / 7b. UID |
| Texkom | Texkom TK13, Texkom TK17, Texkom MMBIT |

::: tip Unleashed
Stock firmware generates only Ultralight/NTAG and MIFARE Classic. Unleashed adds **Mifare Ultralight C** (with the
default 3DES key `BREAKMEIFYOUCAN!`), **Mifare Ultralight AES**, all **MIFARE Plus** variants, the **Texkom**
intercom keys, and **Change UID** right after generation, so a MIFARE Classic with a custom UID can be created
("NFC Add manually → Mifare Classic with custom UID" in the ReadMe).
:::

::: tip Which type for a phone?
To write a link or business card from a phone, **NTAG216** works in most cases. Check what your app or system expects.
:::

## Create an NFC-A card from UID, ATQA and SAK

Some access systems grant access by UID (sometimes with ATQA/SAK). If you know these values:

1. Go to `Main Menu → NFC → Add Manually`.
2. Select **NFC-A 7-bytes UID** or **NFC-A 4-bytes UID**.
3. **"Enter SAK in hex"**: type the SAK (1 byte), confirm.
4. **"Enter ATQA in hex"**: type the ATQA (2 bytes), confirm.
5. **"Enter UID in hex"**: type the UID, confirm.
6. Name the card and save.

Typical values: MIFARE Classic 1K: ATQA `00 04` (4-byte UID) or `00 44` (7-byte), SAK `08`; Ultralight/NTAG:
ATQA `00 44`, SAK `00`. Byte input tip: press <kbd>↑</kbd> repeatedly until the nibble editor appears (Unleashed).

## Using the card

- **Emulate**: `Main Menu → NFC → Saved → <card> → Emulate` (or **Emulate UID** for an NFC-A card) and hold the
  Flipper to the reader. To "program" a virtual key into an access system, put the system in enrollment mode
  according to its manual and present the emulated card.
- **Edit UID** later: `Saved → <card> → Edit UID` (NFC-A cards).

::: warning
Different access systems and apps enroll cards in different ways; check their documentation for supported card types.
A virtual card can't help with systems that verify the card's cryptography (DESFire, Plus SL3 with unknown keys, EMV).
:::

## Related

[Reading cards](/nfc/read) · [NFC file format](/nfc/file-format) · [Magic cards](/nfc/magic-cards)
