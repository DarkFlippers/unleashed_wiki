---
title: Интеграционное тестирование
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/integration_tests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/general_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/badusb_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/cli_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/goodfaps_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/gpio_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/ibutton_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/infrared_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/nfc_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/rfid_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/subghz_test_cases.md]
sources: [unleashed-docs]
---
# Интеграционное тестирование

Помимо [юнит-тестов](/ru/dev/unit-tests), у прошивки есть **план ручного интеграционного тестирования**: пошаговые
тест-кейсы, сгруппированные по подсистемам, у каждого — ожидаемый результат. Он написан для мейнтейнеров
репозитория, но так же полезен, если вы собираете свою прошивку и хотите проверить её, прежде чем пользоваться или
делиться.

Здесь — краткое изложение плана. Полные списки шагов лежат в репозитории Unleashed в
[`documentation/testing/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation/testing).

## Что и когда тестировать

- **Тестируйте то, что изменилось, плюс связанные регрессии.** Проверьте новое поведение и повторите несколько
  существующих кейсов той же подсистемы. Пример: добавили протокол Sub-GHz — протестируйте его и несколько уже
  существующих протоколов.
- **Пропускайте несвязанные подсистемы.** Нет смысла тестировать NFC, если менялся только Sub-GHz.
- **При изменениях ядра тестируйте всё** — если изменилось что-то глобальное, пройдите все кейсы по порядку.

Когда: **перед принятием pull request-ов** и **перед релиз-кандидатом**.

## Общая схема для ключей и карт

Кейсы протоколов RFID, iButton и NFC используют одни и те же «общие шаги»:

1. **Read** — прочитать оригинал; данные совпадают с оригиналом.
2. **Emulate** — прочитать эмулируемый ключ вторым Флиппером; данные идентичны.
3. **Save** — ключ сохранён с заданным именем; сцена переключается в папку *Saved*.
4. **Write** на болванку — появляется экран успеха.
5. **Прочитать записанную** болванку — данные идентичны сохранённому ключу.

Поэтому для многих кейсов нужен **второй Флиппер**, реальные считыватели и болванки (T5577, RW2004/RW1990 и т. п.).

## Тест-кейсы по подсистемам

### Общие (35 кейсов)

| Область | Что проверяется |
|---|---|
| BLE | Bluetooth включён после перезагрузки; сопряжение с мобильным приложением, правильное имя Флиппера; повторное сопряжение со вторым телефоном |
| U2F | Регистрация и аутентификация ключа на демо-сайте Yubico WebAuthn |
| Настройки | PIN-код, Storage, Power, System, Bluetooth, Desktop, LCD and Notifications, имя Флиппера |
| Archive и файловый браузер | SD-карта с большим количеством файлов: <kbd>↓</kbd> на рабочем столе открывает Archive; каждая вкладка (Favorites, iButton, NFC, Sub-GHz, RFID, Infrared, Browser) показывает свои файлы; запуск, переименование, удаление ключей |
| Карты и протоколы | NTAG215, MIFARE DESFire, MIFARE Ultralight, MIFARE Classic 1K / 4K, Metakom |
| Заводское обновление | Через qFlipper на macOS, Windows 11, Ubuntu; через приложения Android и iOS; через веб Flipper Lab |
| Region provisioning | Те же шесть способов, что и для заводского обновления, плюс сама настройка региона |
| Приложения | Базовые приложения, JS-скрипты, меню на кнопке «вверх» |
| Compliance | Все экраны compliance отображаются корректно |

### CLI (3 кейса)

- **Команды управления:** `power` (off, reboot, перезагрузка в DFU, `power 5v 1`), `gpio` (mode, `gpio set PA7 1`
  зажигает светодиод на devboard), `led b 255`, `vibro 1` / `vibro 0`.
- **Информационные команды:** подключение через `minicom -D /dev/ttyACM0 -b 230400` или PuTTY; `log debug` во время
  работы с устройством, остановка — <kbd>Ctrl</kbd>+<kbd>C</kbd>; сравнить `device_info` / `!` с экраном информации о
  прошивке (удерживать <kbd>↓</kbd> на рабочем столе 3 с); `bt hci_info`; `date`; `help` / `?`; `free`;
  `free_blocks`.
- **Команды storage:** `storage info /ext`, `storage format /ext` (сначала отказаться, затем подтвердить), info с
  картой и без; `factory_reset` — ответ `n` ничего не делает, `y` стирает настройки, но **сохраняет данные на
  SD-карте и время**.

Эталонные значения `bt hci_info` из плана:

```
Ret: 0, HCI_Version: 11, HCI_Revision: 16484, LMP_PAL_Version: 11, Manufacturer_Name: 48,
LMP_PAL_Subversion: 8548
```

### Sub-GHz (7 кейсов)

| Кейс | Ключевые проверки |
|---|---|
| Read RAW | Запись на 315, 433, 868 МГц, включая пульт с шифрованием (роллинг-код), например Came Atomo; воспроизведение на приёмники тестового стенда |
| Frequency Analyzer | Показывает правильную частоту разных пультов |
| Внешний модуль | Внешний CC1101 (модуль на 433,92 МГц): иконка меняется на внешний модуль, сигнал в Read RAW сильнее, чем со встроенным; переключение обратно на встроенный работает. Никогда не отключайте модуль во время работы — Флиппер может зависнуть |
| Сохранённые файлы | Сохранить декодированные и RAW-сигналы, добавить в избранное и отправить оттуда, переименовать (остаётся в избранном), удалить |
| Приём / передача | Read на 315.000, 433.920 и 868.350 МГц, затем с включённым hopping; отправка сохранённых ключей — срабатывают реле стенда (или второй Флиппер) |
| Add Manually | Создание сигналов вручную |

### NFC (7 кейсов)

| Кейс | Ключевые проверки |
|---|---|
| Unlock NTAG/Ultralight | *Auth as* для обоих типов, предупреждение о неверном типе карты, ручной ввод пароля; сохранённые карты появляются в *Saved* примерно через 1,5 с |
| Detect Reader | Сбор nonce-ов со считывателя (например, другого Флиппера), затем экран с QR-кодом по <kbd>OK</kbd> читается камерой |
| Эмуляция | Читается разными считывателями, в том числе Флиппером с 10 мм и Proxmark |
| Чтение | MIFARE Classic, Ultralight, NTAG, DESFire, NFC-F, банковские карты EMV |
| Тайминги | Сравнение таймингов эмуляции Ultralight и Classic с эталоном с помощью Proxmark 3 |
| Add Manually | Создать и сохранить карты всех типов, затем эмулировать их |
| Extra actions | *Read Specific Card Type*, *MIFARE Classic Keys* (добавление/удаление ключей, кнопка *List*), *Unlock SLIX* с паролем |

Команды Proxmark для теста таймингов:

```
hf 14a raw -sc 3000
trace list -t 14a --frame -u
```

### RFID 125 кГц (9 кейсов)

Кейсы протоколов с общими шагами для **EM-Marine EM4100, Motorola Indala26, HID H10301 (Picopass), Indala26,
Тройка/Подорожник**, плюс чтение, запись на **T5577**, Add Manually и эмуляция.

### iButton (9 кейсов)

**Dallas DS1971, DS1990, DS1992, DS1996**, **Cyfral**, **Metakom**: чтение, сохранение, Add Manually, эмуляция
(чтение разными устройствами), запись на болванку **RW2004** и обратное чтение, редактирование и удаление ключей.

### Infrared (3 кейса)

- **Universal library** — пульты TV, аудио, кондиционеров: включение и другие функции работают.
- **Learn new remote** — добавление/удаление пультов и кнопок, переименование, передача отредактированных кнопок.
- **Saved remotes** — добавление кнопок к существующему пульту, управление устройствами с расстояния **не менее
  5 м**, удаление всех кнопок и пультов.

### Bad USB (2 кейса)

На macOS и Windows: отображается список скриптов; демо-скрипт выполняется с раскладкой EN и после смены раскладки;
скрипт «qFlipper download» открывает терминал и скачивает qFlipper; при переключении в режим **BLE** (Bluetooth
включён) устройство сопрягается с компьютером, и скрипт снова выполняется.

### GPIO (1 кейс)

`GPIO → Manual Control` со вставленной платой ST-Link devboard: светодиоды следуют за пинами; включение 5 В зажигает
светодиоды питания.

### GoodFAPs — официальные приложения (10 кейсов)

| Приложение | Ключевые проверки |
|---|---|
| PicoPass | Чтение карты, сохранение, запуск *Elite Dictionary Attack* |
| Weather Station | Читает метеостанцию, которую эмулирует второй Флиппер на разных частотах |
| Приложения из каталога | Установка через мобильное приложение или веб, корректные иконка и имя, запуск/выход, обновление, удаление (приложение, веб, файловый браузер) |
| AVR Flasher | Dump AVR, Flash AVR, ISP-программатор с `avrdude` |
| Video Game Module | Вставить модуль → сообщение инициализации и иконка в статус-баре; HDMI дублирует экран; «Air Arkanoid» управляется акселерометром |
| Tools | Clock (на весь экран, формат из настроек); NFC/RFID Detector определяет оба типа поля |
| Signal Generator | Генераторы PWM и Clock на разных пинах, частотах и делителях |
| NFC Magic | *Check Magic Tag*, *Write Gen1a* (с предупреждением о риске), *Wipe* |
| SPI Mem Manager | Чтение, запись, стирание SPI-флешки |
| Прошивка VGM | Приложение VGM Tool: *Install official firmware*, установка из файла на SD и ручной способ (кнопка Boot + USB mass storage) |

Подключение AVR Flasher по плану:

| AVR | Флиппер |
|---|---|
| MISO | PA6 |
| MOSI | PA7 |
| SCK | PB3 |
| RESET | PB2 |
| GND | GND |
| VCC | 3V3 |

Проверка чтения фьюзов (замените `m2560` на свой чип, например `m328p`, и номер COM-порта):

```
avrdude.exe -p m2560 -c stk500v1 -P COM7 -U lock:r:lock.hex:r -U hfuse:r:hfuse.hex:r -U lfuse:r:lfuse.hex:r -U efuse:r:efuse.hex:r
```

::: tip Unleashed
План взят из официальной прошивки. В Unleashed дополнительно проверяйте возможности, которых нет в стоке, в той
подсистеме, которую меняли, — например, дополнительные протоколы Sub-GHz и [counter mode](/ru/subghz/counter-mode),
или дополнительные приложения в `applications/system/` (Remote Analyzer, Nice-O-Code, Sec+ PIN, Seed Capturer,
Sub-GHz RAW editor, T5577, SIM800…).
:::

## Связанные страницы

- [Юнит-тесты](/ru/dev/unit-tests)
- [Командная строка (CLI)](/ru/dev/cli)
- [Сборка прошивки](/ru/dev/build)
