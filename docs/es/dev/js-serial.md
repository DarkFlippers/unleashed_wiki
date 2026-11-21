---
title: "JavaScript: serial (UART)"
sidebarTitle: "JS: serial"
order: 340
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_serial.md]
sources: [unleashed-docs]
---
# Módulo Serial

El módulo `serial` envía y recibe datos por los puertos UART del Flipper en el conector GPIO. Úsalo para hablar con routers, placas ESP32, módulos GPS, consolas de depuración, etc.

```js
let serial = require("serial");
```

| Nombre del puerto | Pines |
|---|---|
| `"usart"` | TX = 13, RX = 14 |
| `"lpuart"` | TX = 15, RX = 16 |

Consulta [Patillaje GPIO](/es/gpio/pinout). Recuerda: el UART del Flipper es de 3,3 V.

Scripts de ejemplo: `uart_echo.js`, `uart_echo_8e1.js` y `bad_uart.js` en `/ext/apps/Scripts/js_examples/`.

## Métodos

### setup()
Configura el puerto serie. Llámalo **antes que todos los demás métodos**. Desactiva automáticamente el servicio del módulo de expansión para evitar interferencias.

**Parámetros:**

- nombre del puerto: `"usart"` o `"lpuart"`;
- velocidad en baudios;
- objeto de trama opcional, por ejemplo `{ dataBits: "8", parity: "even", stopBits: "1" }`:
  - `dataBits`: `"6"`, `"7"`, `"8"`, `"9"`. 6 bits de datos solo con la paridad activada (par o impar); 9 bits de datos solo con la paridad desactivada (none);
  - `parity`: `"none"`, `"even"`, `"odd"`;
  - `stopBits`: `"0.5"`, `"1"`, `"1.5"`, `"2"`. LPUART solo admite bits de parada enteros (1 y 2, no 0,5 ni 1,5).

```js
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

### write()
Escribe datos en el puerto.

**Parámetros:** uno o más argumentos de estos tipos:

- una cadena;
- un solo número, interpretado como un byte;
- un array de números, cada uno interpretado como un byte;
- un `ArrayBuffer` o un `DataView`.

```js
serial.write(0x0a); // Write a single byte 0x0A
serial.write("Hello, world!"); // Write a string
serial.write("Hello, world!", [0x0d, 0x0a]); // Write a string followed by two bytes
```

### read()
Lee un número fijo de caracteres.

**Parámetros:** número de bytes que se leen; *(opcional)* tiempo de espera en ms.

**Devuelve:** una cadena con los caracteres recibidos, o `undefined` si no se recibió nada antes de agotarse el tiempo de espera.

```js
serial.read(1); // Read a single byte, without timeout
serial.read(10, 5000); // Read 10 bytes, with 5s timeout
```

### readln()
Lee hasta un carácter de salto de línea.

**Parámetros:** *(opcional)* tiempo de espera en ms.

**Devuelve:** una cadena, o `undefined` si no se recibió nada antes de agotarse el tiempo de espera.

```js
serial.readln(); // Read without timeout
serial.readln(5000); // Read with 5s timeout
```

### readAny()
Lee la cantidad de datos que haya disponible. Así se evita que un bucle se atasque con muchas lecturas pequeñas.

**Parámetros:** *(opcional)* tiempo de espera en ms.

**Devuelve:** una cadena, o `undefined` si no se recibió nada antes de agotarse el tiempo de espera.

```js
serial.readAny(); // Read without timeout
serial.readAny(5000); // Read with 5s timeout
```

### readBytes()
Lee un número fijo de bytes como datos binarios.

**Parámetros:** número de bytes que se leen; *(opcional)* tiempo de espera en ms.

**Devuelve:** un `ArrayBuffer` con los datos recibidos, o `undefined` si no se recibió nada antes de agotarse el tiempo de espera.

```js
serial.readBytes(4); // Read 4 bytes, without timeout

// Read one byte from receive buffer with zero timeout, returns UNDEFINED if Rx buffer is empty
serial.readBytes(1, 0);
```

::: info
La documentación original describe `readBytes()` como «lee hasta un salto de línea». Es un error de copiar y pegar: como muestran sus parámetros, lee el número de bytes indicado.
:::

### expect()
Busca un patrón en el flujo de datos entrante.

**Parámetros:**

- un único patrón o un array de patrones, cada uno de ellos:
  - una cadena, o
  - un array de números (bytes);
- *(opcional)* tiempo de espera en ms.

**Devuelve:** el índice del patrón coincidente dentro de la lista, o `undefined` si no coincidió nada.

```js
// Wait for root shell prompt with 1s timeout, returns 0 if it was received before timeout, undefined if not
serial.expect("# ", 1000);

// Infinitely wait for one of two strings, should return 0 if the first string got matched, 1 if the second one
serial.expect([": not found", "Usage: "]);
```

### end()
Desinicializa el puerto, de modo que se puede volver a configurar en el mismo script.

```js
serial.end();
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

## Páginas relacionadas

- [GPIO](/es/dev/js-gpio)
- `bad_uart.js` muestra `expect()` en acción: espera el prompt de una shell de root de Linux (`# `) en LPUART y le envía comandos.
