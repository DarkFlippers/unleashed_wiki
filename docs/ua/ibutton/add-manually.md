---
title: Додавання ключів вручну
order: 30
original: [https://docs.flipper.net/zero/ibutton/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# Додавання ключів iButton вручну

Віртуальний ключ можна створити за його ID, не маючи фізичного ключа — наприклад, за номером, вигравіюваним на
корпусі, або записаним раніше. Такий ключ можна емулювати, а для протоколів із підтримкою запису —
[записати на заготовку](/ua/ibutton/write).

## Порядок дій

1. Відкрийте `Main Menu → iButton → Add Manually`.
2. Оберіть протокол:

   | Пункт меню | Який ID вводити |
   |---|---|
   | **Dallas DS1990** | 8 байт ROM |
   | **Dallas DS1992** | 8 байт ROM |
   | **Dallas DS1996** | 8 байт ROM |
   | **Dallas DS1971** | 8 байт ROM |
   | **Dallas DS1420** | 8 байт ROM |
   | **Dallas (non-specific)** | 8 байт ROM — будь-який пристрій 1-Wire, без перевірок |
   | **Cyfral** | 2 байти |
   | **Metakom** | 4 байти (кожен байт має мати правильну парність) |

   ![Список типів ключів у Add Manually: Dallas DS1990, DS1992, DS1996 і DS1971](/screens/ibutton/add_manually.png)

3. Екран **Enter the key** відкриває hex-редактор. Введіть байти й натисніть **Save**.
4. Введіть назву (типовий префікс — `iBtn`) і збережіть. Ключ зберігається у `/ext/ibutton/<name>.ibtn`.

## Редагування збереженого ключа

`Main Menu → iButton → Saved` → ключ → **Edit** → змініть hex → **Save** → введіть назву → **Save**.

## Про ID ключів Dallas

ROM Dallas складається з `family code` (1 байт) + `serial` (6 байт) + `CRC` (1 байт):

```text
01 DE AD BE EF 00 00 ??
^^ family code (01 = DS1990, 81 = DS1420, 08 = DS1992, 0C = DS1996, 14 = DS1971)
                     ^^ CRC-8 over the first 7 bytes
```

- Більшість домофонних ключів — це DS1990 з family code `01`.
- Якщо CRC хибна, зчитувач може відкинути ключ, а Flipper під час зворотного читання повідомить про помилку CRC.
- Потрібен ключ із навмисно хибним family code або CRC? Скористайтеся **Dallas (non-specific)** — там перевірок немає.
- Ключ, доданий вручну, **не містить даних пам’яті**; для Full Write on Same Type потрібне справжнє читання.

::: tip Редактор байтів
В Unleashed, якщо кілька разів натиснути <kbd>↑</kbd> у полі введення байтів, відкривається міні-редактор
напівбайтів — зручно для довгих ID.
:::

## Пов’язані сторінки

- [Читання](/ua/ibutton/read) · [Запис](/ua/ibutton/write) · [Протоколи](/ua/ibutton/protocols) ·
  [Формат файлів](/ua/ibutton/file-format)
