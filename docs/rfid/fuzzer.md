---
title: RFID fuzzer
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/rfidfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# RFID fuzzer

A **fuzzer** emulates a long series of IDs one after another to test how a reader reacts — e.g. whether it accepts a
default ID, crashes on malformed data, or to check your own system's range of valid cards.

::: tip Unleashed
The Unleashed ReadMe lists **LFRFID and iButton Fuzzer plugins** among its NFC/RFID/iButton features. The fuzzer is an
external app, not part of the firmware source tree: prebuilt app packs are added to release builds, and the
**extra apps pack** published with every release contains all known working apps. Its menus depend on the app version,
so they are not described here.
:::

## What the firmware ships: example UID lists

The firmware installs example ID lists for the fuzzer into **`/ext/rfidfuzzer/`**:

| File | Protocol | ID length (hex chars) |
|---|---|---|
| `example_uids_em4100.txt` | EM4100 | 10 (5 bytes) |
| `example_uids_h10301.txt` | HID H10301 | 6 (3 bytes) |
| `example_uids_hidprox.txt` | HIDProx | 12 (6 bytes) |
| `example_uids_pac.txt` | PAC/Stanley | 8 (4 bytes) |

Format — one hex ID per line, `#` for comments, and an **empty line at the end** of the file:

```text
# Example file, P.S. keep empty line at the end!
0000000000
FE00000000
CAFE000000
00CAFE0000

```

Make your own list by copying one of the examples and replacing the IDs; the ID length must match the protocol's key
size (see [protocols](/rfid/protocols), *Bytes* column).

The Unleashed FAQ links ready-made dictionary files shared by the community:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058) and
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Use the fuzzer only on readers you own or are authorised to test.
:::

## Related

- [Protocols](/rfid/protocols) · [Reading](/rfid/read) · [iButton fuzzer](/ibutton/fuzzer)
