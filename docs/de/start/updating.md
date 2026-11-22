---
title: Aktualisieren
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Aktualisieren

Unleashed wird häufig aktualisiert. Ein Update funktioniert genauso wie eine Installation: die neue Version kommt
**direkt über** die aktuelle. Du musst nicht auf die offizielle Firmware zurück und nichts dazwischen installieren.

## So aktualisierst du

**Empfohlen: [qUnleashed](/de/mobile/qunleashed-app)**, die Begleit-App von Unleashed für **Android, iOS, Windows,
macOS und Linux** (überall per USB, außer unter iOS, das Bluetooth nutzt). Sie lädt die neue Firmware selbst
herunter.

1. Installiere oder aktualisiere qUnleashed von der
   [Releases-Seite](https://github.com/DarkFlippers/qUnleashed/releases).
2. Verbinde den Flipper per USB oder Bluetooth.
3. Öffne den **Firmware-Updater**, wähle den Kanal **Unleashed** (**Release** oder **Dev**) und den Build, den du
   nutzt: **base**, **extra apps** oder **compact**.
4. Starte die Installation und warte, bis der Flipper alle Phasen durchlaufen hat.

Bootet der Flipper nicht mehr, flasht ihn **Repair from DFU mode** in derselben App per USB neu
([Wiederherstellung](/de/start/recovery#firmware-recovery)).

Alternativen, alle beschrieben unter [Installationsmethoden](/de/start/install):

1. **[Web Installer](https://web.unleashedflip.com)**: Connect → Release oder Dev wählen → Install.
2. **qFlipper**: **Install from file** mit der neuen `flipper-z-f7-update-(version).tgz`.
3. **Mobil-App**: eigener Update-Kanal mit der `.tgz`.
4. **Offline**: `f7-update-(version)` nach `/ext/update/` kopieren und `update.fuf` im Archive öffnen.

::: warning Drücke in qFlipper und in der offiziellen App nicht auf „Update“
Die eingebaute Schaltfläche **Update** in qFlipper und in der Flipper Mobile App nutzt den **offiziellen**
Update-Server. Sie ersetzt Unleashed durch die Stock-Firmware. Nutze für Unleashed den Updater von qUnleashed,
**Install from file**, den eigenen Kanal oder den Web Installer.
:::

## Release oder Dev?

| | Release | Dev |
|---|---|---|
| Stabilität | Getestet | Kann Fehler enthalten |
| Neue Funktionen | Mit jedem Release | Sobald sie gemergt sind |
| Bezugsquelle | Web Installer → Release, [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), [@unleashed_fw](https://t.me/unleashed_fw) | Web Installer → Dev, [dev.unleashedflip.com](https://dev.unleashedflip.com), [@kotnehleb](https://t.me/kotnehleb) |

Dev-Builds werden automatisch aus den neuesten Commits gebaut. Sobald ein neuer Build hochgeladen wird, verschwindet
der vorherige von der Website. Fehler kannst du über
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues) melden.

## Was ein Update übersteht

- **Deine Dateien auf der microSD-Karte**: gespeicherte Schlüssel, Karten, Handsender und Skripte bleiben unberührt.
- **Dein eigener Name**: liegt auf der Karte in `/ext/dolphin/name.settings`
  ([Eigener Flipper-Name](/de/start/custom-name)).
- **Einstellungen**: bleiben normalerweise erhalten. **Ausnahme:** Ändert ein Release den Aufbau einer
  Einstellungsdatei, wird diese Datei einmalig auf die Standardwerte zurückgesetzt. Das passiert nur in bestimmten
  Releases. Wenn deine Desktop-Einstellungen (PIN, Favoriten …) nach einem Update zurückgesetzt sind, stelle sie
  erneut ein und sieh ins Changelog.
- **Eingebaute Apps** in `/ext/apps/` werden nur durch die Versionen aus der neuen Firmware ersetzt. Zusätzliche
  App-Pakete können sie nie überschreiben oder auf einen älteren Stand zurücksetzen.

## Version prüfen

- **Main Menu → Settings → About**: Firmware-Version, Build-Datum, Branch und Commit;
- oder <kbd>↓</kbd> auf dem Desktop gedrückt halten, um den Debug-/Info-Bildschirm zu öffnen.

## Wo du nachlesen kannst, was sich geändert hat

- [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases): Changelog jedes Releases;
- [CHANGELOG.md](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md) im Dev-Branch: was im
  nächsten Release kommt;
- App-Updates: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/commits/dev).

## Der Update-Server von Unleashed

Unleashed betreibt einen eigenen Update-Server im gleichen Format wie der offizielle:
`https://up.unleashedflip.com/directory.json`. Offizielle Apps lassen sich nicht darauf umbiegen, ohne sie neu zu
bauen. **uFBT** nimmt diese URL als Argument, um Apps gegen das Unleashed-SDK zu bauen (siehe
[Firmware bauen](/de/dev/build)).

## Wenn ein Update fehlschlägt

1. Mit <kbd>←</kbd> + <kbd>BACK</kbd> neu starten und es erneut versuchen.
2. Eine andere Methode probieren (qUnleashed ↔ Web Installer ↔ qFlipper ↔ offline).
3. Die SD-Karte prüfen (**Settings → Storage → About SD Card**) oder sie nach einem Backup formatieren.
4. Klappt es weiterhin nicht: [Wiederherstellung](/de/start/recovery).
