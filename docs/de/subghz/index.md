---
title: Sub-GHz
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz]
---
# Sub-GHz

Flipper Zero hat einen eingebauten **CC1101**-Transceiver und eine Antenne für die Bänder unter 1 GHz. Damit
kannst du die Signale von Garagen- und Torfernbedienungen, Schranken, Rollläden, Türklingeln, Funksensoren und
anderen Geräten lesen, speichern und wieder abspielen, die in den Bereichen
**300–348 MHz, 387–464 MHz und 779–928 MHz** arbeiten. Die meisten Fernbedienungen, die dir begegnen, nutzen
**315 MHz**, **433,92 MHz** oder **868,35 MHz**.

Die App liegt unter `Main Menu → Sub-GHz`. Ihr Hauptmenü in Unleashed:

![Sub-GHz-Hauptmenü: Read, Read RAW, Saved, Add Manually](/screens/subghz/menu.png)

| Menüpunkt | Funktion | Seite |
|---|---|---|
| `Read` | Fernbedienungen bekannter Protokolle dekodieren, speichern und senden | [Read](/de/subghz/read) |
| `Read RAW` | Das Rohsignal einer beliebigen Fernbedienung aufnehmen und abspielen | [Read RAW](/de/subghz/read-raw) |
| `Saved` | Gespeicherte `.sub`-Dateien: Emulate, Rename, Delete — und Signal Settings, wenn Debug an ist | [Read](/de/subghz/read) |
| `Add Manually` | Eine ganz neue Fernbedienung mit zufälliger Seriennummer anlegen | [Add Manually](/de/subghz/add-manually) |
| `Add Manually [Advanced]` | Dasselbe, aber Seriennummer / Taste / Zähler / Seed gibst du selbst ein | [Add Manually](/de/subghz/add-manually) |
| `Frequency Analyzer` | Herausfinden, auf welcher Frequenz eine Fernbedienung sendet | [Frequency Analyzer](/de/subghz/frequency-analyzer) |
| `Radio Settings` | Internes / externes Modul, Sendeleistung, Dateinamen, Zählerschrittweite | [Einstellungen](/de/subghz/settings) |

::: tip Unleashed
Die Sub-GHz-App, ihre Protokollbibliothek und der Frequency Analyzer kommen aus der offiziellen Firmware.
Unleashed entfernt die regionalen Sendebeschränkungen, ergänzt zusätzliche Frequenzen und weitere Protokolle, erlaubt das Speichern und Senden vieler Rolling-Code-Protokolle, erzeugt neue
Rolling-Code-Fernbedienungen, die du in deinem Empfänger anlernen kannst (`Add Manually`), nutzt die Pfeiltasten als
zusätzliche Fernbedienungstasten, unterstützt ein externes CC1101-Modul und bringt weitere Sub-GHz-Apps mit
(Remote Analyzer, Seed Capturer, Nice O-Code, Security+ PIN, Sub-GHz RAW Edit, Sub-GHz Remote).
:::

::: warning
Nutze diese Funktionen nur mit deiner eigenen Technik oder für legale Forschung.
:::

## Erste Schritte

1. Finde die Frequenz deiner Fernbedienung — [Frequency Analyzer](/de/subghz/frequency-analyzer).
2. Versuche sie zu dekodieren — [Read](/de/subghz/read). Wird sie dekodiert und ist das Protokoll **statisch**,
   speichere sie und du bist fertig.
3. Ist es eine Fernbedienung mit **Rolling Code**, klone sie nicht — lies
   [Rolling Codes](/de/subghz/rolling-codes) und lege mit [Add Manually](/de/subghz/add-manually) +
   [Neue Fernbedienung anlernen](/de/subghz/remote-prog) eine neue Fernbedienung an.
4. Wird nichts dekodiert, nimm sie mit [Read RAW](/de/subghz/read-raw) auf.

## Alle Seiten

**Grundlagen**
- [Frequenzen](/de/subghz/frequencies) — Bänder, Standardlisten, Regionssperren und erweiterter Bereich
- [Frequency Analyzer](/de/subghz/frequency-analyzer) — die Frequenz einer Fernbedienung finden
- [Read](/de/subghz/read) — Signale dekodieren, speichern und senden
- [Read RAW](/de/subghz/read-raw) — Rohsignale aufnehmen

**Rolling Codes und neue Fernbedienungen**
- [Add Manually](/de/subghz/add-manually) — jedes Protokoll im Menü
- [Rolling Codes](/de/subghz/rolling-codes) — Zählerkonflikte, eigene Tasten
- [KeeLoq](/de/subghz/keeloq) — wie KeeLoq funktioniert, Herstellerschlüssel und Seeds
- [Neue Fernbedienung anlernen](/de/subghz/remote-prog) — Schritt für Schritt für jedes System
- [Zählermodi](/de/subghz/counter-mode) — der experimentelle `CounterMode` für Klone
- [Signal Settings](/de/subghz/signal-settings) — Zählermodus, Zähler und Taste eines gespeicherten Signals
- [Unterstützte Systeme](/de/subghz/supported-systems) — vollständige Protokolltabelle

**Konfiguration und Hardware**
- [Einstellungen](/de/subghz/settings) — Radio Settings, Read-Konfiguration, eigene Frequenzen
- [Dateiformate](/de/subghz/file-format) — `.sub`, Presets, eigene Einstellungsdateien
- [Externes CC1101](/de/subghz/external-cc1101) — externe Module und Verstärker

**Apps**
- [Sub-GHz Remote](/de/subghz/remote) — bis zu 5 Signale auf dem Steuerkreuz
- [Sub-GHz Bruteforce](/de/subghz/bruteforce) — Brute-Force statischer Codes
- [Remote Analyzer](/de/subghz/remote-analyzer) — eine Fernbedienung dekodieren, zusätzliche Protokolle
- [Nice O-Code](/de/subghz/nice-o-code) — den Installationscode zurückrechnen
- [Security+ PIN](/de/subghz/secplus-pin) — Tastatur-PIN von Security+ 2.0
- [Seed Capturer](/de/subghz/seed-capturer) — Hops für die Seed-Rückrechnung sammeln
- [Sub-GHz RAW Edit](/de/subghz/raw-editor) — RAW-Dateien kürzen, zusammenfügen und dekodieren

**Aus der Praxis**
- [ZKTeco CMP200](/de/subghz/zkteco-cmp200) — eine Princeton-Fernbedienung in Verkleidung

## Wo die Dateien liegen

| Pfad | Inhalt |
|---|---|
| `/ext/subghz/` | Gespeicherte Signale (`.sub`), RAW-Aufnahmen |
| `/ext/subghz/assets/setting_user` | Eigene Frequenzen, Hopper-Liste, eigene Presets |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Eigene KeeLoq-Herstellerschlüssel |
| `/ext/subghz/assets/dangerous_settings` | Schalter für den erweiterten Frequenzbereich |
| `/ext/subghz_remote/` | Map-Dateien der App Sub-GHz Remote |
| `/ext/apps_data/subghz_seed_captures/` | Aufnahmen des Seed Capturer |
