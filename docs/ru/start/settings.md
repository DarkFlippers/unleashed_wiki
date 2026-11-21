---
title: Настройки
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Настройки

В **Main Menu → Settings** такие пункты (в том порядке, в каком они идут на устройстве):

**About** · **Bluetooth** · **Clock & Alarm** · **Desktop** · **Expansion Modules** · **Input** ·
**LCD and Notifications** · **Passport** · **Power** · **Storage** · **System**

В таких списках <kbd>↑</kbd>/<kbd>↓</kbd> перемещают по пунктам, <kbd>←</kbd>/<kbd>→</kbd> меняют значение,
<kbd>OK</kbd> открывает пункт с подменю.

![Меню Settings: About, Bluetooth, Clock & Alarm, Desktop…](/screens/settings/menu.png)

::: tip Закрепить настройку в избранном
Зажмите <kbd>OK</kbd> на любом пункте списка Settings, чтобы закрепить его во вкладке **Favorites** в Archive (или
открепить). Так его можно быстро открыть с рабочего стола через <kbd>↓</kbd>.
:::

::: info
Большинство приложений настроек (About, Bluetooth, Clock & Alarm, Desktop, Expansion Modules, Input,
LCD and Notifications, Passport) — это файлы `.fap`, которые обновление прошивки ставит в `/ext/apps/assets/`.
**Power**, **Storage** и **System** встроены в прошивку и работают даже без SD-карты.
:::

## About

Информационные экраны, листаются кнопками **Next** (<kbd>→</kbd>) и **Prev.** (<kbd>←</kbd>):

1. предупреждение **Unleashed Firmware**: только для экспериментов, не для незаконного использования;
2. лицензия: прошивка бесплатная и открытая, *«If you paid any money for it - you got scammed.»* («Если вы за неё
   заплатили — вас обманули»);
3. *«Community apps included in all builds except `c` build»* и ссылка на github.com/DarkFlippers;
4. продукт, модель, FCC ID / IC;
5. ссылка на сертификаты и адрес производителя;
6. **HW Version Info**: версия железа, регион, имя Флиппера, серийный номер;
7. **FW Version Info**: версия и дата сборки, git-хэш, версия API, радиостек, платформа и ветка.

## Bluetooth

| Пункт | Значения / действие |
|---|---|
| **Bluetooth** | `ON` / `OFF`. Показывает `Broken`, если радиостек повреждён ([Восстановление](/ru/start/recovery)) |
| **Unpair All Devices** | Подтверждение — **Unpair**. Удаляет все сопряжения, включая ключи Bad USB по Bluetooth (BadKB), Bluetooth Remote и Authenticator |

**Unpair All Devices** помогает, если мобильное приложение перестало подключаться после установки или смены имени
(см. [FAQ](/ru/start/faq)).

## Clock & Alarm

Один экран с тремя строками: **Time** (чч:мм:сс), **Date** (дд.мм.гггг) и **Alarm** (чч:мм, `On`/`Off`).

1. <kbd>↑</kbd>/<kbd>↓</kbd> — выбор строки, <kbd>←</kbd>/<kbd>→</kbd> — выбор поля.
2. <kbd>OK</kbd> — режим редактирования, значение меняется <kbd>↑</kbd>/<kbd>↓</kbd>.
3. <kbd>OK</kbd> или <kbd>BACK</kbd> — выход из редактирования.

Когда звонит будильник, <kbd>BACK</kbd> **откладывает** его на 9 минут, любая другая кнопка — выключает. Если
будильник никто не остановил, через 10 минут он выключится сам. Приложение **Clock** в главном меню показывает
крупные часы и умеет регулировать яркость, ставить будильник и таймер.

## Desktop

