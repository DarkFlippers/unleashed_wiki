---
title: "JavaScript: infrared"
sidebarTitle: "JS: infrared"
order: 410
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_infrared]
sources: [unleashed-src]
---
# Modul infrared

Dodatak firmvera Unleashed, nije prisutan u službenom firmveru. Šalje IR signale iz skripte, bilo po nazivu protokola ili kao sirovi (raw) popis vremenskih intervala. Ne postoji strana za primanje — upotrijebite aplikaciju Infrared za prethodno snimanje signala.

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");
```

Naziv značajke je `infrared-send`, a naziv modula `infrared`.

Primjer skripte: `/ext/apps/Scripts/js_examples/infrared-send.js`.

## Metode

### sendSignal()
Šalje signal koristeći protokol koji firmver poznaje.

- **Parametri:**
  - `protocol`: `"NEC"`, `"NECext"`, `"NEC42"`, `"NEC42ext"`, `"Samsung32"`, `"RC6"`, `"RC5"`, `"RC5X"`, `"SIRC"`, `"SIRC15"`, `"SIRC20"`, `"Kaseikyo"` ili `"RCA"`;
  - `address`: broj;
  - `command`: broj;
  - `options` (neobavezno): `{ repeat?: boolean, times?: number }`. `repeat` označava signal kao ponavljajući okvir (repeat frame), a `times` koliko ga puta poslati (zadano 1).

```js
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
```

U datotekama `.ir` adresa i naredba pohranjene su kao little-endian heksadecimalni zapisi, dok je JS brojevni literal big-endian. `A9 00 00 00` u datoteci ovdje je `0x000000A9`, pa obrnite redoslijed bajtova prije nego što ih zalijepite.

### sendRawSignal()
Šalje signal putem njegovih vremenskih intervala uključeno/isključeno, za daljinske upravljače koje ne pokriva nijedan protokol.

- **Parametri:**
  - `timings`: polje brojeva, trajanja u mikrosekundama;
  - `startFromMark` (neobavezno): logička vrijednost (boolean), označava je li prva vrijednost impuls umjesto pauze. Zadano `true`;
  - `advancedSettings` (neobavezno): `{ frequency: number, dutyCycle: number }`. Oba su polja obavezna ako je objekt zadan. Bez njega nositelj je 38000 Hz uz radni ciklus (duty cycle) 0.33.

## Primjer

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");

// Samsung TV, stišavanje zvuka
print("Sending Samsung32");
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
delay(1000);

// Tri pritiska zaredom
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b, { times: 3 });
delay(1000);

// Sirovi (raw) vremenski intervali na 36 kHz
infrared.sendRawSignal([3298, 1571, 442, 368, 442, 367], true, {
  frequency: 36000,
  dutyCycle: 0.33,
});
print("Done");
```

## Povezano

- [Format datoteke Infrared](/hr/infrared/file-format) — odakle pročitati adresu i naredbu
- [Podržani IR protokoli](/hr/infrared/protocols)
- [Pregled JavaScripta](/hr/dev/js-about)
