---
title: "JavaScript: blebeacon"
sidebarTitle: "JS: blebeacon"
order: 420
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_blebeacon.c]
sources: [unleashed-src]
---
# Modul BLE-Beacon

Ein Unleashed-Extra, in der Stock-Firmware gibt es das nicht. Es sendet ein eigenes Bluetooth-LE-Advertisement — deine MAC-Adresse, deine Nutzdaten. Es ist dasselbe „zusätzliche Beacon", das die Firmware für Hintergrund-Advertising nutzt, es läuft also neben der normalen Bluetooth-Verbindung.

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");
```

Beispielskript: `/ext/apps/Scripts/js_examples/blebeacon.js`.

Beim Beenden des Skripts stellt das Modul die vorherige Beacon-Konfiguration, die vorherigen Daten und den vorherigen Zustand wieder her — außer du hast das mit `keepAlive(true)` abbestellt.

## Methoden

### isActive()
- **Rückgabe:** boolean, ob das Beacon gerade sendet. Prüfe das gleich zu Beginn: ein Beacon, das ein früheres Skript laufen ließ, sendet noch.

### setConfig()
Setzt die Parameter des Advertisements.

- **Parameter:**
  - `mac`: `Uint8Array` mit genau 6 Bytes. Alles andere wirft `Wrong MAC address`;
  - `power` (optional): Sendeleistung auf der GapAdvPowerLevel-Skala, `0x00` (-40 dBm) bis `0x1F` (+6 dBm). Standard sind 0 dBm, Werte außerhalb des Bereichs werden begrenzt;
  - `minInterval` (optional): minimales Advertising-Intervall in ms. Standard 50, Werte unter 20 werden auf 20 angehoben, das Maximum ist 255;
  - `maxInterval` (optional): maximales Intervall in ms. Standard 150, nie kleiner als `minInterval`, Maximum 255.

### setData()
- **Parameter:** `data`, ein `Uint8Array` mit den Nutzdaten des Advertisements. Die Hardware-Grenze liegt bei 31 Bytes.

### start()
Startet das Senden.

### stop()
Stoppt das Senden.

### keepAlive()
- **Parameter:** `keep`, boolean. Mit `true` sendet das Beacon nach dem Skriptende weiter und nichts wird wiederhergestellt. Standard ist `false`.

## Beispiel

Fünf Sekunden lang eine kurze Nutzlast senden:

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");

if (blebeacon.isActive()) {
    blebeacon.stop();
}
blebeacon.keepAlive(false);

blebeacon.setConfig(Uint8Array([0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x01]), 0x1F, 50, 150);
blebeacon.setData(Uint8Array([0x02, 0x01, 0x06, 0x03, 0xFF, 0xAB, 0xCD]));

blebeacon.start();
print("Advertising");
delay(5000);
blebeacon.stop();
print("Stopped");
```

## Verwandte Themen

- [JavaScript-Übersicht](/de/dev/js-about)
- [Datentypen](/de/dev/js-data-types) — wie `Uint8Array` in mJS funktioniert
