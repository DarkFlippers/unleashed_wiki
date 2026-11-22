---
title: "JavaScript: GUI"
sidebarTitle: "JS: gui"
order: 270
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_gui]
sources: [unleashed-docs, unleashed-src]
---
# GUI modul

Modul `gui` daje skriptama pristup standardnom sučelju Flippera Zero: izbornicima, tipkovnicama, dijalozima, tekstnim okvirima i tako dalje. Ovisi o modulu `event_loop`, stoga se **mora** učitati nakon njega:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
```

Pojedini zasloni („prikazi“ / „views“) zasebni su moduli pod nazivom `gui/<view>`. Opisani su na stranici [GUI prikazi](/hr/dev/js-gui-views).

## Koncepti

**Petlja događaja (Event loop).** Sav GUI unos stiže kao događaji petlje događaja. Najprije pročitajte [Petlja događaja](/hr/dev/js-event-loop).

**Platno (Canvas).** Sirovo područje za crtanje bez apstrakcija. Izravno crtanje na njemu potrebno je samo za prilagođene elemente dizajna i rijetko se koristi.

**Prozor prikaza (Viewport).** Prozor u pravokutni dio platna. Aplikacije uvijek crtaju kroz viewport.

**Prikaz (View).** Element korisničkog sučelja preko cijelog zaslona koji preuzima cijeli viewport i sav unos. Dostupni prikazi:

`button_menu`, `button_panel`, `byte_input`, `dialog`, `empty_screen`, `file_picker`, `loading`, `menu`, `number_input`, `popup`, `submenu`, `text_box`, `text_input`, `vi_list`, `widget`.

Svaki prikaz ima **svojstva** („props“). Postavljate ih na dva načina:

- stvorite prikaz pomoću `makeWith(props)` i proslijedite početna svojstva;
- promijenite svojstvo postojećeg prikaza pomoću `set(name, value)`.

**View Dispatcher.** Sadrži sve prikaze aplikacije i prebacuje se između njih na zahtjev.

**Scene Manager.** Neobavezni dodatak view dispatcheru za složenu navigaciju. Nije dostupan iz JS-a.

| Pristup | Namjena | Dostupno iz JS-a |
|---|---|---|
| Samo ViewPort | Izravan pristup grafičkom API-ju, bez UI apstrakcija | Ne |
| ViewDispatcher | Standardni UI elementi koji odgovaraju izgledu sustava | **Da** |
| SceneManager | Dodatno upravljanje navigacijom za složene aplikacije | Ne |

## Primjer {#example}

Tri prikaza kojima upravlja view dispatcher:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let loadingView = require("gui/loading");
let submenuView = require("gui/submenu");
let emptyView = require("gui/empty_screen");

// Uobičajen obrazac: deklarirajte sve prikaze u objektu. Ovo nikako nije
// obavezno, ali čini skriptu preglednijom.
let views = {
    // view dispatcher automatski pamti prikaze čim se stvore
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

// prijelaz na različite zaslone ovisno o tome što je odabrano
eventLoop.subscribe(views.demos.chosen, function (_sub, index, gui, eventLoop, views) {
    if (index === 0) {
        gui.viewDispatcher.switchTo(views.loading);
    } else if (index === 1) {
        gui.viewDispatcher.switchTo(views.empty);
    } else if (index === 2) {
        eventLoop.stop();
    }
}, gui, eventLoop, views);

// povratak na zaslon odabira demonstracije kada se pritisne tipka Back
eventLoop.subscribe(gui.viewDispatcher.navigation, function (_sub, _, gui, views) {
    gui.viewDispatcher.switchTo(views.demos);
}, gui, views);

// pokretanje korisničkog sučelja
gui.viewDispatcher.switchTo(views.demos);
eventLoop.run();
```

::: warning Stavke podizbornika su podređeni elementi (children)
Službena dokumentacija prikazuje stavke podizbornika proslijeđene kao svojstvo `items` (`makeWith({ items: [...] })`). U trenutačnom firmveru (JS SDK 0.4+) podizbornik ima samo svojstvo `header`, a **stavke su podređeni elementi**: drugi argument funkcije `makeWith()` ili se dodaju pomoću `addChild()`. Gornji primjer koristi aktualni API, kao i priloženi primjer `gui.js`.
:::

Mnogo veći pokazni primjer koji koristi svaki prikaz instaliran je kao `/ext/apps/Scripts/js_examples/gui.js`.

## API referenca

### viewDispatcher
Konstanta `viewDispatcher` sadrži singleton `ViewDispatcher`.

#### viewDispatcher.switchTo(view)
Prebacuje na prikaz, dajući mu kontrolu nad zaslonom i unosom.

- `view`: objekt `View` na koji se prebacuje.

#### viewDispatcher.sendTo(direction)
Šalje viewport kojim upravlja dispatcher na vrh stoga (čineći ga vidljivim) ili na dno (čineći ga nevidljivim).

- `direction`: `"front"` ili `"back"`.

#### viewDispatcher.sendCustom(event)
Šalje prilagođeni broj obrađivaču događaja `custom`.

- `event`: broj koji se šalje.

#### viewDispatcher.custom
`Contract` petlje događaja za prilagođene događaje, koji se pokreće pozivom `ViewDispatcher.sendCustom(event)`.

#### viewDispatcher.navigation
`Contract` petlje događaja za navigacijske događaje, koji se pokreće kada se pritisne <kbd>Back</kbd>.

#### viewDispatcher.currentView
Trenutačno prikazani `View`.

### ViewFactory
Uvozom modula prikaza dobivate `ViewFactory`. U primjeru su `loadingView`, `submenuView` i `emptyView` tvornice prikaza.

#### ViewFactory.make()
Stvara instancu objekta `View`.

#### ViewFactory.makeWith(props, children)
Stvara `View` i dodjeljuje mu početna svojstva iz `props` te, po želji, popis podređenih elemenata.

- `props`: jednostavan objekt ključ-vrijednost, npr. `{ header: "Header" }`;
- `children`: neobavezno polje podređenih elemenata, npr. `[ { element: "button", button: "right", text: "Back" } ]`.

### View
`ViewFactory.make()` i `ViewFactory.makeWith()` vraćaju `View`. U primjeru su `views.loading`, `views.demos` i `views.empty` prikazi.

#### View.set(property, value)
Dodjeljuje vrijednost svojstvu prema nazivu.

- `property`: naziv svojstva;
- `value`: nova vrijednost.

#### View.addChild(child)
Dodaje podređeni element prikazu.

- `child`: podređeni element koji se dodaje, npr. `{ element: "button", button: "right", text: "Back" }`.

Format podređenog elementa ovisi o vrsti prikaza; pogledajte [GUI prikazi](/hr/dev/js-gui-views).

#### View.resetChildren()
Uklanja sve podređene elemente iz prikaza.

#### View.setChildren(children)
Uklanja sve prethodne podređene elemente i dodjeljuje nove.

- `children`: polje novih podređenih elemenata, npr. `[ { element: "button", button: "right", text: "Back" } ]`.

### Zajednički tipovi

Iz SDK definicija tipova:

```ts
type Font = "primary" | "secondary" | "keyboard" | "big_numbers";
type InputType = "press" | "release" | "short" | "long" | "repeat";
```
