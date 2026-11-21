---
title: Внешние модули
order: 30
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SIM800.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# Внешние модули

Большинство плат расширения для Flipper Zero вставляются прямо в GPIO-разъём и общаются с ним по одной из трёх шин:
**SPI** (пины 2–5), **UART** (пины 13/14 или 15/16) или **I2C** (пины 15/16). По занятым пинам сразу видно, какие
модули получится использовать одновременно, а какие нет.

## Типы модулей

| Модуль | Шина / пины | Чем управляется | Страница |
|---|---|---|---|
| Внешний CC1101 (Sub-GHz) | SPI 2–5, GDO0 на 6, усилитель на 7 | Встроенное приложение Sub-GHz (`Radio Settings → Module → External`) | [Внешний CC1101](/ru/subghz/external-cc1101) |
| NRF24L01 (2,4 ГГц) | SPI 2–5, CE на 6 | Плагины NRF24 Sniffer / Mouse Jacker | [NRF24](/ru/gpio/nrf24) |
| Платы Wi-Fi на ESP32 / ESP8266, Wi-Fi Devboard | UART 13/14 (SWD 10/12 для отладки) | Плагины Marauder, Wi-Fi Scanner, Deauther; прошивка Black Magic | [ESP32](/ru/gpio/esp32), [Devboard](/ru/gpio/devboard) |
| GSM SIM800C / SIM800L | UART 13/14 или 15/16, питание с пина 1 | Встроенное приложение SIM800 | [SIM800](/ru/gpio/sim800) |
| GPS (NMEA) | UART | Плагин `[NMEA] GPS` | [GPS](/ru/gpio/gps) |
| Video Game Module | UART 13/14, пины 2–7, питание | Прошивка Flipper + прошивка модуля | [Video Game Module](/ru/gpio/video-game-module) |
| Expansion-модули (протокол) | UART 13/14 или 15/16 | `Settings → Expansion Modules` | [Expansion-модули](/ru/gpio/expansion-modules) |
| Внешний ИК-светодиод / ИК-бустер | Пин 2 (PA7), 5 В с пина 1 | Встроенное приложение Infrared (`GPIO Settings`) | см. ниже |
| Датчики температуры / влажности / давления | зависит от датчика (см. README) | Плагин `Unitemp` | [README Unitemp](https://github.com/quen0n/unitemp-flipperzero#readme) |
| Любое I2C-устройство | I2C 15/16 | Плагин `i2c Tools`, команда CLI `i2c` | [Приложение GPIO](/ru/gpio/gpio-app) |
| ESP32-CAM | UART | Плагин Camera Suite | [Camera Suite](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |
| Сейфы Sentry Safe / Master Lock (два провода) | Пин 15 (C1) + GND 8 | Плагин SentrySafe | [SentrySafe](/ru/apps/sentry-safe) |

::: tip Unleashed
Прямо в прошивке Unleashed есть поддержка:
- **внешнего CC1101** по аппаратному SPI с управлением внешним усилителем / светодиодами (`Ext Amp & LEDs`, включено по
  умолчанию) в `Sub-GHz → Radio Settings`;
- **внешних ИК-модулей** в `Infrared → GPIO Settings` (автоопределение, как в стоковой прошивке);
- GSM-приложения **SIM800** (`Apps → GPIO → SIM800`).

Сами внешние радиомодули работают на любой прошивке, не только на Unleashed. Первую реализацию CC1101 написал
@quen0n для Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307)); ту, что используется сегодня, написал **Skorp** в официальной прошивке, и
Unleashed берёт именно её.

Плагины для остального (NRF24, Marauder, GPS, Unitemp, i2c Tools, Camera Suite…) — в паках Base и Extra:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest). См.
[Приложения на SD-карте](/ru/apps/sd-card-apps).
:::

## Конфликты пинов

Модули на одной шине без доработок одновременно не работают. Частые пересечения:

| Пины | Кто занимает |
|---|---|
| 2, 3, 4, 5 | SPI: внешний CC1101, NRF24 (MOSI, MISO, CS, SCK) |
| 6 | GDO0 у CC1101 / CE у NRF24 |
| 7 | Управление усилителем CC1101 (модули E07) |
| 13, 14 | USART: Wi-Fi платы, SIM800, expansion-модули, Video Game Module, мост USB-UART, вывод логов |
| 15, 16 | LPUART или I2C (не одновременно) |
| 10, 12 | Отладка SWD (Devboard) |

Если у вас «комбо»-плата с несколькими радиомодулями (например, CC1101 + NRF24 + ESP32 на одной плате), смотрите её
собственную документацию: какие пины и какие настройки плагинов использует каждое радио.

## Внешние ИК-модули

1. Подключите вход драйвера ИК-светодиода к **пину 2 (A7)**, землю к GND, питание — с пина 1 (5 В), если модулю нужно.
2. Откройте `Main Menu → Infrared → GPIO Settings`.
3. Выберите `Signal Output`:
   - `Flipper` — встроенный ИК-светодиод;
   - `2 (A7)` — внешний модуль на пине 2;
   - `Detect` — прошивка сама определит подключённый модуль.
4. При `2 (A7)` здесь же можно включить `5V on GPIO`. При `Detect` пункт 5 В показывает `Auto`.

Работа с пультами — в разделе [Infrared](/ru/infrared/).

## Общие правила

1. **Выключайте Flipper перед подключением.** Большие конденсаторы «на горячую» могут повредить данные на SD-карте.
2. **Логика 3,3 В.** Не подавайте выходы Flipper на 5-вольтовую логику; входы выдерживают 5 В, только пока настроены
   как входы.
3. **Соблюдайте ограничения по току:** 1,2 А на пинах 1 и 9, 20 мА на пин I/O. См. [Распиновку](/ru/gpio/pinout).
4. **Перекрещивайте TX и RX** у UART-модулей: TX Flipper идёт на RX модуля.
5. **Вставляйте до упора.** Недовставленный модуль даёт плавающий контакт.

## См. также

- [Распиновка GPIO](/ru/gpio/pinout)
- [Приложение GPIO](/ru/gpio/gpio-app)
- [Expansion-модули](/ru/gpio/expansion-modules)
- [Модули и приложения для них](/ru/gpio/module-apps)
