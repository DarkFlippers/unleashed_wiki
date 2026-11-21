---
title: Clock
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/clock_app, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Clock

A bedside clock: big time display, date and battery level, screen brightness control with a red LED nightlight, a
stopwatch and a daily alarm. Based on FlipperNightStand by @nymda, with @Willy-JL, @mishamyte and @xMasterX
(app version 1.3).

`Main Menu → Clock`

![Clock: the date above the big time display and the battery level below it](/screens/apps/clock.png)

::: tip Unleashed
In Unleashed the Clock is a main-menu app with alarm and nightlight. If you only want the time on the desktop, turn on
`Settings → Desktop → Show Clock` instead.
:::

## Buttons on the clock screen

| Button | Action |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | screen brightness up / down (a bar appears and hides 3 s after the last press) |
| <kbd>↓</kbd> at brightness 0 | switch the dim red LED nightlight on / off |
| <kbd>OK</kbd> | stopwatch Start / Stop |
| <kbd>←</kbd> | reset the stopwatch |
| <kbd>→</kbd> | alarm setup |
| <kbd>Back</kbd> | exit |

The time follows the system format: 12-hour with AM/PM or 24-hour, as set in `Settings → System → Time Format`.

## Stopwatch

1. Press <kbd>OK</kbd> to start; the running time appears as `MM:SS`.
2. Press <kbd>OK</kbd> again to stop, once more to continue.
3. Press <kbd>←</kbd> (**Reset**) to clear it.

## Daily alarm

1. On the clock screen press <kbd>→</kbd>.
2. Set **Alarm** to **ON** with <kbd>←</kbd> / <kbd>→</kbd>.
3. Select **Set time** and press <kbd>OK</kbd>.
4. In the `Alarm time` picker: <kbd>←</kbd> / <kbd>→</kbd> choose hours, minutes (and AM/PM in 12-hour mode),
   <kbd>↑</kbd> / <kbd>↓</kbd> change the value (hold to repeat). <kbd>OK</kbd> or <kbd>Back</kbd> saves.
5. Press <kbd>Back</kbd> to return to the clock. The alarm time is shown on the clock screen.

When the alarm fires, the screen flashes `! ALARM !` with `Press any key to stop`, a melody plays with vibration and
the red LED. Press any key to stop it. The alarm stays armed and goes off again the next day at the same time.

::: warning
The alarm only rings while the Clock app is open. Leave the Flipper on the charger with the Clock running overnight.
:::

The alarm and the brightness level are saved in `/ext/apps_data/clock/` and restored the next time you open the app.

## Related pages

- [Desktop](/start/desktop)
- [Settings](/start/settings)
- [Apps that ship with Unleashed](/apps/catalog)
