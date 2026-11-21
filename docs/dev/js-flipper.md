---
title: "JavaScript: flipper"
sidebarTitle: "JS: flipper"
order: 300
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_flipper.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_flipper.c]
sources: [unleashed-docs, unleashed-src]
---
# Flipper module

Values and methods for querying device information. Load the module first:

```js
let flipper = require("flipper");
```

## Values

### firmwareVendor
A string naming the firmware on the device. The official firmware reports `"flipperdevices"`.

::: tip Unleashed
Unleashed reports `"unleashed"`.
:::

**Do not** use this to check whether a feature is available. Use the [SDK compatibility functions](/dev/js-builtin#sdk-compatibility) instead.

### jsSdkVersion
Version of the JavaScript SDK. Again, **do not** use it for feature checks; see [SDK compatibility](/dev/js-builtin#sdk-compatibility).

## Methods

### getModel()
Returns the device model.

```js
flipper.getModel(); // "Flipper Zero"
```

### getName()
Returns the name of the virtual dolphin (the device name).

```js
flipper.getName(); // "Fur1pp44"
```

### getBatteryCharge()
Returns the battery charge in percent.

```js
flipper.getBatteryCharge(); // 100
```
