---
title: "JavaScript: usbdisk"
sidebarTitle: "JS: usbdisk"
order: 430
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_usbdisk]
sources: [unleashed-src]
---
# Modulo archiviazione di massa USB

Un extra di Unleashed, assente nel firmware di serie. Fa apparire il Flipper al PC come una chiavetta USB. Il contenuto arriva da un file immagine sulla scheda SD; il PC legge e scrive i blocchi direttamente dentro quel file.

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
```

Script di esempio: `/ext/apps/Scripts/js_examples/usbdisk.js`.

`createImage()` crea un'immagine vuota, oppure copi tu stesso un `.img` in `/ext/apps_data/mass_storage/`. Il file viene letto in blocchi da 512 byte, quindi la sua dimensione deve essere un multiplo di 512.

Se prima lo script ha usato BadUSB, chiama [`badusb.quit()`](/it/dev/js-badusb#quit) per liberare la porta USB.

## Metodi

### createImage()
Crea un'immagine vuota della dimensione richiesta. Lo spazio viene solo riservato, non scritto, quindi anche un'immagine grande è veloce. I primi 4 KB vengono azzerati così il PC propone di formattare la nuova unità. Genera un errore se a quel percorso c'è già qualcosa o se la scheda è troppo piena.

- **Parametri:** `path`, dove mettere l'immagine; `size`, la dimensione in byte, arrotondata per difetto a blocchi interi da 512 byte.

### start()
Apre l'immagine in lettura e scrittura e collega l'unità al PC. Il nome dell'unità è il nome del file immagine senza estensione. Genera un errore se il file manca o se un disco è già in funzione.

- **Parametri:** `path`, il percorso completo dell'immagine, per esempio `"/ext/apps_data/mass_storage/128MB.img"`.

### stop()
Scollega l'unità e chiude il file. Avviene anche alla fine dello script.

### wasEjected()
- **Restituisce:** booleano, `true` una volta che il PC ha espulso l'unità. Usalo come condizione di un ciclo. Genera un errore se il disco non è in funzione.

## Esempio

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
let storage = require("storage");

let imagePath = "/ext/apps_data/mass_storage/128MB.img";
if (!storage.fileExists(imagePath)) {
    usbdisk.createImage(imagePath, 128 * 1024 * 1024);
}

print("Starting UsbDisk...");
usbdisk.start(imagePath);

print("Started, waiting until ejected...");
while (!usbdisk.wasEjected()) {
    delay(1000);
}

print("Ejected, stopping UsbDisk...");
usbdisk.stop();
```

::: tip
`createImage()` è arrivato dopo il resto del modulo. Uno script che può girare anche su una build più vecchia dovrebbe prima controllare `doesSdkSupport(["usbdisk-createimage"])`, come fa l'esempio incluso.
:::

## Pagine correlate

- [Modulo BadUSB](/it/dev/js-badusb) — `quit()` libera l'USB per questo modulo
- [Modulo storage](/it/dev/js-storage) — controlla che l'immagine esista prima di partire
- [Panoramica su JavaScript](/it/dev/js-about)
