---
title: "JavaScript: встроенные функции"
sidebarTitle: "JS: встроенные функции"
order: 250
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_builtin.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/js_modules.c]
sources: [unleashed-docs, unleashed-src]
---
# Встроенные функции

Эти функции и объекты доступны в любом скрипте без `require()`.

## Глобальные функции

### require()
Загружает плагин модуля. См. [Использование модулей](/ru/dev/js-modules).

- **Параметры:** имя модуля

```js
let serial = require("serial"); // Load "serial" module
```

### delay()
- **Параметры:** задержка в мс

```js
delay(500); // Delay for 500ms
```

### print()
Выводит сообщение в экранную консоль (или в CLI, если скрипт запущен из CLI).

- **Параметры:** любое количество аргументов типов String, Number, Bool или `undefined`

```js
print("string1", "string2", 123);
```

### Объект console
То же, что `print()`, но пишет **только в последовательную консоль (лог)** с соответствующим уровнем:

- `console.log()`
- `console.warn()`
- `console.error()`
- `console.debug()`

### load()
Выполняет JS-файл и возвращает из него значение.

- **Параметры:**
  - путь к файлу;
  - необязательный объект, который используется как глобальная область видимости при выполнении файла.

```js
load("/ext/apps/Scripts/script.js");
```

### chr()
Преобразует ASCII-код символа в строку.

```js
chr(65); // "A"
```

### die()
Завершает скрипт с заданным сообщением.

```js
die("Some error occurred");
```

### parseInt()
Преобразует строку в число, основание системы счисления необязательно.

```js
parseInt("123"); // 123
parseInt("7b", 16); // 123
```

## Number

### Number.toString()
Преобразует число в строку, основание необязательно.

```js
let num = 123;
num.toString(); // "123"
num.toString(16); // "0x7b"
```

## ArrayBuffer

**Поля:** `byteLength` — длина буфера в байтах.

### ArrayBuffer.slice()
Создаёт `ArrayBuffer` с частью буфера.

- **Параметры:** начальный индекс; необязательный конечный индекс (не включается).

```js
Uint8Array([1, 2, 3]).buffer.slice(0, 1) // ArrayBuffer([1])
```

## DataView (типизированные массивы)

Обёртки над `ArrayBuffer` с фиксированным типом элемента:

- `Uint8Array`, `Int8Array`
- `Uint16Array`, `Int16Array`
- `Uint32Array`, `Int32Array`

**Поля:**

- `byteLength` — длина буфера в байтах;
- `length` — длина в типизированных элементах;
- `buffer` — исходный `ArrayBuffer`.

## Array

**Поля:** `length` — количество элементов.

### Array.splice()
Удаляет элементы из массива и возвращает их новым массивом.

- **Параметры:** начальный индекс; необязательное количество элементов.

```js
let arr = [1, 2, 3];
arr.splice(1); // [2, 3]
arr; // [1]
```

### Array.push()
Добавляет значение в конец массива.

```js
let arr = [1, 2];
arr.push(3);
arr; // [1, 2, 3]
```

## String

**Поля:** `length` — количество символов (байтов).

### String.charCodeAt()
Возвращает код символа по индексу.

```js
"A".charCodeAt(0) // 65
```

### String.at()
То же, что `String.charCodeAt()`.

### String.indexOf()
Возвращает индекс первого вхождения подстроки или `-1`, если не найдено.

- **Параметры:** искомая подстрока; необязательный индекс начала поиска.

```js
"Example".indexOf("amp") // 2
```

### String.slice()
Возвращает подстроку между двумя индексами.

- **Параметры:** начальный индекс; необязательный конечный индекс (не включается).

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

## Пути скрипта

### __dirname
Путь к папке текущего скрипта.

```js
print(__dirname); // /ext/apps/Scripts
```

### __filename
Путь к файлу текущего скрипта.

```js
print(__filename); // /ext/apps/Scripts/path.js
```

## Совместимость SDK {#sdk-compatibility}

Скрипт может проверить, какую версию JS SDK и какие дополнительные фичи предоставляет прошивка. **Не используйте** для этого `flipper.firmwareVendor` или `flipper.jsSdkVersion`, для этого есть функции ниже.

В текущем Unleashed версия JS SDK — **1.0**.

### sdkCompatibilityStatus()
Проверяет совместимость скрипта и JS SDK прошивки.

- **Возвращает:**
  - `"compatible"`, если скрипт и JS SDK совместимы;
  - `"firmwareTooOld"`, если ожидаемая major-версия больше версии прошивки или ожидаемая minor-версия больше версии прошивки;
  - `"firmwareTooNew"`, если ожидаемая major-версия меньше версии прошивки.

```js
sdkCompatibilityStatus(0, 3); // "compatible"
```

### isSdkCompatible()
Та же проверка, но возвращает boolean.

```js
isSdkCompatible(0, 3); // true
```

### checkSdkCompatibility()
Если версии несовместимы, спрашивает пользователя, продолжать ли выполнение. Если совместимы, ничего не делает.

```js
checkSdkCompatibility(0, 3);
```

### doesSdkSupport()
Проверяет, поддерживает ли интерпретатор **все** перечисленные фичи.

```js
doesSdkSupport(["gui-widget"]); // true
```

### checkSdkFeatures()
Та же проверка, но если чего-то не хватает, спрашивает пользователя, продолжать ли.

```js
checkSdkFeatures(["gui-widget"]);
```

::: tip Unleashed
Фичи, которые поддерживает Unleashed: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras` и дополнительные модули Unleashed `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`. См. [обзор JavaScript](/ru/dev/js-about#unleashed-extras).
:::

Типичный шаблон для необязательной фичи:

```js
if (doesSdkSupport(["subghz"])) {
    let subghz = require("subghz");
    // ...
}
```
