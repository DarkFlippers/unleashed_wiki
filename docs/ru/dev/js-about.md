---
title: "JavaScript: обзор"
sidebarTitle: "JS: обзор"
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_about.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app]
sources: [unleashed-docs, unleashed-src]
---
# JavaScript на Flipper Zero

Раньше для приложения под Flipper Zero нужен был C, полноценный тулчейн и долгое изучение чужих исходников. Теперь в прошивке есть **встроенный движок JavaScript**: пишете обычный `.js`-файл, кладёте на SD-карту и запускаете прямо с устройства. Компилировать на ПК ничего не нужно, а скриптами легко делиться.

- Скрипты лежат в `/ext/apps/Scripts/` и запускаются из `Main Menu → Apps → Scripts` или из CLI командой `js <путь>`.
- Движок основан на [mJS](https://github.com/cesanta/mjs), интерпретаторе JavaScript для микроконтроллеров: ему нужно меньше 50 КБ флеша и около 2 КБ ОЗУ. Flipper сохранил ядро mJS и добавил улучшения, например компактные бинарные массивы (`ArrayBuffer`, типизированные массивы).
- Через **модули**, подключаемые `require()`, скрипты работают с GUI, кнопками, USB HID (BadUSB), GPIO, UART, файловой системой и т. д.

::: warning mJS — не браузерный движок
mJS поддерживает только подмножество JavaScript. Главное: **нет замыканий** (функция не видит переменные внешней области; обходной путь описан в [Event loop](/ru/dev/js-event-loop)), строки однобайтовые без поддержки UTF-8, многих стандартных объектов нет. Полный список ограничений см. в [README mJS](https://github.com/cesanta/mjs).
:::

## С чего начать

1. [Первое JS-приложение](/ru/dev/js-first-app): пишем скрипт, копируем на Flipper, запускаем из меню или CLI.
2. [JavaScript SDK](/ru/dev/js-sdk): TypeScript, автодополнение и загрузка одной командой `npm start`.
3. [Использование модулей](/ru/dev/js-modules): как работает `require()`.

## Справочник по языку

- [Типы данных](/ru/dev/js-data-types)
- [Встроенные функции](/ru/dev/js-builtin): `print`, `delay`, `require`, `load`, методы строк и массивов, проверка совместимости SDK.

## Справочник по модулям

| Модуль | Имя для `require()` | Страница |
|---|---|---|
| Цикл событий | `event_loop` | [Event loop](/ru/dev/js-event-loop) |
| Интерфейс | `gui`, `gui/*` | [GUI](/ru/dev/js-gui), [Виды GUI](/ru/dev/js-gui-views) |
| BadUSB (USB-клавиатура) | `badusb` | [BadUSB](/ru/dev/js-badusb) |
| Информация об устройстве | `flipper` | [Flipper](/ru/dev/js-flipper) |
| GPIO, АЦП, ШИМ | `gpio` | [GPIO](/ru/dev/js-gpio) |
| Математика | `math` | [Math](/ru/dev/js-math) |
| Уведомления (LED / вибро / звук) | `notification` | [Notification](/ru/dev/js-notification) |
| UART | `serial` | [Serial](/ru/dev/js-serial) |
| Файлы и папки | `storage` | [Storage](/ru/dev/js-storage) |

Примеры скриптов для всех модулей ставятся вместе с прошивкой в `/ext/apps/Scripts/js_examples/` (например, `gui.js`, `badusb_demo.js`, `gpio.js`, `storage.js`). Это самый быстрый способ разобраться в API.

## Дополнения Unleashed: модули без официальной документации {#unleashed-extras}

::: tip Unleashed
Unleashed возвращает `flipper.firmwareVendor === "unleashed"` и содержит **дополнительные JS-модули**, которых нет в стоковой прошивке. В официальной документации JS их нет, поэтому страницы ниже написаны по исходникам прошивки (`applications/system/js_app/modules/`) и TypeScript-типам в `packages/fz-sdk/`. Каждый модуль — ещё и «фича» SDK: проверяйте её через `doesSdkSupport([...])` или `checkSdkFeatures([...])` (см. [Встроенные функции](/ru/dev/js-builtin#sdk-compatibility)), чтобы скрипт работал и на других прошивках.
:::

Полный список фич, которые сообщает Unleashed: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`.

| Модуль | Фича | Что делает | Страница |
|---|---|---|---|
| `subghz` | `subghz` | Управление радиомодулем Sub-GHz (встроенный или внешний CC1101): приём, RSSI, частота, отправка `.sub`-файлов | [JS: subghz](/ru/dev/js-subghz) |
| `infrared` | `infrared-send` | Отправка ИК-сигналов по протоколу или в виде сырых таймингов | [JS: infrared](/ru/dev/js-infrared) |
| `blebeacon` | `blebeacon` | Рассылка произвольных BLE-advertisement пакетов (extra beacon) | [JS: blebeacon](/ru/dev/js-blebeacon) |
| `usbdisk` | `usbdisk` | Эмуляция USB-накопителя из образа диска | [JS: usbdisk](/ru/dev/js-usbdisk) |
| `i2c` | `i2c` | Работа с I2C-устройствами на гребёнке GPIO | [JS: i2c](/ru/dev/js-i2c) |
| `spi` | `spi` | Работа с SPI-устройствами на внешней шине SPI | [JS: spi](/ru/dev/js-spi) |
| `vgm` | `vgm` | Чтение IMU (pitch/roll/yaw) модуля Video Game Module | [JS: vgm](/ru/dev/js-vgm) |

У модуля GUI также есть виды, которых нет в официальной документации: `button_menu`, `button_panel`, `menu`, `number_input`, `popup`, `vi_list`. Они описаны на странице [Виды GUI](/ru/dev/js-gui-views).

API прошивки, которых нет в этой вики, ищите в официальном [справочнике Doxygen](https://developer.flipper.net/flipperzero/doxygen/).

## См. также

- [Приложения на C](/ru/dev/first-app-c), когда JS не хватает скорости или гибкости.
- [Формат скриптов BadUSB](/ru/badusb/script-format): классический DuckyScript как альтернатива JS-модулю `badusb`.
