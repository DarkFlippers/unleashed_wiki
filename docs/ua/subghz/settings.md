---
title: Radio Settings (налаштування радіо)
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/radio_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://docs.flipper.net/zero/sub-ghz]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Radio Settings (налаштування радіо)

У `Main Menu → Sub-GHz → Radio Settings` зібрані налаштування, що діють на весь застосунок Sub-GHz: яке радіо
використовується, потужність передавання, формування імен файлів і поведінка динамічного лічильника. Налаштування
приймання (частота, модуляція, хопінг, фільтри) лежать у `Read → Config` — див. [Read](/ua/subghz/read#config).

::: tip Unleashed
У стоковій прошивці це меню лише перемикає внутрішній і зовнішній модуль. Unleashed додає **TX Power**,
**Protocol Names**, **Counter Incr.**, а в режимі Debug — ще **Ext Amp & LEDs** і **Debug Pin**.
:::

## Пункти меню

![Radio Settings: Module, TX Power, Protocol Names і Counter Incr.](/screens/subghz/radio_settings.png)

| Пункт | Значення | Що робить |
|---|---|---|
| `Module` | `Internal`, `External` | Радіо для приймання й передавання. `External` пропонується лише тоді, коли на GPIO виявлено зовнішній CC1101; якщо він не відповідає, Flipper повертається до `Internal` |
| `TX Power` | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | Потужність передавання. `Preset` = те, що задає пресет модуляції (стандартне значення). Нижчі значення зручні для тестів на малій відстані |
| `Protocol Names` | `OFF` / `ON` | Коли `ON`, автоматично створені імена файлів містять назву протоколу + позначку часу, а не лише час чи випадкове ім'я |
| `Counter Incr.` | `+1`, `+2`, `+3` (у звичайному режимі) | На скільки збільшується динамічний лічильник за одне передавання для динамічних протоколів. Стандартно `+1` |

Додаткові пункти в **режимі Debug** (`Settings → System → Debug → ON`):

| Пункт | Значення | Що робить |
|---|---|---|
| `Counter Incr.` | `+1` `+2` `+3` `+4` `+5` `+10` `+50` `OVFL` `OFEX` `No` `-1` `-2` `-3` `-4` `-5` `-10` `-50` | Повний перелік кроків лічильника для експериментів: великі стрибки, `OVFL` (крок 65535), `OFEX` (спеціальний режим), `No` (лічильник не змінюється) та від'ємні кроки |
| `Ext Amp & LEDs` | `ON` / `OFF` | Керує піном підсилювача / світлодіода зовнішніх модулів (GPIO PC3, як на модулях E07). Стандартно `ON`. Вимкніть, якщо ваш модуль використовує цей пін для чогось іншого |
| `Debug Pin` | `OFF` / `17(1W)` | Дублює сигнал даних радіо на пін GPIO 17 (1-Wire) — для розробки протоколів із логічним аналізатором |

`TX Power`, `Protocol Names` та `Ext Amp & LEDs` зберігаються негайно (у `/ext/subghz/assets/last_subghz.settings`).
`Counter Incr.` не зберігається: він діє до перезавантаження Flipper, після чого повертається до `+1`.

::: warning Крок лічильника
Великі або від'ємні кроки лічильника призначені для експериментів **на власних приймачах**. Якщо прогнати лічильник
далеко вперед, збережене в приймачі значення назавжди обганяє ваш оригінальний пульт; а якщо відкотити назад —
приймач просто ігноруватиме вас. Щоб співіснувати з оригінальним пультом, використовуйте
[Режими лічильника](/ua/subghz/counter-mode) або створіть новий пульт через
[Add Manually](/ua/subghz/add-manually). Теорія: [Динамічні коди](/ua/subghz/rolling-codes).
:::

## Інші налаштування, що лежать на SD-картці

| Файл | Призначення | Докладніше |
|---|---|---|
| `/ext/subghz/assets/setting_user` | Додаткові частоти, список хопінгу, стандартна частота, користувацькі пресети модуляції | [Частоти](/ua/subghz/frequencies#adding-frequencies), [Формати файлів](/ua/subghz/file-format#setting-user) |
| `/ext/subghz/assets/dangerous_settings` | Розширений (позаспецифікаційний) діапазон частот | [Частоти](/ua/subghz/frequencies#extended-range) |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Власні ключі виробників KeeLoq | [Формати файлів](/ua/subghz/file-format#keeloq-mfcodes-user), [KeeLoq](/ua/subghz/keeloq) |
| `/ext/subghz/assets/last_subghz.settings` | Остання використана частота, модуляція, фільтри, тригер аналізатора — записує сам застосунок | не редагуйте вручну |

Файли із закінченням `.example` — це шаблони: перейменуйте їх на `…_user`, щоб активувати. Файли `_user` не
перезаписуються під час оновлення прошивки.

## Якщо не працює

- **У `Module` є лише `Internal`** — зовнішній CC1101 не виявлено. Перевірте підключення та живлення, тоді зайдіть
  до меню знову. Див. [Зовнішній CC1101](/ua/subghz/external-cc1101).
- **Слабкий сигнал під час передавання** — перевірте, чи не виставлено в `TX Power` від'ємне значення.
- **Імена файлів — лише дати** — увімкніть `Protocol Names`.
- **Немає пунктів `Ext Amp & LEDs` / `Debug Pin`** — вони з'являються лише в режимі Debug.

## Пов'язані сторінки

- [Read → Config](/ua/subghz/read#config) · [Частоти](/ua/subghz/frequencies) · [Зовнішній CC1101](/ua/subghz/external-cc1101)
- [Режими лічильника](/ua/subghz/counter-mode) · [Формати файлів](/ua/subghz/file-format) · [Небезпечні налаштування](/ua/start/dangerous-settings)
