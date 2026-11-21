---
title: "JavaScript: GUI"
sidebarTitle: "JS: gui"
order: 270
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_gui]
sources: [unleashed-docs, unleashed-src]
---
# Модуль gui

Модуль `gui` відкриває скриптам доступ до стандартного інтерфейсу Flipper Zero: меню, клавіатур, діалогів, текстових полів тощо. Він залежить від `event_loop`, тому його **обов’язково** завантажувати після нього:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
```

Окремі екрани («представлення», views) — це окремі модулі з назвами `gui/<view>`. Їх описано на сторінці [Представлення GUI](/ua/dev/js-gui-views).

## Поняття

**Цикл подій.** Будь-яке введення в GUI надходить як події циклу подій. Спершу прочитайте [Цикл подій](/ua/dev/js-event-loop).

**Canvas** (канва). Область малювання без жодних абстракцій. Малювати на ній напряму потрібно лише для нестандартних елементів оформлення, тож трапляється це рідко.

**Viewport.** Вікно, що показує прямокутну частину канви. Застосунки завжди малюють через viewport.

**View** (представлення). Повноекранний елемент інтерфейсу, який забирає собі весь viewport і все введення. Доступні представлення:

`button_menu`, `button_panel`, `byte_input`, `dialog`, `empty_screen`, `file_picker`, `loading`, `menu`, `number_input`, `popup`, `submenu`, `text_box`, `text_input`, `vi_list`, `widget`.

Кожне представлення має **властивості** («props»). Задати їх можна двома способами:

- створити представлення через `makeWith(props)`, передавши початкові властивості;
- змінити властивість уже створеного представлення через `set(name, value)`.

**View Dispatcher.** Тримає всі представлення застосунку й перемикається між ними на запит.

**Scene Manager.** Необов’язкове доповнення до view dispatcher для складної навігації. З JS недоступне.

| Підхід | Для чого | Доступно з JS |
|---|---|---|
| Лише ViewPort | Прямий доступ до графічного API, без абстракцій інтерфейсу | Ні |
| ViewDispatcher | Стандартні елементи інтерфейсу у системному стилі | **Так** |
| SceneManager | Додаткове керування навігацією для складних застосунків | Ні |

## Приклад {#example}

Три представлення під керуванням view dispatcher:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
let loadingView = require("gui/loading");
let submenuView = require("gui/submenu");
let emptyView = require("gui/empty_screen");

// Common pattern: declare all the views in an object. This is absolutely not
// required, but adds clarity to the script.
let views = {
    // the view dispatcher auto-✨magically✨ remembers views as they are created
    loading: loadingView.make(),
    empty: emptyView.make(),
    demos: submenuView.makeWith({
        header: "Choose a demo",
    }, [
        "Hourglass screen",
        "Empty screen",
        "Exit app",
    ]),
};

// go to different screens depending on what was selected
eventLoop.subscribe(views.demos.chosen, function (_sub, index, gui, eventLoop, views) {
    if (index === 0) {
        gui.viewDispatcher.switchTo(views.loading);
    } else if (index === 1) {
        gui.viewDispatcher.switchTo(views.empty);
    } else if (index === 2) {
        eventLoop.stop();
    }
}, gui, eventLoop, views);

// go to the demo chooser screen when the back key is pressed
eventLoop.subscribe(gui.viewDispatcher.navigation, function (_sub, _, gui, views) {
    gui.viewDispatcher.switchTo(views.demos);
}, gui, views);

// run UI
gui.viewDispatcher.switchTo(views.demos);
eventLoop.run();
```

::: warning Пункти submenu передаються як дочірні елементи
В офіційній документації пункти submenu передаються як властивість `items` (`makeWith({ items: [...] })`). У поточній прошивці (JS SDK 0.4+) submenu має лише властивість `header`, а **пункти є дочірніми елементами**: другий аргумент `makeWith()` або додавання через `addChild()`. Приклад вище використовує актуальний API — так само, як вбудований приклад `gui.js`.
:::

Значно більша демонстрація з усіма представленнями встановлюється разом із прошивкою як `/ext/apps/Scripts/js_examples/gui.js`.

## Довідник API

### viewDispatcher
Константа `viewDispatcher` містить єдиний екземпляр `ViewDispatcher`.

#### viewDispatcher.switchTo(view)
Перемикається на представлення, передаючи йому контроль над дисплеєм і введенням.

- `view`: `View`, на яке потрібно перемкнутися.

#### viewDispatcher.sendTo(direction)
Переносить viewport, яким керує dispatcher, на передній план стека (робить його видимим) або на задній (робить невидимим).

- `direction`: `"front"` або `"back"`.

#### viewDispatcher.sendCustom(event)
Надсилає власне число обробнику події `custom`.

- `event`: число, яке потрібно надіслати.

#### viewDispatcher.custom
`Contract` циклу подій для власних подій; спрацьовує від `ViewDispatcher.sendCustom(event)`.

#### viewDispatcher.navigation
`Contract` циклу подій для подій навігації; спрацьовує при натисканні <kbd>Back</kbd>.

#### viewDispatcher.currentView
Представлення (`View`), яке показується зараз.

### ViewFactory
Імпорт модуля представлення дає вам `ViewFactory`. У прикладі вище `loadingView`, `submenuView` і `emptyView` — це фабрики представлень.

#### ViewFactory.make()
Створює екземпляр `View`.

#### ViewFactory.makeWith(props, children)
Створює `View` і присвоює йому початкові властивості з `props`, а також, за бажанням, список дочірніх елементів.

- `props`: простий об’єкт «ключ-значення», наприклад `{ header: "Header" }`;
- `children`: необов’язковий масив дочірніх елементів, наприклад `[ { element: "button", button: "right", text: "Back" } ]`.

### View
`ViewFactory.make()` і `ViewFactory.makeWith()` повертають `View`. У прикладі вище `views.loading`, `views.demos` і `views.empty` — це представлення.

#### View.set(property, value)
Присвоює значення властивості за її назвою.

- `property`: назва властивості;
- `value`: нове значення.

#### View.addChild(child)
Додає дочірній елемент до представлення.

- `child`: елемент, який потрібно додати, наприклад `{ element: "button", button: "right", text: "Back" }`.

Формат дочірнього елемента залежить від типу представлення; див. [Представлення GUI](/ua/dev/js-gui-views).

#### View.resetChildren()
Видаляє всі дочірні елементи представлення.

#### View.setChildren(children)
Видаляє всі попередні дочірні елементи й призначає нові.

- `children`: масив нових дочірніх елементів, наприклад `[ { element: "button", button: "right", text: "Back" } ]`.

### Загальні типи

З типів SDK:

```ts
type Font = "primary" | "secondary" | "keyboard" | "big_numbers";
type InputType = "press" | "release" | "short" | "long" | "repeat";
```
