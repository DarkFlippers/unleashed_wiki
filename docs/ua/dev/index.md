---
title: Розробка
original: [https://docs.flipper.net/zero/development, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Розробка

Цей розділ — для тих, хто хоче вийти за межі звичайного користування Flipper: зібрати прошивку Unleashed з
початкового коду, написати власні застосунки на C або JavaScript, налагодити їх на справжньому пристрої,
поспілкуватися з пристроєм через командний рядок або розібратися, як насправді працюють оновлення та апаратна
частина.

::: tip Unleashed
Unleashed — це форк офіційної прошивки, який залишається **повністю сумісним з офіційним API та застосунками**.
Майже все з офіційної документації для розробників застосовне без змін. Основне, що варто пам’ятати:

- клонуйте `https://github.com/DarkFlippers/unleashed-firmware`, а не офіційний репозиторій;
- коли збираєте застосунки за допомогою **uFBT**, вказуйте йому SDK Unleashed
  (`--index-url=https://up.unleashedflip.com/directory.json`), інакше застосунок буде зібраний проти офіційного
  SDK і може відмовитися запускатися ([докладніше](/ua/dev/build#build-apps-against-the-unleashed-sdk-with-ufbt));
- прошивка повідомляє про своє походження як `Unleashed`, поточна версія API в гілці `dev` — **88.27**.
:::

## Збірка прошивки

| Сторінка | Що дає |
|---|---|
| [Збірка прошивки](/ua/dev/build) | Клонування, збірка та прошивка Unleashed на Linux, macOS і Windows |
| [Flipper Build Tool (fbt)](/ua/dev/fbt) | Усі цілі, параметри та змінні середовища `fbt` |
| [Апаратні таргети](/ua/dev/hardware-targets) | Як `targets/` і `target.json` описують апаратні варіанти (f7, f18) |
| [Збірка застосунків на Android](/ua/dev/android-build) | Компіляція `.fap` просто на телефоні: Termux + uFBT, без ПК |

## Написання застосунків

| Сторінка | Що дає |
|---|---|
| [Перший застосунок на C](/ua/dev/first-app-c) | uFBT, шаблон застосунку, «Hello world» з діалогом, збірка та запуск |
| [Маніфести застосунків (.fam)](/ua/dev/app-manifests) | Усі поля `application.fam`, параметри зовнішніх застосунків, приватні бібліотеки |
| [Furi API](/ua/dev/furi-api) | Архітектура апаратної та програмної частини, ядро Furi, `furi_assert` / `furi_check` |
| [GUI у застосунках](/ua/dev/gui) | Діалоги, ViewPort, Views і Scenes, модулі представлень |
| [Налагодження застосунків](/ua/dev/debugging) | SWD-зонди, налагодження у VS Code, сигнали налагодження Furi HAL |
| [FuriHalBus API](/ua/dev/furi-hal-bus) | Як правильно вмикати та вимикати периферію MCU, карта каналів DMA |
| [JavaScript на Flipper](/ua/dev/js-about) | Пишіть скрипти на JavaScript замість C (окрема група сторінок) |
| JS-модулі лише в Unleashed | [subghz](/ua/dev/js-subghz), [infrared](/ua/dev/js-infrared), [blebeacon](/ua/dev/js-blebeacon), [usbdisk](/ua/dev/js-usbdisk), [i2c](/ua/dev/js-i2c), [spi](/ua/dev/js-spi), [vgm](/ua/dev/js-vgm) — їх немає ні в стоковій прошивці, ні в офіційній документації |

## Робота з пристроєм

| Сторінка | Що дає |
|---|---|
| [Командний рядок (CLI)](/ua/dev/cli) | Підключення через USB-serial; усі команди CLI з аргументами |
| [OTA-оновлення](/ua/dev/ota) | Як працює оновлювач, поля маніфесту, коди помилок `[XX-YY]`, збірка пакетів |
| [Формат tar + heatshrink](/ua/dev/tar-heatshrink) | Контейнер `.tar.hs`, у якому лежать ресурси пакетів оновлення |
| [Апаратна частина](/ua/dev/hardware) | Технічні характеристики, схеми, 3D-моделі, креслення модулів і девборд |

## Тестування

| Сторінка | Що дає |
|---|---|
| [Юніт-тести](/ua/dev/unit-tests) | Збірка та запуск застосунку `unit_tests` на пристрої, додавання власних тестів |
| [Інтеграційне тестування](/ua/dev/testing) | Ручний тест-план, який проходять перед злиттям PR і релізами |

## Інші корисні ресурси

- Офіційна документація для розробників (Doxygen): [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen/) — місце, де шукати API прошивки, яких немає в цій вікі; там є розділи про системне програмування, розробку застосунків, JavaScript, модулі розширення та формати файлів
- Налаштування робочого простору CLion — [посібник від Savely Krasovsky](https://krasovs.ky/2022/11/01/flipper-zero-clion.html)
- Посібники «Hello world!» для плагінів: [англійською (DroomOne)](https://github.com/DroomOne/Flipper-Plugin-Tutorial),
  [російською (Павел Яковлев)](https://yakovlev.me/hello-flipper-zero)
- [Як написати власний застосунок](https://flipper.atmanos.com/docs/overview/intro)

### Структура репозиторію прошивки

| Папка | Вміст |
|---|---|
| `applications` | Застосунки та служби, які використовує прошивка |
| `assets` | Ресурси, якими користуються застосунки та служби |
| `furi` | Furi Core: примітиви та допоміжні засоби рівня ОС |
| `debug` | Інструменти налагодження: плагіни GDB, файл SVD тощо |
| `documentation` | Джерела документації та конфігурації генераторів |
| `firmware` | Початковий код прошивки |
| `lib` | Власні та сторонні бібліотеки, драйвери |
| `site_scons` | Допоміжні засоби збірки |
| `scripts` | Додаткові скрипти та бібліотеки Python |
| `targets` | Описи апаратних таргетів (`f7`, `f18`) |

У багатьох із цих папок є власний `ReadMe.md` — його варто прочитати.
