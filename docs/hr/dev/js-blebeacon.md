---
title: "JavaScript: blebeacon"
sidebarTitle: "JS: blebeacon"
order: 420
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_blebeacon.c]
sources: [unleashed-src]
---
# Modul BLE beacon

Dodatak specifičan za Unleashed, nije prisutan u tvorničkom firmveru. Emitira prilagođeno Bluetooth LE oglašavanje — s vašom vlastitom MAC adresom i vašim vlastitim sadržajem (payloadom). Ovo je isti "dodatni beacon" koji firmver koristi za pozadinsko oglašavanje, pa radi usporedno s uobičajenom Bluetooth vezom.

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");
```

Primjer skripte: `/ext/apps/Scripts/js_examples/blebeacon.js`.

Kada skripta završi s radom, modul vraća konfiguraciju, podatke i stanje beacona kakvi su bili prije — osim ako mu niste zadali da to ne čini pomoću `keepAlive(true)`.

## Metode

### isActive()
- **Vraća:** boolean (logičku vrijednost), oglašava li beacon u ovom trenutku. Provjerite ovo na početku: beacon koji je ostavila pokrenutim prethodna skripta i dalje je aktivan.

### setConfig()
Postavlja parametre oglašavanja.

- **Parametri:**
  - `mac`: `Uint8Array` od točno 6 bajtova. Sve ostalo izbacuje pogrešku `Wrong MAC address`;
  - `power` (neobavezno): snaga odašiljanja na ljestvici GapAdvPowerLevel, od `0x00` (-40 dBm) do `0x1F` (+6 dBm). Zadano je 0 dBm, vrijednosti izvan raspona se ograničavaju na granice raspona;
  - `minInterval` (neobavezno): minimalni interval oglašavanja u ms. Zadano 50, vrijednosti ispod 20 podižu se na 20, maksimum je 255;
  - `maxInterval` (neobavezno): maksimalni interval u ms. Zadano 150, nikada manji od `minInterval`, maksimum 255.

### setData()
- **Parametri:** `data`, `Uint8Array` s payloadom oglašavanja. Hardversko ograničenje je 31 bajt.

### start()
Pokreće oglašavanje.

### stop()
Zaustavlja oglašavanje.

### keepAlive()
- **Parametri:** `keep`, boolean. S vrijednošću `true` beacon se nastavlja oglašavati i nakon završetka skripte te se ništa ne vraća na prijašnje stanje. Zadano je `false`.

## Primjer

Oglašavanje kratkog payloada u trajanju od pet sekundi:

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

## Povezano

- [Pregled JavaScripta](/hr/dev/js-about)
- [Tipovi podataka](/hr/dev/js-data-types) — kako `Uint8Array` radi u mJS-u
