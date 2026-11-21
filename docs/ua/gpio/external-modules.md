---
title: Зовнішні модулі
order: 30
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SIM800.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# Зовнішні модулі

Більшість додаткових плат для Flipper Zero вставляються просто в гребінку GPIO й спілкуються з ним через одну з
трьох шин: **SPI** (піни 2–5), **UART** (піни 13/14 або 15/16) чи **I2C** (піни 15/16). Ця сторінка — карта: які
типи модулів існують, яка прошивка чи застосунок ними керує і які піни вони займають, щоб ви розуміли, які модулі
можна використовувати разом.

## Типи модулів

| Модуль | Шина / піни | Чим керується | Сторінка |
|---|---|---|---|
| Зовнішній CC1101 (Sub-GHz) | SPI 2–5, GDO0 на 6, керування підсилювачем на 7 | Вбудований застосунок Sub-GHz (`Radio Settings → Module → External`) | [Зовнішній CC1101](/ua/subghz/external-cc1101) |
| NRF24L01 (2,4 ГГц) | SPI 2–5, CE на 6 | Плагіни NRF24 Sniffer / Mouse Jacker | [NRF24](/ua/gpio/nrf24) |
| Wi-Fi-плати на ESP32 / ESP8266, Wi-Fi Devboard | UART 13/14 (SWD 10/12 для відлагодження) | Плагіни Marauder, Wi-Fi Scanner, Deauther; прошивка Black Magic | [ESP32](/ua/gpio/esp32), [Devboard](/ua/gpio/devboard) |
| GSM SIM800C / SIM800L | UART 13/14 або 15/16, живлення від піна 1 | Вбудований застосунок SIM800 | [SIM800](/ua/gpio/sim800) |
| GPS (NMEA) | UART | Плагін `[NMEA] GPS` | [GPS](/ua/gpio/gps) |
| Video Game Module | UART 13/14, піни 2–7, живлення | Прошивка Flipper + прошивка модуля | [Video Game Module](/ua/gpio/video-game-module) |
| Модулі розширення (протокол) | UART 13/14 або 15/16 | `Settings → Expansion Modules` | [Модулі розширення](/ua/gpio/expansion-modules) |
| Зовнішній ІЧ-світлодіод / ІЧ-підсилювач | Пін 2 (PA7), 5 В на піні 1 | Вбудований застосунок Infrared (`GPIO Settings`) | див. нижче |
| Датчики температури / вологості / тиску | залежить від датчика (див. README) | Плагін `Unitemp` | [README Unitemp](https://github.com/quen0n/unitemp-flipperzero#readme) |
| Будь-який пристрій I2C | I2C 15/16 | Плагін `i2c Tools`, команда CLI `i2c` | [Застосунок GPIO](/ua/gpio/gpio-app) |
| ESP32-CAM | UART | Плагін Camera Suite | [Camera Suite](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |
| Сейфи Sentry Safe / Master Lock (два дроти) | Пін 15 (C1) + GND 8 | Плагін SentrySafe | [SentrySafe](/ua/apps/sentry-safe) |

::: tip Unleashed
Unleashed додає підтримку безпосередньо у прошивку для:
- **зовнішнього CC1101** через апаратний SPI, із керуванням зовнішнім підсилювачем / світлодіодами
  (`Ext Amp & LEDs`, увімкнено типово) у `Sub-GHz → Radio Settings`;
- **зовнішніх ІЧ-модулів** у `Infrared → GPIO Settings` (автовизначення, як у стоковій прошивці);
- GSM-застосунку **SIM800** (`Apps → GPIO → SIM800`).

Самі зовнішні радіомодулі працюють на будь-якій прошивці, не лише на Unleashed. Першу реалізацію CC1101 написав
@quen0n для Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307)); ту, яку використовують сьогодні, написав **Skorp** в офіційній прошивці, і
Unleashed бере саме її.

Плагіни для решти (NRF24, Marauder, GPS, Unitemp, i2c Tools, Camera Suite…) є в пакетах Base та Extra:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest). Див.
[Застосунки на SD-карті](/ua/apps/sd-card-apps).
:::

## Конфлікти пінів

Модулі, що ділять одну шину, не можуть працювати одночасно без обережності. Найчастіші конфлікти:

| Піни | Кому потрібні |
|---|---|
| 2, 3, 4, 5 | SPI: зовнішній CC1101, NRF24 (MOSI, MISO, CS, SCK) |
| 6 | CC1101 GDO0 / NRF24 CE |
| 7 | Керування підсилювачем CC1101 (модулі E07) |
| 13, 14 | USART: Wi-Fi-плати, SIM800, модулі розширення, Video Game Module, мост USB-UART, вивід логів |
| 15, 16 | LPUART або I2C (не обидва одночасно) |
| 10, 12 | Відлагодження через SWD (Devboard) |

Якщо ви користуєтеся «комбо»-платою з кількома радіомодулями (наприклад, CC1101 + NRF24 + ESP32 на одній платі),
дивіться її власну документацію щодо того, які піни й налаштування плагінів використовує кожне радіо.

## Зовнішні ІЧ-модулі

1. Підключіть вхід драйвера ІЧ-світлодіода до **піна 2 (A7)**, GND до GND, а живлення — від піна 1 (5 В), якщо
   модулю це потрібно.
2. Відкрийте `Main Menu → Infrared → GPIO Settings`.
3. Установіть `Signal Output`:
   - `Flipper` — вбудований ІЧ-світлодіод;
   - `2 (A7)` — зовнішній модуль на піні 2;
   - `Detect` — прошивка визначає підключений модуль автоматично.
4. З вибраним `2 (A7)` тут же можна перемкнути `5V on GPIO`. З `Detect` пункт 5 В показує `Auto`.

Про користування пультами див. розділ [Інфрачервоний порт](/ua/infrared/).

## Загальні правила

1. **Вимикайте пристрій перед підключенням.** Гаряче підключення великих конденсаторів може пошкодити дані на
   SD-карті.
2. **Логіка 3,3 В.** Не подавайте виходи Flipper на 5-вольтову логіку; піни витримують 5 В лише тоді, коли
   налаштовані як входи.
3. **Дотримуйтеся обмежень струму:** 1,2 А на піні 1 і піні 9, 20 мА на кожний пін введення/виведення. Див.
   [розпіновку](/ua/gpio/pinout).
4. **Перехрещуйте TX і RX** у модулях на UART: TX Flipper іде до RX модуля.
5. **Вставляйте до кінця.** Напіввставлений модуль дає переривчастий контакт.

## Пов'язані сторінки

- [Розпіновка GPIO](/ua/gpio/pinout)
- [Застосунок GPIO](/ua/gpio/gpio-app)
- [Модулі розширення](/ua/gpio/expansion-modules)
- [Модулі та застосунки для них](/ua/gpio/module-apps)
