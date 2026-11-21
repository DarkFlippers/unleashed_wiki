---
title: T5577 e Hitag Micro (di @gromovyna)
order: 60
author: gromovyna
original: [https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577]
sources: [gromovyna, unleashed-src]
---
# Scrittura su Hitag Micro, UX di scrittura e wipe del T5577

Basato sull'articolo di @gromovyna *"Anteprima delle funzioni LF (RFID) che ho preparato per Unleashed"* (giugno
2026), aggiornato con l'aspetto che queste funzioni hanno nel firmware attuale.

![](/img/remote/2e30c69f7eded901.png)

## Introduzione

Dopo una lunga pausa, @gromovyna è tornato alla ricerca e si è occupato delle vergini **H5.5** vendute da *iKey*. Dal
Discord di Iceman era già noto che l'H5.5 è lo stesso clone cinese di **Hitag Micro**, sul quale iKey ha impostato una
password propria. La situazione dei nomi:

| Nome | Di che si tratta |
|---|---|
| **8265 / H5** | il chip con la password predefinita |
| **H5.5** | lo stesso chip con la password di **iKey** |
| **8210** | lo stesso chip con la password del cloner cinese **FURUI** |

Ha recuperato la password iKey (al secondo giorno di tentativi), l'ha condivisa con la comunità e ha
[aggiornato le note di Proxmark3 sulle magic card](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md#id8265).
Poi ha implementato le funzioni per il Flipper — come pull request su **Unleashed**, con l'auspicio di portarle anche
su OFW una volta che questo sarà di nuovo in sviluppo attivo.

Le password che il firmware usa per le tre varianti:

| Variante | Password |
|---|---|
| 8265 / H5 | `00000000` |
| 8210 | `9AC4999C` |
| H5.5 | `496B0E59` |

## Supporto Hitag Micro

Il Flipper può ora **scrivere** i cloni Hitag Micro — **8265/H5**, **H5.5** e **8210** — come chiavi EM4100 (il chip
viene configurato per inviare da sé il frame EM4100, secondo il principio "transponder talks first").

Limiti dell'architettura attuale:
- l'hardware LF del Flipper durante la scrittura è in sola **trasmissione**, quindi il successo può essere verificato
  solo **rileggendo il tag**;
- molto tempo è stato dedicato alla calibrazione delle costanti, ma la scrittura di questi chip richiede ancora un
  **buon posizionamento**.

### Perché la scrittura è diventata più lenta

L'aggiunta del supporto ha peggiorato l'esperienza d'uso, perché la logica di scrittura è ora un ciclo che prova, uno
dopo l'altro:

- **T5577**
- **EM4305**
- **Hitag Micro** — e qui tre varianti, una per ogni password di fabbrica conosciuta; queste operazioni sono già di
  per sé più lente

Per Hitag Micro il Flipper prova a turno la password di ogni variante nota, così da non dover interrogare l'utente —
chiederglielo avrebbe tradito una delle idee portanti del Flipper Zero, la semplicità. Il prezzo è la velocità di
scrittura. Una password errata viene semplicemente rifiutata dal chip e lascia il tag intatto; la variante presente è
quella la cui rilettura risulta corretta.

Per l'utente il risultato era pessimo — come se non stesse succedendo nulla — e non era chiaro con quale protocollo il
tag fosse stato scritto. Da qui la funzione successiva.

## UX: con cosa stiamo scrivendo / cosa abbiamo scritto?

Durante una scrittura lo schermo mostra ora **quale chip viene tentato**:

![Scrittura in corso](/img/remote/34b72cbd8417d74e.png)

Tecnicamente non si tratta di un protocollo ma del nome commerciale della variante di vergine — ma il senso è chiaro.
Dopo la scrittura il risultato viene mostrato con lo stesso livello di dettaglio:

![Risultato della scrittura](/img/remote/3ca59457a78dad5b.png)

::: tip Nel firmware attuale
- I chip da provare sono configurabili: `125 kHz RFID → Settings → Write Chips` — T5577, EM4305, 8265, 8210, H5.5
  (tutti su ON) e **8268** (ID8268 / chip magico Hitag S, su OFF per impostazione predefinita). Disattiva ciò che non
  usi per velocizzare le scritture.
- Il target 8268 scrive solo EM4100 a RF/64 e va abilitato a mano, perché su un Hitag S autentico sovrascriverebbe
  dati utente.
- Il formato della schermata di scrittura è `[Protocol]`, nome del file, `(chip)`; **Success!** mostra il chip che ha
  accettato i dati. Dettagli: [Scrittura su vergini](/it/rfid/write).
:::

## Riportare un T5577 allo stato di fabbrica

Una funzione che a @gromovyna mancava da tempo sul Flipper: riportare un T5577 allo stato vergine. Un tentativo
precedente di aggiungerla a Unleashed era stato bloccato; più tardi funzioni come *clear T5577 password* sono state
integrate con gli stessi problemi architetturali, quindi una soluzione corretta avrebbe richiesto un intervento
globale.

Comportamento (allineato a Proxmark3):

- prima di iniziare viene avvisato che **tutti i dati saranno cancellati** e che il tag **non sarà più leggibile con
  Read** finché non gli si scrivono nuovi dati;
- il wipe **non rimuove la password** — se il tag è protetto, cancella prima la password con la funzione dedicata;
- viene mostrata una barra di avanzamento. La maggior parte del tempo non va nel wipe stesso ma nella sua
  **verifica**: a causa dell'API LF, il Flipper controlla che il tag sia pulito provando a leggerlo e aspettandosi che
  la lettura fallisca;
- alla fine compare un messaggio di successo o di errore.

![Avviso del wipe](/img/remote/f5ed0aa91bfcae98.png)

![Wipe in corso](/img/remote/153b85d1fede96d9.png)

![Verifica](/img/remote/0f2f4e240a35940d.png)

![Successo](/img/remote/312494f343dd8b21.png)

::: tip Unleashed — dove si trova ora
Nell'articolo il wipe si trovava in `125 kHz RFID → Extra Actions`. Nel firmware attuale è stato spostato (insieme a
Clear Password) nell'app **T5577** integrata: `Apps → RFID → T5577 → Wipe Tag`. L'avviso recita *Wipe T5577 — Erases
all data. The tag stops working as a key. Hold still while running*; il risultato è **Wiped!** o **Not wiped** (per
esempio *No answer. Protected? Try Clear Password*). Il wipe scrive blocchi di dati azzerati e una configurazione
predefinita, così l'app T5577 può continuare a leggere il chip. Vedi [App T5577](/it/rfid/t5577-app).
:::

## "Questo l'hai fatto a vibe-coding!"

Nelle parole dell'autore, è stato un esperimento per capire se con un LLM si possa scrivere codice di qualità per
sistemi di questo tipo. Il processo è stato meticoloso: datasheet, il codice del firmware Unleashed per capirne
l'architettura, il codice di Proxmark3. Ogni passo è stato validato, provato su hardware reale e messo a punto. Le
funzioni sono quindi *scritte da Claude Code*, ma *create da @gromovyna*.

## Pull request

- [[RFID]: Support of Hitag Micro chips (8265/8210/H5.5)](https://github.com/DarkFlippers/unleashed-firmware/pull/1002)
- [[RFID]: Wipe T5577 (reset to blank, with read-back verification)](https://github.com/DarkFlippers/unleashed-firmware/pull/1003)

Altri articoli e ricerche: [@gromovyna](https://t.me/gromovyna).

## Pagine correlate

- [Scrittura su vergini](/it/rfid/write) · [App T5577](/it/rfid/t5577-app) · [Protocolli](/it/rfid/protocols)
