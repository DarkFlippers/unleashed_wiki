---
title: "JavaScript: GUI"
sidebarTitle: "JS: gui"
order: 270
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_gui]
sources: [unleashed-docs, unleashed-src]
---
# Modulo GUI

Il modulo `gui` dà agli script accesso all'interfaccia standard del Flipper Zero: menu, tastiere, finestre di dialogo, caselle di testo e così via. Dipende da `event_loop`, quindi **deve** essere caricato dopo di esso:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
```

Le singole schermate ("view") sono moduli separati chiamati `gui/<view>`. Sono descritti in [View della GUI](/it/dev/js-gui-views).

## Concetti

**Event loop.** Tutto l'input della GUI arriva come eventi dell'event loop. Leggi prima [Event loop](/it/dev/js-event-loop).

**Canvas.** Un'area di disegno grezza senza alcuna astrazione. Disegnarvi direttamente serve solo per elementi di design personalizzati ed è un caso raro.

**Viewport.** Una finestra su una porzione rettangolare del canvas. Le applicazioni disegnano sempre attraverso un viewport.

**View.** Un elemento di interfaccia a schermo intero che prende il controllo dell'intero viewport e di tutto l'input. View disponibili:

`button_menu`, `button_panel`, `byte_input`, `dialog`, `empty_screen`, `file_picker`, `loading`, `menu`, `number_input`, `popup`, `submenu`, `text_box`, `text_input`, `vi_list`, `widget`.

Ogni view ha delle **proprietà** ("props"). Si impostano in due modi:

- creando la view con `makeWith(props)`, passando le proprietà iniziali;
- modificando una proprietà di una view esistente con `set(name, value)`.

**View Dispatcher.** Contiene tutte le view dell'app e passa dall'una all'altra su richiesta.

**Scene Manager.** Un componente opzionale che si aggiunge al view dispatcher per una navigazione complessa. Non disponibile da JS.

| Approccio | Caso d'uso | Disponibile da JS |
|---|---|---|
| Solo ViewPort | Accesso diretto all'API grafica, senza astrazioni di interfaccia | No |
| ViewDispatcher | Elementi di interfaccia standard coerenti con l'aspetto di sistema | **Sì** |
| SceneManager | Gestione aggiuntiva della navigazione per app complesse | No |

## Esempio {#example}

Tre view gestite dal view dispatcher:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let loadingView = require("gui/loading");
let submenuView = require("gui/submenu");
let emptyView = require("gui/empty_screen");

// Common pattern: declare all the views in an object. This is absolutely not
// required, but adds clarity to the script.
let views = {
    // the view dispatcher auto-✨magically✨ remembers views as they are created
    loading: loadingView.make(),
    empty: emptyView.make(),
    demos: submenuView.makeWith({
        header: "Choose a demo",
    }, [
        "Hourglass screen",
        "Empty screen",
        "Exit app",
    ]),
};

// go to different screens depending on what was selected
eventLoop.subscribe(views.demos.chosen, function (_sub, index, gui, eventLoop, views) {
    if (index === 0) {
        gui.viewDispatcher.switchTo(views.loading);
    } else if (index === 1) {
        gui.viewDispatcher.switchTo(views.empty);
    } else if (index === 2) {
        eventLoop.stop();
    }
}, gui, eventLoop, views);

// go to the demo chooser screen when the back key is pressed
eventLoop.subscribe(gui.viewDispatcher.navigation, function (_sub, _, gui, views) {
    gui.viewDispatcher.switchTo(views.demos);
}, gui, views);

// run UI
gui.viewDispatcher.switchTo(views.demos);
eventLoop.run();
```

::: warning Le voci del submenu sono figli
La documentazione ufficiale mostra le voci del submenu passate come prop `items` (`makeWith({ items: [...] })`). Nel firmware attuale (JS SDK 0.4+) il submenu ha soltanto la prop `header`, e le **voci sono figli**: il secondo argomento di `makeWith()`, oppure aggiunte con `addChild()`. L'esempio sopra usa l'API attuale, come nell'esempio `gui.js` incluso nel firmware.
:::

Una dimostrazione molto più ampia che usa tutte le view è installata come `/ext/apps/Scripts/js_examples/gui.js`.

## Riferimento delle API

### viewDispatcher
La costante `viewDispatcher` contiene il singleton `ViewDispatcher`.

#### viewDispatcher.switchTo(view)
Passa a una view, dandole il controllo del display e dell'input.

- `view`: la `View` a cui passare.

#### viewDispatcher.sendTo(direction)
Porta il viewport gestito dal dispatcher in cima alla pila (rendendolo visibile) o in fondo (rendendolo invisibile).

- `direction`: `"front"` o `"back"`.

#### viewDispatcher.sendCustom(event)
Invia un numero personalizzato al gestore dell'evento `custom`.

- `event`: il numero da inviare.

#### viewDispatcher.custom
Un `Contract` dell'event loop per gli eventi personalizzati, attivato da `ViewDispatcher.sendCustom(event)`.

#### viewDispatcher.navigation
Un `Contract` dell'event loop per gli eventi di navigazione, attivato alla pressione di <kbd>Back</kbd>.

#### viewDispatcher.currentView
La `View` attualmente mostrata.

### ViewFactory
L'importazione di un modulo di view restituisce una `ViewFactory`. Nell'esempio, `loadingView`, `submenuView` ed `emptyView` sono view factory.

#### ViewFactory.make()
Crea un'istanza di `View`.

#### ViewFactory.makeWith(props, children)
Crea una `View` e le assegna le proprietà iniziali da `props` e, facoltativamente, un elenco di figli.

- `props`: un semplice oggetto chiave-valore, per esempio `{ header: "Header" }`;
- `children`: array facoltativo di figli, per esempio `[ { element: "button", button: "right", text: "Back" } ]`.

### View
`ViewFactory.make()` e `ViewFactory.makeWith()` restituiscono una `View`. Nell'esempio, `views.loading`, `views.demos` e `views.empty` sono view.

#### View.set(property, value)
Assegna un valore a una proprietà indicata per nome.

- `property`: nome della proprietà;
- `value`: il nuovo valore.

#### View.addChild(child)
Aggiunge un figlio alla view.

- `child`: il figlio da aggiungere, per esempio `{ element: "button", button: "right", text: "Back" }`.

Il formato di un figlio dipende dal tipo di view; vedi [View della GUI](/it/dev/js-gui-views).

#### View.resetChildren()
Rimuove tutti i figli dalla view.

#### View.setChildren(children)
Rimuove tutti i figli precedenti e ne assegna di nuovi.

- `children`: array dei nuovi figli, per esempio `[ { element: "button", button: "right", text: "Back" } ]`.

### Tipi comuni

Dalle definizioni di tipo dell'SDK:

```ts
type Font = "primary" | "secondary" | "keyboard" | "big_numbers";
type InputType = "press" | "release" | "short" | "long" | "repeat";
```
