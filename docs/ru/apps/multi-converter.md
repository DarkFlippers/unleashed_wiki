---
title: Multi Converter
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MultiConverter.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Multi Converter

**Multi Converter** от [theisolinearchip](https://github.com/theisolinearchip/flipperzero_stuff/tree/main/applications/multi_converter)
— конвертер единиц: вводите значение в одной единице и видите его в другой. Вырос из более раннего конвертера
автора Dec/Hex Converter.

::: tip Unleashed
Multi Converter идёт в комьюнити [паках приложений](/ru/apps/catalog), а не в самой прошивке.
:::

![Multi Converter](/img/remote/283b5cf67616cbaa.png)

## Поддерживаемые преобразования

| Группа | Единицы |
|---|---|
| Системы счисления | Decimal, Hexadecimal, Binary (десятичная, шестнадцатеричная, двоичная) |
| Температура | Celsius, Fahrenheit, Kelvin |
| Длина | Kilometers, Meters, Centimeters, Miles, Feet, Inches (км, м, см, мили, футы, дюймы) |
| Угол | Degree, Radian (градусы, радианы) |

## Режим отображения (ввод значения)

На экранной клавиатуре есть клавиши от `0` до `F`. Клавиши, не имеющие смысла для текущей исходной единицы,
отключены (например, `2`-`F` для двоичной системы).

| Клавиша | Действие |
|---|---|
| `0`-`F` | ввести цифру |
| долгое нажатие `0` | переключить **отрицательное** значение |
| долгое нажатие `1` | поставить **десятичную точку** (только если единица это допускает) |
| `<` | удалить последний символ |
| `#` | открыть **Unit Select Mode** (выбор единиц) |

Перемещайтесь по клавиатуре стрелками и нажимайте <kbd>OK</kbd> на клавише. Результат в целевой единице
отображается на экране.

![Выбор единиц](/img/remote/bedbc21af3d64be7.png)

## Unit Select Mode (выбор единиц)

1. Нажмите `#`.
2. <kbd>←</kbd> / <kbd>→</kbd> переключают между **исходной** (origin) и **целевой** (destination) единицей. Список
   целевых единиц зависит от выбранной исходной (конвертировать можно только внутри группы).
3. <kbd>OK</kbd> сохраняет и возвращает в режим отображения; <kbd>Back</kbd> возвращает без изменения единиц.

## Известные ограничения

- При очень больших преобразованиях (мили в сантиметры и т.п.) возможны небольшие отклонения в дробной части из-за
  ограничений точности.
- Проверки переполнения базовые: очень длинные числа могут не поместиться в буфер отображения.
- Отметки отрицательного числа и десятичной точки (долгое нажатие) на экране мелкие, их легко не заметить.

## Добавление единиц (для разработчиков)

1. Добавьте единицу в enum `MultiConverterUnitType` в `multi_converter_definitions.h` (значения enum используются как
   индексы массива).
2. Увеличьте `MULTI_CONVERTER_AVAILABLE_UNITS` в `multi_converter_units.h`.
3. Напишите функцию **преобразования** и проверку **допустимости** (может ли эта единица конвертироваться в ту) в
   `multi_converter_units.h` / `.c`.
4. Добавьте структуру `MultiConverterUnit` для новой единицы.
5. Добавьте её в массив `multi_converter_available_units`. Приложение подхватит её автоматически.

## Связанные страницы

- [Приложения в составе Unleashed](/ru/apps/catalog)
- [Barcode Generator](/ru/apps/barcode)
