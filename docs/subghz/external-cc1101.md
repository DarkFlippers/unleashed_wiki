---
title: External CC1101 module
order: 130
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/drivers/subghz/cc1101_ext, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://t.me/gromovyna/10, https://t.me/gromovyna/12, https://t.me/gromovyna/13]
sources: [unleashed-src, unleashed-readme, unleashed-docs, gromovyna]
---
# External CC1101 module

The Flipper's own Sub-GHz radio is a CC1101 chip with a small internal antenna. You can plug a second CC1101 board into the GPIO header and make the Sub-GHz app (and the Sub-GHz system apps) use it instead. External boards usually have a proper SMA antenna and often a power amplifier, so they reach much further, both when receiving and when transmitting.

**When to use it:** the remote or receiver is far away, the internal antenna does not catch a weak remote, or you need more transmit range. For finding a remote's frequency, keep using the internal radio (see [Frequency Analyzer](/subghz/frequency-analyzer)).

::: tip Works on any firmware
External radio modules work on every firmware, the stock one included. @quen0n wrote the first implementation, for Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307), [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101)); the implementation in use today was written by **Skorp** in the official firmware, and Unleashed uses that one.
:::

## Wiring

The module talks over the Flipper's external SPI bus. The standard wiring is:

| CC1101 pin | Flipper GPIO | Header pin |
|---|---|---|
| GDO0 | PB2 | 6 |
| CSN | PA4 | 4 |
| SCK | PB3 | 5 |
| MOSI | PA7 | 2 |
| MISO (GDO1) | PA6 | 3 |
| VCC | 3.3V | 9 |
| GND | GND | 11 or 18 |
| Amplifier / LED control (E07 modules) | PC3 | 7 |

For ready-made boards, schematics and photos see quen0n's guide: [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101) (linked from the Unleashed FAQ). Header numbering is on the [GPIO pinout](/gpio/pinout) page; other add-on boards are on [External modules](/gpio/external-modules).

::: warning
Power the module from **3.3 V** only. CC1101 is not a 5 V chip.
:::

## Switching to the external module

1. Connect the module with the Flipper switched off, or at least with no Sub-GHz app running.
2. Open `Main Menu → Sub-GHz → Radio Settings`.
3. On the **Module** line press <kbd>→</kbd> to change `Internal` to `External`.
4. Press <kbd>←</kbd> (Back) and use `Read`, `Read RAW`, `Saved` etc. as usual.

What to expect:

- The **Module** line offers `External` only when a module is actually detected. If nothing is connected, the line has a single value, `Internal`.
- The firmware probes the module when you select it. If the probe fails, it falls back to the internal radio and the line shows `Internal` again — so what you see is what is really in use.
- On the transmit screen of a saved signal, the bottom line shows `R: Int` or `R: Ext` — the radio that will send.
- The Sub-GHz system apps ([Nice O-Code](/subghz/nice-o-code), [Seed Capturer](/subghz/seed-capturer), [Security+ PIN](/subghz/secplus-pin)) show `Int` or `Ext` in their header and use an external module automatically when one is connected.

## Other Radio Settings

`Sub-GHz → Radio Settings` contains:

| Item | Values | What it does |
|---|---|---|
| Module | `Internal` / `External` | radio used by the Sub-GHz app |
| TX Power | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | overrides the transmit power of the preset; `Preset` keeps the power from the modulation preset |
| Protocol Names | `OFF` / `ON` | see [Settings](/subghz/settings) |
| Counter Incr. | `+1`… | see [Settings](/subghz/settings) |
| Ext Amp & LEDs | `OFF` / `ON` | **debug mode only** — drive the amplifier / LED control pin (PC3, header pin 7) of E07-style modules |
| Debug Pin | `OFF` / `17(1W)` | **debug mode only** — mirror the signal on pin 17 for protocol development |

`Ext Amp & LEDs` is **ON by default**. With it on, the firmware keys the module's amplifier on PC3 only while the chip is really transmitting. Turn it off only if your module uses pin 7 for something else; the menu item appears when debug mode is enabled in `Settings → System`.

## High-power 1 W module (in testing)

In early 2025 @gromovyna shared his tests of a new, much more powerful Sub-GHz module made by quen0n (a member of the Unleashed team):

- At the time of the posts it was the only one in existence, with transmitter power **up to 1 W**.
- It is built on a different chip from CC1101 — nobody had built anything on that chip before.
- Firmware support was **not finished yet**; it was being developed for Unleashed together with Flipper Market, and gromovyna acted as a tester.

![High-power module next to a CC1101 board](/img/remote/29279ff04df77e30.jpg)

His empirical results (no power measurements):

- The module is far more powerful than anything he had seen based on CC1101.
- In a city, transmitting from an apartment with another building in the way, he sent a **Hollarm** signal **600 m** horizontally.
- The same distance was reached both with the bundled antenna and with a walkie-talkie antenna recommended by MMX and quen0n — though with the walkie-talkie antenna the setup is "absolutely not portable".
- Any advantage for *receiving* compared to CC1101 was not yet clear.

![The module with a walkie-talkie antenna](/img/remote/0998ad639bb38e82.jpg)

This describes a device in testing; check the current Unleashed release notes for its support status.

::: warning
Transmit only on frequencies and powers that are legal where you are, and only to your own equipment.
:::

## Troubleshooting

- **`External` cannot be selected** — the module is not detected: check 3.3 V, GND and the four SPI lines (CSN, SCK, MOSI, MISO). A wrong CSN or MISO wire is the most common mistake.
- **Switches back to `Internal` by itself** — the probe failed when the module was selected; reseat the module and try again.
- **Receives but range is poor when sending** — on E07 modules the amplifier needs pin 7 (PC3) connected and `Ext Amp & LEDs` ON.
- **Frequency Analyzer shows random hits** — the external module is much more sensitive to noise; use the internal radio for frequency analysis.
- **Transmission blocked** — the frequency is outside the CC1101 range; see [Frequencies](/subghz/frequencies).

## Related pages

- [Sub-GHz settings](/subghz/settings)
- [Frequencies](/subghz/frequencies)
- [GPIO pinout](/gpio/pinout) · [External modules](/gpio/external-modules)
