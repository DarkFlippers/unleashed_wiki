---
title: qFlipper
order: 10
original: [https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/qflipper/windows-debug, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# qFlipper

**qFlipper** ist die offizielle Desktop-App für den Flipper Zero: Sie aktualisiert Firmware und Datenbanken, verwaltet
Dateien auf der microSD-Karte, erstellt Backups und stellt das Gerät wieder her, repariert defekte Firmware und
spiegelt das Display. Sie läuft unter Windows, macOS und Linux.

::: tip Unleashed
Die Update-Kanäle von qFlipper (Release / RC / Dev) installieren die **offizielle** Firmware. Um Unleashed zu
installieren, nutze **Install from file** mit der `.tgz` von Unleashed (qFlipper 1.2.0 oder neuer), siehe unten, oder
den [Web Installer](/de/mobile/web-tools#unleashed-web-installer).
:::

## qFlipper installieren

Lade die App von [flipperzero.one/update](https://flipperzero.one/update) herunter und führe den Installer aus.

- **Windows**: nur Windows 10 und 11. Der Installer bringt auch die Treiber mit.
- **macOS**: ab 10.14, für Apple Silicon optimiert.
- **Linux**: ein AppImage. Mach die Datei ausführbar und richte die udev-Regeln ein:

```bash
chmod +x qFlipper-x86_64.AppImage
./qFlipper-x86_64.AppImage                 # starten
./qFlipper-x86_64.AppImage rules install   # udev-Regeln, für den Betrieb als normaler Benutzer
```

(Im Dateimanager: Eigenschaften → Zugriffsrechte → „Datei als Programm ausführen“ / „Ist ausführbar“.)

## Überblick

Schließe den Flipper mit eingesteckter SD-Karte per USB an und starte qFlipper.

- **Device information**: Angaben zu Hardware und Firmware, Update-Schaltfläche, Fernsteuerung.
- **Advanced controls**: Backup, Restore, Zurücksetzen auf Werkseinstellungen, Update-Kanal, **Install from file**.
- **File manager**: Dateien auf der SD-Karte und im internen Speicher ansehen, hochladen, herunterladen, umbenennen
  und löschen.

## Unleashed mit qFlipper installieren

1. Achte darauf, dass eine **SD-Karte** eingesteckt ist.
2. Lade `flipper-z-f7-update-(version).tgz` von den
   [Unleashed-Releases](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) herunter (wähle den
   gewünschten Build-Buchstaben, siehe [Build-Varianten](/de/apps/catalog#build-variants)).
3. Starte qFlipper und schließe den Flipper an.
4. Klicke auf **Install from file** und wähle die `.tgz` aus.
5. Warte, bis alle Schritte durchgelaufen sind. Der Flipper startet in Unleashed neu, mit allen installierten Assets.

Du nutzt schon Unleashed? Dann installiere die neue Version einfach darüber, ein Rückweg zur offiziellen Firmware ist
nicht nötig. Weitere Wege: [Unleashed installieren](/de/start/install), [Aktualisieren](/de/start/updating).

## Dateien hoch- und herunterladen

Zieh im **File manager** Dateien in einen Ordner oder klicke mit der rechten Maustaste auf einen Ordner →
**Upload here**. Rechtsklick auf eine Datei oder einen Ordner → **Download** kopiert sie auf den Computer (ein
einfacher Weg, die ganze SD-Karte zu sichern).

| Befehl | Windows / Linux | macOS |
|---|---|---|
| Ordner öffnen | Return | Return |
| Zurück | Backspace | Backspace |
| Hochladen (Upload) | Ctrl+L | Cmd+L |
| Herunterladen (Download) | Ctrl+D | Cmd+D |
| Löschen | Delete | Fn+Backspace |
| Sofort löschen | Shift+Delete | Shift+Fn+Backspace |
| Neuer Ordner | Ctrl+N | Cmd+N |
| Umbenennen | Ctrl+E | Cmd+E |
| Aktualisieren | Ctrl+G | Cmd+G |

## Fernsteuerung und Screenshots

Klicke unter **Device information** auf das Bild des Flippers und dann auf die Tasten am Bildschirm, oder nutze die
Tastatur (ℹ️ zeigt die Tastenbelegung). **SAVE SCREENSHOT** speichert das aktuelle Display als Bild.

## Logs und Bugreports

- **LOGS → OPEN FULL LOG** zeigt das Log der laufenden Sitzung; du kannst es als `.txt` speichern.
- qFlipper behält die Logs der letzten 100 Sitzungen: Rechtsklick auf den Log-Bereich unter **LOGS** →
  **Browse all logs**.
- Probleme mit dem offiziellen qFlipper gehören auf [forum.flipperzero.one](https://forum.flipperzero.one/) (Bereich
  Firmware update / qFlipper). Probleme mit Unleashed selbst gehören in die Unleashed-Chats oder in die GitHub-Issues.

## Fehlerbehebung

### qFlipper sieht den Flipper nicht / Chrome kann sich nicht verbinden

Den seriellen Port kann immer nur ein Programm belegen. Solange qFlipper offen ist, können Flipper Lab, der Web
Installer und die anderen Web-Tools keine Verbindung aufbauen — und umgekehrt. Schließe qFlipper (und überzählige
Flipper-Lab-Tabs), bevor du ein Browser-Tool nutzt.

### Treiber unter Windows

1. Installiere qFlipper nur aus offiziellen Quellen, dann kommen die richtigen Treiber mit. Nach Updates suchen:
   **Advanced controls → CHECK APP UPDATES**.
2. **Normalbetrieb** (Flipper läuft): Der Flipper erscheint als **USB Serial Device** unter
   `Geräte-Manager → Anschlüsse (COM & LPT)`, Hardware-ID **VID 0483, PID 5740**, Treiber von **Microsoft**. Ist ein
   anderer Treiber installiert, deinstalliere ihn und schließe den Flipper erneut an.
3. **COM-Port-Konflikt**: zwei serielle Geräte auf derselben COM-Nummer. Öffne eines davon →
   **Anschlusseinstellungen → Erweitert** und weise eine freie **COM-Anschlussnummer** zu.
4. **Recovery-Modus (DFU)**: Halte <kbd>←</kbd> + <kbd>Back</kbd>, lass <kbd>Back</kbd> los und halte <kbd>←</kbd>
   weiter, bis die LED blau leuchtet. Der Flipper muss als **DFU in FS Mode** unter `USB-Geräte` erscheinen,
   **VID 0483, PID DF11**, Treiber **STMicroelectronics**.
5. Steht stattdessen **STM Device in DFU mode** unter `USB-Controller`, ist der falsche Treiber installiert:
   deinstalliere qFlipper, installiere es von der offiziellen Seite neu und prüfe nochmals.
6. Hängt **DFU in FS Mode** mit einem Ausrufezeichen unter `Andere Geräte`: Rechtsklick → **Treiber aktualisieren →
   Auf dem Computer nach Treibern suchen → Aus einer Liste auswählen** → **USB-Geräte** → **WinUsb Device**.

Wenn der Flipper überhaupt nicht startet, siehe [Wiederherstellung](/de/start/recovery).

## Verwandte Seiten

- [Unleashed installieren](/de/start/install)
- [Flipper Mobile App](/de/mobile/mobile-app)
- [Web-Tools](/de/mobile/web-tools)
