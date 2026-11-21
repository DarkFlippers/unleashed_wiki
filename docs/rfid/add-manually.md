---
title: Adding keys manually
order: 30
original: [https://docs.flipper.net/zero/rfid/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Adding 125 kHz keys manually

You can create a key without the physical tag: choose the protocol and type its data. The result is saved like a
read key and can be emulated or [written to a blank](/rfid/write).

## Steps

1. Go to `Main Menu → 125 kHz RFID → Add Manually`.
2. Pick the protocol / format from the list (see below).

   ![Add Manually tag type list: EM-Micro EM4100, EM4100/32, EM4100/16 and Casi-Rusco C10106](/screens/lfrfid/add_manually.png)

3. For formats that have a facility code / card number layout you get a choice:
   - **Enter FC/ID** — type the decimal fields one by one. The header shows the field name and range, e.g.
     `Facility Code (0-255)`. <kbd>Back</kbd> steps back to the previous field.
   - **Enter Hex Data** — type the raw bytes.

   Other protocols go straight to the hex editor *Enter the data in hex*.

   ![The "Enter the data in hex" editor with the tag bytes above an on-screen hex keyboard](/screens/lfrfid/add_manually_data.png)

4. Enter a name and save. The key is stored as `/ext/lfrfid/<name>.rfid`.

To change a saved key later: `Saved` → key → **Edit** (hex editor, same file name).

::: tip Unleashed
Entering **FC / card number** instead of hex, the extra **HID** formats and **Casi-Rusco** are Unleashed additions.
Stock firmware only accepts hex. Checksums and Wiegand parity are calculated for you.
:::

## The list, in device order

| Menu label | Saved as (`Key type`) | Input | Hex bytes |
|---|---|---|---|
| EM-Micro EM4100 | EM4100 | FC/ID or hex | 5 |
| EM-Micro EM4100/32 | EM4100/32 | FC/ID or hex | 5 |
| EM-Micro EM4100/16 | EM4100/16 | FC/ID or hex | 5 |
| Casi-Rusco C10106 | EM4100/32 | Credential + Card Number | — |
| Electra | Electra | hex | 8 |
| HID H10301 | H10301 | FC/ID or hex | 3 |
| HID H10304 | HIDProx | FC + Card Number | — |
| HID H10302 | HIDProx | Card Number | — |
| HID S10401 | HIDProx | FC + Card Number | — |
| HID H10306 | HIDProx | FC + Card Number | — |
| HID Corp1000-35 | HIDProx | FC + Card Number | — |
| IDTECK Idteck | Idteck | hex | 8 |
| Motorola Indala26 | Indala26 | hex | 4 |
| Kantech IoProxXSF | IoProxXSF | FC/ID or hex | 4 |
| AWID | AWID | FC/ID or hex | 9 |
| FECAVA FDX-A | FDX-A | hex | 5 |
| ISO FDX-B | FDX-B | hex | 11 |
| Generic HIDProx | HIDProx | hex | 6 |
| Generic HIDExt | HIDExt | hex | 12 |
| Farpointe Pyramid | Pyramid | FC/ID or hex | 4 |
| Viking | Viking | hex | 4 |
| Jablotron | Jablotron | hex | 5 |
| Paradox | Paradox | hex | 6 |
| PAC/Stanley | PAC/Stanley | hex | 4 |
| Keri | Keri | hex | 4 |
| Gallagher | Gallagher | FC/ID or hex | 8 |
| Honeywell Nexwatch | Nexwatch | hex | 8 |
| Securakey Radio Key | Radio Key | hex | 6 |
| Guardall GProxII | GProxII | hex | 12 |
| Noralsy | Noralsy | hex | 12 |
| Motorola Indala224 | Indala224 | hex | 28 |

## Field ranges for "Enter FC/ID"

| Format | Fields (decimal) |
|---|---|
| EM4100, EM4100/32, EM4100/16 | Facility Code 0–255, Card Number 0–65535 (stored in the last 3 bytes, first 2 bytes zero) |
| HID H10301 (26-bit Wiegand) | Facility Code 0–255, Card Number 0–65535 |
| AWID | Facility Code 0–255, Card Number 0–65535 (26-bit format, parity added) |
| Farpointe Pyramid | Facility Code 0–255, Card Number 0–65535 (26-bit, parity and CRC added) |
| Kantech IoProxXSF | Facility Code 0–255, Card Number 0–65535, Version 0–255 (checksum added) |
| Gallagher | Facility Code 0–65535, Card Number 0–16777215, Region Code 0–15, Issue Level 0–15 |
| Casi-Rusco C10106 | Credential 150000–159999, Card Number 0–457681 (as the access system prints it; saved as EM4100/32) |
| HID H10304 (37-bit) | Facility Code 0–65535, Card Number 0–524287 |
| HID H10302 (37-bit) | Card Number only (35 bits) |
| HID S10401 (37-bit) | Facility Code 0–63, Card Number (29 bits) |
| HID H10306 (34-bit) | Facility Code 0–65535, Card Number 0–65535 |
| HID Corp1000-35 (35-bit) | Facility Code 0–4095, Card Number 0–1048575 |

::: info Large card numbers
The number input holds a signed 32-bit value, so the very top of a field wider than 31 bits (e.g. H10302's 35-bit card
number) can only be entered through **Enter Hex Data** / **Edit**.
:::

## Tips

- An EM4100 printed number like `0001234567` is usually the **DEZ 10** form; after saving, compare it on the
  **Info** screen (it shows FC/Card, DEZ 8 and DEZ 10) to be sure you typed the right thing.

  ![Info screen of a saved tag: file name, EM-Micro EM4100, hex data, FC/Card, DEZ 8 and DEZ 10](/screens/lfrfid/saved_info.png)

- EM4100/32 and EM4100/16 are the same frame at RF/32 and RF/16 bit rates; pick the one the original reads as.
- For protocols with hex-only input, the easiest way to get correct bytes is to read the real tag once and copy the
  `Hex:` value.

## Related

- [Protocols](/rfid/protocols) · [File format](/rfid/file-format) · [Writing](/rfid/write) · [Reading](/rfid/read)
