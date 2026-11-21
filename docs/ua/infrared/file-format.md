---
title: Формат ІЧ-файлів
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared]
sources: [unleashed-docs, unleashed-src]
---
# Формат інфрачервоних файлів (`.ir`)

Усі ІЧ-дані на Flipper зберігаються як звичайний текст у Flipper Format (рядки `key: value`). Розширення завжди
`.ir`. Є три різновиди, які відрізняються лише заголовком `Filetype` і призначенням.

| Filetype | Для чого | Розташування |
|---|---|---|
| `IR signals file` | Ваші пульти (записані, збережені з універсального пульта, завантажені із застосунку) | `/ext/infrared/` |
| `IR library file` | Бібліотеки універсальних пультів | `/ext/infrared/assets/` |
| тестовий файл (`.irtest`) | Юніт-тести декодерів/енкодерів | лише в репозиторії прошивки |

## Файл пульта

### Приклад

```text
Filetype: IR signals file
Version: 1
#
name: Button_1
type: parsed
protocol: NECext
address: EE 87 00 00
command: 5D A0 00 00
#
name: Button_2
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 504 3432 502 483 500 484 510 502 502 482 501 485 509 1452 504 1458 509 1452 504 481 501 474 509 3420 503
#
name: Button_3
type: parsed
protocol: SIRC
address: 01 00 00 00
command: 15 00 00 00
```

Файл містить будь-яку кількість кнопок. Кожна кнопка починається з `name:`; рядок-коментар `#` між кнопками
потрібен лише для читабельності.

### Поля

| Поле | Де використовується | Тип | Опис |
|---|---|---|---|
| `name` | в обох | рядок | Назва кнопки. Лише друковані символи ASCII. Інтерфейс Flipper обмежує назви 23 символами. |
| `type` | в обох | рядок | `parsed` або `raw`. |
| `protocol` | parsed | рядок | Назва протоколу точно як у [переліку протоколів](/ua/infrared/protocols) (команда CLI `ir` також її виводить). |
| `address` | parsed | hex | Адреса, завжди **4 байти**, починаючи з молодшого: `EE 87 00 00` = `0x87EE`. |
| `command` | parsed | hex | Команда, завжди **4 байти**, починаючи з молодшого. |
| `frequency` | raw | uint32 | Частота несучої в Гц, зазвичай `38000`. Допустимий діапазон 10000-1000000. |
| `duty_cycle` | raw | float | Коефіцієнт заповнення несучої, зазвичай `0.33`. Мусить бути > 0 і ≤ 1. |
| `data` | raw | список uint32 | Тайминги в мікросекундах між змінами рівня (імпульс, пауза, імпульс, …), через пробіл. **Максимум 1024** значення. |

### Допустимі значення `protocol`

```text
NEC  NECext  NEC42  NEC42ext  Samsung32  RC6  RC5  RC5X  SIRC  SIRC15  SIRC20  Kaseikyo  RCA  Pioneer
```

::: tip Unleashed
`RCA` — доповнення Unleashed. `Pioneer` є у прошивці, хоча офіційний документ про формат його поки що не
перелічує.
:::

### Редагування вручну

- Залишайте два рядки заголовка (`Filetype`, `Version`) на початку.
- Кожній кнопці потрібні `name` і `type`, а далі або `protocol`/`address`/`command`, або
  `frequency`/`duty_cycle`/`data`.
- Щоб об'єднати два пульти, скопіюйте блоки кнопок одного файлу в кінець іншого.
- Байти адреси й команди мусять залишатися довжиною 4 байти, навіть якщо протокол використовує менше бітів;
  невикористані байти — `00`.
- Якщо Flipper пише *«Failed to load …»*, одне з полів сформоване неправильно (наприклад, рядок `data` для RAW
  містить понад 1024 значення або частота поза допустимим діапазоном).

## Файли бібліотек {#library-files}

Файли бібліотек мають точно таку саму структуру; відрізняється лише заголовок:

```text
Filetype: IR library file
Version: 1
# Last Updated 5th Oct, 2024
# Last Checked 5th Oct, 2024
#
# Model: Example TV 1234
name: Power
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Універсальний пульт шукає сигнали **за назвою**, тому назви мусять точно відповідати кнопкам бібліотеки (див.
таблицю в [Як надіслати свої записи](/ua/infrared/captures#button-names-per-library)). Нові моделі додаються в
кінець файлу, а перед ними ставиться коментар `# Model: …`.

Файл бібліотеки не можна відкрити через `Saved Remotes`: застосунок повідомляє
*«Library file … can't be opened as a remote»*.

## Тестові файли (`.irtest`)

Використовуються лише юніт-тестами прошивки
(`applications/debug/unit_tests/resources/unit_tests/infrared` у репозиторії). Вони виглядають як файли пультів,
плюс тип `parsed_array` для цілих послідовностей декодованих повідомлень:

| Поле | Де використовується | Тип | Опис |
|---|---|---|---|
| `name` | в обох | рядок | Назва сигналу, правила назв див. нижче. |
| `type` | в обох | рядок | `parsed_array` або `raw`. |
| `count` | parsed_array | uint32 | Кількість повідомлень у масиві, щонайменше 1. |
| `protocol`, `address`, `command` | parsed_array | | Як вище, по одному на повідомлення. |
| `repeat` | parsed_array | bool | Чи є повідомлення повтором (кнопку тримають). |
| `frequency`, `duty_cycle`, `data` | raw | | Як вище. |

Назви мають вигляд `<name><test_number>`: `decoder_input1` (сирий вхід для декодера, він же очікуваний вихід
енкодера), `decoder_expected1` (очікуваний вихід декодера, він же вхід енкодера), `encoder_decoder_input1`
(розібраний масив, який мусить вціліти після циклу кодування → декодування). Такий тестовий файл мусить бути в
кожного протоколу.

## Пов'язані сторінки

- [Протоколи](/ua/infrared/protocols)
- [Як надіслати свої записи](/ua/infrared/captures)
- [Запис і надсилання сигналів](/ua/infrared/read)
