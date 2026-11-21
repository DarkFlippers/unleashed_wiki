---
title: "JavaScript: event loop"
sidebarTitle: "JS: event_loop"
order: 260
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_event_loop.md]
sources: [unleashed-docs]
---
# Modul event loop

Der Event Loop ist der Kern der ereignisgesteuerten Programmierung, und das JS-Subsystem des Flipper ist um ihn
herum aufgebaut. Mach dich damit vertraut, **bevor** du die fortgeschrittenen Module benutzt (GPIO-Interrupts, GUI).

```js
let eventLoop = require("event_loop");
```

## Die Idee

In JavaScript übergibst du ständig eine Funktion, die später aufgerufen werden soll, wenn etwas passiert. Das ist
ein Callback:

```js
setTimeout(function() { console.log("Hello, World!") }, 1000);
```

Dahinter betreiben die meisten JS-Laufzeitumgebungen eine Ereigniswarteschlange und eine lange Schleife, die
Ereignisse aus der Warteschlange nimmt und die zugehörigen Callbacks aufruft. In Pseudocode:

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

Browser und Node.js verbergen diese Schleife. **Flipper JS tut das nicht**: du erzeugst Ereignisquellen,
abonnierst Callbacks darauf und startest die Schleife selbst.

## Beispiel: ein einmaliger Timer

Das Flipper-Pendant zum `setTimeout`-Beispiel:

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

## Zusätzliche Argumente statt Closures

mJS **unterstützt keine Closures**: eine Funktion kann keine Variablen aus dem Scope lesen, in dem sie definiert
wurde. Deshalb nimmt `subscribe()` nach dem Callback zusätzliche Argumente an und übergibt sie an ihn. Oben wird
`eventLoop` übergeben, damit der Callback `eventLoop.stop()` aufrufen kann.

Der Callback kann diese Werte für den nächsten Aufruf auch **ändern**, indem er ein Array derselben Länge
zurückgibt:

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

Hier gibt es zwei zusätzliche Argumente, deshalb lässt jeder Rückgabewert, der kein Array der Länge 2 ist, sie
unverändert.

Die ersten beiden Argumente jedes Callbacks sind immer:

1. der **Subscription Manager**, über den du das Abonnement mit `.cancel()` beenden kannst;
2. das **Event Item**, bei Ereignissen, die Daten mitbringen. Timer-Ereignisse bringen keine mit und liefern
   `undefined`.

## API-Referenz

### run()
Lässt den Event Loop laufen, bis er mit `stop()` angehalten wird.

### subscribe()
Abonniert eine Funktion auf ein Ereignis.

- **Parameter:**
  - `contract`: eine Kennung der Ereignisquelle;
  - `callback`: die Funktion, die beim Eintreten des Ereignisses aufgerufen wird;
  - zusätzliche Argumente: werden als zusätzliche Argumente an den Callback übergeben.

Der Callback erhält mindestens zwei Argumente zuzüglich der zusätzlichen: den Subscription Manager (dasselbe Objekt,
das `subscribe` zurückgibt) und das Event Item (`undefined` bei Ereignissen ohne Daten). Er darf ein Array mit
derselben Länge wie die Anzahl der zusätzlichen Argumente zurückgeben, um sie für den nächsten Aufruf zu ersetzen.
Andere Rückgabewerte werden verworfen.

- **Rückgabe:** ein `SubscriptionManager`-Objekt:
  - `SubscriptionManager.cancel()` hebt das Abonnement des Callbacks auf das Ereignis auf.

::: warning
Jede Ereignisquelle kann **nur einen** Callback haben.
:::

### stop()
Hält den Event Loop an.

### timer()
Erzeugt eine Ereignisquelle, die in einem festen Intervall auslöst, einmalig oder dauerhaft.

- **Parameter:**
  - `mode`: `"oneshot"` oder `"periodic"`;
  - `interval`: das Timeout (bei `"oneshot"`-Timern) oder die Periode (bei `"periodic"`-Timern), in ms.
- **Rückgabe:** ein `Contract`-Objekt für den ersten Parameter von `subscribe()`.

### queue()
Erzeugt eine Warteschlange zum Übergeben von Nachrichten.

- **Parameter:** `length`, die maximale Anzahl Elemente in der Warteschlange.
- **Rückgabe:** ein `Queue`-Objekt:
  - `Queue.send(message)`: stellt `message` (beliebiger Typ) an das Ende der Warteschlange;
  - `input`: ein `Contract` (eine Ereignisquelle), das Elemente vom Anfang der Warteschlange entnimmt.

## Verwandte Themen

- [GPIO](/de/dev/js-gpio): Pin-Interrupts sind Event-Loop-Contracts.
- [GUI](/de/dev/js-gui): View-Ereignisse und Navigation sind Event-Loop-Contracts.
