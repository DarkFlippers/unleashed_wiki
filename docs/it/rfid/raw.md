---
title: Registrazione RAW
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/LFRFIDRaw.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/lfrfid_debug]
sources: [unleashed-docs, unleashed-src]
---
# Leggere dati RAW a 125 kHz

La modalità RAW registra il segnale del tag così com'è — durate degli impulsi e dei periodi — invece di decodificarlo,
un po' come un registratore vocale. È pensata per la **ricerca sui protocolli**: se il tuo tag non viene riconosciuto,
registralo e invia i file (insieme a una foto della tessera) agli sviluppatori in una issue su GitHub.

## Attivare la modalità Debug

Le voci RAW restano nascoste se Debug non è attivo:

1. `Main Menu → Settings → System`.
2. Imposta **Debug** su **ON**.

## Registrare

1. Vai su `Main Menu → 125 kHz RFID → Extra Actions → Read RAW RFID data`.
2. Assegna un nome alla registrazione (predefinito `RfidRecord`).
3. Leggi le istruzioni (*RAW RFID Data Reader — 1. Hold card next to Flipper, 2. Press OK, 3. Wait until data is
   read*) e premi <kbd>OK</kbd>.
4. Tieni la tessera sul retro del Flipper. Il Flipper registra tre passate di **5 secondi** ciascuna — *Reading ASK*,
   *ASK 134kHz*, *Reading PSK* — chiedendo *Don't move for 5 sec.*
5. **RAW RFID Read Success** — *Now you can analyze files or send them to developers*. Premi <kbd>OK</kbd>.

In `/ext/lfrfid/` vengono creati tre file:

| File | Passata |
|---|---|
| `<name>.ask.raw` | ASK, portante a 125 kHz |
| `<name>.ask134.raw` | ASK, portante a 134,2 kHz |
| `<name>.psk.raw` | PSK, portante a 125 kHz |

::: tip Unleashed
La documentazione di Unleashed e il firmware di serie parlano di due file (ASK e PSK). Il firmware attuale registra
una terza passata, **ASK 134kHz**, per i tag per animali.
:::

Se compare *RAW Reading error! This may be caused by SD card issues*, controlla la scheda (spazio libero, errori).
Senza scheda SD l'app mostra *No SD Card!*.

## Riprodurre

`Extra Actions → Emulate RAW RFID data` apre il browser dei file per i file `.raw` e riproduce quello selezionato
(*Emulating RAW RFID*). È utile soprattutto per il debug dei protocolli, non come sostituto dell'emulazione normale.

## CLI

Le stesse funzioni sono disponibili dalla CLI e sono comode in fase di sviluppo:

```text
rfid raw_read <ask | ask134 | psk> <filename>   - read and save raw data to a file
rfid raw_emulate <filename>                     - emulate raw data
rfid raw_analyze <filename>                     - print the raw data and try to decode it
```

`raw_analyze` stampa ogni coppia impulso/durata, segnala dove un protocollo è stato decodificato e termina con
frequenza, duty cycle, medie e protocollo rilevato (oppure `not found`).

## App LF-RFID Debug

I sorgenti del firmware contengono anche uno strumento per sviluppatori, **LF-RFID Debug**
(`applications/debug/lfrfid_debug`), la cui schermata **Tune** regola in tempo reale il timer della portante (ARR/CCR
— frequenza e duty cycle). È un'app di debug per lo sviluppo dei protocolli, non serve per l'uso normale.

## Pagine correlate

- [Formati dei file](/it/rfid/file-format) · [Lettura](/it/rfid/read) · [Protocolli](/it/rfid/protocols)
