---
title: Einstellungen
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Einstellungen

**Main Menu → Settings** enthält diese Punkte, in der Reihenfolge, in der sie auf dem Gerät erscheinen:

**About** · **Bluetooth** · **Clock & Alarm** · **Desktop** · **Expansion Modules** · **Input** ·
**LCD and Notifications** · **Passport** · **Power** · **Storage** · **System**

In solchen Listen bewegst du dich mit <kbd>↑</kbd>/<kbd>↓</kbd>, änderst einen Wert mit <kbd>←</kbd>/<kbd>→</kbd> und
öffnest einen Punkt mit Unterbildschirm mit <kbd>OK</kbd>.

![Menü Settings: About, Bluetooth, Clock & Alarm, Desktop…](/screens/settings/menu.png)

::: tip Eine Einstellung zu den Favoriten hinzufügen
Halte <kbd>OK</kbd> auf einem beliebigen Punkt der Settings-Liste gedrückt, um ihn im Tab **Favorites** von Archive zu
verankern (oder von dort zu entfernen). So erreichst du ihn vom Desktop aus schnell mit <kbd>↓</kbd>.
:::

::: info
Die meisten Einstellungs-Apps (About, Bluetooth, Clock & Alarm, Desktop, Expansion Modules, Input,
LCD and Notifications, Passport) sind `.fap`-Dateien, die das Firmware-Update nach `/ext/apps/assets/` installiert.
**Power**, **Storage** und **System** sind fest in die Firmware eingebaut und funktionieren auch ohne SD-Karte.
:::

## About

Informationsbildschirme. Zwischen ihnen wechselst du mit **Next** (<kbd>→</kbd>) und **Prev.** (<kbd>←</kbd>):

1. Hinweis zur **Unleashed Firmware**: nur für experimentelle Zwecke, nicht für illegale Nutzung;
2. Lizenz: die Firmware ist frei und Open Source, und *„If you paid any money for it - you got scammed.“*;
3. *„Community apps included in all builds except `c` build“* und ein Link zu github.com/DarkFlippers;
4. Produkt, Modell, FCC ID / IC;
5. Link zur Konformität und Herstelleradresse;
6. **HW Version Info**: Hardware-Version, Region, Flipper-Name, Seriennummer;
7. **FW Version Info**: Version und Build-Datum, Git-Hash, API-Version, Radio-Stack, Target und Branch.

## Bluetooth

| Menüpunkt | Werte / Aktion |
|---|---|
| **Bluetooth** | `ON` / `OFF`. Zeigt `Broken`, wenn der Radio-Stack beschädigt ist ([Wiederherstellung](/de/start/recovery)) |
| **Unpair All Devices** | Mit **Unpair** bestätigen. Entfernt alle Kopplungen, auch die Kopplungsschlüssel für Bad USB über Bluetooth (BadKB), Bluetooth Remote und Authenticator |

Nutze **Unpair All Devices**, wenn sich die mobile App nach einer Installation oder einer Namensänderung nicht mehr
verbindet. Siehe [FAQ](/de/start/faq).

## Clock & Alarm

Ein Bildschirm mit drei Zeilen: **Time** (hh:mm:ss), **Date** (tt.mm.jjjj) und **Alarm** (hh:mm, `On`/`Off`).

1. Wähle eine Zeile mit <kbd>↑</kbd>/<kbd>↓</kbd> und ein Feld mit <kbd>←</kbd>/<kbd>→</kbd>.
2. Drücke <kbd>OK</kbd>, um zu bearbeiten, und ändere den Wert mit <kbd>↑</kbd>/<kbd>↓</kbd>.
3. Drücke <kbd>OK</kbd> oder <kbd>BACK</kbd>, um die Bearbeitung zu beenden.

Wenn der Alarm klingelt, **verschiebt** <kbd>BACK</kbd> ihn um 9 Minuten, jede andere Taste stoppt ihn. Ein Alarm, den
niemand stoppt, schaltet sich nach 10 Minuten selbst ab. Die App **Clock** im Hauptmenü zeigt eine große Uhr und hat
Helligkeitsregler, den Alarm und einen Timer.

## Desktop

