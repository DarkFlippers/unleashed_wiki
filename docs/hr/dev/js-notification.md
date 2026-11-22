---
title: "JavaScript: notification"
sidebarTitle: "JS: notification"
order: 330
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_notification.md]
sources: [unleashed-docs]
---
# Modul notification

Reproducira sistemske obavijesti (LED, vibracija, zvuk) i treperi RGB LED diodom.

```js
let notify = require("notification");
```

Primjer skripte: `/ext/apps/Scripts/js_examples/notify.js`.

## Metode

### success()
Reproducira standardnu obavijest „Success“.

```js
notify.success();
```

### error()
Reproducira standardnu obavijest „Error“.

```js
notify.error();
```

### blink()
Treperi LED diodom za obavijesti.

**Parametri:**

- boja (`color`): `"blue"`, `"red"`, `"green"`, `"yellow"`, `"cyan"` ili `"magenta"`;
- vrsta treptanja (`blink type`): `"short"` ili `"long"`.

```js
notify.blink("red", "short"); // Kratko treptanje crvene LED diode
notify.blink("green", "long"); // Dugo treptanje zelene LED diode
```

Vibracija, zvuk i svjetlina LED diode prate korisničke postavke u `Settings → LCD and Notifications`.
