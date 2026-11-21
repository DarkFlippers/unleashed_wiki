---
title: "JavaScript: serial (UART)"
sidebarTitle: "JS: serial"
order: 340
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_serial.md]
sources: [unleashed-docs]
---
# Modulo serial

Il modulo `serial` invia e riceve dati sulle porte UART del Flipper presenti sul connettore GPIO. Usalo per dialogare con router, schede ESP32, moduli GPS, console di debug e così via.

```js
let serial = require("serial");
```

| Nome della porta | Pin |
|---|---|
| `"usart"` | TX = 13, RX = 14 |
| `"lpuart"` | TX = 15, RX = 16 |

Vedi [Pinout GPIO](/it/gpio/pinout). Ricorda: l'UART del Flipper è a 3,3 V.

Script di esempio: `uart_echo.js`, `uart_echo_8e1.js`, `bad_uart.js` in `/ext/apps/Scripts/js_examples/`.

## Metodi

### setup()
Configura la porta seriale. Chiamalo **prima di tutti gli altri metodi**. Disattiva automaticamente il servizio del modulo di espansione per evitare interferenze.

**Parametri:**

- nome della porta: `"usart"` o `"lpuart"`;
- velocità in baud;
- oggetto di framing facoltativo, per esempio `{ dataBits: "8", parity: "even", stopBits: "1" }`:
  - `dataBits`: `"6"`, `"7"`, `"8"`, `"9"`. 6 bit di dati solo con parità abilitata (even o odd); 9 bit di dati solo con parità disabilitata (none);
  - `parity`: `"none"`, `"even"`, `"odd"`;
  - `stopBits`: `"0.5"`, `"1"`, `"1.5"`, `"2"`. LPUART supporta solo bit di stop interi (1 e 2, non 0,5 e 1,5).

```js
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

### write()
Scrive dati sulla porta.

**Parametri:** uno o più argomenti di questi tipi:

- una stringa;
- un singolo numero, interpretato come un byte;
- un array di numeri, ciascuno interpretato come un byte;
- un `ArrayBuffer` o un `DataView`.

```js
serial.write(0x0a); // Write a single byte 0x0A
serial.write("Hello, world!"); // Write a string
serial.write("Hello, world!", [0x0d, 0x0a]); // Write a string followed by two bytes
```

### read()
Legge un numero fisso di caratteri.

**Parametri:** numero di byte da leggere; *(facoltativo)* timeout in ms.

**Restituisce:** una stringa con i caratteri ricevuti, oppure `undefined` se non è stato ricevuto nulla prima del timeout.

```js
serial.read(1); // Read a single byte, without timeout
serial.read(10, 5000); // Read 10 bytes, with 5s timeout
```

### readln()
Legge fino a un carattere di interruzione di riga.

**Parametri:** *(facoltativo)* timeout in ms.

**Restituisce:** una stringa, oppure `undefined` se non è stato ricevuto nulla prima del timeout.

```js
serial.readln(); // Read without timeout
serial.readln(5000); // Read with 5s timeout
```

### readAny()
Legge la quantità di dati disponibile, qualunque essa sia. Questo evita che un ciclo si blocchi su molte letture di piccole dimensioni.

**Parametri:** *(facoltativo)* timeout in ms.

**Restituisce:** una stringa, oppure `undefined` se non è stato ricevuto nulla prima del timeout.

```js
serial.readAny(); // Read without timeout
serial.readAny(5000); // Read with 5s timeout
```

### readBytes()
Legge un numero fisso di byte come dati binari.

**Parametri:** numero di byte da leggere; *(facoltativo)* timeout in ms.

**Restituisce:** un `ArrayBuffer` con i dati ricevuti, oppure `undefined` se non è stato ricevuto nulla prima del timeout.

```js
serial.readBytes(4); // Read 4 bytes, without timeout

// Read one byte from receive buffer with zero timeout, returns UNDEFINED if Rx buffer is empty
serial.readBytes(1, 0);
```

::: info
La documentazione originale descrive `readBytes()` come "legge fino all'interruzione di riga". Si tratta di un errore di copia-incolla: come mostrano i suoi parametri, legge il numero di byte indicato.
:::

### expect()
Cerca un pattern nel flusso di dati in arrivo.

**Parametri:**

- un singolo pattern o un array di pattern, ciascuno dei quali è:
  - una stringa, oppure
  - un array di numeri (byte);
- *(facoltativo)* timeout in ms.

**Restituisce:** l'indice del pattern corrispondente nell'elenco, oppure `undefined` se nessuno ha corrisposto.

```js
// Wait for root shell prompt with 1s timeout, returns 0 if it was received before timeout, undefined if not
serial.expect("# ", 1000);

// Infinitely wait for one of two strings, should return 0 if the first string got matched, 1 if the second one
serial.expect([": not found", "Usage: "]);
```

### end()
Deinizializza la porta, così da poterla riconfigurare nello stesso script.

```js
serial.end();
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

## Pagine correlate

- [GPIO](/it/dev/js-gpio)
- `bad_uart.js` mostra `expect()` in azione: attende il prompt di una shell root Linux (`# `) su LPUART e le invia dei comandi.
