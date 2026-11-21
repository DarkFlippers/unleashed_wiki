---
title: Вебінструменти
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/apps]
sources: [unleashed-readme, unleashed-docs, flipper-docs]
---
# Вебінструменти

Кілька інструментів для Flipper працюють просто у браузері — встановлювати нічого не потрібно. Інструментам, які
спілкуються з Flipper через USB, потрібен **Web Serial API**, тому користуйтеся **Chrome, Edge або іншим браузером
на Chromium**.

::: warning Спочатку закрийте qFlipper
Вебінструмент не може підключитися, поки послідовний порт Flipper тримає qFlipper (або друга вкладка Flipper Lab).
Це найчастіша причина того, що «Chrome не бачить Flipper».
:::

## Інструменти Unleashed

| Інструмент | Адреса | Що робить |
|---|---|---|
| Вебінсталятор Unleashed | [web.unleashedflip.com](https://web.unleashedflip.com) | встановлює або оновлює Unleashed (Release чи Dev) через USB |
| Dev-збірки | [dev.unleashedflip.com](https://dev.unleashedflip.com) | автоматичні збірки з гілки dev (нестабільні) |
| Карта Sub-GHz і координат | [map.unleashedflip.com](https://map.unleashedflip.com) | показує на карті файли Sub-GHz-вардрайвінгу та будь-які інші файли з координатами |
| Карта Wi-Fi-вардрайвінгу | [wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) | об'єднує й відображає кілька записів у форматі WiGLE (ESP32 Marauder та інші) |
| Вебпрошивальник ESP32 | [espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) | прошиває популярні модулі ESP32 із браузера |

### Вебінсталятор Unleashed {#unleashed-web-installer}

Рекомендований спосіб встановлення Unleashed.

1. Лише для першого встановлення: спочатку оновіться до найновішої **офіційної** прошивки. Переконайтеся, що
   **картка microSD** вставлена.
2. Закрийте qFlipper. Підключіть Flipper USB-кабелем із підтримкою передавання даних.
3. Відкрийте [web.unleashedflip.com](https://web.unleashedflip.com) у браузері на Chromium.
4. Натисніть **Connect** і виберіть свій Flipper у вікні браузера.
5. Виберіть гілку **Release** або **Dev**.
6. Натисніть **Install** і зачекайте. Коли процес завершиться, усі ресурси буде встановлено, і Flipper
   завантажиться в Unleashed.

Крім того, у кожного [релізу на GitHub](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) є
посилання **Install via Web Updater**, яке відкриває реліз у вебоновлювачі Flipper Lab: натисніть **Connect**, а
потім **Install**. Повна інструкція: [Встановлення Unleashed](/ua/start/install).

### Карта Sub-GHz і координат

[map.unleashedflip.com](https://map.unleashedflip.com) розміщує на карті ваші записи Sub-GHz із координатами
(наприклад, зібрані під час Sub-GHz-вардрайвінгу з GPS-модулем) та будь-які інші файли, що містять координати.

### Карта Wi-Fi-вардрайвінгу

[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) об'єднує кілька записів **у форматі WiGLE** з
ESP32 Marauder і подібних інструментів і показує точки доступу на одній карті. Див.
[ESP32 і модулі Wi-Fi](/ua/gpio/esp32).

### Вебпрошивальник ESP32

[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) — простий прошивальник для популярних модулів
ESP32, який працює повністю у браузері, без встановлення будь-яких інструментів прошивання. Див.
[ESP32](/ua/gpio/esp32) і [Dev board](/ua/gpio/devboard).

## Flipper Lab (офіційний)

[lab.flipper.net](https://lab.flipper.net) — офіційний вебнабір інструментів. Він працює з Unleashed:

- [Apps](https://lab.flipper.net/apps): офіційний каталог застосунків, встановлення / оновлення / видалення
  застосунків через USB, див. [Застосунки на SD-карті](/ua/apps/sd-card-apps).
- [CLI](https://lab.flipper.net/cli): термінал для командного рядка Flipper, див. [CLI](/ua/dev/cli).
- [Pulse Plotter](https://lab.flipper.net/pulse-plotter): візуалізація RAW-сигналів Sub-GHz, зручна для аналізу
  невідомого пульта.
- **Вебоновлювач**, який відкривають посилання «Install via Web Updater».

## Інші посилання

- Домашня сторінка Unleashed: [flipperunleashed.com](https://flipperunleashed.com)
- Прямі посилання на `.tgz`-оновлення: [unleashedflip.com](https://unleashedflip.com)
- Directory JSON для збірок uFBT: [up.unleashedflip.com/directory.json](https://up.unleashedflip.com/directory.json)

::: danger Остерігайтеся підробок
[DarkFlippers/unleashed-firmware](https://github.com/DarkFlippers/unleashed-firmware) — єдина офіційна сторінка
проєкту. Платних, преміальних чи закритих версій не існує; хто таке пропонує — шахрай.
:::

## Пов'язані сторінки

- [Встановлення Unleashed](/ua/start/install)
- [qFlipper](/ua/mobile/qflipper)
- [Супутній застосунок qUnleashed](/ua/mobile/qunleashed-app)
