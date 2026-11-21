---
title: "JavaScript: BadUSB"
sidebarTitle: "JS: badusb"
order: 290
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_badusb.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_badusb.c]
sources: [unleashed-docs, unleashed-src]
---
# Модуль badusb

Модуль `badusb` перетворює Flipper Zero на USB-клавіатуру (HID), якою керує JavaScript. Це гнучка альтернатива класичним [файлам BadUSB у форматі DuckyScript](/ua/badusb/script-format): ви отримуєте змінні, цикли й усі інші JS-модулі (GUI, storage, serial) в одному скрипті.

```js
let badusb = require("badusb");
```

::: warning
Використовуйте це лише на власних комп’ютерах або там, де у вас є дозвіл на тестування.
:::

Приклад скрипта: `/ext/apps/Scripts/js_examples/badusb_demo.js`.

## Методи

### setup()
Запускає USB HID — за потреби з власними параметрами. Викликайте його **перед усіма іншими методами**.

**Параметри:** необов’язковий об’єкт конфігурації:

- `vid`, `pid` (number): VID і PID; якщо використовуються, то обидва обов’язкові;
- `mfrName` (string): назва виробника (не більше ніж 32 символи ASCII), необов’язковий;
- `prodName` (string): назва продукту (не більше ніж 32 символи ASCII), необов’язковий;
- `layoutPath` (string): шлях до файлу розкладки клавіатури, необов’язковий.

```js
// Start USB HID with default parameters
badusb.setup();
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer and product strings not defined
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB }); 
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer string = "Flipper Devices", product string = "Flipper Zero"
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB, mfrName: "Flipper Devices", prodName: "Flipper Zero" });
```

Розкладки клавіатури — ті самі файли `.kl`, що використовує застосунок BadUSB (лежать у `/ext/badusb/assets/layouts/`), наприклад `layoutPath: "/ext/badusb/assets/layouts/de-DE.kl"`.

### isConnected()
Повертає стан USB-з’єднання.

```js
if (badusb.isConnected()) {
    // Do something
} else {
    // Show an error
}
```

### press()
Натискає й відпускає клавішу або комбінацію клавіш.

**Параметри:** назви клавіш чи модифікаторів або їхні коди. Див. [перелік назв клавіш](#key-names).

```js
badusb.press("a"); // Press "a" key
badusb.press("A"); // SHIFT + "a"
badusb.press("CTRL", "a"); // CTRL + "a"
badusb.press("CTRL", "SHIFT", "ESC"); // CTRL + SHIFT + ESC combo
badusb.press(98); // Press key with HID code (dec) 98 (Numpad 0 / Insert)
badusb.press(0x47); // Press key with HID code (hex) 0x47 (Scroll lock)
```

### hold()
Утримує клавішу натиснутою. Одночасно можна утримувати до 5 клавіш (не враховуючи модифікаторів).

**Параметри:** такі самі, як у `press()`.

```js
badusb.hold("a"); // Press and hold "a" key
badusb.hold("CTRL", "v"); // Press and hold CTRL + "v" combo
```

### release()
Відпускає раніше затиснуту клавішу. Виклик **без параметрів** відпускає всі клавіші.

**Параметри:** такі самі, як у `press()`.

```js
badusb.release(); // Release all keys
badusb.release("a"); // Release "a" key
```

### print()
Набирає рядок.

**Параметри:** рядок; *(необов’язково)* затримка між натисканнями клавіш у мс.

```js
badusb.print("Hello, world!"); // print "Hello, world!"
badusb.print("Hello, world!", 100); // Add 100ms delay between key presses
```

### println()
Те саме, що `print()`, але після рядка натискається <kbd>ENTER</kbd>.

```js
badusb.println("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### altPrint()
Набирає рядок методом **Alt+Numpad**, який працює незалежно від розкладки клавіатури на хості. **Лише для Windows.**

**Параметри:** рядок; *(необов’язково)* затримка між натисканнями клавіш у мс.

```js
badusb.altPrint("Hello, world!"); // print "Hello, world!"
badusb.altPrint("Hello, world!", 100); // Add 100ms delay between key presses
```

### altPrintln()
Те саме, що `altPrint()`, але після рядка натискається <kbd>ENTER</kbd>.

```js
badusb.altPrintln("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### quit() {#quit}
Звільняє USB. Необов’язковий, але дає скрипту змогу перейти в інший режим USB — наприклад, передати керування модулю `usbdisk`.

```js
badusb.quit();
usbdisk.start(...)
```

::: tip Unleashed
`usbdisk` (емуляція USB-накопичувача) — JS-модуль, який є лише в Unleashed; див. [огляд JavaScript](/ua/dev/js-about#unleashed-extras).
:::

## Назви клавіш {#key-names}

### Клавіші-модифікатори

| Назва |
|---|
| CTRL |
| SHIFT |
| ALT |
| GUI |

### Спеціальні клавіші

| Назва | Примітки |
|---|---|
| DOWN | Стрілка вниз |
| LEFT | Стрілка ліворуч |
| RIGHT | Стрілка праворуч |
| UP | Стрілка вгору |
| ENTER | |
| DELETE | |
| BACKSPACE | |
| END | |
| HOME | |
| ESC | |
| INSERT | |
| PAGEUP | |
| PAGEDOWN | |
| CAPSLOCK | |
| NUMLOCK | |
| SCROLLLOCK | |
| PRINTSCREEN | |
| PAUSE | Клавіша Pause/Break |
| SPACE | |
| TAB | |
| MENU | Клавіша контекстного меню |
| Fx | Клавіші F1-F24 |
| NUMx | Клавіші NUM0-NUM9 |

## Пов’язані сторінки

- [Використання BadUSB](/ua/badusb/usage) і [формат скриптів](/ua/badusb/script-format)
- [Цикл подій](/ua/dev/js-event-loop), [GUI](/ua/dev/js-gui) — для інтерактивних меню вибору payload
