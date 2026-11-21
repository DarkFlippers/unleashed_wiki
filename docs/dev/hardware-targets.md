---
title: Hardware targets
order: 25
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HardwareTargets.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets]
sources: [unleashed-docs, unleashed-src]
---
# Hardware targets

The firmware is modular: one code base supports several hardware configurations. Everything that differs between
boards — the `furi_hal` implementation, board init code, linker scripts, SDK symbol tables — is bundled into a
**target definition**.

The Unleashed repository ships two targets in `targets/`:

| Folder | Hardware |
|---|---|
| `targets/f7` | Flipper Zero — the default (`TARGET_HW = 7`) |
| `targets/f18` | "Not Flipper Zero" — a board without the radio front-ends; inherits f7 |

Shared headers are in `targets/furi_hal_include`.

## How a target is organised

Each target lives in its own subfolder of `targets/`. It must contain `target.json` and may contain any other files
that definition refers to. By default `fbt` compiles **every source file** in the target folder unless it is
explicitly excluded. Targets can **inherit** from another target to avoid duplicating code.

## `target.json` fields

| Field | Type | Meaning |
|---|---|---|
| `include_paths` | list of strings | Folders (relative to the target) added to the global C/C++ include path |
| `sdk_header_paths` | list of strings | Folders whose headers are included in the SDK |
| `startup_script` | filename | Startup script doing the initial hardware init |
| `linker_script_flash` | filename | Linker script for the main firmware image |
| `linker_script_ram` | filename | Linker script for the "updater" configuration (runs from RAM) |
| `linker_script_app` | filename | Linker script for `.fap` files |
| `sdk_symbols` | filename | `.csv` with the current SDK (API) definition for this target |
| `linker_dependencies` | list | Libraries to link the firmware with. Libraries not listed are **not built**. Several link passes may need the same name twice |
| `inherit` | string | Target to take the base configuration from. List values are extended, other values are overridden |
| `excluded_sources` | list | Files from inherited configuration(s) **not** to build |
| `excluded_headers` | list | Headers from inherited configuration(s) **not** to put in the SDK |
| `excluded_modules` | list | `fbt` library (module) names to exclude when configuring the build |

## Example: how f18 inherits f7

`targets/f18/target.json` (shortened) shows inheritance and exclusions in practice — it takes everything from f7
and drops the Sub-GHz, NFC, RFID, iButton and infrared drivers:

```json
{
    "inherit": "7",
    "include_paths": [
        "furi_hal"
    ],
    "sdk_symbols": "api_symbols.csv",
    "excluded_sources": [
        "furi_hal_infrared.c",
        "furi_hal_nfc.c",
        "furi_hal_rfid.c",
        "furi_hal_subghz.c"
    ],
    "excluded_modules": [
        "nfc",
        "lfrfid",
        "subghz",
        "ibutton",
        "infrared"
    ]
}
```

## Apps and hardware

Not every app is available on every target.

- **Built-in apps:** choose a compatible app set with the `FIRMWARE_APP_SET=...` option
  (see [fbt → firmware app sets](/dev/fbt#firmware-app-sets)).
- **External apps (FAPs):** list compatible targets in the app's `application.fam`. For example, to build an app for
  f7 only, add:

```python
    targets=["f7"],
```

It won't be built for other targets. See [App manifests](/dev/app-manifests).

## Building for a specific target

Pass `TARGET_HW` (and optionally `FIRMWARE_APP_SET`) to `fbt`. For example, to build and flash firmware for f18
over USB:

```sh
./fbt TARGET_HW=18 flash_usb_full
```

## Related pages

- [Flipper Build Tool (fbt)](/dev/fbt)
- [App manifests (.fam)](/dev/app-manifests)
- [FuriHalBus API](/dev/furi-hal-bus)
