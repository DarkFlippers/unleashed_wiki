---
title: "JavaScript: GUI views"
sidebarTitle: "JS: gui views"
order: 280
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__byte_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__dialog.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__empty_screen.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__file_picker.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__icon.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__loading.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__submenu.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_box.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__widget.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages/fz-sdk/gui]
sources: [unleashed-docs, unleashed-src]
---
# GUI views

Each view is a separate module loaded with `require("gui/<name>")`. Every view module depends on `gui`, which depends on `event_loop`, so always load them **in this order**:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let submenuView = require("gui/submenu");
```

Read [GUI](/dev/js-gui) first for how views, props, children and the view dispatcher work. All views below are used in the bundled example `/ext/apps/Scripts/js_examples/gui.js`.

| Module | What it shows |
|---|---|
| [`gui/submenu`](#submenu) | Scrollable list of text entries |
| [`gui/menu`](#menu) | List of entries with icons |
| [`gui/button_menu`](#button-menu) | List of buttons |
| [`gui/button_panel`](#button-panel) | Grid of icon buttons |
| [`gui/vi_list`](#vi-list) | Settings-style list with switchable values |
| [`gui/dialog`](#dialog) | Dialog with up to 3 buttons |
| [`gui/popup`](#popup) | Dialog that closes on a timer |
| [`gui/text_box`](#text-box) | Scrollable read-only text |
| [`gui/text_input`](#text-input) | Text keyboard |
| [`gui/byte_input`](#byte-input) | Hex keyboard |
| [`gui/number_input`](#number-input) | Number keyboard |
| [`gui/loading`](#loading) | Animated hourglass |
| [`gui/empty_screen`](#empty-screen) | Blank screen |
| [`gui/widget`](#widget) | Custom combination of elements |
| [`gui/file_picker`](#file-picker) | File selection prompt (function, not a view) |
| [`gui/icon`](#icon) | Icons for other views (helper) |

::: tip Unleashed
`menu`, `button_menu`, `button_panel`, `vi_list`, `number_input` and `popup` exist in the firmware but have no page in the official JS docs. Their props and events below come from the SDK typings (`packages/fz-sdk/gui/*.d.ts`).
:::

## Submenu {#submenu}

![Submenu](/img/dev/js_gui_submenu.png)

```js
let submenuView = require("gui/submenu");
```

| Prop | Type | Description |
|---|---|---|
| `header` | `string` | A single line of text above the list |

**Children:** strings, one per entry.

| Event | Item type | Description |
|---|---|---|
| `chosen` | `number` | Fires when the user picks an entry; the item is its index |

```js
let menu = submenuView.makeWith({ header: "Choose a demo" }, ["One", "Two", "Exit"]);
```

::: warning
The older docs list an `items` prop. Current firmware takes the entries as **children** instead (see [GUI](/dev/js-gui#example)).
:::

## Menu {#menu}

A list of selectable entries, each with an icon and a label.

```js
let menuView = require("gui/menu");
```

**Props:** none. **Children:** `{ icon: IconData, label: string }` (icons from [`gui/icon`](#icon)).

| Event | Item type | Description |
|---|---|---|
| `chosen` | `number` | Index of the chosen entry |

```js
let settingsIcon = icon.getBuiltin("Settings_14");
let menu = menuView.makeWith({}, [
    { label: "One", icon: settingsIcon },
    { label: "Two", icon: settingsIcon },
]);
```

## Button menu {#button-menu}

A list of buttons.

```js
let buttonMenuView = require("gui/button_menu");
```

| Prop | Type | Description |
|---|---|---|
| `header` | `string` | Text header above the buttons |

**Children:** `{ type: "common" | "control", label: string }`.

| Event | Item type | Description |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Button index and input type (`"press"`, `"release"`, `"short"`, `"long"`, `"repeat"`) |

```js
let buttonMenu = buttonMenuView.makeWith({ header: "Header" }, [
    { type: "common", label: "Test" },
    { type: "control", label: "Test2" },
]);
```

## Button panel {#button-panel}

A matrix of icon buttons with optional labels.

```js
let buttonPanelView = require("gui/button_panel");
```

| Prop | Type | Description |
|---|---|---|
| `matrixSizeX` | `number` | Width of the imaginary grid used for navigation |
| `matrixSizeY` | `number` | Height of the imaginary grid used for navigation |

**Children** (`x`, `y` are screen coordinates):

- `{ type: "button", x, y, matrixX, matrixY, icon: IconData, iconSelected: IconData }`
- `{ type: "label", x, y, font: Font, text: string }`
- `{ type: "icon", icon: IconData }`

| Event | Item type | Description |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Pressed button index and input type |

```js
let buttonPanel = buttonPanelView.makeWith({ matrixSizeX: 2, matrixSizeY: 2 }, [
    { type: "button", x: 0, y: 0, matrixX: 0, matrixY: 0, icon: offIcons[0], iconSelected: offIcons[1] },
    { type: "button", x: 30, y: 30, matrixX: 1, matrixY: 1, icon: powerIcons[0], iconSelected: powerIcons[1] },
    { type: "label", x: 0, y: 50, text: "Label", font: "primary" },
]);
```

## Variable item list {#vi-list}

A settings-style list: each item has a label and a set of values switched with <kbd>←</kbd> / <kbd>→</kbd>.

```js
let viListView = require("gui/vi_list");
```

**Props:** none. **Children:** `{ label: string, variants: string[] }`.

| Event | Item type | Description |
|---|---|---|
| `valueUpdate` | `{ itemIndex: number, valueIndex: number }` | Fires when the value of an item changes |

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

| Prop | Type | Description |
|---|---|---|
| `header` | `string` | Bold text at the top of the screen |
| `text` | `string` | Text in the middle of the screen |
| `left` | `string` | Left button text. If unset, the left button is hidden |
| `center` | `string` | Center button text. If unset, the center button is hidden |
| `right` | `string` | Right button text. If unset, the right button is hidden |

| Event | Item type | Description |
|---|---|---|
| `input` | `string` | Fires when one of the buttons is pressed; the item is `"left"`, `"center"` or `"right"` |

## Popup {#popup}

Like a dialog, but with a built-in timer.

```js
let popupView = require("gui/popup");
```

| Prop | Type | Description |
|---|---|---|
| `header` | `string` | Bold text at the top of the screen |
| `text` | `string` | Text in the middle of the screen |
| `timeout` | `number` | Timeout in ms after which the event fires. The countdown starts when this property is assigned |

| Event | Item type | Description |
|---|---|---|
| `timeout` | (none) | Fires when the timeout expires |

## Text box {#text-box}

![Text box](/img/dev/js_gui_text_box.png)

A scrollable read-only text field.

```js
let textBoxView = require("gui/text_box");
```

| Prop | Type | Description |
|---|---|---|
| `text` | `string` | Text to show |
| `font` | `string` | Font: `"text"` or `"hex"` |
| `focus` | `string` | Initial scroll position: `"start"` or `"end"` |

## Text input {#text-input}

![Text input](/img/dev/js_gui_text_input.png)

An on-screen keyboard.

```js
let textInputView = require("gui/text_input");
```

| Prop | Type | Description |
|---|---|---|
| `minLength` | `number` | Shortest allowed text length |
| `maxLength` | `number` | Longest allowed text length. Default: `32` |
| `header` | `string` | A single line of text above the keyboard |
| `defaultText` | `string` | Text shown by default |
| `defaultTextClear` | `boolean` | Whether to clear the default text when the next character is typed |

| Event | Item type | Description |
|---|---|---|
| `input` | `string` | Fires when the user selects **Save** and the text length fits `minLength`/`maxLength` |

## Byte input {#byte-input}

![Byte input](/img/dev/js_gui_byte_input.png)

A hexadecimal keyboard.

```js
let byteInputView = require("gui/byte_input");
```

| Prop | Type | Description |
|---|---|---|
| `length` | `number` | Length in bytes of the buffer to edit |
| `header` | `string` | A single line of text above the keyboard |
| `defaultData` | `Uint8Array` / `ArrayBuffer` | Data shown by default (must not be longer than `length`) |

| Event | Item type | Description |
|---|---|---|
| `input` | `ArrayBuffer` | Fires when the user selects **Save** |

::: info
The official doc lists `defaultData` as `string`. The firmware actually reads it as an `ArrayBuffer` (or a typed array such as `Uint8Array`) and errors if it is longer than `length`.
:::

## Number input {#number-input}

A numeric keyboard.

```js
let numberInputView = require("gui/number_input");
```

| Prop | Type | Description |
|---|---|---|
| `header` | `string` | Text at the top of the screen |
| `minValue` | `number` | Minimum allowed value |
| `maxValue` | `number` | Maximum allowed value |
| `defaultValue` | `number` | Default value |

| Event | Item type | Description |
|---|---|---|
| `input` | `number` | The entered number |

## Loading {#loading}

![Loading](/img/dev/js_gui_loading.png)

An animated hourglass. It **suppresses all `navigation` events**, so the user cannot leave it with <kbd>Back</kbd>; switch away from it in code.

```js
let loadingView = require("gui/loading");
```

No props.

## Empty screen {#empty-screen}

![Empty screen](/img/dev/js_gui_empty.png)

```js
let emptyView = require("gui/empty_screen");
```

No props.

## Widget {#widget}

![Widget](/img/dev/js_gui_widget.png)

Shows a combination of custom elements on one screen.

```js
let widgetView = require("gui/widget");
```

**Props:** none. **Children:** elements in the form `{ element: "type", ...properties }`, e.g. `{ element: "button", button: "right", text: "Back" }`.

| Element | Properties | Description |
|---|---|---|
| `string_multiline` | `x`, `y` (number); `align`; `font`; `text` (string) | Text that can span several lines |
| `string` | `x`, `y` (number); `align`; `font`; `text` (string) | Single string of text |
| `text_box` | `x`, `y`, `w`, `h` (number); `align`; `text` (string); `stripToDots` (boolean) | Box with vertically scrollable text |
| `text_scroll` | `x`, `y`, `w`, `h` (number); `text` (string) | Vertically scrollable text |
| `button` | `text` (string); `button` (`"left"`, `"center"`, `"right"`) | Button at the bottom of the screen |
| `icon` | `x`, `y` (number); `iconData` ([IconData](#icon)) | An icon |
| `rect` | `x`, `y`, `w`, `h` (number); `radius` (number), `fill` (boolean) | Rectangle, optionally rounded and filled |
| `circle` | `x`, `y` (number); `radius` (number), `fill` (boolean) | Circle, optionally filled |
| `line` | `x1`, `y1`, `x2`, `y2` (number) | Line between two points |

- `align` is a vertical letter (`"t"`, `"c"`, `"b"`) followed by a horizontal one (`"l"`, `"m"`, `"r"`), e.g. `"bl"` or `"cm"`.
- `font` is one of `"primary"`, `"secondary"`, `"keyboard"`, `"big_numbers"`.

**ButtonEvent** structure:

- `key`: the key pressed (`"left" | "center" | "right"`);
- `type`: the event type (`"press" | "release" | "short" | "long" | "repeat"`).

| Event | Item type | Description |
|---|---|---|
| `button` | `ButtonEvent` | Fires when one of the three buttons is pressed, if there is a matching `button` element |

```js
let stopwatchWidgetElements = [
    { element: "string", x: 67, y: 44, align: "bl", font: "big_numbers", text: "00 00" },
    { element: "button", button: "right", text: "Back" },
];
let widget = widgetView.makeWith({}, stopwatchWidgetElements);
```

## File picker {#file-picker}

Not a view like the others, just a function that shows a file selection prompt.

```js
let filePicker = require("gui/file_picker");
```

### pickFile()
Shows a file picker and returns the selected file, or `undefined` if cancelled.

- **Parameters:**
  - `basePath`: the path to start at;
  - `extension`: file extension(s) to show (like `.sub`, `.iso|.img`, `*`).
- **Returns:** a `string` path, or `undefined`.

## Icons {#icon}

Gets and loads icons for views such as [Menu](#menu), [Button panel](#button-panel) and [Widget](#widget).

```js
let icon = require("gui/icon");
```

### getBuiltin()
Gets a built-in firmware icon by name and returns an `IconData` object.

Only some icons are available. The official docs name `"DolphinWait_59x54"` and `"js_script_10px"`. The current firmware also has `"off_19x20"`, `"off_hover_19x20"`, `"power_19x20"`, `"power_hover_19x20"` and the animated `"Settings_14"`.

- **Parameters:** `icon`, the name of the icon.

### loadFxbm()
Loads a `.fxbm` icon (XBM Flipper sprite, from `flipperzero-game-engine`) from a file and returns an `IconData` object. It is unloaded automatically when the script exits.

- **Parameters:** `path`, the path to the `.fxbm` file.
