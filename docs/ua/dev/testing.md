---
title: Інтеграційне тестування
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/integration_tests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/general_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/badusb_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/cli_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/goodfaps_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/gpio_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/ibutton_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/infrared_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/nfc_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/rfid_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/subghz_test_cases.md]
sources: [unleashed-docs]
---
# Інтеграційне тестування

Окрім [юніт-тестів](/ua/dev/unit-tests), у прошивки є **ручний план інтеграційного тестування**: покрокові
тест-кейси, згруповані за підсистемами, кожен із описаним очікуваним результатом. Його писали для тих, хто
підтримує репозиторій, але він так само корисний, якщо ви збираєте власну прошивку й хочете перевірити її перед
використанням чи публікацією.

Ця сторінка підсумовує план. Повні списки кроків лежать у репозиторії Unleashed у папці
[`documentation/testing/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation/testing).

## Що і коли тестувати

- **Тестуйте те, що змінилося, плюс пов’язані регресії.** Перевірте нову поведінку й прогоніть кілька наявних
  кейсів тієї ж підсистеми. Приклад: додаючи протокол Sub-GHz, протестуйте його і ще декілька наявних протоколів.
- **Не чіпайте непов’язані підсистеми.** Немає сенсу тестувати NFC, якщо змінився лише Sub-GHz.
- **Тестуйте все, якщо зміни зачіпають ядро** — коли змінилося щось глобальне, прогоніть усі кейси по порядку.

Коли: **перед прийняттям pull request** і **перед релізним кандидатом**.

## Спільний шаблон тестування ключів і карт

Кейси протоколів RFID, iButton і NFC користуються тими самими «спільними кроками»:

1. **Read** оригіналу — дані збігаються з оригіналом.
2. **Emulate** — прочитайте емульований ключ другим Flipper; дані ідентичні.
3. **Save** — зберігається із заданим ім’ям, сцена перемикається на каталог *Saved*.
4. **Write** на заготовку — з’являється екран успіху.
5. **Read** записаної заготовки — дані ідентичні збереженому ключу.

Тому для багатьох кейсів потрібні **другий Flipper**, справжні зчитувачі та заготовки (T5577, RW2004/RW1990 тощо).

## Тест-кейси за підсистемами

### Загальні (35 кейсів)

| Ділянка | Що перевіряється |
|---|---|
| BLE | Bluetooth увімкнений після перезавантаження; парування з мобільним застосунком, правильна назва Flipper; повторне парування з другим телефоном |
| U2F | Реєстрація та автентифікація ключа на демосайті Yubico WebAuthn |
| Налаштування | PIN-код, Storage, Power, System, Bluetooth, Desktop, LCD and Notifications, Flipper Name |
| Archive і файловий браузер | Картка microSD із багатьма файлами: <kbd>↓</kbd> на робочому столі відкриває Archive; кожна вкладка (Favorites, iButton, NFC, Sub-GHz, RFID, Infrared, Browser) показує свої файли; запуск, перейменування, видалення ключів |
| Карти та протоколи | NTAG215, MIFARE DESFire, MIFARE Ultralight, MIFARE Classic 1K / 4K, Metakom |
| Заводське оновлення | Через qFlipper на macOS, Windows 11, Ubuntu; через застосунки для Android та iOS; через веб Flipper Lab |
| Налаштування регіону | Ті самі шість каналів, що й для заводського оновлення, плюс саме налаштування регіону |
| Застосунки | Базові застосунки, скрипти JS, меню на кнопці «вгору» |
| Відповідність вимогам | Усі екрани відповідності показуються правильно |

### CLI (3 кейси)

- **Команди керування:** `power` (off, reboot, reboot to DFU, `power 5v 1`), `gpio` (mode, `gpio set PA7 1`
  засвічує світлодіод на девборді), `led b 255`, `vibro 1` / `vibro 0`.
- **Команди отримання інформації:** під’єднайтеся через `minicom -D /dev/ttyACM0 -b 230400` або PuTTY; `log debug`
  під час користування пристроєм, зупинка — <kbd>Ctrl</kbd>+<kbd>C</kbd>; порівняйте `device_info` / `!` з екраном
  інформації про прошивку (утримуйте <kbd>↓</kbd> на робочому столі 3 с); `bt hci_info`; `date`; `help` / `?`;
  `free`; `free_blocks`.
- **Команди роботи зі сховищем:** `storage info /ext`, `storage format /ext` (спершу відмовтеся, потім
  підтвердьте), інформація з карткою та без неї; `factory_reset` — відповідь `n` нічого не робить, `y` стирає
  налаштування, але **залишає дані на картці microSD і час**.

Контрольні значення `bt hci_info` з плану:

```
Ret: 0, HCI_Version: 11, HCI_Revision: 16484, LMP_PAL_Version: 11, Manufacturer_Name: 48,
LMP_PAL_Subversion: 8548
```

### Sub-GHz (7 кейсів)

| Кейс | Ключові перевірки |
|---|---|
| Read RAW | Запис на 315, 433, 868 МГц, зокрема шифрованого пульта з динамічним кодом, як-от Came Atomo; відтворення на приймачі тестового стенда |
| Frequency Analyzer | Показує правильну частоту різних пультів |
| Зовнішній модуль | Зовнішній CC1101 (модуль на 433,92 МГц): піктограма змінюється на зовнішню, сигнал у Read RAW сильніший, ніж у внутрішнього; перемикання назад на внутрішній працює. Ніколи не виймайте модуль під час роботи — Flipper може зависнути |
| Збережені файли | Збереження декодованих і RAW-сигналів, додавання до улюблених і надсилання звідти, перейменування (залишається в улюблених), видалення |
| Приймання / передавання | Читання на 315.000, 433.920 і 868.350 МГц, потім з увімкненим перестрибуванням частот; надсилання збережених ключів — реле стенда (або другий Flipper) реагують |
| Add Manually | Створення сигналів вручну |

### NFC (7 кейсів)

| Кейс | Ключові перевірки |
|---|---|
| Unlock NTAG/Ultralight | *Auth as* для обох типів, попередження про хибний тип карти, введення пароля вручну; збережені карти з’являються в *Saved* приблизно за 1,5 с |
| Detect Reader | Збір nonce зі зчитувача (наприклад, з іншого Flipper), після чого екран із QR-кодом на <kbd>OK</kbd> читається |
| Емуляція | Читається кількома зчитувачами, зокрема Flipper на відстані 10 мм і Proxmark |
| Читання | MIFARE Classic, Ultralight, NTAG, DESFire, NFC-F, банківські карти EMV |
| Таймінги | Порівняйте таймінги емуляції Ultralight і Classic з еталоном за допомогою Proxmark 3 |
| Add Manually | Створення та збереження карт усіх типів, а потім їхня емуляція |
| Додаткові дії | *Read Specific Card Type*, *MIFARE Classic Keys* (додавання/видалення ключів, кнопка *List*), *Unlock SLIX* з паролем |

Команди Proxmark, які використовуються в тесті таймінгів:

```
hf 14a raw -sc 3000
trace list -t 14a --frame -u
```

### 125 кГц RFID (9 кейсів)

Кейси протоколів зі спільними кроками для **EM-Marine EM4100, Motorola Indala26, HID H10301 (Picopass), Indala26,
Troyka/Podorozhnik**, а також читання, запис на **T5577**, Add Manually та емуляція.

### iButton (9 кейсів)

**Dallas DS1971, DS1990, DS1992, DS1996**, **Cyfral**, **Metakom**: читання, збереження, Add Manually, емуляція
(читання різними пристроями), запис на заготовку **RW2004** і читання назад, редагування та видалення ключів.

### Інфрачервоний порт (3 кейси)

- **Універсальна бібліотека** — пульти для телевізорів, аудіо, кондиціонерів: живлення та інші функції працюють.
- **Learn new remote** — додавання/видалення пультів і кнопок, перейменування, передавання відредагованих кнопок.
- **Збережені пульти** — додавання кнопок до наявного пульта, керування пристроями з відстані **щонайменше 5 м**,
  видалення всіх кнопок і пультів.

### Bad USB (2 кейси)

На macOS і Windows: список скриптів показується; демонстраційний скрипт виконується з розкладкою EN і після зміни
розкладки; скрипт «qFlipper download» відкриває термінал і завантажує qFlipper; після перемикання в режим **BLE**
(з увімкненим Bluetooth) пристрій парується з комп’ютером і скрипт виконується знову.

### GPIO (1 кейс)

`GPIO → Manual Control` зі вставленою девбордою ST-Link: світлодіоди повторюють стан виводів; увімкнення 5 В
засвічує світлодіоди живлення.

### GoodFAPs — офіційні застосунки (10 кейсів)

| Застосунок | Ключові перевірки |
|---|---|
| PicoPass | Читання карти, збереження, запускається *Elite Dictionary Attack* |
| Weather Station | Читає метеостанцію, яку імітує другий Flipper, на різних частотах |
| Застосунки з каталогу | Установлення через мобільний застосунок або веб, правильні піктограма й назва, запуск/вихід, оновлення, видалення (із застосунку, вебу, файлового браузера) |
| AVR Flasher | Dump AVR, Flash AVR, ISP-програматор з `avrdude` |
| Video Game Module | Вставлення модуля → повідомлення про ініціалізацію та піктограма в рядку стану; HDMI дублює екран; «Air Arkanoid» використовує акселерометр |
| Tools | Clock (на весь екран, формат із налаштувань); NFC/RFID Detector виявляє поля обох типів |
| Signal Generator | Генератори PWM і Clock на різних виводах, частотах і дільниках |
| NFC Magic | *Check Magic Tag*, *Write Gen1a* (з попередженням про ризик), *Wipe* |
| SPI Mem Manager | Читання, запис і стирання мікросхеми SPI-флеш |
| Прошивання VGM | Застосунок VGM Tool: *Install official firmware*, установлення з файлу на картці, а також спосіб вручну (кнопка Boot + USB mass storage) |

Схема під’єднання AVR Flasher з плану:

| AVR | Flipper |
|---|---|
| MISO | PA6 |
| MOSI | PA7 |
| SCK | PB3 |
| RESET | PB2 |
| GND | GND |
| VCC | 3V3 |

Перевірка читання fuse-бітів (замініть `m2560` на свою мікросхему, наприклад `m328p`, і вкажіть свій COM-порт):

```
avrdude.exe -p m2560 -c stk500v1 -P COM7 -U lock:r:lock.hex:r -U hfuse:r:hfuse.hex:r -U lfuse:r:lfuse.hex:r -U efuse:r:efuse.hex:r
```

::: tip Unleashed
План узятий з офіційної прошивки. На Unleashed додатково перевіряйте те, що є лише в Unleashed, у підсистемі, яку
ви змінювали, — наприклад, додаткові протоколи Sub-GHz і [режим лічильника](/ua/subghz/counter-mode) або додаткові
застосунки в `applications/system/` (Remote Analyzer, Nice-O-Code, Sec+ PIN, Seed Capturer, Sub-GHz RAW editor,
T5577, SIM800…).
:::

## Пов’язані сторінки

- [Юніт-тести](/ua/dev/unit-tests)
- [Командний рядок](/ua/dev/cli)
- [Збірка прошивки](/ua/dev/build)
