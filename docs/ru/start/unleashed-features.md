---
title: Возможности Unleashed
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings]
sources: [unleashed-readme, unleashed-src]
---
# Возможности Unleashed

Unleashed построен на официальной прошивке (OFW) и **полностью совместим с её API и приложениями**: всё, что умеет
стоковая прошивка, продолжает работать. Ниже перечислены изменения и дополнения относительно официальной версии прошивки (OFW).

## Sub-GHz: радиобиблиотека и железо

- **Сняты региональные ограничения на передачу.** Передача работает на всех частотах, которые поддерживает чип CC1101,
  без дополнительных действий.
- **Дополнительные частоты** в стандартном списке и редактируемый пользователем список частот: [Частоты и пресеты](/ru/subghz/frequencies).
- **Опциональный расширенный диапазон** за пределами спецификации чипа. Может повредить железо:
  [Опасные настройки](/ru/start/dangerous-settings).
- **Большое число нестандартных протоколов** с возможностью **сохранять и отправлять сигналы многих динамических систем**:
  [Поддерживаемые системы](/ru/subghz/supported-systems), [Динамические коды](/ru/subghz/rolling-codes), [KeeLoq](/ru/subghz/keeloq).
- Поддержка **внешнего модуля CC1101** по аппаратному SPI с управлением усилителем/светодиодом:
  [Внешний CC1101](/ru/subghz/external-cc1101).
- **Специальные режимы работы счётчика** для динамических кодов, чтобы избежать рассинхронизации: [Режим счётчика](/ru/subghz/counter-mode).

## Sub-GHz: основное приложение

- **Запоминаются последние настройки** (частота, модуляция…).
- **Улучшения Frequency Analyzer**: основной функционал аналогичен официальной прошивке; дополнительно реализовано:
  в Unleashed <kbd>OK</kbd> передаёт найденную частоту в Read, а долгое <kbd>OK</kbd> сразу открывает Read: [Frequency Analyzer](/ru/subghz/frequency-analyzer).
- **Улучшения Read**: показывается время приёма сигнала. Удержание <kbd>→</kbd> в списке удаляет сигнал.
  Многосистемные протоколы показывают название распознанной системы (CAME, Nice FloR-S, FAAC SLH, KeeLoq): [Read](/ru/subghz/read).
- **Имена протоколов в именах файлов**: `Radio Settings → Protocol Names = ON` — сохранённые файлы получают имя из
  метки времени и протокола.
- **Кастомные кнопки** для KeeLoq, Alutech AT4N, Nice Flor S, Somfy Telis, Security+ 2.0, CAME Atomo, BelKorn и
  других: стрелками джойстика можно отправить сигнал с другим кодом кнопки: [Флиппер как пульт](/ru/subghz/remote).
- **Расширенный `Add manually`**: один пункт на систему, выбор диапазона, продвинутый режим с TE, guard time и другими
  полями. Можно создать пульты FAAC SLH, BFT Mitto, Somfy Telis, Nice Flor S, CAME Atomo и другие и привязать их к
  приёмнику: [Add manually](/ru/subghz/add-manually), [Привязка нового пульта](/ru/subghz/remote-prog).
- **Read RAW → More → Edit** открывает RAW-файл прямо в Sub-GHz RAW Edit: [RAW-редактор](/ru/subghz/raw-editor).
- **Фильтры Ignore** для «шумных» протоколов (сигнализации, датчики, звонки, поисковые брелоки, светильники Feron…) и
  отладочные опции (шаг счётчика, вывод на отладочный пин): [Настройки Sub-GHz](/ru/subghz/settings).

## Приложения Sub-GHz

| Приложение | Что делает | Страница |
|---|---|---|
| Sub-GHz Remote | До 5 файлов `.sub` на кнопки, встроенный конфигуратор | [Пульт](/ru/subghz/remote) |
| Sub-GHz Bruteforcer | Перебор статических кодов, свои файлы, задержка и повторы | [Брутфорс](/ru/subghz/bruteforce) |
| Remote Analyzer | Расшифровка одного пульта за раз, встроенный анализатор частоты | [Remote Analyzer](/ru/subghz/remote-analyzer) |
| Nice O-Code | Восстановление installer code пульта Nice O-Code | [Nice O-Code](/ru/subghz/nice-o-code) |
| Security+ PIN | Поиск PIN клавиатуры по сигналу Security+ 2.0 | [Security+ PIN](/ru/subghz/secplus-pin) |
| Seed Capturer | Сбор пар Fix + Hop (FAAC SLH, Genius, Erreka, BFT Mitto) для восстановления seed | [Seed Capturer](/ru/subghz/seed-capturer) |
| Sub-GHz RAW Edit | Обрезка, склейка и расшифровка RAW-записей | [RAW-редактор](/ru/subghz/raw-editor) |

## NFC, RFID и iButton

- **Дополнительные ключи MIFARE Classic** в системном словаре: [MIFARE Classic](/ru/nfc/mifare-classic). Гайды по
  восстановлению ключей: [Nested и Fudan](/ru/nfc/nested-fudan), [MFKey](/ru/nfc/mfkey).
- **MFKey** прямо на устройстве: [Приложение MFKey](/ru/nfc/mfkey-app).
- **Протокол EMV и парсер публичных данных**: [Банковские карты (EMV)](/ru/nfc/emv).
- **NFC `Add manually` → MIFARE Classic с произвольным UID**: [Add manually](/ru/nfc/add-manually).
- **Много дополнительных парсеров карт** (транспортные и городские карты: Тройка, Умарш, Золотая Корона, Казань,
  Metromoney, Социальная карта москвича и другие): [Поддерживаемые карты](/ru/nfc/supported-cards).
