---
title: Unlocking cards with passwords
order: 65
original: [https://docs.flipper.net/zero/nfc/unlock-with-password, https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [flipper-docs, unleashed-src]
---
# Unlocking cards with passwords and keys

Cards organised in **pages** (MIFARE Ultralight, NTAG) can protect part of their memory. If `Read` shows
**"Some Pages Are Locked!"** / **"Password-protected pages!"** and `Pages Read: X/Y` with X < Y, the card needs a
password or key. Depending on the card:

| Card | Protection | How Flipper unlocks it |
|---|---|---|
| NTAG21x, Ultralight EV1 (11/21) | 4-byte password (PWD) + 2-byte PACK | capture from the reader, generate from UID (amiibo, Xiaomi), or enter manually |
| Ultralight C | 16-byte 3DES key | dictionary attack (automatic) or enter key manually |
| Ultralight AES | 16-byte AES key | dictionary attack (automatic) or enter key manually, see [Ultralight AES](/nfc/ultralight-aes) |
| ICODE SLIX-L | 4-byte password | `Extra Actions → Unlock SLIX-L` |

::: danger Wrong passwords can lock the card
Many cards count failed authentications (`AUTHLIM`) and lock themselves permanently after too many. Flipper warns
with **"Risky action! Wrong password can block your card."** before trying a password. Don't brute force.
:::

## Capture the password from the reader

If you have the card and the reader that accepts it: emulate the card, let the reader send its password, capture it,
then read the card with it.

1. [Read and save](/nfc/read) the card.
2. Go to `Main Menu → NFC → Saved → <card> → Unlock`.
3. Select **Unlock With Reader**. The screen says *"Touch the reader to get password..."*. Tap the reader with the
   Flipper.
4. When the password is captured you see **Password Captured!** with its value. Press **Continue**.
5. Hold the card to the back of the Flipper (*"Hold card next to Flipper's back"*, then *"Don't move"*).
6. When the pages are unlocked (**"All Pages Are Unlocked!"**), go to **More → Save**, name the card and save.

If nothing is captured (*"Password not captured."*), the reader may not use a password, or the card belongs to another
reader.

`Unlock With Reader` is not offered for Ultralight C (it uses 3DES mutual authentication, no password is sent in
clear).

## Generate the password from the UID

For **toys-to-life** figures (amiibo-style NTAG215) and **Xiaomi Air Purifier** filters, the password is derived from
the card's UID.

1. Go to `Main Menu → NFC → Extra Actions → Unlock NTAG/Ultralight`
   (or, for a saved card, `Saved → <card> → Unlock`).
2. Select **Auth As Ameebo** or **Auth As Xiaomi Air Purifier**.
3. Confirm the warning and hold the card to the Flipper.
4. When the pages are unlocked, **Save** the card.

## Enter the password manually

1. `Main Menu → NFC → Saved → <card> → Unlock` (or `Extra Actions → Unlock NTAG/Ultralight` before reading).
2. Select **Enter Password Manually**.
3. **"Enter the password in hex"**: type the 4 bytes, confirm.
4. Confirm the *"Try to unlock the card with password: …"* warning and hold the card to the Flipper.
5. **Save** the unlocked card.

## Ultralight C: 3DES keys

Ultralight C cards use a 16-byte 3DES key. Flipper has a built-in dictionary of known keys
(`/ext/nfc/assets/mf_ultralight_c_dict.nfc`, 50 keys, including the NXP sample key `BREAKMEIFYOUCAN!`) and a user
dictionary (`mf_ultralight_c_dict_user.nfc`).

- On `Read`, if the card isn't fully readable, the dictionary attack runs by itself: headers
  **"MFUL C User Dictionary"**, then **"MFUL C System Dictionary"**, with `Key found: Yes/No` and `Pages read: X/Y`.
- On a saved, incomplete card: **Unlock with Dictionary** reruns the attack; **Unlock** asks **"Enter key in hex"**
  (16 bytes) and then **"Risky Action! Unlock with key: … ?"** with **Unlock** / **Cancel**.
- Add your own keys: `Main Menu → NFC → Extra Actions → MIFARE Ultralight C Keys → Add`.

A fully read Ultralight C dump offers **Write (Keep Key)** (keeps the target card's 3DES key) and **Write (Copy Key)**
(also writes the key pages from the dump) to a card of the same type.

::: tip Unleashed
Manual 3DES/AES key entry, Ultralight C/AES write-back with Keep/Copy Key, and the Ultralight AES dictionary
(`Extra Actions → MIFARE UL AES Keys`) are Unleashed features.
:::

## ICODE SLIX-L

1. Go to `Main Menu → NFC → Extra Actions → Unlock SLIX-L`.
2. Choose **Enter Password Manually** (4 bytes in hex) or **Auth As TommyBox** (the known password of TommyBox tags).
3. Hold the tag to the Flipper (*"Unlocking — Hold card next to Flipper's back"*).
4. On **SLIX Unlocked!** press **More** to continue to the read result and save it, or **Retry**.

## If unlocking failed

- The card may be paired with a different reader, or use a key derived per card.
- The password is correct but some pages stay locked: lock bits or `AUTH0`/`PROT` settings can make pages permanently
  read-only or unreadable without auth.
- For Ultralight AES see the byte-order note on [Ultralight AES](/nfc/ultralight-aes).

## Related

[Reading cards](/nfc/read) · [Ultralight AES](/nfc/ultralight-aes) · [Vizit reader filters](/nfc/vizit-filters) ·
[NFC file format](/nfc/file-format)
