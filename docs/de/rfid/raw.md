---
title: RAW-Aufnahme
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/LFRFIDRaw.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/lfrfid_debug]
sources: [unleashed-docs, unleashed-src]
---
# RAW-Daten bei 125 kHz lesen

Der RAW-Modus nimmt das Signal des Tags auf, wie es ist — Puls- und Periodendauern — statt es zu dekodieren, ein
bisschen wie ein Diktiergerät. Gedacht ist er für die **Protokollforschung**: Wird dein Tag nicht erkannt, nimm es auf
und schicke die Dateien (samt Foto der Karte) in einem GitHub-Issue an die Entwickler.

## Debug-Modus aktivieren

Die RAW-Einträge sind ausgeblendet, solange Debug aus ist:

1. `Main Menu → Settings → System`.
2. Setze **Debug** auf **ON**.

## Aufnehmen

1. Öffne `Main Menu → 125 kHz RFID → Extra Actions → Read RAW RFID data`.
2. Benenne die Aufnahme (Standard `RfidRecord`).
3. Lies die Anleitung (*RAW RFID Data Reader — 1. Hold card next to Flipper, 2. Press OK, 3. Wait until data is
   read*) und drücke <kbd>OK</kbd>.
4. Halte die Karte an die Rückseite des Flippers. Der Flipper nimmt drei Durchgänge von je **5 Sekunden** auf —
   *Reading ASK*, *ASK 134kHz*, *Reading PSK* — und bittet mit *Don't move for 5 sec.* um Ruhe.
5. **RAW RFID Read Success** — *Now you can analyze files or send them to developers*. Drücke <kbd>OK</kbd>.

In `/ext/lfrfid/` entstehen drei Dateien:

| Datei | Durchgang |
|---|---|
| `<name>.ask.raw` | ASK, Träger 125 kHz |
| `<name>.ask134.raw` | ASK, Träger 134,2 kHz |
| `<name>.psk.raw` | PSK, Träger 125 kHz |

::: tip Unleashed
Die Unleashed-Dokumentation und die Stock-Firmware nennen zwei Dateien (ASK und PSK). Die aktuelle Firmware nimmt
einen dritten Durchgang, **ASK 134kHz**, für Tierchips auf.
:::

Erscheint *RAW Reading error! This may be caused by SD card issues*, prüfe die Karte (freier Platz, Fehler). Ohne
SD-Karte zeigt die App *No SD Card!*.

## Wiedergeben

`Extra Actions → Emulate RAW RFID data` öffnet den Dateibrowser für `.raw`-Dateien und spielt die ausgewählte wieder
ab (*Emulating RAW RFID*). Das ist vor allem zum Debuggen von Protokollen nützlich, nicht als Ersatz für die normale
Emulation.

## CLI

Dasselbe gibt es über die CLI und ist in der Entwicklung praktisch:

```text
rfid raw_read <ask | ask134 | psk> <filename>   - read and save raw data to a file
rfid raw_emulate <filename>                     - emulate raw data
rfid raw_analyze <filename>                     - print the raw data and try to decode it
```

`raw_analyze` gibt jedes Puls-/Dauer-Paar aus, markiert, wo ein Protokoll dekodiert wurde, und schließt mit Frequenz,
Tastverhältnis, Mittelwerten und dem erkannten Protokoll ab (oder `not found`).

## Die App LF-RFID Debug

Der Firmware-Quellcode enthält außerdem ein Entwicklerwerkzeug, **LF-RFID Debug**
(`applications/debug/lfrfid_debug`), dessen Bildschirm **Tune** den Träger-Timer (ARR/CCR — Frequenz und
Tastverhältnis) live verstellt. Es ist eine Debug-App für die Protokollentwicklung und für den normalen Gebrauch
nicht nötig.

## Verwandte Seiten

- [Dateiformate](/de/rfid/file-format) · [Lesen](/de/rfid/read) · [Protokolle](/de/rfid/protocols)
