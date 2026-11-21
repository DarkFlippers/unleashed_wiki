---
title: Desktop
order: 60
original: [https://docs.flipper.net/zero/basics/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Desktop

Der Desktop ist der Startbildschirm. Hier lebt dein [Delfin](/de/start/dolphin), und oben läuft eine Statusleiste.
Vom Desktop aus öffnen einzelne Tastendrücke das Hauptmenü, das Archive, das Lock Menu und deine Favoriten-Apps.

## Statusleiste

Die obere Zeile zeigt kleine Symbole:

| Symbol | Bedeutung |
|---|---|
| Akku | Ladezustand. Beim Laden erscheint ein Blitz. Die Darstellung legt `Battery View` fest |
| SD-Karte | microSD ist eingebunden. Ein durchgestrichenes Symbol heißt, dass die Karte nicht eingebunden werden konnte: siehe [microSD-Karte](/de/start/sd-card) |
| Bluetooth | BLE ist an. Ein anderes Symbol bedeutet, dass ein Gerät verbunden ist |
| Schloss | Der Flipper ist gesperrt |
| Durchgestrichener Lautsprecher | Stealth-Modus: Ton und Vibration aus (siehe [Lock Menu](#lock-menu)) |
| PC | Über USB mit qFlipper / Flipper Lab verbunden |
| Gamepad | Dummy Mode ist an |
| Modul | Ein Erweiterungsmodul ist angeschlossen |
| Beacon | BLE-Beacon-Modus (zum Beispiel FindMy Flipper) |
| Hintergrund-App | Eine App läuft im Hintergrund |

::: tip Unleashed
- **Settings → Desktop → Battery View** wählt die Akkudarstellung: `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`,
  `Bar %`.
- **Settings → Desktop → Show Clock** = `ON` zeigt die Uhrzeit auf dem Desktop. Das Format (24h/12h) kommt aus
  **Settings → System → Time Format**.
:::

## Tasten auf dem Desktop

| Taste | Kurz drücken | Lang drücken |
|---|---|---|
| <kbd>OK</kbd> | **Main Menu** | Favorite App - Ok Long |
| <kbd>↑</kbd> | **Lock Menu** | **Sperren** (mit PIN, falls gesetzt) |
| <kbd>↓</kbd> | **Archive** | Geräteinfo / Debug-Bildschirm |
| <kbd>←</kbd> | Favorite App - Left Short (standardmäßig das Menü **Apps**) | Favorite App - Left Long |
| <kbd>→</kbd> | Standardmäßig **Passport** (Favorite App - Right Short) | Favorite App - Right Long |
| <kbd>BACK</kbd> | — | **Ausschaltbildschirm** |

### Geräte-Infobildschirm {#info-screen}

Langes Drücken von <kbd>↓</kbd> öffnet einen Infobildschirm: Firmware-Version und Build-Datum, Hardware-Version,
Laufzeit, Flipper-Name und ob Debug auf `ON` oder `OFF` steht.

![Geräte-Infobildschirm: Firmware-Version, Hardware-Version, Laufzeit und der Debug-Zustand](/screens/desktop/debug.png)

Auf diesem Bildschirm schaltet **langes Drücken von <kbd>OK</kbd> Debug ein oder aus** — derselbe Schalter wie
`Settings → System → Debug` ([Einstellungen](/de/start/settings)), nur ohne den Weg durch die Menüs. Kurzes
<kbd>BACK</kbd> führt zurück zum Desktop.

Debug `ON` zeigt Einträge, die sonst verborgen sind: den Tab **Internal** im [Archive](#archive) und
`Signal Settings` im Menü eines gespeicherten Sub-GHz-Signals ([Signal Settings](/de/subghz/signal-settings)).
Schalte es wieder aus, wenn du fertig bist — Debug-Einstellungen bremsen den Flipper und verhindern, dass er
einschläft.

## Main Menu

Drücke <kbd>OK</kbd>. Das Hauptmenü öffnet sich auf **Apps** (alle `.fap`-Apps von der SD-Karte, nach Kategorie
gruppiert), danach folgen **Sub-GHz**, **125 kHz RFID**, **NFC**, **Infrared**, **GPIO**, **iButton**, **Bad USB**,
**U2F**, **Clock**, und als letztes **Settings**. Die Liste ist umlaufend: <kbd>↑</kbd> auf **Apps** springt direkt
auf **Settings**.

![Hauptmenü mit markiertem Apps, darüber Settings und darunter Sub-GHz](/screens/mainmenu/main.png)

::: tip Menüstile
**Settings → Desktop → Menu Style** ändert das Aussehen des Hauptmenüs. Die Stile sind Plugins in
`/ext/apps_data/loader/plugins/` (Dateien, die mit `menu_style_` beginnen). `Default` ist die eingebaute Liste.
:::

## Lock Menu {#lock-menu}

Drücke <kbd>↑</kbd> auf dem Desktop. Navigiere mit <kbd>↑</kbd>/<kbd>↓</kbd> und drücke <kbd>OK</kbd>:

| Punkt | Funktion |
|---|---|
| **Turn Bluetooth On / Off** | Schaltet BLE um, ohne in die Einstellungen zu gehen |
| **Mute / Unmute** | Stealth-Modus: kein Ton, keine Vibration. Solange er aktiv ist, zeigen die Einstellungen **Volume** und **Vibro** den Wert `Stealth` |
| **Dummy Mode / Default Mode** | [Dummy Mode](#dummy-mode) betreten oder verlassen |

Mit <kbd>←</kbd> oder <kbd>→</kbd> im Lock Menu öffnest du die zweite Seite, die **Quick Settings**:

| Punkt | Bedienung |
|---|---|
| Brightness | <kbd>OK</kbd> zum Bearbeiten, dann <kbd>←</kbd>/<kbd>→</kbd> (oder <kbd>↑</kbd>/<kbd>↓</kbd>), in Schritten von 5 % |
| Volume | Genauso. Ein kurzer Piepton macht die neue Lautstärke hörbar |
| Vibro | <kbd>OK</kbd> schaltet sie direkt um |

<kbd>BACK</kbd> verlässt den gerade bearbeiteten Punkt, ein zweites <kbd>BACK</kbd> die Seite. Die Änderungen landen
in denselben Einstellungen wie unter **LCD and Notifications**.

::: tip Unleashed
Bei Unleashed ist **das Sperren selbst** ein langes Drücken von <kbd>↑</kbd> auf dem Desktop: mit PIN, falls einer
gesetzt ist, sonst als normale Sperre.
:::

## Sperren und PIN

- **Sperren:** halte <kbd>↑</kbd> auf dem Desktop. Ohne PIN sind nur die Tasten gesperrt. **Zum Entsperren drückst du
  dreimal schnell <kbd>BACK</kbd>.**
- **Mit PIN:** einrichten unter **Settings → Desktop → PIN Setup → Set PIN**. Eine PIN besteht aus 4 bis 10
  Pfeiltastendrücken. Der gesperrte Flipper fragt dann die PIN ab. Nach Fehlversuchen zeigt er `Wrong PIN!` und eine
  Wartezeit bis zum nächsten Versuch.
- **Auto Lock:** **Settings → Desktop → Auto Lock Time** (`OFF`, `10s` … `10min`) sperrt das Gerät nach dieser Zeit
  ohne Eingabe. **Auto Lock disarm by active USB session** = `ON` verhindert die automatische Sperre, solange der
  Flipper über USB verbunden ist.

::: warning Vergessene PIN
Eine vergessene PIN lässt sich nur zusammen mit allen Benutzereinstellungen zurücksetzen: siehe
[Wiederherstellung → Vergessenen PIN zurücksetzen](/de/start/recovery#reset-pin). Die Dateien auf der microSD-Karte
bleiben erhalten.
:::

## Dummy Mode {#dummy-mode}

Der Dummy Mode macht aus dem Flipper ein Spielzeug. Die meisten Funktionen sind versteckt, und die Tasten starten Apps
deiner Wahl, etwa Spiele. Einschalten über **Lock Menu → Dummy Mode**, ausschalten über **Lock Menu → Default Mode**.

Im Dummy Mode kann jede Taste ihre eigene App starten. Festgelegt wird das unter **Settings → Desktop**:

`DummyMode - Left`, `- Left Long`, `- Right`, `- Right Long`, `- Up Long`, `- Down`, `- Down Long`, `- Ok`, `- Ok Long`.

Eine nicht belegte Taste öffnet das Passport. Ein kurzes <kbd>↑</kbd> öffnet weiterhin das Lock Menu. Steht
`DummyMode - Up Long` auf `None`, sperrt ein langes <kbd>↑</kbd> das Gerät.

::: tip Unleashed
Die Stock-Firmware hat 4 Schnellzugriffe im Dummy Mode, Unleashed hat 9 (kurzes und langes Drücken auf jeder Taste).
So bleiben mehrere Spiele einen Tastendruck entfernt.
:::

## Favoriten-Apps (Schnellzugriff)

**Settings → Desktop → Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long**

Für jeden Platz hast du die Wahl:
- **Apps Menu (Default)** oder **Passport (Default)**: die eingebaute Vorgabe für diesen Platz;
- **None (disable)**: die Taste tut nichts;
- **Lock Flipper**;
- jede App aus dem Hauptmenü;
- **[Select App]**: eine beliebige `.fap`-Datei aus `/ext/apps/` auswählen.

## Archive

Drücke <kbd>↓</kbd>. Das Archive zeigt deine gespeicherten Dateien, in Tabs sortiert. Zwischen den Tabs wechselst du
mit <kbd>←</kbd>/<kbd>→</kbd>:

| Tab | Ordner / Inhalt |
|---|---|
| Favorites | Von dir angepinnte Dateien |
| iButton | `/ext/ibutton` (`.ibtn`) |
| NFC | `/ext/nfc` (`.nfc`) |
| Sub-GHz | `/ext/subghz` (`.sub`) |
| SubRem | `/ext/subghz_remote`: Belegungen für Sub-GHz Remote |
| RFID LF | `/ext/lfrfid` (`.rfid` und T5577-Dumps) |
| Infrared | `/ext/infrared` (`.ir`) |
| Bad USB | `/ext/badusb` (`.txt`) |
| Phone | `/ext/phonebook`: Telefonbuch für SIM800 (`.phone`) |
| U2F | U2F-Token |
| Apps | `/ext/apps` (`.fap` und `.js`) |
| Internal | Interner Speicher (nur bei **Debug** = `ON`) |
| Browser | Die ganze microSD-Karte |

Drücke <kbd>OK</kbd> auf einer Datei, um ihr Kontextmenü zu öffnen: ausführen/emulieren, **Pin**/**Unpin** (zu den
Favorites hinzufügen), **Rename**, **Delete**, und im Browser außerdem **Cut**, **Copy**, **Paste** und **NewDir**.
Im Tab Favorites hältst du <kbd>OK</kbd>, um das Menü zu öffnen.

::: tip Einstellungen zu den Favorites anpinnen
Halte in **Main Menu → Settings** auf einem beliebigen Eintrag <kbd>OK</kbd>, um ihn zu den Favorites anzupinnen. Du
kannst ihn dann aus dem Archive öffnen, ohne durch die Menüs zu gehen.
:::

## Passport

Drücke <kbd>→</kbd> auf dem Desktop oder öffne **Settings → Passport**. Dort stehen Name (der Flipper-Name), Laune und
Level des Delfins: siehe [Delfin](/de/start/dolphin).
