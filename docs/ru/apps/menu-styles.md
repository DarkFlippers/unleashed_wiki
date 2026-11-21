---
title: Стили главного меню
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/menu_styles, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-src]
---
# Стили главного меню

::: tip Unleashed
В Unleashed можно поменять внешний вид **главного меню** (списка, который открывается по <kbd>OK</kbd> на рабочем
столе). Каждый вариант оформления — небольшой плагин, поставляемый вместе с прошивкой; в стоковой прошивке есть
только стандартный список.
:::

## Выбор стиля

1. Откройте `Main Menu → Settings → Desktop`.
2. Пролистайте до пункта **Menu Style**.
3. Кнопками <kbd>←</kbd> / <kbd>→</kbd> выберите стиль. **Default** — стандартное меню.
4. Выйдите из настроек и нажмите <kbd>OK</kbd> на рабочем столе: меню откроется в новом стиле.

## Доступные стили

| Стиль | Как выглядит | Происхождение |
|---|---|---|
| Default | стандартный список Флиппера | встроенный |
| 3D | 3D-карусель иконок | портировал @apfxtech, на основе 3D OLED carousel menu от @upiir |
| C64 | экран Commodore 64 | портирован из Momentum, автор Sil (@Sil333033) |
| Compact | более плотный список | портирован из Momentum, автор @MatthewKuKanich |
| CoverFlow | карусель в стиле обложек альбомов | портирован из Momentum, автор Cody Tolene (@CodyTolene), доработал @956MB |
| DSi | в стиле Nintendo DSi | портирован из Momentum, автор Willy-JL |
| Grid | иконки сеткой | автор @apfxtech |
| Macintosh | рабочий стол классической Mac OS | портировал @apfxtech, на основе Ardutosh от @jhhoward |
| PS4 | в стиле PlayStation 4 | портирован из Momentum, автор Willy-JL |
| Vertical | вертикальный список | портирован из Momentum, автор Willy-JL |
| Wii | сетка каналов Nintendo Wii | портирован из Momentum, автор Willy-JL |

В настройках стили идут по алфавиту после **Default**. В любом стиле <kbd>OK</kbd> открывает выбранное приложение,
а <kbd>Back</kbd> возвращает на рабочий стол.

## Где лежат стили

Стили — это плагины загрузчика: файлы `.fal` с именами `menu_style_<name>.fal` в `/ext/apps_data/loader/plugins/`.
Список **Menu Style** строится из найденных там файлов, поэтому:

- для стилей нужна **SD-карта**;
- стиль отображается как **Missing**, если выбранный файл удалён (переустановите прошивку, чтобы вернуть его), и как
  **Unknown**, если карту не удалось прочитать;
- если стиль не загрузился, Флиппер откатывается на стандартное меню.

::: info Для разработчиков
Новый стиль — это `FlipperAppType.PLUGIN` с `requires=["loader"]` и `appid`, начинающимся с `menu_style_`; по этому
префиксу настройки отличают стили меню от других плагинов загрузчика в той же папке. Смотрите
`applications/system/menu_styles/` в исходниках прошивки и [Манифесты приложений](/ru/dev/app-manifests).
:::

## Связанные страницы

- [Рабочий стол](/ru/start/desktop)
- [Настройки](/ru/start/settings)
- [Возможности Unleashed](/ru/start/unleashed-features)
