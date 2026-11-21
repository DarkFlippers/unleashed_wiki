---
title: Kommandozeile (CLI)
order: 100
original: [https://docs.flipper.net/zero/development/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/toolbox/cli]
sources: [flipper-docs, unleashed-src]
---
# Kommandozeile (CLI)

Der Flipper stellt über USB-Serial eine Textkonsole bereit. Von dort aus kannst du Signale lesen und senden, Apps
starten, Dateien verwalten, Logs beobachten, GPIO und LEDs steuern, mit anderen Flippern über Sub-GHz chatten und
viel mehr — praktisch für Skripte, Fehlersuche und App-Entwicklung.

## Mit der CLI verbinden

::: warning Schließe zuerst qFlipper
Nur ein Programm kann den seriellen Port des Flipper gleichzeitig nutzen. Beende **qFlipper** (und schließe Flipper
Lab oder andere Terminals), bevor du dich verbindest.
:::

Die serielle Geschwindigkeit ist **230400** Baud (bei USB CDC wird der Wert meist ignoriert, manche Terminals
verlangen ihn aber).

### Variante 1: Flipper Lab (Browser)

Funktioniert in Chrome, Edge oder einem anderen Chromium-Browser mit Web-Serial-Unterstützung.

1. Verbinde den Flipper über USB.
2. Öffne [lab.flipper.net](https://lab.flipper.net/) → **CLI**.

### Variante 2: Web-Serial-Terminal (Browser)

1. Verbinde den Flipper über USB und öffne einen Chromium-Browser.
2. Gehe zum [Web-Serial-Terminal](https://googlechromelabs.github.io/serial-terminal/).
3. Setze **Baud rate** auf **230400**, klicke **Connect**, wähle deinen Flipper und klicke **Connect**.

### Variante 3: Serielles Terminal — macOS

1. Finde den Port:

   ```sh
   ls /dev/cu.*
   ```

   Der Flipper erscheint als `/dev/cu.usbmodemflip_NAME`, wobei `NAME` der Name deines Flipper ist.
2. Verbinde dich mit **screen**:

   ```sh
   screen /dev/cu.usbmodemflip_NAME
   ```

   Beenden: <kbd>Ctrl</kbd>+<kbd>A</kbd>, dann <kbd>K</kbd>, dann <kbd>Y</kbd>.
3. … oder mit **minicom** (Installation über [Homebrew](https://brew.sh/): `brew install minicom`):

   ```sh
   minicom -D /dev/cu.usbmodemflip_NAME
   ```

   Beenden: <kbd>Esc</kbd>+<kbd>Z</kbd>, dann <kbd>X</kbd>, dann <kbd>Return</kbd>.

### Variante 3: Serielles Terminal — Linux

1. Finde den Port:

   ```sh
   ls /dev/serial/by-id/
   ```

   Suche nach `usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00`. Wenn du nur ein serielles Gerät hast, ist es
   üblicherweise auch `/dev/ttyACM0`; qFlipper zeigt den Portnamen ebenfalls an.
2. Verbinde dich:

   ```sh
   screen /dev/serial/by-id/usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00
   # or
   minicom -D /dev/ttyACM0
   ```

   screen beenden: <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>K</kbd>, <kbd>Y</kbd>. minicom beenden:
   <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>X</kbd>, <kbd>Return</kbd>.

::: tip
Wenn du unter Linux "permission denied" bekommst, füge dich der Gruppe `dialout` hinzu (oder `uucp` auf manchen
Distributionen) und melde dich neu an.
:::

### Variante 3: Serielles Terminal — Windows

1. Installiere [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Verbinde den Flipper; notiere im **Geräte-Manager → Anschlüsse (COM & LPT)** seinen COM-Port (ab- und
   wieder anstecken, um zu sehen, welcher erscheint).
3. Wähle in PuTTY **Connection type: Serial**, **Serial line**: z. B. `COM3`, **Speed**: `230400` und klicke
   **Open**.

### Aus dem Firmware-Baum

Wenn du den Firmware-Quellcode hast, öffnet `./fbt cli` direkt eine CLI-Sitzung; mit uFBT nutze `ufbt cli`.

**Erwartetes Ergebnis:** ein Flipper-ASCII-Art-Banner, "Welcome to Flipper Zero Command Line Interface!", die Zeile
mit der Firmware-Version und ein `>:`-Prompt.

## Eingebaute und externe Befehle

Führe `help` oder `?` aus, um die auf deinem Gerät verfügbaren Befehle aufzulisten.

::: tip Unleashed / neue CLI-Architektur
Die meisten Funk- und Peripheriebefehle (`subghz`, `nfc`, `ir`, `rfid`, `ikey`, `onewire`, `bt`, `crypto`, `js`,
`gpio`, `led`, `vibro`, `buzzer`, `i2c`, `neofetch`, …) sind **externe CLI-Plugins**, die aus dem SD-Karten-Ordner
`/ext/apps_data/cli/plugins` geladen werden (Dateien mit dem Präfix `cli_`). Ohne SD-Karte — oder mit einer
beschädigten — bleiben nur die Kernbefehle. Führe nach dem Kopieren oder Aktualisieren von Plugins
`reload_ext_cmds` aus, statt neu zu starten.
:::

### Befehlsübersicht

| Befehl | Beschreibung |
|---|---|
| `!` | Alias für `info device` |
| `?`, `help` | Listet die verfügbaren Befehle auf |
| `bt` | Testwerkzeug für den Funkkern (BLE) — HCI-Version und, im Debug-Modus, Carrier-/Paket-Tests |
| `buzzer` | Spielt einen Ton oder eine Note auf dem Piezo-Lautsprecher |
| `crypto` | Schlüsselbereitstellung in der Secure Enclave und AES-Ver-/Entschlüsselung |
| `date` | Zeigt / setzt Datum und Uhrzeit |
| `device_info` | Alias für `info device` (veraltet) |
| `echo` | Sendet empfangene Bytes unverändert zurück (für Performance-Tests); stoppt mit <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `exit` | Verlässt die Shell (nützlich in Sub-Shells wie `nfc`) |
| `factory_reset` | Setzt auf Werkseinstellungen zurück; Daten auf der microSD-Karte bleiben erhalten |
| `free` | Informationen zum Heap-Allocator — allgemeine Speicheranalyse |
| `free_blocks` | Freie Heap-Blöcke und ihre Größen — zum Abschätzen der Fragmentierung |
| `gpio` | Modus setzen / schreiben / lesen an GPIO-Pins |
| `i2c` | Durchsucht den I2C-Bus nach Geräten |
| `ikey` | Liest, emuliert und schreibt iButton-Schlüssel |
| `info` | Ausführliche Geräte- und Energieinformationen |
| `input` | Zeigt Tastenereignisse, injiziert Tastendrücke |
| `ir` | Empfängt, sendet und dekodiert Infrarotsignale; Universalfernbedienungen |
| `js` | Führt eine JavaScript-Datei aus, die Konsolenausgabe geht an die CLI |
| `led` | Steuert die RGB-LED und die Displaybeleuchtung |
| `loader` | Listet Apps auf, öffnet und schließt sie |
| `log` | Zeigt das Systemlog |
| `neofetch` | Systeminformationen, wie `neofetch` unter Linux |
| `nfc` | NFC-Sub-Shell: dump, emulate, raw, APDU, scanner |
| `onewire` | Durchsucht den 1-Wire-Bus (iButton-Pins) |
| `power` | Ausschalten, Neustart, Neustart in DFU, GPIO 5 V / 3,3 V |
| `reload_ext_cmds` | Lädt die Liste der externen Befehle von der SD-Karte neu |
| `rfid` | Liest, schreibt und emuliert 125-kHz-Karten; RAW-Werkzeuge |
| `sleep` | Wartet eine angegebene Zeit, z. B. `sleep 5s` (nützlich in Skripten) |
| `start_rpc_session` | Schaltet die CLI in den Protobuf-RPC-Modus (von qFlipper/Apps genutzt; normalerweise nicht nötig) |
| `storage` | Dateisystembefehle |
| `subghz` | Sub-GHz-Werkzeuge: rx/tx, RAW, decode, chat |
| `sysctl` | Systemeinstellungen: Debug-Modus, Heap-Tracking |
| `top` | Live-Liste der Threads (wie `top` unter Linux); <kbd>Ctrl</kbd>+<kbd>C</kbd> zum Beenden |
| `update` | Installiert ein Update-Paket, sichert / stellt den internen Speicher wieder her |
| `uptime` | Zeit seit dem letzten Start |
| `vibro` | Schaltet den Vibrationsmotor ein/aus |
| `unit_tests` | Nur im Firmware-Build `unit_tests` — siehe [Unit-Tests](/de/dev/unit-tests) |

## Logs lesen {#reading-logs}

1. Verbinde dich mit der CLI.
2. Starte das Logging auf dem Level, das du brauchst:

   | Befehl | Zeigt |
   |---|---|
   | `log` | Das aktuelle Level aus den Systemeinstellungen |
   | `log error` | Nur kritische Fehler und wichtige Meldungen |
   | `log warn` | Warnungen und nicht kritische Fehler, zusätzlich `error` |
   | `log info` | Nicht kritische Informationen, zusätzlich `warn` |
   | `log default` | Das Standard-Systemlevel (= `info`) |
   | `log debug` | Debug-Informationen, zusätzlich `info` (beeinträchtigt die Performance) |
   | `log trace` | Systemtraces, zusätzlich `debug` (beeinträchtigt die Performance) |

   `log ?` gibt diese Liste auf dem Gerät aus.
3. Benutze den Flipper — die Meldungen erscheinen im Terminal.
4. Mit <kbd>Ctrl</kbd>+<kbd>C</kbd> beenden.

## Über Sub-GHz chatten

Mehrere Flipper auf derselben Frequenz können über die CLI chatten.

1. Jeder Teilnehmer verbindet sich mit der CLI seines Flipper.
2. Führe `subghz chat <frequency_in_hz> <device>` aus, zum Beispiel:

   ```
   subghz chat 868150000 0
   ```

   - Frequenz in Hz innerhalb von 299999755–348000000, 386999938–464000000 oder 778999847–928000000;
   - Gerät `0` = internes CC1101, `1` = externes CC1101-Modul.
3. Tippe eine Nachricht und drücke <kbd>Enter</kbd>.
4. Mit <kbd>Ctrl</kbd>+<kbd>C</kbd> beenden.

::: tip Unleashed
Die Original-Firmware sendet nur auf Frequenzen, die in deiner Region erlaubt sind; Unleashed entfernt die
regionalen TX-Beschränkungen. Beachte die örtlichen Funkvorschriften.
:::

## Befehlsreferenz

### bt

| Befehl | Beschreibung |
|---|---|
| `bt hci_info` | Bluetooth-HCI-Informationen |
| `bt tx_carrier <channel:0-39> <power:0-6>` | *Nur im Debug-Modus.* Startet den TX-Carrier-Test |
| `bt rx_carrier <channel:0-39>` | *Nur im Debug-Modus.* Startet den RX-Carrier-Test |
| `bt tx_packet <channel:0-39> <pattern:0-5> <datarate:1-2>` | *Nur im Debug-Modus.* Startet den TX-Paket-Test |
| `bt rx_packet <channel:0-39> <datarate:1-2>` | *Nur im Debug-Modus.* Startet den RX-Paket-Test |

### buzzer

| Befehl | Beschreibung |
|---|---|
| `buzzer freq <frequency_in_hz> <duration>` | Spielt einen Ton |
| `buzzer note <note> <duration>` | Spielt eine Note; `s` bedeutet Kreuz, z. B. `cs3` = C♯3; Bes werden nicht unterstützt |

Die Dauer akzeptiert `ms`, `s`, `m`, `h`, z. B. `buzzer note cs3 500ms`.

### crypto

Ver- und entschlüsselt mit Schlüsseln, die in der Secure Enclave des Mikrocontrollers liegen.

| Befehl | Beschreibung |
|---|---|
| `crypto encrypt <key_slot> <iv_hex>` | Verschlüsselt Text mit AES256-CBC, Ausgabe in Hex |
| `crypto decrypt <key_slot> <iv_hex>` | Entschlüsselt Hex zurück in Text |
| `crypto has_key <key_slot>` | Prüft, ob ein Slot (1–100) einen Schlüssel enthält |
| `crypto store_key <key_slot> <key_type> <key_size> <key_data_hex>` | **Nicht umkehrbar!** Speichert einen Schlüssel — er kann nicht entfernt werden |

- `key_slot`: die Slots 1–11 sind mit Schlüsseln vorbelegt, die die Firmware verwendet.
- `iv_hex`: 16-Byte-Initialisierungsvektor in Hex.
- `key_type`: `master`, `simple` oder `encrypted`; `key_size`: `128` oder `256`.

### gpio

| Befehl | Beschreibung |
|---|---|
| `gpio mode <pin_name> <0/1>` | Setzt den Pin auf Eingang (0) oder Ausgang (1) |
| `gpio set <pin_name> <0/1>` | Setzt den Pin-Wert |
| `gpio read <pin_name>` | Liest den Pin-Wert |

Pin-Namen: `PA7`, `PA6`, `PA4`, `PB3`, `PB2`, `PC3`, `PC1`, `PC0` — siehe
[GPIO-Pinbelegung](/de/gpio/pinout).

### ikey

| Befehl | Beschreibung |
|---|---|
| `ikey read` | Liest einen iButton-Schlüssel |
| `ikey emulate <key_type> <key_data>` | Emuliert einen Schlüssel |
| `ikey write Dallas <key_data>` | Schreibt 8 Bytes auf einen Dallas-kompatiblen Rohling |

Schlüsseltypen und Datenlänge (Hex): `Dallas` — 8 Bytes, `Cyfral` — 2 Bytes, `Metakom` — 4 Bytes (muss korrekte
Parität enthalten).

### info

| Befehl | Beschreibung |
|---|---|
| `info device` | Geräteinformationen (Firmware, Hardware, Radio-Stack, …) |
| `info power` | Informationen zum Energiesystem |
| `info power_debug` | Ausführliche Energieinformationen |

### input

| Befehl | Beschreibung |
|---|---|
| `input dump` | Gibt Tastenereignisse aus |
| `input send <key> <type>` | Injiziert ein Ereignis; `key`: `up`, `down`, `left`, `right`, `back`, `ok`; `type`: `press`, `release`, `short`, `long` |

Ein vollständiger kurzer Tastendruck besteht aus drei Befehlen, sonst wird die Eingabe verworfen:

```
input send ok press
input send ok short
input send ok release
```

Für einen langen Druck verwende `long` statt `short`.

### ir

| Befehl | Beschreibung |
|---|---|
| `ir rx` | Empfängt und dekodiert IR-Signale |
| `ir rx raw` | Empfängt im RAW-Format |
| `ir tx <protocol> <address> <command>` | Sendet einen Befehl; Address und Command in Hex |
| `ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...` | Sendet RAW-Daten: Frequenz 10000–56000, Tastverhältnis 0–100, maximal 512 Samples |
| `ir decode <input_file> [<output_file>]` | Dekodiert eine Datei mit RAW-Signalen |
| `ir universal list <remote_name>` | Listet die Signale einer Universalfernbedienung auf |
| `ir universal <remote_name> <signal_name>` | Sendet ein Signal aus einer Universalfernbedienung |

Protokolle: `NEC`, `NECext`, `NEC42`, `NEC42ext`, `Samsung32`, `RC6`, `RC5`, `RC5X`, `SIRC`, `SIRC15`, `SIRC20`,
`Kaseikyo`, `RCA`, `Pioneer`.

::: tip Unleashed
Die Namen der Universalfernbedienungen stammen aus den Dateien in `/ext/infrared/assets/`. Unleashed liefert `tv`,
`audio`, `ac`, `projectors`, `fans` und `leds` mit (die Original-Firmware hat weniger). Führe
`ir universal list tv` aus, um die gültigen Signalnamen zu sehen.
:::

### js

| Befehl | Beschreibung |
|---|---|
| `js <path>` | Führt eine JavaScript-Datei aus und gibt deren Konsolenausgabe aus — siehe [JavaScript](/de/dev/js-about) |

### led

| Befehl | Beschreibung |
|---|---|
| `led r <0-255>` / `led g <0-255>` / `led b <0-255>` | Helligkeit des roten / grünen / blauen LED-Anteils |
| `led bl <0-255>` | Helligkeit der Displaybeleuchtung (`128` ≈ 50 %) |

Für reines Rot: `led r 255`, `led g 0`, `led b 0`.

### loader

| Befehl | Beschreibung |
|---|---|
| `loader list` | Listet die verfügbaren Apps auf |
| `loader open <Application Name> [args]` | Öffnet eine App anhand ihres Namens, optional mit Argumenten |
| `loader info` | Zeigt den Zustand des Loaders |
| `loader close` | Schließt die laufende App |
| `loader signal <signal> [arg_hex]` | Sendet ein Signal mit einem optionalen Hex-Argument |

Argumente, die Leerzeichen enthalten, können in Anführungszeichen stehen:

```
loader open subghz "/ext/subghz/Some File.sub"
```

### nfc

`nfc` öffnet eine **Sub-Shell**. Darin: `help` / `?` listet die Befehle auf, `<command> -h` zeigt Details, `exit`
verlässt sie.

| Befehl | Beschreibung |
|---|---|
| `dump -f <path>` | Liest eine physische Karte in eine `.nfc`-Datei aus. Optionen: `-k <key>`, `-p <protocol>`, `-t <timeout_ms>` |
| `emulate -f <path>` | Emuliert eine `.nfc`-Datei |
| `field` | Schaltet das 13,56-MHz-Feld ein; <kbd>Ctrl</kbd>+<kbd>C</kbd> zum Stoppen |
| `scanner` | Listet alle Protokolle auf, die ein Tag unterstützt; `-t` zeigt den Protokollbaum |
| `raw -p <protocol> -d <data>` | Sendet rohe Bytes. Optionen: `-t <timeout>` (Carrier-Zyklen), `-k` Feld eingeschaltet lassen, `-c` CRC anhängen, `-s` vorher Aktivierung/Antikollision durchführen |
| `apdu -d <data> [<data2> ...]` | Sendet APDU(s) an ISO14443-4A/4B- oder ISO15693-3-Tags; `-p 4a`/`4b`/`15` erzwingt das Protokoll |
| `mfu info` | Grundinformationen zu einem MIFARE Ultralight-Tag |
| `mfu rdbl -b <block>` | Liest einen Block |
| `mfu wrbl -b <block> -d <data>` | Schreibt einen 4-Byte-Block |

Protokolle für `dump -p`: `14_3a`, `14_3b`, `14_4a`, `14_4b`, `15` (ISO 15693-3), `felica`, `mfu`, `mfc`, `mfp`,
`des`, `slix`, `st25`, `ntag4` (NTAG 4xx), `t4t` (Type 4 Tag).
Protokolle für `raw -p`: `14a` / `iso14a`, `14b` / `iso14b`, `15`, `felica`.

### onewire

| Befehl | Beschreibung |
|---|---|
| `onewire search` | Sucht nach 1-Wire-Geräten |

### power

| Befehl | Beschreibung |
|---|---|
| `power off` | Schaltet aus |
| `power reboot` | Startet neu |
| `power reboot2dfu` | Startet in den DFU-Modus neu |
| `power 5v <1/0>` | Aktiviert/deaktiviert 5 V an GPIO-Pin 1 |
| `power 3v3 <1/0>` | Aktiviert/deaktiviert 3,3 V an GPIO-Pin 9 (nur im Debug-Modus) |

### rfid

| Befehl | Beschreibung |
|---|---|
| `rfid read [normal/indala/ask134]` | Liest eine Karte im ASK/PSK-Modus; das optionale Argument wählt einen Lesemodus (`ask134` — 134-kHz-Tiertags) |
| `rfid write <key_type> <key_data>` | Schreibt auf einen T5577 |
| `rfid emulate <key_type> <key_data>` | Emuliert |
| `rfid raw_read <ask/ask134/psk> <filename>` | Speichert das Rohsignal in eine Datei |
| `rfid raw_emulate <filename>` | Emuliert eine Rohdatei (Protokoll-Debugging) |
| `rfid raw_analyze <filename>` | Gibt eine Rohdatei aus und versucht, sie zu dekodieren (Protokollentwicklung) |

Schlüsseltypen und Datenlänge (Hex-Bytes):

| Typ | Bytes | Typ | Bytes | Typ | Bytes |
|---|---|---|---|---|---|
| EM4100 | 5 | IoProxXSF | 4 | Paradox | 6 |
| EM4100/32 | 5 | AWID | 9 | PAC/Stanley | 4 |
| EM4100/16 | 5 | FDX-A | 5 | Keri | 4 |
| Electra | 8 | FDX-B | 11 | Gallagher | 8 |
| H10301 | 3 | HIDProx | 6 | Nexwatch | 8 |
| Idteck | 8 | HIDExt | 12 | Radio Key | 6 |
| Indala26 | 4 | Pyramid | 4 | GProxII | 12 |
| Viking | 4 | Jablotron | 5 | Noralsy | 12 |

### storage

Pfade beginnen mit `/int` (interner Flash) oder `/ext` (SD-Karte).

| Befehl | Beschreibung |
|---|---|
| `storage info /ext` | Dateisysteminformationen und freier Speicher |
| `storage format /ext` | Formatiert die SD-Karte (fragt nach Bestätigung) |
| `storage list <path>` | Listet ein Verzeichnis auf |
| `storage tree <path>` | Listet rekursiv auf |
| `storage remove <path>` | Löscht eine Datei oder ein **leeres** Verzeichnis |
| `storage read <file>` | Gibt Größe und Textinhalt aus |
| `storage read_chunks <file> <1-512>` | Gibt den Inhalt in Blöcken der angegebenen Größe aus |
| `storage write <file>` | Hängt in der CLI eingetippten Text an; <kbd>Ctrl</kbd>+<kbd>C</kbd> zum Abschließen |
| `storage write_chunk <file> <1-512>` | Hängt genau N Bytes aus der CLI an (die Eingabe wird nicht wiedergegeben) |
| `storage copy <src> <dst>` | Kopiert eine Datei |
| `storage rename <old> <new>` | Benennt um / verschiebt |
| `storage mkdir <path>` | Erstellt ein Verzeichnis |
| `storage md5 <file>` | MD5-Hash |
| `storage stat <path>` | Informationen zu Datei oder Verzeichnis |
| `storage timestamp <file>` | Zeitpunkt der letzten Änderung |
| `storage extract <archive.tar> <dir>` | Entpackt ein `.tar`-Archiv |

### subghz

| Befehl | Beschreibung |
|---|---|
| `subghz chat <frequency> <device>` | Chattet mit anderen Flippern |
| `subghz tx <3-byte_key_hex> <frequency> <te_us> <repeat> <device>` | Sendet einen Schlüssel (Princeton) |
| `subghz rx <frequency> <device>` | Empfängt und dekodiert |
| `subghz rx_raw <frequency>` | Empfängt RAW |
| `subghz decode_raw <path_to_raw_file>` | Dekodiert eine RAW-`.sub`-Datei und gibt die Ergebnisse aus |
| `subghz tx_from_file <path> <repeat> <device>` | Sendet eine gespeicherte `.sub`-Datei |

Nur im Debug-Modus:

| Befehl | Beschreibung |
|---|---|
| `subghz tx_carrier <frequency>` | Sendet einen unmodulierten Träger |
| `subghz rx_carrier <frequency>` | Empfängt den Träger (RSSI) |
| `subghz encrypt_keeloq <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Verschlüsselt eine Datei mit KeeLoq-Herstellerschlüsseln |
| `subghz encrypt_raw <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Verschlüsselt RAW-Daten |

`device`: `0` — internes CC1101, `1` — externes CC1101 ([externes Modul](/de/subghz/external-cc1101)).
`te_us` — die Basis-Pulslänge in µs.

Beispiel — eine gespeicherte Datei dreimal über das interne Funkmodul senden:

```
subghz tx_from_file /ext/subghz/gate.sub 3 0
```

### sysctl

| Befehl | Beschreibung |
|---|---|
| `sysctl debug <0/1>` | Deaktiviert / aktiviert den System-Debug-Modus |
| `sysctl heap_track <none/main>` | Verfolgt Heap-Allokationen des Haupt-Threads der App; Debug-Builds (`DEBUG=1`) akzeptieren außerdem `tree` (Haupt- und Kind-Threads) und `all` |

### update

| Befehl | Beschreibung |
|---|---|
| `update install /ext/path/to/update.fuf` | Prüft und installiert ein Update-Paket (das `.fuf`-Manifest im entpackten Paketordner) |
| `update backup /ext/backup.tar` | Sichert den internen Speicher |
| `update restore /ext/backup.tar` | Stellt den internen Speicher aus einer Sicherung wieder her |

Siehe [OTA-Updates](/de/dev/ota).

### vibro

| Befehl | Beschreibung |
|---|---|
| `vibro <1/0>` | Schaltet den Vibrationsmotor ein / aus |

## Verwandte Seiten

- [Apps debuggen](/de/dev/debugging)
- [OTA-Updates](/de/dev/ota)
- [Unit-Tests](/de/dev/unit-tests)
- [qFlipper](/de/mobile/qflipper)

MIFARE, MIFARE Ultralight, MIFARE Classic, DESFire und ICODE sind eingetragene Marken von NXP B.V. FeliCa ist eine
Marke der Sony Corporation.
