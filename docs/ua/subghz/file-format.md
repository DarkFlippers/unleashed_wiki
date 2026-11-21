---
title: Формати файлів
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/resources/subghz/assets, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md]
sources: [unleashed-docs, unleashed-src]
---
# Формати файлів Sub-GHz

Усі файли Sub-GHz — це звичайний текст у *Flipper File Format* (рядки `Key: value`), тому їх можна дивитися й
редагувати на ПК. На цій сторінці описано файли сигналів (`.sub`) і файли конфігурації в `/ext/subghz/assets/`.

| Шлях | Що це |
|---|---|
| `/ext/subghz/*.sub` | Збережені сигнали: ключі, RAW і BinRAW |
| `/ext/subghz/assets/setting_user` | Ваші частоти, перелік для hopper, користувацькі пресети |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Ваші ключі виробників KeeLoq |
| `/ext/subghz/assets/keeloq_mfcodes` | Вбудовані ключі виробників KeeLoq (зашифровані, постачаються з прошивкою) |
| `/ext/subghz/assets/nice_flor_s`, `alutech_at_4n` | Вбудовані таблиці для цих протоколів |
| `/ext/subghz/assets/dangerous_settings` | Перемикач розширеного діапазону частот, див. [Частоти](/ua/subghz/frequencies#extended-range) |

## Структура файла `.sub`

Файл `.sub` складається з трьох частин:

1. **Заголовок** — тип файла, версія, частота.
2. **Пресет** — пресет модуляції або повна користувацька конфігурація CC1101.
3. **Дані** — назва протоколу та його поля або тривалості RAW.

### Заголовок

| Поле | Тип | Опис |
|---|---|---|
| `Filetype` | рядок | `Flipper SubGhz Key File` для ключів, `Flipper SubGhz RAW File` для RAW-записів |
| `Version` | uint | Версія формату файла, на цей момент `1` |
| `Frequency` | uint | Частота в Гц, наприклад `433920000` |

### Пресет

| Поле | Опис |
|---|---|
| `Preset` | Назва пресета. Для користувацького пресета має бути `FuriHalSubGhzPresetCustom` |
| `Custom_preset_module` | Трансивер, для Flipper Zero — `CC1101` (лише для користувацького пресета) |
| `Custom_preset_data` | Конфігурація трансивера (лише для користувацького пресета) |

Вбудовані пресети:

| Значення `Preset` | Назва в меню | Що означає |
|---|---|---|
| `FuriHalSubGhzPresetOok270Async` | `AM270` | OOK, смуга 270 кГц |
| `FuriHalSubGhzPresetOok650Async` | `AM650` | OOK, смуга 650 кГц |
| `FuriHalSubGhzPreset2FSKDev238Async` | `FM238` | 2-FSK, девіація 2,38 кГц, смуга 270 кГц |
| `FuriHalSubGhzPreset2FSKDev12KAsync` | `FM12K` | 2-FSK, девіація 12 кГц |
| `FuriHalSubGhzPreset2FSKDev476Async` | `FM476` | 2-FSK, девіація 47,6 кГц, смуга 270 кГц |

Користувацький пресет вбудовується у файл, тому інший Flipper може надіслати сигнал навіть без цього пресета у
своїх налаштуваннях.

#### Дані користувацького пресета {#custom-preset-data}

Шістнадцяткові байти, розділені пробілами: `XX YY XX YY … 00 00 ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ`

- `XX` — адреса регістра CC1101, `YY` — значення регістра (стільки пар, скільки потрібно);
- `00 00` — кінець блоку регістрів;
- `ZZ ×8` — 8-байтова таблиця PA (крива підсилювача потужності).

Значення регістрів дивіться в [документації на CC1101](https://www.ti.com/lit/ds/symlink/cc1101.pdf).

### Файли ключів

Декодовані сигнали зберігають назву протоколу та його поля:

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

| Поле | Опис |
|---|---|
| `Protocol` | Назва протоколу точно так, як у реєстрі протоколів (наприклад, `Princeton`, `KeeLoq`, `Nice FloR-S`, `CAME Atomo`, `Security+ 2.0`) |
| `Bit` | Довжина корисного навантаження в бітах |
| `Key` | Корисне навантаження, hex, 8 байтів |
| `TE` | Базова тривалість імпульсу (інтервал квантування) у мкс, для протоколів, які її зберігають |

Протоколи можуть додавати власні поля. Ті, що трапляються в Unleashed:

| Поле | Де використовується | Що означає |
|---|---|---|
| `Manufacture` | KeeLoq, FAAC SLH / Genius | Виробник, чий ключ декодує сигнал (наприклад, `DoorHan`, `BFT`, `Genius`) |
| `Seed` | BFT Mitto, Erreka, FAAC SLH, Genius, частина KeeLoq | Секрет окремого пульта для secure learning |
| `CounterMode` | Nice Flor-S, CAME Atomo, Alutech AT-4N, KeeLoq, V2 Phoenix | Експериментальна поведінка лічильника, див. [Режими лічильника](/ua/subghz/counter-mode) |
| `Secplus_packet_1`, `Pin` | Security+ 2.0 | Другий пакет; PIN клавіатури для 86-бітних посилок ([Security+ PIN](/ua/subghz/secplus-pin)) |
| `Cert` | Nice O-Code | Сертифікат приймача ([Nice O-Code](/ua/subghz/nice-o-code)) |

Приклад із користувацьким пресетом:

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

::: warning Редагування файлів із динамічним кодом
Зміна `Key` вручну для динамічного протоколу рідко дає валідний код. Щоб змінити серійник, кнопку або лічильник,
користуйтеся [Add Manually [Advanced]](/ua/subghz/add-manually) або, у режимі Debug, пунктом
`Saved → файл → Signal Settings`.
:::

### Файли RAW

Записи з [Read RAW](/ua/subghz/read-raw):

```text
Filetype: Flipper SubGhz RAW File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: RAW
RAW_Data: 29262 361 -68 2635 -66 24113 -66 11 ...
RAW_Data: -424 205 -412 159 -412 381 -240 181 ...
```

- `Protocol` мусить бути `RAW`.
- `RAW_Data` — тривалості в мкс: додатне значення = носійна увімкнена, від'ємне = вимкнена. Значення не можуть
  бути нулями, перелік має починатися з додатного числа й чергувати знак. До 512 значень у рядку; рядок може
  повторюватися скільки потрібно.

Довгі дані читаються з SD-картки під час передавання. При дуже коротких тривалостях (менше 10 мкс) повільна
картка може не встигати, і передавання зупиняється, не дійшовши до кінця.

### Файли BinRAW

Режим `Bin RAW` у `Read → Config` дає файли **BinRAW**. На відміну від RAW, вони зберігають лише корисну
повторювану послідовність, із відновленою бітовою швидкістю й без шуму, тому ними можна відтворити майже будь-який
**статичний** протокол, відомий чи ні. Під час зчитування тримайте кнопку пульта трохи довше, щоб накопичилося
достатньо даних.

| Поле | Опис |
|---|---|
| `Protocol` | `BinRAW` |
| `Bit` | Довжина корисного навантаження всього файла в бітах (максимум 4096) |
| `TE` | Інтервал квантування, мкс |
| `Bit_RAW` | Довжина наступного блоку `Data_RAW`, у бітах |
| `Data_RAW` | Закодовані тривалості: кожний біт = один `TE`; `1` = носійна, `0` = її немає |

Приклад: `TE: 100`, `Bit_RAW: 8`, `Data_RAW: 37` → `0b00110111` → надсилається `-200 200 -100 300`.
Пари `Bit_RAW` + `Data_RAW` утворюють повторювані блоки; кілька блоків надсилаються один за одним.

```text
Protocol: BinRAW
Bit: 1572
TE: 597
Bit_RAW: 260
Data_RAW: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F 4A B5 55 4C B3 52 AC D5 2D 53 52 AD 4A D5 35 00
```

## `setting_user` {#setting-user}

Додаткові частоти й пресети, які завантажуються під час запуску застосунку Sub-GHz. Перейменуйте
`setting_user.example` на `setting_user`.

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

| Ключ | Що означає |
|---|---|
| `Add_standard_frequencies` | `true` — перелік із прошивки + ваші (додаються після нього); `false` — лише ваші (тоді заповнюйте і `Frequency`, і `Hopper_frequency`) |
| `Default_frequency` | Частота, з якої починають Read / Read RAW |
| `Frequency` | Додає частоту до основного переліку (9 цифр, Гц). Можна повторювати |
| `Hopper_frequency` | Додає частоту до hopping. Повторення однієї частоти змушує Flipper слухати її частіше |
| `Custom_preset_name` / `_module` / `_data` | Користувацький пресет модуляції, який показується в переліку `Modulation` під цією назвою. Формат даних: [вище](#custom-preset-data) |

У файлі `.example` є закоментовані пресети, які можна увімкнути: `FM95`, `FM15k` (2-FSK, смуга 200 кГц /
фільтр 135 кГц, девіація 15,86 кГц), `Pagers`, `AM_1`, `AM_2`.

## `keeloq_mfcodes_user` {#keeloq-mfcodes-user}

Ваші власні ключі виробників KeeLoq, які завантажуються під час запуску застосунку додатково до вбудованої
(зашифрованої) бази. Створіть його з `keeloq_mfcodes_user.example`, видаліть зразки ключів і **залиште порожній
рядок у кінці**.

```text
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:2:Test2
```

Кожний рядок має вигляд `KEY:METHOD:NAME`:

- `KEY` — 64-бітний ключ виробника, 16 шістнадцяткових цифр;
- `NAME` — назва без пробілів, до 64 символів (показується в Read як виробник);
- `METHOD` — тип навчання:

| Значення | Навчання |
|---|---|
| `0` | пробувати все: перебирає попередній ключ і ключ виробника в прямому та зворотному порядку байтів |
| `1` | Simple Learning |
| `2` | Normal Learning |
| `3` | Secure Learning (потрібен Seed) |
| `4` | Magic XOR type 1 |
| `5` | FAAC SLH |
| `6` | Magic Serial type 1 |
| `7` | Magic Serial type 2 |
| `8` | Magic Serial type 3 |

`Encryption: 0` означає, що файл — звичайний текст: користувацькі файли не можуть бути зашифрованими. Докладніше
про типи навчання: [KeeLoq](/ua/subghz/keeloq).

## Пов'язані сторінки

- [Read](/ua/subghz/read) · [Read RAW](/ua/subghz/read-raw) · [Частоти](/ua/subghz/frequencies) · [Radio Settings](/ua/subghz/settings)
- [KeeLoq](/ua/subghz/keeloq) · [Режими лічильника](/ua/subghz/counter-mode) · [Файли розкладок Sub-GHz Remote](/ua/subghz/remote)
