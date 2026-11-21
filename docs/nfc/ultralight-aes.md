---
title: MIFARE Ultralight AES
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_QA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_SecureMessaging_QA.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_ultralight]
sources: [unleashed-docs, unleashed-src]
---
# MIFARE Ultralight AES (MF0AES20)

**MIFARE Ultralight AES** is an Ultralight with **AES-128** mutual authentication instead of a password (NTAG21x) or
3DES (Ultralight C). It has 60 pages, three one-way counters, a 48-byte ECC originality signature, an optional
**Random ID** mode and optional **secure messaging** (every command and answer protected by a CMAC).

::: tip Unleashed
Ultralight AES support (read, dictionary attack, manual key entry, emulation, write-back, config decoding, Random ID,
secure messaging) is an Unleashed feature, validated on a real MF0AES20 card against Proxmark3 ground truth.
:::

## What Flipper does with it

| Feature | Details |
|---|---|
| Identify and read | Detected as `Mifare Ultralight AES`, ATQA `0044`, SAK `00`, `60/60` pages on an open card, counters. |
| Originality signature | Saved in the `.nfc` file as an `AES signature:` line (48 bytes) and replayed during emulation, so a reader's signature check passes. |
| AES authentication | 3-pass AES challenge-response, then protected pages are read. |
| Dictionary attack | Runs automatically on an incomplete read: **MFUL AES User Dictionary**, then **MFUL AES System Dictionary**. |
| Manual key | `Saved → <card> → Unlock` → **"Enter key in hex"** (16 bytes) → confirm **Unlock**. |
| Key management | `NFC → Extra Actions → MIFARE UL AES Keys` → **Add** / **List**. |
| Write-back | **Write (Keep Key)** / **Write (Copy Key)** on a fully read dump. |
| Emulation | Full, including AES auth as a card, AUTH0 gate and secure messaging. |
| Config decoding | `Info` shows a **UL-AES Config** block (see below). |
| Random ID | Detected and shown (`Random ID: on`); **Reveal Real UID** tries to recover the real UID. |

Dictionaries: system `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` (factory all-zero key, `BREAKMEIFYOUCAN!` reused as
AES, and other common defaults from Proxmark3), user `/ext/nfc/assets/mf_ultralight_aes_dict_user.nfc`. A factory card
uses the all-zero key `00000000000000000000000000000000` for both the DataProtKey and the UIDRetrKey.

## Reading a protected card

1. `Main Menu → NFC → Read`, hold the card.
2. Open pages are read; if the card has an AES-protected region, the dictionary attack starts on its own (user
   dictionary first, then system).
3. If a key works, all pages are read and the key is shown and saved with the dump. If not, you get a partial read
   (e.g. `42/60` pages) and **"AES-protected pages!"**, without hanging or using up attempts on an unlimited card.
4. Save the card. Later you can retry with **Unlock with Dictionary** (after adding keys) or **Unlock** (manual key).

::: warning Byte order of the key
Raw page writes (e.g. Proxmark3 `hf mfu wrbl`) store the key in **tag-memory order**; the AES engine, the Flipper's
manual entry and PM3 `hf mfu aesauth --key` use the **reverse** order. A card whose pages `0x30–0x33` read
`A0A1A2A3 A4A5A6A7 A8A9AAAB ACADAEAF` authenticates with `AFAEADACABAAA9A8A7A6A5A4A3A2A1A0`. Enter a manually
recovered key **in AES order**. In the saved `.nfc` the key pages (`Page 48`–`51`) are stored in tag-memory order so they
can be written back verbatim; the `DataProtKey:` line on screen is only a rendering.
:::

## Memory and configuration

| Item | Location |
|---|---|
| DataProtKey | pages `0x30`–`0x33` |
| UIDRetrKey | pages `0x34`–`0x37` |
| CFG | page `0x29`: byte 0 bit0 = `RID_ACT`, bit1 = `SEC_MSG_ACT`; byte 3 = `AUTH0` |
| ACCESS | page `0x2A`: byte 0 bit2 = `CNT_RD_EN`, bit3 = `CNT_INC_EN`, bit6 = `CFGLCK`, bit7 = `PROT`; bytes 2–3 = `AUTH_LIM` |
| LOCK_KEYS | page `0x2D`: byte 0 = per-key lock bits |

