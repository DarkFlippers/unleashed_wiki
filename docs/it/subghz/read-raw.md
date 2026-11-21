---
title: Read RAW (registrare il segnale grezzo)
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/sub-ghz/read-raw]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Read RAW

**Read RAW** registra il segnale demodulato "così com'è", senza decodificarlo — come un registratore vocale. La
registrazione può essere riprodotta, salvata, decodificata in seguito o modificata. Usalo quando:

- **Read** non riconosce il telecomando (protocollo sconosciuto);
- vuoi acquisire un segnale per analizzarlo o per segnalare un nuovo protocollo agli sviluppatori;
- ti serve la riproduzione esatta di un segnale statico il cui protocollo il Flipper non conosce.

La registrazione viene comunque effettuata con la **frequenza e la modulazione** selezionate — il Flipper non è un SDR.
Una modulazione sbagliata ti dà una registrazione di rumore.

::: warning Codici rolling
Riprodurre in RAW un telecomando a codice rolling equivale a un clone: fa avanzare il contatore del ricevitore e può
desincronizzare il tuo originale. **Non farlo mai con la chiave di un'auto** — la chiave può finire in blacklist.
Dettagli: [Codici rolling](/it/subghz/rolling-codes).
:::

## Registrare

1. Se non la conosci, trova la frequenza con il [Frequency Analyzer](/it/subghz/frequency-analyzer).
2. Apri `Main Menu → Sub-GHz → Read RAW`.
3. Premi <kbd>←</kbd> **Config** e imposta `Frequency`, `Modulation` e `RSSI Threshold:` (vedi sotto).
   Premi <kbd>Back</kbd> per tornare.

   ![Read RAW pronto a registrare: forma d'onda vuota, pulsanti Config e REC](/screens/subghz/read_raw.png)

4. Premi <kbd>OK</kbd> **REC**. La forma d'onda inizia a scorrere, l'RSSI è mostrato a destra.
5. Premi il tasto sul telecomando (tienilo premuto 1–2 s).

   ![Read RAW in registrazione: due raffiche di segnale sulla forma d'onda, contatore di campioni e pulsante Stop](/screens/subghz/read_raw_recording.png)

6. Premi <kbd>OK</kbd> **Stop**.
7. A questo punto hai tre possibilità:
   - <kbd>←</kbd> **Erase** — scartare e ricominciare;
   - <kbd>OK</kbd> **Send** — riprodurre la registrazione (tieni premuto per ripeterla);
   - <kbd>→</kbd> **Save** — inserire un nome (predefinito `RAW_<date-time>`) e salvare in `/ext/subghz/`.

## Config in Read RAW

Il menu di configurazione RAW è più breve di quello di Read:

| Voce | Valori | Significato |
|---|---|---|
| `Frequency` | elenco di frequenze | Frequenza di ricezione |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + personalizzati | Preset di demodulazione |
| `Sound` | `OFF` / `ON` | Riproduce dall'altoparlante il segnale ricevuto |
| `RSSI Threshold:` | `-----`, `-85.0` … `-40.0` | Registra solo mentre il segnale è sopra questo livello. `-----` = registra tutto |

::: tip Quando usare la soglia
Con una soglia il file contiene solo le raffiche del tuo telecomando e non secondi di rumore tra una pressione e
l'altra: i file sono molto più piccoli e puliti. Per le acquisizioni da inviare agli sviluppatori, lasciala a `-----`
(registrazione completa).
:::

## Riprodurre un RAW salvato {#playback}

1. `Main Menu → Sub-GHz → Saved` e seleziona il file RAW. Si apre nella schermata Read RAW.
2. <kbd>OK</kbd> **Send** — invia l'intera registrazione una volta; tieni premuto <kbd>OK</kbd> per ripeterla
   (**Hold to repeat**).
3. <kbd>←</kbd> **New** — avvia una nuova registrazione.
4. <kbd>→</kbd> **More**:
   - `Decode` — passa la registrazione attraverso tutti i decodificatori dell'app Sub-GHz; i segnali trovati possono
     essere salvati come normali file chiave;
   - `Edit` — apre il file nell'app [Sub-GHz RAW Edit](/it/subghz/raw-editor) (mostrato solo quando quell'app è
     installata in una versione compatibile); Sub-GHz si riapre quando esci dall'editor;
   - `Rename`, `Delete`.

::: tip Unleashed
`More → Decode` e `More → Edit` sono aggiunte di Unleashed. Con `Edit` puoi trovare il segnale reale in
un'acquisizione rumorosa, tagliarlo, unire file e decodificare solo una selezione.
:::

I file RAW lunghi e densi vengono trasmessi in streaming dalla scheda SD durante l'invio. Se sono coinvolti impulsi
molto brevi (sotto i 10 µs) e la scheda è lenta, la trasmissione può interrompersi prima della fine del file — usa una
scheda di buona qualità.

## Registrare un telecomando per richiedere un protocollo

È la procedura che gli sviluppatori di Unleashed chiedono quando vuoi il supporto di un nuovo protocollo:

1. Trova la frequenza con l'analizzatore. In Read prova `AM650`, `FM238`, `FM476`, `FM12K` — se nulla viene
   decodificato, continua.
2. In Read RAW imposta quella frequenza e **`RSSI Threshold: -----`**.
3. Crea **un RAW per ciascuna modulazione**: `AM650`, `FM238`, `FM476`, `FM12K`.
4. Per ognuna: premi **REC**, poi premi un tasto del telecomando **5 volte tenendolo premuto 1–2 s**, poi **5 volte
   tenendolo premuto ~5 s**. Ferma e salva.
5. Se il telecomando ha più tasti, registra ogni tasto nello stesso modo. Dai a ogni file il nome del tasto.
6. Copia i file su un PC, comprimili in uno zip e apri una issue nel repository del firmware. Aggiungi buone foto del
   telecomando (anche all'interno, se possibile), modello e produttore.

## Risoluzione dei problemi

- **La registrazione è piatta / solo rumore** — frequenza o modulazione sbagliate, oppure il telecomando è troppo
  lontano. Tienilo vicino.
- **File enormi** — imposta un `RSSI Threshold`.
- **La riproduzione non funziona** — il telecomando usa un codice rolling (il ricevitore rifiuta i contatori vecchi),
  la modulazione era sbagliata, o la registrazione contiene solo una parte del segnale. Registra pressioni più lunghe.
- **La trasmissione si interrompe a metà** — scheda SD lenta con un file lungo e denso. Taglia il file con
  [RAW Edit](/it/subghz/raw-editor) o usa una scheda più veloce.
- **`Edit` manca in `More`** — l'app Sub-GHz RAW Edit non è installata o è troppo vecchia.

## Pagine correlate

- [Read](/it/subghz/read) · [Sub-GHz RAW Edit](/it/subghz/raw-editor) · [Remote Analyzer](/it/subghz/remote-analyzer)
- [Formati dei file (RAW, BinRAW)](/it/subghz/file-format) · [Codici rolling](/it/subghz/rolling-codes)
