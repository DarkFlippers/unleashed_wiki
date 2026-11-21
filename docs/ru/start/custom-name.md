---
title: Своё имя Флиппера
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/CustomFlipperName.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/namechanger, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-docs, unleashed-src]
---
# Своё имя Флиппера

У каждого Флиппера есть заводское имя. Оно видно в паспорте, в **About**, в списках Bluetooth-устройств и в qFlipper.
В Unleashed его можно заменить своим.

::: tip Unleashed
В стоковой прошивке нет меню для переименования устройства. В Unleashed это **Settings → Desktop → Change Flipper
Name**, и имя **сохраняется при обновлениях прошивки**, потому что хранится на microSD-карте.
:::

## Задать имя

1. Откройте **Main Menu → Settings → Desktop → Change Flipper Name**.
2. Введите новое имя. В заголовке клавиатуры написано `Leave empty for default` («оставьте пустым для имени по
   умолчанию»).
   - **от 2 до 8 символов**;
   - **только латинские буквы и цифры** (`A–Z`, `a–z`, `0–9`). На другие символы появится *«Please only enter letters
     and numbers!»*.
3. Выберите **Save**.
4. Появится сообщение **`Name is set!`** / *«Your Flipper will be restarted on exit.»* («Флиппер перезагрузится при
   выходе»).
5. Выйдите из настроек кнопкой <kbd>BACK</kbd> — Флиппер **перезагрузится автоматически**.
6. После перезагрузки новое имя видно в паспорте, в **Settings → About** и по Bluetooth.

## Вернуть заводское имя

1. Откройте **Settings → Desktop → Change Flipper Name**.
2. Сотрите все символы, оставьте поле **пустым**.
3. Нажмите **Save** и выйдите из настроек. Флиппер перезагрузится с исходным именем.

## Как это работает

- Имя сохраняется в файл **`/ext/dolphin/name.settings`** на SD-карте:
  ```text
  Filetype: Flipper Name File
  Version: 1
  Name: MyFlip
  ```
- При загрузке служба `namechanger` ждёт SD-карту, читает этот файл и применяет имя, если оно корректно: верные
  заголовок и версия, 2–8 символов, только буквы и цифры. Затем она перезапускает USB-последовательный порт и
  Bluetooth-профиль, чтобы они подхватили новое имя.
- Сохранение пустого имени удаляет файл.
- Служба работает только при обычной загрузке — не в апдейтере и не в DFU.

Поскольку имя хранится на карте, после обновлений оно остаётся. Пропадёт, если отформатировать или заменить карту
либо удалить файл.

## Проблемы

| Проблема | Решение |
|---|---|
| Имя не сменилось | Вы вышли из настроек (имя применяется после перезагрузки)? Вставлена ли SD-карта? Имя — 2–8 букв/цифр? Имя из 1 символа сохранится, но при загрузке будет проигнорировано |
| Мобильное приложение перестало подключаться | Изменилось Bluetooth-имя. Забудьте Флиппер в приложении **и** в настройках Bluetooth телефона, на Флиппере выполните **Settings → Bluetooth → Unpair All Devices** и сопрягите заново |
| Файл имени, скопированный откуда-то, не работает | Проверьте заголовок `Flipper Name File`, `Version: 1` и правила для имени |
