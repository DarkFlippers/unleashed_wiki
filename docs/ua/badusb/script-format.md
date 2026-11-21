---
title: Формат скриптів
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/bad-usb]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Формат скриптів Bad USB (DuckyScript)

Bad USB виконує текстові скрипти у синтаксисі **розширеного DuckyScript**. Класичні скрипти USB Rubber Ducky 1.0
працюють без змін; поверх них Flipper додає власну ідентичність USB/BLE, введення через `ALT`+Numpad, `SYSRQ`,
мультимедійні клавіші, керування мишею, очікування натискання кнопки та інше. Цей довідник перевірено за таблицею
команд у прошивці (`helpers/ducky_script_commands.c`, `ducky_script_keycodes.c`).

## Правила файлу

- Звичайний текст, розширення **`.txt`**, без компіляції. Закінчення рядків `\n` або `\r\n`.
- Одна команда на рядок. Порожні рядки пропускаються; рядки можна зсувати пробілами або табуляціями.
- Команди пишуться **ВЕЛИКИМИ літерами й чутливі до регістру**: `STRING`, а не `string`.
- Команда й аргумент розділяються одним пробілом.
- Коментарями є цілі рядки, що починаються з `REM`. Коментарів у кінці рядка не існує.
- Текст для введення (`STRING`, `STRINGLN`) мусить бути **ASCII**. Символи поза ASCII зупиняють скрипт із
  повідомленням *«Native .kl supports ASCII, not UTF-8»*.
- У разі помилки скрипт зупиняється, а на екрані з'являється *ERROR:*, номер рядка та причина.

## Коротка довідка

| Команда | Аргумент | Дія |
|---|---|---|
| `REM` | текст | Коментар, ігнорується. |
| `ID` | `VID:PID [Manufacturer:Product]` | Ідентичність USB, **лише в першому рядку**. |
| `BLE_ID` / `BT_ID` | `MAC Name` | Ідентичність Bluetooth, **лише в першому рядку**. |
| `DELAY` | мс | Одноразова пауза. |
| `DEFAULT_DELAY` / `DEFAULTDELAY` | мс | Пауза перед кожною наступною командою. |
| `STRING` | текст | Набрати текст. |
| `STRINGLN` | текст | Набрати текст і натиснути Enter. |
| `STRING_DELAY` / `STRINGDELAY` | мс | Пауза між натисканнями лише для **наступного** `STRING`. |
| `DEFAULT_STRING_DELAY` / `DEFAULTSTRINGDELAY` | мс | Пауза між натисканнями для **кожного** `STRING`. |
| `REPEAT` | n | Повторити попередню команду ще n разів. |
| `DUCKY_LANG` | назва розкладки | Перемкнути розкладку клавіатури для решти скрипта (Unleashed). |
| `HOLD` | клавіша / кнопка миші | Натиснути й тримати. |
| `RELEASE` | клавіша / кнопка миші | Відпустити затиснуту клавішу. |
| `ALTCHAR` | код | Набрати один символ через `ALT`+Numpad. |
| `ALTSTRING` / `ALTCODE` | текст | Набрати текст через `ALT`+Numpad. |
| `SYSRQ` | символ | Комбінація Magic SysRq. |
| `MEDIA` | мультимедійна клавіша | Клавіша consumer control (звук, відтворення…). |
| `GLOBE` | клавіша | Fn/Globe + клавіша (Mac/iPad). |
| `WAIT_FOR_BUTTON_PRESS` | немає | Пауза до натискання <kbd>OK</kbd> на Flipper. |
| `LEFTCLICK`, `RIGHTCLICK`, `MIDDLECLICK`… | немає | Клацання мишею. |
| `MOUSEMOVE` / `MOUSE_MOVE` | x y | Перемістити мишу. |
| `MOUSESCROLL` / `MOUSE_SCROLL` | delta | Прокрутити колесо. |
| комбінація клавіш | напр. `CTRL-ALT DELETE` | Натиснути й відпустити клавіші разом. |

## Коментарі

```text
REM This line is ignored
```

## Затримки

| Команда | Параметр | Примітки |
|---|---|---|
| `DELAY` | мс | Одна пауза. |
| `DEFAULT_DELAY` | мс | Додається перед кожною наступною командою. Те саме, що `DEFAULTDELAY`. |

```text
DEFAULT_DELAY 50
DELAY 1000
```

Затримки — ваш головний інструмент надійності: хосту потрібен час, щоб відкрити вікна, тому додавайте `DELAY`
після `GUI r`, після `ENTER` у рядку запуску тощо. Довгі затримки показуються на екрані як `Delay Ns`.

## Введення тексту

