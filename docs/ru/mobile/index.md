---
title: Мобильные и десктопные приложения
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/mobile-app]
sources: [unleashed-readme, flipper-docs]
---
# Мобильные и десктопные приложения

Флиппер прекрасно работает и сам по себе, но с компьютером или телефоном многое делается проще: установка и
обновление прошивки, копирование файлов, установка приложений, бэкап ключей и пультов, удалённое управление.

| Инструмент | Где работает | Для чего |
|---|---|---|
| [qFlipper](/ru/mobile/qflipper) | Windows, macOS, Linux | установка Unleashed из `.tgz`, файловый менеджер, бэкап / восстановление, recovery |
| [Мобильное приложение Flipper](/ru/mobile/mobile-app) | iOS, Android | обновление по Bluetooth (в том числе своим `.tgz`), архив ключей, каталог приложений, удалённое управление |
| [qUnleashed](/ru/mobile/qunleashed-app) | Android, iOS, Windows, macOS, Linux | собственное приложение Unleashed: прошивка по BLE и USB, архив, каталог приложений, удалённый экран, CLI, восстановление Seed |
| [Веб-инструменты](/ru/mobile/web-tools) | браузер | Web Installer, карта Sub-GHz и координат, карта Wi-Fi вардрайвинга, прошивальщик ESP32, Flipper Lab |

::: tip Unleashed
Unleashed полностью совместим с официальным qFlipper и официальным мобильным приложением Flipper. Самый быстрый
способ установить или обновить Unleashed — [Web Installer](/ru/mobile/web-tools#unleashed-web-installer) в браузере
на Chromium.
:::

::: warning Только одно подключение
USB-порт (serial) Флиппера может занять только одна программа. Закройте qFlipper перед тем, как работать с Flipper Lab,
Web Installer, CLI-терминалом или U2F, и держите открытой только одну вкладку Flipper Lab.
:::

## Страницы раздела

- [qFlipper](/ru/mobile/qflipper)
- [Мобильное приложение Flipper](/ru/mobile/mobile-app)
- [Приложение-компаньон qUnleashed](/ru/mobile/qunleashed-app)
- [Веб-инструменты](/ru/mobile/web-tools)
