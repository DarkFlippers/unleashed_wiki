---
title: "JavaScript: BadUSB"
sidebarTitle: "JS: badusb"
order: 290
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_badusb.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_badusb.c]
sources: [unleashed-docs, unleashed-src]
---
# Módulo BadUSB

El módulo `badusb` convierte el Flipper Zero en un teclado USB (HID) controlado desde JavaScript. Es una alternativa programable a los clásicos [archivos DuckyScript de BadUSB](/es/badusb/script-format): tienes variables, bucles y el resto de los módulos de JS (GUI, storage, serial) en el mismo script.

```js
let badusb = require("badusb");
```

::: warning
Úsalo solo en ordenadores que sean tuyos o en los que tengas permiso para hacer pruebas.
:::

Script de ejemplo: `/ext/apps/Scripts/js_examples/badusb_demo.js`.

## Métodos

### setup()
Inicia el HID USB, opcionalmente con parámetros personalizados. Llámalo **antes que todos los demás métodos**.

**Parámetros:** objeto de configuración opcional:

- `vid`, `pid` (number): VID y PID; si se usan, ambos son obligatorios;
- `mfrName` (string): nombre del fabricante (32 caracteres ASCII como máximo), opcional;
- `prodName` (string): nombre del producto (32 caracteres ASCII como máximo), opcional;
- `layoutPath` (string): ruta a un archivo de distribución de teclado, opcional.

```js
// Start USB HID with default parameters
badusb.setup();
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer and product strings not defined
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB }); 
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer string = "Flipper Devices", product string = "Flipper Zero"
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB, mfrName: "Flipper Devices", prodName: "Flipper Zero" });
```

Las distribuciones de teclado son los mismos archivos `.kl` que usa la app BadUSB (en `/ext/badusb/assets/layouts/`), por ejemplo `layoutPath: "/ext/badusb/assets/layouts/de-DE.kl"`.

### isConnected()
Devuelve el estado de la conexión USB.

```js
if (badusb.isConnected()) {
    // Do something
} else {
    // Show an error
}
```

### press()
Pulsa y suelta una tecla o una combinación de teclas.

**Parámetros:** nombres de teclas o modificadores, o códigos de tecla. Consulta la [lista de nombres de teclas](#key-names).

```js
badusb.press("a"); // Press "a" key
badusb.press("A"); // SHIFT + "a"
badusb.press("CTRL", "a"); // CTRL + "a"
badusb.press("CTRL", "SHIFT", "ESC"); // CTRL + SHIFT + ESC combo
badusb.press(98); // Press key with HID code (dec) 98 (Numpad 0 / Insert)
badusb.press(0x47); // Press key with HID code (hex) 0x47 (Scroll lock)
```

### hold()
Mantiene pulsada una tecla. Se pueden mantener hasta 5 teclas a la vez (sin contar los modificadores).

**Parámetros:** los mismos que en `press()`.

```js
badusb.hold("a"); // Press and hold "a" key
badusb.hold("CTRL", "v"); // Press and hold CTRL + "v" combo
```

### release()
Suelta una tecla mantenida previamente. Si se llama **sin parámetros**, suelta todas las teclas.

**Parámetros:** los mismos que en `press()`.

```js
badusb.release(); // Release all keys
badusb.release("a"); // Release "a" key
```

### print()
Escribe una cadena.

**Parámetros:** la cadena; *(opcional)* retardo entre pulsaciones en ms.

```js
badusb.print("Hello, world!"); // print "Hello, world!"
badusb.print("Hello, world!", 100); // Add 100ms delay between key presses
```

### println()
Igual que `print()`, seguido de una pulsación de <kbd>ENTER</kbd>.

```js
badusb.println("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### altPrint()
Escribe una cadena con el método **Alt+Numpad**, que funciona con independencia de la distribución de teclado configurada en el equipo anfitrión. **Solo en Windows.**

**Parámetros:** la cadena; *(opcional)* retardo entre pulsaciones en ms.

```js
badusb.altPrint("Hello, world!"); // print "Hello, world!"
badusb.altPrint("Hello, world!", 100); // Add 100ms delay between key presses
```

### altPrintln()
Igual que `altPrint()`, seguido de una pulsación de <kbd>ENTER</kbd>.

```js
badusb.altPrintln("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### quit() {#quit}
Libera el USB. Es opcional, pero permite que el script cambie a otro modo USB, por ejemplo al módulo `usbdisk`.

```js
badusb.quit();
usbdisk.start(...)
```

::: tip Unleashed
`usbdisk` (emulación de almacenamiento masivo USB) es un módulo de JS exclusivo de Unleashed; consulta [Visión general de JavaScript](/es/dev/js-about#unleashed-extras).
:::

## Nombres de teclas {#key-names}

### Teclas modificadoras

| Nombre |
|---|
| CTRL |
| SHIFT |
| ALT |
| GUI |

### Teclas especiales

| Nombre | Notas |
|---|---|
| DOWN | Flecha abajo |
| LEFT | Flecha izquierda |
| RIGHT | Flecha derecha |
| UP | Flecha arriba |
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
| PAUSE | Tecla Pausa/Inter |
| SPACE | |
| TAB | |
| MENU | Tecla de menú contextual |
| Fx | Teclas F1-F24 |
| NUMx | Teclas NUM0-NUM9 |

## Páginas relacionadas

- [Uso de BadUSB](/es/badusb/usage) y [formato de script](/es/badusb/script-format)
- [Bucle de eventos](/es/dev/js-event-loop) y [GUI](/es/dev/js-gui) para menús de payload interactivos
