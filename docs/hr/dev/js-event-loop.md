---
title: "JavaScript: petlja događaja"
sidebarTitle: "JS: event_loop"
order: 260
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_event_loop.md]
sources: [unleashed-docs]
---
# Modul petlje događaja (event_loop)

Petlja događaja (event loop) jezgra je programiranja vođenog događajima, a Flipperov JS podsustav izgrađen je oko nje. Naučite je **prije** korištenja naprednih modula (GPIO prekidi, GUI).

```js
let eventLoop = require("event_loop");
```

## Osnovna zamisao

U JavaScriptu stalno prosljeđujete funkciju koja će se pozvati kasnije, kada se nešto dogodi. To je povratni poziv (callback):

```js
setTimeout(function() { console.log("Hello, World!") }, 1000);
```

U pozadini većina JS okruženja pokreće red čekanja događaja i dugu petlju koja uzima događaje iz reda i poziva odgovarajuće povratne pozive. U pseudokôdu:

```js
while(loop_is_running()) {
    if(event_available_in_queue()) {
        let event = fetch_event_from_queue();
        let callback = get_callback_associated_with(event);
        if(callback)
            callback(get_extra_data_for(event));
    } else {
        // izbjegavanje trošenja procesorskog vremena
        sleep_until_any_event_becomes_available();
    }
}
```

Preglednici i Node.js skrivaju ovu petlju. **Flipper JS to ne čini**: sami stvarate izvore događaja, pretplaćujete povratne pozive na njih i pokrećete petlju.

## Primjer: jednokratni mjerač vremena

Flipperov ekvivalent primjera sa `setTimeout`:

```js
// uvoz modula
let eventLoop = require("event_loop");

// stvori izvor događaja koji će se aktivirati jednom, 1 sekundu nakon stvaranja
let timer = eventLoop.timer("oneshot", 1000);

// pretplati povratni poziv na izvor događaja
eventLoop.subscribe(timer, function(_subscription, _item, eventLoop) {
    print("Hello, World!");
    eventLoop.stop();
}, eventLoop); // obratite pozornost na ovaj dodatni argument, vratit ćemo se na njega kasnije

// pokreni petlju dok se ne zaustavi
eventLoop.run();

// prethodni redak završit će s izvođenjem tek kada se pozove `.stop()`, pa će se
// sljedeći redak izvršiti tek nakon ispisa "Hello, World!"
print("Stopped");
```

## Dodatni argumenti umjesto zatvorenja (closures)

mJS **ne podržava zatvorenja (closures)**: funkcija ne može čitati varijable iz dosega u kojem je definirana. Zbog toga `subscribe()` prima dodatne argumente nakon povratnog poziva i prosljeđuje ih u njega. U gornjem primjeru `eventLoop` je proslijeđen kako bi povratni poziv mogao pozvati `eventLoop.stop()`.

Povratni poziv također može **promijeniti** te vrijednosti za sljedeći poziv tako da vrati niz iste duljine:

```js
// ovaj će se mjerač vremena aktivirati svake sekunde
let timer = eventLoop.timer("periodic", 1000);
eventLoop.subscribe(timer, function(_subscription, _item, counter, eventLoop) {
    print("Counter is at:", counter);
    if(counter === 10)
        eventLoop.stop();
    // izmijeni dodatne argumente koji će nam biti proslijeđeni sljedeći put
    return [counter + 1, eventLoop];
}, 0, eventLoop);
```

Ovdje postoje dva dodatna argumenta, pa ih svaka povratna vrijednost osim niza duljine 2 ostavlja nepromijenjenima.

Prva dva argumenta svakog povratnog poziva uvijek su:

1. **upravitelj pretplate** (subscription manager), koji vam omogućuje da otkažete pretplatu pomoću `.cancel()`;
2. **stavka događaja** (event item), za događaje koji nose podatke. Događaji mjerača vremena ne nose podatke i daju `undefined`.

## Referenca API-ja

### run()
Pokreće petlju događaja dok se ne zaustavi pomoću `stop()`.

### subscribe()
Pretplaćuje funkciju na događaj.

- **Parametri:**
  - `contract`: identifikator izvora događaja;
  - `callback`: funkcija koja se poziva kada se događaj dogodi;
  - dodatni argumenti: prosljeđuju se kao dodatni argumenti povratnom pozivu.

Povratni poziv dobiva najmanje dva argumenta plus dodatne: upravitelj pretplate (isti objekt koji vraća `subscribe`) i stavku događaja (`undefined` za događaje bez podataka). Može vratiti niz iste duljine kao broj dodatnih argumenata kako bi ih zamijenio za sljedeći poziv. Ostale povratne vrijednosti se odbacuju.

- **Vraća:** objekt `SubscriptionManager`:
  - `SubscriptionManager.cancel()` odjavljuje povratni poziv s događaja.

::: warning
Svaki izvor događaja može imati **samo jedan** povratni poziv.
:::

### stop()
Zaustavlja petlju događaja.

### timer()
Stvara izvor događaja koji se aktivira u fiksnom intervalu, jednom ili zauvijek.

- **Parametri:**
  - `mode`: `"oneshot"` ili `"periodic"`;
  - `interval`: vremensko ograničenje (za `"oneshot"` mjerače) ili razdoblje (za `"periodic"` mjerače), u ms.
- **Vraća:** objekt `Contract` za prvi parametar funkcije `subscribe()`.

### queue()
Stvara red čekanja za prosljeđivanje poruka.

- **Parametri:** `length`, najveći broj stavki u redu.
- **Vraća:** objekt `Queue`:
  - `Queue.send(message)`: stavlja `message` (bilo kojeg tipa) na kraj reda;
  - `input`: `Contract` (izvor događaja) koji uzima stavke s početka reda.

## Povezano

- [GPIO](/hr/dev/js-gpio): prekidi pinova su ugovori (contracts) petlje događaja.
- [GUI](/hr/dev/js-gui): događaji prikaza i navigacija su ugovori petlje događaja.
