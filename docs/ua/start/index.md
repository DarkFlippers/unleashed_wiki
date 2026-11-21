---
title: Початок роботи
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-readme, unleashed-docs, unleashed-src, flipper-docs]
---
# Початок роботи

Цей розділ проведе вас від щойно купленого Flipper Zero до повністю налаштованого пристрою з прошивкою
**Unleashed**. Тут зібрана база, на яку спираються всі інші розділи вікі: кнопки, робочий стіл, живлення,
картка microSD, налаштування та відновлення.

## Що таке Flipper Zero

Flipper Zero — кишеньковий мультитул для дослідження радіо та систем контролю доступу. На борту:

- **трансивер CC1101 (Sub-GHz)** — пульти воріт і шлагбаумів, датчики та інші пристрої, що працюють нижче 1 ГГц;
- модуль **NFC 13,56 МГц** і антена **RFID 125 кГц** — карти, брелоки, мітки;
- **інфрачервоний** приймач і передавач — телевізори, кондиціонери та інші пульти;
- контактна площадка **1-Wire (iButton)** — ключі Dallas, Cyfral, Metakom;
- **USB** і **Bluetooth LE** — режим клавіатури (Bad USB), токен U2F, пульт;
- виводи **GPIO** для зовнішніх модулів (зовнішній CC1101, NRF24, ESP32, SIM800 та інші);
- монохромний екран 128×64, п’ятипозиційний джойстик з кнопкою «назад» і акумулятор на 2100 мА·год.

На робочому столі живе цифровий улюбленець — дельфін, який підвищує рівень, поки ви користуєтеся пристроєм.

## Що таке Unleashed

[Unleashed](https://github.com/DarkFlippers/unleashed-firmware) — форк офіційної прошивки (OFW). Він залишається
**повністю сумісним з API та застосунками OFW** і додає можливості поверх них. Головне:

- **немає регіональних обмежень на передавання Sub-GHz**, є додаткові частоти й опціональний розширений діапазон;
- **значно більше протоколів Sub-GHz**, зокрема можливість зберігати й надсилати багато систем із динамічними
  (rolling code) кодами, кастомні кнопки та створення нових пультів через `Add manually`;
- підтримка **зовнішнього модуля CC1101**;
- додаткові парсери NFC, парсер EMV, більше ключів MIFARE Classic у системному словнику;
- фазери RFID та iButton, інструмент T5577 й інші вбудовані застосунки;
- дрібні зручності: власне ім’я Фліппера, годинник на робочому столі, заряд у відсотках, Night Shift, більше ігор
  у Dummy Mode, BadKB (Bad USB через Bluetooth) та багато іншого.

Повний список із посиланнями — на сторінці [Можливості Unleashed](/ua/start/unleashed-features).

::: warning Лише офіційні джерела
`DarkFlippers/unleashed-firmware` — єдине офіційне місце проєкту. Усі збірки безкоштовні та з відкритим вихідним
кодом. Платних, «преміум» чи закритих версій не існує. Якщо вам таке пропонують — це шахраї.
:::

## Релізні та dev-збірки

| Збірка | Що це | Де взяти |
|---|---|---|
| **Release** (стабільна) | Перевірені релізи, рекомендовані для щоденного використання | [Web Installer](https://web.unleashedflip.com), [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), Telegram [@unleashed_fw](https://t.me/unleashed_fw) |
| **Dev** (нестабільна) | Збирається автоматично з кожного нового коміту в гілці `dev` | [dev.unleashedflip.com](https://dev.unleashedflip.com), Telegram [@kotnehleb](https://t.me/kotnehleb), канал `unleashed-development` у Discord |

Нова dev-збірка заміняє попередню на сайті; старі dev-збірки залишаються лише файлами в Telegram-каналі. У dev-збірках
нові можливості з’являються першими, але **в них можуть бути баги**. Знайшли баг — повідомте про нього в
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

Кожен реліз виходить у трьох варіантах: `e` (базові + додаткові застосунки), без суфікса (базові застосунки) та
`c` (без застосунків спільноти). Подробиці — на сторінці
[Встановлення Unleashed](/ua/start/install#which-file-to-download).

## Спільнота

- Чати в Telegram: [англійський](https://t.me/flipperzero_unofficial), [російський](https://t.me/flipperzero_unofficial_ru), [український](https://t.me/flipperzero_unofficial_ua)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Сайт Unleashed: [flipperunleashed.com](https://flipperunleashed.com)

## Сторінки розділу

**Перші кроки**
- [Перший запуск](/ua/start/first-start) — увімкнення, картка microSD, перше оновлення
- [Встановлення Unleashed](/ua/start/install) — Web Installer, qFlipper, мобільні застосунки, офлайн-оновлення з картки
- [Оновлення](/ua/start/updating) — як тримати прошивку актуальною, реліз чи dev, що зберігається після оновлення
- [Можливості Unleashed](/ua/start/unleashed-features) — усе, що Unleashed додає до стокової прошивки

**Робота з пристроєм**
- [Керування](/ua/start/controls) — кнопки, режим для лівші, гарячі клавіші
- [Робочий стіл](/ua/start/desktop) — рядок стану, ярлики, Lock Menu, Quick Settings, Dummy Mode, Archive
- [Дельфін](/ua/start/dolphin) — настрій, рівні та досвід
- [Живлення та акумулятор](/ua/start/power) — заряджання, вимкнення, Auto PowerOff, Limit Charge
- [Картка microSD](/ua/start/sd-card) — вибір, форматування, структура папок
- [Налаштування](/ua/start/settings) — усі пункти меню Settings по порядку
- [Власне ім’я Фліппера](/ua/start/custom-name)

**Якщо щось пішло не так**
- [Комбінації кнопок](/ua/start/key-combos) — скидання та вхід у DFU
- [Відновлення](/ua/start/recovery) — відновлення прошивки, скидання до заводських налаштувань, скидання PIN-коду
- [Небезпечні налаштування](/ua/start/dangerous-settings) — розширений діапазон Sub-GHz (прочитайте, перш ніж чіпати)
- [FAQ](/ua/start/faq)

::: tip Закон
Unleashed призначений для експериментів і законних досліджень. Використовуйте його на власних пристроях або з
дозволу власника.
:::
