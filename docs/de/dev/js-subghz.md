---
title: "JavaScript: subghz"
sidebarTitle: "JS: subghz"
order: 400
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_subghz]
sources: [unleashed-src]
---
# Modul Sub-GHz

Ein Unleashed-Extra, in der Stock-Firmware gibt es das nicht. Es gibt einem Skript das Sub-GHz-Funkmodul: zwischen Empfang und Ruhezustand umschalten, den Signalpegel lesen, die Frequenz wechseln, eine gespeicherte `.sub`-Datei senden.

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");
subghz.setup();
```

`setup()` sucht zuerst nach einem externen CC1101-Modul und nimmt sonst das eingebaute Funkmodul. Vorher wirft jede andere Methode `Radio is not setup`.

Beispielskript: `/ext/apps/Scripts/js_examples/subghz.js`.

## Methoden

### setup()
Initialisiert das Funkmodul und wählt das Gerät. Startet bei 433920000 Hz im Zustand `IDLE`. Wirft einen Fehler, wenn das Funkmodul schon initialisiert ist.

### end()
Legt das Funkmodul schlafen und gibt das Gerät frei. Passiert am Skriptende automatisch. Ein `setup()` danach sucht erneut nach einem externen Modul.

### setRx()
Schaltet das Funkmodul auf Empfang.

### setIdle()
Schaltet das Funkmodul in den Ruhezustand. Nur in diesem Zustand lässt sich die Frequenz ändern.

### getRssi()
Signalpegel auf der aktuellen Frequenz, in dBm.

- **Rückgabe:** `number` oder `undefined`, wenn das Funkmodul nicht auf Empfang steht.

### getState()
- **Rückgabe:** `"RX"`, `"TX"` oder `"IDLE"`.

### getFrequency()
- **Rückgabe:** die aktuelle Frequenz in Hz, als Zahl.

### setFrequency()
Stimmt das Funkmodul ab. Wirft einen Fehler, wenn es nicht `IDLE` ist oder die Frequenz außerhalb der Bänder liegt, die das Gerät kann.

- **Parameter:** `frequency`, eine Zahl in Hz — zum Beispiel `433920000`.
- **Rückgabe:** die Frequenz, auf die das Funkmodul tatsächlich abgestimmt hat. Ein CC1101 trifft nicht jeden Wert genau, es nimmt deshalb den nächstmöglichen.

### isExternal()
- **Rückgabe:** boolean — `true`, wenn ein externes CC1101 genutzt wird, `false` beim eingebauten Funkmodul.

### transmitFile()
Sendet eine `.sub`-Datei. Frequenz und Modulation kommen aus der Datei, nicht aus `setFrequency()`. Gibt `true` zurück; bei jedem Problem (Datei fehlt, fehlerhafter Header, nicht unterstützte Frequenz, unbekanntes Preset) wirft es einen Fehler. Das Funkmodul bleibt danach auf `IDLE`.

- **Parameter:**
  - `path`: vollständiger Pfad zur Datei, z. B. `"/ext/subghz/0.sub"`;
  - `repeat` (optional): wie oft gesendet wird.

Ohne `repeat` gehen RAW-Dateien einmal raus und Protokolldateien 10-mal, was dem Halten der Taste an einer echten Fernbedienung entspricht. `CAME Atomo`, `CAME TWEE`, `Hormann HSM`, `Nice FloR-S` und `Power Smart` senden pro Durchgang schon mehrere Pakete, dort ist der Standard 1.

## Beispiel

Auf 433,92 MHz lauschen, dann einen gespeicherten Schlüssel senden:

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");

subghz.setup();
subghz.setIdle();
subghz.setFrequency(433920000);

subghz.setRx();
print("RSSI:", subghz.getRssi(), "dBm, external:", subghz.isExternal());
delay(1000);

print("Sending 0.sub");
subghz.transmitFile("/ext/subghz/0.sub");
print("Sent");

subghz.end();
```

## Verwandte Themen

- [Sub-GHz-Dateiformat](/de/subghz/file-format) — was in einer `.sub` steht
- [Externe CC1101-Module](/de/subghz/external-cc1101)
- [JavaScript-Übersicht](/de/dev/js-about)
