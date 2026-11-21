---
title: Lettori Iron Logic
order: 100
author: gromovyna
original: [https://telegra.ph/Schityvateli-Iron-Logic-i-chto-s-nimi-delat-03-13, https://t.me/gromovyna/14]
sources: [gromovyna]
---
# Lettori Iron Logic (CP-Z-2 "3 strisce" / "4 strisce")

I lettori Iron Logic (i cosiddetti "tappi") sono diffusi nei citofoni e nei controlli accessi di tutta l'ex URSS. Questa pagina spiega come proteggono i portachiavi MIFARE Classic, come capire con quale variante hai a che fare e cosa dice la ricerca pubblicata sulla lettura, l'emulazione e la copia del **tuo** portachiavi con un Flipper Zero.

::: tip Ambito
Solo per le tue credenziali e per ricerca lecita. Basato sull'articolo di @gromovyna (13/03/2025).
:::

## Come questi sistemi si difendono dalla clonazione

Iron Logic parte da MIFARE Classic, economico, e vi sovrappone delle difese:

- **Diversificazione delle chiavi.** Le chiavi dei settori sono derivate per singola carta dall'UID della carta e dalla "mappa dell'oggetto" del lettore (una costante caricata nel lettore). Per questo un attacco a dizionario di solito non trova nulla su un sistema configurato.
- **Filtri** contro le magic card e gli emulatori (per esempio "IL-30 only", OTP1, OTP2), a seconda del firmware del lettore.
- **Modalità dinamica** ("only first", vedi [Registrazione dinamica Iron Logic](/it/nfc/iron-logic-enrollment)), in cui i dati sulla carta cambiano a ogni passaggio.

Capire questo ti spiega perché il semplice "leggi, poi scrivi su una carta vuota" spesso fallisce e cosa fare invece.

## Che lettore hai

| Variante | Note |
|---|---|
| CP-Z-2 ("3 strisce") | Più vecchio, fuori produzione, ancora comune. |
| CP-Z-2 (mod. MF-I) ("4 strisce") | Modello attuale, supportato dalle release del firmware. L'articolo è scritto per questo, ma funziona anche per il precedente. |

L'identificazione dal contenitore non è affidabile al 100 % (un installatore può mettere elettronica nuova in un vecchio contenitore) ma in pratica funziona quasi sempre. I lettori sono usati anche all'interno di pannelli di altri produttori (Eltis, Metakom e altri); non fa differenza, perché l'obiettivo è recuperare tutti i settori della carta MIFARE Classic.

## Verifica se sei sfortunato

### Carta SmartMX (IL-30)

Se è in uso un lettore a "4 strisce" e il Flipper mostra la schermata del tipo "carta non supportata", controlla la carta: **SAK = 28** e **ATQA = 0004** indicano una carta **SmartMX**, e il lettore potrebbe avere attivo il filtro **"IL-30 only"**. Puoi comunque provare i passi qui sotto nel caso in cui il filtro sia disattivato e il lettore sia in modalità mista (chiavi SmartMX nuove e MIFARE Classic vecchie). Se non funziona nulla e ti serve una copia, l'autore suggerisce un'officina attrezzata con dispositivi iKey, che scrivono i dati su chip originali (iMF+) sfruttando un difetto logico di Iron Logic.

### Citofoni dinamici ("Sokol" di Petrunya)

I citofoni Sokol (di solito costruiti su un pannello Eltis 5000) usano lettori Iron Logic **con dinamica**: i dati nella chiave cambiano a ogni passaggio e le vecchie copie diventano non valide. Emulare o scrivere una carta vuota può **corrompere il tuo originale**. Dettagli: [registrazione dinamica](/it/nfc/iron-logic-enrollment).

## Passo 1: fare il dump di tutti i settori

Ti servono tutti i settori e tutte le chiavi della carta. Non aspettare che l'attacco a dizionario finisca: con le chiavi diversificate non ha senso.

1. Leggi la carta (`Main Menu → NFC → Read`). Vedi [Leggere le carte](/it/nfc/read).
2. Se il risultato è **16/16 settori letti ma 0/32 chiavi trovate**, la carta ha una backdoor. Vai direttamente alla [guida a Nested / backdoor Fudan](/it/nfc/nested-fudan).
3. Se non hai alcuna chiave, raccogli i nonce dal lettore (vedi sotto), poi recupera le chiavi con [MFKey](/it/nfc/mfkey).
4. Recupera le chiavi restanti con Nested ([guida](/it/nfc/nested-fudan)).

### Raccogliere i nonce dal lettore

Fino a poco tempo fa si credeva che il Flipper non potesse lavorare affatto con i lettori a 4 strisce. Grazie a @blowtreez si è scoperto che è possibile, anche se richiede precisione e pratica. Il Flipper raccoglie i nonce da **tutte** le versioni dei lettori, indipendentemente dal numero di strisce o dal firmware.

- Trova la posizione in cui il Flipper interagisce con il lettore. Empiricamente: la scritta **"FLI"** sul contenitore del Flipper deve stare **sopra il lettore**.
- Tienilo il più vicino possibile, a contatto con il lettore.
- A volte (come nel caso dell'autore) non funziona con la custodia; togli il Flipper dalla custodia e prova nudo.

Poi segui l'articolo ufficiale [Recovering MIFARE Classic keys](https://docs.flipper.net/nfc/mfkey32).

::: tip Note dell'autore
- Nella maggior parte dei casi bastano le chiavi e i settori **0, 1 e 14** letti completamente, ma alcuni sistemi tengono i dati in settori personalizzati (per esempio l'8). Fai sempre una copia completa e decifra tutti i settori.
- L'autore accenna di avere una API privata che calcola la chiave del settore 14 a partire dall'UID della carta, per poter proseguire con Nested (offerta nella chat della comunità Unleashed).
:::

## Passo 2: emulazione

- Funziona su tutti i lettori a "3 strisce" (con rare eccezioni) e su quelli a "4 strisce" a meno che non abbiano il firmware più recente (**7.28**, come indicato nel post del canale).
- Sulle versioni più vecchie come la **7.20** (il firmware di fabbrica attuale) l'emulazione funziona, ma devi trovare la posizione esatta del Flipper rispetto al lettore, come per la raccolta dei nonce.
- I filtri OTP1 e OTP2 **non** influiscono sull'emulazione.
- Chameleon Ultra si comporta nello stesso modo.
- Con il filtro "IL-30 only" attivo, l'emulazione non funziona.

## Passo 3: copiare su una carta vuota

La scelta universale è una carta vuota **CUID static nonce (alias MF-3.2)** (vedi [Magic card](/it/nfc/magic-cards)). Al momento della stesura funzionava su tutte le versioni del firmware e con tutte le impostazioni dei filtri per entrambi i tipi di lettore. Per le "3 strisce" va bene un **CUID** normale, e qualcuno è riuscito anche con uno **Zero**.

L'autore consiglia di non andare a caccia della carta vuota minima funzionante, a meno che gli esperimenti ti divertano: la differenza di prezzo tra un CUID static nonce e un CUID normale è piccola, ed eviti il "fattore casinò". Ha anche trovato diversi chip CUID normali (revisioni più recenti) che funzionano su tutte le versioni del firmware a 4 strisce, oltre a segnalazioni più vecchie della comunità di successi con carte vuote CUID normali, che però non è riuscito a riprodurre in modo affidabile fino a poco tempo fa.

## Non trattato

L'autore elenca gli argomenti fuori ambito o ancora in fase di ricerca: come sono implementati i filtri OTP1/OTP2, la KDF per la chiave A del settore 14 a partire dall'UID e il ruolo della mappa dell'oggetto nella cifratura dei settori.

## Pagine correlate

- [Nested e backdoor Fudan](/it/nfc/nested-fudan) · [MFKey](/it/nfc/mfkey) · [Magic card](/it/nfc/magic-cards)
- [Registrazione dinamica Iron Logic](/it/nfc/iron-logic-enrollment) · [Filtri Vizit](/it/nfc/vizit-filters)
