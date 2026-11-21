---
title: Desktop
order: 60
original: [https://docs.flipper.net/zero/basics/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Desktop

The desktop is the home screen. Your [dolphin](/start/dolphin) lives here, and a status bar runs along the top.
From the desktop, single button presses open the main menu, the Archive, the Lock Menu and your favourite apps.

## Status bar

The top line shows small icons:

| Icon | Meaning |
|---|---|
| Battery | Charge level. Shows a lightning bolt while charging. Style set by `Battery View` |
| SD card | microSD mounted. A crossed icon means the card failed to mount: see [microSD card](/start/sd-card) |
| Bluetooth | BLE is on. A different icon means a device is connected |
| Lock | The Flipper is locked |
| Muted speaker | Stealth mode: sound and vibro off (see [Lock Menu](#lock-menu)) |
| PC | Connected to qFlipper / Flipper Lab over USB |
| Gamepad | Dummy Mode is on |
| Module | An expansion module is connected |
| Beacon | BLE beacon mode (for example FindMy Flipper) |
| Background app | An app is running in the background |

::: tip Unleashed
- **Settings → Desktop → Battery View** selects the battery style: `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %`.
- **Settings → Desktop → Show Clock** = `ON` shows the time on the desktop. The format (24h/12h) comes from
  **Settings → System → Time Format**.
:::

## Desktop buttons

| Button | Short press | Long press |
|---|---|---|
| <kbd>OK</kbd> | **Main Menu** | Favorite App - Ok Long |
| <kbd>↑</kbd> | **Lock Menu** | **Lock** (with PIN if set) |
| <kbd>↓</kbd> | **Archive** | Device info / debug screen |
| <kbd>←</kbd> | Favorite App - Left Short (**Apps** menu by default) | Favorite App - Left Long |
| <kbd>→</kbd> | **Passport** by default (Favorite App - Right Short) | Favorite App - Right Long |
| <kbd>BACK</kbd> | — | **Power off** screen |

### Device info screen {#info-screen}

A long press of <kbd>↓</kbd> opens an info screen: firmware version and build date, hardware version, uptime, the
Flipper name and whether Debug is `ON`/`OFF`.

![Device info screen: firmware version, hardware version, uptime and the Debug state](/screens/desktop/debug.png)

On that screen a **long press of <kbd>OK</kbd> turns Debug on or off** — the same switch as
`Settings → System → Debug` ([Settings](/start/settings)), without walking the menus. A short <kbd>BACK</kbd>
returns to the desktop.

Debug `ON` adds entries that are otherwise hidden: the **Internal** tab in the [Archive](#archive) and
`Signal Settings` in the Sub-GHz saved-signal menu ([Signal Settings](/subghz/signal-settings)). Turn it off again
when you are done — debug settings slow the Flipper down and stop it sleeping.

## Main Menu

Press <kbd>OK</kbd>. The main menu opens on **Apps** (all `.fap` apps from the SD card, grouped by
category), followed by **Sub-GHz**, **125 kHz RFID**, **NFC**, **Infrared**, **GPIO**, **iButton**,
**Bad USB**, **U2F**, **Clock**, and **Settings** last. The list wraps around, so pressing <kbd>↑</kbd>
on **Apps** jumps straight to **Settings**.

![Main menu with Apps selected, Settings above it and Sub-GHz below](/screens/mainmenu/main.png)

::: tip Menu styles
**Settings → Desktop → Menu Style** switches the main-menu look. Styles are plugins in
`/ext/apps_data/loader/plugins/` (files starting with `menu_style_`). `Default` is the built-in list.
:::

## Lock Menu {#lock-menu}

Press <kbd>↑</kbd> on the desktop. Move with <kbd>↑</kbd>/<kbd>↓</kbd> and press <kbd>OK</kbd>:

| Item | What it does |
|---|---|
| **Turn Bluetooth On / Off** | Switches BLE without going into Settings |
| **Mute / Unmute** | Stealth mode: no sound and no vibration. The **Volume** and **Vibro** settings show `Stealth` while it is on |
| **Dummy Mode / Default Mode** | Enter or leave [Dummy Mode](#dummy-mode) |

Press <kbd>←</kbd> or <kbd>→</kbd> in the Lock Menu to open the second page, **Quick Settings**:

| Item | Control |
|---|---|
| Brightness | <kbd>OK</kbd> to edit, then <kbd>←</kbd>/<kbd>→</kbd> (or <kbd>↑</kbd>/<kbd>↓</kbd>), in 5 % steps |
| Volume | Same. A short beep plays so you can hear the new level |
| Vibro | <kbd>OK</kbd> toggles it on the spot |

<kbd>BACK</kbd> leaves the item being edited, and a second <kbd>BACK</kbd> leaves the page. Changes go into the same
settings as **LCD and Notifications**.

::: tip Unleashed
In Unleashed, **locking itself** is a long press of <kbd>↑</kbd> on the desktop: with the PIN if one is set, or a
regular lock otherwise.
:::

## Locking and PIN

- **Lock:** hold <kbd>↑</kbd> on the desktop. Without a PIN, the buttons are locked. **To unlock, press
  <kbd>BACK</kbd> three times** quickly.
- **With a PIN:** set it in **Settings → Desktop → PIN Setup → Set PIN**. A PIN is 4 to 10 arrow presses. The locked
  Flipper then asks for the PIN. After wrong attempts it shows `Wrong PIN!` and a timeout before the next try.
- **Auto Lock:** **Settings → Desktop → Auto Lock Time** (`OFF`, `10s` … `10min`) locks the device after that much
  inactivity. **Auto Lock disarm by active USB session** = `ON` prevents auto-lock while the Flipper is connected over USB.

::: warning Forgotten PIN
A forgotten PIN can only be reset together with all user settings: see [Recovery → Reset a forgotten PIN](/start/recovery#reset-pin).
Files on the microSD card are kept.
:::

## Dummy Mode {#dummy-mode}

Dummy Mode turns the Flipper into a toy. Most functions are hidden, and the buttons launch apps you choose, such as games. Turn it on in **Lock Menu → Dummy Mode**, and off with **Lock Menu → Default Mode**.

In Dummy Mode, each button can start its own app. Set them in **Settings → Desktop**:

`DummyMode - Left`, `- Left Long`, `- Right`, `- Right Long`, `- Up Long`, `- Down`, `- Down Long`, `- Ok`, `- Ok Long`.

An unassigned button opens the Passport. A short <kbd>↑</kbd> still opens the Lock Menu. If `DummyMode - Up Long` is set
to `None`, a long <kbd>↑</kbd> locks the device.

::: tip Unleashed
Stock firmware has 4 Dummy Mode shortcuts. Unleashed has 9 (short and long press on each button), so you can keep
several games one press away.
:::

## Favourite apps (quick access)

**Settings → Desktop → Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long**

For each slot you can choose:
- **Apps Menu (Default)** or **Passport (Default)**: the built-in default for that slot;
- **None (disable)**: the button does nothing;
- **Lock Flipper**;
- any main-menu app;
- **[Select App]**: pick any `.fap` file from `/ext/apps/`.

## Archive

Press <kbd>↓</kbd>. The Archive shows your saved files sorted into tabs. Switch tabs with <kbd>←</kbd>/<kbd>→</kbd>:

| Tab | Folder / content |
|---|---|
| Favorites | Files you pinned |
| iButton | `/ext/ibutton` (`.ibtn`) |
| NFC | `/ext/nfc` (`.nfc`) |
| Sub-GHz | `/ext/subghz` (`.sub`) |
| SubRem | `/ext/subghz_remote`: Sub-GHz Remote maps |
| RFID LF | `/ext/lfrfid` (`.rfid` and T5577 dumps) |
| Infrared | `/ext/infrared` (`.ir`) |
| Bad USB | `/ext/badusb` (`.txt`) |
| Phone | `/ext/phonebook`: SIM800 phonebook (`.phone`) |
| U2F | U2F token |
| Apps | `/ext/apps` (`.fap` and `.js`) |
| Internal | Internal storage (only with **Debug** = `ON`) |
| Browser | The whole microSD card |

Press <kbd>OK</kbd> on a file to open its context menu: run/emulate, **Pin**/**Unpin** (add to Favorites),
**Rename**, **Delete**, and in the Browser also **Cut**, **Copy**, **Paste** and **NewDir**. In the Favorites tab,
hold <kbd>OK</kbd> to open the menu.

::: tip Pin settings to Favorites
In **Main Menu → Settings**, hold <kbd>OK</kbd> on any settings item to pin it to Favorites. You can then open it from
the Archive without going through the menus.
:::

## Passport

Press <kbd>→</kbd> on the desktop, or open **Settings → Passport**. It shows the dolphin's name (the Flipper name), mood
and level: see [Pet dolphin](/start/dolphin).
