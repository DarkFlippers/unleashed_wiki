---
title: "JavaScript: event loop"
sidebarTitle: "JS: event_loop"
order: 260
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_event_loop.md]
sources: [unleashed-docs]
---
# Modulo event loop

L'event loop è il cuore della programmazione a eventi, e il sottosistema JS del Flipper è costruito attorno a esso. Imparalo **prima** di usare i moduli avanzati (interrupt GPIO, GUI).

```js
let eventLoop = require("event_loop");
```

## L'idea

In JavaScript si passa continuamente una funzione da richiamare più tardi, quando accade qualcosa. Questa è una callback:

```js
setTimeout(function() { console.log("Hello, World!") }, 1000);
```

Dietro le quinte, la maggior parte dei runtime JS gestisce una coda di eventi e un lungo ciclo che prende gli eventi dalla coda e chiama le callback corrispondenti. In pseudocodice:

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

I browser e Node.js nascondono questo ciclo. **Il JS del Flipper no**: crei tu le sorgenti di eventi, iscrivi le callback a esse e avvii il ciclo in prima persona.

## Esempio: un timer a colpo singolo

L'equivalente Flipper dell'esempio con `setTimeout`:

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

## Argomenti aggiuntivi invece delle closure

mJS **non supporta le closure**: una funzione non può leggere le variabili dello scope in cui è stata definita. Per questo `subscribe()` accetta argomenti aggiuntivi dopo la callback e li passa al suo interno. Nell'esempio sopra `eventLoop` viene passato così che la callback possa chiamare `eventLoop.stop()`.

La callback può anche **modificare** questi valori per la chiamata successiva restituendo un array della stessa lunghezza:

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

Qui gli argomenti aggiuntivi sono due, quindi qualunque valore restituito diverso da un array di lunghezza 2 li lascia invariati.

I primi due argomenti di ogni callback sono sempre:

1. il **gestore dell'iscrizione**, che permette di annullarla con `.cancel()`;
2. l'**elemento dell'evento**, per gli eventi che trasportano dati. Gli eventi dei timer non ne trasportano e restituiscono `undefined`.

## Riferimento delle API

### run()
Esegue l'event loop fino a quando non viene fermato con `stop()`.

### subscribe()
Iscrive una funzione a un evento.

- **Parametri:**
  - `contract`: un identificatore di sorgente di eventi;
  - `callback`: la funzione da chiamare quando l'evento accade;
  - argomenti aggiuntivi: passati come argomenti extra alla callback.

La callback riceve almeno due argomenti più quelli aggiuntivi: il gestore dell'iscrizione (lo stesso oggetto restituito da `subscribe`) e l'elemento dell'evento (`undefined` per gli eventi senza dati). Può restituire un array della stessa lunghezza del numero di argomenti aggiuntivi per sostituirli alla chiamata successiva. Gli altri valori restituiti vengono ignorati.

- **Restituisce:** un oggetto `SubscriptionManager`:
  - `SubscriptionManager.cancel()` annulla l'iscrizione della callback all'evento.

::: warning
Ogni sorgente di eventi può avere **una sola** callback.
:::

### stop()
Ferma l'event loop.

### timer()
Crea una sorgente di eventi che scatta a intervalli fissi, una volta sola o indefinitamente.

- **Parametri:**
  - `mode`: `"oneshot"` o `"periodic"`;
  - `interval`: il timeout (per i timer `"oneshot"`) o il periodo (per i timer `"periodic"`), in ms.
- **Restituisce:** un oggetto `Contract` da usare come primo parametro di `subscribe()`.

### queue()
Crea una coda per lo scambio di messaggi.

- **Parametri:** `length`, il numero massimo di elementi nella coda.
- **Restituisce:** un oggetto `Queue`:
  - `Queue.send(message)`: inserisce `message` (di qualunque tipo) in fondo alla coda;
  - `input`: un `Contract` (sorgente di eventi) che estrae gli elementi dalla testa della coda.

## Pagine correlate

- [GPIO](/it/dev/js-gpio): gli interrupt dei pin sono contract dell'event loop.
- [GUI](/it/dev/js-gui): gli eventi delle view e la navigazione sono contract dell'event loop.
