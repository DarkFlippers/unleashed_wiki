---
title: Security+ PIN
order: 180
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/secplus_pin, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Security+ PIN

**Security+ PIN** (di @xMasterX) lavora su un segnale di **tastiera Security+ 2.0** acquisito — il pacchetto da 86 bit inviato dalle tastiere wireless Chamberlain / LiftMaster. Il PIN della tastiera si trova all'interno di quel pacchetto. L'app permette di impostare un PIN a mano o di scorrere da `0000` a `9999`, trasmette ogni candidato e riscrive il PIN nel file una volta trovato quello giusto.

::: tip Unleashed
Security+ 2.0 Keypad (86 bit, 315 / 390 / 868 MHz) viene decodificato dall'app Sub-GHz di Unleashed, e questa app di sistema integrata ne modifica il PIN. I normali telecomandi Security+ 2.0 da 62 bit non sono pacchetti di tastiera e vengono rifiutati.
:::

::: warning
Solo per il tuo apriporta da garage e la tua tastiera.
:::

## Prima di iniziare

1. Acquisisci la tua tastiera con `Sub-GHz → Read` sulla sua frequenza (vedi [Read](/it/subghz/read)) e salvala. Il
   file salvato deve mostrare `Security+ 2.0` con `Bit: 86`.
2. Il file si trova in `/ext/subghz/`.

## Usare l'app

1. Apri `Main Menu → Apps → Sub-GHz → Security+ PIN`.
2. Scegli `Open .sub file` e seleziona l'acquisizione della tastiera. Al caricamento, lo stato mostra la frequenza e
   `ready` (per esempio `315MHz  ready`). Se il file contiene già un `Pin`, viene mostrato.
3. Le quattro cifre del PIN sono a schermo, con una cornice attorno alla cifra attiva:
   - <kbd>←</kbd> / <kbd>→</kbd> — spostarsi tra le cifre
   - <kbd>↑</kbd> / <kbd>↓</kbd> — cambiare il PIN
   - <kbd>OK</kbd> (`Send`) — trasmettere il PIN corrente (`Sending 1234...` → `Sent 1234`)
   - <kbd>OK</kbd> tenuto premuto — **sweep**: invia tutti i PIN a partire da quello corrente; una barra di
     avanzamento mostra `N of 9999`. Un <kbd>OK</kbd> breve oppure <kbd>←</kbd> (Back) lo ferma su
     `Stopped at NNNN`
   - <kbd>←</kbd> tenuto premuto — **salva** il PIN corrente nel file (`Saved PIN NNNN`)
   - <kbd>Back</kbd> — torna al menu

La riga di suggerimento a schermo riassume tutto: `hold OK sweep   < save`.

Il salvataggio aggiorna il file aperto sul posto: scrive i campi `Pin`, `Key` e `Secplus_packet_1`. Dopodiché il file
può essere inviato normalmente da `Sub-GHz → Saved`.

## Messaggi

| Messaggio | Significato |
|---|---|
| `Not Security+ 2.0: …` | il file è di un altro protocollo |
| `Not an 86-bit keypad` | è un telecomando Security+ 2.0, non un pacchetto di tastiera |
| `Missing packet 1` / `No Key value` | acquisizione incompleta — rileggi la tastiera |
| `Unsupported preset …` / `Bad custom preset` | il preset del file non può essere usato |
| `NNNMHz TX blocked` / `TX blocked, sweep stopped` | la trasmissione su questa frequenza non è consentita (vedi [Frequenze e portata](/it/subghz/frequencies)) |
| `TX failed` | la radio non è riuscita a trasmettere |

## Risoluzione dei problemi

- **Lo sweep è lento** — ogni PIN è una trasmissione separata con una breve pausa; uno sweep completo richiede molto
  tempo. Avvialo da un valore probabile e fermalo appena la porta reagisce.
- **La porta ha reagito ma ti è sfuggito il PIN** — lo sweep si ferma sul numero mostrato; torna indietro con
  <kbd>↓</kbd> e invia singoli PIN con <kbd>OK</kbd> per confermare, poi tieni premuto <kbd>←</kbd> per salvare.
- **File sbagliato rifiutato** — acquisisci la tastiera stessa, non un telecomando portatile.

## Pagine correlate

- [Read](/it/subghz/read) · [Sistemi supportati](/it/subghz/supported-systems)
- [Codici rolling](/it/subghz/rolling-codes)
