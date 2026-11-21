---
title: "JavaScript: spi"
sidebarTitle: "JS: spi"
order: 450
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_spi.c]
sources: [unleashed-src]
---
# Módulo SPI

Un extra de Unleashed, no está en el firmware de serie. Habla con chips SPI del bus externo: memorias flash, módulos de radio, pantallas.

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");
```

Conexiones en el [conector GPIO](/es/gpio/pinout): **MOSI = pin 2 (PA7)**, **MISO = pin 3 (PA6)**, **CS = pin 4 (PA4)**, **SCK = pin 5 (PB3)**, 3,3 V en el pin 9, GND en el pin 8. De la señal de chip select se encarga el firmware, no la manejas tú.

Script de ejemplo: `/ext/apps/Scripts/js_examples/spi.js`.

## Métodos

### acquire()
Toma el bus y mantiene CS en bajo hasta `release()`. Úsalo cuando varias transferencias tengan que parecerle una sola transacción al dispositivo: comando y después respuesta. Sin esto, cada llamada toma y suelta el bus por su cuenta, lo que sube CS entre medias.

### release()
Suelta el bus.

### write()
- **Parámetros:** `data` (`number[]` con valores de 0 a 255, o un `ArrayBuffer`/`Uint8Array`), `timeout` (opcional, en milisegundos, por defecto 1).
- **Devuelve:** booleano.

### read()
- **Parámetros:** `length` (número de bytes, mínimo 1), `timeout` (opcional, ms, por defecto 1).
- **Devuelve:** un `ArrayBuffer`, o `undefined` si falla. Envuélvelo en `Uint8Array(buf)` para acceder a los bytes.

### writeRead()
Transferencia full-duplex: envía el búfer y lee exactamente tantos bytes como ha enviado.

- **Parámetros:** `data` (`number[]` o `ArrayBuffer`), `timeout` (opcional, ms, por defecto 1).
- **Devuelve:** un `ArrayBuffer` del mismo tamaño que `data`, o `undefined` si falla.

## Ejemplo

Leer el identificador JEDEC de un chip flash W25Q32:

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

## Páginas relacionadas

- [Patillaje GPIO](/es/gpio/pinout)
- [Módulo I2C](/es/dev/js-i2c)
- [Visión general de JavaScript](/es/dev/js-about)
