---
title: "JavaScript: flipper"
sidebarTitle: "JS: flipper"
order: 300
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_flipper.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_flipper.c]
sources: [unleashed-docs, unleashed-src]
---
# Модуль flipper

Значення та методи для отримання інформації про пристрій. Спочатку завантажте модуль:

```js
let flipper = require("flipper");
```

## Значення

### firmwareVendor
Рядок із назвою прошивки, встановленої на пристрої. Офіційна прошивка повідомляє `"flipperdevices"`.

::: tip Unleashed
Unleashed повідомляє `"unleashed"`.
:::

**Не** використовуйте це значення, щоб перевірити наявність певної можливості. Для цього є [функції перевірки сумісності SDK](/ua/dev/js-builtin#sdk-compatibility).

### jsSdkVersion
Версія JavaScript SDK. Так само **не** використовуйте її для перевірки можливостей — див. [Сумісність SDK](/ua/dev/js-builtin#sdk-compatibility).

## Методи

### getModel()
Повертає модель пристрою.

```js
flipper.getModel(); // "Flipper Zero"
```

### getName()
Повертає ім’я віртуального дельфіна (ім’я пристрою).

```js
flipper.getName(); // "Fur1pp44"
```

### getBatteryCharge()
Повертає заряд акумулятора у відсотках.

```js
flipper.getBatteryCharge(); // 100
```
