---
title: Reading cards
order: 10
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols]
sources: [flipper-docs, unleashed-src]
---
# Reading, saving and emulating NFC cards

`Read` is the main entry point of the NFC app. Flipper detects the protocol by itself, reads all data it can reach,
runs the key attacks where they apply (MIFARE Classic, Ultralight C, Ultralight AES, MIFARE Plus SL3) and then lets
you save, emulate or write the result.

## Read a card

1. Go to `Main Menu → NFC → Read`.
2. The screen says **"Reading — Hold card next to Flipper's back"**. Put the card flat against the **centre of the
   back** of the Flipper and keep it still.

   ![Reading screen: Hold card next to Flipper's back](/screens/nfc/reading.png)

3. When the card is found you'll see **"Don't move"** while the data is read. For protected cards an attack screen
   may appear (dictionary attack, nested attack, see [MIFARE Classic](/nfc/mifare-classic)).

   ![MIFARE Classic system dictionary attack: unlocking sector 9, 19 of 32 keys found](/screens/nfc/dict_attack.png)

4. The result screen shows the card name and a summary. If a [parser](/nfc/supported-cards) recognised the card, you
   see the decoded data (balance, number of trips, card number…).

   ![Read result: MIFARE Classic 1K with UID, 32/32 keys found and 16/16 sectors read](/screens/nfc/card_info.png)

   - <kbd>←</kbd> **Retry**: asks *"Retry Reading? All unsaved data will be lost"*.
   - <kbd>→</kbd> **More**: opens the card menu.
5. In **More**, choose **Save**, type a name in **"Name the card"** and confirm. The file goes to
   `/ext/nfc/<name>.nfc`.

The `More` menu after reading always has **Save** and **Info**; depending on the card type it also has
**Emulate** / **Emulate UID**, protocol-specific items (e.g. **Unlock**, **Show Keys**, **Extract MFC Keys**,
**Transactions** for EMV).

### Multi-protocol cards

Some cards answer as more than one protocol (for example a bank card that also contains a MIFARE Classic area).
Flipper then shows a **"Multi-protocol card"** menu with entries like **Read as MIFARE Classic**. To skip
auto-detection entirely use `Main Menu → NFC → Extra Actions → Read Specific Card Type`, pick the type and press
<kbd>OK</kbd>.

## Supported card types

| Family | Card types (as named by the firmware) | Read | Emulate | Write |
|---|---|---|---|---|
| ISO14443-3A (NFC-A) | Any NFC-A card: UID, ATQA, SAK | yes | UID only | — |
| MIFARE Classic | Mini, 1K, 4K (4- and 7-byte UID) | sectors with known keys | full | to the source card only |
| MIFARE Ultralight / NTAG | Ultralight, Ultralight 11/21 (EV1), Ultralight C, Ultralight AES, NTAG203/210/212/213/215/216, NTAG I2C 1K/2K, NTAG I2C Plus 1K/2K | open pages, more after unlock | full | same type (see below) |
| MIFARE Plus | Plus, S, X, SE, EV1, EV2; SL0–SL3 | SL1 as Classic, SL3 with AES keys | SL3 full, others UID | SL3 to the source card |
| MIFARE DESFire | DESFire | unprotected applications and files | UID only | — |
| ISO14443-4A | Unknown ISO-DEP cards | UID, ATQA, SAK, ATS | UID only | — |
| NTAG4xx, Type 4 Tag | NTAG 4xx DNA; NFC Forum Type 4 tags (NDEF) | yes | NTAG4xx: UID; T4T: full | T4T: yes |
| EMV | Bank cards | public data | — | — |
| ISO14443-3B / -4B | NFC-B cards | UID, app data, protocol info | — | — |
| ST25TB | ST25TB512, ST25TB512-AC, SRIX512, ST25TB02K, ST25TB04K, SRIX4K | yes | — | — |
| ISO15693-3 (NFC-V) | Unknown NFC-V tags | UID + readable blocks | full | yes |
| SLIX | ICODE SLIX, SLIX-S, SLIX-L, SLIX2 | yes, password unlock | full | yes |
| FeliCa | FeliCa (Lite-S and others) | IDm, PMm, blocks | full | — |
| Texkom | Texkom TK13, TK15, TK17, MMBIT intercom keys | yes | full | — |

::: tip Unleashed
**Texkom** keys (13.56 MHz intercom fobs common in Russia that implement no ISO standard), **MIFARE Plus SL3**
dumps with AES keys, **Ultralight AES** and the extended **Write** support for Ultralight are firmware additions you
won't find in stock firmware. MIFARE Classic also gets the CUID dictionary and **Save Keys to Dictionary**.
:::

### MIFARE Classic

To read sectors, Flipper needs the keys: up to **10 keys for 5 sectors** (Mini), **32 keys for 16 sectors** (1K) or
**80 keys for 40 sectors** (4K). It tries the per-card key cache, then the CUID, user and system dictionaries, then
nested attacks. The details are on the [MIFARE Classic](/nfc/mifare-classic) page; if keys are still missing, see
[MFKey32](/nfc/mfkey) and [Nested attacks](/nfc/nested-fudan).

### MIFARE Ultralight and NTAG

Open pages are read directly. Pages protected by a password (NTAG21x, Ultralight EV1), a 3DES key (Ultralight C) or
an AES key (Ultralight AES) stay locked until you unlock them, see [Unlocking cards](/nfc/unlock-with-password) and
[Ultralight AES](/nfc/ultralight-aes). Ultralight C and Ultralight AES run a dictionary attack automatically.

**Write** is offered for a fully read **NTAG213, NTAG215, NTAG216, Ultralight, Ultralight 11, Ultralight 21,
Ultralight C** and **Ultralight AES** dump, onto a card of the same type. Ultralight C and AES have two entries:
**Write (Keep Key)** keeps the target card's key, **Write (Copy Key)** also writes the key from the dump. If the
target is protected by a password, AUTH0 or lock bits, you get *"Card protected by password, AUTH0 or lock bits"*.

### Unknown cards

For an unknown NFC-A card only UID, ATQA and SAK are saved; for an unknown NFC-V tag the UID and the readable
blocks. Many simple access readers check only the UID, so **Emulate UID** may still work.

## Saved cards

`Main Menu → NFC → Saved` lists your `.nfc` files. The menu of a saved card contains (depending on type):

- **Emulate** or **Emulate UID**
- **Write** / **Write to Initial Card** (MIFARE Classic, MIFARE Plus SL3) / **Write (Keep Key)** + **Write (Copy Key)**
- **Edit UID** (NFC-A, ISO14443-4A, ISO15693)
- protocol items: **Unlock**, **Unlock with Dictionary**, **Extract MFC Keys**, **Update from Initial Card**,
  **Show Keys**, **Save Keys to Dictionary**, **Reveal Real UID**…
- **Restore to Original State** (only when a shadow file exists, see below)
- **Rename**, **Delete**, **Info**

## Emulating a card

1. Go to `Main Menu → NFC → Saved`, pick the card.
2. Select **Emulate** (full emulation) or **Emulate UID** (only UID/ATQA/SAK are sent).
3. The screen shows **Emulating** with the card name. Hold the back of the Flipper to the reader.
4. If the reader talked to the emulated card, a **Log** button (<kbd>OK</kbd>) appears that shows the exchange.
5. Press <kbd>←</kbd> to stop.

### Shadow files

When a reader writes to an emulated card (for example it updates a balance or a counter), Flipper does not change
your original file. It writes the new state into a **shadow file** next to it (`<name>.shd`). The original dump stays
intact:

- **Restore to Original State** (`Saved → card`): asks *"Restore Card Data?"* and deletes the shadow file.
- **Update from Initial Card** (MIFARE Classic, MIFARE Plus SL3): re-reads the physical card with the saved keys and
  refreshes the dump. Only the source card is accepted, otherwise *"Wrong Card! Data management is only possible
  with source card"*.

## If reading fails

- **Nothing is detected**: the card may be a 125 kHz card. Try `Main Menu → 125 kHz RFID → Read`
  (see the [RFID section](/rfid/read)).
- **Wrong type detected / hybrid card**: use `Extra Actions → Read Specific Card Type`.
- **"Lost the tag!"** during a long attack: put the card back in the same place, keep it still. Thick cases and
  metal behind the card disturb the field.
- **Not all sectors / pages read**: the card is protected. Continue with [MIFARE Classic](/nfc/mifare-classic),
  [MFKey32](/nfc/mfkey) or [Unlocking cards](/nfc/unlock-with-password).
- **"Plugin Not Loaded — Plugin file missing or outdated"**: the parser `.fal` files on the SD card don't match the
  firmware. Reinstall/update the firmware with the SD card inserted.

## Related

- [MIFARE Classic](/nfc/mifare-classic) · [Supported cards](/nfc/supported-cards) · [NFC file format](/nfc/file-format)
- [Magic cards](/nfc/magic-cards) · [NFC Magic 2.0](/nfc/nfc-magic)
