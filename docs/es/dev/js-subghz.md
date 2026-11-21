---
title: "JavaScript: subghz"
sidebarTitle: "JS: subghz"
order: 400
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_subghz]
sources: [unleashed-src]
---
# Módulo Sub-GHz

Un extra de Unleashed, no está en el firmware de serie. Le da a tu script la radio Sub-GHz: cambiar entre recepción y reposo, leer el nivel de señal, cambiar de frecuencia, transmitir un fichero `.sub` guardado.

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");
subghz.setup();
```

`setup()` busca primero un módulo CC1101 externo y, si no lo encuentra, usa la radio interna. Hasta que se ejecuta, cualquier otro método lanza `Radio is not setup`.

Script de ejemplo: `/ext/apps/Scripts/js_examples/subghz.js`.

## Métodos

### setup()
Inicializa la radio y elige el dispositivo. Arranca en 433920000 Hz y en estado `IDLE`. Lanza un error si la radio ya está inicializada.

### end()
Duerme la radio y libera el dispositivo. Ocurre solo al terminar el script. Si llamas a `setup()` después, vuelve a buscar un módulo externo.

### setRx()
Pone la radio en modo recepción.

### setIdle()
Pone la radio en reposo. La frecuencia solo se puede cambiar en este estado.

### getRssi()
Nivel de señal en la frecuencia actual, en dBm.

- **Devuelve:** `number`, o `undefined` si la radio no está en RX.

### getState()
- **Devuelve:** `"RX"`, `"TX"` o `"IDLE"`.

### getFrequency()
- **Devuelve:** la frecuencia actual en Hz, como número.

### setFrequency()
Sintoniza la radio. Lanza un error si la radio no está en `IDLE` o si la frecuencia queda fuera de las bandas que admite el dispositivo.

- **Parámetros:** `frequency`, un número en Hz — por ejemplo `433920000`.
- **Devuelve:** la frecuencia a la que la radio ha sintonizado de verdad. Un CC1101 no puede alcanzar todos los valores exactos, así que coge el más cercano que puede.

### isExternal()
- **Devuelve:** booleano — `true` cuando se usa un CC1101 externo, `false` con la radio interna.

### transmitFile()
Envía un fichero `.sub`. La frecuencia y la modulación salen del fichero, no de `setFrequency()`. Devuelve `true`; ante cualquier problema (fichero que falta, cabecera incorrecta, frecuencia no admitida, preset desconocido) lanza un error. La radio se queda en `IDLE`.

- **Parámetros:**
  - `path`: ruta completa al fichero, p. ej. `"/ext/subghz/0.sub"`;
  - `repeat` (opcional): cuántas veces enviarlo.

Sin `repeat`, los ficheros RAW salen una vez y los de protocolo 10 veces, lo que imita mantener pulsado el botón de un mando real. `CAME Atomo`, `CAME TWEE`, `Hormann HSM`, `Nice FloR-S` y `Power Smart` ya envían varios paquetes por repetición, así que para esos el valor por defecto es 1.

## Ejemplo

Escuchar en 433,92 MHz y luego enviar una llave guardada:

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

## Páginas relacionadas

- [Formatos de fichero Sub-GHz](/es/subghz/file-format) — qué hay dentro de un `.sub`
- [Módulos CC1101 externos](/es/subghz/external-cc1101)
- [Visión general de JavaScript](/es/dev/js-about)
