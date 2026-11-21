---
title: Fuzzer iButton
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/ibtnfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# Fuzzer iButton

Un **fuzzer** emula una serie di ID di chiave uno dopo l'altro per osservare come reagisce un lettore — per esempio
per verificare se il tuo citofono accetta ID predefiniti o malformati.

::: tip Unleashed
Il ReadMe di Unleashed elenca i **plugin LFRFID e iButton Fuzzer**. Il fuzzer è un'app esterna, non fa parte
dell'albero dei sorgenti del firmware: pacchetti di app precompilate vengono aggiunti alle build di release, e
l'**extra apps pack** pubblicato con ogni release contiene tutte le app funzionanti conosciute. I suoi menu dipendono
dalla versione dell'app, quindi non sono descritti qui.
:::

## Cosa fornisce il firmware: elenchi di UID di esempio

Il firmware installa alcuni elenchi di ID di esempio in **`/ext/ibtnfuzzer/`**:

| File | Protocollo | Lunghezza dell'ID (caratteri esadecimali) |
|---|---|---|
| `example_uids_ds1990.txt` | Dallas DS1990 | 16 (8 byte) |
| `example_uids_cyfral.txt` | Cyfral | 4 (2 byte) |
| `example_uids_metakom.txt` | Metakom | 8 (4 byte) |

Formato — un ID esadecimale per riga, `#` per i commenti, e va mantenuta una **riga vuota alla fine**:

```text
# Example file, P.S. keep empty line at the end!
0000000000000000
FE00000000000000
CAFE000000000000
00CAFE0000000000

```

Per creare un elenco personale, copia un esempio e sostituisci gli ID; la lunghezza deve corrispondere al protocollo.

Dizionari della comunità segnalati nelle FAQ di Unleashed:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058),
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Usa il fuzzer solo su lettori di tua proprietà o che sei autorizzato a testare.
:::

## Pagine correlate

- [Protocolli](/it/ibutton/protocols) · [Emulazione delle chiavi](/it/ibutton/read) ·
  [Fuzzer RFID](/it/rfid/fuzzer)
