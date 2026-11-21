---
title: Clock
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/clock_app, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Clock

Eine Nachttischuhr: große Zeitanzeige, Datum und Akkustand, Helligkeitsregelung für das Display mit rotem
LED-Nachtlicht, eine Stoppuhr und ein täglicher Wecker. Basiert auf FlipperNightStand von @nymda, mit @Willy-JL,
@mishamyte und @xMasterX (App-Version 1.3).

`Main Menu → Clock`

![Clock: das Datum über der großen Zeitanzeige und darunter der Akkustand](/screens/apps/clock.png)

::: tip Unleashed
In Unleashed ist Clock eine Hauptmenü-App mit Wecker und Nachtlicht. Wenn du nur die Uhrzeit auf dem Desktop
sehen willst, aktiviere stattdessen `Settings → Desktop → Show Clock`.
:::

## Tasten im Uhren-Bildschirm

| Taste | Aktion |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | Displayhelligkeit höher / niedriger (ein Balken erscheint und verschwindet 3 s nach dem letzten Tastendruck) |
| <kbd>↓</kbd> bei Helligkeit 0 | das gedimmte rote LED-Nachtlicht ein- / ausschalten |
| <kbd>OK</kbd> | Stoppuhr Start / Stop |
| <kbd>←</kbd> | Stoppuhr zurücksetzen |
| <kbd>→</kbd> | Weckereinstellungen |
| <kbd>Back</kbd> | beenden |

Die Uhrzeit folgt dem Systemformat: 12-Stunden-Format mit AM/PM oder 24-Stunden-Format, je nach Einstellung unter
`Settings → System → Time Format`.

## Stoppuhr

1. Drücke <kbd>OK</kbd> zum Starten; die laufende Zeit erscheint als `MM:SS`.
2. Drücke erneut <kbd>OK</kbd> zum Anhalten, noch einmal zum Fortsetzen.
3. Drücke <kbd>←</kbd> (**Reset**), um sie zurückzusetzen.

## Täglicher Wecker

1. Drücke im Uhren-Bildschirm <kbd>→</kbd>.
2. Stelle **Alarm** mit <kbd>←</kbd> / <kbd>→</kbd> auf **ON**.
3. Wähle **Set time** und drücke <kbd>OK</kbd>.
4. In der Auswahl `Alarm time`: <kbd>←</kbd> / <kbd>→</kbd> wählen Stunden, Minuten (und AM/PM im
   12-Stunden-Format), <kbd>↑</kbd> / <kbd>↓</kbd> ändern den Wert (gedrückt halten zum Wiederholen). <kbd>OK</kbd>
   oder <kbd>Back</kbd> speichert.
5. Drücke <kbd>Back</kbd>, um zur Uhr zurückzukehren. Die Weckzeit wird im Uhren-Bildschirm angezeigt.

Wenn der Wecker auslöst, blinkt auf dem Display `! ALARM !` mit `Press any key to stop`, eine Melodie spielt,
begleitet von Vibration und der roten LED. Drücke eine beliebige Taste, um ihn zu beenden. Der Wecker bleibt
aktiviert und löst am nächsten Tag zur gleichen Zeit wieder aus.

::: warning
Der Wecker klingelt nur, solange die Clock-App geöffnet ist. Lass den Flipper über Nacht mit laufender Clock-App
am Ladegerät.
:::

Wecker und Helligkeitsstufe werden in `/ext/apps_data/clock/` gespeichert und beim nächsten Öffnen der App
wiederhergestellt.

## Verwandte Seiten

- [Desktop](/de/start/desktop)
- [Einstellungen](/de/start/settings)
- [Apps im Lieferumfang von Unleashed](/de/apps/catalog)
