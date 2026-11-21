---
title: "JavaScript: serial (UART)"
sidebarTitle: "JS: serial"
order: 340
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_serial.md]
sources: [unleashed-docs]
---
# Serial module

The `serial` module sends and receives data over Flipper's UART ports on the GPIO header. Use it to talk to routers, ESP32 boards, GPS modules, debug consoles, etc.

```js
let serial = require("serial");
```

| Port name | Pins |
|---|---|
| `"usart"` | TX = 13, RX = 14 |
| `"lpuart"` | TX = 15, RX = 16 |

See [GPIO pinout](/gpio/pinout). Remember: UART on Flipper is 3.3 V.

Example scripts: `uart_echo.js`, `uart_echo_8e1.js`, `bad_uart.js` in `/ext/apps/Scripts/js_examples/`.

## Methods

### setup()
Configures the serial port. Call it **before all other methods**. It automatically disables the Expansion module service to prevent interference.

**Parameters:**

- port name: `"usart"` or `"lpuart"`;
- baud rate;
- optional framing object, e.g. `{ dataBits: "8", parity: "even", stopBits: "1" }`:
  - `dataBits`: `"6"`, `"7"`, `"8"`, `"9"`. 6 data bits only with parity enabled (even or odd); 9 data bits only with parity disabled (none);
  - `parity`: `"none"`, `"even"`, `"odd"`;
  - `stopBits`: `"0.5"`, `"1"`, `"1.5"`, `"2"`. LPUART supports only whole stop bits (1 and 2, not 0.5 and 1.5).

```js
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

### write()
Writes data to the port.

**Parameters:** one or more arguments of these types:

- a string;
- a single number, interpreted as a byte;
- an array of numbers, each interpreted as a byte;
- an `ArrayBuffer` or `DataView`.

```js
serial.write(0x0a); // Write a single byte 0x0A
serial.write("Hello, world!"); // Write a string
serial.write("Hello, world!", [0x0d, 0x0a]); // Write a string followed by two bytes
```

### read()
Reads a fixed number of characters.

**Parameters:** number of bytes to read; *(optional)* timeout in ms.

**Returns:** a string of received characters, or `undefined` if nothing was received before the timeout.

```js
serial.read(1); // Read a single byte, without timeout
serial.read(10, 5000); // Read 10 bytes, with 5s timeout
```

### readln()
Reads until a line break character.

**Parameters:** *(optional)* timeout in ms.

**Returns:** a string, or `undefined` if nothing was received before the timeout.

```js
serial.readln(); // Read without timeout
serial.readln(5000); // Read with 5s timeout
```

### readAny()
Reads whatever amount of data is available. This keeps a loop from stalling on many small reads.

**Parameters:** *(optional)* timeout in ms.

**Returns:** a string, or `undefined` if nothing was received before the timeout.

```js
serial.readAny(); // Read without timeout
serial.readAny(5000); // Read with 5s timeout
```

### readBytes()
Reads a fixed number of bytes as binary data.

**Parameters:** number of bytes to read; *(optional)* timeout in ms.

**Returns:** an `ArrayBuffer` with the received data, or `undefined` if nothing was received before the timeout.

```js
serial.readBytes(4); // Read 4 bytes, without timeout

// Read one byte from receive buffer with zero timeout, returns UNDEFINED if Rx buffer is empty
serial.readBytes(1, 0);
```

::: info
The original doc describes `readBytes()` as "read until line break". That is a copy-paste error: as its parameters show, it reads the given number of bytes.
:::

### expect()
Searches the incoming data stream for a pattern.

**Parameters:**

- a single pattern or an array of patterns, each one:
  - a string, or
  - an array of numbers (bytes);
- *(optional)* timeout in ms.

**Returns:** the index of the matched pattern in the list, or `undefined` if nothing matched.

```js
// Wait for root shell prompt with 1s timeout, returns 0 if it was received before timeout, undefined if not
serial.expect("# ", 1000);

// Infinitely wait for one of two strings, should return 0 if the first string got matched, 1 if the second one
serial.expect([": not found", "Usage: "]);
```

### end()
Deinitializes the port, so it can be set up again in the same script.

```js
serial.end();
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

## Related

- [GPIO](/dev/js-gpio)
- `bad_uart.js` shows `expect()` in action: it waits for a Linux root shell prompt (`# `) on LPUART and sends commands to it.
