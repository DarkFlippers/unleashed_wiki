---
title: Налаштування
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Налаштування

**Main Menu → Settings** містить такі пункти в тому порядку, у якому вони з'являються на пристрої:

**About** · **Bluetooth** · **Clock & Alarm** · **Desktop** · **Expansion Modules** · **Input** ·
**LCD and Notifications** · **Passport** · **Power** · **Storage** · **System**

У таких списках переміщайтеся клавішами <kbd>↑</kbd>/<kbd>↓</kbd>, змінюйте значення клавішами
<kbd>←</kbd>/<kbd>→</kbd>, а пункт із власним екраном відкривайте клавішею <kbd>OK</kbd>.

![Меню Settings: About, Bluetooth, Clock & Alarm, Desktop…](/screens/settings/menu.png)

::: tip Закріпіть налаштування в улюбленому
Утримуйте <kbd>OK</kbd> на будь-якому пункті переліку Settings, щоб закріпити його на вкладці **Favorites** в
Archive (або зняти звідти). Це дає швидкий доступ із робочого стола клавішею <kbd>↓</kbd>.
:::

::: info
Більшість застосунків налаштувань (About, Bluetooth, Clock & Alarm, Desktop, Expansion Modules, Input,
LCD and Notifications, Passport) — це файли `.fap`, які оновлення прошивки встановлює в `/ext/apps/assets/`.
**Power**, **Storage** і **System** вбудовані у прошивку й працюють навіть без SD-картки.
:::

## About

Інформаційні екрани. Переміщайтеся між ними через **Next** (<kbd>→</kbd>) і **Prev.** (<kbd>←</kbd>):

1. застереження **Unleashed Firmware**: лише для експериментальних цілей, не для незаконного використання;
2. ліцензія: прошивка безкоштовна й з відкритим кодом, а також *«If you paid any money for it - you got
   scammed.»*;
3. *«Community apps included in all builds except `c` build»* і посилання на github.com/DarkFlippers;
4. продукт, модель, FCC ID / IC;
5. посилання на відповідність нормам та адреса виробника;
6. **HW Version Info**: версія апаратної частини, регіон, ім'я Flipper, серійний номер;
7. **FW Version Info**: версія й дата збірки, git-хеш, версія API, radio stack, таргет і гілка.

## Bluetooth

| Пункт | Значення / дія |
|---|---|
| **Bluetooth** | `ON` / `OFF`. Показує `Broken`, якщо radio stack пошкоджений ([Відновлення](/ua/start/recovery)) |
| **Unpair All Devices** | Підтвердьте через **Unpair**. Видаляє всі спарювання, включно з ключами спарювання Bad USB через Bluetooth (BadKB), Bluetooth Remote і Authenticator |

Скористайтеся **Unpair All Devices**, якщо після встановлення прошивки чи зміни імені мобільний застосунок більше
не підключається. Див. [FAQ](/ua/start/faq).

## Clock & Alarm

Один екран із трьома рядками: **Time** (гг:хх:сс), **Date** (дд.мм.рррр) і **Alarm** (гг:хх, `On`/`Off`).

1. Виберіть рядок клавішами <kbd>↑</kbd>/<kbd>↓</kbd>, а поле — клавішами <kbd>←</kbd>/<kbd>→</kbd>.
2. Натисніть <kbd>OK</kbd>, щоб почати редагування, і змінюйте значення клавішами <kbd>↑</kbd>/<kbd>↓</kbd>.
3. Натисніть <kbd>OK</kbd> або <kbd>BACK</kbd>, щоб завершити редагування.

Коли дзвенить будильник, <kbd>BACK</kbd> **відкладає** його на 9 хвилин, а будь-яка інша кнопка вимикає. Будильник,
який ніхто не вимкнув, вимикається сам через 10 хвилин. Застосунок **Clock** у головному меню показує великий
годинник і має регулювання яскравості, будильник і таймер.

## Desktop

