---
title: 125 кГц RFID
author: gromovyna
original: [https://docs.flipper.net/zero/rfid, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08]
sources: [unleashed-src, flipper-docs, unleashed-readme, gromovyna]
---
# 125 кГц RFID

Низькочастотний (LF) RFID — це «проксиміті»-технологія, на якій працюють дешеві пропуски та брелоки, домофонні
мітки, частина паркувальних і спортзальних систем, а також чипи для тварин. Такі мітки зазвичай просто передають
фіксований ID без жодної криптографії — саме тому їх легко прочитати, емулювати та клонувати.

У Flipper Zero на задній стінці є антена 125 кГц (на двосмуговій антені, поряд із котушкою NFC 13,56 МГц), якою
керує мікроконтролер STM32WB55. З її допомогою Фліппер може **читати**, **зберігати**, **емулювати** та
**записувати** LF-мітки.

::: tip Unleashed
Застосунок 125 kHz RFID — з офіційної прошивки. На додачу у збірці Unleashed є:
- меню **Settings → Write Chips**: окрім T5577 він уміє записувати **EM4305** і клони Hitag Micro (**8265**,
  **8210**, **H5.5**), а також типово вимкнену ціль **8268** (Hitag S). На екрані запису видно, який чип
  пробується і на який зрештою записалося;
- **Write and set password** — запис на чисті T5577 з одночасним встановленням пароля;
- додаткові формати в **Add Manually** (введення facility code / номера карти замість hex, HID
  H10304/H10302/S10401/H10306/Corp1000-35, Casi-Rusco), показ DEZ 8 / DEZ 10 для EM4100;
- третій прохід читання на **134,2 кГц** для чипів тварин і окремий режим **Read FDX-B (Animals)**;
- вбудований застосунок **T5577** (читання/редагування/відновлення блоків, тест, стирання, скидання та перехоплення
  паролів).
:::

## Головне меню

`Main Menu → 125 kHz RFID` відкриває меню з такими пунктами (назви — точно як у прошивці):

![Меню 125 kHz RFID із пунктами Read, Saved, Add Manually та Extra Actions](/screens/lfrfid/menu.png)

| Пункт | Що робить | Сторінка |
|---|---|---|
| **Read** | Автовизначення та читання мітки (цикл ASK → PSK → 134 кГц) | [Читання міток](/ua/rfid/read) |
| **Saved** | Перегляд `/ext/lfrfid/` — емуляція, запис, редагування, перейменування, видалення збережених ключів | [Читання міток](/ua/rfid/read), [Запис](/ua/rfid/write) |
| **Add Manually** | Створити ключ за його протоколом та ID | [Додавання вручну](/ua/rfid/add-manually) |
| **Extra Actions** | Читання з фіксованою модуляцією (ASK, PSK, FDX-B); RAW-читання та емуляція в режимі Debug | [Читання міток](/ua/rfid/read), [RAW](/ua/rfid/raw) |
| **Settings** | **Write Chips** — на які типи заготовок дозволено запис | [Запис](/ua/rfid/write) |

## Сторінки розділу

- [Читання міток](/ua/rfid/read) — читання, збереження та емуляція LF-міток; читання з фіксованою модуляцією.
- [Запис на заготовки](/ua/rfid/write) — які заготовки підходять (T5577, EM4305, Hitag Micro, 8268), налаштування
  Write Chips, запис із паролем, повідомлення про помилки.
- [Додавання вручну](/ua/rfid/add-manually) — усі протоколи Add Manually та формати введення FC/ID.
- [Підтримувані протоколи](/ua/rfid/protocols) — повна таблиця протоколів: модуляція, обсяг даних, розпізнані поля,
  підтримка запису.
- [Чипи для тварин](/ua/rfid/animal-microchips) — чипи FDX-B / FDX-A для домашніх улюбленців.
- [T5577 і Hitag Micro (від @gromovyna)](/ua/rfid/t5577-hitag) — історія H5.5 / 8265 / 8210, UX запису, стирання
  T5577.
- [Застосунок T5577](/ua/rfid/t5577-app) — читання, редагування, відновлення, тест, стирання блоків, скидання та
  перехоплення пароля.
- [RAW-запис](/ua/rfid/raw) — запис «сирого» ASK/PSK-сигналу для дослідження протоколів.
- [Фазер](/ua/rfid/fuzzer) — що прошивка постачає для застосунку RFID-фазера.
- [Формати файлів](/ua/rfid/file-format) — файли `.rfid`, `.t5577` і `.raw`.

## Де лежать файли

| Шлях | Вміст |
|---|---|
| `/ext/lfrfid/*.rfid` | Збережені ключі |
| `/ext/lfrfid/*.t5577` | Дампи блоків T5577 (відкриваються застосунком T5577) |
| `/ext/lfrfid/*.ask.raw`, `*.ask134.raw`, `*.psk.raw` | RAW-записи |
| `/ext/lfrfid/.lfrfid.settings` | Налаштування Write Chips |
| `/ext/lfrfid/assets/t5577_dict.lfrfid` | Словник паролів T5577 (перезаписується під час оновлення) |
| `/ext/lfrfid/assets/t5577_dict_user.lfrfid` | Ваші власні паролі T5577 |
| `/ext/lfrfid/assets/iso3166.lfrfid` | Назви країн для чипів FDX-B |

::: warning
Клонуйте та емулюйте лише ті мітки, які належать вам або на тестування яких ви маєте дозвіл.
:::
