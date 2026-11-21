---
title: Schlüssel lesen
order: 10
original: [https://docs.flipper.net/zero/ibutton/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols]
sources: [unleashed-src, flipper-docs]
---
# iButton-Schlüssel lesen, speichern und emulieren

Flipper Zero liest Dallas-1-Wire-Schlüssel (ID und bei Speicherschlüsseln auch deren Speicher) sowie Cyfral- und
Metakom-Schlüssel und kann sie anschließend speichern und emulieren.

| Schlüssel | Was gelesen wird |
|---|---|
| Dallas **DS1990** / **DS1420** | nur das 8-Byte-ROM (ID) — der Schlüssel hat keinen Speicher |
| Dallas **DS1992** | ROM + 128 Byte SRAM |
| Dallas **DS1996** | ROM + 8192 Byte SRAM |
| Dallas **DS1971** | ROM + 32 Byte EEPROM |
| Andere 1-Wire-Geräte | nur das ROM, angezeigt als **Dallas (non-specific)** |
| **Cyfral** | 2-Byte-Code |
| **Metakom** | 4-Byte-Code |

## Einen Schlüssel lesen

1. Öffne `Main Menu → iButton → Read`. Auf dem Display steht **Reading — Connect key with pogo pins**.

   ![Lesebildschirm mit der Aufforderung „Connect key with pogo pins"](/screens/ibutton/read.png)

2. Halte den Schlüssel an den **flachen Teil** des iButton-Kontaktfelds, sodass seine Mitte den **linken Daten-Pin**
   und sein Rand den **mittleren Masse-Pin** berührt. Halte ihn still.
3. Ist der Schlüssel gelesen, piept der Flipper und zeigt das Protokoll (z. B. **Dallas DS1990**) und die ID.

   ![Leseergebnis: Dallas DS1990 mit achtstelliger ID und Family Code, unten Retry und More](/screens/ibutton/read_success.png)

4. Tasten: <kbd>←</kbd> **Retry**, <kbd>→</kbd> **More**. <kbd>Back</kbd> fragt *Exit to iButton Menu? All unsaved data
   will be lost!*

**More** bietet (die Einträge hängen vom Protokoll ab):

| Eintrag | Wann sichtbar | Aktion |
|---|---|---|
| **Save** | immer | Schlüssel benennen, gespeichert unter `/ext/ibutton/<name>.ibtn` |
| **Emulate** | immer | Sofort emulieren |
| **Write ID** | schreibbare Protokolle | ID auf einen Rohling schreiben — [Schreiben](/de/ibutton/write) |
| **Full Write on Same Type** | DS1992, DS1996, DS1971 | Speicher auf einen Schlüssel desselben Typs kopieren |
| **Data Info** | DS1992, DS1996, DS1971 | Speicherinhalt anzeigen |

## Lesefehler

Bestehen die Daten die Prüfung des Protokolls nicht, erklärt der Fehlerbildschirm den Grund und bietet weiterhin
**Retry** und **More** an:

- **CRC Error** (Dallas) — das 8. Byte des ROM ist eine CRC über die ersten sieben; der Bildschirm zeigt das ROM mit
  hervorgehobenem fehlerhaftem Byte und die *Expected CRC*. Meist liegt es an schlechtem Kontakt: Schlüssel reinigen
  und erneut lesen. Wiederholt sich das, kannst du ihn trotzdem speichern und die Emulation versuchen — manche
  Lesegeräte ignorieren die CRC. Schlägt die Emulation fehl, ist der Fehler nicht zu beheben.
- **Invalid Metakom key: odd parity in byte N** — ein Metakom-Byte hat die Paritätsprüfung nicht bestanden; lies den
  Schlüssel erneut.

## Gespeicherte Schlüssel

`Main Menu → iButton → Saved` öffnet `/ext/ibutton/`. Das Menü eines Schlüssels:

| Eintrag | Aktion |
|---|---|
| **Emulate** | Gegenüber einem Lesegerät emulieren |
| **Write ID** | ID auf einen Rohling schreiben |
| **Full Write on Same Type** | nur DS1992/DS1996/DS1971 — Speicher kopieren |
| **Edit** | ID in Hex ändern und unter einem Namen speichern |
| **Rename** / **Delete** | Datei verwalten |
| **Info** | Name, Protokoll, ID; <kbd>→</kbd> **More** zeigt bei Speicherschlüsseln die Speicherdaten |

## Emulieren

1. Öffne einen gespeicherten Schlüssel → **Emulate** (oder direkt nach dem Lesen **More → Emulate**). Der Bildschirm
   zeigt **Emulating**, `[Protocol]` und den Schlüsselnamen (oder *Unsaved Key*).

   ![Emulationsbildschirm mit „Emulating", dem Protokoll [DS1990] und dem Schlüsselnamen](/screens/ibutton/emulate.png)

2. Drücke den **hervorstehenden Teil** des Kontaktfelds gegen das Lesegerät: Der **rechte Daten-Pin** muss die Mitte
   des Lesegeräts berühren, der **mittlere Masse-Pin** seinen Rand.
3. Erreicht der Masse-Pin den Rand nicht, verbinde zwei Kabel: GPIO **17** → Mitte des Lesegeräts, GPIO
   **8 / 11 / 18** (GND) → Rand.

## CLI

```text
ikey read
ikey emulate <key_type> <key_data>
ikey write Dallas <key_data>
	<key_type>: Dallas (8 bytes), Cyfral (2 bytes), Metakom (4 bytes, must contain correct parity)
	<key_data> is hex
```

## Fehlerbehebung

- **Es passiert nichts.** Der Schlüssel berührt nicht beide Pins — kippe ihn so, dass der Rand den Masse-Pin berührt.
- **Nicht unterstützter Schlüssel.** Möglicherweise nutzt er ein nicht unterstütztes Protokoll (oder es ist ein
  RFID-Anhänger — probiere [125 kHz RFID](/de/rfid/read)).
- **Emulation wird abgewiesen.** Prüfe den Pin-Kontakt; manche Lesegeräte erkennen Emulatoren oder prüfen Dinge, die
  der Flipper nicht nachbilden kann. Hast du den Schlüssel von Hand bearbeitet oder angelegt, kontrolliere die ID
  noch einmal.

## Verwandte Seiten

- [Schreiben](/de/ibutton/write) · [Manuell anlegen](/de/ibutton/add-manually) ·
  [Protokolle](/de/ibutton/protocols) · [Dateiformat](/de/ibutton/file-format)
