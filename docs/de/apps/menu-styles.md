---
title: Hauptmenü-Stile
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/menu_styles, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-src]
---
# Hauptmenü-Stile

::: tip Unleashed
Mit Unleashed kannst du ändern, wie das **Hauptmenü** gezeichnet wird (die Liste, die du mit <kbd>OK</kbd> auf dem
Desktop öffnest). Jedes Aussehen ist ein kleines Plugin, das mit der Firmware ausgeliefert wird; die
Original-Firmware hat nur die Standardliste.
:::

## Einen Stil auswählen

1. Öffne `Main Menu → Settings → Desktop`.
2. Scrolle zu **Menu Style**.
3. Drücke <kbd>←</kbd> / <kbd>→</kbd>, um einen Stil zu wählen. **Default** ist das Standardmenü.
4. Verlasse Settings und drücke auf dem Desktop <kbd>OK</kbd>: das Menü öffnet sich im neuen Stil.

## Verfügbare Stile

| Stil | Aussehen | Herkunft |
|---|---|---|
| Default | die Standardliste des Flipper | eingebaut |
| 3D | ein 3D-Karussell aus Icons | portiert von @apfxtech, basierend auf dem 3D-OLED-Karussellmenü von @upiir |
| C64 | Commodore-64-Bildschirm | portiert von Momentum, von Sil (@Sil333033) |
| Compact | eine dichtere Liste | portiert von Momentum, von @MatthewKuKanich |
| CoverFlow | Karussell im Album-Cover-Stil | portiert von Momentum, von Cody Tolene (@CodyTolene), verfeinert von @956MB |
| DSi | Nintendo-DSi-Stil | portiert von Momentum, von Willy-JL |
| Grid | Icons in einem Raster | von @apfxtech |
| Macintosh | klassischer Mac-OS-Desktop | portiert von @apfxtech, basierend auf Ardutosh von @jhhoward |
| PS4 | PlayStation-4-Stil | portiert von Momentum, von Willy-JL |
| Vertical | vertikale Liste | portiert von Momentum, von Willy-JL |
| Wii | Nintendo-Wii-Kanalraster | portiert von Momentum, von Willy-JL |

In den Settings sind die Stile nach **Default** alphabetisch aufgelistet. In jedem Stil öffnet <kbd>OK</kbd> die
ausgewählte App und <kbd>Back</kbd> führt zurück zum Desktop.

## Wo die Stile liegen

Stile sind Loader-Plugins: `.fal`-Dateien mit dem Namen `menu_style_<name>.fal` in
`/ext/apps_data/loader/plugins/`. Die Liste **Menu Style** wird aus den dort gefundenen Dateien aufgebaut, daher:

- Stile brauchen die **SD-Karte**;
- ein Stil erscheint als **Missing**, wenn die ausgewählte Datei gelöscht wurde (installiere die Firmware neu, um
  sie wiederherzustellen), und als **Unknown**, wenn die Karte nicht gelesen werden konnte;
- wenn ein Stil nicht geladen werden kann, fällt der Flipper auf das Standardmenü zurück.

::: info Für Entwickler
Ein neuer Stil ist ein `FlipperAppType.PLUGIN` mit `requires=["loader"]` und einer `appid`, die mit
`menu_style_` beginnt; an diesem Präfix erkennen die Settings, welche Loader-Plugins im selben Ordner Menü-Stile
sind. Siehe `applications/system/menu_styles/` im Firmware-Quellcode und [App-Manifeste](/de/dev/app-manifests).
:::

## Verwandte Seiten

- [Desktop](/de/start/desktop)
- [Einstellungen](/de/start/settings)
- [Unleashed-Funktionen](/de/start/unleashed-features)
