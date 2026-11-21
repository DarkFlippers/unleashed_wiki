---
title: GPIO и модули
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# GPIO и модули

18-контактная гребёнка на верхнем торце Flipper Zero превращает его в аппаратный инструмент: он может питать внешние
модули и общаться с ними, работать как USB-UART адаптер, вручную дёргать пины для проверки и быть целью для
аппаратного отладчика.

![GPIO-разъём Flipper Zero](/img/remote/f9f4fe12522d6f9d.png)

## Основы

| Страница | Что внутри |
|---|---|
| [Распиновка GPIO](/ru/gpio/pinout) | Все 18 пинов, напряжения, ограничения по току, 5 В на пине 1, толерантность к 3,3 / 5 В |
| [Приложение GPIO](/ru/gpio/gpio-app) | `Main Menu → GPIO`: USB-UART Bridge, GPIO Manual Control, 5V on GPIO; команды CLI `gpio` и `i2c` |
| [Внешние модули](/ru/gpio/external-modules) | Обзор типов модулей и какие пины занимает каждый |
| [Expansion-модули](/ru/gpio/expansion-modules) | `Settings → Expansion Modules` и протокол Expansion Module Protocol |
| [Модули и приложения для них](/ru/gpio/module-apps) | Все модули, которые поддерживают паки приложений, и что делает каждое приложение |

## Модули

| Страница | Модуль |
|---|---|
| [Внешний CC1101](/ru/subghz/external-cc1101) | Sub-GHz радио с более мощным трактом (описано в разделе Sub-GHz) |
| [ESP32 / Wi-Fi](/ru/gpio/esp32) | Wi-Fi Devboard, ESP32 Marauder, веб-прошивальщик и карта вардрайвинга Unleashed |
| [NRF24](/ru/gpio/nrf24) | Сниффер 2,4 ГГц на nRF24L01 и MouseJack |
| [SIM800](/ru/gpio/sim800) | GSM-модуль: звонки, SMS, телефонная книга, USSD (встроенное приложение Unleashed) |
| [GPS](/ru/gpio/gps) | Координаты с телефона-компаньона (сервис GPS) и NMEA GPS-модули по UART |
| [Video Game Module](/ru/gpio/video-game-module) | Модуль на RP2040 с видеовыходом и датчиком движения |

## Wi-Fi Developer Board

| Страница | Что внутри |
|---|---|
| [Devboard: начало работы](/ru/gpio/devboard) | Подготовка Flipper, подключение, соединение по USB и Wi-Fi |
| [Devboard: отладка и логи](/ru/gpio/devboard-debug) | Black Magic / DAPLink, отладка в VS Code, чтение логов UART |
| [Devboard: обновление прошивки](/ru/gpio/devboard-firmware) | Прошивка самой платы через uFBT |

::: tip Unleashed
В Unleashed «из коробки» больше GPIO-инструментов: приложение [SIM800](/ru/gpio/sim800) (`Apps → GPIO → SIM800`),
поддержка внешнего CC1101 с управлением усилителем в Sub-GHz, вывод на внешний ИК-модуль в
`Infrared → GPIO Settings` и большой набор GPIO-плагинов в дополнительных паках приложений. См.
[Внешние модули](/ru/gpio/external-modules).
:::

::: warning Прежде чем что-то подключать
Выключите Flipper перед подключением модуля и вставляйте модуль в разъём до упора. Подключение «на горячую» модуля с
большой ёмкостной нагрузкой может повредить данные на microSD: карта и пин 9 питаются от одной линии 3,3 В.
:::
