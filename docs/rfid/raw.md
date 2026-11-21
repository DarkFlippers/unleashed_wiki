---
title: RAW recording
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/LFRFIDRaw.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/lfrfid_debug]
sources: [unleashed-docs, unleashed-src]
---
# Reading RAW 125 kHz data

RAW mode records the tag's signal as it is — pulse and period durations — instead of decoding it, a bit like a
dictaphone. It is meant for **protocol research**: if your tag is not recognised, record it and send the files (and a
photo of the card) to the developers in a GitHub issue.

## Enable Debug mode

RAW items are hidden unless Debug is on:

1. `Main Menu → Settings → System`.
2. Set **Debug** to **ON**.

## Recording

1. Go to `Main Menu → 125 kHz RFID → Extra Actions → Read RAW RFID data`.
2. Name the recording (default `RfidRecord`).
3. Read the instructions (*RAW RFID Data Reader — 1. Hold card next to Flipper, 2. Press OK, 3. Wait until data is
   read*) and press <kbd>OK</kbd>.
4. Hold the card on the Flipper's back. The Flipper records three passes of **5 seconds** each — *Reading ASK*,
   *ASK 134kHz*, *Reading PSK* — and asks *Don't move for 5 sec.*
5. **RAW RFID Read Success** — *Now you can analyze files or send them to developers*. Press <kbd>OK</kbd>.

Three files are created in `/ext/lfrfid/`:

| File | Pass |
|---|---|
| `<name>.ask.raw` | ASK, 125 kHz carrier |
| `<name>.ask134.raw` | ASK, 134.2 kHz carrier |
| `<name>.psk.raw` | PSK, 125 kHz carrier |

::: tip Unleashed
The Unleashed doc and stock firmware mention two files (ASK and PSK). The current firmware records a third,
**ASK 134kHz**, pass for animal tags.
:::

If you see *RAW Reading error! This may be caused by SD card issues*, check the card (free space, errors). Without an
SD card the app shows *No SD Card!*.

## Playing back

`Extra Actions → Emulate RAW RFID data` opens the file browser for `.raw` files and replays the selected one
(*Emulating RAW RFID*). It is mostly useful for debugging protocols, not as a replacement for normal emulation.

## CLI

The same is available over CLI and is handy for development:

```text
rfid raw_read <ask | ask134 | psk> <filename>   - read and save raw data to a file
rfid raw_emulate <filename>                     - emulate raw data
rfid raw_analyze <filename>                     - print the raw data and try to decode it
```

`raw_analyze` prints every pulse/duration pair, marks where a protocol decoded, and ends with frequency, duty cycle,
averages and the detected protocol (or `not found`).

## LF-RFID Debug app

The firmware source also contains a developer tool, **LF-RFID Debug** (`applications/debug/lfrfid_debug`), whose
**Tune** screen adjusts the carrier timer (ARR/CCR — frequency and duty cycle) live. It is a debug app for protocol
development, not needed for normal use.

## Related

- [File formats](/rfid/file-format) · [Reading](/rfid/read) · [Protocols](/rfid/protocols)
