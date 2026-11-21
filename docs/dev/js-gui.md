---
title: "JavaScript: GUI"
sidebarTitle: "JS: gui"
order: 270
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_gui]
sources: [unleashed-docs, unleashed-src]
---
# GUI module

The `gui` module gives scripts access to the standard Flipper Zero interface: menus, keyboards, dialogs, text boxes and so on. It depends on `event_loop`, so it **must** be loaded after it:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
```

The individual screens ("views") are separate modules named `gui/<view>`. They are described on [GUI views](/dev/js-gui-views).

## Concepts

**Event loop.** All GUI input arrives as event-loop events. Read [Event loop](/dev/js-event-loop) first.

**Canvas.** A raw drawing area with no abstractions. Drawing on it directly is only needed for custom design elements and is rare.

**Viewport.** A window into a rectangular part of the canvas. Applications always draw through a viewport.

**View.** A full-screen UI element that takes over the whole viewport and all input. Available views:

`button_menu`, `button_panel`, `byte_input`, `dialog`, `empty_screen`, `file_picker`, `loading`, `menu`, `number_input`, `popup`, `submenu`, `text_box`, `text_input`, `vi_list`, `widget`.

Each view has **properties** ("props"). You set them in two ways:

- create the view with `makeWith(props)`, passing the initial properties;
- change a property of an existing view with `set(name, value)`.

**View Dispatcher.** Holds all views of the app and switches between them on request.

**Scene Manager.** An optional add-on to the view dispatcher for complex navigation. Not available from JS.

| Approach | Use case | Available from JS |
|---|---|---|
| ViewPort only | Direct access to the graphics API, without UI abstractions | No |
| ViewDispatcher | Standard UI elements that match the system look | **Yes** |
| SceneManager | Extra navigation management for complex apps | No |

## Example {#example}

Three views managed by the view dispatcher:

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

::: warning Submenu items are children
The official documentation shows submenu entries passed as an `items` prop (`makeWith({ items: [...] })`). In the current firmware (JS SDK 0.4+) the submenu has only a `header` prop, and **entries are children**: the second argument of `makeWith()`, or added with `addChild()`. The example above uses the current API, as in the bundled `gui.js` example.
:::

A much larger demo using every view is installed as `/ext/apps/Scripts/js_examples/gui.js`.

## API reference

### viewDispatcher
The `viewDispatcher` constant holds the `ViewDispatcher` singleton.

#### viewDispatcher.switchTo(view)
Switches to a view, giving it control over the display and input.

- `view`: the `View` to switch to.

#### viewDispatcher.sendTo(direction)
Sends the viewport managed by the dispatcher to the front of the stack (making it visible) or to the back (making it invisible).

- `direction`: `"front"` or `"back"`.

#### viewDispatcher.sendCustom(event)
Sends a custom number to the `custom` event handler.

- `event`: the number to send.

#### viewDispatcher.custom
An event-loop `Contract` for custom events, triggered by `ViewDispatcher.sendCustom(event)`.

#### viewDispatcher.navigation
An event-loop `Contract` for navigation events, triggered when <kbd>Back</kbd> is pressed.

#### viewDispatcher.currentView
The `View` currently shown.

### ViewFactory
Importing a view module gives you a `ViewFactory`. In the example, `loadingView`, `submenuView` and `emptyView` are view factories.

#### ViewFactory.make()
Creates a `View` instance.

#### ViewFactory.makeWith(props, children)
Creates a `View` and assigns initial properties from `props` and, optionally, a list of children.

- `props`: a simple key-value object, e.g. `{ header: "Header" }`;
- `children`: optional array of children, e.g. `[ { element: "button", button: "right", text: "Back" } ]`.

### View
`ViewFactory.make()` and `ViewFactory.makeWith()` return a `View`. In the example, `views.loading`, `views.demos` and `views.empty` are views.

#### View.set(property, value)
Assigns a value to a property by name.

- `property`: name of the property;
- `value`: the new value.

#### View.addChild(child)
Adds a child to the view.

- `child`: the child to add, e.g. `{ element: "button", button: "right", text: "Back" }`.

The format of a child depends on the view type; see [GUI views](/dev/js-gui-views).

#### View.resetChildren()
Removes all children from the view.

#### View.setChildren(children)
Removes all previous children and assigns new ones.

- `children`: array of new children, e.g. `[ { element: "button", button: "right", text: "Back" } ]`.

### Common types

From the SDK typings:

```ts
type Font = "primary" | "secondary" | "keyboard" | "big_numbers";
type InputType = "press" | "release" | "short" | "long" | "repeat";
```
