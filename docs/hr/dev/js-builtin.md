---
title: "JavaScript: ugrađene funkcije"
sidebarTitle: "JS: ugrađene funkcije"
order: 250
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_builtin.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/js_modules.c]
sources: [unleashed-docs, unleashed-src]
---
# Ugrađene funkcije

Ove su funkcije i objekti dostupni u svakoj skripti bez poziva `require()`.

## Globalne funkcije

### require()
Učitava dodatak modula. Pogledajte [Korištenje JS modula](/hr/dev/js-modules).

- **Parametri:** naziv modula

```js
let serial = require("serial"); // Učitaj modul "serial"
```

### delay()
- **Parametri:** kašnjenje u ms

```js
delay(500); // Kašnjenje od 500ms
```

### print()
Ispisuje poruku na konzolu na zaslonu (ili u CLI, ako je skripta pokrenuta iz CLI-ja).

- **Parametri:** bilo koji broj argumenata tipa String, Number, Bool ili `undefined`

```js
print("string1", "string2", 123);
```

### objekt console
Isto kao `print()`, ali zapisuje **samo na serijsku konzolu (zapisnik)**, s odgovarajućom razinom zapisa:

- `console.log()`
- `console.warn()`
- `console.error()`
- `console.debug()`

### load()
Izvršava JS datoteku i vraća vrijednost iz nje.

- **Parametri:**
  - putanja do datoteke;
  - neobavezni objekt koji se koristi kao globalni doseg (scope) tijekom izvođenja datoteke.

```js
load("/ext/apps/Scripts/script.js");
```

### chr()
Pretvara ASCII kod znaka u niz znakova.

```js
chr(65); // "A"
```

### die()
Završava izvršavanje skripte sa zadanom porukom.

```js
die("Some error occurred");
```

### parseInt()
Pretvara niz znakova u broj, s neobaveznom bazom brojevnog sustava.

```js
parseInt("123"); // 123
parseInt("7b", 16); // 123
```

## Number

### Number.toString()
Pretvara broj u niz znakova, s neobaveznom bazom brojevnog sustava.

```js
let num = 123;
num.toString(); // "123"
num.toString(16); // "0x7b"
```

## ArrayBuffer

**Polja:** `byteLength`, duljina međuspremnika u bajtovima.

### ArrayBuffer.slice()
Stvara `ArrayBuffer` koji sadrži dio međuspremnika.

- **Parametri:** početni indeks; neobavezni isključivi završni indeks.

```js
Uint8Array([1, 2, 3]).buffer.slice(0, 1) // ArrayBuffer([1])
```

## DataView (tipizirana polja)

Omotači oko objekta `ArrayBuffer` s fiksnim tipom elemenata:

- `Uint8Array`, `Int8Array`
- `Uint16Array`, `Int16Array`
- `Uint32Array`, `Int32Array`

**Polja:**

- `byteLength`: duljina međuspremnika u bajtovima;
- `length`: duljina međuspremnika u tipiziranim elementima;
- `buffer`: temeljni `ArrayBuffer`.

## Array

**Polja:** `length`, broj elemenata.

### Array.splice()
Uklanja elemente iz polja i vraća ih kao novo polje.

- **Parametri:** početni indeks; neobavezni broj elemenata za uzimanje.

```js
let arr = [1, 2, 3];
arr.splice(1); // [2, 3]
arr; // [1]
```

### Array.push()
Dodaje vrijednost na kraj polja.

```js
let arr = [1, 2];
arr.push(3);
arr; // [1, 2, 3]
```

## String

**Polja:** `length`, broj znakova (bajtova).

### String.charCodeAt()
Vraća kod znaka na određenom indeksu.

```js
"A".charCodeAt(0) // 65
```

### String.at()
Isto kao `String.charCodeAt()`.

### String.indexOf()
Vraća indeks prvog pojavljivanja podniza ili `-1` ako nije pronađen.

- **Parametri:** podniz za pretraživanje; neobavezni početni indeks.

```js
"Example".indexOf("amp") // 2
```

### String.slice()
Vraća podniz između dvaju indeksa.

- **Parametri:** početni indeks; neobavezni isključivi završni indeks.

```js
"Example".slice(2) // "ample"
```

### String.toUpperCase()

```js
"Example".toUpperCase() // "EXAMPLE"
```

### String.toLowerCase()

```js
"Example".toLowerCase() // "example"
```

## Putanje skripte

### __dirname
Putanja do direktorija koji sadrži trenutnu skriptu.

```js
print(__dirname); // /ext/apps/Scripts
```

### __filename
Putanja do datoteke trenutne skripte.

```js
print(__filename); // /ext/apps/Scripts/path.js
```

## Kompatibilnost SDK-a {#sdk-compatibility}

Skripte mogu provjeriti koju verziju JS SDK-a i koje dodatne značajke firmver pruža. Za to **nemojte** koristiti `flipper.firmwareVendor` ni `flipper.jsSdkVersion`. Upotrijebite funkcije u nastavku.

Na trenutnom Unleashed firmveru verzija JS SDK-a je **1.0**.

### sdkCompatibilityStatus()
Provjerava kompatibilnost između skripte i JS SDK-a firmvera.

- **Vraća:**
  - `"compatible"` ako su skripta i JS SDK kompatibilni;
  - `"firmwareTooOld"` ako je očekivana glavna (major) verzija veća od verzije firmvera, ili ako je očekivana sporedna (minor) verzija veća od verzije firmvera;
  - `"firmwareTooNew"` ako je očekivana glavna (major) verzija manja od verzije firmvera.

```js
sdkCompatibilityStatus(0, 3); // "compatible"
```

### isSdkCompatible()
Ista provjera, vraća logičku vrijednost (boolean).

```js
isSdkCompatible(0, 3); // true
```

### checkSdkCompatibility()
Ako verzije nisu kompatibilne, pita korisnika želi li nastaviti s izvršavanjem skripte. Ne čini ništa ako su kompatibilne.

```js
checkSdkCompatibility(0, 3);
```

### doesSdkSupport()
Provjerava podržava li interpreter **sve** navedene dodatne značajke.

```js
doesSdkSupport(["gui-widget"]); // true
```

### checkSdkFeatures()
Ista provjera, ali pita korisnika želi li nastaviti ako neke značajke nedostaju.

```js
checkSdkFeatures(["gui-widget"]);
```

::: tip Unleashed
Nazivi značajki koje podržava Unleashed: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, te dodatni Unleashed moduli `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`. Pogledajte [Pregled JavaScripta](/hr/dev/js-about#unleashed-extras).
:::

Tipičan obrazac za neobaveznu značajku:

```js
if (doesSdkSupport(["subghz"])) {
    let subghz = require("subghz");
    // ...
}
```
