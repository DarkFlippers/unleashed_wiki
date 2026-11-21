---
title: RAW-запись
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/LFRFIDRaw.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/lfrfid_debug]
sources: [unleashed-docs, unleashed-src]
---
# Чтение RAW-данных 125 кГц

Режим RAW записывает сигнал метки как есть — длительности импульсов и периодов — без декодирования, примерно как
диктофон. Он нужен для **исследования протоколов**: если ваша метка не распознаётся, запишите её и отправьте файлы (и
фото карты) разработчикам в GitHub issue.

## Включите режим Debug

Пункты RAW скрыты, пока Debug выключен:

1. `Main Menu → Settings → System`.
2. Установите **Debug** в **ON**.

## Запись

1. Откройте `Main Menu → 125 kHz RFID → Extra Actions → Read RAW RFID data`.
2. Введите имя записи (по умолчанию `RfidRecord`).
3. Прочитайте инструкцию (*RAW RFID Data Reader — 1. Hold card next to Flipper, 2. Press OK, 3. Wait until data is
   read*) и нажмите <kbd>OK</kbd>.
4. Приложите карту к задней стороне. Флиппер делает три прохода по **5 секунд** — *Reading ASK*, *ASK 134kHz*,
   *Reading PSK* — и просит *Don't move for 5 sec.*
5. **RAW RFID Read Success** — *Now you can analyze files or send them to developers*. Нажмите <kbd>OK</kbd>.

В `/ext/lfrfid/` появятся три файла:

| Файл | Проход |
|---|---|
| `<имя>.ask.raw` | ASK, несущая 125 кГц |
| `<имя>.ask134.raw` | ASK, несущая 134,2 кГц |
| `<имя>.psk.raw` | PSK, несущая 125 кГц |

::: tip Unleashed
В документации Unleashed и в стоке упомянуты два файла (ASK и PSK). Текущая прошивка записывает третий проход
**ASK 134kHz** — для меток животных.
:::

Если видите *RAW Reading error! This may be caused by SD card issues* — проверьте карту (свободное место, ошибки). Без
SD-карты приложение пишет *No SD Card!*.

## Воспроизведение

`Extra Actions → Emulate RAW RFID data` открывает браузер файлов `.raw` и воспроизводит выбранный (*Emulating RAW
RFID*). Это в основном для отладки протоколов, а не замена обычной эмуляции.

## CLI

То же доступно в CLI — удобно для разработки:

```text
rfid raw_read <ask | ask134 | psk> <filename>   - read and save raw data to a file
rfid raw_emulate <filename>                     - emulate raw data
rfid raw_analyze <filename>                     - print the raw data and try to decode it
```

`raw_analyze` выводит каждую пару импульс/длительность, отмечает места, где декодировался протокол, и в конце печатает
частоту, скважность, средние значения и найденный протокол (или `not found`).

## Приложение LF-RFID Debug

В исходниках прошивки есть инструмент разработчика **LF-RFID Debug** (`applications/debug/lfrfid_debug`): на его
экране **Tune** можно на лету подстраивать таймер несущей (ARR/CCR — частота и скважность). Это отладочное
приложение для разработки протоколов, в обычной работе не нужно.

## Связанные страницы

- [Форматы файлов](/ru/rfid/file-format) · [Чтение](/ru/rfid/read) · [Протоколы](/ru/rfid/protocols)
