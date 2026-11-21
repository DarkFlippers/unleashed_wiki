---
title: "JavaScript: вбудовані функції"
sidebarTitle: "JS: вбудовані функції"
order: 250
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_builtin.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/js_modules.c]
sources: [unleashed-docs, unleashed-src]
---
# Вбудовані функції

Ці функції та об’єкти доступні в будь-якому скрипті без `require()`.

## Глобальні функції

### require()
Завантажує плагін модуля. Див. [Використання JS-модулів](/ua/dev/js-modules).

- **Параметри:** назва модуля

```js
let serial = require("serial"); // Load "serial" module
```

### delay()
- **Параметри:** затримка в мс

```js
delay(500); // Delay for 500ms
```

### print()
Виводить повідомлення в екранну консоль (або в CLI, якщо скрипт запущено з CLI).

- **Параметри:** будь-яка кількість аргументів типу String, Number, Bool або `undefined`

```js
print("string1", "string2", 123);
```

### об’єкт console
Те саме, що `print()`, але пише **лише в послідовну консоль (журнал)** з відповідним рівнем логування:

- `console.log()`
- `console.warn()`
- `console.error()`
- `console.debug()`

### load()
Виконує файл JS і повертає значення з нього.

- **Параметри:**
  - шлях до файлу;
  - необов’язковий об’єкт, який буде використано як глобальна область видимості під час виконання файлу.

```js
load("/ext/apps/Scripts/script.js");
```

### chr()
Перетворює код символу ASCII в рядок.

```js
chr(65); // "A"
```

### die()
Завершує скрипт із заданим повідомленням.

```js
die("Some error occurred");
```

### parseInt()
Перетворює рядок у число; основу системи числення можна вказати.

```js
parseInt("123"); // 123
parseInt("7b", 16); // 123
```

## Number

### Number.toString()
Перетворює число в рядок; основу системи числення можна вказати.

```js
let num = 123;
num.toString(); // "123"
num.toString(16); // "0x7b"
```

## ArrayBuffer

**Поля:** `byteLength` — довжина буфера в байтах.

### ArrayBuffer.slice()
Створює `ArrayBuffer` із частиною вмісту буфера.

- **Параметри:** початковий індекс; необов’язковий кінцевий індекс (не включається).

```js
Uint8Array([1, 2, 3]).buffer.slice(0, 1) // ArrayBuffer([1])
```

## DataView (типізовані масиви)

Обгортки навколо `ArrayBuffer` із фіксованим типом елемента:

- `Uint8Array`, `Int8Array`
- `Uint16Array`, `Int16Array`
- `Uint32Array`, `Int32Array`

**Поля:**

- `byteLength`: довжина буфера в байтах;
- `length`: довжина буфера в типізованих елементах;
- `buffer`: базовий `ArrayBuffer`.

## Array

**Поля:** `length` — кількість елементів.

### Array.splice()
Видаляє елементи з масиву й повертає їх як новий масив.

- **Параметри:** початковий індекс; необов’язкова кількість елементів.

```js
let arr = [1, 2, 3];
arr.splice(1); // [2, 3]
arr; // [1]
```

### Array.push()
Додає значення в кінець масиву.

```js
let arr = [1, 2];
arr.push(3);
arr; // [1, 2, 3]
```

## String

**Поля:** `length` — кількість символів (байтів).

### String.charCodeAt()
Повертає код символу за індексом.

```js
"A".charCodeAt(0) // 65
```

### String.at()
Те саме, що `String.charCodeAt()`.

### String.indexOf()
Повертає індекс першого входження підрядка або `-1`, якщо його не знайдено.

- **Параметри:** підрядок для пошуку; необов’язковий початковий індекс.

```js
"Example".indexOf("amp") // 2
```

### String.slice()
Повертає підрядок між двома індексами.

- **Параметри:** початковий індекс; необов’язковий кінцевий індекс (не включається).

```js
"Example".slice(2) // "ample"
```

### String.toUpperCase()

```js
"Example".toUpperCase() // "EXAMPLE"
```

### String.toLowerCase()

```js
"Example".toLowerCase() // "example"
```

## Шляхи до скриптів

### __dirname
Шлях до каталогу, у якому лежить поточний скрипт.

```js
print(__dirname); // /ext/apps/Scripts
```

### __filename
Шлях до файлу поточного скрипта.

```js
print(__filename); // /ext/apps/Scripts/path.js
```

## Сумісність SDK {#sdk-compatibility}

Скрипти можуть перевірити, яку версію JS SDK і які додаткові можливості надає прошивка. **Не** використовуйте для цього `flipper.firmwareVendor` чи `flipper.jsSdkVersion` — користуйтеся функціями нижче.

У поточній версії Unleashed версія JS SDK — **1.0**.

### sdkCompatibilityStatus()
Перевіряє сумісність скрипта з JS SDK прошивки.

- **Повертає:**
  - `"compatible"`, якщо скрипт і JS SDK сумісні;
  - `"firmwareTooOld"`, якщо очікувана основна версія більша за версію прошивки або очікувана проміжна версія більша за версію прошивки;
  - `"firmwareTooNew"`, якщо очікувана основна версія менша за версію прошивки.

```js
sdkCompatibilityStatus(0, 3); // "compatible"
```

### isSdkCompatible()
Та сама перевірка, але повертає логічне значення.

```js
isSdkCompatible(0, 3); // true
```

### checkSdkCompatibility()
Якщо версії несумісні, запитує користувача, чи продовжувати виконання скрипта. Якщо сумісні — не робить нічого.

```js
checkSdkCompatibility(0, 3);
```

### doesSdkSupport()
Перевіряє, чи інтерпретатор підтримує **усі** перелічені додаткові можливості.

```js
doesSdkSupport(["gui-widget"]); // true
```

### checkSdkFeatures()
Та сама перевірка, але якщо якихось можливостей немає — запитує користувача, чи продовжувати.

```js
checkSdkFeatures(["gui-widget"]);
```

::: tip Unleashed
Назви можливостей, які підтримує Unleashed: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, а також додаткові модулі Unleashed — `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`. Див. [огляд JavaScript](/ua/dev/js-about#unleashed-extras).
:::

Типовий шаблон для необов’язкової можливості:

```js
if (doesSdkSupport(["subghz"])) {
    let subghz = require("subghz");
    // ...
}
```
