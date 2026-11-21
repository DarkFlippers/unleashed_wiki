---
title: "JavaScript: представлення GUI"
sidebarTitle: "JS: gui views"
order: 280
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__byte_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__dialog.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__empty_screen.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__file_picker.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__icon.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__loading.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__submenu.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_box.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__widget.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages/fz-sdk/gui]
sources: [unleashed-docs, unleashed-src]
---
# Представлення GUI

Кожне представлення — окремий модуль, що завантажується через `require("gui/<name>")`. Будь-який модуль представлення залежить від `gui`, а той — від `event_loop`, тому завантажуйте їх **саме в такому порядку**:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let submenuView = require("gui/submenu");
```

Спершу прочитайте [GUI](/ua/dev/js-gui) — там описано, як працюють представлення, властивості, дочірні елементи та view dispatcher. Усі представлення, наведені нижче, задіяні у вбудованому прикладі `/ext/apps/Scripts/js_examples/gui.js`.

| Модуль | Що показує |
|---|---|
| [`gui/submenu`](#submenu) | Прокручуваний список текстових пунктів |
| [`gui/menu`](#menu) | Список пунктів з піктограмами |
| [`gui/button_menu`](#button-menu) | Список кнопок |
| [`gui/button_panel`](#button-panel) | Сітка кнопок-піктограм |
| [`gui/vi_list`](#vi-list) | Список у стилі налаштувань із перемиканням значень |
| [`gui/dialog`](#dialog) | Діалог із щонайбільше 3 кнопками |
| [`gui/popup`](#popup) | Діалог, який закривається за таймером |
| [`gui/text_box`](#text-box) | Прокручуваний текст лише для читання |
| [`gui/text_input`](#text-input) | Текстова клавіатура |
| [`gui/byte_input`](#byte-input) | Шістнадцяткова клавіатура |
| [`gui/number_input`](#number-input) | Числова клавіатура |
| [`gui/loading`](#loading) | Анімований пісочний годинник |
| [`gui/empty_screen`](#empty-screen) | Порожній екран |
| [`gui/widget`](#widget) | Власна комбінація елементів |
| [`gui/file_picker`](#file-picker) | Запит на вибір файлу (функція, а не представлення) |
| [`gui/icon`](#icon) | Піктограми для інших представлень (допоміжний модуль) |

::: tip Unleashed
`menu`, `button_menu`, `button_panel`, `vi_list`, `number_input` і `popup` є у прошивці, але окремої сторінки в офіційній документації з JS не мають. Їхні властивості й події нижче взято з типів SDK (`packages/fz-sdk/gui/*.d.ts`).
:::

## Submenu {#submenu}

![Submenu](/img/dev/js_gui_submenu.png)

```js
let submenuView = require("gui/submenu");
```

| Властивість | Тип | Опис |
|---|---|---|
| `header` | `string` | Один рядок тексту над списком |

**Дочірні елементи:** рядки, по одному на пункт.

| Подія | Тип елемента | Опис |
|---|---|---|
| `chosen` | `number` | Спрацьовує, коли користувач вибирає пункт; елементом є його індекс |

```js
let menu = submenuView.makeWith({ header: "Choose a demo" }, ["One", "Two", "Exit"]);
```

::: warning
У старій документації згадується властивість `items`. Поточна прошивка натомість приймає пункти як **дочірні елементи** (див. [GUI](/ua/dev/js-gui#example)).
:::

## Menu {#menu}

Список пунктів для вибору, кожен з піктограмою і підписом.

```js
let menuView = require("gui/menu");
```

**Властивості:** немає. **Дочірні елементи:** `{ icon: IconData, label: string }` (піктограми — з [`gui/icon`](#icon)).

| Подія | Тип елемента | Опис |
|---|---|---|
| `chosen` | `number` | Індекс вибраного пункту |

```js
let settingsIcon = icon.getBuiltin("Settings_14");
let menu = menuView.makeWith({}, [
    { label: "One", icon: settingsIcon },
    { label: "Two", icon: settingsIcon },
]);
```

## Button menu {#button-menu}

Список кнопок.

```js
let buttonMenuView = require("gui/button_menu");
```

| Властивість | Тип | Опис |
|---|---|---|
| `header` | `string` | Текстовий заголовок над кнопками |

**Дочірні елементи:** `{ type: "common" | "control", label: string }`.

| Подія | Тип елемента | Опис |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Індекс кнопки й тип введення (`"press"`, `"release"`, `"short"`, `"long"`, `"repeat"`) |

```js
let buttonMenu = buttonMenuView.makeWith({ header: "Header" }, [
    { type: "common", label: "Test" },
    { type: "control", label: "Test2" },
]);
```

## Button panel {#button-panel}

Матриця кнопок-піктограм із необов’язковими підписами.

```js
let buttonPanelView = require("gui/button_panel");
```

| Властивість | Тип | Опис |
|---|---|---|
| `matrixSizeX` | `number` | Ширина умовної сітки, що використовується для навігації |
| `matrixSizeY` | `number` | Висота умовної сітки, що використовується для навігації |

**Дочірні елементи** (`x`, `y` — координати на екрані):

- `{ type: "button", x, y, matrixX, matrixY, icon: IconData, iconSelected: IconData }`
- `{ type: "label", x, y, font: Font, text: string }`
- `{ type: "icon", icon: IconData }`

| Подія | Тип елемента | Опис |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Індекс натиснутої кнопки й тип введення |

```js
let buttonPanel = buttonPanelView.makeWith({ matrixSizeX: 2, matrixSizeY: 2 }, [
    { type: "button", x: 0, y: 0, matrixX: 0, matrixY: 0, icon: offIcons[0], iconSelected: offIcons[1] },
    { type: "button", x: 30, y: 30, matrixX: 1, matrixY: 1, icon: powerIcons[0], iconSelected: powerIcons[1] },
    { type: "label", x: 0, y: 50, text: "Label", font: "primary" },
]);
```

## Variable item list {#vi-list}

Список у стилі налаштувань: кожен пункт має підпис і набір значень, які перемикаються кнопками <kbd>←</kbd> / <kbd>→</kbd>.

```js
let viListView = require("gui/vi_list");
```

**Властивості:** немає. **Дочірні елементи:** `{ label: string, variants: string[] }`.

| Подія | Тип елемента | Опис |
|---|---|---|
| `valueUpdate` | `{ itemIndex: number, valueIndex: number }` | Спрацьовує, коли змінюється значення пункту |

```js
let viList = viListView.makeWith({}, [
    { label: "One", variants: ["1", "1.0"] },
    { label: "Two", variants: ["2", "2.0"] },
]);
```

## Dialog {#dialog}

![Dialog](/img/dev/js_gui_dialog.png)

```js
let dialogView = require("gui/dialog");
```

| Властивість | Тип | Опис |
|---|---|---|
| `header` | `string` | Жирний текст у верхній частині екрана |
| `text` | `string` | Текст у центрі екрана |
| `left` | `string` | Підпис лівої кнопки. Якщо не задано, ліву кнопку сховано |
| `center` | `string` | Підпис центральної кнопки. Якщо не задано, центральну кнопку сховано |
| `right` | `string` | Підпис правої кнопки. Якщо не задано, праву кнопку сховано |

| Подія | Тип елемента | Опис |
|---|---|---|
| `input` | `string` | Спрацьовує при натисканні однієї з кнопок; елементом є `"left"`, `"center"` або `"right"` |

## Popup {#popup}

Те саме, що діалог, але з вбудованим таймером.

```js
let popupView = require("gui/popup");
```

| Властивість | Тип | Опис |
|---|---|---|
| `header` | `string` | Жирний текст у верхній частині екрана |
| `text` | `string` | Текст у центрі екрана |
| `timeout` | `number` | Час у мс, після якого спрацює подія. Відлік починається в момент присвоєння цієї властивості |

| Подія | Тип елемента | Опис |
|---|---|---|
| `timeout` | (немає) | Спрацьовує, коли час очікування вичерпано |

## Text box {#text-box}

![Text box](/img/dev/js_gui_text_box.png)

Прокручуване текстове поле лише для читання.

```js
let textBoxView = require("gui/text_box");
```

| Властивість | Тип | Опис |
|---|---|---|
| `text` | `string` | Текст для показу |
| `font` | `string` | Шрифт: `"text"` або `"hex"` |
| `focus` | `string` | Початкова позиція прокручування: `"start"` або `"end"` |

## Text input {#text-input}

![Text input](/img/dev/js_gui_text_input.png)

Екранна клавіатура.

```js
let textInputView = require("gui/text_input");
```

| Властивість | Тип | Опис |
|---|---|---|
| `minLength` | `number` | Найменша допустима довжина тексту |
| `maxLength` | `number` | Найбільша допустима довжина тексту. Типово: `32` |
| `header` | `string` | Один рядок тексту над клавіатурою |
| `defaultText` | `string` | Текст, що показується типово |
| `defaultTextClear` | `boolean` | Чи очищати типовий текст при введенні наступного символу |

| Подія | Тип елемента | Опис |
|---|---|---|
| `input` | `string` | Спрацьовує, коли користувач вибирає **Save**, а довжина тексту вкладається в `minLength`/`maxLength` |

## Byte input {#byte-input}

![Byte input](/img/dev/js_gui_byte_input.png)

Шістнадцяткова клавіатура.

```js
let byteInputView = require("gui/byte_input");
```

| Властивість | Тип | Опис |
|---|---|---|
| `length` | `number` | Довжина (у байтах) буфера, який редагується |
| `header` | `string` | Один рядок тексту над клавіатурою |
| `defaultData` | `Uint8Array` / `ArrayBuffer` | Дані, що показуються типово (не можуть бути довшими за `length`) |

| Подія | Тип елемента | Опис |
|---|---|---|
| `input` | `ArrayBuffer` | Спрацьовує, коли користувач вибирає **Save** |

::: info
В офіційній документації `defaultData` вказано як `string`. Насправді прошивка читає його як `ArrayBuffer` (або типізований масив, як-от `Uint8Array`) і повідомляє про помилку, якщо дані довші за `length`.
:::

## Number input {#number-input}

Числова клавіатура.

```js
let numberInputView = require("gui/number_input");
```

| Властивість | Тип | Опис |
|---|---|---|
| `header` | `string` | Текст у верхній частині екрана |
| `minValue` | `number` | Найменше допустиме значення |
| `maxValue` | `number` | Найбільше допустиме значення |
| `defaultValue` | `number` | Типове значення |

| Подія | Тип елемента | Опис |
|---|---|---|
| `input` | `number` | Введене число |

## Loading {#loading}

![Loading](/img/dev/js_gui_loading.png)

Анімований пісочний годинник. Це представлення **глушить усі події `navigation`**, тож користувач не може вийти з нього кнопкою <kbd>Back</kbd> — перемикайтеся з нього в коді.

```js
let loadingView = require("gui/loading");
```

Властивостей немає.

## Empty screen {#empty-screen}

![Empty screen](/img/dev/js_gui_empty.png)

```js
let emptyView = require("gui/empty_screen");
```

Властивостей немає.

## Widget {#widget}

![Widget](/img/dev/js_gui_widget.png)

Показує на одному екрані комбінацію власних елементів.

```js
let widgetView = require("gui/widget");
```

**Властивості:** немає. **Дочірні елементи:** елементи у вигляді `{ element: "type", ...properties }`, наприклад `{ element: "button", button: "right", text: "Back" }`.

| Елемент | Властивості | Опис |
|---|---|---|
| `string_multiline` | `x`, `y` (number); `align`; `font`; `text` (string) | Текст, що може займати кілька рядків |
| `string` | `x`, `y` (number); `align`; `font`; `text` (string) | Один рядок тексту |
| `text_box` | `x`, `y`, `w`, `h` (number); `align`; `text` (string); `stripToDots` (boolean) | Поле з текстом, що прокручується вертикально |
| `text_scroll` | `x`, `y`, `w`, `h` (number); `text` (string) | Текст, що прокручується вертикально |
| `button` | `text` (string); `button` (`"left"`, `"center"`, `"right"`) | Кнопка в нижній частині екрана |
| `icon` | `x`, `y` (number); `iconData` ([IconData](#icon)) | Піктограма |
| `rect` | `x`, `y`, `w`, `h` (number); `radius` (number), `fill` (boolean) | Прямокутник, за потреби зі скругленими кутами й заливкою |
| `circle` | `x`, `y` (number); `radius` (number), `fill` (boolean) | Коло, за потреби із заливкою |
| `line` | `x1`, `y1`, `x2`, `y2` (number) | Лінія між двома точками |

- `align` — це літера вертикального вирівнювання (`"t"`, `"c"`, `"b"`), за якою йде літера горизонтального (`"l"`, `"m"`, `"r"`), наприклад `"bl"` або `"cm"`.
- `font` — одне з `"primary"`, `"secondary"`, `"keyboard"`, `"big_numbers"`.

Структура **ButtonEvent**:

- `key`: натиснута кнопка (`"left" | "center" | "right"`);
- `type`: тип події (`"press" | "release" | "short" | "long" | "repeat"`).

| Подія | Тип елемента | Опис |
|---|---|---|
| `button` | `ButtonEvent` | Спрацьовує при натисканні однієї з трьох кнопок, якщо для неї є відповідний елемент `button` |

```js
let stopwatchWidgetElements = [
    { element: "string", x: 67, y: 44, align: "bl", font: "big_numbers", text: "00 00" },
    { element: "button", button: "right", text: "Back" },
];
let widget = widgetView.makeWith({}, stopwatchWidgetElements);
```

## File picker {#file-picker}

Це не представлення, як решта, а просто функція, що показує запит на вибір файлу.

```js
let filePicker = require("gui/file_picker");
```

### pickFile()
Показує вибір файлу й повертає вибраний файл або `undefined`, якщо вибір скасовано.

- **Параметри:**
  - `basePath`: шлях, з якого починати;
  - `extension`: розширення файлів, які показувати (наприклад, `.sub`, `.iso|.img`, `*`).
- **Повертає:** шлях у вигляді `string` або `undefined`.

## Піктограми {#icon}

Отримує й завантажує піктограми для таких представлень, як [Menu](#menu), [Button panel](#button-panel) і [Widget](#widget).

```js
let icon = require("gui/icon");
```

### getBuiltin()
Отримує вбудовану піктограму прошивки за назвою й повертає об’єкт `IconData`.

Доступні лише деякі піктограми. В офіційній документації названо `"DolphinWait_59x54"` і `"js_script_10px"`. У поточній прошивці є також `"off_19x20"`, `"off_hover_19x20"`, `"power_19x20"`, `"power_hover_19x20"` та анімована `"Settings_14"`.

- **Параметри:** `icon` — назва піктограми.

### loadFxbm()
Завантажує з файлу піктограму `.fxbm` (спрайт XBM для Flipper із `flipperzero-game-engine`) і повертає об’єкт `IconData`. Вона вивантажується автоматично, коли скрипт завершується.

- **Параметри:** `path` — шлях до файлу `.fxbm`.
