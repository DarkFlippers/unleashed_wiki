---
title: "JavaScript: огляд"
sidebarTitle: "JS: огляд"
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_about.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app]
sources: [unleashed-docs, unleashed-src]
---
# JavaScript на Flipper Zero

Раніше написати застосунок для Flipper Zero означало взятися за C, розгорнути повний тулчейн і перечитати купу вихідного коду інших застосунків. Тепер прошивка містить **вбудований рушій JavaScript**, тож ви можете написати звичайний файл `.js`, скопіювати його на SD-картку й запустити просто з пристрою. Нічого компілювати на ПК не потрібно, а скриптами легко обмінюватися.

- Скрипти лежать у `/ext/apps/Scripts/` і запускаються з `Main Menu → Apps → Scripts` або з CLI командою `js <path>`.
- Рушій побудований на [mJS](https://github.com/cesanta/mjs) — інтерпретаторі JavaScript, розробленому для мікроконтролерів: йому потрібно менше ніж 50 КБ флеш-пам’яті та близько 2 КБ RAM. Flipper залишає ядро mJS і додає розширення, як-от компактні бінарні масиви (`ArrayBuffer`, типізовані масиви).
- Скрипти можуть працювати з GUI, кнопками, USB HID (BadUSB), GPIO, UART, файловою системою та іншим через **модулі**, що завантажуються функцією `require()`.

::: warning mJS — не браузерний рушій
mJS підтримує лише підмножину JavaScript. Найважливіше: **немає замикань** (функція не може використовувати змінні з навколишньої області видимості; обхідний шлях описано в [Циклі подій](/ua/dev/js-event-loop)), рядки однобайтові й без підтримки UTF-8, а багатьох об’єктів стандартної бібліотеки просто немає. Повний перелік обмежень — у [README mJS](https://github.com/cesanta/mjs).
:::

## З чого почати

1. [Ваш перший JS-застосунок](/ua/dev/js-first-app): написати скрипт, скопіювати його на Flipper, запустити з меню або CLI.
2. [JavaScript SDK](/ua/dev/js-sdk): TypeScript, автодоповнення коду й завантаження на пристрій однією командою `npm start`.
3. [Використання JS-модулів](/ua/dev/js-modules): як працює `require()`.

## Довідник з мови

- [Типи даних](/ua/dev/js-data-types)
- [Вбудовані функції](/ua/dev/js-builtin): `print`, `delay`, `require`, `load`, методи рядків і масивів, перевірка сумісності SDK.

## Довідник модулів

| Модуль | Назва для `require()` | Сторінка |
|---|---|---|
| Цикл подій | `event_loop` | [Цикл подій](/ua/dev/js-event-loop) |
| GUI | `gui`, `gui/*` | [GUI](/ua/dev/js-gui), [Представлення GUI](/ua/dev/js-gui-views) |
| BadUSB (USB HID-клавіатура) | `badusb` | [BadUSB](/ua/dev/js-badusb) |
| Інформація про пристрій | `flipper` | [Flipper](/ua/dev/js-flipper) |
| GPIO, ADC, PWM | `gpio` | [GPIO](/ua/dev/js-gpio) |
| Математика | `math` | [Math](/ua/dev/js-math) |
| Сповіщення: світлодіод, вібро, звук | `notification` | [Notification](/ua/dev/js-notification) |
| UART | `serial` | [Serial](/ua/dev/js-serial) |
| Файли й папки | `storage` | [Storage](/ua/dev/js-storage) |

Приклади скриптів для кожного модуля встановлюються разом із прошивкою в `/ext/apps/Scripts/js_examples/` (наприклад, `gui.js`, `badusb_demo.js`, `gpio.js`, `storage.js`). Прочитати їх — найшвидший спосіб опанувати API.

## Додатки Unleashed: модулі без офіційної документації {#unleashed-extras}

::: tip Unleashed
Unleashed повідомляє про себе як `flipper.firmwareVendor === "unleashed"` і постачає **додаткові JS-модулі**, яких немає в стоковій прошивці. Офіційна документація з JS їх не описує, тому сторінки нижче написані за вихідним кодом прошивки (`applications/system/js_app/modules/`) і типами TypeScript у `packages/fz-sdk/`. Кожен модуль водночас є «можливістю» (feature) SDK, тож перевіряйте його наявність через `doesSdkSupport([...])` або `checkSdkFeatures([...])` (див. [Вбудовані функції](/ua/dev/js-builtin#sdk-compatibility)), щоб скрипт працював і на інших прошивках.
:::

Повний список додаткових можливостей, про які повідомляє Unleashed: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`.

| Модуль | Назва можливості | Що робить | Сторінка |
|---|---|---|---|
| `subghz` | `subghz` | Керує радіо Sub-GHz (внутрішнім або зовнішнім CC1101): RX, RSSI, частота, передача файлів `.sub` | [JS: subghz](/ua/dev/js-subghz) |
| `infrared` | `infrared-send` | Надсилає ІЧ-сигнали за протоколом або як сирі тайминги | [JS: infrared](/ua/dev/js-infrared) |
| `blebeacon` | `blebeacon` | Транслює власні рекламні пакети BLE (extra beacon) | [JS: blebeacon](/ua/dev/js-blebeacon) |
| `usbdisk` | `usbdisk` | Емулює USB-накопичувач з образу диска | [JS: usbdisk](/ua/dev/js-usbdisk) |
| `i2c` | `i2c` | Обмінюється даними з I2C-пристроями на гребінці GPIO | [JS: i2c](/ua/dev/js-i2c) |
| `spi` | `spi` | Обмінюється даними з SPI-пристроями на зовнішній шині SPI | [JS: spi](/ua/dev/js-spi) |
| `vgm` | `vgm` | Читає IMU (pitch/roll/yaw) модуля Video Game Module | [JS: vgm](/ua/dev/js-vgm) |

Модуль GUI також має представлення, яких немає в офіційній документації: `button_menu`, `button_panel`, `menu`, `number_input`, `popup`, `vi_list`. Їх описано на сторінці [Представлення GUI](/ua/dev/js-gui-views).

API прошивки, яких немає в цій вікі, шукайте в офіційному [довіднику Doxygen](https://developer.flipper.net/flipperzero/doxygen/).

## Пов’язані сторінки

- [Написання застосунків на C](/ua/dev/first-app-c) — коли JS уже не вистачає за швидкістю або гнучкістю.
- [Формат скриптів BadUSB](/ua/badusb/script-format) — класична альтернатива JS-модулю `badusb` у вигляді DuckyScript.
