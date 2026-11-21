---
title: "JavaScript : vues GUI"
sidebarTitle: "JS : vues gui"
order: 280
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__byte_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__dialog.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__empty_screen.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__file_picker.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__icon.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__loading.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__submenu.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_box.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__text_input.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui__widget.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages/fz-sdk/gui]
sources: [unleashed-docs, unleashed-src]
---
# Vues GUI

Chaque vue est un module distinct chargé avec `require("gui/<name>")`. Tout module de vue dépend de `gui`, qui dépend
d'`event_loop` : chargez-les donc toujours **dans cet ordre**.

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let submenuView = require("gui/submenu");
```

Lisez d'abord [GUI](/fr/dev/js-gui) pour comprendre le fonctionnement des vues, des propriétés, des enfants et du view
dispatcher. Toutes les vues ci-dessous sont utilisées dans l'exemple fourni
`/ext/apps/Scripts/js_examples/gui.js`.

| Module | Ce qu'il affiche |
|---|---|
| [`gui/submenu`](#submenu) | Liste défilante d'entrées textuelles |
| [`gui/menu`](#menu) | Liste d'entrées avec icônes |
| [`gui/button_menu`](#button-menu) | Liste de boutons |
| [`gui/button_panel`](#button-panel) | Grille de boutons à icônes |
| [`gui/vi_list`](#vi-list) | Liste façon réglages avec valeurs commutables |
| [`gui/dialog`](#dialog) | Boîte de dialogue avec jusqu'à 3 boutons |
| [`gui/popup`](#popup) | Boîte de dialogue qui se ferme sur minuteur |
| [`gui/text_box`](#text-box) | Texte défilant en lecture seule |
| [`gui/text_input`](#text-input) | Clavier texte |
| [`gui/byte_input`](#byte-input) | Clavier hexadécimal |
| [`gui/number_input`](#number-input) | Clavier numérique |
| [`gui/loading`](#loading) | Sablier animé |
| [`gui/empty_screen`](#empty-screen) | Écran vide |
| [`gui/widget`](#widget) | Combinaison personnalisée d'éléments |
| [`gui/file_picker`](#file-picker) | Invite de sélection de fichier (une fonction, pas une vue) |
| [`gui/icon`](#icon) | Icônes pour les autres vues (utilitaire) |

::: tip Unleashed
`menu`, `button_menu`, `button_panel`, `vi_list`, `number_input` et `popup` existent dans le firmware mais n'ont pas de
page dans la documentation JS officielle. Leurs propriétés et événements ci-dessous proviennent des typages du SDK
(`packages/fz-sdk/gui/*.d.ts`).
:::

## Submenu {#submenu}

![Submenu](/img/dev/js_gui_submenu.png)

```js
let submenuView = require("gui/submenu");
```

| Propriété | Type | Description |
|---|---|---|
| `header` | `string` | Une seule ligne de texte au-dessus de la liste |

**Enfants :** des chaînes, une par entrée.

| Événement | Type de l'élément | Description |
|---|---|---|
| `chosen` | `number` | Se déclenche quand l'utilisateur choisit une entrée ; l'élément est son indice |

```js
let menu = submenuView.makeWith({ header: "Choose a demo" }, ["One", "Two", "Exit"]);
```

::: warning
L'ancienne documentation mentionne une propriété `items`. Le firmware actuel prend les entrées comme **enfants** à la
place (voir [GUI](/fr/dev/js-gui#example)).
:::

## Menu {#menu}

Une liste d'entrées sélectionnables, chacune avec une icône et un libellé.

```js
let menuView = require("gui/menu");
```

**Propriétés :** aucune. **Enfants :** `{ icon: IconData, label: string }` (icônes issues de
[`gui/icon`](#icon)).

| Événement | Type de l'élément | Description |
|---|---|---|
| `chosen` | `number` | Indice de l'entrée choisie |

```js
let settingsIcon = icon.getBuiltin("Settings_14");
let menu = menuView.makeWith({}, [
    { label: "One", icon: settingsIcon },
    { label: "Two", icon: settingsIcon },
]);
```

## Button menu {#button-menu}

Une liste de boutons.

```js
let buttonMenuView = require("gui/button_menu");
```

| Propriété | Type | Description |
|---|---|---|
| `header` | `string` | En-tête textuel au-dessus des boutons |

**Enfants :** `{ type: "common" | "control", label: string }`.

| Événement | Type de l'élément | Description |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Indice du bouton et type d'entrée (`"press"`, `"release"`, `"short"`, `"long"`, `"repeat"`) |

```js
let buttonMenu = buttonMenuView.makeWith({ header: "Header" }, [
    { type: "common", label: "Test" },
    { type: "control", label: "Test2" },
]);
```

## Button panel {#button-panel}

Une matrice de boutons à icônes, avec libellés facultatifs.

```js
let buttonPanelView = require("gui/button_panel");
```

| Propriété | Type | Description |
|---|---|---|
| `matrixSizeX` | `number` | Largeur de la grille imaginaire utilisée pour la navigation |
| `matrixSizeY` | `number` | Hauteur de la grille imaginaire utilisée pour la navigation |

**Enfants** (`x`, `y` sont des coordonnées à l'écran) :

- `{ type: "button", x, y, matrixX, matrixY, icon: IconData, iconSelected: IconData }`
- `{ type: "label", x, y, font: Font, text: string }`
- `{ type: "icon", icon: IconData }`

| Événement | Type de l'élément | Description |
|---|---|---|
| `input` | `{ index: number, type: InputType }` | Indice du bouton pressé et type d'entrée |

```js
let buttonPanel = buttonPanelView.makeWith({ matrixSizeX: 2, matrixSizeY: 2 }, [
    { type: "button", x: 0, y: 0, matrixX: 0, matrixY: 0, icon: offIcons[0], iconSelected: offIcons[1] },
    { type: "button", x: 30, y: 30, matrixX: 1, matrixY: 1, icon: powerIcons[0], iconSelected: powerIcons[1] },
    { type: "label", x: 0, y: 50, text: "Label", font: "primary" },
]);
```

## Variable item list {#vi-list}

Une liste façon réglages : chaque élément possède un libellé et un jeu de valeurs commutées avec
<kbd>←</kbd> / <kbd>→</kbd>.

```js
let viListView = require("gui/vi_list");
```

**Propriétés :** aucune. **Enfants :** `{ label: string, variants: string[] }`.

| Événement | Type de l'élément | Description |
|---|---|---|
| `valueUpdate` | `{ itemIndex: number, valueIndex: number }` | Se déclenche quand la valeur d'un élément change |

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

| Propriété | Type | Description |
|---|---|---|
| `header` | `string` | Texte en gras en haut de l'écran |
| `text` | `string` | Texte au milieu de l'écran |
| `left` | `string` | Texte du bouton gauche. S'il n'est pas défini, le bouton gauche est masqué |
| `center` | `string` | Texte du bouton central. S'il n'est pas défini, le bouton central est masqué |
| `right` | `string` | Texte du bouton droit. S'il n'est pas défini, le bouton droit est masqué |

| Événement | Type de l'élément | Description |
|---|---|---|
| `input` | `string` | Se déclenche lorsqu'un des boutons est pressé ; l'élément vaut `"left"`, `"center"` ou `"right"` |

## Popup {#popup}

Comme une boîte de dialogue, mais avec un minuteur intégré.

```js
let popupView = require("gui/popup");
```

| Propriété | Type | Description |
|---|---|---|
| `header` | `string` | Texte en gras en haut de l'écran |
| `text` | `string` | Texte au milieu de l'écran |
| `timeout` | `number` | Délai en ms après lequel l'événement se déclenche. Le décompte démarre à l'affectation de cette propriété |

| Événement | Type de l'élément | Description |
|---|---|---|
| `timeout` | (aucun) | Se déclenche à l'expiration du délai |

## Text box {#text-box}

![Text box](/img/dev/js_gui_text_box.png)

Un champ de texte défilant en lecture seule.

```js
let textBoxView = require("gui/text_box");
```

| Propriété | Type | Description |
|---|---|---|
| `text` | `string` | Texte à afficher |
| `font` | `string` | Police : `"text"` ou `"hex"` |
| `focus` | `string` | Position de défilement initiale : `"start"` ou `"end"` |

## Text input {#text-input}

![Text input](/img/dev/js_gui_text_input.png)

Un clavier à l'écran.

```js
let textInputView = require("gui/text_input");
```

| Propriété | Type | Description |
|---|---|---|
| `minLength` | `number` | Longueur de texte minimale autorisée |
| `maxLength` | `number` | Longueur de texte maximale autorisée. Par défaut : `32` |
| `header` | `string` | Une seule ligne de texte au-dessus du clavier |
| `defaultText` | `string` | Texte affiché par défaut |
| `defaultTextClear` | `boolean` | Indique s'il faut effacer le texte par défaut à la saisie du caractère suivant |

| Événement | Type de l'élément | Description |
|---|---|---|
| `input` | `string` | Se déclenche quand l'utilisateur choisit **Save** et que la longueur du texte respecte `minLength`/`maxLength` |

## Byte input {#byte-input}

![Byte input](/img/dev/js_gui_byte_input.png)

Un clavier hexadécimal.

```js
let byteInputView = require("gui/byte_input");
```

| Propriété | Type | Description |
|---|---|---|
| `length` | `number` | Longueur en octets du tampon à modifier |
| `header` | `string` | Une seule ligne de texte au-dessus du clavier |
| `defaultData` | `Uint8Array` / `ArrayBuffer` | Données affichées par défaut (ne doivent pas être plus longues que `length`) |

| Événement | Type de l'élément | Description |
|---|---|---|
| `input` | `ArrayBuffer` | Se déclenche quand l'utilisateur choisit **Save** |

::: info
La documentation officielle indique `defaultData` comme `string`. Le firmware le lit en réalité comme un
`ArrayBuffer` (ou un tableau typé tel que `Uint8Array`) et signale une erreur s'il est plus long que `length`.
:::

## Number input {#number-input}

Un clavier numérique.

```js
let numberInputView = require("gui/number_input");
```

| Propriété | Type | Description |
|---|---|---|
| `header` | `string` | Texte en haut de l'écran |
| `minValue` | `number` | Valeur minimale autorisée |
| `maxValue` | `number` | Valeur maximale autorisée |
| `defaultValue` | `number` | Valeur par défaut |

| Événement | Type de l'élément | Description |
|---|---|---|
| `input` | `number` | Le nombre saisi |

## Loading {#loading}

![Loading](/img/dev/js_gui_loading.png)

Un sablier animé. Il **supprime tous les événements `navigation`** : l'utilisateur ne peut donc pas le quitter avec
<kbd>Back</kbd> ; faites la bascule depuis le code.

```js
let loadingView = require("gui/loading");
```

Aucune propriété.

## Empty screen {#empty-screen}

![Empty screen](/img/dev/js_gui_empty.png)

```js
let emptyView = require("gui/empty_screen");
```

Aucune propriété.

## Widget {#widget}

![Widget](/img/dev/js_gui_widget.png)

Affiche une combinaison d'éléments personnalisés sur un même écran.

```js
let widgetView = require("gui/widget");
```

**Propriétés :** aucune. **Enfants :** des éléments de la forme `{ element: "type", ...properties }`, par ex.
`{ element: "button", button: "right", text: "Back" }`.

| Élément | Propriétés | Description |
|---|---|---|
| `string_multiline` | `x`, `y` (number) ; `align` ; `font` ; `text` (string) | Texte pouvant s'étendre sur plusieurs lignes |
| `string` | `x`, `y` (number) ; `align` ; `font` ; `text` (string) | Une seule chaîne de texte |
| `text_box` | `x`, `y`, `w`, `h` (number) ; `align` ; `text` (string) ; `stripToDots` (boolean) | Cadre avec texte défilant verticalement |
| `text_scroll` | `x`, `y`, `w`, `h` (number) ; `text` (string) | Texte défilant verticalement |
| `button` | `text` (string) ; `button` (`"left"`, `"center"`, `"right"`) | Bouton en bas de l'écran |
| `icon` | `x`, `y` (number) ; `iconData` ([IconData](#icon)) | Une icône |
| `rect` | `x`, `y`, `w`, `h` (number) ; `radius` (number), `fill` (boolean) | Rectangle, éventuellement arrondi et rempli |
| `circle` | `x`, `y` (number) ; `radius` (number), `fill` (boolean) | Cercle, éventuellement rempli |
| `line` | `x1`, `y1`, `x2`, `y2` (number) | Ligne entre deux points |

- `align` est une lettre verticale (`"t"`, `"c"`, `"b"`) suivie d'une lettre horizontale (`"l"`, `"m"`, `"r"`), par
  ex. `"bl"` ou `"cm"`.
- `font` vaut `"primary"`, `"secondary"`, `"keyboard"` ou `"big_numbers"`.

Structure **ButtonEvent** :

- `key` : la touche pressée (`"left" | "center" | "right"`) ;
- `type` : le type d'événement (`"press" | "release" | "short" | "long" | "repeat"`).

| Événement | Type de l'élément | Description |
|---|---|---|
| `button` | `ButtonEvent` | Se déclenche lorsqu'un des trois boutons est pressé, s'il existe un élément `button` correspondant |

```js
let stopwatchWidgetElements = [
    { element: "string", x: 67, y: 44, align: "bl", font: "big_numbers", text: "00 00" },
    { element: "button", button: "right", text: "Back" },
];
let widget = widgetView.makeWith({}, stopwatchWidgetElements);
```

## File picker {#file-picker}

Ce n'est pas une vue comme les autres, juste une fonction qui affiche une invite de sélection de fichier.

```js
let filePicker = require("gui/file_picker");
```

### pickFile()
Affiche un sélecteur de fichiers et renvoie le fichier sélectionné, ou `undefined` en cas d'annulation.

- **Paramètres :**
  - `basePath` : le chemin de départ ;
  - `extension` : la ou les extensions de fichiers à afficher (comme `.sub`, `.iso|.img`, `*`).
- **Renvoie :** un chemin de type `string`, ou `undefined`.

## Icônes {#icon}

Récupère et charge des icônes pour les vues telles que [Menu](#menu), [Button panel](#button-panel) et
[Widget](#widget).

```js
let icon = require("gui/icon");
```

### getBuiltin()
Récupère une icône intégrée au firmware par son nom et renvoie un objet `IconData`.

Seules certaines icônes sont disponibles. La documentation officielle cite `"DolphinWait_59x54"` et
`"js_script_10px"`. Le firmware actuel possède également `"off_19x20"`, `"off_hover_19x20"`, `"power_19x20"`,
`"power_hover_19x20"` ainsi que l'animée `"Settings_14"`.

- **Paramètres :** `icon`, le nom de l'icône.

### loadFxbm()
Charge depuis un fichier une icône `.fxbm` (sprite Flipper XBM, issu de `flipperzero-game-engine`) et renvoie un
objet `IconData`. Elle est déchargée automatiquement à la fin du script.

- **Paramètres :** `path`, le chemin du fichier `.fxbm`.
