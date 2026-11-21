---
title: "JavaScript: usbdisk"
sidebarTitle: "JS: usbdisk"
order: 430
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_usbdisk]
sources: [unleashed-src]
---
# Módulo de almacenamiento USB

Un extra de Unleashed, no está en el firmware de serie. Hace que el PC vea el Flipper como una memoria USB. El contenido sale de un fichero de imagen en la tarjeta SD: el PC lee y escribe bloques directamente en ese fichero.

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
```

Script de ejemplo: `/ext/apps/Scripts/js_examples/usbdisk.js`.

`createImage()` crea una imagen vacía, o puedes copiar tú mismo un `.img` a `/ext/apps_data/mass_storage/`. El fichero se lee en bloques de 512 bytes, así que su tamaño tiene que ser múltiplo de 512.

Si el script ha usado BadUSB antes, llama primero a [`badusb.quit()`](/es/dev/js-badusb#quit) para liberar el puerto USB.

## Métodos

### createImage()
Crea una imagen vacía del tamaño que le pidas. El espacio solo se reserva, no se escribe, así que incluso una imagen grande se hace rápido. Los primeros 4 KB se ponen a cero para que el PC ofrezca formatear la unidad nueva. Lanza un error si ya hay algo en esa ruta o si la tarjeta está demasiado llena.

- **Parámetros:** `path`, dónde dejar la imagen; `size`, su tamaño en bytes, redondeado hacia abajo a bloques enteros de 512 bytes.

### start()
Abre la imagen para lectura y escritura y conecta la unidad al PC. La unidad se llama como el fichero de imagen sin la extensión. Lanza un error si falta el fichero o si ya hay un disco en marcha.

- **Parámetros:** `path`, la ruta completa a la imagen, p. ej. `"/ext/apps_data/mass_storage/128MB.img"`.

### stop()
Desconecta la unidad y cierra el fichero. También ocurre al terminar el script.

### wasEjected()
- **Devuelve:** booleano, `true` en cuanto el PC ha expulsado la unidad. Úsalo como condición de bucle. Lanza un error si el disco no está en marcha.

## Ejemplo

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
`createImage()` llegó después del resto del módulo. Un script que también pueda ejecutarse en una compilación antigua debería comprobar antes `doesSdkSupport(["usbdisk-createimage"])`, como hace el ejemplo incluido.
:::

## Páginas relacionadas

- [Módulo BadUSB](/es/dev/js-badusb) — `quit()` libera el USB para este módulo
- [Módulo storage](/es/dev/js-storage) — comprueba si la imagen existe antes de arrancar
- [Visión general de JavaScript](/es/dev/js-about)
