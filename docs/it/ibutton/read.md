---
title: Lettura delle chiavi
order: 10
original: [https://docs.flipper.net/zero/ibutton/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols]
sources: [unleashed-src, flipper-docs]
---
# Leggere, salvare ed emulare chiavi iButton

Flipper Zero legge le chiavi Dallas 1-Wire (l'ID e, per le chiavi con memoria, il contenuto della memoria), le chiavi
Cyfral e Metakom, e può poi salvarle ed emularle.

| Chiave | Cosa viene letto |
|---|---|
| Dallas **DS1990** / **DS1420** | solo la ROM da 8 byte (l'ID) — la chiave non ha memoria |
| Dallas **DS1992** | ROM + 128 byte di SRAM |
| Dallas **DS1996** | ROM + 8192 byte di SRAM |
| Dallas **DS1971** | ROM + 32 byte di EEPROM |
| Altri dispositivi 1-Wire | solo la ROM, mostrati come **Dallas (non-specific)** |
| **Cyfral** | codice da 2 byte |
| **Metakom** | codice da 4 byte |

## Leggere una chiave

1. Vai su `Main Menu → iButton → Read`. Lo schermo mostra **Reading — Connect key with pogo pins**.

   ![Schermata di lettura con l'invito "Connect key with pogo pins"](/screens/ibutton/read.png)

2. Appoggia la chiave alla **parte piatta** della piazzola iButton in modo che il suo centro tocchi il **pin dati di
   sinistra** e la sua corona il **pin di massa centrale**. Tienila ferma.
3. Quando la chiave è stata letta, il Flipper emette un bip e mostra il protocollo (per esempio **Dallas DS1990**) e
   il suo ID.

   ![Risultato della lettura: Dallas DS1990 con l'ID da otto byte e il family code, Retry e More in basso](/screens/ibutton/read_success.png)

4. Pulsanti: <kbd>←</kbd> **Retry**, <kbd>→</kbd> **More**. <kbd>Back</kbd> chiede *Exit to iButton Menu? All unsaved
   data will be lost!*

**More** propone (le voci dipendono dal protocollo):

| Voce | Quando appare | Azione |
|---|---|---|
| **Save** | sempre | Assegna un nome alla chiave, salvata in `/ext/ibutton/<name>.ibtn` |
| **Emulate** | sempre | Emula subito |
| **Write ID** | protocolli scrivibili | Scrive l'ID su una vergine — [Scrittura](/it/ibutton/write) |
| **Full Write on Same Type** | DS1992, DS1996, DS1971 | Copia la memoria su una chiave dello stesso tipo |
| **Data Info** | DS1992, DS1996, DS1971 | Mostra il dump della memoria |

## Errori di lettura

Se i dati non superano il controllo previsto dal protocollo, la schermata di errore ne spiega il motivo e offre
comunque **Retry** e **More**:

- **CRC Error** (Dallas) — l'ottavo byte della ROM è un CRC sui primi sette; la schermata mostra la ROM con il byte
  errato evidenziato e l'*Expected CRC*. Di solito si tratta di un contatto imperfetto: pulisci la chiave e rileggila.
  Se l'errore si ripete, puoi comunque salvarla e provare a emularla — alcuni lettori ignorano il CRC. Se l'emulazione
  non funziona, l'errore non è correggibile.
- **Invalid Metakom key: odd parity in byte N** — un byte Metakom non ha superato il controllo di parità; rileggi la
  chiave.

## Chiavi salvate

`Main Menu → iButton → Saved` apre `/ext/ibutton/`. Il menu di una chiave:

| Voce | Azione |
|---|---|
| **Emulate** | Emula verso un lettore |
| **Write ID** | Scrive l'ID su una vergine |
| **Full Write on Same Type** | solo DS1992/DS1996/DS1971 — copia la memoria |
| **Edit** | Modifica l'ID in esadecimale, poi salva con un nome |
| **Rename** / **Delete** | Gestisce il file |
| **Info** | Nome, protocollo, ID; <kbd>→</kbd> **More** mostra i dati di memoria per le chiavi con memoria |

## Emulazione

1. Apri una chiave salvata → **Emulate** (oppure **More → Emulate** subito dopo la lettura). Lo schermo mostra
   **Emulating**, `[Protocol]` e il nome della chiave (o *Unsaved Key*).

   ![Schermata di emulazione con "Emulating", il protocollo [DS1990] e il nome della chiave](/screens/ibutton/emulate.png)

2. Premi la **parte sporgente** della piazzola contro il lettore: il **pin dati di destra** deve toccare il centro del
   lettore, il **pin di massa centrale** la sua corona.
3. Se il pin di massa non raggiunge la corona, collega due fili: GPIO **17** → centro del lettore, GPIO
   **8 / 11 / 18** (GND) → corona.

## CLI

```text
ikey read
ikey emulate <key_type> <key_data>
ikey write Dallas <key_data>
	<key_type>: Dallas (8 bytes), Cyfral (2 bytes), Metakom (4 bytes, must contain correct parity)
	<key_data> is hex
```

## Risoluzione dei problemi

- **Non accade nulla.** La chiave non tocca entrambi i pin — inclinala in modo che la corona tocchi il pin di massa.
- **Chiave non supportata.** Può usare un protocollo non supportato (oppure essere un portachiavi RFID — prova con
  [RFID 125 kHz](/it/rfid/read)).
- **Emulazione rifiutata.** Controlla il contatto dei pin; alcuni lettori riconoscono gli emulatori o verificano cose
  che il Flipper non può simulare. Se hai modificato o aggiunto la chiave a mano, ricontrolla l'ID.

## Pagine correlate

- [Scrittura](/it/ibutton/write) · [Aggiunta manuale](/it/ibutton/add-manually) ·
  [Protocolli](/it/ibutton/protocols) · [Formato dei file](/it/ibutton/file-format)
