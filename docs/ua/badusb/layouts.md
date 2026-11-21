---
title: Розкладки клавіатури
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/assets/layouts, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Розкладки клавіатури Bad USB

USB-клавіатура надсилає не символи, а **позиції клавіш**. Комп'ютер перетворює їх на символи відповідно до *своєї*
розкладки. Тому щоб набрати `z` на німецькому ПК (QWERTZ), Flipper має натиснути клавішу, яка на американській
клавіатурі є `y`. **Файл розкладки** (`.kl`) повідомляє Bad USB, яка клавіша (і який модифікатор) дає кожен символ
у цільовій розкладці.

::: tip Unleashed
Розкладки клавіатури для Bad USB походять від [rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl)
і є частиною Unleashed. Команда `DUCKY_LANG` для окремого скрипта — новинка саме Unleashed (PR #1224).
:::

## Доступні розкладки

Файли у `/ext/badusb/assets/layouts/` (у поточній збірці їх 31):

| Файл | Розкладка |
|---|---|
| `en-US.kl` | англійська (США), **типова** і вбудований резервний варіант |
| `en-UK.kl` | англійська (Велика Британія) |
| `de-DE.kl`, `de-DE-mac.kl` | німецька (Німеччина), PC і Mac |
| `de-CH.kl` | німецька (Швейцарія) |
| `fr-FR.kl`, `fr-FR-mac.kl` | французька (Франція), PC і Mac |
| `fr-BE.kl`, `fr-CA.kl`, `fr-CH.kl` | французька (Бельгія, Канада, Швейцарія) |
| `es-ES.kl`, `es-LA.kl` | іспанська (Іспанія, Латинська Америка) |
| `it-IT.kl`, `it-IT-mac.kl` | італійська, PC і Mac |
| `pt-PT.kl`, `pt-BR.kl` | португальська (Португалія, Бразилія) |
| `nl-NL.kl` | нідерландська |
| `da-DA.kl` | данська |
| `nb-NO.kl` | норвезька |
| `sv-SE.kl` | шведська |
| `fi-FI.kl` | фінська |
| `cz_CS.kl` | чеська |
| `sk-SK.kl` | словацька |
| `hu-HU.kl` | угорська |
| `hr-HR.kl` | хорватська |
| `si-SI.kl` | словенська |
| `ba-BA.kl` | боснійська |
| `tr-TR.kl` | турецька |
| `ja-JP.kl` | японська |
| `dvorak.kl` | Dvorak (US) |
| `colemak.kl` | Colemak |

Української чи іншої кириличної розкладки немає: формат здатен описати лише символи ASCII (див. нижче).

## Вибір розкладки

**Глобально** (для всіх скриптів): на екрані скрипта натисніть <kbd>←</kbd> **Config → Keyboard Layout (global)**
і виберіть файл `.kl`. Вибір зберігається у `/ext/badusb/.badusb.settings` і показується на екрані скрипта в
дужках, наприклад `(de-DE)`. Якщо збережений файл відсутній або зіпсований, використовується `en-US`.

![Меню Bad USB Config, Keyboard Layout (global) — перший пункт](/screens/badusb/config.png)

**Для окремого скрипта**: поставте `DUCKY_LANG <name>` на початку скрипта:

```text
DUCKY_LANG fr-FR
STRINGLN bonjour
```

- `<name>` — ім'я файлу без `.kl`. Псевдоніми: `en` = `en-US`, `de` = `de-DE`, `fr` = `fr-FR`.
- Команда діє з цього рядка й далі, а на початку кожного запуску скидається до глобальної розкладки.
- Невідоме або некоректне ім'я відкочує розкладку до вбудованої `en-US`, не зупиняючи скрипт.

## Чого розкладка НЕ змінює

- Через розкладку проходять лише текст `STRING` / `STRINGLN` та односимвольні клавіші (`CTRL c`, `HOLD a`…).
  Названі клавіші (`ENTER`, `F5`, стрілки…) однакові всюди.
- `ALTCHAR` / `ALTSTRING` розкладкою не користуються взагалі; вони вводять символи за кодом через `ALT`+Numpad —
  саме тому вони працюють з будь-якою розкладкою у Windows.
- Розкладка має відповідати **поточній мові введення на хості**. На ПК із кількома мовами (наприклад, англійська
  та українська) перемкніть хост на мову розкладки перед запуском, інакше `STRING` набиратиме кириличні літери.

## Формат файлу (`.kl`)

Файл `.kl` — це двійкова таблиця розміром рівно **256 байтів**: 128 записів по 2 байти (little-endian `uint16`),
по одному на кожний ASCII-код 0-127.

- **Молодший байт**: HID usage code клавіші, яку потрібно натиснути (наприклад, `0x1F` = клавіша `2`).
- **Старший байт**: біти модифікаторів, які треба тримати разом із нею:

| Біт (старший байт) | Модифікатор |
|---|---|
| `0x01` | Left Ctrl |
| `0x02` | Left Shift |
| `0x04` | Left Alt |
| `0x08` | Left GUI |
| `0x10` | Right Ctrl |
| `0x20` | Right Shift |
| `0x40` | Right Alt (AltGr) |
| `0x80` | Right GUI |

Приклад із `de-DE.kl`: запис для `"` (ASCII 34) — це `1F 02`, тобто Shift + `2`, бо саме там розташовані подвійні
лапки на німецькій клавіатурі.

Оскільку таблиця має лише 128 записів, **набирати можна тільки ASCII**; `STRING` із будь-яким байтом ≥ 128
(діакритика в UTF-8, кирилиця, емодзі) зупиняє скрипт із повідомленням *«Native .kl supports ASCII, not UTF-8»*.
Імена файлів можуть містити літери, цифри, `-` і `_` (не більше 32 символів до `.kl`).

Щоб зробити власну розкладку, скористайтеся інструкціями у
[dummy-decoy/flipperzero_badusb_kl](https://github.com/dummy-decoy/flipperzero_badusb_kl) і скопіюйте отриманий
файл до `/ext/badusb/assets/layouts/`.

## Пов'язані сторінки

- [Формат скриптів](/ua/badusb/script-format#keyboard-layout-per-script-ducky-lang)
- [Використання Bad USB](/ua/badusb/usage)
- [Приклади](/ua/badusb/examples)
