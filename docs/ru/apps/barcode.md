---
title: Barcode Generator
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BarcodeGenerator.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Barcode Generator

**Barcode Generator** рисует штрихкод на экране Флиппера, чтобы сканер мог считать его прямо с дисплея.
Оригинальное приложение от [McAzzaMan](https://github.com/McAzzaMan/flipperzero-firmware/tree/UPC-A_Barcode_Generator/applications/barcode_generator)
генерирует штрихкоды **UPC-A** (12 цифр).

::: tip Unleashed
Barcode Generator — не системное приложение: оно идёт в комьюнити [паках приложений](/ru/apps/catalog)
(или установите его сами, см. [Приложения на SD-карте](/ru/apps/sd-card-apps)). Документация Unleashed описывает
оригинальную версию с UPC-A; версия в текущем паке может поддерживать больше типов штрихкодов, так что смотрите её
собственные экраны.
:::

![Barcode Generator](/img/remote/2c7ed96cc46ad024.png)

## Использование

1. Откройте приложение из `Main Menu → Apps` (ищите в папке его категории).
2. Нажмите <kbd>OK</kbd>, чтобы войти в **режим редактирования**.
3. <kbd>←</kbd> / <kbd>→</kbd> — переход к цифре, которую нужно изменить.
4. <kbd>↑</kbd> / <kbd>↓</kbd> — изменение значения цифры.
5. Снова нажмите <kbd>OK</kbd>, чтобы выйти из режима редактирования. Штрихкод перерисуется под новое число.
6. Поднесите экран Флиппера к сканеру. Если сканер плохо считывает, прибавьте подсветку.

![Режим редактирования](/img/remote/612b2014b71a93e4.png)

::: info Контрольная цифра UPC-A
Последняя из 12 цифр UPC-A — контрольная, она вычисляется из остальных 11. Если сканер не принимает код, скорее всего
контрольная цифра не соответствует остальной части номера.
:::

## Связанные страницы

- [Приложения в составе Unleashed](/ru/apps/catalog)
- [Multi Converter](/ru/apps/multi-converter)
