---
title: "JavaScript: SDK und TypeScript"
sidebarTitle: "JS: SDK"
order: 220
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_developing_apps_using_js_sdk.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages]
sources: [unleashed-docs, unleashed-src]
---
# Apps mit dem JavaScript-SDK entwickeln

Nach jeder Änderung ein Skript mit qFlipper auf das Gerät zu kopieren wird schnell mühsam. Das **Flipper Zero
JavaScript SDK** ist eine Werkzeugsammlung, die diese Schritte überflüssig macht:

- **ein Befehl** (`npm start`) baut die App, überträgt sie und führt sie aus;
- **Code-Vervollständigung** und Typprüfung (du schreibst TypeScript);
- ein optionaler **JS-Minifier**.

::: tip Unleashed
Unleashed hat einen eigenen Fork des SDK: **`@darkflippers/fz-sdk-ul`**, erzeugt mit
**`@darkflippers/create-fz-app-ul`**. Er ergänzt Typdefinitionen für die
[Unleashed-exklusiven Module](/de/dev/js-about#unleashed-extras) (`subghz`, `infrared`, `blebeacon`, `usbdisk`,
`i2c`, `spi`, `vgm`) und die zusätzlichen GUI-Views. Skripte, die für das offizielle SDK
(`@flipperdevices/fz-sdk`) geschrieben wurden, laufen ebenfalls auf Unleashed. Wenn du Unleashed-Extras nutzt,
sichere sie mit `doesSdkSupport([...])` ab, damit deine App auch auf anderen Firmwares funktioniert, oder rufe zu
Beginn `checkSdkFeatures([...])` auf, wenn das Feature unverzichtbar ist.
:::

## Das SDK installieren

Das SDK wird als NPM-Paket verteilt, du brauchst also **Node.js** mit einem Paketmanager (npm, pnpm oder yarn).
Diese Anleitung verwendet npm.

1. Installiere **Node.js + npm** von der
   [offiziellen Downloadseite](https://nodejs.org/en/download/package-manager).
2. Öffne ein Terminal in dem Ordner, in dem du dein Projekt ablegen willst.
3. Erzeuge ein Projekt aus der Vorlage. Der interaktive Assistent fragt nach dem Projektnamen und dem
   Paketmanager:

```sh
# official SDK
npx @flipperdevices/create-fz-app@latest

# Unleashed SDK (recommended on Unleashed)
npx @darkflippers/create-fz-app-ul@latest
```

Der Projektordner enthält jetzt die Vorlagen-App, das SDK-Paket, die Abhängigkeiten und die Konfigurationen. Dein
Code kommt in `index.ts`.

## Deine App ausführen {#run}

1. Verbinde den Flipper Zero über USB mit deinem PC.
2. Öffne ein Terminal im Projektordner (`cd my-flip-app`).
3. Führe aus:

```sh
npm start
```

Das SDK kompiliert die App, kopiert die `.js`-Datei auf den Flipper Zero und führt sie aus. Die Ausgabe von
`print()` erscheint im Terminal.

![Ausgabe von npm start](/img/dev/js_sdk_npm_start.jpg)

## Deine App aktualisieren

Führe nach einer Codeänderung erneut `npm start` aus. Solange der Flipper noch verbunden ist, wird die alte
`.js`-Datei auf dem Gerät ersetzt und die neue Version gestartet.

## Konfiguration: `fz-sdk.config.json5`

Die Konfiguration der Vorlage (Unleashed-SDK) sieht so aus:

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

### Code-Vervollständigung

Editoren mit Language-Server-Unterstützung (zum Beispiel [VS Code](https://code.visualstudio.com/)) schlagen während
des Tippens Modulfunktionen und deren Parameter vor, sodass du selten etwas nachschlagen musst.

![Code-Vervollständigung in VS Code](/img/dev/js_sdk_code_completion.jpg)

### JS-Minifier

Der Minifier entfernt Leerzeichen, Tabulatoren und Zeilenumbrüche und kürzt Variablennamen. Das Skript wird kleiner
und kann etwas schneller laufen, aber Fehlermeldungen werden deutlich schwerer zu lesen. Deshalb ist er
**standardmäßig aus**. Setze zum Aktivieren `minify: true` in `fz-sdk.config.json5`.

## Unterschiede zu einfachem Flipper-JS

Mit dem SDK schreibst du **TypeScript**: bessere Vervollständigung und Typwarnungen, aber der Code sieht etwas
anders aus.

- **Module importieren**
  - einfaches JS: `let module = require("module");`
  - SDK: `import * as module from "@flipperdevices/fz-sdk/module";` (beim Unleashed-SDK:
    `"@darkflippers/fz-sdk-ul/module"`)
- **Mehrere Quelldateien.** Das SDK unterstützt noch nicht mehrere `.ts`-Dateien, die sich gegenseitig importieren.
  Du kannst weiterhin `load()` verwenden, allerdings ohne Typprüfung.
- **Werte casten.** Manche Funktionen geben generische Typen zurück. `eventLoop.subscribe()` ruft deinen Callback
  zum Beispiel mit einem generischen `Item` auf. Caste ihn, wenn nötig:
  - inline: `<string>item`
  - mit einer neuen Variablen: `let text = item as string;`

`npm start` übersetzt deinen Code in einfaches JavaScript (und minifiziert ihn, falls aktiviert). Die daraus
entstehende `.js`-Datei in `dist/` ist die, die du an andere weitergibst.

## Verwandte Themen

- [Deine erste JS-App](/de/dev/js-first-app)
- [JS-Module verwenden](/de/dev/js-modules)
- [Eingebaute Funktionen: SDK-Kompatibilität](/de/dev/js-builtin#sdk-compatibility)
