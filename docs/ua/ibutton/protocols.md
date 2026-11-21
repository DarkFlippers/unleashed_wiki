---
title: Підтримувані протоколи
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks, https://docs.flipper.net/zero/ibutton/read, https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Підтримувані протоколи iButton

Складено за каталогом `lib/ibutton/protocols/` прошивки Unleashed. Прошивка поділяє протоколи на **Dallas** (1-Wire)
і **misc** (Cyfral, Metakom).

| Протокол (назва файла) | Пункт меню | Family code | Пам’ять | Емуляція | Write ID на | Full Write on Same Type |
|---|---|---|---|---|---|---|
| `DS1990` | Dallas DS1990 | `01` | — | ✓ | RW1990.1, RW1990.2, TM2004, TM01x | — |
| `DS1420` | Dallas DS1420 | `81` | — | ✓ | RW1990.1, RW1990.2, TM2004 | — |
| `DS1992` | Dallas DS1992 | `08` | 128 байт SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1996` | Dallas DS1996 | `0C` | 8192 байти SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1971` | Dallas DS1971 | `14` | 32 байти EEPROM (`Eeprom Data`) | ✓ | TM2004 | ✓ |
| `(non-specific)` | Dallas (non-specific) | будь-який | — (лише ROM) | ✓ | TM2004 | — |
| `Cyfral` | Cyfral | — | 2-байтовий код | ✓ | TM01x | — |
| `Metakom` | Metakom | — | 4-байтовий код | ✓ | TM01x | — |

## Dallas 1-Wire

«Touch memory» від Dallas Semiconductor (тепер Analog Devices). Кожен пристрій має 8-байтовий ROM: family code,
48-бітний серійний номер і CRC-8. Flipper перевіряє CRC та визначає тип за family code.

- **DS1990 (DS1990A)** — класичний ключ лише з ID, який використовує більшість домофонів.
- **DS1420** — повністю сумісний із DS1990, відрізняється лише family code (`81` замість `01`).
- **DS1992 / DS1996** — ключі з пам’яттю SRAM; DS1971 — з EEPROM. Flipper зчитує пам’ять, може показати її
  (**Data Info**), емулювати та скопіювати на ключ того самого типу.
- **Dallas (non-specific)** — узагальнений варіант для будь-якого іншого пристрою 1-Wire: зчитується лише ROM, нічого
  не перевіряється. Придатний також для того, щоб зробити ключ із навмисно хибним family code або CRC.

## Cyfral

Протокол домофонних ключів, поширений у Росії та країнах СНД; це не 1-Wire. Код зберігається у 2 байтах. Можна емулювати та записати на заготовку TM01x.

## Metakom

Ще один домофонний протокол із країн СНД. Код займає 4 байти, кожен байт містить біт парності — ключ із хибною
парністю вважається недійсним і не записується. Можна емулювати та записати на заготовку TM01x.

## Заготовки

| Заготовка | Що приймає | Поведінка |
|---|---|---|
| **RW1990.1** | ROM Dallas (8 байт) | Розблокування, запис (біти інвертовані), блокування |
| **RW1990.2** | ROM Dallas (8 байт) | Розблокування, запис, блокування |
| **TM2004** | ROM Dallas (8 байт) | Запис з адреси 0 зі зворотною перевіркою кожного байта |
| **TM01x** | ROM Dallas, Cyfral, Metakom | Cyfral/Metakom записуються як 36-бітний кадр (4-бітний префікс + 32 біти коду), перевіряються, а потім **фіналізуються** (незворотно). ID Dallas не фіналізуються |

Про використання див. [Запис](/ua/ibutton/write).

::: tip Unleashed
В офіційній документації немає ні DS1420, ні налаштування Write Blanks, ні запису Cyfral/Metakom на TM01x.
:::

## Пов’язані сторінки

- [Читання](/ua/ibutton/read) · [Запис](/ua/ibutton/write) · [Формат файлів](/ua/ibutton/file-format)
