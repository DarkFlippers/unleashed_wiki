---
title: IR file format
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared]
sources: [unleashed-docs, unleashed-src]
---
# Infrared file format (`.ir`)

All IR data on the Flipper is stored as plain text in the Flipper Format (`key: value` lines). The extension is
always `.ir`. There are three flavours that differ only in the `Filetype` header and in what they are used for.

| Filetype | Used for | Location |
|---|---|---|
| `IR signals file` | Your remotes (learned, saved from a universal remote, downloaded from the app) | `/ext/infrared/` |
| `IR library file` | Universal remote libraries | `/ext/infrared/assets/` |
| test file (`.irtest`) | Unit tests of the decoders/encoders | firmware repo only |

## Remote file

### Example

```text
Filetype: IR signals file
Version: 1
#
name: Button_1
type: parsed
protocol: NECext
address: EE 87 00 00
command: 5D A0 00 00
#
name: Button_2
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 504 3432 502 483 500 484 510 502 502 482 501 485 509 1452 504 1458 509 1452 504 481 501 474 509 3420 503
#
name: Button_3
type: parsed
protocol: SIRC
address: 01 00 00 00
command: 15 00 00 00
```

The file holds any number of buttons. Each button starts with `name:`; a `#` comment line between buttons is only
for readability.

### Fields

| Field | Used in | Type | Description |
|---|---|---|---|
| `name` | both | string | Button name. Printable ASCII only. The Flipper UI limits names to 23 characters. |
| `type` | both | string | `parsed` or `raw`. |
| `protocol` | parsed | string | Protocol name, exactly as in the [protocol list](/infrared/protocols) (`ir` CLI command prints it too). |
| `address` | parsed | hex | Address, always **4 bytes**, least significant byte first: `EE 87 00 00` = `0x87EE`. |
| `command` | parsed | hex | Command, always **4 bytes**, least significant byte first. |
| `frequency` | raw | uint32 | Carrier frequency in Hz, usually `38000`. Valid range 10000-1000000. |
| `duty_cycle` | raw | float | Carrier duty cycle, usually `0.33`. Must be > 0 and ≤ 1. |
| `data` | raw | uint32 list | Timings in microseconds between level changes (mark, space, mark, …), space-separated. **Max. 1024** values. |

### Valid `protocol` values

```text
NEC  NECext  NEC42  NEC42ext  Samsung32  RC6  RC5  RC5X  SIRC  SIRC15  SIRC20  Kaseikyo  RCA  Pioneer
```

::: tip Unleashed
`RCA` is an Unleashed addition. `Pioneer` exists in the firmware even though the official format document doesn't
list it yet.
:::

### Editing by hand

- Keep the two header lines (`Filetype`, `Version`) at the top.
- Every button needs `name` and `type`, then either `protocol`/`address`/`command` or `frequency`/`duty_cycle`/`data`.
- To merge two remotes, copy the button blocks of one file to the end of the other.
- Address/command bytes must stay 4 bytes long even if the protocol uses fewer bits; unused bytes are `00`.
- If the Flipper says *"Failed to load …"*, one of the fields is malformed (for example a RAW `data` line with more
  than 1024 values or a frequency out of range).

## Library files

Library files use exactly the same structure; only the header differs:

```text
Filetype: IR library file
Version: 1
# Last Updated 5th Oct, 2024
# Last Checked 5th Oct, 2024
#
# Model: Example TV 1234
name: Power
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

The universal remote looks up signals **by name**, so names must match the buttons of the library exactly (see the
table in [Contributing captures](/infrared/captures#button-names-per-library)). New models are appended at the end,
preceded by a `# Model: …` comment.

A library file can't be opened via `Saved Remotes`: the app reports *"Library file … can't be opened as a remote"*.

## Test files (`.irtest`)

Used only by the firmware unit tests (`applications/debug/unit_tests/resources/unit_tests/infrared` in the repo).
They look like remote files, plus a `parsed_array` type for whole sequences of decoded messages:

| Field | Used in | Type | Description |
|---|---|---|---|
| `name` | both | string | Signal name, see naming below. |
| `type` | both | string | `parsed_array` or `raw`. |
| `count` | parsed_array | uint32 | Number of messages in the array, at least 1. |
| `protocol`, `address`, `command` | parsed_array | | As above, one per message. |
| `repeat` | parsed_array | bool | Whether the message is a repeat (button held). |
| `frequency`, `duty_cycle`, `data` | raw | | As above. |

Names follow `<name><test_number>`: `decoder_input1` (raw input for the decoder, also expected encoder output),
`decoder_expected1` (expected decoder output, also encoder input), `encoder_decoder_input1` (parsed array that must
survive an encode → decode round trip). Every protocol must have such a test file.

## Related pages

- [Protocols](/infrared/protocols)
- [Contributing captures](/infrared/captures)
- [Learning and sending signals](/infrared/read)
