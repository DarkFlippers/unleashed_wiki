---
title: Multi Converter
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MultiConverter.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Multi Converter

**Multi Converter** by [theisolinearchip](https://github.com/theisolinearchip/flipperzero_stuff/tree/main/applications/multi_converter)
is a unit converter: type a value in one unit and see it in another. It grew out of the author's earlier Dec/Hex
Converter.

::: tip Unleashed
Multi Converter comes with the community [app packs](/apps/catalog#base-and-extra-packs), not with the firmware itself.
:::

![Multi Converter](/img/remote/283b5cf67616cbaa.png)

## Supported conversions

| Group | Units |
|---|---|
| Number bases | Decimal, Hexadecimal, Binary |
| Temperature | Celsius, Fahrenheit, Kelvin |
| Length | Kilometers, Meters, Centimeters, Miles, Feet, Inches |
| Angle | Degree, Radian |

## Display mode (typing a value)

The on-screen keypad has the keys `0` to `F`. Keys that make no sense for the current source unit are disabled
(for example `2`-`F` for binary).

| Key | Action |
|---|---|
| `0`-`F` | type a digit |
| long press `0` | toggle a **negative** value |
| long press `1` | insert a **decimal point** (only where the unit allows it) |
| `<` | delete the last character |
| `#` | open **Unit Select Mode** |

Move over the keypad with the arrows and press <kbd>OK</kbd> on a key. The result in the destination unit is shown
on the screen.

![Unit select](/img/remote/bedbc21af3d64be7.png)

## Unit Select Mode

1. Press `#`.
2. <kbd>←</kbd> / <kbd>→</kbd> switch between the **origin** and **destination** unit. The destination list depends on
   the origin you chose (you can only convert within a group).
3. <kbd>OK</kbd> saves and returns to display mode; <kbd>Back</kbd> returns without changing the units.

## Known limitations

- Very large conversions (miles to centimeters and the like) can show small decimal deviations from precision limits.
- Overflow checks are basic: very long numbers may not fit the display buffer.
- The negative and decimal-point long-press markers are small on screen and easy to miss.

## Adding units (for developers)

1. Add the unit to the `MultiConverterUnitType` enum in `multi_converter_definitions.h` (enum values are array indices).
2. Increase `MULTI_CONVERTER_AVAILABLE_UNITS` in `multi_converter_units.h`.
3. Write a **convert** function and an **allowed** check (can this unit convert to that one) in
   `multi_converter_units.h` / `.c`.
4. Add a `MultiConverterUnit` struct for the new unit.
5. Add it to the `multi_converter_available_units` array. The app picks it up automatically.

## Related pages

- [Apps that ship with Unleashed](/apps/catalog)
- [Barcode Generator](/apps/barcode)
