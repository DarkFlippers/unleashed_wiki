---
title: "JavaScript: spi"
sidebarTitle: "JS: spi"
order: 450
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_spi.c]
sources: [unleashed-src]
---
# Modul SPI

Ein Unleashed-Extra, in der Stock-Firmware gibt es das nicht. Es spricht mit SPI-Chips am externen Bus — Flash-Speicher, Funkmodule, Displays.

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");
```

Verdrahtung an der [GPIO-Stiftleiste](/de/gpio/pinout): **MOSI = Pin 2 (PA7)**, **MISO = Pin 3 (PA6)**, **CS = Pin 4 (PA4)**, **SCK = Pin 5 (PB3)**, 3,3 V an Pin 9, GND an Pin 8. Chip Select steuert die Firmware, du schaltest es nicht selbst.

Beispielskript: `/ext/apps/Scripts/js_examples/spi.js`.

## Methoden

### acquire()
Belegt den Bus und hält CS auf Low bis zum `release()`. Nutze es, wenn mehrere Übertragungen für das Gerät wie eine einzige Transaktion aussehen müssen — Befehl, dann Antwort. Ohne das belegt und befreit jeder Aufruf den Bus für sich, was CS dazwischen anhebt.

### release()
Gibt den Bus frei.

### write()
- **Parameter:** `data` (`number[]` mit Werten 0–255, oder ein `ArrayBuffer`/`Uint8Array`), `timeout` (optional, Millisekunden, Standard 1).
- **Rückgabe:** boolean.

### read()
- **Parameter:** `length` (Anzahl Bytes, mindestens 1), `timeout` (optional, ms, Standard 1).
- **Rückgabe:** ein `ArrayBuffer`, oder `undefined` bei einem Fehlschlag. Pack ihn in `Uint8Array(buf)`, um auf die Bytes zuzugreifen.

### writeRead()
Vollduplex-Übertragung: sendet den Puffer und liest genau so viele Bytes zurück, wie gesendet wurden.

- **Parameter:** `data` (`number[]` oder `ArrayBuffer`), `timeout` (optional, ms, Standard 1).
- **Rückgabe:** ein `ArrayBuffer` mit derselben Länge wie `data`, oder `undefined` bei einem Fehlschlag.

## Beispiel

Die JEDEC-ID eines W25Q32-Flash-Chips auslesen:

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");

spi.acquire();
spi.write([0x9F]);          // command: read JEDEC ID
let data = Uint8Array(spi.read(3));
spi.release();

print("Manufacturer: 0x" + data[0].toString(16));
print("Memory type:  0x" + data[1].toString(16));
print("Capacity:     0x" + data[2].toString(16));

if (data[0] === 0xEF) {
    print("Winbond device");
}
```

## Verwandte Themen

- [GPIO-Pinbelegung](/de/gpio/pinout)
- [Modul I2C](/de/dev/js-i2c)
- [JavaScript-Übersicht](/de/dev/js-about)
