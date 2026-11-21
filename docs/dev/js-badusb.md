---
title: "JavaScript: BadUSB"
sidebarTitle: "JS: badusb"
order: 290
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_badusb.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_badusb.c]
sources: [unleashed-docs, unleashed-src]
---
# BadUSB module

The `badusb` module turns Flipper Zero into a USB keyboard (HID) controlled from JavaScript. It is a scriptable alternative to classic [BadUSB DuckyScript files](/badusb/script-format): you get variables, loops and the rest of the JS modules (GUI, storage, serial) in the same script.

```js
let badusb = require("badusb");
```

::: warning
Use it only on computers you own or are allowed to test.
:::

Example script: `/ext/apps/Scripts/js_examples/badusb_demo.js`.

## Methods

### setup()
Starts USB HID, optionally with custom parameters. Call it **before all other methods**.

**Parameters:** optional configuration object:

- `vid`, `pid` (number): VID and PID; if used, both are mandatory;
- `mfrName` (string): manufacturer name (32 ASCII characters max), optional;
- `prodName` (string): product name (32 ASCII characters max), optional;
- `layoutPath` (string): path to a keyboard layout file, optional.

```js
// Start USB HID with default parameters
badusb.setup();
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer and product strings not defined
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB }); 
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer string = "Flipper Devices", product string = "Flipper Zero"
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB, mfrName: "Flipper Devices", prodName: "Flipper Zero" });
```

Keyboard layouts are the same `.kl` files the BadUSB app uses (in `/ext/badusb/assets/layouts/`), e.g. `layoutPath: "/ext/badusb/assets/layouts/de-DE.kl"`.

### isConnected()
Returns the USB connection state.

```js
if (badusb.isConnected()) {
    // Do something
} else {
    // Show an error
}
```

### press()
Presses and releases a key or a key combination.

**Parameters:** key or modifier names, or key codes. See the [key name list](#key-names).

```js
badusb.press("a"); // Press "a" key
badusb.press("A"); // SHIFT + "a"
badusb.press("CTRL", "a"); // CTRL + "a"
badusb.press("CTRL", "SHIFT", "ESC"); // CTRL + SHIFT + ESC combo
badusb.press(98); // Press key with HID code (dec) 98 (Numpad 0 / Insert)
badusb.press(0x47); // Press key with HID code (hex) 0x47 (Scroll lock)
```

### hold()
Holds a key down. Up to 5 keys (not counting modifiers) can be held at once.

**Parameters:** same as `press()`.

```js
badusb.hold("a"); // Press and hold "a" key
badusb.hold("CTRL", "v"); // Press and hold CTRL + "v" combo
```

### release()
Releases a previously held key. Called **without parameters**, releases all keys.

**Parameters:** same as `press()`.

```js
badusb.release(); // Release all keys
badusb.release("a"); // Release "a" key
```

### print()
Types a string.

**Parameters:** the string; *(optional)* delay between key presses in ms.

```js
badusb.print("Hello, world!"); // print "Hello, world!"
badusb.print("Hello, world!", 100); // Add 100ms delay between key presses
```

### println()
Same as `print()`, followed by an <kbd>ENTER</kbd> press.

```js
badusb.println("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### altPrint()
Types a string with the **Alt+Numpad** method, which works independently of the keyboard layout set on the host. **Windows only.**

**Parameters:** the string; *(optional)* delay between key presses in ms.

```js
badusb.altPrint("Hello, world!"); // print "Hello, world!"
badusb.altPrint("Hello, world!", 100); // Add 100ms delay between key presses
```

### altPrintln()
Same as `altPrint()`, followed by an <kbd>ENTER</kbd> press.

```js
badusb.altPrintln("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### quit() {#quit}
Releases USB. Optional, but it lets the script switch to another USB mode, for example the `usbdisk` module.

```js
badusb.quit();
usbdisk.start(...)
```

::: tip Unleashed
`usbdisk` (USB mass storage emulation) is an Unleashed-only JS module; see [JavaScript overview](/dev/js-about#unleashed-extras).
:::

## Key names {#key-names}

### Modifier keys

| Name |
|---|
| CTRL |
| SHIFT |
| ALT |
| GUI |

### Special keys

| Name | Notes |
|---|---|
| DOWN | Down arrow |
| LEFT | Left arrow |
| RIGHT | Right arrow |
| UP | Up arrow |
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
| PAUSE | Pause/Break key |
| SPACE | |
| TAB | |
| MENU | Context menu key |
| Fx | F1-F24 keys |
| NUMx | NUM0-NUM9 keys |

## Related

- [BadUSB usage](/badusb/usage) and [script format](/badusb/script-format)
- [Event loop](/dev/js-event-loop), [GUI](/dev/js-gui) for interactive payload menus
