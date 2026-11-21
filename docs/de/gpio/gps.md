---
title: GPS
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples/example_gps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# GPS

Es gibt zwei Wege, dem Flipper einen Standort zu geben:

| Variante | Hardware | Funktionsweise |
|---|---|---|
| **GPS-Dienst (Standort des Begleitgeräts)** | Keine: ein Telefon oder Computer, per USB oder Bluetooth verbunden | Apps fragen die verbundene Begleit-App per RPC nach ihrem Standort |
| **NMEA-GPS-Modul** | Ein serieller GPS-Empfänger am GPIO-UART | Das Plugin `[NMEA] GPS` liest NMEA-Sätze vom Modul |

## GPS-Dienst (Standort des Begleitgeräts)

::: tip Unleashed
Die Unleashed-Firmware enthält einen Systemdienst `gps` (Record `gps`, beim Start gestartet). Er belegt keine
GPIO-Pins: Er leitet Standortanfragen über die aktive **RPC-Sitzung** (USB oder Bluetooth) an die Begleit-App weiter,
die mit der Position des Telefons bzw. Computers antwortet.
:::

Was eine App davon bekommt:

| Feld | Einheit |
|---|---|
| Breiten-, Längengrad | Grad × 10⁷ |
| Kurs | Grad × 100 (0…36000) |
| Geschwindigkeit | mm/s |
| Höhe | cm |
| Genauigkeit | mm |
| Satelliten | Anzahl |

Apps können einen einzelnen Fix anfordern (`gps_request_location()`), einen Datenstrom mit **1–10 Hz**
(`gps_request_stream()` / `gps_stop_stream()`) und außerdem einen Standort an das Begleitgerät zurücksenden
(`gps_report_location()`). Das Begleitgerät kann mit einem Fehler antworten: nicht unterstützt, keine Berechtigung,
Standort deaktiviert, unbekannter Fehler.

### Ausprobieren

Im Quellbaum liegen zwei Beispiel-Apps von @apfxtech (Kategorie `Examples`, als FAPs gebaut):

- **`[RPC] GPS Click`** — einmalige Anfrage: Drücke <kbd>OK</kbd>, um den Standort zu holen; zeigt Breiten- und
  Längengrad, Kurs, Geschwindigkeit, Höhe, Satelliten und Genauigkeit. <kbd>BACK</kbd> beendet.
- **`[RPC] GPS Stream`** — ein durchgehender Datenstrom derselben Werte.

Meldungen, die auftreten können:

| Meldung | Bedeutung |
|---|---|
| `No USB/BLE connection` | Keine RPC-Sitzung: Verbinde die Begleit-App über USB oder Bluetooth |
| `GPS not available` | Das Begleitgerät unterstützt keine Standortabfrage |
| `Permission denied` | Die Begleit-App hat keine Standortberechtigung |
| `Location disabled` | Die Standortdienste sind auf dem Telefon bzw. Computer aus |
| `No response` | Das Begleitgerät hat nicht rechtzeitig geantwortet |
| `Waiting for data...` | Datenstrom gestartet, noch kein Fix |

Die Begleit-App muss diese RPC-GPS-Anfragen unterstützen; prüfe deine Begleit-App (siehe [Mobil](/de/mobile/)).

Für App-Entwickler: Binde `<gps/gps.h>` ein und öffne den Record mit `furi_record_open(RECORD_GPS)`; der Header enthält
außerdem Hilfsfunktionen, um Koordinaten, Kurs, Geschwindigkeit, Höhe und Genauigkeit zu formatieren.

## NMEA-GPS-Modul am UART

Für einen Standort ohne Telefon schließe einen seriellen GPS-Empfänger an (die meisten Module, die NMEA-Sätze mit
3,3-V-Logik ausgeben).

Verdrahtung (USART):

| Flipper-Pin | GPS-Modul |
|---|---|
| 13 (TX) | RX |
| 14 (RX) | TX |
| 9 (3V3) oder 1 (5V) | VCC (Versorgungsbereich des Moduls prüfen) |
| 8, 11 oder 18 (GND) | GND |

Öffne dann das Plugin `[NMEA] GPS` aus den zusätzlichen App-Paketen. Einrichtung, Baudrate und unterstützte Module
stehen in seiner
[README](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md).

::: tip
Das GPS-Modul und andere UART-Nutzer (Wi-Fi-Boards, SIM800, Expansion-Module, Log-Ausgabe) teilen sich die Pins 13/14.
Wenn das Plugin keine Daten erhält, prüfe `Settings → Expansion Modules → Listen UART` und
`Settings → System → Log Device`.
:::

## Apps

Apps, die mit einem GPS-Modul arbeiten, alle aus den App-Paketen:

| App | Paket | Was sie macht |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Position von jedem NMEA-GPS-Modul am UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Zeigt und protokolliert Daten von u-blox-GPS-Modulen über I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | NMEA-Tracker mit Breadcrumb-Navigation |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Dateibrowser, der die Dateien nach Entfernung vom aktuellen Standort sortiert |

Vollständige Liste der Modul-Apps: [Module und ihre Apps](/de/gpio/module-apps).

## Siehe auch

- [ESP32 & Wi-Fi](/de/gpio/esp32) — Wardriving-Karte
- [Externe Module](/de/gpio/external-modules)
- [GPIO-Pinbelegung](/de/gpio/pinout)
