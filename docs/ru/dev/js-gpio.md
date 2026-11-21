---
title: "JavaScript: GPIO"
sidebarTitle: "JS: gpio"
order: 310
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gpio.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/apps/Scripts/js_examples]
sources: [unleashed-docs, unleashed-src]
---
# Модуль GPIO

Модуль `gpio` управляет пинами гребёнки расширения на верхней грани Flipper Zero: цифровой выход, цифровой и аналоговый вход, прерывания и ШИМ. Он зависит от `event_loop`, поэтому **обязательно** подключается после него:

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");
```

Номера и названия пинов см. в [распиновке GPIO](/ru/gpio/pinout).

::: warning
Пины GPIO работают на 3,3 В. Не подавайте на них 5 В напрямую.
:::

## Пример: мигаем светодиодом

Подключите светодиод (через резистор) между пином `PC3` (пин 7) и GND:

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

## Пример: таймеры, ШИМ, аналоговый вход и прерывание

Это встроенный пример `/ext/apps/Scripts/js_examples/gpio.js`. Он мигает светодиодом на PC3, плавно меняет яркость второго светодиода на PA7 через ШИМ и при нажатии кнопки на PC1 выводит напряжение с потенциометра на PC0:

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

### Имена и номера пинов

| Имя | Пин гребёнки | Имя | Пин гребёнки |
|---|---|---|---|
| `"pa7"` | 2 | `"pa14"` | 10 |
| `"pa6"` | 3 | `"pa13"` | 12 |
| `"pa4"` | 4 | `"pb6"` | 13 |
| `"pb3"` | 5 | `"pb7"` | 14 |
| `"pb2"` | 6 | `"pc1"` | 15 |
| `"pc3"` | 7 | `"pc0"` | 16 |
| | | `"pb14"` | 17 |

## Справочник API

### get()
Возвращает объект `Pin` для управления пином.

- **Параметры:** `pin` — идентификатор пина (например, `"pc3"`, `7`, `"pa6"`, `3`). Подходят и имена портов, и номера пинов гребёнки.
- **Возвращает:** объект `Pin`.

### Pin.init()
Настраивает пин.

- **Параметры:** `mode` — объект `Mode`:
  - `direction` (обязательно): `"in"` или `"out"`;
  - `outMode` (обязательно при `direction: "out"`): `"open_drain"` или `"push_pull"`;
  - `inMode` (обязательно при `direction: "in"`): `"analog"`, `"plain_digital"`, `"interrupt"` или `"event"`;
  - `edge` (обязательно при `inMode: "interrupt"` или `"event"`): `"rising"`, `"falling"` или `"both"`;
  - `pull` (необязательно): `"up"`, `"down"` или не задано.

### Pin.write()
Записывает цифровое значение в пин с `direction: "out"`.

- **Параметры:** `value` — логический уровень (boolean).

### Pin.read()
Читает цифровое значение с пина с `direction: "in"` и любым `inMode`, кроме `"analog"`.

- **Возвращает:** логический уровень (boolean).

### Pin.readAnalog()
Читает напряжение на пине с `direction: "in"` и `inMode: "analog"`.

- **Возвращает:** напряжение в милливольтах.

### Pin.interrupt()
Подключает прерывание к пину с `direction: "in"` и `inMode: "interrupt"` или `"event"`.

- **Возвращает:** `Contract` цикла событий для прерывания. Событие не несёт дополнительных данных.

### Pin.isPwmSupported()
Поддерживает ли пин ШИМ. Если `false`, остальные ШИМ-методы этого пина выбрасывают ошибку.

- **Возвращает:** boolean.

### Pin.pwmWrite()
Задаёт параметры ШИМ и запускает его. Настраивает пин как `{ direction: "out", outMode: "push_pull" }`. Выбрасывает ошибку, если пин не поддерживает ШИМ.

- **Параметры:**
  - `freq` — частота в Гц;
  - `duty` — скважность (коэффициент заполнения) в %.

### Pin.isPwmRunning()
Запущен ли ШИМ. Выбрасывает ошибку, если пин не поддерживает ШИМ.

- **Возвращает:** boolean.

### Pin.pwmStop()
Останавливает ШИМ. Прежнюю конфигурацию пина **не** восстанавливает. Выбрасывает ошибку, если пин не поддерживает ШИМ.

## См. также

- [Event loop](/ru/dev/js-event-loop)
- [Serial](/ru/dev/js-serial) для UART на гребёнке GPIO
- Дополнительные модули Unleashed `i2c` и `spi`: [обзор JavaScript](/ru/dev/js-about#unleashed-extras)
