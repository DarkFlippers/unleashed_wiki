---
title: Hardware
order: 140
original: [https://docs.flipper.net/zero/development/hardware, https://docs.flipper.net/zero/development/hardware/tech-specs, https://docs.flipper.net/zero/development/hardware/schematic, https://docs.flipper.net/zero/development/hardware/flipper-blueprints, https://docs.flipper.net/zero/development/hardware/modules-blueprints, https://docs.flipper.net/zero/development/hardware/vgm-blueprints, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Hardware

Technische Daten des Flipper Zero sowie Hinweise darauf, wo du seine Schaltpläne, Zeichnungen und 3D-Modelle
findest — nützlich für den Bau externer Module und Gehäuse und für Low-Level-Debugging.

![Übersicht der technischen Daten des Flipper Zero](/img/remote/629725f9f16a5946.png)

## Technische Daten

### Gehäuse, Maße und Gewicht

| | |
|---|---|
| Materialien | PC, ABS, PMMA |
| Höhe | 40,1 mm (1.58 in) |
| Breite | 100,3 mm (3.95 in) |
| Tiefe | 25,6 mm (1.01 in) |
| Gewicht | 102 g (3.6 oz) |

### Display

| | |
|---|---|
| Typ | Monochromes LCD |
| Auflösung | 128×64 Pixel |
| Controller | ST7567 |
| Schnittstelle | SPI |
| Diagonale | 1,4″ |

### Mikrocontroller

| | |
|---|---|
| Modell | [STM32WB55RG](https://www.st.com/en/microcontrollers-microprocessors/stm32wb55rg.html) |
| Anwendungskern | Arm Cortex-M4, 32 Bit, 64 MHz |
| Funkkern | Arm Cortex-M0+, 32 Bit, 32 MHz |
| Funk | Bluetooth LE 5.4, 802.15.4, proprietär |
| Flash | 1024 KB (zwischen Anwendung und Funk geteilt) |
| SRAM | 256 KB (zwischen Anwendung und Funk geteilt) |

### Sub-1 GHz

| | |
|---|---|
| Transceiver | [CC1101](https://www.ti.com/product/CC1101) |
| TX-Leistung | maximal −20 dBm (nach offiziellen Angaben) |
| Frequenzbänder | 315 MHz, 433 MHz, 868 MHz, 915 MHz (regionsabhängig) |

Der CC1101 lässt sich in den Bereichen 299,999755–348 MHz, 386,999938–464 MHz und 778,999847–928 MHz abstimmen.

::: tip Unleashed
Unleashed entfernt die regionalen TX-Beschränkungen und ergänzt zusätzliche Frequenzen (350 MHz und 467 MHz werden
dem Standardbereich hinzugefügt). Der Bereich lässt sich über die Datei `subghz/assets/dangerous_settings` weiter
auf 281–361, 378–481 und 749–962 MHz ausdehnen — das liegt außerhalb der CC1101-Spezifikationen und
**kann die Hardware beschädigen** ([gefährliche Einstellungen](/de/start/dangerous-settings)). Ein
[externes CC1101-Modul](/de/subghz/external-cc1101) wird ebenfalls unterstützt. Beachte die Funkvorschriften deines
Landes.
:::

### NFC

| | |
|---|---|
| Transceiver | [ST25R3916](https://www.st.com/en/nfc/st25r3916.html) |
| Frequenz | 13,56 MHz |
| Karten | ISO-14443A/B; NXP MIFARE Classic®, Ultralight®, DESFire® usw.; FeliCa™; HID iClass (Picopass); NFC-Forum-Protokolle |

### 125 kHz RFID

| | |
|---|---|
| Frequenz | 125 kHz |
| Modulation | AM, OOK |
| Kodierung | ASK, PSK |
| Karten (offizielle Liste) | EM-Micro EM4100, HID H10301, IDTECK Idteck, Motorola Indala 26, Kantech IoProx XSF, AWID, FECAVA FDX-A, ISO FDX-B, Generic HID Prox, Generic HID Ext, Farpointe Pyramid, Viking, Jablotron, Paradox, PAC Stanley, Keri, Gallagher, Honeywell Nexwatch, Electra, Securakey |

Welche Protokolle die Unleashed-Firmware tatsächlich unterstützt, steht unter [RFID → Lesen](/de/rfid/read).

### Infrarot

| | |
|---|---|
| RX-Wellenlänge | 950 nm (±100 nm) |
| RX-Trägerfrequenz | 38 kHz (±5 %) |
| TX-Wellenlänge | 940 nm |
| TX-Trägerfrequenz | 0–2 MHz |
| TX-Leistung | 300 mW |
| Protokolle | NEC-Familie, Kaseikyo, RCA, RC5, RC6, Samsung, SIRC |

### iButton (1-Wire)

Dallas DS199x, DS1971, CYFRAL, Metakom, TM2004, RW1990.

### GPIO

- 13 E/A-Pins auf externen 2,54-mm-Stiftleisten verfügbar
- 3,3-V-CMOS-Pegel
- Eingänge sind 5-V-tolerant (siehe ST [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf))
- bis zu 20 mA pro digitalem Pin

Pinbelegung: [GPIO-Pinbelegung](/de/gpio/pinout).

### Akku und Energie

| | |
|---|---|
| Typ | Lithium-Polymer (LiPo) |
| Kapazität | 2100 mAh |
| Laufzeit | bis zu 28 Tage |
| Betriebstemperatur | 0…40 °C (32…104 °F) |

### microSD-Karte

| | |
|---|---|
| Maximale Kapazität | bis zu 256 GB |
| Empfohlene Kapazität | 2–32 GB |
| Schnittstelle | SPI |
| Lese-/Schreibgeschwindigkeit | bis zu 5 Mbps |

Der Flipper wird ohne microSD-Karte geliefert — kaufe eine separat. Siehe [SD-Karte](/de/start/sd-card).

### USB

| | |
|---|---|
| Anschluss | Type-C |
| Standard | USB 2.0 |
| Datenrate | 12 Mbps |
| Maximaler Ladestrom | 1 A |

### Bluetooth LE 5.4

| | |
|---|---|
| TX-Leistung | maximal 4 dBm |
| RX-Empfindlichkeit | −96 dBm |
| Datenrate | 2 Mbps |

### Summer und Vibration

| | |
|---|---|
| Summerfrequenz | 100–2500 Hz |
| Summerlautstärke | 87 dB |
| Summertyp | Coin |
| Vibrationskraft | 30 N |
| Drehzahl des Vibrationsmotors | 13500 U/min |

### Lieferumfang

Flipper Zero, USB-C-auf-USB-A-Kabel, Dokumentation, Aufkleber.

## Schaltpläne

Die Schaltpläne aller Platinen des Flipper Zero werden von Flipper Devices "zu Bildungszwecken" veröffentlicht —
nützlich für die Entwicklung von Hardwaremodulen und für Low-Level-Debugging. Die interaktiven Altium-Viewer und die
PDF-Downloads liegen auf der offiziellen Seite:
**[Schematics of Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)**.

![Platinen des Flipper Zero](/img/remote/db285947a71be613.png)

| Platine | Verfügbare Dokumente |
|---|---|
| **Main PCB** (Rev. 12.1.F7B9C6) | Bestückungszeichnung; Übersicht der Hauptblöcke; Power; Peripherals; MCU STM32WB55; LCD display; Sub-1 GHz CC1101; Buttons |
| **iButton PCB** (Rev. 12.F7B9C6) — trägt außerdem den Piezo-Lautsprecher und IR | Bestückungszeichnung; iButton-Schaltplan |
| **NFC RFID PCB** (Rev. 12.F7B9C6) — 125 kHz RFID und NFC | Bestückungszeichnung; Übersicht der NFC-Blöcke; NFC; Power and vibro; RFID |
| **Antenna PCB** | Platinenbild |

::: info
In Revision 13.F7B9C6 der iButton-Platine haben sich die Footprints der Pogo-Pins geändert: Durchsteck-Pogo-Pins
ersetzen die SMD-Varianten. Die Durchmesser der Footprints sind dieselben wie in 12.F7B9C6.
:::

## Zeichnungen und 3D-Modelle

Alle Dateien sind auf den offiziellen Seiten herunterladbar:

| Was | Dateien | Seite |
|---|---|---|
| Gehäuse des Flipper Zero | 2D-Zeichnung (`.pdf`, `.dwg`), 3D-Modell (`.stl`) | [Blueprints of Flipper Zero](https://docs.flipper.net/zero/development/hardware/flipper-blueprints) |
| Reguläres externes Modul | Zeichnung (`.pdf`), 3D-Modell der Platine (`.stp`, einfach und bestückt), Platinenumriss (`.dwg`, `.dxf`) | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Kleines externes Modul | Derselbe Satz wie beim regulären Modul | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Video Game Module | Zeichnung (`.pdf`, `.dwg.zip`), 3D-Modell (`.stp`) | [Blueprints of Video Game Module](https://docs.flipper.net/zero/development/hardware/vgm-blueprints) |

![Zeichnung des Flipper Zero](/img/remote/c91e01d61829df8e.png)

Die Zeichnungen der externen Module geben die empfohlene Geometrie für Platinen vor, die auf die GPIO-Stiftleiste
gesteckt werden — fang dort an, wenn du dein eigenes Modul entwirfst (siehe auch
[Erweiterungsmodule](/de/gpio/expansion-modules)).

## Entwicklerboards

### Wi-Fi Developer Board

Basiert auf **ESP32-S2-WROVER-N4R2**. Veröffentlichte Dokumente: Platinenansicht, Bestückungszeichnung
(`Wi-Fi Module_V1_Assembly.pdf`), ESP32-S2-Schaltplan, Power-Schaltplan, Connectors-Schaltplan —
[Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).
Verwendung: [Dev Board](/de/gpio/devboard), [Apps debuggen](/de/dev/debugging).

### ST-Link-V3-Entwicklerboard {#st-link-v3-developer-board}

Für fortgeschrittene Entwickler, die In-Circuit-Debugging brauchen. Es basiert auf dem Modul
[ST-Link V3 Mods](https://www.st.com/en/development-tools/stlink-v3mods.html) und unterscheidet sich nur in
Formfaktor und Anschlusskomfort.

- ST-Link V3 Mods zum Flashen und für In-Circuit-Debugging.
- Eingebautes UART-zu-USB, mit dem UART des Flipper verbunden (GPIO-Pins 13 und 14).
- Unbenutzte Pins von Flipper Zero und ST-Link sind zum Debuggen und Prototypen herausgeführt.

Altium-Designer-Projekt:
[github.com/Flipper-Zero/flipperzero-devboard-stlinkv3](https://github.com/Flipper-Zero/flipperzero-devboard-stlinkv3).
Schaltplan und Stückliste: [ST-Link V3 Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3).

::: info Zum Aktualisieren oder Entwickeln brauchst du es nicht
Firmware-Updates, Entwicklung und das Aufspielen eigener Firmware funktionieren alle über normales USB. Ein
Debug-Board brauchst du nur, um die Firmware im laufenden Betrieb zu debuggen (GDB, OpenOCD, …).
:::

## Verwandte Seiten

- [GPIO-Pinbelegung](/de/gpio/pinout)
- [Furi-API](/de/dev/furi-api) — Hardware-Blockdiagramm
- [Apps debuggen](/de/dev/debugging)
- [OTA-Updates](/de/dev/ota)

MIFARE, MIFARE Ultralight, MIFARE Classic und DESFire sind eingetragene Marken von NXP B.V. FeliCa ist eine Marke
der Sony Corporation.
