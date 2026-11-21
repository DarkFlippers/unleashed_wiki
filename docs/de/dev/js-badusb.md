---
title: "JavaScript: BadUSB"
sidebarTitle: "JS: badusb"
order: 290
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_badusb.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_badusb.c]
sources: [unleashed-docs, unleashed-src]
---
# Modul BadUSB

Das Modul `badusb` macht aus dem Flipper Zero eine USB-Tastatur (HID), die aus JavaScript gesteuert wird. Es ist
eine skriptfähige Alternative zu den klassischen [BadUSB-DuckyScript-Dateien](/de/badusb/script-format): du bekommst
Variablen, Schleifen und die übrigen JS-Module (GUI, storage, serial) im selben Skript.

```js
let badusb = require("badusb");
```

::: warning
Verwende es nur an Computern, die dir gehören oder die du testen darfst.
:::

Beispielskript: `/ext/apps/Scripts/js_examples/badusb_demo.js`.

## Methoden

### setup()
Startet USB HID, optional mit eigenen Parametern. Rufe es **vor allen anderen Methoden** auf.

**Parameter:** optionales Konfigurationsobjekt:

- `vid`, `pid` (number): VID und PID; werden sie verwendet, sind beide zwingend;
- `mfrName` (string): Herstellername (maximal 32 ASCII-Zeichen), optional;
- `prodName` (string): Produktname (maximal 32 ASCII-Zeichen), optional;
- `layoutPath` (string): Pfad zu einer Tastaturlayout-Datei, optional.

```js
// Start USB HID with default parameters
badusb.setup();
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer and product strings not defined
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB }); 
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer string = "Flipper Devices", product string = "Flipper Zero"
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB, mfrName: "Flipper Devices", prodName: "Flipper Zero" });
```

Tastaturlayouts sind dieselben `.kl`-Dateien, die die BadUSB-App verwendet (in
`/ext/badusb/assets/layouts/`), z. B. `layoutPath: "/ext/badusb/assets/layouts/de-DE.kl"`.

### isConnected()
Gibt den Status der USB-Verbindung zurück.

```js
if (badusb.isConnected()) {
    // Do something
} else {
    // Show an error
}
```

### press()
Drückt eine Taste oder eine Tastenkombination und lässt sie wieder los.

**Parameter:** Tasten- oder Modifikatornamen oder Tastencodes. Siehe die [Liste der Tastennamen](#key-names).

```js
badusb.press("a"); // Press "a" key
badusb.press("A"); // SHIFT + "a"
badusb.press("CTRL", "a"); // CTRL + "a"
badusb.press("CTRL", "SHIFT", "ESC"); // CTRL + SHIFT + ESC combo
badusb.press(98); // Press key with HID code (dec) 98 (Numpad 0 / Insert)
badusb.press(0x47); // Press key with HID code (hex) 0x47 (Scroll lock)
```

### hold()
Hält eine Taste gedrückt. Bis zu 5 Tasten (Modifikatoren nicht mitgezählt) können gleichzeitig gehalten werden.

**Parameter:** wie bei `press()`.

```js
badusb.hold("a"); // Press and hold "a" key
badusb.hold("CTRL", "v"); // Press and hold CTRL + "v" combo
```

### release()
Lässt eine zuvor gehaltene Taste los. **Ohne Parameter** aufgerufen, lässt es alle Tasten los.

**Parameter:** wie bei `press()`.

```js
badusb.release(); // Release all keys
badusb.release("a"); // Release "a" key
```

### print()
Tippt eine Zeichenkette.

**Parameter:** die Zeichenkette; *(optional)* Verzögerung zwischen den Tastenanschlägen in ms.

```js
badusb.print("Hello, world!"); // print "Hello, world!"
badusb.print("Hello, world!", 100); // Add 100ms delay between key presses
```

### println()
Wie `print()`, gefolgt von einem Druck auf <kbd>ENTER</kbd>.

```js
badusb.println("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### altPrint()
Tippt eine Zeichenkette mit der **Alt+Numpad**-Methode, die unabhängig vom auf dem Host eingestellten
Tastaturlayout funktioniert. **Nur Windows.**

**Parameter:** die Zeichenkette; *(optional)* Verzögerung zwischen den Tastenanschlägen in ms.

```js
badusb.altPrint("Hello, world!"); // print "Hello, world!"
badusb.altPrint("Hello, world!", 100); // Add 100ms delay between key presses
```

### altPrintln()
Wie `altPrint()`, gefolgt von einem Druck auf <kbd>ENTER</kbd>.

```js
badusb.altPrintln("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### quit() {#quit}
Gibt USB frei. Optional, erlaubt dem Skript aber, in einen anderen USB-Modus zu wechseln, zum Beispiel zum Modul
`usbdisk`.

```js
badusb.quit();
usbdisk.start(...)
```

::: tip Unleashed
`usbdisk` (Emulation eines USB-Massenspeichers) ist ein JS-Modul, das es nur in Unleashed gibt; siehe
[JavaScript – Übersicht](/de/dev/js-about#unleashed-extras).
:::

## Tastennamen {#key-names}

### Modifikatortasten

| Name |
|---|
| CTRL |
| SHIFT |
| ALT |
| GUI |

### Sondertasten

| Name | Hinweise |
|---|---|
| DOWN | Pfeil nach unten |
| LEFT | Pfeil nach links |
| RIGHT | Pfeil nach rechts |
| UP | Pfeil nach oben |
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
| PAUSE | Taste Pause/Break |
| SPACE | |
| TAB | |
| MENU | Kontextmenü-Taste |
| Fx | Tasten F1–F24 |
| NUMx | Tasten NUM0–NUM9 |

## Verwandte Themen

- [BadUSB verwenden](/de/badusb/usage) und das [Skriptformat](/de/badusb/script-format)
- [Event loop](/de/dev/js-event-loop), [GUI](/de/dev/js-gui) für interaktive Payload-Menüs
