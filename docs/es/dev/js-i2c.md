---
title: "JavaScript: i2c"
sidebarTitle: "JS: i2c"
order: 440
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_i2c.c]
sources: [unleashed-src]
---
# Módulo I2C

Un extra de Unleashed, no está en el firmware de serie. Habla con chips I2C del bus externo: sensores, EEPROM, pantallas.

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");
```

Conexiones en el [conector GPIO](/es/gpio/pinout): **SDA = pin 15 (PC1)**, **SCL = pin 16 (PC0)**, 3,3 V en el pin 9, GND en el pin 8. El bus es de 3,3 V: no conectes dispositivos de 5 V.

Script de ejemplo: `/ext/apps/Scripts/js_examples/i2c.js`.

Las direcciones son de 8 bits (la dirección de 7 bits desplazada un bit a la izquierda). Si la hoja de datos dice `0x50`, aquí suele ser `0xA0`. Cada llamada toma el bus, hace su transferencia y lo suelta, así que otra app puede usar el I2C entre llamadas.

## Métodos

### isDeviceReady()
Hace ping a una dirección.

- **Parámetros:** `address` (número), `timeout` (opcional, en milisegundos, por defecto 1).
- **Devuelve:** booleano.

### write()
- **Parámetros:** `address` (número), `data` (`number[]` con valores de 0 a 255, o un `ArrayBuffer`/`Uint8Array`), `timeout` (opcional, ms, por defecto 1).
- **Devuelve:** booleano — `true` si el dispositivo ha respondido con ACK.

### read()
- **Parámetros:** `address` (número), `length` (número de bytes, mínimo 1), `timeout` (opcional, ms, por defecto 1).
- **Devuelve:** un `ArrayBuffer`, o `undefined` si la transferencia ha fallado. Envuélvelo en `Uint8Array(buf)` para acceder a los bytes.

### writeRead()
Escribe y luego lee sin soltar el bus. Así se lee un registro: escribes su número y lees el valor.

- **Parámetros:** `address`, `writeData` (`number[]` o `ArrayBuffer`), `readLength`, `timeout` (opcional, ms, por defecto 1).
- **Devuelve:** un `ArrayBuffer`, o `undefined` si falla.

## Ejemplo

Escanear el bus y luego leer tres bytes de una EEPROM 24C32N:

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

## Páginas relacionadas

- [Patillaje GPIO](/es/gpio/pinout)
- [Módulo GPIO](/es/dev/js-gpio)
- [Módulo SPI](/es/dev/js-spi)
