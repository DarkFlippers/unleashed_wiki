---
title: Веб-инструменты
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/apps]
sources: [unleashed-readme, unleashed-docs, flipper-docs]
---
# Веб-инструменты

Часть инструментов для Флиппера работает прямо в браузере, ничего ставить не нужно. Инструментам, которые общаются с
Флиппером по USB, нужен **Web Serial API**, поэтому используйте **Chrome, Edge или другой браузер на Chromium**.

::: warning Сначала закройте qFlipper
Браузерный инструмент не подключится, пока serial-порт Флиппера занят qFlipper (или второй вкладкой Flipper Lab).
Это самая частая причина того, что «Chrome не видит Флиппер».
:::

## Инструменты Unleashed

| Инструмент | Адрес | Что делает |
|---|---|---|
| Unleashed Web Installer | [web.unleashedflip.com](https://web.unleashedflip.com) | установка и обновление Unleashed (Release или Dev) по USB |
| Dev-сборки | [dev.unleashedflip.com](https://dev.unleashedflip.com) | автоматические сборки из ветки dev (нестабильные) |
| Sub-GHz & Coordinates Map | [map.unleashedflip.com](https://map.unleashedflip.com) | показ на карте файлов Sub-GHz вардрайвинга и любых других файлов с координатами |
| Wi-Fi Wardriving Map | [wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) | объединение и показ нескольких захватов в формате WiGLE (ESP32 Marauder и другие) |
| ESP32 Web Flasher | [espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) | прошивка популярных модулей ESP32 из браузера |

### Unleashed Web Installer

Рекомендуемый способ установки Unleashed.

1. Только при первой установке: сначала обновитесь до последней **официальной** прошивки. Проверьте, что
   **microSD-карта** вставлена.
2. Закройте qFlipper. Подключите Флиппер USB-кабелем с передачей данных.
3. Откройте [web.unleashedflip.com](https://web.unleashedflip.com) в браузере на Chromium.
4. Нажмите **Connect** и выберите свой Флиппер во всплывающем окне браузера.
5. Выберите ветку **Release** или **Dev**.
6. Нажмите **Install** и ждите. По окончании все ресурсы установлены, и Флиппер загружается в Unleashed.

Ещё вариант: в каждом [релизе на GitHub](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) есть ссылка
**Install via Web Updater**, которая открывает релиз в веб-апдейтере Flipper Lab: нажмите **Connect**, затем
**Install**. Полная инструкция: [Установка Unleashed](/ru/start/install).

### Sub-GHz & Coordinates Map

[map.unleashedflip.com](https://map.unleashedflip.com) показывает на карте ваши захваты Sub-GHz с координатами
(например, из Sub-GHz вардрайвинга с GPS-модулем) и любые другие файлы, в которых есть координаты.

### Wi-Fi Wardriving Map

[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) объединяет несколько захватов в **формате WiGLE** от
ESP32 Marauder и похожих инструментов и показывает точки доступа на одной карте. См.
[ESP32 и Wi-Fi модули](/ru/gpio/esp32).

### ESP32 Web Flasher

[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) прошивает популярные модули ESP32 прямо в
браузере. См. [ESP32](/ru/gpio/esp32) и [Devboard](/ru/gpio/devboard).

## Flipper Lab (официальный)

[lab.flipper.net](https://lab.flipper.net) — официальный набор веб-инструментов. Работает и с Unleashed:

- [Apps](https://lab.flipper.net/apps): официальный каталог приложений, установка / обновление / удаление по USB, см.
  [Приложения на SD-карте](/ru/apps/sd-card-apps).
- [CLI](https://lab.flipper.net/cli): терминал командной строки Флиппера, см. [CLI](/ru/dev/cli).
- [Pulse Plotter](https://lab.flipper.net/pulse-plotter): визуализация RAW-сигналов Sub-GHz, полезно для разбора
  незнакомого пульта.
- **Веб-апдейтер**, который открывают ссылки «Install via Web Updater».

## Другие ссылки

- Сайт Unleashed: [flipperunleashed.com](https://flipperunleashed.com)
- Прямые ссылки на `.tgz` для обновления: [unleashedflip.com](https://unleashedflip.com)
- Directory JSON для сборок через uFBT: [up.unleashedflip.com/directory.json](https://up.unleashedflip.com/directory.json)

::: danger Осторожно, подделки
[DarkFlippers/unleashed-firmware](https://github.com/DarkFlippers/unleashed-firmware) — единственная официальная
страница проекта. Платных, «премиум» или закрытых версий не существует; любой, кто такое предлагает, — мошенник.
:::

## Связанные страницы

- [Установка Unleashed](/ru/start/install)
- [qFlipper](/ru/mobile/qflipper)
- [Приложение-компаньон qUnleashed](/ru/mobile/qunleashed-app)
