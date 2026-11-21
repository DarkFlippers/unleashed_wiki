---
title: iButton
original: [https://docs.flipper.net/zero/ibutton, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# iButton

iButton («touch memory», у країнах СНД такі ключі часто називають *таблетками*) — це ключ у невеликому стальному
корпусі, який зчитують дотиком до зчитувача. Більшість із них працює за протоколом Dallas **1-Wire**; у домофонних
системах використовують також ключі **Cyfral** і **Metakom**. Flipper Zero вміє читати, зберігати, емулювати та
записувати такі ключі.

## Апаратна частина

Модуль iButton — це контактний майданчик із трьома пружинними pogo-пінами на платі iButton.

- Два крайні піни — дані (підключені до **піна GPIO 17**), середній пін — **земля**.
- **Читання / запис ключа**: ключ прикладають до **плоскої частини** майданчика — лівий пін даних + середній пін землі.
- **Емуляція для зчитувача**: до зчитувача притискають **виступаючу частину** майданчика — правий пін даних +
  середня земля.
- Якщо земля не дістає до обідка зчитувача, скористайтеся двома дротами: GPIO **17** (дані) і GPIO **8, 11 або 18**
  (земля).

## Головне меню

`Main Menu → iButton`:

![Меню iButton: Read, Saved, Add Manually і Settings](/screens/ibutton/menu.png)

| Пункт | Що робить | Сторінка |
|---|---|---|
| **Read** | Визначає тип ключа та читає його ID (а для DS1992/1996/1971 — і пам’ять) | [Читання](/ua/ibutton/read) |
| **Saved** | Перегляд `/ext/ibutton/` — емуляція, запис, редагування, перейменування, видалення | [Читання](/ua/ibutton/read), [Запис](/ua/ibutton/write) |
| **Add Manually** | Створити ключ за протоколом і hex-ID | [Додавання вручну](/ua/ibutton/add-manually) |
| **Settings** | **Write Blanks** — на які типи заготовок дозволено запис | [Запис](/ua/ibutton/write) |

::: tip Unleashed
Порівняно з офіційною документацією в Unleashed є сторінка **Settings → Write Blanks** (RW1990.1, RW1990.2, TM2004,
TM01x), під час запису видно, яка заготовка пробується і на яку записалося, ключі **Cyfral і Metakom** можна писати
на заготовки **TM01x**, а також є підтримка **DS1420**. У ReadMe згадано й плагін iButton Fuzzer.
:::

## Сторінки розділу

- [Читання ключів](/ua/ibutton/read) — читання, збереження, емуляція, помилки CRC.
- [Запис на заготовки](/ua/ibutton/write) — RW1990, TM2004, TM01x; Write ID проти Full Write on Same Type.
- [Додавання вручну](/ua/ibutton/add-manually) — створення ключів за ID.
- [Підтримувані протоколи](/ua/ibutton/protocols) — Dallas DS1990/1992/1996/1971/1420, універсальний 1-Wire, Cyfral,
  Metakom.
- [Фазер](/ua/ibutton/fuzzer) — що прошивка постачає для застосунку iButton Fuzzer.
- [Формат файлів](/ua/ibutton/file-format) — файли `.ibtn`.

## Файли

| Шлях | Вміст |
|---|---|
| `/ext/ibutton/*.ibtn` | Збережені ключі (типовий префікс назви — `iBtn`) |
| `/ext/ibutton/.ibutton.settings` | Налаштування Write Blanks |

::: warning
Копіюйте й емулюйте лише свої ключі або ті, на тестування яких у вас є дозвіл.
:::
