---
title: "JavaScript: цикл событий"
sidebarTitle: "JS: event_loop"
order: 260
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_event_loop.md]
sources: [unleashed-docs]
---
# Модуль Event loop (цикл событий)

Цикл событий — основа событийного программирования, и JS-подсистема Flipper построена вокруг него. Разберитесь с ним **до** того, как браться за продвинутые модули (прерывания GPIO, GUI).

```js
let eventLoop = require("event_loop");
```

## Идея

В JavaScript постоянно передают функцию, которую нужно вызвать позже, когда что-то произойдёт. Это колбэк:

```js
setTimeout(function() { console.log("Hello, World!") }, 1000);
```

Под капотом большинство JS-движков держат очередь событий и бесконечный цикл, который достаёт события из очереди и вызывает соответствующие колбэки. В псевдокоде:

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

Браузеры и Node.js этот цикл прячут. **Flipper JS — нет**: вы сами создаёте источники событий, подписываете на них колбэки и запускаете цикл.

## Пример: одноразовый таймер

Аналог примера с `setTimeout` на Flipper:

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

## Дополнительные аргументы вместо замыканий

mJS **не поддерживает замыкания**: функция не видит переменные области, где она объявлена. Поэтому `subscribe()` принимает после колбэка дополнительные аргументы и передаёт их в него. Выше передан `eventLoop`, чтобы колбэк мог вызвать `eventLoop.stop()`.

Колбэк может **изменить** эти значения для следующего вызова, вернув массив той же длины:

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

Здесь два дополнительных аргумента, поэтому любой результат, кроме массива длины 2, оставит их без изменений.

Первые два аргумента любого колбэка всегда такие:

1. **менеджер подписки**, через него можно отменить подписку `.cancel()`;
2. **элемент события** для событий с данными. Таймеры данных не несут, у них `undefined`.

## Справочник API

### run()
Запускает цикл событий до вызова `stop()`.

### subscribe()
Подписывает функцию на событие.

- **Параметры:**
  - `contract` — идентификатор источника событий;
  - `callback` — функция, вызываемая при событии;
  - дополнительные аргументы — передаются в колбэк.

Колбэк получает минимум два аргумента плюс дополнительные: менеджер подписки (тот же объект, что возвращает `subscribe`) и элемент события (`undefined` для событий без данных). Он может вернуть массив той же длины, что и число дополнительных аргументов, чтобы заменить их для следующего вызова. Прочие возвращаемые значения отбрасываются.

- **Возвращает:** объект `SubscriptionManager`:
  - `SubscriptionManager.cancel()` отписывает колбэк от события.

::: warning
У каждого источника событий может быть **только один** колбэк.
:::

### stop()
Останавливает цикл событий.

### timer()
Создаёт источник событий, который срабатывает с постоянным интервалом один раз или бесконечно.

- **Параметры:**
  - `mode` — `"oneshot"` или `"periodic"`;
  - `interval` — таймаут (для `"oneshot"`) или период (для `"periodic"`), в мс.
- **Возвращает:** объект `Contract` для первого параметра `subscribe()`.

### queue()
Создаёт очередь для обмена сообщениями.

- **Параметры:** `length` — максимальное число элементов в очереди.
- **Возвращает:** объект `Queue`:
  - `Queue.send(message)` — кладёт `message` (любого типа) в конец очереди;
  - `input` — `Contract` (источник событий), который достаёт элементы из начала очереди.

## См. также

- [GPIO](/ru/dev/js-gpio): прерывания пинов — это контракты цикла событий.
- [GUI](/ru/dev/js-gui): события видов и навигация — тоже контракты цикла событий.
