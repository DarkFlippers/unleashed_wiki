---
title: "JavaScript: usbdisk"
sidebarTitle: "JS: usbdisk"
order: 430
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_usbdisk]
sources: [unleashed-src]
---
# USB mass storage module

An Unleashed extra, not present in stock firmware. It makes Flipper appear to a PC as a USB flash drive. The contents come from one image file on the SD card; the PC reads and writes blocks straight into that file.

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
```

Example script: `/ext/apps/Scripts/js_examples/usbdisk.js`.

`createImage()` makes an empty image, or you can copy an `.img` to `/ext/apps_data/mass_storage/` yourself. The file is read in 512-byte blocks, so its size has to be a multiple of 512.

If the script used BadUSB before this, call [`badusb.quit()`](/dev/js-badusb#quit) first to free the USB port.

## Methods

### createImage()
Makes an empty image of the size you ask for. The space is only claimed, not written, so even a big image is quick. The first 4 KB are cleared so the PC offers to format the new disk. Throws if something is already at that path, or if the card is too full.

- **Parameters:** `path`, where to put it; `size`, bytes, rounded down to a whole 512-byte block.

### start()
Opens the image for reading and writing and connects the drive to the PC. The drive's name is the image file name without its extension. Throws if the file is missing or if a disk is already running.

- **Parameters:** `path`, the full path to the image, e.g. `"/ext/apps_data/mass_storage/128MB.img"`.

### stop()
Disconnects the drive and closes the file. Also happens when the script ends.

### wasEjected()
- **Returns:** boolean, `true` once the PC has ejected the drive. Use it as a loop condition. Throws if the disk is not running.

## Example

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
let storage = require("storage");

let imagePath = "/ext/apps_data/mass_storage/128MB.img";
if (!storage.fileExists(imagePath)) {
    usbdisk.createImage(imagePath, 128 * 1024 * 1024);
}

print("Starting UsbDisk...");
usbdisk.start(imagePath);

print("Started, waiting until ejected...");
while (!usbdisk.wasEjected()) {
    delay(1000);
}

print("Ejected, stopping UsbDisk...");
usbdisk.stop();
```

::: tip
`createImage()` is newer than the rest of the module. A script that may also run on an older build should check `doesSdkSupport(["usbdisk-createimage"])` first, like the bundled example does.
:::

## Related

- [BadUSB module](/dev/js-badusb) — `quit()` releases USB for this module
- [Storage module](/dev/js-storage) — check whether the image exists before starting
- [JavaScript overview](/dev/js-about)
