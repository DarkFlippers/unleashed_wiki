---
title: Apps im Lieferumfang von Unleashed
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, unleashed-src]
---
# Apps im Lieferumfang von Unleashed

Eine Unleashed-Installation besteht aus drei App-Ebenen:

1. **System-Apps (eingebaute Apps).** Sie werden aus dem Firmware-Repository gebaut und mit jedem Firmware-Update
   installiert, unabhängig von der gewählten Build-Variante.
2. **Das Base-Apps-Pack.** Eine Sammlung von Community-Apps, im Standard-Build vorinstalliert.
3. **Das Extra-Apps-Pack.** Viele weitere Community-Apps, nur im `e`-Build vorinstalliert.

Zusätzlich kannst du alles Weitere selbst installieren, siehe [Apps auf der SD-Karte](/de/apps/sd-card-apps).

## Build-Varianten {#build-variants}

Die Release-Dateien heißen `flipper-z-f7-update-(version)(e / c).tgz`:

| Teil | Bedeutung |
|---|---|
| `flipper-z` | für Flipper Zero |
| `f7` | Hardware-Target, bei jedem Flipper Zero gleich |
| `update` | Update-Paket: Updater, Assets (Apps, IR-Bibliotheken usw.) und die Firmware selbst |
| `(version)` | Firmware-Version |
| Suffix | welche App-Packs enthalten sind (siehe unten) |

| Suffix | Base Apps | Extra Apps |
|---|:---:|:---:|
| keines (` `) | ja | nein |
| `c` | nein | nein |
| `e` | ja | ja |

- **` ` (kein Buchstabe)** ist der Standard: Firmware, System-Apps und das Base-Pack.
- **`c`**: nur Firmware und System-Apps, kein App-Pack. Nimm diese Variante, wenn du dir deine eigene App-Auswahl
  zusammenstellen willst.
- **`e`**: Firmware, System-Apps, Base-Pack und Extra-Pack.

Der empfohlene Weg, eine dieser Varianten zu installieren, ist der [Web Installer](/de/mobile/web-tools), siehe auch
[Unleashed installieren](/de/start/install).

::: tip Unleashed
Eingebaute Apps sind **kein** Teil des Base- oder Extra-Packs. Ein Firmware-Update schreibt sie in den Ordner `apps/`
auf der SD-Karte, deshalb kann die Installation eines App-Packs eine System-App niemals überschreiben oder auf eine
ältere Version zurücksetzen.
:::

## System-Apps: im Hauptmenü sichtbar

| App | Funktion | Autor / Herkunft |
|---|---|---|
| GPIO | GPIO-Pin-Steuerung, USB-UART-Bridge und die 1-Wire-/iButton-Werkzeuge | OFW |
| iButton | Dallas-, Cyfral- und Metakom-Schlüssel lesen, speichern und emulieren | OFW |
| Infrared | IR-Signale anlernen, speichern und senden, Universalfernbedienungen | OFW |
| NFC | NFC-Karten lesen, speichern, emulieren und auswerten | OFW |
| 125 kHz RFID | LF-RFID-Tags lesen, speichern, emulieren und beschreiben | OFW |
| Bad USB | Ducky-Script-Payloads über USB und BadKB über Bluetooth | OFW + BadKB von Willy-JL, ClaraCrazy und XFW-Mitwirkenden |
| U2F | FIDO-U2F-Sicherheitstoken über USB, siehe [U2F](/de/apps/u2f) | OFW |
| Clock | Uhr mit Helligkeitsregelung, Weckfunktion und einfachem Timer, siehe [Clock](/de/apps/clock) | @nymda, mit @Willy-JL, @mishamyte und @xMasterX |
| Sub-GHz Remote | bis zu 5 gespeicherte `.sub`-Dateien auf die Tasten legen und senden, siehe [Sub-GHz Remote](/de/subghz/remote) | @gid9798 und @xMasterX |

Sub-GHz, Archive, Settings und die Systemdienste sind direkt in die Firmware-Binärdatei kompiliert.

## System-Apps: im Apps-Ordner

Das sind `.fap`-Dateien unter `Main Menu → Apps`, nach Kategorie-Ordnern sortiert.

| App | Ordner | Funktion | Autor / Herkunft |
|---|---|---|---|
| MFKey | NFC | MIFARE-Classic-Schlüssel aus den von Detect Reader gesammelten Nonces wiederherstellen, siehe [MFKey-App](/de/nfc/mfkey-app) | @noproto |
| T5577 | RFID | T5577-Blöcke lesen, bearbeiten und schreiben, Passwort löschen oder zurücksetzen, Passwort mitschneiden, siehe [T5577-App](/de/rfid/t5577-app) | @mishamyte |
| Nice O-Code | Sub-GHz | den Installer-Code einer Nice-O-Code-Fernbedienung wiederherstellen und als `.sub` speichern, siehe [Nice O-Code](/de/subghz/nice-o-code) | @xMasterX |
| Security+ PIN | Sub-GHz | die Tastenfeld-PIN in einem aufgezeichneten Security+ 2.0-Signal finden, siehe [Security+ PIN](/de/subghz/secplus-pin) | @xMasterX |
| Seed Capturer | Sub-GHz | Fix-+-Hop-Paare von FAAC SLH-, Genius-, Erreka- und BFT-Mitto-Fernbedienungen für die Offline-Seed-Wiederherstellung sammeln, siehe [Seed Capturer](/de/subghz/seed-capturer) | @xMasterX |
| Remote Analyzer | Sub-GHz | eine Fernbedienung auf dem internen CC1101 dekodieren, mit eingebautem Frequenzanalysator, siehe [Remote Analyzer](/de/subghz/remote-analyzer) | @xMasterX |
| Sub-GHz RAW Edit | Sub-GHz | eine RAW-`.sub`-Aufnahme öffnen, das Signal finden, zuschneiden, zusammenfügen und dekodieren, siehe [RAW-Editor](/de/subghz/raw-editor) | Lechnio |
| SIM800 | GPIO | ein SIM800C/SIM800L-GSM-Modul ansteuern: Anrufe, SMS, Telefonbuch, USSD, DTMF, AT-Terminal, siehe [SIM800](/de/gpio/sim800) | @xMasterX |
| FindMy Flipper | Bluetooth | BLE-Standortbeacon für Apple Find My / Google Find My Device und andere, siehe [FindMy Flipper](/de/apps/find-my-flipper) | @MatthewKuKanich |
| USB Keyboard & Mouse | USB | die HID-Fernbedienung über USB, siehe [HID-Fernbedienung](/de/apps/hid-remote) | OFW |
| Bluetooth Remote | Bluetooth | die HID-Fernbedienung über Bluetooth, siehe [HID-Fernbedienung](/de/apps/hid-remote) | OFW |
| Snake Game | Games | Snake, siehe [Snake](/de/apps/snake) | OFW |

