---
title: "JavaScript: GUI"
sidebarTitle: "JS: gui"
order: 270
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_gui]
sources: [unleashed-docs, unleashed-src]
---
# Модуль GUI

Модуль `gui` даёт скриптам доступ к стандартному интерфейсу Flipper Zero: меню, клавиатуры, диалоги, текстовые поля и т. д. Он зависит от `event_loop`, поэтому **обязательно** подключается после него:

```js
let eventLoop = require("event_loop");
let gui = require("gui");
```

Отдельные экраны («виды», views) — это отдельные модули `gui/<вид>`. Они описаны на странице [Виды GUI](/ru/dev/js-gui-views).

## Основные понятия

**Event loop.** Весь ввод в GUI приходит событиями цикла событий. Сначала прочитайте [Event loop](/ru/dev/js-event-loop).

**Canvas (холст).** Область рисования без абстракций. Рисовать на нём напрямую нужно только для своих элементов интерфейса, и это редкость.

**Viewport.** Окно в прямоугольную часть холста. Приложения всегда рисуют через viewport.

**View (вид).** Полноэкранный элемент интерфейса, который забирает весь viewport и весь ввод. Доступные виды:

`button_menu`, `button_panel`, `byte_input`, `dialog`, `empty_screen`, `file_picker`, `loading`, `menu`, `number_input`, `popup`, `submenu`, `text_box`, `text_input`, `vi_list`, `widget`.

У каждого вида есть **свойства** (props). Задать их можно двумя способами:

- создать вид через `makeWith(props)`, передав начальные свойства;
- изменить свойство существующего вида через `set(name, value)`.

**View Dispatcher.** Хранит все виды приложения и переключает их по запросу.

**Scene Manager.** Необязательная надстройка над view dispatcher для сложной навигации. Из JS недоступна.

| Подход | Для чего | Доступен из JS |
|---|---|---|
| Только ViewPort | Прямой доступ к графическому API без UI-абстракций | Нет |
| ViewDispatcher | Стандартные элементы в стиле системы | **Да** |
| SceneManager | Управление навигацией в сложных приложениях | Нет |

## Пример {#example}

Три вида под управлением view dispatcher:

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

::: warning Пункты submenu передаются как дочерние элементы
В официальной документации пункты submenu передаются свойством `items` (`makeWith({ items: [...] })`). В текущей прошивке (JS SDK 0.4+) у submenu есть только свойство `header`, а **пункты — это дочерние элементы**: второй аргумент `makeWith()` или `addChild()`. Пример выше использует актуальный API, как и встроенный пример `gui.js`.
:::

Большое демо со всеми видами лежит в `/ext/apps/Scripts/js_examples/gui.js`.

## Справочник API

### viewDispatcher
Константа `viewDispatcher` содержит синглтон `ViewDispatcher`.

#### viewDispatcher.switchTo(view)
Переключается на вид и отдаёт ему экран и ввод.

- `view` — `View`, на который переключиться.

#### viewDispatcher.sendTo(direction)
Перемещает viewport диспетчера на передний план (делая его видимым) или на задний (делая невидимым).

- `direction` — `"front"` или `"back"`.

#### viewDispatcher.sendCustom(event)
Отправляет произвольное число обработчику события `custom`.

- `event` — отправляемое число.

#### viewDispatcher.custom
`Contract` цикла событий для пользовательских событий, вызываемых `ViewDispatcher.sendCustom(event)`.

#### viewDispatcher.navigation
`Contract` цикла событий для навигации, срабатывает при нажатии <kbd>Back</kbd>.

#### viewDispatcher.currentView
Текущий отображаемый `View`.

### ViewFactory
При подключении модуля вида вы получаете `ViewFactory`. В примере `loadingView`, `submenuView` и `emptyView` — фабрики видов.

#### ViewFactory.make()
Создаёт экземпляр `View`.

#### ViewFactory.makeWith(props, children)
Создаёт `View`, задаёт начальные свойства из `props` и, при желании, список дочерних элементов.

- `props` — простой объект ключ-значение, например `{ header: "Header" }`;
- `children` — необязательный массив дочерних элементов, например `[ { element: "button", button: "right", text: "Back" } ]`.

### View
`ViewFactory.make()` и `ViewFactory.makeWith()` возвращают `View`. В примере `views.loading`, `views.demos` и `views.empty` — виды.

#### View.set(property, value)
Присваивает значение свойству по имени.

- `property` — имя свойства;
- `value` — новое значение.

#### View.addChild(child)
Добавляет дочерний элемент.

- `child` — элемент, например `{ element: "button", button: "right", text: "Back" }`.

Формат элемента зависит от типа вида, см. [Виды GUI](/ru/dev/js-gui-views).

#### View.resetChildren()
Удаляет все дочерние элементы.

#### View.setChildren(children)
Удаляет прежние дочерние элементы и задаёт новые.

- `children` — массив новых элементов, например `[ { element: "button", button: "right", text: "Back" } ]`.

### Общие типы

Из типов SDK:

```ts
type Font = "primary" | "secondary" | "keyboard" | "big_numbers";
type InputType = "press" | "release" | "short" | "long" | "repeat";
```
