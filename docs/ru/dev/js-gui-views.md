---
title: "JavaScript: виды GUI"
sidebarTitle: "JS: виды gui"
order: 280
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__byte_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__dialog.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__empty_screen.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__file_picker.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__icon.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__loading.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__submenu.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_box.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__widget.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages/fz-sdk/gui]
sources: [unleashed-docs, unleashed-src]
---
# Виды GUI

Каждый вид — отдельный модуль, подключаемый через `require("gui/<имя>")`. Модуль вида зависит от `gui`, а тот от `event_loop`, поэтому подключайте их **именно в таком порядке**:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let submenuView = require("gui/submenu");
```

Как устроены виды, свойства, дочерние элементы и view dispatcher, описано на странице [GUI](/ru/dev/js-gui). Все виды ниже используются во встроенном примере `/ext/apps/Scripts/js_examples/gui.js`.

| Модуль | Что показывает |
|---|---|
| [`gui/submenu`](#submenu) | Прокручиваемый список текстовых пунктов |
| [`gui/menu`](#menu) | Список пунктов с иконками |
| [`gui/button_menu`](#button-menu) | Список кнопок |
| [`gui/button_panel`](#button-panel) | Сетка кнопок-иконок |
| [`gui/vi_list`](#vi-list) | Список настроек с переключаемыми значениями |
| [`gui/dialog`](#dialog) | Диалог с кнопками (до 3) |
| [`gui/popup`](#popup) | Диалог, закрывающийся по таймеру |
| [`gui/text_box`](#text-box) | Прокручиваемый текст только для чтения |
| [`gui/text_input`](#text-input) | Текстовая клавиатура |
| [`gui/byte_input`](#byte-input) | HEX-клавиатура |
| [`gui/number_input`](#number-input) | Цифровая клавиатура |
| [`gui/loading`](#loading) | Анимированные песочные часы |
| [`gui/empty_screen`](#empty-screen) | Пустой экран |
| [`gui/widget`](#widget) | Произвольный набор элементов |
| [`gui/file_picker`](#file-picker) | Выбор файла (функция, а не вид) |
| [`gui/icon`](#icon) | Иконки для других видов (вспомогательный) |

::: tip Unleashed
`menu`, `button_menu`, `button_panel`, `vi_list`, `number_input` и `popup` есть в прошивке, но в официальной JS-документации у них нет страниц. Их свойства и события ниже взяты из типов SDK (`packages/fz-sdk/gui/*.d.ts`).
:::

## Submenu {#submenu}

![Submenu](/img/dev/js_gui_submenu.png)

```js
let submenuView = require("gui/submenu");
```

| Свойство | Тип | Описание |
|---|---|---|
| `header` | `string` | Одна строка текста над списком |

**Дочерние элементы:** строки, по одной на пункт.

| Событие | Тип | Описание |
|---|---|---|
| `chosen` | `number` | Срабатывает при выборе пункта; значение — его индекс |

```js
let menu = submenuView.makeWith({ header: "Choose a demo" }, ["One", "Two", "Exit"]);
```

::: warning
В старой документации указано свойство `items`. В текущей прошивке пункты передаются **дочерними элементами** (см. [GUI](/ru/dev/js-gui#example)).
:::

## Menu {#menu}

Список пунктов, у каждого иконка и подпись.

```js
let menuView = require("gui/menu");
```

**Свойств нет.** **Дочерние элементы:** `{ icon: IconData, label: string }` (иконки из [`gui/icon`](#icon)).

| Событие | Тип | Описание |
|---|---|---|
| `chosen` | `number` | Индекс выбранного пункта |

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

| Свойство | Тип | Описание |
|---|---|---|
| `header` | `string` | Заголовок над кнопками |

**Дочерние элементы:** `{ type: "common" | "control", label: string }`.

| Событие | Тип | Описание |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Индекс кнопки и тип нажатия (`"press"`, `"release"`, `"short"`, `"long"`, `"repeat"`) |

```js
let buttonMenu = buttonMenuView.makeWith({ header: "Header" }, [
    { type: "common", label: "Test" },
    { type: "control", label: "Test2" },
]);
```

## Button panel {#button-panel}

Матрица кнопок-иконок с необязательными подписями.

```js
let buttonPanelView = require("gui/button_panel");
```

| Свойство | Тип | Описание |
|---|---|---|
| `matrixSizeX` | `number` | Ширина воображаемой сетки для навигации |
| `matrixSizeY` | `number` | Высота воображаемой сетки для навигации |

**Дочерние элементы** (`x`, `y` — координаты на экране):

- `{ type: "button", x, y, matrixX, matrixY, icon: IconData, iconSelected: IconData }`
- `{ type: "label", x, y, font: Font, text: string }`
- `{ type: "icon", icon: IconData }`

| Событие | Тип | Описание |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Индекс нажатой кнопки и тип нажатия |

```js
let buttonPanel = buttonPanelView.makeWith({ matrixSizeX: 2, matrixSizeY: 2 }, [
    { type: "button", x: 0, y: 0, matrixX: 0, matrixY: 0, icon: offIcons[0], iconSelected: offIcons[1] },
    { type: "button", x: 30, y: 30, matrixX: 1, matrixY: 1, icon: powerIcons[0], iconSelected: powerIcons[1] },
    { type: "label", x: 0, y: 50, text: "Label", font: "primary" },
]);
```

## Variable item list {#vi-list}

Список в стиле настроек: у каждого пункта подпись и набор значений, переключаемых <kbd>←</kbd> / <kbd>→</kbd>.

```js
let viListView = require("gui/vi_list");
```

**Свойств нет.** **Дочерние элементы:** `{ label: string, variants: string[] }`.

| Событие | Тип | Описание |
|---|---|---|
| `valueUpdate` | `{ itemIndex: number, valueIndex: number }` | Срабатывает при смене значения пункта |

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

| Свойство | Тип | Описание |
|---|---|---|
| `header` | `string` | Жирный текст вверху экрана |
| `text` | `string` | Текст в середине экрана |
| `left` | `string` | Текст левой кнопки. Если не задан, кнопки нет |
| `center` | `string` | Текст центральной кнопки. Если не задан, кнопки нет |
| `right` | `string` | Текст правой кнопки. Если не задан, кнопки нет |

| Событие | Тип | Описание |
|---|---|---|
| `input` | `string` | Срабатывает при нажатии одной из кнопок; значение — `"left"`, `"center"` или `"right"` |

## Popup {#popup}

Как диалог, но со встроенным таймером.

```js
let popupView = require("gui/popup");
```

| Свойство | Тип | Описание |
|---|---|---|
| `header` | `string` | Жирный текст вверху экрана |
| `text` | `string` | Текст в середине экрана |
| `timeout` | `number` | Таймаут в мс, после которого сработает событие. Отсчёт начинается в момент присвоения свойства |

| Событие | Тип | Описание |
|---|---|---|
| `timeout` | (нет) | Срабатывает по истечении таймаута |

## Text box {#text-box}

![Text box](/img/dev/js_gui_text_box.png)

Прокручиваемое текстовое поле только для чтения.

```js
let textBoxView = require("gui/text_box");
```

| Свойство | Тип | Описание |
|---|---|---|
| `text` | `string` | Отображаемый текст |
| `font` | `string` | Шрифт: `"text"` или `"hex"` |
| `focus` | `string` | Начальная позиция прокрутки: `"start"` или `"end"` |

## Text input {#text-input}

![Text input](/img/dev/js_gui_text_input.png)

Экранная клавиатура.

```js
let textInputView = require("gui/text_input");
```

| Свойство | Тип | Описание |
|---|---|---|
| `minLength` | `number` | Минимальная длина текста |
| `maxLength` | `number` | Максимальная длина текста. По умолчанию `32` |
| `header` | `string` | Одна строка текста над клавиатурой |
| `defaultText` | `string` | Текст по умолчанию |
| `defaultTextClear` | `boolean` | Стирать ли текст по умолчанию при вводе следующего символа |

| Событие | Тип | Описание |
|---|---|---|
| `input` | `string` | Срабатывает, когда пользователь нажал **Save** и длина текста укладывается в `minLength`/`maxLength` |

## Byte input {#byte-input}

![Byte input](/img/dev/js_gui_byte_input.png)

HEX-клавиатура.

```js
let byteInputView = require("gui/byte_input");
```

| Свойство | Тип | Описание |
|---|---|---|
| `length` | `number` | Длина редактируемого буфера в байтах |
| `header` | `string` | Одна строка текста над клавиатурой |
| `defaultData` | `Uint8Array` / `ArrayBuffer` | Данные по умолчанию (не длиннее `length`) |

| Событие | Тип | Описание |
|---|---|---|
| `input` | `ArrayBuffer` | Срабатывает, когда пользователь нажал **Save** |

::: info
В официальной документации тип `defaultData` указан как `string`. На деле прошивка читает его как `ArrayBuffer` (или типизированный массив, например `Uint8Array`) и выдаёт ошибку, если он длиннее `length`.
:::

## Number input {#number-input}

Цифровая клавиатура.

```js
let numberInputView = require("gui/number_input");
```

| Свойство | Тип | Описание |
|---|---|---|
| `header` | `string` | Текст вверху экрана |
| `minValue` | `number` | Минимальное значение |
| `maxValue` | `number` | Максимальное значение |
| `defaultValue` | `number` | Значение по умолчанию |

| Событие | Тип | Описание |
|---|---|---|
| `input` | `number` | Введённое число |

## Loading {#loading}

![Loading](/img/dev/js_gui_loading.png)

Анимированные песочные часы. Вид **подавляет все события `navigation`**, поэтому пользователь не может выйти из него кнопкой <kbd>Back</kbd>; переключайтесь с него программно.

```js
let loadingView = require("gui/loading");
```

Свойств нет.

## Empty screen {#empty-screen}

![Empty screen](/img/dev/js_gui_empty.png)

```js
let emptyView = require("gui/empty_screen");
```

Свойств нет.

## Widget {#widget}

![Widget](/img/dev/js_gui_widget.png)

Показывает набор произвольных элементов на одном экране.

```js
let widgetView = require("gui/widget");
```

**Свойств нет.** **Дочерние элементы:** объекты вида `{ element: "type", ...properties }`, например `{ element: "button", button: "right", text: "Back" }`.

| Элемент | Свойства | Описание |
|---|---|---|
| `string_multiline` | `x`, `y` (number); `align`; `font`; `text` (string) | Многострочный текст |
| `string` | `x`, `y` (number); `align`; `font`; `text` (string) | Одна строка текста |
| `text_box` | `x`, `y`, `w`, `h` (number); `align`; `text` (string); `stripToDots` (boolean) | Блок с вертикально прокручиваемым текстом |
| `text_scroll` | `x`, `y`, `w`, `h` (number); `text` (string) | Вертикально прокручиваемый текст |
| `button` | `text` (string); `button` (`"left"`, `"center"`, `"right"`) | Кнопка внизу экрана |
| `icon` | `x`, `y` (number); `iconData` ([IconData](#icon)) | Иконка |
| `rect` | `x`, `y`, `w`, `h` (number); `radius` (number), `fill` (boolean) | Прямоугольник, можно скруглить и залить |
| `circle` | `x`, `y` (number); `radius` (number), `fill` (boolean) | Круг, можно залить |
| `line` | `x1`, `y1`, `x2`, `y2` (number) | Линия между двумя точками |

- `align` — буква по вертикали (`"t"`, `"c"`, `"b"`) и буква по горизонтали (`"l"`, `"m"`, `"r"`), например `"bl"` или `"cm"`.
- `font` — один из `"primary"`, `"secondary"`, `"keyboard"`, `"big_numbers"`.

Структура **ButtonEvent**:

- `key` — нажатая кнопка (`"left" | "center" | "right"`);
- `type` — тип события (`"press" | "release" | "short" | "long" | "repeat"`).

| Событие | Тип | Описание |
|---|---|---|
| `button` | `ButtonEvent` | Срабатывает при нажатии одной из трёх кнопок, если есть соответствующий элемент `button` |

```js
let stopwatchWidgetElements = [
    { element: "string", x: 67, y: 44, align: "bl", font: "big_numbers", text: "00 00" },
    { element: "button", button: "right", text: "Back" },
];
let widget = widgetView.makeWith({}, stopwatchWidgetElements);
```

## File picker {#file-picker}

Это не вид, как остальные, а функция, показывающая окно выбора файла.

```js
let filePicker = require("gui/file_picker");
```

### pickFile()
Показывает выбор файла и возвращает выбранный файл или `undefined` при отмене.

- **Параметры:**
  - `basePath` — начальный путь;
  - `extension` — показываемые расширения (например, `.sub`, `.iso|.img`, `*`).
- **Возвращает:** путь (`string`) или `undefined`.

## Иконки {#icon}

Получение и загрузка иконок для видов [Menu](#menu), [Button panel](#button-panel) и [Widget](#widget).

```js
let icon = require("gui/icon");
```

### getBuiltin()
Возвращает встроенную иконку прошивки по имени (объект `IconData`).

Доступны не все иконки. Официальная документация называет `"DolphinWait_59x54"` и `"js_script_10px"`. В текущей прошивке есть также `"off_19x20"`, `"off_hover_19x20"`, `"power_19x20"`, `"power_hover_19x20"` и анимированная `"Settings_14"`.

- **Параметры:** `icon` — имя иконки.

### loadFxbm()
Загружает иконку `.fxbm` (XBM-спрайт Flipper из `flipperzero-game-engine`) из файла и возвращает объект `IconData`. Выгружается автоматически при завершении скрипта.

- **Параметры:** `path` — путь к файлу `.fxbm`.