Die Firmware bringt außerdem **Stile für das Hauptmenü** mit, kleine Plugins, die du unter
`Settings → Desktop → Menu Style` umschaltest, siehe [Hauptmenü-Stile](/de/apps/menu-styles), sowie die
JavaScript-Laufzeitumgebung für `.js`-Skripte (siehe [JavaScript](/de/dev/js-about)).

::: info Neuere Änderungen
Ab dem Build vom 20. Nov. 2026 ist Sub-GHz RAW Edit Teil der Firmware und nicht mehr des Extra-Packs, und SIM800 ist
eine neue eingebaute App (`Apps → GPIO → SIM800`).
:::

## Base- und Extra-Pack {#base-and-extra-packs}

Die Community-Apps werden von @xMasterX in
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev) gesammelt: dieses Repository enthält
die vollständige Liste und den Quellcode, und auf der Seite
[Releases](https://github.com/xMasterX/all-the-plugins/releases/latest) liegen Base- und Extra-Pack als separate
Downloads – falls du ein Pack zu einem `c`-Build hinzufügen oder Apps zwischen Firmware-Releases aktualisieren willst.

Ein Pack von Hand installieren: die `.zip` von der [Releases-Seite](https://github.com/xMasterX/all-the-plugins/releases/latest) laden, entpacken und die App-Ordner in den
Ordner `apps` auf der SD-Karte (`/ext/apps/`) kopieren. Die API-Version des Packs muss zur Firmware passen
(`Current API:` oben in jedem Changelog).

Apps, auf die die Unleashed-ReadMe verweist (jede davon steckt in einem der Packs):

| App | Wo du mehr erfährst |
|---|---|
| TOTP (Authenticator) | [Beschreibung der Konfigurationsdatei](https://github.com/akopachov/flipper-zero_authenticator/blob/master/docs/conf-file_description.md) |
| Barcode Generator | [Barcode Generator](/de/apps/barcode) |
| Multi Converter | [Multi Converter](/de/apps/multi-converter) |
| WAV Player | [Beispieldateien und Konvertierung](https://github.com/UberGuidoZ/Flipper/tree/main/Wav_Player#readme) |
| Sub-GHz Playlist | [Generator-Skript](https://github.com/darmiel/flipper-scripts/blob/main/playlist/playlist_creator_by_chunk.py) |
| Sub-GHz Bruteforcer | [Sub-GHz-Bruteforce](/de/subghz/bruteforce) |
| LF RFID / iButton Fuzzer | [RFID-Fuzzer](/de/rfid/fuzzer), [iButton-Fuzzer](/de/ibutton/fuzzer) |
| Unitemp (Temperatursensoren) | [Verwendung und unterstützte Sensoren](https://github.com/quen0n/unitemp-flipperzero#readme) |
| [NMEA] GPS | [Verwendung](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md) |
| i2c Tools | [Verwendung](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/flipper_i2ctools/README.md) |
| NRF24-Apps | [NRF24](/de/gpio/nrf24) |
| [WiFi] Scanner, [ESP8266] Deauther, [ESP32] WiFi Marauder, [ESP32-CAM] Camera Suite | [ESP32- und Wi-Fi-Module](/de/gpio/esp32) |
| ESP flasher | [FAP "ESP flasher"](https://github.com/0xchocolate/flipperzero-esp-flasher) |
| Sentry Safe | [Sentry Safe](/de/apps/sentry-safe) |

::: warning
Der Inhalt der Packs ändert sich von Release zu Release. Das Build-Tag der aktuellen Packs steht oben in jedem
Unleashed-Changelog (zum Beispiel `Apps: Build tag (20nov2026)`), zusammen mit einem Link zu den neuesten
App-Commits.
:::

## Offizieller Katalog

Der offizielle Flipper Zero Apps Catalog ist über [Flipper Lab](https://lab.flipper.net/apps) und die
[Flipper-Mobil-App](/de/mobile/mobile-app) erreichbar. Die Installation daraus ist unter
[Apps auf der SD-Karte](/de/apps/sd-card-apps#installing-from-the-official-catalog) beschrieben.

## Verwandte Seiten

- [Apps auf der SD-Karte (.fap)](/de/apps/sd-card-apps)
- [Probleme mit Apps](/de/apps/troubleshoot)
- [Unleashed installieren](/de/start/install)
