---
title: Frequencies and range
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/lib/subghz/subghz_setting.c, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/frequencies]
sources: [unleashed-src, unleashed-docs, flipper-docs]
---
# Frequencies and range

Flipper Zero talks to the sub-1 GHz world through a **TI CC1101** transceiver.

## Hardware bands

The CC1101 datasheet specifies three bands:

| Band | Typical use |
|---|---|
| 300–348 MHz | US garage doors and gates (300, 310, 315, 318, 390 MHz family), car fobs |
| 387–464 MHz | 433.92 MHz LPD433 remotes, barriers, sensors, doorbells (most of Europe/CIS) |
| 779–928 MHz | 868 MHz (EU SRD) and 915 MHz (US ISM) devices |

Unleashed widens the default transmit window slightly so that the common 350 MHz and 467.75 MHz frequencies work.

## Transmit limits in Unleashed

::: tip Unleashed
Stock firmware locks transmission to the frequencies allowed in the **region** detected during the update
(e.g. only 433.05–434.79 and 868.15–868.55 MHz in the EU/Russia). **Unleashed removes the regional lock entirely.**
You can send on any frequency the chip supports, no extra steps needed.
:::

What still applies is a hardware safety limit (from `furi_hal_subghz.c`):

| Mode | Allowed TX ranges |
|---|---|
| Default | 300–350 MHz, 387–467.75 MHz, 779–928 MHz |
| Extended ("dangerous") | 281–361 MHz, 378–481 MHz, 749–962 MHz |

If you try to send outside the allowed range, the Flipper refuses to transmit.

### Extending the range (dangerous) {#extended-range}

::: danger
Transmitting outside the CC1101 specifications can **damage the radio chip**. Neither the Flipper team nor the
Unleashed developers are responsible for damage. Almost nobody needs this — the default range already covers
practically every real remote.
:::

1. Connect the SD card to a PC (or use qFlipper / the mobile app file manager).
2. Open `/ext/subghz/assets/dangerous_settings`. Its content looks like this:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Change `false` to `true`, save the file and reboot the Flipper (the setting is read at startup).

See also [Dangerous settings](/start/dangerous-settings).

## Default frequency list

These are the frequencies you can step through with <kbd>←</kbd> <kbd>→</kbd> in **Read**, **Read RAW** → `Config`
and that the Frequency Analyzer rounds to. **433.92 MHz** is the default.

| 300–350 MHz | 387–467.75 MHz | 779–928 MHz |
|---|---|---|
| 300.000, 302.757, 303.000, 303.875, 303.900, 304.250, 307.000, 307.500, 307.800, 309.000, 310.000, 312.000, 312.100, 312.200, 313.000, 313.850, 314.000, 314.350, 314.980, 315.000, 317.000, 318.000, 320.000, 320.150, 330.000, 336.100, 345.000, 348.000, 350.000 | 387.000, 390.000, 418.000, 430.000, 430.500, 431.000, 431.500, 433.075 (LPD433 first), 433.220, 433.420, 433.657070, 433.889, **433.920** (LPD433 mid, default), 434.075, 434.176948, 434.190, 434.390, 434.420, 434.620, 434.775 (LPD433 last), 438.900, 440.175, 462.750, 464.000, 467.750 | 779.000, 868.000, 868.350, 868.400, 868.460, 868.800, 868.950, 906.400, 915.000, 925.000, 928.000 |

### Hopping list

When **Hopping** is on, the receiver cycles through a short list only (a long list would miss signals):

`315.00`, `390.00`, `430.50`, `433.92`, `434.42`, `868.35` MHz.

## Modulations (presets)

Frequency alone is not enough — the Flipper is not an SDR, it must be told the modulation in advance.
Built-in presets:

| Name in menu | Preset in `.sub` file | Meaning |
|---|---|---|
| `AM270` | `FuriHalSubGhzPresetOok270Async` | OOK/ASK, 270 kHz bandwidth |
| `AM650` | `FuriHalSubGhzPresetOok650Async` | OOK/ASK, 650 kHz bandwidth — **default, used by most remotes** |
| `FM238` | `FuriHalSubGhzPreset2FSKDev238Async` | 2-FSK, 2.38 kHz deviation |
| `FM476` | `FuriHalSubGhzPreset2FSKDev476Async` | 2-FSK, 47.6 kHz deviation |
| `FM12K` | `FuriHalSubGhzPreset2FSKDev12KAsync` | 2-FSK, 12 kHz deviation (e.g. Cardin S449, Sommer) |

You can add your own presets (for example `FM15k`, `Pagers`) — see [File formats](/subghz/file-format#setting-user).

## Adding your own frequencies {#adding-frequencies}

1. On the SD card, go to `/ext/subghz/assets/`.
2. Rename `setting_user.example` to `setting_user` (the `_user` files survive firmware updates).
3. Add lines in this format — always 9 digits, in Hz:
   ```text
   Frequency: 928000000
   Hopper_frequency: 345000000
   ```
4. Restart the Sub-GHz app.

Rules worth knowing:

- User frequencies are **appended after** the default list — scroll to the end of the list to find them.
- `Hopper_frequency` adds a frequency to hopping. Keep the hopper list short. Repeating a frequency makes the
  Flipper listen to it more often.
- To use **only** your own frequencies, change `#Add_standard_frequencies: true` to
  `Add_standard_frequencies: false`. Then you must fill **both** lists (`Frequency:` and `Hopper_frequency:`) —
  otherwise the main list is empty.
- `Default_frequency: 433920000` sets the frequency Read and Read RAW start with.

## Troubleshooting

- **Nothing is received** — frequency or modulation is wrong. Find the frequency with the
  [Frequency Analyzer](/subghz/frequency-analyzer), then try `AM650`, then the FM presets.
- **My frequency isn't in the list** — add it to `setting_user` (above). The analyzer will still round to the
  nearest list entry, so set the exact value manually in `Config`.
- **Transmission refused** — the frequency is outside the default TX window; check the table above. Don't enable
  the extended range just to "try".

## Related

- [Frequency Analyzer](/subghz/frequency-analyzer) · [Read](/subghz/read) · [Read RAW](/subghz/read-raw)
- [Radio settings](/subghz/settings) · [File formats](/subghz/file-format) · [External CC1101](/subghz/external-cc1101)
