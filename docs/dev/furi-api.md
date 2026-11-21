---
title: Furi API
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_furi_api.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriCheck.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi]
sources: [unleashed-docs, unleashed-src]
---
# Furi API

To use the Flipper's hardware — screen, speaker, radio, USB, NFC — your app talks to **Furi**, the set of libraries
that sits between the bare hardware and application code. This page gives an overview of the hardware and software
architecture, and explains Furi's run-time checks.

## Hardware

The heart of Flipper Zero is an **STM32WB55** microcontroller (MCU): two cores, RAM, flash and dozens of peripheral
blocks (timers, RTC, BLE, GPIO, …). Their operation is described in the MCU's Reference Manual. Around the MCU there
are several external chips (CC1101, ST25R3916, display controller, etc.) with their own datasheets.

![Hardware structure of Flipper Zero](/img/dev/flipper_zero_hardware.png)

Colour legend:

- **Purple** — blocks inside the MCU
- **Blue** — chips external to the MCU
- **Orange** — other peripheral components that don't need complex interaction

Because the firmware is open-source, you *can* access the hardware directly and write your own low-level drivers —
but usually you don't need to.

## Software: Furi

**Furi** (**F**lipper **U**niversal **R**egistry **I**mplementation) is the abstraction layer included in the
firmware. It gives a straightforward API for the hardware and for common system tasks: threads, dynamic memory,
resource access control (records), timers, message queues, logging and so on.

With Furi you don't have to read hundreds of pages of datasheets or write drivers — learning the Furi API is enough.
It also avoids every developer re-implementing the same things.

![Hardware + software structure of Flipper Zero](/img/dev/flipper_zero_architecture.png)

Furi spans the full width of the diagram: it separates application-level code (services and apps) from the hardware
underneath.

Furi consists of two parts:

| Part | Where | What |
|---|---|---|
| Furi Core | `furi/` | OS primitives: threads, mutexes, message queues, records, timers, event loop, logging, checks |
| Furi HAL | `targets/` (e.g. `targets/f7/furi_hal/`) | Hardware abstraction: GPIO, SPI, I2C, USB, Sub-GHz, NFC, RFID, power, … — see [FuriHalBus](/dev/furi-hal-bus) |

Source code:

- Furi Core: [unleashed-firmware/furi](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi)
  (official: [flipperzero-firmware/furi](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/furi))
- Furi HAL: [unleashed-firmware/targets](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets)
  (official: [flipperzero-firmware/targets](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/targets))

## Finding examples

Every Flipper app uses Furi, so there are examples for any hardware block:

- example apps in [`applications/examples/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples)
  (`example_event_loop`, `example_adc`, `example_ble_beacon`, …);
- built-in apps in `applications/main/` and the extra Unleashed apps in `applications/system/`;
- community apps in the [Apps Catalog](https://lab.flipper.net/apps) — the source link is at the bottom of each app
  page. Pick apps whose functionality is close to what you want to build.

Every Furi function, struct and header is listed in the official [Doxygen API reference](https://developer.flipper.net/flipperzero/doxygen/) — use it when this wiki does not cover the call you need.

## Run-time checks and forced crashes

The best way to protect system integrity is to handle fewer impossible cases and **crash as early as possible** when
something is wrong. Furi Core's `check.h` provides helpers for that.

Terms:

- **Crash** — log the event, save crash information in RTC, reboot.
- **Halt** — log the event, stall the system.

Notes:

- Debug and release builds behave differently: a **debug build never resets** the system, to preserve state for the
  debugger.
- With a debugger connected, execution stops automatically before reboot.
- All helpers accept an optional `MESSAGE_CSTR`. It can be in RAM or flash, but **only messages stored in flash** are
  shown after the reboot (i.e. use string literals).
- `MESSAGE_CSTR` can be `NULL`, but the macros already handle the no-message case — just omit it.

| Macro | Behaviour | When to use |
|---|---|---|
| `furi_assert(CONDITION)` / `furi_assert(CONDITION, MESSAGE_CSTR)` | Crash if `CONDITION` is false — **only in development builds** | Development-stage checks in apps and services |
| `furi_check(CONDITION)` / `furi_check(CONDITION, MESSAGE_CSTR)` | **Always** crash if `CONDITION` is false | Conditions that must hold in every build |
| `furi_crash()` / `furi_crash(MESSAGE_CSTR)` | Crash unconditionally | An abnormal condition was detected |
| `furi_halt()` / `furi_halt(MESSAGE_CSTR)` | Halt the system | Used internally, e.g. to stop when power-off isn't possible |

::: warning furi_assert pitfalls
- Release builds (`DEBUG=0`) never contain `furi_assert` checks.
- Libraries never contain them by default; build with `LIB_DEBUG=1` if you need them.
- Don't put function calls (side effects) inside the `CONDITION` — the whole expression may be compiled out.
:::

Example:

```c
#include <furi.h>

void my_set_level(uint8_t level) {
    furi_check(level <= 100, "Level out of range");
    // ...
}
```

## Related pages

- [GUI in apps](/dev/gui)
- [FuriHalBus API](/dev/furi-hal-bus)
- [Debugging apps](/dev/debugging) — includes Furi HAL debug signals
