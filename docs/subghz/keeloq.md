---
title: KeeLoq
order: 70
author: gromovyna
original: [https://blog.li0ard.rest/wtfiskeeloq, https://t.me/gromovyna/24, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [li0ard, gromovyna, unleashed-docs, unleashed-src]
---
# KeeLoq

KeeLoq is the cipher behind a huge number of gate, garage-door and barrier remotes (DoorHan, Nice Smilo, FAAC RC,
BFT, Came Space, Beninca, Hormann EcoStar…) and older car alarms. This page explains how it works, what
"manufacturer keys" and "seeds" are, and how Unleashed handles them.

The theory part is based on the article **"KeeLoq и с чем его едят"** by [@li0ard](https://blog.li0ard.rest/wtfiskeeloq),
a member of @gromovyna's research team, recommended in [his channel](https://t.me/gromovyna/24) to anyone who
wants to understand this cipher.

## What KeeLoq is

KeeLoq is a block cipher based on an NLFSR (non-linear feedback shift register), designed by Nanoteq Pty Ltd. and
sold to Microchip Technology Inc. It encrypts **32-bit blocks** with a **64-bit key** in **528 rounds**. It
implements *code hopping*: every transmission is a unique packet.

### Packet structure

A 64-bit KeeLoq packet, e.g. `239B3DEBF16C47A6`, consists of:

- **Fix** (first 4 bytes, `239B3DEB`) — sent in clear: the button ID (`2`) and the 28-bit serial number of the
  remote (`39B3DEB`).
- **Hop** (last 4 bytes, `F16C47A6`) — encrypted with the manufacturer key. Decrypted it looks like `21EB000A`:
  the button ID again (`2`), 12 bits of discrimination data (often `serial & 0x3FF`) and the **16-bit counter**
  (`000A`).

![KeeLoq packet structure](/img/remote/167cc7293a53adb1.png)

That's what the Flipper shows after a [Read](/subghz/read): `Fix`, `Hop`, `Btn`, `Cnt`, and the manufacturer name.

### Counter logic

- Counter equals the value the receiver expects → command executed.
- Counter is **higher** than the stored one → the receiver resyncs to it and works normally from the next press.
- Counter is **lower** → ignored; some receivers unpair the remote after several "stale" values. *That is the real
  danger when experimenting with KeeLoq.* See [Rolling codes](/subghz/rolling-codes).

## Learning modes (key derivation)

The key that actually encrypts the hop is derived from a **manufacturer key** (64 bit, the same for all remotes of
a brand/model line). The standard defines three modes:

| Mode | How the per-remote key is made |
|---|---|
| **Simple learning** | the manufacturer key is used as-is (weakest) |
| **Normal learning** | the manufacturer key is mixed with the remote's serial number |
| **Secure learning** | uses an extra value — the **seed** — unique per remote and transmitted only when pairing (strongest standard mode) |

Manufacturers also invent their own, e.g. **Magic XOR Type-1** (Beninca: serial XOR manufacturer key) or
**FAAC SLH (SPA)** — a series of bit operations and encryptions, the most thought-out of them in li0ard's opinion.

::: tip Unleashed
Unleashed implements all standard modes plus many vendor ones (`lib/subghz/protocols/keeloq_common.h`):
Simple, Normal, Secure, Magic XOR type 1, FAAC, Magic Serial types 1–3, KingGates, Jarolift, Erreka, Pujol,
AERF, JCM, JCM Gen2, Stagnoli and the table-driven Telcoma learning. 100+ manufacturers are listed in
[Supported systems](/subghz/supported-systems).
:::

## Manufacturer keys in Unleashed

To decode a KeeLoq signal the Flipper must know the manufacturer key. Unleashed ships them in an
**encrypted** keystore on the SD card:

| File | Purpose |
|---|---|
| `/ext/subghz/assets/keeloq_mfcodes` | built-in keys, encrypted (`Encryption: 1`), updated with the firmware |
| `/ext/subghz/assets/keeloq_mfcodes_user` | **your own** keys, plain text (create it from `keeloq_mfcodes_user.example`) |

When a signal is decoded, every key is tried; on success the name appears as `KL: DoorHan`, `KL: Nice_Smilo` etc.
Half-rate KeeLoq remotes also display their real manufacturer name (instead of `Crypt Key`), marked as `KL HR` in the
read list and `66b HR` in signal info. If no key fits, the signal shows as **`KL: Unknown`**: it can be saved, but
not sent or used to generate the next code. The `subghz` CLI commands that decode signals print
`Load_keystore keeloq_mfcodes OK` and `Load_keystore keeloq_mfcodes_user OK` / `Absent` when they start — a quick way
to check the keystores load.

### User key file format

```text
# AABBCCDDEEFFAABB:X:NAME
# AABBCCDDEEFFAABB - manufacture key, 64 bit
# X - learning type: 1 - Simple, 2 - Normal, 3 - Secure, 4 - Magic_xor_type1,
#     5 - FAAC SLH, 6 - Magic Serial typ1, 7 - Magic Serial typ2, 8 - Magic Serial typ3,
#     0 - iterates over both previous and man in direct and reverse byte sequence
# NAME - name (no spaces), max 64 characters
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:1:Test2
```

Keep an empty line at the end of the file. The `_user` file is not overwritten by updates.

### The `Manufacture` and `Seed` fields

A saved KeeLoq `.sub` stores the manufacturer by name:

```text
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: DoorHan
```

Secure-learning systems also store `Seed: XX XX XX XX`. Adding `Seed` + `Manufacture` lines by hand to a file that
reads as `KL: Unknown` makes it decodable (see BFT/Erreka below).

## Seeds: BFT Mitto, Erreka, FAAC SLH, Genius

These systems use a per-remote (or per-installation) **seed**; without it the signal reads as `KL: Unknown` (or
doesn't decode) and no accepted remote can be built.

- **BFT Mitto** — newer remotes derive the seed from the serial and decode straight away in Read (`KL: BFT`).
  Older ones have a unique seed. Put the original in programming mode (pin hole on the back or buttons 1+2): it
  sends a packet whose `Fix` starts with `F`; that packet's **`Hop` is the seed** in clear.
- **Erreka IRIS** — bridge pins `1` and `5` of the 5-way connector on the side: again `Fix` starts with `F` and
  `Hop` is the seed. Some installations give **every** remote the same seed — then a new remote must reuse it.
- **FAAC SLH / Genius** — read the seed from a **master** remote in programming mode; the seed differs **per
  button**.
- No programming button available? Use the **[Seed Capturer](/subghz/seed-capturer)** app: it collects consecutive
  Fix/Hop pairs and the seed is recovered in the qUnleashed companion app.

With the seed, create the remote in `Sub-GHz → Add Manually [Advanced]` (SERIAL → BUTTON → COUNTER → SEED), see
[Add Manually](/subghz/add-manually) and [remote programming](/subghz/remote-prog).

## Known attacks (overview)

From li0ard's article, for understanding — not instructions.

**Theoretical:** slide attack (~2³² plaintext/ciphertext pairs, yields the first 32 key bits), correlation
approach (exploits a 5/8 bias of the NLFSR), linear step (last 16 key bits once the rest are known). Total
complexity ≈ 2⁵².

**Practical** (thanks to Derek Jamison's materials, "SubGHz Rolling Flaws"):

| Attack | Idea |
|---|---|
| Replay | resend a captured packet; works on static codes and on receivers that don't check the counter |
| Remote cloning | with the manufacturer key a working copy can be made — but it conflicts with the original's counter and may get it unpaired |
| Future | send a far-ahead counter (`0001` → `3E91`); the receiver resyncs, the original is desynced |
| Rollback | roll the counter back after some uses; rare receivers resync to old values |
| RollJam | record while jamming the receiver, use later. **Jamming is illegal** in almost all countries |
| Manufacturer-key (KGB) | the receiver may accept several manufacturer keys; send the original fix with a counter encrypted by another key |
| Enc00 | swap the fix for another paired remote's fix and use the original hop; the other remote gets desynced |
| Unknown | when a receiver can't decode the hop it uses 0; universal receivers may open on 0 |

Despite all this, KeeLoq — like Mifare Classic with its broken Crypto-1 — remains popular in budget access
systems; some vendors (Beninca, Hormann) have moved to AES.

::: warning
Experiment only with your own remotes and receivers. A desynced or unpaired remote may need re-registration at the
receiver.
:::

## Troubleshooting

- **`KL: Unknown`** — no matching key. Check the modulation, update the firmware (new keys), or add a key to
  `keeloq_mfcodes_user` if you legitimately own it. For seed systems, recover the seed.
- **Decodes but the receiver ignores the Flipper** — you are sending a clone; see [Rolling codes](/subghz/rolling-codes)
  and [Counter modes](/subghz/counter-mode).
- **`Function requires an SD card with fresh databases.`** in Add Manually — the keystore is missing; reinstall
  the firmware with the SD card in place.

## Related

- [Supported systems](/subghz/supported-systems) · [Add Manually](/subghz/add-manually)
- [Seed Capturer](/subghz/seed-capturer) · [Remote programming](/subghz/remote-prog)
- [Counter modes](/subghz/counter-mode) · [.sub file format](/subghz/file-format)
