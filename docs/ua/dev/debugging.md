---
title: Налагодження застосунків
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_debugging_faps.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalDebugging.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md]
sources: [unleashed-docs]
---
# Налагодження застосунків

Налагодження в реальному часі (in-circuit) дає змогу запустити застосунок, зупинити його в будь-якому місці,
покроково пройти код і спостерігати за змінними та стеком викликів. Так знаходиться значно більше помилок, ніж
методом «додати рядок у журнал і спробувати ще раз».

::: info
Налагодження через зонд не обов’язкове. Завжди можна налагоджувати, завантажуючи застосунки через USB і читаючи
[журнал](/ua/dev/cli#reading-logs).
:::

## Що потрібно

- Flipper Zero (*цільовий пристрій*).
- Комп’ютер із Windows, Linux або macOS із [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) (для
  застосунків) чи з повним деревом прошивки та [fbt](/ua/dev/fbt).
- Підтримуваний **SWD-зонд**.

### Підтримувані SWD-зонди

| Зонд | Примітки |
|---|---|
| **Другий Flipper Zero** | Запустіть на ньому [застосунок DAP Link](https://lab.flipper.net/apps/dap_link), і він стане SWD-зондом |
| [Wi-Fi Devboard](https://shop.flipperzero.one/products/wifi-devboard) | Зі стоковою прошивкою (Blackmagic); підключається через USB або Wi-Fi — див. [Dev Board](/ua/gpio/devboard) |
| Зонди CMSIS-DAP | Наприклад, [Raspberry Pi Debug Probe](https://www.raspberrypi.com/products/debug-probe/), [l-tek](https://www.l-tek.com/web-shop/cmsis-dap-debug-probe/), [makerdiary Pitaya-Link](https://makerdiary.com/products/pitaya-link) |
| [Зонди, сумісні з Blackmagic](https://black-magic.org/hardware.html) | |
| ST-Link | [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html), [ST-LINK V3](https://www.st.com/en/development-tools/stlink-v3set.html), [плата ST-Link V3](/ua/dev/hardware#st-link-v3-developer-board) |
| J-Link | Прошивання та налагодження лише з VS Code; інструменти SEGGER потрібно встановити самостійно |

## Підготовка Фліппера

Увімкніть на цільовому пристрої режим налагодження: `Main Menu → Settings → System → Debug` → **ON**.

## Крок за кроком (VS Code)

1. **Під’єднайте зонд до GPIO-гребінки Фліппера.** Зонди, зроблені під Фліппер, просто вставляються у гребінку. Для
   універсального зонда потрібні три проводи:

   | Сигнал | Вивід Фліппера |
   |---|---|
   | SWCLK | 10 |
   | SWDIO | 12 |
   | GND | 8, 11 або 18 |

   Якщо зонд має ще й UART, під’єднайте його до USART Фліппера (виводи **13** TX і **14** RX). Цей порт виводить
   журнал і дані про збої, що дуже допомагає.
2. **Під’єднайте зонд до комп’ютера** — зазвичай через USB; Wi-Fi Devboard працює ще й через Wi-Fi.
3. **Підготуйте проєкт:** один раз виконайте `ufbt vscode_dist` (застосунок) або `./fbt vscode_dist` (прошивка) і
   відкрийте папку у VS Code.
4. **Перейдіть у VS Code до Run and Debug:** натисніть піктограму налагодження на бічній панелі або
   <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> (<kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> у macOS). Виберіть
   конфігурацію для свого зонда й натисніть **Play**.

   ::: info
   Початок сесії налагодження **зупиняє** прошивку. Щоб продовжити виконання, натисніть **Continue** на панелі
   налагодження.
   :::
5. **Користуйтеся елементами керування:** reset, pause, continue, step in, step out, disconnect.
6. **Ставте точки зупину**, клікаючи ліворуч від номера рядка. Виконання спиняється, коли доходить до цього рядка.
7. **Дивіться стек викликів** на панелі *Call Stack*, доки виконання зупинене.
8. **Дивіться значення змінних** на панелях *Variables*, *Watch* або *Live Watch*.

Відеодемонстрація від Flipper Devices: [Debugging FAPs in VS Code](https://cdn.flipperzero.one/app_dev_flipper_zero_debug_demo.mp4).

## Налагодження з командного рядка через fbt

З повним деревом прошивки налагоджувати можна й без VS Code:

| Команда | Що робить |
|---|---|
| `./fbt debug` | Збирає й прошиває прошивку, після чого підключає GDB із завантаженим `.elf` прошивки |
| `./fbt blackmagic` | Налагодження через зонд Blackmagic (Wi-Fi Devboard) |
| `./fbt debug_other` / `debug_other_blackmagic` | Підключає GDB без завантаження `.elf`; `.elf` свого застосунку додайте командою `add-symbol-file` |
| `./fbt updater_debug` | Підключає GDB із `.elf` оновлювача |
| `./fbt openocd ARGS="..."` | Просто запускає OpenOCD |
| `./fbt get_stlink` | Виводить серійні номери ST-Link для `SWD_TRANSPORT_SERIAL=...` |

## Налагоджувальні сигнали Furi HAL

Деякі підсистеми Furi можуть виводити свій внутрішній стан на виводи GPIO — щоб стежити за ним логічним аналізатором
чи осцилографом. Увімкнути їх можна відповідним define під час збірки, наприклад:

```sh
./fbt --extra-define=FURI_HAL_OS_DEBUG flash
```

### `FURI_HAL_OS_DEBUG` — планувальник і сон

Показує тики, їхнє приглушення, простій і плин часу:

| Сигнал | Вивід | Значення |
|---|---|---|
| `AWAKE` | `PA7` | Високий, доки система щось обчислює, низький під час сну — показує переходи до сну |
| `TICK` | `PA6` | Перемикається на кожному системному тику (лише коли приглушення тиків не діє) — виявляє зсув тиків і нештатне планування |
| `SECOND` | `PA4` | Перемикається щосекунди — збої в його періоді означають, що система не витримує жорсткого реального часу |

### `FURI_HAL_POWER_DEBUG` — режими живлення

Відслідковує переходи між режимами живлення:

| Сигнал | Вивід | Значення |
|---|---|---|
| `WFI` | `PB2` | Легкий сон (wait for interrupt). Найлегший режим енергозбереження, який нічого не ламає — працює все, включно з налагодженням |
| `STOP` | `PC3` | Режим STOP, глибокий сон платформи. Більшість кристала вимкнена або недоступна; налагоджувати MCU в цьому режимі практично неможливо |

### `FURI_HAL_SD_SPI_DEBUG` — картка microSD

Записує в журнал обмін по шині SPI з карткою microSD.

## Усунення проблем

| Проблема | Що робити |
|---|---|
| Зонд підключається, але нічого не відбувається | Прошивка зупинена — натисніть **Continue** |
| Точки зупину в застосунку ігноруються | Переконайтеся, що символи з `.elf` застосунку завантажені (конфігурація VS Code з `vscode_dist` робить це сама; з `debug_other` скористайтеся `add-symbol-file`) |
| Зневаджувач втрачає цільовий пристрій | MCU може бути в режимі STOP, див. `FURI_HAL_POWER_DEBUG`. Режим Debug на Фліппері має бути **ON** |
| Змінні показані як optimised out | Зберіть із `DEBUG=1` (зверніть увагу: така прошивка може бути завелика для пакування — див. [Збірка](/ua/dev/build)) |

## Пов’язані сторінки

- [Перший застосунок на C](/ua/dev/first-app-c)
- [Flipper Build Tool (fbt)](/ua/dev/fbt)
- [Dev Board](/ua/gpio/devboard)
- [Апаратна частина](/ua/dev/hardware) — схеми розпіновки та плат розширення
