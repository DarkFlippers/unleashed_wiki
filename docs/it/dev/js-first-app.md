---
title: "JavaScript: la tua prima app"
sidebarTitle: "JS: prima app"
order: 210
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_your_first_js_app.md]
sources: [unleashed-docs]
---
# La tua prima app JavaScript

In questa guida scriverai un piccolo script che stampa numeri con un ritardo, e poi lo eseguirai su Flipper Zero in due modi: dal menu del dispositivo e da un PC tramite la CLI. Ti servono un Flipper Zero, un PC e un cavo USB.

## Passo 1. Creare lo script

Crea un file di testo chiamato `first_app.js` con questo contenuto:

```js
print("start");
delay(1000);
print("1");
delay(500);
print("2");
delay(500);
print("3");
delay(500);
print("end");
```

Che cosa fa:

- stampa **start** e attende 1 secondo;
- stampa **1**, **2** e **3**, con una pausa di 0,5 secondi dopo ciascuno;
- stampa **end**.

`print()` stampa del testo, e `delay()` mette in pausa per il numero di millisecondi indicato (1000 ms = 1 s). Sono entrambe **funzioni integrate**, quindi non è necessario caricare alcun modulo. Vedi [Funzioni integrate](/it/dev/js-builtin) per l'elenco completo.

## Passo 2. Copiare il file sul Flipper Zero

1. Collega il Flipper Zero al PC via USB.
2. Apri [qFlipper](/it/mobile/qflipper).
3. Vai alla scheda **File manager** e apri `SD Card/apps/Scripts/`.
4. Trascina `first_app.js` nella finestra di qFlipper.

Puoi anche copiare il file con un lettore di schede. Deve finire in `/ext/apps/Scripts/`.

## Passo 3. Eseguire lo script

### Dal menu del Flipper

1. Apri `Main Menu → Apps → Scripts`. L'elenco mostra gli script presenti in `SD Card/apps/Scripts/`.
2. Seleziona `first_app`.
3. Premi <kbd>OK</kbd> per eseguirlo.

![Script in esecuzione su Flipper Zero](/img/dev/js_first_app_on_fz.jpg)

Le righe compaiono sullo schermo del Flipper con i ritardi definiti nello script.

### Dalla CLI

Eseguirlo dalla [CLI](/it/dev/cli) è comodo per il debug: modifichi e provi lo script senza toccare il dispositivo.

1. Collega il Flipper Zero via USB.
2. Apri la CLI (per esempio con la scheda CLI di qFlipper, un terminale seriale o `./fbt cli`).
3. Esegui `js` seguito dal percorso dello script:

```sh
js /ext/apps/Scripts/first_app.js
```

![Output dello script nella CLI](/img/dev/js_first_app_on_cli.jpg)

Quando uno script viene avviato dalla CLI, tutto ciò che viene stampato con `print()` va alla CLI, non allo schermo del Flipper.

## Risoluzione dei problemi

- **Lo script non è nell'elenco.** Verifica che il file abbia l'estensione `.js` e si trovi in `/ext/apps/Scripts/` (le sottocartelle vanno bene; entra al loro interno).
- **Lo script si interrompe con un errore.** mJS supporta solo un sottoinsieme di JavaScript (nessuna closure, nessuna arrow function, nessuna classe). Eseguilo dalla CLI per vedere il messaggio di errore e la riga.

**Prossimo passo:** [Sviluppare app con l'SDK JavaScript](/it/dev/js-sdk)
