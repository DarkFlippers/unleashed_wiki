---
title: Можливості Unleashed
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings]
sources: [unleashed-readme, unleashed-src]
---
# Що додає Unleashed

Unleashed побудований на офіційній прошивці (OFW) і залишається **повністю сумісним із її API та застосунками**.
Усе, що вміє стокова прошивка, працює й тут. На цій сторінці перелічено те, що Unleashed додає або змінює, за
напрямками й із посиланнями на сторінки вікі, де кожна можливість описана докладно.

## Sub-GHz: радіобібліотека та обладнання

- **Знято регіональні обмеження на передавання.** Передавати можна на будь-якій частоті, яку підтримує чип
  CC1101, без додаткових дій.
- **Додаткові частоти** у стандартному переліку (наприклад, нещодавно додали 317,0 і 336,1 МГц) і перелік частот,
  який можна редагувати самому: [Частоти](/ua/subghz/frequencies).
- **Необов'язковий розширений діапазон частот** поза специфікацією чипа. Він може пошкодити обладнання:
  [Небезпечні налаштування](/ua/start/dangerous-settings).
- **Багато нових протоколів** і можливість **зберігати й надсилати багато систем із динамічним кодом**:
  [Підтримувані системи](/ua/subghz/supported-systems), [Динамічні коди](/ua/subghz/rolling-codes),
  [KeeLoq](/ua/subghz/keeloq).
- Підтримка **зовнішнього модуля CC1101** через апаратний SPI, з керуванням підсилювачем/світлодіодом:
  [Зовнішній CC1101](/ua/subghz/external-cc1101).
- **Режими лічильника** для динамічних кодів, щоб уникнути розсинхронізації:
  [Режими лічильника](/ua/subghz/counter-mode).

## Sub-GHz: основний застосунок

- **Останні використані налаштування запам'ятовуються** (частота, модуляція…).
- **Покращення Frequency Analyzer**: сам аналізатор — з офіційної прошивки; в Unleashed <kbd>OK</kbd> передає
  знайдену частоту в Read, а довге натискання <kbd>OK</kbd> переходить одразу до Read: [Frequency Analyzer](/ua/subghz/frequency-analyzer).
- **Покращення Read**: показує, коли було отримано кожний сигнал. Утримання <kbd>→</kbd> у переліку видаляє
  сигнал. Для багатосистемних протоколів показується декодована назва системи (CAME, Nice FloR-S, FAAC SLH,
  KeeLoq): [Read](/ua/subghz/read).
- **Назви протоколів в іменах файлів**: `Radio Settings → Protocol Names = ON` називає збережені файли за
  позначкою часу плюс протоколом.
- **Кастомні кнопки** для KeeLoq, Alutech AT4N, Nice Flor S, Somfy Telis, Security+ 2.0, CAME Atomo, BelKorn та
  інших. Клавішами-стрілками можна надіслати код іншої кнопки:
  [Використання як пульта](/ua/subghz/remote).
- **Розширений `Add manually`**: по одному запису на систему, вибір діапазону, розширений режим із TE, guard time
  та іншими полями. Можна створити пульт FAAC SLH, BFT Mitto, Somfy Telis, Nice Flor S, CAME Atomo та інші й
  прописати їх у приймач: [Add Manually](/ua/subghz/add-manually),
  [Програмування нового пульта](/ua/subghz/remote-prog).
- **Read RAW → More → Edit** відкриває RAW-файл прямо в Sub-GHz RAW Edit: [Редактор RAW](/ua/subghz/raw-editor).
- **Фільтри ignore** для шумних протоколів (сигналізації, датчики, дзвінки, шукачі ключів, світильники Feron…) і
  відлагоджувальні опції (крок інкременту лічильника, вивід на debug-пін):
  [Налаштування Sub-GHz](/ua/subghz/settings).

## Застосунки Sub-GHz

| Застосунок | Що робить | Сторінка |
|---|---|---|
| Sub-GHz Remote | Прив'язує до 5 файлів `.sub` до кнопок, із вбудованим конфігуратором | [Remote](/ua/subghz/remote) |
| Sub-GHz Bruteforcer | Перебір статичних кодів, власні файли, затримка й повтори | [Брутфорс Sub-GHz](/ua/subghz/bruteforce) |
| Remote Analyzer | Декодування одного пульта за раз, із вбудованим аналізатором частот | [Remote Analyzer](/ua/subghz/remote-analyzer) |
| Nice O-Code | Відновлення коду інсталятора пульта Nice O-Code | [Nice O-Code](/ua/subghz/nice-o-code) |
| Security+ PIN | Пошук PIN-коду клавіатури за сигналом Security+ 2.0 | [Security+ PIN](/ua/subghz/secplus-pin) |
| Seed Capturer | Збір пар Fix + Hop (FAAC SLH, Genius, Erreka, BFT Mitto) для відновлення seed | [Seed Capturer](/ua/subghz/seed-capturer) |
| Sub-GHz RAW Edit | Обрізання, склеювання й декодування RAW-записів | [Редактор RAW](/ua/subghz/raw-editor) |

## NFC, RFID та iButton

- **Додаткові ключі MIFARE Classic** у системному словнику: [MIFARE Classic](/ua/nfc/mifare-classic).
  Інструкції з відновлення ключів: [Nested і Fudan](/ua/nfc/nested-fudan), [MFKey](/ua/nfc/mfkey).
- **MFKey** просто на пристрої: [Застосунок MFKey](/ua/nfc/mfkey-app).
- **Протокол EMV і парсер публічних даних**: [Банківські картки (EMV)](/ua/nfc/emv).
- **NFC `Add manually` → MIFARE Classic із власним UID**: [Додавання міток вручну](/ua/nfc/add-manually).
- **Багато додаткових парсерів карток** (транспортні й міські картки: Troika, Umarsh, Zolotaya Korona, Kazan,
  Metromoney, Moscow Social Card та інші): [Підтримувані картки](/ua/nfc/supported-cards).
