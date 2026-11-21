---
title: Multi Converter
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MultiConverter.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Multi Converter

**Multi Converter** від [theisolinearchip](https://github.com/theisolinearchip/flipperzero_stuff/tree/main/applications/multi_converter) —
це конвертер одиниць: введіть значення в одних одиницях і побачте його в інших. Він виріс із раннішого Dec/Hex
Converter того самого автора.

::: tip Unleashed
Multi Converter входить до [наборів застосунків](/ua/apps/catalog#base-and-extra-packs) спільноти, а не до самої
прошивки.
:::

![Multi Converter](/img/remote/283b5cf67616cbaa.png)

## Підтримувані перетворення

| Група | Одиниці |
|---|---|
| Системи числення | Decimal, Hexadecimal, Binary (десяткова, шістнадцяткова, двійкова) |
| Температура | Celsius, Fahrenheit, Kelvin |
| Довжина | Kilometers, Meters, Centimeters, Miles, Feet, Inches (км, м, см, милі, фути, дюйми) |
| Кут | Degree, Radian (градуси, радіани) |

## Режим відображення (введення значення)

На екранній клавіатурі є клавіші від `0` до `F`. Клавіші, що не мають сенсу для поточної вихідної одиниці,
вимкнені (наприклад, `2`-`F` для двійкової системи).

| Клавіша | Дія |
|---|---|
| `0`-`F` | ввести цифру |
| довге натискання `0` | перемкнути **від’ємне** значення |
| довге натискання `1` | вставити **десяткову крапку** (лише там, де одиниця це дозволяє) |
| `<` | видалити останній символ |
| `#` | відкрити **Unit Select Mode** |

Переміщайтеся по клавіатурі стрілками й натискайте <kbd>OK</kbd> на клавіші. Результат у цільових одиницях
показується на екрані.

![Вибір одиниць](/img/remote/bedbc21af3d64be7.png)

## Unit Select Mode

1. Натисніть `#`.
2. <kbd>←</kbd> / <kbd>→</kbd> перемикають між **вихідною** та **цільовою** одиницею. Список цільових одиниць
   залежить від вибраної вихідної (перетворювати можна лише в межах однієї групи).
3. <kbd>OK</kbd> зберігає й повертає в режим відображення; <kbd>Back</kbd> повертає, не змінюючи одиниць.

## Відомі обмеження

- Дуже великі перетворення (милі в сантиметри тощо) можуть показувати невеликі відхилення в десяткових знаках
  через обмеження точності.
- Перевірки переповнення базові: дуже довгі числа можуть не вміститися в буфер дисплея.
- Позначки довгого натискання для від’ємного значення та десяткової крапки дрібні на екрані, їх легко не помітити.

## Додавання одиниць (для розробників)

1. Додайте одиницю до перелічення `MultiConverterUnitType` у `multi_converter_definitions.h` (значення перелічення —
   це індекси масиву).
2. Збільште `MULTI_CONVERTER_AVAILABLE_UNITS` у `multi_converter_units.h`.
3. Напишіть функцію **convert** і перевірку **allowed** (чи можна перетворити цю одиницю в ту) у
   `multi_converter_units.h` / `.c`.
4. Додайте структуру `MultiConverterUnit` для нової одиниці.
5. Додайте її до масиву `multi_converter_available_units`. Застосунок підхопить її автоматично.

## Пов’язані сторінки

- [Застосунки у складі Unleashed](/ua/apps/catalog)
- [Barcode Generator](/ua/apps/barcode)
