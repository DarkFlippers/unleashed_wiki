---
title: "JavaScript: notification"
sidebarTitle: "JS: notification"
order: 330
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_notification.md]
sources: [unleashed-docs]
---
# Модуль notification

Відтворює системні сповіщення (світлодіод, вібрація, звук) і блимає RGB-світлодіодом.

```js
let notify = require("notification");
```

Приклад скрипта: `/ext/apps/Scripts/js_examples/notify.js`.

## Методи

### success()
Відтворює стандартне сповіщення «Success».

```js
notify.success();
```

### error()
Відтворює стандартне сповіщення «Error».

```js
notify.error();
```

### blink()
Блимає світлодіодом сповіщень.

**Параметри:**

- колір: `"blue"`, `"red"`, `"green"`, `"yellow"`, `"cyan"` або `"magenta"`;
- тип блимання: `"short"` або `"long"`.

```js
notify.blink("red", "short"); // Short blink of red LED
notify.blink("green", "long"); // Long blink of green LED
```

Вібрація, звук і яскравість світлодіода залежать від налаштувань користувача в `Settings → LCD and Notifications`.
