---
title: Multi Converter
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MultiConverter.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Multi Converter

**Multi Converter**, de [theisolinearchip](https://github.com/theisolinearchip/flipperzero_stuff/tree/main/applications/multi_converter),
es un conversor de unidades: escribe un valor en una unidad y lo verás en otra. Surgió a partir del anterior Dec/Hex
Converter del mismo autor.

::: tip Unleashed
Multi Converter viene con los [packs de apps](/es/apps/catalog#base-and-extra-packs) de la comunidad, no con el propio
firmware.
:::

![Multi Converter](/img/remote/283b5cf67616cbaa.png)

## Conversiones admitidas

| Grupo | Unidades |
|---|---|
| Bases numéricas | Decimal, Hexadecimal, Binario |
| Temperatura | Celsius, Fahrenheit, Kelvin |
| Longitud | Kilómetros, metros, centímetros, millas, pies, pulgadas |
| Ángulo | Grado, radián |

## Modo de visualización (escribir un valor)

El teclado en pantalla tiene las teclas de `0` a `F`. Las teclas que no tienen sentido para la unidad de origen actual
están desactivadas (por ejemplo, de `2` a `F` en binario).

| Tecla | Acción |
|---|---|
| `0`-`F` | escribir un dígito |
| pulsación larga en `0` | conmutar un valor **negativo** |
| pulsación larga en `1` | insertar un **punto decimal** (solo donde la unidad lo permite) |
| `<` | borrar el último carácter |
| `#` | abrir el **Unit Select Mode** |

Desplázate por el teclado con las flechas y pulsa <kbd>OK</kbd> sobre una tecla. El resultado en la unidad de destino
se muestra en la pantalla.

![Selección de unidades](/img/remote/bedbc21af3d64be7.png)

## Unit Select Mode

1. Pulsa `#`.
2. <kbd>←</kbd> / <kbd>→</kbd> alternan entre la unidad de **origen** y la de **destino**. La lista de destino depende
   del origen que hayas elegido (solo se puede convertir dentro de un grupo).
3. <kbd>OK</kbd> guarda y vuelve al modo de visualización; <kbd>Back</kbd> vuelve sin cambiar las unidades.

## Limitaciones conocidas

- Las conversiones muy grandes (de millas a centímetros y similares) pueden mostrar pequeñas desviaciones decimales por
  los límites de precisión.
- Las comprobaciones de desbordamiento son básicas: los números muy largos pueden no caber en el búfer de pantalla.
- Los indicadores de pulsación larga para el signo negativo y el punto decimal son pequeños en pantalla y fáciles de
  pasar por alto.

## Añadir unidades (para desarrolladores)

1. Añade la unidad al enum `MultiConverterUnitType` de `multi_converter_definitions.h` (los valores del enum son
   índices de array).
2. Incrementa `MULTI_CONVERTER_AVAILABLE_UNITS` en `multi_converter_units.h`.
3. Escribe una función **convert** y una comprobación **allowed** (si esa unidad puede convertirse a la otra) en
   `multi_converter_units.h` / `.c`.
4. Añade una estructura `MultiConverterUnit` para la nueva unidad.
5. Añádela al array `multi_converter_available_units`. La app la detecta automáticamente.

## Páginas relacionadas

- [Aplicaciones incluidas en Unleashed](/es/apps/catalog)
- [Barcode Generator](/es/apps/barcode)
