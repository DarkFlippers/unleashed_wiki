---
title: Seed Capturer
order: 190
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/seed_capturer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Seed Capturer

**FAAC SLH**, **Genius**, **Erreka** and **BFT Mitto** build their rolling code from a secret **Seed**. Without it the Flipper cannot decode these remotes (they read as `KL: Unknown` or not at all) and cannot build a remote the receiver accepts. **Seed Capturer** (by @xMasterX) collects the raw material for recovering the Seed: the remote's `Fix` and a run of consecutive `Hop` values.

It does **not** recover the Seed itself and it **never transmits** — it only listens and writes a file. The search runs in the [qUnleashed](/mobile/qunleashed-app) companion app.

::: tip Unleashed
Seed Capturer is a built-in Unleashed system app, and qUnleashed reads its captures straight off the Flipper. Once the Seed is known, Unleashed can decode the remote and create new ones via `Add Manually [Advanced]`.
:::

## When you need it

- The receiver's radio programming is disabled, so the only way in is a clone of a known remote — and a clone needs the Seed.
- Your FAAC / Genius remote is a **slave**, which cannot send the programming code.
- You cannot reach the receiver.
- **Erreka** installations where every remote shares one Seed.
- **Older BFT Mitto** remotes with a unique Seed when the programming button route does not work (newer BFT remotes derive the Seed from the serial and decode in a normal Read).

If the remote can be put into programming mode, the Seed is often sent in the clear — that route is faster; see [Programming a new remote](/subghz/remote-prog).

## Capturing

1. Open `Main Menu → Apps → Sub-GHz → Seed Capturer`.
2. Choose `New capture`.
3. **Remote type:** `FAAC SLH`, `Genius`, `Erreka` or `BFT Mitto`.
4. **Frequency:** `433.92 MHz  AM650` or `868.35 MHz  AM650` (`BFT Mitto` offers only 433.92 MHz).
5. Press **the same button of the same remote** over and over, about once a second, with the remote right next to the Flipper.
6. Watch the screen:
   - `Fix XXXXXXXX` — the remote's fixed part; the app locks onto the first one it hears;
   - `Hops n/10  Xpkt` — how many **different** hops are collected, and the raw packet count;
   - status `Hop n: XXXXXXXX` each time a new one lands.
7. From **2 hops** on, `Save` appears on <kbd>OK</kbd>. Press it; the app shows `Saved N hops` and the file name.

<kbd>←</kbd> (`Reset`) throws the capture away so you can lock onto another remote or button.

| Status | Meaning |
|---|---|
| `Hop n: XXXXXXXX` | new rolling part stored — keep pressing |
| `Other remote XXXXXXXX` | another remote or another button — ignored |
| `Same hop, ignored` | a repeat of the last press |
| `Have 10, enough` | full — press `Save` |

**How many presses:** 2 is the minimum, 5–10 is better. What matters just as much: the presses must be **consecutive with nothing missed** — check that `Hops` goes up on every press. If one is missed, press `Reset` and start over.

::: warning
On **FAAC SLH and Genius the Seed is different for every button** — capture the button you actually want to use. On Erreka the Seed is per remote (sometimes per installation), on BFT Mitto per remote.
:::

## Other menu items

- `Decode RAW file` — take the Fix/Hops from a RAW `.sub` (from `/ext/subghz`) recorded earlier with [Read RAW](/subghz/read-raw); the frequency comes from the file. A key file is refused with `Not a RAW capture`. Here <kbd>←</kbd> is `Back` instead of `Reset`.
- `Delete all captures` — asks `Delete every capture file in subghz_seed_captures?`, then deletes them.
- `Exit`.

## The capture file

Files go to `/ext/apps_data/subghz_seed_captures/`, named `<Type>_<Fix>_<date-time>.txt`, e.g. `Erreka_F00F1C9B_261008-142233.txt`. It is a text file, **not a playable `.sub`**:

```text
Filetype: Flipper SubGhz Seed Capture
Version: 1
# Fix + Hop set for offline seed recovery, not a playable .sub
Received: 2026-10-08 14:22:33
Manufacturer: Erreka
Protocol: KeeLoq
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Fix: F00F1C9B
Hops: 3
# Hops in the order they were received
Hop: ...
Hop: ...
Hop: ...
```

## Recovering the Seed in qUnleashed

1. Connect the Flipper to **qUnleashed** and open its Seed recovery tool. It fetches the captures from `subghz_seed_captures` itself — no copying or renaming.
2. Pick the capture and start the search (a brute-force search, which is why it does not run on the Flipper).
3. If the Seed is found, qUnleashed can compose the finished clone `.sub` (serial and button from `Fix`, plus Seed and counter) and put it on the Flipper.
4. If nothing is found, the capture most likely had a gap — capture again, carefully.

With the Seed you can also build remotes by hand in `Sub-GHz → Add Manually [Advanced]`: your own `SERIAL` + the `SEED` for a new remote, or the original's `SERIAL`/`BUTTON` + `SEED` + a slightly higher `COUNTER` for a clone. A clone fights the original over the counter — see [Rolling codes](/subghz/rolling-codes).

::: warning
Only for remotes and receivers you own.
:::

## Related pages

- [Programming a new remote](/subghz/remote-prog) · [KeeLoq](/subghz/keeloq) · [Add manually](/subghz/add-manually)
- [qUnleashed app](/mobile/qunleashed-app)
