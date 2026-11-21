---
title: Registrazione dinamica Iron Logic
order: 110
author: gromovyna
original: [https://telegra.ph/Enrollment-ataka-na-dinamiku-ot-Iron-Logic-06-05, https://t.me/gromovyna/14, https://t.me/gromovyna/19, https://t.me/gromovyna/20, https://t.me/gromovyna/25]
sources: [gromovyna]
---
# La "dinamica" Iron Logic e il difetto logico nella registrazione

Un resoconto di ricerca su come i lettori Iron Logic implementano la "dinamica" anticlonazione (la modalità "ТП" / "first only") e su un difetto logico nel firmware 7.29 dei lettori, **corretto nella 7.30**. Lettura istruttiva per proprietari e ricercatori.

::: tip Ambito
Solo per le tue credenziali e per ricerca lecita. Il difetto descritto qui è corretto nel firmware attuale (7.30). Basato sull'articolo di @gromovyna (05/06/2025) e sui post del canale.
:::

## Come questi sistemi si difendono dalla clonazione

Un portachiavi MIFARE Classic statico può essere copiato da chiunque abbia le chiavi. I produttori rispondono in due modi:

1. **Filtri**, che rilevano le carte magic e gli emulatori (vedi [Lettori Iron Logic](/it/nfc/iron-logic), [Filtri Vizit](/it/nfc/vizit-filters)).
2. **Dinamica**: alcuni dati sulla carta vengono sincronizzati con la memoria del lettore a ogni passaggio (un "contatore"). Una copia fatta prima non corrisponde più e viene rifiutata. Varianti di questo approccio sono usate da Intratone, Hexact, Comelit, Noralsy e Urmet in Francia, Belgio e Lussemburgo (dove una desincronizzazione rilevata può disattivare tutti i tag di un utente), e sono state viste su alcuni citofoni Eltis in Russia.

## La modalità "ТП" ("Только первый" / "solo il primo")

Dall'annuncio del produttore citato sul canale (post 20): a ogni accesso il lettore scrive una **nuova password** sulla carta. All'accesso successivo il numero della carta più la password vengono confrontati con quanto il lettore ha memorizzato; se corrispondono, la carta è accettata e viene scritta una nuova password. Risultato: quante copie esistano, solo una carta continua a funzionare. All'inizio supportata solo da **CP-Z2 MF-I**, con il firmware 7.29 (annunciato come non completamente testato). Il produttore avverte che ora ogni passaggio **scrive sulla carta**, quindi dovresti verificare la resistenza alla scrittura delle tue carte prima di passare a questa modalità.

Perché è un grattacapo: il mercato è pieno di tag MIFARE Classic contraffatti cinesi, che potrebbero non sopravvivere al numero di riscritture, e una scrittura interrotta (posizione sbagliata, perdita di alimentazione) può lasciare la carta desincronizzata. È anche per questo che emulare o clonare su sistemi di questo tipo può **rovinare il tuo originale**.

## Firmware 7.29: nessun filtro, dinamica come modalità principale

Il firmware 7.29 (test aperto) ha disattivato tutti i filtri e ha reso la dinamica la modalità principale. Il team di ricerca ha trovato vulnerabilità in questa release; un bug logico è stato corretto nella **7.30**, dopodiché l'autore ne ha pubblicato la descrizione.

## Registrazione: come una carta diventa dinamica

Per spostare migliaia di carte statiche esistenti alla dinamica senza costringere gli utenti a farsele riemettere, Iron Logic ha introdotto la **registrazione** (enrollment). I metadati vengono scritti nel **settore 14** della carta. Logica del lettore semplificata:

1. Il lettore controlla i metadati della carta.
2. Se la carta **non è ancora in modalità dinamica**, il lettore la registra e memorizza un valore di contatore. **Non** verifica se quell'ID di carta sia già presente nella sua memoria.
3. Se la carta è già registrata, si applicano controlli stretti sul contatore.

Le coppie ID/contatore sono conservate nella memoria non volatile del lettore.

## Il difetto (corretto nella 7.30)

La debolezza deriva dal punto 2: un lettore al quale viene presentata una carta che sembra ancora "statica" la registra semplicemente di nuovo. L'unico ostacolo per un attaccante è avere un dump della carta **precedente** alla sua prima registrazione. Le carte abbastanza vecchie da non avere metadati non vengono accettate dal lettore, quindi la riconversione dei dati dinamici a uno stato "statico" è stata esplorata solo in superficie.

L'autore descrive due modi pratici per presentare ogni volta una carta "statica":

- **Tag GDM (GDMIC)**, una variante di USCUID con modalità shadow: i dati vengono scritti in una memoria temporanea e tornano alla memoria permanente quando il campo del lettore si spegne, così l'originale (già registrato) e un numero illimitato di copie possono convivere. L'autore osserva che è semplice ma fuori portata per la maggior parte dei fabbri, e può essere contrastato dai filtri precedenti o da una gestione più intelligente del campo RF.
- **Flipper Zero, manuale**: leggi la carta statica, emulala, usa `Return to Initial State`, ripeti. Va bene per i test, impraticabile ogni giorno.

Il team ha altri attacchi teorici e pratici, e ha condiviso alcune idee con iKey.

## Cosa dovrebbero fare i proprietari

- Aggiornare i lettori alla **7.30 o successiva**.
- Testare la resistenza alla scrittura delle proprie carte prima di abilitare la dinamica.
- Preferire, dove possibile, le famiglie di carte moderne (MIFARE Plus, DESFire e simili); MIFARE Classic è considerata obsoleta dal suo stesso produttore.

## Pagine correlate

- [Lettori Iron Logic](/it/nfc/iron-logic) · [Magic card](/it/nfc/magic-cards) · [Filtri Vizit](/it/nfc/vizit-filters)
