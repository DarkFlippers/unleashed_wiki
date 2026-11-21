---
title: Unit test
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UnitTests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests]
sources: [unleashed-docs, unleashed-src]
---
# Unit test

Gli unit test forniscono input noti al codice di una funzionalità e verificano che i risultati siano corretti. Sono
essenziali per avere codice robusto e privo di bug.

Il firmware contiene un'app a sé, **`unit_tests`** (`applications/debug/unit_tests`), che viene eseguita **sul
Flipper stesso** — così i test usano l'hardware reale ed escludono differenze legate alla piattaforma.

Quando contribuisci al firmware, accompagna con unit test le nuove funzionalità ove possibile ed esegui quelli
esistenti per assicurarti che la tua modifica non introduca regressioni.

## Eseguire i test

1. **Compila il firmware con l'insieme di app dei test:**

   ```sh
   ./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests updater_package
   ```

   ::: warning `DEBUG=0` è obbligatorio
   `fbt_options.py` imposta per impostazione predefinita `DEBUG=1`, e un'immagine di debug non entra più sotto la
   regione di flash dello stack radio — l'impacchettamento si interrompe con
   `Firmware image overlaps C2 region and is not programmable!`. A partire dall'API 88.23 un'immagine di debug è
   grande circa 7 KB in eccesso per questo insieme di app (10 KB per quello predefinito), quindi ridurre i test non
   serve. (`COMPACT=1` è già il valore predefinito; è indicato esplicitamente per uniformità con gli altri comandi.)

   Tieni presente che `DEBUG=0` elimina in compilazione `furi_assert()`, quindi le asserzioni nel codice sotto test
   non scatteranno. `furi_check()` e le asserzioni di minunit non ne sono influenzate.
   :::

   L'insieme di app `unit_tests` comprende: `basic_services`, `updater_app`, `radio_device_cc1101_ext`,
   `unit_tests`, `infrared`, `archive`.

2. **Flasha il firmware comprese le risorse per la scheda SD** (`build/latest/resources`) — per esempio installa con
   qFlipper il `.tgz` generato in `dist/`, oppure usa
   `./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests flash_usb_full`. Gli asset dei test devono finire sulla
   scheda SD.
3. **Apri una sessione [CLI](/it/dev/cli)** ed esegui:

   ```
   unit_tests
   ```

**Risultato atteso:** le suite vengono eseguite una dopo l'altra, poi compare un rapporto come questo:

```
Tests run: …, asserts: …
Failed tests: 0
Consumed: … ms
Leaked: …
```

Se compare `Cannot open /ext/apps_data/unit_tests/plugins - are the SD card resources deployed?`, le risorse per la
scheda SD non sono state installate — ripeti il passo 2 includendo le risorse.

Per eseguire **un solo** test e saltare gli altri, passane il nome:

```
unit_tests test_infrared
```

Le altre suite vengono saltate (`Skipping …`); un nome errato produce `No suite named …`. I nomi dei test
corrispondono agli ID delle app (`test_furi`, `test_storage`, `test_subghz`, `test_infrared`, `test_nfc`,
`test_lfrfid`, …) definiti in
[`applications/debug/unit_tests/application.fam`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/application.fam).

::: info
Questa è una build speciale del firmware, priva delle app consuete. Reinstalla una build normale quando hai finito.
:::

## Aggiungere unit test

### Punto di ingresso

Tutti i test vengono eseguiti dall'app "madre" `unit_tests`. Il codice dei test è impacchettato come app di tipo
`PLUGIN` in una sottodirectory di `tests/` all'interno di `unit_tests`, ed è indicato nell'`application.fam` comune.
Copia la struttura di un test esistente.

### Asset dei test

Alcuni test hanno bisogno di dati esterni ("asset"). Risiedono in
[`applications/debug/unit_tests/resources/unit_tests`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests),
ciascuno nella propria sottodirectory. Gli asset possono essere di qualunque tipo: testo semplice, Flipper Format
(FFF), binario, ecc.

### Esempio: protocolli infrarossi

Ogni protocollo infrarossi ha un insieme di unit test, quindi aggiungine uno quando aggiungi un nuovo protocollo:

1. Crea `test_<your_protocol_name>.irtest` nella
   [directory degli asset infrarossi](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests/infrared).
2. Riempilo con i dati di test (vedi sotto).
3. Aggiungi il codice del test a
   [`infrared_test.c`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/tests/infrared/infrared_test.c).
4. Compila e installa il firmware con le risorse, poi esegui i test e verifica che passino.

#### Formato dei dati di test

Ogni test infrarossi ha tre sezioni:

| Sezione | Cosa fa |
|---|---|
| `decoder` | Prende un segnale grezzo e produce messaggi decodificati |
| `encoder` | Prende messaggi decodificati e produce un segnale grezzo |
| `encoder_decoder` | Codifica messaggi decodificati in forma grezza, poi li decodifica di nuovo |

I file `.irtest` sono normali [file `.ir`](/it/infrared/file-format) con qualche aggiunta:

- i segnali di ingresso del decoder si chiamano `decoder_input_N` (N = numero della sequenza di test), l'output
  atteso `decoder_expected_N`;
- per i test dell'encoder i due sono scambiati;
- i dati decodificati sono un **array**, perché un singolo segnale grezzo può decodificarsi in più messaggi — un
  singolo messaggio è un array di dimensione 1.

Usa i file `.irtest` esistenti come esempi di sintassi.

#### Registrare segnali grezzi

Apri una sessione CLI ed esegui:

```
ir rx raw
```

Punta il telecomando verso il Flipper e premi i pulsanti. I dati grezzi vengono stampati in un formato pronto
all'uso.

## Pagine correlate

- [Test di integrazione](/it/dev/testing)
- [Flipper Build Tool (fbt)](/it/dev/fbt)
- [Interfaccia a riga di comando](/it/dev/cli)
