---
title: "JavaScript: usbdisk"
sidebarTitle: "JS: usbdisk"
order: 430
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_usbdisk]
sources: [unleashed-src]
---
# Modul USB-Massenspeicher

Ein Unleashed-Extra, in der Stock-Firmware gibt es das nicht. Es lässt den Flipper am PC als USB-Stick erscheinen. Der Inhalt kommt aus einer Image-Datei auf der SD-Karte; der PC liest und schreibt die Blöcke direkt in diese Datei.

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
```

Beispielskript: `/ext/apps/Scripts/js_examples/usbdisk.js`.

`createImage()` legt ein leeres Image an, oder du kopierst selbst eine `.img` nach `/ext/apps_data/mass_storage/`. Die Datei wird in 512-Byte-Blöcken gelesen, ihre Größe muss also ein Vielfaches von 512 sein.

Hat das Skript vorher BadUSB benutzt, rufe zuerst [`badusb.quit()`](/de/dev/js-badusb#quit) auf, um den USB-Port freizugeben.

## Methoden

### createImage()
Legt ein leeres Image in der gewünschten Größe an. Der Platz wird nur belegt, nicht geschrieben, darum geht auch ein großes Image schnell. Die ersten 4 KB werden genullt, damit der PC anbietet, das neue Laufwerk zu formatieren. Wirft einen Fehler, wenn an dem Pfad schon etwas liegt oder die Karte zu voll ist.

- **Parameter:** `path`, wohin das Image kommt; `size`, die Größe in Byte, abgerundet auf ganze 512-Byte-Blöcke.

### start()
Öffnet das Image zum Lesen und Schreiben und verbindet das Laufwerk mit dem PC. Der Laufwerksname ist der Dateiname des Images ohne Endung. Wirft einen Fehler, wenn die Datei fehlt oder schon ein Laufwerk läuft.

- **Parameter:** `path`, der vollständige Pfad zum Image, z. B. `"/ext/apps_data/mass_storage/128MB.img"`.

### stop()
Trennt das Laufwerk und schließt die Datei. Passiert auch am Skriptende.

### wasEjected()
- **Rückgabe:** boolean, `true`, sobald der PC das Laufwerk ausgeworfen hat. Nimm es als Schleifenbedingung. Wirft einen Fehler, wenn kein Laufwerk läuft.

## Beispiel

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
`createImage()` ist neuer als der Rest des Moduls. Ein Skript, das auch auf älteren Builds laufen soll, prüft vorher `doesSdkSupport(["usbdisk-createimage"])` — so macht es das mitgelieferte Beispiel.
:::

## Verwandte Themen

- [Modul BadUSB](/de/dev/js-badusb) — `quit()` gibt USB für dieses Modul frei
- [Modul storage](/de/dev/js-storage) — vor dem Start prüfen, ob das Image existiert
- [JavaScript-Übersicht](/de/dev/js-about)
