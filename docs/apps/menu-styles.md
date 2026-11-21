---
title: Main menu styles
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/menu_styles, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-src]
---
# Main menu styles

::: tip Unleashed
Unleashed lets you change how the **main menu** (the list you get by pressing <kbd>OK</kbd> on the desktop) is drawn.
Each look is a small plugin that ships with the firmware; the stock firmware has only the default list.
:::

## Choosing a style

1. Open `Main Menu → Settings → Desktop`.
2. Scroll to **Menu Style**.
3. Press <kbd>←</kbd> / <kbd>→</kbd> to pick a style. **Default** is the standard menu.
4. Leave Settings and press <kbd>OK</kbd> on the desktop: the menu opens in the new style.

## Available styles

| Style | Look | Origin |
|---|---|---|
| Default | the standard Flipper list | built in |
| 3D | a 3D carousel of icons | ported by @apfxtech, based on the 3D OLED carousel menu by @upiir |
| C64 | Commodore 64 screen | ported from Momentum, by Sil (@Sil333033) |
| Compact | a denser list | ported from Momentum, by @MatthewKuKanich |
| CoverFlow | album-cover style carousel | ported from Momentum, by Cody Tolene (@CodyTolene), refined by @956MB |
| DSi | Nintendo DSi style | ported from Momentum, by Willy-JL |
| Grid | icons in a grid | by @apfxtech |
| Macintosh | classic Mac OS desktop | ported by @apfxtech, based on Ardutosh by @jhhoward |
| PS4 | PlayStation 4 style | ported from Momentum, by Willy-JL |
| Vertical | vertical list | ported from Momentum, by Willy-JL |
| Wii | Nintendo Wii channel grid | ported from Momentum, by Willy-JL |

In Settings the styles are listed alphabetically after **Default**. In every style <kbd>OK</kbd> opens the selected
app and <kbd>Back</kbd> returns to the desktop.

## Where the styles live

Styles are loader plugins: `.fal` files named `menu_style_<name>.fal` in `/ext/apps_data/loader/plugins/`. The
**Menu Style** list is built from the files found there, so:

- styles need the **SD card**;
- a style shows as **Missing** if the selected file was deleted (reinstall the firmware to restore it), and
  **Unknown** if the card could not be read;
- if a style fails to load, the Flipper falls back to the default menu.

::: info For developers
A new style is a `FlipperAppType.PLUGIN` with `requires=["loader"]` and an `appid` starting with `menu_style_`; the
prefix is what Settings uses to tell menu styles from other loader plugins in the same folder. See
`applications/system/menu_styles/` in the firmware source and [App manifests](/dev/app-manifests).
:::

## Related pages

- [Desktop](/start/desktop)
- [Settings](/start/settings)
- [Unleashed features](/start/unleashed-features)
