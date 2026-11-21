---
title: Форматы файлов
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/resources/subghz/assets, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md]
sources: [unleashed-docs, unleashed-src]
---
# Форматы файлов Sub-GHz

Все файлы Sub-GHz — обычный текст в формате *Flipper File Format* (строки `Ключ: значение`), так что открыть и
поправить их можно на ПК в любом редакторе.

| Путь | Что это |
|---|---|
| `/ext/subghz/*.sub` | Сохранённые сигналы: ключи, RAW и BinRAW |
| `/ext/subghz/assets/setting_user` | Свои частоты, список хоппинга, свои пресеты |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Свои ключи производителей KeeLoq |
| `/ext/subghz/assets/keeloq_mfcodes` | Встроенная база ключей производителей KeeLoq (зашифрована, идёт с прошивкой) |
| `/ext/subghz/assets/nice_flor_s`, `alutech_at_4n` | Встроенные таблицы для этих протоколов |
| `/ext/subghz/assets/dangerous_settings` | Включение расширенного диапазона, см. [Частоты](/ru/subghz/frequencies#extended-range) |

## Структура файла `.sub`

Файл `.sub` состоит из трёх частей:

1. **Заголовок** — тип файла, версия, частота.
2. **Пресет** — пресет модуляции или полная пользовательская конфигурация CC1101.
3. **Данные** — имя протокола и его поля либо RAW-тайминги.

### Заголовок

| Поле | Тип | Описание |
|---|---|---|
| `Filetype` | строка | `Flipper SubGhz Key File` для ключей, `Flipper SubGhz RAW File` для RAW-записей |
| `Version` | число | Версия формата, сейчас `1` |
| `Frequency` | число | Частота в герцах, например `433920000` |

### Пресет

| Поле | Описание |
|---|---|
| `Preset` | Имя пресета. Для пользовательского — обязательно `FuriHalSubGhzPresetCustom` |
| `Custom_preset_module` | Трансивер, для Flipper Zero — `CC1101` (только для пользовательского пресета) |
| `Custom_preset_data` | Конфигурация трансивера (только для пользовательского пресета) |

Встроенные пресеты:

| Значение `Preset` | В меню | Что это |
|---|---|---|
| `FuriHalSubGhzPresetOok270Async` | `AM270` | OOK, полоса 270 кГц |
| `FuriHalSubGhzPresetOok650Async` | `AM650` | OOK, полоса 650 кГц |
| `FuriHalSubGhzPreset2FSKDev238Async` | `FM238` | 2-FSK, девиация 2.38 кГц, полоса 270 кГц |
| `FuriHalSubGhzPreset2FSKDev12KAsync` | `FM12K` | 2-FSK, девиация 12 кГц |
| `FuriHalSubGhzPreset2FSKDev476Async` | `FM476` | 2-FSK, девиация 47.6 кГц, полоса 270 кГц |

Пользовательский пресет записывается прямо в файл, поэтому другой Флиппер сможет отправить сигнал даже без этого
пресета в своих настройках.

#### Данные пользовательского пресета {#custom-preset-data}

HEX-байты через пробел: `XX YY XX YY … 00 00 ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ`

- `XX` — адрес регистра CC1101, `YY` — его значение (сколько угодно пар);
- `00 00` — конец блока регистров;
- `ZZ ×8` — 8-байтная PA-таблица (рампа усилителя мощности).

Значения регистров — в [даташите CC1101](https://www.ti.com/lit/ds/symlink/cc1101.pdf).

### Файлы-ключи

Декодированные сигналы хранят имя протокола и его поля:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

| Поле | Описание |
|---|---|
| `Protocol` | Имя протокола точно как в реестре протоколов (например, `Princeton`, `KeeLoq`, `Nice FloR-S`, `CAME Atomo`, `Security+ 2.0`) |
| `Bit` | Длина посылки в битах |
| `Key` | Посылка, HEX, 8 байт |
| `TE` | Базовая длительность импульса (квант) в мкс — для протоколов, которые её хранят |

Протоколы могут добавлять свои поля. Те, что встречаются в Unleashed:

| Поле | Где | Значение |
|---|---|---|
| `Manufacture` | KeeLoq, FAAC SLH / Genius | Производитель, чьим ключом декодируется сигнал (например, `DoorHan`, `BFT`, `Genius`) |
| `Seed` | BFT Mitto, Erreka, FAAC SLH, Genius, часть KeeLoq | Секрет пульта для secure learning |
| `CounterMode` | Nice Flor-S, CAME Atomo, Alutech AT-4N, KeeLoq, V2 Phoenix | Экспериментальное поведение счётчика, см. [Режимы счётчика](/ru/subghz/counter-mode) |
| `Secplus_packet_1`, `Pin` | Security+ 2.0 | Второй пакет; PIN клавиатуры для 86-битных посылок ([Security+ PIN](/ru/subghz/secplus-pin)) |
| `Cert` | Nice O-Code | Сертификат приёмника ([Nice O-Code](/ru/subghz/nice-o-code)) |

Пример с пользовательским пресетом:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetCustom
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

::: warning Правка файлов динамических кодов
Ручное изменение `Key` у динамического протокола почти никогда не даёт валидный код. Чтобы поменять серийник, кнопку
или счётчик, используйте [Add Manually [Advanced]](/ru/subghz/add-manually) или, в режиме Debug,
`Saved → файл → Signal Settings`.
:::

### RAW-файлы

Записи из [Read RAW](/ru/subghz/read-raw):

```text
Filetype: Flipper SubGhz RAW File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: RAW
RAW_Data: 29262 361 -68 2635 -66 24113 -66 11 ...
RAW_Data: -424 205 -412 159 -412 381 -240 181 ...
```

- `Protocol` — обязательно `RAW`.
- `RAW_Data` — длительности в мкс: положительные — несущая есть, отрицательные — нет. Значения ненулевые, первое
  положительное, знаки чередуются. До 512 значений в строке; строк может быть сколько угодно.

Длинные посылки читаются с SD-карты во время передачи. При очень коротких таймингах (менее 10 мкс) медленная карта может не
успевать, и передача оборвётся раньше конца.

### BinRAW-файлы

Опция `Bin RAW` в `Read → Config` создаёт файлы **BinRAW**. В отличие от RAW, в них хранится только полезная
повторяющаяся последовательность с восстановленной скоростью передачи и без эфирного шума, поэтому ими можно
воспроизвести почти любой **статический** протокол — известный Флипперу или нет. При чтении держите кнопку пульта
подольше, чтобы накопилось достаточно данных.

| Поле | Описание |
|---|---|
| `Protocol` | `BinRAW` |
| `Bit` | Длина данных всего файла в битах (макс. 4096) |
| `TE` | Квант времени, мкс |
| `Bit_RAW` | Длина следующего блока `Data_RAW` в битах |
| `Data_RAW` | Закодированные длительности: каждый бит = один `TE`; `1` — несущая есть, `0` — нет |

Пример: `TE: 100`, `Bit_RAW: 8`, `Data_RAW: 37` → `0b00110111` → будет передано `-200 200 -100 300`.
Пары `Bit_RAW` + `Data_RAW` образуют повторяемые блоки; несколько блоков передаются друг за другом.

```text
Protocol: BinRAW
Bit: 1572
TE: 597
Bit_RAW: 260
Data_RAW: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F 4A B5 55 4C B3 52 AC D5 2D 53 52 AD 4A D5 35 00
```

## `setting_user` {#setting-user}

Дополнительные частоты и пресеты, загружаются при старте Sub-GHz. Переименуйте `setting_user.example` в
`setting_user`.

```text
Filetype: Flipper SubGhz Setting File
Version: 1

# Add standard frequencies included with firmware and place user frequencies after them
Add_standard_frequencies: true

# Default frequency for "Read" and "Read Raw"
Default_frequency: 433920000

# Frequencies for "Read", "Read Raw" and "Frequency Analyzer"
Frequency: 300000000
Frequency: 310000000

# Frequencies for hopping mode (keep this list small)
Hopper_frequency: 300000000
Hopper_frequency: 310000000

# Custom preset
Custom_preset_name: AM_1
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
```

| Ключ | Значение |
|---|---|
| `Add_standard_frequencies` | `true` — список прошивки + ваши (добавляются после него); `false` — только ваши (тогда заполните и `Frequency`, и `Hopper_frequency`) |
| `Default_frequency` | Частота, с которой стартуют Read / Read RAW |
| `Frequency` | Добавляет частоту в основной список (9 цифр, Гц). Можно повторять |
| `Hopper_frequency` | Добавляет частоту в хоппинг. Повтор частоты — Флиппер будет слушать её чаще |
| `Custom_preset_name` / `_module` / `_data` | Свой пресет модуляции, появится в списке `Modulation` под этим именем. Формат данных — [выше](#custom-preset-data) |

В файле `.example` есть закомментированные пресеты, которые можно включить: `FM95`, `FM15k` (2-FSK, полоса 200 кГц /
фильтр 135 кГц, девиация 15.86 кГц), `Pagers`, `AM_1`, `AM_2`.

## `keeloq_mfcodes_user` {#keeloq-mfcodes-user}

Свои ключи производителей KeeLoq, загружаются при старте в дополнение к встроенной (зашифрованной) базе. Создайте файл
из `keeloq_mfcodes_user.example`, удалите тестовые ключи и **оставьте пустую строку в конце**.

```text
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:2:Test2
```

Каждая строка — `KEY:METHOD:NAME`:

- `KEY` — 64-битный ключ производителя, 16 HEX-цифр;
- `NAME` — имя без пробелов, до 64 символов (показывается как производитель в Read);
- `METHOD` — тип обучения (learning):

| Значение | Learning |
|---|---|
| `0` | перебор всех: предыдущий и мануфактурный ключ в прямом и обратном порядке байт |
| `1` | Simple Learning |
| `2` | Normal Learning |
| `3` | Secure Learning (нужен Seed) |
| `4` | Magic XOR type 1 |
| `5` | FAAC SLH |
| `6` | Magic Serial type 1 |
| `7` | Magic Serial type 2 |
| `8` | Magic Serial type 3 |

`Encryption: 0` — файл в открытом виде; пользовательские файлы не шифруются. Подробнее о типах обучения —
[KeeLoq](/ru/subghz/keeloq).

## См. также

- [Read](/ru/subghz/read) · [Read RAW](/ru/subghz/read-raw) · [Частоты](/ru/subghz/frequencies) · [Radio Settings](/ru/subghz/settings)
- [KeeLoq](/ru/subghz/keeloq) · [Режимы счётчика](/ru/subghz/counter-mode) · [Файлы карт Sub-GHz Remote](/ru/subghz/remote)