| Команда | Параметр | Примітки |
|---|---|---|
| `STRING` | текст | Набирає текст точно як є, використовуючи активну розкладку клавіатури. |
| `STRINGLN` | текст | Те саме, а потім натискає Enter. |
| `STRING_DELAY` | мс | Пауза між натисканнями лише для наступного `STRING`/`STRINGLN`. Те саме, що `STRINGDELAY`. |
| `DEFAULT_STRING_DELAY` | мс | Пауза між натисканнями для всіх наступних рядків. Те саме, що `DEFAULTSTRINGDELAY`. |

```text
DEFAULT_STRING_DELAY 10
STRINGLN Hello World!
```

Без затримки між символами текст надсилається максимально швидко; деякі хости й застосунки при цьому губять
символи. Вбудовані демонстраційні скрипти використовують `DEFAULT_STRING_DELAY 10`.

::: warning Розкладка має значення
`STRING` надсилає *позиції клавіш*, перекладені через вибрану [розкладку клавіатури](/ua/badusb/layouts). Якщо
хост використовує іншу розкладку, ніж застосунок, ви отримаєте не ті символи. Текст мусить бути ASCII.
:::

## Клавіші та комбінації

Рядок, який не є командою, читається як натискання клавіш: нуль або більше **модифікаторів**, а потім одна
**клавіша**. Модифікатори поєднуються пробілами або дефісами. Клавіша — це назва спеціальної клавіші або один
символ.

```text
ENTER
GUI r
CTRL c
CTRL-SHIFT ESC
CTRL ALT DELETE
ALT F4
SHIFT TAB
```

### Модифікатори

| Назва | Примітки |
|---|---|
| `CTRL`, `CONTROL` | |
| `SHIFT` | |
| `ALT` | |
| `GUI`, `WINDOWS` | Клавіша Windows / Command / Super |

### Спеціальні клавіші

| Назва | Примітки |
|---|---|
| `DOWNARROW` / `DOWN`, `LEFTARROW` / `LEFT`, `RIGHTARROW` / `RIGHT`, `UPARROW` / `UP` | Стрілки |
| `ENTER` | |
| `DELETE` | Видалення вперед |
| `BACKSPACE` | |
| `END`, `HOME`, `INSERT`, `PAGEUP`, `PAGEDOWN` | |
| `ESCAPE` / `ESC` | |
| `CAPSLOCK`, `NUMLOCK`, `SCROLLLOCK` | |
| `PRINTSCREEN` | |
| `BREAK`, `PAUSE` | Pause/Break |
| `SPACE`, `TAB` | |
| `MENU`, `APP` | Клавіша контекстного меню |
| `F1` … `F24` | Функційні клавіші (прошивка знає й F13-F24) |

## Повторення

```text
DOWN
REPEAT 9
```

`REPEAT n` виконує **попередню команду** ще n разів (у прикладі Down натискається 10 разів). `n` мусить бути ≥ 1.

## Затискання та відпускання

| Команда | Параметр | Примітки |
|---|---|---|
| `HOLD` | спеціальна клавіша, модифікатор, один символ або кнопка миші | Натиснути й тримати до `RELEASE`. |
| `RELEASE` | те саме | Відпустити цю клавішу. |

```text
HOLD SHIFT
DOWN
REPEAT 4
RELEASE SHIFT
```

Одночасно можна тримати не більше **6** клавіш чи кнопок (це розмір HID-звіту клавіатури); більше дає
*«Too many keys are held»*. `RELEASE` без затиснутих клавіш дає *«No keys are held»*. В офіційному документі
згадано 5; перевірка у прошивці допускає 6.

## Введення через ALT + Numpad

У Windows (і в деяких конфігураціях Linux) будь-який символ можна набрати, тримаючи `ALT` і вводячи його код на
цифровому блоці. Це **не залежить від розкладки клавіатури**, тому зручно на незнайомих машинах.

| Команда | Параметр | Примітки |
|---|---|---|
| `ALTCHAR` | код символу | Набирає один символ: тримає ALT і вводить цифри на Numpad. |
| `ALTSTRING` | текст | Набирає кожний друкований ASCII-символ (32-126) тексту через його ALT-код. |
| `ALTCODE` | текст | Те саме, що `ALTSTRING` (назва, яку використовують деякі реалізації DuckyScript). |

NumLock автоматично вмикається перед ALT-введенням.

```text
ALTCHAR 7
ALTSTRING This works with any keyboard layout
```

## SysRq

```text
SYSRQ b
```

