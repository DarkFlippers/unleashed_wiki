---
title: "JavaScript: flipper"
sidebarTitle: "JS: flipper"
order: 300
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_flipper.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_flipper.c]
sources: [unleashed-docs, unleashed-src]
---
# Modul flipper

Werte und Methoden zum Abfragen von Geräteinformationen. Lade zuerst das Modul:

```js
let flipper = require("flipper");
```

## Werte

### firmwareVendor
Ein String, der die Firmware auf dem Gerät benennt. Die offizielle Firmware meldet `"flipperdevices"`.

::: tip Unleashed
Unleashed meldet `"unleashed"`.
:::

Verwende das **nicht**, um zu prüfen, ob eine Funktion verfügbar ist. Nutze stattdessen die
[SDK-Kompatibilitätsfunktionen](/de/dev/js-builtin#sdk-compatibility).

### jsSdkVersion
Version des JavaScript-SDK. Auch hier: **nicht** für Funktionsprüfungen verwenden, siehe
[SDK-Kompatibilität](/de/dev/js-builtin#sdk-compatibility).

## Methoden

### getModel()
Gibt das Gerätemodell zurück.

```js
flipper.getModel(); // "Flipper Zero"
```

### getName()
Gibt den Namen des virtuellen Delfins zurück (den Gerätenamen).

```js
flipper.getName(); // "Fur1pp44"
```

### getBatteryCharge()
Gibt den Akkuladestand in Prozent zurück.

```js
flipper.getBatteryCharge(); // 100
```
