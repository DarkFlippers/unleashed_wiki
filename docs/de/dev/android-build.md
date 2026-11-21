---
title: Apps unter Android bauen
order: 15
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md, https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX]
sources: [unleashed-docs, unleashed-readme]
---
# Apps unter Android bauen (Termux + uFBT)

Richte `ufbt` in [Termux](https://termux.dev/) auf einem gewöhnlichen, nicht gerooteten Android-Smartphone ein und
kompiliere Flipper-Zero-Apps (`.fap`) direkt auf dem Telefon — kein PC, kein proot, keine virtuelle Maschine.

::: info Danksagung
Von [@CamsShaft](https://github.com/CamsShaft) mit viel Ausprobieren auf einem Samsung Galaxy S22 (SM-S901W,
aarch64) erarbeitet. Ursprüngliche Anleitung (MIT):
[BUILD-FLIPPER-FAPS-IN-TERMUX](https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX). Sie ist Teil der
Unleashed-Dokumentation.
:::

**Umfang:** damit werden **Apps** gebaut, nicht die Firmware. Für die Firmware selbst siehe
[Die Firmware bauen](/de/dev/build).

Die Pfade unten setzen ein **aarch64**-Gerät und das Standard-Termux-Präfix voraus
(`$PREFIX` = `/data/data/com.termux/files/usr`). Bei deinem Gerät kann das abweichen — die typischen Fehlschläge
behandelt der Abschnitt [Fehlerbehebung](#troubleshooting).

## Warum zusätzliche Arbeit nötig ist

uFBT lädt eine vorgebaute `arm-none-eabi-gcc`-Cross-Toolchain herunter, die für gewöhnliches Linux mit **glibc**
gebaut ist. Termux läuft auf Androids **Bionic**-libc mit einem nicht standardkonformen Dateisystem-Layout, und
jede ELF-Binärdatei der Toolchain verlangt `/lib/ld-linux-aarch64.so.1` als dynamischen Linker — den es unter
Android nicht gibt.

Die Lösung: die glibc-Kompatibilitätsschicht von Termux installieren und dann jede Toolchain-Binärdatei über ein
kleines Wrapper-Skript durch den Linker von glibc laufen lassen.

::: danger Führe `patchelf` nicht auf den Toolchain-Binärdateien aus
Es beschädigt deren ELF-Segment-Layout, und du bekommst Segfaults aus `cc1`. Die Wrapper unten lassen die
Binärdateien Byte für Byte unverändert.
:::

## Voraussetzungen

- Ein aarch64-Android-Gerät.
- [Termux](https://f-droid.org/en/packages/com.termux/), installiert **von F-Droid** — der Google-Play-Build ist
  veraltet und funktioniert nicht.
- Internet und einige GB frei für Toolchain, SDK und glibc.

## 1. Basis-Pakete

```sh
pkg update && pkg upgrade -y
pkg install python python-pip git file -y
```

`file` ist **nicht** optional — die Wrapper-Schleife in Schritt 6 nutzt es, um ELF-Binärdateien von allem anderen
zu unterscheiden.

## 2. glibc-Kompatibilitätsschicht

```sh
pkg install glibc-repo -y
pkg install glibc-runner -y
```

Das müssen **zwei getrennte Befehle** sein: `glibc-repo` fügt das Repository hinzu, aus dem `glibc-runner` kommt.
Gemeinsam installieren sie eine vollständige glibc unter `$PREFIX/glibc/`, einschließlich des dynamischen Linkers.
Prüfe es:

```sh
ls $PREFIX/glibc/lib/ld-linux-aarch64.so.1
```

::: warning
**Setze `LD_PRELOAD` niemals global auf die `libc.so.6` von glibc.** Das bricht auf nicht offensichtliche Weise die
eigenen Bionic-Binärdateien von Termux, Python eingeschlossen. Die Wrapper aus Schritt 6 machen es unnötig.
:::

## 3. uFBT und die Python-Build-Abhängigkeiten installieren

```sh
pip install ufbt colorlog heatshrink2 pyelftools scons pillow
```

| Paket | Wofür es nötig ist |
|---|---|
| `colorlog` | Logging der Build-Skripte |
| `heatshrink2` | Komprimierung von Icons und Assets |
| `pyelftools` | Der Nachbearbeitungsschritt `FASTFAP` |
| `scons` | Das Build-System — muss eigenständig installiert sein; die mitgelieferte Kopie der Toolchain ist hier unbrauchbar |
| `pillow` | Icon-Konvertierung; ohne es ist der einzige Fehler ein nacktes `convert: No such file or directory` |

Wenn sich das `pillow`-Wheel nicht bauen lässt, nimm das Termux-Paket: `pkg install python-pillow`.

## 4. uFBT auf das Unleashed-SDK ausrichten {#_4-point-ufbt-at-the-unleashed-sdk}

**uFBT verwendet standardmäßig das SDK der offiziellen Firmware.** Um gegen Unleashed zu bauen, übergib den
Unleashed-Update-Index:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Kanäle: `dev` und `release`. **Jedes spätere `ufbt update` braucht dieselben Flags**, sonst fällst du unbemerkt auf
das offizielle SDK zurück und baust gegen die falsche API.

Wenn `~/.ufbt/toolchain/` noch leer ist, richtet jeder uFBT-Aufruf die Toolchain ein:

```sh
ufbt -h
```

Ein Fehler, der hier `python3` erwähnt, ist zu erwarten — Schritt 5 behebt ihn. Prüfe, ob die Toolchain angekommen
ist:

```sh
ls ~/.ufbt/toolchain/aarch64-linux/bin/arm-none-eabi-gcc
ls ~/.ufbt/toolchain/aarch64-linux/arm-none-eabi/bin/as
ls ~/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*/cc1
```

## 5. Das Python der Toolchain umbiegen

Die Toolchain bringt ihr eigenes, gegen glibc gelinktes Python mit, das hier nicht laufen kann. Lass jeden
`python3*`-Eintrag auf das Python von Termux zeigen:

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"

for py in "$TOOLCHAIN"/bin/python3*; do
    [ -e "$py" ] || [ -L "$py" ] || continue
    ln -sf "$PREFIX/bin/python3" "$py"
done
```

## 6. Die Toolchain-Binärdateien einpacken

Alles Weitere hängt von diesem Schritt ab. Jeder Wrapper führt die echte Binärdatei über den dynamischen Linker von
glibc mit einem ausdrücklichen `--library-path` aus, sodass die Binärdatei selbst nie verändert wird.

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"
GLIBC_LIB="$PREFIX/glibc/lib"

wrap() {
    for f in "$@"; do
        [ -f "$f" ] || continue
        case "$f" in *.real | *.so | *.so.*) continue ;; esac
        [ -e "$f.real" ] && continue
        file -b "$f" | grep -q '^ELF' || continue

        mv "$f" "$f.real"
        cat > "$f" <<WRAPPER
#!$PREFIX/bin/bash
exec "$GLIBC_LIB/ld-linux-aarch64.so.1" --library-path "$GLIBC_LIB:$TOOLCHAIN/lib" "$f.real" "\$@"
WRAPPER
        chmod +x "$f"
        echo "wrapped $f"
    done
}

wrap "$TOOLCHAIN"/bin/arm-none-eabi-*
wrap "$TOOLCHAIN"/arm-none-eabi/bin/*
wrap "$TOOLCHAIN"/libexec/gcc/arm-none-eabi/*/*
```

Die drei Globs sind drei getrennte Verzeichnisse mit ELF-Binärdateien. Fehlt eines, gibt es einen jeweils eigenen
Fehler:

| Verzeichnis | Inhalt | Fehler, wenn nicht eingepackt |
|---|---|---|
| `bin/` | `arm-none-eabi-gcc`, `-g++`, … | `cannot execute` / `No such file or directory` |
| `arm-none-eabi/bin/` | `as`, `ld`, `ar`, `objcopy`, … | `cannot execute as` |
| `libexec/gcc/arm-none-eabi/<gcc-version>/` | `cc1`, `cc1plus`, `collect2`, `lto1` | `cannot execute cc1` |

Warum die Absicherungen wichtig sind (besonders beim erneuten Durchlauf):

- `*.so` wird übersprungen, weil `liblto_plugin.so` in `libexec/` eine Shared Library und keine ausführbare Datei
  ist — sie einzupacken ergibt `invalid ELF header`.
- `*.real` und die Prüfung auf `$f.real` machen die Funktion idempotent: ein erneuter Durchlauf nach einem
  Toolchain-Update kann keinen Wrapper einpacken.
- In `bin/` wird absichtlich nur `arm-none-eabi-*` eingepackt: `bin/python3` zeigt jetzt auf das Bionic-Python von
  Termux und darf **nicht** durch den Linker von glibc laufen.

::: warning
`ufbt update` kann die gesamte Toolchain ersetzen — **führe die Schritte 5 und 6 nach jedem Update erneut aus.**
:::

## 7. Bauen

```sh
git clone https://github.com/<owner>/<some-flipper-app>.git
cd <some-flipper-app>
ufbt
```

Ein erfolgreicher Build endet so:

```
scons: Entering directory '...'
        CC      ...
        LINK    ...
        FAP     ...
        FASTFAP ...
        APPCHK  dist/some_app.fap
                Target: 7, API: 88.2
```

Die `.fap` liegt in `dist/`. Vergleiche die gemeldete API mit der Firmware deines Flipper — stimmen sie nicht
überein, verweigert die App das Laden.

## 8. Die .fap auf den Flipper bringen

`ufbt launch` und `ufbt flash_usb` brauchen eine serielle Verbindung (`/dev/ttyACM*`). **Auf einem unveränderten,
nicht gerooteten Android funktioniert das nicht** — Android stellt Termux keine USB-CDC-ACM-Gerätedateien bereit.
Nur ein gerootetes Gerät mit funktionierendem CDC-ACM-Treiber kann diese Befehle nutzen.

Kopiere die Datei stattdessen heraus. FAPs liegen auf der microSD-Karte in `/ext/apps/<Category>/`:

```sh
termux-setup-storage                        # one-time: grants Termux access to shared storage
cp dist/some_app.fap ~/storage/downloads/
```

Aus `Downloads` ist die Datei für andere Apps sichtbar, bringe sie also auf dem üblichen Weg auf den Flipper — mit
der Flipper-Mobil-App oder einem USB-C-microSD-Kartenleser.

## Fehlerbehebung {#troubleshooting}

### `cannot execute cc1` / `cannot execute as`

Eines der drei Verzeichnisse aus Schritt 6 wurde nicht eingepackt. Führe die `wrap`-Aufrufe erneut aus — sie können
ohne Risiko wiederholt werden.

### `liblto_plugin.so: invalid ELF header`

Eine Shared Library wurde eingepackt. Stelle sie wieder her:

```sh
LIBEXEC="$(echo "$HOME"/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*)"
mv "$LIBEXEC/liblto_plugin.so.real" "$LIBEXEC/liblto_plugin.so"
```

### `Segmentation fault` aus cc1

Die Binärdatei wurde beschädigt, fast immer durch `patchelf`. Lade die Toolchain neu herunter:

```sh
rm -rf ~/.ufbt/toolchain
ufbt -h
```

Wiederhole dann die Schritte 5 und 6. **Verwende `patchelf` nie auf diesen Binärdateien.**

### `No module named 'colorlog'` / `'heatshrink2'` / `'elftools'`

```sh
pip install colorlog heatshrink2 pyelftools
```

### `convert: No such file or directory`

`pillow` fehlt: `pip install pillow` oder `pkg install python-pillow`.

### `python3: No such file or directory`

Der Python-Symlink der Toolchain ist defekt oder wurde von einem Update wiederhergestellt. Führe Schritt 5 erneut
aus.

### `CANNOT LINK EXECUTABLE "python3": library "ld-linux-aarch64.so.1" not found`

`LD_PRELOAD` zeigt auf die `libc.so.6` von glibc, was die Bionic-Binärdateien von Termux bricht. Lösche es:

```sh
unset LD_PRELOAD
unset -f ufbt          # in case a shell function is shadowing ufbt
```

Prüfe danach die Startdateien deiner Shell auf Überreste:

```sh
grep -r "glibc\|LD_PRELOAD" ~/.bashrc ~/.profile ~/.bash_profile ~/.zshrc 2>/dev/null
```

### `ufbt update` meldet, das SDK sei aktuell, aber die Toolchain fehlt

uFBT verfolgt SDK und Toolchain getrennt. Erzwinge beides:

```sh
rm -rf ~/.ufbt/current ~/.ufbt/toolchain
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
ufbt -h
```

Wiederhole dann die Schritte 5 und 6.

### Die App baut, meldet aber die falsche API-Version

Ein `ufbt update` lief ohne `--index-url`, deshalb ist uFBT zum offiziellen SDK zurückgewechselt. Führe den Befehl
aus [Schritt 4](#_4-point-ufbt-at-the-unleashed-sdk) erneut aus.

### Die Wrapper sind nach einem Update verschwunden

Das ist zu erwarten — `ufbt update` kann das gesamte Toolchain-Verzeichnis ersetzen. Führe die Schritte 5 und 6
erneut aus.

## Was dabei wirklich passiert

Jeder Wrapper führt seine echte Binärdatei über den dynamischen Linker von glibc aus, wobei `--library-path` auf
die Bibliotheken von glibc zeigt. Wenn `arm-none-eabi-gcc` `cc1` ausführt, landet es in einem Shell-Skript, das
über den Linker zur unveränderten `.real`-Binärdatei weiterleitet. Die cross-kompilierte Ausgabe bleibt davon
unberührt — sie richtet sich an Bare-Metal-Cortex-M, nicht an Linux.

```
ufbt (Python, Bionic)
  └─ arm-none-eabi-gcc (wrapper)
       └─ ld-linux-aarch64.so.1 → arm-none-eabi-gcc.real (glibc)
            ├─ cc1 (wrapper)      → ld-linux-aarch64.so.1 → cc1.real
            ├─ as (wrapper)       → ld-linux-aarch64.so.1 → as.real
            └─ collect2 → ld (wrapper) → ld-linux-aarch64.so.1 → ld.real
                 └─ output: some_app.fap (ARM Cortex-M4, for the Flipper Zero)
```

## Verwandte Seiten

- [Deine erste App in C](/de/dev/first-app-c)
- [Die Firmware bauen](/de/dev/build)
- [Apps auf der SD-Karte](/de/apps/sd-card-apps)
- [Flipper-Mobil-App](/de/mobile/mobile-app)
