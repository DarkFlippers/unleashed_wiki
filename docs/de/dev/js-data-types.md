---
title: "JavaScript: Datentypen"
sidebarTitle: "JS: Datentypen"
order: 240
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_data_types.md]
sources: [unleashed-docs]
---
# Datentypen

Die gängigen Datentypen in mJS, der JavaScript-Engine des Flipper Zero:

| Typ | Hinweise |
|---|---|
| `string` | Folge von Einzelbyte-Zeichen. **Keine UTF-8-Unterstützung.** |
| `number` | |
| `boolean` | |
| `foreign` | Zeiger auf eine C-Funktion oder C-Daten, intern von Modulen verwendet |
| `undefined` | |
| `null` | |
| `Object` | Datenstruktur mit benannten Feldern |
| `Array` | Besonderer Objekttyp: alle Elemente sind indiziert und haben denselben Typ |
| `ArrayBuffer` | Rohdatenpuffer |
| `DataView` | Schnittstelle für den Zugriff auf den Inhalt eines `ArrayBuffer` (typisierte Arrays wie `Uint8Array`) |

Die für diese Typen verfügbaren Methoden (`String.slice()`, `Array.push()`, `ArrayBuffer.slice()`, Felder
typisierter Arrays usw.) sind unter [Eingebaute Funktionen](/de/dev/js-builtin) aufgeführt.

::: tip
Da Strings Einzelbyte-Strings ohne UTF-8-Unterstützung sind, arbeiten `length`, `charCodeAt()` und `slice()` auf
Bytes, nicht auf Zeichen. Halte Strings in ASCII, um Überraschungen zu vermeiden.
:::
