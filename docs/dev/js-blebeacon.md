---
title: "JavaScript: blebeacon"
sidebarTitle: "JS: blebeacon"
order: 420
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_blebeacon.c]
sources: [unleashed-src]
---
# BLE beacon module

An Unleashed extra, not present in stock firmware. It broadcasts a custom Bluetooth LE advertisement — your own MAC address, your own payload. This is the same "extra beacon" the firmware uses for background advertising, so it runs alongside the normal Bluetooth connection.

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");
```

Example script: `/ext/apps/Scripts/js_examples/blebeacon.js`.

When the script exits, the module restores whatever beacon configuration, data and state were in place before — unless you asked it not to with `keepAlive(true)`.

## Methods

### isActive()
- **Returns:** boolean, whether the beacon is advertising right now. Check this at the start: a beacon left running by an earlier script is still active.

### setConfig()
Sets the advertisement parameters.

- **Parameters:**
  - `mac`: `Uint8Array` of exactly 6 bytes. Anything else throws `Wrong MAC address`;
  - `power` (optional): transmit power on the GapAdvPowerLevel scale, `0x00` (-40 dBm) to `0x1F` (+6 dBm). Default is 0 dBm, values outside the range are clamped;
  - `minInterval` (optional): minimum advertising interval in ms. Default 50, values below 20 are raised to 20, the maximum is 255;
  - `maxInterval` (optional): maximum interval in ms. Default 150, never less than `minInterval`, maximum 255.

### setData()
- **Parameters:** `data`, a `Uint8Array` with the advertisement payload. The hardware limit is 31 bytes.

### start()
Starts advertising.

### stop()
Stops advertising.

### keepAlive()
- **Parameters:** `keep`, boolean. With `true` the beacon keeps advertising after the script exits and nothing is restored. Default is `false`.

## Example

Advertise a short payload for five seconds:

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");

if (blebeacon.isActive()) {
    blebeacon.stop();
}
blebeacon.keepAlive(false);

blebeacon.setConfig(Uint8Array([0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x01]), 0x1F, 50, 150);
blebeacon.setData(Uint8Array([0x02, 0x01, 0x06, 0x03, 0xFF, 0xAB, 0xCD]));

blebeacon.start();
print("Advertising");
delay(5000);
blebeacon.stop();
print("Stopped");
```

## Related

- [JavaScript overview](/dev/js-about)
- [Data types](/dev/js-data-types) — how `Uint8Array` works in mJS
