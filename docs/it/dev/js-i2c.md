---
title: "JavaScript: i2c"
sidebarTitle: "JS: i2c"
order: 440
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_i2c.c]
sources: [unleashed-src]
---
# Modulo I2C

Un extra di Unleashed, assente nel firmware di serie. Dialoga con i chip I2C sul bus esterno: sensori, EEPROM, display.

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");
```

Collegamenti sul [connettore GPIO](/it/gpio/pinout): **SDA = pin 15 (PC1)**, **SCL = pin 16 (PC0)**, 3,3 V sul pin 9, GND sul pin 8. Il bus è a 3,3 V: non collegare dispositivi a 5 V.

Script di esempio: `/ext/apps/Scripts/js_examples/i2c.js`.

Gli indirizzi sono a 8 bit (l'indirizzo a 7 bit spostato a sinistra di uno). Un datasheet che dice `0x50` di solito qui significa `0xA0`. Ogni chiamata prende il bus, esegue il trasferimento e lo rilascia, così un'altra app può usare l'I2C tra una chiamata e l'altra.

## Metodi

### isDeviceReady()
Fa un ping a un indirizzo.

- **Parametri:** `address` (numero), `timeout` (facoltativo, millisecondi, predefinito 1).
- **Restituisce:** booleano.

### write()
- **Parametri:** `address` (numero), `data` (`number[]` di valori 0–255, oppure un `ArrayBuffer`/`Uint8Array`), `timeout` (facoltativo, ms, predefinito 1).
- **Restituisce:** booleano — `true` se il dispositivo ha risposto con un ACK.

### read()
- **Parametri:** `address` (numero), `length` (numero di byte, almeno 1), `timeout` (facoltativo, ms, predefinito 1).
- **Restituisce:** un `ArrayBuffer`, oppure `undefined` se il trasferimento è fallito. Avvolgilo in `Uint8Array(buf)` per indicizzare i byte.

### writeRead()
Scrive e poi legge senza rilasciare il bus. È così che si legge un registro: scrivi il suo numero, leggi il valore.

- **Parametri:** `address`, `writeData` (`number[]` o `ArrayBuffer`), `readLength`, `timeout` (facoltativo, ms, predefinito 1).
- **Restituisce:** un `ArrayBuffer`, oppure `undefined` in caso di errore.

## Esempio

Scansiona il bus, poi legge tre byte da una EEPROM 24C32N:

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

## Pagine correlate

- [Pinout GPIO](/it/gpio/pinout)
- [Modulo GPIO](/it/dev/js-gpio)
- [Modulo SPI](/it/dev/js-spi)
