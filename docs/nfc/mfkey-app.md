---
title: The MFKey app
order: 40
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/mfkey, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://t.me/gromovyna/27, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, gromovyna, flipper-docs, unleashed-readme]
---
# The MFKey app (MFKey 4.1)

**MFKey** (by [@noproto](https://github.com/noproto)) recovers MIFARE Classic keys **on the Flipper itself** from
nonces collected by the NFC app: reader nonces (MFKey32) and card nonces from the nested attacks. It's the tool for
when you have no phone or PC at hand; it's slower than [qUnleashed](/nfc/qunleashed), but it works anywhere, even in
your pocket.

| | |
|---|---|
| Location | `Main Menu → Apps → NFC → MFKey` (`/ext/apps/NFC/mfkey.fap`) |
| Version in Unleashed | **4.1** |
| Inputs | `/ext/nfc/.mfkey32.log` (reader nonces), `/ext/nfc/.nested.log` (card nonces) |
| Output | `/ext/nfc/assets/mf_classic_dict_user.nfc` (keys), `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` (SEN candidates) |

## Usage

1. Collect nonces first:
   - from a reader: [MFKey32](/nfc/mfkey) (`Extract MFC Keys`);
   - from the card: [nested attacks](/nfc/nested-fudan) during `NFC → Read`.
2. Open `Main Menu → Apps → NFC → MFKey`, or press **Run** on the *"Now run Mfkey32 to extract keys"* screen in the NFC
   app (it appears after `Extract MFC Keys` and after `Crack nonces in MFKey32`).
3. The screen says **Ready**. <kbd>→</kbd> **Help** shows *"Collect nonces by reading tag or reader in NFC app"*.
   Press <kbd>OK</kbd> **Start**.
4. First MFKey checks the nonces against the existing dictionaries: **Dict solves: N (in progress)**,
   **Keys in dict: N**. Nonces whose key is already known are skipped.
5. Then the attack runs with three progress bars: **Cracking: X/Y**, **Round: X/Y – ETA NN Sec** and
   **Total ETA NNN Sec**. The **RAM** line at the top shows the free heap.
6. When finished you hear a beep and see **Complete**, **Keys added to user dict: N** and, for static encrypted nonces,
   **SEN key candidates: N**.
7. Go back to the NFC app and read the card again (or `Saved → <card> → Unlock with Dictionary`).

<kbd>←</kbd> stops the work and exits (the thread is stopped cleanly; keys found so far are still written).

### Errors

| Screen | Meaning |
|---|---|
| **No nonces found** | Neither `.mfkey32.log` nor `.nested.log` exists. Collect nonces first. Also shown for HardNested-only tags: their nonces can't be cracked on the Flipper. |
| **Nonces already cracked** | Every nonce in the logs is already solved by a key in your dictionaries. |
| **No free RAM** | Not enough memory. Reboot the Flipper and try again; close other apps. |

## What MFKey 4.x changed

From @gromovyna's article "MFKey 4.1 — faster, higher, stronger": the new major version arrived rather quietly,
yet it is a big speed-up. It's available in **Unleashed dev builds from 1251**. (At the time of the article the app
changes were merged in official firmware too, but the firmware-side changes it needs were not.) Thanks to
@noproto and team.

Below, **SEN** = static encrypted nonce (see [Nested attacks](/nfc/nested-fudan)).

**4.0**

- Support for the new SEN dictionary format: key recovery is **10× faster**.
- The old SEN dictionary format is no longer supported.

**4.1**

- Key recovery another **40% faster**; better memory efficiency.
- The monolithic `mfkey.c` split into modules: `mfkey_batch_prelude`, `mfkey_state_expansion`, `mfkey_bs_verify`,
  `mfkey_recovery`, `mfkey_dedup`.
- 32 candidates verified in parallel via SWAR (bit operations instead of one-by-one checks).
- A precomputed 2 KB "Super-LUT" for rounds 0–3: one indexed load per round instead of computation.
- Radix sort O(n) instead of quicksort; deduplication via Fibonacci hashing instead of a naive scan.
- The M4 FPU registers are used as extra scratch space (`vmov`), reducing register pressure.
- An 8× unrolled Duff's-device loop when scanning for duplicates.

### Real-world timings

The author tested the hardest case: a tag with **static encrypted nonces**. For such tags the computed keys are not
verified on the fly and don't go straight to the user dictionary; instead a dictionary of **candidates** is built
that must later be checked against the tag. So **all** keys that could produce a nonce are extracted, the biggest
dictionary, the longest scenario. Not a single *Out Of Memory* during the tests.

| Test | Setup | Result |
|---|---|---|
| Iron Logic key | Tag encrypted with an [Iron Logic](/nfc/iron-logic) object card; no key in the dictionary, attacked via the backdoor; **18 unique keys over 32 sectors** | Full cycle **6 h 8 min**, more than **1.2 million candidates**; then several more hours checking candidates on the tag. |
| 1 sector, 2 keys | Same tag (wiped), sector 0 encrypted with random different keys A and B | **17 minutes**; candidate check on one sector was quick as well. |

For comparison, recovering the first test on a Proxmark3 with a computer took 24 seconds, so the Flipper will never
compete with that. But if you're travelling or just have time for background work, the Flipper in your pocket can
recover the keys and emulate the tag. And since mostly Iron Logic-like systems love key diversification, the chance
of hitting the longest scenario is relatively small.

::: tip Unleashed
Unleashed includes MFKey 4.1 with the firmware-side changes it needs (the CUID dictionary in `Read`, with a progress
bar while it loads). After MFKey finishes on a SEN tag, use **Save Keys to Dictionary** on the fully read dump to copy
the recovered keys into your user dictionary, see [MIFARE Classic](/nfc/mifare-classic#save-keys-to-dictionary).
:::

## Tips

- Clean `/ext/nfc/.nested.log` and `/ext/nfc/.mfkey32.log` after successful recovery: old nonces are re-checked on
  every start.
- If you installed apps separately, make sure an old `mfkey.fap` didn't overwrite the one from the firmware.
- Much faster alternatives: [qUnleashed](/nfc/qunleashed) on a phone/PC, or the
  [mfkey_desktop_cli](https://github.com/phntm-lab/mfkey_desktop_cli) project.

## Related

[MFKey32](/nfc/mfkey) · [Nested attacks](/nfc/nested-fudan) · [qUnleashed](/nfc/qunleashed) ·
[MIFARE Classic](/nfc/mifare-classic)