Надсилає `ALT`+`PRINTSCREEN`+клавіша — комбінацію [Magic SysRq](https://en.wikipedia.org/wiki/Magic_SysRq_key) у
Linux. Будьте уважні: деякі клавіші SysRq негайно перезавантажують або зупиняють систему.

## Мультимедійні клавіші

`MEDIA <key>` натискає клавішу consumer control:

| Клавіша | Примітки |
|---|---|
| `POWER`, `REBOOT`, `SLEEP`, `LOGOFF` | Система |
| `EXIT`, `HOME`, `BACK`, `FORWARD`, `REFRESH` | Навігація у браузері / застосунку |
| `SNAPSHOT` | Зробити фото у застосунку камери |
| `PLAY`, `PAUSE`, `PLAY_PAUSE`, `NEXT_TRACK`, `PREV_TRACK`, `STOP`, `EJECT` | Відтворення |
| `MUTE`, `VOLUME_UP`, `VOLUME_DOWN` | Гучність |
| `FN` | Клавіша Fn/Globe на клавіатурах Mac |
| `BRIGHT_UP`, `BRIGHT_DOWN` | Яскравість дисплея |

```text
MEDIA VOLUME_UP
REPEAT 5
```

## Клавіша Fn / Globe (Mac, iPad)

```text
GLOBE e
```

`GLOBE <key>` тримає Fn/Globe, натискає клавішу й відпускає обидві (спеціальна клавіша або один символ).

## Очікування натискання кнопки

```text
WAIT_FOR_BUTTON_PRESS
```

Скрипт зупиняється на невизначений час; Flipper показує **Press to continue**. Натисніть <kbd>OK</kbd>, щоб
продовжити. Зручно для синхронізації з чимось, що ви робите вручну (увійти в систему, розблокувати екран…).

## Миша

| Команда | Параметр | Примітки |
|---|---|---|
| `LEFTCLICK` / `LEFT_CLICK` | немає | Клацання лівою кнопкою |
| `RIGHTCLICK` / `RIGHT_CLICK` | немає | Клацання правою кнопкою |
| `MIDDLECLICK` / `MIDDLE_CLICK` / `WHEELCLICK` / `WHEEL_CLICK` | немає | Клацання середньою кнопкою (колесом) |
| `MOUSEMOVE` / `MOUSE_MOVE` | `x y` (цілі числа) | Відносне переміщення; від'ємні значення — ліворуч / вгору |
| `MOUSESCROLL` / `MOUSE_SCROLL` | `delta` (ціле число) | Прокручування колесом; знак задає напрямок |

Кнопки миші працюють із `HOLD`/`RELEASE` — наприклад, для перетягування:

```text
HOLD LEFTCLICK
MOUSEMOVE 100 0
RELEASE LEFTCLICK
```

## Device ID {#device-id}

Ви можете задати ідентичність, з якою Flipper представляється хосту. Команда мусить стояти в **найпершому
рядку**; вона застосовується під час відкриття скрипта, ще до запуску, і застосунок **перемикається у відповідний
режим з'єднання** (перемкнути назад вручну все одно можна). В інших рядках ці команди ігноруються.

| Команда | Параметри | Приклад | Режим |
|---|---|---|---|
| `ID` | `VID:PID Manufacturer:Product` | `ID 1234:abcd Flipper Devices:Flipper Zero` | USB |
| `BLE_ID` | `MAC Device name` | `BLE_ID AA:BB:CC:DD:EE:FF Smart Fridge` | Bluetooth |
| `BT_ID` | `MAC Device name` | `BT_ID AA:BB:CC:DD:EE:FF Smart Fridge` | те саме, що `BLE_ID` |

- `ID`: VID і PID (у шістнадцятковій формі) обов'язкові; рядки виробника та продукту необов'язкові (не більше
  31 символа кожний).
- `BLE_ID` / `BT_ID`: і 6-байтова MAC-адреса, і ім'я пристрою обов'язкові.

## Розкладка клавіатури для окремого скрипта: `DUCKY_LANG` {#keyboard-layout-per-script-ducky-lang}

::: tip Unleashed
`DUCKY_LANG` — новинка Unleashed (PR #1224 від @ANTONiO-eagle).
:::

```text
DUCKY_LANG de-DE
STRING Hallo Welt
```

- Завантажує `/ext/badusb/assets/layouts/<name>.kl` і використовує її з цього рядка й далі, замість глобальної
  розкладки, заданої в Config. Короткі псевдоніми: `en` → `en-US`, `de` → `de-DE`, `fr` → `fr-FR`.
- Назва може містити літери, цифри, `-` і `_`, і після неї в рядку не має бути нічого.
- Відсутній файл або некоректна назва **не зупиняють скрипт**: він тихо відкочується до вбудованої `en-US`.
- Кожен новий запуск знову починається з глобальної розкладки, тому ставте `DUCKY_LANG` ближче до початку.

Перелік назв розкладок є на сторінці [Розкладки клавіатури](/ua/badusb/layouts).

## Пов'язані сторінки

- [Приклади](/ua/badusb/examples)
- [Розкладки клавіатури](/ua/badusb/layouts)
- [Використання Bad USB](/ua/badusb/usage)
