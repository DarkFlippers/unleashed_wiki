---
title: Формат файла
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-docs, unleashed-src]
---
# Формат файла ключа iButton (`.ibtn`)

Сохранённые ключи лежат в `/ext/ibutton/` с расширением `.ibtn`. Один файл — один ключ со всеми данными, нужными его
протоколу.

## Пример

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1992
Rom Data: 08 DE AD BE EF FA CE 4E
Sram Data: 4E 65 76 65 72 47 6F 6E 6E 61 47 69 76 65 59 6F 75 55 70 4E 65 76 65 72 47 6F 6E 6E 61 4C 65 74 59 6F 75 44 6F 77 6E 4E 65 76 65 72 47 6F 6E 6E 61 52 75 6E 41 72 6F 75 6E 64 41 6E 64 44 65 73 65 72 74 59 6F 75 4E 65 76 65 72 47 6F 6E 6E 61 4D 61 6B 65 59 6F 75 43 72 79 4E 65 76 65 72 47 6F 6E 6E 61 53 61 79 47 6F 6F 64 62 79 65 4E 65 76 65 72 47 6F 6E 6E 61 54 65 6C 6C 41 4C 69 65
```

Ключ DS1990 (байты — пример; в настоящем ROM последний байт — правильный CRC):

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

## Версия 2 (текущая)

Поля после `Protocol` зависят от протокола.

| Поле | Тип | Описание |
|---|---|---|
| `Protocol` | строка | `DS1990`, `DS1992`, `DS1996`, `DS1971`, `DS1420`, `(non-specific)`, `Cyfral`, `Metakom` |
| `Rom Data` | hex | 8-байтный ROM (только протоколы Dallas) |
| `Sram Data` | hex | Содержимое SRAM (DS1992: 128 байт, DS1996: 8192 байта) |
| `Eeprom Data` | hex | Содержимое EEPROM (DS1971: 32 байта) |
| `Data` | hex | Код ключа (Cyfral: 2 байта, Metakom: 4 байта) |

Примечания:
- **(non-specific)** — «всё остальное» для неизвестных устройств 1-Wire (пункт меню *Dallas (non-specific)*). Хранит
  только ROM и ничего не проверяет — подходит для ключей с намеренно неверным family code или CRC. Прошивка сохраняет
  его как `Protocol: (non-specific)`; имя `DSGeneric` из официального описания и старых файлов тоже принимается.
- **DS1420** полностью совместим с DS1990; отличается только family code (`0x81` против `0x01`).
- Новые протоколы не требуют повышать версию формата — каждый протокол сам определяет свои поля.

## Версия 1 (устаревшая)

```text
Filetype: Flipper iButton key
Version: 1
Key type: Dallas
Data: 01 23 45 67 89 AB CD EF
```

| Поле | Тип | Описание |
|---|---|---|
| `Key type` | строка | `Cyfral`, `Dallas`, `Metakom` |
| `Data` | hex | Данные ключа |

Файлы версии 1 по-прежнему загружаются (`Dallas` читается как DS1990) и при сохранении конвертируются в версию 2.

## Связанные страницы

- [Протоколы](/ru/ibutton/protocols) · [Добавление вручную](/ru/ibutton/add-manually) · [Чтение](/ru/ibutton/read)
