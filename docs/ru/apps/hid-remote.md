---
title: USB / Bluetooth-пульт (HID)
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app, https://docs.flipper.net/zero/apps/controllers]
sources: [unleashed-src, flipper-docs]
---
# USB / Bluetooth-пульт (HID)

С HID-приложением компьютер, телефон или планшет видят Flipper как клавиатуру, мышь или медиапульт
(USB **H**uman **I**nterface **D**evice). Одно и то же приложение собрано в двух вариантах:

| Приложение | Где на Flipper | Подключение |
|---|---|---|
| **USB Keyboard & Mouse** | `Main Menu → Apps → USB → USB Keyboard & Mouse` | USB-кабель |
| **Bluetooth Remote** | `Main Menu → Apps → Bluetooth → Bluetooth Remote` | Bluetooth LE |

Как подключить — на странице [Подключение HID-пульта](/ru/apps/controllers). Здесь описаны все режимы.

## Режимы

Стартовое меню:

`Keynote` · `Keynote Vertical` · `Keyboard` · `Numpad` · `Media` · `Apple Music macOS` · `Movie` · `Mouse` ·
`TikTok / YT Shorts` · `Mouse Clicker` · `Mouse Jiggler` · `Mouse Jiggler Stealth` · `PushToTalk`

В Bluetooth-версии есть ещё `Bluetooth Remote Name` и `Bluetooth Unpairing`.

::: tip Unleashed
Официальная документация описывает Keynote, Keyboard, Media, Mouse, TikTok, Mouse Jiggler и Mouse Clicker. В сборке
Unleashed в приложении также есть **Numpad**, **Apple Music macOS**, **Movie**, **Mouse Jiggler Stealth**,
**PushToTalk** и **Bluetooth Remote Name** для смены имени, под которым виден пульт.
:::

Почти во всех режимах **удержание <kbd>Back</kbd> — выход** в список режимов; при выходе все клавиши отпускаются.

### Keynote и Keynote Vertical

Кликер для презентаций. Keynote Vertical — то же самое, но повёрнуто, чтобы держать Flipper вертикально.

| Кнопка | Отправляет |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | стрелки (следующий / предыдущий слайд) |
| <kbd>OK</kbd> | Space (пробел) |
| <kbd>Back</kbd> | Backspace + "AC Back" (в большинстве программ выход из режима показа) |
| удержание <kbd>Back</kbd> | выход |

### Keyboard

Экранная клавиатура QWERTY с цифрами, символами, F1-F12, Esc, Tab, Enter, Backspace, Delete и модификаторами Ctrl,
Alt, Shift и Cmd (Win).

1. Перемещайтесь стрелками, <kbd>OK</kbd> вводит выбранную клавишу.
2. Выберите клавишу ⬆ (Shift), чтобы вводить заглавные буквы и второй ряд символов.
3. Для сочетания клавиш сначала нажмите модификатор (Ctrl, Alt или Cmd), затем клавишу.
4. Удерживайте <kbd>Back</kbd> для выхода.

### Numpad

Цифровая клавиатура: `0`-`9`, `.`, `+`, `-`, `*`, `/`, `En` (Enter цифрового блока), `NL` (Num Lock) и Backspace.
Стрелки выбирают, <kbd>OK</kbd> нажимает клавишу, удержание <kbd>Back</kbd> — выход.

### Media

| Кнопка | Отправляет |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | предыдущий / следующий трек |
| <kbd>↑</kbd> / <kbd>↓</kbd> | громкость больше / меньше |
| удержание <kbd>Back</kbd> | выход |

На телефонах клавиши громкости работают и как спуск затвора камеры: откройте камеру и нажмите <kbd>↑</kbd> или
<kbd>↓</kbd>, чтобы сделать фото или начать/остановить видео.

### Apple Music macOS

| Кнопка | Отправляет |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | предыдущий / следующий трек |
| <kbd>↑</kbd> / <kbd>↓</kbd> | <kbd>Cmd</kbd>+<kbd>↑</kbd> / <kbd>Cmd</kbd>+<kbd>↓</kbd> (громкость в Apple Music) |
| удержание <kbd>Back</kbd> | выход |

### Movie

| Кнопка | Отправляет |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | стрелки влево / вправо (перемотка в большинстве плееров) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | громкость больше / меньше |
| удержание <kbd>Back</kbd> | выход |

### Mouse

