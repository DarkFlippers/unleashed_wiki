---
title: Stilovi glavnog izbornika
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/menu_styles, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-src]
---
# Stilovi glavnog izbornika

::: tip Unleashed
Unleashed omogućuje promjenu načina prikaza **glavnog izbornika** (popisa koji dobijete pritiskom na <kbd>OK</kbd> na radnoj površini).
Svaki izgled je mali dodatak koji dolazi uz firmver; tvornički firmver ima samo zadani popis.
:::

## Odabir stila

1. Otvorite `Main Menu → Settings → Desktop`.
2. Pomaknite se do **Menu Style**.
3. Pritisnite <kbd>←</kbd> / <kbd>→</kbd> za odabir stila. **Default** je standardni izbornik.
4. Napustite Settings i pritisnite <kbd>OK</kbd> na radnoj površini: izbornik se otvara u novom stilu.

## Dostupni stilovi

| Stil | Izgled | Podrijetlo |
|---|---|---|
| Default | standardni Flipperov popis | ugrađeno |
| 3D | 3D vrtuljak ikona | portao @apfxtech, temeljeno na 3D OLED vrtuljak izborniku autora @upiir |
| C64 | zaslon računala Commodore 64 | portano iz Momentuma, autor Sil (@Sil333033) |
| Compact | zbijeniji popis | portano iz Momentuma, autor @MatthewKuKanich |
| CoverFlow | vrtuljak u stilu omota albuma | portano iz Momentuma, autor Cody Tolene (@CodyTolene), doradio @956MB |
| DSi | stil Nintendo DSi | portano iz Momentuma, autor Willy-JL |
| Grid | ikone u mreži | autor @apfxtech |
| Macintosh | klasična radna površina Mac OS-a | portao @apfxtech, temeljeno na Ardutoshu autora @jhhoward |
| PS4 | stil PlayStation 4 | portano iz Momentuma, autor Willy-JL |
| Vertical | okomiti popis | portano iz Momentuma, autor Willy-JL |
| Wii | mreža kanala Nintendo Wii | portano iz Momentuma, autor Willy-JL |

U postavkama (Settings) stilovi su poredani abecednim redom nakon **Default**. U svakom stilu <kbd>OK</kbd> otvara odabranu
aplikaciju, a <kbd>Back</kbd> vraća na radnu površinu.

## Gdje se stilovi nalaze

Stilovi su dodaci učitavača (loader plugins): `.fal` datoteke pod nazivom `menu_style_<name>.fal` u `/ext/apps_data/loader/plugins/`.
Popis **Menu Style** gradi se od datoteka pronađenih na toj lokaciji, pa stoga:

- stilovi zahtijevaju **SD karticu**;
- stil se prikazuje kao **Missing** ako je odabrana datoteka izbrisana (ponovno instalirajte firmver da biste ga vratili), a
  **Unknown** ako kartica nije mogla biti pročitana;
- ako se stil ne uspije učitati, Flipper se vraća na zadani izbornik.

::: info Za programere
Novi stil je `FlipperAppType.PLUGIN` s `requires=["loader"]` i `appid` koji počinje s `menu_style_`; taj
prefiks Settings koristi za razlikovanje stilova izbornika od ostalih dodataka učitavača u istoj mapi. Pogledajte
`applications/system/menu_styles/` u izvornom kodu firmvera i [Manifesti aplikacija](/hr/dev/app-manifests).
:::

## Povezane stranice

- [Radna površina](/hr/start/desktop)
- [Postavke](/hr/start/settings)
- [Značajke Unleasheda](/hr/start/unleashed-features)
