---
title: Dangerous settings
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/furi_hal]
sources: [unleashed-docs, unleashed-src]
---
# Dangerous settings: extended Sub-GHz range

Unleashed can let the CC1101 radio work **outside its official frequency range**. You almost certainly don't need
it, and turning it on can cost you the radio chip.

::: danger Read this first
1. Don't do this unless you know exactly what you are doing.
2. You don't need the extended range for almost any use case.
3. Transmitting outside the hardware specification **can damage your hardware**.
4. Neither the Flipper Devices team nor the Unleashed developers are responsible for any damage caused by custom
   firmware or by extending the frequency range.
:::

## You probably don't need it: there is no region lock

::: tip Unleashed
In Unleashed, **all regional TX restrictions are removed by default**. Every frequency inside the chip's supported range
transmits with no extra steps. Don't use the dangerous setting to "unlock your region". It is not needed for that.
:::

If transmission is blocked on a frequency, first check that the frequency is inside the normal TX range below. Outside it,
the firmware logs `Frequency blocked - outside default range`.

## Frequency ranges

| | Ranges |
|---|---|
| CC1101 datasheet | 300–348 MHz, 386–464 MHz, 778–928 MHz |
| Unleashed default **TX** range | ≈ 300–350 MHz, 387–467.75 MHz, 779–928 MHz (widened to include 350 MHz and 467 MHz) |
| TX with `dangerous_settings` enabled | **281–361 MHz, 378–481 MHz, 749–962 MHz** |

The extended range matches the YARD Stick One extended range (per the firmware source). Outside the datasheet ranges
the chip works out of spec, and transmitting there may damage it.

## How to enable it

1. Take the microSD card out, or connect with qFlipper / the file manager of your choice.
2. Open the file **`/ext/subghz/assets/dangerous_settings`**. It looks like this:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Read the comments, then change `false` to `true`:
   ```text
   yes_i_want_to_destroy_my_flipper: true
   ```
4. Save the file and reboot the Flipper. The setting is read at startup.

To go back, set the value to `false` and reboot.

::: warning Updates
The file is part of the firmware resources. An update may overwrite it with the default `false`. Check it after updating
if you rely on the setting.
:::

## Related

- Sub-GHz frequencies and presets, adding your own frequencies: [Frequencies](/subghz/frequencies)
- Sub-GHz settings inside the app: [Sub-GHz settings](/subghz/settings)
- External CC1101 module: [External CC1101](/subghz/external-cc1101)

Use the radio only on your own devices and in line with your local radio regulations.
