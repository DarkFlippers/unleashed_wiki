---
title: Barcode Generator
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BarcodeGenerator.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Barcode Generator

**Barcode Generator** dibuja un código de barras en la pantalla del Flipper, de modo que un escáner pueda leerlo
directamente del display. La app original de
[McAzzaMan](https://github.com/McAzzaMan/flipperzero-firmware/tree/UPC-A_Barcode_Generator/applications/barcode_generator)
genera códigos de barras **UPC-A** (12 dígitos).

::: tip Unleashed
Barcode Generator no es una app de sistema: viene con los [packs de apps](/es/apps/catalog#base-and-extra-packs) de la
comunidad (o instálala tú mismo, consulta [Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps)). La documentación de
Unleashed describe la versión UPC-A original; la versión del pack actual puede admitir más tipos de código de barras,
así que revisa sus propias pantallas.
:::

![Barcode Generator](/img/remote/2c7ed96cc46ad024.png)

## Uso

1. Abre la app desde `Main Menu → Apps` (búscala en su carpeta de categoría).
2. Pulsa <kbd>OK</kbd> para entrar en el **modo de edición**.
3. <kbd>←</kbd> / <kbd>→</kbd> te llevan al dígito que quieras cambiar.
4. <kbd>↑</kbd> / <kbd>↓</kbd> cambian el valor del dígito.
5. Pulsa <kbd>OK</kbd> otra vez para salir del modo de edición. El código de barras se redibuja con el nuevo número.
6. Sostén la pantalla del Flipper delante del escáner. Sube la retroiluminación si el escáner tiene dificultades.

![Modo de edición](/img/remote/612b2014b71a93e4.png)

::: info Dígito de control de UPC-A
El último de los 12 dígitos de UPC-A es un dígito de control calculado a partir de los otros 11. Si un escáner rechaza
el código, probablemente el dígito de control no concuerde con el resto del número.
:::

## Páginas relacionadas

- [Aplicaciones incluidas en Unleashed](/es/apps/catalog)
- [Multi Converter](/es/apps/multi-converter)
