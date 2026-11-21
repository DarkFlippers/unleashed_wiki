---
title: Командная строка (CLI)
order: 100
original: [https://docs.flipper.net/zero/development/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/toolbox/cli]
sources: [flipper-docs, unleashed-src]
---
# Командная строка (CLI)

У Флиппера есть текстовая консоль на последовательном порту USB. Из неё можно читать и отправлять сигналы,
запускать приложения, работать с файлами, смотреть логи, управлять GPIO и светодиодом, переписываться с другими
Флипперами через Sub-GHz и многое другое — удобно для скриптов, отладки и разработки приложений.

## Подключение к CLI

::: warning Сначала закройте qFlipper
Последовательный порт Флиппера одновременно может использовать только одна программа. Перед подключением закройте
**qFlipper** (а также Flipper Lab и другие терминалы).
:::

Скорость порта — **230400** бод (для USB CDC значение в основном игнорируется, но некоторые терминалы требуют его
указать).

### Вариант 1: Flipper Lab (браузер)

Работает в Chrome, Edge или другом браузере на Chromium с поддержкой Web Serial.

1. Подключите Флиппер по USB.
2. Откройте [lab.flipper.net](https://lab.flipper.net/) → **CLI**.

### Вариант 2: веб-терминал (браузер)

1. Подключите Флиппер по USB, откройте браузер на Chromium.
2. Перейдите в [web serial terminal](https://googlechromelabs.github.io/serial-terminal/).
3. Установите **Baud rate** = **230400**, нажмите **Connect**, выберите свой Флиппер и снова нажмите **Connect**.

### Вариант 3: терминал — macOS

1. Найдите порт:

   ```sh
   ls /dev/cu.*
   ```

   Флиппер виден как `/dev/cu.usbmodemflip_NAME`, где `NAME` — имя вашего Флиппера.
2. Подключитесь через **screen**:

   ```sh
   screen /dev/cu.usbmodemflip_NAME
   ```

   Выход: <kbd>Ctrl</kbd>+<kbd>A</kbd>, затем <kbd>K</kbd>, затем <kbd>Y</kbd>.
3. …или через **minicom** (установка через [Homebrew](https://brew.sh/): `brew install minicom`):

   ```sh
   minicom -D /dev/cu.usbmodemflip_NAME
   ```

   Выход: <kbd>Esc</kbd>+<kbd>Z</kbd>, затем <kbd>X</kbd>, затем <kbd>Return</kbd>.

### Вариант 3: терминал — Linux

1. Найдите порт:

   ```sh
   ls /dev/serial/by-id/
   ```

   Ищите `usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00`. Если последовательное устройство одно, обычно это
   также `/dev/ttyACM0`; имя порта показывает и qFlipper.
2. Подключитесь:

   ```sh
   screen /dev/serial/by-id/usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00
   # or
   minicom -D /dev/ttyACM0
   ```

   Выход из screen: <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>K</kbd>, <kbd>Y</kbd>. Выход из minicom:
   <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>X</kbd>, <kbd>Return</kbd>.

::: tip
Если в Linux появляется «permission denied», добавьте себя в группу `dialout` (в некоторых дистрибутивах — `uucp`) и
перелогиньтесь.
:::

### Вариант 3: терминал — Windows

1. Установите [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Подключите Флиппер; в **Диспетчере устройств → Порты (COM и LPT)** найдите его COM-порт (отключите и подключите
   снова, чтобы увидеть, какой появляется).
3. В PuTTY выберите **Connection type: Serial**, **Serial line**: например `COM3`, **Speed**: `230400` и нажмите
   **Open**.

### Из дерева исходников прошивки

Если у вас есть исходники прошивки, `./fbt cli` сразу открывает сессию CLI; с uFBT — `ufbt cli`.

**Ожидаемый результат:** ASCII-баннер Flipper, «Welcome to Flipper Zero Command Line Interface!», строка с версией
прошивки и приглашение `>:`.

## Встроенные и внешние команды

`help` или `?` выводит список команд, доступных на вашем устройстве.

::: tip Unleashed / новая архитектура CLI
Большинство команд для радио и периферии (`subghz`, `nfc`, `ir`, `rfid`, `ikey`, `onewire`, `bt`, `crypto`, `js`,
`gpio`, `led`, `vibro`, `buzzer`, `i2c`, `neofetch`, …) — это **внешние CLI-плагины**, которые загружаются с SD-карты
из папки `/ext/apps_data/cli/plugins` (файлы с префиксом `cli_`). Без SD-карты (или с повреждённой картой) остаются
только базовые команды. После копирования или обновления плагинов выполните `reload_ext_cmds` вместо перезагрузки.
:::

### Обзор команд

| Команда | Описание |
|---|---|
| `!` | Псевдоним `info device` |
| `?`, `help` | Список доступных команд |
| `bt` | Тестовая утилита радиоядра (BLE) — версия HCI, а в режиме отладки тесты несущей/пакетов |
| `buzzer` | Сыграть тон или ноту на пьезодинамике |
| `crypto` | Запись ключей в secure enclave и шифрование/расшифровка AES |
| `date` | Показать / установить дату и время |
| `device_info` | Псевдоним `info device` (устарел) |
| `echo` | Возвращает полученные байты как есть (для тестов производительности); остановка — <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `exit` | Выйти из оболочки (полезно во вложенных оболочках вроде `nfc`) |
| `factory_reset` | Сброс к заводским настройкам; данные на microSD сохраняются |
| `free` | Информация о куче — общее профилирование памяти |
| `free_blocks` | Свободные блоки кучи и их размеры — оценка фрагментации |
| `gpio` | Режим / запись / чтение пинов GPIO |
| `i2c` | Сканирование шины I2C |
| `ikey` | Чтение, эмуляция и запись ключей iButton |
| `info` | Подробная информация об устройстве и питании |
| `input` | Показ событий кнопок, эмуляция нажатий |
| `ir` | Приём, передача, декодирование ИК-сигналов; универсальные пульты |
| `js` | Запуск JavaScript-файла, вывод консоли идёт в CLI |
| `led` | Управление RGB-светодиодом и подсветкой экрана |
| `loader` | Список, запуск и закрытие приложений |
| `log` | Просмотр системного лога |
| `neofetch` | Информация о системе, как `neofetch` в Linux |
| `nfc` | Вложенная оболочка NFC: dump, emulate, raw, APDU, scanner |
| `onewire` | Сканирование шины 1-Wire (пины iButton) |
| `power` | Выключение, перезагрузка, перезагрузка в DFU, 5 В / 3,3 В на GPIO |
| `reload_ext_cmds` | Перечитать список внешних команд с SD-карты |
| `rfid` | Чтение, запись, эмуляция карт 125 кГц; RAW-инструменты |
| `sleep` | Подождать заданное время, например `sleep 5s` (полезно в скриптах) |
| `start_rpc_session` | Переключить CLI в режим protobuf RPC (используется qFlipper/приложениями; вручную обычно не нужно) |
| `storage` | Команды файловой системы |
| `subghz` | Инструменты Sub-GHz: rx/tx, RAW, декодирование, чат |
| `sysctl` | Системные настройки: режим отладки, отслеживание кучи |
| `top` | Список потоков в реальном времени (как `top` в Linux); выход — <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `update` | Установка пакета обновления, бэкап / восстановление внутренней памяти |
| `uptime` | Время с последней загрузки |
| `vibro` | Включить/выключить вибромотор |
| `unit_tests` | Только в сборке прошивки `unit_tests` — см. [Юнит-тесты](/ru/dev/unit-tests) |

## Чтение логов

1. Подключитесь к CLI.
2. Запустите логирование с нужным уровнем:

   | Команда | Что показывает |
   |---|---|
   | `log` | Текущий уровень из системных настроек |
   | `log error` | Только критические ошибки и важные сообщения |
   | `log warn` | Предупреждения и некритичные ошибки, плюс `error` |
   | `log info` | Некритичная информация, плюс `warn` |
   | `log default` | Системный уровень по умолчанию (= `info`) |
   | `log debug` | Отладочная информация, плюс `info` (влияет на производительность) |
   | `log trace` | Системные трассировки, плюс `debug` (влияет на производительность) |

   `log ?` выводит этот список на устройстве.
3. Пользуйтесь Флиппером — сообщения появляются в терминале.
4. Остановка — <kbd>Ctrl</kbd>+<kbd>C</kbd>.

## Чат через Sub-GHz

Несколько Флипперов на одной частоте могут переписываться через CLI.

1. Каждый участник подключается к CLI своего Флиппера.
2. Выполните `subghz chat <frequency_in_hz> <device>`, например:

   ```
   subghz chat 868150000 0
   ```

   - частота в Гц в диапазонах 299999755–348000000, 386999938–464000000 или 778999847–928000000;
   - устройство `0` — встроенный CC1101, `1` — внешний модуль CC1101.
3. Введите сообщение и нажмите <kbd>Enter</kbd>.
4. Выход — <kbd>Ctrl</kbd>+<kbd>C</kbd>.

::: tip Unleashed
Стоковая прошивка передаёт только на частотах, разрешённых в вашем регионе; Unleashed снимает региональные
ограничения на передачу. Соблюдайте местные правила использования радиочастот.
:::

## Справочник команд

### bt

| Команда | Описание |
|---|---|
| `bt hci_info` | Информация Bluetooth HCI |
| `bt tx_carrier <channel:0-39> <power:0-6>` | *Только в режиме отладки.* Тест передачи несущей |
| `bt rx_carrier <channel:0-39>` | *Только в режиме отладки.* Тест приёма несущей |
| `bt tx_packet <channel:0-39> <pattern:0-5> <datarate:1-2>` | *Только в режиме отладки.* Тест передачи пакетов |
| `bt rx_packet <channel:0-39> <datarate:1-2>` | *Только в режиме отладки.* Тест приёма пакетов |

### buzzer

| Команда | Описание |
|---|---|
| `buzzer freq <frequency_in_hz> <duration>` | Сыграть тон |
| `buzzer note <note> <duration>` | Сыграть ноту; `s` означает диез, например `cs3` = до-диез 3-й октавы (C♯3); бемоли не поддерживаются |

Длительность — в `ms`, `s`, `m`, `h`, например `buzzer note cs3 500ms`.

### crypto

Шифрование и расшифровка ключами, хранящимися в secure enclave микроконтроллера.

| Команда | Описание |
|---|---|
| `crypto encrypt <key_slot> <iv_hex>` | Зашифровать текст AES256-CBC, вывод в hex |
| `crypto decrypt <key_slot> <iv_hex>` | Расшифровать hex обратно в текст |
| `crypto has_key <key_slot>` | Проверить, есть ли ключ в слоте (1–100) |
| `crypto store_key <key_slot> <key_type> <key_size> <key_data_hex>` | **Необратимо!** Записать ключ — удалить его будет нельзя |

- `key_slot`: слоты 1–11 заранее заняты ключами, которые использует прошивка.
- `iv_hex`: 16-байтовый вектор инициализации в hex.
- `key_type`: `master`, `simple` или `encrypted`; `key_size`: `128` или `256`.

### gpio

| Команда | Описание |
|---|---|
| `gpio mode <pin_name> <0/1>` | Режим пина: вход (0) или выход (1) |
| `gpio set <pin_name> <0/1>` | Установить значение пина |
| `gpio read <pin_name>` | Прочитать значение пина |

Имена пинов: `PA7`, `PA6`, `PA4`, `PB3`, `PB2`, `PC3`, `PC1`, `PC0` — см. [распиновку GPIO](/ru/gpio/pinout).

### ikey

| Команда | Описание |
|---|---|
| `ikey read` | Прочитать ключ iButton |
| `ikey emulate <key_type> <key_data>` | Эмулировать ключ |
| `ikey write Dallas <key_data>` | Записать 8 байт на Dallas-совместимую болванку |

Типы ключей и длина данных (hex): `Dallas` — 8 байт, `Cyfral` — 2 байта, `Metakom` — 4 байта (с корректной
чётностью).

### info

| Команда | Описание |
|---|---|
| `info device` | Информация об устройстве (прошивка, железо, радиостек, …) |
| `info power` | Информация о системе питания |
| `info power_debug` | Подробная информация о питании |

### input

| Команда | Описание |
|---|---|
| `input dump` | Выводить события кнопок |
| `input send <key> <type>` | Сэмулировать событие; `key`: `up`, `down`, `left`, `right`, `back`, `ok`; `type`: `press`, `release`, `short`, `long` |

Полное короткое нажатие — это три команды, иначе ввод отбрасывается:

```
input send ok press
input send ok short
input send ok release
```

Для долгого нажатия используйте `long` вместо `short`.

### ir

| Команда | Описание |
|---|---|
| `ir rx` | Принять и декодировать ИК-сигналы |
| `ir rx raw` | Принять в формате RAW |
| `ir tx <protocol> <address> <command>` | Отправить команду; адрес и команда в hex |
| `ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...` | Отправить RAW: частота 10000–56000, скважность 0–100, максимум 512 отсчётов |
| `ir decode <input_file> [<output_file>]` | Декодировать файл с RAW-сигналами |
| `ir universal list <remote_name>` | Список сигналов универсального пульта |
| `ir universal <remote_name> <signal_name>` | Отправить сигнал универсального пульта |

Протоколы: `NEC`, `NECext`, `NEC42`, `NEC42ext`, `Samsung32`, `RC6`, `RC5`, `RC5X`, `SIRC`, `SIRC15`, `SIRC20`,
`Kaseikyo`, `RCA`, `Pioneer`.

::: tip Unleashed
Имена универсальных пультов берутся из файлов в `/ext/infrared/assets/`. В Unleashed есть `tv`, `audio`, `ac`,
`projectors`, `fans` и `leds` (в стоке их меньше). `ir universal list tv` покажет допустимые имена сигналов.
:::

### js

| Команда | Описание |
|---|---|
| `js <path>` | Запустить JavaScript-файл и выводить его консоль — см. [JavaScript](/ru/dev/js-about) |

### led

| Команда | Описание |
|---|---|
| `led r <0-255>` / `led g <0-255>` / `led b <0-255>` | Яркость красной / зелёной / синей составляющей светодиода |
| `led bl <0-255>` | Яркость подсветки экрана (`128` ≈ 50%) |

Чисто красный: `led r 255`, `led g 0`, `led b 0`.

### loader

| Команда | Описание |
|---|---|
| `loader list` | Список доступных приложений |
| `loader open <Application Name> [args]` | Открыть приложение по имени, при необходимости с аргументами |
| `loader info` | Состояние загрузчика |
| `loader close` | Закрыть запущенное приложение |
| `loader signal <signal> [arg_hex]` | Отправить сигнал с необязательным hex-аргументом |

Аргументы с пробелами можно взять в кавычки:

```
loader open subghz "/ext/subghz/Some File.sub"
```

### nfc

`nfc` открывает **вложенную оболочку**. Внутри: `help` / `?` — список команд, `<command> -h` — подробности,
`exit` — выход.

| Команда | Описание |
|---|---|
| `dump -f <path>` | Сдампить физическую карту в файл `.nfc`. Опции: `-k <key>`, `-p <protocol>`, `-t <timeout_ms>` |
| `emulate -f <path>` | Эмулировать файл `.nfc` |
| `field` | Включить поле 13,56 МГц; остановка — <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `scanner` | Перечислить все протоколы, которые поддерживает метка; `-t` показывает дерево протоколов |
| `raw -p <protocol> -d <data>` | Отправить сырые байты. Опции: `-t <timeout>` (в периодах несущей), `-k` не выключать поле, `-c` добавить CRC, `-s` сначала выполнить активацию/антиколлизию |
| `apdu -d <data> [<data2> ...]` | Отправить APDU меткам ISO14443-4A/4B или ISO15693-3; `-p 4a`/`4b`/`15` задаёт протокол принудительно |
| `mfu info` | Базовая информация о метке MIFARE Ultralight |
| `mfu rdbl -b <block>` | Прочитать блок |
| `mfu wrbl -b <block> -d <data>` | Записать 4-байтовый блок |

Протоколы для `dump -p`: `14_3a`, `14_3b`, `14_4a`, `14_4b`, `15` (ISO 15693-3), `felica`, `mfu`, `mfc`, `mfp`, `des`,
`slix`, `st25`, `ntag4` (NTAG 4xx), `t4t` (Type 4 Tag).
Протоколы для `raw -p`: `14a` / `iso14a`, `14b` / `iso14b`, `15`, `felica`.

### onewire

| Команда | Описание |
|---|---|
| `onewire search` | Поиск устройств 1-Wire |

### power

| Команда | Описание |
|---|---|
| `power off` | Выключить |
| `power reboot` | Перезагрузить |
| `power reboot2dfu` | Перезагрузить в режим DFU |
| `power 5v <1/0>` | Включить/выключить 5 В на пине GPIO 1 |
| `power 3v3 <1/0>` | Включить/выключить 3,3 В на пине GPIO 9 (только в режиме отладки) |

### rfid

| Команда | Описание |
|---|---|
| `rfid read [normal/indala/ask134]` | Прочитать карту в режиме ASK/PSK; необязательный аргумент выбирает режим чтения (`ask134` — метки животных 134 кГц) |
| `rfid write <key_type> <key_data>` | Записать на T5577 |
| `rfid emulate <key_type> <key_data>` | Эмулировать |
| `rfid raw_read <ask/ask134/psk> <filename>` | Сохранить сырой сигнал в файл |
| `rfid raw_emulate <filename>` | Эмулировать RAW-файл (отладка протоколов) |
| `rfid raw_analyze <filename>` | Вывести RAW-файл и попытаться декодировать (разработка протоколов) |

Типы ключей и длина данных (байт, hex):

| Тип | Байт | Тип | Байт | Тип | Байт |
|---|---|---|---|---|---|
| EM4100 | 5 | IoProxXSF | 4 | Paradox | 6 |
| EM4100/32 | 5 | AWID | 9 | PAC/Stanley | 4 |
| EM4100/16 | 5 | FDX-A | 5 | Keri | 4 |
| Electra | 8 | FDX-B | 11 | Gallagher | 8 |
| H10301 | 3 | HIDProx | 6 | Nexwatch | 8 |
| Idteck | 8 | HIDExt | 12 | Radio Key | 6 |
| Indala26 | 4 | Pyramid | 4 | GProxII | 12 |
| Viking | 4 | Jablotron | 5 | Noralsy | 12 |

### storage

Пути начинаются с `/int` (внутренняя флеш-память) или `/ext` (SD-карта).

| Команда | Описание |
|---|---|
| `storage info /ext` | Информация о файловой системе и свободном месте |
| `storage format /ext` | Отформатировать SD-карту (с подтверждением) |
| `storage list <path>` | Содержимое папки |
| `storage tree <path>` | Рекурсивный список |
| `storage remove <path>` | Удалить файл или **пустую** папку |
| `storage read <file>` | Вывести размер и текстовое содержимое |
| `storage read_chunks <file> <1-512>` | Вывести содержимое блоками заданного размера |
| `storage write <file>` | Дописать текст, введённый в CLI; завершить — <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `storage write_chunk <file> <1-512>` | Дописать ровно N байт из CLI (ввод не отображается) |
| `storage copy <src> <dst>` | Скопировать файл |
| `storage rename <old> <new>` | Переименовать / переместить |
| `storage mkdir <path>` | Создать папку |
| `storage md5 <file>` | MD5-хеш |
| `storage stat <path>` | Информация о файле или папке |
| `storage timestamp <file>` | Время последнего изменения |
| `storage extract <archive.tar> <dir>` | Распаковать архив `.tar` |

### subghz

| Команда | Описание |
|---|---|
| `subghz chat <frequency> <device>` | Чат с другими Флипперами |
| `subghz tx <3-byte_key_hex> <frequency> <te_us> <repeat> <device>` | Передать ключ (Princeton) |
| `subghz rx <frequency> <device>` | Приём и декодирование |
| `subghz rx_raw <frequency>` | Приём RAW |
| `subghz decode_raw <path_to_raw_file>` | Декодировать RAW-файл `.sub` и вывести результат |
| `subghz tx_from_file <path> <repeat> <device>` | Передать сохранённый файл `.sub` |

Только в режиме отладки:

| Команда | Описание |
|---|---|
| `subghz tx_carrier <frequency>` | Передавать немодулированную несущую |
| `subghz rx_carrier <frequency>` | Приём несущей (RSSI) |
| `subghz encrypt_keeloq <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Зашифровать файл с ключами производителей KeeLoq |
| `subghz encrypt_raw <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Зашифровать RAW-данные |

`device`: `0` — встроенный CC1101, `1` — внешний CC1101 ([внешний модуль](/ru/subghz/external-cc1101)).
`te_us` — базовая длительность импульса в мкс.

Пример — передать сохранённый файл 3 раза через встроенное радио:

```
subghz tx_from_file /ext/subghz/gate.sub 3 0
```

### sysctl

| Команда | Описание |
|---|---|
| `sysctl debug <0/1>` | Выключить / включить системный режим отладки |
| `sysctl heap_track <none/main>` | Отслеживание выделений кучи для главного потока приложения; отладочные сборки (`DEBUG=1`) принимают также `tree` (главный + дочерние потоки) и `all` |

### update

| Команда | Описание |
|---|---|
| `update install /ext/path/to/update.fuf` | Проверить и установить пакет обновления (манифест `.fuf` внутри распакованной папки пакета) |
| `update backup /ext/backup.tar` | Бэкап внутренней памяти |
| `update restore /ext/backup.tar` | Восстановить внутреннюю память из бэкапа |

См. [OTA-обновления](/ru/dev/ota).

### vibro

| Команда | Описание |
|---|---|
| `vibro <1/0>` | Включить / выключить вибромотор |

## Связанные страницы

- [Отладка приложений](/ru/dev/debugging)
- [OTA-обновления](/ru/dev/ota)
- [Юнит-тесты](/ru/dev/unit-tests)
- [qFlipper](/ru/mobile/qflipper)

MIFARE, MIFARE Ultralight, MIFARE Classic, DESFire и ICODE — зарегистрированные товарные знаки NXP B.V. FeliCa —
товарный знак Sony Corporation.
