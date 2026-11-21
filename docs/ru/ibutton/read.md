---
title: Чтение ключей
order: 10
original: [https://docs.flipper.net/zero/ibutton/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols]
sources: [unleashed-src, flipper-docs]
---
# Чтение, сохранение и эмуляция ключей iButton

Flipper Zero читает ключи Dallas 1-Wire (ID, а у ключей с памятью — и память), ключи Cyfral и Metakom, а затем может
их сохранить и эмулировать.

| Ключ | Что читается |
|---|---|
| Dallas **DS1990** / **DS1420** | Только 8-байтный ROM (ID) — памяти у ключа нет |
| Dallas **DS1992** | ROM + 128 байт SRAM |
| Dallas **DS1996** | ROM + 8192 байта SRAM |
| Dallas **DS1971** | ROM + 32 байта EEPROM |
| Другие устройства 1-Wire | Только ROM, показывается как **Dallas (non-specific)** |
| **Cyfral** | 2-байтный код |
| **Metakom** | 4-байтный код |

## Чтение ключа

1. Откройте `Main Menu → iButton → Read`. На экране — **Reading — Connect key with pogo pins**.

   ![Экран чтения с подсказкой «Connect key with pogo pins»](/screens/ibutton/read.png)

2. Приложите ключ к **плоской части** площадки так, чтобы центр ключа касался **левого пина данных**, а ободок —
   **среднего пина земли**. Не двигайте.
3. Когда ключ прочитан, Флиппер пищит и показывает протокол (например **Dallas DS1990**) и ID.

   ![Результат чтения: Dallas DS1990, восьмибайтовый ID и код семейства, внизу Retry и More](/screens/ibutton/read_success.png)

4. Кнопки: <kbd>←</kbd> **Retry**, <kbd>→</kbd> **More**. <kbd>Back</kbd> спросит *Exit to iButton Menu? All unsaved
   data will be lost!*

В **More** (набор пунктов зависит от протокола):

| Пункт | Когда есть | Действие |
|---|---|---|
| **Save** | всегда | Ввести имя, сохраняется в `/ext/ibutton/<имя>.ibtn` |
| **Emulate** | всегда | Сразу эмулировать |
| **Write ID** | записываемые протоколы | Записать ID на болванку — [Запись](/ru/ibutton/write) |
| **Full Write on Same Type** | DS1992, DS1996, DS1971 | Скопировать память на ключ того же типа |
| **Data Info** | DS1992, DS1996, DS1971 | Показать дамп памяти |

## Ошибки чтения

Если данные не прошли проверку протокола, экран ошибки объясняет причину и всё равно предлагает **Retry** и **More**:

- **CRC Error** (Dallas) — 8-й байт ROM — это CRC от первых семи; на экране ROM с подсвеченным неверным байтом и
  *Expected CRC*. Обычно виноват плохой контакт: протрите ключ и прочитайте ещё раз. Если повторяется, ключ всё равно
  можно сохранить и попробовать эмулировать — некоторые считыватели CRC не проверяют. Если эмуляция не проходит,
  ошибку не исправить.
- **Invalid Metakom key: odd parity in byte N** — байт Metakom не прошёл проверку чётности; перечитайте.

## Сохранённые ключи

`Main Menu → iButton → Saved` открывает `/ext/ibutton/`. Меню ключа:

| Пункт | Действие |
|---|---|
| **Emulate** | Эмулировать перед считывателем |
| **Write ID** | Записать ID на болванку |
| **Full Write on Same Type** | Только DS1992/DS1996/DS1971 — скопировать память |
| **Edit** | Изменить ID в hex и сохранить под именем |
| **Rename** / **Delete** | Управление файлом |
| **Info** | Имя, протокол, ID; <kbd>→</kbd> **More** показывает память у ключей с памятью |

## Эмуляция

1. Откройте сохранённый ключ → **Emulate** (или **More → Emulate** сразу после чтения). На экране **Emulating**,
   `[Протокол]` и имя ключа (или *Unsaved Key*).

   ![Экран эмуляции: надпись «Emulating», протокол [DS1990] и имя ключа](/screens/ibutton/emulate.png)

2. Прижмите **выступающую часть** площадки к считывателю: **правый пин данных** — к центру считывателя, **средний пин
   земли** — к ободку.
3. Если пин земли не достаёт до ободка, подключите два провода: GPIO **17** → центр считывателя, GPIO **8 / 11 / 18**
   (GND) → ободок.

## CLI

```text
ikey read
ikey emulate <key_type> <key_data>
ikey write Dallas <key_data>
	<key_type>: Dallas (8 bytes), Cyfral (2 bytes), Metakom (4 bytes, must contain correct parity)
	<key_data> is hex
```

## Если не получается

- **Ничего не происходит.** Ключ не касается обоих пинов — наклоните его, чтобы ободок касался пина земли.
- **Неподдерживаемый ключ.** Возможно, неподдерживаемый протокол (или это RFID-брелок — попробуйте
  [125 kHz RFID](/ru/rfid/read)).
- **Считыватель не принимает эмуляцию.** Проверьте контакт; некоторые считыватели распознают эмуляторы или проверяют
  то, что Флиппер подделать не может. Если ключ добавлен/изменён вручную — перепроверьте ID.

## Связанные страницы

- [Запись](/ru/ibutton/write) · [Добавление вручную](/ru/ibutton/add-manually) · [Протоколы](/ru/ibutton/protocols) ·
  [Формат файла](/ru/ibutton/file-format)
