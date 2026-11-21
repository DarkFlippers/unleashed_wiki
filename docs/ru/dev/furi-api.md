---
title: Furi API
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_furi_api.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriCheck.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi]
sources: [unleashed-docs, unleashed-src]
---
# Furi API

Чтобы работать с железом Флиппера — экраном, динамиком, радио, USB, NFC, — приложение обращается к **Furi**, набору
библиотек между «голым» железом и кодом приложений.

## Железо

Сердце Flipper Zero — микроконтроллер (MCU) **STM32WB55**: два ядра, RAM, флеш и десятки периферийных блоков
(таймеры, RTC, BLE, GPIO, …). Их работа описана в Reference Manual на MCU. Вокруг MCU стоят несколько внешних
микросхем (CC1101, ST25R3916, контроллер дисплея и т. д.) со своими даташитами.

![Аппаратная структура Flipper Zero](/img/dev/flipper_zero_hardware.png)

Цвета на схеме:

- **Фиолетовый** — блоки внутри MCU
- **Синий** — микросхемы вне MCU
- **Оранжевый** — прочие периферийные компоненты, не требующие сложного взаимодействия

Поскольку прошивка открытая, вы *можете* работать с железом напрямую и писать свои низкоуровневые драйверы — но
обычно это не нужно.

## Софт: Furi

**Furi** (**F**lipper **U**niversal **R**egistry **I**mplementation) — слой абстракции, входящий в прошивку. Он даёт
простой API к железу и к типовым системным задачам: потокам, динамической памяти, контролю доступа к ресурсам
(records), таймерам, очередям сообщений, логированию и т. д.

С Furi не нужно читать сотни страниц даташитов и писать драйверы — достаточно изучить Furi API. Заодно разработчикам
не приходится каждому заново реализовывать одно и то же.

![Аппаратная и программная структура Flipper Zero](/img/dev/flipper_zero_architecture.png)

Furi занимает всю ширину схемы: он отделяет код уровня приложений (сервисы и приложения) от железа под ним.

Furi состоит из двух частей:

| Часть | Где | Что |
|---|---|---|
| Furi Core | `furi/` | Примитивы ОС: потоки, мьютексы, очереди сообщений, records, таймеры, event loop, логирование, проверки |
| Furi HAL | `targets/` (например, `targets/f7/furi_hal/`) | Абстракция железа: GPIO, SPI, I2C, USB, Sub-GHz, NFC, RFID, питание, … — см. [FuriHalBus](/ru/dev/furi-hal-bus) |

Исходный код:

- Furi Core: [unleashed-firmware/furi](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi)
  (официальный: [flipperzero-firmware/furi](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/furi))
- Furi HAL: [unleashed-firmware/targets](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets)
  (официальный: [flipperzero-firmware/targets](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/targets))

## Где искать примеры

Furi используют все приложения Флиппера, так что примеры есть для любого аппаратного блока:

- примеры в [`applications/examples/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples)
  (`example_event_loop`, `example_adc`, `example_ble_beacon`, …);
- встроенные приложения в `applications/main/` и дополнительные приложения Unleashed в `applications/system/`;
- приложения сообщества в [Apps Catalog](https://lab.flipper.net/apps) — ссылка на исходники внизу страницы каждого
  приложения. Выбирайте те, что по функциональности близки к задуманному.

Все функции, структуры и заголовки Furi перечислены в официальном [справочнике API Doxygen](https://developer.flipper.net/flipperzero/doxygen/) — загляните туда, если нужного вызова нет в этой вики.

## Проверки во время выполнения и принудительный крэш

Лучший способ защитить целостность системы — обрабатывать меньше «невозможных» случаев и **падать как можно раньше**,
если что-то пошло не так. Для этого в `check.h` из Furi Core есть хелперы.

Термины:

- **Crash** — записать событие в лог, сохранить информацию о падении в RTC, перезагрузиться.
- **Halt** — записать событие в лог, остановить систему.

Замечания:

- Отладочная и релизная сборки ведут себя по-разному: **отладочная сборка никогда не перезагружает** систему, чтобы
  сохранить состояние для отладчика.
- При подключённом отладчике выполнение автоматически останавливается перед перезагрузкой.
- Все хелперы принимают необязательный `MESSAGE_CSTR`. Он может лежать в RAM или во флеше, но **после перезагрузки
  показываются только сообщения из флеша** (то есть используйте строковые литералы).
- `MESSAGE_CSTR` может быть `NULL`, но макросы и так обрабатывают вариант без сообщения — просто не указывайте его.

| Макрос | Поведение | Когда использовать |
|---|---|---|
| `furi_assert(CONDITION)` / `furi_assert(CONDITION, MESSAGE_CSTR)` | Крэш, если `CONDITION` ложно — **только в отладочных сборках** | Проверки на этапе разработки в приложениях и сервисах |
| `furi_check(CONDITION)` / `furi_check(CONDITION, MESSAGE_CSTR)` | **Всегда** крэш, если `CONDITION` ложно | Условия, которые должны выполняться в любой сборке |
| `furi_crash()` / `furi_crash(MESSAGE_CSTR)` | Безусловный крэш | Обнаружено аномальное состояние |
| `furi_halt()` / `furi_halt(MESSAGE_CSTR)` | Остановить систему | Используется внутри, например чтобы остановиться, когда выключение невозможно |

::: warning Подводные камни furi_assert
- В релизных сборках (`DEBUG=0`) проверок `furi_assert` нет.
- В библиотеках их по умолчанию тоже нет; при необходимости собирайте с `LIB_DEBUG=1`.
- Не помещайте вызовы функций (побочные эффекты) в `CONDITION` — всё выражение может быть вырезано при компиляции.
:::

Пример:

```c
#include <furi.h>

void my_set_level(uint8_t level) {
    furi_check(level <= 100, "Level out of range");
    // ...
}
```

## Связанные страницы

- [GUI в приложениях](/ru/dev/gui)
- [FuriHalBus API](/ru/dev/furi-hal-bus)
- [Отладка приложений](/ru/dev/debugging) — включая отладочные сигналы Furi HAL
