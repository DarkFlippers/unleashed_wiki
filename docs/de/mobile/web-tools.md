---
title: Web-Tools
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/apps]
sources: [unleashed-readme, unleashed-docs, flipper-docs]
---
# Web-Tools

Einige Flipper-Werkzeuge laufen direkt im Browser, ohne Installation. Werkzeuge, die per USB mit dem Flipper
sprechen, brauchen die **Web Serial API** — nutze also **Chrome, Edge oder einen anderen Chromium-Browser**.

::: warning Zuerst qFlipper schließen
Ein Browser-Tool kann sich nicht verbinden, solange qFlipper (oder ein zweiter Flipper-Lab-Tab) den seriellen Port
des Flippers belegt. Das ist der häufigste Grund dafür, dass „Chrome den Flipper nicht sieht“.
:::

## Unleashed-Werkzeuge

| Werkzeug | Adresse | Was es macht |
|---|---|---|
| Unleashed Web Installer | [web.unleashedflip.com](https://web.unleashedflip.com) | Unleashed per USB installieren oder aktualisieren (Release oder Dev) |
| Dev-Builds | [dev.unleashedflip.com](https://dev.unleashedflip.com) | automatische Builds aus dem dev-Branch (instabil) |
| Sub-GHz & Coordinates Map | [map.unleashedflip.com](https://map.unleashedflip.com) | Sub-GHz-Wardriving-Dateien und beliebige andere Dateien mit Koordinaten auf einer Karte anzeigen |
| Wi-Fi Wardriving Map | [wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) | mehrere Captures im WiGLE-Format (ESP32 Marauder und andere) zusammenführen und anzeigen |
| ESP32 Web Flasher | [espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) | gängige ESP32-Module aus dem Browser flashen |

### Unleashed Web Installer {#unleashed-web-installer}

Der empfohlene Weg, Unleashed zu installieren.

1. Nur bei der ersten Installation: Aktualisiere zuerst auf die neueste **offizielle** Firmware. Achte darauf, dass
   die **microSD-Karte** eingesteckt ist.
2. Schließe qFlipper. Verbinde den Flipper mit einem USB-Kabel, das Daten überträgt.
3. Öffne [web.unleashedflip.com](https://web.unleashedflip.com) in einem Chromium-Browser.
4. Drücke **Connect** und wähle deinen Flipper im Dialog des Browsers aus.
5. Wähle den Branch **Release** oder **Dev**.
6. Drücke **Install** und warte. Am Ende sind alle Assets installiert und der Flipper startet in Unleashed.

Alternativ hat jeder [GitHub-Release](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) einen Link
**Install via Web Updater**, der den Release im Web-Updater von Flipper Lab öffnet: **Connect** drücken, dann
**Install**. Vollständige Anleitung: [Unleashed installieren](/de/start/install).

### Sub-GHz & Coordinates Map

[map.unleashedflip.com](https://map.unleashedflip.com) zeigt deine Sub-GHz-Captures mit Koordinaten (zum Beispiel aus
Sub-GHz-Wardriving mit einem GPS-Modul) und alle anderen Dateien, die Koordinaten enthalten, auf einer Karte.

### Wi-Fi Wardriving Map

[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) führt mehrere Captures im **WiGLE-Format** von
ESP32 Marauder und ähnlichen Werkzeugen zusammen und zeigt die Access Points auf einer Karte. Siehe
[ESP32 und Wi-Fi-Module](/de/gpio/esp32).

### ESP32 Web Flasher

[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) ist ein einfach zu bedienender Flasher für
gängige ESP32-Module, der vollständig im Browser läuft, ohne dass du Flash-Werkzeuge installieren musst. Siehe
[ESP32](/de/gpio/esp32) und [Dev Board](/de/gpio/devboard).

## Flipper Lab (offiziell)

[lab.flipper.net](https://lab.flipper.net) ist der offizielle Web-Werkzeugkasten. Er funktioniert mit Unleashed:

- [Apps](https://lab.flipper.net/apps): der offizielle App-Katalog, Apps per USB installieren / aktualisieren /
  löschen, siehe [Apps auf der SD-Karte](/de/apps/sd-card-apps).
- [CLI](https://lab.flipper.net/cli): ein Terminal für die Kommandozeile des Flippers, siehe [CLI](/de/dev/cli).
- [Pulse Plotter](https://lab.flipper.net/pulse-plotter): Sub-GHz-RAW-Signale visualisieren, nützlich beim Analysieren
  einer unbekannten Fernbedienung.
- Der **Web-Updater**, den die Links „Install via Web Updater“ öffnen.

## Weitere Links

- Unleashed-Startseite: [flipperunleashed.com](https://flipperunleashed.com)
- Direkte `.tgz`-Update-Links: [unleashedflip.com](https://unleashedflip.com)
- Directory JSON für uFBT-Builds: [up.unleashedflip.com/directory.json](https://up.unleashedflip.com/directory.json)

::: danger Achtung, Fälschungen
[DarkFlippers/unleashed-firmware](https://github.com/DarkFlippers/unleashed-firmware) ist die einzige offizielle Seite
des Projekts. Es gibt keine kostenpflichtigen, „Premium“- oder Closed-Source-Versionen; wer dir so etwas anbietet,
ist ein Betrüger.
:::

## Verwandte Seiten

- [Unleashed installieren](/de/start/install)
- [qFlipper](/de/mobile/qflipper)
- [Begleit-App qUnleashed](/de/mobile/qunleashed-app)
