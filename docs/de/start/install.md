---
title: Unleashed installieren
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-readme, unleashed-src, flipper-docs]
---
# Unleashed installieren

Es gibt mehrere Wege, Unleashed Firmware zu installieren. Alle installieren dasselbe Update-Paket, das die Firmware,
den Updater und sämtliche Assets enthält (Apps, IR-Bibliotheken, Sub-GHz-Einstellungen und so weiter).

::: tip Vorbereitung
- **Nur bei der Erstinstallation:** zuerst auf das **aktuelle offizielle Release** aktualisieren
  ([Erster Start](/de/start/first-start)).
- **Schon auf Unleashed:** nichts dazwischen installieren. Die neue Version kommt direkt über die aktuelle.
- Achte darauf, dass eine **microSD-Karte eingelegt ist**. Das Update wird auf die Karte entpackt, und dort liegen
  auch die Apps.
- Lade den Akku. Ein komplettes Update dauert mehrere Minuten.
:::

## Welche Datei du herunterladen musst {#which-file-to-download}

Release-Dateien heißen `flipper-z-f7-update-(version)(e / c).tgz`:

| Teil | Bedeutung |
|---|---|
| `flipper-z` | Für das Gerät Flipper Zero |
| `f7` | Hardware-Target. Bei jedem Flipper Zero gleich |
| `update` | Selbst-Update-Paket: Updater, Firmware und alle Assets |
| `(version)` | Firmware-Version |
| Suffix | Variante des App-Pakets, siehe unten |

