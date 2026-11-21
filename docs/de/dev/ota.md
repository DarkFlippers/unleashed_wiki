---
title: OTA-Updates
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/OTA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/update.py]
sources: [unleashed-docs, unleashed-src]
---
# Der OTA-Update-Prozess

Wie der Flipper ein Update-Paket installiert — was in jeder Phase passiert, was im Update-Manifest steht, was die
Fehlercodes `[XX-YY]` bedeuten und wie du eigene Pakete baust.

Die Benutzerseite (Unleashed mit qFlipper, dem Web Installer oder von der SD-Karte installieren) steht unter
[Aktualisieren](/de/start/updating). Wenn ein Update schwer scheitert, siehe
[Wiederherstellung](/de/start/recovery).

## Code aus dem RAM ausführen

Die Firmware hat einen besonderen Boot-Modus, der ein speziell aufgebautes Systemabbild in das **RAM** lädt und
dorthin springt. Code, der aus dem RAM läuft, hat vollen Schreibzugriff auf den gesamten Flash — was unmöglich ist,
solange die Hauptfirmware aus eben diesem Flash läuft. Der OTA-Updater nutzt diesen Modus, auch um den Radio-Stack
auf dem zweiten Kern des Mikrocontrollers zu aktualisieren.

## Die drei Phasen

### 1. Den internen Speicher (`/int`) sichern

`/int` ist eine Partition im Flash des Flipper, die allen von der Firmware nicht genutzten Platz einnimmt. Eine neue
Firmware kann eine andere Größe haben, ihre Installation würde den Flash also neu partitionieren und Daten
verlieren. Deshalb wird vor allem anderen der aktuelle Inhalt von `/int` in ein einfaches `.tar`-Archiv auf der
SD-Karte gesichert.

### 2. Das Gerät aktualisieren

Die Hauptfirmware lädt den **Updater** — einen angepassten Build der Firmware — in das RAM und führt ihn aus. Der
Updater arbeitet am System-Flash so, wie es das Update-Manifest beschreibt:

1. Enthält das Paket ein Abbild des **Radio-Stacks**, wird seine Version mit der installierten verglichen.
   Unterscheiden sie sich, wird der alte Stack deinstalliert und der neue geschrieben und installiert. Die
   Installation übernimmt STs proprietäres **FUS**, das auf Core2 läuft, und umfasst mehrere Neustarts.
2. Die **Option Bytes** (die Low-Level-Konfiguration des Mikrocontrollers) werden geprüft und korrigiert.
3. Die `.dfu`-Datei der Firmware wird geladen, ihre Integrität mit CRC32 geprüft, in den Flash geschrieben und
   verifiziert.

### 3. Den internen Speicher wiederherstellen und Ressourcen aktualisieren

Das System startet in die neue Firmware neu, stellt den gesicherten Inhalt von `/int` wieder her und entpackt —
sofern das Paket ein Ressourcenarchiv enthält — dieses auf die SD-Karte.

## Update-Manifest

Jedes Paket bringt ein Manifest mit (die `.fuf`-Datei) im Flipper File Format — eine einfache Textdatei mit
Schlüssel-Wert-Paaren.

### Zwingende Felder (in dieser Reihenfolge)

| Schlüssel | Bedeutung |
|---|---|
| `Filetype` | Die konstante Zeichenkette `Flipper firmware upgrade configuration` |
| `Version` | Version des Manifests, derzeit `2` |
| `Info` | Freie Beschreibung des Pakets |
| `Target` | Hardwarerevision, für die das Paket gebaut ist |
| `Loader` | Dateiname des Stage-2-Loaders, der aus dem RAM ausgeführt wird |
| `Loader CRC` | CRC32 der Loader-Datei, als **Little-Endian**-Hex |

### Optionale Felder

Diese dürfen leer sein — der Updater überspringt dann die zugehörigen Operationen.

| Schlüssel | Bedeutung |
|---|---|
| `Radio` | Dateiname des Radio-Stack-Abbilds (von ST bereitgestellt) |
| `Radio address` | Adresse, an der der Radio-Stack installiert wird (aus den ST-Release-Notes) |
| `Radio version` | Major-, Minor- und Sub-Version, Branch, Release und Stack-Typ, in 6 Hex-Bytes gepackt |
| `Radio CRC` | CRC32 des Radio-Abbilds |
| `Resources` | Dateiname des Archivs mit den SD-Karten-Ressourcen — `resources.ths`, ein mit Heatshrink komprimierter Tarball (siehe [Heatshrink-Tarball-Format](/de/dev/tar-heatshrink)) |
| `OB reference`, `OB mask`, `OB write mask` | Referenzwerte zum Prüfen und Korrigieren der Option Bytes |

## Fehlercodes

Der Prozess ist so ausfallsicher wie möglich gestaltet: keine riskante Operation beginnt, bevor alle zugehörigen
Daten geprüft sind, sodass das Gerät nicht halb aktualisiert oder unbrauchbar zurückbleibt. Geht etwas schief, lässt
der Updater dich erneut versuchen und zeigt einen Fehlercode `[XX-YY]`: `XX` ist die fehlgeschlagene Operation,
`YY` der Fortschritt oder das Detail, bei dem sie scheiterte.