- **NFC Magic 2.0** для magic-карток, включно з Ultralight: [NFC Magic](/ua/nfc/nfc-magic).
- **Застосунок T5577**: читання, редагування й запис блоків, очищення або скидання пароля, перехоплення пароля:
  [Застосунок T5577](/ua/rfid/t5577-app).
- Формат відображення **EM4100 DEZ 8**: [Зчитування RFID](/ua/rfid/read).
- **Фузери RFID та iButton**: [RFID Fuzzer](/ua/rfid/fuzzer), [iButton Fuzzer](/ua/ibutton/fuzzer).

## Інфрачервоний порт

- Універсальний пульт для телевізорів перероблено так, щоб він охоплював **усі кнопки**.
- **Універсальні пульти для проєкторів, вентиляторів, кондиціонерів і аудіотехніки** (саундбари…), які команда
  тримає актуальними.
- Протокол **RCA** і підтримка зовнішнього ІЧ-модуля (визначається автоматично):
  [Універсальні пульти](/ua/infrared/universal-remotes).
- Як робити добрі записи для бази універсальних пультів: [Записи ІЧ-сигналів](/ua/infrared/captures).

## Bad USB і USB/Bluetooth

- **BadKB**: запуск скриптів Bad USB через **Bluetooth**, інтегрований у застосунок Bad USB:
  [Bad USB](/ua/badusb/usage).
- **Розкладки клавіатури** і команда `DUCKY_LANG`, яка дозволяє скрипту вибрати власну розкладку:
  [Формат скриптів](/ua/badusb/script-format).

## Робочий стіл, налаштування та дрібні зручності

- **Власне ім'я Фліппера** у **Settings → Desktop → Change Flipper Name**:
  [Власне ім'я](/ua/start/custom-name).
- **Годинник на робочому столі** (`Settings → Desktop → Show Clock`) і **стилі індикатора акумулятора**
  (`Battery View`: Bar, %, Inv. %, Retro 3, Retro 5, Bar %): [Робочий стіл](/ua/start/desktop).
- **Блокування утриманням <kbd>↑</kbd>** на робочому столі: з PIN-кодом, якщо він заданий, інакше звичайне
  блокування.
- **Більше ігор у Dummy Mode**: кожна стрілка (коротке й довге натискання) та <kbd>OK</kbd> можуть запускати
  власний застосунок.
- Підтримка **модифікації з RGB-підсвіткою** в **LCD and Notifications → RGB Mod Settings** (лише для Flipper із
  апаратною модифікацією).
- **Курсор у полі введення тексту** і **мініредактор побайтового введення** (натискайте <kbd>↑</kbd>, доки не
  з'явиться редактор півбайтів).
- **Archive** із додатковими вкладками (SubRem для розкладок Sub-GHz Remote, Phone для телефонної книги SIM800).

Усі пункти Settings описані на сторінці [Налаштування](/ua/start/settings).

## Вбудовані застосунки {#built-in-apps}

Ці застосунки збираються з репозиторію прошивки й встановлюються в `/ext/apps/` кожним оновленням, у **кожному**
варіанті збірки (`e`, без суфікса, `c`). Пакети застосунків їх не містять, тому пакет ніколи не перезапише їх і не
відкотить до старішої версії.

**У головному меню:** GPIO, iButton, Infrared, NFC, 125 kHz RFID, Bad USB (із BadKB), U2F, **Clock** (керування
яскравістю, будильник, таймер), **Sub-GHz Remote**. Sub-GHz, Archive і Settings є частиною двійкового файлу
прошивки.

**В Apps:**

| Застосунок | Категорія | Сторінка |
|---|---|---|
| MFKey | NFC | [Застосунок MFKey](/ua/nfc/mfkey-app) |
| T5577 | RFID | [Застосунок T5577](/ua/rfid/t5577-app) |
| Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit | Sub-GHz | див. таблицю вище |
| SIM800 (дзвінки, SMS, телефонна книга, USSD, AT-термінал) | GPIO | [SIM800](/ua/gpio/sim800) |
| FindMy Flipper (маячок Apple FindMy / Google Find My Device) | Bluetooth | [Каталог застосунків](/ua/apps/catalog) |
| USB Keyboard & Mouse, Bluetooth Remote | USB / Bluetooth | [Контролери](/ua/apps/controllers) |
| Snake Game | Games | — |

## Пакети застосунків від спільноти

- **Базовий пакет** (у збірках без суфікса та `e`) і **додатковий пакет** (лише `e`): джерела й повний перелік —
  на [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev). Найновіші пакети є в
  [релізах на GitHub](https://github.com/xMasterX/all-the-plugins/releases/latest).
- Офіційний каталог теж працює: [lab.flipper.net/apps](https://lab.flipper.net/apps) або мобільний застосунок.
- Докладніше: [Каталог застосунків](/ua/apps/catalog),
  [Застосунки на SD-картці](/ua/apps/sd-card-apps).

## Супутні застосунки та вебінструменти

- **qUnleashed**: супутній застосунок для смартфона й ПК: [qUnleashed](/ua/mobile/qunleashed-app).
- **Вебінструменти**: [Web Installer](https://web.unleashedflip.com), карта Sub-GHz
  ([map.unleashedflip.com](https://map.unleashedflip.com)), карта Wi-Fi-вардрайвінгу
  ([wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)), вебпрошивальник ESP32
  ([espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)):
  [Вебінструменти](/ua/mobile/web-tools).
