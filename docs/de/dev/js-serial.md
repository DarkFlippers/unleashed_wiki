---
title: "JavaScript: serial (UART)"
sidebarTitle: "JS: serial"
order: 340
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_serial.md]
sources: [unleashed-docs]
---
# Modul serial

Das Modul `serial` sendet und empfängt Daten über die UART-Ports des Flipper an der GPIO-Stiftleiste. Nutze es, um
mit Routern, ESP32-Boards, GPS-Modulen, Debug-Konsolen usw. zu kommunizieren.

```js
let serial = require("serial");
```

| Portname | Pins |
|---|---|
| `"usart"` | TX = 13, RX = 14 |
| `"lpuart"` | TX = 15, RX = 16 |

Siehe [GPIO-Pinbelegung](/de/gpio/pinout). Denk daran: UART arbeitet beim Flipper mit 3,3 V.

Beispielskripte: `uart_echo.js`, `uart_echo_8e1.js`, `bad_uart.js` in `/ext/apps/Scripts/js_examples/`.

## Methoden

### setup()
Konfiguriert den seriellen Port. Rufe es **vor allen anderen Methoden** auf. Es deaktiviert automatisch den Dienst
für Erweiterungsmodule, um Störungen zu vermeiden.

**Parameter:**

- Portname: `"usart"` oder `"lpuart"`;
- Baudrate;
- optionales Framing-Objekt, z. B. `{ dataBits: "8", parity: "even", stopBits: "1" }`:
  - `dataBits`: `"6"`, `"7"`, `"8"`, `"9"`. 6 Datenbits nur mit aktivierter Parität (even oder odd); 9 Datenbits
    nur mit deaktivierter Parität (none);
  - `parity`: `"none"`, `"even"`, `"odd"`;
  - `stopBits`: `"0.5"`, `"1"`, `"1.5"`, `"2"`. LPUART unterstützt nur ganze Stoppbits (1 und 2, nicht 0.5 und
    1.5).

```js
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

### write()
Schreibt Daten in den Port.

**Parameter:** ein oder mehrere Argumente dieser Typen:

- eine Zeichenkette;
- eine einzelne Zahl, die als Byte interpretiert wird;
- ein Array von Zahlen, jede davon als Byte interpretiert;
- ein `ArrayBuffer` oder `DataView`.

```js
serial.write(0x0a); // Write a single byte 0x0A
serial.write("Hello, world!"); // Write a string
serial.write("Hello, world!", [0x0d, 0x0a]); // Write a string followed by two bytes
```

### read()
Liest eine feste Anzahl Zeichen.

**Parameter:** Anzahl der zu lesenden Bytes; *(optional)* Timeout in ms.

**Rückgabe:** eine Zeichenkette mit den empfangenen Zeichen oder `undefined`, wenn vor Ablauf des Timeouts nichts
empfangen wurde.

```js
serial.read(1); // Read a single byte, without timeout
serial.read(10, 5000); // Read 10 bytes, with 5s timeout
```

### readln()
Liest bis zu einem Zeilenumbruchzeichen.

**Parameter:** *(optional)* Timeout in ms.

**Rückgabe:** eine Zeichenkette oder `undefined`, wenn vor Ablauf des Timeouts nichts empfangen wurde.

```js
serial.readln(); // Read without timeout
serial.readln(5000); // Read with 5s timeout
```

### readAny()
Liest, so viele Daten gerade verfügbar sind. Das verhindert, dass eine Schleife bei vielen kleinen Lesevorgängen
ins Stocken gerät.

**Parameter:** *(optional)* Timeout in ms.

**Rückgabe:** eine Zeichenkette oder `undefined`, wenn vor Ablauf des Timeouts nichts empfangen wurde.

```js
serial.readAny(); // Read without timeout
serial.readAny(5000); // Read with 5s timeout
```

### readBytes()
Liest eine feste Anzahl Bytes als Binärdaten.

**Parameter:** Anzahl der zu lesenden Bytes; *(optional)* Timeout in ms.

**Rückgabe:** ein `ArrayBuffer` mit den empfangenen Daten oder `undefined`, wenn vor Ablauf des Timeouts nichts
empfangen wurde.

```js
serial.readBytes(4); // Read 4 bytes, without timeout

// Read one byte from receive buffer with zero timeout, returns UNDEFINED if Rx buffer is empty
serial.readBytes(1, 0);
```

::: info
Die Originaldokumentation beschreibt `readBytes()` als "read until line break". Das ist ein Copy-Paste-Fehler: wie
die Parameter zeigen, liest die Funktion die angegebene Anzahl Bytes.
:::

### expect()
Durchsucht den eingehenden Datenstrom nach einem Muster.

**Parameter:**

- ein einzelnes Muster oder ein Array von Mustern, jedes davon:
  - eine Zeichenkette oder
  - ein Array von Zahlen (Bytes);
- *(optional)* Timeout in ms.

**Rückgabe:** der Index des gefundenen Musters in der Liste oder `undefined`, wenn nichts passte.

```js
// Wait for root shell prompt with 1s timeout, returns 0 if it was received before timeout, undefined if not
serial.expect("# ", 1000);

// Infinitely wait for one of two strings, should return 0 if the first string got matched, 1 if the second one
serial.expect([": not found", "Usage: "]);
```

### end()
Deinitialisiert den Port, sodass er im selben Skript erneut eingerichtet werden kann.

```js
serial.end();
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

## Verwandte Themen

- [GPIO](/de/dev/js-gpio)
- `bad_uart.js` zeigt `expect()` in Aktion: es wartet auf den Prompt einer Linux-Root-Shell (`# `) an LPUART und
  sendet Befehle dorthin.
