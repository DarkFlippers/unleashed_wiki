---
title: "JavaScript: GUI"
sidebarTitle: "JS: gui"
order: 270
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_gui]
sources: [unleashed-docs, unleashed-src]
---
# Módulo GUI

El módulo `gui` da a los scripts acceso a la interfaz estándar de Flipper Zero: menús, teclados, diálogos, cuadros de texto, etc. Depende de `event_loop`, así que **debe** cargarse después de él:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
```

Las pantallas individuales («vistas») son módulos aparte llamados `gui/<view>`. Se describen en [Vistas de la GUI](/es/dev/js-gui-views).

## Conceptos

**Bucle de eventos.** Toda la entrada de la GUI llega como eventos del bucle de eventos. Lee primero [Bucle de eventos](/es/dev/js-event-loop).

**Canvas.** Una zona de dibujo en bruto, sin abstracciones. Dibujar directamente sobre ella solo es necesario para elementos de diseño propios y es poco frecuente.

**Viewport.** Una ventana a una parte rectangular del canvas. Las aplicaciones dibujan siempre a través de un viewport.

**View.** Un elemento de interfaz a pantalla completa que toma todo el viewport y toda la entrada. Vistas disponibles:

`button_menu`, `button_panel`, `byte_input`, `dialog`, `empty_screen`, `file_picker`, `loading`, `menu`, `number_input`, `popup`, `submenu`, `text_box`, `text_input`, `vi_list`, `widget`.

Cada vista tiene **propiedades** («props»). Se asignan de dos formas:

- creando la vista con `makeWith(props)` y pasando las propiedades iniciales;
- cambiando una propiedad de una vista existente con `set(name, value)`.

**View Dispatcher.** Contiene todas las vistas de la app y alterna entre ellas cuando se le pide.

**Scene Manager.** Un complemento opcional del view dispatcher para navegaciones complejas. No está disponible desde JS.

| Enfoque | Caso de uso | Disponible desde JS |
|---|---|---|
| Solo ViewPort | Acceso directo a la API gráfica, sin abstracciones de interfaz | No |
| ViewDispatcher | Elementos de interfaz estándar que respetan el aspecto del sistema | **Sí** |
| SceneManager | Gestión adicional de la navegación para apps complejas | No |

## Ejemplo {#example}

Tres vistas gestionadas por el view dispatcher:

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

::: warning Los elementos del submenú son hijos
La documentación oficial muestra las entradas del submenú pasadas como una prop `items` (`makeWith({ items: [...] })`). En el firmware actual (SDK de JS 0.4 en adelante) el submenú solo tiene la prop `header`, y **las entradas son hijos**: el segundo argumento de `makeWith()`, o se añaden con `addChild()`. El ejemplo de arriba usa la API actual, igual que el ejemplo `gui.js` incluido.
:::

Hay una demostración mucho más amplia que usa todas las vistas instalada como `/ext/apps/Scripts/js_examples/gui.js`.

## Referencia de la API

### viewDispatcher
La constante `viewDispatcher` contiene el singleton `ViewDispatcher`.

#### viewDispatcher.switchTo(view)
Cambia a una vista, dándole el control de la pantalla y de la entrada.

- `view`: la `View` a la que cambiar.

#### viewDispatcher.sendTo(direction)
Envía el viewport que gestiona el dispatcher al frente de la pila (haciéndolo visible) o al fondo (haciéndolo invisible).

- `direction`: `"front"` o `"back"`.

#### viewDispatcher.sendCustom(event)
Envía un número personalizado al manejador del evento `custom`.

- `event`: el número que se envía.

#### viewDispatcher.custom
Un `Contract` del bucle de eventos para los eventos personalizados, que dispara `ViewDispatcher.sendCustom(event)`.

#### viewDispatcher.navigation
Un `Contract` del bucle de eventos para los eventos de navegación, que se dispara al pulsar <kbd>Back</kbd>.

#### viewDispatcher.currentView
La `View` que se muestra en ese momento.

### ViewFactory
Importar un módulo de vista te da un `ViewFactory`. En el ejemplo, `loadingView`, `submenuView` y `emptyView` son view factories.

#### ViewFactory.make()
Crea una instancia de `View`.

#### ViewFactory.makeWith(props, children)
Crea una `View` y le asigna las propiedades iniciales de `props` y, opcionalmente, una lista de hijos.

- `props`: un objeto clave-valor sencillo, por ejemplo `{ header: "Header" }`;
- `children`: array opcional de hijos, por ejemplo `[ { element: "button", button: "right", text: "Back" } ]`.

### View
`ViewFactory.make()` y `ViewFactory.makeWith()` devuelven una `View`. En el ejemplo, `views.loading`, `views.demos` y `views.empty` son vistas.

#### View.set(property, value)
Asigna un valor a una propiedad por su nombre.

- `property`: nombre de la propiedad;
- `value`: el nuevo valor.

#### View.addChild(child)
Añade un hijo a la vista.

- `child`: el hijo que se añade, por ejemplo `{ element: "button", button: "right", text: "Back" }`.

El formato de un hijo depende del tipo de vista; consulta [Vistas de la GUI](/es/dev/js-gui-views).

#### View.resetChildren()
Elimina todos los hijos de la vista.

#### View.setChildren(children)
Elimina todos los hijos anteriores y asigna otros nuevos.

- `children`: array con los nuevos hijos, por ejemplo `[ { element: "button", button: "right", text: "Back" } ]`.

### Tipos comunes

De las declaraciones de tipos del SDK:

```ts
type Font = "primary" | "secondary" | "keyboard" | "big_numbers";
type InputType = "press" | "release" | "short" | "long" | "repeat";
```
