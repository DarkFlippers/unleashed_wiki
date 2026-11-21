---
title: "JavaScript: i2c"
sidebarTitle: "JS: i2c"
order: 440
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_i2c.c]
sources: [unleashed-src]
---
# Modul I2C

Ein Unleashed-Extra, in der Stock-Firmware gibt es das nicht. Es spricht mit I2C-Chips am externen Bus: Sensoren, EEPROMs, Displays.

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");
```

Verdrahtung an der [GPIO-Stiftleiste](/de/gpio/pinout): **SDA = Pin 15 (PC1)**, **SCL = Pin 16 (PC0)**, 3,3 V an Pin 9, GND an Pin 8. Der Bus arbeitet mit 3,3 V — schließe keine 5-V-Geräte an.

Beispielskript: `/ext/apps/Scripts/js_examples/i2c.js`.

Adressen sind 8 Bit breit (die 7-Bit-Adresse um eins nach links geschoben). Ein Datenblatt, das `0x50` nennt, meint hier meistens `0xA0`. Jeder Aufruf belegt den Bus, führt seine Übertragung aus und gibt ihn wieder frei, zwischen den Aufrufen kann also eine andere App I2C nutzen.

## Methoden

### isDeviceReady()
Pingt eine Adresse an.

- **Parameter:** `address` (Zahl), `timeout` (optional, Millisekunden, Standard 1).
- **Rückgabe:** boolean.

### write()
- **Parameter:** `address` (Zahl), `data` (`number[]` mit Werten 0–255, oder ein `ArrayBuffer`/`Uint8Array`), `timeout` (optional, ms, Standard 1).
- **Rückgabe:** boolean — `true`, wenn das Gerät quittiert hat.

### read()
- **Parameter:** `address` (Zahl), `length` (Anzahl Bytes, mindestens 1), `timeout` (optional, ms, Standard 1).
- **Rückgabe:** ein `ArrayBuffer`, oder `undefined`, wenn die Übertragung fehlschlug. Pack ihn in `Uint8Array(buf)`, um auf die Bytes zuzugreifen.

### writeRead()
Schreibt und liest dann, ohne den Bus freizugeben. So liest man ein Register: Nummer schreiben, Wert lesen.

- **Parameter:** `address`, `writeData` (`number[]` oder `ArrayBuffer`), `readLength`, `timeout` (optional, ms, Standard 1).
- **Rückgabe:** ein `ArrayBuffer`, oder `undefined` bei einem Fehlschlag.

## Beispiel

Den Bus scannen, dann drei Bytes aus einem 24C32N-EEPROM lesen:

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");

let addr = -1;
for (let a = 0; a !== 0xff; a++) {
    if (i2c.isDeviceReady(a, 5)) {
        addr = a;
        break;
    }
}

if (addr === -1) {
    print("No I2C device found");
} else {
    print("Device at 0x" + addr.toString(16));
    // write 3 bytes starting at EEPROM address 0x0000
    i2c.write(addr, [0x00, 0x00, 0x41, 0x42, 0x43]);
    delay(10);
    // read 3 bytes back from address 0x0000
    let data = Uint8Array(i2c.writeRead(addr, [0x00, 0x00], 3, 100));
    for (let i = 0; i < data.length; i++) {
        print("data[" + i.toString() + "] = " + data[i].toString(16));
    }
}
```

## Verwandte Themen

- [GPIO-Pinbelegung](/de/gpio/pinout)
- [Modul GPIO](/de/dev/js-gpio)
- [Modul SPI](/de/dev/js-spi)
