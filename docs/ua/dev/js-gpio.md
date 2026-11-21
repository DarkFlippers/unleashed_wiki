---
title: "JavaScript: GPIO"
sidebarTitle: "JS: gpio"
order: 310
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gpio.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/apps/Scripts/js_examples]
sources: [unleashed-docs, unleashed-src]
---
# Модуль gpio

Модуль `gpio` керує виводами гребінки розширення на верхньому торці Flipper Zero: цифровий вихід, цифровий і аналоговий вхід, перервання та PWM. Він залежить від `event_loop`, тому його **обов’язково** завантажувати після нього:

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");
```

Номери й назви виводів показано на сторінці [Розпіновка GPIO](/ua/gpio/pinout).

::: warning
Виводи GPIO працюють на 3,3 В. Не підключайте до них 5-вольтові сигнали напряму.
:::

## Приклад: блимання світлодіодом

Підключіть світлодіод (з резистором) між виводом `PC3` (пін 7) і GND:

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

## Приклад: таймери, PWM, аналоговий вхід і перервання

Це готовий приклад `/ext/apps/Scripts/js_examples/gpio.js`. Він блимає світлодіодом на PC3, плавно змінює яскравість другого світлодіода на PA7 через PWM і виводить напругу з потенціометра на PC0, коли натиснуто кнопку на PC1:

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

### Назви й номери виводів

| Назва | Пін гребінки | Назва | Пін гребінки |
|---|---|---|---|
| `"pa7"` | 2 | `"pa14"` | 10 |
| `"pa6"` | 3 | `"pa13"` | 12 |
| `"pa4"` | 4 | `"pb6"` | 13 |
| `"pb3"` | 5 | `"pb7"` | 14 |
| `"pb2"` | 6 | `"pc1"` | 15 |
| `"pc3"` | 7 | `"pc0"` | 16 |
| | | `"pb14"` | 17 |

## Довідник API

### get()
Повертає об’єкт `Pin` для керування виводом.

- **Параметри:** `pin` — ідентифікатор виводу (наприклад, `"pc3"`, `7`, `"pa6"`, `3`). Працюють і назви портів, і номери пінів гребінки.
- **Повертає:** об’єкт `Pin`.

### Pin.init()
Налаштовує вивід.

- **Параметри:** `mode` — об’єкт `Mode`:
  - `direction` (обов’язковий): `"in"` або `"out"`;
  - `outMode` (обов’язковий для `direction: "out"`): `"open_drain"` або `"push_pull"`;
  - `inMode` (обов’язковий для `direction: "in"`): `"analog"`, `"plain_digital"`, `"interrupt"` або `"event"`;
  - `edge` (обов’язковий для `inMode: "interrupt"` або `"event"`): `"rising"`, `"falling"` або `"both"`;
  - `pull` (необов’язковий): `"up"`, `"down"` або не задано.

### Pin.write()
Записує цифрове значення на вивід, налаштований як `direction: "out"`.

- **Параметри:** `value` — логічний рівень (boolean).

### Pin.read()
Читає цифрове значення з виводу, налаштованого як `direction: "in"` із будь-яким `inMode`, крім `"analog"`.

- **Повертає:** логічний рівень (boolean).

### Pin.readAnalog()
Читає напругу на виводі, налаштованому як `direction: "in"` і `inMode: "analog"`.

- **Повертає:** напругу в мілівольтах.

### Pin.interrupt()
Призначає перервання виводу, налаштованому як `direction: "in"` і `inMode: "interrupt"` або `"event"`.

- **Повертає:** `Contract` циклу подій для цього перервання. Подія не несе додаткових даних.

### Pin.isPwmSupported()
Повідомляє, чи підтримує цей вивід PWM. Якщо `false`, усі інші методи PWM на цьому виводі кидають виняток.

- **Повертає:** boolean.

### Pin.pwmWrite()
Задає параметри PWM і запускає його. Налаштовує вивід як `{ direction: "out", outMode: "push_pull" }`. Кидає виняток, якщо вивід не підтримує PWM.

- **Параметри:**
  - `freq`: частота в Гц;
  - `duty`: коефіцієнт заповнення у %.

### Pin.isPwmRunning()
Повідомляє, чи працює PWM. Кидає виняток, якщо вивід не підтримує PWM.

- **Повертає:** boolean.

### Pin.pwmStop()
Зупиняє PWM. **Не** відновлює попередню конфігурацію виводу. Кидає виняток, якщо вивід не підтримує PWM.

## Пов’язані сторінки

- [Цикл подій](/ua/dev/js-event-loop)
- [Serial](/ua/dev/js-serial) — UART на гребінці GPIO
- Розширення Unleashed `i2c` і `spi`: [огляд JavaScript](/ua/dev/js-about#unleashed-extras)
