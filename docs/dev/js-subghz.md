---
title: "JavaScript: subghz"
sidebarTitle: "JS: subghz"
order: 400
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_subghz]
sources: [unleashed-src]
---
# Sub-GHz module

An Unleashed extra, not present in stock firmware. It gives a script the Sub-GHz radio: switch between receive and idle, read the signal level, change frequency, transmit a saved `.sub` file.

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");
subghz.setup();
```

`setup()` looks for an external CC1101 module first and falls back to the built-in radio. Until it has run, every other method throws `Radio is not setup`.

Example script: `/ext/apps/Scripts/js_examples/subghz.js`.

## Methods

### setup()
Initializes the radio and picks the device. Starts at 433920000 Hz in state `IDLE`. Throws if the radio is already set up.

### end()
Puts the radio to sleep and releases the device. Happens automatically when the script ends. Calling `setup()` after it searches for an external module again.

### setRx()
Switches the radio to receive mode.

### setIdle()
Switches the radio to idle. The frequency can only be changed in this state.

### getRssi()
Signal level on the current frequency, in dBm.

- **Returns:** `number`, or `undefined` if the radio is not in RX.

### getState()
- **Returns:** `"RX"`, `"TX"` or `"IDLE"`.

### getFrequency()
- **Returns:** the current frequency in Hz, as a number.

### setFrequency()
Tunes the radio. Throws if the radio is not `IDLE` or if the frequency is outside the bands the device supports.

- **Parameters:** `frequency`, a number in Hz — for example `433920000`.
- **Returns:** the frequency the radio actually tuned to. A CC1101 cannot hit every value exactly, so it takes the closest one it can.

### isExternal()
- **Returns:** boolean — `true` when an external CC1101 is in use, `false` for the built-in radio.

### transmitFile()
Sends a `.sub` file. Frequency and modulation come from the file, not from `setFrequency()`. Returns `true`; on any problem (file missing, bad header, unsupported frequency, unknown preset) it throws. The radio is left in `IDLE`.

- **Parameters:**
  - `path`: full path to the file, e.g. `"/ext/subghz/0.sub"`;
  - `repeat` (optional): how many times to send it.

Without `repeat`, RAW files go out once and protocol files 10 times, which imitates holding the button on a real remote. `CAME Atomo`, `CAME TWEE`, `Hormann HSM`, `Nice FloR-S` and `Power Smart` send several frames per repeat already, so those default to 1.

## Example

Listen on 433.92 MHz, then send a saved key:

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");

subghz.setup();
subghz.setIdle();
subghz.setFrequency(433920000);

subghz.setRx();
print("RSSI:", subghz.getRssi(), "dBm, external:", subghz.isExternal());
delay(1000);

print("Sending 0.sub");
subghz.transmitFile("/ext/subghz/0.sub");
print("Sent");

subghz.end();
```

## Related

- [Sub-GHz file format](/subghz/file-format) — what is inside a `.sub`
- [External CC1101 modules](/subghz/external-cc1101)
- [JavaScript overview](/dev/js-about)
