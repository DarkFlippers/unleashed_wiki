---
title: ZKTeco CMP200 barrier remote
order: 210
author: gromovyna
original: [https://telegra.ph/ZKTeco-CMP200---Princeton-v-kitajskoj-obyortke-03-09, https://t.me/gromovyna/28, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md]
sources: [gromovyna, unleashed-src, unleashed-docs]
---
# ZKTeco CMP200 — Princeton in a Chinese wrapper

*A short review by @gromovyna of the remote for ZKTeco barriers, plus how to handle it on Unleashed.*

![ZKTeco CMP200 remote](/img/remote/a2cb668ab24d6625.png)

## Intro

Some time ago a private clinic opened near gromovyna's home and installed a **ZKTeco** boom barrier. He was curious, but there was little traffic and not much reason to dig in, so it went into the mental backlog.

![ZKTeco barrier (photo from the internet)](/img/remote/4cfaf6cbf4b21db6.png)

Then, leaving an appointment, he saw the key fob lying on the reception desk from an upper floor, photographed it, identified the model with Google Lens and put it on his "buy" list. Before buying, he asked MMX (xMasterX) — and it turned out the mystery was already solved.

## How the Chinese wrapped Princeton

It is all quite prosaic, and it has been supported in **Unleashed** (thanks to MMX) for more than a year. Under the hood it is an ordinary **Princeton** with an 8-bit button code — and the button codes are well known, **the same for every remote**:

| Parameter | Value |
|---|---|
| Frequency | **430.50 MHz** |
| Modulation | **AM650** |
| Button UP | `0x30` |
| Button STOP | `0x03` |
| Button DOWN | `0x0C` |

Best of all, in Unleashed these button codes are **already mapped to the arrow keys**, so a single saved signal works as the whole remote.

::: tip Unleashed
ZKTeco appears in the Unleashed supported systems list as `ZKTeco 430.5MHz AM650 (24 bits, Static - Princeton based)` and has its own entry in `Add Manually`. 430.50 MHz is in the default frequency list.
:::

## How to use it with the Flipper

Because the code is static, a copy is identical to the original — both keep working in any order.

### Option 1 — read your remote

1. `Main Menu → Sub-GHz → Read`.
2. <kbd>←</kbd> `Config` → **Frequency** `430.50`, **Modulation** `AM650`. Back.
3. Press a button on the CMP200 near the Flipper. A `Princeton` signal appears.
4. <kbd>OK</kbd> → `Save`, name the file.
5. Open it in `Sub-GHz → Saved` → `Emulate`. <kbd>OK</kbd> sends the captured button; the arrow keys send the other buttons (UP / STOP / DOWN).

### Option 2 — create a remote

1. `Main Menu → Sub-GHz → Add Manually → ZKTeco`.
2. Pick the band `430.50 AM650` (it is listed first for this entry).
3. Name and save. The Flipper creates a Princeton 24-bit key with a random code, TE 357 µs, button `0x30` (UP).

A remote created this way has its own code — the barrier will only react after it is registered in the barrier's receiver (follow the barrier's manual). To act like an existing remote, read it instead (option 1).

::: warning
Only for barriers you own or administer.
:::

## Is that all?

For now — yes. As gromovyna notes, this support arrived quietly, so most of the community never noticed it; he tested it and shared the results.

## Troubleshooting

- **Nothing is received** — make sure the frequency is 430.50, not 433.92; check with [Frequency Analyzer](/subghz/frequency-analyzer).
- **`Ignore Princeton` is ON** in Read `Config` — Princeton-based remotes like this one are then hidden; switch it off.
- **Arrows send nothing** — open the signal from `Saved → Emulate`; custom buttons work on the transmit screen.

## Related pages

- [Read](/subghz/read) · [Add manually](/subghz/add-manually) · [Supported systems](/subghz/supported-systems)
- [Rolling codes](/subghz/rolling-codes) — custom buttons explained
