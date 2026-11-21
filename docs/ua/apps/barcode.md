---
title: Barcode Generator
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BarcodeGenerator.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Barcode Generator

**Barcode Generator** малює штрихкод на екрані Flipper, щоб сканер міг прочитати його просто з дисплея.
Оригінальний застосунок від [McAzzaMan](https://github.com/McAzzaMan/flipperzero-firmware/tree/UPC-A_Barcode_Generator/applications/barcode_generator)
генерує штрихкоди **UPC-A** (12 цифр).

::: tip Unleashed
Barcode Generator не є системним застосунком: він входить до [наборів застосунків](/ua/apps/catalog#base-and-extra-packs)
від спільноти (або встановіть його самостійно, див. [Застосунки на SD-карті](/ua/apps/sd-card-apps)). Документація
Unleashed описує оригінальну версію з UPC-A; версія з поточного набору може підтримувати більше типів штрихкодів,
тож дивіться на її власні екрани.
:::

![Barcode Generator](/img/remote/2c7ed96cc46ad024.png)

## Використання

1. Відкрийте застосунок через `Main Menu → Apps` (шукайте у папці його категорії).
2. Натисніть <kbd>OK</kbd>, щоб перейти в **режим редагування**.
3. <kbd>←</kbd> / <kbd>→</kbd> переходять до цифри, яку потрібно змінити.
4. <kbd>↑</kbd> / <kbd>↓</kbd> змінюють значення цифри.
5. Натисніть <kbd>OK</kbd> ще раз, щоб вийти з режиму редагування. Штрихкод буде перемальовано для нового номера.
6. Піднесіть екран Flipper до сканера. Якщо сканер не справляється, збільште яскравість підсвічування.

![Режим редагування](/img/remote/612b2014b71a93e4.png)

::: info Контрольна цифра UPC-A
Остання з 12 цифр UPC-A — контрольна, вона обчислюється з решти 11. Якщо сканер відкидає код, найімовірніше
контрольна цифра не відповідає решті номера.
:::

## Пов’язані сторінки

- [Застосунки у складі Unleashed](/ua/apps/catalog)
- [Multi Converter](/ua/apps/multi-converter)
