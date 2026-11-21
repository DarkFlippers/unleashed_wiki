---
title: "JavaScript: event loop"
sidebarTitle: "JS: event_loop"
order: 260
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_event_loop.md]
sources: [unleashed-docs]
---
# Event loop module

The event loop is the core of event-driven programming, and Flipper's JS subsystem is built around it. Learn it **before** using the advanced modules (GPIO interrupts, GUI).

```js
let eventLoop = require("event_loop");
```

## The idea

In JavaScript you constantly pass a function to be called later, when something happens. This is a callback:

```js
setTimeout(function() { console.log("Hello, World!") }, 1000);
```

Behind this, most JS runtimes run a queue of events and a long loop that takes events from the queue and calls the matching callbacks. In pseudocode:

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

Browsers and Node.js hide this loop. **Flipper JS does not**: you create event sources, subscribe callbacks to them and start the loop yourself.

## Example: a one-shot timer

The Flipper equivalent of the `setTimeout` example:

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

## Extra arguments instead of closures

mJS **does not support closures**: a function cannot read variables from the scope where it was defined. That is why `subscribe()` accepts extra arguments after the callback and passes them into it. Above, `eventLoop` is passed so the callback can call `eventLoop.stop()`.

The callback can also **change** these values for the next call by returning an array of the same length:

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

There are two extra arguments here, so any return value other than an array of length 2 leaves them unchanged.

The first two arguments of every callback are always:

1. the **subscription manager**, which lets you `.cancel()` the subscription;
2. the **event item**, for events that carry data. Timer events carry none and give `undefined`.

## API reference

### run()
Runs the event loop until it is stopped with `stop()`.

### subscribe()
Subscribes a function to an event.

- **Parameters:**
  - `contract`: an event source identifier;
  - `callback`: the function to call when the event happens;
  - extra arguments: passed as extra arguments to the callback.

The callback gets at least two arguments plus the extra ones: the subscription manager (the same object `subscribe` returns) and the event item (`undefined` for events without data). It may return an array of the same length as the number of extra arguments to replace them for the next call. Other return values are discarded.

- **Returns:** a `SubscriptionManager` object:
  - `SubscriptionManager.cancel()` unsubscribes the callback from the event.

::: warning
Each event source can have **only one** callback.
:::

### stop()
Stops the event loop.

### timer()
Creates an event source that fires at a fixed interval, once or forever.

- **Parameters:**
  - `mode`: `"oneshot"` or `"periodic"`;
  - `interval`: the timeout (for `"oneshot"` timers) or the period (for `"periodic"` timers), in ms.
- **Returns:** a `Contract` object for `subscribe()`'s first parameter.

### queue()
Creates a queue for passing messages.

- **Parameters:** `length`, the maximum number of items in the queue.
- **Returns:** a `Queue` object:
  - `Queue.send(message)`: puts `message` (any type) at the end of the queue;
  - `input`: a `Contract` (event source) that pops items from the front of the queue.

## Related

- [GPIO](/dev/js-gpio): pin interrupts are event-loop contracts.
- [GUI](/dev/js-gui): view events and navigation are event-loop contracts.
