---
title: Разработка
original: [https://docs.flipper.net/zero/development, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Разработка

Этот раздел — для тех, кто хочет не только пользоваться Флиппером: собрать Unleashed Firmware из исходников, написать
своё приложение на C или JavaScript, отлаживать его на реальном железе, работать с устройством через командную строку
или разобраться, как устроены обновления и сама железка.

::: tip Unleashed
Unleashed — форк официальной прошивки, который остаётся **полностью совместимым с официальным API и приложениями**.
Почти всё из официальной документации для разработчиков применимо как есть. Главное, что нужно помнить:

- клонируйте `https://github.com/DarkFlippers/unleashed-firmware` вместо официального репозитория;
- при сборке приложений через **uFBT** укажите ему Unleashed SDK
  (`--index-url=https://up.unleashedflip.com/directory.json`), иначе приложение соберётся под официальный SDK и может
  не запуститься ([подробнее](/ru/dev/build#build-apps-against-the-unleashed-sdk-with-ufbt));
- прошивка сообщает о себе как `Unleashed`, текущая версия API в ветке `dev` — **88.27**.
:::

## Сборка прошивки

| Страница | Что внутри |
|---|---|
| [Сборка прошивки](/ru/dev/build) | Клонирование, сборка и прошивка Unleashed на Linux, macOS и Windows |
| [Flipper Build Tool (fbt)](/ru/dev/fbt) | Все цели, опции и переменные окружения `fbt` |
| [Аппаратные таргеты](/ru/dev/hardware-targets) | Как `targets/` и `target.json` описывают варианты железа (f7, f18) |
| [Сборка приложений на Android](/ru/dev/android-build) | Компиляция `.fap` на телефоне через Termux + uFBT, без ПК |

## Написание приложений

| Страница | Что внутри |
|---|---|
| [Первое приложение на C](/ru/dev/first-app-c) | uFBT, шаблон приложения, «Hello world» с диалогом, сборка и запуск |
| [Манифесты приложений (.fam)](/ru/dev/app-manifests) | Все поля `application.fam`, опции внешних приложений, приватные библиотеки |
| [Furi API](/ru/dev/furi-api) | Архитектура железа и софта, ядро Furi, `furi_assert` / `furi_check` |
| [GUI в приложениях](/ru/dev/gui) | Dialogs, ViewPort, Views и Scenes, view-модули |
| [Отладка приложений](/ru/dev/debugging) | SWD-отладчики, отладка в VS Code, отладочные сигналы Furi HAL |
| [FuriHalBus API](/ru/dev/furi-hal-bus) | Правильное включение/выключение периферии MCU, карта каналов DMA |
| [JavaScript на Флиппере](/ru/dev/js-about) | Скрипты на JavaScript вместо C (отдельная группа страниц) |
| JS-модули только для Unleashed | [subghz](/ru/dev/js-subghz), [infrared](/ru/dev/js-infrared), [blebeacon](/ru/dev/js-blebeacon), [usbdisk](/ru/dev/js-usbdisk), [i2c](/ru/dev/js-i2c), [spi](/ru/dev/js-spi), [vgm](/ru/dev/js-vgm) — их нет ни в стоковой прошивке, ни в официальной документации |

## Работа с устройством

| Страница | Что внутри |
|---|---|
| [Командная строка (CLI)](/ru/dev/cli) | Подключение по USB-serial; все команды CLI с аргументами |
| [OTA-обновления](/ru/dev/ota) | Как работает апдейтер, поля манифеста, коды ошибок `[XX-YY]`, сборка пакетов |
| [Формат tar + heatshrink](/ru/dev/tar-heatshrink) | Контейнер `.ths`, в котором лежат ресурсы в пакетах обновления |
| [Железо](/ru/dev/hardware) | Характеристики, схемы, 3D-модели, чертежи модулей и девбордов |

## Тестирование

| Страница | Что внутри |
|---|---|
| [Юнит-тесты](/ru/dev/unit-tests) | Сборка и запуск приложения `unit_tests` на устройстве, добавление своих тестов |
| [Интеграционное тестирование](/ru/dev/testing) | Ручной тест-план, по которому проверяют PR и релизы |

## Другие полезные ресурсы

- Официальная документация для разработчиков (Doxygen): [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen/) — там ищут API прошивки, которых нет в этой вики: системное программирование, разработка приложений, JavaScript, модули расширения, форматы файлов
- Настройка CLion — [гайд от Savely Krasovsky](https://krasovs.ky/2022/11/01/flipper-zero-clion.html)
- Туториалы «Hello world!»: [на английском (DroomOne)](https://github.com/DroomOne/Flipper-Plugin-Tutorial),
  [на русском (Павел Яковлев)](https://yakovlev.me/hello-flipper-zero)
- [Как написать своё приложение](https://flipper.atmanos.com/docs/overview/intro)

### Структура репозитория прошивки

| Папка | Содержимое |
|---|---|
| `applications` | Приложения и сервисы прошивки |
| `assets` | Ресурсы, используемые приложениями и сервисами |
| `furi` | Furi Core: примитивы и хелперы уровня ОС |
| `debug` | Инструменты отладки: плагины GDB, SVD-файл и т. п. |
| `documentation` | Исходники документации и конфиги генератора |
| `firmware` | Исходный код прошивки |
| `lib` | Собственные и сторонние библиотеки, драйверы |
| `site_scons` | Хелперы сборки |
| `scripts` | Вспомогательные скрипты и Python-библиотеки |
| `targets` | Описания аппаратных таргетов (`f7`, `f18`) |

Во многих папках есть свой `ReadMe.md` — их стоит почитать.
