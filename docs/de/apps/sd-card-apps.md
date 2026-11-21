---
title: Apps auf der SD-Karte (.fap)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Apps auf der SD-Karte (.fap)

Fast jede App, die du über `Main Menu → Apps` startest, ist ein **FAP** (Flipper App Package): eine
`.elf`-Programmdatei mit zusätzlichen Metadaten (Name, Icon, Kategorie, benötigte API-Version) und optional
mitgelieferten Ressourcen. FAPs liegen auf der microSD-Karte, deshalb **brauchen Apps eine SD-Karte**, um zu laufen.

## Wo Apps liegen

| Pfad | Was dort liegt |
|---|---|
| `/ext/apps/<Category>/*.fap` | installierte Apps, ein Ordner pro Kategorie (`Sub-GHz`, `NFC`, `RFID`, `GPIO`, `USB`, `Bluetooth`, `Games`, `Tools`, ...) |
| `/ext/apps_data/<appid>/` | Daten und Einstellungen, die jede App für sich speichert |
| `/ext/apps_data/loader/plugins/` | Loader-Plugins, zum Beispiel die [Hauptmenü-Stile](/de/apps/menu-styles) |

`Main Menu → Apps` zeigt einfach die Ordner unter `/ext/apps` an. Der Tab **Apps** im
[Archive](/de/apps/archive) listet denselben Ordner auf und zeigt außerdem `.js`-Skripte.

## Wie der Flipper ein FAP ausführt

Der Mikrocontroller kann Code nicht direkt vom externen Speicher ausführen. Wenn du eine App startest, geht der
**App Loader** so vor:

1. er liest das FAP von der SD-Karte und prüft seine Integrität und sein Manifest;
2. er prüft, ob die **Major-API-Version** der App mit der Major-API-Version der Firmware übereinstimmt;
3. er kopiert die Code- und Datensektionen ins RAM und korrigiert die Adressen für den neuen Ort (Relocation);
4. er löst jede von der App importierte Funktion über die **Symboltabelle** der Firmware auf;
5. er startet die App.

Weil die App aus dem RAM läuft, bleibt bei einer großen App weniger Heap für alles Übrige. Es werden nur Code und
Daten geladen, deshalb ist der belegte RAM kleiner als die Größe der `.fap`-Datei.

::: tip Unleashed
Unleashed behält die offizielle API bei (die aktuelle API-Version steht oben in jedem Changelog, zum Beispiel
`Current API: 88.27`), deshalb laufen die meisten Apps aus dem offiziellen Katalog unverändert. Weicht die
Major-API-Version ab, verweigert Unleashed nicht sofort: es zeigt **App Too Old** oder **App Too New** mit den beiden
Versionen (zum Beispiel `APP:86 < FW:88`) und eine **Continue**-Schaltfläche, sodass du es trotzdem versuchen kannst.
Siehe [Probleme mit Apps](/de/apps/troubleshoot).
:::

## Apps installieren

### Aus den App-Packs

Am einfachsten ist es, einen Firmware-Build zu nehmen, der schon ein Pack enthält (Standard- oder `e`-Build), siehe
[Apps im Lieferumfang von Unleashed](/de/apps/catalog).

