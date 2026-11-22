---
title: "JavaScript: GUI prikazi"
sidebarTitle: "JS: gui prikazi"
order: 280
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__byte_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__dialog.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__empty_screen.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__file_picker.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__icon.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__loading.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__submenu.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_box.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__widget.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages/fz-sdk/gui]
sources: [unleashed-docs, unleashed-src]
---
# GUI prikazi

Svaki prikaz je zaseban modul koji se učitava putem `require("gui/<name>")`. Svaki modul prikaza ovisi o modulu `gui`, koji ovisi o modulu `event_loop`, stoga ih uvijek učitavajte **ovim redoslijedom**:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let submenuView = require("gui/submenu");
```

Prvo pročitajte [GUI](/hr/dev/js-gui) kako biste vidjeli kako rade prikazi, svojstva (props), djeca (children) i upravljač prikaza (view dispatcher). Svi prikazi u nastavku koriste se u priloženom primjeru `/ext/apps/Scripts/js_examples/gui.js`.

| Modul | Što prikazuje |
|---|---|
| [`gui/submenu`](#submenu) | Klizni popis tekstualnih stavki |
| [`gui/menu`](#menu) | Popis stavki s ikonama |
| [`gui/button_menu`](#button-menu) | Popis tipki |
| [`gui/button_panel`](#button-panel) | Mreža ikonskih tipki |
| [`gui/vi_list`](#vi-list) | Popis u stilu postavki s izmjenjivim vrijednostima |
| [`gui/dialog`](#dialog) | Dijalog s do 3 tipke |
| [`gui/popup`](#popup) | Dijalog koji se zatvara nakon isteka vremena |
| [`gui/text_box`](#text-box) | Klizni tekst samo za čitanje |
| [`gui/text_input`](#text-input) | Tekstualna tipkovnica |
| [`gui/byte_input`](#byte-input) | Heksadecimalna tipkovnica |
| [`gui/number_input`](#number-input) | Brojčana tipkovnica |
| [`gui/loading`](#loading) | Animirani pješčani sat |
| [`gui/empty_screen`](#empty-screen) | Prazan zaslon |
| [`gui/widget`](#widget) | Prilagođena kombinacija elemenata |
| [`gui/file_picker`](#file-picker) | Upit za odabir datoteke (funkcija, nije prikaz) |
| [`gui/icon`](#icon) | Ikone za druge prikaze (pomoćni modul) |

::: tip Unleashed
`menu`, `button_menu`, `button_panel`, `vi_list`, `number_input` i `popup` postoje u firmveru, ali nemaju stranicu u službenoj JS dokumentaciji. Njihova svojstva i događaji u nastavku preuzeti su iz SDK definicija tipova (`packages/fz-sdk/gui/*.d.ts`).
:::

## Submenu {#submenu}

![Submenu](/img/dev/js_gui_submenu.png)

```js
let submenuView = require("gui/submenu");
```

| Svojstvo | Tip | Opis |
|---|---|---|
| `header` | `string` | Jedan redak teksta iznad popisa |

**Djeca:** znakovni nizovi (`string`), po jedan za svaku stavku.

| Događaj | Tip stavke | Opis |
|---|---|---|
| `chosen` | `number` | Pokreće se kada korisnik odabere stavku; vrijednost je njezin indeks |

```js
let menu = submenuView.makeWith({ header: "Choose a demo" }, ["One", "Two", "Exit"]);
```

::: warning
Starija dokumentacija navodi svojstvo `items`. Trenutni firmver umjesto toga prima stavke kao **djecu** (pogledajte [GUI](/hr/dev/js-gui#example)).
:::

## Menu {#menu}

Popis stavki koje se mogu odabrati, svaka s ikonom i oznakom.

```js
let menuView = require("gui/menu");
```

**Svojstva:** nema. **Djeca:** `{ icon: IconData, label: string }` (ikone iz [`gui/icon`](#icon)).

| Događaj | Tip stavke | Opis |
|---|---|---|
| `chosen` | `number` | Indeks odabrane stavke |

```js
let settingsIcon = icon.getBuiltin("Settings_14");
let menu = menuView.makeWith({}, [
    { label: "One", icon: settingsIcon },
    { label: "Two", icon: settingsIcon },
]);
```

## Button menu {#button-menu}

Popis tipki.

```js
let buttonMenuView = require("gui/button_menu");
```

| Svojstvo | Tip | Opis |
|---|---|---|
| `header` | `string` | Tekstualno zaglavlje iznad tipki |

**Djeca:** `{ type: "common" | "control", label: string }`.

| Događaj | Tip stavke | Opis |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Indeks tipke i vrsta unosa (`"press"`, `"release"`, `"short"`, `"long"`, `"repeat"`) |

```js
let buttonMenu = buttonMenuView.makeWith({ header: "Header" }, [
    { type: "common", label: "Test" },
    { type: "control", label: "Test2" },
]);
```

## Button panel {#button-panel}

Matrica ikonskih tipki s neobaveznim oznakama.

```js
let buttonPanelView = require("gui/button_panel");
```

| Svojstvo | Tip | Opis |
|---|---|---|
| `matrixSizeX` | `number` | Širina zamišljene mreže za navigaciju |
| `matrixSizeY` | `number` | Visina zamišljene mreže za navigaciju |

**Djeca** (`x`, `y` su koordinate na zaslonu):

- `{ type: "button", x, y, matrixX, matrixY, icon: IconData, iconSelected: IconData }`
- `{ type: "label", x, y, font: Font, text: string }`
- `{ type: "icon", icon: IconData }`

| Događaj | Tip stavke | Opis |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Indeks pritisnute tipke i vrsta unosa |

```js
let buttonPanel = buttonPanelView.makeWith({ matrixSizeX: 2, matrixSizeY: 2 }, [
    { type: "button", x: 0, y: 0, matrixX: 0, matrixY: 0, icon: offIcons[0], iconSelected: offIcons[1] },
    { type: "button", x: 30, y: 30, matrixX: 1, matrixY: 1, icon: powerIcons[0], iconSelected: powerIcons[1] },
    { type: "label", x: 0, y: 50, text: "Label", font: "primary" },
]);
```

## Variable item list {#vi-list}

Popis u stilu postavki: svaka stavka ima oznaku i skup vrijednosti koje se mijenjaju tipkama <kbd>←</kbd> / <kbd>→</kbd>.

```js
let viListView = require("gui/vi_list");
```

**Svojstva:** nema. **Djeca:** `{ label: string, variants: string[] }`.

| Događaj | Tip stavke | Opis |
|---|---|---|
| `valueUpdate` | `{ itemIndex: number, valueIndex: number }` | Pokreće se kada se promijeni vrijednost stavke |

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

| Svojstvo | Tip | Opis |
|---|---|---|
| `header` | `string` | Podebljani tekst na vrhu zaslona |
| `text` | `string` | Tekst na sredini zaslona |
| `left` | `string` | Tekst lijeve tipke. Ako nije postavljeno, lijeva tipka je skrivena |
| `center` | `string` | Tekst središnje tipke. Ako nije postavljeno, središnja tipka je skrivena |
| `right` | `string` | Tekst desne tipke. Ako nije postavljeno, desna tipka je skrivena |

| Događaj | Tip stavke | Opis |
|---|---|---|
| `input` | `string` | Pokreće se kada se pritisne jedna od tipki; vrijednost je `"left"`, `"center"` ili `"right"` |

## Popup {#popup}

Slično dijalogu, ali s ugrađenim odbrojavanjem vremena.

```js
let popupView = require("gui/popup");
```

| Svojstvo | Tip | Opis |
|---|---|---|
| `header` | `string` | Podebljani tekst na vrhu zaslona |
| `text` | `string` | Tekst na sredini zaslona |
| `timeout` | `number` | Vrijeme isteka u ms nakon kojeg se događaj pokreće. Odbrojavanje počinje kada se dodijeli ovo svojstvo |

| Događaj | Tip stavke | Opis |
|---|---|---|
| `timeout` | (nema) | Pokreće se kada vrijeme istekne |

## Text box {#text-box}

![Text box](/img/dev/js_gui_text_box.png)

Klizno tekstualno polje samo za čitanje.

```js
let textBoxView = require("gui/text_box");
```

| Svojstvo | Tip | Opis |
|---|---|---|
| `text` | `string` | Tekst za prikaz |
| `font` | `string` | Font: `"text"` ili `"hex"` |
| `focus` | `string` | Početni položaj klizanja: `"start"` ili `"end"` |

## Text input {#text-input}

![Text input](/img/dev/js_gui_text_input.png)

Zaslonska tipkovnica.

```js
let textInputView = require("gui/text_input");
```

| Svojstvo | Tip | Opis |
|---|---|---|
| `minLength` | `number` | Najkraća dopuštena duljina teksta |
| `maxLength` | `number` | Najveća dopuštena duljina teksta. Zadano: `32` |
| `header` | `string` | Jedan redak teksta iznad tipkovnice |
| `defaultText` | `string` | Tekst koji se prikazuje po zadanim postavkama |
| `defaultTextClear` | `boolean` | Treba li obrisati zadani tekst pri upisu sljedećeg znaka |

| Događaj | Tip stavke | Opis |
|---|---|---|
| `input` | `string` | Pokreće se kada korisnik odabere **Save**, a duljina teksta odgovara `minLength`/`maxLength` |

## Byte input {#byte-input}

![Byte input](/img/dev/js_gui_byte_input.png)

Heksadecimalna tipkovnica.

```js
let byteInputView = require("gui/byte_input");
```

| Svojstvo | Tip | Opis |
|---|---|---|
| `length` | `number` | Duljina međuspremnika za uređivanje u bajtovima |
| `header` | `string` | Jedan redak teksta iznad tipkovnice |
| `defaultData` | `Uint8Array` / `ArrayBuffer` | Podaci prikazani po zadanim postavkama (ne smiju biti dulji od `length`) |

| Događaj | Tip stavke | Opis |
|---|---|---|
| `input` | `ArrayBuffer` | Pokreće se kada korisnik odabere **Save** |

::: info
Službena dokumentacija navodi `defaultData` kao `string`. Firmver ga zapravo čita kao `ArrayBuffer` (ili tipizirano polje kao što je `Uint8Array`) i javlja pogrešku ako je dulji od `length`.
:::

## Number input {#number-input}

Brojčana tipkovnica.

```js
let numberInputView = require("gui/number_input");
```

| Svojstvo | Tip | Opis |
|---|---|---|
| `header` | `string` | Tekst na vrhu zaslona |
| `minValue` | `number` | Najmanja dopuštena vrijednost |
| `maxValue` | `number` | Najveća dopuštena vrijednost |
| `defaultValue` | `number` | Zadana vrijednost |

| Događaj | Tip stavke | Opis |
|---|---|---|
| `input` | `number` | Uneseni broj |

## Loading {#loading}

![Loading](/img/dev/js_gui_loading.png)

Animirani pješčani sat. **Potiskuje sve `navigation` događaje**, pa ga korisnik ne može napustiti tipkom <kbd>Back</kbd>; prebacite se s njega u kodu.

```js
let loadingView = require("gui/loading");
```

Nema svojstava.

## Empty screen {#empty-screen}

![Empty screen](/img/dev/js_gui_empty.png)

```js
let emptyView = require("gui/empty_screen");
```

Nema svojstava.

## Widget {#widget}

![Widget](/img/dev/js_gui_widget.png)

Prikazuje kombinaciju prilagođenih elemenata na jednom zaslonu.

```js
let widgetView = require("gui/widget");
```

**Svojstva:** nema. **Djeca:** elementi u obliku `{ element: "type", ...properties }`, npr. `{ element: "button", button: "right", text: "Back" }`.

| Element | Svojstva | Opis |
|---|---|---|
| `string_multiline` | `x`, `y` (number); `align`; `font`; `text` (string) | Tekst koji se može protezati kroz više redaka |
| `string` | `x`, `y` (number); `align`; `font`; `text` (string) | Jedan redak teksta |
| `text_box` | `x`, `y`, `w`, `h` (number); `align`; `text` (string); `stripToDots` (boolean) | Okvir s okomito kliznim tekstom |
| `text_scroll` | `x`, `y`, `w`, `h` (number); `text` (string) | Okomito klizni tekst |
| `button` | `text` (string); `button` (`"left"`, `"center"`, `"right"`) | Tipka na dnu zaslona |
| `icon` | `x`, `y` (number); `iconData` ([IconData](#icon)) | Ikona |
| `rect` | `x`, `y`, `w`, `h` (number); `radius` (number), `fill` (boolean) | Pravokutnik, po izboru zaobljen i ispunjen |
| `circle` | `x`, `y` (number); `radius` (number), `fill` (boolean) | Kružnica, po izboru ispunjena |
| `line` | `x1`, `y1`, `x2`, `y2` (number) | Crta između dviju točaka |

- `align` je okomito slovo (`"t"`, `"c"`, `"b"`) iza kojeg slijedi vodoravno slovo (`"l"`, `"m"`, `"r"`), npr. `"bl"` ili `"cm"`.
- `font` je jedno od `"primary"`, `"secondary"`, `"keyboard"`, `"big_numbers"`.

Struktura **ButtonEvent**:

- `key`: pritisnuta tipka (`"left" | "center" | "right"`);
- `type`: vrsta događaja (`"press" | "release" | "short" | "long" | "repeat"`).

| Događaj | Tip stavke | Opis |
|---|---|---|
| `button` | `ButtonEvent` | Pokreće se kada se pritisne jedna od triju tipki, ako postoji odgovarajući element `button` |

```js
let stopwatchWidgetElements = [
    { element: "string", x: 67, y: 44, align: "bl", font: "big_numbers", text: "00 00" },
    { element: "button", button: "right", text: "Back" },
];
let widget = widgetView.makeWith({}, stopwatchWidgetElements);
```

## Birač datoteka {#file-picker}

Nije prikaz poput ostalih, već samo funkcija koja prikazuje upit za odabir datoteke.

```js
let filePicker = require("gui/file_picker");
```

### pickFile()
Prikazuje birač datoteka i vraća odabranu datoteku ili `undefined` ako se odustane.

- **Parametri:**
  - `basePath`: početna putanja;
  - `extension`: datotečni nastavci za prikaz (npr. `.sub`, `.iso|.img`, `*`).
- **Povratna vrijednost:** putanja tipa `string` ili `undefined`.

## Ikone {#icon}

Dohvaća i učitava ikone za prikaze kao što su [Menu](#menu), [Button panel](#button-panel) i [Widget](#widget).

```js
let icon = require("gui/icon");
```

### getBuiltin()
Dohvaća ugrađenu ikonu firmvera po nazivu i vraća objekt `IconData`.

Dostupne su samo neke ikone. Službena dokumentacija navodi `"DolphinWait_59x54"` i `"js_script_10px"`. Trenutni firmver također ima `"off_19x20"`, `"off_hover_19x20"`, `"power_19x20"`, `"power_hover_19x20"` te animiranu `"Settings_14"`.

- **Parametri:** `icon`, naziv ikone.

### loadFxbm()
Učitava ikonu `.fxbm` (XBM Flipper sprite iz `flipperzero-game-engine`) iz datoteke i vraća objekt `IconData`. Automatski se oslobađa iz memorije kada skripta završi.

- **Parametri:** `path`, putanja do datoteke `.fxbm`.
