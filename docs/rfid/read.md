---
title: Reading tags
order: 10
original: [https://docs.flipper.net/zero/rfid/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-src, flipper-docs]
---
# Reading, saving and emulating 125 kHz tags

A 125 kHz tag is a transponder that, when powered by a reader's field, sends a fixed ID. If the tag uses one of the
[supported protocols](/rfid/protocols), Flipper Zero decodes the ID, shows it, and can save it to the SD card, emulate
it to a reader, or [write it to a blank](/rfid/write).

::: tip Insert an SD card
Saved keys, dictionaries and settings live on the microSD card (`/ext/lfrfid/`). Install the firmware with the SD card
inserted so the app's resources are present.
:::

## Reading a tag

1. Go to `Main Menu → 125 kHz RFID → Read`.
2. Put the tag against the **back** of the Flipper, near the middle, and hold it still. The screen says
   *Don't move card*.
3. The Flipper cycles through three reading passes of about 2 seconds each and shows the active one as
   **Reading 1/3 … 3/3**: **ASK** (125 kHz), **PSK** (125 kHz) and **134kHz** (ASK at 134.2 kHz, for animal chips).

   ![Reading 1/3 with the ASK pass active, PSK and 134 kHz below it, and "Don't move card" at the bottom](/screens/lfrfid/read.png)

4. Watch the LED: it blinks **cyan** while reading, switches to **yellow** when it hears something and **green** when a
   tag's frames start decoding — useful for finding the sweet spot.
5. When a tag is decoded the Flipper beeps and shows the result screen:
   - header: manufacturer and protocol, e.g. **EM-Micro EM4100**;
   - `Hex:` — the raw key data (first 7 bytes, longer keys end with `...`);
   - decoded fields (facility code, card number, etc. — see [protocols](/rfid/protocols)).

   ![Read result: EM-Micro EM4100 with its hex data, facility code, card number, DEZ 8 and DEZ 10, Retry and More at the bottom](/screens/lfrfid/read_success.png)

6. Buttons: <kbd>←</kbd> **Retry** (asks *Retry Reading? All unsaved data will be lost*), <kbd>→</kbd> **More**,
   <kbd>Back</kbd> asks whether to exit and lose the unsaved read.

::: tip Unleashed
The stock docs describe only ASK/PSK switching. Unleashed adds the third **134 kHz** pass (FDX-A/FDX-B tags are tuned
to 134.2 kHz and weak ones only answer there), and for EM4100 also shows **DEZ 8** and **DEZ 10** — the decimal
forms printed on many fobs. An EM4100 that decodes as a Casi-Rusco C10106 badge gets an extra `or C10106: …` line,
and a Generic HIDProx key is matched against known HID formats (H10304, H10302, S10401, H10306, Corp1000-35) and shows
their FC/card number.
:::

## After reading: More

<kbd>→</kbd> **More** opens:

| Item | Action |
|---|---|
| **Save** | Enter a name (default prefix `RFID`), saved as `/ext/lfrfid/<name>.rfid` |
| **Emulate** | Emulate the key right away, without saving |
| **Write** | Write the key to a blank — see [Writing](/rfid/write) |

## Reading with a fixed modulation

Some tags need longer than one 2-second pass to decode, or are only found reliably with a specific demodulator.
`Main Menu → 125 kHz RFID → Extra Actions` offers:

| Item | Reads |
|---|---|
| **Read ASK (Regular)** | ASK at 125 kHz only, until a tag is found: EM4100, HID, AWID, Viking, Paradox… |
| **Read PSK (Indala)** | PSK only: Indala, Keri, Nexwatch, Idteck… |
| **Read FDX-B (Animals)** | ASK at 134.2 kHz only — animal chips, see [Animal microchips](/rfid/animal-microchips) |

In Debug mode the same menu also has **Read RAW RFID data** and **Emulate RAW RFID data** — see [RAW](/rfid/raw).

## Saved keys

`Main Menu → 125 kHz RFID → Saved` opens the file browser in `/ext/lfrfid/`. Picking a `.rfid` key opens:

![Saved tag menu with Emulate, Write, Write and set password and Edit](/screens/lfrfid/saved_menu.png)

| Item | Action |
|---|---|
| **Emulate** | Act as this key towards a reader |
| **Write** | Write it to a blank ([Writing](/rfid/write)) |
| **Write and set password** | Write to a T5577 and protect it with a password ([Writing](/rfid/write#write-and-set-password)) |
| **Edit** | Change the key data in hex; saved under the same name |
| **Rename** | Change the file name |
| **Delete** | Delete the file (with confirmation) |
| **Info** | Name, protocol, full hex data and all decoded fields |

::: tip Unleashed
The browser also lists **`.t5577`** block dumps (marked with the T5577 icon). Selecting one launches the
[T5577 app](/rfid/t5577-app) with that dump. If the app is missing you get *No T5577 app — It comes with the
firmware - install its resources to get it*.
:::

## Emulating

1. Open a saved key (or a fresh read via **More**) and choose **Emulate**.
2. The screen shows *Emulating*, `[Protocol]` and the key name (or *Unsaved Tag*); the LED blinks magenta.

   ![Emulating screen showing "Emulating", the protocol [EM4100] and the key name](/screens/lfrfid/emulate.png)

3. Hold the Flipper's back flat against the reader. Press <kbd>Back</kbd> to stop.

## CLI

Over USB/serial CLI (`rfid` command):

```text
rfid read <optional: normal | indala | ask134>   - read in ASK/PSK mode
rfid <write | emulate> <key_type> <key_data>      - write or emulate a card
rfid raw_read <ask | ask134 | psk> <filename>     - read and save raw data to a file
rfid raw_emulate <filename>
rfid raw_analyze <filename>
```

`key_type` is the protocol name as stored in `.rfid` files (e.g. `EM4100`, `H10301`), `key_data` is hex.

## Troubleshooting

- **Nothing is found.** The card may be 13.56 MHz — try [NFC](/nfc/read). Many "dual" cards contain both.
- **Read keeps cycling.** Try a fixed mode in **Extra Actions** — a pass of 2 s may be too short for some tags.
- **Weak tags / small fobs.** Move the tag slowly over the back; watch for the yellow/green LED. Don't hold it in
  your hand over metal.
- **Unknown protocol.** Record a [RAW](/rfid/raw) capture and report it to the developers.
- **Emulation not accepted.** Some readers are picky about distance and orientation — hold the Flipper flat, try a
  few positions. Readers that check something beyond the ID (e.g. crypto cards) can't be fooled by emulation.

## Related

- [Writing to blanks](/rfid/write) · [Add manually](/rfid/add-manually) · [Protocols](/rfid/protocols) ·
  [File format](/rfid/file-format)
