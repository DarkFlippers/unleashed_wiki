---
title: Remote Analyzer
order: 160
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/remote_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Remote Analyzer

**Remote Analyzer** (di @xMasterX) decodifica un telecomando alla volta sul CC1101 interno e mostra tutti i campi che riesce a ricavare. A differenza di `Sub-GHz → Read` non conserva **nessuna cronologia** — a schermo c'è solo l'ultimo segnale — e **non salva mai** un file `.sub`. È uno strumento per rispondere alla domanda "che telecomando è questo?".

::: tip Unleashed
Remote Analyzer è un'app di sistema integrata di Unleashed. Oltre a tutti i protocolli che conosce l'app Sub-GHz, ha protocolli propri di sola decodifica: **Crypt**, **Crypt Lite**, **Hormann BiSecur**, **KCE6xxx**, **Life Fido**, **Nero Intro II** e **PC4**.
:::

**Quando usarlo:** vuoi identificare rapidamente un telecomando sconosciuto, vedere se è a codice fisso o rolling, o controllare un telecomando che l'app principale non riesce a decodificare. Per acquisire e riprodurre, usa [Read](/it/subghz/read) o [Read RAW](/it/subghz/read-raw).

## Menu principale

`Main Menu → Apps → Sub-GHz → Remote Analyzer`:

- `Read` — decodifica in tempo reale
- `Decode RAW File` — passa un'acquisizione RAW salvata attraverso gli stessi decodificatori
- `Frequency Analyzer` — trova la frequenza del telecomando
- `How to use` — il manuale integrato

## Leggere un telecomando

1. Apri `Read`. La schermata mostra `Waiting for a signal`.
2. Premi <kbd>←</kbd> (`Config`) e imposta **Frequency** e **Modulation** (oppure attiva **Hopping**).
3. Tieni il telecomando vicino al Flipper e premi il suo tasto.
4. Compare la lettura:
   - l'icona in alto a sinistra indica codice **fisso** o **rolling**;
   - la riga sotto il nome del protocollo e il numero di bit indica se anche l'app Sub-GHz conosce questo protocollo,
     oppure se è **solo per l'analizzatore**;
   - `xN` in alto a destra conta quante volte questo codice è stato ricevuto;
   - la barra sotto la riga è l'intensità del segnale.
5. <kbd>↑</kbd> / <kbd>↓</kbd> scorrono una lettura che non ci sta a schermo, <kbd>→</kbd> (`Reset`) la cancella.

**Il LED:** viola — in ascolto; giallo — c'è qualcosa in onda che nulla ha decodificato; verde — è arrivato un codice.

## Config

| Voce | Cosa fa |
|---|---|
| Frequency | frequenza di ricezione (ignorata quando Hopping è attivo) |
| Modulation | preset: AM270, AM650, FM238, FM476, FM12K e qualsiasi preset personalizzato |
| Hopping | `OFF` oppure un livello da `-90dB` a `-40dB` |
| Sound | riproduce il segnale demodulato dall'altoparlante |
| Mod. sweep | prova altre modulazioni quando nulla viene decodificato |
| Notify | una vibrazione quando arriva un codice diverso dal precedente |
| Reset to default | ripristina i valori predefiniti |

**Hopping.** Con un livello impostato, l'app percorre **315, 390, 430.5, 433.92, 434.42 e 868.35 MHz** mentre l'aria è silenziosa e si ferma sulla prima banda in cui la portante raggiunge quel livello. Una decodifica mantiene la banda per due secondi prima che l'hopping riprenda. Scegliere una frequenza nel Frequency Analyzer disattiva l'hopping. Il livello è anche ciò che lo sweep e il LED considerano "un segnale", quindi conta anche con l'hopping su `OFF`.

**Mod. sweep.** Quando un telecomando sta chiaramente trasmettendo ma nulla lo decodifica, l'app percorre le altre modulazioni, circa un secondo ciascuna. Un `~` accanto alla modulazione significa che sta ancora provando — **tieni premuto il tasto del telecomando**. La prima decodifica riuscita fissa la modulazione e il `~` scompare; dopo due secondi senza alcuna decodifica lo sweep riparte da lì. `Unknown remote` significa che un giro completo non ha trovato nulla; ricomincia finché il tasto è premuto.

**Notify.** Un telecomando tenuto premuto ripete un solo codice, quindi fa soltanto lampeggiare il LED; un codice nuovo e diverso fa anche vibrare.

## Decode RAW File

1. Scegli `Decode RAW File` e seleziona un `.sub` RAW da `/ext/subghz`.
2. Una barra di avanzamento mostra a che punto è nel file.
3. Ogni codice distinto trovato viene elencato; premi <kbd>OK</kbd> su uno per la lettura completa.

Solo un'acquisizione RAW contiene campioni — un file chiave salvato viene rifiutato. Se nulla viene decodificato (o se il file viene rifiutato) viene emesso un errore sonoro e il LED resta rosso.

## Frequency Analyzer

Tieni premuto il tasto del telecomando vicino al Flipper, poi **tieni premuto** <kbd>OK</kbd> per riportare la frequenza rilevata in `Read`. <kbd>←</kbd> / <kbd>→</kbd> spostano il livello di trigger. Funziona come l'[analizzatore dell'app principale](/it/subghz/frequency-analyzer).

## Risoluzione dei problemi

- **Resta sempre su `Waiting for a signal`** — frequenza sbagliata; usa il Frequency Analyzer oppure attiva l'Hopping.
- **LED giallo ma nessuna decodifica** — attiva `Mod. sweep` e tieni premuto il tasto, oppure registra il segnale con
  [Read RAW](/it/subghz/read-raw) e prova `Decode RAW File`.
- **Protocollo solo per l'analizzatore** — l'app Sub-GHz principale non può salvarlo né inviarlo; Remote Analyzer lo
  identifica soltanto.
- **Vuoi salvare il segnale** — usa [Read](/it/subghz/read); questa app non scrive file.

## Pagine correlate

- [Read](/it/subghz/read) · [Read RAW](/it/subghz/read-raw) · [Frequency Analyzer](/it/subghz/frequency-analyzer)
- [Sistemi supportati](/it/subghz/supported-systems)
