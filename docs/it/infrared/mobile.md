---
title: Telecomandi nell'app mobile
order: 30
original: [https://docs.flipper.net/zero/infrared/remotes-mobile, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# Telecomandi IR nella Flipper Mobile App

La Flipper Mobile App (iOS / Android) ha una **Remotes Library**: un database online di telecomandi IR. Scegli il tipo
di apparecchio e la marca, l'app trova il telecomando giusto provando qualche segnale, lo scarica sul Flipper e poi
mostra un layout di telecomando vero e proprio sullo schermo del telefono. La trasmissione effettiva la fa il Flipper.

Rispetto ai [Telecomandi universali](/it/infrared/universal-remotes), che inviano tutta la libreria a ogni pressione,
un telecomando preso dalla Remotes Library viene trovato **una volta** e poi funziona istantaneamente. Ha anche più
pulsanti e copre più tipi di apparecchi.

## Cosa puoi trovare

La libreria comprende telecomandi, tra gli altri, per: TV, proiettori, TV box, ventilatori, purificatori d'aria,
lettori DVD, fotocamere e amplificatori AV. Il database è open source:
[flipperdevices/IRDB](https://github.com/flipperdevices/IRDB); puoi contribuire con il tuo telecomando seguendo la sua
[guida ai contributi](https://github.com/flipperdevices/IRDB/blob/dev/docs/adding_remote.md).

::: tip Unleashed
L'app mobile funziona con Unleashed esattamente come con il firmware di serie: comunica con l'app Infrared tramite RPC.
Mentre il telefono la comanda, lo schermo del Flipper mostra **"Infrared – RPC mode"**. I telecomandi scaricati
dall'app sono normali file `.ir` in `/ext/infrared/` e possono essere usati, modificati e rinominati sul Flipper come
qualsiasi telecomando appreso. Di più sull'app stessa: [Flipper Mobile App](/it/mobile/mobile-app).
:::

## Trovare il telecomando del tuo apparecchio

1. Collega il Flipper all'app via Bluetooth.
2. Nell'app vai in `Tools → Remotes Library`.
3. Seleziona il **tipo di apparecchio**, poi la **marca**.
4. Molte marche hanno diversi telecomandi, quindi l'app prova i segnali uno a uno: punta il Flipper verso
   l'apparecchio, tocca il pulsante per inviare il segnale e indica se l'apparecchio ha reagito.
5. Quando il telecomando giusto è stato trovato, l'app mostra il suo layout. Puoi usarlo subito.
6. Tocca **Save** (in alto a destra) e dai un nome al telecomando. Viene scritto sul Flipper.
7. *(Facoltativo)* Tocca **⋯ → Add to Favorites** per averlo nella scheda Archive e accedervi rapidamente.

![Remotes Library](/img/remote/9c74a923d5c1aae5.jpg)

## Usare un telecomando salvato

**Dal telefono.** Nell'app apri `Archive → Infrared` (oppure Favorites), seleziona il telecomando, punta il Flipper
verso l'apparecchio e tocca i pulsanti sul telefono. L'app dice al Flipper quale segnale inviare.

![Layout del telecomando nell'app](/img/remote/7387cb59433e202d.jpg)

**Dal solo Flipper.** Vai in `Main Menu → Infrared → Saved Remotes`, apri il telecomando, scegli un pulsante con
<kbd>↑</kbd> / <kbd>↓</kbd> e premi <kbd>OK</kbd>. Vedi
[Apprendere e inviare segnali](/it/infrared/read#send-a-saved-button).

## Risoluzione dei problemi

| Problema | Cosa provare |
|---|---|
| L'app non riesce a inviare / non accade nulla | Assicurati che il Flipper sia collegato e non occupato in un'altra app. Chiudi qualsiasi app in esecuzione sul Flipper e riprova. |
| Nessun telecomando trovato per la tua marca | Apprendi il telecomando originale sul Flipper ([come](/it/infrared/read)) oppure prova i [Telecomandi universali](/it/infrared/universal-remotes). |
| L'apparecchio reagisce solo da molto vicino | Usa un [modulo IR esterno](/it/infrared/external-ir); l'app usa il trasmettitore selezionato nelle GPIO Settings di Infrared. |

## Pagine correlate

- [Flipper Mobile App](/it/mobile/mobile-app)
- [Telecomandi universali](/it/infrared/universal-remotes)
- [Formato dei file IR](/it/infrared/file-format)
