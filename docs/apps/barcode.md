---
title: Barcode Generator
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BarcodeGenerator.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Barcode Generator

**Barcode Generator** draws a barcode on the Flipper's screen, so a scanner can read it straight off the display.
The original app by [McAzzaMan](https://github.com/McAzzaMan/flipperzero-firmware/tree/UPC-A_Barcode_Generator/applications/barcode_generator)
generates **UPC-A** barcodes (12 digits).

::: tip Unleashed
Barcode Generator is not a system app: it comes with the community [app packs](/apps/catalog#base-and-extra-packs)
(or install it yourself, see [Apps on the SD card](/apps/sd-card-apps)). The Unleashed documentation describes the
original UPC-A version; the version in the current pack may support more barcode types, so check its own screens.
:::

![Barcode Generator](/img/remote/2c7ed96cc46ad024.png)

## Usage

1. Open the app from `Main Menu → Apps` (look in its category folder).
2. Press <kbd>OK</kbd> to enter **edit mode**.
3. <kbd>←</kbd> / <kbd>→</kbd> move to the digit you want to change.
4. <kbd>↑</kbd> / <kbd>↓</kbd> change the digit's value.
5. Press <kbd>OK</kbd> again to leave edit mode. The barcode is redrawn for the new number.
6. Hold the Flipper screen in front of the scanner. Turn the backlight up if the scanner struggles.

![Edit mode](/img/remote/612b2014b71a93e4.png)

::: info UPC-A check digit
The last of the 12 UPC-A digits is a check digit computed from the other 11. If a scanner rejects the code, the
check digit probably does not match the rest of the number.
:::

## Related pages

- [Apps that ship with Unleashed](/apps/catalog)
- [Multi Converter](/apps/multi-converter)
