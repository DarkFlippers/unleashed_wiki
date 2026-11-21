---
title: Fuzzer RFID
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/rfidfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# Fuzzer RFID

Un **fuzzer** emula una lunga serie di ID uno dopo l'altro per verificare come reagisce un lettore — per esempio se
accetta un ID predefinito, se si blocca con dati malformati, oppure per individuare l'intervallo di tessere valide del
tuo sistema.

::: tip Unleashed
Il ReadMe di Unleashed elenca i **plugin LFRFID e iButton Fuzzer** tra le sue funzioni NFC/RFID/iButton. Il fuzzer è
un'app esterna, non fa parte dell'albero dei sorgenti del firmware: pacchetti di app precompilate vengono aggiunti
alle build di release, e l'**extra apps pack** pubblicato con ogni release contiene tutte le app funzionanti
conosciute. I suoi menu dipendono dalla versione dell'app, quindi non sono descritti qui.
:::

## Cosa fornisce il firmware: elenchi di UID di esempio

Il firmware installa in **`/ext/rfidfuzzer/`** alcuni elenchi di ID di esempio per il fuzzer:

| File | Protocollo | Lunghezza dell'ID (caratteri esadecimali) |
|---|---|---|
| `example_uids_em4100.txt` | EM4100 | 10 (5 byte) |
| `example_uids_h10301.txt` | HID H10301 | 6 (3 byte) |
| `example_uids_hidprox.txt` | HIDProx | 12 (6 byte) |
| `example_uids_pac.txt` | PAC/Stanley | 8 (4 byte) |

Formato — un ID esadecimale per riga, `#` per i commenti e una **riga vuota alla fine** del file:

```text
# Example file, P.S. keep empty line at the end!
0000000000
FE00000000
CAFE000000
00CAFE0000

```

Crea un elenco personale copiando uno degli esempi e sostituendo gli ID; la lunghezza dell'ID deve corrispondere alla
dimensione della chiave del protocollo (vedi [protocolli](/it/rfid/protocols), colonna *Byte*).

Le FAQ di Unleashed segnalano file di dizionario già pronti condivisi dalla comunità:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058) e
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Usa il fuzzer solo su lettori di tua proprietà o che sei autorizzato a testare.
:::

## Pagine correlate

- [Protocolli](/it/rfid/protocols) · [Lettura](/it/rfid/read) · [Fuzzer iButton](/it/ibutton/fuzzer)
