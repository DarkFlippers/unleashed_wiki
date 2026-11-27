---
title: Sub-GHz RAW Edit
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/subghz_raw_editor, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/Lechnio/SubGHz-RAW-Edit]
sources: [unleashed-src, unleashed-readme]
---
# Sub-GHz RAW Edit

**Sub-GHz RAW Edit** (di Lechnio) è un piccolo editor di forme d'onda che gira sul dispositivo e lavora sulle acquisizioni RAW `.sub`. Una registrazione di [Read RAW](/it/subghz/read-raw) contiene di solito secondi di rumore attorno alla breve raffica che ti interessa. Con RAW Edit trovi il segnale reale, lo marchi e salvi solo quella parte — e puoi unire più file, tagliare pezzi via e decodificare una selezione con i decodificatori Sub-GHz del firmware.

::: tip Unleashed
RAW Edit è distribuito con Unleashed come app di sistema, e l'app Sub-GHz lo apre direttamente:
`Sub-GHz → Read RAW` (oppure `Saved`) → apri un file RAW → <kbd>→</kbd> `More` → `Edit`. La voce `Edit` è mostrata solo quando RAW Edit è installato. Quando esci dall'editor torni a Sub-GHz.
:::

**Quando usarlo:** tagliare una lunga acquisizione RAW prima di condividerla o inviarla, dividere una registrazione in tasti separati, incollare insieme più acquisizioni, oppure scoprire quale protocollo si nasconde dentro un file RAW.

## Menu principale

`Main Menu → Apps → Sub-GHz → Sub-GHz RAW Edit`:

- `Select .sub file` — apre un file da `/ext/subghz` nell'editor
- `Merge .sub files` — unisce più file in uno
- `Config` — opzioni di caricamento e unione
- `About` — versione e link al progetto

Oltre ai file RAW, l'app può caricare qualsiasi segnale che il firmware sia in grado di codificare (viene convertito in RAW tramite il codificatore interno). Per i protocolli con tasti personalizzati propone prima un selettore di tasto.

## L'editor

La schermata mostra la forma d'onda con una barra panoramica in alto e due righe sotto: `View:` (zoom) e `Marked:` (lunghezza della selezione A..B). L'intervallo selezionato è evidenziato con una linea punteggiata; piccoli segni indicano che c'è altro segnale oltre il bordo dello schermo.

| Tasto | Azione |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | sposta il marcatore attivo (A o B); tieni premuto per spostarti più rapidamente |
| <kbd>↑</kbd> / <kbd>↓</kbd> | zoom avanti / indietro |
| <kbd>OK</kbd> | passa da un marcatore all'altro, A o B |
| <kbd>OK</kbd> tenuto premuto | apre il menu delle azioni |
| <kbd>Back</kbd> | chiude l'editor |

Il menu delle azioni (<kbd>↑</kbd> / <kbd>↓</kbd>, <kbd>OK</kbd> per eseguire, <kbd>Back</kbd> per chiudere) sta a sinistra, con accanto un pannello informativo di sola lettura che mostra il numero di campioni di A..B, `TE` e la codifica di linea rilevata (`PWM`, `PPM`, `Manchester`, `NRZ` o `1:1`):

- **Save** — scrive solo l'intervallo A..B in un nuovo file RAW. Il nome proposto è `<nome>_edit1`, `_edit2`, …
  Salvare con un nome esistente chiede `Name exists, overwrite?`; il file aperto non viene mai sovrascritto.
- **Decode** — decodifica l'intervallo A..B con i decodificatori Sub-GHz del firmware (provando ogni produttore su ciascun frame KeeLoq; salta BinRAW), raggruppa i pacchetti identici
  (`Decoded: N`) e salva quello scelto come file chiave, con nome basato per impostazione predefinita su protocollo e
  produttore (per esempio `KeeLoq_Verex`). Ogni voce decodificata ha anche un pulsante **Locate** che aggancia A..B al relativo frame (il primo quando si ripete). `No known protocol` significa che non è stato decodificato nulla.
- **Cut** / **Copy** / **Paste** — premi <kbd>←</kbd> / <kbd>→</kbd> su `Cut` per passare tra **Cut** (rimuove A..B e lo mette negli appunti; rifiutato se lascerebbe il segnale vuoto), **Copy** (copia A..B nel file degli appunti) e **Paste** (inserisce gli appunti al marcatore attivo e li seleziona).
- **Undo** — cronologia su scheda SD degli ultimi **32** tagli e incollaggi (non occupa RAM). Con più di una modifica, le elenca dalla più recente con numero di campioni e posizioni, riportando il segnale allo stato precedente a quella scelta. Barrato quando non c'è nulla da annullare.

## Tagliare un'acquisizione, passo per passo

1. Registra il telecomando in [Read RAW](/it/subghz/read-raw) e salvalo.
2. Aprilo in RAW Edit (tramite `More → Edit` oppure `Select .sub file`).
3. Riduci lo zoom con <kbd>↓</kbd> per vedere dove si trovano le raffiche.
4. Sposta il marcatore **A** appena prima della raffica con <kbd>←</kbd>/<kbd>→</kbd>, premi <kbd>OK</kbd>, sposta il
   marcatore **B** appena dopo.
5. Tieni premuto <kbd>OK</kbd> → `Save`, accetta o modifica il nome.
6. Prova il file salvato da `Sub-GHz → Saved`.

## Unire file

1. `Merge .sub files` → scegli un file; la finestra mostra `Added N file(s)` e il numero di campioni. Scegli
   `Add more` oppure `Done`.
2. Tutti i file devono essere sulla stessa frequenza, altrimenti ottieni `Frequency mismatch`.
3. Il risultato si apre nell'editor come `merged`; salvalo dal menu delle azioni.

## Config

| Voce | Cosa fa |
|---|---|
| Normalize jitter | `OFF`/`ON` — ripulisce jitter e deriva delle temporizzazioni durante il caricamento |
| Merge gap | silenzio inserito tra i file uniti, 0–1000 ms (predefinito 100); <kbd>OK</kbd> apre l'inserimento di un numero |
| Repeat | ripete ogni segnale caricato / unito da 1 a 64 volte |

Una riga di sola lettura in fondo a `Config` mostra anche se i tasti personalizzati e la conservazione del contatore rolling sono disponibili nella build attuale del firmware.

## Limiti e risoluzione dei problemi

- **Nessun limite di lunghezza (v2.0):** segnali e unioni sono tenuti in un file di lavoro sulla scheda SD, mentre la RAM mantiene una finestra scorrevole dell'acquisizione (fino a ~38 000 campioni a Flipper appena avviato), lasciando spazio per Decode e Save. Spingendo il marcatore A o B oltre il bordo della finestra, questa scorre avanti di un quarto; lo zoom indietro si ferma al limite della finestra con `No RAM to zoom out`.
- **Avviso `Low RAM`** — mostrato quando la RAM libera contiene meno di 15 000 campioni di un segnale più grande; propone `Reboot` o `Continue`. Anche `Decode` verifica la presenza di ~8 KB di RAM libera e segnala `Low memory` invece di bloccarsi.
- `Unsupported protocol or file is empty` — il file non è un segnale che il firmware possa codificare.
- `Nothing in A..B` / `Range too small` — allontana di più i marcatori.
- I lunghi intervalli di silenzio vengono mantenuti alla loro lunghezza reale nel file salvato.

## Pagine correlate

- [Read RAW](/it/subghz/read-raw) · [Formati dei file](/it/subghz/file-format)
- [Remote Analyzer](/it/subghz/remote-analyzer)