| Кнопка | Действие |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | движение курсора; при удержании ускоряется |
| <kbd>OK</kbd> | левый клик |
| удержание <kbd>OK</kbd> | зажать левую кнопку (перетаскивание, "Selecting...") |
| <kbd>Back</kbd> | правый клик |
| удержание <kbd>Back</kbd> | выход |

### TikTok / YT Shorts

Для приложений с короткими видео на телефоне или планшете.

| Кнопка | Действие |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | прокрутка к предыдущему / следующему видео |
| <kbd>OK</kbd> | двойной тап (лайк) |
| <kbd>←</kbd> / <kbd>→</kbd> | громкость меньше / больше |
| <kbd>Back</kbd> | одиночный тап (пауза) |
| удержание <kbd>Back</kbd> | выход |

::: tip iPhone / iPad
Если режим TikTok на iOS ничего не делает, включите `Settings → Accessibility → Touch → AssistiveTouch`, затем в
**Pointer Devices → Devices → Bluetooth Devices** выберите свой Flipper.
:::

### Mouse Clicker

Автоматически кликает с заданной частотой.

| Кнопка | Действие |
|---|---|
| <kbd>OK</kbd> | Start / Stop |
| <kbd>↑</kbd> / <kbd>↓</kbd> | кликов в секунду, до 100 (по умолчанию 1) |
| <kbd>←</kbd> / <kbd>→</kbd> | какая кнопка: левая, правая или колесо (средняя) |
| <kbd>Back</kbd> | выход |

### Mouse Jiggler

Слегка двигает курсор с постоянным интервалом, чтобы компьютер не засыпал и не показывал вас как «отошёл».

1. До запуска выберите интервал кнопками <kbd>←</kbd> / <kbd>→</kbd>: 500, 2000, 5000, 10000, 30000 или 60000 мс
   (по умолчанию 5000 мс).
2. Нажмите <kbd>OK</kbd> — **Start**, ещё раз — **Stop**. Пока хост не подключился, на экране
   `Waiting for Connection...`.
3. <kbd>Back</kbd> — выход.

### Mouse Jiggler Stealth

Как обычный jiggler, но двигает курсор через случайные интервалы между минимумом и максимумом, которые задаются в
минутах (от 1 до 30), — так меньше похоже на автомат. В остановленном состоянии <kbd>↑</kbd> / <kbd>↓</kbd> меняют
минимум, а <kbd>→</kbd> / <kbd>←</kbd> увеличивают / уменьшают максимум; <kbd>OK</kbd> запускает или останавливает.

### PushToTalk

Кнопка выключения микрофона / push-to-talk для видеозвонков.

1. Выберите список под свою ОС (**macOS** или **Win/Linux**), затем программу: Google Meet, Google Meet Global, Google
   Hangouts, Discord, FaceTime, Gather, Jamulus, Signal, Skype, Slack Call, Slack Huddle, TeamSpeak, Teams, Webex, Zoom
   или Zoom Global.
2. Долгое нажатие <kbd>OK</kbd> на пункте списка открывает его справку (некоторым программам нужна настройка или
   расширение, например глобальный хоткей для Google Meet или привязка клавиш в TeamSpeak).
3. Во время звонка: <kbd>Back</kbd> включает/выключает микрофон, **удержание <kbd>OK</kbd>** — push-to-talk (микрофон
   выключается, когда отпускаете), удержание <kbd>→</kbd> меняет статус микрофона на Flipper, если он рассинхронизировался
   с компьютером. Для Zoom долгое нажатие <kbd>←</kbd> отправляет Enter.
4. Удерживайте <kbd>Back</kbd> для выхода.

### Bluetooth Remote Name и Bluetooth Unpairing (только Bluetooth)

- **Bluetooth Remote Name**: введите имя в `Bluetooth Name`; пульт будет виден под ним. По умолчанию он называется
  `Control <имя Flipper>`.
- **Bluetooth Unpairing**: спрашивает `Unpair All Devices? All previous pairings will be lost!`; нажмите **Unpair**, чтобы
  забыть все хосты, сопряжённые с пультом. Пульт хранит свои ключи сопряжения отдельно
  (`/ext/apps_data/hid_ble/.bt_hid.keys`) от основных Bluetooth-сопряжений Flipper.

## Связанные страницы

- [Подключение HID-пульта](/ru/apps/controllers)
- [Bad USB](/ru/badusb/usage)
- [Приложения в комплекте Unleashed](/ru/apps/catalog)
