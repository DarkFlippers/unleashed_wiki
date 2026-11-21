---
title: App companion qUnleashed
order: 30
original: [https://github.com/DarkFlippers/qUnleashed, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md]
sources: [unleashed-readme, unleashed-docs]
---
# App companion qUnleashed

::: tip Unleashed
**qUnleashed** è l'app companion del team di Unleashed per telefono e computer. È stata scritta da zero
in Flutter come alternativa all'app mobile Flipper ufficiale, quindi non è un fork di qFlipper.
Licenza GPL-3.0 o successiva, sorgenti e build su
[DarkFlippers/qUnleashed](https://github.com/DarkFlippers/qUnleashed).
:::

È pensata per Unleashed, ma funziona anche con altri firmware. La versione stabile attuale è la **0.17.2**.

## Gira sul tuo dispositivo?

| Sistema | Ti serve |
|---|---|
| Android | 10 (API 29) o più recente |
| iOS | 15 o più recente |
| macOS | 12 o più recente |
| Windows | 10 o più recente, a 64 bit |
| Linux | GLib 2.72 e glibc 2.35 — Ubuntu 22.04, Debian 12, Mint 21 o più recenti |

Su un Linux più vecchio il binario non parte nemmeno.

## Installazione

Scegli la build per il tuo sistema nella
[pagina delle release](https://github.com/DarkFlippers/qUnleashed/releases). Non c'è nessuna pubblicazione
sugli store e nessuno script di installazione.

## Collegamento

Il Bluetooth funziona su tutti e cinque i sistemi. La seriale USB funziona su Android, Windows, macOS e
Linux: su iOS l'opzione USB non esiste proprio, perché Apple non permette alle app di parlare con un
dispositivo seriale USB.

L'app ricorda i Flipper che hai usato e si riconnette da sola. Se uno è collegato via USB, ha la
precedenza sull'ultimo dispositivo Bluetooth. Su Android un servizio in primo piano tiene vivo il
collegamento Bluetooth mentre l'app è in background.

## Firmware

- **Updater** con canali release e dev e i relativi changelog. Scarica e installa dall'app stessa: la
  build base di Unleashed, quella con le app extra, quella compatta e i canali ufficiali.
- **Repair from DFU mode** riscrive completamente il firmware del Flipper via USB. Stessa idea del Full
  Repair di qFlipper, per un dispositivo che non si avvia più.
- **Le notifiche di release** sono facoltative, e il canale dev ha un interruttore tutto suo.

## Dispositivo

- **Informazioni sul dispositivo**: versione e data di build del firmware, batteria, memoria.
- **Condivisione di GPS e internet**: il telefono passa la propria posizione alle app sul Flipper e porta
  il traffico di rete del Flipper. Serve il firmware con l'estensione RPC GPS/rete.
- **Desktop remoto**: lo schermo del Flipper in diretta sul telefono o sul PC, con i tasti a schermo. Su un
  computer puoi usare la tastiera vera. Gli screenshot si possono esportare e lo schermo si può registrare
  come GIF.
- **Riga di comando**: la CLI completa del Flipper. Solo via USB, quindi non su iOS.

## Archivio

Una copia delle tue chiavi sta sul telefono, un archivio per ogni Flipper. Ogni file è marcato
**synced**, **remote-only**, **local-only** o **deleted**, così vedi cosa sta dove, e un file cancellato
si può ripristinare. I file si possono segnare come preferiti.

Categorie: Sub-GHz, Wardriving (autosalvataggi inclusi), RFID 125, NFC, Infrared, iButton, Bad USB,
JavaScript.

Un file si può eseguire direttamente dall'app. NFC, RFID e iButton vengono emulati via RPC; Sub-GHz,
Infrared, Bad USB e JavaScript si aprono nell'app corrispondente sul Flipper.

C'è anche un editor di testo con evidenziazione per i formati di file del Flipper, così puoi sistemare un
`.sub` o un `.ir` senza computer.

## File manager

Sfoglia `/ext` (la scheda SD) e `/int` (la memoria interna). Crea, rinomina, cancella, scarica, carica e
modifica file di testo.

## App

Il catalogo delle app, con ricerca, categorie, ordinamento, pagina di dettaglio e screenshot. Installa,
aggiorna ed elimina le app. Vede anche cosa c'è già sul Flipper, app preinstallate comprese.

## Strumenti

- **Pixel Draw**: un editor di pixel art con gestione dei progetti e animazioni a più fotogrammi. Può
  importare le animazioni del delfino e mostrare un'anteprima dal vivo sul Flipper.
- **Extract MIFARE Keys**: esegue Mfkey32 sul telefono partendo dai nonce raccolti dal Flipper. La
  procedura completa è su [Recupero rapido delle chiavi con qUnleashed](/it/nfc/qunleashed).
- **Remotes Library**: telecomandi a infrarossi dalla fonte ufficiale e dal repository pubblico
  [Lucaslhm/Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB). Sfoglia, cerca, modifica il file
  `.ir` e poi salvalo nell'archivio o direttamente in `/ext/infrared`.
- **Pulse Plotter**: disegna le acquisizioni di impulsi grezzi di Sub-GHz, infrarossi e RFID.
- **Saved Locations**: pin sulla mappa costruiti dalla latitudine e longitudine salvate nei file
  dell'archivio.

## Recupero del Seed per le acquisizioni Sub-GHz

Alcuni telecomandi basati su KeeLoq (FAAC SLH, Genius, Erreka, i vecchi BFT Mitto) usano un **Seed** segreto che serve
per decodificarli. Il Flipper si limita a raccogliere i dati con l'app [Seed Capturer](/it/subghz/seed-capturer); la
ricerca vera e propria è un attacco a forza bruta, quindi gira in qUnleashed e non sul Flipper.

1. Acquisisci il telecomando con `Apps → Sub-GHz → Seed Capturer`: premi ripetutamente lo **stesso tasto**, una
   pressione decisa per volta, e controlla che il contatore `Hops` cresca a ogni pressione.
2. Collega il Flipper a **qUnleashed** e apri lo strumento **Seed recovery**.
3. Scegli la tua acquisizione dall'elenco. qUnleashed legge le acquisizioni direttamente dalla cartella
   `subghz_seed_captures` del Flipper; produttore, frequenza e valori `Fix` e `Hop` sono già nel file. **Non devi
   copiare, spostare, rinominare o modificare nessun file.**
4. Avvia la ricerca e aspetta.
5. Se il Seed viene trovato, qUnleashed restituisce il Seed e il contatore e può **salvare il telecomando clone
   completo** come file `.sub` (il `Fix` porta già seriale e tasto). Rimettilo sul Flipper e invialo, senza dover
   digitare nulla in `Add Manually`.
6. Se non trova niente, molto probabilmente l'acquisizione aveva un buco. Riacquisisci tenendo il telecomando proprio
   accanto al Flipper, e premi `Reset` (<kbd>←</kbd>) per ricominciare se una pressione non viene registrata.

::: warning Il Seed appartiene all'impianto
Su FAAC SLH e Genius il Seed è **diverso per ogni tasto**, quindi acquisisci il tasto che intendi usare. Su Erreka il
Seed è per telecomando (a volte per impianto). Su BFT Mitto è per telecomando, e solo i telecomandi più vecchi con un
Seed unico hanno bisogno di un'acquisizione.
:::

La procedura completa, con la programmazione del clone in un ricevitore, è in
[Programmare telecomandi a codice rolling](/it/subghz/remote-prog) e [KeeLoq](/it/subghz/keeloq).

Usalo solo sui tuoi telecomandi e sui tuoi cancelli.

## Pagine correlate

- [Recupero rapido delle chiavi con qUnleashed](/it/nfc/qunleashed)
- [Seed Capturer](/it/subghz/seed-capturer)
- [App mobile Flipper](/it/mobile/mobile-app)
- [qFlipper](/it/mobile/qflipper)
- [Strumenti web](/it/mobile/web-tools)
