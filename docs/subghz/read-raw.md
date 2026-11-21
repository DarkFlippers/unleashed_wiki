---
title: Read RAW
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/sub-ghz/read-raw]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Read RAW

**Read RAW** records the demodulated signal "as is", without decoding — like a voice recorder. The recording can be
played back, saved, decoded later, or edited. Use it when:

- **Read** does not recognise the remote (unknown protocol);
- you want to capture a signal for analysis or to report a new protocol to the developers;
- you need an exact replay of a static signal whose protocol the Flipper doesn't know.

The recording is still made with the selected **frequency and modulation** — the Flipper is not an SDR. A wrong
modulation gives you a recording of noise.

::: warning Rolling codes
A RAW replay of a rolling-code remote is just like a clone: it pushes the receiver counter and can desynchronise
your original. **Never do this with a car key** — it can get the key blacklisted. Details: [Rolling codes](/subghz/rolling-codes).
:::

## Recording

1. Find the frequency with the [Frequency Analyzer](/subghz/frequency-analyzer) if you don't know it.
2. Open `Main Menu → Sub-GHz → Read RAW`.
3. Press <kbd>←</kbd> **Config** and set `Frequency`, `Modulation` and `RSSI Threshold:` (see below).
   Press <kbd>Back</kbd> to return.

   ![Read RAW ready to record: empty waveform, Config and REC buttons](/screens/subghz/read_raw.png)

4. Press <kbd>OK</kbd> **REC**. The waveform starts scrolling, RSSI is shown on the right.
5. Press the button on the remote (hold 1–2 s).

   ![Read RAW recording: two signal bursts on the waveform, sample counter and Stop button](/screens/subghz/read_raw_recording.png)

6. Press <kbd>OK</kbd> **Stop**.
7. Now you have three options:
   - <kbd>←</kbd> **Erase** — discard and start over;
   - <kbd>OK</kbd> **Send** — play the recording back (hold to repeat it);
   - <kbd>→</kbd> **Save** — enter a name (default `RAW_<date-time>`) and save to `/ext/subghz/`.

## Config in Read RAW

The RAW config menu is shorter than in Read:

| Item | Values | Meaning |
|---|---|---|
| `Frequency` | frequency list | Receive frequency |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + custom | Demodulation preset |
| `Sound` | `OFF` / `ON` | Play the received signal through the speaker |
| `RSSI Threshold:` | `-----`, `-85.0` … `-40.0` | Records only while the signal is above this level. `-----` = record everything |

::: tip When to use the threshold
With a threshold the file contains only the bursts of your remote and not seconds of noise between presses — files
are much smaller and cleaner. For captures you send to developers, keep it at `-----` (full recording).
:::

## Playing back a saved RAW {#playback}

1. `Main Menu → Sub-GHz → Saved` and select the RAW file. It opens in the Read RAW screen.
2. <kbd>OK</kbd> **Send** — sends the whole recording once; keep <kbd>OK</kbd> held to repeat it (**Hold to repeat**).
3. <kbd>←</kbd> **New** — start a new recording.
4. <kbd>→</kbd> **More**:
   - `Decode` — run the recording through all decoders of the Sub-GHz app; found signals can be saved as normal key
     files;
   - `Edit` — open the file in the [Sub-GHz RAW Edit](/subghz/raw-editor) app (shown only when that app is installed
     in a compatible version); Sub-GHz reopens when you exit the editor;
   - `Rename`, `Delete`.

::: tip Unleashed
`More → Decode` and `More → Edit` are Unleashed additions. With `Edit` you can find the real signal in a noisy
capture, trim it, merge files and decode just a selection.
:::

Long, dense RAW files are streamed from the SD card while sending. If very short pulses (under 10 µs) are involved and the
card is slow, transmission can stop before the end of the file — use a good card.

## Recording a remote for a protocol request

This is the procedure the Unleashed developers ask for when you want a new protocol supported:

1. Find the frequency with the analyzer. In Read try `AM650`, `FM238`, `FM476`, `FM12K` — if nothing decodes,
   continue.
2. In Read RAW set that frequency and **`RSSI Threshold: -----`**.
3. Make **one RAW per modulation**: `AM650`, `FM238`, `FM476`, `FM12K`.
4. For each: press **REC**, then press one remote button **5 times holding it 1–2 s**, then **5 times holding it
   ~5 s**. Stop and save.
5. If the remote has several buttons, record each button the same way. Name every file after the button.
6. Copy the files to a PC, zip them and open an issue in the firmware repository. Add good photos of the remote
   (inside too, if possible), model and manufacturer.

## Troubleshooting

- **The recording is flat / only noise** — wrong frequency or modulation, or the remote is too far. Hold it close.
- **Huge files** — set an `RSSI Threshold`.
- **Replay doesn't work** — the remote uses a rolling code (the receiver rejects old counters), the modulation was
  wrong, or the recording contains only part of the signal. Record longer presses.
- **Transmission stops in the middle** — slow SD card with a long, dense file. Trim the file with
  [RAW Edit](/subghz/raw-editor) or use a faster card.
- **`Edit` is missing in `More`** — the Sub-GHz RAW Edit app is not installed or is too old.

## Related

- [Read](/subghz/read) · [Sub-GHz RAW Edit](/subghz/raw-editor) · [Remote Analyzer](/subghz/remote-analyzer)
- [File formats (RAW, BinRAW)](/subghz/file-format) · [Rolling codes](/subghz/rolling-codes)
