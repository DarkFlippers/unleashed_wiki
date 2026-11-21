---
title: "JavaScript : GUI"
sidebarTitle: "JS : gui"
order: 270
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_gui]
sources: [unleashed-docs, unleashed-src]
---
# Module GUI

Le module `gui` donne aux scripts accès à l'interface standard du Flipper Zero : menus, claviers, boîtes de dialogue,
zones de texte, etc. Il dépend d'`event_loop` : il **doit** donc être chargé après lui.

```js
let eventLoop = require("event_loop");
let gui = require("gui");
```

Les différents écrans (les « vues ») sont des modules distincts nommés `gui/<view>`. Ils sont décrits sur
[Vues GUI](/fr/dev/js-gui-views).

## Notions

**Boucle d'événements.** Toutes les entrées de l'interface arrivent sous forme d'événements de la boucle
d'événements. Lisez d'abord [Boucle d'événements](/fr/dev/js-event-loop).

**Canvas.** Une zone de dessin brute, sans aucune abstraction. Y dessiner directement n'est nécessaire que pour des
éléments de design personnalisés, ce qui est rare.

**Viewport.** Une fenêtre sur une partie rectangulaire du canvas. Les applications dessinent toujours à travers un
viewport.

**Vue.** Un élément d'interface plein écran qui prend le contrôle de tout le viewport et de toutes les entrées. Vues
disponibles :

`button_menu`, `button_panel`, `byte_input`, `dialog`, `empty_screen`, `file_picker`, `loading`, `menu`,
`number_input`, `popup`, `submenu`, `text_box`, `text_input`, `vi_list`, `widget`.

Chaque vue possède des **propriétés** (« props »). Vous les définissez de deux façons :

- créez la vue avec `makeWith(props)`, en passant les propriétés initiales ;
- modifiez une propriété d'une vue existante avec `set(name, value)`.

**View Dispatcher.** Contient toutes les vues de l'application et bascule entre elles à la demande.

**Scene Manager.** Un complément facultatif du view dispatcher pour les navigations complexes. Non disponible depuis
JS.

| Approche | Cas d'usage | Disponible depuis JS |
|---|---|---|
| ViewPort seul | Accès direct à l'API graphique, sans abstractions d'interface | Non |
| ViewDispatcher | Éléments d'interface standard respectant l'apparence du système | **Oui** |
| SceneManager | Gestion de navigation supplémentaire pour les applications complexes | Non |

## Exemple {#example}

Trois vues gérées par le view dispatcher :

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

::: warning Les entrées de sous-menu sont des enfants
La documentation officielle montre les entrées de sous-menu passées dans une propriété `items`
(`makeWith({ items: [...] })`). Dans le firmware actuel (SDK JS 0.4+), le sous-menu n'a qu'une propriété `header`, et
les **entrées sont des enfants** : le second argument de `makeWith()`, ou ajoutés avec `addChild()`. L'exemple
ci-dessus utilise l'API actuelle, comme l'exemple `gui.js` fourni.
:::

Une démonstration beaucoup plus complète, utilisant toutes les vues, est installée sous
`/ext/apps/Scripts/js_examples/gui.js`.

## Référence de l'API

### viewDispatcher
La constante `viewDispatcher` contient le singleton `ViewDispatcher`.

#### viewDispatcher.switchTo(view)
Bascule vers une vue, en lui donnant le contrôle de l'écran et des entrées.

- `view` : la `View` vers laquelle basculer.

#### viewDispatcher.sendTo(direction)
Envoie le viewport géré par le dispatcher à l'avant de la pile (le rendant visible) ou à l'arrière (le rendant
invisible).

- `direction` : `"front"` ou `"back"`.

#### viewDispatcher.sendCustom(event)
Envoie un nombre personnalisé au gestionnaire de l'événement `custom`.

- `event` : le nombre à envoyer.

#### viewDispatcher.custom
Un `Contract` de boucle d'événements pour les événements personnalisés, déclenchés par
`ViewDispatcher.sendCustom(event)`.

#### viewDispatcher.navigation
Un `Contract` de boucle d'événements pour les événements de navigation, déclenchés lors d'un appui sur
<kbd>Back</kbd>.

#### viewDispatcher.currentView
La `View` actuellement affichée.

### ViewFactory
L'import d'un module de vue vous donne une `ViewFactory`. Dans l'exemple, `loadingView`, `submenuView` et `emptyView`
sont des fabriques de vues.

#### ViewFactory.make()
Crée une instance de `View`.

#### ViewFactory.makeWith(props, children)
Crée une `View` et lui affecte les propriétés initiales issues de `props` et, éventuellement, une liste d'enfants.

- `props` : un simple objet clé-valeur, par ex. `{ header: "Header" }` ;
- `children` : tableau d'enfants facultatif, par ex.
  `[ { element: "button", button: "right", text: "Back" } ]`.

### View
`ViewFactory.make()` et `ViewFactory.makeWith()` renvoient une `View`. Dans l'exemple, `views.loading`, `views.demos`
et `views.empty` sont des vues.

#### View.set(property, value)
Affecte une valeur à une propriété désignée par son nom.

- `property` : nom de la propriété ;
- `value` : la nouvelle valeur.

#### View.addChild(child)
Ajoute un enfant à la vue.

- `child` : l'enfant à ajouter, par ex. `{ element: "button", button: "right", text: "Back" }`.

Le format d'un enfant dépend du type de vue ; voir [Vues GUI](/fr/dev/js-gui-views).

#### View.resetChildren()
Supprime tous les enfants de la vue.

#### View.setChildren(children)
Supprime tous les enfants précédents et en affecte de nouveaux.

- `children` : tableau des nouveaux enfants, par ex.
  `[ { element: "button", button: "right", text: "Back" } ]`.

### Types communs

D'après les typages du SDK :

```ts
type Font = "primary" | "secondary" | "keyboard" | "big_numbers";
type InputType = "press" | "release" | "short" | "long" | "repeat";
```