| Menüpunkt | Werte | Beschreibung |
|---|---|---|
| **PIN Setup** | → Untermenü | **Set PIN** / **Change PIN** / **Remove PIN**. Ein PIN besteht aus 4–10 Tastendrücken auf dem Pad |
| **Auto Lock Time** | `OFF`, `10s`, `15s`, `30s`, `60s`, `90s`, `2min`, `5min`, `10min` | Sperren nach Inaktivität |
| **Auto Lock disarm by active USB session** | `OFF` / `ON` | Keine automatische Sperre, solange USB verbunden ist |
| **Battery View** | `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %` | Darstellung des Akkusymbols |
| **Show Clock** | `OFF` / `ON` | Uhr auf dem Desktop |
| **Menu Style** | `Default` + installierte Styles | Aussehen des Hauptmenüs. Styles sind `menu_style_*`-Plugins in `/ext/apps_data/loader/plugins/`. Zeigt `Missing`, wenn die gewählte Style-Datei gelöscht wurde |
| **Change Flipper Name** | Text | [Eigener Flipper-Name](/de/start/custom-name) |
| **Happy Mode** | Enable / Disable | Der Delfin wird nie wütend ([Delfin](/de/start/dolphin)) |
| **Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long** | App | Apps für den Schnellzugriff vom Desktop |
| **DummyMode - Left / Left Long / Right / Right Long / Up Long / Down / Down Long / Ok / Ok Long** | App | Apps für [Dummy Mode](/de/start/desktop#dummy-mode) |

Für jeden Favorite-/Dummy-Slot kannst du **Apps Menu (Default)** oder **Passport (Default)**, **None (disable)**,
**Lock Flipper**, eine beliebige App aus dem Hauptmenü oder **[Select App]** wählen — damit jede `.fap` aus
`/ext/apps/`.

::: warning PIN
Der Einrichtungsbildschirm warnt: *„Forgotten PIN can only be reset with entire device.“* Das Zurücksetzen des PIN
löscht auch deine Einstellungen (Dateien auf der SD-Karte bleiben erhalten): siehe
[Wiederherstellung](/de/start/recovery#reset-pin).
:::

::: tip Unleashed
Change Flipper Name, Battery View, Show Clock und die 9 Dummy-Mode-Slots sind Ergänzungen von Unleashed.
:::

## Expansion Modules

| Menüpunkt | Werte | Beschreibung |
|---|---|---|
| **Listen UART** | `USART` (Pins 13, 14), `LPUART` (Pins 15, 16), `None` | Welcher UART auf Module lauscht, die das Expansion-Protokoll verwenden (zum Beispiel das [Video Game Module](/de/gpio/video-game-module)) |

Setz es auf `None`, wenn du solche Module nicht nutzt. Das spart Energie und erlaubt dem Flipper, einzuschlafen.

## Input

| Menüpunkt | Werte | Beschreibung |
|---|---|---|
| **Buttons Vibro** | `OFF`, `1`…`9` | Vibration als Rückmeldung auf Tastenereignisse. Höhere Werte geben einen längeren Impuls |
| **Vibro Trigger** | `Press`, `Release`, `Both` | Wann die Rückmeldung ausgelöst wird |

## LCD and Notifications

| Menüpunkt | Werte | Beschreibung |
|---|---|---|
| **LCD Contrast** | `-10` … `+18` | Kontrast des Displays |
| **LCD Backlight** | `0%` … `100%` (Schritt 5 %) | Helligkeit der Hintergrundbeleuchtung |
| **Backlight Time** | `Always ON`, `2s`, `5s`, `10s`, `15s`, `30s`, `60s`, `90s`, `120s`, `5min`, `10min`, `30min` | Abschaltzeit der Beleuchtung |
| **Night Shift** | `OFF`, `-10%` … `-60%` | Dimmt die Beleuchtung im Nachtzeitraum um diesen Betrag |
| **. Start** | `17:00` … `23:30` | Beginn des Nachtzeitraums (gesperrt, solange Night Shift `OFF` ist) |
| **. End** | `05:00` … `11:30` | Ende des Nachtzeitraums |
| **LED Brightness** | `0%` … `100%` | Helligkeit der Status-LED |
| **Volume** | `0%` … `100%` | Lautstärke des Lautsprechers (`Stealth`, wenn über das Lock Menu stummgeschaltet) |
| **Vibro** | `OFF` / `ON` | Vibration (`Stealth`, wenn stummgeschaltet) |
| **LCD Inversion** | `OFF` / `ON` | Invertiert die Displayfarben |
| **RGB Mod Settings** | → Untermenü | Nur für Flipper mit dem **Hardware-Mod** für RGB-Beleuchtung |

**RGB Mod Settings** (<kbd>OK</kbd> auf dem Punkt): **RGB backlight installed** (`OFF`/`ON`). Die übrigen Punkte
bleiben gesperrt (`RGB MOD OFF!`), bis das auf `ON` steht: **LED 1 Color**, **LED 2 Color**, **LED 3 Color**,
**Effects** (`OFF`, `Rainbow`, `Wave`), **. Speed** (`0.1s`…`1s`), **. Color step** (`1`–`3`), **. Saturation**,
**. Wave wide** (`1`–`3`).

::: danger RGB mod
Schalte **RGB backlight installed** **nur** dann ein, wenn dein Flipper den
[Hardware-Mod für RGB-Beleuchtung](https://github.com/quen0n/flipperzero-firmware-rgb#readme) hat. Auf einem
unveränderten Flipper hört die Beleuchtung sonst auf zu funktionieren. Falls das passiert ist, geh hierher zurück und
setz den Wert auf `OFF` (siehe [FAQ](/de/start/faq#backlight-does-not-work)).
:::

## Passport

Das Profil des Delfins: Name, Laune und Level. Lässt sich auch mit <kbd>→</kbd> vom Desktop aus öffnen. Siehe
[Delfin](/de/start/dolphin).

## Power

| Menüpunkt | Werte | Beschreibung |
|---|---|---|
| **Battery Info** | — | Ladezustand, Spannung, Strom, Temperatur, Akkuzustand |
| **Reboot** | **Firmware Upgrade** / **Reboot Flipper** | Neustart in den DFU-Modus (`Reboot to DFU Mode?`) oder normaler Neustart |
| **Power OFF** | — | Ausschalten |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` | Abschalten nach Inaktivität |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` | Laden auf diesem Stand beenden |

Mehr dazu: [Stromversorgung und Akku](/de/start/power).

## Storage

| Menüpunkt | Beschreibung |
|---|---|
| **About Internal Storage** | Infos zum internen Speicher (`Virtual (/.int on SD)`) und freier Flash |
| **About SD Card** | Label, Typ, Größe, freier Speicher, Hersteller und Seriennummer der Karte |
| **Unmount SD Card** / **Mount SD Card** | Sicher entnehmen / wieder einbinden |
| **Format SD Card** | Karte löschen und formatieren |
| **Benchmark SD Card** | Geschwindigkeitstest über SPI |
| **Factory Reset** | **Erase** 5-mal drücken. Löscht den internen Speicher und startet neu |

Mehr dazu: [microSD-Karte](/de/start/sd-card), [Wiederherstellung](/de/start/recovery#factory-reset).

## System

| Menüpunkt | Werte | Beschreibung |
|---|---|---|
| **Hand Orient** | `Righty` / `Lefty` | Linkshänder-Modus: dreht das Display und belegt die Tasten um |
| **Units** | `Metric` / `Imperial` | Einheiten (zum Beispiel °C/°F in Battery Info) |
| **Time Format** | `24h` / `12h` | Format der Uhrzeit |
| **Date Format** | `D/M/Y`, `M/D/Y`, `Y/M/D` | Format des Datums |
| **Log Level** | `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace` | Wie viel protokolliert wird. `Default` = `Info` |
| **Log Device** | `USART`, `LPUART`, `None` | UART für die Logs (USART = Pins 13/14, LPUART = Pins 15/16) |
| **Log Baud Rate** | `9600` … `1843200` | Baudrate des Log-UART |
| **Debug** | `OFF` / `ON` | Debug-Modus: zusätzliche Debug-Funktionen in Apps, der Tab **Internal** in Archive, SWD-Zugriff |
| **Heap Trace** | `None`, `Main` | Nachverfolgung von Speicherzuweisungen (für Entwickler) |
| **Sleep Method** | `Default` / `Legacy` | `Legacy` braucht mehr Energie (~9 mA statt ~1,5 mA), kann aber stabiler sein |
| **File Naming** | `Default` / `Detailed` | `Detailed` schreibt Typ, Datum und Uhrzeit in die Namen neuer Dateien |

![Settings → System: Hand Orient Righty, Units Metric, Time Format 24h, Date Format D/M/Y…](/screens/settings/system.png)

Für **Debug** gibt es eine Abkürzung: halte <kbd>↓</kbd> auf dem Desktop gedrückt, dann <kbd>OK</kbd> auf dem
Infobildschirm ([Desktop → Geräte-Infobildschirm](/de/start/desktop#info-screen)).

::: warning Flipper zu langsam?
Halte für den normalen Betrieb **Log Level** = `None` (oder `Default`), **Debug** = `OFF` und **Heap Trace** = `None`.
Debug-Einstellungen bremsen das Gerät und verhindern, dass es einschläft.
:::

## Siehe auch

- [Desktop](/de/start/desktop) — was die Desktop-Einstellungen in der Praxis bewirken
- [Eigener Flipper-Name](/de/start/custom-name)
- [Sub-GHz-Einstellungen](/de/subghz/settings) — die Funkeinstellungen in der Sub-GHz-App
