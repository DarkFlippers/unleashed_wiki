---
title: Furi API
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_furi_api.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriCheck.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi]
sources: [unleashed-docs, unleashed-src]
---
# Furi API

Щоб скористатися апаратною частиною Flipper — екраном, динаміком, радіо, USB, NFC — застосунок звертається до
**Furi**, набору бібліотек між «голим» залізом і прикладним кодом. Ця сторінка оглядово описує архітектуру
апаратної та програмної частини й розповідає про перевірки Furi під час виконання.

## Апаратна частина

Серце Flipper Zero — мікроконтролер (MCU) **STM32WB55**: два ядра, RAM, флеш-пам’ять і десятки периферійних
блоків (таймери, RTC, BLE, GPIO, …). Їхню роботу описано в Reference Manual до MCU. Навколо MCU стоїть кілька
зовнішніх мікросхем (CC1101, ST25R3916, контролер дисплея тощо) з власними даташитами.

![Структура апаратної частини Flipper Zero](/img/dev/flipper_zero_hardware.png)

Що означають кольори:

- **Фіолетовий** — блоки всередині MCU
- **Синій** — мікросхеми, зовнішні щодо MCU
- **Оранжевий** — решта периферійних компонентів, для яких не потрібна складна взаємодія

Прошивка має відкритий код, тому ви *можете* звертатися до заліза напряму й писати власні низькорівневі драйвери —
але зазвичай цього не потрібно.

## Програмна частина: Furi

**Furi** (**F**lipper **U**niversal **R**egistry **I**mplementation) — шар абстракції, який входить до складу
прошивки. Він дає зрозумілий API до апаратної частини й до типових системних завдань: потоків, динамічної пам’яті,
керування доступом до ресурсів (records), таймерів, черг повідомлень, журналювання тощо.

З Furi не доведеться читати сотні сторінок даташитів і писати драйвери — достатньо вивчити Furi API. До того ж це
звільняє кожного розробника від потреби щоразу реалізовувати те саме наново.

![Структура апаратної та програмної частини Flipper Zero](/img/dev/flipper_zero_architecture.png)

Furi розтягується на всю ширину схеми: він відділяє код прикладного рівня (служби та застосунки) від апаратної
частини під ним.

Furi складається з двох частин:

| Частина | Де | Що |
|---|---|---|
| Furi Core | `furi/` | Примітиви ОС: потоки, м’ютекси, черги повідомлень, records, таймери, цикл подій, журналювання, перевірки |
| Furi HAL | `targets/` (наприклад, `targets/f7/furi_hal/`) | Абстракція апаратної частини: GPIO, SPI, I2C, USB, Sub-GHz, NFC, RFID, живлення, … — див. [FuriHalBus](/ua/dev/furi-hal-bus) |

Початковий код:

- Furi Core: [unleashed-firmware/furi](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi)
  (офіційний: [flipperzero-firmware/furi](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/furi))
- Furi HAL: [unleashed-firmware/targets](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets)
  (офіційний: [flipperzero-firmware/targets](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/targets))

## Де шукати приклади

Furi використовує кожен застосунок Flipper, тому приклади є для будь-якого апаратного блоку:

- приклади застосунків у [`applications/examples/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples)
  (`example_event_loop`, `example_adc`, `example_ble_beacon`, …);
- вбудовані застосунки в `applications/main/` і додаткові застосунки Unleashed в `applications/system/`;
- застосунки спільноти в [каталозі застосунків](https://lab.flipper.net/apps) — посилання на початковий код є
  внизу сторінки кожного застосунку. Беріть ті, чия функціональність близька до того, що ви хочете зробити.

Усі функції, структури й заголовки Furi перелічено в офіційному [довіднику Doxygen](https://developer.flipper.net/flipperzero/doxygen/) — зазирніть туди, якщо потрібного виклику в цій вікі немає.

## Перевірки під час виконання та примусові падіння

Найкращий спосіб захистити цілісність системи — обробляти менше неможливих випадків і **падати якомога раніше**,
коли щось не так. Для цього у Furi Core є `check.h`.

Терміни:

- **Crash** — записати подію до журналу, зберегти інформацію про падіння в RTC, перезавантажитися.
- **Halt** — записати подію до журналу, зупинити систему.

Нюанси:

- Збірки debug і release поводяться по-різному: **debug-збірка ніколи не скидає** систему, щоб зберегти стан для
  налагоджувача.
- Якщо під’єднаний налагоджувач, виконання автоматично зупиняється перед перезавантаженням.
- Усі ці засоби приймають необов’язковий `MESSAGE_CSTR`. Він може бути в RAM або у флеші, але після
  перезавантаження показуються **лише повідомлення з флешу** (тобто використовуйте рядкові літерали).
- `MESSAGE_CSTR` може бути `NULL`, але макроси й самі коректно обробляють випадок без повідомлення — просто
  не передавайте його.

| Макрос | Поведінка | Коли застосовувати |
|---|---|---|
| `furi_assert(CONDITION)` / `furi_assert(CONDITION, MESSAGE_CSTR)` | Падіння, якщо `CONDITION` хибна — **лише в збірках для розробки** | Перевірки на етапі розробки застосунків і служб |
| `furi_check(CONDITION)` / `furi_check(CONDITION, MESSAGE_CSTR)` | **Завжди** падає, якщо `CONDITION` хибна | Умови, які мають виконуватися в будь-якій збірці |
| `furi_crash()` / `furi_crash(MESSAGE_CSTR)` | Безумовне падіння | Виявлено ненормальний стан |
| `furi_halt()` / `furi_halt(MESSAGE_CSTR)` | Зупинка системи | Використовується всередині системи, наприклад щоб зупинитися, коли вимкнення живлення неможливе |

::: warning Підводні камені furi_assert
- У релізних збірках (`DEBUG=0`) перевірок `furi_assert` немає взагалі.
- У бібліотеках їх типово теж немає; якщо вони потрібні, збирайте з `LIB_DEBUG=1`.
- Не ставте в `CONDITION` виклики функцій (побічні дії) — увесь вираз може бути вирізаний компілятором.
:::

Приклад:

```c
#include <furi.h>

void my_set_level(uint8_t level) {
    furi_check(level <= 100, "Level out of range");
    // ...
}
```

## Пов’язані сторінки

- [GUI у застосунках](/ua/dev/gui)
- [FuriHalBus API](/ua/dev/furi-hal-bus)
- [Налагодження застосунків](/ua/dev/debugging) — зокрема сигнали налагодження Furi HAL
