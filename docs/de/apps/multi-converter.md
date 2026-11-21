---
title: Multi Converter
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MultiConverter.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Multi Converter

**Multi Converter** von [theisolinearchip](https://github.com/theisolinearchip/flipperzero_stuff/tree/main/applications/multi_converter)
ist ein Einheitenumrechner: du gibst einen Wert in einer Einheit ein und siehst ihn in einer anderen. Die App ist aus
dem früheren Dec/Hex Converter desselben Autors entstanden.

::: tip Unleashed
Multi Converter kommt mit den Community-[App-Packs](/de/apps/catalog#base-and-extra-packs), nicht mit der Firmware
selbst.
:::

![Multi Converter](/img/remote/283b5cf67616cbaa.png)

## Unterstützte Umrechnungen

| Gruppe | Einheiten |
|---|---|
| Zahlensysteme | Decimal, Hexadecimal, Binary |
| Temperatur | Celsius, Fahrenheit, Kelvin |
| Länge | Kilometers, Meters, Centimeters, Miles, Feet, Inches |
| Winkel | Degree, Radian |

## Anzeigemodus (einen Wert eingeben)

Das Tastenfeld auf dem Display hat die Tasten `0` bis `F`. Tasten, die für die aktuelle Ausgangseinheit keinen Sinn
ergeben, sind deaktiviert (zum Beispiel `2`–`F` bei Binär).

| Taste | Aktion |
|---|---|
| `0`–`F` | eine Ziffer eingeben |
| langer Druck auf `0` | einen **negativen** Wert umschalten |
| langer Druck auf `1` | ein **Dezimalkomma** einfügen (nur wo die Einheit es erlaubt) |
| `<` | das letzte Zeichen löschen |
| `#` | den **Unit Select Mode** öffnen |

Bewege dich mit den Pfeiltasten über das Tastenfeld und drücke <kbd>OK</kbd> auf einer Taste. Das Ergebnis in der
Zieleinheit erscheint auf dem Display.

![Einheitenauswahl](/img/remote/bedbc21af3d64be7.png)

## Unit Select Mode

1. Drücke `#`.
2. <kbd>←</kbd> / <kbd>→</kbd> wechseln zwischen **Ausgangs-** und **Zieleinheit**. Die Zielliste hängt von der
   gewählten Ausgangseinheit ab (umgerechnet wird nur innerhalb einer Gruppe).
3. <kbd>OK</kbd> speichert und kehrt in den Anzeigemodus zurück; <kbd>Back</kbd> kehrt zurück, ohne die Einheiten zu
   ändern.

## Bekannte Einschränkungen

- Sehr große Umrechnungen (Meilen in Zentimeter und Ähnliches) können aufgrund der Genauigkeitsgrenzen kleine
  Abweichungen in den Dezimalstellen zeigen.
- Die Überlaufprüfungen sind einfach gehalten: sehr lange Zahlen passen möglicherweise nicht in den Anzeigepuffer.
- Die Markierungen für negativen Wert und Dezimalkomma per langem Druck sind auf dem Display klein und leicht zu
  übersehen.

## Einheiten hinzufügen (für Entwickler)

1. Ergänze die Einheit im Enum `MultiConverterUnitType` in `multi_converter_definitions.h` (die Enum-Werte sind
   Array-Indizes).
2. Erhöhe `MULTI_CONVERTER_AVAILABLE_UNITS` in `multi_converter_units.h`.
3. Schreibe eine **convert**-Funktion und eine **allowed**-Prüfung (kann diese Einheit in jene umgerechnet werden)
   in `multi_converter_units.h` / `.c`.
4. Füge ein `MultiConverterUnit`-Struct für die neue Einheit hinzu.
5. Trage sie in das Array `multi_converter_available_units` ein. Die App erkennt sie automatisch.

## Verwandte Seiten

- [Apps im Lieferumfang von Unleashed](/de/apps/catalog)
- [Barcode Generator](/de/apps/barcode)
