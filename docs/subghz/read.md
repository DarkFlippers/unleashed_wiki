---
title: Read
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Read

**Read** listens on one frequency (or hops between several), **decodes** signals of known protocols and shows them
as a list. A decoded signal can be saved as a key file and sent again. It is the main way to copy a remote with
a **static (fixed) code** — gates, barriers, doorbells, sockets — and to identify what protocol a remote uses.

For remotes that Read does not recognise, use [Read RAW](/subghz/read-raw). For rolling-code remotes read
[Rolling codes](/subghz/rolling-codes) **before** sending anything.

::: tip Unleashed
Compared with stock firmware Unleashed adds: dozens of extra protocols ([full list](/subghz/supported-systems)),
saving and sending of many **rolling-code** protocols, arrow-key **custom buttons** when sending, hopping with an
RSSI threshold, `Ignore …` filters, `Delete old signals when memory is full`, **hold <kbd>→</kbd> to delete** a
signal from the list, receive time shown for each signal, and remembered last settings.
:::

## Reading a remote

1. Find the frequency first if you don't know it: [Frequency Analyzer](/subghz/frequency-analyzer)
   (long <kbd>OK</kbd> there jumps directly into Read on the found frequency).
2. Open `Main Menu → Sub-GHz → Read`. The screen shows `Fixed scan...` (or `Hopper scan...` with hopping on),
   and the current frequency and modulation at the bottom.

   ![Read screen waiting for a signal: Fixed scan on 433.92 MHz, AM650](/screens/subghz/read.png)

3. Hold the remote close to the left side of the Flipper and press its button for 1–2 seconds.
4. The decoded signal appears in the list as `protocol name` + time of reception. The counter at the bottom shows
   how many signals are in the list.

   ![Read list with three received signals: Princeton, CAME 12bit and KL: DoorHan](/screens/subghz/read_list.png)

5. Select it with <kbd>↑</kbd> <kbd>↓</kbd> and press <kbd>OK</kbd> to see the details (key, bit count, serial,
   button, counter, manufacturer for KeeLoq, etc.).

   ![Signal details: Princeton 24bit with key, serial and button, Send and Save buttons](/screens/subghz/signal_info.png)

6. Press <kbd>→</kbd> **Save**, enter a name and confirm. The file goes to `/ext/subghz/`.
7. Or press <kbd>OK</kbd> **Send** to transmit it right away.

