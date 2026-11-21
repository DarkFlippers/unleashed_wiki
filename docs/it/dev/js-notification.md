---
title: "JavaScript: notification"
sidebarTitle: "JS: notification"
order: 330
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_notification.md]
sources: [unleashed-docs]
---
# Modulo notification

Riproduce le notifiche di sistema (LED, vibrazione, suono) e fa lampeggiare il LED RGB.

```js
let notify = require("notification");
```

Script di esempio: `/ext/apps/Scripts/js_examples/notify.js`.

## Metodi

### success()
Riproduce la notifica standard "Success".

```js
notify.success();
```

### error()
Riproduce la notifica standard "Error".

```js
notify.error();
```

### blink()
Fa lampeggiare il LED di notifica.

**Parametri:**

- colore: `"blue"`, `"red"`, `"green"`, `"yellow"`, `"cyan"` o `"magenta"`;
- tipo di lampeggio: `"short"` o `"long"`.

```js
notify.blink("red", "short"); // Short blink of red LED
notify.blink("green", "long"); // Long blink of green LED
```

Vibrazione, suono e luminosità del LED seguono le impostazioni dell'utente in `Settings → LCD and Notifications`.
