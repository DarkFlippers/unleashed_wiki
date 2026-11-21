---
title: Read RAW (Rohsignal aufnehmen)
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/sub-ghz/read-raw]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Read RAW

**Read RAW** nimmt das demodulierte Signal „so wie es ist" auf, ohne es zu dekodieren — wie ein Diktiergerät. Die
Aufnahme lässt sich abspielen, speichern, später dekodieren oder bearbeiten. Nutze sie, wenn:

- **Read** die Fernbedienung nicht erkennt (unbekanntes Protokoll);
- du ein Signal zur Analyse mitschneiden oder den Entwicklern ein neues Protokoll melden willst;
- du ein exaktes Wiederabspielen eines statischen Signals brauchst, dessen Protokoll der Flipper nicht kennt.

Die Aufnahme erfolgt trotzdem mit der gewählten **Frequenz und Modulation** — der Flipper ist kein SDR. Eine falsche
Modulation liefert dir eine Aufnahme von Rauschen.

::: warning Rolling Codes
Das RAW-Wiederabspielen einer Rolling-Code-Fernbedienung ist genau wie ein Klon: Es treibt den Empfängerzähler
voran und kann dein Original desynchronisieren. **Mach das niemals mit einem Autoschlüssel** — der Schlüssel kann
dadurch gesperrt werden. Details: [Rolling Codes](/de/subghz/rolling-codes).
:::

## Aufnehmen

1. Finde die Frequenz mit dem [Frequency Analyzer](/de/subghz/frequency-analyzer), falls du sie nicht kennst.
2. Öffne `Main Menu → Sub-GHz → Read RAW`.
3. Drücke <kbd>←</kbd> **Config** und setze `Frequency`, `Modulation` und `RSSI Threshold:` (siehe unten).
   Mit <kbd>Back</kbd> geht es zurück.

   ![Read RAW bereit zur Aufnahme: leere Kurve, Schaltflächen Config und REC](/screens/subghz/read_raw.png)

4. Drücke <kbd>OK</kbd> **REC**. Die Kurve beginnt zu laufen, rechts steht der RSSI.
5. Drücke die Taste auf der Fernbedienung (1–2 s halten).

   ![Read RAW nimmt auf: zwei Signalbursts in der Kurve, Sample-Zähler und Schaltfläche Stop](/screens/subghz/read_raw_recording.png)

6. Drücke <kbd>OK</kbd> **Stop**.
7. Jetzt hast du drei Möglichkeiten:
   - <kbd>←</kbd> **Erase** — verwerfen und neu anfangen;
   - <kbd>OK</kbd> **Send** — die Aufnahme abspielen (halten, um sie zu wiederholen);
   - <kbd>→</kbd> **Save** — einen Namen eingeben (Standard `RAW_<Datum-Uhrzeit>`) und in `/ext/subghz/` speichern.

## Config in Read RAW

Das RAW-Konfigurationsmenü ist kürzer als in Read:

| Punkt | Werte | Bedeutung |
|---|---|---|
| `Frequency` | Frequenzliste | Empfangsfrequenz |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + eigene | Demodulations-Preset |
| `Sound` | `OFF` / `ON` | Das empfangene Signal über den Lautsprecher ausgeben |
| `RSSI Threshold:` | `-----`, `-85.0` … `-40.0` | Nimmt nur auf, solange das Signal über diesem Pegel liegt. `-----` = alles aufnehmen |

::: tip Wann die Schwelle sinnvoll ist
Mit einer Schwelle enthält die Datei nur die Bursts deiner Fernbedienung und nicht sekundenlanges Rauschen zwischen
den Tastendrücken — die Dateien sind viel kleiner und sauberer. Für Aufnahmen, die du an Entwickler schickst, lasse
sie auf `-----` (vollständige Aufnahme).
:::

## Eine gespeicherte RAW-Aufnahme abspielen {#playback}

