---
title: "JavaScript: SDK e TypeScript"
sidebarTitle: "JS: SDK"
order: 220
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_developing_apps_using_js_sdk.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages]
sources: [unleashed-docs, unleashed-src]
---
# Sviluppare app con l'SDK JavaScript

Copiare uno script sul dispositivo con qFlipper dopo ogni modifica diventa noioso molto presto. Il **Flipper Zero JavaScript SDK** è un insieme di strumenti che elimina quei passaggi:

- **un solo comando** (`npm start`) compila l'app, la carica e la esegue;
- **completamento del codice** e controllo dei tipi (si scrive in TypeScript);
- un **minificatore JS** opzionale.

::: tip Unleashed
Unleashed ha un proprio fork dell'SDK: **`@darkflippers/fz-sdk-ul`**, creato con
**`@darkflippers/create-fz-app-ul`**. Aggiunge le definizioni di tipo per i
[moduli esclusivi di Unleashed](/it/dev/js-about#unleashed-extras) (`subghz`, `infrared`, `blebeacon`, `usbdisk`,
`i2c`, `spi`, `vgm`) e per le view aggiuntive della GUI. Gli script scritti per l'SDK ufficiale
(`@flipperdevices/fz-sdk`) funzionano anche su Unleashed. Se usi gli extra di Unleashed, proteggili con
`doesSdkSupport([...])` così la tua app continua a funzionare su altri firmware, oppure chiama
`checkSdkFeatures([...])` all'inizio se la funzionalità è indispensabile.
:::

## Installare l'SDK

L'SDK è distribuito come pacchetto NPM, quindi ti serve **Node.js** con un gestore di pacchetti (npm, pnpm o yarn). Questa guida usa npm.

1. Installa **Node.js + npm** dalla [pagina di download ufficiale](https://nodejs.org/en/download/package-manager).
2. Apri un terminale nella cartella in cui vuoi tenere il tuo progetto.
3. Crea un progetto dal template. La procedura guidata interattiva chiede il nome del progetto e il gestore di pacchetti:

```sh
# official SDK
npx @flipperdevices/create-fz-app@latest

# Unleashed SDK (recommended on Unleashed)
npx @darkflippers/create-fz-app-ul@latest
```

La cartella del progetto contiene ora l'app di esempio, il pacchetto dell'SDK, le dipendenze e i file di configurazione. Il tuo codice va in `index.ts`.

## Eseguire la tua app {#run}

1. Collega il Flipper Zero al PC via USB.
2. Apri un terminale nella cartella del progetto (`cd my-flip-app`).
3. Esegui:

```sh
npm start
```

L'SDK compila l'app, copia il file `.js` sul Flipper Zero e lo esegue. L'output di `print()` viene mostrato nel terminale.

![Output di npm start](/img/dev/js_sdk_npm_start.jpg)

## Aggiornare la tua app

Dopo aver modificato il codice, esegui di nuovo `npm start`. Se il Flipper è ancora collegato, il vecchio file `.js` sul dispositivo viene sostituito e parte la nuova versione.

## Configurazione: `fz-sdk.config.json5`

La configurazione del template (SDK Unleashed) si presenta così:

```js
{
    build: {
        // Where to put the compiled file
        output: "dist/<app_name>.js",

        // Whether to reduce the final file size at the cost of readability and
        // clarity of error messages
        minify: false,

        // Set this to `false` if you've thoroughly read the documentation and
        // are sure that you can use manual version checks to your advantage
        enforceSdkVersion: true,
    },

    upload: {
        // Where to grab the file from. If you're not doing any extra processing
        // after the SDK, this should match `build.output`
        input: "dist/<app_name>.js",

        // Where to put the file on the device
        output: "/ext/apps/Scripts/<app_name>.js",
    },
}
```

### Completamento del codice

Gli editor che supportano un Language Server (per esempio [VS Code](https://code.visualstudio.com/)) suggeriscono le funzioni dei moduli e i loro parametri mentre scrivi, quindi raramente devi cercare qualcosa nella documentazione.

![Completamento del codice in VS Code](/img/dev/js_sdk_code_completion.jpg)

### Minificatore JS

Il minificatore rimuove spazi, tabulazioni e interruzioni di riga e abbrevia i nomi delle variabili. Lo script diventa più piccolo e può essere un po' più rapido, ma i messaggi di errore diventano molto più difficili da leggere. Per questo è **disattivato per impostazione predefinita**. Per abilitarlo, imposta `minify: true` in `fz-sdk.config.json5`.

## Differenze rispetto al JS semplice del Flipper

Con l'SDK si scrive in **TypeScript**: completamento e avvisi sui tipi migliori, ma il codice ha un aspetto leggermente diverso.

- **Importazione dei moduli**
  - JS semplice: `let module = require("module");`
  - SDK: `import * as module from "@flipperdevices/fz-sdk/module";` (con l'SDK Unleashed: `"@darkflippers/fz-sdk-ul/module"`)
- **Più file sorgente.** L'SDK non supporta ancora più file `.ts` che si importano a vicenda. Puoi comunque usare `load()`, ma senza il controllo dei tipi.
- **Conversione dei valori.** Alcune funzioni restituiscono tipi generici. Per esempio `eventLoop.subscribe()` chiama la tua callback con un `Item` generico. Convertilo quando serve:
  - inline: `<string>item`
  - con una nuova variabile: `let text = item as string;`

`npm start` traspila il tuo codice in JavaScript semplice (e lo minifica, se l'opzione è attiva). Il file `.js` risultante in `dist/` è quello da condividere con altre persone.

## Pagine correlate

- [La tua prima app JS](/it/dev/js-first-app)
- [Usare i moduli JS](/it/dev/js-modules)
- [Funzioni integrate: compatibilità dell'SDK](/it/dev/js-builtin#sdk-compatibility)
