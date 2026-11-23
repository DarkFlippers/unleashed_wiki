---
title: Frequency Analyzer
order: 20
original: [https://t.me/how2flipper_rus/3, https://t.me/how2flipper_rus/4, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/frequency_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [how2flipper, unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Frequency Analyzer

Il Frequency Analyzer ti dice **su quale frequenza trasmette un telecomando**. Scansiona le frequenze dell'elenco
Sub-GHz, misura l'intensità del segnale (RSSI) e mostra la più forte. Usalo prima di **Read** o **Read RAW** quando
non conosci la frequenza di un telecomando.

::: tip Unleashed
Unleashed include un analizzatore rielaborato (originariamente di ClusterM) con una cronologia di 4 voci, un trigger
regolabile, feedback selezionabile (suono / vibrazione / muto) e un **salto diretto a Read**: <kbd>OK</kbd> breve
memorizza la frequenza per Read / Read RAW, <kbd>OK</kbd> lungo la memorizza e apre subito Read.
:::

## La regola d'oro

L'analizzatore è pensato per funzionare **solo a pochi centimetri dall'antenna del Flipper, sulla radio interna**.
L'antenna si trova sul lato sinistro, accanto alla finestrella IR nera. Le sue impostazioni esistono per filtrare il
rumore, non per catturare segnali da lontano. Con un trigger molto basso l'analizzatore segnala soltanto interferenze
casuali e il rumore prodotto dal Flipper stesso invece del tuo telecomando. Per *ricevere* davvero i segnali usa
[Read](/it/subghz/read) e [Read RAW](/it/subghz/read-raw).

::: warning Moduli esterni
Nella versione estesa di Unleashed (`E`) è possibile usare il Frequency Analyzer con i moduli esterni avviando l'app
da `Apps → Sub-GHz` (invece che dal menu principale Sub-GHz). Tieni presente che con un modulo esterno aumenta molto
la sensibilità a rumore e interferenze, che possono essere facilmente scambiati per un segnale utile.
:::

## La schermata

![Frequency Analyzer con 433.920 MHz, le voci di cronologia e la barra RSSI](/screens/subghz/frequency_analyzer.png)

| Elemento | Significato |
|---|---|
| Icona in alto a destra | Feedback quando un segnale viene catturato: altoparlante = vibrazione + suono, altoparlante piccolo = solo vibrazione, barrato = muto |
| Numero grande al centro | Frequenza corrente (principale). Mentre si riceve un segnale sopra il trigger viene mostrata **in negativo, in un riquadro nero** |
| Quattro voci sotto | Cronologia: frequenza arrotondata e quante volte è stata catturata (`x3`). Utile con telecomandi deboli o che derivano |
| Barra `RSSI` in basso | Intensità del segnale in tempo reale con il segno del trigger |
| `T-` / `+T` | Tasti del livello di trigger |

## Tasti

| Tasto | Azione |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | Spostano il trigger (da −97 dBm a −60 dBm, passo 1 dBm). Sinistra = più sensibile, destra = meno sensibile |
| <kbd>↑</kbd> | Cicla la modalità di feedback: vibrazione + suono → muto → vibrazione → … |
| <kbd>↓</kbd> | Seleziona una voce della cronologia (compare una cornice attorno) |
| <kbd>OK</kbd> breve | Salva la frequenza selezionata per Read / Read RAW |
| <kbd>OK</kbd> lungo | Salva la frequenza e apre subito **Read** |
| <kbd>Back</kbd> | Uscita (trigger e modalità di feedback vengono ricordati) |

Quale frequenza prende <kbd>OK</kbd>:

- se un segnale si sta ricevendo **in quel momento** (riquadro nero attorno alla frequenza principale) — quella
  frequenza, anche se è selezionata una voce di cronologia;
- se non si riceve nulla ed è selezionata una voce di cronologia — la voce selezionata;
- altrimenti — l'ultima frequenza che ha superato il trigger, così non devi tenere premuto il telecomando.

::: warning Arrotondamento
La frequenza salvata viene sempre **arrotondata alla frequenza più vicina nell'elenco**
([Frequenze e portata](/it/subghz/frequencies)). Se il tuo telecomando è lontano da tutti i valori standard, aggiungi
la sua frequenza a `setting_user`. Il numero principale mostrerà allora la frequenza reale, ma dopo il salto a
Read / Read RAW dovrai impostarla manualmente in `Config`.
:::

Salvare una frequenza dall'analizzatore **disattiva anche l'Hopping**, così Read parte esattamente su quella frequenza.

## Come trovare la frequenza di un telecomando

1. Allontanati da alimentatori switching, caricabatterie e altra elettronica rumorosa.
2. Apri `Main Menu → Sub-GHz → Frequency Analyzer`.
3. Tieni il telecomando appoggiato al lato sinistro del Flipper (vicino alla finestrella nera).
4. Premi e tieni premuto un tasto del telecomando. La frequenza principale passa in negativo mentre il segnale viene ricevuto.
5. Rilascia il tasto e attendi che la frequenza finisca nella cronologia.
6. Premi <kbd>OK</kbd> per memorizzarla, oppure tieni premuto <kbd>OK</kbd> per andare diretto a **Read**.

La maggior parte dei telecomandi trasmette intorno a 315, 433.92 o 868.35 MHz. In Read prova comunque più modulazioni
se nulla viene decodificato (prima `AM650`, poi `FM238`, `FM476`, `FM12K`).

## Regolare il trigger

Per impostazione predefinita il trigger è a −93 dBm, una posizione che va bene nella maggior parte dei casi, quindi
normalmente non si tocca. Regolalo solo quando il telecomando non viene catturato nemmeno a contatto, oppure quando c'è
molto rumore:

1. Senza premere nessun telecomando, sposta il segno con <kbd>←</kbd> / <kbd>→</kbd> finché il Flipper smette di
   catturare qualsiasi cosa (nessun rumore, nessun colpo casuale). La posizione più a sinistra è la più sensibile:
   cattura i segnali *e* il rumore interno del Flipper e qualsiasi interferenza; quella più a destra è la meno
   sensibile a entrambi.
2. Tieni il telecomando contro il bordo sinistro del Flipper e premi il suo tasto.
3. Se non viene catturato nulla, sposta il trigger **a sinistra** un passo alla volta finché il segnale compare.
4. Durante la regolazione premi e rilascia ripetutamente il tasto del telecomando: un segnale intermittente rende più
   facile trovare la posizione giusta rispetto a uno continuo.

## Risoluzione dei problemi

- **Compaiono continuamente frequenze casuali** — trigger troppo basso o rumore nelle vicinanze. Spostalo a destra,
  allontanati dagli alimentatori.
- **Il telecomando non viene mai catturato** — avvicinalo, controlla la batteria, sposta il trigger a sinistra. Alcuni
  telecomandi inviano raffiche molto brevi: premi ripetutamente.
- **Read non mostra nulla sulla frequenza trovata** — modulazione sbagliata. Cambiala in `Read → Config`. Se nulla
  viene decodificato, registra il segnale con [Read RAW](/it/subghz/read-raw).
- **La frequenza non corrisponde all'etichetta sul telecomando** — è normale; i telecomandi economici derivano. Usa i
  conteggi della cronologia per scegliere il valore più frequente.

## Pagine correlate

- [Frequenze e portata](/it/subghz/frequencies) · [Read](/it/subghz/read) · [Read RAW](/it/subghz/read-raw)
- [Remote Analyzer](/it/subghz/remote-analyzer) — un'app con analizzatore proprio e decodifica di un telecomando alla volta
