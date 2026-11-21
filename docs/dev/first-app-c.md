---
title: Your first app in C
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_your_first_app_in_c.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md]
sources: [unleashed-docs]
---
# Your first app in C

In this tutorial you set up a development environment with **uFBT**, generate an app template, add a simple GUI,
and build and run the app on your Flipper Zero.

Apps built this way are `.fap` files (Flipper App Package) — they live on the microSD card and are loaded on demand,
so you don't need to rebuild the firmware.

## 1. Set up the environment

You need a Flipper Zero, a USB cable, and on Windows / macOS / Linux:

- [**uFBT**](https://github.com/flipperdevices/flipperzero-ufbt) ("micro Flipper Build Tool") — a version of
  [fbt](/dev/fbt) with everything needed for app development. Install it with `pip install ufbt` (see the uFBT
  README for details).
- [**Visual Studio Code**](https://code.visualstudio.com/) — the recommended IDE. Others work too, but need manual
  configuration to integrate with uFBT.

::: tip Unleashed
uFBT downloads the **official** SDK by default. To build for Unleashed, run once (and use the same flags for every
later update):

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Use `--channel=release` if your Flipper runs a release build. The SDK version must match the firmware on the
device — see [step 5](#_5-build-and-run-the-app).
:::

## 2. Generate an app template

1. Create a folder for the app, e.g. `test_app`.
2. Open a terminal in that folder and run:

   ```sh
   ufbt create APPID=test_app
   ```

   uFBT generates the file structure.
3. Run:

   ```sh
   ufbt vscode_dist
   ```

   This configures VS Code to build and debug the app directly from the IDE.

::: warning
`APPID` may contain only lowercase letters `a-z`, digits `0-9` and `_`.
:::

The resulting structure:

```
test_app/
├── application.fam
├── test_app.c
├── test_app.png
├── .github/
│   └── workflows/
|       └── build.yml
└── images/
    └── .gitkeep
```

| File | Purpose |
|---|---|
| `application.fam` | The app manifest uFBT reads to know how to build the app — see [App manifests](/dev/app-manifests) |
| `test_app.c` | Main source file with the entry point |
| `test_app.png` | App icon (10×10, 1-bit) |
| `.github/workflows/build.yml` | GitHub Actions config — [more](https://github.com/marketplace/actions/build-flipper-application-package-fap) |
| `images/` | Your image assets |
| `images/.gitkeep` | Placeholder so Git tracks the empty `images/` folder |

## 3. The template code

```c
#include <furi.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm test_app!");

    return 0;
}
```

What each part does:

- `#include <furi.h>` — the main header of **Furi**, the core of the Flipper firmware ([Furi API](/dev/furi-api)).
- `#include <test_app_icons.h>` — needed if the app uses images. uFBT converts PNGs from `images/` into Flipper's
  internal format and generates this header automatically.
- `int32_t` — the usual return type of an app's main function.
- `UNUSED(p);` — a macro that silences the "unused parameter" warning.
- `FURI_LOG_I` — writes an `info`-level message to the Flipper log. Watch it via `ufbt cli` → `log info`.
- `return 0;` — success, by C convention.

## 4. Add a GUI

Open the app folder in VS Code (**File → Open Folder…**). Install the suggested extensions when asked.

Let's show two lines on the screen: `Hello world` and `I'm test_app!`. Replace the contents of `test_app.c` with:

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);
    DialogMessage* message = dialog_message_alloc();
    dialog_message_set_header(message, "Hello world", 64, 20, AlignCenter, AlignTop);
    dialog_message_set_text(message, "I'm test_app!", 64, 32, AlignCenter, AlignTop);
    dialog_message_show(dialogs, message);
    dialog_message_free(message);
    furi_record_close(RECORD_DIALOGS);

    return 0;
}
```

This uses the **Dialogs** GUI service, the simplest GUI API. Other approaches are described in
[GUI in apps](/dev/gui).

## 5. Build and run the app

**The quick way:**

1. Connect the Flipper to your computer with the USB cable.
2. Close qFlipper and any other program using the Flipper's serial port.
3. Run:

   ```sh
   ufbt launch
   ```

   It builds the app, uploads it and starts it on the Flipper.

**The manual way:**

1. Build with <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (Windows/Linux) or <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>
   (macOS), or run `ufbt` in the terminal. The self-contained `.fap` (with all resources) appears in `dist/`.
2. In qFlipper open **File Manager → SD Card → apps → Examples** (create the folder if needed) and drag the `.fap`
   there.
3. On the Flipper: `Main Menu → Apps → Examples → your app`.

**Expected result:** a screen with "Hello world" as a header and "I'm test_app!" below it. Press any button to close
it.

::: warning SDK version must match
The firmware SDK (API) version on the device must match the SDK uFBT built against. If you get an API mismatch error
when starting the app, either update uFBT's SDK to match your firmware, or flash the matching firmware with
`ufbt flash_usb`. On Unleashed, make sure uFBT uses the Unleashed index (see the tip in step 1) — otherwise
`ufbt flash_usb` would install the **official** firmware.
:::

To see the `FURI_LOG_I` output: run `ufbt cli`, then `log` (or `log info` if you changed the default log level).

## Troubleshooting

| Problem | Fix |
|---|---|
| `ufbt create` rejects the APPID | Use only `a-z`, `0-9`, `_` |
| API / SDK mismatch when launching | Update uFBT's SDK for your firmware (Unleashed index!) and rebuild |
| `ufbt launch` can't find the device | Close qFlipper / Lab / any serial terminal; reconnect the cable |
| App not in the menu | It must be in a category folder under `/ext/apps/`, e.g. `/ext/apps/Examples/` |
| Nothing in `log` | Start `log` **before** launching the app; check the log level |

## What's next?

- If your C is rusty, *The C Programming Language* by B. Kernighan and D. Ritchie is the classic reference.
- [Debugging apps](/dev/debugging) — step through your app with a debugger.
- [GUI in apps](/dev/gui) — ViewPort, Views and Scenes.
- [App manifests](/dev/app-manifests) — all `application.fam` options.
- No PC? [Build apps on Android](/dev/android-build).
- Prefer scripting? [JavaScript on Flipper](/dev/js-about).
