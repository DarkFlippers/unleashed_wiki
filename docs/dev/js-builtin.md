---
title: "JavaScript: built-in functions"
sidebarTitle: "JS: built-in functions"
order: 250
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_builtin.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/js_modules.c]
sources: [unleashed-docs, unleashed-src]
---
# Built-in functions

These functions and objects are available in every script without `require()`.

## Global functions

### require()
Loads a module plugin. See [Using JS modules](/dev/js-modules).

- **Parameters:** module name

```js
let serial = require("serial"); // Load "serial" module
```

### delay()
- **Parameters:** delay in ms

```js
delay(500); // Delay for 500ms
```

### print()
Prints a message to the on-screen console (or to the CLI, if the script was started from the CLI).

- **Parameters:** any number of arguments of type String, Number, Bool or `undefined`

```js
print("string1", "string2", 123);
```

### console object
Same as `print()`, but writes **to the serial console (log) only**, with the corresponding log level:

- `console.log()`
- `console.warn()`
- `console.error()`
- `console.debug()`

### load()
Runs a JS file and returns a value from it.

- **Parameters:**
  - path to the file;
  - optional object to use as the global scope while running the file.

```js
load("/ext/apps/Scripts/script.js");
```

### chr()
Converts an ASCII character code to a string.

```js
chr(65); // "A"
```

### die()
Exits the script with the given message.

```js
die("Some error occurred");
```

### parseInt()
Converts a string to a number, with an optional base.

```js
parseInt("123"); // 123
parseInt("7b", 16); // 123
```

## Number

### Number.toString()
Converts a number to a string, with an optional base.

```js
let num = 123;
num.toString(); // "123"
num.toString(16); // "0x7b"
```

## ArrayBuffer

**Fields:** `byteLength`, the length of the buffer in bytes.

### ArrayBuffer.slice()
Creates an `ArrayBuffer` containing a part of the buffer.

- **Parameters:** start index; optional non-inclusive end index.

```js
Uint8Array([1, 2, 3]).buffer.slice(0, 1) // ArrayBuffer([1])
```

## DataView (typed arrays)

Wrappers around `ArrayBuffer` with a fixed element type:

- `Uint8Array`, `Int8Array`
- `Uint16Array`, `Int16Array`
- `Uint32Array`, `Int32Array`

**Fields:**

- `byteLength`: length of the buffer in bytes;
- `length`: length of the buffer in typed elements;
- `buffer`: the underlying `ArrayBuffer`.

## Array

**Fields:** `length`, the number of elements.

### Array.splice()
Removes elements from the array and returns them as a new array.

- **Parameters:** start index; optional count of elements to take.

```js
let arr = [1, 2, 3];
arr.splice(1); // [2, 3]
arr; // [1]
```

### Array.push()
Adds a value to the end of the array.

```js
let arr = [1, 2];
arr.push(3);
arr; // [1, 2, 3]
```

## String

**Fields:** `length`, the number of characters (bytes).

### String.charCodeAt()
Returns the character code at an index.

```js
"A".charCodeAt(0) // 65
```

### String.at()
Same as `String.charCodeAt()`.

### String.indexOf()
Returns the index of the first occurrence of a substring, or `-1` if not found.

- **Parameters:** substring to search for; optional start index.

```js
"Example".indexOf("amp") // 2
```

### String.slice()
Returns the substring between two indices.

- **Parameters:** start index; optional non-inclusive end index.

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

## Script paths

### __dirname
Path to the directory containing the current script.

```js
print(__dirname); // /ext/apps/Scripts
```

### __filename
Path to the current script file.

```js
print(__filename); // /ext/apps/Scripts/path.js
```

## SDK compatibility {#sdk-compatibility}

Scripts can check which JS SDK version and which extra features the firmware provides. **Do not** use `flipper.firmwareVendor` or `flipper.jsSdkVersion` for this. Use the functions below.

On current Unleashed the JS SDK version is **1.0**.

### sdkCompatibilityStatus()
Checks compatibility between the script and the JS SDK of the firmware.

- **Returns:**
  - `"compatible"` if the script and the JS SDK are compatible;
  - `"firmwareTooOld"` if the expected major version is larger than the firmware's, or the expected minor version is larger than the firmware's;
  - `"firmwareTooNew"` if the expected major version is lower than the firmware's.

```js
sdkCompatibilityStatus(0, 3); // "compatible"
```

### isSdkCompatible()
Same check, returning a boolean.

```js
isSdkCompatible(0, 3); // true
```

### checkSdkCompatibility()
If the versions are not compatible, asks the user whether to continue running the script. Does nothing if they are compatible.

```js
checkSdkCompatibility(0, 3);
```

### doesSdkSupport()
Checks whether **all** of the listed extra features are supported by the interpreter.

```js
doesSdkSupport(["gui-widget"]); // true
```

### checkSdkFeatures()
Same check, but asks the user whether to continue if some features are missing.

```js
checkSdkFeatures(["gui-widget"]);
```

::: tip Unleashed
Feature names supported by Unleashed: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, and the Unleashed extra modules `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`. See [JavaScript overview](/dev/js-about#unleashed-extras).
:::

Typical pattern for an optional feature:

```js
if (doesSdkSupport(["subghz"])) {
    let subghz = require("subghz");
    // ...
}
```