- **NFC Magic 2.0** для magic-карт, включая Ultralight: [NFC Magic](/ru/nfc/nfc-magic).
- **Приложение T5577**: чтение, редактирование и запись блоков, очистка и сброс пароля, сниффер пароля (`Sniff Password`):
  [Приложение T5577](/ru/rfid/t5577-app).
- Формат отображения **DEZ 8** для EM4100: [Чтение RFID](/ru/rfid/read).
- **Фаззеры RFID и iButton**: [RFID Fuzzer](/ru/rfid/fuzzer), [iButton Fuzzer](/ru/ibutton/fuzzer).

## Инфракрасный порт

- Универсальный пульт для ТВ пересобран и покрывает **все кнопки**.
- **Большая коллекция универсальных пультов для проекторов, вентиляторов, кондиционеров и аудио** (саундбары и т. п.).
  Коллекция регулярно обновляется, проверяется и пополняется командой.
- Протокол **RCA** и поддержка внешних ИК-модулей (с автоопределением): [Универсальные пульты](/ru/infrared/universal-remotes).
- Как правильно записывать сигналы для включения в базу универсальных пультов: [ИК-записи](/ru/infrared/captures).

## Bad USB и USB/Bluetooth

- **BadKB**: скрипты Bad USB по **Bluetooth**, встроено в приложение Bad USB: [Bad USB](/ru/badusb/usage).
- **Раскладки клавиатуры** и команда `DUCKY_LANG`, которой скрипт сам выбирает раскладку: [Формат скриптов](/ru/badusb/script-format).

## Рабочий стол, настройки и удобства

- **Своё имя Флиппера** в **Settings → Desktop → Change Flipper Name**: [Своё имя](/ru/start/custom-name).
- **Часы на рабочем столе** (`Settings → Desktop → Show Clock`) и **стили батареи** (`Battery View`: Bar, %, Inv. %,
  Retro 3, Retro 5, Bar %): [Рабочий стол](/ru/start/desktop).
- **Блокировка удержанием <kbd>↑</kbd>** на рабочем столе: с PIN, если он задан, иначе обычная блокировка.
- **Больше игр в Dummy Mode**: каждая стрелка (короткое и долгое нажатие) и <kbd>OK</kbd> могут запускать своё приложение.
- Поддержка **[RGB-мода подсветки](https://github.com/quen0n/flipperzero-firmware-rgb#readme)** в **LCD and Notifications → RGB Mod Settings** (только для Флипперов с аппаратным модом).
- **Курсор в текстовом вводе** и **мини-редактор байтов** (нажимайте <kbd>↑</kbd>, пока не появится редактор полубайтов).
- В **Archive** есть дополнительные вкладки: SubRem для карт Sub-GHz Remote и Phone для телефонной книги SIM800.

Все пункты настроек описаны на странице [Настройки](/ru/start/settings).

## Встроенные приложения {#built-in-apps}

Эти приложения собираются из репозитория прошивки и устанавливаются в `/ext/apps/` при каждом обновлении — в **любом**
варианте сборки (`e`, без суффикса, `c`). В наборах приложений их нет, поэтому набор никогда не перезапишет и не
откатит их.

**В главном меню:** GPIO, iButton, Infrared, NFC, 125 kHz RFID, Bad USB (с BadKB), U2F, **Clock** (яркость, будильник,
таймер), **Sub-GHz Remote**. Sub-GHz, Archive и Settings входят в саму прошивку.

**В Apps:**

| Приложение | Категория | Страница |
|---|---|---|
| MFKey | NFC | [Приложение MFKey](/ru/nfc/mfkey-app) |
| T5577 | RFID | [Приложение T5577](/ru/rfid/t5577-app) |
| Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit | Sub-GHz | см. таблицу выше |
| SIM800 (звонки, SMS, телефонная книга, USSD, AT-терминал) | GPIO | [SIM800](/ru/gpio/sim800) |
| FindMy Flipper (маячок для Apple FindMy / Google Find My Device) | Bluetooth | [Каталог приложений](/ru/apps/catalog) |
| USB Keyboard & Mouse, Bluetooth Remote | USB / Bluetooth | [Контроллеры](/ru/apps/controllers) |
| Snake Game | Games | — |

## Наборы приложений сообщества

- **Base pack** (в сборках без суффикса и `e`) и **Extra pack** (только `e`): исходники и полный список —
  [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev), свежие наборы —
  в [релизах на GitHub](https://github.com/xMasterX/all-the-plugins/releases/latest).
- Официальный каталог тоже работает: [lab.flipper.net/apps](https://lab.flipper.net/apps) или мобильное приложение.
- Подробнее: [Каталог приложений](/ru/apps/catalog), [Приложения на SD-карте](/ru/apps/sd-card-apps).

## Приложения-компаньоны и веб-инструменты

- **qUnleashed** — приложение-компаньон для телефона и ПК: [qUnleashed](/ru/mobile/qunleashed-app).
- **Веб-инструменты**: [Web Installer](https://web.unleashedflip.com), карта Sub-GHz ([map.unleashedflip.com](https://map.unleashedflip.com)),
  карта Wi-Fi вардрайвинга ([wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)), веб-прошивальщик ESP32
  ([espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)): [Веб-инструменты](/ru/mobile/web-tools).