Saved signals are in `Main Menu → Sub-GHz → Saved` (see [below](#saved-signals)).

## Buttons on the Read screen

| Button | Action |
|---|---|
| <kbd>←</kbd> | **Config** — receiver settings |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Move in the list of received signals |
| <kbd>OK</kbd> | Open the selected signal |
| hold <kbd>→</kbd> | Delete the selected signal from the list |
| <kbd>Back</kbd> | Leave Read. If there are unsaved signals you get **Exit to Sub-GHz Menu?** — `Exit` / `Stay` |

Depending on the size of the received data, the list can hold up to 128 signals.

## Config

Press <kbd>←</kbd> **Config** on the Read screen:

![Read Config menu: Frequency, Modulation, Hopping and Bin RAW](/screens/subghz/read_config.png)

| Item | Values | What it does |
|---|---|---|
| `Frequency` | list from [Frequencies](/subghz/frequencies) | Fixed receive frequency. Shows ` -----` while hopping is on |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + custom presets | Demodulation preset. `AM650` fits most remotes |
| `Hopping` / `Hopping RSSI` | `OFF`, `-90dBm` … `-40dBm` | Cycles through the hopper list (315, 390, 430.5, 433.92, 434.42, 868.35 MHz). The value is the RSSI level that stops hopping on a frequency |
| `Bin RAW` | `OFF` / `ON` | Also collect unknown static signals as **BinRAW** (repeating pattern with restored bit rate). Hold the remote button a bit longer so enough data accumulates |
| `Ignore ReversRB2` | `OFF` / `ON` | Hide Revers RB-2(M) signals |
| `Ignore Alarms` | `OFF` / `ON` | Hide bike/motorbike alarm protocols (Hollarm, GangQi) |
| `Ignore Sensors` | `OFF` / `ON` | Hide sensors and similar chatter: Magellan, Honeywell, Honeywell WDB and Legrand doorbells, Doorbell32, KeyFinder/KeyFinder2, Feron |
| `Ignore Princeton` | `OFF` / `ON` | Hide Princeton (PT2262 and clones) — useful where cheap remotes flood the air |
| `Ignore Nice Flor-S / Nice One` | `OFF` / `ON` | Hide Nice Flor-S / Nice One |
| `Delete old signals when memory is full` | `OFF` / `ON` | When the list is full, drop the oldest signals instead of stopping. The counter then shows `!` |
| `Sound` | `OFF` / `ON` | Play everything the radio receives through the speaker |
| `Reset to default` | — | Back to 433.92 MHz AM650, hopping off, all filters off, Bin RAW off, TX power `Preset` |
| `Lock Keyboard` | — | Locks the buttons while scanning (in a pocket). **Unlock: press <kbd>Back</kbd> three times** |

All Read settings are saved and restored the next time you open the app.

::: tip Which hopping value to pick
With `Hopping` on, the receiver stays on a frequency only when the signal is above the chosen level. `-90dBm` is the
most sensitive; raise it if noise keeps stopping the hopper. For reliable reception prefer a **fixed frequency**
found with the analyzer — signals sent during a frequency switch are missed.
:::

## Sending a signal

Open the signal (from the Read list or from `Saved → <file> → Emulate`). The transmit screen shows the key data,
frequency, modulation and `R: Int` / `R: Ext` (which radio will send).

- **Press** <kbd>OK</kbd> (**Send**) — a single press transmits a full signal packet (typically with 1–3 repeats for
  reliability). **Holding** <kbd>OK</kbd> repeats the transmission continuously until you release it (useful at longer
  range or with heavy interference). For rolling-code protocols, holding the button does **not** increment the counter
  (see also [Counter mode](/subghz/counter-mode)) — the signal repeats with the same counter until you release and
  press again.
- <kbd>Back</kbd> — leave.

### Custom buttons (Unleashed)

::: tip Unleashed
For many protocols the arrow keys send the **same remote with another button code** — so one saved file acts like
the whole remote. Supported, among others: KeeLoq, Alutech AT-4N, Nice Flor-S, Somfy Telis/Keytis, Security+ 2.0,
CAME Atomo, FAAC SLH, BelKorn, Beninca ARC, Ditec GOL4, Jarolift, KingGates Stylo 4k, V2 Phoenix, Prastel, Roger,
Nord ICE, Princeton, Proteco, Dooya, Hay21, GangQi, Hollarm. While an arrow is held, the button code sent is shown on
the right edge of the screen. Which arrow means which button depends on the protocol — see
[Rolling codes](/subghz/rolling-codes) and [Programming a new remote](/subghz/remote-prog).
:::

## Saved signals {#saved-signals}

`Main Menu → Sub-GHz → Saved` lists the files in `/ext/subghz/`. Pick one and you get:

- `Emulate` — open the transmit screen;
- `Rename`;
- `Delete`;
- `Signal Settings` — **only in Debug mode** (`Settings → System → Debug`): change `Counter Mode`, `Edit Counter`,
  `Edit Button` of a rolling-code file. See [Counter modes](/subghz/counter-mode).

RAW files open in the Read RAW screen instead — see [Read RAW](/subghz/read-raw#playback).

File names are generated automatically (date-time) unless `Protocol Names` is on in
[Radio Settings](/subghz/settings) — then the protocol name is put in front of the timestamp.

## Static vs rolling codes

- **Static code** (Princeton, CAME 12/24 bit, Nice Flo, Marantec, Roger, Gate TX…): every press sends the same code.
  A saved copy works forever alongside the original.
- **Rolling (dynamic) code** (KeeLoq, Nice Flor-S, CAME Atomo, FAAC SLH, Somfy, Security+…): every press carries a
  new counter value. Unleashed can save and send many of them, **but sending a copy desynchronises the original
  remote**. Read [Rolling codes](/subghz/rolling-codes) and prefer [Add Manually](/subghz/add-manually) to create
  a *new* remote.

::: danger Car key fobs
Do not experiment with your car key. Replaying a car fob (Read or Read RAW) can desync or blacklist the original
key, and re-pairing often needs dealer tools. Use the Flipper only with your own equipment and for lawful research.
:::

## Troubleshooting

- **Nothing appears** — wrong frequency or modulation. Use the Frequency Analyzer and try different modulations (`AM650`/`FM238`/`FM476`/`FM12K`).
  Check that an `Ignore …` filter isn't hiding the protocol.
- **Signal received but not decoded** — the protocol is unknown: turn `Bin RAW` on (static remotes) or record with
  [Read RAW](/subghz/read-raw). Also try the [Remote Analyzer](/subghz/remote-analyzer) app.
- **KeeLoq shows `Unknown` manufacturer** — the manufacturer key isn't in the database, or the remote needs a Seed
  (BFT, Erreka, FAAC SLH). See [KeeLoq](/subghz/keeloq) and [Seed Capturer](/subghz/seed-capturer).
- **No `Send` button** — the protocol is decode-only (e.g. iDo), or a Nice O-Code frame without installer code
  (use the [Nice O-Code](/subghz/nice-o-code) app).
- **The list fills up with noise** — enable the relevant `Ignore` options or `Delete old signals when memory is full`.

## Related

- [Read RAW](/subghz/read-raw) · [Frequency Analyzer](/subghz/frequency-analyzer) · [Supported systems](/subghz/supported-systems)
- [Rolling codes](/subghz/rolling-codes) · [Add Manually](/subghz/add-manually) · [Radio Settings](/subghz/settings) · [File formats](/subghz/file-format)
