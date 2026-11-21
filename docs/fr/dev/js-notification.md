---
title: "JavaScript : notification"
sidebarTitle: "JS : notification"
order: 330
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_notification.md]
sources: [unleashed-docs]
---
# Module notification

Joue les notifications système (LED, vibration, son) et fait clignoter la LED RGB.

```js
let notify = require("notification");
```

Script d'exemple : `/ext/apps/Scripts/js_examples/notify.js`.

## Méthodes

### success()
Joue la notification standard « Success ».

```js
notify.success();
```

### error()
Joue la notification standard « Error ».

```js
notify.error();
```

### blink()
Fait clignoter la LED de notification.

**Paramètres :**

- couleur : `"blue"`, `"red"`, `"green"`, `"yellow"`, `"cyan"` ou `"magenta"` ;
- type de clignotement : `"short"` ou `"long"`.

```js
notify.blink("red", "short"); // Short blink of red LED
notify.blink("green", "long"); // Long blink of green LED
```

La vibration, le son et la luminosité de la LED suivent les réglages de l'utilisateur dans
`Settings → LCD and Notifications`.