| Phase | XX | YY | Bedeutung |
|---|--:|---|---|
| Update-Manifest laden | **1** | **13** | Der Updater meldete eine abweichende Hardwareversion |
| | | **20** | Der Pfad des gespeicherten Manifests konnte nicht ermittelt werden |
| | | **30** | Das Manifest konnte nicht geladen werden |
| | | **40** | Nicht unterstützte Version des Update-Pakets |
| | | **50** | Das Paket hat ein abweichendes HW-Target |
| | | **60** | DFU-Datei fehlt |
| | | **80** | Datei der Funk-Firmware fehlt |
| Konfiguration sichern | **2** | **0-100** | Lese-/Schreibfehler im Dateisystem |
| Funk-Firmware prüfen | **3** | **0-99** | Fehler beim Lesen der Funk-Firmware-Datei |
| | | **100** | CRC-Abweichung |
| Funk-Firmware deinstallieren | **4** | **0** | Fehler im SHCI-Delete-Befehl |
| | | **80** | Fehler beim Warten auf den Befehlsstatus |
| Funk-Firmware schreiben | **5** | **0-100** | Lese-/Schreibfehler eines Blocks |
| Funk-Firmware installieren | **6** | **10** | Fehler im SHCI-Install-Befehl |
| | | **80** | Fehler beim Warten auf den Befehlsstatus |
| Core2 ist beschäftigt | **7** | **10** | C2 konnte nicht gestartet werden |
| | | **20** | C2 konnte nicht in den FUS-Modus geschaltet werden |
| | | **30** | Fehler in einer FUS-Operation |
| | | **50** | C2 konnte nicht in den Stack-Modus geschaltet werden |
| Option Bytes prüfen | **8** | **yy** | Option-Byte-Code |
| DFU-Datei prüfen | **9** | **0** | Fehler beim Öffnen der DFU-Datei |
| | | **1-98** | Fehler beim Lesen der DFU-Datei |
| | | **99-100** | Beschädigte DFU-Datei |
| Flash schreiben | **10** | **0-100** | Lese-/Schreibfehler eines Blocks |
| Flash prüfen | **11** | **0-100** | Lese-/Schreibfehler eines Blocks |
| Konfiguration wiederherstellen | **12** | **0-100** | Lese-/Schreibfehler im Dateisystem |
| Ressourcen aktualisieren | **13-15** | **0-100** | Lese-/Schreibfehler der SD-Karte |

::: tip Was bei einem Fehler zu tun ist
- **1-50 / 1-13** — das Paket ist für ein anderes Hardware-Target: lade das richtige herunter.
- **2, 12, 13-15** — Problem mit der SD-Karte: prüfe oder formatiere die Karte und kopiere das Paket erneut.
- **3-100, 9-99/100** — beschädigte Dateien: lade das Paket erneut herunter.
- Versuche es zuerst noch einmal — der Updater ist dafür gemacht. Wenn der Flipper überhaupt nicht mehr startet,
  nutze die [Wiederherstellung](/de/start/recovery).
:::

## Update-Pakete bauen

Übergib unbedingt `DEBUG=0` — siehe [Die Firmware bauen](/de/dev/build).

**Vollständiges Paket** — Firmware, Radio-Stack und SD-Karten-Ressourcen:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

**Minimales Paket** — nur die Firmware:

```sh
./fbt COMPACT=1 DEBUG=0 updater_minpackage
```

Das Ergebnis liegt in `dist/<target>-<cfg>/` als Ordner `f7-update-<suffix>` und als
`flipper-z-f7-update-<suffix>.tgz`.

### Einen anderen Radio-Stack wählen

Pakete verwenden standardmäßig den Stack **Bluetooth Light**. Wenn deine Firmware einen anderen Stack unterstützt,
übergib dessen Typ und Binärdatei:

```sh
./fbt updater_package COMPACT=1 DEBUG=0 COPRO_OB_DATA=scripts/ob_custradio.data COPRO_STACK_BIN=stm32wb5x_BLE_Stack_full_fw.bin COPRO_STACK_TYPE=ble_full
```

`COPRO_OB_DATA` muss auf eine Datei in `scripts/` mit den Referenz-Option-Byte-Daten für diesen Stack-Typ zeigen. In
manchen Fällen musst du zusätzlich mit `COPRO_DISCLAIMER=...` auf der Kommandozeile bestätigen.

### Teilpakete

Rufe für eigene Inhalte `scripts/update.py` direkt auf. Zum Beispiel ein Paket, das nur den BLE-FULL-Stack
installiert:

```shell
scripts/update.py generate \
  -t f7 -d r13.3_full -v "BLE FULL 13.3" \
  --stage dist/f7/flipper-z-f7-updater-*.bin \
  --radio lib/stm32wb_copro/firmware/stm32wb5x_BLE_Stack_full_fw.bin \
  --radiotype ble_full
```

Alle Optionen zeigt `scripts/update.py generate --help`.

## Ein Paket über die CLI installieren

Kopiere den entpackten Paketordner auf die SD-Karte und führe aus:

```
update install /ext/update/f7-update-local/update.fuf
```

Die [CLI](/de/dev/cli#update) bietet außerdem `update backup` und `update restore` für den internen Speicher.

## Verwandte Seiten

- [Die Firmware aktualisieren](/de/start/updating)
- [Wiederherstellung](/de/start/recovery)
- [Heatshrink-Tarball-Format](/de/dev/tar-heatshrink)
- [Flipper Build Tool (fbt)](/de/dev/fbt)
