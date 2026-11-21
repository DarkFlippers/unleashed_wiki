---
title: GPIO & Module
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# GPIO & Module

Die 18-polige Stiftleiste an der Oberseite des Flipper Zero macht ihn zum Hardware-Werkzeug: Sie versorgt externe
Module mit Strom und kommuniziert mit ihnen, dient als USB-UART-Adapter, schaltet Pins zum Testen von Hand und ist
Ziel für einen Hardware-Debugger.

![GPIO-Stiftleiste des Flipper Zero](/img/remote/f9f4fe12522d6f9d.png)

## Grundlagen

| Seite | Inhalt |
|---|---|
| [GPIO-Pinbelegung](/de/gpio/pinout) | Alle 18 Pins, Spannungen, Strombegrenzungen, 5 V an Pin 1, 3,3-V-/5-V-Toleranz |
| [GPIO-App](/de/gpio/gpio-app) | `Main Menu → GPIO`: USB-UART Bridge, GPIO Manual Control, 5V on GPIO; CLI-Befehle `gpio` und `i2c` |
| [Externe Module](/de/gpio/external-modules) | Überblick über die Modultypen und die Pins, die jeder davon belegt |
| [Expansion-Module](/de/gpio/expansion-modules) | `Settings → Expansion Modules` und das Expansion Module Protocol |
| [Module und ihre Apps](/de/gpio/module-apps) | Alle Module, die die App-Pakete unterstützen, und was jede App macht |

## Module

| Seite | Modul |
|---|---|
| [Externes CC1101](/de/subghz/external-cc1101) | Sub-GHz-Funk mit stärkerem Frontend (im Sub-GHz-Abschnitt beschrieben) |
| [ESP32 / Wi-Fi](/de/gpio/esp32) | Wi-Fi Devboard, ESP32 Marauder, der Unleashed-Web-Flasher und die Wardriving-Karte |
| [NRF24](/de/gpio/nrf24) | 2,4-GHz-Sniffer mit nRF24L01 und MouseJack |
| [SIM800](/de/gpio/sim800) | GSM-Modul: Anrufe, SMS, Telefonbuch, USSD (eingebaute Unleashed-App) |
| [GPS](/de/gpio/gps) | Standort vom gekoppelten Telefon (GPS-Dienst) und NMEA-GPS-Module am UART |
| [Video Game Module](/de/gpio/video-game-module) | RP2040-Modul mit Videoausgang und Bewegungssensor |

## Wi-Fi Developer Board

| Seite | Inhalt |
|---|---|
| [Devboard: erste Schritte](/de/gpio/devboard) | Flipper vorbereiten, Modul einstecken, Verbindung über USB und Wi-Fi |
| [Devboard: Debugging und Logs](/de/gpio/devboard-debug) | Black Magic / DAPLink, Debugging in VS Code, UART-Logs lesen |
| [Devboard: Firmware-Update](/de/gpio/devboard-firmware) | Die Firmware des Boards selbst mit uFBT flashen |

::: tip Unleashed
Unleashed bringt von Haus aus zusätzliche GPIO-Werkzeuge mit: die [SIM800](/de/gpio/sim800)-App (`Apps → GPIO → SIM800`),
Unterstützung für externe CC1101 samt Verstärkersteuerung in Sub-GHz, Ausgabe über externe IR-Module in
`Infrared → GPIO Settings` sowie eine große Auswahl an GPIO-Plugins in den zusätzlichen App-Paketen. Siehe
[Externe Module](/de/gpio/external-modules).
:::

::: warning Bevor du etwas einsteckst
Schalte den Flipper aus, bevor du ein Modul anschließt, und schiebe das Modul vollständig in die Stiftleiste. Wird ein
Modul mit großer kapazitiver Last im Betrieb eingesteckt, kann die microSD-Karte beschädigt werden, denn Karte und
Pin 9 hängen an derselben 3,3-V-Schiene.
:::
