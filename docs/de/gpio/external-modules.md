---
title: Externe Module
order: 30
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SIM800.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# Externe Module

Die meisten Zusatzplatinen für den Flipper Zero stecken direkt auf der GPIO-Stiftleiste und kommunizieren über einen
von drei Bussen: **SPI** (Pins 2–5), **UART** (Pins 13/14 oder 15/16) oder **I2C** (Pins 15/16). Diese Seite ist eine
Übersichtskarte: welche Modultypen es gibt, welche Firmware oder App sie ansteuert und welche Pins sie belegen — damit
du erkennst, welche sich gemeinsam nutzen lassen.

## Modultypen

| Modul | Bus / Pins | Angesteuert von | Seite |
|---|---|---|---|
| Externes CC1101 (Sub-GHz) | SPI 2–5, GDO0 an 6, Verstärkersteuerung an 7 | Eingebaute Sub-GHz-App (`Radio Settings → Module → External`) | [Externes CC1101](/de/subghz/external-cc1101) |
| NRF24L01 (2,4 GHz) | SPI 2–5, CE an 6 | Plugins NRF24 Sniffer / Mouse Jacker | [NRF24](/de/gpio/nrf24) |
| ESP32-/ESP8266-Wi-Fi-Boards, Wi-Fi Devboard | UART 13/14 (SWD 10/12 zum Debuggen) | Plugins Marauder, Wi-Fi Scanner, Deauther; Black-Magic-Firmware | [ESP32](/de/gpio/esp32), [Devboard](/de/gpio/devboard) |
| SIM800C / SIM800L GSM | UART 13/14 oder 15/16, Versorgung über Pin 1 | Eingebaute SIM800-App | [SIM800](/de/gpio/sim800) |
| GPS (NMEA) | UART | Plugin `[NMEA] GPS` | [GPS](/de/gpio/gps) |
| Video Game Module | UART 13/14, Pins 2–7, Versorgung | Flipper-Firmware + Modul-Firmware | [Video Game Module](/de/gpio/video-game-module) |
| Expansion-Module (Protokoll) | UART 13/14 oder 15/16 | `Settings → Expansion Modules` | [Expansion-Module](/de/gpio/expansion-modules) |
| Externe IR-LED / IR-Booster | Pin 2 (PA7), 5 V an Pin 1 | Eingebaute Infrared-App (`GPIO Settings`) | siehe unten |
| Temperatur-, Feuchte- und Drucksensoren | abhängig vom Sensor (siehe README) | Plugin `Unitemp` | [Unitemp README](https://github.com/quen0n/unitemp-flipperzero#readme) |
| Beliebiges I2C-Gerät | I2C 15/16 | Plugin `i2c Tools`, CLI-Befehl `i2c` | [GPIO-App](/de/gpio/gpio-app) |
| ESP32-CAM | UART | Plugin Camera Suite | [Camera Suite](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |
| Tresore von Sentry Safe / Master Lock (zwei Drähte) | Pin 15 (C1) + GND 8 | Plugin SentrySafe | [SentrySafe](/de/apps/sentry-safe) |

::: tip Unleashed
Unleashed ergänzt direkt in der Firmware Unterstützung für:
- **Externes CC1101** über Hardware-SPI, mit Steuerung von externem Verstärker und LEDs (`Ext Amp & LEDs`,
  standardmäßig aktiv) in `Sub-GHz → Radio Settings`.
- **Externe IR-Module** in `Infrared → GPIO Settings` (automatische Erkennung wie in der Stock-Firmware).
- Die **SIM800**-GSM-App (`Apps → GPIO → SIM800`).

Externe Funkmodule laufen auf jeder Firmware, nicht nur auf Unleashed. Die erste CC1101-Umsetzung schrieb @quen0n
für Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307)); die heute verwendete stammt von **Skorp** aus der offiziellen Firmware, und Unleashed
nutzt diese.

Plugins für alles Übrige (NRF24, Marauder, GPS, Unitemp, i2c Tools, Camera Suite …) stecken in den Paketen Base und
Extra: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest). Siehe
[Apps von der SD-Karte](/de/apps/sd-card-apps).
:::

## Pin-Konflikte

Module, die sich einen Bus teilen, lassen sich nicht ohne Weiteres gleichzeitig betreiben. Die typischen Kollisionen:

| Pins | Belegt durch |
|---|---|
| 2, 3, 4, 5 | SPI: externes CC1101, NRF24 (MOSI, MISO, CS, SCK) |
| 6 | CC1101 GDO0 / NRF24 CE |
| 7 | Verstärkersteuerung des CC1101 (E07-Module) |
| 13, 14 | USART: Wi-Fi-Boards, SIM800, Expansion-Module, Video Game Module, USB-UART-Bridge, Log-Ausgabe |
| 15, 16 | LPUART oder I2C (nicht beides gleichzeitig) |
| 10, 12 | SWD-Debugging (Devboard) |

Wenn du ein „Combo“-Board verwendest, das mehrere Funkmodule trägt (etwa CC1101 + NRF24 + ESP32 auf einer Platine),
richte dich nach seiner eigenen Dokumentation, welche Pins und Plugin-Einstellungen das jeweilige Funkmodul nutzt.

## Externe IR-Module

1. Verbinde den Eingang des IR-LED-Treibers mit **Pin 2 (A7)**, GND mit GND und die Versorgung mit Pin 1 (5 V), falls
   das Modul sie braucht.
2. Öffne `Main Menu → Infrared → GPIO Settings`.
3. Setze `Signal Output`:
   - `Flipper` — die eingebaute IR-LED;
   - `2 (A7)` — das externe Modul an Pin 2;
   - `Detect` — die Firmware erkennt ein angeschlossenes Modul automatisch.
4. Bei ausgewähltem `2 (A7)` kannst du hier auch `5V on GPIO` umschalten. Mit `Detect` zeigt der 5-V-Eintrag `Auto`.

Zur Arbeit mit Fernbedienungen siehe den Abschnitt [Infrarot](/de/infrared/).

## Allgemeine Regeln

1. **Vor dem Einstecken ausschalten.** Große Kondensatoren im Betrieb einzustecken kann die SD-Karte beschädigen.
2. **3,3-V-Logik.** Treibe Flipper-Ausgänge nicht in 5-V-Logik; Eingänge sind nur 5-V-tolerant, solange sie als
   Eingänge konfiguriert sind.
3. **Halte die Strombegrenzungen ein:** 1,2 A an Pin 1 und Pin 9, 20 mA pro I/O-Pin. Siehe
   [Pinbelegung](/de/gpio/pinout).
4. **Kreuze TX und RX** bei UART-Modulen: Flipper TX geht an RX des Moduls.
5. **Vollständig einstecken.** Ein nur halb eingestecktes Modul macht Wackelkontakt.

## Siehe auch

- [GPIO-Pinbelegung](/de/gpio/pinout)
- [GPIO-App](/de/gpio/gpio-app)
- [Expansion-Module](/de/gpio/expansion-modules)
- [Module und ihre Apps](/de/gpio/module-apps)
