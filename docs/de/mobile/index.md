---
title: Mobile- und Desktop-Apps
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/mobile-app]
sources: [unleashed-readme, flipper-docs]
---
# Mobile- und Desktop-Apps

Der Flipper funktioniert auch für sich allein, aber mit einem Computer oder Telefon geht vieles deutlich leichter:
Firmware installieren und aktualisieren, Dateien kopieren, Apps installieren, Schlüssel und Fernbedienungen sichern,
den Flipper aus der Ferne steuern.

| Werkzeug | Läuft auf | Wofür |
|---|---|---|
| [qFlipper](/de/mobile/qflipper) | Windows, macOS, Linux | Unleashed aus einer `.tgz` installieren, Dateimanager, Backup / Restore, Recovery |
| [Flipper Mobile App](/de/mobile/mobile-app) | iOS, Android | Update über Bluetooth (auch mit eigener `.tgz`), Archiv der Schlüssel, App-Katalog, Fernsteuerung |
| [qUnleashed](/de/mobile/qunleashed-app) | Android, iOS, Windows, macOS, Linux | die eigene App von Unleashed: Firmware-Updates über BLE oder USB, Archiv, App-Katalog, Fernbildschirm, CLI, Seed-Recovery |
| [Web-Tools](/de/mobile/web-tools) | Browser | Web Installer, Sub-GHz- und Koordinatenkarte, Wi-Fi-Wardriving-Karte, ESP32-Flasher, Flipper Lab |

::: tip Unleashed
Unleashed ist vollständig mit dem offiziellen qFlipper und der offiziellen Flipper Mobile App kompatibel. Der
schnellste Weg, Unleashed zu installieren oder zu aktualisieren, ist der
[Web Installer](/de/mobile/web-tools#unleashed-web-installer) in einem Chromium-Browser.
:::

::: warning Nur eine Verbindung gleichzeitig
Den seriellen USB-Port des Flippers kann immer nur ein Programm belegen. Schließe qFlipper, bevor du Flipper Lab, den
Web Installer, ein CLI-Terminal oder U2F nutzt, und halte nur einen einzigen Flipper-Lab-Tab offen.
:::

## Seiten

- [qFlipper](/de/mobile/qflipper)
- [Flipper Mobile App](/de/mobile/mobile-app)
- [Begleit-App qUnleashed](/de/mobile/qunleashed-app)
- [Web-Tools](/de/mobile/web-tools)
