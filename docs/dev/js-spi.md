---
title: "JavaScript: spi"
sidebarTitle: "JS: spi"
order: 450
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_spi.c]
sources: [unleashed-src]
---
# SPI module

An Unleashed extra, not present in stock firmware. It talks to SPI chips on the external bus — flash memory, radio modules, displays.

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");
```

Wiring on the [GPIO header](/gpio/pinout): **MOSI = pin 2 (PA7)**, **MISO = pin 3 (PA6)**, **CS = pin 4 (PA4)**, **SCK = pin 5 (PB3)**, 3.3 V on pin 9, GND on pin 8. Chip select is driven by the firmware, you don't toggle it yourself.

Example script: `/ext/apps/Scripts/js_examples/spi.js`.

## Methods

### acquire()
Takes the bus and holds CS low until `release()`. Use it when several transfers must look like one transaction to the device — command, then answer. Without it, each call takes and frees the bus on its own, which raises CS in between.

### release()
Frees the bus.

### write()
- **Parameters:** `data` (`number[]` of values 0–255, or an `ArrayBuffer`/`Uint8Array`), `timeout` (optional, milliseconds, default 1).
- **Returns:** boolean.

### read()
- **Parameters:** `length` (number of bytes, at least 1), `timeout` (optional, ms, default 1).
- **Returns:** an `ArrayBuffer`, or `undefined` on failure. Wrap it in `Uint8Array(buf)` to index the bytes.

### writeRead()
Full-duplex transfer: sends the buffer and reads back exactly as many bytes as it sent.

- **Parameters:** `data` (`number[]` or `ArrayBuffer`), `timeout` (optional, ms, default 1).
- **Returns:** an `ArrayBuffer` the same length as `data`, or `undefined` on failure.

## Example

Read the JEDEC ID of a W25Q32 flash chip:

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");

spi.acquire();
spi.write([0x9F]);          // command: read JEDEC ID
let data = Uint8Array(spi.read(3));
spi.release();

print("Manufacturer: 0x" + data[0].toString(16));
print("Memory type:  0x" + data[1].toString(16));
print("Capacity:     0x" + data[2].toString(16));

if (data[0] === 0xEF) {
    print("Winbond device");
}
```

## Related

- [GPIO pinout](/gpio/pinout)
- [I2C module](/dev/js-i2c)
- [JavaScript overview](/dev/js-about)
