---
title: "JavaScript: blebeacon"
sidebarTitle: "JS: blebeacon"
order: 420
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_blebeacon.c]
sources: [unleashed-src]
---
# Modulo BLE beacon

Un extra di Unleashed, assente nel firmware di serie. Trasmette un advertisement Bluetooth LE personalizzato: indirizzo MAC tuo, payload tuo. È lo stesso "extra beacon" che il firmware usa per l'advertising in background, quindi funziona insieme alla normale connessione Bluetooth.

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");
```

Script di esempio: `/ext/apps/Scripts/js_examples/blebeacon.js`.

Quando lo script termina, il modulo ripristina la configurazione, i dati e lo stato del beacon che c'erano prima — a meno che tu non l'abbia impedito con `keepAlive(true)`.

## Metodi

### isActive()
- **Restituisce:** booleano, se il beacon sta trasmettendo in questo momento. Controllalo all'inizio: un beacon lasciato acceso da uno script precedente è ancora attivo.

### setConfig()
Imposta i parametri dell'advertisement.

- **Parametri:**
  - `mac`: `Uint8Array` di esattamente 6 byte. Qualsiasi altra cosa genera `Wrong MAC address`;
  - `power` (facoltativo): potenza di trasmissione sulla scala GapAdvPowerLevel, da `0x00` (-40 dBm) a `0x1F` (+6 dBm). Il valore predefinito è 0 dBm, i valori fuori intervallo vengono limitati;
  - `minInterval` (facoltativo): intervallo minimo di advertising in ms. Predefinito 50, i valori sotto 20 vengono portati a 20, il massimo è 255;
  - `maxInterval` (facoltativo): intervallo massimo in ms. Predefinito 150, mai inferiore a `minInterval`, massimo 255.

### setData()
- **Parametri:** `data`, un `Uint8Array` con il payload dell'advertisement. Il limite hardware è 31 byte.

### start()
Avvia l'advertising.

### stop()
Ferma l'advertising.

### keepAlive()
- **Parametri:** `keep`, booleano. Con `true` il beacon continua a trasmettere dopo la fine dello script e non viene ripristinato nulla. Il valore predefinito è `false`.

## Esempio

Trasmettere un payload breve per cinque secondi:

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

## Pagine correlate

- [Panoramica su JavaScript](/it/dev/js-about)
- [Tipi di dati](/it/dev/js-data-types) — come funziona `Uint8Array` in mJS
