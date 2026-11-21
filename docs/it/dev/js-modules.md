---
title: "JavaScript: usare i moduli"
sidebarTitle: "JS: moduli"
order: 230
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_using_js_modules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules]
sources: [unleashed-docs, unleashed-src]
---
# Usare i moduli JavaScript

Le [funzioni integrate](/it/dev/js-builtin) sono volutamente poche. Le funzionalità hardware e di sistema risiedono nei **moduli JS**, per esempio:

- `serial` invia e riceve dati su UART;
- `badusb` emula una tastiera USB;
- `math` fornisce funzioni matematiche.

I moduli sono scritti in C, quindi sono veloci. Vengono distribuiti con il firmware e memorizzati sulla scheda SD in forma compilata come plugin **FAL (Flipper Application File)**. Sorgenti dei moduli: [`applications/system/js_app/modules`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules). L'elenco dei moduli si trova in [Panoramica su JavaScript](/it/dev/js-about).

## Caricare un modulo

**Devi** caricare un modulo con `require()` prima di chiamarne i metodi. Questo carica il modulo in RAM.

- Carica solo ciò che usi, per risparmiare RAM. (`math`, per esempio, occupa circa 21 KB di RAM una volta caricato.)
- Tutti i moduli caricati vengono scaricati automaticamente al termine dello script.
- Un modulo può essere caricato una sola volta per script; un secondo `require()` dello stesso nome fallisce con `"... module is already installed"`.
- Alcuni moduli dipendono da altri e devono essere caricati dopo di essi: `gpio` e `gui` richiedono `event_loop`, e ogni view `gui/*` richiede `gui`.

Passa il nome del modulo tra apici:

```js
let notify = require("notification");
```

Poi chiama i suoi metodi attraverso la variabile:

```js
let notify = require("notification");

notify.success();
print("success notification");
```

Il firmware accetta anche il nome in stile SDK `require("@flipperdevices/fz-sdk/notification")`: il prefisso viene rimosso automaticamente. I nomi con una barra, come `gui/submenu`, corrispondono al file di plugin `js_gui__submenu`.

## Passi successivi

- Sfoglia le pagine dei moduli di questa sezione, a partire da [Event loop](/it/dev/js-event-loop) e [GUI](/it/dev/js-gui).
- Studia gli script di esempio in `/ext/apps/Scripts/js_examples/`.
