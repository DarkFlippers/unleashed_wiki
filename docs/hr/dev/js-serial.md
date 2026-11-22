---
title: "JavaScript: serial (UART)"
sidebarTitle: "JS: serial"
order: 340
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_serial.md]
sources: [unleashed-docs]
---
# Modul Serial

Modul `serial` šalje i prima podatke putem Flipperovih UART priključaka na GPIO zaglavlju. Koristite ga za komunikaciju s usmjerivačima, ESP32 pločicama, GPS modulima, konzola za otklanjanje grešaka itd.

```js
let serial = require("serial");
```

| Naziv priključka | Pinovi |
|---|---|
| `"usart"` | TX = 13, RX = 14 |
| `"lpuart"` | TX = 15, RX = 16 |

Pogledajte [raspored GPIO pinova](/hr/gpio/pinout). Zapamtite: UART na Flipperu radi na 3,3 V.

Primjeri skripti: `uart_echo.js`, `uart_echo_8e1.js`, `bad_uart.js` u `/ext/apps/Scripts/js_examples/`.

## Metode

### setup()
Konfigurira serijski priključak. Pozovite je **prije svih ostalih metoda**. Automatski onemogućuje servis modula za proširenje (Expansion module) kako ne bi došlo do smetnji.

**Parametri:**

- naziv priključka: `"usart"` ili `"lpuart"`;
- brzina prijenosa (baud rate);
- opcionalni objekt okvira prijenosa, npr. `{ dataBits: "8", parity: "even", stopBits: "1" }`:
  - `dataBits`: `"6"`, `"7"`, `"8"`, `"9"`. 6 podatkovnih bitova samo uz omogućenu parnost (parna ili neparna); 9 podatkovnih bitova samo uz onemogućenu parnost (none);
  - `parity`: `"none"`, `"even"`, `"odd"`;
  - `stopBits`: `"0.5"`, `"1"`, `"1.5"`, `"2"`. LPUART podržava samo cjelobrojne stop bitove (1 i 2, ne 0.5 i 1.5).

```js
// Konfiguriraj LPUART priključak s brzinom prijenosa 115200
serial.setup("lpuart", 115200);
```

### write()
Zapisuje podatke na priključak.

**Parametri:** jedan ili više argumenata sljedećih tipova:

- niz znakova (string);
- jedan broj, protumačen kao bajt;
- polje brojeva, svaki protumačen kao bajt;
- `ArrayBuffer` ili `DataView`.

```js
serial.write(0x0a); // Zapiši jedan bajt 0x0A
serial.write("Hello, world!"); // Zapiši niz znakova
serial.write("Hello, world!", [0x0d, 0x0a]); // Zapiši niz znakova nakon kojeg slijede dva bajta
```

### read()
Čita zadani broj znakova.

**Parametri:** broj bajtova za čitanje; *(opcionalno)* vremensko ograničenje (timeout) u ms.

**Vraća:** niz primljenih znakova ili `undefined` ako ništa nije primljeno prije isteka vremenskog ograničenja.

```js
serial.read(1); // Pročitaj jedan bajt, bez vremenskog ograničenja
serial.read(10, 5000); // Pročitaj 10 bajtova, s vremenskim ograničenjem od 5 s
```

### readln()
Čita do znaka za prijelom retka.

**Parametri:** *(opcionalno)* vremensko ograničenje u ms.

**Vraća:** niz znakova ili `undefined` ako ništa nije primljeno prije isteka vremenskog ograničenja.

```js
serial.readln(); // Čitaj bez vremenskog ograničenja
serial.readln(5000); // Čitaj s vremenskim ograničenjem od 5 s
```

### readAny()
Čita bilo koju količinu dostupnih podataka. Time se sprječava zastoj petlje zbog mnogo malih čitanja.

**Parametri:** *(opcionalno)* vremensko ograničenje u ms.

**Vraća:** niz znakova ili `undefined` ako ništa nije primljeno prije isteka vremenskog ograničenja.

```js
serial.readAny(); // Čitaj bez vremenskog ograničenja
serial.readAny(5000); // Čitaj s vremenskim ograničenjem od 5 s
```

### readBytes()
Čita zadani broj bajtova kao binarne podatke.

**Parametri:** broj bajtova za čitanje; *(opcionalno)* vremensko ograničenje u ms.

**Vraća:** `ArrayBuffer` s primljenim podacima ili `undefined` ako ništa nije primljeno prije isteka vremenskog ograničenja.

```js
serial.readBytes(4); // Pročitaj 4 bajta, bez vremenskog ograničenja

// Pročitaj jedan bajt iz prijemnog međuspremnika s nultim vremenskim ograničenjem, vraća UNDEFINED ako je Rx međuspremnik prazan
serial.readBytes(1, 0);
```

::: info
Izvorna dokumentacija opisuje `readBytes()` kao „čitanje do prijeloma retka“. To je greška nastala kopiranjem i lijepljenjem: kao što pokazuju parametri, metoda čita zadani broj bajtova.
:::

### expect()
Pretražuje dolazni tok podataka za zadanim uzorkom.

**Parametri:**

- jedan uzorak ili polje uzoraka, od kojih je svaki:
  - niz znakova, ili
  - polje brojeva (bajtova);
- *(opcionalno)* vremensko ograničenje u ms.

**Vraća:** indeks podudarnog uzorka u popisu ili `undefined` ako se ništa nije podudaralo.

```js
// Čekaj upit root ljuske s vremenskim ograničenjem od 1 s, vraća 0 ako je primljen prije isteka, undefined ako nije
serial.expect("# ", 1000);

// Beskonačno čekaj jedan od dva niza znakova, vraća 0 ako je prvi podudaren, 1 ako je drugi
serial.expect([": not found", "Usage: "]);
```

### end()
Deinicijalizira priključak kako bi se mogao ponovno postaviti u istoj skripti.

```js
serial.end();
// Konfiguriraj LPUART priključak s brzinom prijenosa 115200
serial.setup("lpuart", 115200);
```

## Povezano

- [GPIO](/hr/dev/js-gpio)
- `bad_uart.js` pokazuje `expect()` na djelu: čeka upit root ljuske Linuxa (`# `) na LPUART-u i šalje mu naredbe.
