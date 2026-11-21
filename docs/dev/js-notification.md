---
title: "JavaScript: notification"
sidebarTitle: "JS: notification"
order: 330
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_notification.md]
sources: [unleashed-docs]
---
# Notification module

Plays the system notifications (LED, vibration, sound) and blinks the RGB LED.

```js
let notify = require("notification");
```

Example script: `/ext/apps/Scripts/js_examples/notify.js`.

## Methods

### success()
Plays the standard "Success" notification.

```js
notify.success();
```

### error()
Plays the standard "Error" notification.

```js
notify.error();
```

### blink()
Blinks the notification LED.

**Parameters:**

- color: `"blue"`, `"red"`, `"green"`, `"yellow"`, `"cyan"` or `"magenta"`;
- blink type: `"short"` or `"long"`.

```js
notify.blink("red", "short"); // Short blink of red LED
notify.blink("green", "long"); // Long blink of green LED
```

The vibration, sound and LED brightness follow the user's settings in `Settings → LCD and Notifications`.
