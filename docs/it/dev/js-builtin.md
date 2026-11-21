---
title: "JavaScript: funzioni integrate"
sidebarTitle: "JS: funzioni integrate"
order: 250
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_builtin.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/js_modules.c]
sources: [unleashed-docs, unleashed-src]
---
# Funzioni integrate

Queste funzioni e questi oggetti sono disponibili in ogni script senza `require()`.

## Funzioni globali

### require()
Carica il plugin di un modulo. Vedi [Usare i moduli JS](/it/dev/js-modules).

- **Parametri:** nome del modulo

```js
let serial = require("serial"); // Load "serial" module
```

### delay()
- **Parametri:** ritardo in ms

```js
delay(500); // Delay for 500ms
```

### print()
Stampa un messaggio sulla console a schermo (oppure nella CLI, se lo script è stato avviato dalla CLI).

- **Parametri:** un numero qualsiasi di argomenti di tipo String, Number, Bool o `undefined`

```js
print("string1", "string2", 123);
```

### oggetto console
Come `print()`, ma scrive **solo sulla console seriale (log)**, con il corrispondente livello di log:

- `console.log()`
- `console.warn()`
- `console.error()`
- `console.debug()`

### load()
Esegue un file JS e ne restituisce un valore.

- **Parametri:**
  - percorso del file;
  - oggetto facoltativo da usare come scope globale durante l'esecuzione del file.

```js
load("/ext/apps/Scripts/script.js");
```

### chr()
Converte un codice di carattere ASCII in una stringa.

```js
chr(65); // "A"
```

### die()
Termina lo script con il messaggio indicato.

```js
die("Some error occurred");
```

### parseInt()
Converte una stringa in un numero, con una base facoltativa.

```js
parseInt("123"); // 123
parseInt("7b", 16); // 123
```

## Number

### Number.toString()
Converte un numero in una stringa, con una base facoltativa.

```js
let num = 123;
num.toString(); // "123"
num.toString(16); // "0x7b"
```

## ArrayBuffer

**Campi:** `byteLength`, la lunghezza del buffer in byte.

### ArrayBuffer.slice()
Crea un `ArrayBuffer` contenente una parte del buffer.

- **Parametri:** indice iniziale; indice finale facoltativo, escluso.

```js
Uint8Array([1, 2, 3]).buffer.slice(0, 1) // ArrayBuffer([1])
```

## DataView (array tipizzati)

Wrapper attorno a un `ArrayBuffer` con un tipo di elemento fisso:

- `Uint8Array`, `Int8Array`
- `Uint16Array`, `Int16Array`
- `Uint32Array`, `Int32Array`

**Campi:**

- `byteLength`: lunghezza del buffer in byte;
- `length`: lunghezza del buffer in elementi tipizzati;
- `buffer`: l'`ArrayBuffer` sottostante.

## Array

**Campi:** `length`, il numero di elementi.

### Array.splice()
Rimuove elementi dall'array e li restituisce come nuovo array.

- **Parametri:** indice iniziale; numero facoltativo di elementi da prelevare.

```js
let arr = [1, 2, 3];
arr.splice(1); // [2, 3]
arr; // [1]
```

### Array.push()
Aggiunge un valore alla fine dell'array.

```js
let arr = [1, 2];
arr.push(3);
arr; // [1, 2, 3]
```

## String

**Campi:** `length`, il numero di caratteri (byte).

### String.charCodeAt()
Restituisce il codice del carattere all'indice indicato.

```js
"A".charCodeAt(0) // 65
```

### String.at()
Equivalente a `String.charCodeAt()`.

### String.indexOf()
Restituisce l'indice della prima occorrenza di una sottostringa, oppure `-1` se non la trova.

- **Parametri:** sottostringa da cercare; indice iniziale facoltativo.

```js
"Example".indexOf("amp") // 2
```

### String.slice()
Restituisce la sottostringa compresa tra due indici.

- **Parametri:** indice iniziale; indice finale facoltativo, escluso.

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

## Percorsi degli script

### __dirname
Percorso della directory che contiene lo script corrente.

```js
print(__dirname); // /ext/apps/Scripts
```

### __filename
Percorso del file dello script corrente.

```js
print(__filename); // /ext/apps/Scripts/path.js
```

## Compatibilità dell'SDK {#sdk-compatibility}

Gli script possono verificare quale versione dell'SDK JS e quali funzionalità aggiuntive offre il firmware. **Non** usare `flipper.firmwareVendor` o `flipper.jsSdkVersion` a questo scopo. Usa le funzioni riportate qui sotto.

Nell'attuale Unleashed la versione dell'SDK JS è **1.0**.

### sdkCompatibilityStatus()
Verifica la compatibilità tra lo script e l'SDK JS del firmware.

- **Restituisce:**
  - `"compatible"` se lo script e l'SDK JS sono compatibili;
  - `"firmwareTooOld"` se la versione major attesa è superiore a quella del firmware, oppure se la versione minor attesa è superiore a quella del firmware;
  - `"firmwareTooNew"` se la versione major attesa è inferiore a quella del firmware.

```js
sdkCompatibilityStatus(0, 3); // "compatible"
```

### isSdkCompatible()
Lo stesso controllo, con un valore booleano come risultato.

```js
isSdkCompatible(0, 3); // true
```

### checkSdkCompatibility()
Se le versioni non sono compatibili, chiede all'utente se continuare l'esecuzione dello script. Non fa nulla se sono compatibili.

```js
checkSdkCompatibility(0, 3);
```

### doesSdkSupport()
Verifica se **tutte** le funzionalità aggiuntive elencate sono supportate dall'interprete.

```js
doesSdkSupport(["gui-widget"]); // true
```

### checkSdkFeatures()
Lo stesso controllo, ma chiede all'utente se continuare nel caso manchi qualche funzionalità.

```js
checkSdkFeatures(["gui-widget"]);
```

::: tip Unleashed
Nomi delle funzionalità supportate da Unleashed: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, più i moduli aggiuntivi di Unleashed `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`. Vedi [Panoramica su JavaScript](/it/dev/js-about#unleashed-extras).
:::

Schema tipico per una funzionalità opzionale:

```js
if (doesSdkSupport(["subghz"])) {
    let subghz = require("subghz");
    // ...
}
```
