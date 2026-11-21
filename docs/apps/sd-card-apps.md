---
title: Apps on the SD card (.fap)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Apps on the SD card (.fap)

Almost every app you launch from `Main Menu → Apps` is a **FAP** (Flipper App Package): an `.elf` executable with
extra metadata (name, icon, category, required API version) and optional bundled resources. FAPs live on the microSD
card, so **apps need an SD card** to run.

## Where apps live

| Path | What is there |
|---|---|
| `/ext/apps/<Category>/*.fap` | installed apps, one folder per category (`Sub-GHz`, `NFC`, `RFID`, `GPIO`, `USB`, `Bluetooth`, `Games`, `Tools`, ...) |
| `/ext/apps_data/<appid>/` | data and settings each app saves for itself |
| `/ext/apps_data/loader/plugins/` | loader plugins, for example the [main menu styles](/apps/menu-styles) |

`Main Menu → Apps` shows the folders under `/ext/apps`. The **Apps** tab of the [Archive](/apps/archive) lists
the same folder and also shows `.js` scripts.

## How the Flipper runs a FAP

The MCU cannot execute code straight from external storage. When you start an app, the **App Loader**:

1. reads the FAP from the SD card and checks its integrity and its manifest;
2. checks that the app's **major API version** matches the firmware's major API version;
3. copies the code and data sections to RAM and fixes up addresses for the new location (relocation);
4. resolves every function the app imports through the firmware's **symbol table**;
5. starts the app.

Because the app runs from RAM, a big app leaves less heap for everything else. Only code and data are loaded, so
the RAM used is smaller than the `.fap` file size.

::: tip Unleashed
Unleashed keeps the official API (the current API version is printed at the top of every changelog, for example
`Current API: 88.27`), so most apps from the official catalog run as is. If the API major version differs, Unleashed
does not refuse outright: it shows **App Too Old** or **App Too New** with the two versions (for example
`APP:86 < FW:88`) and a **Continue** button, so you can try to run it anyway. See
[Troubleshooting apps](/apps/troubleshoot).
:::

## Installing apps

### From the app packs

The easiest way is to pick a firmware build that already includes a pack (default or `e` build), see
[Apps that ship with Unleashed](/apps/catalog).

Both packs come from [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). To add one by hand:

1. Download the `.zip` from the [releases page](https://github.com/xMasterX/all-the-plugins/releases/latest).
2. Unpack it.
3. Copy the app folders into the `apps` folder on the SD card (`/ext/apps/`), keeping their category folders.
4. Check that the pack's API version matches your firmware (`Current API:` at the top of the changelog).

### From the official catalog {#installing-from-the-official-catalog}

The official Apps Catalog is in [Flipper Lab](https://lab.flipper.net/apps) (Chrome, Edge and other Chromium
browsers with Web Serial) and in the **Apps** tab of the [Flipper mobile app](/mobile/mobile-app).

1. Close qFlipper and any other Flipper Lab tab (only one program can hold the USB serial port).
2. Connect the Flipper over USB (Flipper Lab) or Bluetooth (mobile app).
3. Open **Apps**, find the app by category or search.
4. Press **Install** on the app card or on its page and wait until it is uploaded.
5. On the Flipper open `Main Menu → Apps → <category> → <app>`.

To update or delete catalog apps, open **Apps → Installed** and press **Update** or the delete (bin) icon.

If installation fails: check the connection, free some space on the SD card (delete files in the
[Archive](/apps/archive)), and make sure the firmware is current.

### By hand (any `.fap`)

1. Download the `.fap` built for your firmware (an Unleashed build, or an OFW build of a matching API version).
2. Copy it to `/ext/apps/<Category>/` with [qFlipper](/mobile/qflipper), the mobile app file manager, or a card reader.
3. Start it from `Main Menu → Apps`, or open the file in the [Archive](/apps/archive) and choose **Run**.

::: warning
Apps built for another firmware fork may import functions Unleashed does not export, and then fail with
**Missing Imports**. Take apps from the Unleashed packs or rebuild them against the Unleashed SDK.
:::

## Building your own FAP

FAPs are developed exactly like built-in apps. In short:

1. Put your app folder into `applications_user/` of a firmware checkout.
2. In its `application.fam` set `apptype=FlipperAppType.EXTERNAL` (see [App manifests](/dev/app-manifests)).
3. Build with one of:

```bash
./fbt fap_{APPID}                                     # build one app
./fbt launch APPSRC=applications_user/path/to/app     # build, upload over USB and run
./fbt build APPSRC=applications_user/path/to/app      # build without uploading
./fbt faps                                            # build all FAPs (or ./fbt fap_dist)
```

In the default VS Code profile `launch` is the **Launch App on Flipper** action (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>).

**Assets.** Put images in a subfolder of the app and name it in `fap_icon_assets`; then `#include "{APPID}_icons.h"`
and use them like icons from `assets_icons.h`.

**API versioning.** Not every firmware function is available to apps: the exported set is listed in
`api_symbols.csv` of the hardware target. The major version grows on breaking changes (a function or variable
removed, a signature changed), the minor version on additions. `fbt` manages this automatically: new symbols appear
with `?`, and you must mark each one `+` (exported) or `-` (hidden) before the firmware builds.

**Debugging.** `fbt` loads `debug/flipperapps.py` into gdb, so you can debug a FAP like firmware code. Build and flash
the firmware (`./fbt`, `./fbt flash`), run your FAP, then attach with `./fbt debug`. The firmware hits a breakpoint
right after the FAP is loaded, so you can set breakpoints in it. Firmware and app build type (debug/release) must
match, and the matching build must be linked as `build/latest`.

More in [Building the firmware](/dev/build), [fbt](/dev/fbt) and [Your first app in C](/dev/first-app-c).

## Related pages

- [Apps that ship with Unleashed](/apps/catalog)
- [Troubleshooting apps](/apps/troubleshoot)
- [Archive (file browser)](/apps/archive)
