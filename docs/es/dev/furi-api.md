---
title: API Furi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_furi_api.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriCheck.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi]
sources: [unleashed-docs, unleashed-src]
---
# API Furi

Para usar el hardware del Flipper — pantalla, altavoz, radio, USB, NFC — tu app habla con **Furi**, el conjunto de
bibliotecas que se sitúa entre el hardware desnudo y el código de aplicación. Esta página ofrece una visión general de
la arquitectura de hardware y software, y explica las comprobaciones en tiempo de ejecución de Furi.

## Hardware

El corazón de Flipper Zero es un microcontrolador (MCU) **STM32WB55**: dos núcleos, RAM, flash y decenas de bloques
periféricos (temporizadores, RTC, BLE, GPIO, …). Su funcionamiento se describe en el Reference Manual del MCU.
Alrededor del MCU hay varios chips externos (CC1101, ST25R3916, el controlador de pantalla, etc.) con sus propias
hojas de datos.

![Estructura de hardware de Flipper Zero](/img/dev/flipper_zero_hardware.png)

Leyenda de colores:

- **Morado** — bloques internos del MCU
- **Azul** — chips externos al MCU
- **Naranja** — otros componentes periféricos que no requieren una interacción compleja

Como el firmware es de código abierto, *puedes* acceder al hardware directamente y escribir tus propios controladores
de bajo nivel — pero normalmente no hace falta.

## Software: Furi

**Furi** (**F**lipper **U**niversal **R**egistry **I**mplementation) es la capa de abstracción incluida en el
firmware. Ofrece una API directa para el hardware y para las tareas habituales del sistema: hilos, memoria dinámica,
control de acceso a recursos (records), temporizadores, colas de mensajes, registro de eventos, etc.

Con Furi no tienes que leer cientos de páginas de hojas de datos ni escribir controladores: basta con aprender la API
de Furi. También evita que cada desarrollador vuelva a implementar lo mismo.

![Estructura de hardware y software de Flipper Zero](/img/dev/flipper_zero_architecture.png)

Furi abarca todo el ancho del diagrama: separa el código de nivel de aplicación (servicios y apps) del hardware que
hay debajo.

Furi consta de dos partes:

| Parte | Dónde | Qué es |
|---|---|---|
| Furi Core | `furi/` | Primitivas del SO: hilos, mutex, colas de mensajes, records, temporizadores, bucle de eventos, logging, comprobaciones |
| Furi HAL | `targets/` (por ejemplo `targets/f7/furi_hal/`) | Abstracción del hardware: GPIO, SPI, I2C, USB, Sub-GHz, NFC, RFID, alimentación, … — consulta [FuriHalBus](/es/dev/furi-hal-bus) |

Código fuente:

- Furi Core: [unleashed-firmware/furi](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi)
  (oficial: [flipperzero-firmware/furi](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/furi))
- Furi HAL: [unleashed-firmware/targets](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets)
  (oficial: [flipperzero-firmware/targets](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/targets))

## Encontrar ejemplos

Todas las apps del Flipper usan Furi, así que hay ejemplos para cualquier bloque de hardware:

- apps de ejemplo en [`applications/examples/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples)
  (`example_event_loop`, `example_adc`, `example_ble_beacon`, …);
- apps integradas en `applications/main/` y las apps añadidas por Unleashed en `applications/system/`;
- apps de la comunidad en el [catálogo de aplicaciones](https://lab.flipper.net/apps) — el enlace al código está al
  final de la página de cada app. Elige apps cuya funcionalidad se parezca a lo que quieres construir.

Todas las funciones, structs y cabeceras de Furi están listadas en la [referencia de la API en Doxygen](https://developer.flipper.net/flipperzero/doxygen/) oficial — úsala cuando esta wiki no cubra la llamada que necesitas.

## Comprobaciones en tiempo de ejecución y fallos provocados

La mejor forma de proteger la integridad del sistema es gestionar menos casos imposibles y **fallar lo antes posible**
cuando algo va mal. El `check.h` de Furi Core ofrece utilidades para eso.

Terminología:

- **Crash** — registrar el evento, guardar la información del fallo en el RTC y reiniciar.
- **Halt** — registrar el evento y dejar el sistema bloqueado.

Notas:

- Las compilaciones de depuración y de release se comportan de forma distinta: una compilación de depuración **nunca
  reinicia** el sistema, para conservar el estado para el depurador.
- Con un depurador conectado, la ejecución se detiene automáticamente antes del reinicio.
- Todas las utilidades aceptan un `MESSAGE_CSTR` opcional. Puede estar en RAM o en flash, pero **solo los mensajes
  almacenados en flash** se muestran después del reinicio (es decir, usa literales de cadena).
- `MESSAGE_CSTR` puede ser `NULL`, pero las macros ya gestionan el caso sin mensaje — simplemente omítelo.

| Macro | Comportamiento | Cuándo usarla |
|---|---|---|
| `furi_assert(CONDITION)` / `furi_assert(CONDITION, MESSAGE_CSTR)` | Provoca un fallo si `CONDITION` es falsa — **solo en compilaciones de desarrollo** | Comprobaciones de la fase de desarrollo en apps y servicios |
| `furi_check(CONDITION)` / `furi_check(CONDITION, MESSAGE_CSTR)` | Provoca **siempre** un fallo si `CONDITION` es falsa | Condiciones que deben cumplirse en todas las compilaciones |
| `furi_crash()` / `furi_crash(MESSAGE_CSTR)` | Provoca un fallo sin condición | Se ha detectado una situación anómala |
| `furi_halt()` / `furi_halt(MESSAGE_CSTR)` | Bloquea el sistema | Uso interno, por ejemplo para detenerse cuando no es posible apagar |

::: warning Trampas de furi_assert
- Las compilaciones de release (`DEBUG=0`) nunca contienen comprobaciones `furi_assert`.
- Las bibliotecas nunca las contienen por defecto; compila con `LIB_DEBUG=1` si las necesitas.
- No pongas llamadas a funciones (efectos secundarios) dentro de `CONDITION` — toda la expresión puede eliminarse en
  compilación.
:::

Ejemplo:

```c
#include <furi.h>

void my_set_level(uint8_t level) {
    furi_check(level <= 100, "Level out of range");
    // ...
}
```

## Páginas relacionadas

- [GUI en las apps](/es/dev/gui)
- [API FuriHalBus](/es/dev/furi-hal-bus)
- [Depurar apps](/es/dev/debugging) — incluye las señales de depuración del Furi HAL
