---
title: Integration testing
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/integration_tests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/general_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/badusb_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/cli_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/goodfaps_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/gpio_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/ibutton_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/infrared_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/nfc_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/rfid_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/subghz_test_cases.md]
sources: [unleashed-docs]
---
# Integration testing

Besides [unit tests](/dev/unit-tests), the firmware has a **manual integration test plan**: step-by-step test cases
grouped by subsystem, each with an expected result. It's written for repository maintainers, but it's just as
useful if you build your own firmware and want to check it before using or sharing it.

This page summarises the plan. The full step lists are in the Unleashed repository under
[`documentation/testing/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation/testing).

## What and when to test

- **Test what changed, plus related regressions.** Test the new behaviour and re-run a few existing cases of the same
  subsystem. Example: when adding a Sub-GHz protocol, test it and some existing protocols.
- **Skip unrelated subsystems.** No need to test NFC when only Sub-GHz changed.
- **Test everything for core-wide changes** — if something global changed, run all cases in order.

When: **before accepting pull requests** and **before a release candidate**.

## Common test pattern for keys and cards

RFID, iButton and NFC protocol cases reuse the same "shared steps":

1. **Read** the original — data matches the original.
2. **Emulate** — read the emulated key with a second Flipper; data is identical.
3. **Save** — saved with the given name; the scene switches to the *Saved* directory.
4. **Write** to a blank — a success scene appears.
5. **Read the written** blank — data is identical to the saved key.

Many cases therefore need **a second Flipper**, real readers and blanks (T5577, RW2004/RW1990 etc.).

## Test cases by subsystem

### General (35 cases)

| Area | What is checked |
|---|---|
| BLE | Bluetooth on after reboot; pairing with the mobile app, correct Flipper name; re-pairing with a second phone |
| U2F | Register and authenticate a key on the Yubico WebAuthn demo site |
| Settings | PIN code, Storage, Power, System, Bluetooth, Desktop, LCD and Notifications, Flipper Name |
| Archive & file browser | SD card with many files: <kbd>↓</kbd> on the desktop opens Archive; each tab (Favorites, iButton, NFC, Sub-GHz, RFID, Infrared, Browser) shows its files; run, rename, delete keys |
| Cards and protocols | NTAG215, MIFARE DESFire, MIFARE Ultralight, MIFARE Classic 1K / 4K, Metakom |
| Factory update | Via qFlipper on macOS, Windows 11, Ubuntu; via the Android and iOS apps; via Flipper Lab web |
| Region provisioning | Same six channels as factory update, plus the region setting itself |
| Apps | Base apps, JS scripts, the menu on the Up button |
| Compliance | All compliance screens are shown correctly |

### CLI (3 cases)

- **Control commands:** `power` (off, reboot, reboot to DFU, `power 5v 1`), `gpio` (mode, `gpio set PA7 1` lights an
  LED on the devboard), `led b 255`, `vibro 1` / `vibro 0`.
- **Information commands:** connect with `minicom -D /dev/ttyACM0 -b 230400` or PuTTY; `log debug` while using the
  device, stop with <kbd>Ctrl</kbd>+<kbd>C</kbd>; compare `device_info` / `!` with the firmware info screen (hold
  <kbd>↓</kbd> on the desktop for 3 s); `bt hci_info`; `date`; `help` / `?`; `free`; `free_blocks`.
- **Storage commands:** `storage info /ext`, `storage format /ext` (refuse, then confirm), info with and without the
  card; `factory_reset` — answering `n` does nothing, `y` erases settings but **keeps SD card data and the time**.

Reference values for `bt hci_info` in the plan:

```
Ret: 0, HCI_Version: 11, HCI_Revision: 16484, LMP_PAL_Version: 11, Manufacturer_Name: 48,
LMP_PAL_Subversion: 8548
```

### Sub-GHz (7 cases)

| Case | Key checks |
|---|---|
| Read RAW | Record on 315, 433, 868 MHz, incl. an encrypted (rolling) remote such as Came Atomo; replay to the test stand receivers |
| Frequency Analyzer | Shows the correct frequency of different remotes |
| External module | External CC1101 (433.92 MHz module): icon changes to external, Read RAW signal stronger than internal; switching back to internal works. Never unplug the module while it's in use — the Flipper may freeze |
| Saved files | Save decoded and RAW signals, add to favourites and send from there, rename (stays in favourites), delete |
| Reception / transmission | Read on 315.000, 433.920 and 868.350 MHz, then with hopping enabled; send saved keys — the stand relays (or a second Flipper) react |
| Add Manually | Create signals manually |

### NFC (7 cases)

| Case | Key checks |
|---|---|
| Unlock NTAG/Ultralight | *Auth as* both types, wrong card type warning, manual password entry; saved cards appear in *Saved* after ~1.5 s |
| Detect Reader | Collect nonces from a reader (e.g. another Flipper), then the QR code screen on <kbd>OK</kbd> is readable |
| Emulation | Readable by several readers, including a Flipper at 10 mm and a Proxmark |
| Reading | MIFARE Classic, Ultralight, NTAG, DESFire, NFC-F, EMV bank cards |
| Timing | Compare Ultralight and Classic emulation timing with a reference using a Proxmark 3 |
| Add Manually | Create and save cards of all types, then emulate them |
| Extra actions | *Read Specific Card Type*, *MIFARE Classic Keys* (add/delete keys, the *List* button), *Unlock SLIX* with password |

Proxmark commands used for the timing test:

```
hf 14a raw -sc 3000
trace list -t 14a --frame -u
```

### 125 kHz RFID (9 cases)

Protocol cases with the shared steps for **EM-Marine EM4100, Motorola Indala26, HID H10301 (Picopass), Indala26,
Troyka/Podorozhnik**, plus Reading, writing to **T5577**, Add Manually and Emulation.

### iButton (9 cases)

**Dallas DS1971, DS1990, DS1992, DS1996**, **Cyfral**, **Metakom**: read, save, Add Manually, emulate (read by
different devices), write to an **RW2004** blank and read back, edit and delete keys.

### Infrared (3 cases)

- **Universal library** — TV, audio, AC remotes: power and other functions work.
- **Learn new remote** — add/delete remotes and buttons, rename, transmit the edited buttons.
- **Saved remotes** — add buttons to an existing remote, control devices from **at least 5 m**, delete all buttons
  and remotes.

### Bad USB (2 cases)

On macOS and Windows: the script list shows; the demo script runs with the EN layout and after changing the layout;
the "qFlipper download" script opens a terminal and downloads qFlipper; switching to **BLE** mode (Bluetooth on)
pairs with the computer and the script runs again.

### GPIO (1 case)

`GPIO → Manual Control` with the ST-Link devboard inserted: LEDs follow the pins; enabling 5 V lights the power LEDs.

### GoodFAPs — official apps (10 cases)

| App | Key checks |
|---|---|
| PicoPass | Read card, save, *Elite Dictionary Attack* starts |
| Weather Station | Reads a weather station simulated by a second Flipper on different frequencies |
| Apps from the catalog | Install via mobile app or web, icon and name correct, launch/quit, update, uninstall (app, web, file browser) |
| AVR Flasher | Dump AVR, Flash AVR, ISP programmer with `avrdude` |
| Video Game Module | Insert module → init message and status-bar icon; HDMI mirrors the screen; "Air Arkanoid" uses the accelerometer |
| Tools | Clock (full screen, format from settings); NFC/RFID Detector detects both field types |
| Signal Generator | PWM and Clock generators on different pins, frequencies and dividers |
| NFC Magic | *Check Magic Tag*, *Write Gen1a* (with risk warning), *Wipe* |
| SPI Mem Manager | Read, write, erase a SPI flash chip |
| VGM flashing | VGM Tool app: *Install official firmware*, install from a file on SD, and the manual way (Boot button + USB mass storage) |

AVR Flasher wiring used in the plan:

| AVR | Flipper |
|---|---|
| MISO | PA6 |
| MOSI | PA7 |
| SCK | PB3 |
| RESET | PB2 |
| GND | GND |
| VCC | 3V3 |

Fuse readout check (replace `m2560` with your chip, e.g. `m328p`, and the COM port):

```
avrdude.exe -p m2560 -c stk500v1 -P COM7 -U lock:r:lock.hex:r -U hfuse:r:hfuse.hex:r -U lfuse:r:lfuse.hex:r -U efuse:r:efuse.hex:r
```

::: tip Unleashed
The plan comes from the official firmware. On Unleashed, also exercise the Unleashed-only additions in the subsystem
you changed — for example extra Sub-GHz protocols and [counter mode](/subghz/counter-mode), or the extra apps in
`applications/system/` (Remote Analyzer, Nice-O-Code, Sec+ PIN, Seed Capturer, Sub-GHz RAW editor, T5577, SIM800…).
:::

## Related pages

- [Unit tests](/dev/unit-tests)
- [Command-line interface](/dev/cli)
- [Building the firmware](/dev/build)
