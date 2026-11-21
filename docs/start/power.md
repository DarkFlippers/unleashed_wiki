---
title: Power and battery
order: 80
original: [https://docs.flipper.net/zero/basics/power, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/power_settings_app, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/power]
sources: [flipper-docs, unleashed-src]
---
# Power and battery

Flipper Zero has a built-in **2100 mAh** Li-Po battery. It can last up to about a month in standby and charges over
USB-C in about two hours.

## Power on and off

- **On:** hold <kbd>BACK</kbd> for about 3 s. A fully drained Flipper turns on by itself once you plug in USB.
- **Off:** hold <kbd>BACK</kbd> on the desktop. The **Turn Off Device?** screen appears: <kbd>→</kbd> **Power Off**
  turns it off, and <kbd>←</kbd> **Battery** opens battery info. You can also use
  **Main Menu → Settings → Power → Power OFF**.

![Turn Off Device? with the crying dolphin, Battery on the left button and Power Off on the right](/screens/settings/power_off.png)

## Charging

Plug the USB-C cable into a charger or computer. The battery icon shows a lightning bolt while charging. Charging
input is 5 V / 1 A, so a full charge takes about 2 hours.

::: warning Long storage
If you won't use the Flipper for a long time, charge it to about **50 %** before turning it off. Storing it fully
discharged harms the battery. Keep it within 0–40 °C.
:::

## Settings → Power

| Item | What it does |
|---|---|
| **Battery Info** | Charge %, voltage, current, battery temperature and health |
| **Reboot** | **Firmware Upgrade** (reboot to DFU mode) or **Reboot Flipper** (normal reboot). Confirm with <kbd>→</kbd> **Reboot** |
| **Power OFF** | Turn the device off |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min`: turn off after this long idle |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%`: stop charging at this level |

![Settings → Power: Battery Info, Reboot, Power OFF, Auto PowerOff OFF, Limit Charge OFF](/screens/settings/power.png)

::: tip Limit Charge
Limit Charge is useful if the Flipper sits on USB most of the day, for example as a desktop gadget. Keeping the battery
below 100 % extends its lifespan.
:::

## Battery Info screen

The screen shows a different message depending on the state:

| Header | Meaning |
|---|---|
| `Yummy!` / `Charging at` | Charging. Shows USB voltage and charge current |
| `Om-nom-nom!` / `Consumption is` | Running on battery, with the current draw. `Oh no!` and `mA!` mean a high drain |
| `Charged!` | USB connected, not charging (battery full) |
| `Charged!` / `Limited to` | USB connected, and a non-default charge voltage limit is set (shown in V) |
| `Napping...` | On battery, almost no current draw |

It also shows battery %, voltage, temperature (°C or °F, set by **Settings → System → Units**) and battery **health** %.

![Battery Info: Om-nom-nom! Consumption is 18 mA, 100 %, 29 °C, 4.1 V, health 100 %](/screens/settings/battery_info.png)

## Power consumption

| Mode | Typical current |
|---|---|
| Sleep (Default sleep method) | ~1.5 mA |
| Sleep (Legacy sleep method) | ~9 mA |
| Active, backlight on | up to ~30 mA (up to ~50 mA with a poor SD card) |
| Active radio | up to ~400 mA |
| Radio + external module | up to ~2 A |

**Sleep Method** is in **Settings → System**. `Default` saves power. `Legacy` uses more but can help if you see
crashes in sleep.

Sleep needs **Debug** = `OFF` (**Settings → System**) and **Listen UART** = `None`
(**Settings → Expansion Modules**). Otherwise the device cannot go to sleep and the battery drains faster.

## Tips for longer battery life

- Keep the firmware up to date.
- Turn Bluetooth off when you don't need it (Lock Menu → **Turn Bluetooth Off**).
- Lower **LCD Backlight** and **Backlight Time** in **LCD and Notifications**.
- Use a good branded microSD card.
- Set **Auto PowerOff**.
- If the battery drains fast, check the current in **Battery Info**.

## Power specifications

| Parameter | Value |
|---|---|
| Battery capacity | 2100 mAh |
| Battery operating voltage | 3.3–4.2 V |
| Charge time | ~2 hours |
| Charging voltage / current | 5 V, 1 A |
| Connector | USB Type-C |
| Max current from USB including connected devices | 3 A |

## Related

- Rebooting and reset combinations: [Key combos](/start/key-combos)
- The device does not turn on: [Recovery](/start/recovery)
