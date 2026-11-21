---
title: "JavaScript: vgm"
sidebarTitle: "JS: vgm"
order: 460
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [unleashed-src]
---
# Video Game Module

An Unleashed extra, not present in stock firmware. It reads the motion sensor (ICM42688P IMU) inside the [Video Game Module](/gpio/video-game-module) and reports how the Flipper is tilted.

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");
```

There is no example script in the firmware for this one.

Angles are degrees:

- **pitch** — nose up and down;
- **roll** — tilt left and right;
- **yaw** — rotation flat on the table.

Without a module attached, `require("vgm")` still works, but every method returns `undefined`. Check for that instead of assuming hardware.

The IMU driver comes from the [Flipper game engine](https://github.com/flipperdevices/flipperzero-game-engine).

## Methods

### getPitch()
- **Returns:** number, or `undefined` if no module is attached.

### getRoll()
- **Returns:** number, or `undefined` if no module is attached.

### getYaw()
- **Returns:** number, or `undefined` if no module is attached.

### deltaYaw()
Blocks until the yaw has turned by `angle` degrees, polling 10 times a second.

- **Parameters:**
  - `angle`: how many degrees of change to wait for;
  - `timeout` (optional): milliseconds to wait. Default 3000.
- **Returns:** the change in degrees, signed — negative for one direction, positive for the other. `0` if the angle was not reached before the timeout, `undefined` if no module is attached.

## Example

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");

if (vgm.getPitch() === undefined) {
    print("No Video Game Module attached");
} else {
    for (let i = 0; i < 10; i++) {
        print("pitch", vgm.getPitch(), "roll", vgm.getRoll(), "yaw", vgm.getYaw());
        delay(200);
    }

    print("Turn the Flipper 45 degrees...");
    let turned = vgm.deltaYaw(45, 5000);
    if (turned === 0) {
        print("Nothing happened");
    } else {
        print("Turned by", turned);
    }
}
```

## Related

- [Video Game Module](/gpio/video-game-module)
- [JavaScript overview](/dev/js-about)
