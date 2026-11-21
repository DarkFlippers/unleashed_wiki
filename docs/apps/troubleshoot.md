---
title: Troubleshooting apps
order: 140
original: [https://docs.flipper.net/zero/apps/troubleshoot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# Troubleshooting apps

When an app cannot start, the Flipper shows `Error: <name>` with a short hint and a link `r.flipper.net/err_0X`.
Here is what each message means in Unleashed.

::: tip Unleashed
Unleashed does not block apps built for a different API version. Instead of the stock **Outdated App** /
**Outdated Firmware** errors it shows a warning and lets you decide, see [App Too Old / App Too New](#app-too-old-app-too-new).
:::

## App Too Old / App Too New

```
App Too Old
APP:86 < FW:88
This app might not work
Continue anyways?
```

The app's **major API version** differs from the firmware's: **App Too Old** means the app was built for an older API,
**App Too New** for a newer one.

- Press **Continue** (<kbd>→</kbd>) to try anyway. Many apps work, but an app that calls a changed function may crash.
- Press <kbd>Back</kbd> to cancel.
- The real fix: update the app (take it from the current Unleashed pack, or rebuild it for the current SDK), or, for
  **App Too New**, update the firmware.

## Error: App Not Found (err_01)

`Update firmware or app`

| Cause | Fix |
|---|---|
| the app's file was deleted from the SD card | reinstall the app, or reinstall the firmware (for system apps) |
| an old or beta mobile app opened a catalog app that is not on the card | install the official Flipper mobile app from the App Store / Google Play and reinstall the app |

A related message, **SD card needed** / `Install SD card to run this app`, means a menu app lives on the SD card and
no card is inserted. **Update needed** / `Update firmware to run this app` means the card is there but the app file is
missing: reinstall the firmware with the card inserted.

## Error: Invalid File (err_02)

`Update the app`. The `.fap` is damaged: corrupted ELF header, incomplete file (interrupted copy) or sections that
cannot be loaded. Copy or install the app again.

## Error: Invalid Manifest (err_03)

`Update firmware or app`. The manifest (a special ELF section with the API version and app info) cannot be read. The
file is corrupted, or app and firmware are too far apart. Update the app; if it is newer than your firmware, update
the firmware.

## Error: Missing Imports (err_04)

`Update firmware or app`. The app calls functions your firmware does not export.

| Cause | Fix |
|---|---|
| the app was built for a newer firmware | update Unleashed |
| the app was built for another fork (it uses that fork's own functions) | find a build of the app for Unleashed, or rebuild it with the Unleashed SDK |

## Error: HW Target Mismatch (err_05)

`App not supported`. The app was built for a different Flipper hardware target. It cannot run on this device.

## Error: Out of Memory

`Not enough RAM to run the app. Please reboot the device`. A FAP is loaded into RAM; if the heap is fragmented or too
much is running (for example a background BLE beacon or a large app), it does not fit. Press **Reboot** and start the
app again right after boot.

## Still not working

1. Update to the latest Unleashed release, see [Updating](/start/updating).
2. Reinstall the app from the current [app pack](/apps/catalog#base-and-extra-packs) or from the catalog
   ([Apps on the SD card](/apps/sd-card-apps)).
3. If an app crashes the Flipper, reboot with <kbd>←</kbd> + <kbd>Back</kbd>; see [Recovery](/start/recovery) if it no
   longer boots.
4. Ask in the community chats, see [FAQ](/start/faq).

## Related pages

- [Apps on the SD card (.fap)](/apps/sd-card-apps)
- [Apps that ship with Unleashed](/apps/catalog)
