---
title: Фазер iButton
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/ibtnfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# Фазер iButton

**Фазер** (fuzzer) по черзі емулює низку ID ключів, щоб побачити реакцію зчитувача — наприклад, щоб перевірити, чи
приймає ваш власний домофон типові або некоректні ID.

::: tip Unleashed
У ReadMe Unleashed згадано **плагіни LFRFID та iButton Fuzzer**. Фазер — це зовнішній застосунок, якого немає в дереві
вихідних кодів прошивки: у релізні збірки додають готові набори застосунків, а **extra apps pack**, який публікують
разом із кожним релізом, містить усі відомі робочі застосунки. Меню фазера залежить від версії застосунку, тому тут
воно не описане.
:::

## Що постачає прошивка: приклади списків UID

Прошивка встановлює приклади списків ID у **`/ext/ibtnfuzzer/`**:

| Файл | Протокол | Довжина ID (hex-символів) |
|---|---|---|
| `example_uids_ds1990.txt` | Dallas DS1990 | 16 (8 байт) |
| `example_uids_cyfral.txt` | Cyfral | 4 (2 байти) |
| `example_uids_metakom.txt` | Metakom | 8 (4 байти) |

Формат — один hex-ID на рядок, `#` для коментарів, у кінці обов’язково **порожній рядок**:

```text
# Example file, P.S. keep empty line at the end!
0000000000000000
FE00000000000000
CAFE000000000000
00CAFE0000000000

```

Щоб зробити власний список, скопіюйте приклад і замініть ID; довжина має відповідати протоколу.

Словники від спільноти, на які посилається FAQ Unleashed:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058),
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Застосовуйте фазер лише до зчитувачів, які належать вам або на тестування яких у вас є дозвіл.
:::

## Пов’язані сторінки

- [Протоколи](/ua/ibutton/protocols) · [Емуляція ключів](/ua/ibutton/read) · [RFID-фазер](/ua/rfid/fuzzer)
