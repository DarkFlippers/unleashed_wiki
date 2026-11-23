---
title: Read (lettura)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Read

**Read** ascolta su una frequenza (o salta tra più frequenze), **decodifica** i segnali dei protocolli noti e li
mostra in un elenco. Un segnale decodificato può essere salvato come file chiave e inviato di nuovo. È il modo
principale per copiare un telecomando a **codice statico (fisso)** — cancelli, sbarre, campanelli, prese — e per
identificare quale protocollo usa un telecomando.

Per i telecomandi che Read non riconosce, usa [Read RAW](/it/subghz/read-raw). Per i telecomandi a codice rolling
leggi [Codici rolling](/it/subghz/rolling-codes) **prima** di inviare qualsiasi cosa.

::: tip Unleashed
Rispetto al firmware di serie, Unleashed aggiunge: decine di protocolli in più
([elenco completo](/it/subghz/supported-systems)), salvataggio e invio di molti protocolli a **codice rolling**,
**tasti personalizzati** sulle frecce durante l'invio, hopping con soglia RSSI, filtri `Ignore …`,
`Delete old signals when memory is full`, **tenere premuto <kbd>→</kbd> per eliminare** un segnale dall'elenco, l'ora
di ricezione mostrata per ogni segnale e le ultime impostazioni ricordate.
:::

## Leggere un telecomando

1. Se non la conosci, trova prima la frequenza: [Frequency Analyzer](/it/subghz/frequency-analyzer)
   (lì <kbd>OK</kbd> lungo salta direttamente in Read sulla frequenza trovata).
2. Apri `Main Menu → Sub-GHz → Read`. La schermata mostra `Fixed scan...` (oppure `Hopper scan...` con l'hopping
   attivo) e in basso la frequenza e la modulazione correnti.

   ![Schermata Read in attesa di un segnale: Fixed scan su 433.92 MHz, AM650](/screens/subghz/read.png)

3. Tieni il telecomando vicino al lato sinistro del Flipper e premi il suo tasto per 1–2 secondi.
4. Il segnale decodificato compare nell'elenco come `nome del protocollo` + ora di ricezione. Il contatore in basso
   mostra quanti segnali ci sono nell'elenco.

   ![Elenco di Read con tre segnali ricevuti: Princeton, CAME 12bit e KL: DoorHan](/screens/subghz/read_list.png)

5. Selezionalo con <kbd>↑</kbd> <kbd>↓</kbd> e premi <kbd>OK</kbd> per vedere i dettagli (chiave, numero di bit,
   seriale, tasto, contatore, produttore per KeeLoq ecc.).

   ![Dettagli del segnale: Princeton 24bit con chiave, seriale e tasto, pulsanti Send e Save](/screens/subghz/signal_info.png)

6. Premi <kbd>→</kbd> **Save**, inserisci un nome e conferma. Il file finisce in `/ext/subghz/`.
7. Oppure premi <kbd>OK</kbd> **Send** per trasmetterlo subito.

