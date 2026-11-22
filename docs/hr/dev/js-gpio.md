---
title: "JavaScript: GPIO"
sidebarTitle: "JS: gpio"
order: 310
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gpio.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/apps/Scripts/js_examples]
sources: [unleashed-docs, unleashed-src]
---
# Modul GPIO

Modul `gpio` upravlja pinovima priključka za proširenje na vrhu uređaja Flipper Zero: digitalnim izlazom, digitalnim i analognim ulazom, prekidima i PWM-om. Ovisi o modulu `event_loop`, stoga se **mora** učitati nakon njega:

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");
```

Brojevi i nazivi pinova prikazani su na stranici [Raspored GPIO pinova](/hr/gpio/pinout).

::: warning
GPIO pinovi rade na 3,3 V. Nemojte izravno spajati signale od 5 V.
:::

## Primjer: treptanje LED diode

Spojite LED diodu (s otpornikom) između pina `PC3` (pin 7) i GND-a:

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

## Primjer: tajmeri, PWM, analogni ulaz i prekid

Ovo je priložena skripta `/ext/apps/Scripts/js_examples/gpio.js`. Treperi LED diodom na pinu PC3, postupno mijenja svjetlinu druge LED diode na PA7 pomoću PWM-a te ispisuje napon potenciometra na PC0 kada se pritisne tipka na PC1:

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

### Nazivi i brojevi pinova

| Naziv | Pin priključka | Naziv | Pin priključka |
|---|---|---|---|
| `"pa7"` | 2 | `"pa14"` | 10 |
| `"pa6"` | 3 | `"pa13"` | 12 |
| `"pa4"` | 4 | `"pb6"` | 13 |
| `"pb3"` | 5 | `"pb7"` | 14 |
| `"pb2"` | 6 | `"pc1"` | 15 |
| `"pc3"` | 7 | `"pc0"` | 16 |
| | | `"pb14"` | 17 |

## Referenca API-ja

### get()
Vraća objekt `Pin` za upravljanje pinom.

- **Parametri:** `pin`, identifikator pina (primjeri: `"pc3"`, `7`, `"pa6"`, `3`). Rade i nazivi priključaka i brojevi pinova.
- **Vraća:** objekt `Pin`.

### Pin.init()
Konfigurira pin.

- **Parametri:** `mode`, objekt `Mode`:
  - `direction` (obavezno): `"in"` ili `"out"`;
  - `outMode` (obavezno za `direction: "out"`): `"open_drain"` ili `"push_pull"`;
  - `inMode` (obavezno za `direction: "in"`): `"analog"`, `"plain_digital"`, `"interrupt"` ili `"event"`;
  - `edge` (obavezno za `inMode: "interrupt"` ili `"event"`): `"rising"`, `"falling"` ili `"both"`;
  - `pull` (neobavezno): `"up"`, `"down"` ili nepostavljeno.

### Pin.write()
Zapisuje digitalnu vrijednost na pin konfiguriran s `direction: "out"`.

- **Parametri:** `value`, logička razina tipa boolean.

### Pin.read()
Čita digitalnu vrijednost s pina konfiguriranog s `direction: "in"` i bilo kojim `inMode` osim `"analog"`.

- **Vraća:** logička razina tipa boolean.

### Pin.readAnalog()
Čita napon na pinu konfiguriranom s `direction: "in"` i `inMode: "analog"`.

- **Vraća:** napon u milivoltima.

### Pin.interrupt()
Veže prekid na pin konfiguriran s `direction: "in"` i `inMode: "interrupt"` ili `"event"`.

- **Vraća:** objekt `Contract` petlje događaja za taj prekid. Događaj ne nosi dodatne podatke.

### Pin.isPwmSupported()
Provjerava podržava li ovaj pin PWM. Ako je `false`, sve ostale PWM metode na tom pinu bacaju pogrešku.

- **Vraća:** boolean.

### Pin.pwmWrite()
Postavlja parametre PWM-a i pokreće PWM. Konfigurira pin kao `{ direction: "out", outMode: "push_pull" }`. Baca pogrešku ako pin ne podržava PWM.

- **Parametri:**
  - `freq`: frekvencija u Hz;
  - `duty`: faktor ispune u %.

### Pin.isPwmRunning()
Provjerava radi li PWM. Baca pogrešku ako pin ne podržava PWM.

- **Vraća:** boolean.

### Pin.pwmStop()
Zaustavlja PWM. **Ne** vraća prethodnu konfiguraciju pina. Baca pogrešku ako pin ne podržava PWM.

## Povezano

- [Petlja događaja (Event loop)](/hr/dev/js-event-loop)
- [Serial](/hr/dev/js-serial) za UART na GPIO priključku
- Dodaci firmvera Unleashed `i2c` i `spi`: [Pregled JavaScripta](/hr/dev/js-about#unleashed-extras)
