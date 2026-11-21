---
title: Filtri dei lettori Vizit
order: 120
author: gromovyna
original: [https://telegra.ph/Filtry-schityvatelej-Vizit-dlya-zashchity-ot-klonov-metok-Vizit-RF-31-05-15]
sources: [gromovyna]
---
# I filtri dei lettori Vizit contro i cloni delle Vizit RF 3.1

Come i lettori Vizit cercano di rilevare le chiavi **Vizit RF 3.1** (MIFARE Ultralight EV1) clonate, e cosa cerca ciascun filtro. Basato sull'articolo di @gromovyna (15/05/2025).

::: tip Ambito
Solo per le tue credenziali e per ricerca lecita.
:::

## Contesto

Vizit è un produttore russo di controlli accessi (dal 1996, secondo quanto dichiara). I vecchi lettori usavano chiavi **Dallas**, poi **EM Marine**; quelli più recenti usano le **Vizit RF 3.1** (= MIFARE Ultralight, UID che inizia con `34`); le chiavi più nuove, **Vizit RF 7.1**, sono **MIFARE Ultralight C** (autenticazione 3DES). Il firmware minimo per le RF 7.1 è indicato sul sito del produttore. L'autore osserva che la derivazione delle chiavi per le 7.1 è nota a iKey e che i ricercatori occidentali stanno lavorando al recupero delle chiavi 3DES (nessun dettaglio divulgato).

## Come questi sistemi si difendono dalla clonazione

A differenza di Iron Logic, i filtri Vizit che l'autore conosce sono **software**, non hardware, quindi sono visibili nel traffico catturato con un Proxmark3. Sono stati trovati nel lettore **RD-5F, firmware 212**; anche altri pannelli li hanno, ma non si sa in quale versione sia comparso ciascun filtro.

### Filtro 1: backdoor Gen1

Il lettore invia il noto comando di backdoor `40(7)` e attende una risposta. Un tag originale non risponde. Prende di mira le carte vuote più antiche (UL-0116 / UL-0416), che venivano scritte attraverso la backdoor, UID compreso.

### Filtro 2: EV1 VERSION

Il lettore invia `EV1 VERSION` e confronta il **secondo byte del risultato** con il **primo byte dell'UID del tag**. I tag Vizit RF 3.1 dichiarano come produttore **Micron Russia** (byte `34`) e i loro UID iniziano con `34`. Questo sconfigge le varianti USCUID-UL (le cinesi "UL-21", le "UL-2" del mercato russo). La risposta del mercato sono stati i tag "ULtra", USCUID-UL con la stessa version delle 3.1 (che si può configurare a mano con due comandi Proxmark3 se la configurazione è aperta). Dopo il 2022 in Ucraina, gli apparati compatibili con Vizit (lettori Grazhda, pannelli Mriya) usano chip NXP originali con la version corretta, quindi le copie ULtra potrebbero non funzionare là.

### Filtro 3: OTP

La pagina 3 di un Ultralight è OTP: zeri di fabbrica, i bit possono essere portati solo a 1, mai indietro (vedi la sezione 8.5.4 del datasheet MF0ULX1). Nei normali tag USCUID-UL è liberamente riscrivibile. Il lettore prova a scrivere zeri in questa pagina e la rilegge; se è cambiata, il tag è una copia, il lettore ripristina il valore "originale" e lo rifiuta. Un tag originale risponde **NACK** e smette di rispondere fino alla SELECT successiva, che è la macchina a stati corretta.

Altre implementazioni avevano lo stesso difetto: il Flipper Zero è corretto dopo il refactor dell'NFC, e l'emulazione di Proxmark3 lo aveva finché l'autore non l'ha segnalato ([issue 2790](https://github.com/RfidResearchGroup/proxmark3/issues/2790)) e il problema è stato risolto.

La risposta di iKey è stata la carta vuota **UL-5**, scrivibile una sola volta; dopo che la pagina 0 è stata modificata si blocca e si comporta come un originale. Arriva dalla Cina con una version diversa da Micron Russia. L'autore sospetta che sia un USCUID-UL configurato in modo specifico. Lo stesso filtro può essere superato anche su un USCUID-UL normale (per esempio in configurazione ULtra) modificando correttamente il blocco di configurazione, se è aperto.

## Conclusione per i proprietari

Le Vizit RF 7.1 (Ultralight C) soddisfano gli standard di sicurezza moderni e mettono fine a questo gioco del gatto col topo.

## Pagine correlate

- [Lettori Iron Logic](/it/nfc/iron-logic) · [Magic card](/it/nfc/magic-cards) · [Leggere le carte](/it/nfc/read)
