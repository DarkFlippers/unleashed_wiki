---
title: "JavaScript: serial (UART)"
sidebarTitle: "JS: serial"
order: 340
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_serial.md]
sources: [unleashed-docs]
---
# Модуль serial

Модуль `serial` надсилає й приймає дані через UART-порти Flipper на гребінці GPIO. Використовуйте його, щоб спілкуватися з роутерами, платами ESP32, GPS-модулями, службовими консолями тощо.

```js
let serial = require("serial");
```

| Назва порту | Виводи |
|---|---|
| `"usart"` | TX = 13, RX = 14 |
| `"lpuart"` | TX = 15, RX = 16 |

Див. [Розпіновку GPIO](/ua/gpio/pinout). Пам’ятайте: UART у Flipper працює на 3,3 В.

Приклади скриптів: `uart_echo.js`, `uart_echo_8e1.js`, `bad_uart.js` у `/ext/apps/Scripts/js_examples/`.

## Методи

### setup()
Налаштовує послідовний порт. Викликайте його **перед усіма іншими методами**. Він автоматично вимикає службу модулів розширення, щоб та не створювала перешкод.

**Параметри:**

- назва порту: `"usart"` або `"lpuart"`;
- швидкість передачі;
- необов’язковий об’єкт параметрів кадру, наприклад `{ dataBits: "8", parity: "even", stopBits: "1" }`:
  - `dataBits`: `"6"`, `"7"`, `"8"`, `"9"`. 6 бітів даних — лише з увімкненою перевіркою парності (even або odd); 9 бітів даних — лише з вимкненою (none);
  - `parity`: `"none"`, `"even"`, `"odd"`;
  - `stopBits`: `"0.5"`, `"1"`, `"1.5"`, `"2"`. LPUART підтримує лише цілі стоп-біти (1 і 2, але не 0.5 і 1.5).

```js
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

### write()
Записує дані в порт.

**Параметри:** один або кілька аргументів таких типів:

- рядок;
- одне число, що тлумачиться як байт;
- масив чисел, кожне з яких тлумачиться як байт;
- `ArrayBuffer` або `DataView`.

```js
serial.write(0x0a); // Write a single byte 0x0A
serial.write("Hello, world!"); // Write a string
serial.write("Hello, world!", [0x0d, 0x0a]); // Write a string followed by two bytes
```

### read()
Читає фіксовану кількість символів.

**Параметри:** кількість байтів для читання; *(необов’язково)* таймаут у мс.

**Повертає:** рядок отриманих символів або `undefined`, якщо до закінчення таймауту нічого не надійшло.

```js
serial.read(1); // Read a single byte, without timeout
serial.read(10, 5000); // Read 10 bytes, with 5s timeout
```

### readln()
Читає до символу переходу на новий рядок.

**Параметри:** *(необов’язково)* таймаут у мс.

**Повертає:** рядок або `undefined`, якщо до закінчення таймауту нічого не надійшло.

```js
serial.readln(); // Read without timeout
serial.readln(5000); // Read with 5s timeout
```

### readAny()
Читає стільки даних, скільки є в наявності. Це рятує цикл від простою на безлічі дрібних читань.

**Параметри:** *(необов’язково)* таймаут у мс.

**Повертає:** рядок або `undefined`, якщо до закінчення таймауту нічого не надійшло.

```js
serial.readAny(); // Read without timeout
serial.readAny(5000); // Read with 5s timeout
```

### readBytes()
Читає фіксовану кількість байтів як бінарні дані.

**Параметри:** кількість байтів для читання; *(необов’язково)* таймаут у мс.

**Повертає:** `ArrayBuffer` з отриманими даними або `undefined`, якщо до закінчення таймауту нічого не надійшло.

```js
serial.readBytes(4); // Read 4 bytes, without timeout

// Read one byte from receive buffer with zero timeout, returns UNDEFINED if Rx buffer is empty
serial.readBytes(1, 0);
```

::: info
В оригінальній документації `readBytes()` описано як «читання до переходу на новий рядок». Це помилка копіювання: як видно з параметрів, функція читає задану кількість байтів.
:::

### expect()
Шукає заданий шаблон у вхідному потоці даних.

**Параметри:**

- один шаблон або масив шаблонів, де кожен — це:
  - рядок або
  - масив чисел (байтів);
- *(необов’язково)* таймаут у мс.

**Повертає:** індекс знайденого шаблону у списку або `undefined`, якщо не знайдено жодного.

```js
// Wait for root shell prompt with 1s timeout, returns 0 if it was received before timeout, undefined if not
serial.expect("# ", 1000);

// Infinitely wait for one of two strings, should return 0 if the first string got matched, 1 if the second one
serial.expect([": not found", "Usage: "]);
```

### end()
Деініціалізує порт, щоб його можна було налаштувати знову в тому самому скрипті.

```js
serial.end();
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

## Пов’язані сторінки

- [GPIO](/ua/dev/js-gpio)
- `bad_uart.js` демонструє `expect()` у дії: скрипт чекає на запит root-шелу Linux (`# `) на LPUART і надсилає туди команди.
