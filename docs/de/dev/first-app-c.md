---
title: Deine erste App in C
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_your_first_app_in_c.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md]
sources: [unleashed-docs]
---
# Deine erste App in C

In diesem Tutorial richtest du eine Entwicklungsumgebung mit **uFBT** ein, erzeugst eine App-Vorlage, ergänzt eine
einfache GUI und baust die App und führst sie auf deinem Flipper Zero aus.

So gebaute Apps sind `.fap`-Dateien (Flipper App Package) — sie liegen auf der microSD-Karte und werden bei Bedarf
geladen, du musst also die Firmware nicht neu bauen.

## 1. Die Umgebung einrichten

Du brauchst einen Flipper Zero, ein USB-Kabel und unter Windows / macOS / Linux:

- [**uFBT**](https://github.com/flipperdevices/flipperzero-ufbt) ("micro Flipper Build Tool") — eine Variante von
  [fbt](/de/dev/fbt) mit allem, was für die App-Entwicklung nötig ist. Installiere es mit `pip install ufbt`
  (Details in der uFBT-README).
- [**Visual Studio Code**](https://code.visualstudio.com/) — die empfohlene IDE. Andere funktionieren auch,
  brauchen aber manuelle Konfiguration für die Integration mit uFBT.

::: tip Unleashed
uFBT lädt standardmäßig das **offizielle** SDK herunter. Um für Unleashed zu bauen, führe einmal Folgendes aus
(und verwende dieselben Flags bei jedem späteren Update):

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Verwende `--channel=release`, wenn auf deinem Flipper ein Release-Build läuft. Die SDK-Version muss zur Firmware
auf dem Gerät passen — siehe [Schritt 5](#_5-build-and-run-the-app).
:::

## 2. Eine App-Vorlage erzeugen

1. Erstelle einen Ordner für die App, z. B. `test_app`.
2. Öffne ein Terminal in diesem Ordner und führe aus:

   ```sh
   ufbt create APPID=test_app
   ```

   uFBT erzeugt die Dateistruktur.
3. Führe aus:

   ```sh
   ufbt vscode_dist
   ```

   Das konfiguriert VS Code so, dass du die App direkt aus der IDE bauen und debuggen kannst.

::: warning
`APPID` darf nur Kleinbuchstaben `a-z`, Ziffern `0-9` und `_` enthalten.
:::

Die entstehende Struktur:

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

| Datei | Zweck |
|---|---|
| `application.fam` | Das App-Manifest, das uFBT liest, um zu wissen, wie die App gebaut wird — siehe [App-Manifeste](/de/dev/app-manifests) |
| `test_app.c` | Haupt-Quelldatei mit dem Einstiegspunkt |
| `test_app.png` | App-Icon (10×10, 1 Bit) |
| `.github/workflows/build.yml` | GitHub-Actions-Konfiguration — [mehr dazu](https://github.com/marketplace/actions/build-flipper-application-package-fap) |
| `images/` | Deine Bild-Assets |
| `images/.gitkeep` | Platzhalter, damit Git den leeren Ordner `images/` verfolgt |

## 3. Der Code der Vorlage

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

Was die einzelnen Teile tun:

- `#include <furi.h>` — der Haupt-Header von **Furi**, dem Kern der Flipper-Firmware
  ([Furi-API](/de/dev/furi-api)).
- `#include <test_app_icons.h>` — nötig, wenn die App Bilder verwendet. uFBT wandelt PNGs aus `images/` in das
  interne Format des Flipper um und erzeugt diesen Header automatisch.
- `int32_t` — der übliche Rückgabetyp der Hauptfunktion einer App.
- `UNUSED(p);` — ein Makro, das die Warnung "unused parameter" unterdrückt.
- `FURI_LOG_I` — schreibt eine Meldung mit Level `info` in das Flipper-Log. Beobachte es über `ufbt cli` →
  `log info`.
- `return 0;` — Erfolg, nach C-Konvention.

## 4. Eine GUI ergänzen

Öffne den App-Ordner in VS Code (**File → Open Folder…**). Installiere die vorgeschlagenen Erweiterungen, wenn du
gefragt wirst.

Zeigen wir zwei Zeilen auf dem Display an: `Hello world` und `I'm test_app!`. Ersetze den Inhalt von `test_app.c`
durch:

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

Das nutzt den GUI-Dienst **Dialogs**, die einfachste GUI-API. Andere Ansätze sind in
[GUI in Apps](/de/dev/gui) beschrieben.

## 5. Die App bauen und ausführen {#_5-build-and-run-the-app}

**Der schnelle Weg:**

1. Verbinde den Flipper über das USB-Kabel mit deinem Computer.
2. Schließe qFlipper und jedes andere Programm, das den seriellen Port des Flipper benutzt.
3. Führe aus:

   ```sh
   ufbt launch
   ```

   Es baut die App, überträgt sie und startet sie auf dem Flipper.

**Der manuelle Weg:**

1. Baue mit <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (Windows/Linux) oder
   <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (macOS) oder führe `ufbt` im Terminal aus. Die eigenständige
   `.fap` (mit allen Ressourcen) erscheint in `dist/`.
2. Öffne in qFlipper **File Manager → SD Card → apps → Examples** (erstelle den Ordner, falls nötig) und zieh die
   `.fap` dorthin.
3. Auf dem Flipper: `Main Menu → Apps → Examples → deine App`.

**Erwartetes Ergebnis:** ein Bildschirm mit "Hello world" als Kopfzeile und "I'm test_app!" darunter. Drücke eine
beliebige Taste, um ihn zu schließen.

::: warning Die SDK-Version muss passen
Die SDK-Version (API) der Firmware auf dem Gerät muss zu dem SDK passen, gegen das uFBT gebaut hat. Erhältst du
beim Start der App einen API-Konfliktfehler, aktualisiere entweder das SDK von uFBT passend zu deiner Firmware oder
flashe die passende Firmware mit `ufbt flash_usb`. Achte bei Unleashed darauf, dass uFBT den Unleashed-Index
verwendet (siehe den Tipp in Schritt 1) — sonst würde `ufbt flash_usb` die **offizielle** Firmware installieren.
:::

Um die Ausgabe von `FURI_LOG_I` zu sehen: führe `ufbt cli` aus und dann `log` (oder `log info`, wenn du das
Standard-Log-Level geändert hast).

## Fehlerbehebung

| Problem | Lösung |
|---|---|
| `ufbt create` lehnt die APPID ab | Nur `a-z`, `0-9`, `_` verwenden |
| API-/SDK-Konflikt beim Start | Das SDK von uFBT passend zu deiner Firmware aktualisieren (Unleashed-Index!) und neu bauen |
| `ufbt launch` findet das Gerät nicht | qFlipper / Lab / jedes serielle Terminal schließen; das Kabel neu anstecken |
| Die App steht nicht im Menü | Sie muss in einem Kategorie-Ordner unter `/ext/apps/` liegen, z. B. `/ext/apps/Examples/` |
| Nichts im `log` | `log` **vor** dem Start der App starten; das Log-Level prüfen |

## Wie geht es weiter?

- Wenn dein C eingerostet ist, ist *The C Programming Language* von B. Kernighan und D. Ritchie die klassische
  Referenz.
- [Apps debuggen](/de/dev/debugging) — mit einem Debugger durch deine App schreiten.
- [GUI in Apps](/de/dev/gui) — ViewPort, Views und Scenes.
- [App-Manifeste](/de/dev/app-manifests) — alle Optionen von `application.fam`.
- Kein PC? [Apps unter Android bauen](/de/dev/android-build).
- Lieber Skripte? [JavaScript auf dem Flipper](/de/dev/js-about).
