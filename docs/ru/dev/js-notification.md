---
title: "JavaScript: notification"
sidebarTitle: "JS: notification"
order: 330
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_notification.md]
sources: [unleashed-docs]
---
# Модуль Notification

Проигрывает системные уведомления (светодиод, вибрация, звук) и мигает RGB-светодиодом.

```js
let notify = require("notification");
```

Пример: `/ext/apps/Scripts/js_examples/notify.js`.

## Методы

### success()
Стандартное уведомление «Успех».

```js
notify.success();
```

### error()
Стандартное уведомление «Ошибка».

```js
notify.error();
```

### blink()
Мигает светодиодом уведомлений.

**Параметры:**

- цвет: `"blue"`, `"red"`, `"green"`, `"yellow"`, `"cyan"` или `"magenta"`;
- тип мигания: `"short"` или `"long"`.

```js
notify.blink("red", "short"); // Short blink of red LED
notify.blink("green", "long"); // Long blink of green LED
```

Вибрация, звук и яркость светодиода зависят от настроек пользователя в `Settings → LCD and Notifications`.
