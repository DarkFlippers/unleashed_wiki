---
title: API Furi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_furi_api.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriCheck.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi]
sources: [unleashed-docs, unleashed-src]
---
# API Furi

Per usare l'hardware del Flipper — schermo, altoparlante, radio, USB, NFC — la tua app dialoga con **Furi**,
l'insieme di librerie che si colloca tra l'hardware nudo e il codice applicativo. Questa pagina offre una panoramica
dell'architettura hardware e software e spiega i controlli a runtime di Furi.

## Hardware

Il cuore del Flipper Zero è un microcontrollore (MCU) **STM32WB55**: due core, RAM, flash e decine di blocchi
periferici (timer, RTC, BLE, GPIO, …). Il loro funzionamento è descritto nel Reference Manual dell'MCU. Attorno
all'MCU ci sono diversi chip esterni (CC1101, ST25R3916, controller del display, ecc.) con i loro datasheet.

![Struttura hardware del Flipper Zero](/img/dev/flipper_zero_hardware.png)

Legenda dei colori:

- **Viola** — blocchi all'interno dell'MCU
- **Blu** — chip esterni all'MCU
- **Arancione** — altri componenti periferici che non richiedono interazioni complesse

Poiché il firmware è open source, *puoi* accedere direttamente all'hardware e scrivere driver di basso livello
propri — ma di solito non serve.

## Software: Furi

**Furi** (**F**lipper **U**niversal **R**egistry **I**mplementation) è il livello di astrazione incluso nel
firmware. Offre un'API lineare per l'hardware e per le attività di sistema più comuni: thread, memoria dinamica,
controllo dell'accesso alle risorse (record), timer, code di messaggi, logging e così via.

Con Furi non devi leggere centinaia di pagine di datasheet né scrivere driver: è sufficiente imparare l'API di Furi.
Evita anche che ogni sviluppatore reimplementi le stesse cose.

![Struttura hardware + software del Flipper Zero](/img/dev/flipper_zero_architecture.png)

Furi occupa l'intera larghezza dello schema: separa il codice a livello applicativo (servizi e app) dall'hardware
sottostante.

Furi è composto da due parti:

| Parte | Dove | Che cosa |
|---|---|---|
| Furi Core | `furi/` | Primitive di sistema: thread, mutex, code di messaggi, record, timer, event loop, logging, controlli |
| Furi HAL | `targets/` (per esempio `targets/f7/furi_hal/`) | Astrazione dell'hardware: GPIO, SPI, I2C, USB, Sub-GHz, NFC, RFID, alimentazione, … — vedi [FuriHalBus](/it/dev/furi-hal-bus) |

Codice sorgente:

- Furi Core: [unleashed-firmware/furi](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi)
  (ufficiale: [flipperzero-firmware/furi](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/furi))
- Furi HAL: [unleashed-firmware/targets](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets)
  (ufficiale: [flipperzero-firmware/targets](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/targets))

## Trovare esempi

Ogni app del Flipper usa Furi, quindi esistono esempi per qualunque blocco hardware:

- app di esempio in [`applications/examples/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples)
  (`example_event_loop`, `example_adc`, `example_ble_beacon`, …);
- app integrate in `applications/main/` e le app aggiuntive di Unleashed in `applications/system/`;
- app della comunità nell'[Apps Catalog](https://lab.flipper.net/apps) — il link ai sorgenti si trova in fondo alla
  pagina di ogni app. Scegli app la cui funzionalità sia vicina a quella che vuoi realizzare.

Tutte le funzioni, le struct e gli header di Furi sono elencati nel [riferimento API Doxygen](https://developer.flipper.net/flipperzero/doxygen/) ufficiale: usalo quando questa wiki non copre la chiamata che ti serve.

## Controlli a runtime e crash forzati

Il modo migliore per proteggere l'integrità del sistema è gestire meno casi impossibili e **andare in crash il prima
possibile** quando qualcosa non va. Il file `check.h` di Furi Core offre strumenti per farlo.

Terminologia:

- **Crash** — registra l'evento nel log, salva le informazioni di crash nell'RTC, riavvia.
- **Halt** — registra l'evento nel log, blocca il sistema.

Note:

- Le build di debug e di release si comportano in modo diverso: una build di **debug non riavvia mai** il sistema, per
  conservarne lo stato a beneficio del debugger.
- Con un debugger collegato, l'esecuzione si arresta automaticamente prima del riavvio.
- Tutti gli strumenti accettano un `MESSAGE_CSTR` facoltativo. Può risiedere in RAM o in flash, ma **solo i messaggi
  memorizzati in flash** vengono mostrati dopo il riavvio (usa quindi letterali di stringa).
- `MESSAGE_CSTR` può essere `NULL`, ma le macro gestiscono già il caso senza messaggio — è sufficiente ometterlo.

| Macro | Comportamento | Quando usarla |
|---|---|---|
| `furi_assert(CONDITION)` / `furi_assert(CONDITION, MESSAGE_CSTR)` | Va in crash se `CONDITION` è falsa — **solo nelle build di sviluppo** | Controlli in fase di sviluppo in app e servizi |
| `furi_check(CONDITION)` / `furi_check(CONDITION, MESSAGE_CSTR)` | Va **sempre** in crash se `CONDITION` è falsa | Condizioni che devono valere in ogni build |
| `furi_crash()` / `furi_crash(MESSAGE_CSTR)` | Va in crash incondizionatamente | È stata rilevata una condizione anomala |
| `furi_halt()` / `furi_halt(MESSAGE_CSTR)` | Blocca il sistema | Usata internamente, per esempio per fermarsi quando non è possibile spegnere |

::: warning Insidie di furi_assert
- Le build di release (`DEBUG=0`) non contengono mai i controlli `furi_assert`.
- Le librerie non li contengono per impostazione predefinita; compila con `LIB_DEBUG=1` se ti servono.
- Non inserire chiamate a funzione (effetti collaterali) all'interno di `CONDITION` — l'intera espressione può essere
  eliminata in compilazione.
:::

Esempio:

```c
#include <furi.h>

void my_set_level(uint8_t level) {
    furi_check(level <= 100, "Level out of range");
    // ...
}
```

## Pagine correlate

- [GUI nelle app](/it/dev/gui)
- [API FuriHalBus](/it/dev/furi-hal-bus)
- [Debug delle app](/it/dev/debugging) — comprende i segnali di debug di Furi HAL
