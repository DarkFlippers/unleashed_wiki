---
title: Flipper Build Tool (fbt)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Flipper Build Tool (fbt)

`fbt` is the single entry point for building, flashing, debugging and linting the firmware. You run it as `./fbt`
(or `fbt.cmd` on Windows) from the repository root. Internally it is a wrapper around the
[SCons](https://scons.org/) build system.

If you only want to build and debug **one app**, you don't need the full firmware tree — use
[uFBT](https://pypi.org/project/ufbt/) instead (see [Your first app in C](/dev/first-app-c)).

## Environment

The only thing you must have installed is `git`. On the first run `fbt` downloads and unpacks a pre-built
toolchain and adjusts environment variables **for itself only** — your global `PATH` is not modified.

To use the bundled toolchain outside `fbt` (for example to call `arm-none-eabi-gdb` manually), open an
*fbt shell*:

- Windows: run `scripts/toolchain/fbtenv.cmd`
- Linux / macOS: run `source scripts/toolchain/fbtenv.sh` in a new shell
- or type `` . `./fbt -s env` `` in your shell (keep the leading `.`)

Environment variables that change `fbt` behaviour:

| Variable | Effect |
|---|---|
| `FBT_NOENV=1` | Skip toolchain download/setup; all tools must already be on `PATH` (not available on Windows) |
| `FBT_TOOLCHAIN_PATH=…` | Directory to unpack the toolchain into (default: `toolchain/` in the repo root) |
| `FBT_VERBOSE=1` | Extra debug output from `fbt` and the toolchain scripts |
| `FBT_NO_SYNC=1` | Don't run `git submodule update --init` on every start |

Setting a variable for one run:

```sh
# Linux / macOS
FBT_NO_SYNC=1 ./fbt ...
```

```bat
:: Windows (cmd)
set "FBT_NO_SYNC=1"
```

More variables are documented in the `fbt` and `fbtenv` script sources.

## Invoking fbt

Pass configuration options and the targets you want:

```sh
./fbt COMPACT=1 DEBUG=0 VERBOSE=1 updater_package copro_dist
```

To clean (like `make clean`) the given targets, add `-c`.

`fbt` tracks dependencies, so you only name the highest-level target you need — everything it depends on is
rebuilt automatically.

## Build directories

Firmware and updater are built in separate subdirectories of `build/`, named after the optimisation settings
(`COMPACT`, `DEBUG`). For IDEs, the most recently built variant is always linked as `build/latest`, together with a
`compile_commands.json` used for code completion.

::: info
`build/latest` and the compilation database are updated only by **firmware build targets**. Flashing, or building
update bundles for a *different* debug/release configuration or hardware target, does not move `build/latest`.
:::

## VS Code integration

```sh
./fbt vscode_dist
```

copies a ready environment configuration into `.vscode/`. Open the firmware root with **File → Open Folder**.

- To use a language server other than the default `cpptools`, run `./fbt vscode_dist LANG_SERVER=<language-server>`.
  Supported: `cpptools` (default) and `clangd`.
- On first start you'll be offered recommended extensions (listed in `.vscode/extensions.json`) — install them.
- Build tasks live under <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
- Debugging needs a supported probe: Wi-Fi Devboard with stock (Blackmagic) firmware, ST-Link and compatibles, or
  J-Link (VS Code only; J-Link tools are not bundled — [download](https://www.segger.com/downloads/jlink/) them and
  put them on `PATH`).
- Without a probe you can still install firmware over USB.

## High-level targets

These are the targets you'll use most often.

| Target | What it does |
|---|---|
| `fw_dist` | Build the firmware and publish it to `dist/`. **Default target** when none is given |
| `fap_dist` | Build external apps (FAPs) and publish them to `dist/` |
| `updater_package` | Full self-update package: firmware DFU + radio stack + SD card resources |
| `updater_minpackage` | Minimal update package: only the firmware DFU |
| `copro_dist` | Bundle Core2 FUS + radio stack binaries for qFlipper |
| `flash` | Flash over SWD with a supported probe (auto-detected; override with `SWD_TRANSPORT=...`, pick one of several probes with `SWD_TRANSPORT_SERIAL=...`) |
| `flash_usb`, `flash_usb_full` | Build, upload and install the update package over USB (minimal / full package) |
| `debug` | Build and flash firmware, then attach GDB with the firmware `.elf` loaded |
| `debug_other`, `debug_other_blackmagic` | Attach GDB without loading any `.elf`; add external `.elf` files with `add-symbol-file` |
| `updater_debug` | Attach GDB with the updater `.elf` loaded |
| `devboard_flash` | Update the Wi-Fi Devboard; extra args via `ARGS="..."`, e.g. `ARGS="-c dev"` |
| `blackmagic` | Debug firmware with a Blackmagic probe (Wi-Fi Devboard) |
| `openocd` | Just start OpenOCD; extra args via `ARGS="..."` |
| `get_blackmagic` | Print the Blackmagic address in GDB remote format (for IDE integration) |
| `get_stlink` | Print serial numbers of attached ST-Link probes (for `SWD_TRANSPORT_SERIAL=...`) |
| `lint`, `format` | Check / reformat C code with clang-format (`.clang-format`); extra args via `ARGS="..."` |
| `lint_py`, `format_py` | Check / reformat Python, build files and manifests with [black](https://black.readthedocs.io/en/stable/index.html) |
| `lint_img`, `format_img` | Check / fix image assets (colour depth, strip metadata) |
| `lint_all`, `format_all` | Run all linters / formatters |
| `firmware_pvs` | PVS-Studio report (PVS-Studio must be on `PATH`) |
| `doxygen` | Generate Doxygen docs; `doxy` also opens them in a browser |
| `cli` | Open a Flipper [CLI](/dev/cli) session over USB |

## Firmware targets

| Target | What it does |
|---|---|
| `faps` | Build all external and plugin apps as `.fap` |
| `fap_<appid>` | Build one app as `.fap` by its app ID, e.g. `fap_snake_game` |
| `fap_<appid>_list` | Generate source + assembler listing for that app's `.fap` |
| `flash`, `firmware_flash` | Flash the current build over SWD |
| `jflash` | Flash with JFlash using a J-Link probe (JFlash must be on `PATH`) |
| `firmware_all`, `updater_all` | Build a basic set of binaries |
| `firmware_list`, `updater_list` | Generate source + assembler listings |
| `firmware_cdb`, `updater_cdb` | Generate `compilation_database.json` for IDEs — works without a full build |

Use `--extra-ext-apps` (below) to force extra apps into the external build.

## Asset targets

| Target | What it does |
|---|---|
| `resources` | Build SD card resources and their manifest files |
| `dolphin_ext` | Process dolphin animations for the SD card |
| `icons` | Generate `.c` + `.h` for icons from PNG assets |
| `proto` | Generate `.pb.c` + `.pb.h` from `.proto` sources |
| `proto_ver` | Generate a `.h` with the protobuf version |
| `dolphin_internal`, `dolphin_blocking` | Generate `.c` + `.h` for the corresponding dolphin assets |

## Command-line parameters

| Parameter | Meaning |
|---|---|
| `--options optionfile.py` | Load a file with configuration values (default `fbt_options.py`) |
| `--extra-int-apps=app1,app2,appN` | Force listed apps to be built **into** the firmware (`firmware` target) |
| `--extra-ext-apps=app1,app2,appN` | Force listed apps to be built as **external** (`firmware_extapps` target) |
| `--extra-define=A --extra-define=B=C` | Extra global C/C++ defines; can be repeated |
| `--proxy-env=VAR1,VAR2` | Extra environment variables to pass to subprocesses. By default `fbt` sanitises the environment; the always-forwarded list is in `environ.scons` |

## Configuration

Defaults live in `fbt_options.py`. Values on the command line take precedence. For **persistent personal
overrides**, create `fbt_options_local.py` next to it — it is evaluated when the default options load, so you never
need to edit the tracked file. Run `./fbt -h` to list all options.

Notable Unleashed defaults from `fbt_options.py`:

| Option | Default | Notes |
|---|---|---|
| `FIRMWARE_ORIGIN` | `"Unleashed"` | Reported in device info |
| `TARGET_HW` | `7` | Flipper Zero (f7); see [hardware targets](/dev/hardware-targets) |
| `COMPACT` | `1` | Optimise for size |
| `DEBUG` | `1` | Pass `DEBUG=0` for installable builds |
| `DIST_SUFFIX` | `"local"` | Suffix in output file names |
| `COPRO_STACK_TYPE` | `"ble_light"` | `ble_full` is supported but may not fit into debug builds |
| `FIRMWARE_APP_SET` | `"default"` | See below |

### Firmware app sets

Which apps go into the firmware is controlled by `FIRMWARE_APPS` — a map of *configuration name → tuple of app
IDs*. Choose one with `FIRMWARE_APP_SET`. Unleashed defines two sets:

```python
FIRMWARE_APPS = {
    "default": [
        # Svc
        "basic_services",
        # Apps
        "main_apps",
        "system_apps",
        # Settings
        "settings_apps",
    ],
    "unit_tests": [
        "basic_services",
        "updater_app",
        "radio_device_cc1101_ext",
        "unit_tests",
        "infrared",
        "archive",
    ],
}
```

For example, to build an image with unit tests:

```sh
./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests
```

See [Unit tests](/dev/unit-tests) for why that build needs `DEBUG=0`.

## Related pages

- [Building the firmware](/dev/build)
- [App manifests (.fam)](/dev/app-manifests)
- [Debugging apps](/dev/debugging)
- [OTA updates](/dev/ota)