The **UL-AES Config** block in `Info` decodes these, e.g.:

- `Auth from: off (open)` or `Auth from: page 0x10 (r+w)` / `(write)`: `AUTH0` and `PROT`;
- `Auth limit: unlimited` or `Auth limit: N (locks!)`;
- `Counter 2: rd open / inc auth` and similar;
- `Random ID: on/off`, `Secure msg: on/off`, `User cfg: open/locked`, `Key lock: DP N / UID N`;
- `Real UID:` once revealed.

::: danger Don't experiment with these bits
`CFGLCK` locks the configuration **permanently**, `AUTH_LIM` arms a lock-out after failed authentications, and the
`LOCK_KEYS` / static lock bytes can brick the card. Never change them on a card you care about. Note also that PM3's
`hf mfu info` labels pages `0x34`–`0x37` of MF0AES20 with a legacy Ultralight template (`cfg0/cfg1/PWD/PACK`); trust
the table above.
:::

## Writing a dump back

Offered only on a **fully read** Ultralight AES dump, as two items:

- **Write (Keep Key)**: writes data pages `0x04`–`0x27`; the target's key stays.
- **Write (Copy Key)**: data pages plus the **DataProtKey** (`0x30`–`0x33`) from the dump.

Rules built into the firmware:

- The write **authenticates to the target first** with a dictionary key, so the target's *current* key must be in a
  dictionary (the factory all-zero key is).
- Config/lock pages `0x28`–`0x2F` are **never** written; the UIDRetrKey (`0x34`–`0x37`) is never written.
- The target must be of the same **type**; the UID doesn't have to match.

## Emulation

`Saved → <card> → Emulate`. The emulated card answers GET_VERSION, the signature, the counters and the config like the
real one, performs AES authentication as a card using `reverse(pages 0x30–0x33)` as the key, rejects wrong keys and
enforces `AUTH0`. Note: restricted reads without authentication return rolled-over early-page data instead of a NAK.

## Random ID

With `RID_ACT` set, the card presents a **random 4-byte UID starting with `08`** at every selection; the real 7-byte
UID is hidden until an authenticated read. Flipper shows the random UID and `Random ID: on`. For such cards the menu
has **Reveal Real UID**: it confirms with a warning, re-reads the card and tries to authenticate (default all-zero
UIDRetrKey) to reveal the static UID, shown as `Real UID:` in the config view.

## Secure messaging (CMAC)

With `SEC_MSG_ACT` set, once authenticated **every** command and response must carry a CMAC. Flipper handles this
adaptively: after authentication the first plain `READ`/`WRITE` fails (real silicon simply mutes, which the reader
sees as a timeout), the firmware re-authenticates and switches to MAC-wrapped `READ`, `READ_CNT` and `WRITE`. The
command counter advances by 2 per exchange (command uses `CmdCtr`, response `CmdCtr+1`). Validated on hardware: a full
60/60 read over CMAC with no MAC mismatches, counters over CMAC, key pages `0x30`–`0x37` masked to zero in the dump,
and a CMAC write-back of data pages.

The emulator also speaks secure messaging: it verifies the command MAC, MAC-wraps every answer, replaces the `WRITE`
ACK with a MAC, and drops the session on a bad MAC.

::: warning Recoverability
Once `SEC_MSG_ACT` is on, config writes in a protected region need a CMAC-authenticated write, which Proxmark3 can't
do and the Flipper's Write skips (config pages are never written). Don't set `AUTH0 ≤ 0x29` on a secure-messaging
card or you may be unable to turn it off again.
:::

### Debug markers

With `Settings → System → Log Level → Debug` you can follow what happens in the log, for example
`UL-AES: plain read failed post-auth, switching to secure messaging`, `UL-AES response MAC mismatch (ctr N)` (should
not appear in a healthy run), `UL-AES command MAC mismatch, dropping session` (emulator side).

## Related

[Unlocking cards](/nfc/unlock-with-password) · [Reading cards](/nfc/read) · [NFC file format](/nfc/file-format) ·
[Adding cards manually](/nfc/add-manually)
