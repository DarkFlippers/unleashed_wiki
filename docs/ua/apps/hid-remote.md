---
title: Пульт USB / Bluetooth (HID)
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app, https://docs.flipper.net/zero/apps/controllers]
sources: [unleashed-src, flipper-docs]
---
# Пульт USB / Bluetooth (HID)

Застосунок HID робить так, що комп'ютер, смартфон або планшет бачить Flipper як клавіатуру, мишу чи
мультимедійний пульт (USB-пристрій введення, **H**uman **I**nterface **D**evice). Той самий застосунок збирається
двічі:

| Застосунок | Де на Flipper | З'єднання |
|---|---|---|
| **USB Keyboard & Mouse** | `Main Menu → Apps → USB → USB Keyboard & Mouse` | USB-кабель |
| **Bluetooth Remote** | `Main Menu → Apps → Bluetooth → Bluetooth Remote` | Bluetooth LE |

Як його підключити, описано у [Підключенні HID-пульта](/ua/apps/controllers). На цій сторінці розглянуто кожний
режим.

## Режими

У початковому меню перелічені:

`Keynote` · `Keynote Vertical` · `Keyboard` · `Numpad` · `Media` · `Apple Music macOS` · `Movie` · `Mouse` ·
`TikTok / YT Shorts` · `Mouse Clicker` · `Mouse Jiggler` · `Mouse Jiggler Stealth` · `PushToTalk`

У версії для Bluetooth є також `Bluetooth Remote Name` і `Bluetooth Unpairing`.

::: tip Unleashed
Офіційна документація описує Keynote, Keyboard, Media, Mouse, TikTok, Mouse Jiggler і Mouse Clicker. У збірці
застосунку з Unleashed є також **Numpad**, **Apple Music macOS**, **Movie**, **Mouse Jiggler Stealth**,
**PushToTalk** і **Bluetooth Remote Name** — щоб змінити ім'я, під яким пульт себе рекламує.
:::

Майже в кожному режимі **утримання <kbd>Back</kbd> виходить** назад до переліку режимів; під час виходу всі
клавіші відпускаються.

### Keynote і Keynote Vertical

Пульт для презентацій. Keynote Vertical — те саме, але повернуте для вертикального тримання Flipper.

| Кнопка | Що надсилає |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | клавіші-стрілки (наступний / попередній слайд) |
| <kbd>OK</kbd> | Space |
| <kbd>Back</kbd> | Backspace + «AC Back» (у більшості застосунків виходить із режиму показу слайдів) |
| утримання <kbd>Back</kbd> | вихід |

### Keyboard

Екранна клавіатура QWERTY з цифрами, символами, F1-F12, Esc, Tab, Enter, Backspace, Delete і модифікаторами
Ctrl, Alt, Shift та Cmd (Win).

1. Переміщайтеся стрілками, натискайте <kbd>OK</kbd>, щоб надрукувати вибрану клавішу.
2. Виберіть клавішу ⬆ (Shift), щоб друкувати великі літери й другий ряд символів.
3. Для комбінації спочатку натисніть модифікатор (Ctrl, Alt або Cmd), а потім клавішу.
4. Утримуйте <kbd>Back</kbd>, щоб вийти.

### Numpad

Цифровий блок: `0`-`9`, `.`, `+`, `-`, `*`, `/`, `En` (Enter на цифровому блоці), `NL` (Num Lock) і Backspace.
Стрілки вибирають, <kbd>OK</kbd> натискає клавішу, утримання <kbd>Back</kbd> виходить.

### Media

| Кнопка | Що надсилає |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | попередній / наступний трек |
| <kbd>↑</kbd> / <kbd>↓</kbd> | гучніше / тихіше |
| утримання <kbd>Back</kbd> | вихід |

На смартфонах клавіші гучності також працюють як спуск камери: відкрийте камеру й натисніть <kbd>↑</kbd> чи
<kbd>↓</kbd>, щоб зробити фото або почати/зупинити відеозапис.

### Apple Music macOS

| Кнопка | Що надсилає |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | попередній / наступний трек |
| <kbd>↑</kbd> / <kbd>↓</kbd> | <kbd>Cmd</kbd>+<kbd>↑</kbd> / <kbd>Cmd</kbd>+<kbd>↓</kbd> (гучність в Apple Music) |
| утримання <kbd>Back</kbd> | вихід |

### Movie

| Кнопка | Що надсилає |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | стрілка вліво / вправо (перемотування в більшості плеєрів) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | гучніше / тихіше |
| утримання <kbd>Back</kbd> | вихід |

### Mouse

