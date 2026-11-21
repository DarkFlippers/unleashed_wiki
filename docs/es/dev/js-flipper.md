---
title: "JavaScript: flipper"
sidebarTitle: "JS: flipper"
order: 300
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_flipper.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_flipper.c]
sources: [unleashed-docs, unleashed-src]
---
# Módulo Flipper

Valores y métodos para consultar información del dispositivo. Carga primero el módulo:

```js
let flipper = require("flipper");
```

## Valores

### firmwareVendor
Una cadena con el nombre del firmware del dispositivo. El firmware oficial declara `"flipperdevices"`.

::: tip Unleashed
Unleashed declara `"unleashed"`.
:::

**No** uses esto para comprobar si una característica está disponible. Usa en su lugar las
[funciones de compatibilidad del SDK](/es/dev/js-builtin#sdk-compatibility).

### jsSdkVersion
Versión del SDK de JavaScript. De nuevo, **no** la uses para comprobar características; consulta
[compatibilidad del SDK](/es/dev/js-builtin#sdk-compatibility).

## Métodos

### getModel()
Devuelve el modelo del dispositivo.

```js
flipper.getModel(); // "Flipper Zero"
```

### getName()
Devuelve el nombre del delfín virtual (el nombre del dispositivo).

```js
flipper.getName(); // "Fur1pp44"
```

### getBatteryCharge()
Devuelve la carga de la batería en porcentaje.

```js
flipper.getBatteryCharge(); // 100
```
