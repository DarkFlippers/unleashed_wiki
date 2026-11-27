---
title: Was Unleashed hinzufügt
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings]
sources: [unleashed-readme, unleashed-src]
---
# Was Unleashed hinzufügt

Unleashed baut auf der offiziellen Firmware (OFW) auf und bleibt **vollständig kompatibel mit deren API und Apps**.
Alles, was die Stock-Firmware kann, funktioniert weiterhin. Unten sind alle Änderungen und Ergänzungen gegenüber der offiziellen Firmware (OFW) aufgeführt,
nach Bereichen gruppiert und mit Links zu den jeweiligen Detailseiten.

## Sub-GHz: Funkbibliothek und Hardware

- **Regionale Sendebeschränkungen entfernt.** Jede Frequenz, die der CC1101-Chip beherrscht, kann ohne Umwege senden.
- **Zusätzliche Frequenzen** in der Standardliste und eine vom Nutzer editierbare Frequenzliste: [Frequenzen und Presets](/de/subghz/frequencies).
- **Optional erweiterter Frequenzbereich** jenseits der Chip-Spezifikation. Das kann die Hardware beschädigen:
  [Gefährliche Einstellungen](/de/start/dangerous-settings).
- **Große Auswahl an zusätzlichen Protokollen** mit der Möglichkeit, **viele Rolling-Code-Systeme zu speichern und zu senden**:
  [Unterstützte Systeme](/de/subghz/supported-systems), [Rolling Codes](/de/subghz/rolling-codes),
  [KeeLoq](/de/subghz/keeloq).
- Unterstützung für **externe CC1101-Module** über Hardware-SPI, mit Steuerung von Verstärker und LED:
  [Externer CC1101](/de/subghz/external-cc1101).
- **Spezielle Zählermodi** für Rolling Codes, damit der Zähler nicht aus dem Tritt gerät: [Zählermodus](/de/subghz/counter-mode).

## Sub-GHz: Haupt-App

- **Die letzten Einstellungen werden gemerkt** (Frequenz, Modulation …).
- **Verbesserungen am Frequency Analyzer**: Die Grundfunktionen entsprechen der offiziellen Firmware; zusätzlich
  übergibt in Unleashed <kbd>OK</kbd> die erkannte Frequenz an Read und langes <kbd>OK</kbd> springt direkt in Read: [Frequency Analyzer](/de/subghz/frequency-analyzer).
- **Verbesserungen bei Read**: zeigt an, wann jedes Signal empfangen wurde. Halte in der Liste <kbd>→</kbd> gedrückt,
  um ein Signal zu löschen. Bei Protokollen mit mehreren Systemen wird der erkannte Systemname angezeigt (CAME,
  Nice FloR-S, FAAC SLH, KeeLoq): [Read](/de/subghz/read).
- **Protokollnamen in Dateinamen**: mit `Radio Settings → Protocol Names = ON` bekommen gespeicherte Dateien einen
  Zeitstempel plus das Protokoll im Namen.
- **Eigene Tastencodes** für KeeLoq, Alutech AT4N, Nice Flor S, Somfy Telis, Security+ 2.0, CAME Atomo, BelKorn und
  weitere. Mit den Pfeiltasten des Steuerkreuzes sendest du den Code einer anderen Taste: [Als Fernbedienung nutzen](/de/subghz/remote).
- **Erweitertes `Add manually`**: ein Eintrag je System, Bandauswahl, erweiterter Modus mit TE, Guard Time und
  weiteren Feldern. Damit legst du Handsender für FAAC SLH, BFT Mitto, Somfy Telis, Nice Flor S, CAME Atomo und andere
  an und lernst sie an einem Empfänger ein: [Add manually](/de/subghz/add-manually),
  [Neuen Handsender anlernen](/de/subghz/remote-prog).
- **Read RAW → More → Edit** öffnet eine RAW-Datei direkt in Sub-GHz RAW Edit: [RAW-Editor](/de/subghz/raw-editor).
- **Ignore-Filter** für störende Protokolle (Alarme, Sensoren, Türklingeln, Schlüsselfinder, Feron-Leuchten …) und
  Debug-Optionen (Schrittweite des Zählers, Ausgabe auf einem Debug-Pin): [Sub-GHz-Einstellungen](/de/subghz/settings).

