---
title: "Devboard: начало работы"
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/USB%20connection%20to%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Wi-Fi%20connection%20to%20the%20Devboard.md, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3]
sources: [unleashed-docs, flipper-docs]
---
# Wi-Fi Devboard: начало работы

Официальная **Wi-Fi Developer Board** — модуль на ESP32-S2 (ESP32-S2-WROVER-N4R2) для GPIO-разъёма. С завода на нём
прошивка **Black Magic Probe**, и он работает как **отладочный пробник**: соединяет отладчик на компьютере с STM32
во Flipper по SWD — через USB или Wi-Fi. Также он может пересылать логи UART Flipper.

![Wi-Fi Developer Board](/img/remote/7a7349f75be87abb.jpg)

::: tip Для прошивки она не нужна
Обновление, сборка и заливка собственной прошивки работают по обычному USB. Devboard нужна только для живой отладки
(GDB, точки останова) и для чтения логов независимо от ОС Flipper. Как использовать ту же плату для Wi-Fi (Marauder) —
см. [ESP32 и Wi-Fi](/ru/gpio/esp32).
:::

## Шаг 1. Включите режим Debug на Flipper

1. Откройте `Main Menu → Settings → System`.
2. Переключите `Debug` в `ON`.

Режим Debug нужен для отладки приложений и открывает отладочные опции в приложениях и [CLI](/ru/dev/cli). Его нужно
включать заново после каждого обновления прошивки.

## Шаг 2. Обновите прошивку платы

Плата поставляется со старой прошивкой. Сначала обновите её: [Devboard: обновление прошивки](/ru/gpio/devboard-firmware).

## Шаг 3. Вставьте Devboard во Flipper

1. **Сначала выключите Flipper.** Плата и microSD питаются от одной линии 3,3 В; подключение большой ёмкостной нагрузки
   «на горячую» может повредить данные на карте.
2. **Вставьте до упора.** Без чехла — без зазора между Flipper и платой (может понадобиться усилие). В силиконовом
   чехле — без зазора посередине между чехлом и платой.
3. Удерживайте <kbd>BACK</kbd>, чтобы включить Flipper.

![Devboard вставлена, Flipper без чехла](/img/remote/4eb1e40120ff42bb.jpg)

## Шаг 4. Подключите к компьютеру

### По USB

USB используется для отладки в режимах **Black Magic** или **DAPLink** и для чтения логов.

1. Посмотрите список последовательных устройств на компьютере:
   - **macOS:** `ls /dev/cu.*`
   - **Linux:** `ls /dev/tty*`
   - **Windows:** Диспетчер устройств → **Порты (COM и LPT)**
2. Подключите порт USB-C **на Devboard** к компьютеру.
3. Снова посмотрите список: появятся **два новых порта**, оба принадлежат Devboard.

Если ничего не появилось — другой кабель (с передачей данных), другой USB-порт или другой компьютер.

### По Wi-Fi: режим точки доступа (по умолчанию)

Плата создаёт собственную сеть. Пока вы подключены к ней, обычный Wi-Fi на компьютере отключается.

1. На компьютере или телефоне подключитесь к сети:
   - Имя: `blackmagic`
   - Пароль: `iamwitcher`
2. Откройте <http://192.168.4.1> или <http://blackmagic.local> — веб-интерфейс платы.

Если сеть `blackmagic` не видна:

- переподключите Wi-Fi на компьютере;
- возможно, плата настроена как клиент (STA). Удерживайте кнопку **BOOT** на плате **10 секунд**, чтобы сбросить
  настройки; после перезагрузки она снова станет точкой доступа.

### По Wi-Fi: режим клиента (STA)

Плата подключается к вашей существующей сети 2,4 ГГц, и интернет остаётся.

1. Подключитесь к плате в режиме точки доступа (выше) и откройте <http://192.168.4.1>.
2. Выберите режим **STA**, введите **SSID** и **пароль** своей сети. Кнопка **+** показывает ближайшие сети 2,4 ГГц
   (5 ГГц не поддерживается).
3. Сохраните и перезагрузите плату.
4. Теперь открывайте <http://blackmagic.local> через обычную сеть.

По Wi-Fi доступна только отладка в режиме **Black Magic**.

## Железо

- МК: ESP32-S2-WROVER-N4R2.
- SWD к Flipper на **пине 10 (SWCLK)** и **пине 12 (SWDIO)**; логи UART — на пинах USART 13/14 Flipper.
- Схемы (плата, ESP32-S2, питание, разъёмы) и сборочный чертёж:
  [Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).

## Дальше

- [Devboard: отладка и логи](/ru/gpio/devboard-debug)
- [Devboard: обновление прошивки](/ru/gpio/devboard-firmware)
- Сообщество: [Discord](https://discord.com/invite/flipper) (канал #wifi-devboard), [Reddit](https://www.reddit.com/r/flipperzero/)
