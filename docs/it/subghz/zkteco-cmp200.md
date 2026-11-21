---
title: Telecomando per barriere ZKTeco CMP200
order: 210
author: gromovyna
original: [https://telegra.ph/ZKTeco-CMP200---Princeton-v-kitajskoj-obyortke-03-09, https://t.me/gromovyna/28, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md]
sources: [gromovyna, unleashed-src, unleashed-docs]
---
# ZKTeco CMP200 — un Princeton in confezione cinese

*Una breve recensione di @gromovyna del telecomando per le barriere ZKTeco, più come gestirlo su Unleashed.*

![Telecomando ZKTeco CMP200](/img/remote/a2cb668ab24d6625.png)

## Introduzione

Tempo fa, vicino a casa di gromovyna, ha aperto una clinica privata che ha installato una **barriera a sbarra ZKTeco**. Era curioso, ma il traffico era scarso e non c'erano molti motivi per approfondire, quindi la cosa è finita nella lista mentale delle cose da fare.

![Barriera ZKTeco (foto trovata in rete)](/img/remote/4cfaf6cbf4b21db6.png)

Poi, uscendo da una visita, ha visto il radiocomando appoggiato sul banco della reception di un piano superiore, l'ha fotografato, ne ha identificato il modello con Google Lens e l'ha messo nella lista "da comprare". Prima di acquistarlo ha chiesto a MMX (xMasterX) — e si è scoperto che il mistero era già stato risolto.

## Come i cinesi hanno impacchettato Princeton

È tutto piuttosto prosaico, e in **Unleashed** è supportato (grazie a MMX) da più di un anno. Sotto il cofano è un normale **Princeton** con codice tasto a 8 bit — e i codici dei tasti sono ben noti, **gli stessi per tutti i telecomandi**:

| Parametro | Valore |
|---|---|
| Frequenza | **430.50 MHz** |
| Modulazione | **AM650** |
| Tasto UP | `0x30` |
| Tasto STOP | `0x03` |
| Tasto DOWN | `0x0C` |

E la cosa migliore è che in Unleashed questi codici dei tasti sono **già mappati sui tasti freccia**, così un unico segnale salvato funziona rapidamente come l'intero telecomando.

::: tip Unleashed
ZKTeco compare nell'elenco dei sistemi supportati di Unleashed come
`ZKTeco 430.5MHz AM650 (24 bits, Static - Princeton based)` e ha una voce propria in `Add Manually`. 430.50 MHz è
nell'elenco di frequenze predefinito.
:::

## Come usarlo con il Flipper

Poiché il codice è statico, una copia è identica all'originale — entrambi continuano a funzionare in qualsiasi ordine.

### Opzione 1 — leggere il proprio telecomando

1. `Main Menu → Sub-GHz → Read`.
2. <kbd>←</kbd> `Config` → **Frequency** `430.50`, **Modulation** `AM650`. Back.
3. Premi un tasto del CMP200 vicino al Flipper. Compare un segnale `Princeton`.
4. <kbd>OK</kbd> → `Save`, dai un nome al file.
5. Aprilo in `Sub-GHz → Saved` → `Emulate`. <kbd>OK</kbd> invia il tasto acquisito; i tasti freccia inviano gli altri
   tasti (UP / STOP / DOWN).

### Opzione 2 — creare un telecomando

1. `Main Menu → Sub-GHz → Add Manually → ZKTeco`.
2. Scegli la banda `430.50 AM650` (per questa voce è elencata per prima).
3. Dai un nome e salva. Il Flipper crea una chiave Princeton a 24 bit con codice casuale, TE 357 µs, tasto `0x30`
   (UP).

Un telecomando creato così ha un codice proprio: la barriera reagirà solo dopo che è stato registrato nel ricevitore della barriera (segui il manuale della barriera). Per comportarsi come un telecomando esistente, leggilo invece (opzione 1).

::: warning
Solo per barriere di tua proprietà o che amministri.
:::

## È tutto?

Per ora sì. Come osserva gromovyna, questo supporto è arrivato in silenzio, quindi la maggior parte della comunità non l'ha mai notato; lui l'ha provato e ha condiviso i risultati.

## Risoluzione dei problemi

- **Non si riceve nulla** — assicurati che la frequenza sia 430.50 e non 433.92; verifica con il
  [Frequency Analyzer](/it/subghz/frequency-analyzer).
- **`Ignore Princeton` è su ON** nel `Config` di Read — i telecomandi basati su Princeton come questo vengono allora
  nascosti; disattivalo.
- **Le frecce non inviano nulla** — apri il segnale da `Saved → Emulate`; i tasti personalizzati funzionano nella
  schermata di trasmissione.

## Pagine correlate

- [Read](/it/subghz/read) · [Add Manually](/it/subghz/add-manually) · [Sistemi supportati](/it/subghz/supported-systems)
- [Codici rolling](/it/subghz/rolling-codes) — i tasti personalizzati spiegati
