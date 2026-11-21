---
title: "JavaScript: serial (UART)"
sidebarTitle: "JS: serial"
order: 340
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_serial.md]
sources: [unleashed-docs]
---
# Модуль Serial

Модуль `serial` передаёт и принимает данные через UART-порты Flipper на гребёнке GPIO. С его помощью можно общаться с роутерами, платами ESP32, GPS-модулями, отладочными консолями и т. д.

```js
let serial = require("serial");
```

| Имя порта | Пины |
|---|---|
| `"usart"` | TX = 13, RX = 14 |
| `"lpuart"` | TX = 15, RX = 16 |

См. [распиновку GPIO](/ru/gpio/pinout). Помните: UART у Flipper 3,3-вольтовый.

Примеры: `uart_echo.js`, `uart_echo_8e1.js`, `bad_uart.js` в `/ext/apps/Scripts/js_examples/`.

## Методы

### setup()
Настраивает порт. Вызывается **до всех остальных методов**. Автоматически отключает сервис Expansion module, чтобы он не мешал.

**Параметры:**

- имя порта: `"usart"` или `"lpuart"`;
- скорость (baud rate);
- необязательный объект формата кадра, например `{ dataBits: "8", parity: "even", stopBits: "1" }`:
  - `dataBits`: `"6"`, `"7"`, `"8"`, `"9"`. 6 бит данных — только с включённой чётностью (even или odd); 9 бит — только без чётности (none);
  - `parity`: `"none"`, `"even"`, `"odd"`;
  - `stopBits`: `"0.5"`, `"1"`, `"1.5"`, `"2"`. LPUART поддерживает только целые стоп-биты (1 и 2, но не 0.5 и 1.5).

```js
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

### write()
Записывает данные в порт.

**Параметры:** один или несколько аргументов следующих типов:

- строка;
- одно число, интерпретируется как байт;
- массив чисел, каждое — байт;
- `ArrayBuffer` или `DataView`.

```js
serial.write(0x0a); // Write a single byte 0x0A
serial.write("Hello, world!"); // Write a string
serial.write("Hello, world!", [0x0d, 0x0a]); // Write a string followed by two bytes
```

### read()
Читает заданное число символов.

**Параметры:** сколько байтов прочитать; *(необязательно)* таймаут в мс.

**Возвращает:** строку принятых символов или `undefined`, если до таймаута ничего не пришло.

```js
serial.read(1); // Read a single byte, without timeout
serial.read(10, 5000); // Read 10 bytes, with 5s timeout
```

### readln()
Читает до символа перевода строки.

**Параметры:** *(необязательно)* таймаут в мс.

**Возвращает:** строку или `undefined`, если до таймаута ничего не пришло.

```js
serial.readln(); // Read without timeout
serial.readln(5000); // Read with 5s timeout
```

### readAny()
Читает столько данных, сколько есть в буфере. Так цикл не тормозит на множестве мелких чтений.

**Параметры:** *(необязательно)* таймаут в мс.

**Возвращает:** строку или `undefined`, если до таймаута ничего не пришло.

```js
serial.readAny(); // Read without timeout
serial.readAny(5000); // Read with 5s timeout
```

### readBytes()
Читает заданное число байтов как двоичные данные.

**Параметры:** сколько байтов прочитать; *(необязательно)* таймаут в мс.

**Возвращает:** `ArrayBuffer` с принятыми данными или `undefined`, если до таймаута ничего не пришло.

```js
serial.readBytes(4); // Read 4 bytes, without timeout

// Read one byte from receive buffer with zero timeout, returns UNDEFINED if Rx buffer is empty
serial.readBytes(1, 0);
```

::: info
В оригинальной документации `readBytes()` описан как «чтение до перевода строки». Это ошибка копирования: судя по параметрам, метод читает заданное число байтов.
:::

### expect()
Ищет шаблон во входящем потоке данных.

**Параметры:**

- один шаблон или массив шаблонов, каждый из которых:
  - строка, или
  - массив чисел (байтов);
- *(необязательно)* таймаут в мс.

**Возвращает:** индекс совпавшего шаблона в списке или `undefined`, если ничего не нашлось.

```js
// Wait for root shell prompt with 1s timeout, returns 0 if it was received before timeout, undefined if not
serial.expect("# ", 1000);

// Infinitely wait for one of two strings, should return 0 if the first string got matched, 1 if the second one
serial.expect([": not found", "Usage: "]);
```

### end()
Деинициализирует порт, чтобы его можно было настроить заново в том же скрипте.

```js
serial.end();
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

## См. также

- [GPIO](/ru/dev/js-gpio)
- `bad_uart.js` показывает `expect()` в деле: ждёт приглашение root-шелла Linux (`# `) на LPUART и отправляет ему команды.
