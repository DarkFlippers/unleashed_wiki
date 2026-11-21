---
title: Отладка приложений
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_debugging_faps.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalDebugging.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md]
sources: [unleashed-docs]
---
# Отладка приложений

С внутрисхемной отладкой приложение можно остановить в любом месте, пройти код построчно и следить за переменными и
стеком вызовов. Так находится гораздо больше ошибок, чем методом «добавить строчку в лог и попробовать ещё раз».

::: info
Внутрисхемная отладка не обязательна. Всегда можно отлаживать, загружая приложения по USB и читая
[лог](/ru/dev/cli#чтение-логов).
:::

## Что понадобится

- Flipper Zero (*целевое устройство*).
- Компьютер с Windows, Linux или macOS и [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) (для приложений)
  или полным деревом исходников прошивки с [fbt](/ru/dev/fbt).
- Поддерживаемый **SWD-отладчик** (probe).

### Поддерживаемые SWD-отладчики

| Отладчик | Примечания |
|---|---|
| **Второй Flipper Zero** | Запустите на нём приложение [DAP Link](https://lab.flipper.net/apps/dap_link) — он станет SWD-отладчиком |
| [Wi-Fi Devboard](https://shop.flipperzero.one/products/wifi-devboard) | Со стоковой прошивкой (Blackmagic); подключается по USB или Wi-Fi — см. [Dev Board](/ru/gpio/devboard) |
| Отладчики CMSIS-DAP | например [Raspberry Pi Debug Probe](https://www.raspberrypi.com/products/debug-probe/), [l-tek](https://www.l-tek.com/web-shop/cmsis-dap-debug-probe/), [makerdiary Pitaya-Link](https://makerdiary.com/products/pitaya-link) |
| [Blackmagic-совместимые отладчики](https://black-magic.org/hardware.html) | |
| ST-Link | [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html), [ST-LINK V3](https://www.st.com/en/development-tools/stlink-v3set.html), [плата ST-Link V3 devboard](/ru/dev/hardware#st-link-v3-developer-board) |
| J-Link | Прошивка и отладка только из VS Code; утилиты SEGGER нужно установить самостоятельно |

## Подготовка Флиппера

Включите режим отладки на целевом устройстве: `Main Menu → Settings → System → Debug` → **ON**.

## Пошагово (VS Code)

1. **Подключите отладчик к GPIO-разъёму Флиппера.** Отладчики, сделанные для Флиппера, просто вставляются в
   разъём. Для универсального отладчика подключите три провода:

   | Сигнал | Пин Флиппера |
   |---|---|
   | SWCLK | 10 |
   | SWDIO | 12 |
   | GND | 8, 11 или 18 |

   Если у отладчика есть UART, подключите его к USART Флиппера (пины **13** TX и **14** RX). В этот порт выводятся
   логи и информация о падениях — это очень помогает.
2. **Подключите отладчик к компьютеру** — обычно по USB; Wi-Fi Devboard работает и по Wi-Fi.
3. **Подготовьте проект:** один раз выполните `ufbt vscode_dist` (приложение) или `./fbt vscode_dist` (прошивка) и
   откройте папку в VS Code.
4. **Переключите VS Code в режим Run and Debug:** нажмите значок отладки на боковой панели или
   <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> (<kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> на macOS). Выберите
   конфигурацию для своего отладчика и нажмите **Play**.

   ::: info
   Запуск сессии отладки **останавливает** прошивку. Чтобы продолжить, нажмите **Continue** на панели отладки.
   :::
5. **Пользуйтесь кнопками отладки:** сброс, пауза, продолжить, шаг внутрь, шаг наружу, отключиться.
6. **Ставьте точки останова** кликом слева от номера строки. Выполнение остановится, дойдя до этой строки.
7. **Смотрите стек вызовов** на панели *Call Stack*, пока выполнение на паузе.
8. **Смотрите переменные** на панелях *Variables*, *Watch* или *Live Watch*.

Видео-демонстрация от Flipper Devices: [Debugging FAPs in VS Code](https://cdn.flipperzero.one/app_dev_flipper_zero_debug_demo.mp4).

## Отладка из командной строки через fbt

С полным деревом исходников прошивки можно отлаживать и без VS Code:

| Команда | Что делает |
|---|---|
| `./fbt debug` | Собрать и прошить прошивку, затем подключить GDB с загруженным `.elf` прошивки |
| `./fbt blackmagic` | Отладка через Blackmagic (Wi-Fi Devboard) |
| `./fbt debug_other` / `debug_other_blackmagic` | Подключить GDB без загрузки `.elf`; `.elf` своего приложения добавьте через `add-symbol-file` |
| `./fbt updater_debug` | Подключить GDB с `.elf` апдейтера |
| `./fbt openocd ARGS="..."` | Просто запустить OpenOCD |
| `./fbt get_stlink` | Показать серийные номера ST-Link для `SWD_TRANSPORT_SERIAL=...` |

## Отладочные сигналы Furi HAL

Некоторые подсистемы Furi умеют выводить внутреннее состояние на GPIO-пины, чтобы его можно было снять логическим
анализатором или осциллографом. Включаются они define-ом при сборке, например:

```sh
./fbt --extra-define=FURI_HAL_OS_DEBUG flash
```

### `FURI_HAL_OS_DEBUG` — планировщик и сон

Выводит тики, подавление тиков, простой (idle) и ход времени:

| Сигнал | Пин | Значение |
|---|---|---|
| `AWAKE` | `PA7` | Высокий уровень, пока система занята вычислениями, низкий — во сне. Позволяет отслеживать переходы в сон |
| `TICK` | `PA6` | Переключается на каждом системном тике (только если не идёт подавление тиков) — показывает дрейф тиков и аномальное планирование |
| `SECOND` | `PA4` | Переключается каждую секунду — сбои в этом ритме значат, что система не соблюдает требования жёсткого реального времени |

### `FURI_HAL_POWER_DEBUG` — режимы питания

Трассировка переходов между режимами питания:

| Сигнал | Пин | Значение |
|---|---|---|
| `WFI` | `PB2` | Лёгкий сон (wait for interrupt). Самый лёгкий режим энергосбережения, ничего не ломает — всё, включая отладку, работает |
| `STOP` | `PC3` | Режим STOP — глубокий сон платформы. Большая часть кристалла выключена или непригодна; отлаживать МК в этом режиме практически невозможно |

### `FURI_HAL_SD_SPI_DEBUG` — SD-карта

Логирует обмен по шине SPI с SD-картой.

## Решение проблем

| Проблема | Решение |
|---|---|
| Отладчик подключился, но ничего не происходит | Прошивка остановлена — нажмите **Continue** |
| Точки останова в приложении игнорируются | Убедитесь, что загружены символы `.elf` приложения (конфигурация VS Code из `vscode_dist` делает это сама; с `debug_other` используйте `add-symbol-file`) |
| Отладчик теряет устройство | МК может уходить в режим STOP; см. `FURI_HAL_POWER_DEBUG`. Режим Debug на Флиппере должен быть **ON** |
| Переменные показываются как optimized out | Соберите с `DEBUG=1` (учтите: такая прошивка может не влезть в пакет — см. [Сборку](/ru/dev/build)) |

## Связанные страницы

- [Первое приложение на C](/ru/dev/first-app-c)
- [Flipper Build Tool (fbt)](/ru/dev/fbt)
- [Dev Board](/ru/gpio/devboard)
- [Железо](/ru/dev/hardware) — чертежи, распиновка и схемы devboard
