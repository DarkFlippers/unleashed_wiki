---
title: Sub-GHz
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz]
---
# Sub-GHz

Flipper Zero має вбудований трансивер **CC1101** та антену для діапазонів нижче 1 ГГц. З їхньою допомогою можна
зчитувати, зберігати й відтворювати сигнали пультів гаражних і в'їзних воріт, шлагбаумів, ролет, дзвінків,
бездротових датчиків та інших пристроїв, які працюють у діапазонах **300–348 МГц, 387–464 МГц і 779–928 МГц**.
Більшість пультів, які вам трапляться, працюють на **315 МГц**, **433.92 МГц** або **868.35 МГц**.

Застосунок розташований у `Main Menu → Sub-GHz`. Його головне меню в Unleashed:

![Головне меню Sub-GHz: Read, Read RAW, Saved, Add Manually](/screens/subghz/menu.png)

| Пункт меню | Що робить | Сторінка |
|---|---|---|
| `Read` | Декодує пульти відомих протоколів, зберігає та надсилає їх | [Read](/ua/subghz/read) |
| `Read RAW` | Записує сирий сигнал будь-якого пульта й відтворює його | [Read RAW](/ua/subghz/read-raw) |
| `Saved` | Збережені файли `.sub`: Emulate, Rename, Delete, а з увімкненим Debug ще й Signal Settings | [Read](/ua/subghz/read) |
| `Add Manually` | Створює цілком новий пульт із випадковим серійником | [Add Manually](/ua/subghz/add-manually) |
| `Add Manually [Advanced]` | Те саме, але серійник / кнопку / лічильник / seed ви вводите самі | [Add Manually](/ua/subghz/add-manually) |
| `Frequency Analyzer` | Визначає, на якій частоті передає пульт | [Frequency Analyzer](/ua/subghz/frequency-analyzer) |
| `Radio Settings` | Внутрішній / зовнішній модуль, потужність TX, імена файлів, крок лічильника | [Налаштування](/ua/subghz/settings) |

::: tip Unleashed
Застосунок Sub-GHz, його бібліотека протоколів і Frequency Analyzer — з офіційної прошивки. Unleashed знімає
регіональні обмеження на передачу, додає додаткові частоти й ще протоколи, дозволяє зберігати та надсилати чимало протоколів із динамічним кодом, створює нові пульти з динамічним
кодом, які можна зареєструвати у власному приймачі (`Add Manually`), використовує клавіші-стрілки як додаткові
кнопки пульта, підтримує зовнішній модуль CC1101 і містить додаткові Sub-GHz застосунки (Remote Analyzer,
Seed Capturer, Nice O-Code, Security+ PIN, Sub-GHz RAW Edit, Sub-GHz Remote).
:::

::: warning
Користуйтеся цими можливостями лише з власним обладнанням або для законних досліджень.
:::

## З чого почати

1. Визначте частоту свого пульта — [Frequency Analyzer](/ua/subghz/frequency-analyzer).
2. Спробуйте декодувати його — [Read](/ua/subghz/read). Якщо сигнал декодується і протокол **статичний**, збережіть
   його — і на цьому все.
3. Якщо це пульт із **динамічним кодом**, не клонуйте його: прочитайте
   [Динамічні коди](/ua/subghz/rolling-codes) і створіть новий пульт через
   [Add Manually](/ua/subghz/add-manually) + [Програмування нового пульта](/ua/subghz/remote-prog).
4. Якщо нічого не декодується, запишіть сигнал через [Read RAW](/ua/subghz/read-raw).

## Усі сторінки

**Основи**
- [Частоти](/ua/subghz/frequencies) — діапазони, стандартні списки, регіональні обмеження та розширений діапазон
- [Frequency Analyzer](/ua/subghz/frequency-analyzer) — як дізнатися частоту пульта
- [Read](/ua/subghz/read) — декодування, збереження та надсилання сигналів
- [Read RAW](/ua/subghz/read-raw) — запис сирих сигналів

**Динамічні коди та нові пульти**
- [Add Manually](/ua/subghz/add-manually) — усі протоколи з меню
- [Динамічні коди](/ua/subghz/rolling-codes) — конфлікти лічильників, кастомні кнопки
- [KeeLoq](/ua/subghz/keeloq) — як працює KeeLoq, ключі виробників і seed
- [Програмування нового пульта](/ua/subghz/remote-prog) — покроково для кожної системи
- [Режими лічильника](/ua/subghz/counter-mode) — експериментальний `CounterMode` для клонів
- [Signal Settings](/ua/subghz/signal-settings) — режим лічильника, лічильник і кнопка збереженого сигналу
- [Підтримувані системи](/ua/subghz/supported-systems) — повна таблиця протоколів

**Налаштування та обладнання**
- [Налаштування](/ua/subghz/settings) — Radio Settings, конфігурація Read, власні частоти
- [Формати файлів](/ua/subghz/file-format) — `.sub`, пресети, користувацькі файли налаштувань
- [Зовнішній CC1101](/ua/subghz/external-cc1101) — зовнішні модулі та підсилювачі

**Застосунки**
- [Sub-GHz Remote](/ua/subghz/remote) — до 5 сигналів на хрестовині
- [Sub-GHz Bruteforce](/ua/subghz/bruteforce) — перебір статичних кодів
- [Remote Analyzer](/ua/subghz/remote-analyzer) — декодування одного пульта, додаткові протоколи
- [Nice O-Code](/ua/subghz/nice-o-code) — відновлення коду інсталятора
- [Security+ PIN](/ua/subghz/secplus-pin) — PIN-код клавіатури Security+ 2.0
- [Seed Capturer](/ua/subghz/seed-capturer) — збір хопів для відновлення seed
- [Sub-GHz RAW Edit](/ua/subghz/raw-editor) — обрізання, склеювання та декодування RAW-файлів

**Нотатки з практики**
- [ZKTeco CMP200](/ua/subghz/zkteco-cmp200) — замаскований пульт Princeton

## Де зберігаються файли

| Шлях | Вміст |
|---|---|
| `/ext/subghz/` | Збережені сигнали (`.sub`), RAW-записи |
| `/ext/subghz/assets/setting_user` | Власні частоти, список хопінгу, користувацькі пресети |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Власні ключі виробників KeeLoq |
| `/ext/subghz/assets/dangerous_settings` | Перемикач розширеного діапазону частот |
| `/ext/subghz_remote/` | Файли карт застосунку Sub-GHz Remote |
| `/ext/apps_data/subghz_seed_captures/` | Записи Seed Capturer |
