---
title: GPIO та модулі
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# GPIO та модулі

18-контактна гребінка на верхньому торці Flipper Zero перетворює його на апаратний інструмент: вона може живити
зовнішні модулі й спілкуватися з ними, працювати як перехідник USB-UART, перемикати піни вручну для тестів і бути
таргетом для апаратного відлагоджувача.

![Гребінка GPIO Flipper Zero](/img/remote/f9f4fe12522d6f9d.png)

## Основи

| Сторінка | Що всередині |
|---|---|
| [Розпіновка GPIO](/ua/gpio/pinout) | Усі 18 пінів, напруги, обмеження струму, 5 В на піні 1, толерантність 3,3 В / 5 В |
| [Застосунок GPIO](/ua/gpio/gpio-app) | `Main Menu → GPIO`: USB-UART Bridge, GPIO Manual Control, 5V on GPIO; команди CLI `gpio` та `i2c` |
| [Зовнішні модулі](/ua/gpio/external-modules) | Огляд типів модулів і того, які піни використовує кожен |
| [Модулі розширення](/ua/gpio/expansion-modules) | `Settings → Expansion Modules` і Expansion Module Protocol |
| [Модулі та застосунки для них](/ua/gpio/module-apps) | Усі модулі, які підтримують паки застосунків, і що робить кожен застосунок |

## Модулі

| Сторінка | Модуль |
|---|---|
| [Зовнішній CC1101](/ua/subghz/external-cc1101) | Радіо Sub-GHz із потужнішим вхідним каскадом (описано в розділі Sub-GHz) |
| [ESP32 / Wi-Fi](/ua/gpio/esp32) | Wi-Fi Devboard, ESP32 Marauder, вебпрошивальник Unleashed і карта вардрайвінгу |
| [NRF24](/ua/gpio/nrf24) | Сніфер nRF24L01 на 2,4 ГГц і MouseJack |
| [SIM800](/ua/gpio/sim800) | GSM-модуль: дзвінки, SMS, телефонна книга, USSD (вбудований застосунок Unleashed) |
| [GPS](/ua/gpio/gps) | Місцеположення від під'єднаного смартфона (служба GPS) і NMEA-GPS-модулі на UART |
| [Video Game Module](/ua/gpio/video-game-module) | Модуль на RP2040 із відеовиходом і датчиком руху |

## Wi-Fi Developer Board

| Сторінка | Що всередині |
|---|---|
| [Devboard: перші кроки](/ua/gpio/devboard) | Підготовка Flipper, підключення, з'єднання через USB і Wi-Fi |
| [Devboard: відлагодження й логи](/ua/gpio/devboard-debug) | Black Magic / DAPLink, відлагодження у VS Code, читання логів UART |
| [Devboard: оновлення прошивки](/ua/gpio/devboard-firmware) | Прошивання власної прошивки плати через uFBT |

::: tip Unleashed
Unleashed постачається з додатковими інструментами для GPIO «з коробки»: застосунок [SIM800](/ua/gpio/sim800)
(`Apps → GPIO → SIM800`), підтримка зовнішнього CC1101 із керуванням підсилювачем у Sub-GHz, вихід на зовнішній
ІЧ-модуль у `Infrared → GPIO Settings` і великий набір GPIO-плагінів у додаткових пакетах застосунків. Див.
[Зовнішні модулі](/ua/gpio/external-modules).
:::

::: warning Перед підключенням будь-чого
Вимикайте Flipper перед підключенням модуля й вставляйте модуль у гребінку до кінця. Гаряче підключення модуля з
великим ємнісним навантаженням може пошкодити дані на картці microSD, бо картка й пін 9 живляться від однієї лінії
3,3 В.
:::
