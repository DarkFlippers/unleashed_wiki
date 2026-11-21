---
title: RAW-запис
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/LFRFIDRaw.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/lfrfid_debug]
sources: [unleashed-docs, unleashed-src]
---
# Читання сирих даних 125 кГц

Режим RAW записує сигнал мітки як він є — тривалості імпульсів і періодів — замість того, щоб його розшифровувати,
трохи як диктофон. Він призначений для **дослідження протоколів**: якщо вашу мітку не розпізнано, запишіть її й
надішліть файли (разом із фотографією карти) розробникам у GitHub issue.

## Увімкніть режим Debug

Пункти RAW приховані, доки Debug не ввімкнено:

1. `Main Menu → Settings → System`.
2. Перемкніть **Debug** на **ON**.

## Запис

1. Відкрийте `Main Menu → 125 kHz RFID → Extra Actions → Read RAW RFID data`.
2. Дайте запису назву (типово `RfidRecord`).
3. Прочитайте інструкцію (*RAW RFID Data Reader — 1. Hold card next to Flipper, 2. Press OK, 3. Wait until data is
   read*) і натисніть <kbd>OK</kbd>.
4. Тримайте карту на задній стінці Фліппера. Фліппер записує три проходи по **5 секунд** кожен — *Reading ASK*,
   *ASK 134kHz*, *Reading PSK* — і просить *Don't move for 5 sec.*
5. **RAW RFID Read Success** — *Now you can analyze files or send them to developers*. Натисніть <kbd>OK</kbd>.

У `/ext/lfrfid/` створюються три файли:

| Файл | Прохід |
|---|---|
| `<name>.ask.raw` | ASK, носійна 125 кГц |
| `<name>.ask134.raw` | ASK, носійна 134,2 кГц |
| `<name>.psk.raw` | PSK, носійна 125 кГц |

::: tip Unleashed
Документація Unleashed і стокова прошивка згадують два файли (ASK і PSK). Поточна прошивка записує третій прохід,
**ASK 134kHz**, для міток тварин.
:::

Якщо ви бачите *RAW Reading error! This may be caused by SD card issues*, перевірте картку (вільне місце, помилки).
Без картки застосунок показує *No SD Card!*.

## Відтворення

`Extra Actions → Emulate RAW RFID data` відкриває файловий браузер для файлів `.raw` і відтворює вибраний
(*Emulating RAW RFID*). Це корисно насамперед для налагодження протоколів, а не як заміна звичайної емуляції.

## CLI

Те саме доступно через CLI і зручне для розробки:

```text
rfid raw_read <ask | ask134 | psk> <filename>   - read and save raw data to a file
rfid raw_emulate <filename>                     - emulate raw data
rfid raw_analyze <filename>                     - print the raw data and try to decode it
```

`raw_analyze` виводить кожну пару «імпульс/тривалість», позначає місце, де розшифрувався протокол, і завершує
частотою, коефіцієнтом заповнення, середніми значеннями та виявленим протоколом (або `not found`).

## Застосунок LF-RFID Debug

У вихідному коді прошивки є ще й інструмент для розробників — **LF-RFID Debug**
(`applications/debug/lfrfid_debug`), екран **Tune** якого на льоту підстроює таймер носійної (ARR/CCR — частота та
коефіцієнт заповнення). Це налагоджувальний застосунок для роботи над протоколами, у звичайному використанні він не
потрібен.

## Пов’язані сторінки

- [Формати файлів](/ua/rfid/file-format) · [Читання](/ua/rfid/read) · [Протоколи](/ua/rfid/protocols)
