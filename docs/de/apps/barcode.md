---
title: Barcode Generator
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BarcodeGenerator.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Barcode Generator

**Barcode Generator** zeichnet einen Barcode auf das Display des Flipper, sodass ein Scanner ihn direkt vom
Bildschirm ablesen kann. Die ursprüngliche App von
[McAzzaMan](https://github.com/McAzzaMan/flipperzero-firmware/tree/UPC-A_Barcode_Generator/applications/barcode_generator)
erzeugt **UPC-A**-Barcodes (12 Ziffern).

::: tip Unleashed
Barcode Generator ist keine System-App: sie kommt mit den Community-[App-Packs](/de/apps/catalog#base-and-extra-packs)
(oder du installierst sie selbst, siehe [Apps auf der SD-Karte](/de/apps/sd-card-apps)). Die Unleashed-Dokumentation
beschreibt die ursprüngliche UPC-A-Version; die Version im aktuellen Pack unterstützt möglicherweise weitere
Barcode-Typen, sieh dir also ihre eigenen Bildschirme an.
:::

![Barcode Generator](/img/remote/2c7ed96cc46ad024.png)

## Verwendung

1. Öffne die App über `Main Menu → Apps` (sie liegt in ihrem Kategorie-Ordner).
2. Drücke <kbd>OK</kbd>, um in den **Bearbeitungsmodus** zu wechseln.
3. <kbd>←</kbd> / <kbd>→</kbd> springen zu der Ziffer, die du ändern möchtest.
4. <kbd>↑</kbd> / <kbd>↓</kbd> ändern den Wert der Ziffer.
5. Drücke erneut <kbd>OK</kbd>, um den Bearbeitungsmodus zu verlassen. Der Barcode wird für die neue Nummer neu
   gezeichnet.
6. Halte das Display des Flipper vor den Scanner. Erhöhe die Hintergrundbeleuchtung, wenn der Scanner Probleme hat.

![Bearbeitungsmodus](/img/remote/612b2014b71a93e4.png)

::: info UPC-A-Prüfziffer
Die letzte der 12 UPC-A-Ziffern ist eine Prüfziffer, die aus den anderen 11 berechnet wird. Wenn ein Scanner den
Code ablehnt, passt die Prüfziffer wahrscheinlich nicht zum Rest der Nummer.
:::

## Verwandte Seiten

- [Apps im Lieferumfang von Unleashed](/de/apps/catalog)
- [Multi Converter](/de/apps/multi-converter)
