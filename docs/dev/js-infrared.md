---
title: "JavaScript: infrared"
sidebarTitle: "JS: infrared"
order: 410
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_infrared]
sources: [unleashed-src]
---
# Infrared module

An Unleashed extra, not present in stock firmware. It sends IR signals from a script, either by protocol name or as a raw list of timings. There is no receive side — use the Infrared app to capture a signal first.

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");
```

The feature name is `infrared-send`, the module name is `infrared`.

Example script: `/ext/apps/Scripts/js_examples/infrared-send.js`.

## Methods

### sendSignal()
Sends a signal using a protocol the firmware knows.

- **Parameters:**
  - `protocol`: `"NEC"`, `"NECext"`, `"NEC42"`, `"NEC42ext"`, `"Samsung32"`, `"RC6"`, `"RC5"`, `"RC5X"`, `"SIRC"`, `"SIRC15"`, `"SIRC20"`, `"Kaseikyo"` or `"RCA"`;
  - `address`: number;
  - `command`: number;
  - `options` (optional): `{ repeat?: boolean, times?: number }`. `repeat` marks the signal as a repeat frame, `times` is how many times to send it (default 1).

```js
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
```

In `.ir` files the address and command are stored as little-endian hex, while a JS number literal is big-endian. `A9 00 00 00` in a file is `0x000000A9` here, so reverse the bytes before pasting them in.

### sendRawSignal()
Sends a signal by its on/off timings, for remotes no protocol covers.

- **Parameters:**
  - `timings`: array of numbers, durations in microseconds;
  - `startFromMark` (optional): boolean, whether the first value is a pulse rather than a pause. Default `true`;
  - `advancedSettings` (optional): `{ frequency: number, dutyCycle: number }`. Both fields are required once the object is given. Without it the carrier is 38000 Hz at a duty cycle of 0.33.

## Example

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");

// Samsung TV, volume down
print("Sending Samsung32");
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
delay(1000);

// Three presses in a row
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b, { times: 3 });
delay(1000);

// Raw timings at 36 kHz
infrared.sendRawSignal([3298, 1571, 442, 368, 442, 367], true, {
  frequency: 36000,
  dutyCycle: 0.33,
});
print("Done");
```

## Related

- [Infrared file format](/infrared/file-format) — where to read address and command from
- [Supported IR protocols](/infrared/protocols)
- [JavaScript overview](/dev/js-about)
