---
title: Sub-GHz
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz]
---
# Sub-GHz

Во Flipper Zero встроен трансивер **CC1101** с антенной для диапазонов ниже 1 ГГц. С ним можно принимать,
сохранять и повторять сигналы пультов от ворот и гаражей, шлагбаумов, рольставней, дверных звонков,
беспроводных датчиков и прочих устройств, работающих в диапазонах **300–348 МГц, 387–464 МГц и 779–928 МГц**.
Чаще всего пульты работают на **315 МГц**, **433.92 МГц** или **868.35 МГц**.

Приложение находится в `Main Menu → Sub-GHz`. Его главное меню в Unleashed:

![Главное меню Sub-GHz: Read, Read RAW, Saved, Add Manually](/screens/subghz/menu.png)

| Пункт меню | Что делает | Страница |
|---|---|---|
| `Read` | Декодирует пульты известных протоколов, сохраняет и отправляет | [Read](/ru/subghz/read) |
| `Read RAW` | Записывает «сырой» сигнал любого пульта и воспроизводит его | [Read RAW](/ru/subghz/read-raw) |
| `Saved` | Сохранённые `.sub`-файлы: Emulate, Rename, Delete и Signal Settings при включённом Debug | [Read](/ru/subghz/read) |
| `Add Manually` | Создаёт новый пульт со случайным серийным номером | [Add Manually](/ru/subghz/add-manually) |
| `Add Manually [Advanced]` | То же, но серийник / кнопку / счётчик / сид вводите сами | [Add Manually](/ru/subghz/add-manually) |
| `Frequency Analyzer` | Определяет, на какой частоте передаёт пульт | [Frequency Analyzer](/ru/subghz/frequency-analyzer) |
| `Radio Settings` | Внутренний / внешний модуль, мощность, имена файлов, шаг счётчика | [Настройки](/ru/subghz/settings) |

::: tip Unleashed
Приложение Sub-GHz, его библиотека протоколов и Frequency Analyzer — из официальной прошивки. Unleashed снимает
региональные ограничения на передачу, добавляет частоты и ещё протоколы, позволяет сохранять и отправлять многие динамические (rolling code) протоколы, создаёт
новые динамические пульты, которые можно привязать к своему приёмнику (`Add Manually`), использует стрелки
как дополнительные кнопки пульта, поддерживает внешний модуль CC1101 и включает дополнительные Sub-GHz
приложения (Remote Analyzer, Seed Capturer, Nice O-Code, Security+ PIN, Sub-GHz RAW Edit, Sub-GHz Remote).
:::

::: warning
Используйте эти функции только со своим оборудованием или в рамках законных исследований.
:::

## С чего начать

1. Узнайте частоту пульта — [Frequency Analyzer](/ru/subghz/frequency-analyzer).
2. Попробуйте декодировать его — [Read](/ru/subghz/read). Если сигнал распознан и протокол **статический** —
   сохраните его, и всё готово.
3. Если пульт **динамический** (rolling code), не клонируйте его — прочитайте про
   [динамические коды](/ru/subghz/rolling-codes) и создайте новый пульт через
   [Add Manually](/ru/subghz/add-manually) + [привязку нового пульта](/ru/subghz/remote-prog).
4. Если ничего не декодируется — запишите сигнал через [Read RAW](/ru/subghz/read-raw).

## Все страницы

**Основы**
- [Частоты](/ru/subghz/frequencies) — диапазоны, списки по умолчанию, региональные ограничения и расширенный диапазон
- [Frequency Analyzer](/ru/subghz/frequency-analyzer) — как узнать частоту пульта
- [Read](/ru/subghz/read) — декодирование, сохранение и отправка сигналов
- [Read RAW](/ru/subghz/read-raw) — запись «сырых» сигналов

**Динамические коды и новые пульты**
- [Add Manually](/ru/subghz/add-manually) — все протоколы меню
- [Динамические коды](/ru/subghz/rolling-codes) — конфликт счётчиков, кастомные кнопки
- [KeeLoq](/ru/subghz/keeloq) — как устроен KeeLoq, мануфактурные ключи и сиды
- [Привязка нового пульта](/ru/subghz/remote-prog) — пошагово для каждой системы
- [Режимы счётчика](/ru/subghz/counter-mode) — экспериментальный `CounterMode` для клонов
- [Signal Settings](/ru/subghz/signal-settings) — режим счётчика, счётчик и кнопка сохранённого сигнала
- [Поддерживаемые системы](/ru/subghz/supported-systems) — полная таблица протоколов

**Настройки и железо**
- [Настройки](/ru/subghz/settings) — Radio Settings, конфиг Read, свои частоты
- [Формат файлов](/ru/subghz/file-format) — `.sub`, пресеты, пользовательские файлы настроек
- [Внешний CC1101](/ru/subghz/external-cc1101) — внешние модули и усилители

**Приложения**
- [Sub-GHz Remote](/ru/subghz/remote) — до 5 сигналов на кнопках
- [Sub-GHz Bruteforce](/ru/subghz/bruteforce) — перебор статических кодов
- [Remote Analyzer](/ru/subghz/remote-analyzer) — разбор одного пульта, дополнительные протоколы
- [Nice O-Code](/ru/subghz/nice-o-code) — восстановление кода установщика
- [Security+ PIN](/ru/subghz/secplus-pin) — PIN клавиатуры Security+ 2.0
- [Seed Capturer](/ru/subghz/seed-capturer) — сбор hop'ов для восстановления сида
- [Sub-GHz RAW Edit](/ru/subghz/raw-editor) — обрезка, склейка и декодирование RAW

**Заметки из практики**
- [ZKTeco CMP200](/ru/subghz/zkteco-cmp200) — Princeton в китайской обёртке

## Где лежат файлы

| Путь | Содержимое |
|---|---|
| `/ext/subghz/` | Сохранённые сигналы (`.sub`), RAW-записи |
| `/ext/subghz/assets/setting_user` | Свои частоты, список hopper, пользовательские пресеты |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Свои мануфактурные ключи KeeLoq |
| `/ext/subghz/assets/dangerous_settings` | Переключатель расширенного диапазона |
| `/ext/subghz_remote/` | Файлы раскладок приложения Sub-GHz Remote |
| `/ext/apps_data/subghz_seed_captures/` | Захваты Seed Capturer |
