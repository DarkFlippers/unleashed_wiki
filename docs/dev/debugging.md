---
title: Debugging apps
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_debugging_faps.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalDebugging.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md]
sources: [unleashed-docs]
---
# Debugging apps

Real-time (in-circuit) debugging lets you start an app, pause it anywhere, step through the code line by line and
watch variables and the call stack. It finds far more bugs than "add a log line and try again".

::: info
In-circuit debugging is optional. You can always debug by loading apps over USB and reading the
[log](/dev/cli#reading-logs).
:::

## What you need

- A Flipper Zero (the *target*).
- A Windows, Linux or macOS computer with [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) (for apps) or
  the full firmware tree with [fbt](/dev/fbt).
- A supported **SWD probe**.

### Supported SWD probes

| Probe | Notes |
|---|---|
| A **second Flipper Zero** | Run the [DAP Link app](https://lab.flipper.net/apps/dap_link) on it to turn it into an SWD probe |
| [Wi-Fi Devboard](https://shop.flipperzero.one/products/wifi-devboard) | With stock (Blackmagic) firmware; connects over USB or Wi-Fi — see [Dev Board](/gpio/devboard) |
| CMSIS-DAP probes | e.g. [Raspberry Pi Debug Probe](https://www.raspberrypi.com/products/debug-probe/), [l-tek](https://www.l-tek.com/web-shop/cmsis-dap-debug-probe/), [makerdiary Pitaya-Link](https://makerdiary.com/products/pitaya-link) |
| [Blackmagic-compatible probes](https://black-magic.org/hardware.html) | |
| ST-Link | [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html), [ST-LINK V3](https://www.st.com/en/development-tools/stlink-v3set.html), the [ST-Link V3 devboard](/dev/hardware#st-link-v3-developer-board) |
| J-Link | Flashing and debugging from VS Code only; install SEGGER tools yourself |

## Prepare the Flipper

Enable debug mode on the target: `Main Menu → Settings → System → Debug` → **ON**.

## Step by step (VS Code)

1. **Connect the probe to the Flipper's GPIO header.** Probes made for Flipper just plug in. For a generic probe
   connect three wires:

   | Signal | Flipper pin |
   |---|---|
   | SWCLK | 10 |
   | SWDIO | 12 |
   | GND | 8, 11 or 18 |

   If the probe also has a UART, connect it to the Flipper's USART (pins **13** TX and **14** RX). That port prints
   logs and crash information, which helps a lot.
2. **Connect the probe to the computer** — usually via USB; the Wi-Fi Devboard also works over Wi-Fi.
3. **Prepare the project:** run `ufbt vscode_dist` (app) or `./fbt vscode_dist` (firmware) once, open the folder in
   VS Code.
4. **Switch VS Code to Run and Debug:** click the debug icon in the sidebar or press
   <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> (<kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> on macOS). Choose the
   configuration for your probe and press **Play**.

   ::: info
   Starting a debug session **halts** the firmware. Click **Continue** in the debug toolbar to resume.
   :::
5. **Use the debug controls:** reset, pause, continue, step in, step out, disconnect.
6. **Set breakpoints** by clicking left of a line number. Execution stops when it reaches that line.
7. **Inspect the call stack** in the *Call Stack* panel while paused.
8. **Inspect variables** in the *Variables*, *Watch* or *Live Watch* panels.

A video demo from Flipper Devices: [Debugging FAPs in VS Code](https://cdn.flipperzero.one/app_dev_flipper_zero_debug_demo.mp4).

## Debugging from the command line with fbt

With the full firmware tree you can debug without VS Code:

| Command | What it does |
|---|---|
| `./fbt debug` | Build and flash firmware, then attach GDB with the firmware `.elf` loaded |
| `./fbt blackmagic` | Debug with a Blackmagic probe (Wi-Fi Devboard) |
| `./fbt debug_other` / `debug_other_blackmagic` | Attach GDB without loading an `.elf`; add your app's `.elf` with `add-symbol-file` |
| `./fbt updater_debug` | Attach GDB with the updater `.elf` |
| `./fbt openocd ARGS="..."` | Just start OpenOCD |
| `./fbt get_stlink` | List ST-Link serials, for `SWD_TRANSPORT_SERIAL=...` |

## Furi HAL debug signals

Some Furi subsystems can expose internal state on GPIO pins for tracing with a logic analyser or oscilloscope. Enable
them by adding a define at build time, for example:

```sh
./fbt --extra-define=FURI_HAL_OS_DEBUG flash
```

### `FURI_HAL_OS_DEBUG` — scheduler and sleep

Exposes tick, tick suppression, idle and time flow:

| Signal | Pin | Meaning |
|---|---|---|
| `AWAKE` | `PA7` | High while the system is busy computing, low while sleeping — tracks transitions to sleep |
| `TICK` | `PA6` | Toggles on each system tick (only when no tick suppression is in progress) — reveals tick skew and abnormal scheduling |
| `SECOND` | `PA4` | Toggles every second — disturbances in its timing mean the system doesn't meet hard real-time |

### `FURI_HAL_POWER_DEBUG` — power modes

Traces power-mode transitions:

| Signal | Pin | Meaning |
|---|---|---|
| `WFI` | `PB2` | Light sleep (wait for interrupt). The lightest, non-breaking power save mode — everything including debugging works |
| `STOP` | `PC3` | STOP mode, the platform's deep sleep. Most of the silicon is off or unusable; debugging the MCU in this mode is nearly impossible |

### `FURI_HAL_SD_SPI_DEBUG` — SD card

Logs SD card SPI bus traffic.

## Troubleshooting

| Problem | Fix |
|---|---|
| Probe connects but nothing happens | The firmware is halted — press **Continue** |
| Breakpoints in your app are ignored | Make sure the app's `.elf` symbols are loaded (VS Code config from `vscode_dist` does this; with `debug_other` use `add-symbol-file`) |
| Debugger loses the target | The MCU may be in STOP mode; see `FURI_HAL_POWER_DEBUG`. Debug mode on the Flipper must be **ON** |
| Variables show as optimised out | Build with `DEBUG=1` (note: such firmware may be too large to package — see [Building](/dev/build)) |

## Related pages

- [Your first app in C](/dev/first-app-c)
- [Flipper Build Tool (fbt)](/dev/fbt)
- [Dev Board](/gpio/devboard)
- [Hardware](/dev/hardware) — pinout drawings and devboard schematics
