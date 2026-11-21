---
title: microSD-Karte
order: 90
original: [https://docs.flipper.net/zero/basics/sd-card, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# microSD-Karte

Die microSD-Karte ist nicht optional. Auf ihr liegen deine gespeicherten Schlüssel, Karten und Fernbedienungen, alle
`.fap`-Apps (auch die mitgelieferten Unleashed-Apps), Datenbanken, das Update-Paket und in aktuellen Firmware-Versionen
sogar der **interne Speicher**.

## Die richtige Karte

- **Kapazität:** 16–32 GB reichen völlig. Bis 256 GB werden unterstützt, große Karten brauchen aber länger zum
  Einbinden.
- **Dateisystem:** FAT12, FAT16, FAT32 oder exFAT.
- **Qualität:** nimm eine **Markenkarte** (SanDisk, Kingston …). Der Flipper spricht die Karte über **SPI** an, nicht im
  schnellen SDIO-Modus, den Telefone und PCs verwenden. Nicht jede Karte kommt mit SPI gut zurecht, selbst wenn sie in
  anderen Geräten einwandfrei läuft. Eine schlechte Karte macht den Flipper langsam, kann den Akku schneller leeren
  (bis ~50 mA statt ~30 mA) und Daten beschädigen.
- Beim Lesen über SPI sind fast 600 KiB/s erreichbar, was für alles ausreicht, was der Flipper tut.

## Einsetzen

1. Der Slot sitzt an der Unterseite des Flippers.
2. Halte die Karte mit den **Kontakten nach oben** und schieb sie hinein, bis sie einrastet.
3. Das SD-Symbol erscheint in der Statusleiste.

## Wenn die Karte nicht erkannt wird

Es erscheint eine Meldung zur SD-Karte, oder das Symbol in der Statusleiste ist durchgestrichen. Mögliche Ursachen:

| Ursache | Lösung |
|---|---|
| Falsches oder kein Dateisystem | Karte formatieren (siehe unten) |
| Staub im Slot | Vorsichtig mit Druckluft reinigen |
| Die Karte unterstützt SPI nicht | Andere Karte nehmen |
| Die Karte ist defekt | Andere Karte nehmen |

## Settings → Storage

**Main Menu → Settings → Storage**

| Menüpunkt | Funktion |
|---|---|
| **About Internal Storage** | Name, Typ `Virtual (/.int on SD)`, Gesamt- und freier Speicher, freier Flash |
| **About SD Card** | Label, Dateisystemtyp, Gesamt- und freier Speicher, Hersteller und Seriennummer |
| **Unmount SD Card** / **Mount SD Card** | Vor dem Entnehmen sicher aushängen oder wieder einbinden. Das Einbinden kann externe Module kurz von der Spannung trennen |
| **Format SD Card** | Formatiert die Karte. **Alle Daten gehen verloren!** |
| **Benchmark SD Card** | Testet Schreib- und Lesegeschwindigkeit im SPI-Modus |
| **Factory Reset** | Löscht den internen Speicher (Einstellungen, Kopplungen, Delfin). Siehe [Wiederherstellung](/de/start/recovery#factory-reset) |

### Formatieren

1. **Settings → Storage → Format SD Card**.
2. Bestätige mit <kbd>→</kbd> **Format**.
3. Warte auf `Formatted` und drücke dann **Finish**.

Scheitert das Formatieren auf dem Flipper (`Cannot Format SD Card`), formatier die Karte am PC als FAT32/exFAT oder
probier eine andere Karte.

### Sicher entnehmen

1. **Settings → Storage → Unmount SD Card** → <kbd>→</kbd> **Unmount**.
2. Sobald `SD Card Unmounted` / `You can remove SD card now.` erscheint, drück die Karte zum Entriegeln an und zieh sie
   heraus.

Eine Karte zu entnehmen, während der Flipper darauf schreibt, kann Dateien oder das Dateisystem beschädigen.

### Benchmark

Der Benchmark schreibt die Testdatei `/ext/rwfiletest.bin` und zeigt Zeilen wie `4096b : W 300K R 600K`: Blockgröße,
dann Schreib- und Lesegeschwindigkeit in KiB/s. Für den normalen Betrieb sollte eine Karte **mindestens ~260 KiB/s**
schreiben. Die Ergebnisse weichen von PC-Benchmarks ab, weil der Test im SPI-Modus läuft. Lass ihn ein paar Mal laufen,
um ein verlässliches Bild zu bekommen.

## Ordnerstruktur

`/ext` ist die Wurzel der Karte. Die wichtigsten Ordner:

| Ordner | Inhalt |
|---|---|
| `/ext/subghz/` | Sub-GHz-`.sub`-Dateien. In `assets/` liegen `dangerous_settings`, `setting_user.example` (Vorlage für eine eigene Frequenzliste) und der KeeLoq-Keystore `keeloq_mfcodes` |
| `/ext/subghz_remote/` | Maps für Sub-GHz Remote |
| `/ext/nfc/` | NFC-`.nfc`-Dateien. In `assets/` liegen die Schlüsselwörterbücher |
| `/ext/lfrfid/` | 125-kHz-RFID-`.rfid`-Dateien |
| `/ext/ibutton/` | iButton-`.ibtn`-Dateien |
| `/ext/infrared/` | IR-Fernbedienungen als `.ir`. In `assets/` liegen die Bibliotheken der Universalfernbedienungen |
| `/ext/badusb/` | Bad-USB-Skripte (`.txt`). In `assets/layouts/` liegen die Tastaturlayouts (`.kl`) |
| `/ext/apps/` | `.fap`-Apps nach Kategorie (mitgelieferte Apps und App-Packs) |
| `/ext/apps_data/` | Daten und Einstellungen der Apps |
| `/ext/dolphin/` | `name.settings` (eigener Name) und Animationen |
| `/ext/update/` | Entpackte Update-Pakete |
| `/ext/.int/` | Ablage für den internen Speicher (`/int`). Nicht von Hand bearbeiten |

::: tip
Sichere die ganze Karte von Zeit zu Zeit (qFlipper kann Dateien herunterladen, oder du kopierst sie am PC). Deine
Schlüssel und Fernbedienungen existieren nur auf der Karte.
:::

## macOS: versteckte Dateien und Sortierung {#macos-hidden-files-and-sorting}

macOS lässt `._*`- und `.DS_Store`-Dateien auf der Karte zurück. So räumst du sie weg:

```bash
sudo dot_clean -mn /Volumes/Flipper\ SD
```

Ersetze `Flipper\ SD` durch den Namen deiner Karte.

Der Dateibrowser listet Dateien schneller auf, wenn das FAT-Verzeichnis sortiert ist. Unter macOS (mit
[Homebrew](https://brew.sh)):

```bash
brew install fatsort
diskutil list                         # Karte finden, z. B. disk4s1
diskutil unmount /Volumes/Flipper\ SD
sudo fatsort -n /dev/disk4s1          # eigene Disk-ID einsetzen
```

`fatsort` gibt es auch für Linux.

## Siehe auch

- Was ein Update übersteht: [Aktualisieren](/de/start/updating)
- Dateiformate: [Sub-GHz](/de/subghz/file-format), [NFC](/de/nfc/file-format), [RFID](/de/rfid/file-format),
  [Infrarot](/de/infrared/file-format), [iButton](/de/ibutton/file-format)
