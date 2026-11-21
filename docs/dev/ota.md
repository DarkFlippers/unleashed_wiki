---
title: OTA updates
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/OTA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/update.py]
sources: [unleashed-docs, unleashed-src]
---
# OTA update process

How the Flipper installs an update package — what happens at each stage, what the update manifest contains, what
the `[XX-YY]` error codes mean, and how to build your own packages.

For the user side (installing Unleashed with qFlipper, the web installer or from the SD card) see
[Updating](/start/updating). If an update fails badly, see [Recovery](/start/recovery).

## Running code from RAM

The firmware has a special boot mode that loads a specially crafted system image into **RAM** and jumps to it. Code
running from RAM has full write access to the whole flash — impossible while the main firmware runs from that same
flash. The OTA updater uses this mode, including for updating the radio stack on the MCU's second core.

## The three stages

### 1. Back up internal storage (`/int`)

`/int` is a partition of the Flipper's flash that takes all space not used by the firmware. A new firmware can have
a different size, so installing it would repartition flash and lose data. Therefore, before anything else, the
current contents of `/int` are backed up into a plain `.tar` archive on the SD card.

### 2. Update the device

The main firmware loads the **updater** — a customised build of the firmware — into RAM and runs it. The updater
works on system flash as described by the update manifest:

1. If the package contains a **radio stack** image, its version is compared with the installed one. If they differ,
   the old stack is uninstalled and the new one written and installed. The installation is done by ST's proprietary
   **FUS** running on Core2 and involves several restarts.
2. The **Option Bytes** (low-level MCU configuration) are validated and corrected.
3. The firmware `.dfu` file is loaded, its integrity checked with CRC32, written to flash and verified.

### 3. Restore internal storage and update resources

The system restarts into the new firmware, restores the backed-up `/int` contents, and — if the package contains a
resources archive — extracts it onto the SD card.

## Update manifest

Each package comes with a manifest (the `.fuf` file) in Flipper File Format — a plain text file of key-value pairs.

### Mandatory fields (in this order)

| Key | Meaning |
|---|---|
| `Filetype` | Constant string `Flipper firmware upgrade configuration` |
| `Version` | Manifest version, currently `2` |
| `Info` | Free-form description of the package |
| `Target` | Hardware revision the package is built for |
| `Loader` | File name of the stage-2 loader executed from RAM |
| `Loader CRC` | CRC32 of the loader file, as **little-endian** hex |

### Optional fields

These may be empty — the updater then skips the related operations.

| Key | Meaning |
|---|---|
| `Radio` | File name of the radio stack image (provided by ST) |
| `Radio address` | Address to install the radio stack at (from ST release notes) |
| `Radio version` | Major, minor, sub version, branch, release and stack type packed into 6 hex bytes |
| `Radio CRC` | CRC32 of the radio image |
| `Resources` | File name of the archive with SD card resources — `resources.ths`, a heatshrink-compressed tarball (see [Heatshrink tarball format](/dev/tar-heatshrink)) |
| `OB reference`, `OB mask`, `OB write mask` | Reference values for validating and correcting option bytes |

## Error codes

The process is designed to be as fail-safe as possible: no risky operation starts before all related data has been
validated, so the device isn't left half-updated or bricked. If something goes wrong, the updater lets you retry and
shows an error code `[XX-YY]`: `XX` is the failed operation, `YY` the progress or detail at which it failed.

| Stage | XX | YY | Meaning |
|---|--:|---|---|
| Loading update manifest | **1** | **13** | Updater reported hardware version mismatch |
| | | **20** | Failed to get saved manifest path |
| | | **30** | Failed to load manifest |
| | | **40** | Unsupported update package version |
| | | **50** | Package has mismatching HW target |
| | | **60** | Missing DFU file |
| | | **80** | Missing radio firmware file |
| Backing up configuration | **2** | **0-100** | FS read/write error |
| Checking radio FW | **3** | **0-99** | Error reading radio firmware file |
| | | **100** | CRC mismatch |
| Uninstalling radio FW | **4** | **0** | SHCI Delete command error |
| | | **80** | Error awaiting command status |
| Writing radio FW | **5** | **0-100** | Block read/write error |
| Installing radio FW | **6** | **10** | SHCI Install command error |
| | | **80** | Error awaiting command status |
| Core2 is busy | **7** | **10** | Couldn't start C2 |
| | | **20** | Failed to switch C2 to FUS mode |
| | | **30** | Error in FUS operation |
| | | **50** | Failed to switch C2 to stack mode |
| Validating option bytes | **8** | **yy** | Option byte code |
| Checking DFU file | **9** | **0** | Error opening DFU file |
| | | **1-98** | Error reading DFU file |
| | | **99-100** | Corrupted DFU file |
| Writing flash | **10** | **0-100** | Block read/write error |
| Validating flash | **11** | **0-100** | Block read/write error |
| Restoring configuration | **12** | **0-100** | FS read/write error |
| Updating resources | **13-15** | **0-100** | SD card read/write error |

::: tip What to do on an error
- **1-50 / 1-13** — the package is for a different hardware target: download the right one.
- **2, 12, 13-15** — SD card problem: check / reformat the card, copy the package again.
- **3-100, 9-99/100** — corrupted files: re-download the package.
- Retry first — the updater is designed for it. If the Flipper won't boot at all, use [Recovery](/start/recovery).
:::

## Building update packages

Make sure to pass `DEBUG=0` — see [Building the firmware](/dev/build).

**Full package** — firmware, radio stack and SD card resources:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

**Minimal package** — firmware only:

```sh
./fbt COMPACT=1 DEBUG=0 updater_minpackage
```

The result is in `dist/<target>-<cfg>/` as a folder `f7-update-<suffix>` and a `flipper-z-f7-update-<suffix>.tgz`.

### Choosing a different radio stack

Packages use the **Bluetooth Light** stack by default. If your firmware supports another stack, pass its type and
binary:

```sh
./fbt updater_package COMPACT=1 DEBUG=0 COPRO_OB_DATA=scripts/ob_custradio.data COPRO_STACK_BIN=stm32wb5x_BLE_Stack_full_fw.bin COPRO_STACK_TYPE=ble_full
```

`COPRO_OB_DATA` must point to a file in `scripts/` with reference Option Byte data matching that stack type. In some
cases you also have to confirm with `COPRO_DISCLAIMER=...` on the command line.

### Partial packages

Call `scripts/update.py` directly for custom contents. For example, a package that only installs the BLE FULL stack:

```shell
scripts/update.py generate \
  -t f7 -d r13.3_full -v "BLE FULL 13.3" \
  --stage dist/f7/flipper-z-f7-updater-*.bin \
  --radio lib/stm32wb_copro/firmware/stm32wb5x_BLE_Stack_full_fw.bin \
  --radiotype ble_full
```

See `scripts/update.py generate --help` for all options.

## Installing a package from the CLI

Copy the unpacked package folder to the SD card and run:

```
update install /ext/update/f7-update-local/update.fuf
```

The [CLI](/dev/cli#update) also offers `update backup` and `update restore` for the internal storage.

## Related pages

- [Updating the firmware](/start/updating)
- [Recovery](/start/recovery)
- [Heatshrink tarball format](/dev/tar-heatshrink)
- [Flipper Build Tool (fbt)](/dev/fbt)
