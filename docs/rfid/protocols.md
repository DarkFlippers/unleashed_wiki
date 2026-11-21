---
title: Supported protocols
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://docs.flipper.net/zero/rfid/read]
sources: [unleashed-src, flipper-docs]
---
# Supported 125 kHz protocols

The table is built from `lib/lfrfid/protocols/` of the Unleashed firmware. All protocols can be **read**, **saved**,
**emulated** and **added manually**; the last columns show which blank chips can carry them (see
[Writing](/rfid/write)).

- **Name** — as shown on screen and stored in `.rfid` files as `Key type`.
- **Read** — which reading pass decodes it: ASK, PSK or both.
- **Bytes** — length of the `Data:` field.

| Name | Manufacturer | Read | Bytes | Shown fields | T5577 | EM4305 | Hitag Micro¹ | 8268² |
|---|---|---|---|---|---|---|---|---|
| EM4100 | EM-Micro | ASK/PSK | 5 | FC, Card, CL, DEZ 8, DEZ 10 | ✓ | ✓ | ✓ | ✓ |
| EM4100/32 | EM-Micro | ASK/PSK | 5 | same (RF/32 bit rate) | ✓ | ✓ | ✓ | — |
| EM4100/16 | EM-Micro | ASK/PSK | 5 | same (RF/16 bit rate) | ✓ | ✓ | ✓ | — |
| Electra | Electra | ASK/PSK | 8 | Epilogue | ✓ | ✓ | — | — |
| H10301 | HID | ASK | 3 | FC, Card (26-bit Wiegand) | ✓ | — | — | — |
| Idteck | IDTECK | PSK | 8 | FC, Card | ✓ | — | — | — |
| Indala26 | Motorola | PSK | 4 | FC, Card, Parity, Checksum | ✓ | — | — | — |
| Indala224 | Motorola | PSK | 28 | Raw | ✓ | — | — | — |
| IoProxXSF | Kantech | ASK | 4 | FC, Version, Card | ✓ | — | — | — |
| AWID | AWID | ASK | 9 | Format, FC, Card | ✓ | — | — | — |
| FDX-A | FECAVA | ASK | 5 | ID, Parity | ✓ | — | — | — |
| FDX-B | ISO | ASK | 11 | ID, country, temperature, animal flag… | ✓ | ✓ | — | — |
| HIDProx | Generic | ASK | 6 | bit length; matching HID formats | ✓ | — | — | — |
| HIDExt | Generic | ASK | 12 | — | ✓ | — | — | — |
| Pyramid | Farpointe | ASK | 4 | Format, FC, Card | ✓ | — | — | — |
| Viking | Viking | ASK | 4 | ID | ✓ | ✓ | — | — |
| Jablotron | Jablotron | ASK | 5 | Card | ✓ | ✓ | — | — |
| Paradox | Paradox | ASK | 6 | FC, Card, CRC check | ✓ | — | — | — |
| PAC/Stanley | — | ASK | 4 | CIN | ✓ | — | — | — |
| Keri | Keri | PSK | 4 | Internal ID, FC, Card | ✓ | — | — | — |
| Gallagher | Gallagher | ASK | 8 | FC, Card, Region, Issue Level | ✓ | ✓ | — | — |
| Nexwatch | Honeywell | PSK | 8 | ID, Mode, Type | ✓ | — | — | — |
| Radio Key | Securakey | ASK | 6 | RKKT n-bit (FC, Card) or RKKTH plaintext (Card) | ✓ | ✓ | — | — |
| GProxII | Guardall | ASK | 12 | FC, Card, LEN, XOR, CRC | ✓ | ✓ | — | — |
| Noralsy | Noralsy | ASK | 12 | Card ID, Year | ✓ | — | — | — |

¹ Hitag Micro = 8265/H5, 8210 and H5.5 targets. ² 8268 (Hitag S) only takes EM4100 at the RF/64 rate and is off by
default.

::: tip Unleashed
Compared to the list in the official docs, this firmware adds **Indala224** and a **134.2 kHz** reading pass for
FDX-A/FDX-B. The official file-format doc also lacks EM4100/32, EM4100/16, Electra, Nexwatch, Radio Key, Noralsy and
Indala224 — they are valid `Key type` values here.
:::

## Notes on some protocols

- **EM4100 / EM-Marin** — the most common fob type in the CIS ("ЕМ-Марин"). 40-bit ID; FC is the 3rd byte, card number
  the last two. DEZ 8 / DEZ 10 are the decimal forms printed on fobs.
- **Casi-Rusco C10106** — not a separate protocol; it is an EM4100 frame (usually RF/32). When the data fits, the
  info screen adds an `or C10106: credential card` line, and Add Manually offers it as an input format.
- **HIDProx** — generic HID Prox container of 26–37 bits. The Flipper tries known layouts (H10304, H10302, S10401,
  H10306, Corp1000-35) and prints FC/card for each match.
- **Paradox** — the info screen shows the CRC and *CRC Mismatch, Invalid Card!* if it doesn't match.
- **Indala26 legacy name** — very old files with `Key type: I40134` are converted to Indala26 on load.

## Related

- [Reading](/rfid/read) · [Add manually](/rfid/add-manually) · [Writing](/rfid/write) ·
  [Animal microchips](/rfid/animal-microchips) · [File format](/rfid/file-format)
