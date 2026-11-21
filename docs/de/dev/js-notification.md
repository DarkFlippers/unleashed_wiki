---
title: "JavaScript: notification"
sidebarTitle: "JS: notification"
order: 330
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_notification.md]
sources: [unleashed-docs]
---
# Modul notification

Spielt die Systembenachrichtigungen ab (LED, Vibration, Ton) und lässt die RGB-LED blinken.

```js
let notify = require("notification");
```

Beispielskript: `/ext/apps/Scripts/js_examples/notify.js`.

## Methoden

### success()
Spielt die Standardbenachrichtigung "Success" ab.

```js
notify.success();
```

### error()
Spielt die Standardbenachrichtigung "Error" ab.

```js
notify.error();
```

### blink()
Lässt die Benachrichtigungs-LED blinken.

**Parameter:**

- Farbe: `"blue"`, `"red"`, `"green"`, `"yellow"`, `"cyan"` oder `"magenta"`;
- Blinkart: `"short"` oder `"long"`.

```js
notify.blink("red", "short"); // Short blink of red LED
notify.blink("green", "long"); // Long blink of green LED
```

Vibration, Ton und LED-Helligkeit folgen den Benutzereinstellungen unter `Settings → LCD and Notifications`.
