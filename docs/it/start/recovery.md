---
title: Ripristino
order: 130
original: [https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://docs.flipper.net/zero/basics/firmware-update/storage-repair, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings]
sources: [flipper-docs, unleashed-docs, unleashed-src]
---
# Ripristino

Cosa fare quando il Flipper si blocca, non si aggiorna, non mostra nulla, oppure hai dimenticato il PIN. Procedi nei
passaggi in ordine, dal più delicato al più drastico.

## 1. Prima di tutto, riavvia

- **Bloccato:** tieni premuti <kbd>←</kbd> + <kbd>BACK</kbd> per circa 5 secondi.
- **Ancora bloccato:** scollega l'USB e tieni premuto <kbd>BACK</kbd> per 30 secondi (reset dell'alimentazione).
- **Batteria scarica:** carica per qualche minuto (o per un'ora) e riprova.
- Da un Flipper funzionante: **Settings → Power → Reboot → Reboot Flipper**.

Tutte le combinazioni: [Combinazioni di tasti](/it/start/key-combos).

## 2. Ripristino del firmware dalla modalità DFU {#firmware-recovery}

Usa questa procedura quando il firmware è corrotto: l'aggiornamento fallisce, lo schermo mostra caratteri casuali o
nulla, oppure i pulsanti non reagiscono. Il bootloader DFU su USB programma il firmware senza l'aiuto del sistema
operativo del dispositivo.

### Passo 1: portare il Flipper in modalità DFU (ripristino)

**Se il Flipper funziona ancora ma non si aggiorna correttamente:**
1. **Main Menu → Settings → Power → Reboot → Firmware Upgrade**.
2. Confermi `Reboot to DFU Mode?` con <kbd>→</kbd> **Reboot**.

*oppure:* tieni premuti <kbd>←</kbd> + <kbd>BACK</kbd> per 5 s, rilascia <kbd>BACK</kbd> e continua a tenere premuto
<kbd>←</kbd> finché il **LED blu** non si accende.

**Se lo schermo non mostra nulla e i pulsanti non reagiscono:**
1. **Scollega il cavo USB.**
2. Tieni premuti <kbd>OK</kbd> + <kbd>BACK</kbd> per **30 secondi**. Qui lo schermo spento è normale.

Poi collega il Flipper al computer con un cavo USB.

### Passo 2: verificare che il computer veda un dispositivo DFU

| Sistema | Dove guardare | Nome |
|---|---|---|
| Windows | Gestione dispositivi | **DFU in FS Mode** |
| macOS | Menu Apple → Informazioni su questo Mac → Resoconto di sistema → Hardware → USB (o `system_profiler SPUSBDataType`) | **DFU in FS Mode** |
| Linux | `lsusb` | **STMicroelectronics STM Device in DFU Mode** |

Non viene rilevato? Prova un altro cavo. Collega direttamente a una porta USB della scheda madre, non a un hub o a un
adattatore. Oppure rimuovi la scheda SD, carica per un'ora e collega senza la scheda.

### Passo 3: riparare

Va bene una delle due app. Entrambe riflashano completamente il Flipper via USB.

**[qUnleashed](/it/mobile/qunleashed-app)** — Android, Windows, macOS e Linux (su iOS non c'è USB):

1. Collega il Flipper in modalità DFU via USB.
2. Apri **Repair from DFU mode** e avvialo.

**qFlipper** — Windows, macOS e Linux:

1. Avvia **qFlipper**. Rileva il dispositivo DFU.
2. Clicca **Repair**. qFlipper installa completamente il firmware **ufficiale**.

Poi reinstalla Unleashed: [Installare Unleashed](/it/start/install).

::: tip Unleashed
Il comando **Repair** di qFlipper ripristina sempre il firmware ufficiale. Non è un problema: ti dà una base pulita.
Dopo la riparazione reinstalla Unleashed con qUnleashed, con il Web Installer o con **Install from file**. La
riparazione non tocca i file sulla scheda SD.
:::

### Se qFlipper non riesce a riparare

- Verifica che qFlipper sia installato correttamente. Su Windows consulta la guida di qFlipper sui driver.
- Scollega l'USB, riavvia con <kbd>←</kbd> + <kbd>BACK</kbd> e ripeti.
- Fai un reset dell'alimentazione (<kbd>BACK</kbd> per 30 s, USB scollegata) e ripeti.
- Avvia qFlipper come amministratore.
- Usa una porta USB direttamente sulla scheda madre.
- Ultima risorsa: programmazione via SWD con un ST-Link (vedi
  [Combinazioni di tasti](/it/start/key-combos#if-nothing-helps)).

## 3. Riparazione della memoria interna / reset di fabbrica {#factory-reset}

Se gli aggiornamenti falliscono perché la memoria interna è piena o danneggiata, riporta il Flipper allo stato di
fabbrica. Questa operazione cancella la **memoria interna**: impostazioni, accoppiamenti Bluetooth, PIN, livello del
delfino. **I file sulla scheda SD restano.**

::: info La memoria interna nei firmware attuali
Nei firmware attuali la memoria interna (`/int`) è **virtuale** e risiede nella cartella nascosta `/ext/.int/` sulla
scheda SD. **Settings → Storage → About Internal Storage** mostra `Type: Virtual (/.int on SD)`.
:::

### Prima fai un backup (opzionale)

qFlipper → **Advanced controls** → **BACKUP** → scegli una cartella → **BACKUP**. Salva la memoria interna in un file
`.tgz`. La scheda SD non è compresa, quindi copiala a parte.

### Reset dal dispositivo

1. **Main Menu → Settings → Storage → Factory Reset**.
2. La schermata chiede `Confirm Factory Reset?`: *"Internal storage will be erased, data and settings will be lost!"*
3. Premi <kbd>→</kbd> **Erase** **5 volte**. Lo schermo conta le pressioni rimanenti.
4. Il Flipper si riavvia e formatta la memoria interna.

### Reset con qFlipper

**Advanced controls** → **ERASE** → **ERASE** → **CONTINUE** al termine.

### Ripristino

qFlipper → **Advanced controls** → **RESTORE** → seleziona il `.tgz` del backup → **RESTORE** → **CONTINUE**.

Se dopo un reset l'aggiornamento continua a non funzionare, esegui un nuovo reset **senza** ripristinare il backup,
oppure procedi con il [ripristino del firmware](#firmware-recovery).

## 4. Azzerare un PIN dimenticato {#reset-pin}

Se il Flipper è bloccato con un PIN che non ricordi:

1. **Scollega il cavo USB.**
2. Spegni il Flipper: tieni premuto <kbd>BACK</kbd> → **Power Off**. Se non riesci, passa al punto successivo ma tieni
   premuti i pulsanti per 30–40 secondi.
3. Tieni premuti <kbd>↑</kbd> + <kbd>BACK</kbd> per circa 5 secondi. Il Flipper si avvia con <kbd>↑</kbd> premuto e
   mostra la **schermata di reset del PIN**.
4. **Tieni premuto <kbd>→</kbd>** fino a riempire la barra di avanzamento per confermare il reset. Premi invece
   <kbd>↓</kbd> per uscire senza azzerare nulla.
5. Il Flipper si riavvia.

Questo riporta la configurazione utente (registri RTC, memoria interna con impostazioni e PIN) allo stato di fabbrica.
**I file dell'utente sulla scheda microSD restano.**

## 5. Ancora morto?

- Carica per un'ora, poi riprova.
- Scollega e ricollega la batteria (richiede l'apertura del case).
- Programma via SWD con un ST-Link o un altro programmatore.

Se nulla di tutto questo funziona, il problema è hardware, non software.

## Argomenti correlati

- [Combinazioni di tasti](/it/start/key-combos)
- [Installare Unleashed](/it/start/install)
- [App companion qUnleashed](/it/mobile/qunleashed-app)
- [qFlipper](/it/mobile/qflipper)
