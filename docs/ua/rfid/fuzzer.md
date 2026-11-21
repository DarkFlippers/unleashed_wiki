---
title: Фазер RFID
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/rfidfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# Фазер RFID

**Фазер** (fuzzer) емулює довгу послідовність ID один за одним, щоб перевірити реакцію зчитувача — наприклад, чи приймає він
типовий ID, чи не падає від некоректних даних, або щоб перевірити діапазон дійсних карт у вашій власній системі.

::: tip Unleashed
ReadMe Unleashed перераховує **плагіни LFRFID та iButton Fuzzer** серед можливостей для NFC/RFID/iButton. Фазер —
це зовнішній застосунок, а не частина дерева вихідного коду прошивки: до релізних збірок додаються готові набори
застосунків, а **extra apps pack**, який публікується з кожним релізом, містить усі відомі робочі застосунки. Його
меню залежать від версії застосунку, тому тут вони не описані.
:::

## Що постачає прошивка: приклади списків UID

Прошивка встановлює для фазера приклади списків ID у **`/ext/rfidfuzzer/`**:

| Файл | Протокол | Довжина ID (hex-символів) |
|---|---|---|
| `example_uids_em4100.txt` | EM4100 | 10 (5 байтів) |
| `example_uids_h10301.txt` | HID H10301 | 6 (3 байти) |
| `example_uids_hidprox.txt` | HIDProx | 12 (6 байтів) |
| `example_uids_pac.txt` | PAC/Stanley | 8 (4 байти) |

Формат — один hex-ID на рядок, `#` для коментарів і **порожній рядок у кінці** файлу:

```text
# Example file, P.S. keep empty line at the end!
0000000000
FE00000000
CAFE000000
00CAFE0000

```

Свій список зробіть, скопіювавши один із прикладів і замінивши ID; довжина ID має відповідати розміру ключа протоколу
(див. [протоколи](/ua/rfid/protocols), стовпець *Байтів*).

FAQ Unleashed посилається на готові файли словників, якими поділилася спільнота:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058) і
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Застосовуйте фазер лише до зчитувачів, які належать вам або на тестування яких ви маєте дозвіл.
:::

## Пов’язані сторінки

- [Протоколи](/ua/rfid/protocols) · [Читання](/ua/rfid/read) · [Фазер iButton](/ua/ibutton/fuzzer)
