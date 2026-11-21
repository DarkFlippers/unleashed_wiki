---
title: File formats
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/resources/subghz/assets, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md]
sources: [unleashed-docs, unleashed-src]
---
# Sub-GHz file formats

Sub-GHz files — signal files (`.sub`) and the configuration files in `/ext/subghz/assets/` — are plain text in
the *Flipper File Format* (`Key: value` lines), so you can view and edit them on a PC.

| Path | What |
|---|---|
| `/ext/subghz/*.sub` | Saved signals: keys, RAW and BinRAW |
| `/ext/subghz/assets/setting_user` | Your frequencies, hopper list, custom presets |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Your KeeLoq manufacturer keys |
| `/ext/subghz/assets/keeloq_mfcodes` | Built-in KeeLoq manufacturer keys (encrypted, shipped with the firmware) |
| `/ext/subghz/assets/nice_flor_s`, `alutech_at_4n` | Built-in tables for those protocols |
| `/ext/subghz/assets/dangerous_settings` | Extended frequency range switch, see [Frequencies](/subghz/frequencies#extended-range) |

## `.sub` file structure

A `.sub` file has three parts:

1. **Header** — file type, version, frequency.
2. **Preset** — modulation preset, or a full custom CC1101 configuration.
3. **Data** — protocol name and its fields, or RAW timings.

### Header

| Field | Type | Description |
|---|---|---|
| `Filetype` | string | `Flipper SubGhz Key File` for keys, `Flipper SubGhz RAW File` for RAW recordings |
| `Version` | uint | File format version, currently `1` |
| `Frequency` | uint | Frequency in Hz, e.g. `433920000` |

### Preset

| Field | Description |
|---|---|
| `Preset` | Preset name. For a custom preset it must be `FuriHalSubGhzPresetCustom` |
| `Custom_preset_module` | Transceiver, `CC1101` for Flipper Zero (custom preset only) |
| `Custom_preset_data` | Transceiver configuration (custom preset only) |

Built-in presets:

| `Preset` value | Menu name | Meaning |
|---|---|---|
| `FuriHalSubGhzPresetOok270Async` | `AM270` | OOK, 270 kHz bandwidth |
| `FuriHalSubGhzPresetOok650Async` | `AM650` | OOK, 650 kHz bandwidth |
| `FuriHalSubGhzPreset2FSKDev238Async` | `FM238` | 2-FSK, 2.38 kHz deviation, 270 kHz bandwidth |
| `FuriHalSubGhzPreset2FSKDev12KAsync` | `FM12K` | 2-FSK, 12 kHz deviation |
| `FuriHalSubGhzPreset2FSKDev476Async` | `FM476` | 2-FSK, 47.6 kHz deviation, 270 kHz bandwidth |

A custom preset is embedded in the file, so another Flipper can send it even without that preset in its settings.

#### Custom preset data {#custom-preset-data}

Hex bytes separated by spaces: `XX YY XX YY … 00 00 ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ`

- `XX` — CC1101 register address, `YY` — register value (as many pairs as needed);
- `00 00` — end of the register block;
- `ZZ ×8` — the 8-byte PA table (power amplifier ramp).

See the [CC1101 datasheet](https://www.ti.com/lit/ds/symlink/cc1101.pdf) for register meanings.

### Key files

Decoded signals store the protocol name and its fields:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

| Field | Description |
|---|---|
| `Protocol` | Protocol name exactly as in the protocol registry (e.g. `Princeton`, `KeeLoq`, `Nice FloR-S`, `CAME Atomo`, `Security+ 2.0`) |
| `Bit` | Payload length in bits |
| `Key` | Payload, hex, 8 bytes |
| `TE` | Base pulse duration (quantisation interval) in µs, for protocols that store it |

Protocols can add their own fields. Ones you will meet in Unleashed:

| Field | Used by | Meaning |
|---|---|---|
| `Manufacture` | KeeLoq, FAAC SLH / Genius | Manufacturer whose key decodes the signal (e.g. `DoorHan`, `BFT`, `Genius`) |
| `Seed` | BFT Mitto, Erreka, FAAC SLH, Genius, some KeeLoq | Per-remote secret for secure learning |
| `CounterMode` | Nice Flor-S, CAME Atomo, Alutech AT-4N, KeeLoq, V2 Phoenix | Experimental counter behaviour, see [Counter modes](/subghz/counter-mode) |
| `Secplus_packet_1`, `Pin` | Security+ 2.0 | Second packet; keypad PIN for 86-bit frames ([Security+ PIN](/subghz/secplus-pin)) |
| `Cert` | Nice O-Code | Receiver certificate ([Nice O-Code](/subghz/nice-o-code)) |

Custom preset example:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetCustom
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

::: warning Editing rolling-code files
Changing `Key` of a dynamic protocol by hand rarely produces a valid code. To change serial, button or counter use
[Add Manually [Advanced]](/subghz/add-manually) or, in Debug mode, `Saved → file → Signal Settings`.
:::

### RAW files

Recordings from [Read RAW](/subghz/read-raw):

```text
Filetype: Flipper SubGhz RAW File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: RAW
RAW_Data: 29262 361 -68 2635 -66 24113 -66 11 ...
RAW_Data: -424 205 -412 159 -412 381 -240 181 ...
```

- `Protocol` must be `RAW`.
- `RAW_Data` — durations in µs: positive = carrier on, negative = carrier off. Values must be non-zero, start with a
  positive number and alternate in sign. Up to 512 values per line; the line can repeat as many times as needed.

Long payloads are read from the SD card during transmission. With very short timings (under 10 µs) a slow card may not
keep up and transmission stops before the end.

### BinRAW files

`Bin RAW` in `Read → Config` produces **BinRAW** files. Unlike RAW, they store only the useful repeating sequence,
with the bit rate restored and without the noise, so they can replay nearly any **static** protocol, known or not.
Hold the remote button a bit longer when reading so enough data accumulates.

| Field | Description |
|---|---|
| `Protocol` | `BinRAW` |
| `Bit` | Payload length of the whole file in bits (max 4096) |
| `TE` | Quantisation interval, µs |
| `Bit_RAW` | Length of the following `Data_RAW` block, bits |
| `Data_RAW` | Encoded durations: each bit = one `TE`; `1` = carrier, `0` = no carrier |

Example: `TE: 100`, `Bit_RAW: 8`, `Data_RAW: 37` → `0b00110111` → sends `-200 200 -100 300`.
`Bit_RAW` + `Data_RAW` pairs form repeated blocks; several blocks are sent one after another.

```text
Protocol: BinRAW
Bit: 1572
TE: 597
Bit_RAW: 260
Data_RAW: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F 4A B5 55 4C B3 52 AC D5 2D 53 52 AD 4A D5 35 00
```

## `setting_user` {#setting-user}

Extra frequencies and presets, loaded when the Sub-GHz app starts. Rename `setting_user.example` to `setting_user`.

```text
Filetype: Flipper SubGhz Setting File
Version: 1

# Add standard frequencies included with firmware and place user frequencies after them
Add_standard_frequencies: true

# Default frequency for "Read" and "Read Raw"
Default_frequency: 433920000

# Frequencies for "Read", "Read Raw" and "Frequency Analyzer"
Frequency: 300000000
Frequency: 310000000

# Frequencies for hopping mode (keep this list small)
Hopper_frequency: 300000000
Hopper_frequency: 310000000

# Custom preset
Custom_preset_name: AM_1
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
```

| Key | Meaning |
|---|---|
| `Add_standard_frequencies` | `true` — firmware list + yours (appended after it); `false` — only yours (then fill both `Frequency` and `Hopper_frequency`) |
| `Default_frequency` | Frequency Read / Read RAW start with |
| `Frequency` | Adds a frequency to the main list (9 digits, Hz). Repeatable |
| `Hopper_frequency` | Adds a frequency to hopping. Repeating one makes the Flipper listen to it more often |
| `Custom_preset_name` / `_module` / `_data` | A custom modulation preset, shown in the `Modulation` list under that name. Data format: [above](#custom-preset-data) |

The `.example` file ships commented-out presets you can enable: `FM95`, `FM15k` (2-FSK, 200 kHz BW / 135 kHz filter,
15.86 kHz deviation), `Pagers`, `AM_1`, `AM_2`.

## `keeloq_mfcodes_user` {#keeloq-mfcodes-user}

Your own KeeLoq manufacturer keys, loaded at app start in addition to the built-in (encrypted) database. Create it
from `keeloq_mfcodes_user.example`, remove the sample keys and **keep an empty line at the end**.

```text
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:2:Test2
```

Each line is `KEY:METHOD:NAME`:

- `KEY` — 64-bit manufacturer key, 16 hex digits;
- `NAME` — name without spaces, up to 64 characters (shown as the manufacturer in Read);
- `METHOD` — learning type:

| Value | Learning |
|---|---|
| `0` | try all: iterates previous and manufacturer key in direct and reversed byte order |
| `1` | Simple Learning |
| `2` | Normal Learning |
| `3` | Secure Learning (needs Seed) |
| `4` | Magic XOR type 1 |
| `5` | FAAC SLH |
| `6` | Magic Serial type 1 |
| `7` | Magic Serial type 2 |
| `8` | Magic Serial type 3 |

`Encryption: 0` means the file is plain text — user files must not be encrypted. More about learning types:
[KeeLoq](/subghz/keeloq).

## Related

- [Read](/subghz/read) · [Read RAW](/subghz/read-raw) · [Frequencies](/subghz/frequencies) · [Radio Settings](/subghz/settings)
- [KeeLoq](/subghz/keeloq) · [Counter modes](/subghz/counter-mode) · [Sub-GHz Remote map files](/subghz/remote)
