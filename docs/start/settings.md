---
title: Settings
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Settings

**Main Menu → Settings** contains these items, in the order they appear on the device:

**About** · **Bluetooth** · **Clock & Alarm** · **Desktop** · **Expansion Modules** · **Input** ·
**LCD and Notifications** · **Passport** · **Power** · **Storage** · **System**

In lists like these, move with <kbd>↑</kbd>/<kbd>↓</kbd>, change a value with <kbd>←</kbd>/<kbd>→</kbd>, and open an
item that has a sub-screen with <kbd>OK</kbd>.

![Settings menu: About, Bluetooth, Clock & Alarm, Desktop…](/screens/settings/menu.png)

::: tip Pin a setting to Favorites
Hold <kbd>OK</kbd> on any item in the Settings list to pin it to (or unpin it from) the Archive **Favorites** tab.
That gives you quick access from the desktop with <kbd>↓</kbd>.
:::

::: info
Most settings apps (About, Bluetooth, Clock & Alarm, Desktop, Expansion Modules, Input, LCD and Notifications, Passport)
are `.fap` files installed to `/ext/apps/assets/` by the firmware update. **Power**, **Storage** and **System** are
built into the firmware and work even without an SD card.
:::

## About

Information screens. Move between them with **Next** (<kbd>→</kbd>) and **Prev.** (<kbd>←</kbd>):

1. **Unleashed Firmware** notice: for experimental purposes only, not for illegal use;
2. licence: the firmware is free and open source, and *"If you paid any money for it - you got scammed."*;
3. *"Community apps included in all builds except `c` build"* and a link to github.com/DarkFlippers;
4. product, model, FCC ID / IC;
5. compliance link and manufacturer address;
6. **HW Version Info**: hardware version, region, Flipper name, serial number;
7. **FW Version Info**: version and build date, git hash, API version, radio stack, target and branch.

## Bluetooth

| Item | Values / action |
|---|---|
| **Bluetooth** | `ON` / `OFF`. Shows `Broken` if the radio stack is damaged ([Recovery](/start/recovery)) |
| **Unpair All Devices** | Confirm with **Unpair**. Removes all pairings, including the Bad USB over Bluetooth (BadKB), Bluetooth Remote and Authenticator pairing keys |

Use **Unpair All Devices** if the mobile app no longer connects after an install or a name change. See [FAQ](/start/faq).

## Clock & Alarm

One screen with three rows: **Time** (hh:mm:ss), **Date** (dd.mm.yyyy) and **Alarm** (hh:mm, `On`/`Off`).

1. Select a row with <kbd>↑</kbd>/<kbd>↓</kbd> and a field with <kbd>←</kbd>/<kbd>→</kbd>.
2. Press <kbd>OK</kbd> to edit and change the value with <kbd>↑</kbd>/<kbd>↓</kbd>.
3. Press <kbd>OK</kbd> or <kbd>BACK</kbd> to stop editing.

When the alarm rings, <kbd>BACK</kbd> **snoozes** for 9 minutes and any other button stops it. An alarm that nobody
stops turns itself off after 10 minutes. The **Clock** app in the main menu shows a large clock and has brightness
controls, the alarm and a timer.

## Desktop

