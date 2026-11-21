---
title: Flipper Build Tool (fbt)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Flipper Build Tool (fbt)

`fbt` ist der einzige Einstiegspunkt zum Bauen, Flashen, Debuggen und Linten der Firmware. Du führst es als
`./fbt` (oder `fbt.cmd` unter Windows) im Wurzelverzeichnis des Repositorys aus. Intern ist es ein Wrapper um das
Build-System [SCons](https://scons.org/).

Wenn du nur **eine App** bauen und debuggen willst, brauchst du nicht den vollständigen Firmware-Baum — nimm
stattdessen [uFBT](https://pypi.org/project/ufbt/) (siehe [Deine erste App in C](/de/dev/first-app-c)).

## Umgebung {#environment}

Das Einzige, was installiert sein muss, ist `git`. Beim ersten Start lädt `fbt` eine vorgebaute Toolchain herunter,
entpackt sie und passt Umgebungsvariablen **nur für sich selbst** an — dein globaler `PATH` wird nicht verändert.

Um die mitgelieferte Toolchain außerhalb von `fbt` zu nutzen (zum Beispiel, um `arm-none-eabi-gdb` manuell
aufzurufen), öffne eine *fbt-Shell*:

- Windows: `scripts/toolchain/fbtenv.cmd` ausführen
- Linux / macOS: `source scripts/toolchain/fbtenv.sh` in einer neuen Shell ausführen
- oder `` . `./fbt -s env` `` in deiner Shell eingeben (den führenden `.` beibehalten)

Umgebungsvariablen, die das Verhalten von `fbt` ändern:

| Variable | Wirkung |
|---|---|
| `FBT_NOENV=1` | Überspringt Download/Einrichtung der Toolchain; alle Werkzeuge müssen bereits im `PATH` liegen (unter Windows nicht verfügbar) |
| `FBT_TOOLCHAIN_PATH=…` | Verzeichnis, in das die Toolchain entpackt wird (Standard: `toolchain/` im Repository-Wurzelverzeichnis) |
| `FBT_VERBOSE=1` | Zusätzliche Debug-Ausgaben von `fbt` und den Toolchain-Skripten |
| `FBT_NO_SYNC=1` | Führt `git submodule update --init` nicht bei jedem Start aus |

Eine Variable für einen einzelnen Lauf setzen:

```sh
# Linux / macOS
FBT_NO_SYNC=1 ./fbt ...
```

```bat
:: Windows (cmd)
set "FBT_NO_SYNC=1"
```

Weitere Variablen sind im Quellcode der Skripte `fbt` und `fbtenv` dokumentiert.

## fbt aufrufen

Übergib Konfigurationsoptionen und die gewünschten Targets:

```sh
./fbt COMPACT=1 DEBUG=0 VERBOSE=1 updater_package copro_dist
```

Um die angegebenen Targets zu reinigen (wie `make clean`), ergänze `-c`.

`fbt` verfolgt Abhängigkeiten, du nennst also nur das höchste Target, das du brauchst — alles, wovon es abhängt,
wird automatisch neu gebaut.

## Build-Verzeichnisse

Firmware und Updater werden in getrennten Unterverzeichnissen von `build/` gebaut, benannt nach den
Optimierungseinstellungen (`COMPACT`, `DEBUG`). Für IDEs ist die zuletzt gebaute Variante immer als `build/latest`
verlinkt, zusammen mit einer `compile_commands.json` für die Code-Vervollständigung.

::: info
`build/latest` und die Compilation Database werden nur von **Firmware-Build-Targets** aktualisiert. Flashen oder
das Bauen von Update-Bundles für eine *andere* Debug-/Release-Konfiguration oder ein anderes Hardware-Target
verschiebt `build/latest` nicht.
:::

## VS-Code-Integration {#vs-code-integration}

```sh
./fbt vscode_dist
```

kopiert eine fertige Umgebungskonfiguration nach `.vscode/`. Öffne das Firmware-Wurzelverzeichnis mit
**File → Open Folder**.

- Um einen anderen Language Server als das standardmäßige `cpptools` zu verwenden, führe
  `./fbt vscode_dist LANG_SERVER=<language-server>` aus. Unterstützt werden `cpptools` (Standard) und `clangd`.
- Beim ersten Start werden dir empfohlene Erweiterungen angeboten (aufgelistet in `.vscode/extensions.json`) —
  installiere sie.
- Die Build-Tasks liegen unter <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
- Debugging braucht eine unterstützte Probe: Wi-Fi Devboard mit der Original-Firmware (Blackmagic), ST-Link und
  Kompatible oder J-Link (nur VS Code; die J-Link-Werkzeuge sind nicht mitgeliefert —
  [herunterladen](https://www.segger.com/downloads/jlink/) und in den `PATH` legen).
- Ohne Probe kannst du die Firmware weiterhin über USB installieren.

## Übergeordnete Targets {#high-level-targets}

Das sind die Targets, die du am häufigsten brauchst.

| Target | Funktion |
|---|---|
| `fw_dist` | Baut die Firmware und veröffentlicht sie in `dist/`. **Standard-Target**, wenn keines angegeben wird |
| `fap_dist` | Baut externe Apps (FAPs) und veröffentlicht sie in `dist/` |
| `updater_package` | Vollständiges Selbstupdate-Paket: Firmware-DFU + Radio-Stack + SD-Karten-Ressourcen |
| `updater_minpackage` | Minimales Update-Paket: nur das Firmware-DFU |
| `copro_dist` | Bündelt die Core2-FUS- und Radio-Stack-Binärdateien für qFlipper |
| `flash` | Flasht über SWD mit einer unterstützten Probe (automatisch erkannt; mit `SWD_TRANSPORT=...` überschreiben, mit `SWD_TRANSPORT_SERIAL=...` eine von mehreren Probes wählen) |
| `flash_usb`, `flash_usb_full` | Baut, überträgt und installiert das Update-Paket über USB (minimales / vollständiges Paket) |
| `debug` | Baut und flasht die Firmware, hängt dann GDB mit geladener Firmware-`.elf` an |
| `debug_other`, `debug_other_blackmagic` | Hängt GDB an, ohne eine `.elf` zu laden; externe `.elf`-Dateien mit `add-symbol-file` ergänzen |
| `updater_debug` | Hängt GDB mit geladener Updater-`.elf` an |
| `devboard_flash` | Aktualisiert das Wi-Fi Devboard; zusätzliche Argumente über `ARGS="..."`, z. B. `ARGS="-c dev"` |
| `blackmagic` | Debuggt die Firmware mit einer Blackmagic-Probe (Wi-Fi Devboard) |
| `openocd` | Startet nur OpenOCD; zusätzliche Argumente über `ARGS="..."` |
| `get_blackmagic` | Gibt die Blackmagic-Adresse im GDB-Remote-Format aus (für die IDE-Integration) |
| `get_stlink` | Gibt die Seriennummern der angeschlossenen ST-Link-Probes aus (für `SWD_TRANSPORT_SERIAL=...`) |
| `lint`, `format` | Prüft / formatiert C-Code mit clang-format (`.clang-format`); zusätzliche Argumente über `ARGS="..."` |
| `lint_py`, `format_py` | Prüft / formatiert Python, Build-Dateien und Manifeste mit [black](https://black.readthedocs.io/en/stable/index.html) |
| `lint_img`, `format_img` | Prüft / korrigiert Bild-Assets (Farbtiefe, Metadaten entfernen) |
| `lint_all`, `format_all` | Führt alle Linter / Formatierer aus |
| `firmware_pvs` | PVS-Studio-Bericht (PVS-Studio muss im `PATH` liegen) |
| `doxygen` | Erzeugt die Doxygen-Dokumentation; `doxy` öffnet sie zusätzlich im Browser |
| `cli` | Öffnet eine Flipper-[CLI](/de/dev/cli)-Sitzung über USB |

## Firmware-Targets

| Target | Funktion |
|---|---|
| `faps` | Baut alle externen Apps und Plugin-Apps als `.fap` |
| `fap_<appid>` | Baut eine App anhand ihrer App-ID als `.fap`, z. B. `fap_snake_game` |
| `fap_<appid>_list` | Erzeugt Quellcode- und Assembler-Listings für die `.fap` dieser App |
| `flash`, `firmware_flash` | Flasht den aktuellen Build über SWD |
| `jflash` | Flasht mit JFlash über eine J-Link-Probe (JFlash muss im `PATH` liegen) |
| `firmware_all`, `updater_all` | Baut einen Grundsatz von Binärdateien |
| `firmware_list`, `updater_list` | Erzeugt Quellcode- und Assembler-Listings |
| `firmware_cdb`, `updater_cdb` | Erzeugt `compilation_database.json` für IDEs — funktioniert ohne vollständigen Build |

Verwende `--extra-ext-apps` (siehe unten), um zusätzliche Apps in den externen Build zu zwingen.

## Asset-Targets

| Target | Funktion |
|---|---|
| `resources` | Baut die SD-Karten-Ressourcen und deren Manifestdateien |
| `dolphin_ext` | Verarbeitet die Dolphin-Animationen für die SD-Karte |
| `icons` | Erzeugt `.c` + `.h` für Icons aus PNG-Assets |
| `proto` | Erzeugt `.pb.c` + `.pb.h` aus `.proto`-Quellen |
| `proto_ver` | Erzeugt eine `.h` mit der Protobuf-Version |
| `dolphin_internal`, `dolphin_blocking` | Erzeugt `.c` + `.h` für die jeweiligen Dolphin-Assets |

## Kommandozeilenparameter

| Parameter | Bedeutung |
|---|---|
| `--options optionfile.py` | Lädt eine Datei mit Konfigurationswerten (Standard `fbt_options.py`) |
| `--extra-int-apps=app1,app2,appN` | Erzwingt, dass die genannten Apps **in** die Firmware gebaut werden (Target `firmware`) |
| `--extra-ext-apps=app1,app2,appN` | Erzwingt, dass die genannten Apps als **extern** gebaut werden (Target `firmware_extapps`) |
| `--extra-define=A --extra-define=B=C` | Zusätzliche globale C/C++-Defines; kann wiederholt werden |
| `--proxy-env=VAR1,VAR2` | Zusätzliche Umgebungsvariablen, die an Unterprozesse übergeben werden. Standardmäßig bereinigt `fbt` die Umgebung; die immer weitergegebene Liste steht in `environ.scons` |

## Konfiguration

Die Standardwerte stehen in `fbt_options.py`. Werte auf der Kommandozeile haben Vorrang. Für **dauerhafte
persönliche Anpassungen** erstelle daneben eine `fbt_options_local.py` — sie wird beim Laden der Standardoptionen
ausgewertet, du musst also nie die versionierte Datei bearbeiten. `./fbt -h` listet alle Optionen auf.

Bemerkenswerte Unleashed-Standardwerte aus `fbt_options.py`:

| Option | Standard | Hinweise |
|---|---|---|
| `FIRMWARE_ORIGIN` | `"Unleashed"` | Wird in den Geräteinformationen gemeldet |
| `TARGET_HW` | `7` | Flipper Zero (f7); siehe [Hardware-Targets](/de/dev/hardware-targets) |
| `COMPACT` | `1` | Auf Größe optimieren |
| `DEBUG` | `1` | Für installierbare Builds `DEBUG=0` übergeben |
| `DIST_SUFFIX` | `"local"` | Suffix in den Namen der Ausgabedateien |
| `COPRO_STACK_TYPE` | `"ble_light"` | `ble_full` wird unterstützt, passt aber möglicherweise nicht in Debug-Builds |
| `FIRMWARE_APP_SET` | `"default"` | Siehe unten |

### Firmware-App-Sets {#firmware-app-sets}

Welche Apps in die Firmware wandern, steuert `FIRMWARE_APPS` — eine Abbildung von *Konfigurationsname → Tupel von
App-IDs*. Mit `FIRMWARE_APP_SET` wählst du eine davon. Unleashed definiert zwei Sets:

```python
FIRMWARE_APPS = {
    "default": [
        # Svc
        "basic_services",
        # Apps
        "main_apps",
        "system_apps",
        # Settings
        "settings_apps",
    ],
    "unit_tests": [
        "basic_services",
        "updater_app",
        "radio_device_cc1101_ext",
        "unit_tests",
        "infrared",
        "archive",
    ],
}
```

Um zum Beispiel ein Image mit Unit-Tests zu bauen:

```sh
./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests
```

Siehe [Unit-Tests](/de/dev/unit-tests), warum dieser Build `DEBUG=0` braucht.

## Verwandte Seiten

- [Die Firmware bauen](/de/dev/build)
- [App-Manifeste (.fam)](/de/dev/app-manifests)
- [Apps debuggen](/de/dev/debugging)
- [OTA-Updates](/de/dev/ota)
