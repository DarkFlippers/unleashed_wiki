---
title: Sentry Safe
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Sentry Safe

The **Sentry Safe** plugin by [H4ckd4ddy](https://github.com/H4ckd4ddy/flipperzero-sentry-safe-plugin) opens
Sentry Safe and Master Lock electronic safes **without the PIN code**, using a known vulnerability in their keypad
connection. The vulnerability and a demo are described in
[bypass-sentry-safe](https://github.com/H4ckd4ddy/bypass-sentry-safe).

::: warning
Only use it on a safe you own. Opening someone else's safe is illegal.
:::

::: tip Unleashed
Sentry Safe is a GPIO plugin from the community [app packs](/apps/catalog#base-and-extra-packs), it is not part of
the firmware itself.
:::

## Wiring

The Flipper connects to two wires of the safe (black and green). The
[vulnerability write-up](https://github.com/H4ckd4ddy/bypass-sentry-safe) shows where to reach them.

| Flipper GPIO pin | Safe wire |
|---|---|
| 8 (GND) | black |
| 15 (C1) | green |

Pin numbers are the numbers printed on the Flipper's GPIO header, see [GPIO pinout](/gpio/pinout).

## Usage

1. Open the **Sentry Safe** app from `Main Menu → Apps` (it is a GPIO plugin, look in the GPIO folder).
2. Connect the wires as shown on the app screen and in the table above.
3. Press <kbd>OK</kbd> (enter).
4. Open the safe.

## Troubleshooting

- Nothing happens: check that GND really goes to the black wire and C1 (pin 15) to the green wire, and that the
  contact is solid.

## Related pages

- [GPIO pinout](/gpio/pinout)
- [Apps that ship with Unleashed](/apps/catalog)
