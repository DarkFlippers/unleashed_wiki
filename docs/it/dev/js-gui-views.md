---
title: "JavaScript: view della GUI"
sidebarTitle: "JS: view della gui"
order: 280
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__byte_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__dialog.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__empty_screen.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__file_picker.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__icon.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__loading.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__submenu.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_box.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__widget.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages/fz-sdk/gui]
sources: [unleashed-docs, unleashed-src]
---
# View della GUI

Ogni view è un modulo separato, caricato con `require("gui/<name>")`. Ogni modulo di view dipende da `gui`, che a sua volta dipende da `event_loop`, quindi caricali sempre **in questo ordine**:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let submenuView = require("gui/submenu");
```

Leggi prima [GUI](/it/dev/js-gui) per capire come funzionano view, prop, figli e view dispatcher. Tutte le view descritte qui sotto sono usate nell'esempio incluso `/ext/apps/Scripts/js_examples/gui.js`.

| Modulo | Cosa mostra |
|---|---|
| [`gui/submenu`](#submenu) | Elenco scorrevole di voci testuali |
| [`gui/menu`](#menu) | Elenco di voci con icone |
| [`gui/button_menu`](#button-menu) | Elenco di pulsanti |
| [`gui/button_panel`](#button-panel) | Griglia di pulsanti con icone |
| [`gui/vi_list`](#vi-list) | Elenco in stile impostazioni con valori commutabili |
| [`gui/dialog`](#dialog) | Finestra di dialogo con un massimo di 3 pulsanti |
| [`gui/popup`](#popup) | Finestra di dialogo che si chiude allo scadere di un timer |
| [`gui/text_box`](#text-box) | Testo di sola lettura scorrevole |
| [`gui/text_input`](#text-input) | Tastiera di testo |
| [`gui/byte_input`](#byte-input) | Tastiera esadecimale |
| [`gui/number_input`](#number-input) | Tastiera numerica |
| [`gui/loading`](#loading) | Clessidra animata |
| [`gui/empty_screen`](#empty-screen) | Schermata vuota |
| [`gui/widget`](#widget) | Combinazione personalizzata di elementi |
| [`gui/file_picker`](#file-picker) | Richiesta di selezione di un file (funzione, non una view) |
| [`gui/icon`](#icon) | Icone per le altre view (utilità) |

::: tip Unleashed
`menu`, `button_menu`, `button_panel`, `vi_list`, `number_input` e `popup` esistono nel firmware ma non hanno una pagina nella documentazione JS ufficiale. Le loro prop e i loro eventi riportati qui sotto provengono dalle definizioni di tipo dell'SDK (`packages/fz-sdk/gui/*.d.ts`).
:::

## Submenu {#submenu}

![Submenu](/img/dev/js_gui_submenu.png)

```js
let submenuView = require("gui/submenu");
```

| Prop | Tipo | Descrizione |
|---|---|---|
| `header` | `string` | Una singola riga di testo sopra l'elenco |

**Figli:** stringhe, una per voce.

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `chosen` | `number` | Scatta quando l'utente sceglie una voce; l'item è il suo indice |

```js
let menu = submenuView.makeWith({ header: "Choose a demo" }, ["One", "Two", "Exit"]);
```

::: warning
La documentazione più vecchia elenca una prop `items`. Il firmware attuale riceve invece le voci come **figli** (vedi [GUI](/it/dev/js-gui#example)).
:::

## Menu {#menu}

Un elenco di voci selezionabili, ciascuna con un'icona e un'etichetta.

```js
let menuView = require("gui/menu");
```

**Prop:** nessuna. **Figli:** `{ icon: IconData, label: string }` (le icone vengono da [`gui/icon`](#icon)).

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `chosen` | `number` | Indice della voce scelta |

```js
let settingsIcon = icon.getBuiltin("Settings_14");
let menu = menuView.makeWith({}, [
    { label: "One", icon: settingsIcon },
    { label: "Two", icon: settingsIcon },
]);
```

## Button menu {#button-menu}

Un elenco di pulsanti.

```js
let buttonMenuView = require("gui/button_menu");
```

| Prop | Tipo | Descrizione |
|---|---|---|
| `header` | `string` | Intestazione testuale sopra i pulsanti |

**Figli:** `{ type: "common" | "control", label: string }`.

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Indice del pulsante e tipo di input (`"press"`, `"release"`, `"short"`, `"long"`, `"repeat"`) |

```js
let buttonMenu = buttonMenuView.makeWith({ header: "Header" }, [
    { type: "common", label: "Test" },
    { type: "control", label: "Test2" },
]);
```

## Button panel {#button-panel}

Una matrice di pulsanti con icone ed etichette facoltative.

```js
let buttonPanelView = require("gui/button_panel");
```

| Prop | Tipo | Descrizione |
|---|---|---|
| `matrixSizeX` | `number` | Larghezza della griglia immaginaria usata per la navigazione |
| `matrixSizeY` | `number` | Altezza della griglia immaginaria usata per la navigazione |

**Figli** (`x`, `y` sono coordinate dello schermo):

- `{ type: "button", x, y, matrixX, matrixY, icon: IconData, iconSelected: IconData }`
- `{ type: "label", x, y, font: Font, text: string }`
- `{ type: "icon", icon: IconData }`

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Indice del pulsante premuto e tipo di input |

```js
let buttonPanel = buttonPanelView.makeWith({ matrixSizeX: 2, matrixSizeY: 2 }, [
    { type: "button", x: 0, y: 0, matrixX: 0, matrixY: 0, icon: offIcons[0], iconSelected: offIcons[1] },
    { type: "button", x: 30, y: 30, matrixX: 1, matrixY: 1, icon: powerIcons[0], iconSelected: powerIcons[1] },
    { type: "label", x: 0, y: 50, text: "Label", font: "primary" },
]);
```

## Variable item list {#vi-list}

Un elenco in stile impostazioni: ogni voce ha un'etichetta e un insieme di valori commutabili con <kbd>←</kbd> / <kbd>→</kbd>.

```js
let viListView = require("gui/vi_list");
```

**Prop:** nessuna. **Figli:** `{ label: string, variants: string[] }`.

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `valueUpdate` | `{ itemIndex: number, valueIndex: number }` | Scatta quando il valore di una voce cambia |

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

| Prop | Tipo | Descrizione |
|---|---|---|
| `header` | `string` | Testo in grassetto in cima allo schermo |
| `text` | `string` | Testo al centro dello schermo |
| `left` | `string` | Testo del pulsante sinistro. Se non è impostato, il pulsante sinistro è nascosto |
| `center` | `string` | Testo del pulsante centrale. Se non è impostato, il pulsante centrale è nascosto |
| `right` | `string` | Testo del pulsante destro. Se non è impostato, il pulsante destro è nascosto |

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `input` | `string` | Scatta quando viene premuto uno dei pulsanti; l'item è `"left"`, `"center"` o `"right"` |

## Popup {#popup}

Come una finestra di dialogo, ma con un timer integrato.

```js
let popupView = require("gui/popup");
```

| Prop | Tipo | Descrizione |
|---|---|---|
| `header` | `string` | Testo in grassetto in cima allo schermo |
| `text` | `string` | Testo al centro dello schermo |
| `timeout` | `number` | Timeout in ms dopo il quale scatta l'evento. Il conto alla rovescia inizia quando questa proprietà viene assegnata |

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `timeout` | (nessuno) | Scatta allo scadere del timeout |

## Text box {#text-box}

![Text box](/img/dev/js_gui_text_box.png)

Un campo di testo di sola lettura scorrevole.

```js
let textBoxView = require("gui/text_box");
```

| Prop | Tipo | Descrizione |
|---|---|---|
| `text` | `string` | Testo da mostrare |
| `font` | `string` | Carattere: `"text"` o `"hex"` |
| `focus` | `string` | Posizione iniziale di scorrimento: `"start"` o `"end"` |

## Text input {#text-input}

![Text input](/img/dev/js_gui_text_input.png)

Una tastiera a schermo.

```js
let textInputView = require("gui/text_input");
```

| Prop | Tipo | Descrizione |
|---|---|---|
| `minLength` | `number` | Lunghezza minima ammessa del testo |
| `maxLength` | `number` | Lunghezza massima ammessa del testo. Predefinito: `32` |
| `header` | `string` | Una singola riga di testo sopra la tastiera |
| `defaultText` | `string` | Testo mostrato per impostazione predefinita |
| `defaultTextClear` | `boolean` | Se cancellare il testo predefinito alla digitazione del carattere successivo |

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `input` | `string` | Scatta quando l'utente seleziona **Save** e la lunghezza del testo rientra in `minLength`/`maxLength` |

## Byte input {#byte-input}

![Byte input](/img/dev/js_gui_byte_input.png)

Una tastiera esadecimale.

```js
let byteInputView = require("gui/byte_input");
```

| Prop | Tipo | Descrizione |
|---|---|---|
| `length` | `number` | Lunghezza in byte del buffer da modificare |
| `header` | `string` | Una singola riga di testo sopra la tastiera |
| `defaultData` | `Uint8Array` / `ArrayBuffer` | Dati mostrati per impostazione predefinita (non devono superare `length`) |

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `input` | `ArrayBuffer` | Scatta quando l'utente seleziona **Save** |

::: info
La documentazione ufficiale indica `defaultData` come `string`. Il firmware lo legge in realtà come un `ArrayBuffer` (o come un array tipizzato quale `Uint8Array`) e genera un errore se è più lungo di `length`.
:::

## Number input {#number-input}

Una tastiera numerica.

```js
let numberInputView = require("gui/number_input");
```

| Prop | Tipo | Descrizione |
|---|---|---|
| `header` | `string` | Testo in cima allo schermo |
| `minValue` | `number` | Valore minimo ammesso |
| `maxValue` | `number` | Valore massimo ammesso |
| `defaultValue` | `number` | Valore predefinito |

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `input` | `number` | Il numero inserito |

## Loading {#loading}

![Loading](/img/dev/js_gui_loading.png)

Una clessidra animata. **Sopprime tutti gli eventi `navigation`**, quindi l'utente non può uscirne con <kbd>Back</kbd>; cambia view da codice.

```js
let loadingView = require("gui/loading");
```

Nessuna prop.

## Empty screen {#empty-screen}

![Empty screen](/img/dev/js_gui_empty.png)

```js
let emptyView = require("gui/empty_screen");
```

Nessuna prop.

## Widget {#widget}

![Widget](/img/dev/js_gui_widget.png)

Mostra una combinazione di elementi personalizzati su un'unica schermata.

```js
let widgetView = require("gui/widget");
```

**Prop:** nessuna. **Figli:** elementi nella forma `{ element: "type", ...properties }`, per esempio `{ element: "button", button: "right", text: "Back" }`.

| Elemento | Proprietà | Descrizione |
|---|---|---|
| `string_multiline` | `x`, `y` (number); `align`; `font`; `text` (string) | Testo che può occupare più righe |
| `string` | `x`, `y` (number); `align`; `font`; `text` (string) | Singola stringa di testo |
| `text_box` | `x`, `y`, `w`, `h` (number); `align`; `text` (string); `stripToDots` (boolean) | Riquadro con testo scorrevole verticalmente |
| `text_scroll` | `x`, `y`, `w`, `h` (number); `text` (string) | Testo scorrevole verticalmente |
| `button` | `text` (string); `button` (`"left"`, `"center"`, `"right"`) | Pulsante nella parte inferiore dello schermo |
| `icon` | `x`, `y` (number); `iconData` ([IconData](#icon)) | Un'icona |
| `rect` | `x`, `y`, `w`, `h` (number); `radius` (number), `fill` (boolean) | Rettangolo, eventualmente arrotondato e riempito |
| `circle` | `x`, `y` (number); `radius` (number), `fill` (boolean) | Cerchio, eventualmente riempito |
| `line` | `x1`, `y1`, `x2`, `y2` (number) | Linea tra due punti |

- `align` è una lettera verticale (`"t"`, `"c"`, `"b"`) seguita da una orizzontale (`"l"`, `"m"`, `"r"`), per esempio `"bl"` o `"cm"`.
- `font` è uno tra `"primary"`, `"secondary"`, `"keyboard"`, `"big_numbers"`.

Struttura **ButtonEvent**:

- `key`: il tasto premuto (`"left" | "center" | "right"`);
- `type`: il tipo di evento (`"press" | "release" | "short" | "long" | "repeat"`).

| Evento | Tipo dell'item | Descrizione |
|---|---|---|
| `button` | `ButtonEvent` | Scatta quando viene premuto uno dei tre pulsanti, se esiste un elemento `button` corrispondente |

```js
let stopwatchWidgetElements = [
    { element: "string", x: 67, y: 44, align: "bl", font: "big_numbers", text: "00 00" },
    { element: "button", button: "right", text: "Back" },
];
let widget = widgetView.makeWith({}, stopwatchWidgetElements);
```

## File picker {#file-picker}

Non è una view come le altre, ma soltanto una funzione che mostra una richiesta di selezione di un file.

```js
let filePicker = require("gui/file_picker");
```

### pickFile()
Mostra un selettore di file e restituisce il file scelto, oppure `undefined` se l'operazione viene annullata.

- **Parametri:**
  - `basePath`: il percorso da cui partire;
  - `extension`: l'estensione o le estensioni dei file da mostrare (come `.sub`, `.iso|.img`, `*`).
- **Restituisce:** un percorso di tipo `string`, oppure `undefined`.

## Icone {#icon}

Recupera e carica le icone per view come [Menu](#menu), [Button panel](#button-panel) e [Widget](#widget).

```js
let icon = require("gui/icon");
```

### getBuiltin()
Recupera un'icona integrata nel firmware in base al nome e restituisce un oggetto `IconData`.

Sono disponibili solo alcune icone. La documentazione ufficiale cita `"DolphinWait_59x54"` e `"js_script_10px"`. Il firmware attuale ha anche `"off_19x20"`, `"off_hover_19x20"`, `"power_19x20"`, `"power_hover_19x20"` e l'animata `"Settings_14"`.

- **Parametri:** `icon`, il nome dell'icona.

### loadFxbm()
Carica da file un'icona `.fxbm` (sprite XBM del Flipper, da `flipperzero-game-engine`) e restituisce un oggetto `IconData`. Viene scaricata automaticamente all'uscita dallo script.

- **Parametri:** `path`, il percorso del file `.fxbm`.
