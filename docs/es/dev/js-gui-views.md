---
title: "JavaScript: vistas de la GUI"
sidebarTitle: "JS: vistas de la gui"
order: 280
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__byte_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__dialog.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__empty_screen.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__file_picker.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__icon.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__loading.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__submenu.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_box.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__widget.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages/fz-sdk/gui]
sources: [unleashed-docs, unleashed-src]
---
# Vistas de la GUI

Cada vista es un módulo aparte que se carga con `require("gui/<name>")`. Todos los módulos de vista dependen de `gui`, que a su vez depende de `event_loop`, así que cárgalos siempre **en este orden**:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let submenuView = require("gui/submenu");
```

Lee primero [GUI](/es/dev/js-gui) para entender cómo funcionan las vistas, las props, los hijos y el view dispatcher. Todas las vistas de abajo se usan en el ejemplo incluido `/ext/apps/Scripts/js_examples/gui.js`.

| Módulo | Qué muestra |
|---|---|
| [`gui/submenu`](#submenu) | Lista desplazable de entradas de texto |
| [`gui/menu`](#menu) | Lista de entradas con iconos |
| [`gui/button_menu`](#button-menu) | Lista de botones |
| [`gui/button_panel`](#button-panel) | Cuadrícula de botones con iconos |
| [`gui/vi_list`](#vi-list) | Lista estilo ajustes con valores conmutables |
| [`gui/dialog`](#dialog) | Diálogo con hasta 3 botones |
| [`gui/popup`](#popup) | Diálogo que se cierra con un temporizador |
| [`gui/text_box`](#text-box) | Texto de solo lectura desplazable |
| [`gui/text_input`](#text-input) | Teclado de texto |
| [`gui/byte_input`](#byte-input) | Teclado hexadecimal |
| [`gui/number_input`](#number-input) | Teclado numérico |
| [`gui/loading`](#loading) | Reloj de arena animado |
| [`gui/empty_screen`](#empty-screen) | Pantalla en blanco |
| [`gui/widget`](#widget) | Combinación personalizada de elementos |
| [`gui/file_picker`](#file-picker) | Diálogo de selección de archivo (una función, no una vista) |
| [`gui/icon`](#icon) | Iconos para otras vistas (utilidad) |

::: tip Unleashed
`menu`, `button_menu`, `button_panel`, `vi_list`, `number_input` y `popup` existen en el firmware pero no tienen página en la documentación oficial de JS. Sus props y eventos, que aparecen abajo, provienen de las declaraciones de tipos del SDK (`packages/fz-sdk/gui/*.d.ts`).
:::

## Submenu {#submenu}

![Submenu](/img/dev/js_gui_submenu.png)

```js
let submenuView = require("gui/submenu");
```

| Prop | Tipo | Descripción |
|---|---|---|
| `header` | `string` | Una única línea de texto encima de la lista |

**Hijos:** cadenas, una por entrada.

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `chosen` | `number` | Se dispara cuando el usuario elige una entrada; el elemento es su índice |

```js
let menu = submenuView.makeWith({ header: "Choose a demo" }, ["One", "Two", "Exit"]);
```

::: warning
La documentación más antigua menciona una prop `items`. El firmware actual toma las entradas como **hijos** (consulta [GUI](/es/dev/js-gui#example)).
:::

## Menu {#menu}

Una lista de entradas seleccionables, cada una con un icono y una etiqueta.

```js
let menuView = require("gui/menu");
```

**Props:** ninguna. **Hijos:** `{ icon: IconData, label: string }` (los iconos vienen de [`gui/icon`](#icon)).

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `chosen` | `number` | Índice de la entrada elegida |

```js
let settingsIcon = icon.getBuiltin("Settings_14");
let menu = menuView.makeWith({}, [
    { label: "One", icon: settingsIcon },
    { label: "Two", icon: settingsIcon },
]);
```

## Button menu {#button-menu}

Una lista de botones.

```js
let buttonMenuView = require("gui/button_menu");
```

| Prop | Tipo | Descripción |
|---|---|---|
| `header` | `string` | Encabezado de texto encima de los botones |

**Hijos:** `{ type: "common" | "control", label: string }`.

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Índice del botón y tipo de entrada (`"press"`, `"release"`, `"short"`, `"long"`, `"repeat"`) |

```js
let buttonMenu = buttonMenuView.makeWith({ header: "Header" }, [
    { type: "common", label: "Test" },
    { type: "control", label: "Test2" },
]);
```

## Button panel {#button-panel}

Una matriz de botones con iconos y etiquetas opcionales.

```js
let buttonPanelView = require("gui/button_panel");
```

| Prop | Tipo | Descripción |
|---|---|---|
| `matrixSizeX` | `number` | Ancho de la cuadrícula imaginaria que se usa para la navegación |
| `matrixSizeY` | `number` | Alto de la cuadrícula imaginaria que se usa para la navegación |

**Hijos** (`x`, `y` son coordenadas de pantalla):

- `{ type: "button", x, y, matrixX, matrixY, icon: IconData, iconSelected: IconData }`
- `{ type: "label", x, y, font: Font, text: string }`
- `{ type: "icon", icon: IconData }`

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Índice del botón pulsado y tipo de entrada |

```js
let buttonPanel = buttonPanelView.makeWith({ matrixSizeX: 2, matrixSizeY: 2 }, [
    { type: "button", x: 0, y: 0, matrixX: 0, matrixY: 0, icon: offIcons[0], iconSelected: offIcons[1] },
    { type: "button", x: 30, y: 30, matrixX: 1, matrixY: 1, icon: powerIcons[0], iconSelected: powerIcons[1] },
    { type: "label", x: 0, y: 50, text: "Label", font: "primary" },
]);
```

## Lista de elementos variables {#vi-list}

Una lista estilo ajustes: cada elemento tiene una etiqueta y un conjunto de valores que se cambian con <kbd>←</kbd> / <kbd>→</kbd>.

```js
let viListView = require("gui/vi_list");
```

**Props:** ninguna. **Hijos:** `{ label: string, variants: string[] }`.

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `valueUpdate` | `{ itemIndex: number, valueIndex: number }` | Se dispara cuando cambia el valor de un elemento |

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

| Prop | Tipo | Descripción |
|---|---|---|
| `header` | `string` | Texto en negrita en la parte superior de la pantalla |
| `text` | `string` | Texto en el centro de la pantalla |
| `left` | `string` | Texto del botón izquierdo. Si no se define, el botón izquierdo se oculta |
| `center` | `string` | Texto del botón central. Si no se define, el botón central se oculta |
| `right` | `string` | Texto del botón derecho. Si no se define, el botón derecho se oculta |

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `input` | `string` | Se dispara al pulsar uno de los botones; el elemento es `"left"`, `"center"` o `"right"` |

## Popup {#popup}

Como un diálogo, pero con un temporizador integrado.

```js
let popupView = require("gui/popup");
```

| Prop | Tipo | Descripción |
|---|---|---|
| `header` | `string` | Texto en negrita en la parte superior de la pantalla |
| `text` | `string` | Texto en el centro de la pantalla |
| `timeout` | `number` | Tiempo de espera en ms tras el cual se dispara el evento. La cuenta atrás empieza al asignar esta propiedad |

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `timeout` | (ninguno) | Se dispara cuando expira el tiempo de espera |

## Text box {#text-box}

![Text box](/img/dev/js_gui_text_box.png)

Un campo de texto de solo lectura y desplazable.

```js
let textBoxView = require("gui/text_box");
```

| Prop | Tipo | Descripción |
|---|---|---|
| `text` | `string` | Texto que se muestra |
| `font` | `string` | Fuente: `"text"` o `"hex"` |
| `focus` | `string` | Posición inicial del desplazamiento: `"start"` o `"end"` |

## Text input {#text-input}

![Text input](/img/dev/js_gui_text_input.png)

Un teclado en pantalla.

```js
let textInputView = require("gui/text_input");
```

| Prop | Tipo | Descripción |
|---|---|---|
| `minLength` | `number` | Longitud mínima de texto permitida |
| `maxLength` | `number` | Longitud máxima de texto permitida. Por defecto: `32` |
| `header` | `string` | Una única línea de texto encima del teclado |
| `defaultText` | `string` | Texto que se muestra por defecto |
| `defaultTextClear` | `boolean` | Si se borra el texto por defecto al escribir el siguiente carácter |

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `input` | `string` | Se dispara cuando el usuario elige **Save** y la longitud del texto encaja con `minLength`/`maxLength` |

## Byte input {#byte-input}

![Byte input](/img/dev/js_gui_byte_input.png)

Un teclado hexadecimal.

```js
let byteInputView = require("gui/byte_input");
```

| Prop | Tipo | Descripción |
|---|---|---|
| `length` | `number` | Longitud en bytes del búfer que se edita |
| `header` | `string` | Una única línea de texto encima del teclado |
| `defaultData` | `Uint8Array` / `ArrayBuffer` | Datos que se muestran por defecto (no pueden ser más largos que `length`) |

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `input` | `ArrayBuffer` | Se dispara cuando el usuario elige **Save** |

::: info
La documentación oficial indica que `defaultData` es de tipo `string`. En realidad el firmware lo lee como un `ArrayBuffer` (o un typed array como `Uint8Array`) y da error si es más largo que `length`.
:::

## Number input {#number-input}

Un teclado numérico.

```js
let numberInputView = require("gui/number_input");
```

| Prop | Tipo | Descripción |
|---|---|---|
| `header` | `string` | Texto en la parte superior de la pantalla |
| `minValue` | `number` | Valor mínimo permitido |
| `maxValue` | `number` | Valor máximo permitido |
| `defaultValue` | `number` | Valor por defecto |

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `input` | `number` | El número introducido |

## Loading {#loading}

![Loading](/img/dev/js_gui_loading.png)

Un reloj de arena animado. **Suprime todos los eventos `navigation`**, así que el usuario no puede salir de él con <kbd>Back</kbd>; cambia de vista desde el código.

```js
let loadingView = require("gui/loading");
```

Sin props.

## Empty screen {#empty-screen}

![Empty screen](/img/dev/js_gui_empty.png)

```js
let emptyView = require("gui/empty_screen");
```

Sin props.

## Widget {#widget}

![Widget](/img/dev/js_gui_widget.png)

Muestra una combinación de elementos personalizados en una sola pantalla.

```js
let widgetView = require("gui/widget");
```

**Props:** ninguna. **Hijos:** elementos con la forma `{ element: "type", ...properties }`, por ejemplo `{ element: "button", button: "right", text: "Back" }`.

| Elemento | Propiedades | Descripción |
|---|---|---|
| `string_multiline` | `x`, `y` (number); `align`; `font`; `text` (string) | Texto que puede ocupar varias líneas |
| `string` | `x`, `y` (number); `align`; `font`; `text` (string) | Una sola línea de texto |
| `text_box` | `x`, `y`, `w`, `h` (number); `align`; `text` (string); `stripToDots` (boolean) | Cuadro con texto desplazable verticalmente |
| `text_scroll` | `x`, `y`, `w`, `h` (number); `text` (string) | Texto desplazable verticalmente |
| `button` | `text` (string); `button` (`"left"`, `"center"`, `"right"`) | Botón en la parte inferior de la pantalla |
| `icon` | `x`, `y` (number); `iconData` ([IconData](#icon)) | Un icono |
| `rect` | `x`, `y`, `w`, `h` (number); `radius` (number), `fill` (boolean) | Rectángulo, opcionalmente redondeado y relleno |
| `circle` | `x`, `y` (number); `radius` (number), `fill` (boolean) | Círculo, opcionalmente relleno |
| `line` | `x1`, `y1`, `x2`, `y2` (number) | Línea entre dos puntos |

- `align` es una letra vertical (`"t"`, `"c"`, `"b"`) seguida de otra horizontal (`"l"`, `"m"`, `"r"`), por ejemplo `"bl"` o `"cm"`.
- `font` es uno de estos valores: `"primary"`, `"secondary"`, `"keyboard"`, `"big_numbers"`.

Estructura **ButtonEvent**:

- `key`: la tecla pulsada (`"left" | "center" | "right"`);
- `type`: el tipo de evento (`"press" | "release" | "short" | "long" | "repeat"`).

| Evento | Tipo del elemento | Descripción |
|---|---|---|
| `button` | `ButtonEvent` | Se dispara al pulsar uno de los tres botones, si hay un elemento `button` que coincida |

```js
let stopwatchWidgetElements = [
    { element: "string", x: 67, y: 44, align: "bl", font: "big_numbers", text: "00 00" },
    { element: "button", button: "right", text: "Back" },
];
let widget = widgetView.makeWith({}, stopwatchWidgetElements);
```

## File picker {#file-picker}

No es una vista como las demás, solo una función que muestra un diálogo de selección de archivo.

```js
let filePicker = require("gui/file_picker");
```

### pickFile()
Muestra un selector de archivos y devuelve el archivo seleccionado, o `undefined` si se cancela.

- **Parámetros:**
  - `basePath`: la ruta en la que empezar;
  - `extension`: la extensión o extensiones de archivo que se muestran (como `.sub`, `.iso|.img`, `*`).
- **Devuelve:** una ruta de tipo `string`, o `undefined`.

## Iconos {#icon}

Obtiene y carga iconos para vistas como [Menu](#menu), [Button panel](#button-panel) y [Widget](#widget).

```js
let icon = require("gui/icon");
```

### getBuiltin()
Obtiene por su nombre un icono integrado en el firmware y devuelve un objeto `IconData`.

Solo algunos iconos están disponibles. La documentación oficial menciona `"DolphinWait_59x54"` y `"js_script_10px"`. El firmware actual tiene además `"off_19x20"`, `"off_hover_19x20"`, `"power_19x20"`, `"power_hover_19x20"` y el animado `"Settings_14"`.

- **Parámetros:** `icon`, el nombre del icono.

### loadFxbm()
Carga desde un archivo un icono `.fxbm` (sprite XBM del Flipper, de `flipperzero-game-engine`) y devuelve un objeto `IconData`. Se descarga automáticamente cuando el script termina.

- **Parámetros:** `path`, la ruta del archivo `.fxbm`.
