---
title: Інфрачервоний порт
original: [https://docs.flipper.net/zero/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Інфрачервоний порт

Flipper Zero має вбудований інфрачервоний (ІЧ) модуль. Він умієить **записувати** кнопки майже будь-якого ІЧ-пульта,
**зберігати** їх як віртуальний пульт на microSD-картці, **надсилати** їх назад і працювати як **універсальний
пульт**, що перебирає бібліотеку відомих кодів для телевізорів, аудіосистем, проєкторів, світлодіодних лент,
вентиляторів і кондиціонерів.

![Інфрачервоний порт на Flipper Zero](/img/remote/133011d2bd3dc44c.png)

## Обладнання

- Прозоре для ІЧ пластикове вікно на верхньому торці Flipper.
- **Три ІЧ-світлодіоди** для передавання.
- **ІЧ-приймач**, який демодулює несучу (він налаштований на поширену несучу 38 кГц). Запис завжди виконується
  саме цим вбудованим приймачем.
- За бажанням — **зовнішній ІЧ-передавач** на піні GPIO 2 (A7) для більшої дальності, див.
  [Зовнішні ІЧ-модулі](/ua/infrared/external-ir).

## Меню Infrared

Відкрийте `Main Menu → Infrared`. Пункти меню взяті безпосередньо з прошивки:

![Меню Infrared із пунктами Universal Remotes, Learn New Remote, Saved Remotes і GPIO Settings](/screens/infrared/menu.png)

| Пункт | Що робить |
|---|---|
| **Universal Remotes** | Надсилає цілу бібліотеку кодів для однієї кнопки (Power, Vol+…), доки ваш пристрій не відреагує. Див. [Універсальні пульти](/ua/infrared/universal-remotes). |
| **Learn New Remote** | Записує кнопки з фізичного пульта й зберігає їх як новий пульт. Див. [Запис і надсилання сигналів](/ua/infrared/read). |
| **Saved Remotes** | Відкриває файловий браузер у `/ext/infrared/`, щоб надсилати, редагувати, перейменовувати або видаляти ваші пульти. |
| **GPIO Settings** | Вибір передавача (вбудований, пін 2 (A7) або автовизначення) і 5 В на GPIO. Див. [Зовнішні ІЧ-модулі](/ua/infrared/external-ir). |
| **Learn New Remote RAW** | Лише з увімкненим `Settings → System → Debug`. Те саме, що Learn, але декодер вимкнений: кожен сигнал зберігається як RAW. |
| **Debug RX** | Лише з увімкненим Debug. Живий «INFRARED monitor» того, що приймає приймач. |

::: tip Unleashed
Застосунок Infrared, його декодери протоколів і механіка універсальних пультів — з офіційної прошивки.
Unleashed додає:
- ІЧ-протокол **RCA** (див. [Протоколи](/ua/infrared/protocols));
- додаткові бібліотеки універсальних пультів (**LEDs**, **Fans**) і значно більші, регулярно перевірені бібліотеки
  для телевізорів, аудіо, проєкторів і кондиціонерів, які підтримує команда Unleashed (ІЧ-ресурси від @amec0e).
  Бібліотека телевізорів перезібрана так, щоб працювали **всі** її кнопки;
- підтримку зовнішніх ІЧ-модулів з автовизначенням (перенесено з офіційної прошивки).
:::

## Де лежать файли

| Шлях | Вміст |
|---|---|
| `/ext/infrared/*.ir` | Ваші збережені пульти (`Filetype: IR signals file`). |
| `/ext/infrared/assets/*.ir` | Бібліотеки універсальних пультів: `tv.ir`, `audio.ir`, `projectors.ir`, `leds.ir`, `fans.ir`, `ac.ir` (`Filetype: IR library file`). Вони встановлюються й оновлюються разом із прошивкою. |
| `/ext/infrared/.infrared.settings` | Налаштування GPIO (пін виходу, 5 В). |

Формат файлів `.ir` описано на сторінці [Формат ІЧ-файлів](/ua/infrared/file-format).

## Командний рядок

Команда `ir` доступна в [CLI](/ua/dev/cli) (наприклад, через qFlipper або серійний термінал):

```text
ir rx [raw]                                  receive and print signals (raw = no decoding)
ir tx <protocol> <address> <command>         send a parsed signal, address/command in hex
ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...
                                             frequency 10000-1000000 Hz, duty cycle 0-100, max 512 samples
ir decode <input_file> [<output_file>]       try to decode RAW signals of a file into parsed ones
ir universal <remote_name> <signal_name>     run a universal library, e.g. ir universal tv Power
ir universal list <remote_name>              list the signal names of a library
```

## Сторінки цього розділу

| Сторінка | Про що вона |
|---|---|
| [Запис і надсилання сигналів](/ua/infrared/read) | Записати пульт, зберегти його, надсилати кнопки, редагувати / переміщувати / перейменовувати / видаляти кнопки |
| [Універсальні пульти](/ua/infrared/universal-remotes) | Усі категорії універсальних пультів, кнопки, керування, збереження робочого коду |
| [Пульти в мобільному застосунку](/ua/infrared/mobile) | Remotes Library у Flipper Mobile App |
| [Як надіслати свої записи](/ua/infrared/captures) | Як зробити чисті записи для універсальних бібліотек |
| [Зовнішні ІЧ-модулі](/ua/infrared/external-ir) | Вихід на GPIO, автовизначення, живлення 5 В |
| [Протоколи](/ua/infrared/protocols) | Усі протоколи, які знає декодер, включно з RCA |
| [Формат ІЧ-файлів](/ua/infrared/file-format) | Формати файлів пульта, бібліотеки й тестів `.ir` |
