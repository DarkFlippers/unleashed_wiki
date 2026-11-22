---
title: "JavaScript: usbdisk"
sidebarTitle: "JS: usbdisk"
order: 430
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_usbdisk]
sources: [unleashed-src]
---
# Modul za USB masovnu pohranu (usbdisk)

Dodatak firmvera Unleashed koji nije prisutan u tvorničkom firmveru. Prikazuje Flipper računalu kao USB flash pogon. Sadržaj dolazi iz jedne datoteke slike na SD kartici; računalo čita i zapisuje blokove izravno u tu datoteku.

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
```

Primjer skripte: `/ext/apps/Scripts/js_examples/usbdisk.js`.

`createImage()` stvara praznu sliku, ili možete sami kopirati `.img` u `/ext/apps_data/mass_storage/`. Datoteka se čita u blokovima od 512 bajtova, pa njezina veličina mora biti višekratnik broja 512.

Ako je skripta prije toga koristila BadUSB, prvo pozovite [`badusb.quit()`](/hr/dev/js-badusb#quit) kako biste oslobodili USB priključak.

## Metode

### createImage()
Stvara praznu sliku tražene veličine. Prostor se samo rezervira, ne zapisuje se, pa je i stvaranje velike slike brzo. Prvih 4 KB se briše kako bi računalo ponudilo formatiranje novog diska. Baca iznimku ako na toj putanji već nešto postoji ili ako je kartica prepuna.

- **Parametri:** `path`, kamo spremiti sliku; `size`, bajtovi, zaokruženo naniže na cijeli blok od 512 bajtova.

### start()
Otvara sliku za čitanje i pisanje te povezuje pogon s računalom. Naziv pogona jest naziv datoteke slike bez nastavka. Baca iznimku ako datoteka nedostaje ili ako je disk već pokrenut.

- **Parametri:** `path`, puna putanja do slike, npr. `"/ext/apps_data/mass_storage/128MB.img"`.

### stop()
Odspaja pogon i zatvara datoteku. Također se izvršava automatski kada skripta završi.

### wasEjected()
- **Vraća:** logičku vrijednost (boolean), `true` nakon što računalo izbaci (eject) pogon. Koristite kao uvjet petlje. Baca iznimku ako disk nije pokrenut.

## Primjer

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
`createImage()` je noviji od ostatka modula. Skripta koja se može pokretati i na starijoj inačici firmvera trebala bi najprije provjeriti `doesSdkSupport(["usbdisk-createimage"])`, kao što to čini priloženi primjer.
:::

## Povezano

- [Modul BadUSB](/hr/dev/js-badusb) — `quit()` oslobađa USB za ovaj modul
- [Modul Storage](/hr/dev/js-storage) — provjera postoji li slika prije pokretanja
- [Pregled JavaScripta](/hr/dev/js-about)
