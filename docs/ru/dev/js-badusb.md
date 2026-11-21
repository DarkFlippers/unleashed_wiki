---
title: "JavaScript: BadUSB"
sidebarTitle: "JS: badusb"
order: 290
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_badusb.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_badusb.c]
sources: [unleashed-docs, unleashed-src]
---
# Модуль BadUSB

Модуль `badusb` превращает Flipper Zero в USB-клавиатуру (HID), управляемую из JavaScript. Это программируемая альтернатива классическим [скриптам BadUSB на DuckyScript](/ru/badusb/script-format): в одном скрипте доступны переменные, циклы и остальные JS-модули (GUI, storage, serial).

```js
let badusb = require("badusb");
```

::: warning
Используйте только на своих компьютерах или там, где вам разрешено тестировать.
:::

Пример: `/ext/apps/Scripts/js_examples/badusb_demo.js`.

## Методы

### setup()
Запускает USB HID, при желании с собственными параметрами. Вызывается **до всех остальных методов**.

**Параметры:** необязательный объект конфигурации:

- `vid`, `pid` (number) — VID и PID; если указаны, то оба обязательны;
- `mfrName` (string) — имя производителя (до 32 ASCII-символов), необязательно;
- `prodName` (string) — имя продукта (до 32 ASCII-символов), необязательно;
- `layoutPath` (string) — путь к файлу раскладки клавиатуры, необязательно.

```js
// Start USB HID with default parameters
badusb.setup();
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer and product strings not defined
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB }); 
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer string = "Flipper Devices", product string = "Flipper Zero"
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB, mfrName: "Flipper Devices", prodName: "Flipper Zero" });
```

Раскладки — те же файлы `.kl`, что использует приложение BadUSB (в `/ext/badusb/assets/layouts/`), например `layoutPath: "/ext/badusb/assets/layouts/de-DE.kl"`.

### isConnected()
Возвращает состояние USB-подключения.

```js
if (badusb.isConnected()) {
    // Do something
} else {
    // Show an error
}
```

### press()
Нажимает и отпускает клавишу или сочетание клавиш.

**Параметры:** имена клавиш и модификаторов или коды клавиш. См. [список имён клавиш](#key-names).

```js
badusb.press("a"); // Press "a" key
badusb.press("A"); // SHIFT + "a"
badusb.press("CTRL", "a"); // CTRL + "a"
badusb.press("CTRL", "SHIFT", "ESC"); // CTRL + SHIFT + ESC combo
badusb.press(98); // Press key with HID code (dec) 98 (Numpad 0 / Insert)
badusb.press(0x47); // Press key with HID code (hex) 0x47 (Scroll lock)
```

### hold()
Удерживает клавишу. Одновременно можно держать до 5 клавиш (не считая модификаторов).

**Параметры:** как у `press()`.

```js
badusb.hold("a"); // Press and hold "a" key
badusb.hold("CTRL", "v"); // Press and hold CTRL + "v" combo
```

### release()
Отпускает ранее удержанную клавишу. Вызов **без параметров** отпускает все клавиши.

**Параметры:** как у `press()`.

```js
badusb.release(); // Release all keys
badusb.release("a"); // Release "a" key
```

### print()
Набирает строку.

**Параметры:** строка; *(необязательно)* задержка между нажатиями в мс.

```js
badusb.print("Hello, world!"); // print "Hello, world!"
badusb.print("Hello, world!", 100); // Add 100ms delay between key presses
```

### println()
То же, что `print()`, плюс нажатие <kbd>ENTER</kbd> в конце.

```js
badusb.println("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### altPrint()
Набирает строку методом **Alt+Numpad**, который не зависит от раскладки на компьютере. **Только для Windows.**

**Параметры:** строка; *(необязательно)* задержка между нажатиями в мс.

```js
badusb.altPrint("Hello, world!"); // print "Hello, world!"
badusb.altPrint("Hello, world!", 100); // Add 100ms delay between key presses
```

### altPrintln()
То же, что `altPrint()`, плюс <kbd>ENTER</kbd> в конце.

```js
badusb.altPrintln("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### quit() {#quit}
Освобождает USB. Необязательно, но позволяет переключиться в другой режим USB в том же скрипте, например на модуль `usbdisk`.

```js
badusb.quit();
usbdisk.start(...)
```

::: tip Unleashed
`usbdisk` (эмуляция USB-накопителя) — JS-модуль, который есть только в Unleashed; см. [обзор JavaScript](/ru/dev/js-about#unleashed-extras).
:::

## Имена клавиш {#key-names}

### Модификаторы

| Имя |
|---|
| CTRL |
| SHIFT |
| ALT |
| GUI |

### Специальные клавиши

| Имя | Примечание |
|---|---|
| DOWN | Стрелка вниз |
| LEFT | Стрелка влево |
| RIGHT | Стрелка вправо |
| UP | Стрелка вверх |
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
| PAUSE | Pause/Break |
| SPACE | |
| TAB | |
| MENU | Клавиша контекстного меню |
| Fx | F1–F24 |
| NUMx | NUM0–NUM9 |

## См. также

- [Использование BadUSB](/ru/badusb/usage) и [формат скриптов](/ru/badusb/script-format)
- [Event loop](/ru/dev/js-event-loop), [GUI](/ru/dev/js-gui) для интерактивных меню выбора пейлоада
