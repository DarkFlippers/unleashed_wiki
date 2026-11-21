---
title: "JavaScript: GUI-Views"
sidebarTitle: "JS: gui views"
order: 280
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__byte_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__dialog.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__empty_screen.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__file_picker.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__icon.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__loading.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__submenu.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_box.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__widget.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages/fz-sdk/gui]
sources: [unleashed-docs, unleashed-src]
---
# GUI-Views

Jede View ist ein eigenes Modul, das mit `require("gui/<name>")` geladen wird. Jedes View-Modul hängt von `gui` ab,
das von `event_loop` abhängt, lade sie daher immer **in dieser Reihenfolge**:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let submenuView = require("gui/submenu");
```

Lies zuerst [GUI](/de/dev/js-gui), um zu verstehen, wie Views, Props, Kinder und der View Dispatcher
funktionieren. Alle Views unten werden im mitgelieferten Beispiel `/ext/apps/Scripts/js_examples/gui.js` verwendet.

| Modul | Was es zeigt |
|---|---|
| [`gui/submenu`](#submenu) | Scrollbare Liste von Texteinträgen |
| [`gui/menu`](#menu) | Liste von Einträgen mit Icons |
| [`gui/button_menu`](#button-menu) | Liste von Schaltflächen |
| [`gui/button_panel`](#button-panel) | Raster aus Icon-Schaltflächen |
| [`gui/vi_list`](#vi-list) | Liste im Einstellungsstil mit umschaltbaren Werten |
| [`gui/dialog`](#dialog) | Dialog mit bis zu 3 Schaltflächen |
| [`gui/popup`](#popup) | Dialog, der nach einem Timer schließt |
| [`gui/text_box`](#text-box) | Scrollbarer, nur lesbarer Text |
| [`gui/text_input`](#text-input) | Texttastatur |
| [`gui/byte_input`](#byte-input) | Hex-Tastatur |
| [`gui/number_input`](#number-input) | Zahlentastatur |
| [`gui/loading`](#loading) | Animierte Sanduhr |
| [`gui/empty_screen`](#empty-screen) | Leerer Bildschirm |
| [`gui/widget`](#widget) | Eigene Kombination von Elementen |
| [`gui/file_picker`](#file-picker) | Dateiauswahl-Dialog (eine Funktion, keine View) |
| [`gui/icon`](#icon) | Icons für andere Views (Hilfsmodul) |

::: tip Unleashed
`menu`, `button_menu`, `button_panel`, `vi_list`, `number_input` und `popup` gibt es in der Firmware, sie haben in
der offiziellen JS-Dokumentation aber keine Seite. Ihre Props und Ereignisse unten stammen aus den
SDK-Typdefinitionen (`packages/fz-sdk/gui/*.d.ts`).
:::

## Submenu {#submenu}

![Submenu](/img/dev/js_gui_submenu.png)

```js
let submenuView = require("gui/submenu");
```

| Prop | Typ | Beschreibung |
|---|---|---|
| `header` | `string` | Eine einzelne Textzeile über der Liste |

**Kinder:** Zeichenketten, eine pro Eintrag.

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `chosen` | `number` | Wird ausgelöst, wenn der Benutzer einen Eintrag wählt; das Item ist dessen Index |

```js
let menu = submenuView.makeWith({ header: "Choose a demo" }, ["One", "Two", "Exit"]);
```

::: warning
Die älteren Dokumentationen führen ein Prop `items` auf. Die aktuelle Firmware nimmt die Einträge stattdessen als
**Kinder** (siehe [GUI](/de/dev/js-gui#example)).
:::

## Menu {#menu}

Eine Liste auswählbarer Einträge, jeder mit einem Icon und einer Bezeichnung.

```js
let menuView = require("gui/menu");
```

**Props:** keine. **Kinder:** `{ icon: IconData, label: string }` (Icons aus [`gui/icon`](#icon)).

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `chosen` | `number` | Index des gewählten Eintrags |

```js
let settingsIcon = icon.getBuiltin("Settings_14");
let menu = menuView.makeWith({}, [
    { label: "One", icon: settingsIcon },
    { label: "Two", icon: settingsIcon },
]);
```

## Button menu {#button-menu}

Eine Liste von Schaltflächen.

```js
let buttonMenuView = require("gui/button_menu");
```

| Prop | Typ | Beschreibung |
|---|---|---|
| `header` | `string` | Textkopfzeile über den Schaltflächen |

**Kinder:** `{ type: "common" | "control", label: string }`.

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Index der Schaltfläche und Eingabeart (`"press"`, `"release"`, `"short"`, `"long"`, `"repeat"`) |

```js
let buttonMenu = buttonMenuView.makeWith({ header: "Header" }, [
    { type: "common", label: "Test" },
    { type: "control", label: "Test2" },
]);
```

## Button panel {#button-panel}

Eine Matrix aus Icon-Schaltflächen mit optionalen Bezeichnungen.

```js
let buttonPanelView = require("gui/button_panel");
```

| Prop | Typ | Beschreibung |
|---|---|---|
| `matrixSizeX` | `number` | Breite des gedachten Rasters, das für die Navigation verwendet wird |
| `matrixSizeY` | `number` | Höhe des gedachten Rasters, das für die Navigation verwendet wird |

**Kinder** (`x`, `y` sind Bildschirmkoordinaten):

- `{ type: "button", x, y, matrixX, matrixY, icon: IconData, iconSelected: IconData }`
- `{ type: "label", x, y, font: Font, text: string }`
- `{ type: "icon", icon: IconData }`

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Index der gedrückten Schaltfläche und Eingabeart |

```js
let buttonPanel = buttonPanelView.makeWith({ matrixSizeX: 2, matrixSizeY: 2 }, [
    { type: "button", x: 0, y: 0, matrixX: 0, matrixY: 0, icon: offIcons[0], iconSelected: offIcons[1] },
    { type: "button", x: 30, y: 30, matrixX: 1, matrixY: 1, icon: powerIcons[0], iconSelected: powerIcons[1] },
    { type: "label", x: 0, y: 50, text: "Label", font: "primary" },
]);
```

## Variable item list {#vi-list}

Eine Liste im Einstellungsstil: jeder Eintrag hat eine Bezeichnung und eine Reihe von Werten, die mit
<kbd>←</kbd> / <kbd>→</kbd> umgeschaltet werden.

```js
let viListView = require("gui/vi_list");
```

**Props:** keine. **Kinder:** `{ label: string, variants: string[] }`.

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `valueUpdate` | `{ itemIndex: number, valueIndex: number }` | Wird ausgelöst, wenn sich der Wert eines Eintrags ändert |

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

| Prop | Typ | Beschreibung |
|---|---|---|
| `header` | `string` | Fetter Text am oberen Bildschirmrand |
| `text` | `string` | Text in der Bildschirmmitte |
| `left` | `string` | Text der linken Schaltfläche. Ist er nicht gesetzt, wird die linke Schaltfläche ausgeblendet |
| `center` | `string` | Text der mittleren Schaltfläche. Ist er nicht gesetzt, wird die mittlere Schaltfläche ausgeblendet |
| `right` | `string` | Text der rechten Schaltfläche. Ist er nicht gesetzt, wird die rechte Schaltfläche ausgeblendet |

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `input` | `string` | Wird ausgelöst, wenn eine der Schaltflächen gedrückt wird; das Item ist `"left"`, `"center"` oder `"right"` |

## Popup {#popup}

Wie ein Dialog, aber mit eingebautem Timer.

```js
let popupView = require("gui/popup");
```

| Prop | Typ | Beschreibung |
|---|---|---|
| `header` | `string` | Fetter Text am oberen Bildschirmrand |
| `text` | `string` | Text in der Bildschirmmitte |
| `timeout` | `number` | Timeout in ms, nach dem das Ereignis ausgelöst wird. Der Countdown beginnt, sobald diese Eigenschaft zugewiesen wird |

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `timeout` | (keines) | Wird ausgelöst, wenn das Timeout abläuft |

## Text box {#text-box}

![Text box](/img/dev/js_gui_text_box.png)

Ein scrollbares, nur lesbares Textfeld.

```js
let textBoxView = require("gui/text_box");
```

| Prop | Typ | Beschreibung |
|---|---|---|
| `text` | `string` | Anzuzeigender Text |
| `font` | `string` | Schrift: `"text"` oder `"hex"` |
| `focus` | `string` | Anfängliche Scrollposition: `"start"` oder `"end"` |

## Text input {#text-input}

![Text input](/img/dev/js_gui_text_input.png)

Eine Tastatur auf dem Display.

```js
let textInputView = require("gui/text_input");
```

| Prop | Typ | Beschreibung |
|---|---|---|
| `minLength` | `number` | Kürzeste erlaubte Textlänge |
| `maxLength` | `number` | Längste erlaubte Textlänge. Standard: `32` |
| `header` | `string` | Eine einzelne Textzeile über der Tastatur |
| `defaultText` | `string` | Standardmäßig angezeigter Text |
| `defaultTextClear` | `boolean` | Ob der Standardtext beim Eingeben des nächsten Zeichens gelöscht wird |

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `input` | `string` | Wird ausgelöst, wenn der Benutzer **Save** wählt und die Textlänge zu `minLength`/`maxLength` passt |

## Byte input {#byte-input}

![Byte input](/img/dev/js_gui_byte_input.png)

Eine hexadezimale Tastatur.

```js
let byteInputView = require("gui/byte_input");
```

| Prop | Typ | Beschreibung |
|---|---|---|
| `length` | `number` | Länge des zu bearbeitenden Puffers in Bytes |
| `header` | `string` | Eine einzelne Textzeile über der Tastatur |
| `defaultData` | `Uint8Array` / `ArrayBuffer` | Standardmäßig angezeigte Daten (dürfen nicht länger als `length` sein) |

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `input` | `ArrayBuffer` | Wird ausgelöst, wenn der Benutzer **Save** wählt |

::: info
Die offizielle Dokumentation führt `defaultData` als `string` auf. Die Firmware liest es tatsächlich als
`ArrayBuffer` (oder als typisiertes Array wie `Uint8Array`) und meldet einen Fehler, wenn es länger als `length`
ist.
:::

## Number input {#number-input}

Eine numerische Tastatur.

```js
let numberInputView = require("gui/number_input");
```

| Prop | Typ | Beschreibung |
|---|---|---|
| `header` | `string` | Text am oberen Bildschirmrand |
| `minValue` | `number` | Minimal erlaubter Wert |
| `maxValue` | `number` | Maximal erlaubter Wert |
| `defaultValue` | `number` | Standardwert |

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `input` | `number` | Die eingegebene Zahl |

## Loading {#loading}

![Loading](/img/dev/js_gui_loading.png)

Eine animierte Sanduhr. Sie **unterdrückt alle `navigation`-Ereignisse**, der Benutzer kann sie also nicht mit
<kbd>Back</kbd> verlassen; wechsle im Code von ihr weg.

```js
let loadingView = require("gui/loading");
```

Keine Props.

## Empty screen {#empty-screen}

![Empty screen](/img/dev/js_gui_empty.png)

```js
let emptyView = require("gui/empty_screen");
```

Keine Props.

## Widget {#widget}

![Widget](/img/dev/js_gui_widget.png)

Zeigt eine Kombination eigener Elemente auf einem Bildschirm.

```js
let widgetView = require("gui/widget");
```

**Props:** keine. **Kinder:** Elemente in der Form `{ element: "type", ...properties }`, z. B.
`{ element: "button", button: "right", text: "Back" }`.

| Element | Eigenschaften | Beschreibung |
|---|---|---|
| `string_multiline` | `x`, `y` (number); `align`; `font`; `text` (string) | Text, der sich über mehrere Zeilen erstrecken kann |
| `string` | `x`, `y` (number); `align`; `font`; `text` (string) | Einzelne Textzeichenkette |
| `text_box` | `x`, `y`, `w`, `h` (number); `align`; `text` (string); `stripToDots` (boolean) | Feld mit vertikal scrollbarem Text |
| `text_scroll` | `x`, `y`, `w`, `h` (number); `text` (string) | Vertikal scrollbarer Text |
| `button` | `text` (string); `button` (`"left"`, `"center"`, `"right"`) | Schaltfläche am unteren Bildschirmrand |
| `icon` | `x`, `y` (number); `iconData` ([IconData](#icon)) | Ein Icon |
| `rect` | `x`, `y`, `w`, `h` (number); `radius` (number), `fill` (boolean) | Rechteck, optional abgerundet und gefüllt |
| `circle` | `x`, `y` (number); `radius` (number), `fill` (boolean) | Kreis, optional gefüllt |
| `line` | `x1`, `y1`, `x2`, `y2` (number) | Linie zwischen zwei Punkten |

- `align` besteht aus einem vertikalen Buchstaben (`"t"`, `"c"`, `"b"`) gefolgt von einem horizontalen (`"l"`,
  `"m"`, `"r"`), z. B. `"bl"` oder `"cm"`.
- `font` ist eines von `"primary"`, `"secondary"`, `"keyboard"`, `"big_numbers"`.

Struktur **ButtonEvent**:

- `key`: die gedrückte Taste (`"left" | "center" | "right"`);
- `type`: die Ereignisart (`"press" | "release" | "short" | "long" | "repeat"`).

| Ereignis | Typ des Items | Beschreibung |
|---|---|---|
| `button` | `ButtonEvent` | Wird ausgelöst, wenn eine der drei Schaltflächen gedrückt wird, sofern es ein passendes `button`-Element gibt |

```js
let stopwatchWidgetElements = [
    { element: "string", x: 67, y: 44, align: "bl", font: "big_numbers", text: "00 00" },
    { element: "button", button: "right", text: "Back" },
];
let widget = widgetView.makeWith({}, stopwatchWidgetElements);
```

## File picker {#file-picker}

Keine View wie die anderen, sondern einfach eine Funktion, die einen Dateiauswahl-Dialog zeigt.

```js
let filePicker = require("gui/file_picker");
```

### pickFile()
Zeigt einen File Picker und gibt die ausgewählte Datei zurück oder `undefined`, wenn abgebrochen wurde.

- **Parameter:**
  - `basePath`: der Pfad, an dem begonnen wird;
  - `extension`: anzuzeigende Dateiendung(en) (etwa `.sub`, `.iso|.img`, `*`).
- **Rückgabe:** ein `string`-Pfad oder `undefined`.

## Icons {#icon}

Holt und lädt Icons für Views wie [Menu](#menu), [Button panel](#button-panel) und [Widget](#widget).

```js
let icon = require("gui/icon");
```

### getBuiltin()
Holt ein in der Firmware eingebautes Icon anhand seines Namens und gibt ein `IconData`-Objekt zurück.

Es sind nur einige Icons verfügbar. Die offizielle Dokumentation nennt `"DolphinWait_59x54"` und
`"js_script_10px"`. Die aktuelle Firmware hat außerdem `"off_19x20"`, `"off_hover_19x20"`, `"power_19x20"`,
`"power_hover_19x20"` und das animierte `"Settings_14"`.

- **Parameter:** `icon`, der Name des Icons.

### loadFxbm()
Lädt ein `.fxbm`-Icon (XBM-Flipper-Sprite aus `flipperzero-game-engine`) aus einer Datei und gibt ein
`IconData`-Objekt zurück. Es wird beim Beenden des Skripts automatisch entladen.

- **Parameter:** `path`, der Pfad zur `.fxbm`-Datei.
