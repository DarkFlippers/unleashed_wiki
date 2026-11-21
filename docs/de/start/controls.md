---
title: Steuerung
order: 50
original: [https://docs.flipper.net/zero/basics/control, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/input_settings_app]
sources: [flipper-docs, unleashed-src]
---
# Steuerung

Der Flipper Zero hat ein Fünf-Wege-Pad und eine separate Taste <kbd>BACK</kbd>.

| Taste | Funktion |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | Navigation in Menüs und auf der Bildschirmtastatur. <kbd>←</kbd>/<kbd>→</kbd> ändern den Wert der ausgewählten Option |
| <kbd>OK</kbd> | App starten, Auswahl bestätigen. Langes Drücken öffnet häufig weitere Aktionen |
| <kbd>BACK</kbd> | Zurück oder App verlassen. Langes Drücken auf dem Desktop öffnet den Ausschaltbildschirm |

In einer Liste verschieben die Pfeiltasten den Rahmen über die Einträge, und <kbd>OK</kbd> öffnet den markierten:

![Hauptmenü mit dem Rahmen auf Sub-GHz](/screens/mainmenu/subghz.png)

„Halten“ oder „langes Drücken“ heißt in diesem Wiki, eine Taste etwa eine Sekunde zu drücken. Die Tastenhinweise am
unteren Bildschirmrand (zum Beispiel `◀ Cancel` oder `Save ▶`) zeigen, was <kbd>←</kbd>, <kbd>OK</kbd> und
<kbd>→</kbd> auf dem aktuellen Bildschirm tun.

## Linkshänder-Modus

**Main Menu → Settings → System → Hand Orient → `Lefty`**

Das Display dreht sich um 180° und das Pad wird neu belegt, damit du den Flipper in der linken Hand halten kannst.

## Tastenkürzel

| Aktion | Wie |
|---|---|
| Einschalten | <kbd>BACK</kbd> etwa 3 s halten |
| Ausschalten | <kbd>BACK</kbd> auf dem Desktop halten → **Power Off** (<kbd>→</kbd>) |
| Neustart (hängendes Gerät) | <kbd>←</kbd> + <kbd>BACK</kbd> etwa 5 s halten |
| Harter Neustart (Power Reset) | USB abziehen, <kbd>BACK</kbd> etwa 30 s halten |
| Neustart in den DFU-Modus (Wiederherstellung) | <kbd>←</kbd> + <kbd>BACK</kbd> halten, <kbd>BACK</kbd> loslassen, <kbd>←</kbd> halten, bis die blaue LED leuchtet |

Alle Kombinationen für Reset und DFU — und die Fälle, in denen sie nicht greifen — stehen unter
[Tastenkombinationen](/de/start/key-combos).

## Schnellzugriffe auf dem Desktop

| Taste | Kurz drücken | Lang drücken |
|---|---|---|
| <kbd>OK</kbd> | Main Menu | Favoriten-App (Ok Long) |
| <kbd>↑</kbd> | Lock Menu | **Flipper sperren** (mit PIN, falls gesetzt) |
| <kbd>↓</kbd> | Archive | Geräteinfo / Debug-Bildschirm |
| <kbd>←</kbd> | Favoriten-App (Left Short), standardmäßig das Menü Apps | Favoriten-App (Left Long) |
| <kbd>→</kbd> | Passport (oder die zugewiesene App) | Favoriten-App (Right Long) |
| <kbd>BACK</kbd> | — | Ausschaltbildschirm |

Apps weist du unter **Settings → Desktop → Favorite App - …** zu. Details stehen auf der Seite
[Desktop](/de/start/desktop).

::: tip Unleashed
Hältst du <kbd>↑</kbd> auf dem Desktop, wird das Gerät sofort gesperrt (mit PIN, falls einer gesetzt ist). In der
Stock-Firmware sperrst du über das Lock Menu.
:::

Kurzes <kbd>↑</kbd> öffnet das Lock Menu:

![Lock Menu: Turn Bluetooth On ist markiert, darunter Mute und Dummy Mode](/screens/desktop/lock_menu.png)

Ist ein PIN gesetzt, fragt der Flipper vor dem Entsperren danach. Mit den Pfeiltasten gibst du den Code ein,
<kbd>BACK</kbd> löscht ihn und <kbd>OK</kbd> bestätigt:

![Enter PIN: vier eingegebene Stellen als Sterne, eine leere fünfte Zelle, der Hinweis zum Löschen und die Taste OK](/screens/desktop/pin_input.png)

Langes <kbd>↓</kbd> öffnet den Geräte-Infobildschirm — Laufzeit, Hardware-Revision, Flipper-Name, Firmware-Version
und Build-Datum, Commit, API-Version und das Debug-Flag. Langes <kbd>OK</kbd> schaltet dort Debug ein oder aus:

![Geräte-Infobildschirm: Uptime 1h23m45s, Hardware 13.F7B9C6 R00, Firmware unlshd-080 vom 21-11-2026 und D:ON](/screens/desktop/debug.png)

## Tastenrückmeldung

**Main Menu → Settings → Input**

| Punkt | Werte | Bedeutung |
|---|---|---|
| Buttons Vibro | `OFF`, `1`…`9` | Kurze Vibration bei jedem Tastenereignis. Je höher der Wert, desto länger der Impuls |
| Vibro Trigger | `Press`, `Release`, `Both` | Wann die Vibration auslöst |

## Texteingabe

Auf der Bildschirmtastatur navigierst du mit den Pfeiltasten, <kbd>OK</kbd> gibt das markierte Zeichen ein. Halte
<kbd>OK</kbd> auf einem Buchstaben, um ihn groß zu schreiben. Zum Bestätigen wählst du die Taste `⏎` / **Save**.
<kbd>BACK</kbd> löscht das letzte Zeichen oder verlässt die Tastatur.

::: tip Unleashed
Die Texteingabe hat einen **Cursor**, du kannst also mitten im Text arbeiten. Drücke bei der hexadezimalen
**Byte-Eingabe** (zum Beispiel wenn du einen Schlüssel manuell hinzufügst) mehrfach <kbd>↑</kbd>, bis der
**Nibble-Mini-Editor** erscheint. Damit änderst du jeweils ein halbes Byte.
:::
