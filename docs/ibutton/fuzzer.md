---
title: iButton fuzzer
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/ibtnfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# iButton fuzzer

A **fuzzer** emulates a series of key IDs one after another to see how a reader reacts — for example to check whether
your own intercom accepts default or malformed IDs.

::: tip Unleashed
The Unleashed ReadMe lists **LFRFID and iButton Fuzzer plugins**. The fuzzer is an external app, not part of the
firmware source tree: prebuilt app packs are added to release builds, and the **extra apps pack** published with every
release contains all known working apps. Its menus depend on the app version, so they are not described here.
:::

## What the firmware ships: example UID lists

The firmware installs example ID lists into **`/ext/ibtnfuzzer/`**:

| File | Protocol | ID length (hex chars) |
|---|---|---|
| `example_uids_ds1990.txt` | Dallas DS1990 | 16 (8 bytes) |
| `example_uids_cyfral.txt` | Cyfral | 4 (2 bytes) |
| `example_uids_metakom.txt` | Metakom | 8 (4 bytes) |

Format — one hex ID per line, `#` for comments, keep an **empty line at the end**:

```text
# Example file, P.S. keep empty line at the end!
0000000000000000
FE00000000000000
CAFE000000000000
00CAFE0000000000

```

To make your own list, copy an example and replace the IDs; the length must match the protocol.

Community dictionaries linked from the Unleashed FAQ:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058),
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Use the fuzzer only on readers you own or are authorised to test.
:::

## Related

- [Protocols](/ibutton/protocols) · [Emulating keys](/ibutton/read) · [RFID fuzzer](/rfid/fuzzer)