| Suffix | [Base Apps](https://github.com/xMasterX/all-the-plugins#default-pack) | [Extra Apps](https://github.com/xMasterX/all-the-plugins#extra-pack) |
|---|:---:|:---:|
| `e` | ✅ | ✅ |
| *(keines)* | ✅ | — |
| `c` | — | — |

- **`e`**: alles. Base-Paket plus das Extra-Paket mit Community-Apps. Nimm diese Variante, wenn du unsicher bist.
- **Ohne Suffix**: nur das Base-Paket mit Community-Apps.
- **`c`** („clean“): keine Community-Apps.

**Eingebaute System-Apps** (MFKey, T5577, Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit,
SIM800, FindMy Flipper, USB-/BT-Fernbedienungen, Snake …) kommen **mit der Firmware selbst** und sind in **jeder**
Variante enthalten, auch in `c`. Siehe [Was Unleashed hinzufügt](/de/start/unleashed-features#built-in-apps).

Weitere Dateien eines Releases:
- `flipper-z-any-scripts-(version).tgz`: der Ordner `scripts` für die Firmware- und App-Entwicklung;
- `flipper-z-f7-sdk-(version).zip`: SDK für die App-Entwicklung und für uFBT.

## Methode 1: qUnleashed (empfohlen)

[qUnleashed](/de/mobile/qunleashed-app) ist die eigene Begleit-App des Unleashed-Teams. Sie lädt und installiert die
Firmware selbst, du musst also keine Datei auswählen. Sie läuft unter **Android, iOS, Windows, macOS und Linux** —
überall per USB, außer unter iOS, das sich per Bluetooth verbindet.

1. Installiere qUnleashed für dein System von der
   [Releases-Seite](https://github.com/DarkFlippers/qUnleashed/releases).
2. Verbinde den Flipper per USB oder koppel ihn per Bluetooth (unter iOS geht nur Bluetooth).
3. Öffne in der App den **Firmware-Updater**.
4. Wähle den Kanal **Unleashed**, **Release** oder **Dev**.
5. Wähle den Build: **base**, **extra apps** oder **compact** ([was darin steckt](#which-file-to-download)).
6. Starte die Installation und warte. Der Flipper startet in den Updater neu und durchläuft alle Phasen.

Bootet der Flipper nicht mehr, flasht ihn **Repair from DFU mode** in derselben App per USB komplett neu. Siehe
[Wiederherstellung](/de/start/recovery#firmware-recovery).

Die folgenden Methoden sind Alternativen. Nimm eine davon, wenn qUnleashed nicht zu deinem Setup passt.

## Methode 2: Unleashed Web Installer

Du brauchst einen **Chromium-basierten Browser** (Chrome, Edge, Opera, Brave, Vivaldi) und ein USB-Kabel.

1. Schließe **qFlipper** und alle anderen Flipper-Webseiten. Sie belegen den seriellen Port.
2. Verbinde den Flipper per USB.
3. Öffne **[web.unleashedflip.com](https://web.unleashedflip.com)**.
4. Klicke auf **Connect** und wähle deinen Flipper im Dialog des Browsers aus.
5. Wähle den Branch **Release** oder **Dev**.
6. Klicke auf **Install** und warte. Der Flipper startet in den Updater neu und durchläuft alle Phasen.
7. Fertig. Alle Assets sind installiert.

## Methode 3: Web-Updater von Flipper Lab

1. Öffne die [Seite des aktuellen Releases](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
2. Verbinde den Flipper und klicke auf den Link **Install via Web Updater**.
3. Klicke auf der Seite des Web-Updaters auf **Connect** und danach auf **Install**.
4. Warte, bis das Update durchgelaufen ist.

![Web-Updater](/img/remote/b803c9d8ec0350d6.png)

## Methode 4: qFlipper (1.2.0 oder neuer)

1. Installiere [qFlipper](https://flipperzero.one/update) 1.2.0+ (ältere Versionen können keine `.tgz`-Dateien
   installieren).
2. Lade `flipper-z-f7-update-(version).tgz` von den [Releases](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) herunter.
3. Starte qFlipper und verbinde den Flipper.
4. Klicke auf **Install from file** und wähle die heruntergeladene `.tgz` aus.
5. Das Update startet. Warte, bis es fertig ist.

![qFlipper: Install from file](/img/remote/f1a3ede83085d040.png)

::: warning
Nutze nach der Installation von Unleashed **nicht** die Schaltfläche **Update** in qFlipper. Sie installiert die
**offizielle** Firmware über Unleashed. Verwende stattdessen **Install from file**.
:::

## Methode 5: Flipper Mobile App

### Android, mit einer `.tgz`-Datei
1. Lade `flipper-z-f7-update-(version).tgz` auf das Telefon.
2. Tippe in der Flipper-App auf **Update channel** und wähle **Custom**.
3. Wähle die heruntergeladene `.tgz` und tippe auf **Update**.
4. Warte, bis das Update abgeschlossen ist.

### Android, über den Link zum Web-Updater
1. Tippe auf der Release-Seite auf **Install via Web Updater**.
2. Wenn du gefragt wirst, ob der Browser oder die Flipper-App öffnen soll, wähle die **Flipper App**.
3. Setze die Installation fort und warte.

### iOS
1. Lade `flipper-z-f7-update-(version).tgz` herunter.
2. Öffne die Datei in der App **Files**. Tippe auf **Share** und wähle die **Flipper App**.
3. Tippe in der Flipper-App auf die grüne Schaltfläche **Update**. Prüfe, dass als Update-Kanal
   `Custom flipper-z-f7-update...` angezeigt wird.
4. Warte. **Die iOS-App zeigt am Ende möglicherweise einen Fehler, der Flipper ist aber erfolgreich aktualisiert.**

## Methode 6: Offline-Update von der microSD-Karte

Ohne Programm auf dem Rechner. Funktioniert vom PC und vom Telefon aus.

1. Entpacke `flipper-z-f7-update-(version).tgz` (oder `.zip`). Darin liegt ein Ordner `f7-update-(version)` mit
   `update.fuf`, `resources.tar` und weiteren Dateien.
2. Stecke die Karte in einen PC oder ein Telefon, oder lade die Dateien mit qFlipper hoch.
3. Erstelle im **Wurzelverzeichnis** der Karte einen Ordner `update` und verschiebe `f7-update-(version)` hinein:
   ```text
   /ext/update/f7-update-(version)/update.fuf
   /ext/update/f7-update-(version)/resources.tar
   ...
   ```
4. Prüfe, dass **alle** Dateien vorhanden sind. Die Standard-App **Files** unter iOS zeigt teilweise nur 3 der 6
   Dateien. Nimm dann eine andere Entpack-App, einen PC oder Android.
5. Stecke die Karte wieder in den Flipper.
6. Öffne **Archive** (<kbd>↓</kbd> auf dem Desktop), wechsle auf den Tab **Browser**, navigiere zu
   `update/f7-update-(version)/` und öffne `update.fuf`.
7. Das Update startet. Warte, bis alle Phasen durchgelaufen sind.

![Offline-Update](/img/remote/92717373349f3b7c.png)

## Nach der Installation

- Der About-Bildschirm (**Settings → About**) zeigt die Unleashed-Firmware und die Versionsinfos.
- Beim ersten Start nach einem Update entpackt der Flipper die Ressourcen auf die Karte. Das ist normal.
- Lies [Was Unleashed hinzufügt](/de/start/unleashed-features) und richte das Gerät unter
  [Einstellungen](/de/start/settings) ein.

## Fehlerbehebung

| Problem | Lösung |
|---|---|
| Der Browser kann sich nicht verbinden | qFlipper und andere Flipper-Lab-Tabs schließen. Einen Chromium-Browser verwenden. Anderes Kabel oder anderen Port probieren |
| Das Update schlägt fehl oder hängt | Mit <kbd>←</kbd> + <kbd>BACK</kbd> neu starten, SD-Karte prüfen, eine andere Methode probieren |
| Die Mobil-App verbindet sich nach der Installation nicht | Den Flipper in der App und in den Bluetooth-Einstellungen des Telefons entfernen. Dann am Flipper **Settings → Bluetooth → Unpair All Devices** und neu koppeln |
| Die Hintergrundbeleuchtung bleibt nach der Installation aus | Siehe [FAQ](/de/start/faq#backlight-does-not-work) (Einstellung für den RGB-Mod) |
| Das Gerät ist tot bzw. gebrickt | [Wiederherstellung](/de/start/recovery) |
