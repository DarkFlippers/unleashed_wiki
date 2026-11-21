---
title: La tua prima app in C
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_your_first_app_in_c.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md]
sources: [unleashed-docs]
---
# La tua prima app in C

In questo tutorial allestirai un ambiente di sviluppo con **uFBT**, genererai un template di app, aggiungerai una
semplice GUI e poi compilerai ed eseguirai l'app sul tuo Flipper Zero.

Le app realizzate in questo modo sono file `.fap` (Flipper App Package) — risiedono sulla scheda microSD e vengono
caricate su richiesta, quindi non è necessario ricompilare il firmware.

## 1. Preparare l'ambiente

Ti servono un Flipper Zero, un cavo USB e, su Windows / macOS / Linux:

- [**uFBT**](https://github.com/flipperdevices/flipperzero-ufbt) ("micro Flipper Build Tool") — una versione di
  [fbt](/it/dev/fbt) con tutto il necessario per lo sviluppo di app. Installalo con `pip install ufbt` (vedi il
  README di uFBT per i dettagli).
- [**Visual Studio Code**](https://code.visualstudio.com/) — l'IDE consigliato. Anche altri funzionano, ma richiedono
  una configurazione manuale per integrarsi con uFBT.

::: tip Unleashed
uFBT scarica per impostazione predefinita l'SDK **ufficiale**. Per compilare per Unleashed, esegui una volta questo
comando (e usa gli stessi flag per ogni aggiornamento successivo):

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Usa `--channel=release` se il tuo Flipper esegue una build di release. La versione dell'SDK deve corrispondere al
firmware installato sul dispositivo — vedi il [passo 5](#_5-build-and-run-the-app).
:::

## 2. Generare un template di app

1. Crea una cartella per l'app, per esempio `test_app`.
2. Apri un terminale in quella cartella ed esegui:

   ```sh
   ufbt create APPID=test_app
   ```

   uFBT genera la struttura dei file.
3. Esegui:

   ```sh
   ufbt vscode_dist
   ```

   Questo configura VS Code per compilare ed eseguire il debug dell'app direttamente dall'IDE.

::: warning
`APPID` può contenere solo lettere minuscole `a-z`, cifre `0-9` e `_`.
:::

La struttura risultante:

```
test_app/
├── application.fam
├── test_app.c
├── test_app.png
├── .github/
│   └── workflows/
|       └── build.yml
└── images/
    └── .gitkeep
```

| File | Scopo |
|---|---|
| `application.fam` | Il manifest dell'app che uFBT legge per sapere come compilarla — vedi [Manifest delle app](/it/dev/app-manifests) |
| `test_app.c` | File sorgente principale con il punto di ingresso |
| `test_app.png` | Icona dell'app (10×10, 1 bit) |
| `.github/workflows/build.yml` | Configurazione di GitHub Actions — [altri dettagli](https://github.com/marketplace/actions/build-flipper-application-package-fap) |
| `images/` | I tuoi asset grafici |
| `images/.gitkeep` | Segnaposto perché Git tenga traccia della cartella `images/` vuota |

## 3. Il codice del template

```c
#include <furi.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm test_app!");

    return 0;
}
```

Che cosa fa ciascuna parte:

- `#include <furi.h>` — l'intestazione principale di **Furi**, il nucleo del firmware del Flipper
  ([API Furi](/it/dev/furi-api)).
- `#include <test_app_icons.h>` — necessaria se l'app usa immagini. uFBT converte i PNG di `images/` nel formato
  interno del Flipper e genera automaticamente questa intestazione.
- `int32_t` — il tipo di ritorno consueto della funzione principale di un'app.
- `UNUSED(p);` — una macro che silenzia l'avviso "unused parameter".
- `FURI_LOG_I` — scrive un messaggio di livello `info` nel log del Flipper. Puoi osservarlo con `ufbt cli` →
  `log info`.
- `return 0;` — successo, secondo la convenzione del C.

## 4. Aggiungere una GUI

Apri la cartella dell'app in VS Code (**File → Open Folder…**). Installa le estensioni suggerite quando ti viene
chiesto.

Mostriamo due righe sullo schermo: `Hello world` e `I'm test_app!`. Sostituisci il contenuto di `test_app.c` con:

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);
    DialogMessage* message = dialog_message_alloc();
    dialog_message_set_header(message, "Hello world", 64, 20, AlignCenter, AlignTop);
    dialog_message_set_text(message, "I'm test_app!", 64, 32, AlignCenter, AlignTop);
    dialog_message_show(dialogs, message);
    dialog_message_free(message);
    furi_record_close(RECORD_DIALOGS);

    return 0;
}
```

Questo codice usa il servizio GUI **Dialogs**, l'API grafica più semplice. Altri approcci sono descritti in
[GUI nelle app](/it/dev/gui).

## 5. Compilare ed eseguire l'app {#_5-build-and-run-the-app}

**La via rapida:**

1. Collega il Flipper al computer con il cavo USB.
2. Chiudi qFlipper e qualunque altro programma che stia usando la porta seriale del Flipper.
3. Esegui:

   ```sh
   ufbt launch
   ```

   Compila l'app, la carica e la avvia sul Flipper.

**La via manuale:**

1. Compila con <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (Windows/Linux) o
   <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (macOS), oppure esegui `ufbt` nel terminale. Il `.fap` autonomo (con
   tutte le risorse) compare in `dist/`.
2. In qFlipper apri **File Manager → SD Card → apps → Examples** (crea la cartella se non esiste) e trascinaci il
   `.fap`.
3. Sul Flipper: `Main Menu → Apps → Examples → la tua app`.

**Risultato atteso:** una schermata con "Hello world" come intestazione e "I'm test_app!" sotto di essa. Premi un
pulsante qualsiasi per chiuderla.

::: warning La versione dell'SDK deve corrispondere
La versione dell'SDK (API) del firmware sul dispositivo deve corrispondere a quella dell'SDK con cui uFBT ha
compilato. Se all'avvio dell'app ottieni un errore di mancata corrispondenza delle API, aggiorna l'SDK di uFBT in modo
che corrisponda al tuo firmware, oppure flasha il firmware corrispondente con `ufbt flash_usb`. Su Unleashed,
assicurati che uFBT usi l'indice di Unleashed (vedi il suggerimento al passo 1) — altrimenti `ufbt flash_usb`
installerebbe il firmware **ufficiale**.
:::

Per vedere l'output di `FURI_LOG_I`: esegui `ufbt cli`, poi `log` (oppure `log info` se hai modificato il livello di
log predefinito).

## Risoluzione dei problemi

| Problema | Rimedio |
|---|---|
| `ufbt create` rifiuta l'APPID | Usa solo `a-z`, `0-9`, `_` |
| Mancata corrispondenza di API / SDK all'avvio | Aggiorna l'SDK di uFBT per il tuo firmware (indice Unleashed!) e ricompila |
| `ufbt launch` non trova il dispositivo | Chiudi qFlipper / Lab / qualunque terminale seriale; ricollega il cavo |
| L'app non è nel menu | Deve trovarsi in una cartella di categoria sotto `/ext/apps/`, per esempio `/ext/apps/Examples/` |
| Nel `log` non compare nulla | Avvia `log` **prima** di lanciare l'app; controlla il livello di log |

## Passi successivi

- Se il tuo C è un po' arrugginito, *The C Programming Language* di B. Kernighan e D. Ritchie è il riferimento
  classico.
- [Debug delle app](/it/dev/debugging) — procedi nella tua app con un debugger.
- [GUI nelle app](/it/dev/gui) — ViewPort, Views e Scenes.
- [Manifest delle app](/it/dev/app-manifests) — tutte le opzioni di `application.fam`.
- Non hai un PC? [Compila app su Android](/it/dev/android-build).
- Preferisci lo scripting? [JavaScript sul Flipper](/it/dev/js-about).
