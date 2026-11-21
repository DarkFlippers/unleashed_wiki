---
title: Bad USB
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Bad USB

Приложение **Bad USB** превращает Флиппер в клавиатуру (и мышь), которая набирает на компьютере заранее
подготовленный скрипт. Компьютер видит обычное HID-устройство (Human Interface Device), драйверы не нужны. Скрипты
пишутся на расширенном **DuckyScript** (язык USB Rubber Ducky) и хранятся как обычные `.txt`-файлы на microSD.

![Bad USB](/img/remote/2a3485aa02031f3f.png)

Типичные законные применения: автоматизация рутинной настройки своих машин, ввод длинных паролей и конфигов,
установка софта на свежий ПК, демонстрации и обучение по информационной безопасности.

::: danger Закон
Устройство для инъекции нажатий может всё, что может человек за клавиатурой. Запускайте скрипты только на своих
компьютерах или там, где вам явно разрешили тестирование.
:::

Приложение работает по **USB**-кабелю или по **Bluetooth (BLE)** — во втором случае хост видит Bluetooth-клавиатуру.

::: tip Unleashed
В Unleashed прямо в приложение Bad USB встроен **BadKB** (авторы Willy-JL, ClaraCrazy и контрибьюторы XFW):
- **режим BLE** с настраиваемым именем устройства, MAC-адресом, режимом сопряжения и постоянным сопряжением, плюс
  команды скрипта `BLE_ID` / `BT_ID`;
- настройки **USB-идентичности**: производитель и название продукта, VID/PID, рандомизация;
- **раскладки клавиатуры** для многих языков ([от rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl));
- команда **`DUCKY_LANG`**, чтобы скрипт сам выбирал раскладку (новинка текущего релиза, PR #1224 от @ANTONiO-eagle).
:::

## Файлы

| Путь | Содержимое |
|---|---|
| `/ext/badusb/` | Ваши скрипты (`.txt`). Файловый браузер приложения открывается здесь. |
| `/ext/badusb/examples/` | Демо-скрипты из комплекта прошивки (Windows, macOS, GNOME, ChromeOS, тест мыши, установщики qFlipper). |
| `/ext/badusb/assets/layouts/` | Файлы раскладок (`.kl`). См. [Раскладки клавиатуры](/ru/badusb/layouts). |
| `/ext/badusb/.badusb.settings` | Настройки приложения: глобальная раскладка, режим USB/BLE, USB- и BLE-идентичность. |

Загружайте скрипты через [qFlipper](/ru/mobile/qflipper), [мобильное приложение](/ru/mobile/mobile-app) или просто
копированием на SD-карту. Файл с тем же именем перезаписывается без предупреждения.

## Страницы раздела

| Страница | О чём |
|---|---|
| [Работа с Bad USB](/ru/badusb/usage) | Запуск скриптов по USB и BLE, меню Config, все настройки |
| [Формат скриптов](/ru/badusb/script-format) | Полный справочник команд: STRING, DELAY, HOLD/RELEASE, ALTCHAR, MEDIA, мышь, ID, DUCKY_LANG… |
| [Примеры](/ru/badusb/examples) | Безопасные скрипты для начала |
| [Раскладки клавиатуры](/ru/badusb/layouts) | Какие раскладки есть, как они работают, выбор раскладки для скрипта |
