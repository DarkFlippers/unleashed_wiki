---
title: Erste Schritte
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-readme, unleashed-docs, unleashed-src, flipper-docs]
---
# Erste Schritte

Dieser Abschnitt führt dich vom neu gekauften Flipper Zero zu einem fertig eingerichteten Gerät mit
**Unleashed Firmware**. Hier stehen die Grundlagen, die alle anderen Abschnitte des Wikis voraussetzen: Tasten,
Desktop, Stromversorgung, microSD-Karte, Einstellungen und Wiederherstellung.

## Was ist Flipper Zero?

Flipper Zero ist ein Multitool im Taschenformat, um Funk- und Zutrittstechnik zu erforschen. An Bord sind:

- ein **CC1101-Transceiver (Sub-GHz)** für Garagentor-Handsender, Schranken, Sensoren und andere Geräte unter 1 GHz;
- ein **NFC-Modul (13,56 MHz)** und eine **125-kHz-RFID**-Antenne für Karten, Schlüsselanhänger und Tags;
- ein **Infrarot**-Sender und -Empfänger für Fernseher, Klimaanlagen und andere Fernbedienungen;
- eine Kontaktfläche für **1-Wire (iButton)** — Schlüssel von Dallas, Cyfral und Metakom;
- **USB** und **Bluetooth LE** — als Tastatur (Bad USB), als U2F-Token oder als Fernbedienung;
- **GPIO**-Pins für externe Module (externer CC1101, NRF24, ESP32, SIM800 und weitere);
- ein monochromes Display mit 128×64 Pixeln, ein Fünf-Wege-Pad mit separater Back-Taste und ein Akku mit 2100 mAh.

Auf dem Desktop lebt ein digitaler Delfin. Er steigt im Level, je mehr du mit dem Gerät arbeitest.

## Was ist Unleashed Firmware?

[Unleashed](https://github.com/DarkFlippers/unleashed-firmware) ist ein Fork der offiziellen Firmware (OFW). Die
Firmware bleibt **vollständig kompatibel mit der OFW-API und deren Apps** und ergänzt sie um neue Funktionen. Das
Wichtigste:

- **keine regionalen Sendebeschränkungen bei Sub-GHz**, zusätzliche Frequenzen und ein optional erweiterter Bereich;
- **deutlich mehr Sub-GHz-Protokolle**: Speichern und Senden vieler Rolling-Code-Systeme, eigene Tastencodes und
  `Add manually` für neue Handsender;
- Unterstützung für **externe CC1101-Module**;
- zusätzliche NFC-Parser, ein EMV-Parser und mehr MIFARE Classic-Schlüssel im System-Wörterbuch;
- Fuzzer für RFID und iButton, ein T5577-Werkzeug und weitere eingebaute Apps;
- Komfortfunktionen: eigener Flipper-Name, Uhr auf dem Desktop, Akkustand in Prozent, Night Shift, mehr Spiele im
  Dummy Mode, BadKB (Bad USB über Bluetooth) und mehr.

Die vollständige Liste mit Links steht unter [Was Unleashed hinzufügt](/de/start/unleashed-features).

::: warning Nur offizielle Quellen
`DarkFlippers/unleashed-firmware` ist die einzige offizielle Heimat des Projekts. Jeder Build ist kostenlos und Open
Source. Es gibt keine kostenpflichtigen, „Premium“- oder Closed-Source-Versionen. Wer dir so etwas anbietet, betrügt
dich.
:::

## Release- und Dev-Builds

| Build | Was es ist | Woher |
|---|---|---|
| **Release** (stabil) | Getestete Releases, empfohlen für den täglichen Einsatz | [Web Installer](https://web.unleashedflip.com), [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), Telegram [@unleashed_fw](https://t.me/unleashed_fw) |
| **Dev** (Testversion) | Automatische Builds aus dem Branch `dev` zum Testen neuer Funktionen | [dev.unleashedflip.com](https://dev.unleashedflip.com), Telegram [@kotnehleb](https://t.me/kotnehleb), Discord-Kanal `unleashed-development` |

Ein neuer Dev-Build ersetzt den vorherigen auf der Website; ältere Dev-Builds bleiben nur als Dateien im
Telegram-Kanal erhalten. Dev-Builds erhalten neue Funktionen zuerst, **können aber Fehler enthalten**. Wenn du einen
findest, melde ihn über [GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

Jedes Release erscheint in drei Varianten: `e` (Base- plus Extra-Apps), ohne Suffix (Base-Apps) und `c` (ohne
Community-Apps). Details unter [Unleashed installieren](/de/start/install#which-file-to-download).

## Community-Kanäle

- Telegram-Chats: [englisch](https://t.me/flipperzero_unofficial), [russisch](https://t.me/flipperzero_unofficial_ru), [ukrainisch](https://t.me/flipperzero_unofficial_ua)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Unleashed-Website: [flipperunleashed.com](https://flipperunleashed.com)

## Seiten in diesem Abschnitt

**Erste Schritte**
- [Erster Start](/de/start/first-start) — einschalten, microSD-Karte einlegen, Unleashed installieren
- [Unleashed installieren](/de/start/install) — Web Installer, qFlipper, Mobil-Apps, Offline-Update von der Karte
- [Aktualisieren](/de/start/updating) — aktuell bleiben, Release oder Dev, was ein Update übersteht
- [Was Unleashed hinzufügt](/de/start/unleashed-features) — alle Unleashed-Funktionen im Vergleich zur Stock-Firmware

**Mit dem Gerät arbeiten**
- [Steuerung](/de/start/controls) — Tasten, Linkshänder-Modus, Tastenkürzel
- [Desktop](/de/start/desktop) — Statusleiste, Schnellzugriffe, Lock Menu, Quick Settings, Dummy Mode, Archive
- [Delfin](/de/start/dolphin) — Laune, Level und XP
- [Stromversorgung und Akku](/de/start/power) — Laden, Ausschalten, Auto PowerOff, Limit Charge
- [microSD-Karte](/de/start/sd-card) — Auswahl, Formatieren, Ordnerstruktur
- [Einstellungen](/de/start/settings) — alle Punkte im Menü `Settings`, der Reihe nach
- [Eigener Flipper-Name](/de/start/custom-name)

**Wenn etwas schiefgeht**
- [Tastenkombinationen](/de/start/key-combos) — Kombinationen für Reset und DFU
- [Wiederherstellung](/de/start/recovery) — Firmware wiederherstellen, Werksreset, PIN zurücksetzen
- [Gefährliche Einstellungen](/de/start/dangerous-settings) — erweiterter Sub-GHz-Bereich (lies das, bevor du daran drehst)
- [FAQ](/de/start/faq)

::: tip Rechtliches
Unleashed ist für Experimente und legale Forschung gedacht. Nutze es an deinen eigenen Geräten oder mit Erlaubnis des
Besitzers.
:::
