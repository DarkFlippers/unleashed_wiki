---
title: Debug delle app
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_debugging_faps.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalDebugging.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md]
sources: [unleashed-docs]
---
# Debug delle app

Il debug in tempo reale (in-circuit) permette di avviare un'app, metterla in pausa in qualunque punto, procedere nel
codice riga per riga e osservare variabili e stack delle chiamate. Trova molti più bug di un "aggiungi una riga di log
e riprova".

::: info
Il debug in-circuit è facoltativo. Puoi sempre fare debug caricando le app via USB e leggendo il
[log](/it/dev/cli#reading-logs).
:::

## Cosa ti serve

- Un Flipper Zero (il *target*).
- Un computer Windows, Linux o macOS con [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) (per le app) o
  l'albero completo del firmware con [fbt](/it/dev/fbt).
- Una **sonda SWD** supportata.

### Sonde SWD supportate

| Sonda | Note |
|---|---|
| Un **secondo Flipper Zero** | Esegui su di esso l'[app DAP Link](https://lab.flipper.net/apps/dap_link) per trasformarlo in una sonda SWD |
| [Wi-Fi Devboard](https://shop.flipperzero.one/products/wifi-devboard) | Con il firmware di serie (Blackmagic); si collega via USB o Wi-Fi — vedi [Dev Board](/it/gpio/devboard) |
| Sonde CMSIS-DAP | per esempio [Raspberry Pi Debug Probe](https://www.raspberrypi.com/products/debug-probe/), [l-tek](https://www.l-tek.com/web-shop/cmsis-dap-debug-probe/), [makerdiary Pitaya-Link](https://makerdiary.com/products/pitaya-link) |
| [Sonde compatibili Blackmagic](https://black-magic.org/hardware.html) | |
| ST-Link | [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html), [ST-LINK V3](https://www.st.com/en/development-tools/stlink-v3set.html), la [devboard ST-Link V3](/it/dev/hardware#st-link-v3-developer-board) |
| J-Link | Flashing e debug solo da VS Code; gli strumenti SEGGER vanno installati a parte |

## Preparare il Flipper

Attiva la modalità debug sul target: `Main Menu → Settings → System → Debug` → **ON**.

## Passo per passo (VS Code)

1. **Collega la sonda al connettore GPIO del Flipper.** Le sonde realizzate per il Flipper si inseriscono
   direttamente. Per una sonda generica collega tre fili:

   | Segnale | Pin del Flipper |
   |---|---|
   | SWCLK | 10 |
   | SWDIO | 12 |
   | GND | 8, 11 o 18 |

   Se la sonda ha anche una UART, collegala all'USART del Flipper (pin **13** TX e **14** RX). Quella porta stampa i
   log e le informazioni di crash, cosa che aiuta molto.
2. **Collega la sonda al computer** — di solito via USB; la Wi-Fi Devboard funziona anche via Wi-Fi.
3. **Prepara il progetto:** esegui una volta `ufbt vscode_dist` (app) o `./fbt vscode_dist` (firmware), poi apri la
   cartella in VS Code.
4. **Passa a Run and Debug in VS Code:** clicca l'icona del debug nella barra laterale oppure premi
   <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> (<kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> su macOS). Scegli la
   configurazione per la tua sonda e premi **Play**.

   ::: info
   L'avvio di una sessione di debug **blocca** il firmware. Clicca **Continue** nella barra degli strumenti del debug
   per riprendere.
   :::
5. **Usa i controlli di debug:** reset, pausa, continua, step in, step out, disconnetti.
6. **Imposta i breakpoint** cliccando a sinistra del numero di riga. L'esecuzione si arresta quando raggiunge quella
   riga.
7. **Esamina lo stack delle chiamate** nel pannello *Call Stack* mentre l'esecuzione è in pausa.
8. **Esamina le variabili** nei pannelli *Variables*, *Watch* o *Live Watch*.

Una dimostrazione video di Flipper Devices: [Debugging FAPs in VS Code](https://cdn.flipperzero.one/app_dev_flipper_zero_debug_demo.mp4).

## Debug dalla riga di comando con fbt

Con l'albero completo del firmware puoi fare debug senza VS Code:

| Comando | Cosa fa |
|---|---|
| `./fbt debug` | Compila e flasha il firmware, poi collega GDB con l'`.elf` del firmware caricato |
| `./fbt blackmagic` | Esegue il debug con una sonda Blackmagic (Wi-Fi Devboard) |
| `./fbt debug_other` / `debug_other_blackmagic` | Collega GDB senza caricare un `.elf`; aggiungi l'`.elf` della tua app con `add-symbol-file` |
| `./fbt updater_debug` | Collega GDB con l'`.elf` dell'updater |
| `./fbt openocd ARGS="..."` | Avvia soltanto OpenOCD |
| `./fbt get_stlink` | Elenca i numeri di serie delle ST-Link, per `SWD_TRANSPORT_SERIAL=...` |

## Segnali di debug di Furi HAL

Alcuni sottosistemi Furi possono esporre il proprio stato interno su pin GPIO, per tracciarlo con un analizzatore
logico o un oscilloscopio. Si attivano aggiungendo una define in fase di compilazione, per esempio:

```sh
./fbt --extra-define=FURI_HAL_OS_DEBUG flash
```

### `FURI_HAL_OS_DEBUG` — scheduler e sospensione

Espone tick, soppressione dei tick, idle e scorrere del tempo:

| Segnale | Pin | Significato |
|---|---|---|
| `AWAKE` | `PA7` | Alto mentre il sistema è occupato in elaborazioni, basso durante la sospensione — segue le transizioni al sonno |
| `TICK` | `PA6` | Commuta a ogni tick di sistema (solo quando non è in corso alcuna soppressione dei tick) — rivela sfasamenti dei tick e scheduling anomalo |
| `SECOND` | `PA4` | Commuta ogni secondo — irregolarità nella sua temporizzazione indicano che il sistema non rispetta i vincoli hard real-time |

### `FURI_HAL_POWER_DEBUG` — modalità di alimentazione

Traccia le transizioni tra le modalità di alimentazione:

| Segnale | Pin | Significato |
|---|---|---|
| `WFI` | `PB2` | Sospensione leggera (wait for interrupt). La modalità di risparmio più leggera e non invasiva — tutto, compreso il debug, continua a funzionare |
| `STOP` | `PC3` | Modalità STOP, la sospensione profonda della piattaforma. La maggior parte del silicio è spenta o inutilizzabile; fare il debug dell'MCU in questa modalità è pressoché impossibile |

### `FURI_HAL_SD_SPI_DEBUG` — scheda SD

Registra nel log il traffico sul bus SPI della scheda SD.

## Risoluzione dei problemi

| Problema | Rimedio |
|---|---|
| La sonda si collega ma non accade nulla | Il firmware è bloccato — premi **Continue** |
| I breakpoint nella tua app vengono ignorati | Assicurati che i simboli dell'`.elf` dell'app siano caricati (la configurazione VS Code generata da `vscode_dist` lo fa; con `debug_other` usa `add-symbol-file`) |
| Il debugger perde il target | L'MCU può essere in modalità STOP; vedi `FURI_HAL_POWER_DEBUG`. La modalità debug sul Flipper deve essere su **ON** |
| Le variabili risultano eliminate dall'ottimizzazione | Compila con `DEBUG=1` (nota: un firmware così può risultare troppo grande per essere impacchettato — vedi [Compilare](/it/dev/build)) |

## Pagine correlate

- [La tua prima app in C](/it/dev/first-app-c)
- [Flipper Build Tool (fbt)](/it/dev/fbt)
- [Dev Board](/it/gpio/devboard)
- [Hardware](/it/dev/hardware) — disegni dei pinout e schemi delle devboard
