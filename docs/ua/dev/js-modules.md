---
title: "JavaScript: використання модулів"
sidebarTitle: "JS: використання модулів"
order: 230
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_using_js_modules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules]
sources: [unleashed-docs, unleashed-src]
---
# Використання JavaScript-модулів

[Вбудованих функцій](/ua/dev/js-builtin) навмисно обмаль. Робота з апаратною частиною та системними можливостями живе в **JS-модулях**, наприклад:

- `serial` надсилає й приймає дані через UART;
- `badusb` емулює USB-клавіатуру;
- `math` надає математичні функції.

Модулі написані на C, тому вони швидкі. Вони постачаються з прошивкою і зберігаються на картці microSD у скомпільованому вигляді — як плагіни **FAL (Flipper Application File)**. Вихідний код модулів: [`applications/system/js_app/modules`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules). Перелік модулів наведено в [огляді JavaScript](/ua/dev/js-about).

## Завантаження модуля

Перед викликом методів модуль **обов’язково** потрібно завантажити через `require()`. Це поміщає модуль у RAM.

- Завантажуйте лише те, що використовуєте, щоб економити RAM. (Наприклад, `math` після завантаження займає близько 21 КБ RAM.)
- Усі завантажені модулі вивантажуються автоматично, коли скрипт завершується.
- У межах одного скрипта модуль можна завантажити лише раз; повторний `require()` з тією самою назвою завершиться помилкою `"... module is already installed"`.
- Деякі модулі залежать від інших і мають завантажуватися після них: `gpio` і `gui` потребують `event_loop`, а кожне представлення `gui/*` потребує `gui`.

Назву модуля передавайте в лапках:

```js
let notify = require("notification");
```

Потім викликайте його методи через змінну:

```js
let notify = require("notification");

notify.success();
print("success notification");
```

Прошивка також приймає назви у стилі SDK — `require("@flipperdevices/fz-sdk/notification")`: префікс відкидається автоматично. Назви зі скісною рискою, як-от `gui/submenu`, відповідають файлу плагіна `js_gui__submenu`.

## Що далі

- Перегляньте сторінки модулів у цьому розділі, починаючи з [Циклу подій](/ua/dev/js-event-loop) і [GUI](/ua/dev/js-gui).
- Вивчіть приклади скриптів у `/ext/apps/Scripts/js_examples/`.
