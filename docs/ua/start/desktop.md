---
title: Робочий стіл
order: 60
original: [https://docs.flipper.net/zero/basics/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Робочий стіл

Робочий стіл — це домашній екран. Тут живе ваш [дельфін](/ua/start/dolphin), а вгорі тягнеться рядок стану.
З робочого стола одним натисканням кнопки відкриваються головне меню, Archive, Lock Menu та улюблені застосунки.

## Рядок стану

У верхньому рядку показуються невеликі піктограми:

| Піктограма | Що означає |
|---|---|
| Акумулятор | Рівень заряду. Під час заряджання показує блискавку. Вигляд задається параметром `Battery View` |
| Картка SD | Картка microSD змонтована. Перекреслена піктограма означає, що картку не вдалося змонтувати: див. [Картка microSD](/ua/start/sd-card) |
| Bluetooth | BLE увімкнено. Інша піктограма означає, що пристрій підключено |
| Замок | Фліппер заблокований |
| Перекреслений гучномовець | Беззвучний режим: звук і вібрація вимкнені (див. [Lock Menu](#lock-menu)) |
| ПК | Підключено до qFlipper / Flipper Lab по USB |
| Геймпад | Увімкнено Dummy Mode |
| Модуль | Під’єднано модуль розширення |
| Маяк | Режим BLE-маяка (наприклад, FindMy Flipper) |
| Фоновий застосунок | У фоні працює застосунок |

::: tip Unleashed
- **Settings → Desktop → Battery View** вибирає вигляд індикатора заряду: `Bar`, `%`, `Inv. %`, `Retro 3`,
  `Retro 5`, `Bar %`.
- **Settings → Desktop → Show Clock** = `ON` показує час на робочому столі. Формат (24- чи 12-годинний) береться з
  **Settings → System → Time Format**.
:::

## Кнопки на робочому столі

| Кнопка | Коротке натискання | Довге натискання |
|---|---|---|
| <kbd>OK</kbd> | **Main Menu** | Favorite App - Ok Long |
| <kbd>↑</kbd> | **Lock Menu** | **Блокування** (з PIN-кодом, якщо він заданий) |
| <kbd>↓</kbd> | **Archive** | Інформація про пристрій / службовий екран |
| <kbd>←</kbd> | Favorite App - Left Short (типово меню **Apps**) | Favorite App - Left Long |
| <kbd>→</kbd> | Типово **Passport** (Favorite App - Right Short) | Favorite App - Right Long |
| <kbd>BACK</kbd> | — | Екран **вимкнення** |

### Інформаційний екран пристрою {#info-screen}

Довге натискання <kbd>↓</kbd> відкриває інформаційний екран: версія прошивки та дата збірки, версія апаратної
платформи, час роботи, ім’я Фліппера й стан Debug (`ON`/`OFF`).

![Інформаційний екран пристрою: версія прошивки, версія апаратної платформи, час роботи та стан Debug](/screens/desktop/debug.png)

На цьому екрані **довге натискання <kbd>OK</kbd> вмикає або вимикає Debug** — той самий перемикач, що й
`Settings → System → Debug` ([Налаштування](/ua/start/settings)), тільки без ходіння по меню. Коротке
<kbd>BACK</kbd> повертає на робочий стіл.

Debug `ON` показує пункти, які інакше сховані: вкладку **Internal** в [Архіві](#archive) і `Signal Settings`
у меню збереженого сигналу Sub-GHz ([Signal Settings](/ua/subghz/signal-settings)). Коли закінчите, вимкніть
його — налаштування для зневадження сповільнюють Фліппер і не дають йому засинати.

## Main Menu

Натисніть <kbd>OK</kbd>. Головне меню відкривається на пункті **Apps** (усі застосунки `.fap` із картки,
згруповані за категоріями), далі йдуть **Sub-GHz**, **125 kHz RFID**, **NFC**, **Infrared**, **GPIO**, **iButton**,
**Bad USB**, **U2F**, **Clock**, а останнім — **Settings**. Список замкнений у коло, тому натискання <kbd>↑</kbd>
на **Apps** одразу переносить до **Settings**.

![Головне меню: вибрано Apps, вище Settings, нижче Sub-GHz](/screens/mainmenu/main.png)

::: tip Стилі меню
**Settings → Desktop → Menu Style** змінює вигляд головного меню. Стилі — це плагіни в
`/ext/apps_data/loader/plugins/` (файли, що починаються з `menu_style_`). `Default` — вбудований список.
:::

## Lock Menu {#lock-menu}

Натисніть <kbd>↑</kbd> на робочому столі. Переміщення — <kbd>↑</kbd>/<kbd>↓</kbd>, вибір — <kbd>OK</kbd>:

| Пункт | Що робить |
|---|---|
| **Turn Bluetooth On / Off** | Перемикає BLE без заходу в Settings |
| **Mute / Unmute** | Беззвучний режим: без звуку й вібрації. Параметри **Volume** та **Vibro** показують `Stealth`, поки він увімкнений |
| **Dummy Mode / Default Mode** | Вхід у [Dummy Mode](#dummy-mode) та вихід із нього |

Натискання <kbd>←</kbd> або <kbd>→</kbd> у Lock Menu відкриває другу сторінку — **Quick Settings**:

| Пункт | Керування |
|---|---|
| Brightness | <kbd>OK</kbd> для редагування, далі <kbd>←</kbd>/<kbd>→</kbd> (або <kbd>↑</kbd>/<kbd>↓</kbd>), крок 5 % |
| Volume | Так само. Прозвучить короткий сигнал, щоб ви почули новий рівень |
| Vibro | <kbd>OK</kbd> перемикає одразу |

<kbd>BACK</kbd> виходить із редагування пункту, друге натискання <kbd>BACK</kbd> закриває сторінку. Зміни
зберігаються в ті самі налаштування, що й **LCD and Notifications**.

::: tip Unleashed
В Unleashed **саме блокування** — це довге натискання <kbd>↑</kbd> на робочому столі: з PIN-кодом, якщо він
заданий, або звичайне блокування, якщо ні.
:::

## Блокування та PIN-код

- **Заблокувати:** утримуйте <kbd>↑</kbd> на робочому столі. Без PIN-коду кнопки просто блокуються.
  **Щоб розблокувати, швидко натисніть <kbd>BACK</kbd> три рази.**
- **З PIN-кодом:** задайте його в **Settings → Desktop → PIN Setup → Set PIN**. PIN-код — це від 4 до 10 натискань
  стрілок. Заблокований Фліппер питатиме цей код. Після хибних спроб він показує `Wrong PIN!` і паузу
  перед наступною спробою.
- **Auto Lock:** **Settings → Desktop → Auto Lock Time** (`OFF`, `10s` … `10min`) блокує пристрій після такого
  періоду неактивності. **Auto Lock disarm by active USB session** = `ON` не дає спрацювати автоблокуванню, поки
  Фліппер підключений по USB.

::: warning Забутий PIN-код
Забутий PIN-код можна скинути лише разом з усіма користувацькими налаштуваннями:
див. [Відновлення → Скидання забутого PIN-коду](/ua/start/recovery#reset-pin). Файли на картці microSD залишаються.
:::

## Dummy Mode {#dummy-mode}

Dummy Mode перетворює Фліппер на іграшку. Більшість функцій приховано, а кнопки запускають вибрані вами застосунки, наприклад ігри. Увімкнути — **Lock Menu → Dummy Mode**, вимкнути — **Lock Menu → Default Mode**.

У Dummy Mode кожна кнопка може запускати власний застосунок. Призначаються вони в **Settings → Desktop**:

`DummyMode - Left`, `- Left Long`, `- Right`, `- Right Long`, `- Up Long`, `- Down`, `- Down Long`, `- Ok`, `- Ok Long`.

Непризначена кнопка відкриває Passport. Коротке <kbd>↑</kbd> так само відкриває Lock Menu. Якщо
`DummyMode - Up Long` має значення `None`, довге <kbd>↑</kbd> блокує пристрій.

::: tip Unleashed
У стоковій прошивці в Dummy Mode 4 ярлики. В Unleashed їх 9 (коротке й довге натискання кожної кнопки), тож
кілька ігор можна тримати за одне натискання.
:::

## Улюблені застосунки (швидкий доступ)

**Settings → Desktop → Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long**

Для кожного слота можна вибрати:
- **Apps Menu (Default)** або **Passport (Default)** — вбудоване типове значення для цього слота;
- **None (disable)** — кнопка нічого не робить;
- **Lock Flipper**;
- будь-який застосунок із головного меню;
- **[Select App]** — будь-який файл `.fap` з `/ext/apps/`.

## Archive

Натисніть <kbd>↓</kbd>. Archive показує збережені файли, розкладені по вкладках. Вкладки перемикаються
кнопками <kbd>←</kbd>/<kbd>→</kbd>:

| Вкладка | Папка / вміст |
|---|---|
| Favorites | Файли, які ви закріпили |
| iButton | `/ext/ibutton` (`.ibtn`) |
| NFC | `/ext/nfc` (`.nfc`) |
| Sub-GHz | `/ext/subghz` (`.sub`) |
| SubRem | `/ext/subghz_remote`: збірні пульти Sub-GHz Remote |
| RFID LF | `/ext/lfrfid` (`.rfid` і дампи T5577) |
| Infrared | `/ext/infrared` (`.ir`) |
| Bad USB | `/ext/badusb` (`.txt`) |
| Phone | `/ext/phonebook`: телефонна книга SIM800 (`.phone`) |
| U2F | Токен U2F |
| Apps | `/ext/apps` (`.fap` і `.js`) |
| Internal | Внутрішнє сховище (лише коли **Debug** = `ON`) |
| Browser | Уся картка microSD |

Натисніть <kbd>OK</kbd> на файлі, щоб відкрити контекстне меню: запуск/емуляція, **Pin**/**Unpin** (додати до
Favorites), **Rename**, **Delete**, а в Browser ще й **Cut**, **Copy**, **Paste** та **NewDir**. На вкладці Favorites
меню відкривається утримуванням <kbd>OK</kbd>.

::: tip Налаштування в Favorites
У **Main Menu → Settings** утримуйте <kbd>OK</kbd> на будь-якому пункті налаштувань, щоб закріпити його у Favorites.
Після цього його можна відкривати з Archive, не блукаючи по меню.
:::

## Passport

Натисніть <kbd>→</kbd> на робочому столі або відкрийте **Settings → Passport**. Там показані ім’я дельфіна (воно ж
ім’я Фліппера), настрій і рівень: див. [Дельфін](/ua/start/dolphin).
