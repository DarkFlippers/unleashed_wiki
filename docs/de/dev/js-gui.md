---
title: "JavaScript: GUI"
sidebarTitle: "JS: gui"
order: 270
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_gui]
sources: [unleashed-docs, unleashed-src]
---
# Modul GUI

Das Modul `gui` gibt Skripten Zugriff auf die Standardoberfläche des Flipper Zero: Menüs, Tastaturen, Dialoge,
Textfelder und so weiter. Es hängt von `event_loop` ab und **muss** daher nach diesem geladen werden:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
```

Die einzelnen Bildschirme ("Views") sind eigene Module mit dem Namen `gui/<view>`. Sie sind unter
[GUI-Views](/de/dev/js-gui-views) beschrieben.

## Konzepte

**Event loop.** Alle GUI-Eingaben kommen als Event-Loop-Ereignisse an. Lies zuerst
[Event loop](/de/dev/js-event-loop).

**Canvas.** Eine rohe Zeichenfläche ohne Abstraktionen. Direkt darauf zu zeichnen ist nur für eigene
Designelemente nötig und kommt selten vor.

**Viewport.** Ein Fenster auf einen rechteckigen Teil des Canvas. Anwendungen zeichnen immer über einen Viewport.

**View.** Ein bildschirmfüllendes UI-Element, das den gesamten Viewport und alle Eingaben übernimmt. Verfügbare
Views:

`button_menu`, `button_panel`, `byte_input`, `dialog`, `empty_screen`, `file_picker`, `loading`, `menu`,
`number_input`, `popup`, `submenu`, `text_box`, `text_input`, `vi_list`, `widget`.

Jede View hat **Eigenschaften** ("Props"). Du setzt sie auf zwei Wegen:

- die View mit `makeWith(props)` erzeugen und die Anfangseigenschaften übergeben;
- eine Eigenschaft einer bestehenden View mit `set(name, value)` ändern.

**View Dispatcher.** Hält alle Views der App und schaltet auf Anforderung zwischen ihnen um.

**Scene Manager.** Eine optionale Ergänzung zum View Dispatcher für komplexe Navigation. Aus JS nicht verfügbar.

| Ansatz | Einsatzzweck | Aus JS verfügbar |
|---|---|---|
| nur ViewPort | Direkter Zugriff auf die Grafik-API, ohne UI-Abstraktionen | Nein |
| ViewDispatcher | Standard-UI-Elemente, die zum Systemlook passen | **Ja** |
| SceneManager | Zusätzliche Navigationsverwaltung für komplexe Apps | Nein |

## Beispiel {#example}

Drei Views, die vom View Dispatcher verwaltet werden:

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

::: warning Submenü-Einträge sind Kinder
Die offizielle Dokumentation zeigt Submenü-Einträge als Prop `items` übergeben (`makeWith({ items: [...] })`). In
der aktuellen Firmware (JS SDK 0.4+) hat das Submenü nur das Prop `header`, und die **Einträge sind Kinder**: das
zweite Argument von `makeWith()` oder per `addChild()` hinzugefügt. Das Beispiel oben verwendet die aktuelle API,
wie im mitgelieferten Beispiel `gui.js`.
:::

Eine viel umfangreichere Demo, die jede View verwendet, wird als `/ext/apps/Scripts/js_examples/gui.js`
installiert.

## API-Referenz

### viewDispatcher
Die Konstante `viewDispatcher` enthält das `ViewDispatcher`-Singleton.

#### viewDispatcher.switchTo(view)
Schaltet auf eine View um und gibt ihr die Kontrolle über Display und Eingabe.

- `view`: die `View`, auf die umgeschaltet wird.

#### viewDispatcher.sendTo(direction)
Schiebt den vom Dispatcher verwalteten Viewport an die Spitze des Stapels (macht ihn sichtbar) oder nach hinten
(macht ihn unsichtbar).

- `direction`: `"front"` oder `"back"`.

#### viewDispatcher.sendCustom(event)
Sendet eine eigene Zahl an den Handler für das Ereignis `custom`.

- `event`: die zu sendende Zahl.

#### viewDispatcher.custom
Ein Event-Loop-`Contract` für eigene Ereignisse, ausgelöst von `ViewDispatcher.sendCustom(event)`.

#### viewDispatcher.navigation
Ein Event-Loop-`Contract` für Navigationsereignisse, ausgelöst beim Druck auf <kbd>Back</kbd>.

#### viewDispatcher.currentView
Die gerade angezeigte `View`.

### ViewFactory
Der Import eines View-Moduls liefert dir eine `ViewFactory`. Im Beispiel sind `loadingView`, `submenuView` und
`emptyView` View-Factories.

#### ViewFactory.make()
Erzeugt eine `View`-Instanz.

#### ViewFactory.makeWith(props, children)
Erzeugt eine `View` und weist ihr Anfangseigenschaften aus `props` und optional eine Liste von Kindern zu.

- `props`: ein einfaches Schlüssel-Wert-Objekt, z. B. `{ header: "Header" }`;
- `children`: optionales Array von Kindern, z. B. `[ { element: "button", button: "right", text: "Back" } ]`.

### View
`ViewFactory.make()` und `ViewFactory.makeWith()` geben eine `View` zurück. Im Beispiel sind `views.loading`,
`views.demos` und `views.empty` Views.

#### View.set(property, value)
Weist einer Eigenschaft anhand ihres Namens einen Wert zu.

- `property`: Name der Eigenschaft;
- `value`: der neue Wert.

#### View.addChild(child)
Fügt der View ein Kind hinzu.

- `child`: das hinzuzufügende Kind, z. B. `{ element: "button", button: "right", text: "Back" }`.

Das Format eines Kindes hängt vom View-Typ ab, siehe [GUI-Views](/de/dev/js-gui-views).

#### View.resetChildren()
Entfernt alle Kinder aus der View.

#### View.setChildren(children)
Entfernt alle bisherigen Kinder und weist neue zu.

- `children`: Array der neuen Kinder, z. B. `[ { element: "button", button: "right", text: "Back" } ]`.

### Gemeinsame Typen

Aus den SDK-Typdefinitionen:

```ts
type Font = "primary" | "secondary" | "keyboard" | "big_numbers";
type InputType = "press" | "release" | "short" | "long" | "repeat";
```
