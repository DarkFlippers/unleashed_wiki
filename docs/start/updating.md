---
title: Updating
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Updating

Unleashed is updated often. Updating works exactly like installing: put the new version **on top of** the current one.
You do not need to go back to official firmware or install anything in between.

## How to update

**Recommended: [qUnleashed](/mobile/qunleashed-app)**, the Unleashed companion app for **Android, iOS, Windows,
macOS and Linux** (USB on all of them except iOS, which uses Bluetooth). It downloads the new firmware itself.

1. Install or update qUnleashed from its [releases page](https://github.com/DarkFlippers/qUnleashed/releases).
2. Connect the Flipper over USB or Bluetooth.
3. Open the **firmware updater**, pick the **Unleashed** channel (**Release** or **Dev**) and the build you use:
   **base**, **extra apps** or **compact**.
4. Start the installation and wait until the Flipper has finished all stages.

If the Flipper stopped booting, **Repair from DFU mode** in the same app re-flashes it over USB
([Recovery](/start/recovery#firmware-recovery)).

Alternatives, all described in [install methods](/start/install):

1. **[Web Installer](https://web.unleashedflip.com)**: Connect → choose Release or Dev → Install.
2. **qFlipper**: **Install from file** with the new `flipper-z-f7-update-(version).tgz`.
3. **Mobile app**: custom update channel with the `.tgz`.
4. **Offline**: copy `f7-update-(version)` into `/ext/update/` and open `update.fuf` in the Archive.

::: warning Don't press "Update" in qFlipper / the official app
The built-in **Update** button in qFlipper and the Flipper Mobile App uses the **official** update server. It replaces
Unleashed with stock firmware. For Unleashed, use the qUnleashed updater, **Install from file**, the custom channel
or the Web Installer.
:::

## Release or dev?

| | Release | Dev |
|---|---|---|
| Stability | Tested | May have bugs |
| New features | With each release | As soon as they are merged |
| Get it | Web Installer → Release, [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), [@unleashed_fw](https://t.me/unleashed_fw) | Web Installer → Dev, [dev.unleashedflip.com](https://dev.unleashedflip.com), [@kotnehleb](https://t.me/kotnehleb) |

Dev builds are built automatically from the latest commits. The previous dev build is deleted from the site when a new
one is uploaded. Report bugs on [GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

## What survives an update

- **Your files on the microSD card**: saved keys, cards, remotes and scripts remain untouched.
- **Your custom name**: stored on the card in `/ext/dolphin/name.settings` ([Custom Flipper name](/start/custom-name)).
- **Settings**: usually kept. **Exception:** when a release changes the layout of a settings file, that file is reset to
  defaults once. This happens only in specific releases. If your desktop settings (PIN, favourites…) reset after an
  update, set them again and check the changelog.
- **Built-in apps** in `/ext/apps/` are replaced only by the versions from the new firmware. Extra app packs can never
  overwrite or downgrade them.

## Checking your version

- **Main Menu → Settings → About**: firmware version, build date, branch and commit;
- or hold <kbd>↓</kbd> on the desktop for the debug/info screen.

## Where to read what changed

- [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases): changelog of every release;
- [CHANGELOG.md](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md) on the dev branch: what is
  coming in the next release;
- app updates: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/commits/dev).

## The Unleashed update server

Unleashed runs its own update server with the same format as the official one:
`https://up.unleashedflip.com/directory.json`. Official apps cannot be pointed at it without rebuilding them. **uFBT**
accepts this URL as an argument to build apps against the Unleashed SDK (see [Build the firmware](/dev/build)).

## If an update fails

1. Reboot with <kbd>←</kbd> + <kbd>BACK</kbd> and try again.
2. Try a different method (qUnleashed ↔ Web Installer ↔ qFlipper ↔ offline).
3. Check the SD card (**Settings → Storage → About SD Card**), or format it after a backup.
4. Still failing: [Recovery](/start/recovery).
