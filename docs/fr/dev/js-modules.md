---
title: "JavaScript : utiliser les modules"
sidebarTitle: "JS : modules"
order: 230
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_using_js_modules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules]
sources: [unleashed-docs, unleashed-src]
---
# Utiliser les modules JavaScript

Les [fonctions intégrées](/fr/dev/js-builtin) sont volontairement peu nombreuses. Le matériel et les fonctions système
résident dans des **modules JS**, par exemple :

- `serial` envoie et reçoit des données via l'UART ;
- `badusb` émule un clavier USB ;
- `math` fournit des fonctions mathématiques.

Les modules sont écrits en C, ils sont donc rapides. Ils sont fournis avec le firmware et stockés sur la carte SD sous
forme compilée, comme plugins **FAL (Flipper Application File)**. Sources des modules :
[`applications/system/js_app/modules`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules).
La liste des modules se trouve sur [Présentation de JavaScript](/fr/dev/js-about).

## Charger un module

Vous **devez** charger un module avec `require()` avant d'appeler ses méthodes. Cela charge le module en RAM.

- Ne chargez que ce que vous utilisez, pour économiser la RAM. (`math`, par exemple, occupe environ 21 Ko de RAM une
  fois chargé.)
- Tous les modules chargés sont déchargés automatiquement à la fin du script.
- Un module ne peut être chargé qu'une fois par script ; un second `require()` du même nom échoue avec
  `"... module is already installed"`.
- Certains modules dépendent d'autres et doivent être chargés après eux : `gpio` et `gui` ont besoin de `event_loop`,
  et chaque vue `gui/*` a besoin de `gui`.

Passez le nom du module entre guillemets :

```js
let notify = require("notification");
```

Appelez ensuite ses méthodes via la variable :

```js
let notify = require("notification");

notify.success();
print("success notification");
```

Le firmware accepte également le nom au format SDK `require("@flipperdevices/fz-sdk/notification")` : le préfixe est
supprimé automatiquement. Les noms contenant une barre oblique, comme `gui/submenu`, correspondent au fichier de
plugin `js_gui__submenu`.

## La suite

- Parcourez les pages de modules de cette section, en commençant par
  [Boucle d'événements](/fr/dev/js-event-loop) et [GUI](/fr/dev/js-gui).
- Étudiez les scripts d'exemple dans `/ext/apps/Scripts/js_examples/`.
