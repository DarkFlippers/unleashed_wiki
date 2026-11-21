---
title: Добавление вручную
order: 30
original: [https://docs.flipper.net/zero/ibutton/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# Добавление ключей iButton вручную

Виртуальный ключ можно создать по ID без физического ключа — например, по номеру, выгравированному на ключе или
записанному раньше. Его можно эмулировать, а для записываемых протоколов — [записать на болванку](/ru/ibutton/write).

## Порядок действий

1. Откройте `Main Menu → iButton → Add Manually`.
2. Выберите протокол:

   | Пункт меню | Что вводить |
   |---|---|
   | **Dallas DS1990** | 8 байт ROM |
   | **Dallas DS1992** | 8 байт ROM |
   | **Dallas DS1996** | 8 байт ROM |
   | **Dallas DS1971** | 8 байт ROM |
   | **Dallas DS1420** | 8 байт ROM |
   | **Dallas (non-specific)** | 8 байт ROM — любое устройство 1-Wire, без проверок |
   | **Cyfral** | 2 байта |
   | **Metakom** | 4 байта (у каждого байта должна быть правильная чётность) |

   ![Список типов ключей в Add Manually: Dallas DS1990, DS1992, DS1996 и DS1971](/screens/ibutton/add_manually.png)

3. Экран **Enter the key** открывает hex-редактор. Введите байты и нажмите **Save**.
4. Введите имя (префикс по умолчанию `iBtn`) и сохраните. Ключ сохраняется в `/ext/ibutton/<имя>.ibtn`.

## Правка сохранённого ключа

`Main Menu → iButton → Saved` → ключ → **Edit** → измените hex → **Save** → имя → **Save**.

## Про ID Dallas

ROM Dallas — это `family code` (1 байт) + `серийный номер` (6 байт) + `CRC` (1 байт):

```text
01 DE AD BE EF 00 00 ??
^^ family code (01 = DS1990, 81 = DS1420, 08 = DS1992, 0C = DS1996, 14 = DS1971)
                     ^^ CRC-8 от первых 7 байт
```

- Большинство домофонных ключей — DS1990 с family code `01`.
- При неверном CRC считыватель может отвергнуть ключ, а Флиппер при обратном чтении покажет ошибку CRC.
- Нужен ключ с заведомо неверным family code или CRC? Используйте **Dallas (non-specific)** — он ничего не проверяет.
- У добавленного вручную ключа **нет данных памяти**; для Full Write on Same Type нужно настоящее чтение.

::: tip Редактор байтов
В Unleashed, если несколько раз нажать <kbd>↑</kbd> в поле ввода байтов, откроется мини-редактор полубайтов — удобно для
длинных ID.
:::

## Связанные страницы

- [Чтение](/ru/ibutton/read) · [Запись](/ru/ibutton/write) · [Протоколы](/ru/ibutton/protocols) ·
  [Формат файла](/ru/ibutton/file-format)
