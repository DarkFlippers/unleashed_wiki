---
title: "JavaScript: eingebaute Funktionen"
sidebarTitle: "JS: eingebaute Funktionen"
order: 250
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_builtin.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/js_modules.c]
sources: [unleashed-docs, unleashed-src]
---
# Eingebaute Funktionen

Diese Funktionen und Objekte stehen in jedem Skript ohne `require()` zur Verfügung.

## Globale Funktionen

### require()
Lädt ein Modul-Plugin. Siehe [JS-Module verwenden](/de/dev/js-modules).

- **Parameter:** Modulname

```js
let serial = require("serial"); // Load "serial" module
```

### delay()
- **Parameter:** Verzögerung in ms

```js
delay(500); // Delay for 500ms
```

### print()
Gibt eine Meldung auf der Konsole auf dem Display aus (oder in der CLI, wenn das Skript von dort gestartet wurde).

- **Parameter:** beliebig viele Argumente vom Typ String, Number, Bool oder `undefined`

```js
print("string1", "string2", 123);
```

### Objekt console
Wie `print()`, schreibt aber **nur auf die serielle Konsole (das Log)**, mit dem jeweiligen Log-Level:

- `console.log()`
- `console.warn()`
- `console.error()`
- `console.debug()`

### load()
Führt eine JS-Datei aus und gibt einen Wert daraus zurück.

- **Parameter:**
  - Pfad zur Datei;
  - optionales Objekt, das beim Ausführen der Datei als globaler Scope dient.

```js
load("/ext/apps/Scripts/script.js");
```

### chr()
Wandelt einen ASCII-Zeichencode in eine Zeichenkette um.

```js
chr(65); // "A"
```

### die()
Beendet das Skript mit der angegebenen Meldung.

```js
die("Some error occurred");
```

### parseInt()
Wandelt eine Zeichenkette in eine Zahl um, optional mit einer Basis.

```js
parseInt("123"); // 123
parseInt("7b", 16); // 123
```

## Number

### Number.toString()
Wandelt eine Zahl in eine Zeichenkette um, optional mit einer Basis.

```js
let num = 123;
num.toString(); // "123"
num.toString(16); // "0x7b"
```

## ArrayBuffer

**Felder:** `byteLength`, die Länge des Puffers in Bytes.

### ArrayBuffer.slice()
Erzeugt einen `ArrayBuffer`, der einen Teil des Puffers enthält.

- **Parameter:** Startindex; optionaler, nicht eingeschlossener Endindex.

```js
Uint8Array([1, 2, 3]).buffer.slice(0, 1) // ArrayBuffer([1])
```

## DataView (typisierte Arrays)

Wrapper um `ArrayBuffer` mit festem Elementtyp:

- `Uint8Array`, `Int8Array`
- `Uint16Array`, `Int16Array`
- `Uint32Array`, `Int32Array`

**Felder:**

- `byteLength`: Länge des Puffers in Bytes;
- `length`: Länge des Puffers in typisierten Elementen;
- `buffer`: der zugrunde liegende `ArrayBuffer`.

## Array

**Felder:** `length`, die Anzahl der Elemente.

### Array.splice()
Entfernt Elemente aus dem Array und gibt sie als neues Array zurück.

- **Parameter:** Startindex; optionale Anzahl der zu entnehmenden Elemente.

```js
let arr = [1, 2, 3];
arr.splice(1); // [2, 3]
arr; // [1]
```

### Array.push()
Fügt einen Wert am Ende des Arrays hinzu.

```js
let arr = [1, 2];
arr.push(3);
arr; // [1, 2, 3]
```

## String

**Felder:** `length`, die Anzahl der Zeichen (Bytes).

### String.charCodeAt()
Gibt den Zeichencode an einem Index zurück.

```js
"A".charCodeAt(0) // 65
```

### String.at()
Dasselbe wie `String.charCodeAt()`.

### String.indexOf()
Gibt den Index des ersten Vorkommens einer Teilzeichenkette zurück oder `-1`, wenn sie nicht gefunden wird.

- **Parameter:** gesuchte Teilzeichenkette; optionaler Startindex.

```js
"Example".indexOf("amp") // 2
```

### String.slice()
Gibt die Teilzeichenkette zwischen zwei Indizes zurück.

- **Parameter:** Startindex; optionaler, nicht eingeschlossener Endindex.

```js
"Example".slice(2) // "ample"
```

### String.toUpperCase()

```js
"Example".toUpperCase() // "EXAMPLE"
```

### String.toLowerCase()

```js
"Example".toLowerCase() // "example"
```

## Skriptpfade

### __dirname
Pfad zum Verzeichnis, das das aktuelle Skript enthält.

```js
print(__dirname); // /ext/apps/Scripts
```

### __filename
Pfad zur Datei des aktuellen Skripts.

```js
print(__filename); // /ext/apps/Scripts/path.js
```

## SDK-Kompatibilität {#sdk-compatibility}

Skripte können prüfen, welche JS-SDK-Version und welche zusätzlichen Features die Firmware bereitstellt. Verwende
dafür **nicht** `flipper.firmwareVendor` oder `flipper.jsSdkVersion`. Nutze die folgenden Funktionen.

Im aktuellen Unleashed ist die JS-SDK-Version **1.0**.

### sdkCompatibilityStatus()
Prüft die Kompatibilität zwischen dem Skript und dem JS-SDK der Firmware.

- **Rückgabe:**
  - `"compatible"`, wenn Skript und JS-SDK kompatibel sind;
  - `"firmwareTooOld"`, wenn die erwartete Major-Version größer als die der Firmware ist oder die erwartete
    Minor-Version größer als die der Firmware ist;
  - `"firmwareTooNew"`, wenn die erwartete Major-Version niedriger als die der Firmware ist.

```js
sdkCompatibilityStatus(0, 3); // "compatible"
```

### isSdkCompatible()
Dieselbe Prüfung, gibt einen Boolean zurück.

```js
isSdkCompatible(0, 3); // true
```

### checkSdkCompatibility()
Sind die Versionen nicht kompatibel, fragt die Funktion den Benutzer, ob das Skript weiterlaufen soll. Sind sie
kompatibel, tut sie nichts.

```js
checkSdkCompatibility(0, 3);
```

### doesSdkSupport()
Prüft, ob **alle** aufgeführten Zusatzfeatures vom Interpreter unterstützt werden.

```js
doesSdkSupport(["gui-widget"]); // true
```

### checkSdkFeatures()
Dieselbe Prüfung, fragt aber den Benutzer, ob weitergemacht werden soll, wenn einige Features fehlen.

```js
checkSdkFeatures(["gui-widget"]);
```

::: tip Unleashed
Von Unleashed unterstützte Feature-Namen: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`,
`gui-widget-extras` sowie die Unleashed-Zusatzmodule `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`,
`usbdisk`, `usbdisk-createimage`, `vgm`. Siehe [JavaScript – Übersicht](/de/dev/js-about#unleashed-extras).
:::

Typisches Muster für ein optionales Feature:

```js
if (doesSdkSupport(["subghz"])) {
    let subghz = require("subghz");
    // ...
}
```
