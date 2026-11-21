---
title: Interfaccia a riga di comando (CLI)
order: 100
original: [https://docs.flipper.net/zero/development/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/toolbox/cli]
sources: [flipper-docs, unleashed-src]
---
# Interfaccia a riga di comando (CLI)

Il Flipper espone una console testuale tramite la seriale USB. Da essa puoi leggere e inviare segnali, eseguire app,
gestire file, osservare i log, controllare GPIO e LED, chattare con altri Flipper via Sub-GHz e molto altro — comoda
per scripting, debug e sviluppo di app.

## Collegarsi alla CLI

::: warning Chiudi prima qFlipper
Solo un programma alla volta può usare la porta seriale del Flipper. Chiudi **qFlipper** (e chiudi Flipper Lab o
altri terminali) prima di collegarti.
:::

La velocità della seriale è **230400** baud (per USB CDC il valore viene in gran parte ignorato, ma alcuni terminali
richiedono di impostarlo).

### Opzione 1: Flipper Lab (browser)

Funziona in Chrome, Edge o un altro browser Chromium con supporto a Web Serial.

1. Collega il Flipper via USB.
2. Apri [lab.flipper.net](https://lab.flipper.net/) → **CLI**.

### Opzione 2: terminale seriale web (browser)

1. Collega il Flipper via USB e apri un browser Chromium.
2. Vai al [terminale seriale web](https://googlechromelabs.github.io/serial-terminal/).
3. Imposta **Baud rate** su **230400**, fai clic su **Connect**, seleziona il tuo Flipper, fai clic su **Connect**.

### Opzione 3: terminale seriale — macOS

1. Individua la porta:

   ```sh
   ls /dev/cu.*
   ```

   Il Flipper compare come `/dev/cu.usbmodemflip_NAME`, dove `NAME` è il nome del tuo Flipper.
2. Collegati con **screen**:

   ```sh
   screen /dev/cu.usbmodemflip_NAME
   ```

   Per uscire: <kbd>Ctrl</kbd>+<kbd>A</kbd>, poi <kbd>K</kbd>, poi <kbd>Y</kbd>.
3. …oppure con **minicom** (installalo con [Homebrew](https://brew.sh/): `brew install minicom`):

   ```sh
   minicom -D /dev/cu.usbmodemflip_NAME
   ```

   Per uscire: <kbd>Esc</kbd>+<kbd>Z</kbd>, poi <kbd>X</kbd>, poi <kbd>Return</kbd>.

### Opzione 3: terminale seriale — Linux

1. Individua la porta:

   ```sh
   ls /dev/serial/by-id/
   ```

   Cerca `usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00`. Se hai un solo dispositivo seriale, di solito è
   anche `/dev/ttyACM0`; anche qFlipper mostra il nome della porta.
2. Collegati:

   ```sh
   screen /dev/serial/by-id/usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00
   # or
   minicom -D /dev/ttyACM0
   ```

   Per uscire da screen: <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>K</kbd>, <kbd>Y</kbd>. Per uscire da minicom:
   <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>X</kbd>, <kbd>Return</kbd>.

::: tip
Se su Linux ottieni "permission denied", aggiungiti al gruppo `dialout` (o `uucp` su alcune distribuzioni) ed esegui
di nuovo l'accesso.
:::

### Opzione 3: terminale seriale — Windows

1. Installa [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Collega il Flipper; in **Device Manager → Ports (COM & LPT)** annota la sua porta COM (scollega e ricollega per
   capire quale compare).
3. In PuTTY scegli **Connection type: Serial**, **Serial line**: per esempio `COM3`, **Speed**: `230400`, poi fai
   clic su **Open**.

### Dall'albero del firmware

Se hai i sorgenti del firmware, `./fbt cli` apre direttamente una sessione CLI; con uFBT usa `ufbt cli`.

**Risultato atteso:** un banner ASCII art del Flipper, "Welcome to Flipper Zero Command Line Interface!", la riga
con la versione del firmware e un prompt `>:`.

## Comandi integrati ed esterni

Esegui `help` o `?` per elencare i comandi disponibili sul tuo dispositivo.

::: tip Unleashed / nuova architettura della CLI
La maggior parte dei comandi radio e per le periferiche (`subghz`, `nfc`, `ir`, `rfid`, `ikey`, `onewire`, `bt`,
`crypto`, `js`, `gpio`, `led`, `vibro`, `buzzer`, `i2c`, `neofetch`, …) sono **plugin CLI esterni** caricati dalla
cartella `/ext/apps_data/cli/plugins` della scheda SD (file con il prefisso `cli_`). Senza scheda SD — o con una
danneggiata — restano solo i comandi di base. Dopo aver copiato o aggiornato i plugin, esegui `reload_ext_cmds`
invece di riavviare.
:::

### Panoramica dei comandi

| Comando | Descrizione |
|---|---|
| `!` | Alias di `info device` |
| `?`, `help` | Elenca i comandi disponibili |
| `bt` | Strumento di test del core radio (BLE) — versione HCI e, in modalità debug, test di portante/pacchetti |
| `buzzer` | Riproduce un tono o una nota sull'altoparlante piezo |
| `crypto` | Provisioning delle chiavi nel secure enclave e cifratura/decifratura AES |
| `date` | Mostra / imposta data e ora |
| `device_info` | Alias di `info device` (obsoleto) |
| `echo` | Rimanda indietro i byte ricevuti così come sono (usato per test di prestazioni); si interrompe con <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `exit` | Esce dalla shell (utile nelle sotto-shell come `nfc`) |
| `factory_reset` | Ripristina le impostazioni di fabbrica; i dati sulla scheda microSD vengono conservati |
| `free` | Informazioni sull'allocatore dell'heap — profilazione generale della memoria |
| `free_blocks` | Blocchi liberi dell'heap e loro dimensioni — per stimare la frammentazione |
| `gpio` | Imposta la modalità / scrive / legge i pin GPIO |
| `i2c` | Scansiona il bus I2C in cerca di dispositivi |
| `ikey` | Legge, emula e scrive chiavi iButton |
| `info` | Informazioni dettagliate su dispositivo e alimentazione |
| `input` | Mostra gli eventi dei pulsanti, inietta pressioni di pulsanti |
| `ir` | Riceve, invia e decodifica segnali infrarossi; telecomandi universali |
| `js` | Esegue un file JavaScript, l'output della console va alla CLI |
| `led` | Controlla il LED RGB e la retroilluminazione del display |
| `loader` | Elenca, apre e chiude le app |
| `log` | Mostra il log di sistema |
| `neofetch` | Informazioni di sistema, come `neofetch` su Linux |
| `nfc` | Sotto-shell NFC: dump, emulazione, raw, APDU, scanner |
| `onewire` | Scansiona il bus 1-Wire (pin iButton) |
| `power` | Spegnimento, riavvio, riavvio in DFU, 5 V / 3,3 V sui GPIO |
| `reload_ext_cmds` | Ricarica l'elenco dei comandi esterni dalla scheda SD |
| `rfid` | Legge, scrive ed emula tessere a 125 kHz; strumenti RAW |
| `sleep` | Attende per un dato tempo, per esempio `sleep 5s` (utile negli script) |
| `start_rpc_session` | Passa la CLI in modalità RPC protobuf (usata da qFlipper e dalle app; normalmente non serve) |
| `storage` | Comandi per il filesystem |
| `subghz` | Strumenti Sub-GHz: rx/tx, RAW, decodifica, chat |
| `sysctl` | Impostazioni di sistema: modalità debug, tracciamento dell'heap |
| `top` | Elenco in tempo reale dei thread (come il `top` di Linux); <kbd>Ctrl</kbd>+<kbd>C</kbd> per uscire |
| `update` | Installa un pacchetto di aggiornamento, salva / ripristina la memoria interna |
| `uptime` | Tempo trascorso dall'ultimo avvio |
| `vibro` | Accende/spegne il motore di vibrazione |
| `unit_tests` | Solo nella build `unit_tests` del firmware — vedi [Unit test](/it/dev/unit-tests) |

## Lettura dei log {#reading-logs}

1. Collegati alla CLI.
2. Avvia la registrazione al livello che ti serve:

   | Comando | Mostra |
   |---|---|
   | `log` | Il livello corrente dalle impostazioni di sistema |
   | `log error` | Solo errori critici e messaggi importanti |
   | `log warn` | Avvisi ed errori non critici, più `error` |
   | `log info` | Informazioni non critiche, più `warn` |
   | `log default` | Il livello predefinito di sistema (= `info`) |
   | `log debug` | Informazioni di debug, più `info` (influisce sulle prestazioni) |
   | `log trace` | Tracce di sistema, più `debug` (influisce sulle prestazioni) |

   `log ?` stampa questo elenco sul dispositivo.
3. Usa il Flipper — i messaggi compaiono nel terminale.
4. Interrompi con <kbd>Ctrl</kbd>+<kbd>C</kbd>.

## Chattare via Sub-GHz

Più Flipper sulla stessa frequenza possono chattare attraverso la CLI.

1. Ogni partecipante si collega alla CLI del proprio Flipper.
2. Esegui `subghz chat <frequency_in_hz> <device>`, per esempio:

   ```
   subghz chat 868150000 0
   ```

   - frequenza in Hz entro 299999755–348000000, 386999938–464000000 o 778999847–928000000;
   - device `0` = CC1101 interno, `1` = modulo CC1101 esterno.
3. Digita un messaggio e premi <kbd>Enter</kbd>.
4. Esci con <kbd>Ctrl</kbd>+<kbd>C</kbd>.

::: tip Unleashed
Il firmware di serie trasmette solo sulle frequenze consentite nella tua regione; Unleashed rimuove le restrizioni
regionali sulla trasmissione. Rispetta le normative radio locali.
:::

## Riferimento dei comandi

### bt

| Comando | Descrizione |
|---|---|
| `bt hci_info` | Informazioni HCI del Bluetooth |
| `bt tx_carrier <channel:0-39> <power:0-6>` | *Solo in modalità debug.* Avvia il test della portante in TX |
| `bt rx_carrier <channel:0-39>` | *Solo in modalità debug.* Avvia il test della portante in RX |
| `bt tx_packet <channel:0-39> <pattern:0-5> <datarate:1-2>` | *Solo in modalità debug.* Avvia il test dei pacchetti in TX |
| `bt rx_packet <channel:0-39> <datarate:1-2>` | *Solo in modalità debug.* Avvia il test dei pacchetti in RX |

### buzzer

| Comando | Descrizione |
|---|---|
| `buzzer freq <frequency_in_hz> <duration>` | Riproduce un tono |
| `buzzer note <note> <duration>` | Riproduce una nota; `s` indica il diesis, per esempio `cs3` = Do♯3; i bemolle non sono supportati |

La durata accetta `ms`, `s`, `m`, `h`, per esempio `buzzer note cs3 500ms`.

### crypto

Cifra e decifra con chiavi conservate nel secure enclave dell'MCU.

| Comando | Descrizione |
|---|---|
| `crypto encrypt <key_slot> <iv_hex>` | Cifra del testo con AES256-CBC, output in esadecimale |
| `crypto decrypt <key_slot> <iv_hex>` | Decifra l'esadecimale riportandolo a testo |
| `crypto has_key <key_slot>` | Verifica se uno slot (1–100) contiene una chiave |
| `crypto store_key <key_slot> <key_type> <key_size> <key_data_hex>` | **Irreversibile!** Memorizza una chiave — non può essere rimossa |

- `key_slot`: gli slot 1–11 sono precaricati con chiavi usate dal firmware.
- `iv_hex`: vettore di inizializzazione di 16 byte in esadecimale.
- `key_type`: `master`, `simple` o `encrypted`; `key_size`: `128` o `256`.

### gpio

| Comando | Descrizione |
|---|---|
| `gpio mode <pin_name> <0/1>` | Imposta il pin come ingresso (0) o uscita (1) |
| `gpio set <pin_name> <0/1>` | Imposta il valore del pin |
| `gpio read <pin_name>` | Legge il valore del pin |

Nomi dei pin: `PA7`, `PA6`, `PA4`, `PB3`, `PB2`, `PC3`, `PC1`, `PC0` — vedi [pinout GPIO](/it/gpio/pinout).

### ikey

| Comando | Descrizione |
|---|---|
| `ikey read` | Legge una chiave iButton |
| `ikey emulate <key_type> <key_data>` | Emula una chiave |
| `ikey write Dallas <key_data>` | Scrive 8 byte su una vergine compatibile Dallas |

Tipi di chiave e lunghezza dei dati (esadecimale): `Dallas` — 8 byte, `Cyfral` — 2 byte, `Metakom` — 4 byte (deve
contenere la parità corretta).

### info

| Comando | Descrizione |
|---|---|
| `info device` | Informazioni sul dispositivo (firmware, hardware, stack radio, …) |
| `info power` | Informazioni sul sistema di alimentazione |
| `info power_debug` | Informazioni dettagliate sull'alimentazione |

### input

| Comando | Descrizione |
|---|---|
| `input dump` | Stampa gli eventi dei pulsanti |
| `input send <key> <type>` | Inietta un evento; `key`: `up`, `down`, `left`, `right`, `back`, `ok`; `type`: `press`, `release`, `short`, `long` |

Una pressione breve completa richiede tre comandi, altrimenti l'input viene scartato:

```
input send ok press
input send ok short
input send ok release
```

Per una pressione prolungata usa `long` invece di `short`.

### ir

| Comando | Descrizione |
|---|---|
| `ir rx` | Riceve e decodifica segnali IR |
| `ir rx raw` | Riceve in formato RAW |
| `ir tx <protocol> <address> <command>` | Invia un comando; indirizzo e comando in esadecimale |
| `ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...` | Invia dati RAW: frequenza 10000–56000, duty cycle 0–100, massimo 512 campioni |
| `ir decode <input_file> [<output_file>]` | Decodifica un file con segnali RAW |
| `ir universal list <remote_name>` | Elenca i segnali di un telecomando universale |
| `ir universal <remote_name> <signal_name>` | Invia un segnale di un telecomando universale |

Protocolli: `NEC`, `NECext`, `NEC42`, `NEC42ext`, `Samsung32`, `RC6`, `RC5`, `RC5X`, `SIRC`, `SIRC15`, `SIRC20`,
`Kaseikyo`, `RCA`, `Pioneer`.

::: tip Unleashed
I nomi dei telecomandi universali provengono dai file in `/ext/infrared/assets/`. Unleashed include `tv`, `audio`,
`ac`, `projectors`, `fans` e `leds` (il firmware di serie ne ha meno). Esegui `ir universal list tv` per vedere i
nomi di segnale validi.
:::

### js

| Comando | Descrizione |
|---|---|
| `js <path>` | Esegue un file JavaScript e stampa l'output della sua console — vedi [JavaScript](/it/dev/js-about) |

### led

| Comando | Descrizione |
|---|---|
| `led r <0-255>` / `led g <0-255>` / `led b <0-255>` | Luminosità della componente rossa / verde / blu del LED |
| `led bl <0-255>` | Luminosità della retroilluminazione del display (`128` ≈ 50%) |

Per un rosso puro: `led r 255`, `led g 0`, `led b 0`.

### loader

| Comando | Descrizione |
|---|---|
| `loader list` | Elenca le app disponibili |
| `loader open <Application Name> [args]` | Apre un'app per nome, con argomenti facoltativi |
| `loader info` | Mostra lo stato del loader |
| `loader close` | Chiude l'app in esecuzione |
| `loader signal <signal> [arg_hex]` | Invia un segnale con un argomento esadecimale facoltativo |

Gli argomenti che contengono spazi possono essere racchiusi tra apici:

```
loader open subghz "/ext/subghz/Some File.sub"
```

### nfc

`nfc` apre una **sotto-shell**. Al suo interno: `help` / `?` elenca i comandi, `<command> -h` mostra i dettagli,
`exit` esce.

| Comando | Descrizione |
|---|---|
| `dump -f <path>` | Esegue il dump di una tessera fisica in un file `.nfc`. Opzioni: `-k <key>`, `-p <protocol>`, `-t <timeout_ms>` |
| `emulate -f <path>` | Emula un file `.nfc` |
| `field` | Attiva il campo a 13,56 MHz; <kbd>Ctrl</kbd>+<kbd>C</kbd> per fermarlo |
| `scanner` | Elenca tutti i protocolli supportati da un tag; `-t` mostra l'albero dei protocolli |
| `raw -p <protocol> -d <data>` | Invia byte grezzi. Opzioni: `-t <timeout>` (cicli di portante), `-k` mantiene il campo attivo, `-c` aggiunge il CRC, `-s` esegue prima attivazione e anticollisione |
| `apdu -d <data> [<data2> ...]` | Invia uno o più APDU a tag ISO14443-4A/4B o ISO15693-3; `-p 4a`/`4b`/`15` forza il protocollo |
| `mfu info` | Informazioni di base su un tag MIFARE Ultralight |
| `mfu rdbl -b <block>` | Legge un blocco |
| `mfu wrbl -b <block> -d <data>` | Scrive un blocco di 4 byte |

Protocolli di `dump -p`: `14_3a`, `14_3b`, `14_4a`, `14_4b`, `15` (ISO 15693-3), `felica`, `mfu`, `mfc`, `mfp`,
`des`, `slix`, `st25`, `ntag4` (NTAG 4xx), `t4t` (Type 4 Tag).
Protocolli di `raw -p`: `14a` / `iso14a`, `14b` / `iso14b`, `15`, `felica`.

### onewire

| Comando | Descrizione |
|---|---|
| `onewire search` | Cerca dispositivi 1-Wire |

### power

| Comando | Descrizione |
|---|---|
| `power off` | Spegne il dispositivo |
| `power reboot` | Riavvia |
| `power reboot2dfu` | Riavvia in modalità DFU |
| `power 5v <1/0>` | Abilita/disabilita i 5 V sul pin GPIO 1 |
| `power 3v3 <1/0>` | Abilita/disabilita i 3,3 V sul pin GPIO 9 (solo in modalità debug) |

### rfid

| Comando | Descrizione |
|---|---|
| `rfid read [normal/indala/ask134]` | Legge una tessera in modalità ASK/PSK; l'argomento facoltativo seleziona una modalità di lettura (`ask134` — tag per animali a 134 kHz) |
| `rfid write <key_type> <key_data>` | Scrive su un T5577 |
| `rfid emulate <key_type> <key_data>` | Emula |
| `rfid raw_read <ask/ask134/psk> <filename>` | Salva il segnale grezzo in un file |
| `rfid raw_emulate <filename>` | Emula un file grezzo (debug dei protocolli) |
| `rfid raw_analyze <filename>` | Stampa un file grezzo e tenta di decodificarlo (sviluppo di protocolli) |

Tipi di chiave e lunghezza dei dati (byte esadecimali):

| Tipo | Byte | Tipo | Byte | Tipo | Byte |
|---|---|---|---|---|---|
| EM4100 | 5 | IoProxXSF | 4 | Paradox | 6 |
| EM4100/32 | 5 | AWID | 9 | PAC/Stanley | 4 |
| EM4100/16 | 5 | FDX-A | 5 | Keri | 4 |
| Electra | 8 | FDX-B | 11 | Gallagher | 8 |
| H10301 | 3 | HIDProx | 6 | Nexwatch | 8 |
| Idteck | 8 | HIDExt | 12 | Radio Key | 6 |
| Indala26 | 4 | Pyramid | 4 | GProxII | 12 |
| Viking | 4 | Jablotron | 5 | Noralsy | 12 |

### storage

I percorsi iniziano con `/int` (flash interna) o `/ext` (scheda SD).

| Comando | Descrizione |
|---|---|
| `storage info /ext` | Informazioni sul filesystem e spazio libero |
| `storage format /ext` | Formatta la scheda SD (chiede conferma) |
| `storage list <path>` | Elenca una directory |
| `storage tree <path>` | Elenca ricorsivamente |
| `storage remove <path>` | Elimina un file o una directory **vuota** |
| `storage read <file>` | Stampa dimensione e contenuto testuale |
| `storage read_chunks <file> <1-512>` | Stampa il contenuto a blocchi della dimensione indicata |
| `storage write <file>` | Aggiunge in coda il testo digitato nella CLI; <kbd>Ctrl</kbd>+<kbd>C</kbd> per terminare |
| `storage write_chunk <file> <1-512>` | Aggiunge in coda esattamente N byte dalla CLI (l'input non viene mostrato) |
| `storage copy <src> <dst>` | Copia un file |
| `storage rename <old> <new>` | Rinomina / sposta |
| `storage mkdir <path>` | Crea una directory |
| `storage md5 <file>` | Hash MD5 |
| `storage stat <path>` | Informazioni su un file o una directory |
| `storage timestamp <file>` | Data dell'ultima modifica |
| `storage extract <archive.tar> <dir>` | Estrae un archivio `.tar` |

### subghz

| Comando | Descrizione |
|---|---|
| `subghz chat <frequency> <device>` | Chatta con altri Flipper |
| `subghz tx <3-byte_key_hex> <frequency> <te_us> <repeat> <device>` | Trasmette una chiave (Princeton) |
| `subghz rx <frequency> <device>` | Riceve e decodifica |
| `subghz rx_raw <frequency>` | Riceve in RAW |
| `subghz decode_raw <path_to_raw_file>` | Decodifica un file RAW `.sub` e stampa i risultati |
| `subghz tx_from_file <path> <repeat> <device>` | Trasmette un file `.sub` salvato |

Solo in modalità debug:

| Comando | Descrizione |
|---|---|
| `subghz tx_carrier <frequency>` | Trasmette una portante non modulata |
| `subghz rx_carrier <frequency>` | Riceve la portante (RSSI) |
| `subghz encrypt_keeloq <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Cifra un file di chiavi produttore KeeLoq |
| `subghz encrypt_raw <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Cifra dati RAW |

`device`: `0` — CC1101 interno, `1` — CC1101 esterno ([modulo esterno](/it/subghz/external-cc1101)).
`te_us` — la durata dell'impulso di base in µs.

Esempio — trasmettere 3 volte un file salvato attraverso la radio interna:

```
subghz tx_from_file /ext/subghz/gate.sub 3 0
```

### sysctl

| Comando | Descrizione |
|---|---|
| `sysctl debug <0/1>` | Disabilita / abilita la modalità debug di sistema |
| `sysctl heap_track <none/main>` | Tracciamento delle allocazioni di heap per il thread principale dell'app; le build di debug (`DEBUG=1`) accettano anche `tree` (thread principale + figli) e `all` |

### update

| Comando | Descrizione |
|---|---|
| `update install /ext/path/to/update.fuf` | Verifica e installa un pacchetto di aggiornamento (il manifest `.fuf` dentro la cartella del pacchetto scompattato) |
| `update backup /ext/backup.tar` | Salva la memoria interna |
| `update restore /ext/backup.tar` | Ripristina la memoria interna da un backup |

Vedi [Aggiornamenti OTA](/it/dev/ota).

### vibro

| Comando | Descrizione |
|---|---|
| `vibro <1/0>` | Accende / spegne il motore di vibrazione |

## Pagine correlate

- [Debug delle app](/it/dev/debugging)
- [Aggiornamenti OTA](/it/dev/ota)
- [Unit test](/it/dev/unit-tests)
- [qFlipper](/it/mobile/qflipper)

MIFARE, MIFARE Ultralight, MIFARE Classic, DESFire e ICODE sono marchi registrati di NXP B.V. FeliCa è un marchio di
Sony Corporation.
