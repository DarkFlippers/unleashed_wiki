---
title: Начало работы
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-readme, unleashed-docs, unleashed-src, flipper-docs]
---
# Начало работы

Этот раздел проведёт от только что купленного Flipper Zero до полностью настроенного устройства на прошивке
**Unleashed**.

## Что такое Flipper Zero

Flipper Zero — карманный мультитул для изучения радио и систем контроля доступа. На борту:

- **трансивер CC1101 (Sub-GHz)** — пульты ворот и шлагбаумов, датчики и прочие устройства ниже 1 ГГц;
- **NFC 13,56 МГц** и антенна **RFID 125 кГц** — карты, брелоки, метки;
- **ИК** приёмник и передатчик — телевизоры, кондиционеры и другие пульты;
- контактная площадка **1-Wire (iButton)** — ключи Dallas, Cyfral, Metakom;
- **USB** и **Bluetooth LE** — режим клавиатуры (Bad USB), U2F-токен, пульт;
- выводы **GPIO** для внешних модулей (внешний CC1101, NRF24, ESP32, SIM800 и др.);
- монохромный экран 128×64, пятипозиционный джойстик с кнопкой «Назад» и аккумулятор 2100 мА·ч.

На рабочем столе живёт цифровой питомец — дельфин, который растёт, когда вы пользуетесь устройством.

## Что такое Unleashed

[Unleashed](https://github.com/DarkFlippers/unleashed-firmware) — форк официальной прошивки (OFW). Он **полностью
совместим с API и приложениями OFW** и добавляет новые возможности. Главное:

- **нет региональных ограничений на передачу Sub-GHz**, есть дополнительные частоты и опциональный расширенный диапазон;
- **гораздо больше протоколов Sub-GHz**: сохранение и отправка многих динамических (rolling code) систем, кастомные
  кнопки, создание новых пультов через `Add manually`;
- поддержка **внешнего модуля CC1101**;
- дополнительные NFC-парсеры, парсер EMV, расширенный словарь ключей MIFARE Classic;
- фаззеры RFID и iButton, приложение T5577 и другие встроенные приложения;
- удобства: своё имя Флиппера, часы на рабочем столе, заряд в процентах, больше игр в Dummy Mode, BadKB (Bad USB по
  Bluetooth) и многое другое.

Полный список со ссылками — на странице [Возможности Unleashed](/ru/start/unleashed-features).

::: warning Только официальные источники
Единственная официальная страница проекта — `DarkFlippers/unleashed-firmware`. Все сборки бесплатные и с открытым
исходным кодом. Платных, «премиум» или закрытых версий не существует. Если вам такое предлагают — это мошенники.
:::

## Релизы и dev-сборки

| Сборка | Что это | Где взять |
|---|---|---|
| **Release** (стабильная) | Проверенные релизы, рекомендуются для повседневного использования | [Web Installer](https://web.unleashedflip.com), [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), Telegram [@unleashed_fw](https://t.me/unleashed_fw) |
| **Dev** (нестабильная) | Собирается автоматически из каждого нового коммита в ветке `dev` | [dev.unleashedflip.com](https://dev.unleashedflip.com), Telegram [@kotnehleb](https://t.me/kotnehleb), канал `unleashed-development` в Discord |

Новая dev-сборка заменяет предыдущую на сайте. Старые остаются только файлами в Telegram-канале. В dev-сборках новые
функции появляются первыми, но **в них могут быть баги**. Нашли баг — сообщите в
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

Каждый релиз выходит в трёх вариантах: `e` (базовые + дополнительные приложения), без суффикса (базовые приложения) и
`c` (без приложений сообщества). Подробнее — в разделе
[Установка Unleashed](/ru/start/install#which-file-to-download).

## Сообщество

- Чаты в Telegram: [английский](https://t.me/flipperzero_unofficial), [русский](https://t.me/flipperzero_unofficial_ru), [украинский](https://t.me/flipperzero_unofficial_ua)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Сайт Unleashed: [flipperunleashed.com](https://flipperunleashed.com)

## Страницы раздела

**Первые шаги**
- [Первый запуск](/ru/start/first-start) — включение, microSD-карта, первое обновление
- [Установка Unleashed](/ru/start/install) — Web Installer, qFlipper, мобильные приложения, офлайн-обновление с карты
- [Обновление](/ru/start/updating) — как обновляться, релиз или dev, что сохраняется
- [Возможности Unleashed](/ru/start/unleashed-features) — всё, что Unleashed добавляет к стоковой прошивке

**Работа с устройством**
- [Управление](/ru/start/controls) — кнопки, режим для левши, горячие клавиши
- [Рабочий стол](/ru/start/desktop) — строка состояния, ярлыки, Lock Menu, Quick Settings, Dummy Mode, Archive
- [Дельфин](/ru/start/dolphin) — настроение, уровни, опыт
- [Питание и аккумулятор](/ru/start/power) — зарядка, выключение, Auto PowerOff, Limit Charge
- [microSD-карта](/ru/start/sd-card) — выбор, форматирование, структура папок
- [Настройки](/ru/start/settings) — все пункты меню Settings по порядку
- [Своё имя Флиппера](/ru/start/custom-name)

**Если что-то пошло не так**
- [Комбинации кнопок](/ru/start/key-combos) — сброс и вход в DFU
- [Восстановление](/ru/start/recovery) — восстановление прошивки, сброс к заводским настройкам, сброс PIN
- [Опасные настройки](/ru/start/dangerous-settings) — расширенный диапазон Sub-GHz (прочитайте до того, как трогать)
- [FAQ](/ru/start/faq)

::: tip Закон
Unleashed предназначен для экспериментов и легальных исследований. Используйте его со своими устройствами или с
разрешения владельца.
:::
