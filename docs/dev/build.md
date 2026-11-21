---
title: Building the firmware
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToBuild.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Building the firmware

Build Unleashed Firmware from source when you want to change the firmware itself, include your own apps in the
build, or test the latest `dev` code before an official release.

If you only want to write an app (`.fap`), you don't need the whole firmware — use
[uFBT](/dev/first-app-c) instead, and skip to
[building apps against the Unleashed SDK](#build-apps-against-the-unleashed-sdk-with-ufbt).

## What you need

- **Git** — [download](https://git-scm.com/downloads) for Windows; on Linux/macOS install it with your package
  manager (`brew`, `apt`, …).
- **VS Code** (recommended for development, optional for just building).
- A few GB of disk space. Nothing else: `fbt` downloads its own ARM toolchain on first run and does not touch your
  system `PATH` (see [fbt → Environment](/dev/fbt#environment)).

## 1. Clone the repository

Always clone **with submodules**:

```shell
git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
cd unleashed-firmware
```

If you already cloned without `--recursive`, initialise the submodules:

```shell
git submodule update --init --recursive
```

## 2. Build on Linux / macOS

Build everything and produce an update package you can install from the microSD card:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

Build a single app from `applications_user/` and launch it on a Flipper connected over USB:

```sh
./fbt COMPACT=1 DEBUG=0 launch_app APPSRC=applications_user/yourplugin
```

## 3. Build on Windows

Use `fbt.cmd` in PowerShell or `cmd`:

```powershell
./fbt.cmd COMPACT=1 DEBUG=0 updater_package
```

::: warning
On Windows you may need to write `.\fbt.cmd` (backslash) instead of `./fbt.cmd`, depending on your shell.
:::

## 4. Find the output and flash it

All build results go to `dist/`. The file to install is the update bundle:

```
dist/f7-C/flipper-z-f7-update-local.tgz
```

The name pattern is `flipper-z-{target}-update-{suffix}.tgz`. The default suffix is `local` (set by `DIST_SUFFIX` in
`fbt_options.py`, or by the `DIST_SUFFIX` environment variable).

Ways to install it:

- open the `.tgz` in **qFlipper** (*Install from file*) or the Unleashed web installer;
- or let `fbt` do it over USB: `./fbt COMPACT=1 DEBUG=0 flash_usb_full` (builds, uploads and installs);
- or flash over SWD with a debug probe: `./fbt flash` (see [fbt targets](/dev/fbt#high-level-targets)).

::: tip Why `DEBUG=0`?
Unleashed's `fbt_options.py` defaults to `COMPACT=1` and **`DEBUG=1`**. A debug image is larger and may not fit
below the radio stack in flash — packaging then stops with
`Firmware image overlaps C2 region and is not programmable!`. For anything you're going to install, pass
`DEBUG=0` explicitly. Note that `DEBUG=0` also compiles out `furi_assert()`.
:::

## VS Code integration

`fbt` ships a ready VS Code configuration:

```sh
./fbt vscode_dist
```

This copies the configuration into `.vscode/`. Then open the firmware root in VS Code via
**File → Open Folder**, accept the recommended extensions, and use <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>
for build tasks. More in [fbt → VS Code](/dev/fbt#vs-code-integration).

## Build apps against the Unleashed SDK with uFBT

uFBT (micro-fbt) builds single apps against a downloaded SDK instead of the full source tree. **By default it
downloads the official firmware SDK.** To build for Unleashed, point it at the Unleashed update index:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Channels are `dev` and `release`. Use the same flags for **every** later `ufbt update`, otherwise uFBT silently
switches back to the official SDK and the built app reports the wrong API version.

::: tip Unleashed
Unleashed keeps the official API, so most official apps run as-is. An app only refuses to load when its API major
version doesn't match the firmware — rebuilding it against the matching SDK fixes that.
:::

## Building apps on Android

Apps (not the firmware) can also be built directly on an Android phone with uFBT inside Termux — see
[Building apps on Android](/dev/android-build).

## Troubleshooting

| Problem | Fix |
|---|---|
| Build fails with missing files / submodule errors | `git submodule update --init --recursive` |
| `Firmware image overlaps C2 region and is not programmable!` | Add `DEBUG=0` to the command |
| `./fbt` not found on Windows | Use `fbt.cmd` / `.\fbt.cmd` |
| App built with uFBT won't start: API mismatch | Re-run `ufbt update` with the Unleashed `--index-url`, rebuild |
| Want a clean rebuild | Add `-c` to clean the given targets, e.g. `./fbt -c fw_dist` |

## Related pages

- [Flipper Build Tool (fbt)](/dev/fbt) — all targets and options
- [Your first app in C](/dev/first-app-c)
- [OTA updates](/dev/ota) — what's inside an update package
- [Hardware targets](/dev/hardware-targets)