1. `Main Menu → Sub-GHz → Saved` und die RAW-Datei auswählen. Sie öffnet sich im Read-RAW-Bildschirm.
2. <kbd>OK</kbd> **Send** — sendet die gesamte Aufnahme einmal; <kbd>OK</kbd> gehalten lassen wiederholt sie
   (**Hold to repeat**).
3. <kbd>←</kbd> **New** — eine neue Aufnahme starten.
4. <kbd>→</kbd> **More**:
   - `Decode` — die Aufnahme durch alle Dekoder der Sub-GHz-App laufen lassen; gefundene Signale lassen sich als
     normale Schlüsseldateien speichern;
   - `Edit` — die Datei in der App [Sub-GHz RAW Edit](/de/subghz/raw-editor) öffnen (nur sichtbar, wenn diese App in
     einer passenden Version installiert ist); Sub-GHz öffnet sich wieder, wenn du den Editor verlässt;
   - `Rename`, `Delete`.

::: tip Unleashed
`More → Decode` und `More → Edit` sind Ergänzungen von Unleashed. Mit `Edit` findest du das echte Signal in einer
verrauschten Aufnahme, kürzt es, fügst Dateien zusammen und dekodierst nur einen Ausschnitt.
:::

Lange, dichte RAW-Dateien werden beim Senden von der SD-Karte gestreamt. Sind sehr kurze Impulse (unter 10 µs) im
Spiel und die Karte ist langsam, kann das Senden vor dem Ende der Datei abbrechen — nimm eine gute Karte.

## Eine Fernbedienung für eine Protokollanfrage aufnehmen

So gehen die Unleashed-Entwickler vor, wenn du Unterstützung für ein neues Protokoll möchtest:

1. Finde die Frequenz mit dem Analyzer. Probiere in Read `AM650`, `FM238`, `FM476`, `FM12K` — wenn nichts
   dekodiert wird, mach weiter.
2. Setze in Read RAW diese Frequenz und **`RSSI Threshold: -----`**.
3. Mache **eine RAW-Aufnahme pro Modulation**: `AM650`, `FM238`, `FM476`, `FM12K`.
4. Für jede: **REC** drücken, dann eine Taste der Fernbedienung **5-mal für 1–2 s gehalten** drücken, dann
   **5-mal für etwa 5 s gehalten**. Stoppen und speichern.
5. Hat die Fernbedienung mehrere Tasten, nimm jede Taste genauso auf. Benenne jede Datei nach der Taste.
6. Kopiere die Dateien auf einen PC, packe sie in ein ZIP und eröffne ein Issue im Firmware-Repository. Füge gute
   Fotos der Fernbedienung hinzu (wenn möglich auch von innen), dazu Modell und Hersteller.

## Fehlersuche

- **Die Aufnahme ist flach / nur Rauschen** — falsche Frequenz oder Modulation, oder die Fernbedienung ist zu weit
  weg. Halte sie nah dran.
- **Riesige Dateien** — setze einen `RSSI Threshold`.
- **Das Wiederabspielen funktioniert nicht** — die Fernbedienung nutzt einen Rolling Code (der Empfänger weist alte
  Zählerwerte ab), die Modulation war falsch, oder die Aufnahme enthält nur einen Teil des Signals. Nimm längere
  Tastendrücke auf.
- **Das Senden bricht mitten drin ab** — langsame SD-Karte bei einer langen, dichten Datei. Kürze die Datei mit
  [RAW Edit](/de/subghz/raw-editor) oder nimm eine schnellere Karte.
- **`Edit` fehlt in `More`** — die App Sub-GHz RAW Edit ist nicht installiert oder zu alt.

## Verwandte Seiten

- [Read](/de/subghz/read) · [Sub-GHz RAW Edit](/de/subghz/raw-editor) · [Remote Analyzer](/de/subghz/remote-analyzer)
- [Dateiformate (RAW, BinRAW)](/de/subghz/file-format) · [Rolling Codes](/de/subghz/rolling-codes)
