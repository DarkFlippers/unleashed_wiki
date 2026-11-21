---
title: Стилі головного меню
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/menu_styles, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-src]
---
# Стилі головного меню

::: tip Unleashed
Unleashed дозволяє змінити вигляд **головного меню** (список, що відкривається натисканням <kbd>OK</kbd> на робочому
столі). Кожен вигляд — це невеликий плагін, що постачається разом із прошивкою; у стоковій прошивці є лише типовий
список.
:::

## Вибір стилю

1. Відкрийте `Main Menu → Settings → Desktop`.
2. Прокрутіть до **Menu Style**.
3. Натискайте <kbd>←</kbd> / <kbd>→</kbd>, щоб обрати стиль. **Default** — стандартне меню.
4. Вийдіть із налаштувань і натисніть <kbd>OK</kbd> на робочому столі: меню відкриється в новому стилі.

## Доступні стилі

| Стиль | Як виглядає | Походження |
|---|---|---|
| Default | стандартний список Flipper | вбудований |
| 3D | 3D-карусель піктограм | портував @apfxtech, на основі 3D OLED carousel menu від @upiir |
| C64 | екран Commodore 64 | портовано з Momentum, автор Sil (@Sil333033) |
| Compact | щільніший список | портовано з Momentum, автор @MatthewKuKanich |
| CoverFlow | карусель у стилі обкладинок альбомів | портовано з Momentum, автор Cody Tolene (@CodyTolene), доопрацював @956MB |
| DSi | у стилі Nintendo DSi | портовано з Momentum, автор Willy-JL |
| Grid | піктограми сіткою | автор @apfxtech |
| Macintosh | робочий стіл класичної Mac OS | портував @apfxtech, на основі Ardutosh від @jhhoward |
| PS4 | у стилі PlayStation 4 | портовано з Momentum, автор Willy-JL |
| Vertical | вертикальний список | портовано з Momentum, автор Willy-JL |
| Wii | сітка каналів Nintendo Wii | портовано з Momentum, автор Willy-JL |

У налаштуваннях стилі йдуть за алфавітом після **Default**. У будь-якому стилі <kbd>OK</kbd> відкриває вибраний
застосунок, а <kbd>Back</kbd> повертає на робочий стіл.

## Де лежать стилі

Стилі — це плагіни завантажувача: файли `.fal` з назвами `menu_style_<name>.fal` у
`/ext/apps_data/loader/plugins/`. Список **Menu Style** будується з файлів, знайдених у цій папці, тому:

- стилям потрібна **SD-карта**;
- стиль показується як **Missing**, якщо вибраний файл видалено (щоб відновити його, перевстановіть прошивку), і
  **Unknown**, якщо картку не вдалося прочитати;
- якщо стиль не завантажується, Flipper повертається до типового меню.

::: info Для розробників
Новий стиль — це `FlipperAppType.PLUGIN` з `requires=["loader"]` та `appid`, що починається на `menu_style_`; саме за
цим префіксом налаштування відрізняють стилі меню від інших плагінів завантажувача в тій самій папці. Див.
`applications/system/menu_styles/` у вихідному коді прошивки та [Маніфести застосунків](/ua/dev/app-manifests).
:::

## Пов’язані сторінки

- [Робочий стіл](/ua/start/desktop)
- [Налаштування](/ua/start/settings)
- [Можливості Unleashed](/ua/start/unleashed-features)
