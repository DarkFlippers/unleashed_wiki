---
title: Remote Analyzer
order: 160
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/remote_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Remote Analyzer

**Remote Analyzer** (by @xMasterX) decodes one remote at a time on the internal CC1101 and shows every field it can work out. Unlike `Sub-GHz → Read` it keeps **no history** — only the last signal is on screen — and it **never saves** a `.sub` file. It is a tool for answering "what is this remote?".

::: tip Unleashed
Remote Analyzer is a built-in Unleashed system app. On top of every protocol the Sub-GHz app knows, it has its own decode-only protocols: **Crypt**, **Crypt Lite**, **Hormann BiSecur**, **KCE6xxx**, **Life Fido**, **Nero Intro II** and **PC4**.
:::

**When to use it:** you want to identify an unknown remote quickly, see whether it is fixed or rolling code, or check a remote the main app cannot decode. To capture and replay, use [Read](/subghz/read) or [Read RAW](/subghz/read-raw).

## Main menu

`Main Menu → Apps → Sub-GHz → Remote Analyzer`:

- `Read` — live decoding
- `Decode RAW File` — run a saved RAW capture through the same decoders
- `Frequency Analyzer` — find the remote's frequency
- `How to use` — the built-in manual

## Reading a remote

1. Open `Read`. The screen shows `Waiting for a signal`.
2. Press <kbd>←</kbd> (`Config`) and set **Frequency** and **Modulation** (or turn **Hopping** on).
3. Hold the remote close to the Flipper and press its button.
4. The reading appears:
   - the icon at the top left says **fixed** or **rolling** code;
   - the line under the protocol name and bit count says whether the Sub-GHz app knows this protocol too, or whether it is **analyzer only**;
   - `xN` at the top right counts how many times this code was received;
   - the bar under the line is signal strength.
5. <kbd>↑</kbd> / <kbd>↓</kbd> scroll a reading that does not fit, <kbd>→</kbd> (`Reset`) clears it.

**The LED:** purple — listening; yellow — something is on the air that nothing decoded; green — a code came through.

## Config

| Item | What it does |
|---|---|
| Frequency | receive frequency (ignored while Hopping is on) |
| Modulation | preset: AM270, AM650, FM238, FM476, FM12K and any custom presets |
| Hopping | `OFF` or a level from `-90dB` to `-40dB` |
| Sound | play the demodulated signal on the speaker |
| Mod. sweep | try other modulations when nothing decodes |
| Notify | buzz once on a code that differs from the last one |
| Reset to default | restore defaults |

**Hopping.** With a level set, the app walks **315, 390, 430.5, 433.92, 434.42 and 868.35 MHz** while the air is quiet and stops on the first band where the carrier reaches that level. A decode holds the band for two seconds before hopping resumes. Picking a frequency in the Frequency Analyzer turns hopping off. The level is also what the sweep and the LED treat as "a signal", so it still matters with hopping `OFF`.

**Mod. sweep.** When a remote is clearly transmitting but nothing decodes it, the app walks the other modulations, about a second each. A `~` next to the modulation means it is still trying — **keep the remote's button held**. The first successful decode fixes the modulation and the `~` disappears; after two seconds with nothing decoding the sweep starts again from there. `Unknown remote` means a whole round found nothing; it goes round again while the button is held.

**Notify.** A held remote repeats one code, so that only blinks the LED; a new, different code also buzzes.

## Decode RAW File

1. Choose `Decode RAW File` and pick a RAW `.sub` from `/ext/subghz`.
2. A progress bar shows how far through the file it is.
3. Every distinct code found is listed; press <kbd>OK</kbd> on one for the full reading.

Only a RAW capture holds samples — a saved key file is refused. Nothing decoded (or a refused file) beeps an error and holds the LED red.

## Frequency Analyzer

Hold the remote's button near the Flipper, then **hold** <kbd>OK</kbd> to carry the detected frequency over to `Read`. <kbd>←</kbd> / <kbd>→</kbd> move the trigger level. It works like the [main app's analyzer](/subghz/frequency-analyzer).

## Troubleshooting

- **Always `Waiting for a signal`** — wrong frequency; run the Frequency Analyzer or enable Hopping.
- **Yellow LED but no decode** — enable `Mod. sweep` and hold the button, or record it with [Read RAW](/subghz/read-raw) and try `Decode RAW File`.
- **Analyzer-only protocol** — the main Sub-GHz app cannot save or send it; Remote Analyzer only identifies it.
- **Want to save the signal** — use [Read](/subghz/read); this app does not write files.

## Related pages

- [Read](/subghz/read) · [Read RAW](/subghz/read-raw) · [Frequency Analyzer](/subghz/frequency-analyzer)
- [Supported systems](/subghz/supported-systems)
