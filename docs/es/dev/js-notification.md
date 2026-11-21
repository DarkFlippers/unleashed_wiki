---
title: "JavaScript: notification"
sidebarTitle: "JS: notification"
order: 330
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_notification.md]
sources: [unleashed-docs]
---
# Módulo Notification

Reproduce las notificaciones del sistema (LED, vibración, sonido) y hace parpadear el LED RGB.

```js
let notify = require("notification");
```

Script de ejemplo: `/ext/apps/Scripts/js_examples/notify.js`.

## Métodos

### success()
Reproduce la notificación estándar de «Success».

```js
notify.success();
```

### error()
Reproduce la notificación estándar de «Error».

```js
notify.error();
```

### blink()
Hace parpadear el LED de notificación.

**Parámetros:**

- color: `"blue"`, `"red"`, `"green"`, `"yellow"`, `"cyan"` o `"magenta"`;
- tipo de parpadeo: `"short"` o `"long"`.

```js
notify.blink("red", "short"); // Short blink of red LED
notify.blink("green", "long"); // Long blink of green LED
```

La vibración, el sonido y el brillo del LED siguen los ajustes del usuario en `Settings → LCD and Notifications`.
