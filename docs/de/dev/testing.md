---
title: Integrationstests
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/integration_tests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/general_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/badusb_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/cli_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/goodfaps_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/gpio_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/ibutton_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/infrared_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/nfc_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/rfid_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/subghz_test_cases.md]
sources: [unleashed-docs]
---
# Integrationstests

Neben den [Unit-Tests](/de/dev/unit-tests) hat die Firmware einen **manuellen Integrationstestplan**:
Schritt-für-Schritt-Testfälle, nach Subsystem gruppiert, jeder mit einem erwarteten Ergebnis. Er ist für die
Maintainer des Repositorys geschrieben, aber genauso nützlich, wenn du deine eigene Firmware baust und sie prüfen
willst, bevor du sie verwendest oder weitergibst.

Diese Seite fasst den Plan zusammen. Die vollständigen Schrittlisten liegen im Unleashed-Repository unter
[`documentation/testing/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation/testing).

## Was und wann getestet wird

- **Teste, was sich geändert hat, und naheliegende Regressionen.** Teste das neue Verhalten und wiederhole einige
  bestehende Fälle desselben Subsystems. Beispiel: wenn du ein Sub-GHz-Protokoll ergänzt, teste es und einige
  bestehende Protokolle.
- **Überspringe unbeteiligte Subsysteme.** NFC muss nicht getestet werden, wenn sich nur Sub-GHz geändert hat.
- **Teste alles bei Änderungen am Kern** — wenn sich etwas Globales geändert hat, arbeite alle Fälle der Reihe nach
  durch.

Wann: **vor dem Annehmen von Pull Requests** und **vor einem Release Candidate**.

## Gemeinsames Testmuster für Schlüssel und Karten

Die Protokollfälle für RFID, iButton und NFC verwenden dieselben "gemeinsamen Schritte":

1. **Read** des Originals — die Daten stimmen mit dem Original überein.
2. **Emulate** — den emulierten Schlüssel mit einem zweiten Flipper lesen; die Daten sind identisch.
3. **Save** — unter dem angegebenen Namen gespeichert; die Scene wechselt in das Verzeichnis *Saved*.
4. **Write** auf einen Rohling — ein Erfolgsbildschirm erscheint.
5. **Den beschriebenen Rohling lesen** — die Daten sind identisch mit dem gespeicherten Schlüssel.

Viele Fälle brauchen daher **einen zweiten Flipper**, echte Lesegeräte und Rohlinge (T5577, RW2004/RW1990 usw.).

## Testfälle nach Subsystem

### Allgemein (35 Fälle)

| Bereich | Was geprüft wird |
|---|---|
| BLE | Bluetooth nach einem Neustart eingeschaltet; Kopplung mit der Mobil-App, korrekter Flipper-Name; erneute Kopplung mit einem zweiten Smartphone |
| U2F | Einen Schlüssel auf der Yubico-WebAuthn-Demoseite registrieren und authentifizieren |
| Settings | PIN-Code, Storage, Power, System, Bluetooth, Desktop, LCD and Notifications, Flipper Name |
| Archive & Dateibrowser | SD-Karte mit vielen Dateien: <kbd>↓</kbd> auf dem Desktop öffnet Archive; jeder Tab (Favorites, iButton, NFC, Sub-GHz, RFID, Infrared, Browser) zeigt seine Dateien; Schlüssel ausführen, umbenennen, löschen |
| Karten und Protokolle | NTAG215, MIFARE DESFire, MIFARE Ultralight, MIFARE Classic 1K / 4K, Metakom |
| Werksupdate | Über qFlipper unter macOS, Windows 11, Ubuntu; über die Android- und iOS-App; über Flipper Lab im Web |
| Regions-Provisionierung | Dieselben sechs Kanäle wie beim Werksupdate, zusätzlich die Regionseinstellung selbst |
| Apps | Base-Apps, JS-Skripte, das Menü auf der Hoch-Taste |
| Compliance | Alle Compliance-Bildschirme werden korrekt angezeigt |

### CLI (3 Fälle)

- **Steuerbefehle:** `power` (off, reboot, reboot to DFU, `power 5v 1`), `gpio` (mode, `gpio set PA7 1` lässt eine
  LED auf dem Devboard leuchten), `led b 255`, `vibro 1` / `vibro 0`.
- **Informationsbefehle:** mit `minicom -D /dev/ttyACM0 -b 230400` oder PuTTY verbinden; `log debug` während der
  Nutzung des Geräts, mit <kbd>Ctrl</kbd>+<kbd>C</kbd> stoppen; `device_info` / `!` mit dem
  Firmware-Informationsbildschirm vergleichen (<kbd>↓</kbd> auf dem Desktop 3 s halten); `bt hci_info`; `date`;
  `help` / `?`; `free`; `free_blocks`.
- **Storage-Befehle:** `storage info /ext`, `storage format /ext` (ablehnen, dann bestätigen), Informationen mit und
  ohne Karte; `factory_reset` — mit `n` zu antworten tut nichts, mit `y` werden die Einstellungen gelöscht, die
  **Daten auf der SD-Karte und die Uhrzeit bleiben aber erhalten**.

Referenzwerte für `bt hci_info` aus dem Plan:

```
Ret: 0, HCI_Version: 11, HCI_Revision: 16484, LMP_PAL_Version: 11, Manufacturer_Name: 48,
LMP_PAL_Subversion: 8548
```

### Sub-GHz (7 Fälle)

| Fall | Wichtige Prüfungen |
|---|---|
| Read RAW | Auf 315, 433, 868 MHz aufnehmen, einschließlich einer verschlüsselten (Rolling-Code-)Fernbedienung wie Came Atomo; auf den Empfängern des Teststands wiedergeben |
| Frequency Analyzer | Zeigt die korrekte Frequenz verschiedener Fernbedienungen an |
| Externes Modul | Externes CC1101 (433,92-MHz-Modul): das Symbol wechselt auf extern, das Read-RAW-Signal ist stärker als beim internen; das Umschalten zurück auf intern funktioniert. Zieh das Modul nie ab, während es benutzt wird — der Flipper kann einfrieren |
| Gespeicherte Dateien | Dekodierte und RAW-Signale speichern, zu den Favoriten hinzufügen und von dort senden, umbenennen (bleibt in den Favoriten), löschen |
| Empfang / Übertragung | Auf 315.000, 433.920 und 868.350 MHz empfangen, dann mit aktiviertem Hopping; gespeicherte Schlüssel senden — die Relais des Teststands (oder ein zweiter Flipper) reagieren |
| Add Manually | Signale manuell erstellen |

### NFC (7 Fälle)

| Fall | Wichtige Prüfungen |
|---|---|
| Unlock NTAG/Ultralight | *Auth as* mit beiden Typen, Warnung bei falschem Kartentyp, manuelle Passworteingabe; gespeicherte Karten erscheinen nach etwa 1,5 s in *Saved* |
| Detect Reader | Nonces von einem Lesegerät sammeln (z. B. einem anderen Flipper), danach ist der QR-Code-Bildschirm auf <kbd>OK</kbd> lesbar |
| Emulation | Von mehreren Lesegeräten lesbar, darunter ein Flipper auf 10 mm und ein Proxmark |
| Lesen | MIFARE Classic, Ultralight, NTAG, DESFire, NFC-F, EMV-Bankkarten |
| Timing | Das Emulations-Timing von Ultralight und Classic mit einer Referenz per Proxmark 3 vergleichen |
| Add Manually | Karten aller Typen erstellen und speichern, dann emulieren |
| Extra actions | *Read Specific Card Type*, *MIFARE Classic Keys* (Schlüssel hinzufügen/löschen, die Schaltfläche *List*), *Unlock SLIX* mit Passwort |

Proxmark-Befehle für den Timing-Test:

```
hf 14a raw -sc 3000
trace list -t 14a --frame -u
```

### 125 kHz RFID (9 Fälle)

Protokollfälle mit den gemeinsamen Schritten für **EM-Marine EM4100, Motorola Indala26, HID H10301 (Picopass),
Indala26, Troyka/Podorozhnik**, dazu Lesen, Schreiben auf **T5577**, Add Manually und Emulation.

### iButton (9 Fälle)

**Dallas DS1971, DS1990, DS1992, DS1996**, **Cyfral**, **Metakom**: lesen, speichern, Add Manually, emulieren (von
verschiedenen Geräten gelesen), auf einen **RW2004**-Rohling schreiben und zurücklesen, Schlüssel bearbeiten und
löschen.

### Infrarot (3 Fälle)

- **Universalbibliothek** — Fernbedienungen für TV, Audio, Klimaanlagen: Einschalten und weitere Funktionen
  arbeiten.
- **Neue Fernbedienung anlernen** — Fernbedienungen und Tasten hinzufügen/löschen, umbenennen, die bearbeiteten
  Tasten senden.
- **Gespeicherte Fernbedienungen** — Tasten zu einer bestehenden Fernbedienung hinzufügen, Geräte aus
  **mindestens 5 m** steuern, alle Tasten und Fernbedienungen löschen.

### Bad USB (2 Fälle)

Unter macOS und Windows: die Skriptliste erscheint; das Demoskript läuft mit dem EN-Layout und nach dem Wechsel des
Layouts; das "qFlipper download"-Skript öffnet ein Terminal und lädt qFlipper herunter; der Wechsel in den
**BLE**-Modus (Bluetooth eingeschaltet) koppelt mit dem Computer und das Skript läuft erneut.

### GPIO (1 Fall)

`GPIO → Manual Control` mit eingestecktem ST-Link-Devboard: die LEDs folgen den Pins; das Aktivieren von 5 V lässt
die Power-LEDs leuchten.

### GoodFAPs — offizielle Apps (10 Fälle)

| App | Wichtige Prüfungen |
|---|---|
| PicoPass | Karte lesen, speichern, *Elite Dictionary Attack* startet |
| Weather Station | Liest eine von einem zweiten Flipper simulierte Wetterstation auf verschiedenen Frequenzen |
| Apps aus dem Katalog | Installation über die Mobil-App oder das Web, Icon und Name korrekt, Starten/Beenden, Aktualisieren, Deinstallieren (App, Web, Dateibrowser) |
| AVR Flasher | AVR auslesen, AVR flashen, ISP-Programmierung mit `avrdude` |
| Video Game Module | Modul einstecken → Init-Meldung und Symbol in der Statusleiste; HDMI spiegelt das Display; "Air Arkanoid" nutzt den Beschleunigungssensor |
| Tools | Clock (Vollbild, Format aus den Einstellungen); NFC/RFID Detector erkennt beide Feldtypen |
| Signal Generator | PWM- und Clock-Generatoren an verschiedenen Pins, Frequenzen und Teilern |
| NFC Magic | *Check Magic Tag*, *Write Gen1a* (mit Risikowarnung), *Wipe* |
| SPI Mem Manager | Einen SPI-Flash-Chip lesen, schreiben, löschen |
| VGM flashen | App VGM Tool: *Install official firmware*, Installation aus einer Datei auf der SD-Karte und der manuelle Weg (Boot-Taste + USB-Massenspeicher) |

Die im Plan verwendete Verkabelung des AVR Flasher:

| AVR | Flipper |
|---|---|
| MISO | PA6 |
| MOSI | PA7 |
| SCK | PB3 |
| RESET | PB2 |
| GND | GND |
| VCC | 3V3 |

Prüfung des Fuse-Auslesens (ersetze `m2560` durch deinen Chip, z. B. `m328p`, und den COM-Port):

```
avrdude.exe -p m2560 -c stk500v1 -P COM7 -U lock:r:lock.hex:r -U hfuse:r:hfuse.hex:r -U lfuse:r:lfuse.hex:r -U efuse:r:efuse.hex:r
```

::: tip Unleashed
Der Plan stammt aus der offiziellen Firmware. Prüfe bei Unleashed zusätzlich die Unleashed-exklusiven Ergänzungen
in dem Subsystem, das du geändert hast — zum Beispiel zusätzliche Sub-GHz-Protokolle und den
[Counter-Modus](/de/subghz/counter-mode) oder die zusätzlichen Apps in `applications/system/` (Remote Analyzer,
Nice-O-Code, Sec+ PIN, Seed Capturer, Sub-GHz-RAW-Editor, T5577, SIM800 …).
:::

## Verwandte Seiten

- [Unit-Tests](/de/dev/unit-tests)
- [Kommandozeile](/de/dev/cli)
- [Die Firmware bauen](/de/dev/build)
