---
title: Bad USB
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Bad USB

Застосунок **Bad USB** перетворює Flipper на клавіатуру (і мишу), яка набирає заздалегідь підготовлений скрипт на
комп'ютері. Комп'ютер бачить звичайний пристрій введення (HID), тому драйвери не потрібні. Скрипти пишуться
розширеним **DuckyScript** (мовою USB Rubber Ducky) і зберігаються як звичайні файли `.txt` на картці microSD.

![Bad USB](/img/remote/2a3485aa02031f3f.png)

Типові законні застосування: автоматизація рутинного налаштування власних машин, введення довгих паролів чи
конфігурацій, встановлення ПЗ на новий ПК, демонстрації та навчання з інформаційної безпеки.

::: danger Правові аспекти
Пристрій для інжекції натискань клавіш може зробити все те саме, що й людина за клавіатурою. Запускайте скрипти
лише на комп'ютерах, які вам належать або які вам явно дозволено тестувати.
:::

Застосунок працює через **USB**-кабель або через **Bluetooth (BLE)** — у другому випадку хост бачить
Bluetooth-клавіатуру.

::: tip Unleashed
Unleashed інтегрує **BadKB** (від Willy-JL, ClaraCrazy та контриб'юторів XFW) безпосередньо в застосунок Bad USB:
- **режим BLE** з налаштовуваними іменем пристрою, MAC-адресою, режимом спарювання та постійним спарюванням, а
  також команди скриптів `BLE_ID` / `BT_ID`;
- налаштування **ідентичності USB**: виробник і назва продукту, VID/PID, рандомізація;
- **розкладки клавіатури** для багатьох мов ([від rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl));
- команда **`DUCKY_LANG`**, завдяки якій скрипт може сам вибрати розкладку клавіатури (нове в цьому релізі, PR #1224 від @ANTONiO-eagle).
:::

## Файли

| Шлях | Вміст |
|---|---|
| `/ext/badusb/` | Ваші скрипти (`.txt`). Файловий браузер застосунку відкривається саме тут. |
| `/ext/badusb/examples/` | Демонстраційні скрипти, що постачаються з прошивкою (Windows, macOS, GNOME, ChromeOS, тест миші, інсталятори qFlipper). |
| `/ext/badusb/assets/layouts/` | Файли розкладок клавіатури (`.kl`). Див. [Розкладки клавіатури](/ua/badusb/layouts). |
| `/ext/badusb/.badusb.settings` | Налаштування застосунку: глобальна розкладка, режим USB/BLE, ідентичність USB і BLE. |

Завантажуйте скрипти через [qFlipper](/ua/mobile/qflipper), [мобільний застосунок](/ua/mobile/mobile-app) або
копіюванням на SD-картку. Файл з однаковим іменем перезаписується без попередження.

## Сторінки цього розділу

| Сторінка | Про що вона |
|---|---|
| [Використання Bad USB](/ua/badusb/usage) | Запуск скриптів через USB і BLE, меню Config, усі налаштування |
| [Формат скриптів](/ua/badusb/script-format) | Повний довідник команд: STRING, DELAY, HOLD/RELEASE, ALTCHAR, MEDIA, миша, ID, DUCKY_LANG… |
| [Приклади](/ua/badusb/examples) | Безпечні приклади скриптів для початку |
| [Розкладки клавіатури](/ua/badusb/layouts) | Які розкладки існують, як вони працюють, як вибрати розкладку для скрипта |
