---
title: "JavaScript: flipper"
sidebarTitle: "JS: flipper"
order: 300
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_flipper.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_flipper.c]
sources: [unleashed-docs, unleashed-src]
---
# Modulo flipper

Valori e metodi per ottenere informazioni sul dispositivo. Carica prima il modulo:

```js
let flipper = require("flipper");
```

## Valori

### firmwareVendor
Una stringa che indica il firmware presente sul dispositivo. Il firmware ufficiale riporta `"flipperdevices"`.

::: tip Unleashed
Unleashed riporta `"unleashed"`.
:::

**Non** usare questo valore per verificare se una funzionalità è disponibile. Usa invece le
[funzioni di compatibilità dell'SDK](/it/dev/js-builtin#sdk-compatibility).

### jsSdkVersion
Versione dell'SDK JavaScript. Anche in questo caso, **non** usarla per verificare le funzionalità; vedi
[compatibilità dell'SDK](/it/dev/js-builtin#sdk-compatibility).

## Metodi

### getModel()
Restituisce il modello del dispositivo.

```js
flipper.getModel(); // "Flipper Zero"
```

### getName()
Restituisce il nome del delfino virtuale (il nome del dispositivo).

```js
flipper.getName(); // "Fur1pp44"
```

### getBatteryCharge()
Restituisce la carica della batteria in percentuale.

```js
flipper.getBatteryCharge(); // 100
```
