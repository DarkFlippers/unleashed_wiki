---
title: Counter modes
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-docs, unleashed-src]
---
# Counter modes (experimental)

**Counter Mode** changes how the rolling counter advances when the Flipper transmits a saved rolling-code
signal. The goal: a clone of your original remote that **doesn't conflict** with it, so both the Flipper and the
original can be used with the same receiver without desync. (Background: [Rolling codes](/subghz/rolling-codes).)

::: tip Unleashed
Counter modes are an Unleashed-only feature. Supported protocols: **Nice FloR-S, CAME Atomo, Alutech AT-4N,
KeeLoq, V2 Phoenix**.
:::

::: danger Read before using
Don't experiment with equipment you don't have access to. If you aren't sure which mode works for your system
and **cannot re-program your original remote** into the receiver — don't use these modes. They may desync or
lock out your remote. If you can test on your own receiver, tell the Unleashed team what works (GitHub issues /
community chats).
:::

## How to set a mode

### Option 1 — edit the `.sub` file

1. Copy the file from `/ext/subghz/` to a PC (qFlipper, mobile app or card reader).
2. Add a line at the end:
   ```text
   CounterMode: X
   ```
   where `X` is the mode number. Note the space after the colon.
3. Copy the file back.

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Nice FloR-S
Bit: 52
Key: AA AA AA AA AA AA AA
CounterMode: 1
```

### Option 2 — Signal Settings on the Flipper

With **Debug** on, the menu of a saved signal gains an extra item: `Sub-GHz → Saved → <file> → Signal Settings`.
Its `Counter Mode` row offers `System` (mode 0) and `Mode 1` … up to the last mode the protocol has, and writes
your choice into the file right away. The same screen can also edit the counter and the button code:
see [Signal Settings](/subghz/signal-settings).

## Modes by protocol {#modes-by-protocol}

Mode 0 is always the default: behaves like a regular remote, the counter grows by the global
[Counter Incr.](/subghz/settings) value (default +1) and wraps to 0 after `0xFFFF`.

### Nice FloR-S

| Mode | Counter | Notes |
|---|---|---|
| 0 | +multiplier | default |
| 1 | `0x0001 / 0xFFFE` | receiver **floxi2r** |
| 2 | `0x0000 / 0x0001` | receiver **ox2** |

### CAME Atomo

| Mode | Counter | Notes |
|---|---|---|
| 0 | +multiplier | default |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | works with external CAME **RE432**, maybe others |
| 2 | `0x807B / 0x807C / 0x007B / 0x007C` | works with external CAME **RE432**, maybe others |
| 3 | frozen | counter does not increment |

### Alutech AT-4N

| Mode | Counter | Notes |
|---|---|---|
| 0 | +multiplier | default |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | receiver **MCSW-3.3M** |
| 2 | `0x0000 … 0x0005` | other receiver boards |

### KeeLoq

| Mode | Counter | Notes |
|---|---|---|
| 0 | +multiplier | default |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | might work with some systems |
| 2 | `+0x3333` per transmission (13107) | e.g. DoorHan |
| 3 | `0x8006 / 0x8007 / 0x0006 / 0x0007` | e.g. Hormann EcoStar |
| 4 | `0x807B / 0x807C / 0x007B / 0x007C` | e.g. Nice Smilo |
| 5 | `0x0000 / 0xFFFF` | alternates 0 and 65535 |
| 6 | frozen | counter does not increment |
| 7–10 | forced resync packs | DoorHan, Phantom / Hiland, see below |

#### Modes 7–10: forced resync packs (DoorHan, Phantom / Hiland)

These modes don't step the counter; each press sends a **fixed pack** of codes. A receiver resyncs only when it
hears two transmissions with **consecutive** counters, so the pack is built from consecutive pairs, spaced so
every hop stays inside the receiver's resync window and the pairs together cover the whole counter space. That
pulls the receiver back from any state. The counter in your file is not changed, so every press sends the same
pack and the file stays usable.

Each pack reproduces, code for code, what a clone remote sends for that board family. Modes 7–9 = DoorHan Smart
clone, mode 10 = Phantom / Hiland clone. `X` = the counter in your file.

| Mode | For | Pack | Time per press |
|---|---|---|---|
| 7 | oldest DoorHan boards | 12 codes: `X / X+1`, four pairs walking forward in steps of 15998 (button 0), then `X-2 / X-1`; first and last pair carry your button | ~1.3 s |
| 8 | DHRE, most newer boards, swing-gate clones | 12 codes: `X / X+1`, four pairs `+0x3334` apart, then back to your counter where `X+1` with your button lands | ~1.3 s |
| 9 | CV01 roller-shutter boards, other old boards | 3 codes with your button: `X + 0x8000`, `X-1`, `X+1`, each sent twice | ~0.65 s |
| 10 | Phantom / Hiland | 2 codes with your button: absolute `0xFFFE`, `0xFFFF`, each sent three times | ~0.4 s |

::: warning Mode 7 changed
Mode 8 is exactly what `CounterMode: 7` did in earlier releases. If you have a file with `CounterMode: 7` that
worked, change it to `CounterMode: 8`.
:::

Details:

- In the long packs (7 and 8) each code goes out **once** (the original clone sends each two or three times) —
  the whole pack is built in memory, and tripling it would need 20 KB instead of 8 KB. Re-sending the pack is not
  a substitute: a receiver that already resynced reads a second pass as a fresh walk and operates the gate again,
  while a back-to-back repeat of one code is ignored as a duplicate.
- Mode 10 ignores your file's counter. With no walk, one press resyncs a receiver holding anything in the 32768
  values below `0xFFFE` — where a receiver that drifted ahead of your remote sits. If it doesn't take, send once more.
- **Holding** Send repeats the pack as long as you hold it; a receiver that resynced on the first pass reads that
  as another press. Pressing Send again while a pack is going out **aborts** it.

### V2 Phoenix (Phox)

| Mode | Counter | Notes |
|---|---|---|
| 0 | +multiplier | default |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` ("ofex like") | verified working |
| 2 | `0x0000 … 0x0004` | might work |

## Example: KeeLoq DoorHan with +0x3333

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: Doorhan
CounterMode: 2
```

## Troubleshooting and FAQ

- **File doesn't work after adding `CounterMode`** — check the syntax `CounterMode: X` (space after the colon)
  and that the number is valid for the protocol.
- **Invalid mode number?** The last mode in the protocol's list is used.
- **Do I need it in every file?** No. Without `CounterMode` mode 0 is used.
- **Can it damage my remote/receiver?** It can desync your remote, depending on the receiver. Don't use it if
  you can't re-pair the original.
- **Which mode should I use?** If you aren't sure — none. Prefer a [new remote](/subghz/add-manually) instead.

## Related

- [Signal Settings](/subghz/signal-settings) — setting a mode, the counter and the button on the Flipper
- [Rolling codes](/subghz/rolling-codes) · [KeeLoq](/subghz/keeloq)
- [Radio Settings: Counter Incr.](/subghz/settings) · [.sub file format](/subghz/file-format)