## Sub-GHz-Apps

| App | Funktion | Seite |
|---|---|---|
| Sub-GHz Remote | Bis zu 5 `.sub`-Dateien auf die Tasten legen, mit eingebautem Konfigurator | [Remote](/de/subghz/remote) |
| Sub-GHz Bruteforcer | Brute Force auf statische Codes, eigene Dateien, Verzögerung und Wiederholungen | [Bruteforce](/de/subghz/bruteforce) |
| Remote Analyzer | Einen Handsender nach dem anderen dekodieren, mit eingebautem Frequenzanalysator | [Remote Analyzer](/de/subghz/remote-analyzer) |
| Nice O-Code | Den Installer-Code eines Nice O-Code-Handsenders rekonstruieren | [Nice O-Code](/de/subghz/nice-o-code) |
| Security+ PIN | Die Tastenfeld-PIN aus einem Security+ 2.0-Signal ermitteln | [Security+ PIN](/de/subghz/secplus-pin) |
| Seed Capturer | Fix-/Hop-Paare sammeln (FAAC SLH, Genius, Erreka, BFT Mitto), um den Seed zu rekonstruieren | [Seed Capturer](/de/subghz/seed-capturer) |
| Sub-GHz RAW Edit | SD-gestützter RAW-Editor: zuschneiden, ausschneiden/kopieren/einfügen, Rückgängig-Verlauf, zusammenführen und dekodieren | [RAW-Editor](/de/subghz/raw-editor) |

## NFC, RFID und iButton

- **Zusätzliche MIFARE Classic-Schlüssel** im System-Wörterbuch: [MIFARE Classic](/de/nfc/mifare-classic).
  Anleitungen zum Rekonstruieren von Schlüsseln: [Nested & Fudan](/de/nfc/nested-fudan), [MFKey](/de/nfc/mfkey).
- **MFKey** direkt auf dem Gerät: [MFKey-App](/de/nfc/mfkey-app).
- **EMV-Protokoll und Parser für öffentliche Daten**: [Bankkarten (EMV)](/de/nfc/emv).
- **NFC `Add manually` → MIFARE Classic mit eigener UID**: [Add manually](/de/nfc/add-manually).
- **Viele zusätzliche Karten-Parser** (Verkehrs- und Stadtkarten: Troika, Umarsh, Zolotaya Korona, Kazan, Metromoney,
  Moscow Social Card und weitere): [Unterstützte Karten](/de/nfc/supported-cards).
- **NFC Magic 2.0** für Magic Cards, auch für Ultralight: [NFC Magic](/de/nfc/nfc-magic).
- **T5577-App**: Blöcke lesen, bearbeiten und schreiben, Passwort löschen oder zurücksetzen, Passwort-Sniffer (`Sniff Password`):
  [T5577-App](/de/rfid/t5577-app).
- **Anzeigeformat EM4100 DEZ 8**: [RFID lesen](/de/rfid/read).
- **Fuzzer für RFID und iButton**: [RFID Fuzzer](/de/rfid/fuzzer), [iButton Fuzzer](/de/ibutton/fuzzer).

## Infrarot

- Die universelle TV-Fernbedienung ist neu gebaut und deckt **alle Tasten** ab.
- **Große Sammlung universeller Fernbedienungen für Projektoren, Ventilatoren, Klimaanlagen und Audiogeräte**
  (Soundbars …), die vom Team regelmäßig aktualisiert, geprüft und erweitert wird.
- **RCA**-Protokoll und Unterstützung für externe IR-Module (werden automatisch erkannt):
  [Universelle Fernbedienungen](/de/infrared/universal-remotes).
- Wie du gute Aufnahmen zur Aufnahme in die Datenbank der universellen Fernbedienungen anfertigst:
  [IR-Aufnahmen](/de/infrared/captures).

## Bad USB und USB/Bluetooth

- **BadKB**: Bad USB-Skripte über **Bluetooth** ausführen, direkt in die Bad USB-App integriert:
  [Bad USB](/de/badusb/usage).
- **Tastaturlayouts** und der Befehl `DUCKY_LANG`, mit dem ein Skript sein Layout selbst wählt:
  [Skriptformat](/de/badusb/script-format).

