---
title: App sulla scheda SD (.fap)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# App sulla scheda SD (.fap)

Quasi ogni app che avvii da `Main Menu → Apps` è un **FAP** (Flipper App Package): un eseguibile `.elf` con metadati
aggiuntivi (nome, icona, categoria, versione delle API richiesta) e, facoltativamente, risorse incluse. I FAP
risiedono sulla scheda microSD, quindi **le app richiedono una scheda SD** per funzionare.

## Dove risiedono le app

| Percorso | Cosa contiene |
|---|---|
| `/ext/apps/<Category>/*.fap` | app installate, una cartella per categoria (`Sub-GHz`, `NFC`, `RFID`, `GPIO`, `USB`, `Bluetooth`, `Games`, `Tools`, ...) |
| `/ext/apps_data/<appid>/` | dati e impostazioni che ciascuna app salva per sé |
| `/ext/apps_data/loader/plugins/` | plugin del loader, per esempio gli [stili del menu principale](/it/apps/menu-styles) |

`Main Menu → Apps` mostra semplicemente le cartelle presenti sotto `/ext/apps`. La scheda **Apps**
dell'[Archive](/it/apps/archive) elenca la stessa cartella e mostra anche gli script `.js`.

## Come il Flipper esegue un FAP

Il microcontrollore non può eseguire codice direttamente dalla memoria esterna. Quando avvii un'app, l'**App Loader**:

1. legge il FAP dalla scheda SD e ne verifica l'integrità e il manifest;
2. controlla che la **versione major delle API** dell'app corrisponda a quella del firmware;
3. copia le sezioni di codice e dati nella RAM e corregge gli indirizzi per la nuova posizione (rilocazione);
4. risolve ogni funzione importata dall'app tramite la **tabella dei simboli** del firmware;
5. avvia l'app.

Poiché l'app viene eseguita dalla RAM, un'app di grandi dimensioni lascia meno heap per tutto il resto. Vengono
caricati solo codice e dati, quindi la RAM usata è inferiore alla dimensione del file `.fap`.

::: tip Unleashed
Unleashed mantiene le API ufficiali (la versione corrente delle API è indicata in cima a ogni changelog, per esempio
`Current API: 88.27`), quindi la maggior parte delle app del catalogo ufficiale funziona così com'è. Se la versione
major delle API è diversa, Unleashed non rifiuta a priori: mostra **App Too Old** o **App Too New** con le due
versioni (per esempio `APP:86 < FW:88`) e un pulsante **Continue**, così puoi provare a eseguirla comunque. Vedi
[Risoluzione dei problemi con le app](/it/apps/troubleshoot).
:::

## Installare le app

### Dai pacchetti di app

Il modo più semplice è scegliere una build del firmware che includa già un pacchetto (build predefinita o `e`), vedi
[App incluse in Unleashed](/it/apps/catalog).

Entrambi i pacchetti vengono da [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Per aggiungerne uno a mano:

1. Scarica lo `.zip` dalla [pagina delle release](https://github.com/xMasterX/all-the-plugins/releases/latest).
2. Estrailo.
3. Copia le cartelle delle app nella cartella `apps` della scheda SD (`/ext/apps/`), mantenendone le cartelle di
   categoria.
4. Controlla che la versione di API del pacchetto corrisponda a quella del firmware (`Current API:` in cima al changelog).

### Dal catalogo ufficiale {#installing-from-the-official-catalog}

L'Apps Catalog ufficiale si trova in [Flipper Lab](https://lab.flipper.net/apps) (Chrome, Edge e altri browser basati
su Chromium con Web Serial) e nella scheda **Apps** dell'[app mobile Flipper](/it/mobile/mobile-app).

1. Chiudi qFlipper e qualunque altra scheda di Flipper Lab (solo un programma alla volta può occupare la porta
   seriale USB).
2. Collega il Flipper via USB (Flipper Lab) o Bluetooth (app mobile).
3. Apri **Apps** e trova l'app per categoria o con la ricerca.
4. Premi **Install** sulla card dell'app o nella sua pagina e attendi il completamento del caricamento.
5. Sul Flipper apri `Main Menu → Apps → <categoria> → <app>`.

Per aggiornare o eliminare le app del catalogo, apri **Apps → Installed** e premi **Update** oppure l'icona del
cestino.

Se l'installazione non riesce: controlla la connessione, libera spazio sulla scheda SD (elimina file
dall'[Archive](/it/apps/archive)) e assicurati che il firmware sia aggiornato.

### A mano (qualunque `.fap`)

1. Scarica il `.fap` compilato per il tuo firmware (una build di Unleashed, oppure una build OFW con una versione
   delle API corrispondente).
2. Copialo in `/ext/apps/<Category>/` con [qFlipper](/it/mobile/qflipper), il gestore di file dell'app mobile o un
   lettore di schede.
3. Avvialo da `Main Menu → Apps`, oppure apri il file nell'[Archive](/it/apps/archive) e scegli **Run**.

::: warning
Le app compilate per un altro fork del firmware possono importare funzioni che Unleashed non esporta, e in quel caso
si interrompono con **Missing Imports**. Prendi le app dai pacchetti Unleashed o ricompilale con l'SDK Unleashed.
:::

## Creare il proprio FAP

I FAP si sviluppano esattamente come le app integrate. In sintesi:

1. Metti la cartella della tua app in `applications_user/` di una copia locale del firmware.
2. Nel suo `application.fam` imposta `apptype=FlipperAppType.EXTERNAL` (vedi
   [Manifest delle app](/it/dev/app-manifests)).
3. Compila con uno di questi comandi:

```bash
./fbt fap_{APPID}                                     # build one app
./fbt launch APPSRC=applications_user/path/to/app     # build, upload over USB and run
./fbt build APPSRC=applications_user/path/to/app      # build without uploading
./fbt faps                                            # build all FAPs (or ./fbt fap_dist)
```

Nel profilo VS Code predefinito `launch` corrisponde all'azione **Launch App on Flipper**
(<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>).

**Asset.** Metti le immagini in una sottocartella dell'app e indicala in `fap_icon_assets`; poi usa
`#include "{APPID}_icons.h"` e impiegale come le icone di `assets_icons.h`.

**Versionamento delle API.** Non tutte le funzioni del firmware sono disponibili alle app: l'insieme esportato è
elencato in `api_symbols.csv` del target hardware. La versione major cresce in caso di modifiche non retrocompatibili
(una funzione o variabile rimossa, una firma cambiata), la minor in caso di aggiunte. `fbt` gestisce tutto questo
automaticamente: i nuovi simboli compaiono con `?`, e devi contrassegnarne ciascuno con `+` (esportato) o `-`
(nascosto) prima che il firmware venga compilato.

**Debug.** `fbt` carica `debug/flipperapps.py` in gdb, così puoi eseguire il debug di un FAP come se fosse codice del
firmware. Compila e flasha il firmware (`./fbt`, `./fbt flash`), avvia il tuo FAP, poi collegati con `./fbt debug`. Il
firmware si ferma su un breakpoint subito dopo il caricamento del FAP, così puoi impostare breakpoint al suo interno.
Il tipo di build (debug/release) di firmware e app deve coincidere, e la build corrispondente deve essere collegata
come `build/latest`.

Altri dettagli in [Compilare il firmware](/it/dev/build), [fbt](/it/dev/fbt) e
[La tua prima app in C](/it/dev/first-app-c).

## Pagine correlate

- [App incluse in Unleashed](/it/apps/catalog)
- [Risoluzione dei problemi con le app](/it/apps/troubleshoot)
- [Archive (browser dei file)](/it/apps/archive)
