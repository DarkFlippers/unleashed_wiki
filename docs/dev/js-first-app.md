---
title: "JavaScript: your first app"
sidebarTitle: "JS: first app"
order: 210
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_your_first_js_app.md]
sources: [unleashed-docs]
---
# Your first JavaScript app

In this guide you will write a tiny script that prints numbers with a delay, and then run it on Flipper Zero in two ways: from the device menu and from a PC over the CLI. You need a Flipper Zero, a PC and a USB cable.

## Step 1. Create the script

Create a text file named `first_app.js` with this content:

```js
print("start");
delay(1000);
print("1");
delay(500);
print("2");
delay(500);
print("3");
delay(500);
print("end");
```

What it does:

- prints **start** and waits 1 second;
- prints **1**, **2** and **3**, pausing 0.5 seconds after each;
- prints **end**.

`print()` outputs text, and `delay()` pauses for the given number of milliseconds (1000 ms = 1 s). Both are **built-in functions**, so no module has to be loaded first. See [Built-in functions](/dev/js-builtin) for the full list.

## Step 2. Copy the file to Flipper Zero

1. Connect Flipper Zero to your PC via USB.
2. Open [qFlipper](/mobile/qflipper).
3. Go to the **File manager** tab and open `SD Card/apps/Scripts/`.
4. Drag and drop `first_app.js` into the qFlipper window.

You can also copy the file with a card reader. It must end up in `/ext/apps/Scripts/`.

## Step 3. Run the script

### From the Flipper menu

1. Open `Main Menu → Apps → Scripts`. The list shows the scripts in `SD Card/apps/Scripts/`.
2. Select `first_app`.
3. Press <kbd>OK</kbd> to run it.

![Script running on Flipper Zero](/img/dev/js_first_app_on_fz.jpg)

The lines appear on the Flipper screen with the delays defined in the script.

### From the CLI

Running from the [CLI](/dev/cli) is handy for debugging: you edit and test the script without touching the device.

1. Connect Flipper Zero via USB.
2. Open the CLI (for example with qFlipper's CLI tab, a serial terminal, or `./fbt cli`).
3. Run `js` followed by the path to the script:

```sh
js /ext/apps/Scripts/first_app.js
```

![Script output in the CLI](/img/dev/js_first_app_on_cli.jpg)

When a script is started from the CLI, everything printed with `print()` goes to the CLI, not to the Flipper screen.

## Troubleshooting

- **The script is not in the list.** Check that the file has the `.js` extension and is in `/ext/apps/Scripts/` (subfolders are fine; browse into them).
- **The script stops with an error.** mJS supports only a subset of JavaScript (no closures, no arrow functions, no classes). Run it from the CLI to see the error message and line.

**Next:** [Developing apps with the JavaScript SDK](/dev/js-sdk)
