---
title: Flipper Mobile App
order: 20
original: [https://docs.flipper.net/zero/mobile-app, https://docs.flipper.net/zero/mobile-app/bug-report, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# Flipper Mobile App

Die offizielle **Flipper Mobile App** ([App Store](https://apps.apple.com/us/app/flipper-mobile-app/id1534655259),
[Google Play](https://play.google.com/store/apps/details?id=com.flipperdevices.app)) verbindet sich per Bluetooth mit
dem Flipper. Damit kannst du die Firmware aktualisieren, gespeicherte Schlüssel ansehen und teilen, Apps aus dem
Katalog installieren, den Flipper aus der Ferne steuern und deine Daten sichern.

::: tip Unleashed
Die offizielle Mobile App funktioniert mit Unleashed. Sie kann eine Unleashed-`.tgz` als **Custom**-Update
installieren (siehe unten). Verbindet sich die App nicht mehr, nachdem du Unleashed installiert oder den Namen des
Flippers geändert hast, koppel sie neu, siehe [Verbindungsprobleme](#connection-problems).
:::

## Verbindung zum Flipper herstellen

1. Auf dem Flipper: `Main Menu → Settings → Bluetooth`, dort **Bluetooth** auf **ON** stellen.
2. Tippe in der App auf **Connect** und dann auf **Connect** neben dem Namen deines Flippers.
3. Gib den **Pairing-Code** ein, der auf dem Display des Flippers steht, und tippe auf **Pair**.
4. Warte, bis die App die Synchronisierung abgeschlossen hat.

## Was die App bietet

- **Main Menu** (Geräte-Tab): Update über Bluetooth, **Device Info** (Details zu Hardware und Firmware), **Options**
  (Backup, Logs, Dateimanager, Neustart, Bugreport; der Umfang hängt von iOS/Android ab), manuelle Synchronisierung,
  einen Ton abspielen, um den Flipper zu finden.
- **Archive**: alle gespeicherten Sub-GHz-, RFID-125-, NFC-, Infrarot- und iButton-Dateien. Favoriten, Suche und das
  Wiederherstellen gelöschter Einträge. Tippe auf einen Schlüssel für **Key Info**: emulieren oder senden, zu den
  Favoriten hinzufügen, umbenennen, eine Notiz anhängen, Details ansehen, löschen, teilen.
- **Apps**: der offizielle App-Katalog, Installation über Bluetooth LE, siehe
  [Apps auf der SD-Karte](/de/apps/sd-card-apps).
- **Tools**: **Mfkey32** (Extract MF Keys), um MIFARE-Classic-Schlüssel aus gesammelten Nonces zu berechnen, und die
  **Remotes Library** mit Infrarot-Fernbedienungen (siehe [Infrarot vom Telefon](/de/infrared/mobile)).
- **Widget**: gespeicherte Fernbedienungen und Karten vom Homescreen des Telefons aus emulieren, ohne die App zu
  öffnen (iOS: Today-Ansicht → Bearbeiten → Widget hinzufügen → Flipper; unter Android fügst du es wie jedes andere
  Widget hinzu und tippst zum Konfigurieren darauf).

## Unleashed vom Telefon installieren

::: warning Erste Installation
Wenn das deine erste Custom-Firmware ist, aktualisiere zuerst auf den neuesten **offiziellen** Release und achte
darauf, dass die SD-Karte eingesteckt ist. Du nutzt schon Unleashed? Dann installiere die neue Version einfach
darüber.
:::

### iOS

1. Öffne den [neuesten Unleashed-Release](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) und lade
   `flipper-z-f7-update-(version).tgz` herunter.
2. Wähle in der App **Dateien** die heruntergeladene `.tgz` aus, tippe auf **Teilen** und wähle die App **Flipper**.
3. Prüfe in der Flipper-App, dass im Update Channel `Custom flipper-z-f7-update...` steht, und tippe dann auf das
   grüne **Update**.
4. Warte, bis das Update durchgelaufen ist. Die iOS-App zeigt am Ende manchmal einen Fehler an, der Flipper ist aber
   aktualisiert.

### Android, mit der `.tgz`-Datei

1. Lade `flipper-z-f7-update-(version).tgz` von der Release-Seite herunter.
2. Tippe in der Flipper-App auf **Update channel** → **Custom** und wähle die heruntergeladene Datei aus.
3. Tippe auf **Update** und warte.

### Android, über den Web-Updater-Link

1. Tippe auf der Release-Seite auf **Install via Web Updater**.
2. Wenn Android fragt, womit der Link geöffnet werden soll, wähle die App **Flipper**.
3. Setze die Installation fort und warte.

Ein Update über Bluetooth kann rund 10 Minuten dauern. Andere Wege: [Unleashed installieren](/de/start/install).

### Wenn das Update fehlschlägt

- Prüfe, ob der Flipper eingeschaltet und noch per Bluetooth verbunden ist.
- Starte den Flipper neu (<kbd>←</kbd> + <kbd>Back</kbd>) und beginne das Update von vorn.
- Schlägt es weiterhin fehl, ist der interne Speicher möglicherweise voll oder defekt: installiere stattdessen mit
  [qFlipper](/de/mobile/qflipper) oder dem [Web Installer](/de/mobile/web-tools#unleashed-web-installer), siehe
  [Wiederherstellung](/de/start/recovery).

## Schlüssel sichern

1. Tippe im Geräte-Tab auf **Options → Backup Keys**.
2. Wähle, wohin das `.zip` mit deinen Schlüsseln, Karten und Fernbedienungen gespeichert oder geteilt werden soll.

Zum Wiederherstellen entpacke das Archiv und lade die Dateien mit [qFlipper](/de/mobile/qflipper) hoch. Für ein
vollständiges Backup der SD-Karte lade die gesamte Karte im **File manager** von qFlipper herunter.

## Verbindungsprobleme {#connection-problems}

**Nach der Installation von Unleashed oder dem Umbenennen des Flippers verbindet sich die App nicht mehr:**

1. Tippe in der App auf **Forget flipper**.
2. Suche den Flipper in den Bluetooth-Einstellungen des Telefons, öffne seine Optionen und wähle
   **Gerät entfernen** („Forget device“).
3. Auf dem Flipper: `Settings → Bluetooth → Unpair All Devices` und mit **Unpair** bestätigen.
4. Stelle sicher, dass Bluetooth auf dem Flipper auf ON steht, und koppel die Geräte dann erneut über die App.

**Der Flipper wird nicht gefunden:** Prüfe, ob Bluetooth auf beiden Geräten aktiv ist, trenne den Flipper von anderen
Geräten (zum Beispiel vom Host einer [Bluetooth-Fernbedienung](/de/apps/controllers)), aktualisiere App und Firmware
und starte den Flipper neu.

**Die Synchronisierung schlägt fehl:** Entkoppel die Geräte und koppel sie erneut, starte beide Geräte neu und
probiere auf dem Flipper `Settings → System → Sleep Method → Legacy`.

## Fehler in der App melden

Fehler in der offiziellen App: **Options → Report Bug**, Titel und Schritte zum Reproduzieren eintragen, die Logs
angehängt lassen, auf **Submit** tippen und die Issue-ID optional auf
[forum.flipperzero.one](https://forum.flipperzero.one/) posten (Bereich Mobile App). So sammelst du Flipper-Logs für
einen Report: Stelle `Settings → System → Log Level` auf **Debug**, verbinde den Flipper per USB, öffne ein serielles
Terminal mit **230400** Baud (oder [lab.flipper.net/cli](https://lab.flipper.net/cli)), führe `info device` und
danach `log` aus, reproduziere den Fehler und entferne die Zeilen `hardware.uid` und `hardware.name`, bevor du das
Log veröffentlichst.

## Verwandte Seiten

- [qFlipper](/de/mobile/qflipper)
- [Begleit-App qUnleashed](/de/mobile/qunleashed-app)
- [Unleashed installieren](/de/start/install)
