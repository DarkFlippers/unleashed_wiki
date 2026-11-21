---
title: Animal microchips
order: 50
original: [https://docs.flipper.net/zero/rfid/animal-microchips, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Animal microchips (FDX-B, FDX-A)

Pet microchips are rice-grain-sized RFID transponders implanted under the skin. When a reader powers them they send an
ID that can be looked up in pet recovery databases. Flipper Zero reads the two common LF types:

| Type | Name in Flipper | Description |
|---|---|---|
| **FDX-B** | `FDX-B` (ISO) | ISO 11784/11785, 15-digit ID; the most common type; some chips also report body temperature |
| **FDX-A** | `FDX-A` (FECAVA) | Older 10-digit, non-ISO chips |

Most animal chips work at **134.2 kHz**, while the Flipper antenna is tuned to 125 kHz, so the reading distance is
short — around **1 cm**. Microchips in the 110–140 kHz range can be read, but closer.

::: tip Unleashed
The official docs tell you to use *Read ASK*. Unleashed generates a real **134.2 kHz** field for these chips:
- **Read** now runs a third pass, **134kHz**, after ASK and PSK;
- `Extra Actions → Read FDX-B (Animals)` stays on 134.2 kHz the whole time — the best choice for weak chips;
- the country name for FDX-B is looked up in `/ext/lfrfid/assets/iso3166.lfrfid`.
:::

## Reading a pet's chip

1. Go to `Main Menu → 125 kHz RFID → Extra Actions → Read FDX-B (Animals)`. The screen shows *Reading FDX-B*.
2. Locate the chip:
   - dogs and cats: usually under the skin **between the shoulder blades**; in continental Europe often **mid-way on
     the left side of the neck**. Chips can migrate a bit;
   - feel gently with your fingertips for a firm rice-grain object, then put the centre of the Flipper's back right
     over it.
3. Hold the Flipper still for about **3 seconds** at each spot. If nothing, move it in small steps across the area,
   then rotate the Flipper 90° and repeat.
4. Watch the LED: yellow/green means a signal is being picked up — stay there.
5. Once decoded you get the result screen. <kbd>→</kbd> **More → Save** to keep it.

## What the Flipper shows for FDX-B

| Field | Meaning |
|---|---|
| `ID: CCC-NNNNNNNNNNNN` | 3-digit country (ISO 3166-1 numeric) or manufacturer code + 12-digit national ID — the 15-digit number to look up |
| Country Code / Country | The code and its name from the ISO 3166 table |
| Temperature | For thermo chips, in °C and °F; `---` if not present |
| Animal | Animal application flag |
| Visual Start Digit, Replacement Number, User Info, RFU | Header fields of the ISO frame |
| Data Block | Present / Absent — extra data block (e.g. temperature) |
| RUDI Bit | Yes / No |

FDX-A shows a 10-hex-digit `ID` and `Parity`.

::: warning
Chip temperature is not a replacement for a proper thermometer.
:::

## Looking up the ID

Enter the 15-digit ID in a pet recovery database, for example:
- [AAHA Pet Microchip Lookup](https://www.aaha.org/petmicrochiplookup) — US and Canada
- [Europetnet](https://www.europetnet.com/) — Europe
- [PETMAXX](http://www.petmaxx.com/) — worldwide

Or ask your local vet / pet registry.

## If the chip isn't found

- Out of range — use smaller steps and hold longer at each point.
- The chip has migrated — scan a larger area.
- Metal or electronics nearby — move away from them.
- The animal may have a 13.56 MHz chip — try [NFC](/nfc/read).
- Unsupported chip — ask a vet to scan it.

FDX-B keys can also be [emulated or written](/rfid/write) (T5577 and EM4305 blanks, which exist as glass tags too),
e.g. to test a pet door.

## Related

- [Reading](/rfid/read) · [Protocols](/rfid/protocols) · [Writing](/rfid/write)