| Пункт | Значення | Опис |
|---|---|---|
| **PIN Setup** | → підменю | **Set PIN** / **Change PIN** / **Remove PIN**. PIN — це 4–10 натискань стрілок |
| **Auto Lock Time** | `OFF`, `10s`, `15s`, `30s`, `60s`, `90s`, `2min`, `5min`, `10min` | Блокування після бездіяльності |
| **Auto Lock disarm by active USB session** | `OFF` / `ON` | Без автоблокування, поки підключений USB |
| **Battery View** | `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %` | Стиль піктограми акумулятора |
| **Show Clock** | `OFF` / `ON` | Годинник на робочому столі |
| **Menu Style** | `Default` + встановлені стилі | Вигляд головного меню. Стилі — це плагіни `menu_style_*` у `/ext/apps_data/loader/plugins/`. Показує `Missing`, якщо файл вибраного стилю видалено |
| **Change Flipper Name** | текст | [Власне ім'я Фліппера](/ua/start/custom-name) |
| **Happy Mode** | Enable / Disable | Дельфін ніколи не сердиться ([Дельфін](/ua/start/dolphin)) |
| **Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long** | застосунок | Застосунки швидкого доступу з робочого стола |
| **DummyMode - Left / Left Long / Right / Right Long / Up Long / Down / Down Long / Ok / Ok Long** | застосунок | Застосунки для [Dummy Mode](/ua/start/desktop#dummy-mode) |

Для кожного слота Favorite/Dummy можна вибрати **Apps Menu (Default)** або **Passport (Default)**,
**None (disable)**, **Lock Flipper**, будь-який застосунок із головного меню чи **[Select App]**, щоб вибрати
будь-який `.fap` із `/ext/apps/`.

::: warning PIN
Екран налаштування попереджає: *«Forgotten PIN can only be reset with entire device.»* Скидання PIN-коду також
стирає ваші налаштування (файли на SD-картці зберігаються): див.
[Відновлення](/ua/start/recovery#reset-pin).
:::

::: tip Unleashed
Change Flipper Name, Battery View, Show Clock і 9 слотів Dummy Mode — доповнення Unleashed.
:::

## Expansion Modules

| Пункт | Значення | Опис |
|---|---|---|
| **Listen UART** | `USART` (піни 13, 14), `LPUART` (піни 15, 16), `None` | Який UART слухає модулі, що використовують протокол розширення (наприклад, [Video Game Module](/ua/gpio/video-game-module)) |

Установіть `None`, якщо такими модулями ви не користуєтеся. Це економить заряд і дозволяє Flipper засинати.

## Input

| Пункт | Значення | Опис |
|---|---|---|
| **Buttons Vibro** | `OFF`, `1`…`9` | Вібровідгук на події кнопок. Більші значення дають довший імпульс |
| **Vibro Trigger** | `Press`, `Release`, `Both` | Коли саме спрацьовує відгук |

## LCD and Notifications

| Пункт | Значення | Опис |
|---|---|---|
| **LCD Contrast** | `-10` … `+18` | Контрастність дисплея |
| **LCD Backlight** | `0%` … `100%` (крок 5 %) | Яскравість підсвітки |
| **Backlight Time** | `Always ON`, `2s`, `5s`, `10s`, `15s`, `30s`, `60s`, `90s`, `120s`, `5min`, `10min`, `30min` | Час до вимкнення підсвітки |
| **Night Shift** | `OFF`, `-10%` … `-60%` | Приглушує підсвітку на цю величину в нічному вікні |
| **. Start** | `17:00` … `23:30` | Початок нічного вікна (заблоковано, поки Night Shift у стані `OFF`) |
| **. End** | `05:00` … `11:30` | Кінець нічного вікна |
| **LED Brightness** | `0%` … `100%` | Яскравість світлодіода стану |
| **Volume** | `0%` … `100%` | Гучність динаміка (`Stealth`, коли звук приглушений з меню блокування) |
| **Vibro** | `OFF` / `ON` | Вібрація (`Stealth`, коли приглушена) |
| **LCD Inversion** | `OFF` / `ON` | Інвертує кольори дисплея |
| **RGB Mod Settings** | → підменю | Лише для Flipper з **апаратною модифікацією** RGB-підсвітки |

**RGB Mod Settings** (<kbd>OK</kbd> на пункті): **RGB backlight installed** (`OFF`/`ON`). Решта пунктів
залишаються заблокованими (`RGB MOD OFF!`), доки тут не буде `ON`: **LED 1 Color**, **LED 2 Color**,
**LED 3 Color**, **Effects** (`OFF`, `Rainbow`, `Wave`), **. Speed** (`0.1s`…`1s`),
**. Color step** (`1`–`3`), **. Saturation**, **. Wave wide** (`1`–`3`).

::: danger Модифікація RGB
Вмикайте **RGB backlight installed** **лише** тоді, коли у вашому Flipper справді є
[апаратна модифікація RGB-підсвітки](https://github.com/quen0n/flipperzero-firmware-rgb#readme). На стоковому
Flipper підсвітка перестане працювати. Якщо так сталося, повернітеся сюди й встановіть `OFF` (див.
[FAQ](/ua/start/faq#backlight-does-not-work)).
:::

## Passport

Профіль дельфіна: ім'я, настрій і рівень. Також відкривається клавішею <kbd>→</kbd> з робочого стола. Див.
[Дельфін](/ua/start/dolphin).

## Power

| Пункт | Значення | Опис |
|---|---|---|
| **Battery Info** | — | Заряд, напруга, струм, температура, стан здоров'я |
| **Reboot** | **Firmware Upgrade** / **Reboot Flipper** | Перезавантаження в режим DFU (`Reboot to DFU Mode?`) або звичайне перезавантаження |
| **Power OFF** | — | Вимкнути |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` | Вимкнення після бездіяльності |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` | Припиняти заряджання на цьому рівні |

Докладніше: [Живлення та акумулятор](/ua/start/power).

## Storage

| Пункт | Опис |
|---|---|
| **About Internal Storage** | Дані про внутрішнє сховище (`Virtual (/.int on SD)`) і вільну флеш-пам'ять |
| **About SD Card** | Мітка картки, тип, обсяг, вільне місце, виробник і серійний номер |
| **Unmount SD Card** / **Mount SD Card** | Безпечне виймання / повторне монтування |
| **Format SD Card** | Стерти й відформатувати картку |
| **Benchmark SD Card** | Тест швидкості по SPI |
| **Factory Reset** | Натисніть **Erase** 5 разів. Стирає внутрішнє сховище й перезавантажує пристрій |

Докладніше: [Картка microSD](/ua/start/sd-card), [Відновлення](/ua/start/recovery#factory-reset).

## System

| Пункт | Значення | Опис |
|---|---|---|
| **Hand Orient** | `Righty` / `Lefty` | Режим для лівшів: повертає екран і перевизначає кнопки |
| **Units** | `Metric` / `Imperial` | Одиниці (наприклад, °C/°F у Battery Info) |
| **Time Format** | `24h` / `12h` | Формат годинника |
| **Date Format** | `D/M/Y`, `M/D/Y`, `Y/M/D` | Формат дати |
| **Log Level** | `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace` | Скільки пишеться в логи. `Default` = `Info` |
| **Log Device** | `USART`, `LPUART`, `None` | UART для логів (USART = піни 13/14, LPUART = піни 15/16) |
| **Log Baud Rate** | `9600` … `1843200` | Швидкість UART для логів |
| **Debug** | `OFF` / `ON` | Режим Debug: додаткові відлагоджувальні можливості в застосунках, вкладка **Internal** в Archive, доступ по SWD |
| **Heap Trace** | `None`, `Main` | Трасування виділення пам'яті (для розробників) |
| **Sleep Method** | `Default` / `Legacy` | `Legacy` споживає більше (~9 мА проти ~1,5 мА), але може бути стабільнішим |
| **File Naming** | `Default` / `Detailed` | `Detailed` додає тип, дату й час до імен нових файлів |

![Settings → System: Hand Orient Righty, Units Metric, Time Format 24h, Date Format D/M/Y…](/screens/settings/system.png)

До **Debug** є швидший шлях: утримуйте <kbd>↓</kbd> на робочому столі, а потім утримуйте <kbd>OK</kbd> на
інформаційному екрані ([Робочий стіл → Інформаційний екран пристрою](/ua/start/desktop#info-screen)).

::: warning Flipper працює повільно?
Для звичайного використання тримайте **Log Level** = `None` (або `Default`), **Debug** = `OFF` і
**Heap Trace** = `None`. Відлагоджувальні налаштування вповільнюють пристрій і не дають йому засинати.
:::

## Пов'язані сторінки

- [Робочий стіл](/ua/start/desktop): що налаштування робочого стола роблять на практиці
- [Власне ім'я Фліппера](/ua/start/custom-name)
- [Налаштування Sub-GHz](/ua/subghz/settings): налаштування радіо всередині застосунку Sub-GHz