| Кнопка | Дія |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | рух курсора; утримання прискорює його |
| <kbd>OK</kbd> | клацання лівою кнопкою |
| утримання <kbd>OK</kbd> | затиснути ліву кнопку (перетягування, «Selecting...») |
| <kbd>Back</kbd> | клацання правою кнопкою |
| утримання <kbd>Back</kbd> | вихід |

### TikTok / YT Shorts

Для застосунків із короткими відео на смартфоні чи планшеті.

| Кнопка | Дія |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | прокрутити до попереднього / наступного відео |
| <kbd>OK</kbd> | подвійний дотик (лайк) |
| <kbd>←</kbd> / <kbd>→</kbd> | тихіше / гучніше |
| <kbd>Back</kbd> | одинарний дотик (пауза) |
| утримання <kbd>Back</kbd> | вихід |

::: tip iPhone / iPad
Якщо режим TikTok на iOS нічого не робить, увімкніть
`Settings → Accessibility → Touch → AssistiveTouch`, а потім у **Pointer Devices → Devices → Bluetooth Devices**
виберіть свій Flipper.
:::

### Mouse Clicker

Клацає автоматично із заданою частотою.

| Кнопка | Дія |
|---|---|
| <kbd>OK</kbd> | Start / Stop |
| <kbd>↑</kbd> / <kbd>↓</kbd> | клацань за секунду, до 100 (типово 1) |
| <kbd>←</kbd> / <kbd>→</kbd> | яка кнопка: ліва, права або колесо (середня) |
| <kbd>Back</kbd> | вихід |

### Mouse Jiggler

Трохи зсуває курсор через фіксований інтервал, щоб комп'ютер не засинав і не показував вас як «відсутнього».

1. Перед запуском виберіть інтервал клавішами <kbd>←</kbd> / <kbd>→</kbd>: 500, 2000, 5000, 10000, 30000 або
   60000 мс (типово 5000 мс).
2. Натисніть <kbd>OK</kbd> для **Start**, а потім ще раз для **Stop**. Поки хост не підключився, на екрані
   написано `Waiting for Connection...`.
3. <kbd>Back</kbd> виходить.

### Mouse Jiggler Stealth

Як звичайний jiggler, але рухає курсор через випадкові інтервали між мінімумом і максимумом, які ви задаєте у
хвилинах (від 1 до 30), — це менше схоже на машину. У зупиненому стані <kbd>↑</kbd> / <kbd>↓</kbd> змінюють
мінімум, а <kbd>→</kbd> / <kbd>←</kbd> збільшують / зменшують максимум; <kbd>OK</kbd> запускає або зупиняє.

### PushToTalk

Кнопка вимкнення мікрофона / push-to-talk для відеодзвінків.

1. Виберіть перелік для своєї ОС (**macOS** або **Win/Linux**), а потім застосунок: Google Meet, Google Meet
   Global, Google Hangouts, Discord, FaceTime, Gather, Jamulus, Signal, Skype, Slack Call, Slack Huddle,
   TeamSpeak, Teams, Webex, Zoom або Zoom Global.
2. Довге натискання <kbd>OK</kbd> на елементі переліку відкриває довідку по ньому (деяким застосункам потрібне
   налаштування або розширення — наприклад, глобальне скорочення для Google Meet чи прив'язування клавіш у
   TeamSpeak).
3. Під час дзвінка: <kbd>Back</kbd> перемикає мікрофон, **утримання <kbd>OK</kbd>** працює як push-to-talk
   (мікрофон вимикається, коли ви відпускаєте кнопку), утримання <kbd>→</kbd> змінює стан мікрофона на Flipper,
   якщо він розійшовся зі станом на комп'ютері. Для Zoom довге натискання <kbd>←</kbd> надсилає Enter.
4. Утримуйте <kbd>Back</kbd>, щоб вийти.

### Bluetooth Remote Name і Bluetooth Unpairing (лише Bluetooth)

- **Bluetooth Remote Name**: введіть ім'я в `Bluetooth Name`; пульт рекламуватиме себе під ним. Типово він
  з'являється як `Control <ім'я Flipper>`.
- **Bluetooth Unpairing**: запитує `Unpair All Devices? All previous pairings will be lost!`; натисніть
  **Unpair**, щоб забути всі хости, спаровані з пультом. Пульт тримає власні ключі спарювання
  (`/ext/apps_data/hid_ble/.bt_hid.keys`), окремо від основних спарювань Bluetooth у Flipper.

## Пов'язані сторінки

- [Підключення HID-пульта](/ua/apps/controllers)
- [Bad USB](/ua/badusb/usage)
- [Застосунки у складі Unleashed](/ua/apps/catalog)
