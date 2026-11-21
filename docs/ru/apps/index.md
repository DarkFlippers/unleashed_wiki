---
title: Приложения
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, flipper-docs, unleashed-src]
---
# Приложения

Помимо больших встроенных инструментов (Sub-GHz, NFC, RFID, Infrared, iButton, Bad USB, GPIO), Flipper Zero запускает
**приложения**: небольшие программы в виде файлов `.fap`, которые лежат на microSD-карте. Unleashed в каждой сборке
поставляет набор собственных системных приложений, предлагает два необязательных пака приложений (Base и Extra) и
остаётся совместимым с официальным каталогом приложений (Apps Catalog).

::: tip Unleashed
Unleashed сохраняет совместимость API с официальной прошивкой, поэтому приложения из официального каталога (Flipper
Lab или мобильное приложение) в большинстве случаев тоже работают. У каждого релиза Unleashed есть сборка `e`, в
которой пак **Extra Apps** с приложениями сообщества уже стоит. См.
[Приложения в комплекте Unleashed](/ru/apps/catalog).
:::

## Где взять и как запустить приложения

- [Приложения в комплекте Unleashed](/ru/apps/catalog): встроенные приложения, паки Base и Extra и что означают буквы сборок `e`, ` ` и `c`.
- [Приложения на SD-карте (.fap)](/ru/apps/sd-card-apps): где лежат приложения, как установить их вручную или из каталога и как загрузчик проверяет версию API.
- [Archive (файловый менеджер)](/ru/apps/archive): просмотр, запуск, закрепление, переименование, перемещение и удаление сохранённых файлов.
- [Проблемы с приложениями](/ru/apps/troubleshoot): что означает каждая ошибка загрузчика и как её исправить.

## Встроенные приложения

- [U2F-ключ безопасности](/ru/apps/u2f): Flipper как второй фактор FIDO U2F.
- [Clock (часы)](/ru/apps/clock): ночные часы с регулировкой яркости, секундомером и ежедневным будильником.
- [USB / Bluetooth-пульт (HID)](/ru/apps/hid-remote): все режимы HID-пульта, по кнопкам.
- [Подключение HID-пульта](/ru/apps/controllers): подключение пульта по Bluetooth или USB и решение проблем с сопряжением.
- [FindMy Flipper](/ru/apps/find-my-flipper): Flipper виден в Apple Find My, Samsung SmartThings, Tile или Google Find My Device.
- [Стили главного меню](/ru/apps/menu-styles): меняют внешний вид главного меню (PS4, Wii, DSi, C64, CoverFlow, Grid и другие).
- [Snake (змейка)](/ru/apps/snake): классическая игра.

## Приложения из паков

- [Barcode Generator](/ru/apps/barcode)
- [Multi Converter](/ru/apps/multi-converter)
- [Sentry Safe](/ru/apps/sentry-safe)

Вспомогательные приложения для Sub-GHz, NFC и RFID (Seed Capturer, Remote Analyzer, MFKey, T5577 и другие) описаны в
своих разделах, например [Seed Capturer](/ru/subghz/seed-capturer), [Приложение MFKey](/ru/nfc/mfkey-app) и
[Приложение T5577](/ru/rfid/t5577-app).
