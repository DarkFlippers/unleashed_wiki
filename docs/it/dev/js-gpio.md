---
title: "JavaScript: GPIO"
sidebarTitle: "JS: gpio"
order: 310
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gpio.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/apps/Scripts/js_examples]
sources: [unleashed-docs, unleashed-src]
---
# Modulo GPIO

Il modulo `gpio` controlla i pin del connettore di espansione sulla parte superiore del Flipper Zero: uscita digitale, ingresso digitale e analogico, interrupt e PWM. Dipende da `event_loop`, quindi **deve** essere caricato dopo di esso:

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");
```

Numeri e nomi dei pin sono riportati in [Pinout GPIO](/it/gpio/pinout).

::: warning
I pin GPIO sono a 3,3 V. Non collegare direttamente segnali a 5 V.
:::

## Esempio: far lampeggiare un LED

Collega un LED (con una resistenza) tra il pin `PC3` (pin 7) e GND:

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

## Esempio: timer, PWM, ingresso analogico e interrupt

Questo è l'esempio `/ext/apps/Scripts/js_examples/gpio.js` incluso nel firmware. Fa lampeggiare un LED su PC3, sfuma un secondo LED su PA7 tramite PWM e stampa la tensione del potenziometro su PC0 quando viene premuto un pulsante collegato a PC1:

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

### Nomi e numeri dei pin

| Nome | Pin del connettore | Nome | Pin del connettore |
|---|---|---|---|
| `"pa7"` | 2 | `"pa14"` | 10 |
| `"pa6"` | 3 | `"pa13"` | 12 |
| `"pa4"` | 4 | `"pb6"` | 13 |
| `"pb3"` | 5 | `"pb7"` | 14 |
| `"pb2"` | 6 | `"pc1"` | 15 |
| `"pc3"` | 7 | `"pc0"` | 16 |
| | | `"pb14"` | 17 |

## Riferimento delle API

### get()
Restituisce un oggetto `Pin` per gestire un pin.

- **Parametri:** `pin`, l'identificatore del pin (esempi: `"pc3"`, `7`, `"pa6"`, `3`). Funzionano sia i nomi di porta sia i numeri dei pin del connettore.
- **Restituisce:** un oggetto `Pin`.

### Pin.init()
Configura il pin.

- **Parametri:** `mode`, un oggetto `Mode`:
  - `direction` (obbligatorio): `"in"` o `"out"`;
  - `outMode` (obbligatorio per `direction: "out"`): `"open_drain"` o `"push_pull"`;
  - `inMode` (obbligatorio per `direction: "in"`): `"analog"`, `"plain_digital"`, `"interrupt"` o `"event"`;
  - `edge` (obbligatorio per `inMode: "interrupt"` o `"event"`): `"rising"`, `"falling"` o `"both"`;
  - `pull` (facoltativo): `"up"`, `"down"` oppure non impostato.

### Pin.write()
Scrive un valore digitale su un pin configurato con `direction: "out"`.

- **Parametri:** `value`, il livello logico booleano.

### Pin.read()
Legge un valore digitale da un pin configurato con `direction: "in"` e qualunque `inMode` tranne `"analog"`.

- **Restituisce:** il livello logico booleano.

### Pin.readAnalog()
Legge la tensione su un pin configurato con `direction: "in"` e `inMode: "analog"`.

- **Restituisce:** la tensione in millivolt.

### Pin.interrupt()
Associa un interrupt a un pin configurato con `direction: "in"` e `inMode: "interrupt"` o `"event"`.

- **Restituisce:** un `Contract` dell'event loop per l'interrupt. L'evento non trasporta dati aggiuntivi.

### Pin.isPwmSupported()
Indica se questo pin supporta il PWM. Se restituisce `false`, tutti gli altri metodi PWM su questo pin generano un errore.

- **Restituisce:** booleano.

### Pin.pwmWrite()
Imposta i parametri PWM e avvia il PWM. Configura il pin come `{ direction: "out", outMode: "push_pull" }`. Genera un errore se il pin non supporta il PWM.

- **Parametri:**
  - `freq`: frequenza in Hz;
  - `duty`: duty cycle in %.

### Pin.isPwmRunning()
Indica se il PWM è in esecuzione. Genera un errore se il pin non supporta il PWM.

- **Restituisce:** booleano.

### Pin.pwmStop()
Ferma il PWM. **Non** ripristina la configurazione precedente del pin. Genera un errore se il pin non supporta il PWM.

## Pagine correlate

- [Event loop](/it/dev/js-event-loop)
- [Serial](/it/dev/js-serial) per l'UART sul connettore GPIO
- Gli extra di Unleashed `i2c` e `spi`: [Panoramica su JavaScript](/it/dev/js-about#unleashed-extras)
