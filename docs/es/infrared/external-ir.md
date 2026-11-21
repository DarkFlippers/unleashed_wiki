---
title: Módulos IR externos
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/furi_hal_include/furi_hal_infrared.h, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/infrared]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Módulos IR externos (GPIO)

Los tres LED IR integrados son suficientes para un salón, pero el alcance es limitado. Para obtener más potencia
puedes conectar un **transmisor IR externo** (una placa con LED más potentes y un transistor de excitación) al
conector GPIO. La aplicación Infrared enviará entonces a través de él en lugar de los LED integrados. Los mandos
universales, los mandos guardados, la aplicación móvil y el botón «Send» de la pantalla de captura usan todos la
salida seleccionada.

::: tip Unleashed
La compatibilidad con módulos IR externos con detección automática figura entre las características de Unleashed;
la lógica de detección en sí proviene del firmware oficial, así que el comportamiento descrito aquí es el mismo en
ambos.
:::

## Conexiones

| Pin del módulo | Pin GPIO del Flipper |
|---|---|
| Signal / IN | **2 (A7)** |
| VCC | **1 (5V)**, alimentado cuando «5V on GPIO» está en ON, o 9 (3V3) para módulos de 3,3 V |
| GND | 8, 11 o 18 (GND) |

El pin 2 transporta la **misma señal modulada** (portadora incluida, normalmente de 38 kHz) que alimenta
habitualmente los LED internos, así que el módulo solo necesita una etapa de excitación y los LED, ningún modulador
propio. Véase el [pinout del GPIO](/es/gpio/pinout) para la disposición del conector.

::: warning
El aprendizaje (la recepción) siempre usa el receptor integrado. El módulo externo es solo de transmisión.
:::

## GPIO Settings

Ve a `Main Menu → Infrared → GPIO Settings`. Hay dos opciones:

| Opción | Valores | Significado |
|---|---|---|
| **Signal Output** | `Flipper` | LED IR integrados (por defecto). |
| | `2 (A7)` | Transmitir siempre por el pin 2 del GPIO. |
| | `Detect` | Detectar automáticamente un módulo externo en el pin 2 cada vez que arranca la aplicación Infrared. |
| **5V on GPIO** | `OFF` / `ON` | Conmuta los 5 V del pin 1 del GPIO para alimentar el módulo. Con `Detect` muestra **`Auto`** y se controla automáticamente. |

Los ajustes se guardan al salir de la pantalla, en `/ext/infrared/.infrared.settings`, y se aplican cada vez que
arranca la aplicación Infrared. Al salir de la aplicación Infrared, la salida vuelve a los LED integrados y los 5 V
se desconectan de nuevo, de modo que el módulo no consume batería en otras aplicaciones.

### Paso a paso

1. Conecta el módulo (Signal → pin 2, VCC → pin 1, GND → pin 8/11/18).
2. Abre `Infrared → GPIO Settings`.
3. Pon **Signal Output** en `Detect` (o en `2 (A7)` si la detección no funciona con tu módulo).
4. Con `2 (A7)`, pon **5V on GPIO** en `ON` si el módulo se alimenta desde el pin 1.
5. Pulsa <kbd>Back</kbd>. Envía cualquier botón guardado o un mando universal; los LED del módulo deberían transmitir.

## Cómo funciona la detección automática

Cuando se selecciona `Detect`, el firmware activa brevemente una **resistencia de pull-up débil** en el pin 2 y lo
vuelve a leer:

- si el pin se mantiene **bajo**, hay algo con una resistencia de pull-down conectado, así que se supone un módulo
  externo. La salida pasa al pin 2 y los **5 V del GPIO se activan automáticamente**;
- si el pin se lee **alto**, no hay nada conectado y se usan los LED integrados.

Esto funciona mejor con módulos cuyo excitador de LED sea un **MOSFET con un pull-down fuerte** en la puerta, o un
**BJT** para alimentar los LED IR. El módulo **debe llevar el pin hasta 0,9 V o menos** para que se detecte. Si tu
módulo no tiene pull-down, elige `2 (A7)` manualmente y activa tú mismo los 5 V.

La detección se produce al arrancar la aplicación Infrared (y al seleccionar `Detect`). Si conectas el módulo con la
aplicación ya abierta, vuelve a seleccionar `Detect` o reinicia la aplicación.

## Resolución de problemas

| Problema | Qué probar |
|---|---|
| `Detect` usa siempre los LED integrados | El módulo no lleva el pin 2 lo bastante bajo (≤ 0,9 V). Usa `2 (A7)` y activa `5V on GPIO` a mano. |
| El LED del módulo no se ilumina | Comprueba VCC: con `2 (A7)` los 5 V deben estar en ON. Comprueba GND. Mira los LED a través de la cámara de un móvil mientras envías. |
| La batería se agota rápido | Un módulo potente consume mucho de los 5 V. Desconéctalo cuando no lo uses. |

## Páginas relacionadas

- [Pinout del GPIO](/es/gpio/pinout)
- [Módulos GPIO](/es/gpio/external-modules)
- [Aprender y enviar señales](/es/infrared/read)
- [Mandos universales](/es/infrared/universal-remotes)
