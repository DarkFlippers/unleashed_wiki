---
title: Формат файлів
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-docs, unleashed-src]
---
# Формат файла ключа iButton (`.ibtn`)

Збережені ключі лежать у `/ext/ibutton/` з розширенням `.ibtn`. Один файл містить один ключ з усіма даними, потрібними
його протоколу.

## Приклад

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1992
Rom Data: 08 DE AD BE EF FA CE 4E
Sram Data: 4E 65 76 65 72 47 6F 6E 6E 61 47 69 76 65 59 6F 75 55 70 4E 65 76 65 72 47 6F 6E 6E 61 4C 65 74 59 6F 75 44 6F 77 6E 4E 65 76 65 72 47 6F 6E 6E 61 52 75 6E 41 72 6F 75 6E 64 41 6E 64 44 65 73 65 72 74 59 6F 75 4E 65 76 65 72 47 6F 6E 6E 61 4D 61 6B 65 59 6F 75 43 72 79 4E 65 76 65 72 47 6F 6E 6E 61 53 61 79 47 6F 6F 64 62 79 65 4E 65 76 65 72 47 6F 6E 6E 61 54 65 6C 6C 41 4C 69 65
```

Ключ DS1990 (байти наведено для прикладу; у справжньому ROM останній байт — коректна CRC):

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1990
Rom Data: 01 23 45 67 89 AB CD EF
```

Ключ Cyfral:

```text
Filetype: Flipper iButton key
Version: 2
Protocol: Cyfral
Data: A1 B2
```

## Версія 2 (поточна)

Поля після `Protocol` залежать від протоколу.

| Поле | Тип | Опис |
|---|---|---|
| `Protocol` | рядок | `DS1990`, `DS1992`, `DS1996`, `DS1971`, `DS1420`, `(non-specific)`, `Cyfral`, `Metakom` |
| `Rom Data` | hex | 8-байтовий ROM (лише протоколи Dallas) |
| `Sram Data` | hex | Вміст SRAM (DS1992: 128 байт, DS1996: 8192 байти) |
| `Eeprom Data` | hex | Вміст EEPROM (DS1971: 32 байти) |
| `Data` | hex | Код ключа (Cyfral: 2 байти, Metakom: 4 байти) |

Примітки:
- **(non-specific)** — узагальнений протокол для невідомих пристроїв 1-Wire (пункт меню *Dallas (non-specific)*). Він
  містить лише ROM і не виконує жодних перевірок — використовуйте його для ключів із навмисно хибним family code або
  CRC. Прошивка зберігає його як `Protocol: (non-specific)`; назву `DSGeneric`, яку вживає офіційна документація та
  старіші файли, також приймають.
- **DS1420** повністю сумісний із DS1990; відрізняється лише family code (`0x81` проти `0x01`).
- Нові протоколи не потребують підняття версії формату — кожен протокол визначає власні поля.

## Версія 1 (застаріла)

```text
Filetype: Flipper iButton key
Version: 1
Key type: Dallas
Data: 01 23 45 67 89 AB CD EF
```

| Поле | Тип | Опис |
|---|---|---|
| `Key type` | рядок | `Cyfral`, `Dallas`, `Metakom` |
| `Data` | hex | Дані ключа |

Файли версії 1 досі завантажуються (`Dallas` читається як DS1990) і перетворюються на версію 2, коли ви їх
зберігаєте.

## Пов’язані сторінки

- [Протоколи](/ua/ibutton/protocols) · [Додавання вручну](/ua/ibutton/add-manually) · [Читання](/ua/ibutton/read)
