---
title: "JavaScript: infrared"
sidebarTitle: "JS: infrared"
order: 410
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_infrared]
sources: [unleashed-src]
---
# Modul Infrarot

Ein Unleashed-Extra, in der Stock-Firmware gibt es das nicht. Es sendet IR-Signale aus einem Skript, entweder über den Protokollnamen oder als rohe Liste von Timings. Eine Empfangsseite gibt es nicht — nimm ein Signal vorher mit der Infrared-App auf.

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");
```

Der Feature-Name ist `infrared-send`, der Modulname `infrared`.

Beispielskript: `/ext/apps/Scripts/js_examples/infrared-send.js`.

## Methoden

### sendSignal()
Sendet ein Signal über ein Protokoll, das die Firmware kennt.

- **Parameter:**
  - `protocol`: `"NEC"`, `"NECext"`, `"NEC42"`, `"NEC42ext"`, `"Samsung32"`, `"RC6"`, `"RC5"`, `"RC5X"`, `"SIRC"`, `"SIRC15"`, `"SIRC20"`, `"Kaseikyo"` oder `"RCA"`;
  - `address`: Zahl;
  - `command`: Zahl;
  - `options` (optional): `{ repeat?: boolean, times?: number }`. `repeat` markiert das Signal als Wiederholungspaket, `times` ist die Anzahl der Sendungen (Standard 1).

```js
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
```

In `.ir`-Dateien liegen Address und Command als Little-Endian-Hex, ein JS-Zahlenliteral ist dagegen Big-Endian. Aus `A9 00 00 00` in der Datei wird hier `0x000000A9`, dreh die Bytes also um, bevor du sie einsetzt.

### sendRawSignal()
Sendet ein Signal über seine Ein/Aus-Timings, für Fernbedienungen, die kein Protokoll abdeckt.

- **Parameter:**
  - `timings`: Array von Zahlen, Dauern in Mikrosekunden;
  - `startFromMark` (optional): boolean, ob der erste Wert ein Impuls und keine Pause ist. Standard `true`;
  - `advancedSettings` (optional): `{ frequency: number, dutyCycle: number }`. Sobald das Objekt angegeben ist, sind beide Felder Pflicht. Ohne es liegt der Träger bei 38000 Hz mit einem Tastverhältnis von 0,33.

## Beispiel

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");

// Samsung TV, volume down
print("Sending Samsung32");
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
delay(1000);

// Three presses in a row
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b, { times: 3 });
delay(1000);

// Raw timings at 36 kHz
infrared.sendRawSignal([3298, 1571, 442, 368, 442, 367], true, {
  frequency: 36000,
  dutyCycle: 0.33,
});
print("Done");
```

## Verwandte Themen

- [IR-Dateiformat](/de/infrared/file-format) — woher Address und Command kommen
- [Unterstützte IR-Protokolle](/de/infrared/protocols)
- [JavaScript-Übersicht](/de/dev/js-about)
