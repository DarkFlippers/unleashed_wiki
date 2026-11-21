---
title: "JavaScript: spi"
sidebarTitle: "JS: spi"
order: 450
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_spi.c]
sources: [unleashed-src]
---
# Modulo SPI

Un extra di Unleashed, assente nel firmware di serie. Dialoga con i chip SPI sul bus esterno: memorie flash, moduli radio, display.

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");
```

Collegamenti sul [connettore GPIO](/it/gpio/pinout): **MOSI = pin 2 (PA7)**, **MISO = pin 3 (PA6)**, **CS = pin 4 (PA4)**, **SCK = pin 5 (PB3)**, 3,3 V sul pin 9, GND sul pin 8. Il chip select lo gestisce il firmware, non devi commutarlo tu.

Script di esempio: `/ext/apps/Scripts/js_examples/spi.js`.

## Metodi

### acquire()
Prende il bus e tiene CS basso fino a `release()`. Usalo quando più trasferimenti devono apparire al dispositivo come un'unica transazione: comando, poi risposta. Senza, ogni chiamata prende e libera il bus da sé, il che alza CS nel mezzo.

### release()
Libera il bus.

### write()
- **Parametri:** `data` (`number[]` di valori 0–255, oppure un `ArrayBuffer`/`Uint8Array`), `timeout` (facoltativo, millisecondi, predefinito 1).
- **Restituisce:** booleano.

### read()
- **Parametri:** `length` (numero di byte, almeno 1), `timeout` (facoltativo, ms, predefinito 1).
- **Restituisce:** un `ArrayBuffer`, oppure `undefined` in caso di errore. Avvolgilo in `Uint8Array(buf)` per indicizzare i byte.

### writeRead()
Trasferimento full-duplex: invia il buffer e rilegge esattamente tanti byte quanti ne ha inviati.

- **Parametri:** `data` (`number[]` o `ArrayBuffer`), `timeout` (facoltativo, ms, predefinito 1).
- **Restituisce:** un `ArrayBuffer` della stessa lunghezza di `data`, oppure `undefined` in caso di errore.

## Esempio

Leggere il JEDEC ID di un chip flash W25Q32:

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

## Pagine correlate

- [Pinout GPIO](/it/gpio/pinout)
- [Modulo I2C](/it/dev/js-i2c)
- [Panoramica su JavaScript](/it/dev/js-about)
