---
title: "JavaScript: infrared"
sidebarTitle: "JS: infrared"
order: 410
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_infrared]
sources: [unleashed-src]
---
# Modulo infrarossi

Un extra di Unleashed, assente nel firmware di serie. Invia segnali IR da uno script, per nome di protocollo oppure come elenco grezzo di temporizzazioni. Non c'è il lato ricezione: per catturare un segnale usa prima l'app Infrared.

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");
```

Il nome della feature è `infrared-send`, il nome del modulo è `infrared`.

Script di esempio: `/ext/apps/Scripts/js_examples/infrared-send.js`.

## Metodi

### sendSignal()
Invia un segnale usando un protocollo che il firmware conosce.

- **Parametri:**
  - `protocol`: `"NEC"`, `"NECext"`, `"NEC42"`, `"NEC42ext"`, `"Samsung32"`, `"RC6"`, `"RC5"`, `"RC5X"`, `"SIRC"`, `"SIRC15"`, `"SIRC20"`, `"Kaseikyo"` o `"RCA"`;
  - `address`: numero;
  - `command`: numero;
  - `options` (facoltativo): `{ repeat?: boolean, times?: number }`. `repeat` marca il segnale come pacchetto di ripetizione, `times` è quante volte inviarlo (predefinito 1).

```js
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
```

Nei file `.ir` address e command sono memorizzati in esadecimale little-endian, mentre un letterale numerico JS è big-endian. `A9 00 00 00` nel file qui diventa `0x000000A9`, quindi inverti i byte prima di incollarli.

### sendRawSignal()
Invia un segnale tramite le sue temporizzazioni di acceso/spento, per i telecomandi che nessun protocollo copre.

- **Parametri:**
  - `timings`: array di numeri, durate in microsecondi;
  - `startFromMark` (facoltativo): booleano, indica se il primo valore è un impulso anziché una pausa. Predefinito `true`;
  - `advancedSettings` (facoltativo): `{ frequency: number, dutyCycle: number }`. Una volta passato l'oggetto, entrambi i campi sono obbligatori. Senza di esso la portante è a 38000 Hz con duty cycle 0.33.

## Esempio

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");

// Samsung TV, volume down
print("Sending Samsung32");
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
delay(1000);

// Three presses in a row
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b, { times: 3 });
delay(1000);

// Raw timings at 36 kHz
infrared.sendRawSignal([3298, 1571, 442, 368, 442, 367], true, {
  frequency: 36000,
  dutyCycle: 0.33,
});
print("Done");
```

## Pagine correlate

- [Formato dei file IR](/it/infrared/file-format) — da dove leggere address e command
- [Protocolli IR supportati](/it/infrared/protocols)
- [Panoramica su JavaScript](/it/dev/js-about)
