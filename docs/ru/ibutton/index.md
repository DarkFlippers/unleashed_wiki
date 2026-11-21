---
title: iButton
original: [https://docs.flipper.net/zero/ibutton, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# iButton

iButton («touch memory», в народе — *таблетка*) — ключ в маленьком стальном корпусе, который считывается касанием
считывателя. Большинство таких ключей работают по Dallas **1-Wire**; в домофонах также встречаются ключи **Cyfral** и
**Metakom**. Flipper Zero умеет их читать, сохранять, эмулировать и записывать.

## Железо

Модуль iButton — контактная площадка с тремя подпружиненными pogo-пинами на плате iButton.

- Два крайних пина — данные (подключены к **GPIO pin 17**), средний — **земля**.
- **Чтение / запись ключа**: ключ касается **плоской части** площадки — левый пин данных + средний пин земли.
- **Эмуляция перед считывателем**: к считывателю прикладывается **выступающая часть** — правый пин данных + средний
  пин земли.
- Если земля не достаёт до ободка считывателя, используйте два провода: GPIO **17** (данные) и GPIO **8, 11 или 18**
  (земля).

## Главное меню

`Main Menu → iButton`:

![Меню iButton: Read, Saved, Add Manually и Settings](/screens/ibutton/menu.png)

| Пункт | Что делает | Страница |
|---|---|---|
| **Read** | Определить тип ключа и прочитать ID (и память у DS1992/1996/1971) | [Чтение](/ru/ibutton/read) |
| **Saved** | Файлы в `/ext/ibutton/` — эмуляция, запись, правка, переименование, удаление | [Чтение](/ru/ibutton/read), [Запись](/ru/ibutton/write) |
| **Add Manually** | Создать ключ по протоколу и hex-ID | [Добавление вручную](/ru/ibutton/add-manually) |
| **Settings** | **Write Blanks** — на какие типы болванок разрешена запись | [Запись](/ru/ibutton/write) |

::: tip Unleashed
По сравнению с официальной документацией в Unleashed есть страница **Settings → Write Blanks** (RW1990.1, RW1990.2,
TM2004, TM01x), при записи видно, какая болванка пробуется и на какую записалось, ключи **Cyfral и Metakom** пишутся на
болванки **TM01x**, поддерживается **DS1420**. В ReadMe также указан плагин iButton Fuzzer.
:::

## Страницы раздела

- [Чтение ключей](/ru/ibutton/read) — чтение, сохранение, эмуляция, ошибки CRC.
- [Запись на болванки](/ru/ibutton/write) — RW1990, TM2004, TM01x; Write ID и Full Write on Same Type.
- [Добавление вручную](/ru/ibutton/add-manually) — создание ключа по ID.
- [Поддерживаемые протоколы](/ru/ibutton/protocols) — Dallas DS1990/1992/1996/1971/1420, generic 1-Wire, Cyfral,
  Metakom.
- [Фаззер](/ru/ibutton/fuzzer) — что прошивка поставляет для iButton-фаззера.
- [Формат файла](/ru/ibutton/file-format) — файлы `.ibtn`.

## Файлы

| Путь | Содержимое |
|---|---|
| `/ext/ibutton/*.ibtn` | Сохранённые ключи (префикс имени по умолчанию `iBtn`) |
| `/ext/ibutton/.ibutton.settings` | Настройка Write Blanks |

::: warning
Копируйте и эмулируйте только свои ключи или те, на тестирование которых у вас есть разрешение.
:::