## Desktop, Einstellungen und Komfort

- **Eigener Flipper-Name** unter **Settings → Desktop → Change Flipper Name**:
  [Eigener Name](/de/start/custom-name).
- **Uhr auf dem Desktop** (`Settings → Desktop → Show Clock`) und **Akkuanzeigen** (`Battery View`: Bar, %, Inv. %,
  Retro 3, Retro 5, Bar %): [Desktop](/de/start/desktop).
- **Sperren durch Halten von <kbd>↑</kbd>** auf dem Desktop: mit PIN, falls einer gesetzt ist, sonst als normale
  Sperre.
- **Mehr Spiele im Dummy Mode**: jede Pfeiltaste (kurz und lang) und <kbd>OK</kbd> kann eine eigene App starten.
- Unterstützung für den **[RGB-Backlight-Mod](https://github.com/quen0n/flipperzero-firmware-rgb#readme)** unter **LCD and Notifications → RGB Mod Settings** (nur für Flipper mit
  entsprechender Hardware-Modifikation).
- **Cursor bei der Texteingabe** und ein **Mini-Editor für die Byte-Eingabe** (drücke <kbd>↑</kbd> mehrfach, bis der
  Nibble-Editor erscheint).
- **Archive** mit zusätzlichen Tabs (SubRem für die Belegungen von Sub-GHz Remote, Phone für das SIM800-Telefonbuch).

Alle Punkte des Menüs `Settings` sind unter [Einstellungen](/de/start/settings) beschrieben.

## Eingebaute Apps {#built-in-apps}

Diese Apps werden aus dem Firmware-Repository gebaut und bei jedem Update nach `/ext/apps/` installiert, und zwar in
**jeder** Build-Variante (`e`, ohne Suffix, `c`). Die App-Pakete enthalten sie nicht, daher kann ein Paket sie nie
überschreiben oder auf einen älteren Stand zurücksetzen.

**Im Hauptmenü:** GPIO, iButton, Infrared, NFC, 125 kHz RFID, Bad USB (mit BadKB), U2F, **Clock** (Helligkeit, Alarm,
Timer), **Sub-GHz Remote**. Sub-GHz, Archive und Settings sind Teil der Firmware-Binärdatei.

**Unter Apps:**

| App | Kategorie | Seite |
|---|---|---|
| MFKey | NFC | [MFKey-App](/de/nfc/mfkey-app) |
| T5577 | RFID | [T5577-App](/de/rfid/t5577-app) |
| Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit | Sub-GHz | siehe Tabelle oben |
| SIM800 (Anrufe, SMS, Telefonbuch, USSD, AT-Terminal) | GPIO | [SIM800](/de/gpio/sim800) |
| FindMy Flipper (Beacon für Apple FindMy / Google Find My Device) | Bluetooth | [App-Katalog](/de/apps/catalog) |
| USB Keyboard & Mouse, Bluetooth Remote | USB / Bluetooth | [Controller](/de/apps/controllers) |
| Snake Game | Spiele | — |

## App-Pakete der Community

- **Base-Paket** (in den Builds ohne Suffix und in `e`) und **Extra-Paket** (nur in `e`): Quellcode und vollständige
  Liste unter [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev). Die aktuellen Pakete
  liegen bei den [GitHub releases](https://github.com/xMasterX/all-the-plugins/releases/latest).
- Der offizielle Katalog funktioniert ebenfalls: [lab.flipper.net/apps](https://lab.flipper.net/apps) oder über die
  Mobil-App.
- Mehr dazu: [App-Katalog](/de/apps/catalog), [Apps auf der SD-Karte](/de/apps/sd-card-apps).

## Begleit-Apps und Web-Werkzeuge

- **qUnleashed**: Begleit-App für Telefon und PC: [qUnleashed](/de/mobile/qunleashed-app).
- **Web-Werkzeuge**: [Web Installer](https://web.unleashedflip.com), Sub-GHz-Karte
  ([map.unleashedflip.com](https://map.unleashedflip.com)), Wi-Fi-Wardriving-Karte
  ([wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)), ESP32-Web-Flasher
  ([espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)): [Web-Werkzeuge](/de/mobile/web-tools).
