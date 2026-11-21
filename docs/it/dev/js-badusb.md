---
title: "JavaScript: BadUSB"
sidebarTitle: "JS: badusb"
order: 290
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_badusb.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_badusb.c]
sources: [unleashed-docs, unleashed-src]
---
# Modulo BadUSB

Il modulo `badusb` trasforma Flipper Zero in una tastiera USB (HID) controllata da JavaScript. È un'alternativa programmabile ai classici [file DuckyScript di BadUSB](/it/badusb/script-format): nello stesso script hai variabili, cicli e tutti gli altri moduli JS (GUI, storage, serial).

```js
let badusb = require("badusb");
```

::: warning
Usalo solo su computer di tua proprietà o che sei autorizzato a testare.
:::

Script di esempio: `/ext/apps/Scripts/js_examples/badusb_demo.js`.

## Metodi

### setup()
Avvia l'USB HID, eventualmente con parametri personalizzati. Chiamalo **prima di tutti gli altri metodi**.

**Parametri:** oggetto di configurazione facoltativo:

- `vid`, `pid` (number): VID e PID; se usati, sono entrambi obbligatori;
- `mfrName` (string): nome del produttore (massimo 32 caratteri ASCII), facoltativo;
- `prodName` (string): nome del prodotto (massimo 32 caratteri ASCII), facoltativo;
- `layoutPath` (string): percorso di un file di layout di tastiera, facoltativo.

```js
// Start USB HID with default parameters
badusb.setup();
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer and product strings not defined
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB }); 
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer string = "Flipper Devices", product string = "Flipper Zero"
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB, mfrName: "Flipper Devices", prodName: "Flipper Zero" });
```

I layout di tastiera sono gli stessi file `.kl` usati dall'app BadUSB (in `/ext/badusb/assets/layouts/`), per esempio `layoutPath: "/ext/badusb/assets/layouts/de-DE.kl"`.

### isConnected()
Restituisce lo stato della connessione USB.

```js
if (badusb.isConnected()) {
    // Do something
} else {
    // Show an error
}
```

### press()
Preme e rilascia un tasto o una combinazione di tasti.

**Parametri:** nomi di tasti o modificatori, oppure codici dei tasti. Vedi l'[elenco dei nomi dei tasti](#key-names).

```js
badusb.press("a"); // Press "a" key
badusb.press("A"); // SHIFT + "a"
badusb.press("CTRL", "a"); // CTRL + "a"
badusb.press("CTRL", "SHIFT", "ESC"); // CTRL + SHIFT + ESC combo
badusb.press(98); // Press key with HID code (dec) 98 (Numpad 0 / Insert)
badusb.press(0x47); // Press key with HID code (hex) 0x47 (Scroll lock)
```

### hold()
Tiene premuto un tasto. Si possono tenere premuti fino a 5 tasti contemporaneamente (senza contare i modificatori).

**Parametri:** come per `press()`.

```js
badusb.hold("a"); // Press and hold "a" key
badusb.hold("CTRL", "v"); // Press and hold CTRL + "v" combo
```

### release()
Rilascia un tasto precedentemente tenuto premuto. Chiamato **senza parametri**, rilascia tutti i tasti.

**Parametri:** come per `press()`.

```js
badusb.release(); // Release all keys
badusb.release("a"); // Release "a" key
```

### print()
Digita una stringa.

**Parametri:** la stringa; *(facoltativo)* il ritardo tra le pressioni dei tasti in ms.

```js
badusb.print("Hello, world!"); // print "Hello, world!"
badusb.print("Hello, world!", 100); // Add 100ms delay between key presses
```

### println()
Come `print()`, seguito da una pressione di <kbd>ENTER</kbd>.

```js
badusb.println("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### altPrint()
Digita una stringa con il metodo **Alt+Numpad**, che funziona indipendentemente dal layout di tastiera impostato sull'host. **Solo Windows.**

**Parametri:** la stringa; *(facoltativo)* il ritardo tra le pressioni dei tasti in ms.

```js
badusb.altPrint("Hello, world!"); // print "Hello, world!"
badusb.altPrint("Hello, world!", 100); // Add 100ms delay between key presses
```

### altPrintln()
Come `altPrint()`, seguito da una pressione di <kbd>ENTER</kbd>.

```js
badusb.altPrintln("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### quit() {#quit}
Rilascia l'USB. È facoltativo, ma consente allo script di passare a un'altra modalità USB, per esempio al modulo `usbdisk`.

```js
badusb.quit();
usbdisk.start(...)
```

::: tip Unleashed
`usbdisk` (emulazione di un'unità di archiviazione di massa USB) è un modulo JS esclusivo di Unleashed; vedi [Panoramica su JavaScript](/it/dev/js-about#unleashed-extras).
:::

## Nomi dei tasti {#key-names}

### Tasti modificatori

| Nome |
|---|
| CTRL |
| SHIFT |
| ALT |
| GUI |

### Tasti speciali

| Nome | Note |
|---|---|
| DOWN | Freccia giù |
| LEFT | Freccia sinistra |
| RIGHT | Freccia destra |
| UP | Freccia su |
| ENTER | |
| DELETE | |
| BACKSPACE | |
| END | |
| HOME | |
| ESC | |
| INSERT | |
| PAGEUP | |
| PAGEDOWN | |
| CAPSLOCK | |
| NUMLOCK | |
| SCROLLLOCK | |
| PRINTSCREEN | |
| PAUSE | Tasto Pause/Break |
| SPACE | |
| TAB | |
| MENU | Tasto del menu contestuale |
| Fx | Tasti da F1 a F24 |
| NUMx | Tasti da NUM0 a NUM9 |

## Pagine correlate

- [Uso di BadUSB](/it/badusb/usage) e [formato degli script](/it/badusb/script-format)
- [Event loop](/it/dev/js-event-loop), [GUI](/it/dev/js-gui) per menu di payload interattivi
