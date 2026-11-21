---
title: "JavaScript: GPIO"
sidebarTitle: "JS: gpio"
order: 310
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gpio.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/apps/Scripts/js_examples]
sources: [unleashed-docs, unleashed-src]
---
# Modul GPIO

Das Modul `gpio` steuert die Pins der Erweiterungsstiftleiste auf der Oberseite des Flipper Zero: digitaler Ausgang,
digitaler und analoger Eingang, Interrupts und PWM. Es hängt von `event_loop` ab und **muss** daher nach diesem
geladen werden:

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");
```

Pin-Nummern und -Namen zeigt [GPIO-Pinbelegung](/de/gpio/pinout).

::: warning
Die GPIO-Pins arbeiten mit 3,3 V. Schließe keine 5-V-Signale direkt an.
:::

## Beispiel: eine LED blinken lassen

Schließe eine LED (mit Widerstand) zwischen Pin `PC3` (Pin 7) und GND an:

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

## Beispiel: Timer, PWM, analoger Eingang und Interrupt

Das ist das mitgelieferte `/ext/apps/Scripts/js_examples/gpio.js`. Es lässt eine LED an PC3 blinken, dimmt eine
zweite LED an PA7 per PWM und gibt die Spannung am Potentiometer an PC0 aus, wenn ein Taster an PC1 gedrückt wird:

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

### Pin-Namen und -Nummern

| Name | Pin der Stiftleiste | Name | Pin der Stiftleiste |
|---|---|---|---|
| `"pa7"` | 2 | `"pa14"` | 10 |
| `"pa6"` | 3 | `"pa13"` | 12 |
| `"pa4"` | 4 | `"pb6"` | 13 |
| `"pb3"` | 5 | `"pb7"` | 14 |
| `"pb2"` | 6 | `"pc1"` | 15 |
| `"pc3"` | 7 | `"pc0"` | 16 |
| | | `"pb14"` | 17 |

## API-Referenz

### get()
Gibt ein `Pin`-Objekt zur Verwaltung eines Pins zurück.

- **Parameter:** `pin`, die Pin-Kennung (Beispiele: `"pc3"`, `7`, `"pa6"`, `3`). Sowohl Portnamen als auch
  Pin-Nummern der Stiftleiste funktionieren.
- **Rückgabe:** ein `Pin`-Objekt.

### Pin.init()
Konfiguriert den Pin.

- **Parameter:** `mode`, ein `Mode`-Objekt:
  - `direction` (erforderlich): `"in"` oder `"out"`;
  - `outMode` (erforderlich bei `direction: "out"`): `"open_drain"` oder `"push_pull"`;
  - `inMode` (erforderlich bei `direction: "in"`): `"analog"`, `"plain_digital"`, `"interrupt"` oder `"event"`;
  - `edge` (erforderlich bei `inMode: "interrupt"` oder `"event"`): `"rising"`, `"falling"` oder `"both"`;
  - `pull` (optional): `"up"`, `"down"` oder nicht gesetzt.

### Pin.write()
Schreibt einen digitalen Wert auf einen mit `direction: "out"` konfigurierten Pin.

- **Parameter:** `value`, der logische Pegel als Boolean.

### Pin.read()
Liest einen digitalen Wert von einem Pin, der mit `direction: "in"` und einem beliebigen `inMode` außer `"analog"`
konfiguriert ist.

- **Rückgabe:** logischer Pegel als Boolean.

### Pin.readAnalog()
Liest die Spannung an einem Pin, der mit `direction: "in"` und `inMode: "analog"` konfiguriert ist.

- **Rückgabe:** Spannung in Millivolt.

### Pin.interrupt()
Hängt einen Interrupt an einen Pin, der mit `direction: "in"` und `inMode: "interrupt"` oder `"event"` konfiguriert
ist.

- **Rückgabe:** ein Event-Loop-`Contract` für den Interrupt. Das Ereignis bringt keine zusätzlichen Daten mit.

### Pin.isPwmSupported()
Gibt an, ob dieser Pin PWM unterstützt. Ist das Ergebnis `false`, lösen alle anderen PWM-Methoden an diesem Pin
einen Fehler aus.

- **Rückgabe:** Boolean.

### Pin.pwmWrite()
Setzt die PWM-Parameter und startet PWM. Konfiguriert den Pin als `{ direction: "out", outMode: "push_pull" }`.
Löst einen Fehler aus, wenn der Pin PWM nicht unterstützt.

- **Parameter:**
  - `freq`: Frequenz in Hz;
  - `duty`: Tastverhältnis in %.

### Pin.isPwmRunning()
Gibt an, ob PWM läuft. Löst einen Fehler aus, wenn der Pin PWM nicht unterstützt.

- **Rückgabe:** Boolean.

### Pin.pwmStop()
Stoppt PWM. Stellt die vorherige Pin-Konfiguration **nicht** wieder her. Löst einen Fehler aus, wenn der Pin PWM
nicht unterstützt.

## Verwandte Themen

- [Event loop](/de/dev/js-event-loop)
- [Serial](/de/dev/js-serial) für UART an der GPIO-Stiftleiste
- Die Unleashed-Extras `i2c` und `spi`: [JavaScript – Übersicht](/de/dev/js-about#unleashed-extras)
