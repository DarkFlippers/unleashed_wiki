---
title: Flipper Build Tool (fbt)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Flipper Build Tool (fbt)

`fbt` è l'unico punto di ingresso per compilare, flashare, eseguire il debug e analizzare il firmware. Si esegue come
`./fbt` (o `fbt.cmd` su Windows) dalla radice del repository. Internamente è un wrapper attorno al sistema di build
[SCons](https://scons.org/).

Se vuoi soltanto compilare e fare il debug di **una singola app**, non ti serve l'albero completo del firmware — usa
invece [uFBT](https://pypi.org/project/ufbt/) (vedi [La tua prima app in C](/it/dev/first-app-c)).

## Ambiente {#environment}

L'unica cosa che devi avere installata è `git`. Alla prima esecuzione `fbt` scarica e scompatta una toolchain
precompilata e adatta le variabili d'ambiente **solo per sé** — il tuo `PATH` globale non viene modificato.

Per usare la toolchain integrata al di fuori di `fbt` (per esempio per chiamare manualmente `arm-none-eabi-gdb`),
apri una *fbt shell*:

- Windows: esegui `scripts/toolchain/fbtenv.cmd`
- Linux / macOS: esegui `source scripts/toolchain/fbtenv.sh` in una nuova shell
- oppure digita `` . `./fbt -s env` `` nella tua shell (mantieni il `.` iniziale)

Variabili d'ambiente che modificano il comportamento di `fbt`:

| Variabile | Effetto |
|---|---|
| `FBT_NOENV=1` | Salta il download e la configurazione della toolchain; tutti gli strumenti devono già essere nel `PATH` (non disponibile su Windows) |
| `FBT_TOOLCHAIN_PATH=…` | Directory in cui scompattare la toolchain (predefinita: `toolchain/` nella radice del repository) |
| `FBT_VERBOSE=1` | Output di debug aggiuntivo da `fbt` e dagli script della toolchain |
| `FBT_NO_SYNC=1` | Non esegue `git submodule update --init` a ogni avvio |

Impostare una variabile per una singola esecuzione:

```sh
# Linux / macOS
FBT_NO_SYNC=1 ./fbt ...
```

```bat
:: Windows (cmd)
set "FBT_NO_SYNC=1"
```

Altre variabili sono documentate nei sorgenti degli script `fbt` e `fbtenv`.

## Invocare fbt

Passa le opzioni di configurazione e i target che desideri:

```sh
./fbt COMPACT=1 DEBUG=0 VERBOSE=1 updater_package copro_dist
```

Per ripulire (come `make clean`) i target indicati, aggiungi `-c`.

`fbt` tiene traccia delle dipendenze, quindi devi indicare solo il target di livello più alto che ti serve — tutto
ciò da cui dipende viene ricompilato automaticamente.

## Directory di build

Firmware e updater vengono compilati in sottodirectory separate di `build/`, denominate in base alle impostazioni di
ottimizzazione (`COMPACT`, `DEBUG`). Per gli IDE, la variante compilata più di recente è sempre collegata come
`build/latest`, insieme a un `compile_commands.json` usato per il completamento del codice.

::: info
`build/latest` e il database di compilazione vengono aggiornati soltanto dai **target di build del firmware**.
Flashare, o creare pacchetti di aggiornamento per una configurazione debug/release *diversa* o per un altro target
hardware, non sposta `build/latest`.
:::

## Integrazione con VS Code {#vs-code-integration}

```sh
./fbt vscode_dist
```

copia una configurazione d'ambiente già pronta in `.vscode/`. Apri la radice del firmware con
**File → Open Folder**.

- Per usare un language server diverso da `cpptools` (quello predefinito), esegui
  `./fbt vscode_dist LANG_SERVER=<language-server>`. Supportati: `cpptools` (predefinito) e `clangd`.
- Al primo avvio ti verranno proposte le estensioni consigliate (elencate in `.vscode/extensions.json`) —
  installale.
- I task di compilazione si trovano sotto <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
- Il debug richiede una sonda supportata: Wi-Fi Devboard con il firmware di serie (Blackmagic), ST-Link e
  compatibili, oppure J-Link (solo in VS Code; gli strumenti J-Link non sono inclusi —
  [scaricali](https://www.segger.com/downloads/jlink/) e mettili nel `PATH`).
- Senza una sonda puoi comunque installare il firmware via USB.

## Target di alto livello {#high-level-targets}

Sono i target che userai più spesso.

| Target | Cosa fa |
|---|---|
| `fw_dist` | Compila il firmware e lo pubblica in `dist/`. **Target predefinito** se non ne viene indicato alcuno |
| `fap_dist` | Compila le app esterne (FAP) e le pubblica in `dist/` |
| `updater_package` | Pacchetto di autoaggiornamento completo: DFU del firmware + stack radio + risorse per la scheda SD |
| `updater_minpackage` | Pacchetto di aggiornamento minimo: solo il DFU del firmware |
| `copro_dist` | Raccoglie i binari di Core2 FUS + stack radio per qFlipper |
| `flash` | Flasha via SWD con una sonda supportata (rilevata automaticamente; forzala con `SWD_TRANSPORT=...`, scegli una tra più sonde con `SWD_TRANSPORT_SERIAL=...`) |
| `flash_usb`, `flash_usb_full` | Compila, carica e installa il pacchetto di aggiornamento via USB (pacchetto minimo / completo) |
| `debug` | Compila e flasha il firmware, poi collega GDB con l'`.elf` del firmware caricato |
| `debug_other`, `debug_other_blackmagic` | Collega GDB senza caricare alcun `.elf`; aggiungi file `.elf` esterni con `add-symbol-file` |
| `updater_debug` | Collega GDB con l'`.elf` dell'updater caricato |
| `devboard_flash` | Aggiorna la Wi-Fi Devboard; argomenti aggiuntivi tramite `ARGS="..."`, per esempio `ARGS="-c dev"` |
| `blackmagic` | Esegue il debug del firmware con una sonda Blackmagic (Wi-Fi Devboard) |
| `openocd` | Avvia soltanto OpenOCD; argomenti aggiuntivi tramite `ARGS="..."` |
| `get_blackmagic` | Stampa l'indirizzo Blackmagic in formato GDB remote (per l'integrazione con l'IDE) |
| `get_stlink` | Stampa i numeri di serie delle sonde ST-Link collegate (per `SWD_TRANSPORT_SERIAL=...`) |
| `lint`, `format` | Verifica / riformatta il codice C con clang-format (`.clang-format`); argomenti aggiuntivi tramite `ARGS="..."` |
| `lint_py`, `format_py` | Verifica / riformatta Python, file di build e manifest con [black](https://black.readthedocs.io/en/stable/index.html) |
| `lint_img`, `format_img` | Verifica / corregge gli asset grafici (profondità di colore, rimozione dei metadati) |
| `lint_all`, `format_all` | Esegue tutti i linter / formattatori |
| `firmware_pvs` | Rapporto PVS-Studio (PVS-Studio deve essere nel `PATH`) |
| `doxygen` | Genera la documentazione Doxygen; `doxy` la apre anche nel browser |
| `cli` | Apre una sessione [CLI](/it/dev/cli) del Flipper via USB |

## Target del firmware

| Target | Cosa fa |
|---|---|
| `faps` | Compila tutte le app esterne e i plugin come `.fap` |
| `fap_<appid>` | Compila una singola app come `.fap` in base al suo ID, per esempio `fap_snake_game` |
| `fap_<appid>_list` | Genera il listato dei sorgenti e dell'assembler per il `.fap` di quell'app |
| `flash`, `firmware_flash` | Flasha la build corrente via SWD |
| `jflash` | Flasha con JFlash usando una sonda J-Link (JFlash deve essere nel `PATH`) |
| `firmware_all`, `updater_all` | Compila un insieme di base di binari |
| `firmware_list`, `updater_list` | Genera i listati dei sorgenti e dell'assembler |
| `firmware_cdb`, `updater_cdb` | Genera `compilation_database.json` per gli IDE — funziona anche senza una build completa |

Usa `--extra-ext-apps` (vedi sotto) per forzare l'inclusione di app aggiuntive nella build esterna.

## Target degli asset

| Target | Cosa fa |
|---|---|
| `resources` | Compila le risorse per la scheda SD e i relativi file di manifest |
| `dolphin_ext` | Elabora le animazioni del delfino per la scheda SD |
| `icons` | Genera i file `.c` + `.h` per le icone a partire dagli asset PNG |
| `proto` | Genera `.pb.c` + `.pb.h` dai sorgenti `.proto` |
| `proto_ver` | Genera un `.h` con la versione di protobuf |
| `dolphin_internal`, `dolphin_blocking` | Generano i file `.c` + `.h` per i corrispondenti asset del delfino |

## Parametri da riga di comando

| Parametro | Significato |
|---|---|
| `--options optionfile.py` | Carica un file con valori di configurazione (predefinito `fbt_options.py`) |
| `--extra-int-apps=app1,app2,appN` | Forza la compilazione delle app elencate **dentro** il firmware (target `firmware`) |
| `--extra-ext-apps=app1,app2,appN` | Forza la compilazione delle app elencate come **esterne** (target `firmware_extapps`) |
| `--extra-define=A --extra-define=B=C` | Define C/C++ globali aggiuntive; si può ripetere |
| `--proxy-env=VAR1,VAR2` | Variabili d'ambiente aggiuntive da passare ai sottoprocessi. Per impostazione predefinita `fbt` ripulisce l'ambiente; l'elenco di quelle sempre inoltrate è in `environ.scons` |

## Configurazione

I valori predefiniti risiedono in `fbt_options.py`. I valori indicati da riga di comando hanno la precedenza. Per
**sovrascritture personali persistenti**, crea `fbt_options_local.py` accanto a esso — viene valutato al caricamento
delle opzioni predefinite, quindi non devi mai modificare il file tracciato da Git. Esegui `./fbt -h` per elencare
tutte le opzioni.

Valori predefiniti di Unleashed degni di nota, da `fbt_options.py`:

| Opzione | Predefinito | Note |
|---|---|---|
| `FIRMWARE_ORIGIN` | `"Unleashed"` | Riportato nelle informazioni sul dispositivo |
| `TARGET_HW` | `7` | Flipper Zero (f7); vedi [target hardware](/it/dev/hardware-targets) |
| `COMPACT` | `1` | Ottimizza per le dimensioni |
| `DEBUG` | `1` | Passa `DEBUG=0` per le build installabili |
| `DIST_SUFFIX` | `"local"` | Suffisso nei nomi dei file di output |
| `COPRO_STACK_TYPE` | `"ble_light"` | `ble_full` è supportato ma può non stare nelle build di debug |
| `FIRMWARE_APP_SET` | `"default"` | Vedi sotto |

### Insiemi di app del firmware {#firmware-app-sets}

Quali app finiscono nel firmware è deciso da `FIRMWARE_APPS` — una mappa *nome della configurazione → tupla di ID di
app*. Ne scegli una con `FIRMWARE_APP_SET`. Unleashed definisce due insiemi:

```python
FIRMWARE_APPS = {
    "default": [
        # Svc
        "basic_services",
        # Apps
        "main_apps",
        "system_apps",
        # Settings
        "settings_apps",
    ],
    "unit_tests": [
        "basic_services",
        "updater_app",
        "radio_device_cc1101_ext",
        "unit_tests",
        "infrared",
        "archive",
    ],
}
```

Per esempio, per compilare un'immagine con gli unit test:

```sh
./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests
```

Vedi [Unit test](/it/dev/unit-tests) per capire perché quella build richiede `DEBUG=0`.

## Pagine correlate

- [Compilare il firmware](/it/dev/build)
- [Manifest delle app (.fam)](/it/dev/app-manifests)
- [Debug delle app](/it/dev/debugging)
- [Aggiornamenti OTA](/it/dev/ota)
