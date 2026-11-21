---
title: "JavaScript: GPIO"
sidebarTitle: "JS: gpio"
order: 310
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gpio.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/apps/Scripts/js_examples]
sources: [unleashed-docs, unleashed-src]
---
# GPIO module

The `gpio` module controls the pins of the expansion header on top of Flipper Zero: digital output, digital and analog input, interrupts and PWM. It depends on `event_loop`, so it **must** be loaded after it:

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");
```

Pin numbers and names are shown on [GPIO pinout](/gpio/pinout).

::: warning
GPIO pins are 3.3 V. Don't connect 5 V signals directly.
:::

## Example: blink an LED

Connect an LED (with a resistor) between pin `PC3` (pin 7) and GND:

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

## Example: timers, PWM, analog input and interrupt

This is the bundled `/ext/apps/Scripts/js_examples/gpio.js`. It blinks an LED on PC3, fades a second LED on PA7 with PWM, and prints the potentiometer voltage on PC0 when a button on PC1 is pressed:

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

### Pin names and numbers

| Name | Header pin | Name | Header pin |
|---|---|---|---|
| `"pa7"` | 2 | `"pa14"` | 10 |
| `"pa6"` | 3 | `"pa13"` | 12 |
| `"pa4"` | 4 | `"pb6"` | 13 |
| `"pb3"` | 5 | `"pb7"` | 14 |
| `"pb2"` | 6 | `"pc1"` | 15 |
| `"pc3"` | 7 | `"pc0"` | 16 |
| | | `"pb14"` | 17 |

## API reference

### get()
Returns a `Pin` object for managing a pin.

- **Parameters:** `pin`, the pin identifier (examples: `"pc3"`, `7`, `"pa6"`, `3`). Port names and header pin numbers both work.
- **Returns:** a `Pin` object.

### Pin.init()
Configures the pin.

- **Parameters:** `mode`, a `Mode` object:
  - `direction` (required): `"in"` or `"out"`;
  - `outMode` (required for `direction: "out"`): `"open_drain"` or `"push_pull"`;
  - `inMode` (required for `direction: "in"`): `"analog"`, `"plain_digital"`, `"interrupt"` or `"event"`;
  - `edge` (required for `inMode: "interrupt"` or `"event"`): `"rising"`, `"falling"` or `"both"`;
  - `pull` (optional): `"up"`, `"down"` or unset.

### Pin.write()
Writes a digital value to a pin configured with `direction: "out"`.

- **Parameters:** `value`, the boolean logic level.

### Pin.read()
Reads a digital value from a pin configured with `direction: "in"` and any `inMode` except `"analog"`.

- **Returns:** boolean logic level.

### Pin.readAnalog()
Reads the voltage on a pin configured with `direction: "in"` and `inMode: "analog"`.

- **Returns:** voltage in millivolts.

### Pin.interrupt()
Attaches an interrupt to a pin configured with `direction: "in"` and `inMode: "interrupt"` or `"event"`.

- **Returns:** an event-loop `Contract` for the interrupt. The event carries no extra data.

### Pin.isPwmSupported()
Tells whether this pin supports PWM. If `false`, all other PWM methods on this pin throw an error.

- **Returns:** boolean.

### Pin.pwmWrite()
Sets PWM parameters and starts PWM. Configures the pin as `{ direction: "out", outMode: "push_pull" }`. Throws an error if the pin does not support PWM.

- **Parameters:**
  - `freq`: frequency in Hz;
  - `duty`: duty cycle in %.

### Pin.isPwmRunning()
Tells whether PWM is running. Throws an error if the pin does not support PWM.

- **Returns:** boolean.

### Pin.pwmStop()
Stops PWM. Does **not** restore the previous pin configuration. Throws an error if the pin does not support PWM.

## Related

- [Event loop](/dev/js-event-loop)
- [Serial](/dev/js-serial) for UART on the GPIO header
- Unleashed extras `i2c` and `spi`: [JavaScript overview](/dev/js-about#unleashed-extras)
