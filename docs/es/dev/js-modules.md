---
title: "JavaScript: usar módulos"
sidebarTitle: "JS: usar módulos"
order: 230
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_using_js_modules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules]
sources: [unleashed-docs, unleashed-src]
---
# Usar módulos de JavaScript

Las [funciones integradas](/es/dev/js-builtin) son deliberadamente pocas. Las funciones de hardware y de sistema residen en **módulos de JS**, por ejemplo:

- `serial` envía y recibe datos por UART;
- `badusb` emula un teclado USB;
- `math` ofrece funciones matemáticas.

Los módulos están escritos en C, así que son rápidos. Se incluyen con el firmware y se almacenan en la tarjeta SD en forma compilada como plugins **FAL (Flipper Application File)**. Código fuente de los módulos: [`applications/system/js_app/modules`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules). La lista de módulos está en [Visión general de JavaScript](/es/dev/js-about).

## Cargar un módulo

**Debes** cargar un módulo con `require()` antes de llamar a sus métodos. Esto carga el módulo en la RAM.

- Carga solo lo que uses, para ahorrar RAM. (`math`, por ejemplo, ocupa unos 21 KB de RAM una vez cargado.)
- Todos los módulos cargados se descargan automáticamente cuando termina el script.
- Un módulo solo se puede cargar una vez por script; un segundo `require()` del mismo nombre falla con `"... module is already installed"`.
- Algunos módulos dependen de otros y hay que cargarlos después: `gpio` y `gui` necesitan `event_loop`, y cada vista `gui/*` necesita `gui`.

Pasa el nombre del módulo entre comillas:

```js
let notify = require("notification");
```

Después llama a sus métodos a través de la variable:

```js
let notify = require("notification");

notify.success();
print("success notification");
```

El firmware acepta también el nombre al estilo del SDK `require("@flipperdevices/fz-sdk/notification")`: el prefijo se elimina automáticamente. Los nombres con barra, como `gui/submenu`, se corresponden con el archivo de plugin `js_gui__submenu`.

## ¿Y ahora qué?

- Recorre las páginas de los módulos de esta sección, empezando por [Bucle de eventos](/es/dev/js-event-loop) y [GUI](/es/dev/js-gui).
- Estudia los scripts de ejemplo de `/ext/apps/Scripts/js_examples/`.
