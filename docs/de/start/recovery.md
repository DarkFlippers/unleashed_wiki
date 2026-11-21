---
title: Wiederherstellung
order: 130
original: [https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://docs.flipper.net/zero/basics/firmware-update/storage-repair, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings]
sources: [flipper-docs, unleashed-docs, unleashed-src]
---
# Wiederherstellung

Was zu tun ist, wenn der Flipper hängt, sich nicht aktualisieren lässt, nichts anzeigt oder du den PIN vergessen hast.
Arbeite die Schritte der Reihe nach ab, vom sanftesten zum drastischsten.

## 1. Erst neu starten

- **Hängt:** halte <kbd>←</kbd> + <kbd>BACK</kbd> etwa 5 Sekunden gedrückt.
- **Hängt weiterhin:** zieh USB ab und halte <kbd>BACK</kbd> 30 Sekunden gedrückt (Power-Reset).
- **Leerer Akku:** lade ihn einige Minuten (oder eine Stunde) und versuch es erneut.
- Auf einem funktionierenden Flipper: **Settings → Power → Reboot → Reboot Flipper**.

Alle Kombinationen: [Tastenkombinationen](/de/start/key-combos).

## 2. Firmware-Wiederherstellung aus dem DFU-Modus {#firmware-recovery}

Nimm diesen Weg, wenn die Firmware beschädigt ist: das Update schlägt fehl, der Bildschirm zeigt Müll oder nichts, oder
die Tasten reagieren nicht. Der USB-DFU-Bootloader flasht die Firmware ohne das Betriebssystem des Geräts.

### Schritt 1: den Flipper in den DFU-Modus (Recovery) bringen

**Wenn der Flipper noch läuft, sich aber nicht richtig aktualisieren lässt:**
1. **Main Menu → Settings → Power → Reboot → Firmware Upgrade**.
2. Bestätige `Reboot to DFU Mode?` mit <kbd>→</kbd> **Reboot**.

*oder:* halte <kbd>←</kbd> + <kbd>BACK</kbd> 5 s gedrückt, lass <kbd>BACK</kbd> los und halte <kbd>←</kbd> weiter, bis
die **blaue LED** leuchtet.

**Wenn der Bildschirm nichts zeigt und die Tasten nicht reagieren:**
1. **Zieh das USB-Kabel ab.**
2. Halte <kbd>OK</kbd> + <kbd>BACK</kbd> **30 Sekunden** gedrückt. Ein leerer Bildschirm ist hier normal.

Verbinde den Flipper danach per USB-Kabel mit dem Computer.

### Schritt 2: prüfen, ob der Computer ein DFU-Gerät sieht

| Betriebssystem | Wo nachsehen | Name |
|---|---|---|
| Windows | Geräte-Manager | **DFU in FS Mode** |
| macOS | Apple-Menü → Über diesen Mac → Systembericht → Hardware → USB (oder `system_profiler SPUSBDataType`) | **DFU in FS Mode** |
| Linux | `lsusb` | **STMicroelectronics STM Device in DFU Mode** |

Wird nichts erkannt? Probier ein anderes Kabel. Steck direkt an einen USB-Port des Mainboards, nicht an einen Hub oder
Adapter. Oder nimm die SD-Karte heraus, lade das Gerät eine Stunde und verbinde es ohne Karte.

### Schritt 3: reparieren

Beide Apps gehen. Jede von ihnen flasht den Flipper per USB komplett neu.

**[qUnleashed](/de/mobile/qunleashed-app)** — Android, Windows, macOS und Linux (unter iOS gibt es kein USB):

1. Verbinde den Flipper im DFU-Modus per USB.
2. Öffne **Repair from DFU mode** und starte den Vorgang.

**qFlipper** — Windows, macOS und Linux:

1. Starte **qFlipper**. Es erkennt das DFU-Gerät.
2. Klick auf **Repair**. qFlipper installiert die **offizielle** Firmware vollständig neu.

Installiere danach Unleashed wieder: [Unleashed installieren](/de/start/install).

::: tip Unleashed
**Repair** in qFlipper stellt immer die offizielle Firmware wieder her. Das ist in Ordnung: du bekommst damit eine
saubere Basis. Installiere Unleashed danach erneut mit qUnleashed, dem Web Installer oder über
**Install from file**. Die Dateien auf deiner SD-Karte bleiben von der Reparatur unberührt.
:::

### Wenn qFlipper nicht reparieren kann

- Prüfe, ob qFlipper korrekt installiert ist. Unter Windows hilft die Treiber-Fehlerbehebung von qFlipper.
- Zieh USB ab, starte mit <kbd>←</kbd> + <kbd>BACK</kbd> neu und wiederhole das Ganze.
- Mach einen Power-Reset (<kbd>BACK</kbd> 30 s, USB abgezogen) und wiederhole das Ganze.
- Starte qFlipper als Administrator.
- Nimm einen USB-Port direkt am Mainboard.
- Letzter Ausweg: über SWD mit einem ST-Link flashen (siehe [Tastenkombinationen](/de/start/key-combos#if-nothing-helps)).

## 3. Internen Speicher reparieren / Werkszustand herstellen {#factory-reset}

Wenn Updates fehlschlagen, weil der interne Speicher voll oder beschädigt ist, setz den Flipper in den Werkszustand
zurück. Das löscht den **internen Speicher**: Einstellungen, Bluetooth-Kopplungen, PIN, Level des Delfins.
**Dateien auf der SD-Karte bleiben erhalten.**

::: info Interner Speicher in aktuellen Firmware-Versionen
In aktuellen Firmware-Versionen ist der interne Speicher (`/int`) **virtuell** und liegt im versteckten Ordner
`/ext/.int/` auf der SD-Karte. **Settings → Storage → About Internal Storage** zeigt `Type: Virtual (/.int on SD)`.
:::

### Vorher ein Backup anlegen (optional)

qFlipper → **Advanced controls** → **BACKUP** → Ordner wählen → **BACKUP**. Damit wird der interne Speicher als `.tgz`
gesichert. Die SD-Karte ist nicht enthalten, kopier sie also separat.

### Zurücksetzen auf dem Gerät

1. **Main Menu → Settings → Storage → Factory Reset**.
2. Der Bildschirm fragt `Confirm Factory Reset?`: *„Internal storage will be erased, data and settings will be lost!“*
   („Der interne Speicher wird gelöscht, Daten und Einstellungen gehen verloren“).
3. Drücke <kbd>→</kbd> **Erase** **5-mal**. Der Bildschirm zählt die restlichen Tastendrücke mit.
4. Der Flipper startet neu und formatiert den internen Speicher.

### Zurücksetzen mit qFlipper

**Advanced controls** → **ERASE** → **ERASE** → danach **CONTINUE**.

### Wiederherstellen

qFlipper → **Advanced controls** → **RESTORE** → das Backup-`.tgz` auswählen → **RESTORE** → **CONTINUE**.

Schlägt das Update auch nach einem Reset fehl, setz noch einmal zurück, **ohne** das Backup wiederherzustellen, oder
führe die [Firmware-Wiederherstellung](#firmware-recovery) durch.

## 4. Vergessenen PIN zurücksetzen {#reset-pin}

Wenn der Flipper mit einem PIN gesperrt ist, den du nicht mehr weißt:

1. **Zieh das USB-Kabel ab.**
2. Schalte den Flipper aus: <kbd>BACK</kbd> halten → **Power Off**. Geht das nicht, nimm den nächsten Schritt, halte die
   Tasten dabei aber 30–40 Sekunden.
3. Halte <kbd>↑</kbd> + <kbd>BACK</kbd> etwa 5 Sekunden gedrückt. Der Flipper startet mit gehaltener <kbd>↑</kbd> und
   zeigt den **PIN-Reset-Bildschirm**.
4. **Halte <kbd>→</kbd>**, bis der Fortschrittsbalken voll ist, um das Zurücksetzen zu bestätigen. Mit <kbd>↓</kbd>
   verlässt du den Bildschirm, ohne etwas zurückzusetzen.
5. Der Flipper startet neu.

Das setzt die Nutzerkonfiguration (RTC-Register, interner Speicher mit Einstellungen und PIN) in den Werkszustand
zurück. **Nutzerdateien auf der microSD-Karte bleiben erhalten.**

## 5. Immer noch tot?

- Eine Stunde laden, dann erneut versuchen.
- Den Akku abtrennen und wieder anschließen (dazu muss das Gehäuse geöffnet werden).
- Über SWD mit einem ST-Link oder einem anderen Programmer flashen.

Wenn nichts davon hilft, ist es ein Hardware-Problem und kein Software-Problem.

## Siehe auch

- [Tastenkombinationen](/de/start/key-combos)
- [Unleashed installieren](/de/start/install)
- [Begleit-App qUnleashed](/de/mobile/qunleashed-app)
- [qFlipper](/de/mobile/qflipper)
