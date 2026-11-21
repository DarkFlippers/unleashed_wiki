---
title: Apps
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, flipper-docs, unleashed-src]
---
# Apps

Neben den großen eingebauten Werkzeugen (Sub-GHz, NFC, RFID, Infrared, iButton, Bad USB, GPIO) führt der Flipper Zero
**Apps** aus: kleine Programme, die als `.fap`-Dateien auf der microSD-Karte liegen. Unleashed liefert mit jedem Build
eine Reihe eigener System-Apps, bietet zwei optionale App-Packs an (Base und Extra) und bleibt mit dem offiziellen
Apps Catalog kompatibel.

::: tip Unleashed
Unleashed bleibt API-kompatibel zur offiziellen Firmware, deshalb funktionieren Apps aus dem offiziellen Katalog
(Flipper Lab oder die Mobil-App) in der Regel ebenfalls. Darüber hinaus gibt es zu jedem Unleashed-Release einen
`e`-Build, in dem das Pack **Extra Apps** mit Community-Apps vorinstalliert ist. Siehe
[Apps im Lieferumfang von Unleashed](/de/apps/catalog).
:::

## Apps beziehen und starten

- [Apps im Lieferumfang von Unleashed](/de/apps/catalog): eingebaute Apps, die Packs Base und Extra und was die Build-Buchstaben `e`, ` ` und `c` bedeuten.
- [Apps auf der SD-Karte (.fap)](/de/apps/sd-card-apps): wo Apps liegen, wie du sie von Hand oder aus dem Katalog installierst und wie der Loader die API-Version prüft.
- [Archive (Dateibrowser)](/de/apps/archive): gespeicherte Dateien durchsuchen, starten, anpinnen, umbenennen, verschieben und löschen.
- [Probleme mit Apps](/de/apps/troubleshoot): was jede Loader-Fehlermeldung bedeutet und wie du sie behebst.

## Eingebaute Apps

- [U2F-Sicherheitsschlüssel](/de/apps/u2f): den Flipper als zweiten Faktor nach FIDO U2F nutzen.
- [Clock (Uhr)](/de/apps/clock): Nachtuhr mit Helligkeitsregelung, Stoppuhr und täglichem Wecker.
- [USB-/Bluetooth-Fernbedienung (HID)](/de/apps/hid-remote): alle Modi der HID-Fernbedienungs-App, Taste für Taste.
- [HID-Fernbedienung verbinden](/de/apps/controllers): die Fernbedienung über Bluetooth oder USB verbinden und Kopplungsprobleme lösen.
- [FindMy Flipper](/de/apps/find-my-flipper): den Flipper in Apple Find My, Samsung SmartThings, Tile oder Google Find My Device sichtbar machen.
- [Hauptmenü-Stile](/de/apps/menu-styles): das Aussehen des Hauptmenüs ändern (PS4, Wii, DSi, C64, CoverFlow, Grid und andere).
- [Snake](/de/apps/snake): das klassische Spiel.

## Apps aus den Packs

- [Barcode Generator](/de/apps/barcode)
- [Multi Converter](/de/apps/multi-converter)
- [Sentry Safe](/de/apps/sentry-safe)

Die Hilfs-Apps für Sub-GHz, NFC und RFID (Seed Capturer, Remote Analyzer, MFKey, T5577 und andere) sind in ihren
eigenen Abschnitten beschrieben, zum Beispiel [Seed Capturer](/de/subghz/seed-capturer),
[MFKey-App](/de/nfc/mfkey-app) und [T5577-App](/de/rfid/t5577-app).
