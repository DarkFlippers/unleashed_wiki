---
title: "JavaScript: GPIO"
sidebarTitle: "JS: gpio"
order: 310
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gpio.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/apps/Scripts/js_examples]
sources: [unleashed-docs, unleashed-src]
---
# Módulo GPIO

El módulo `gpio` controla los pines del conector de expansión de la parte superior del Flipper Zero: salida digital, entrada digital y analógica, interrupciones y PWM. Depende de `event_loop`, así que **debe** cargarse después de él:

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");
```

Los números y nombres de los pines se muestran en [Patillaje GPIO](/es/gpio/pinout).

::: warning
Los pines GPIO son de 3,3 V. No conectes señales de 5 V directamente.
:::

## Ejemplo: hacer parpadear un LED

Conecta un LED (con una resistencia) entre el pin `PC3` (pin 7) y GND:

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");

let led = gpio.get("pc3");
led.init({ direction: "out", outMode: "push_pull" });

led.write(true);
delay(1000);
led.write(false);
delay(1000);
```

## Ejemplo: temporizadores, PWM, entrada analógica e interrupción

Este es el `/ext/apps/Scripts/js_examples/gpio.js` incluido con el firmware. Hace parpadear un LED en PC3, atenúa un segundo LED en PA7 con PWM e imprime la tensión del potenciómetro de PC0 cuando se pulsa un botón en PC1:

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");

// initialize pins
let led = gpio.get("pc3"); // same as `gpio.get(7)`
let led2 = gpio.get("pa7"); // same as `gpio.get(2)`
let pot = gpio.get("pc0"); // same as `gpio.get(16)`
let button = gpio.get("pc1"); // same as `gpio.get(15)`
led.init({ direction: "out", outMode: "push_pull" });
pot.init({ direction: "in", inMode: "analog" });
button.init({ direction: "in", pull: "up", inMode: "interrupt", edge: "falling" });

// blink led
print("Commencing blinking (PC3)");
eventLoop.subscribe(eventLoop.timer("periodic", 1000), function (_, _item, led, state) {
    led.write(state);
    return [led, !state];
}, led, true);

// cycle led pwm
print("Commencing PWM (PA7)");
eventLoop.subscribe(eventLoop.timer("periodic", 10), function (_, _item, led2, state) {
    led2.pwmWrite(10000, state);
    return [led2, (state + 1) % 101];
}, led2, 0);

// read potentiometer when button is pressed
print("Press the button (PC1)");
eventLoop.subscribe(button.interrupt(), function (_, _item, pot) {
    print("PC0 is at", pot.readAnalog(), "mV");
}, pot);

// the program will just exit unless this is here
eventLoop.run();
```

### Nombres y números de los pines

| Nombre | Pin del conector | Nombre | Pin del conector |
|---|---|---|---|
| `"pa7"` | 2 | `"pa14"` | 10 |
| `"pa6"` | 3 | `"pa13"` | 12 |
| `"pa4"` | 4 | `"pb6"` | 13 |
| `"pb3"` | 5 | `"pb7"` | 14 |
| `"pb2"` | 6 | `"pc1"` | 15 |
| `"pc3"` | 7 | `"pc0"` | 16 |
| | | `"pb14"` | 17 |

## Referencia de la API

### get()
Devuelve un objeto `Pin` para gestionar un pin.

- **Parámetros:** `pin`, el identificador del pin (ejemplos: `"pc3"`, `7`, `"pa6"`, `3`). Valen tanto los nombres de puerto como los números de pin del conector.
- **Devuelve:** un objeto `Pin`.

### Pin.init()
Configura el pin.

- **Parámetros:** `mode`, un objeto `Mode`:
  - `direction` (obligatorio): `"in"` u `"out"`;
  - `outMode` (obligatorio con `direction: "out"`): `"open_drain"` o `"push_pull"`;
  - `inMode` (obligatorio con `direction: "in"`): `"analog"`, `"plain_digital"`, `"interrupt"` o `"event"`;
  - `edge` (obligatorio con `inMode: "interrupt"` o `"event"`): `"rising"`, `"falling"` o `"both"`;
  - `pull` (opcional): `"up"`, `"down"` o sin definir.

### Pin.write()
Escribe un valor digital en un pin configurado con `direction: "out"`.

- **Parámetros:** `value`, el nivel lógico booleano.

### Pin.read()
Lee un valor digital de un pin configurado con `direction: "in"` y cualquier `inMode` excepto `"analog"`.

- **Devuelve:** el nivel lógico booleano.

### Pin.readAnalog()
Lee la tensión de un pin configurado con `direction: "in"` e `inMode: "analog"`.

- **Devuelve:** la tensión en milivoltios.

### Pin.interrupt()
Asocia una interrupción a un pin configurado con `direction: "in"` e `inMode: "interrupt"` o `"event"`.

- **Devuelve:** un `Contract` del bucle de eventos para la interrupción. El evento no lleva datos adicionales.

### Pin.isPwmSupported()
Indica si este pin admite PWM. Si es `false`, todos los demás métodos de PWM de este pin lanzan un error.

- **Devuelve:** booleano.

### Pin.pwmWrite()
Fija los parámetros de PWM e inicia el PWM. Configura el pin como `{ direction: "out", outMode: "push_pull" }`. Lanza un error si el pin no admite PWM.

- **Parámetros:**
  - `freq`: frecuencia en Hz;
  - `duty`: ciclo de trabajo en %.

### Pin.isPwmRunning()
Indica si el PWM está en marcha. Lanza un error si el pin no admite PWM.

- **Devuelve:** booleano.

### Pin.pwmStop()
Detiene el PWM. **No** restaura la configuración anterior del pin. Lanza un error si el pin no admite PWM.

## Páginas relacionadas

- [Bucle de eventos](/es/dev/js-event-loop)
- [Serial](/es/dev/js-serial) para el UART del conector GPIO
- Los extras de Unleashed `i2c` y `spi`: [Visión general de JavaScript](/es/dev/js-about#unleashed-extras)
