---
title: "JavaScript: использование модулей"
sidebarTitle: "JS: модули"
order: 230
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_using_js_modules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules]
sources: [unleashed-docs, unleashed-src]
---
# Использование JS-модулей

[Встроенных функций](/ru/dev/js-builtin) намеренно мало. Работа с железом и системой вынесена в **JS-модули**, например:

- `serial` — приём и передача данных по UART;
- `badusb` — эмуляция USB-клавиатуры;
- `math` — математические функции.

Модули написаны на C, поэтому работают быстро. Они поставляются с прошивкой и лежат на SD-карте в скомпилированном виде как плагины **FAL (Flipper Application File)**. Исходники: [`applications/system/js_app/modules`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules). Список модулей см. в [обзоре JavaScript](/ru/dev/js-about).

## Подключение модуля

Перед вызовом методов модуль **обязательно** нужно подключить через `require()`. Это загружает модуль в ОЗУ.

- Подключайте только то, что используете, чтобы экономить ОЗУ. (`math`, например, после загрузки занимает около 21 КБ.)
- Все загруженные модули автоматически выгружаются после завершения скрипта.
- Модуль можно подключить только один раз за скрипт; повторный `require()` того же имени завершится ошибкой `"... module is already installed"`.
- Некоторые модули зависят от других и подключаются после них: `gpio` и `gui` требуют `event_loop`, а каждый вид `gui/*` требует `gui`.

Имя модуля передаётся в кавычках:

```js
let notify = require("notification");
```

Дальше методы вызываются через переменную:

```js
let notify = require("notification");

notify.success();
print("success notification");
```

Прошивка также принимает имя в стиле SDK `require("@flipperdevices/fz-sdk/notification")`: префикс отбрасывается автоматически. Имена со слешем, например `gui/submenu`, соответствуют файлу плагина `js_gui__submenu`.

## Что дальше

- Пройдитесь по страницам модулей в этом разделе, начиная с [Event loop](/ru/dev/js-event-loop) и [GUI](/ru/dev/js-gui).
- Посмотрите примеры в `/ext/apps/Scripts/js_examples/`.
