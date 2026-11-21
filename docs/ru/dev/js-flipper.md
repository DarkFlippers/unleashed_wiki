---
title: "JavaScript: flipper"
sidebarTitle: "JS: flipper"
order: 300
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_flipper.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_flipper.c]
sources: [unleashed-docs, unleashed-src]
---
# Модуль Flipper

Значения и методы для получения информации об устройстве. Сначала подключите модуль:

```js
let flipper = require("flipper");
```

## Значения

### firmwareVendor
Строка с названием прошивки на устройстве. Официальная прошивка возвращает `"flipperdevices"`.

::: tip Unleashed
Unleashed возвращает `"unleashed"`.
:::

**Не используйте** это значение для проверки наличия возможностей. Для этого есть [функции совместимости SDK](/ru/dev/js-builtin#sdk-compatibility).

### jsSdkVersion
Версия JavaScript SDK. Её тоже **не используйте** для проверки возможностей, см. [совместимость SDK](/ru/dev/js-builtin#sdk-compatibility).

## Методы

### getModel()
Возвращает модель устройства.

```js
flipper.getModel(); // "Flipper Zero"
```

### getName()
Возвращает имя виртуального дельфина (имя устройства).

```js
flipper.getName(); // "Fur1pp44"
```

### getBatteryCharge()
Возвращает заряд батареи в процентах.

```js
flipper.getBatteryCharge(); // 100
```
