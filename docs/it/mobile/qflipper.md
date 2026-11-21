---
title: qFlipper
order: 10
original: [https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/qflipper/windows-debug, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# qFlipper

**qFlipper** è l'app desktop ufficiale per il Flipper Zero: aggiorna firmware e database, gestisce i file sulla scheda
microSD, esegue backup e ripristini del dispositivo, ripara un firmware danneggiato e replica lo schermo. Funziona su
Windows, macOS e Linux.

::: tip Unleashed
I canali di aggiornamento di qFlipper (Release / RC / Dev) installano il firmware **ufficiale**. Per installare
Unleashed usa **Install from file** con il `.tgz` di Unleashed (qFlipper 1.2.0 o successivo), come spiegato sotto,
oppure il [Web Installer](/it/mobile/web-tools#unleashed-web-installer).
:::

## Installare qFlipper

Scaricalo da [flipperzero.one/update](https://flipperzero.one/update) ed esegui l'installer.

- **Windows**: solo Windows 10 e 11. L'installer installa anche i driver.
- **macOS**: 10.14 o successivo, ottimizzato per Apple Silicon.
- **Linux**: un AppImage. Rendilo eseguibile e configura le regole udev:

```bash
chmod +x qFlipper-x86_64.AppImage
./qFlipper-x86_64.AppImage                 # run it
./qFlipper-x86_64.AppImage rules install   # udev rules, to use it as a normal user
```

(Da un file manager: Proprietà → Permessi → "Consenti esecuzione del file come programma" / "È eseguibile".)

## Panoramica

Collega il Flipper con la scheda SD inserita via USB e avvia qFlipper.

- **Device information**: informazioni su hardware e firmware, pulsante di aggiornamento, controllo remoto.
- **Advanced controls**: backup, ripristino, reset di fabbrica, canale di aggiornamento, **Install from file**.
- **File manager**: sfoglia, carica, scarica, rinomina ed elimina file sulla scheda SD e nella memoria interna.

## Installare Unleashed con qFlipper

1. Se è il tuo primo firmware personalizzato, aggiorna prima all'ultima release **ufficiale**. Assicurati che la
   scheda SD sia inserita.
2. Scarica `flipper-z-f7-update-(version).tgz` dalle
   [release di Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) (scegli la lettera della
   build che vuoi, vedi [varianti di build](/it/apps/catalog#build-variants)).
3. Avvia qFlipper e collega il Flipper.
4. Clicca **Install from file** e seleziona il `.tgz`.
5. Attendi la fine di tutte le fasi. Il Flipper si riavvia in Unleashed con tutti gli asset installati.

Sei già su Unleashed? Installa semplicemente la nuova versione sopra quella attuale: non serve tornare al firmware
ufficiale. Altre opzioni: [Installare Unleashed](/it/start/install), [Aggiornare](/it/start/updating).

## Caricare e scaricare file

Nel **File manager** trascina i file in una cartella, oppure fai clic destro su una cartella → **Upload here**. Clic
destro su un file o una cartella → **Download** per copiarlo sul computer (un modo semplice per fare il backup di
tutta la scheda SD).

| Comando | Windows / Linux | macOS |
|---|---|---|
| Entra nella cartella | Return | Return |
| Indietro | Backspace | Backspace |
| Carica | Ctrl+L | Cmd+L |
| Scarica | Ctrl+D | Cmd+D |
| Elimina | Delete | Fn+Backspace |
| Elimina immediatamente | Shift+Delete | Shift+Fn+Backspace |
| Nuova cartella | Ctrl+N | Cmd+N |
| Rinomina | Ctrl+E | Cmd+E |
| Aggiorna | Ctrl+G | Cmd+G |

## Controllo remoto e screenshot

In **Device information** clicca sull'immagine del Flipper, poi clicca sui pulsanti a schermo oppure usa la tastiera
(ℹ️ mostra la mappa dei tasti). **SAVE SCREENSHOT** salva la schermata attuale come immagine.

## Log e segnalazioni di bug

- **LOGS → OPEN FULL LOG** mostra il log della sessione corrente; puoi salvarlo come `.txt`.
- qFlipper conserva i log delle ultime 100 sessioni: in **LOGS** fai clic destro sull'area del log →
  **Browse all logs**.
- Segnala i problemi di qFlipper ufficiale su [forum.flipperzero.one](https://forum.flipperzero.one/) (sezione
  Firmware update / qFlipper). I problemi di Unleashed vanno invece nelle chat di Unleashed o nelle issue GitHub.

## Risoluzione dei problemi

### qFlipper non vede il Flipper / Chrome non si connette

Solo un programma alla volta può usare la porta seriale. Se qFlipper è aperto, Flipper Lab, il Web Installer e gli
altri strumenti web non possono connettersi, e viceversa. Chiudi qFlipper (e le schede di Flipper Lab in eccesso)
prima di usare uno strumento nel browser.

### Driver su Windows

1. Installa qFlipper solo da fonti ufficiali; installa i driver corretti. Controlla gli aggiornamenti in
   **Advanced controls → CHECK APP UPDATES**.
2. **Modalità normale** (Flipper in funzione): il Flipper è un **USB Serial Device** in
   `Gestione dispositivi → Porte (COM e LPT)`, ID hardware **VID 0483, PID 5740**, driver di **Microsoft**. Se è
   installato un altro driver, disinstallalo e ricollega il dispositivo.
3. **Conflitto di porta COM**: due dispositivi seriali sullo stesso numero di COM. Apri uno dei due →
   **Impostazioni della porta → Avanzate** e assegna un **numero di porta COM** non utilizzato.
4. **Modalità di ripristino (DFU)**: tieni premuti <kbd>←</kbd> + <kbd>Back</kbd>, rilascia <kbd>Back</kbd> e mantieni
   <kbd>←</kbd> finché il LED non diventa blu. Il Flipper deve comparire come **DFU in FS Mode** sotto
   `Dispositivi USB (Universal Serial Bus)`, **VID 0483, PID DF11**, driver **STMicroelectronics**.
5. Se vedi **STM Device in DFU mode** sotto `Controller USB (Universal Serial Bus)`, è installato il driver sbagliato:
   disinstalla qFlipper, reinstallalo dal sito ufficiale e ricontrolla.
6. Se **DFU in FS Mode** è sotto `Altri dispositivi` con un punto esclamativo: clic destro → **Aggiorna driver →
   Cerca nel computer → Scegli manualmente** → **Dispositivi USB (Universal Serial Bus)** → **WinUsb Device**.

Se il Flipper non si avvia affatto, vedi [Ripristino](/it/start/recovery).

## Pagine correlate

- [Installare Unleashed](/it/start/install)
- [App mobile Flipper](/it/mobile/mobile-app)
- [Strumenti web](/it/mobile/web-tools)
