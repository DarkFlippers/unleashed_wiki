---
title: "JavaScript : flipper"
sidebarTitle: "JS : flipper"
order: 300
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_flipper.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_flipper.c]
sources: [unleashed-docs, unleashed-src]
---
# Module flipper

Valeurs et méthodes permettant d'interroger les informations de l'appareil. Chargez d'abord le module :

```js
let flipper = require("flipper");
```

## Valeurs

### firmwareVendor
Une chaîne nommant le firmware présent sur l'appareil. Le firmware officiel renvoie `"flipperdevices"`.

::: tip Unleashed
Unleashed renvoie `"unleashed"`.
:::

**N'utilisez pas** cette valeur pour vérifier la disponibilité d'une fonctionnalité. Utilisez plutôt les
[fonctions de compatibilité du SDK](/fr/dev/js-builtin#sdk-compatibility).

### jsSdkVersion
Version du SDK JavaScript. Là encore, **ne l'utilisez pas** pour tester des fonctionnalités ; voir
[Compatibilité du SDK](/fr/dev/js-builtin#sdk-compatibility).

## Méthodes

### getModel()
Renvoie le modèle de l'appareil.

```js
flipper.getModel(); // "Flipper Zero"
```

### getName()
Renvoie le nom du dauphin virtuel (le nom de l'appareil).

```js
flipper.getName(); // "Fur1pp44"
```

### getBatteryCharge()
Renvoie le niveau de charge de la batterie en pourcentage.

```js
flipper.getBatteryCharge(); // 100
```
