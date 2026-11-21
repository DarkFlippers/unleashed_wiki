---
title: "JavaScript: цикл подій"
sidebarTitle: "JS: event_loop"
order: 260
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_event_loop.md]
sources: [unleashed-docs]
---
# Модуль event_loop

Цикл подій — основа подієво-орієнтованого програмування, і підсистема JS у Flipper побудована саме навколо нього. Розберіться з ним **перед** тим, як братися за складніші модулі (перервання GPIO, GUI).

```js
let eventLoop = require("event_loop");
```

## Ідея

У JavaScript ви постійно передаєте функцію, яку потрібно викликати пізніше, коли щось станеться. Це колбек:

```js
setTimeout(function() { console.log("Hello, World!") }, 1000);
```

За цим стоїть те, що більшість середовищ виконання JS тримають чергу подій і довгий цикл, який бере події з черги й викликає відповідні колбеки. У псевдокоді:

```js
while(loop_is_running()) {
    if(event_available_in_queue()) {
        let event = fetch_event_from_queue();
        let callback = get_callback_associated_with(event);
        if(callback)
            callback(get_extra_data_for(event));
    } else {
        // avoid wasting CPU time
        sleep_until_any_event_becomes_available();
    }
}
```

Браузери й Node.js приховують цей цикл. **Flipper JS — ні**: ви самі створюєте джерела подій, підписуєте на них колбеки й запускаєте цикл.

## Приклад: одноразовий таймер

Аналог прикладу з `setTimeout` для Flipper:

```js
// import module
let eventLoop = require("event_loop");

// create an event source that will fire once 1 second after it has been created
let timer = eventLoop.timer("oneshot", 1000);

// subscribe a callback to the event source
eventLoop.subscribe(timer, function(_subscription, _item, eventLoop) {
    print("Hello, World!");
    eventLoop.stop();
}, eventLoop); // notice this extra argument. we'll come back to this later

// run the loop until it is stopped
eventLoop.run();

// the previous line will only finish executing once `.stop()` is called, hence
// the following line will execute only after "Hello, World!" is printed
print("Stopped");
```

## Додаткові аргументи замість замикань

mJS **не підтримує замикань**: функція не може читати змінні з області видимості, де її було визначено. Саме тому `subscribe()` приймає додаткові аргументи після колбека й передає їх у нього. У прикладі вище передається `eventLoop`, щоб колбек міг викликати `eventLoop.stop()`.

Колбек також може **змінити** ці значення для наступного виклику, повернувши масив такої самої довжини:

```js
// this timer will fire every second
let timer = eventLoop.timer("periodic", 1000);
eventLoop.subscribe(timer, function(_subscription, _item, counter, eventLoop) {
    print("Counter is at:", counter);
    if(counter === 10)
        eventLoop.stop();
    // modify the extra arguments that will be passed to us the next time
    return [counter + 1, eventLoop];
}, 0, eventLoop);
```

Тут два додаткових аргументи, тож будь-яке повернене значення, окрім масиву довжиною 2, залишає їх без змін.

Перші два аргументи кожного колбека завжди такі:

1. **менеджер підписки** — через нього можна викликати `.cancel()` і скасувати підписку;
2. **елемент події** — для подій, що несуть дані. Події таймера даних не несуть, тому там буде `undefined`.

## Довідник API

### run()
Запускає цикл подій і виконує його, доки не буде викликано `stop()`.

### subscribe()
Підписує функцію на подію.

- **Параметри:**
  - `contract`: ідентифікатор джерела подій;
  - `callback`: функція, яку буде викликано, коли станеться подія;
  - додаткові аргументи: передаються в колбек як додаткові аргументи.

Колбек отримує щонайменше два аргументи плюс додаткові: менеджер підписки (той самий об’єкт, який повертає `subscribe`) і елемент події (`undefined` для подій без даних). Колбек може повернути масив такої самої довжини, як кількість додаткових аргументів, щоб замінити їх для наступного виклику. Інші повернені значення відкидаються.

- **Повертає:** об’єкт `SubscriptionManager`:
  - `SubscriptionManager.cancel()` скасовує підписку колбека на подію.

::: warning
Кожне джерело подій може мати **лише один** колбек.
:::

### stop()
Зупиняє цикл подій.

### timer()
Створює джерело подій, яке спрацьовує через заданий інтервал — один раз або постійно.

- **Параметри:**
  - `mode`: `"oneshot"` або `"periodic"`;
  - `interval`: час очікування (для таймерів `"oneshot"`) або період (для таймерів `"periodic"`) у мс.
- **Повертає:** об’єкт `Contract` для першого параметра `subscribe()`.

### queue()
Створює чергу для передавання повідомлень.

- **Параметри:** `length` — максимальна кількість елементів у черзі.
- **Повертає:** об’єкт `Queue`:
  - `Queue.send(message)`: ставить `message` (будь-якого типу) в кінець черги;
  - `input`: `Contract` (джерело подій), який знімає елементи з початку черги.

## Пов’язані сторінки

- [GPIO](/ua/dev/js-gpio): перервання на виводах — це контракти циклу подій.
- [GUI](/ua/dev/js-gui): події представлень і навігація — також контракти циклу подій.
