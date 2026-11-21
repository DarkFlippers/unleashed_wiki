---
title: Expansion-модули
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/ExpansionModules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/expansion, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/expansion_settings_app, https://docs.flipper.net/zero/video-game-module/quick-start]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Expansion-модули

**Expansion-модуль** (модуль расширения) — сторонняя плата на GPIO-разъёме, которую Flipper определяет автоматически и
даёт ей управлять собой по **RPC** (тому же протоколу, что используют qFlipper и мобильное приложение). Самый известный
пример — [Video Game Module](/ru/gpio/video-game-module). Обнаружением и связью занимается сервис прошивки `expansion` и
протокол **Expansion Module Protocol**, описанный ниже.

## Настройка: какой UART слушать

1. Откройте `Main Menu → Settings → Expansion Modules`.
2. Выберите `Listen UART`:
   - `USART` — пины 13 (TX) / 14 (RX). Обязательно для Video Game Module.
   - `LPUART` — пины 15 (TX) / 16 (RX).
   - `None` — обнаружение выключено, Flipper игнорирует модули.
3. Нажмите <kbd>BACK</kbd>. Выбор сохраняется и применяется сразу.

| UART | Пин TX | Пин RX |
|---|---|---|
| USART | 13 | 14 |
| LPUART | 15 | 16 |

::: tip Когда выбирать None
Если тот же UART занят чем-то другим (Wi-Fi плата, GSM, GPS, мост USB-UART) и наблюдаются странности, поставьте
`Listen UART` в `None` или на другой UART. Приложения, которые сами занимают последовательный порт, на время работы
приостанавливают обнаружение.
:::

## Expansion Module Protocol (для разработчиков модулей)

Байт-ориентированный синхронный протокол «запрос-ответ» поверх UART: обнаружение модуля, согласование скорости,
контрольная сумма XOR и прозрачная передача RPC-трафика.

### Термины

- **Host** — Flipper. **Device / модуль** — expansion-модуль.
- **Таймаут, Tto = 250 мс** — время бездействия, после которого соединение считается потерянным.
- **Мёртвое время после смены скорости, Tdt = 25 мс** — сразу после смены скорости передавать нельзя.

### Структура кадра

| Заголовок (1 байт) | Содержимое (0+ байт) | Контрольная сумма (1 байт) |
|---|---|---|
| Тип кадра | Полезная нагрузка | XOR всех предыдущих байтов, начальное значение 0 |

| Тип | Заголовок | Содержимое | Назначение |
|---|---|---|---|
| HEARTBEAT | `0x01` | — | Поддерживает простаивающее соединение |
| STATUS | `0x02` | код ошибки (1 байт) | Подтверждает каждый принятый кадр |
| BAUD RATE | `0x03` | скорость (4 байта) | Согласование скорости |
| CONTROL | `0x04` | команда (1 байт) | Старт/стоп RPC, управление 5 В |
| DATA | `0x05` | размер (1 байт, `0x00`–`0x40`) + до 64 байт данных | Передача RPC-данных |

Коды STATUS: `0x00` OK, `0x01` неизвестная ошибка, `0x02` скорость не поддерживается.

Команды CONTROL:

| Команда | Смысл | Когда можно |
|---|---|---|
| `0x00` | Начать RPC-сессию | RPC не активна |
| `0x01` | Завершить RPC-сессию | RPC активна |
| `0x02` | Включить OTG (5 В) на GPIO | RPC не активна (иначе — через RPC-сообщения) |
| `0x03` | Выключить OTG (5 В) на GPIO | RPC не активна (иначе — через RPC-сообщения) |

### Порядок соединения

1. **Начинает модуль:** кратковременно прижимает RX Flipper к земле.
2. Flipper отвечает **HEARTBEAT**: готов.
3. В течение Tto модуль обязан прислать кадр **BAUD RATE** — всегда первым, даже если 9600 устраивает. Начальная
   скорость всегда **9600 бод**. Flipper отвечает STATUS OK или `0x02`; при отказе модуль может предложить другие
   скорости. До успешного согласования другие кадры запрещены.
4. Обе стороны меняют скорость, модуль выжидает Tdt.
5. Модуль шлёт **CONTROL → Start RPC**, Flipper подтверждает STATUS.
6. RPC-запросы идут в кадрах **DATA** (порциями по 64 байта; каждая подтверждается STATUS). Ответы RPC приходят кадрами
   DATA, которые модуль должен подтвердить STATUS.
7. В простое модуль шлёт **HEARTBEAT** чаще, чем раз в Tto; Flipper отвечает HEARTBEAT.
8. **CONTROL → Stop RPC** завершает сессию. После Tto тишины Flipper возвращается в режим ожидания.

```text
        MODULE               |            FLIPPER
-----------------------------+---------------------------
Pull down RX                -->
                            <--       Heartbeat
Baud Rate                   -->
                            <--       Status [OK | Error]
(both change baud rate, module waits Tdt)
Control [Start RPC]         -->
                            <--       Status [OK | Error]
Data [RPC Request]          -->
                            <--       Status [OK | Error]
                            <--       Data [RPC Response]
Status [OK | Error]         -->
Heartbeat                   -->
                            <--       Heartbeat
Control [Stop RPC]          -->
                            <--       Status [OK | Error]
```

### Ошибки

При любой обнаруженной ошибке (неверная сумма, неожиданный кадр) заметившая сторона **прекращает обмен и
сбрасывается**. Другая сторона получает таймаут через Tto, и соединение устанавливается заново с шага 1.

### Программное управление

Приложения прошивки могут вызывать `expansion_enable()` / `expansion_disable()` (и `expansion_set_listen_serial()`) из
сервиса `expansion` вместо экрана настроек. В исходниках есть отладочное приложение `expansion_test` — эталонная
реализация модуля.

## См. также

- [Video Game Module](/ru/gpio/video-game-module)
- [Распиновка GPIO](/ru/gpio/pinout)
- [Внешние модули](/ru/gpio/external-modules)
