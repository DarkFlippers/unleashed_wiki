---
title: GUI у застосунках
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules]
sources: [unleashed-docs, unleashed-src]
---
# GUI у застосунках

Ця сторінка пояснює базові поняття GUI у прошивці Flipper і порівнює три способи побудувати інтерфейс застосунку —
від найпростішого до найпотужнішого:

1. [Dialogs](#using-dialogs) — кілька вікон-повідомлень, без власної відрисовки.
2. [ViewPort](#using-a-viewport) — одна повноекранна область, яку ви малюєте самі; ідеально для ігор.
3. [Views і Scenes](#using-views-and-scenes) — багатоекранні застосунки з меню та навігацією (більшість вбудованих
   застосунків).

## Базові поняття

### Цикл подій

Механізм асинхронного опрацювання подій. Замість опитування чи блокування в очікуванні подій (натискань кнопок,
отриманих пакетів, таймерів) ви реєструєте функції-обробники, які викликаються в момент настання події, — тож
головний цикл залишається вільним для іншої роботи.

### Канва

**Канва** — це «сира» область малювання без жодних абстракцій. Малювати на ній напряму корисно для власних
візуальних елементів (наприклад, в іграх), але більшості застосунків це не потрібно.

### ViewPort

**ViewPort** визначає, як малюється область екрана заданого розміру й розташування та як вона реагує на введення.
Кілька ViewPort утворюють *стек відрисовки*, який рендериться знизу вгору, тож вони можуть накладатися. Створений
ViewPort можна увімкнути або вимкнути.

### Model, View і View Dispatcher

Вони відокремлюють інтерфейс від даних, завдяки чому застосунки легше розробляти, підтримувати й тестувати.

- **Model** — дані; технічно це структура в пам’яті.
- **View** — відрисовка й опрацювання введення. Для малювання читає Model, а під час обробки подій змінює її.
- **View Dispatcher** — тримає посилання на всі View, потрібні застосунку, і на запит перемикається між ними.

### Модулі представлень

Готові повноекранні шаблони (View + Model) для типових інтерфейсів Flipper, які входять до прошивки
(`applications/services/gui/modules/`):

| Модуль | Типове застосування |
|---|---|
| `button_menu` | Меню з великих кнопок |
| `button_panel` | Сітка кнопок, які можна вибирати |
| `byte_input` | Введення шістнадцяткових байтів |
| `date_time_input` | Введення дати й часу |
| `dialog_ex` | Діалог із заголовком, текстом, піктограмою та до трьох кнопок |
| `empty_screen` | Порожній екран |
| `file_browser` | Вибір файлу на картці microSD |
| `loading` | Анімація «Loading…» |
| `menu` | Список у стилі головного меню, з піктограмами |
| `number_input` | Введення числа |
| `popup` | Тимчасове повідомлення з таймаутом |
| `submenu` | Простий вертикальний список пунктів |
| `text_box` | Текст із прокручуванням |
| `text_input` | Екранна клавіатура |
| `variable_item_list` | Список налаштувань зі значеннями ◀ ▶ |
| `widget` | Вільна композиція з тексту, піктограм і кнопок |

| | | |
|---|---|---|
| ![submenu](/img/dev/submenu.png) `submenu` | ![dialog](/img/dev/dialog.png) `dialog_ex` | ![text_input](/img/dev/text_input.png) `text_input` |
| ![byte_input](/img/dev/byte_input.png) `byte_input` | ![text_box](/img/dev/text_box.png) `text_box` | ![widget](/img/dev/widget.png) `widget` |
| ![loading](/img/dev/loading.png) `loading` | ![empty](/img/dev/empty.png) `empty_screen` | |

Початковий код: [applications/services/gui/modules](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules).

### Scene і Scene Manager

**Scene** керує поведінкою застосунку на одному екрані. Наприклад, застосунок GPIO оголошує такі сцени у файлі
`applications/main/gpio/scenes/gpio_scene_config.h`:

| Сцена | Екран |
|---|---|
| `gpio_scene_start` | Початкове меню |
| `gpio_scene_usb_uart` | Інтерфейс мосту USB-UART |
| `gpio_scene_usb_uart_cfg` | Налаштування мосту USB-UART (файл `gpio_scene_usb_uart_config.c`) |
| `gpio_scene_usb_uart_close_rpc` | «Connection Is Active! Disconnect from PC or phone to use this function.» — показується, коли ви відкриваєте міст USB-UART, а qFlipper чи мобільний застосунок під’єднані |
| `gpio_scene_test` | Ручне керування GPIO |

З початкового меню можна перейти до ручного керування або до режиму мосту USB-UART, а з мосту — до його
налаштувань.

Кожна сцена реалізує три функції:

- `on_enter` — ініціалізувати представлення сцени;
- `on_exit` — деініціалізувати й звільнити ресурси;
- `on_event` — опрацювати вхідні події.

Обробник події може перемкнути застосунок на іншу сцену — наприклад, вибір пункту меню веде до відповідної сцени.
Ці переходи виконує **Scene Manager**, який ще й зберігає історію навігації, завдяки чому складні сценарії
переходів залишаються керованими.

## Підходи до розробки GUI

Чим складніший інтерфейс, тим більше абстракцій GUI вам потрібно.

### Dialogs {#using-dialogs}

Найпростіший підхід — підходить, коли весь інтерфейс складається з діалогових вікон. API:
[`dialogs.h`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/dialogs/dialogs.h).

![Підхід із Dialogs](/img/dev/app_dev_gui_dialogs.jpg)

**Плюси:** просто й легко.
**Мінуси:** тільки діалоги, складний інтерфейс не побудувати; діалоги **синхронні** — поки користувач не натисне
кнопку, решта коду застосунку не виконується.

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app(void* p) {
    UNUSED(p);

    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);
    DialogMessage* message = dialog_message_alloc();
    dialog_message_set_header(message, "Hello world", 64, 20, AlignCenter, AlignTop);
    dialog_message_set_text(message, "I'm test_app!", 64, 32, AlignCenter, AlignTop);
    dialog_message_show(dialogs, message);
    dialog_message_free(message);
    furi_record_close(RECORD_DIALOGS);

    return 0;
}
```

### ViewPort {#using-a-viewport}

Ви створюєте один повноекранний ViewPort, який малює дисплей і опрацьовує все введення.

![Підхід із ViewPort](/img/dev/app_dev_gui_viewport.png)

**Плюси:** легко — один ViewPort і жодних інших абстракцій; швидко й зручно для ігор; повний контроль над екраном.
**Мінуси:** немає допоміжних засобів навігації; немає View, які можна перевикористати.

Приклади:

- більшість [інструментів налагодження](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug)
- [діалог парування BLE](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/bt/bt_service/bt.c)
- [Dolphin Passport](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/settings/dolphin_passport/passport.c)
- більшість ігор, наприклад [Snake](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/snake_game),
  що постачається з Unleashed

### Views і Scenes {#using-views-and-scenes}

Основний підхід для застосунків зі складним, ієрархічним інтерфейсом — ним користується більшість застосунків
Flipper.

![Підхід із Views і Scenes](/img/dev/app_dev_gui_views_and_scenes.jpg)

**Плюси:** підтримує складну навігацію; View перевикористовуються; багато готових модулів представлень.
**Мінуси:** потрібен час, щоб вкласти це в голову; складніша реалізація.

Приклади (початковий код Unleashed):

- [Desktop](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop)
- [iButton](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton)
- [Infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared)
- [GPIO](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio)
- [NFC](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc)
- [RFID](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid)
- [Sub-GHz](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz)

::: tip
У застосунках на сценах список сцен лежить у `scenes/<app>_scene_config.h`, а кожен файл `scenes/*.c` реалізує один
екран. Прочитати їх — найшвидший спосіб зрозуміти, як побудовані меню застосунку.
:::

## Як обрати підхід

| Якщо потрібно… | Беріть |
|---|---|
| Показати повідомлення або запитати «так/ні» | Dialogs |
| Гра, візуалізатор або один власний екран | ViewPort |
| Меню, налаштування, вибір файлів, кілька екранів | Views і Scenes |

## Докладніше (зовнішні матеріали)

- [A Visual Guide to Flipper Zero GUI Modules](https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/) — Christopher Hranj
- [Scenes Demo Application Tutorial](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes#scenes-demo-application-tutorial) — Derek Jamison
- Відеопосібники Derek Jamison на YouTube:
  [Using ViewPort](https://www.youtube.com/watch?v=5QwwihbxkC8) ·
  [Creating UI using Scenes](https://www.youtube.com/watch?v=YbskaB6caqk&list=PLM1cyTMe-PYJaMQ6TWeK1mAWxORdjYJZ5&index=8) ·
  [SceneManager Best Practice](https://www.youtube.com/watch?v=vQAk7fC_no4)

## Пов’язані сторінки

- [Перший застосунок на C](/ua/dev/first-app-c)
- [Furi API](/ua/dev/furi-api)
- [JavaScript на Flipper](/ua/dev/js-about) — скрипти на JS можуть використовувати багато тих самих модулів представлень