I segnali salvati si trovano in `Main Menu → Sub-GHz → Saved` (vedi [sotto](#saved-signals)).

## Tasti nella schermata Read

| Tasto | Azione |
|---|---|
| <kbd>←</kbd> | **Config** — impostazioni del ricevitore |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Spostarsi nell'elenco dei segnali ricevuti |
| <kbd>OK</kbd> | Aprire il segnale selezionato |
| <kbd>→</kbd> tenuto premuto | Eliminare il segnale selezionato dall'elenco |
| <kbd>Back</kbd> | Uscire da Read. Se ci sono segnali non salvati compare **Exit to Sub-GHz Menu?** — `Exit` / `Stay` |

A seconda delle dimensioni dei dati ricevuti, l'elenco può contenere fino a 128 segnali.

## Config {#config}

Premi <kbd>←</kbd> **Config** nella schermata Read:

![Menu Config di Read: Frequency, Modulation, Hopping e Bin RAW](/screens/subghz/read_config.png)

| Voce | Valori | Cosa fa |
|---|---|---|
| `Frequency` | elenco da [Frequenze e portata](/it/subghz/frequencies) | Frequenza di ricezione fissa. Mostra ` -----` quando l'hopping è attivo |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + preset personalizzati | Preset di demodulazione. `AM650` va bene per la maggior parte dei telecomandi |
| `Hopping` / `Hopping RSSI` | `OFF`, `-90dBm` … `-40dBm` | Cicla sull'elenco dell'hopper (315, 390, 430.5, 433.92, 434.42, 868.35 MHz). Il valore è il livello RSSI che ferma l'hopping su una frequenza |
| `Bin RAW` | `OFF` / `ON` | Raccoglie anche i segnali statici sconosciuti come **BinRAW** (pattern ripetuto con bit rate ricostruito). Tieni premuto il tasto del telecomando un po' più a lungo, così si accumulano dati sufficienti |
| `Ignore ReversRB2` | `OFF` / `ON` | Nasconde i segnali Revers RB-2(M) |
| `Ignore Alarms` | `OFF` / `ON` | Nasconde i protocolli degli antifurti per bici/moto (Hollarm, GangQi) |
| `Ignore Sensors` | `OFF` / `ON` | Nasconde sensori e chiacchiericcio simile: Magellan, Honeywell, Honeywell WDB e campanelli Legrand, Doorbell32, KeyFinder/KeyFinder2, Feron |
| `Ignore Princeton` | `OFF` / `ON` | Nasconde Princeton (PT2262 e cloni) — utile dove i telecomandi economici inondano l'aria |
| `Ignore Nice Flor-S / Nice One` | `OFF` / `ON` | Nasconde Nice Flor-S / Nice One |
| `Delete old signals when memory is full` | `OFF` / `ON` | Quando l'elenco è pieno, scarta i segnali più vecchi invece di fermarsi. Il contatore mostra allora `!` |
| `Sound` | `OFF` / `ON` | Riproduce dall'altoparlante tutto ciò che la radio riceve |
| `Reset to default` | — | Torna a 433.92 MHz AM650, hopping disattivato, tutti i filtri disattivati, Bin RAW disattivato, potenza TX `Preset` |
| `Lock Keyboard` | — | Blocca i tasti durante la scansione (in tasca). **Sblocco: premi <kbd>Back</kbd> tre volte** |

Tutte le impostazioni di Read vengono salvate e ripristinate alla successiva apertura dell'app.

::: tip Quale valore di hopping scegliere
Con `Hopping` attivo, il ricevitore resta su una frequenza solo quando il segnale è sopra il livello scelto. `-90dBm`
è il più sensibile; alzalo se il rumore continua a fermare l'hopper. Per una ricezione affidabile preferisci una
**frequenza fissa** trovata con l'analizzatore: i segnali inviati durante un cambio di frequenza vengono persi.
:::

## Inviare un segnale

Apri il segnale (dall'elenco di Read oppure da `Saved → <file> → Emulate`). La schermata di trasmissione mostra i dati
della chiave, la frequenza, la modulazione e `R: Int` / `R: Ext` (quale radio trasmetterà).

- **Premi** <kbd>OK</kbd> (**Send**) — una singola pressione trasmette un pacchetto completo di segnale (di norma con
  1–3 ripetizioni per affidabilità). **Tenere premuto** il tasto ripete continuamente la trasmissione finché non viene
  rilasciato (utile a maggiore distanza o con forti interferenze). Nei protocolli a codice rolling, tenere premuto il
  tasto **non** incrementa il contatore (vedi anche [Modalità contatore](/it/subghz/counter-mode)): il segnale viene
  ripetuto con lo stesso contatore finché non rilasci e premi di nuovo.
- <kbd>Back</kbd> — uscire.

### Tasti personalizzati (Unleashed)

::: tip Unleashed
Per molti protocolli i tasti freccia inviano lo **stesso telecomando con un altro codice tasto**, così un singolo file
salvato si comporta come il telecomando completo. Supportati, tra gli altri: KeeLoq, Alutech AT-4N, Nice Flor-S,
Somfy Telis/Keytis, Security+ 2.0, CAME Atomo, FAAC SLH, BelKorn, Beninca ARC, Ditec GOL4, Jarolift,
KingGates Stylo 4k, V2 Phoenix, Prastel, Roger, Nord ICE, Princeton, Proteco, Dooya, Hay21, GangQi, Hollarm. Mentre una
freccia è premuta, il codice tasto inviato viene mostrato sul bordo destro dello schermo. Quale freccia corrisponda a
quale tasto dipende dal protocollo — vedi [Codici rolling](/it/subghz/rolling-codes) e
[Il Flipper come nuovo telecomando](/it/subghz/remote-prog).
:::

## Segnali salvati {#saved-signals}

`Main Menu → Sub-GHz → Saved` elenca i file in `/ext/subghz/`. Scegline uno e ottieni:

- `Emulate` — apre la schermata di trasmissione;
- `Rename`;
- `Delete`;
- `Signal Settings` — **solo in modalità Debug** (`Settings → System → Debug`): consente di cambiare `Counter Mode`,
  `Edit Counter`, `Edit Button` di un file a codice rolling. Vedi [Modalità contatore](/it/subghz/counter-mode).

I file RAW si aprono invece nella schermata Read RAW — vedi [Read RAW](/it/subghz/read-raw#playback).

I nomi dei file vengono generati automaticamente (data-ora), a meno che `Protocol Names` non sia attivo in
[Radio Settings](/it/subghz/settings) — in quel caso il nome del protocollo viene messo davanti al timestamp.

## Codici statici e codici rolling

- **Codice statico** (Princeton, CAME 12/24 bit, Nice Flo, Marantec, Roger, Gate TX…): ogni pressione invia lo stesso
  codice. Una copia salvata funziona per sempre accanto all'originale.
- **Codice rolling (dinamico)** (KeeLoq, Nice Flor-S, CAME Atomo, FAAC SLH, Somfy, Security+…): ogni pressione porta un
  nuovo valore di contatore. Unleashed può salvarne e inviarne molti, **ma inviare una copia desincronizza il
  telecomando originale**. Leggi [Codici rolling](/it/subghz/rolling-codes) e preferisci
  [Add Manually](/it/subghz/add-manually) per creare un telecomando *nuovo*.

::: danger Radiochiavi per auto
Non fare esperimenti con la chiave della tua auto. Riprodurre una radiochiave (Read o Read RAW) può desincronizzarla o
metterla in blacklist, e il nuovo accoppiamento richiede spesso gli strumenti del concessionario. Usa il Flipper solo
con apparecchiature di tua proprietà e per ricerca lecita.
:::

## Risoluzione dei problemi

- **Non compare nulla** — frequenza o modulazione sbagliate. Usa l'analizzatore e prova diverse modulazioni
  (`AM650`/`FM238`/`FM476`/`FM12K`). Verifica che un filtro `Ignore …` non stia nascondendo il protocollo.
- **Segnale ricevuto ma non decodificato** — il protocollo è sconosciuto: attiva `Bin RAW` (telecomandi statici) o
  registra con [Read RAW](/it/subghz/read-raw). Prova anche l'app [Remote Analyzer](/it/subghz/remote-analyzer).
- **KeeLoq mostra produttore `Unknown`** — la chiave del produttore non è nel database, oppure il telecomando richiede
  un Seed (BFT, Erreka, FAAC SLH). Vedi [KeeLoq](/it/subghz/keeloq) e [Seed Capturer](/it/subghz/seed-capturer).
- **Nessun pulsante `Send`** — il protocollo è di sola decodifica (per esempio iDo), oppure è un pacchetto Nice O-Code senza
  codice installatore (usa l'app [Nice O-Code](/it/subghz/nice-o-code)).
- **L'elenco si riempie di rumore** — abilita le opzioni `Ignore` pertinenti oppure
  `Delete old signals when memory is full`.

## Pagine correlate

- [Read RAW](/it/subghz/read-raw) · [Frequency Analyzer](/it/subghz/frequency-analyzer) · [Sistemi supportati](/it/subghz/supported-systems)
- [Codici rolling](/it/subghz/rolling-codes) · [Add Manually](/it/subghz/add-manually) · [Radio Settings](/it/subghz/settings) · [Formati dei file](/it/subghz/file-format)
