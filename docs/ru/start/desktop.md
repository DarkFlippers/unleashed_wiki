---
title: Рабочий стол
order: 60
original: [https://docs.flipper.net/zero/basics/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Рабочий стол

Рабочий стол (Desktop) — главный экран. Здесь живёт [дельфин](/ru/start/dolphin), а сверху идёт строка состояния.
Одиночные нажатия кнопок с рабочего стола открывают главное меню, Archive, Lock Menu и избранные приложения.

## Строка состояния

В верхней строке — небольшие значки:

| Значок | Значение |
|---|---|
| Батарея | Уровень заряда. Во время зарядки — молния. Вид задаётся в `Battery View` |
| SD-карта | microSD смонтирована. Перечёркнутый значок — карта не смонтировалась, см. [microSD-карта](/ru/start/sd-card) |
| Bluetooth | BLE включён. Другой значок — устройство подключено |
| Замок | Флиппер заблокирован |
| Перечёркнутый динамик | Режим Stealth: без звука и вибрации (см. [Lock Menu](#lock-menu)) |
| ПК | Подключён к qFlipper / Flipper Lab по USB |
| Геймпад | Включён Dummy Mode |
| Модуль | Подключён модуль расширения |
| Маячок | Режим BLE-маячка (например, FindMy Flipper) |
| Фоновое приложение | В фоне работает приложение |

::: tip Unleashed
- **Settings → Desktop → Battery View** — вид батареи: `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %`.
- **Settings → Desktop → Show Clock** = `ON` — часы на рабочем столе. Формат (24h/12h) берётся из
  **Settings → System → Time Format**.
:::

## Кнопки на рабочем столе

| Кнопка | Короткое нажатие | Долгое нажатие |
|---|---|---|
| <kbd>OK</kbd> | **Main Menu** | Favorite App - Ok Long |
| <kbd>↑</kbd> | **Lock Menu** | **Блокировка** (с PIN, если задан) |
| <kbd>↓</kbd> | **Archive** | Информация об устройстве / отладочный экран |
| <kbd>←</kbd> | Favorite App - Left Short (по умолчанию меню **Apps**) | Favorite App - Left Long |
| <kbd>→</kbd> | По умолчанию **Passport** (Favorite App - Right Short) | Favorite App - Right Long |
| <kbd>BACK</kbd> | — | Экран **выключения** |

### Информационный экран {#info-screen}

Долгое нажатие <kbd>↓</kbd> открывает информационный экран: версия и дата сборки прошивки, версия железа, время работы,
имя Флиппера и состояние Debug (`ON`/`OFF`).

![Информационный экран: версия прошивки, версия железа, время работы и состояние Debug](/screens/desktop/debug.png)

На этом экране **долгое нажатие <kbd>OK</kbd> включает и выключает Debug** — тот же переключатель, что
`Settings → System → Debug` ([Настройки](/ru/start/settings)), только без ходьбы по меню. Короткое
<kbd>BACK</kbd> возвращает на рабочий стол.

Debug = `ON` добавляет пункты, которые иначе скрыты: вкладку **Internal** в [Archive](#archive) и
`Signal Settings` в меню сохранённого сигнала Sub-GHz ([Signal Settings](/ru/subghz/signal-settings)). Потом выключите
его обратно — отладочные настройки замедляют Флиппер и не дают ему засыпать.

## Главное меню

Нажмите <kbd>OK</kbd>. Главное меню открывается на пункте **Apps** (все `.fap`-приложения с SD-карты
по категориям), далее идут **Sub-GHz**, **125 kHz RFID**, **NFC**, **Infrared**, **GPIO**, **iButton**,
**Bad USB**, **U2F**, **Clock**, а **Settings** — последним. Список закольцован: нажатие <kbd>↑</kbd>
на **Apps** сразу переводит к **Settings**.

![Главное меню: выбран Apps, выше — Settings, ниже — Sub-GHz](/screens/mainmenu/main.png)

::: tip Стили меню
**Settings → Desktop → Menu Style** меняет вид главного меню. Стили — это плагины в `/ext/apps_data/loader/plugins/`
(файлы, начинающиеся с `menu_style_`). `Default` — встроенный список.
:::

## Lock Menu {#lock-menu}

Нажмите <kbd>↑</kbd> на рабочем столе. Выбор — <kbd>↑</kbd>/<kbd>↓</kbd>, действие — <kbd>OK</kbd>:

| Пункт | Что делает |
|---|---|
| **Turn Bluetooth On / Off** | Включает и выключает BLE без захода в настройки |
| **Mute / Unmute** | Режим Stealth: без звука и вибрации. Пока он включён, **Volume** и **Vibro** в настройках показывают `Stealth` |
| **Dummy Mode / Default Mode** | Вход в [Dummy Mode](#dummy-mode) и выход из него |

<kbd>←</kbd> или <kbd>→</kbd> в Lock Menu открывают вторую страницу — **Quick Settings**:

| Пункт | Управление |
|---|---|
| Brightness | <kbd>OK</kbd> — редактировать, затем <kbd>←</kbd>/<kbd>→</kbd> (или <kbd>↑</kbd>/<kbd>↓</kbd>), шаг 5 % |
| Volume | Так же. Звучит короткий сигнал, чтобы оценить громкость на слух |
| Vibro | <kbd>OK</kbd> переключает сразу |

<kbd>BACK</kbd> выходит из редактирования пункта, повторное <kbd>BACK</kbd> — со страницы. Изменения попадают в те же
настройки, что и **LCD and Notifications**.

::: tip Unleashed
В Unleashed **сама блокировка** — долгое нажатие <kbd>↑</kbd> на рабочем столе: с PIN, если он задан, иначе обычная
блокировка.
:::

## Блокировка и PIN

- **Блокировка:** зажмите <kbd>↑</kbd> на рабочем столе. Без PIN блокируются кнопки. **Для разблокировки быстро
  нажмите <kbd>BACK</kbd> три раза.**
- **С PIN:** задаётся в **Settings → Desktop → PIN Setup → Set PIN**. PIN — от 4 до 10 нажатий стрелок. Заблокированный
  Флиппер будет спрашивать PIN. После неверных попыток появляется `Wrong PIN!` и таймаут до следующей попытки.
- **Автоблокировка:** **Settings → Desktop → Auto Lock Time** (`OFF`, `10s` … `10min`) блокирует устройство после
  указанного времени бездействия. **Auto Lock disarm by active USB session** = `ON` отключает автоблокировку, пока
  Флиппер подключён по USB.

::: warning Забыли PIN
Забытый PIN сбрасывается только вместе со всеми пользовательскими настройками:
[Восстановление → Сброс забытого PIN](/ru/start/recovery#reset-pin). Файлы на microSD сохраняются.
:::

## Dummy Mode {#dummy-mode}

Dummy Mode превращает Флиппер в игрушку: большинство функций скрыто, а кнопки запускают выбранные вами приложения,
например игры. Включается через **Lock Menu → Dummy Mode**, выключается через **Lock Menu → Default Mode**.

В Dummy Mode каждая кнопка может запускать своё приложение. Назначьте их в **Settings → Desktop**:

`DummyMode - Left`, `- Left Long`, `- Right`, `- Right Long`, `- Up Long`, `- Down`, `- Down Long`, `- Ok`, `- Ok Long`.

Кнопка без назначения открывает Passport. Короткое <kbd>↑</kbd> по-прежнему открывает Lock Menu. Если для
`DummyMode - Up Long` выбрано `None`, долгое <kbd>↑</kbd> блокирует устройство.

::: tip Unleashed
В стоковой прошивке в Dummy Mode 4 ярлыка, в Unleashed — 9 (короткое и долгое нажатие каждой кнопки). Несколько игр
всегда под рукой.
:::

## Избранные приложения (быстрый запуск)

**Settings → Desktop → Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long**

Для каждого слота можно выбрать:
- **Apps Menu (Default)** или **Passport (Default)** — встроенное значение по умолчанию для этого слота;
- **None (disable)** — кнопка ничего не делает;
- **Lock Flipper**;
- любое приложение из главного меню;
- **[Select App]** — любой `.fap` из `/ext/apps/`.

## Archive

Нажмите <kbd>↓</kbd>. Archive показывает сохранённые файлы по вкладкам. Вкладки переключаются <kbd>←</kbd>/<kbd>→</kbd>:

| Вкладка | Папка / содержимое |
|---|---|
| Favorites | Закреплённые файлы |
| iButton | `/ext/ibutton` (`.ibtn`) |
| NFC | `/ext/nfc` (`.nfc`) |
| Sub-GHz | `/ext/subghz` (`.sub`) |
| SubRem | `/ext/subghz_remote` — карты Sub-GHz Remote |
| RFID LF | `/ext/lfrfid` (`.rfid` и дампы T5577) |
| Infrared | `/ext/infrared` (`.ir`) |
| Bad USB | `/ext/badusb` (`.txt`) |
| Phone | `/ext/phonebook` — телефонная книга SIM800 (`.phone`) |
| U2F | U2F-токен |
| Apps | `/ext/apps` (`.fap` и `.js`) |
| Internal | Внутреннее хранилище (только при **Debug** = `ON`) |
| Browser | Вся microSD-карта |

<kbd>OK</kbd> на файле открывает контекстное меню: запуск/эмуляция, **Pin**/**Unpin** (добавить в избранное),
**Rename**, **Delete**, а во вкладке Browser ещё **Cut**, **Copy**, **Paste** и **NewDir**. Во вкладке Favorites
меню открывается удержанием <kbd>OK</kbd>.

::: tip Закрепить настройку в избранном
В **Main Menu → Settings** зажмите <kbd>OK</kbd> на любом пункте, чтобы закрепить его в Favorites. Потом его можно
открывать из Archive без хождения по меню.
:::

## Passport

Нажмите <kbd>→</kbd> на рабочем столе или откройте **Settings → Passport**. Здесь имя дельфина (имя Флиппера),
настроение и уровень: см. [Дельфин](/ru/start/dolphin).
