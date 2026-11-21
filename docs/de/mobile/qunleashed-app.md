---
title: Begleit-App qUnleashed
order: 30
original: [https://github.com/DarkFlippers/qUnleashed, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md]
sources: [unleashed-readme, unleashed-docs]
---
# Begleit-App qUnleashed

::: tip Unleashed
**qUnleashed** ist die eigene Begleit-App des Unleashed-Teams für Telefon und Computer. Sie wurde von Grund auf in
Flutter geschrieben, als Alternative zur offiziellen Flipper-Mobile-App, und ist damit kein Fork von qFlipper.
Lizenz GPL-3.0-or-later, Quellcode und Builds unter
[DarkFlippers/qUnleashed](https://github.com/DarkFlippers/qUnleashed).
:::

Sie ist für Unleashed gebaut, funktioniert aber auch mit anderer Firmware. Die aktuelle stabile Version ist **0.17.2**.

## Läuft sie auf deinem Gerät?

| System | Du brauchst |
|---|---|
| Android | 10 (API 29) oder neuer |
| iOS | 15 oder neuer |
| macOS | 12 oder neuer |
| Windows | 10 oder neuer, 64-bit |
| Linux | GLib 2.72 und glibc 2.35 — Ubuntu 22.04, Debian 12, Mint 21 oder neuer |

Ein älteres Linux startet die Binärdatei nicht einmal.

## Installieren

Hol dir den Build für dein System auf der
[Releases-Seite](https://github.com/DarkFlippers/qUnleashed/releases). Es gibt keinen Store-Eintrag und kein
Installationsskript.

## Verbinden

Bluetooth läuft auf allen fünf Systemen. USB-Serial läuft unter Android, Windows, macOS und Linux — unter iOS gibt
es überhaupt keine USB-Option, weil Apple Apps nicht mit einem seriellen USB-Gerät sprechen lässt.

Die App merkt sich die Flipper, die du benutzt hast, und verbindet sich von selbst wieder. Hängt einer per USB dran,
gewinnt er gegen das zuletzt genutzte Bluetooth-Gerät. Unter Android hält ein Vordergrunddienst die
Bluetooth-Verbindung offen, während die App im Hintergrund ist.

## Firmware

- **Updater** mit Release- und Dev-Kanal samt Changelogs. Er lädt und installiert direkt aus der App: den
  Unleashed-Basis-Build, den Build mit Extra-Apps, den kompakten Build und die offiziellen Kanäle.
- **Repair from DFU mode** flasht den Flipper per USB komplett neu. Dasselbe wie Full Repair in qFlipper, für ein
  Gerät, das nicht mehr bootet.
- **Release-Benachrichtigungen** sind optional, und der Dev-Kanal hat seinen eigenen Schalter.

## Gerät

- **Geräteinformationen**: Firmware-Version und Build-Datum, Akku, Speicher.
- **GPS und Internet teilen**: das Telefon gibt seinen Standort an Apps auf dem Flipper weiter und leitet dessen
  Netzwerkverkehr durch. Deine Firmware braucht dafür die RPC-GPS/Netzwerk-Erweiterung.
- **Remote Desktop**: der Bildschirm des Flippers live auf Telefon oder PC, mit Tasten auf dem Display. Am Computer
  kannst du die echte Tastatur nutzen. Screenshots lassen sich exportieren, und der Bildschirm kann als GIF
  aufgezeichnet werden.
- **Kommandozeile**: die komplette Flipper-CLI. Nur über USB, also nicht unter iOS.

## Archiv

Eine Kopie deiner Schlüssel liegt auf dem Telefon, ein Archiv pro Flipper. Jede Datei ist als **synced**,
**remote-only**, **local-only** oder **deleted** markiert, du siehst also, was wo liegt, und eine gelöschte Datei
lässt sich wiederherstellen. Dateien können als Favoriten markiert werden.

Kategorien: Sub-GHz, Wardriving (Autosaves inklusive), RFID 125, NFC, Infrared, iButton, Bad USB, JavaScript.

Du kannst eine Datei direkt aus der App ausführen. NFC, RFID und iButton werden über RPC emuliert; Sub-GHz,
Infrared, Bad USB und JavaScript öffnen sich in der passenden App auf dem Flipper.

Dazu kommt ein Texteditor mit Hervorhebung für Flipper-Dateiformate, du kannst eine `.sub` oder `.ir` also ohne
Computer reparieren.

## Dateimanager

Durchsucht `/ext` (die SD-Karte) und `/int` (den internen Speicher). Anlegen, umbenennen, löschen, herunterladen,
hochladen und Textdateien bearbeiten.

## Apps

Der App-Katalog, mit Suche, Kategorien, Sortierung, Detailseite und Screenshots. Apps installieren, aktualisieren
und löschen. Er sieht außerdem, was schon auf dem Flipper liegt, vorinstallierte Apps eingeschlossen.

## Werkzeuge

- **Pixel Draw**: ein Pixel-Art-Editor mit Projektverwaltung und Animationen aus mehreren Frames. Er kann
  Dolphin-Animationen importieren und eine Live-Vorschau auf dem Flipper zeigen.
- **Extract MIFARE Keys**: lässt Mfkey32 auf dem Telefon laufen, mit den Nonces, die der Flipper gesammelt hat. Der
  ganze Ablauf steht unter [Schnelle Schlüsselsuche mit qUnleashed](/de/nfc/qunleashed).
- **Remotes Library**: Infrarot-Fernbedienungen aus der offiziellen Quelle und aus dem öffentlichen Repository
  [Lucaslhm/Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB). Durchsehen, suchen, die `.ir`-Datei bearbeiten
  und dann ins Archiv oder direkt nach `/ext/infrared` speichern.
- **Pulse Plotter**: zeichnet rohe Pulsaufnahmen aus Sub-GHz, Infrarot und RFID.
- **Saved Locations**: Kartenmarkierungen aus den Breiten- und Längengraden, die in Archivdateien stehen.

## Seed-Recovery für Sub-GHz-Captures

Manche Fernbedienungen auf KeeLoq-Basis (FAAC SLH, Genius, Erreka, ältere BFT Mitto) verwenden einen geheimen
**Seed**, der zum Dekodieren nötig ist. Der Flipper sammelt mit der App [Seed Capturer](/de/subghz/seed-capturer) nur
die Daten; die eigentliche Suche ist Brute Force und läuft daher in qUnleashed, nicht auf dem Flipper.

1. Nimm die Fernbedienung mit `Apps → Sub-GHz → Seed Capturer` auf: Drücke **immer dieselbe Taste**, jeweils einmal
   ruhig und vollständig, und prüfe, dass der Zähler `Hops` bei jedem Druck hochgeht.
2. Verbinde den Flipper mit **qUnleashed** und öffne dort das Werkzeug **Seed recovery**.
3. Wähle deinen Capture aus der Liste. qUnleashed liest die Captures direkt aus dem Ordner
   `subghz_seed_captures` des Flippers; Hersteller, Frequenz sowie die Werte `Fix` und `Hop` stehen bereits in der
   Datei. **Du musst keine Dateien kopieren, verschieben, umbenennen oder bearbeiten.**
4. Starte die Suche und warte.
5. Wird der Seed gefunden, gibt qUnleashed Seed und Zähler zurück und kann dir die **vollständige geklonte
   Fernbedienung** als `.sub`-Datei speichern (der `Fix` enthält Seriennummer und Taste schon). Leg sie zurück auf den
   Flipper und sende sie — kein Eintippen über `Add Manually` nötig.
6. Wird nichts gefunden, hatte der Capture sehr wahrscheinlich eine Lücke. Nimm erneut auf, halte die Fernbedienung
   dabei direkt an den Flipper, und drücke `Reset` (<kbd>←</kbd>), um neu zu beginnen, wenn ein Tastendruck nicht
   erkannt wird.

::: warning Der Seed gehört zur Anlage
Bei FAAC SLH und Genius ist der Seed **für jede Taste anders**, nimm also die Taste auf, die du nutzen willst. Bei
Erreka gilt der Seed pro Fernbedienung (manchmal pro Anlage). Bei BFT Mitto gilt er pro Fernbedienung, und nur
ältere Modelle mit eigenem Seed brauchen überhaupt einen Capture.
:::

Der komplette Ablauf, inklusive Einlernen des Klons in einen Empfänger, steht unter
[Rolling-Code-Fernbedienungen programmieren](/de/subghz/remote-prog) und [KeeLoq](/de/subghz/keeloq).

Nutze das nur bei deinen eigenen Fernbedienungen und Toren.

## Verwandte Seiten

- [Schnelle Schlüsselsuche mit qUnleashed](/de/nfc/qunleashed)
- [Seed Capturer](/de/subghz/seed-capturer)
- [Flipper Mobile App](/de/mobile/mobile-app)
- [qFlipper](/de/mobile/qflipper)
- [Web-Tools](/de/mobile/web-tools)