| Item | Values | Description |
|---|---|---|
| **PIN Setup** | → submenu | **Set PIN** / **Change PIN** / **Remove PIN**. A PIN is 4–10 arrow presses |
| **Auto Lock Time** | `OFF`, `10s`, `15s`, `30s`, `60s`, `90s`, `2min`, `5min`, `10min` | Lock after inactivity |
| **Auto Lock disarm by active USB session** | `OFF` / `ON` | No auto lock while connected over USB |
| **Battery View** | `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %` | Battery icon style |
| **Show Clock** | `OFF` / `ON` | Clock on the desktop |
| **Menu Style** | `Default` + installed styles | Main-menu look. Styles are `menu_style_*` plugins in `/ext/apps_data/loader/plugins/`. Shows `Missing` if the selected style file was deleted |
| **Change Flipper Name** | text | [Custom Flipper name](/start/custom-name) |
| **Happy Mode** | Enable / Disable | The dolphin never gets angry ([Pet dolphin](/start/dolphin)) |
| **Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long** | app | Desktop quick-access apps |
| **DummyMode - Left / Left Long / Right / Right Long / Up Long / Down / Down Long / Ok / Ok Long** | app | Apps for [Dummy Mode](/start/desktop#dummy-mode) |

For each Favorite/Dummy slot you can choose **Apps Menu (Default)** or **Passport (Default)**, **None (disable)**,
**Lock Flipper**, any main-menu app, or **[Select App]** to pick any `.fap` from `/ext/apps/`.

::: warning PIN
The setup screen warns: *"Forgotten PIN can only be reset with entire device."* The PIN reset also wipes your settings
(files on the SD card are kept): see [Recovery](/start/recovery#reset-pin).
:::

::: tip Unleashed
Change Flipper Name, Battery View, Show Clock and the 9 Dummy Mode slots are Unleashed additions.
:::

## Expansion Modules

| Item | Values | Description |
|---|---|---|
| **Listen UART** | `USART` (pins 13, 14), `LPUART` (pins 15, 16), `None` | Which UART listens for modules using the expansion protocol (for example the [Video Game Module](/gpio/video-game-module)) |

Set it to `None` if you don't use such modules. That saves power and lets the Flipper sleep.

## Input

| Item | Values | Description |
|---|---|---|
| **Buttons Vibro** | `OFF`, `1`…`9` | Vibration feedback on button events. Higher numbers give a longer pulse |
| **Vibro Trigger** | `Press`, `Release`, `Both` | When the feedback fires |

## LCD and Notifications

| Item | Values | Description |
|---|---|---|
| **LCD Contrast** | `-10` … `+18` | Display contrast |
| **LCD Backlight** | `0%` … `100%` (step 5 %) | Backlight brightness |
| **Backlight Time** | `Always ON`, `2s`, `5s`, `10s`, `15s`, `30s`, `60s`, `90s`, `120s`, `5min`, `10min`, `30min` | Backlight timeout |
| **Night Shift** | `OFF`, `-10%` … `-60%` | Dims the backlight by this much during the night window |
| **. Start** | `17:00` … `23:30` | Night window start (locked while Night Shift is `OFF`) |
| **. End** | `05:00` … `11:30` | Night window end |
| **LED Brightness** | `0%` … `100%` | Status LED brightness |
| **Volume** | `0%` … `100%` | Speaker volume (`Stealth` when muted from the Lock Menu) |
| **Vibro** | `OFF` / `ON` | Vibration (`Stealth` when muted) |
| **LCD Inversion** | `OFF` / `ON` | Inverts the display colours |
| **RGB Mod Settings** | → submenu | Only for Flippers with the RGB backlight **hardware mod** |

**RGB Mod Settings** (<kbd>OK</kbd> on the item): **RGB backlight installed** (`OFF`/`ON`). The other items stay locked
(`RGB MOD OFF!`) until this is `ON`: **LED 1 Color**, **LED 2 Color**, **LED 3 Color**, **Effects** (`OFF`, `Rainbow`,
`Wave`), **. Speed** (`0.1s`…`1s`), **. Color step** (`1`–`3`), **. Saturation**, **. Wave wide** (`1`–`3`).

::: danger RGB mod
Turn **RGB backlight installed** on **only** if your Flipper has the
[RGB backlight hardware mod](https://github.com/quen0n/flipperzero-firmware-rgb#readme). On a stock Flipper the
backlight stops working. If that happened, go back here and set it to `OFF` (see [FAQ](/start/faq#backlight-does-not-work)).
:::

## Passport

The dolphin's profile: name, mood and level. Also opened with <kbd>→</kbd> on the desktop. See [Pet dolphin](/start/dolphin).

## Power

| Item | Values | Description |
|---|---|---|
| **Battery Info** | — | Charge, voltage, current, temperature, health |
| **Reboot** | **Firmware Upgrade** / **Reboot Flipper** | Reboot into DFU mode (`Reboot to DFU Mode?`) or a normal reboot |
| **Power OFF** | — | Turn off |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` | Turn off after inactivity |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` | Stop charging at this level |

More: [Power and battery](/start/power).

## Storage

| Item | Description |
|---|---|
| **About Internal Storage** | Internal storage info (`Virtual (/.int on SD)`) and free flash |
| **About SD Card** | Card label, type, size, free space, manufacturer and serial |
| **Unmount SD Card** / **Mount SD Card** | Safe removal / mount again |
| **Format SD Card** | Erase and format the card |
| **Benchmark SD Card** | SPI speed test |
| **Factory Reset** | Press **Erase** 5 times. Erases internal storage and reboots |

More: [microSD card](/start/sd-card), [Recovery](/start/recovery#factory-reset).

## System

| Item | Values | Description |
|---|---|---|
| **Hand Orient** | `Righty` / `Lefty` | Left-handed mode: rotates the screen and remaps the buttons |
| **Units** | `Metric` / `Imperial` | Units (for example °C/°F in Battery Info) |
| **Time Format** | `24h` / `12h` | Clock format |
| **Date Format** | `D/M/Y`, `M/D/Y`, `Y/M/D` | Date format |
| **Log Level** | `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace` | How much is logged. `Default` = `Info` |
| **Log Device** | `USART`, `LPUART`, `None` | UART used for logs (USART = pins 13/14, LPUART = pins 15/16) |
| **Log Baud Rate** | `9600` … `1843200` | Log UART speed |
| **Debug** | `OFF` / `ON` | Debug mode: extra debug features in apps, the Archive **Internal** tab, SWD access |
| **Heap Trace** | `None`, `Main` | Memory allocation tracing (for developers) |
| **Sleep Method** | `Default` / `Legacy` | `Legacy` uses more power (~9 mA vs ~1.5 mA) but can be more stable |
| **File Naming** | `Default` / `Detailed` | `Detailed` puts the type, date and time in new file names |

![Settings → System: Hand Orient Righty, Units Metric, Time Format 24h, Date Format D/M/Y…](/screens/settings/system.png)

**Debug** has a shortcut: hold <kbd>↓</kbd> on the desktop, then hold <kbd>OK</kbd> on the info screen
([Desktop → Device info screen](/start/desktop#info-screen)).

::: warning Slow Flipper?
For normal use, keep **Log Level** = `None` (or `Default`), **Debug** = `OFF` and **Heap Trace** = `None`. Debug
settings slow the device down and stop it from sleeping.
:::

## Related

- [Desktop](/start/desktop): what the desktop settings do in practice
- [Custom Flipper name](/start/custom-name)
- [Sub-GHz settings](/subghz/settings): radio settings inside the Sub-GHz app
