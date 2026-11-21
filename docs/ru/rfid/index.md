---
title: 125 кГц RFID
author: gromovyna
original: [https://docs.flipper.net/zero/rfid, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08]
sources: [unleashed-src, flipper-docs, unleashed-readme, gromovyna]
---
# 125 кГц RFID

Низкочастотный (LF) RFID — это «проксимити»-технология дешёвых пропусков и брелоков, домофонных меток, части
парковочных и фитнес-систем, а также чипов животных. Такие метки обычно просто передают фиксированный ID без всякой
криптографии, поэтому их легко прочитать, эмулировать и скопировать.

У Flipper Zero на задней стороне есть 125 кГц антенна (на двухдиапазонной антенне, рядом с катушкой NFC 13,56 МГц),
которой управляет MCU STM32WB55. Флиппер умеет **читать**, **сохранять**, **эмулировать** и **записывать** LF-метки.

::: tip Unleashed
Приложение 125 kHz RFID — из официальной прошивки. Вдобавок в сборке Unleashed есть:
- меню **Settings → Write Chips**: кроме T5577 можно писать **EM4305** и клоны Hitag Micro (**8265**, **8210**,
  **H5.5**), плюс отключённая по умолчанию цель **8268** (Hitag S). При записи на экране видно, какой чип пробуется и
  на какой записалось;
- **Write and set password** — запись на T5577 с установкой пароля;
- дополнительные форматы в **Add Manually** (ввод FC/номера карты вместо hex, HID H10304/H10302/S10401/H10306/
  Corp1000-35, Casi-Rusco), отображение DEZ 8 / DEZ 10 для EM4100;
- третий проход чтения на **134,2 кГц** для чипов животных и отдельный режим **Read FDX-B (Animals)**;
- встроенное приложение **T5577** (чтение/редактирование/восстановление блоков, тест, очистка, снятие и перехват
  пароля).
:::

## Главное меню

`Main Menu → 125 kHz RFID` (названия пунктов — как на устройстве):

![Меню 125 kHz RFID: Read, Saved, Add Manually и Extra Actions](/screens/lfrfid/menu.png)

| Пункт | Что делает | Страница |
|---|---|---|
| **Read** | Автоопределение и чтение метки (цикл ASK → PSK → 134 кГц) | [Чтение](/ru/rfid/read) |
| **Saved** | Файлы в `/ext/lfrfid/` — эмуляция, запись, правка, переименование, удаление | [Чтение](/ru/rfid/read), [Запись](/ru/rfid/write) |
| **Add Manually** | Создать ключ по протоколу и ID | [Добавление вручную](/ru/rfid/add-manually) |
| **Extra Actions** | Чтение с фиксированной модуляцией (ASK, PSK, FDX-B); RAW в режиме Debug | [Чтение](/ru/rfid/read), [RAW](/ru/rfid/raw) |
| **Settings** | **Write Chips** — на какие типы заготовок разрешена запись | [Запись](/ru/rfid/write) |

## Страницы раздела

- [Чтение меток](/ru/rfid/read) — чтение, сохранение и эмуляция; чтение с фиксированной модуляцией.
- [Запись на заготовки](/ru/rfid/write) — какие болванки подходят (T5577, EM4305, Hitag Micro, 8268), настройка Write
  Chips, запись с паролем, сообщения об ошибках.
- [Добавление вручную](/ru/rfid/add-manually) — все протоколы Add Manually и форматы ввода FC/ID.
- [Поддерживаемые протоколы](/ru/rfid/protocols) — таблица: модуляция, размер данных, поля, поддержка записи.
- [Чипы животных](/ru/rfid/animal-microchips) — FDX-B / FDX-A.
- [T5577 и Hitag Micro (от @gromovyna)](/ru/rfid/t5577-hitag) — история H5.5 / 8265 / 8210, UX записи, очистка T5577.
- [Приложение T5577](/ru/rfid/t5577-app) — работа с блоками, тест, очистка, снятие и перехват пароля.
- [RAW-запись](/ru/rfid/raw) — запись «сырого» ASK/PSK-сигнала для исследований.
- [Фаззер](/ru/rfid/fuzzer) — что прошивка поставляет для RFID-фаззера.
- [Форматы файлов](/ru/rfid/file-format) — `.rfid`, `.t5577` и `.raw`.

## Где лежат файлы

| Путь | Содержимое |
|---|---|
| `/ext/lfrfid/*.rfid` | Сохранённые ключи |
| `/ext/lfrfid/*.t5577` | Дампы блоков T5577 (открываются приложением T5577) |
| `/ext/lfrfid/*.ask.raw`, `*.ask134.raw`, `*.psk.raw` | RAW-записи |
| `/ext/lfrfid/.lfrfid.settings` | Настройка Write Chips |
| `/ext/lfrfid/assets/t5577_dict.lfrfid` | Словарь паролей T5577 (перезаписывается при обновлении) |
| `/ext/lfrfid/assets/t5577_dict_user.lfrfid` | Ваши пароли T5577 |
| `/ext/lfrfid/assets/iso3166.lfrfid` | Названия стран для чипов FDX-B |

::: warning
Копируйте и эмулируйте только свои метки или те, на тестирование которых у вас есть разрешение.
:::
