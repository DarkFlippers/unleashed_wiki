---
title: "JavaScript: i2c"
sidebarTitle: "JS: i2c"
order: 440
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_i2c.c]
sources: [unleashed-src]
---
# I2C module

An Unleashed extra, not present in stock firmware. It talks to I2C chips on the external bus: sensors, EEPROMs, displays.

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");
```

Wiring on the [GPIO header](/gpio/pinout): **SDA = pin 15 (PC1)**, **SCL = pin 16 (PC0)**, 3.3 V on pin 9, GND on pin 8. The bus is 3.3 V — do not connect 5 V devices.

Example script: `/ext/apps/Scripts/js_examples/i2c.js`.

Addresses are 8-bit (the 7-bit address shifted left by one). A datasheet that says `0x50` usually means `0xA0` here. Every call takes the bus, does its transfer and releases it, so another app can use I2C between calls.

## Methods

### isDeviceReady()
Pings an address.

- **Parameters:** `address` (number), `timeout` (optional, milliseconds, default 1).
- **Returns:** boolean.

### write()
- **Parameters:** `address` (number), `data` (`number[]` of values 0–255, or an `ArrayBuffer`/`Uint8Array`), `timeout` (optional, ms, default 1).
- **Returns:** boolean — `true` if the device acknowledged.

### read()
- **Parameters:** `address` (number), `length` (number of bytes, must be at least 1), `timeout` (optional, ms, default 1).
- **Returns:** an `ArrayBuffer`, or `undefined` if the transfer failed. Wrap it in `Uint8Array(buf)` to index the bytes.

### writeRead()
Writes, then reads without releasing the bus. This is how you read a register: write its number, read the value.

- **Parameters:** `address`, `writeData` (`number[]` or `ArrayBuffer`), `readLength`, `timeout` (optional, ms, default 1).
- **Returns:** an `ArrayBuffer`, or `undefined` on failure.

## Example

Scan the bus, then read three bytes from a 24C32N EEPROM:

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");

let addr = -1;
for (let a = 0; a !== 0xff; a++) {
    if (i2c.isDeviceReady(a, 5)) {
        addr = a;
        break;
    }
}

if (addr === -1) {
    print("No I2C device found");
} else {
    print("Device at 0x" + addr.toString(16));
    // write 3 bytes starting at EEPROM address 0x0000
    i2c.write(addr, [0x00, 0x00, 0x41, 0x42, 0x43]);
    delay(10);
    // read 3 bytes back from address 0x0000
    let data = Uint8Array(i2c.writeRead(addr, [0x00, 0x00], 3, 100));
    for (let i = 0; i < data.length; i++) {
        print("data[" + i.toString() + "] = " + data[i].toString(16));
    }
}
```

## Related

- [GPIO pinout](/gpio/pinout)
- [GPIO module](/dev/js-gpio)
- [SPI module](/dev/js-spi)
