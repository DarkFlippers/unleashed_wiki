---
title: "JavaScript: blebeacon"
sidebarTitle: "JS: blebeacon"
order: 420
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_blebeacon.c]
sources: [unleashed-src]
---
# Módulo de baliza BLE

Un extra de Unleashed, no está en el firmware de serie. Emite un anuncio Bluetooth LE a tu medida: tu propia dirección MAC, tus propios datos. Es la misma «baliza extra» que el firmware usa para anunciarse en segundo plano, así que funciona a la vez que la conexión Bluetooth normal.

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");
```

Script de ejemplo: `/ext/apps/Scripts/js_examples/blebeacon.js`.

Al terminar el script, el módulo restaura la configuración, los datos y el estado de baliza que hubiera antes, salvo que le pidas lo contrario con `keepAlive(true)`.

## Métodos

### isActive()
- **Devuelve:** booleano, si la baliza está emitiendo ahora mismo. Compruébalo al principio: una baliza que dejó encendida un script anterior sigue activa.

### setConfig()
Fija los parámetros del anuncio.

- **Parámetros:**
  - `mac`: `Uint8Array` de exactamente 6 bytes. Cualquier otra cosa lanza `Wrong MAC address`;
  - `power` (opcional): potencia de transmisión en la escala GapAdvPowerLevel, de `0x00` (-40 dBm) a `0x1F` (+6 dBm). Por defecto 0 dBm; los valores fuera de rango se recortan;
  - `minInterval` (opcional): intervalo mínimo de anuncio en ms. Por defecto 50; por debajo de 20 se sube a 20 y el máximo es 255;
  - `maxInterval` (opcional): intervalo máximo en ms. Por defecto 150, nunca menor que `minInterval`, máximo 255.

### setData()
- **Parámetros:** `data`, un `Uint8Array` con los datos del anuncio. El límite del hardware son 31 bytes.

### start()
Empieza a emitir.

### stop()
Deja de emitir.

### keepAlive()
- **Parámetros:** `keep`, booleano. Con `true` la baliza sigue emitiendo cuando el script termina y no se restaura nada. Por defecto es `false`.

## Ejemplo

Emitir unos pocos bytes durante cinco segundos:

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

## Páginas relacionadas

- [Visión general de JavaScript](/es/dev/js-about)
- [Tipos de datos](/es/dev/js-data-types) — cómo funciona `Uint8Array` en mJS