Beide Packs kommen aus [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Ein Pack von Hand hinzufügen:

1. Die `.zip` von der [Releases-Seite](https://github.com/xMasterX/all-the-plugins/releases/latest) laden.
2. Entpacken.
3. Die App-Ordner in den Ordner `apps` auf der SD-Karte (`/ext/apps/`) kopieren, mitsamt ihren Kategorie-Ordnern.
4. Prüfen, dass die API-Version des Packs zur Firmware passt (`Current API:` oben im Changelog).

### Aus dem offiziellen Katalog {#installing-from-the-official-catalog}

Der offizielle Apps Catalog steckt in [Flipper Lab](https://lab.flipper.net/apps) (Chrome, Edge und andere
Chromium-Browser mit Web Serial) und im Tab **Apps** der [Flipper-Mobil-App](/de/mobile/mobile-app).

1. Schließe qFlipper und jeden weiteren Flipper-Lab-Tab (nur ein Programm kann den USB-Serial-Port belegen).
2. Verbinde den Flipper über USB (Flipper Lab) oder Bluetooth (Mobil-App).
3. Öffne **Apps** und finde die App über die Kategorie oder die Suche.
4. Drücke **Install** auf der App-Karte oder auf ihrer Seite und warte, bis sie übertragen ist.
5. Öffne auf dem Flipper `Main Menu → Apps → <category> → <app>`.

Um Katalog-Apps zu aktualisieren oder zu löschen, öffne **Apps → Installed** und drücke **Update** oder das
Löschsymbol (Papierkorb).

Wenn die Installation fehlschlägt: prüfe die Verbindung, schaffe Platz auf der SD-Karte (lösche Dateien im
[Archive](/de/apps/archive)) und vergewissere dich, dass die Firmware aktuell ist.

### Von Hand (jedes `.fap`)

1. Lade das `.fap` herunter, das für deine Firmware gebaut wurde (ein Unleashed-Build oder ein OFW-Build mit
   passender API-Version).
2. Kopiere es mit [qFlipper](/de/mobile/qflipper), dem Dateimanager der Mobil-App oder einem Kartenleser nach
   `/ext/apps/<Category>/`.
3. Starte es über `Main Menu → Apps` oder öffne die Datei im [Archive](/de/apps/archive) und wähle **Run**.

::: warning
Apps, die für einen anderen Firmware-Fork gebaut wurden, importieren möglicherweise Funktionen, die Unleashed nicht
exportiert, und scheitern dann mit **Missing Imports**. Nimm Apps aus den Unleashed-Packs oder baue sie gegen das
Unleashed-SDK neu.
:::

## Ein eigenes FAP bauen

FAPs werden genau wie eingebaute Apps entwickelt. Kurz gefasst:

1. Lege deinen App-Ordner in `applications_user/` eines Firmware-Checkouts ab.
2. Setze in dessen `application.fam` `apptype=FlipperAppType.EXTERNAL` (siehe [App-Manifeste](/de/dev/app-manifests)).
3. Baue mit einem dieser Befehle:

```bash
./fbt fap_{APPID}                                     # build one app
./fbt launch APPSRC=applications_user/path/to/app     # build, upload over USB and run
./fbt build APPSRC=applications_user/path/to/app      # build without uploading
./fbt faps                                            # build all FAPs (or ./fbt fap_dist)
```

Im Standard-VS-Code-Profil ist `launch` die Aktion **Launch App on Flipper**
(<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>).

**Assets.** Lege Bilder in einen Unterordner der App und nenne diesen in `fap_icon_assets`; danach
`#include "{APPID}_icons.h"` und verwende sie wie Icons aus `assets_icons.h`.

**API-Versionierung.** Nicht jede Firmware-Funktion steht Apps zur Verfügung: der exportierte Satz ist in der
`api_symbols.csv` des Hardware-Targets aufgelistet. Die Major-Version wächst bei inkompatiblen Änderungen (eine
Funktion oder Variable entfernt, eine Signatur geändert), die Minor-Version bei Ergänzungen. `fbt` verwaltet das
automatisch: neue Symbole erscheinen mit `?`, und du musst jedes davon mit `+` (exportiert) oder `-` (versteckt)
markieren, bevor die Firmware baut.

**Debugging.** `fbt` lädt `debug/flipperapps.py` in gdb, sodass du ein FAP wie Firmware-Code debuggen kannst. Baue
und flashe die Firmware (`./fbt`, `./fbt flash`), starte dein FAP und hänge dich dann mit `./fbt debug` an. Die
Firmware hält direkt nach dem Laden des FAP an einem Breakpoint, sodass du Breakpoints darin setzen kannst.
Build-Typ von Firmware und App (debug/release) müssen übereinstimmen, und der passende Build muss als
`build/latest` verlinkt sein.

Mehr dazu in [Die Firmware bauen](/de/dev/build), [fbt](/de/dev/fbt) und
[Deine erste App in C](/de/dev/first-app-c).

## Verwandte Seiten

- [Apps im Lieferumfang von Unleashed](/de/apps/catalog)
- [Probleme mit Apps](/de/apps/troubleshoot)
- [Archive (Dateibrowser)](/de/apps/archive)
