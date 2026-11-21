---
title: Delfin
order: 70
original: [https://docs.flipper.net/zero/basics/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/dolphin_passport]
sources: [flipper-docs, unleashed-src]
---
# Delfin

Auf dem Desktop des Flippers lebt ein digitaler Delfin. Er wird zufriedener und steigt im Level, je mehr du die
Werkzeuge des Geräts benutzt, und seine Animationen ändern sich mit Laune und Level.

## Passport

Drücke <kbd>→</kbd> auf dem Desktop oder öffne **Main Menu → Settings → Passport**. Das Passport zeigt:

- das Bild des Delfins für das aktuelle Level;
- den **Namen**: den Gerätenamen des Flippers ([den kannst du ändern](/de/start/custom-name));
- **Mood**: `Happy`, `Ok` oder `Angry`;
- **Level** und einen Fortschrittsbalken bis zum nächsten Level.

![Passport: das Delfin-Porträt, der Name des Flippers, Mood: Happy, Level: 2 und der Fortschrittsbalken bis Level 3](/screens/settings/passport.png)

## Laune

Der Delfin wird trauriger, wenn du den Flipper nicht benutzt. Sein „butthurt“-Zähler steigt etwa **alle 48 Stunden**
ohne Aktivität um eins. Wer Apps nutzt, hebt die Laune wieder — allerdings mit einer Tagesobergrenze dafür, wie schnell
sie sich erholt.

Der **Happy Mode** hält den Delfin in jedem Fall zufrieden:

**Main Menu → Settings → Desktop → Happy Mode** → **Enable**. Der Dialog sagt: *"I will never get angry at you for not
spending time with me as long as this mode is enabled"*. Zum Abschalten öffnest du ihn erneut und wählst **Disable**.

## Level und XP

| Level | Benötigte XP |
|---|---|
| 1 | 0 |
| 2 | 300 |
| 3 | 1800 |

Jede App gibt höchstens **20 XP pro Tag**. Es gibt 7 gezählte Gruppen (Sub-GHz, RFID, NFC, Infrared, iButton, Bad USB
und „Plugins“, wozu U2F, GPIO und externe Apps gehören), das Maximum sind also **140 XP pro Tag**. Die Grenzen werden
täglich zurückgesetzt.

### XP pro Aktion

| App | Aktion | XP |
|---|---|---|
| Sub-GHz | Signal empfangen und ansehen | 1 |
| | Signal speichern | 3 |
| | RAW aufnehmen | 1 |
| | Add manually | 2 |
| | Gespeichertes Signal senden | 2 |
| | Frequency Analyzer benutzen | 1 |
| 125 kHz RFID | Read öffnen | 1 |
| | Erfolgreich gelesen | 3 |
| | Speichern | 3 |
| | Emulieren | 2 |
| | Add manually | 2 |
| NFC | Read öffnen | 1 |
| | Erfolgreich gelesen | 3 |
| | Speichern | 3 |
| | Detect Reader (Extract MF Keys) | 1 |
| | Emulieren | 2 |
| | Schlüssel manuell hinzufügen | 2 |
| | Add manually und speichern / emulieren | 1 |
| Infrared | Signal senden | 1 |
| | Erfolgreich angelernt | 3 |
| | Speichern | 3 |
| iButton | Read öffnen | 1 |
| | Erfolgreich gelesen | 3 |
| | Speichern | 3 |
| | Emulieren | 2 |
| | Add manually | 2 |
| Bad USB | Skript ausführen | 3 |
| U2F | Erfolgreiche Autorisierung | 3 |
| GPIO | USB-UART Bridge öffnen | 1 |
| Apps | Externe App starten | 2 |
| | Spiel starten | 1 |
| | Spiel gewinnen | 10 |

Erreicht der Delfin ein neues Level, zeigt der Flipper eine Level-up-Meldung, und die Animationen auf dem Desktop
ändern sich.

## Wo der Zustand gespeichert wird

XP, Level und Laune des Delfins liegen in `.dolphin.state` im internen Speicher. Ein
[Werksreset](/de/start/recovery#factory-reset) setzt den Delfin auf Level 1 zurück.
