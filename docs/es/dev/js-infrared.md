---
title: "JavaScript: infrared"
sidebarTitle: "JS: infrared"
order: 410
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_infrared]
sources: [unleashed-src]
---
# Módulo de infrarrojos

Un extra de Unleashed, no está en el firmware de serie. Envía señales IR desde un script, por nombre de protocolo o como lista de tiempos en bruto. No hay parte de recepción: captura antes la señal con la app Infrared.

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");
```

La función se llama `infrared-send` y el módulo, `infrared`.

Script de ejemplo: `/ext/apps/Scripts/js_examples/infrared-send.js`.

## Métodos

### sendSignal()
Envía una señal con un protocolo que el firmware conoce.

- **Parámetros:**
  - `protocol`: `"NEC"`, `"NECext"`, `"NEC42"`, `"NEC42ext"`, `"Samsung32"`, `"RC6"`, `"RC5"`, `"RC5X"`, `"SIRC"`, `"SIRC15"`, `"SIRC20"`, `"Kaseikyo"` o `"RCA"`;
  - `address`: número;
  - `command`: número;
  - `options` (opcional): `{ repeat?: boolean, times?: number }`. `repeat` marca la señal como paquete de repetición, `times` es cuántas veces enviarla (por defecto 1).

```js
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
```

En los ficheros `.ir` la dirección y el comando se guardan en hex little-endian, mientras que un número literal de JS es big-endian. `A9 00 00 00` en el fichero es `0x000000A9` aquí, así que invierte los bytes antes de pegarlos.

### sendRawSignal()
Envía una señal por sus tiempos de encendido y apagado, para mandos que no cubre ningún protocolo.

- **Parámetros:**
  - `timings`: array de números, duraciones en microsegundos;
  - `startFromMark` (opcional): booleano, si el primer valor es un pulso en vez de una pausa. Por defecto `true`;
  - `advancedSettings` (opcional): `{ frequency: number, dutyCycle: number }`. Si pasas el objeto, los dos campos son obligatorios. Sin él, la portadora es de 38000 Hz con un ciclo de trabajo de 0,33.

## Ejemplo

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");

// Samsung TV, volume down
print("Sending Samsung32");
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
delay(1000);

// Three presses in a row
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b, { times: 3 });
delay(1000);

// Raw timings at 36 kHz
infrared.sendRawSignal([3298, 1571, 442, 368, 442, 367], true, {
  frequency: 36000,
  dutyCycle: 0.33,
});
print("Done");
```

## Páginas relacionadas

- [Formato de los ficheros IR](/es/infrared/file-format) — de dónde sacar la dirección y el comando
- [Protocolos IR admitidos](/es/infrared/protocols)
- [Visión general de JavaScript](/es/dev/js-about)
