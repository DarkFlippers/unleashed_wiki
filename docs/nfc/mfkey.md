---
title: "MFKey32: keys from the reader"
order: 30
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, gromovyna]
---
# MFKey32: recovering keys from a reader

**MFKey32** is an attack on the Crypto-1 cipher of MIFARE Classic. Flipper pretends to be the card; the reader tries to
authenticate with its real key, and the two nonce/answer pairs it sends are enough to compute that key offline. The
attack therefore needs **access to the reader**, not to the keys.

Use it when:

- the card is read only partly and the missing keys are those the reader uses (most common case);
- you have no card at all but want to learn a reader's keys and add them to your dictionary;
- the card has no backdoor and no known key, so [nested attacks](/nfc/nested-fudan) cannot start.

## With the card and the reader (recommended)

Having the card means that after the reader's keys are recovered you can read more sectors, which is usually what
the reader actually checks.

1. Read the card (`Main Menu → NFC → Read`). It ends up partly read.
2. In **More** select **Extract MFC Keys**. Flipper asks *"Save the Key?"*: **Save** it (you'll need the dump later)
   or **Skip**.
   *Alternatively*, open an already saved card: `Main Menu → NFC → Saved → <card> → Extract MFC Keys`.
3. The screen shows **"Emulating... MIFARE MFkey32"** with the card UID and *"Touch the reader"*.

   ![Emulating MIFARE MFkey32 with the card UID, prompt to touch the reader](/screens/nfc/mfkey_start.png)

4. Tap the reader with the back of the Flipper, pull it away (*"Move the Flipper away"*), tap again
   (*"Touch the reader again"*). The counter **Nonce pairs: X/10** grows with each successful attempt.

   ![Collecting nonce pairs: 4 of 10 collected, prompt to move the Flipper away](/screens/nfc/mfkey_collecting.png)

5. When 10 pairs are collected the screen says **Completed!**. You can stop earlier with <kbd>OK</kbd> **Done**.
6. The next screen lists **Nonce pairs saved: N** and the **Authenticated sectors** (which sector and key type the
   reader asked for). Press <kbd>OK</kbd>.

   ![Nonce pairs saved: 5, with the list of authenticated sectors and key types](/screens/nfc/mfkey_nonces_info.png)

7. Flipper offers to recover the keys: **"Now run Mfkey32 to extract keys"** with **Run** (opens the
   [MFKey app](/nfc/mfkey-app)). If the app is missing it shows a QR code to `r.flipper.net/nfc-tools` and **Finish**.
8. Recover the keys with one of the tools below. They are added to the user dictionary.
9. Read the card again (or `Saved → <card> → Unlock with Dictionary`). More keys and sectors should now be found.
10. Emulate or write the card.

The nonces are stored in `/ext/nfc/.mfkey32.log`, one line per pair:
`Sec 1 key A cuid 2a234f80 nt0 ... nr0 ... ar0 ... nt1 ... nr1 ... ar1 ...`.

::: tip The counter doesn't grow?
The reader is not trying to authenticate the emulated card. Some readers check only the UID or use another protocol;
others reject the emulation outright. Try different distances and angles; sometimes several taps are needed for one
pair.
:::

## Only the reader

1. Go to `Main Menu → NFC → Extract MFC Keys`. Flipper emulates a generic MIFARE Classic card.
2. Steps 3–8 as above.
3. The recovered keys are in the user dictionary and will be tried automatically when you read cards for that system
   later.

## Recovering the keys from the nonces

| Tool | Where | Notes |
|---|---|---|
| **MFKey app** on the Flipper | `Main Menu → Apps → NFC → MFKey` | No phone/PC needed. Handles `.mfkey32.log` and `.nested.log`. Slower. See [MFKey app](/nfc/mfkey-app). |
| **qUnleashed** (Unleashed companion app) | `Tools → Recover MIFARE Keys` | Processes `.mfkey32.log` and `.nested.log`, including hard and static-encrypted nonces. Fast. See [qUnleashed](/nfc/qunleashed). |
| **Flipper Mobile App** | `Tools → Mfkey32 (Extract MF Keys)` | Official app, reader nonces only. |
| **Flipper Lab** | lab.flipper.net → **NFC tools** → **GIVE ME THE KEYS** | Over USB in the browser. |

::: tip Unleashed
In Unleashed the menu item is called **Extract MFC Keys** (stock: *Extract MF Keys*), and the companion app
**qUnleashed** can recover the keys directly on your phone or computer. Since **MFKey 4.x** (Unleashed dev build
1251+) recovery on the Flipper itself is several times faster, see [MFKey app](/nfc/mfkey-app).
:::

## If recovery fails

- **No keys found from the nonces**: the reader didn't accept Flipper's emulation properly. Collect again, try a
  different card dump (a saved real card works better than a generic emulation).
- **MFKey shows "No nonces found"**: neither `.mfkey32.log` nor `.nested.log` exists.
- **MFKey hangs or crashes**: reboot (hold <kbd>←</kbd> + <kbd>Back</kbd> for 5 seconds), delete
  `/ext/nfc/.mfkey32.log` / `/ext/nfc/.nested.log`, collect again.
- **Last resort**: back up and delete `/ext/nfc/assets/mf_classic_dict_user.nfc` (this removes **all** your user keys).

## Related

[MIFARE Classic](/nfc/mifare-classic) · [Nested attacks](/nfc/nested-fudan) · [MFKey app](/nfc/mfkey-app) ·
[qUnleashed](/nfc/qunleashed)
