---
title: Radio Settings
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/radio_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://docs.flipper.net/zero/sub-ghz]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Radio Settings

`Main Menu → Sub-GHz → Radio Settings` holds the settings that apply to the whole Sub-GHz app: which radio is used,
transmit power, file naming and rolling-counter behaviour. Settings for receiving (frequency, modulation, hopping,
filters) live in `Read → Config` — see [Read](/subghz/read#config).

::: tip Unleashed
In stock firmware this menu only switches between the internal and external module. Unleashed adds **TX Power**,
**Protocol Names**, **Counter Incr.**, and in Debug mode **Ext Amp & LEDs** and **Debug Pin**.
:::

## Menu items

![Radio Settings: Module, TX Power, Protocol Names and Counter Incr.](/screens/subghz/radio_settings.png)

| Item | Values | What it does |
|---|---|---|
| `Module` | `Internal`, `External` | Radio used for receive and transmit. `External` is offered only when an external CC1101 is detected on GPIO; if it doesn't respond, the Flipper falls back to `Internal` |
| `TX Power` | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | Transmit power. `Preset` = whatever the modulation preset defines (default). Lower values are handy for tests at short range |
| `Protocol Names` | `OFF` / `ON` | When `ON`, auto-generated file names contain the protocol name + timestamp instead of only a timestamp/random name |
| `Counter Incr.` | `+1`, `+2`, `+3` (normal) | How much the rolling counter is increased per transmission for dynamic protocols. Default `+1` |

Extra items in **Debug mode** (`Settings → System → Debug → ON`):

| Item | Values | What it does |
|---|---|---|
| `Counter Incr.` | `+1` `+2` `+3` `+4` `+5` `+10` `+50` `OVFL` `OFEX` `No` `-1` `-2` `-3` `-4` `-5` `-10` `-50` | Full list of counter steps for experiments: big jumps, `OVFL` (step 65535), `OFEX` (special mode), `No` (counter not changed) and negative steps |
| `Ext Amp & LEDs` | `ON` / `OFF` | Controls the amplifier / LED pin of external modules (GPIO PC3, as on E07 modules). Default `ON`. Turn off if your module uses that pin for something else |
| `Debug Pin` | `OFF` / `17(1W)` | Mirrors the radio data signal to GPIO pin 17 (1-Wire) — for protocol development with a logic analyser |

`TX Power`, `Protocol Names` and `Ext Amp & LEDs` are saved immediately (to `/ext/subghz/assets/last_subghz.settings`).
`Counter Incr.` is not saved: it stays until the Flipper reboots, then returns to `+1`.

::: warning Counter increment
Large or negative counter steps are for experiments **on your own receivers**. Jumping a counter far ahead
permanently moves the receiver's stored counter past your original remote; going back makes the receiver ignore you.
For coexisting with the original remote use [Counter modes](/subghz/counter-mode) or create a new remote with
[Add Manually](/subghz/add-manually). Background: [Rolling codes](/subghz/rolling-codes).
:::

## Other settings that live on the SD card

| File | Purpose | Details |
|---|---|---|
| `/ext/subghz/assets/setting_user` | Extra frequencies, hopper list, default frequency, custom modulation presets | [Frequencies](/subghz/frequencies#adding-frequencies), [File formats](/subghz/file-format#setting-user) |
| `/ext/subghz/assets/dangerous_settings` | Extended (out-of-spec) frequency range | [Frequencies](/subghz/frequencies#extended-range) |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Your own KeeLoq manufacturer keys | [File formats](/subghz/file-format#keeloq-mfcodes-user), [KeeLoq](/subghz/keeloq) |
| `/ext/subghz/assets/last_subghz.settings` | Last used frequency, modulation, filters, analyzer trigger — written by the app | do not edit by hand |

Files ending in `.example` are templates: rename to `…_user` to activate. `_user` files are not overwritten by
firmware updates.

## Troubleshooting

- **`Module` only shows `Internal`** — no external CC1101 detected. Check wiring and power, then re-enter the menu.
  See [External CC1101](/subghz/external-cc1101).
- **Signals are weak when sending** — check `TX Power` isn't set to a negative value.
- **File names are just dates** — enable `Protocol Names`.
- **No `Ext Amp & LEDs` / `Debug Pin` items** — they appear only in Debug mode.

## Related

- [Read → Config](/subghz/read#config) · [Frequencies](/subghz/frequencies) · [External CC1101](/subghz/external-cc1101)
- [Counter modes](/subghz/counter-mode) · [File formats](/subghz/file-format) · [Dangerous settings](/start/dangerous-settings)
