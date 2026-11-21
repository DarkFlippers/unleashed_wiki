---
title: Die Firmware bauen
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToBuild.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Die Firmware bauen

Baue die Unleashed Firmware aus dem Quellcode, wenn du die Firmware selbst ändern, eigene Apps in den Build
aufnehmen oder den neuesten `dev`-Code vor einem offiziellen Release testen willst.

Wenn du nur eine App (`.fap`) schreiben willst, brauchst du nicht die ganze Firmware — nimm stattdessen
[uFBT](/de/dev/first-app-c) und springe direkt zu
[Apps gegen das Unleashed-SDK bauen](#build-apps-against-the-unleashed-sdk-with-ufbt).

## Was du brauchst

- **Git** — [Download](https://git-scm.com/downloads) für Windows; unter Linux/macOS installiere es mit deinem
  Paketmanager (`brew`, `apt`, …).
- **VS Code** (für die Entwicklung empfohlen, zum reinen Bauen optional).
- Einige GB Festplattenplatz. Mehr nicht: `fbt` lädt beim ersten Start seine eigene ARM-Toolchain herunter und
  rührt deinen System-`PATH` nicht an (siehe [fbt → Umgebung](/de/dev/fbt#environment)).

## 1. Das Repository klonen

Klone immer **mit Submodulen**:

```shell
git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
cd unleashed-firmware
```

Wenn du schon ohne `--recursive` geklont hast, initialisiere die Submodule:

```shell
git submodule update --init --recursive
```

## 2. Unter Linux / macOS bauen

Alles bauen und ein Update-Paket erzeugen, das du von der microSD-Karte installieren kannst:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

Eine einzelne App aus `applications_user/` bauen und auf einem über USB verbundenen Flipper starten:

```sh
./fbt COMPACT=1 DEBUG=0 launch_app APPSRC=applications_user/yourplugin
```

## 3. Unter Windows bauen

Verwende `fbt.cmd` in PowerShell oder `cmd`:

```powershell
./fbt.cmd COMPACT=1 DEBUG=0 updater_package
```

::: warning
Unter Windows musst du je nach Shell möglicherweise `.\fbt.cmd` (Backslash) statt `./fbt.cmd` schreiben.
:::

## 4. Das Ergebnis finden und flashen

Alle Build-Ergebnisse landen in `dist/`. Die zu installierende Datei ist das Update-Bundle:

```
dist/f7-C/flipper-z-f7-update-local.tgz
```

Das Namensmuster ist `flipper-z-{target}-update-{suffix}.tgz`. Das Standard-Suffix ist `local` (gesetzt über
`DIST_SUFFIX` in `fbt_options.py` oder über die Umgebungsvariable `DIST_SUFFIX`).

Möglichkeiten, es zu installieren:

- die `.tgz` in **qFlipper** öffnen (*Install from file*) oder im Unleashed Web Installer;
- oder `fbt` es über USB erledigen lassen: `./fbt COMPACT=1 DEBUG=0 flash_usb_full` (baut, überträgt und
  installiert);
- oder über SWD mit einer Debug-Probe flashen: `./fbt flash` (siehe [fbt-Targets](/de/dev/fbt#high-level-targets)).

::: tip Warum `DEBUG=0`?
Die `fbt_options.py` von Unleashed setzt standardmäßig `COMPACT=1` und **`DEBUG=1`**. Ein Debug-Image ist größer
und passt möglicherweise nicht unter den Radio-Stack in den Flash — das Packen bricht dann mit
`Firmware image overlaps C2 region and is not programmable!` ab. Gib für alles, was du installieren willst,
ausdrücklich `DEBUG=0` an. Beachte, dass `DEBUG=0` auch `furi_assert()` herauskompiliert.
:::

## VS-Code-Integration

`fbt` bringt eine fertige VS-Code-Konfiguration mit:

```sh
./fbt vscode_dist
```

Das kopiert die Konfiguration nach `.vscode/`. Öffne danach das Firmware-Wurzelverzeichnis in VS Code über
**File → Open Folder**, akzeptiere die empfohlenen Erweiterungen und nutze
<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> für Build-Tasks. Mehr dazu unter
[fbt → VS Code](/de/dev/fbt#vs-code-integration).

## Apps mit uFBT gegen das Unleashed-SDK bauen {#build-apps-against-the-unleashed-sdk-with-ufbt}

uFBT (micro-fbt) baut einzelne Apps gegen ein heruntergeladenes SDK statt gegen den vollständigen Quellbaum.
**Standardmäßig lädt es das SDK der offiziellen Firmware herunter.** Um für Unleashed zu bauen, richte es auf den
Unleashed-Update-Index aus:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Die Kanäle sind `dev` und `release`. Verwende dieselben Flags bei **jedem** späteren `ufbt update`, sonst wechselt
uFBT unbemerkt zurück zum offiziellen SDK und die gebaute App meldet die falsche API-Version.

::: tip Unleashed
Unleashed behält die offizielle API bei, deshalb laufen die meisten offiziellen Apps unverändert. Eine App
verweigert das Laden nur, wenn ihre Major-API-Version nicht zur Firmware passt — ein Neubau gegen das passende SDK
behebt das.
:::

## Apps unter Android bauen

Apps (nicht die Firmware) lassen sich auch direkt auf einem Android-Smartphone mit uFBT in Termux bauen — siehe
[Apps unter Android bauen](/de/dev/android-build).

## Fehlerbehebung

| Problem | Lösung |
|---|---|
| Der Build scheitert an fehlenden Dateien / Submodulfehlern | `git submodule update --init --recursive` |
| `Firmware image overlaps C2 region and is not programmable!` | `DEBUG=0` zum Befehl hinzufügen |
| `./fbt` wird unter Windows nicht gefunden | `fbt.cmd` / `.\fbt.cmd` verwenden |
| Eine mit uFBT gebaute App startet nicht: API-Konflikt | `ufbt update` mit der Unleashed-`--index-url` erneut ausführen, neu bauen |
| Du willst einen sauberen Neubau | `-c` ergänzen, um die angegebenen Targets zu reinigen, z. B. `./fbt -c fw_dist` |

## Verwandte Seiten

- [Flipper Build Tool (fbt)](/de/dev/fbt) — alle Targets und Optionen
- [Deine erste App in C](/de/dev/first-app-c)
- [OTA-Updates](/de/dev/ota) — was in einem Update-Paket steckt
- [Hardware-Targets](/de/dev/hardware-targets)
