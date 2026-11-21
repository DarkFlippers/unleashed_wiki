---
title: Archive (Dateibrowser)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Archive (Dateibrowser)

**Archive** ist der Dateibrowser des Flipper. Er listet die gespeicherten Schlüssel, Karten, Fernbedienungen und
Skripte auf, startet sie direkt und übernimmt die grundlegende Dateiverwaltung: zu den Favoriten hinzufügen,
umbenennen, kopieren, verschieben, Ordner anlegen und löschen.

**Öffnen:** auf dem Desktop <kbd>↓</kbd> drücken.

![Archive im Tab Sub-GHz: ein Ordner Garage und gespeicherte .sub-Signale, Barrier ist markiert](/screens/apps/archive.png)

## Tabs

Mit <kbd>←</kbd> / <kbd>→</kbd> wechselst du den Tab. Jeder Tab zeigt einen Ordner, gefiltert nach Dateityp:

| Tab | Ordner | Angezeigte Dateien |
|---|---|---|
| Favorites | deine angepinnten Dateien | alles, was du angepinnt hast (`/ext/favorites.txt`) |
| Sub-GHz | `/ext/subghz` | `.sub` |
| SubRem | `/ext/subghz_remote` | `.txt` ([Sub-GHz Remote](/de/subghz/remote)-Belegungen) |
| RFID LF | `/ext/lfrfid` | `.rfid` und T5577-Dumps |
| NFC | `/ext/nfc` | `.nfc` |
| Infrared | `/ext/infrared` | `.ir` |
| iButton | `/ext/ibutton` | `.ibtn` |
| Bad USB | `/ext/badusb` | `.txt` |
| Phone | `/ext/phonebook` | `.phone` ([SIM800](/de/gpio/sim800)-Telefonbuch) |
| U2F | intern | der Eintrag der U2F-App |
| Apps | `/ext/apps` | `.fap` und `.js` |
| Internal | interner Flash | alles (nur bei aktiviertem Debug-Modus) |
| Browser | die ganze SD-Karte | alles |

Archive startet im Tab **Favorites**.

::: tip Unleashed
Unleashed ergänzt den Tab **SubRem** für Sub-GHz-Remote-Belegungen, den Tab **Phone** für das SIM800-Telefonbuch
(ein `.phone`-Eintrag öffnet direkt die SIM800-App), zeigt T5577-Dumps neben den Schlüsseln in **RFID LF** und
listet `.js`-Skripte in **Apps** auf.
:::

## Tasten in der Liste

| Taste | Aktion |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | durch die Liste bewegen (gedrückt halten für schnelleres Scrollen) |
| <kbd>←</kbd> / <kbd>→</kbd> | vorheriger / nächster Tab |
| <kbd>OK</kbd> auf einer Datei | ihr Menü öffnen |
| <kbd>OK</kbd> auf einem Ordner | Ordner betreten |
| <kbd>OK</kbd> auf einem Ordner halten | Menü des Ordners öffnen |
| <kbd>OK</kbd> in Favorites | Datei sofort ausführen |
| <kbd>OK</kbd> in Favorites halten | Menü öffnen |
| <kbd>OK</kbd> in einem leeren Ordner halten | Menü öffnen (Paste / NewDir) |
| <kbd>Back</kbd> | einen Ordner nach oben oder beenden |

## Das Dateimenü: Actions und Manage

Das Menü hat zwei Seiten. Der Titel zeigt, welche davon offen ist: **Actions** oder **Manage**. Mit <kbd>←</kbd> oder
<kbd>→</kbd> im Menü wechselst du zwischen beiden (nicht im Tab Favorites). <kbd>↑</kbd> / <kbd>↓</kbd> wählt einen
Eintrag, <kbd>OK</kbd> führt ihn aus, <kbd>Back</kbd> schließt das Menü.

**Actions** (bei einer Datei, die die Firmware öffnen kann):

- **Run**: die Datei in ihrer App öffnen (Schlüssel emulieren, Signal senden, Skript ausführen ...).
- **Pin** / **Unpin**: zu den Favoriten hinzufügen oder daraus entfernen.
- **Info**: Dateiname und Größe.
- **Show**: die Datei als Text ansehen (bei Textformaten).

Bei einem unbekannten Dateityp bietet Actions nur **Info** und bei Textdateien **Show**.

**Manage:**

- **Cut** / **Copy**, danach **Paste** im Zielordner.
- **NewDir**: einen Ordner anlegen.
- **Rename**: einen neuen Namen eingeben.
- **Delete**: fragt vorher nach einer Bestätigung.

Im Tab **Favorites** besteht das Menü aus **Run**, **Unpin**, **Show** (falls möglich) und **Move**. Mit Move ordnest
du die Favoriten neu: mit <kbd>↑</kbd> / <kbd>↓</kbd> verschiebst du den Eintrag, mit <kbd>OK</kbd> speicherst du die
neue Position (<kbd>Back</kbd> bricht ab).

## Häufige Aufgaben

### Eine Datei zu den Favoriten hinzufügen

1. Desktop → <kbd>↓</kbd>, um Archive zu öffnen.
2. Mit <kbd>←</kbd> / <kbd>→</kbd> zum passenden Tab wechseln und die Datei auswählen.
3. <kbd>OK</kbd> → **Pin** drücken. Die Datei erscheint jetzt im Tab Favorites.

### Einen gespeicherten Schlüssel oder ein Signal umbenennen

1. Die Datei auswählen und <kbd>OK</kbd> drücken.
2. Mit <kbd>→</kbd> das Menü auf **Manage** umschalten.
3. **Rename** wählen, den Namen eingeben, bestätigen.

### Dateien löschen, um Platz zu schaffen

1. Die Datei auswählen, <kbd>OK</kbd>, <kbd>→</kbd> zu **Manage**.
2. **Delete** wählen und bestätigen.

Um einen ganzen Ordner zu leeren, nimm den Tab **Browser**: den Ordner auswählen, <kbd>OK</kbd> halten,
**Manage → Delete**.

### Eine Datei in einen anderen Ordner verschieben

1. Die Datei auswählen, <kbd>OK</kbd>, **Manage → Cut**.
2. Zum Zielordner wechseln (der Tab **Browser** erreicht jeden Ordner auf der Karte).
3. Auf einer beliebigen Datei <kbd>OK</kbd> drücken (oder in einem leeren Ordner <kbd>OK</kbd> halten) → **Paste**.

## Fehlerbehebung

- **"Empty"** bedeutet, dass der Ordner keine Dateien des Typs dieses Tabs enthält. Prüfe die Dateiendung: eine
  `.ir`-Datei in `/ext/nfc` erscheint in keinem der beiden Tabs, der Tab Browser zeigt sie aber an.
- **Der Tab Internal fehlt**: er ist nur sichtbar, wenn `Settings → System → Debug` auf ON steht.
- **Ein Favorit ist verschwunden**: Favoriten, deren Datei nicht mehr existiert (außerhalb von Archive verschoben,
  umbenannt oder gelöscht), werden aus der Liste entfernt. Pinne die Datei an ihrem neuen Ort erneut an.
- **Delete** fragt immer `Delete <name>?` mit den Schaltflächen **Cancel** / **Delete**, damit nichts durch einen
  versehentlichen Tastendruck verloren geht.

## Verwandte Seiten

- [microSD-Karte](/de/start/sd-card)
- [Apps auf der SD-Karte](/de/apps/sd-card-apps)
- [Desktop](/de/start/desktop)
