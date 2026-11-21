---
title: Tags lesen
order: 10
original: [https://docs.flipper.net/zero/rfid/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-src, flipper-docs]
---
# 125-kHz-Tags lesen, speichern und emulieren

Ein 125-kHz-Tag ist ein Transponder, der im Feld eines Lesegeräts mit Energie versorgt wird und eine feste ID sendet.
Nutzt das Tag eines der [unterstützten Protokolle](/de/rfid/protocols), dekodiert Flipper Zero die ID, zeigt sie an
und kann sie auf die SD-Karte speichern, gegenüber einem Lesegerät emulieren oder
[auf einen Rohling schreiben](/de/rfid/write).

**Nimm das**, wenn du eine Kopie deiner eigenen Zutrittskarte bzw. deines Anhängers auf dem Flipper haben willst,
herausfinden möchtest, was für ein Tag du vor dir hast, oder die ID für ein Zutrittssystem brauchst, das du
verwaltest.

::: tip SD-Karte einlegen
Gespeicherte Schlüssel, Wörterbücher und Einstellungen liegen auf der microSD-Karte (`/ext/lfrfid/`). Installiere die
Firmware mit eingelegter SD-Karte, damit die Ressourcen der App vorhanden sind.
:::

## Ein Tag lesen

1. Öffne `Main Menu → 125 kHz RFID → Read`.
2. Halte das Tag an die **Rückseite** des Flippers, etwa in die Mitte, und halte es still. Auf dem Display steht
   *Don't move card*.
3. Der Flipper durchläuft drei Lesedurchgänge von je rund 2 Sekunden und zeigt den aktiven als **Reading 1/3 … 3/3**:
   **ASK** (125 kHz), **PSK** (125 kHz) und **134kHz** (ASK bei 134,2 kHz, für Tierchips).

   ![Reading 1/3 mit aktivem ASK-Durchgang, darunter PSK und 134 kHz, unten „Don't move card"](/screens/lfrfid/read.png)

4. Achte auf die LED: Sie blinkt beim Lesen **cyan**, wechselt zu **gelb**, wenn sie etwas hört, und zu **grün**,
   sobald die Frames eines Tags dekodiert werden — praktisch, um die beste Position zu finden.
5. Ist ein Tag dekodiert, piept der Flipper und zeigt den Ergebnisbildschirm:
   - Kopfzeile: Hersteller und Protokoll, z. B. **EM-Micro EM4100**;
   - `Hex:` — die rohen Schlüsseldaten (die ersten 7 Byte, längere Schlüssel enden mit `...`);
   - dekodierte Felder (Facility Code, Kartennummer usw. — siehe [Protokolle](/de/rfid/protocols)).

   ![Leseergebnis: EM-Micro EM4100 mit Hex-Daten, Facility Code, Kartennummer, DEZ 8 und DEZ 10, unten Retry und More](/screens/lfrfid/read_success.png)

6. Tasten: <kbd>←</kbd> **Retry** (fragt *Retry Reading? All unsaved data will be lost*), <kbd>→</kbd> **More**,
   <kbd>Back</kbd> fragt, ob du den noch nicht gespeicherten Lesevorgang verwerfen willst.

::: tip Unleashed
Die Stock-Dokumentation beschreibt nur das Umschalten zwischen ASK und PSK. Unleashed ergänzt den dritten Durchgang
bei **134 kHz** (FDX-A-/FDX-B-Tags sind auf 134,2 kHz abgestimmt, schwache antworten nur dort) und zeigt bei EM4100
außerdem **DEZ 8** und **DEZ 10** — die Dezimalformen, die auf vielen Anhängern aufgedruckt sind. Ein EM4100, der
sich als Casi-Rusco-C10106-Badge dekodieren lässt, erhält eine zusätzliche Zeile `or C10106: …`, und ein Generic
HIDProx-Schlüssel wird gegen bekannte HID-Formate geprüft (H10304, H10302, S10401, H10306, Corp1000-35), deren
FC/Kartennummer dann angezeigt wird.
:::

## Nach dem Lesen: More

<kbd>→</kbd> **More** öffnet:

| Eintrag | Aktion |
|---|---|
| **Save** | Namen eingeben (Standardpräfix `RFID`), gespeichert als `/ext/lfrfid/<name>.rfid` |
| **Emulate** | Den Schlüssel sofort emulieren, ohne zu speichern |
| **Write** | Den Schlüssel auf einen Rohling schreiben — siehe [Schreiben](/de/rfid/write) |

## Mit fester Modulation lesen

Manche Tags brauchen länger als einen Durchgang von 2 Sekunden oder lassen sich nur mit einem bestimmten Demodulator
zuverlässig finden. `Main Menu → 125 kHz RFID → Extra Actions` bietet:

| Eintrag | Liest |
|---|---|
| **Read ASK (Regular)** | nur ASK bei 125 kHz, bis ein Tag gefunden ist: EM4100, HID, AWID, Viking, Paradox… |
| **Read PSK (Indala)** | nur PSK: Indala, Keri, Nexwatch, Idteck… |
| **Read FDX-B (Animals)** | nur ASK bei 134,2 kHz — Tierchips, siehe [Tierchips](/de/rfid/animal-microchips) |

Im Debug-Modus hat dasselbe Menü zusätzlich **Read RAW RFID data** und **Emulate RAW RFID data** — siehe
[RAW](/de/rfid/raw).

## Gespeicherte Schlüssel

`Main Menu → 125 kHz RFID → Saved` öffnet den Dateibrowser in `/ext/lfrfid/`. Ein ausgewählter `.rfid`-Schlüssel
öffnet:

![Menü eines gespeicherten Tags mit Emulate, Write, Write and set password und Edit](/screens/lfrfid/saved_menu.png)

| Eintrag | Aktion |
|---|---|
| **Emulate** | Gegenüber einem Lesegerät als dieser Schlüssel auftreten |
| **Write** | Auf einen Rohling schreiben ([Schreiben](/de/rfid/write)) |
| **Write and set password** | Auf einen T5577 schreiben und mit einem Passwort schützen ([Schreiben](/de/rfid/write#write-and-set-password)) |
| **Edit** | Die Schlüsseldaten in Hex ändern; wird unter demselben Namen gespeichert |
| **Rename** | Den Dateinamen ändern |
| **Delete** | Die Datei löschen (mit Rückfrage) |
| **Info** | Name, Protokoll, vollständige Hex-Daten und alle dekodierten Felder |

::: tip Unleashed
Der Browser listet außerdem **`.t5577`**-Block-Dumps (mit dem T5577-Symbol). Wählst du einen aus, startet die
[T5577-App](/de/rfid/t5577-app) mit diesem Dump. Fehlt die App, erscheint *No T5577 app — It comes with the
firmware - install its resources to get it*.
:::

## Emulieren

1. Öffne einen gespeicherten Schlüssel (oder einen frischen Lesevorgang über **More**) und wähle **Emulate**.
2. Der Bildschirm zeigt *Emulating*, `[Protocol]` und den Schlüsselnamen (oder *Unsaved Tag*); die LED blinkt
   magenta.

   ![Emulationsbildschirm mit „Emulating", dem Protokoll [EM4100] und dem Schlüsselnamen](/screens/lfrfid/emulate.png)

3. Halte die Rückseite des Flippers flach an das Lesegerät. <kbd>Back</kbd> beendet die Emulation.

## CLI

Über die USB-/Serial-CLI (Kommando `rfid`):

```text
rfid read <optional: normal | indala | ask134>   - read in ASK/PSK mode
rfid <write | emulate> <key_type> <key_data>      - write or emulate a card
rfid raw_read <ask | ask134 | psk> <filename>     - read and save raw data to a file
rfid raw_emulate <filename>
rfid raw_analyze <filename>
```

`key_type` ist der Protokollname, wie er in `.rfid`-Dateien steht (z. B. `EM4100`, `H10301`), `key_data` ist Hex.

## Fehlerbehebung

- **Es wird nichts gefunden.** Die Karte arbeitet vielleicht mit 13,56 MHz — probiere [NFC](/de/nfc/read). Viele
  „Dual"-Karten enthalten beides.
- **Das Lesen läuft endlos im Kreis.** Probiere einen festen Modus unter **Extra Actions** — ein Durchgang von 2 s
  kann für manche Tags zu kurz sein.
- **Schwache Tags / kleine Anhänger.** Führe das Tag langsam über die Rückseite und achte auf die gelbe/grüne LED.
  Halte es nicht in der Hand über Metall.
- **Unbekanntes Protokoll.** Nimm eine [RAW](/de/rfid/raw)-Aufnahme auf und melde sie den Entwicklern.
- **Emulation wird nicht akzeptiert.** Manche Lesegeräte sind heikel bei Abstand und Ausrichtung — halte den Flipper
  flach und probiere ein paar Positionen. Lesegeräte, die mehr als die ID prüfen (etwa Krypto-Karten), lassen sich
  per Emulation nicht täuschen.

## Verwandte Seiten

- [Auf Rohlinge schreiben](/de/rfid/write) · [Manuell anlegen](/de/rfid/add-manually) ·
  [Protokolle](/de/rfid/protocols) · [Dateiformat](/de/rfid/file-format)
