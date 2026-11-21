---
title: App mobile Flipper
order: 20
original: [https://docs.flipper.net/zero/mobile-app, https://docs.flipper.net/zero/mobile-app/bug-report, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# App mobile Flipper

La **Flipper Mobile App** ufficiale ([App Store](https://apps.apple.com/us/app/flipper-mobile-app/id1534655259),
[Google Play](https://play.google.com/store/apps/details?id=com.flipperdevices.app)) si collega al Flipper via
Bluetooth. Con essa puoi aggiornare il firmware, sfogliare e condividere le chiavi salvate, installare app dal
catalogo, controllare il Flipper a distanza e fare il backup dei tuoi dati.

::: tip Unleashed
L'app mobile ufficiale funziona con Unleashed. Può installare un `.tgz` di Unleashed come aggiornamento **Custom**
(vedi sotto). Se l'app smette di connettersi dopo l'installazione di Unleashed o dopo un cambio di nome del Flipper,
rifai l'accoppiamento: vedi [Problemi di connessione](#connection-problems).
:::

## Collegarsi al Flipper

1. Sul Flipper: `Main Menu → Settings → Bluetooth`, imposta **Bluetooth** su **ON**.
2. Nell'app tocca **Connect**, poi **Connect** accanto al nome del tuo Flipper.
3. Inserisci il **codice di accoppiamento** mostrato sullo schermo del Flipper e tocca **Pair**.
4. Attendi che l'app completi la sincronizzazione.

## Cosa c'è nell'app

- **Main Menu** (scheda del dispositivo): aggiornamento via Bluetooth, **Device Info** (dettagli di hardware e
  firmware), **Options** (backup, log, file manager, riavvio, segnalazione di bug; l'insieme dipende da iOS/Android),
  sincronizzazione manuale, riproduzione di un suono per trovare il Flipper.
- **Archive**: tutti i file Sub-GHz, RFID 125, NFC, Infrared e iButton salvati. Preferiti, ricerca e ripristino degli
  elementi eliminati. Tocca una chiave per **Key Info**: emula o invia, aggiungi ai preferiti, rinomina, aggiungi una
  nota, vedi i dettagli, elimina, condividi.
- **Apps**: il catalogo ufficiale delle app, installate via Bluetooth LE, vedi
  [App sulla scheda SD](/it/apps/sd-card-apps).
- **Tools**: **Mfkey32** (Extract MF Keys) per calcolare le chiavi MIFARE Classic dai nonce raccolti, e la
  **Remotes Library** dei telecomandi a infrarossi (vedi [Infrarossi dal telefono](/it/infrared/mobile)).
- **Widget**: emula telecomandi e card salvati dalla schermata iniziale del telefono senza aprire l'app (su iOS
  Vista Oggi → Modifica → Aggiungi widget → Flipper; su Android aggiungilo come qualsiasi widget e toccalo per
  configurarlo).

## Installare Unleashed dal telefono

::: warning Prima installazione
Se è il tuo primo firmware personalizzato, aggiorna prima all'ultima release **ufficiale** e assicurati che la scheda
SD sia inserita. Sei già su Unleashed? Installa la nuova versione sopra quella attuale.
:::

### iOS

1. Apri l'[ultima release di Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) e scarica
   `flipper-z-f7-update-(version).tgz`.
2. Nell'app **Files** seleziona il `.tgz` scaricato, tocca **Share** e scegli l'app **Flipper**.
3. Nell'app Flipper verifica che l'Update Channel mostri `Custom flipper-z-f7-update...`, poi tocca il pulsante verde
   **Update**.
4. Attendi la fine dell'aggiornamento. L'app iOS può mostrare un errore alla fine, ma il Flipper è aggiornato.

### Android, con il file `.tgz`

1. Scarica `flipper-z-f7-update-(version).tgz` dalla pagina della release.
2. Nell'app Flipper tocca **Update channel** → **Custom** e scegli il file scaricato.
3. Tocca **Update** e attendi.

### Android, tramite il link del web updater

1. Nella pagina della release tocca **Install via Web Updater**.
2. Quando Android chiede con cosa aprirlo, scegli l'app **Flipper**.
3. Prosegui con l'installazione e attendi.

Un aggiornamento via Bluetooth può richiedere circa 10 minuti. Altri modi:
[Installare Unleashed](/it/start/install).

### Se l'aggiornamento fallisce

- Verifica che il Flipper sia acceso e ancora collegato via Bluetooth.
- Riavvia il Flipper (<kbd>←</kbd> + <kbd>Back</kbd>) e riavvia l'aggiornamento.
- Se continua a fallire, la memoria interna potrebbe essere piena o danneggiata: installa invece con
  [qFlipper](/it/mobile/qflipper) o con il [Web Installer](/it/mobile/web-tools#unleashed-web-installer), vedi
  [Ripristino](/it/start/recovery).

## Fare il backup delle chiavi

1. Nella scheda del dispositivo tocca **Options → Backup Keys**.
2. Scegli dove salvare o con chi condividere lo `.zip` con chiavi, card e telecomandi.

Per ripristinare, scompatta l'archivio e carica i file con [qFlipper](/it/mobile/qflipper). Per un backup completo
della scheda SD, scarica l'intera scheda dal **File manager** di qFlipper.

## Problemi di connessione {#connection-problems}

**Dopo l'installazione di Unleashed o il cambio di nome del Flipper l'app non si connette:**

1. Nell'app tocca **Forget flipper**.
2. Nelle impostazioni Bluetooth del telefono trova il Flipper, apri le sue opzioni e scegli **Dimentica
   dispositivo**.
3. Sul Flipper: `Settings → Bluetooth → Unpair All Devices` e confermi con **Unpair**.
4. Verifica che il Bluetooth sia attivo sul Flipper, poi accoppia di nuovo dall'app.

**Il Flipper non viene trovato:** verifica che il Bluetooth sia attivo su entrambi, scollega il Flipper da altri
dispositivi (per esempio da un host di [telecomando Bluetooth](/it/apps/controllers)), aggiorna app e firmware,
riavvia il Flipper.

**La sincronizzazione fallisce:** rimuovi l'accoppiamento e rifallo, riavvia entrambi i dispositivi e prova
`Settings → System → Sleep Method → Legacy` sul Flipper.

## Segnalare bug dell'app

Per i bug dell'app ufficiale: **Options → Report Bug**, compila un titolo e i passaggi per riprodurre il problema,
lascia allegati i log, tocca **Submit** e, se vuoi, pubblica l'ID della issue su
[forum.flipperzero.one](https://forum.flipperzero.one/) (sezione Mobile App). Per raccogliere i log del Flipper da
allegare a una segnalazione: imposta `Settings → System → Log Level` su **Debug**, collega via USB, apri un terminale
seriale a **230400** baud (oppure [lab.flipper.net/cli](https://lab.flipper.net/cli)), esegui `info device` e poi
`log`, riproduci il bug e rimuovi le righe `hardware.uid` e `hardware.name` prima di pubblicare.

## Pagine correlate

- [qFlipper](/it/mobile/qflipper)
- [App companion qUnleashed](/it/mobile/qunleashed-app)
- [Installare Unleashed](/it/start/install)
