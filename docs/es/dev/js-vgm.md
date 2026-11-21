---
title: "JavaScript: vgm"
sidebarTitle: "JS: vgm"
order: 460
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [unleashed-src]
---
# Video Game Module

Un extra de Unleashed, no está en el firmware de serie. Lee el sensor de movimiento (la IMU ICM42688P) que hay dentro del [Video Game Module](/es/gpio/video-game-module) e indica cómo está inclinado el Flipper.

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");
```

Para este módulo el firmware no trae ningún script de ejemplo.

Los ángulos van en grados:

- **pitch** — morro arriba y abajo;
- **roll** — inclinación a izquierda y derecha;
- **yaw** — giro en plano sobre la mesa.

Sin el módulo conectado, `require("vgm")` funciona igual, pero todos los métodos devuelven `undefined`. Compruébalo en vez de dar el hardware por supuesto.

El controlador de la IMU viene del [motor de juegos de Flipper](https://github.com/flipperdevices/flipperzero-game-engine).

## Métodos

### getPitch()
- **Devuelve:** número, o `undefined` si no hay módulo conectado.

### getRoll()
- **Devuelve:** número, o `undefined` si no hay módulo conectado.

### getYaw()
- **Devuelve:** número, o `undefined` si no hay módulo conectado.

### deltaYaw()
Se queda bloqueado hasta que el yaw gire `angle` grados, comprobándolo 10 veces por segundo.

- **Parámetros:**
  - `angle`: cuántos grados de cambio esperar;
  - `timeout` (opcional): milisegundos de espera. Por defecto 3000.
- **Devuelve:** el cambio en grados, con signo: negativo para un sentido, positivo para el otro. `0` si no se ha alcanzado el ángulo antes del tiempo límite, `undefined` si no hay módulo conectado.

## Ejemplo

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");

if (vgm.getPitch() === undefined) {
    print("No Video Game Module attached");
} else {
    for (let i = 0; i < 10; i++) {
        print("pitch", vgm.getPitch(), "roll", vgm.getRoll(), "yaw", vgm.getYaw());
        delay(200);
    }

    print("Turn the Flipper 45 degrees...");
    let turned = vgm.deltaYaw(45, 5000);
    if (turned === 0) {
        print("Nothing happened");
    } else {
        print("Turned by", turned);
    }
}
```

## Páginas relacionadas

- [Video Game Module](/es/gpio/video-game-module)
- [Visión general de JavaScript](/es/dev/js-about)
