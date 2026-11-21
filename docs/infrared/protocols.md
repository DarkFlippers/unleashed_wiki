---
title: Protocols
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Supported IR protocols

The infrared library (`lib/infrared/encoder_decoder/`) contains a decoder and an encoder for every protocol below.
A signal that matches one of them is saved as `type: parsed` (protocol + address + command); everything else is saved
as `type: raw` and replayed as timings. The list and the numbers on this page are taken from the firmware source.

::: tip Unleashed
**RCA** is an Unleashed addition. The other protocols are shared with the official firmware.
:::

## Protocol table

| Protocol (`protocol:` value) | Family | Address bits | Command bits | Carrier |
|---|---|---|---|---|
| `NEC` | NEC | 8 | 8 | 38 kHz |
| `NECext` | NEC (extended, no inverted bytes) | 16 | 16 | 38 kHz |
| `NEC42` | NEC 42-bit | 13 | 8 | 38 kHz |
| `NEC42ext` | NEC 42-bit extended | 26 | 16 | 38 kHz |
| `Samsung32` | Samsung | 8 | 8 | 38 kHz |
| `RC5` | Philips RC5 | 5 | 6 | 36 kHz |
| `RC5X` | Philips RC5 extended | 5 | 7 | 36 kHz |
| `RC6` | Philips RC6 | 8 | 8 | 36 kHz |
| `SIRC` | Sony SIRC 12-bit | 5 | 7 | 40 kHz |
| `SIRC15` | Sony SIRC 15-bit | 8 | 7 | 40 kHz |
| `SIRC20` | Sony SIRC 20-bit | 13 | 7 | 40 kHz |
| `Kaseikyo` | Kaseikyo (Panasonic, Denon…) | 26 | 10 | 38 kHz |
| `RCA` | RCA | 4 | 8 | 38 kHz |
| `Pioneer` | Pioneer | 8 | 8 | 40 kHz |

The duty cycle of all built-in encoders is 33 %. The same names are accepted by the `ir tx` CLI command
(`ir tx NEC 0x04 0x08`, for example) and are what `protocol:` must contain in a `.ir` file.

::: info Pioneer
The `Pioneer` protocol is implemented in the firmware (and used in the Audio and TV libraries) even though the
list in the official *InfraredFileFormats* document doesn't mention it yet.
:::

## Timing reference

Pulse/space timings of the main protocols, as defined in the encoders (µs). Tolerance for decoding is ±200 µs on the
preamble and ±120 µs on bits.

| Protocol | Preamble mark / space | Bit 1 mark / space | Bit 0 mark / space |
|---|---|---|---|
| NEC (all variants) | 9000 / 4500 | 560 / 1690 | 560 / 560 |
| Samsung32 | 4500 / 4500 | 550 / 1650 | 550 / 550 |
| RCA | 4000 / 4000 | 500 / 2000 | 500 / 1000 |
| Pioneer | 8500 / 4225 | 500 / 1500 | 500 / 500 |
| SIRC | 2400 / 600 | 1200 / 600 | 600 / 600 |
| Kaseikyo | 3456 / 1728 (8 / 4 units of 432) | 432 / 1296 | 432 / 432 |
| RC5 / RC5X | none (Manchester) | 888 µs half-bit | |
| RC6 | 2666 / 889 | 444 µs half-bit (Manchester) | |

## What the numbers mean for you

- **Learning:** the built-in receiver is tuned for 38 kHz, but the decoders for the 36 kHz (RC5, RC6) and 40 kHz
  (Sony SIRC, Pioneer) protocols are there, so such remotes are learned as parsed signals too.
- **Saving:** a parsed signal is tiny and plays back reliably. If a decoded signal doesn't work on your device, learn it as
  RAW (debug mode `Learn New Remote RAW`, see [Learning](/infrared/read#debug-mode-extras)).
- **Unknown remotes** (most AC remotes: 181 of the 182 signals in `ac.ir` are RAW) are not parsed at all and are always stored as RAW.
  RAW signals can hold up to 1024 timings; learned RAW captures are normally stored with `frequency: 38000` and `duty_cycle: 0.330000`.

## Related pages

- [IR file format](/infrared/file-format)
- [Learning and sending signals](/infrared/read)
- [Universal remotes](/infrared/universal-remotes)
