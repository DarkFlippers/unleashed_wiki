---
title: "JavaScript: flipper"
sidebarTitle: "JS: flipper"
order: 300
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_flipper.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_flipper.c]
sources: [unleashed-docs, unleashed-src]
---
# Modul flipper

Vrijednosti i metode za dohvaćanje podataka o uređaju. Prvo učitajte modul:

```js
let flipper = require("flipper");
```

## Vrijednosti

### firmwareVendor
Znakovni niz s nazivom firmvera na uređaju. Službeni firmver vraća `"flipperdevices"`.

::: tip Unleashed
Unleashed vraća `"unleashed"`.
:::

**Nemojte** koristiti ovu vrijednost za provjeru je li neka značajka dostupna. Umjesto toga koristite [funkcije kompatibilnosti SDK-a](/hr/dev/js-builtin#sdk-compatibility).

### jsSdkVersion
Verzija JavaScript SDK-a. Također je **nemojte** koristiti za provjeru značajki; pogledajte [kompatibilnost SDK-a](/hr/dev/js-builtin#sdk-compatibility).

## Metode

### getModel()
Vraća model uređaja.

```js
flipper.getModel(); // "Flipper Zero"
```

### getName()
Vraća ime virtualnog dupina (naziv uređaja).

```js
flipper.getName(); // "Fur1pp44"
```

### getBatteryCharge()
Vraća napunjenost baterije u postocima.

```js
flipper.getBatteryCharge(); // 100
```