| Пункт | Значения | Описание |
|---|---|---|
| **PIN Setup** | → подменю | **Set PIN** / **Change PIN** / **Remove PIN**. PIN — от 4 до 10 нажатий стрелок |
| **Auto Lock Time** | `OFF`, `10s`, `15s`, `30s`, `60s`, `90s`, `2min`, `5min`, `10min` | Автоблокировка после бездействия |
| **Auto Lock disarm by active USB session** | `OFF` / `ON` | Не блокировать, пока подключён USB |
| **Battery View** | `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %` | Вид значка батареи |
| **Show Clock** | `OFF` / `ON` | Часы на рабочем столе |
| **Menu Style** | `Default` + установленные стили | Вид главного меню. Стили — плагины `menu_style_*` в `/ext/apps_data/loader/plugins/`. `Missing` — выбранный файл стиля удалён |
| **Change Flipper Name** | текст | [Своё имя Флиппера](/ru/start/custom-name) |
| **Happy Mode** | Enable / Disable | Дельфин никогда не злится ([Дельфин](/ru/start/dolphin)) |
| **Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long** | приложение | Быстрый запуск с рабочего стола |
| **DummyMode - Left / Left Long / Right / Right Long / Up Long / Down / Down Long / Ok / Ok Long** | приложение | Приложения для [Dummy Mode](/ru/start/desktop#dummy-mode) |

Для каждого слота Favorite/Dummy можно выбрать **Apps Menu (Default)** или **Passport (Default)**,
**None (disable)**, **Lock Flipper**, любое приложение главного меню или **[Select App]** — любой `.fap` из `/ext/apps/`.

::: warning PIN
На экране настройки PIN предупреждение: *«Forgotten PIN can only be reset with entire device.»* Сброс PIN стирает и
настройки (файлы на SD-карте сохраняются): см. [Восстановление](/ru/start/recovery#reset-pin).
:::

::: tip Unleashed
Change Flipper Name, Battery View, Show Clock и 9 слотов Dummy Mode — дополнения Unleashed.
:::

## Expansion Modules

| Пункт | Значения | Описание |
|---|---|---|
| **Listen UART** | `USART` (выводы 13, 14), `LPUART` (выводы 15, 16), `None` | На каком UART слушать модули с протоколом расширения (например, [Video Game Module](/ru/gpio/video-game-module)) |

Если такие модули не используете, ставьте `None` — так Флиппер экономит энергию и может засыпать.

## Input

| Пункт | Значения | Описание |
|---|---|---|
| **Buttons Vibro** | `OFF`, `1`…`9` | Вибрация при нажатии кнопок. Чем больше число, тем длиннее импульс |
| **Vibro Trigger** | `Press`, `Release`, `Both` | Когда срабатывает вибрация |

## LCD and Notifications

| Пункт | Значения | Описание |
|---|---|---|
| **LCD Contrast** | `-10` … `+18` | Контраст экрана |
| **LCD Backlight** | `0%` … `100%` (шаг 5 %) | Яркость подсветки |
| **Backlight Time** | `Always ON`, `2s`, `5s`, `10s`, `15s`, `30s`, `60s`, `90s`, `120s`, `5min`, `10min`, `30min` | Время до отключения подсветки |
| **Night Shift** | `OFF`, `-10%` … `-60%` | На сколько приглушать подсветку ночью |
| **. Start** | `17:00` … `23:30` | Начало ночного периода (заблокировано, пока Night Shift = `OFF`) |
| **. End** | `05:00` … `11:30` | Конец ночного периода |
| **LED Brightness** | `0%` … `100%` | Яркость светодиода |
| **Volume** | `0%` … `100%` | Громкость (`Stealth`, если звук выключен через Lock Menu) |
| **Vibro** | `OFF` / `ON` | Вибрация (`Stealth`, если выключена через Lock Menu) |
| **LCD Inversion** | `OFF` / `ON` | Инверсия цветов экрана |
| **RGB Mod Settings** | → подменю | Только для Флипперов с **аппаратным** RGB-модом подсветки |

**RGB Mod Settings** (<kbd>OK</kbd> на пункте): **RGB backlight installed** (`OFF`/`ON`). Остальные пункты заблокированы
(`RGB MOD OFF!`), пока он не включён: **LED 1 Color**, **LED 2 Color**, **LED 3 Color**, **Effects** (`OFF`,
`Rainbow`, `Wave`), **. Speed** (`0.1s`…`1s`), **. Color step** (`1`–`3`), **. Saturation**, **. Wave wide** (`1`–`3`).

::: danger RGB-мод
Включайте **RGB backlight installed** **только** если на Флиппере стоит
[аппаратный RGB-мод подсветки](https://github.com/quen0n/flipperzero-firmware-rgb#readme). На обычном Флиппере
подсветка перестанет работать. Если так случилось, вернитесь сюда и поставьте `OFF`
(см. [FAQ](/ru/start/faq#backlight-does-not-work)).
:::

## Passport

Профиль дельфина: имя, настроение и уровень. Также открывается <kbd>→</kbd> на рабочем столе. См. [Дельфин](/ru/start/dolphin).

## Power

| Пункт | Значения | Описание |
|---|---|---|
| **Battery Info** | — | Заряд, напряжение, ток, температура, здоровье батареи |
| **Reboot** | **Firmware Upgrade** / **Reboot Flipper** | Перезагрузка в DFU (`Reboot to DFU Mode?`) или обычная |
| **Power OFF** | — | Выключение |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` | Выключение после бездействия |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` | Остановка зарядки на этом уровне |

Подробнее: [Питание и аккумулятор](/ru/start/power).

## Storage

| Пункт | Описание |
|---|---|
| **About Internal Storage** | Сведения о внутреннем хранилище (`Virtual (/.int on SD)`) и свободной flash-памяти |
| **About SD Card** | Метка, тип, объём, свободное место, производитель и серийный номер карты |
| **Unmount SD Card** / **Mount SD Card** | Безопасное извлечение / повторное монтирование |
| **Format SD Card** | Стереть и отформатировать карту |
| **Benchmark SD Card** | Тест скорости по SPI |
| **Factory Reset** | Нажать **Erase** 5 раз. Стирает внутреннее хранилище и перезагружает устройство |

Подробнее: [microSD-карта](/ru/start/sd-card), [Восстановление](/ru/start/recovery#factory-reset).

## System

| Пункт | Значения | Описание |
|---|---|---|
| **Hand Orient** | `Righty` / `Lefty` | Режим для левши: экран переворачивается, кнопки переназначаются |
| **Units** | `Metric` / `Imperial` | Единицы измерения (например, °C/°F в Battery Info) |
| **Time Format** | `24h` / `12h` | Формат времени |
| **Date Format** | `D/M/Y`, `M/D/Y`, `Y/M/D` | Формат даты |
| **Log Level** | `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace` | Подробность логов. `Default` = `Info` |
| **Log Device** | `USART`, `LPUART`, `None` | UART для логов (USART — выводы 13/14, LPUART — 15/16) |
| **Log Baud Rate** | `9600` … `1843200` | Скорость UART для логов |
| **Debug** | `OFF` / `ON` | Режим отладки: доп. отладочные функции в приложениях, вкладка **Internal** в Archive, доступ по SWD |
| **Heap Trace** | `None`, `Main` | Трассировка выделения памяти (для разработчиков) |
| **Sleep Method** | `Default` / `Legacy` | `Legacy` потребляет больше (~9 мА против ~1,5 мА), но может быть стабильнее |
| **File Naming** | `Default` / `Detailed` | `Detailed` добавляет в имена новых файлов тип, дату и время |

![Settings → System: Hand Orient Righty, Units Metric, Time Format 24h, Date Format D/M/Y…](/screens/settings/system.png)

У **Debug** есть быстрый путь: долгое нажатие <kbd>↓</kbd> на рабочем столе, затем долгое <kbd>OK</kbd> на
информационном экране ([Рабочий стол → Информационный экран](/ru/start/desktop#info-screen)).

::: warning Флиппер тормозит?
Для обычной работы держите **Log Level** = `None` (или `Default`), **Debug** = `OFF` и **Heap Trace** = `None`.
Отладочные настройки замедляют устройство и не дают ему засыпать.
:::

## См. также

- [Рабочий стол](/ru/start/desktop) — как настройки рабочего стола работают на практике
- [Своё имя Флиппера](/ru/start/custom-name)
- [Настройки Sub-GHz](/ru/subghz/settings) — радионастройки внутри приложения Sub-GHz
