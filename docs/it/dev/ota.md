---
title: Aggiornamenti OTA
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/OTA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/update.py]
sources: [unleashed-docs, unleashed-src]
---
# Il processo di aggiornamento OTA

Come il Flipper installa un pacchetto di aggiornamento — cosa accade in ogni fase, cosa contiene il manifest
dell'aggiornamento, cosa significano i codici di errore `[XX-YY]` e come creare pacchetti propri.

Per il lato utente (installare Unleashed con qFlipper, il web installer o dalla scheda SD) vedi
[Aggiornamento](/it/start/updating). Se un aggiornamento fallisce gravemente, vedi
[Ripristino](/it/start/recovery).

## Eseguire codice dalla RAM

Il firmware ha una modalità di avvio speciale che carica in **RAM** un'immagine di sistema appositamente costruita e
le passa il controllo. Il codice eseguito dalla RAM ha pieno accesso in scrittura a tutta la flash — cosa impossibile
mentre il firmware principale è in esecuzione da quella stessa flash. L'updater OTA usa questa modalità, anche per
aggiornare lo stack radio sul secondo core dell'MCU.

## Le tre fasi

### 1. Backup della memoria interna (`/int`)

`/int` è una partizione della flash del Flipper che occupa tutto lo spazio non usato dal firmware. Un nuovo firmware
può avere dimensioni diverse, quindi installarlo ripartizionerebbe la flash perdendo i dati. Perciò, prima di
qualunque altra cosa, il contenuto corrente di `/int` viene salvato in un semplice archivio `.tar` sulla scheda SD.

### 2. Aggiornamento del dispositivo

Il firmware principale carica in RAM l'**updater** — una build personalizzata del firmware — e lo esegue. L'updater
opera sulla flash di sistema secondo quanto descritto dal manifest dell'aggiornamento:

1. Se il pacchetto contiene un'immagine dello **stack radio**, la sua versione viene confrontata con quella
   installata. Se differiscono, il vecchio stack viene disinstallato e il nuovo scritto e installato.
   L'installazione è eseguita dal **FUS** proprietario di ST in esecuzione su Core2 e comporta diversi riavvii.
