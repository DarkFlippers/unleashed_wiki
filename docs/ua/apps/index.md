---
title: Застосунки
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, flipper-docs, unleashed-src]
---
# Застосунки

Окрім великих вбудованих інструментів (Sub-GHz, NFC, RFID, інфрачервоний порт, iButton, Bad USB, GPIO), Flipper Zero
виконує **застосунки** — невеликі програми у вигляді файлів `.fap`, що лежать на картці microSD. Unleashed постачає
власний набір системних застосунків у кожній збірці, пропонує два додаткові набори застосунків (Base та Extra) і
залишається сумісним з офіційним каталогом Apps Catalog.

::: tip Unleashed
Unleashed зберігає сумісність з API офіційної прошивки, тому застосунки з офіційного каталогу (Flipper Lab або
мобільний застосунок) зазвичай теж працюють. На додачу кожен реліз Unleashed має збірку `e`, у якій уже
встановлено набір **Extra Apps** зі застосунками від спільноти. Докладніше —
[Застосунки у складі Unleashed](/ua/apps/catalog).
:::

## Як отримати й запускати застосунки

- [Застосунки у складі Unleashed](/ua/apps/catalog): вбудовані застосунки, набори Base та Extra й що означають літери збірок `e`, ` ` і `c`.
- [Застосунки на SD-карті (.fap)](/ua/apps/sd-card-apps): де лежать застосунки, як встановити їх вручну або з каталогу та як завантажувач перевіряє версію API.
- [Archive (файловий менеджер)](/ua/apps/archive): перегляд, запуск, закріплення, перейменування, переміщення та видалення збережених файлів.
- [Усунення проблем із застосунками](/ua/apps/troubleshoot): що означає кожна помилка завантажувача і як її виправити.

## Вбудовані застосунки

- [Ключ безпеки U2F](/ua/apps/u2f): використання Flipper як другого фактора FIDO U2F.
- [Clock](/ua/apps/clock): нічний годинник із регулюванням яскравості, секундомір і щоденний будильник.
- [Пульт USB / Bluetooth (HID)](/ua/apps/hid-remote): усі режими застосунку HID-пульта, кнопка за кнопкою.
- [Підключення HID-пульта](/ua/apps/controllers): як підключити пульт через Bluetooth або USB і що робити з проблемами спарювання.
- [FindMy Flipper](/ua/apps/find-my-flipper): зробити Flipper видимим у Apple Find My, Samsung SmartThings, Tile або Google Find My Device.
- [Стилі головного меню](/ua/apps/menu-styles): змінити вигляд головного меню (PS4, Wii, DSi, C64, CoverFlow, Grid та інші).
- [Snake](/ua/apps/snake): класична гра.

## Застосунки з наборів

- [Barcode Generator](/ua/apps/barcode)
- [Multi Converter](/ua/apps/multi-converter)
- [Sentry Safe](/ua/apps/sentry-safe)

Допоміжні застосунки для Sub-GHz, NFC і RFID (Seed Capturer, Remote Analyzer, MFKey, T5577 та інші) описані у
власних розділах, наприклад [Seed Capturer](/ua/subghz/seed-capturer), [Застосунок MFKey](/ua/nfc/mfkey-app) і
[Застосунок T5577](/ua/rfid/t5577-app).