2. Gli **Option Bytes** (configurazione di basso livello dell'MCU) vengono validati e corretti.
3. Il file `.dfu` del firmware viene caricato, la sua integrità verificata con CRC32, scritto in flash e
   controllato.

### 3. Ripristino della memoria interna e aggiornamento delle risorse

Il sistema riparte con il nuovo firmware, ripristina il contenuto di `/int` salvato e, se il pacchetto contiene un
archivio di risorse, lo estrae sulla scheda SD.

## Manifest dell'aggiornamento

Ogni pacchetto è accompagnato da un manifest (il file `.fuf`) in Flipper File Format — un file di testo semplice con
coppie chiave-valore.

### Campi obbligatori (in questo ordine)

| Chiave | Significato |
|---|---|
| `Filetype` | Stringa costante `Flipper firmware upgrade configuration` |
| `Version` | Versione del manifest, attualmente `2` |
| `Info` | Descrizione libera del pacchetto |
| `Target` | Revisione hardware per cui è stato creato il pacchetto |
| `Loader` | Nome del file del loader di secondo stadio eseguito dalla RAM |
| `Loader CRC` | CRC32 del file del loader, in esadecimale **little-endian** |

### Campi facoltativi

Possono essere vuoti — l'updater salta allora le operazioni corrispondenti.

| Chiave | Significato |
|---|---|
| `Radio` | Nome del file dell'immagine dello stack radio (fornita da ST) |
| `Radio address` | Indirizzo in cui installare lo stack radio (dalle release note di ST) |
| `Radio version` | Versione major, minor, sub, branch, release e tipo di stack, impacchettati in 6 byte esadecimali |
| `Radio CRC` | CRC32 dell'immagine radio |
| `Resources` | Nome del file dell'archivio con le risorse per la scheda SD — `resources.ths`, un tarball compresso con heatshrink (vedi [Formato tarball heatshrink](/it/dev/tar-heatshrink)) |
| `OB reference`, `OB mask`, `OB write mask` | Valori di riferimento per validare e correggere gli option bytes |

## Codici di errore

Il processo è progettato per essere il più possibile a prova di guasto: nessuna operazione rischiosa inizia prima che
tutti i dati correlati siano stati validati, così il dispositivo non resta aggiornato a metà né inutilizzabile. Se
qualcosa va storto, l'updater permette di riprovare e mostra un codice di errore `[XX-YY]`: `XX` è l'operazione
fallita, `YY` lo stato di avanzamento o il dettaglio in cui è fallita.

| Fase | XX | YY | Significato |
|---|--:|---|---|
| Caricamento del manifest di aggiornamento | **1** | **13** | L'updater ha segnalato una versione hardware non corrispondente |
| | | **20** | Impossibile ottenere il percorso del manifest salvato |
| | | **30** | Caricamento del manifest fallito |
| | | **40** | Versione del pacchetto di aggiornamento non supportata |
| | | **50** | Il pacchetto ha un target hardware non corrispondente |
| | | **60** | File DFU mancante |
| | | **80** | File del firmware radio mancante |
| Backup della configurazione | **2** | **0-100** | Errore di lettura/scrittura sul filesystem |
| Verifica del firmware radio | **3** | **0-99** | Errore nella lettura del file del firmware radio |
| | | **100** | CRC non corrispondente |
| Disinstallazione del firmware radio | **4** | **0** | Errore nel comando SHCI Delete |
| | | **80** | Errore nell'attesa dello stato del comando |
| Scrittura del firmware radio | **5** | **0-100** | Errore di lettura/scrittura di un blocco |
| Installazione del firmware radio | **6** | **10** | Errore nel comando SHCI Install |
| | | **80** | Errore nell'attesa dello stato del comando |
| Core2 occupato | **7** | **10** | Impossibile avviare C2 |
| | | **20** | Passaggio di C2 in modalità FUS fallito |
| | | **30** | Errore in un'operazione FUS |
| | | **50** | Passaggio di C2 in modalità stack fallito |
| Validazione degli option bytes | **8** | **yy** | Codice dell'option byte |
| Verifica del file DFU | **9** | **0** | Errore nell'apertura del file DFU |
| | | **1-98** | Errore nella lettura del file DFU |
| | | **99-100** | File DFU corrotto |
| Scrittura della flash | **10** | **0-100** | Errore di lettura/scrittura di un blocco |
| Validazione della flash | **11** | **0-100** | Errore di lettura/scrittura di un blocco |
| Ripristino della configurazione | **12** | **0-100** | Errore di lettura/scrittura sul filesystem |
| Aggiornamento delle risorse | **13-15** | **0-100** | Errore di lettura/scrittura sulla scheda SD |

::: tip Cosa fare in caso di errore
- **1-50 / 1-13** — il pacchetto è per un altro target hardware: scarica quello giusto.
- **2, 12, 13-15** — problema con la scheda SD: controllala o riformattala, poi copia di nuovo il pacchetto.
- **3-100, 9-99/100** — file corrotti: riscarica il pacchetto.
- Prima di tutto riprova — l'updater è pensato per questo. Se il Flipper non si avvia più, usa
  [Ripristino](/it/start/recovery).
:::

## Creare pacchetti di aggiornamento

Assicurati di passare `DEBUG=0` — vedi [Compilare il firmware](/it/dev/build).

**Pacchetto completo** — firmware, stack radio e risorse per la scheda SD:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

**Pacchetto minimo** — solo firmware:

```sh
./fbt COMPACT=1 DEBUG=0 updater_minpackage
```

Il risultato si trova in `dist/<target>-<cfg>/` come cartella `f7-update-<suffix>` e come
`flipper-z-f7-update-<suffix>.tgz`.

### Scegliere uno stack radio diverso

I pacchetti usano per impostazione predefinita lo stack **Bluetooth Light**. Se il tuo firmware supporta un altro
stack, passane il tipo e il binario:

```sh
./fbt updater_package COMPACT=1 DEBUG=0 COPRO_OB_DATA=scripts/ob_custradio.data COPRO_STACK_BIN=stm32wb5x_BLE_Stack_full_fw.bin COPRO_STACK_TYPE=ble_full
```

`COPRO_OB_DATA` deve puntare a un file in `scripts/` con i dati di riferimento degli Option Byte corrispondenti a
quel tipo di stack. In alcuni casi devi anche confermare con `COPRO_DISCLAIMER=...` sulla riga di comando.

### Pacchetti parziali

Chiama direttamente `scripts/update.py` per contenuti personalizzati. Per esempio, un pacchetto che installa
soltanto lo stack BLE FULL:

```shell
scripts/update.py generate \
  -t f7 -d r13.3_full -v "BLE FULL 13.3" \
  --stage dist/f7/flipper-z-f7-updater-*.bin \
  --radio lib/stm32wb_copro/firmware/stm32wb5x_BLE_Stack_full_fw.bin \
  --radiotype ble_full
```

Vedi `scripts/update.py generate --help` per tutte le opzioni.

## Installare un pacchetto dalla CLI

Copia la cartella del pacchetto scompattato sulla scheda SD ed esegui:

```
update install /ext/update/f7-update-local/update.fuf
```

La [CLI](/it/dev/cli#update) offre anche `update backup` e `update restore` per la memoria interna.

## Pagine correlate

- [Aggiornare il firmware](/it/start/updating)
- [Ripristino](/it/start/recovery)
- [Formato tarball heatshrink](/it/dev/tar-heatshrink)
- [Flipper Build Tool (fbt)](/it/dev/fbt)
