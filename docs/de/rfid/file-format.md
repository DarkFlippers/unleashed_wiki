---
title: Dateiformate
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/LfRfidFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/T5577FileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-docs, unleashed-src]
---
# Dateiformate für 125 kHz RFID

In `/ext/lfrfid/` liegen drei Arten von Dateien:

| Endung | Was sie beschreibt | Erzeugt von |
|---|---|---|
| `.rfid` | eine **Karte**: Protokoll + ID | Read → Save, Add Manually |
| `.t5577` | einen **Chip**: alle Blöcke eines T5577 | [T5577-App](/de/rfid/t5577-app) |
| `.ask.raw` / `.ask134.raw` / `.psk.raw` | eine rohe Signalaufnahme | [RAW](/de/rfid/raw) |

## `.rfid` — LF-RFID-Schlüssel

```text
Filetype: Flipper RFID key
Version: 1
Key type: EM4100
Data: 01 23 45 67 89
```

Die Datei speichert einen Schlüssel des in `Key type` angegebenen Typs.

| Feld | Beschreibung |
|---|---|
| `Key type` | Protokollname, genau wie in der [Protokolltabelle](/de/rfid/protocols) |
| `Data` | Schlüsseldaten in Hex; die Länge ist pro Protokoll festgelegt |

Gültige `Key type`-Werte in dieser Firmware: `EM4100`, `EM4100/32`, `EM4100/16`, `Electra`, `H10301`, `Idteck`,
`Indala26`, `Indala224`, `IoProxXSF`, `AWID`, `FDX-A`, `FDX-B`, `HIDProx`, `HIDExt`, `Pyramid`, `Viking`,
`Jablotron`, `Paradox`, `PAC/Stanley`, `Keri`, `Gallagher`, `Nexwatch`, `Radio Key`, `GProxII`, `Noralsy`.

Versionsgeschichte: 1 — erste Version. Alte Dateien mit `Key type: I40134` (3 Byte) werden beim Laden in `Indala26`
umgewandelt.

::: tip
Du kannst einen Schlüssel am Rechner anlegen: Schreibe die vier Zeilen von oben mit dem richtigen `Key type` und der
korrekten Anzahl `Data`-Bytes, kopiere die Datei nach `/ext/lfrfid/` und sie erscheint unter **Saved**.
:::

## `.t5577` — T5577-Dump

```text
Filetype: Flipper T5577 dump
Version: 1
# Block 0: ASK/Manchester, RF/64, 2 data blocks, password enabled
Page 0 blocks read: 0 1 2 7
Page 0 Block 0: 00 14 80 50
Page 0 Block 1: 12 34 56 78
Page 0 Block 2: 9A BC DE F0
Page 0 Block 3: 00 00 00 00
Page 0 Block 4: 00 00 00 00
Page 0 Block 5: 00 00 00 00
Page 0 Block 6: 00 00 00 00
Page 0 Block 7: 0C 0D 0E 0F
Page 1 blocks read: 0 1
Page 1 Block 0: E0 15 00 1A
Page 1 Block 1: 20 24 10 00
Page 1 Block 2: 00 00 00 00
Page 1 Block 3: 00 00 00 00
Password: 0C 0D 0E 0F
```

Eine `.t5577`-Datei beschreibt das **Silizium**, eine `.rfid`-Datei die **Karte**. Ein als EM4100 konfigurierter
T5577 lässt sich auf beide Weisen speichern, und die beiden sind nicht austauschbar: `.t5577` enthält die
Konfiguration, die bestimmt, wie der Chip sendet, und das Passwort, das ihn schützt.

| Feld | Beschreibung |
|---|---|
| `Page 0 blocks read` | Blöcke von Page 0, deren Werte vom Chip kommen, durch Leerzeichen getrennt |
| `Page 0 Block 0..7` | Blockinhalt, 4 Hex-Bytes, MSB zuerst. Block 0 = Konfiguration, Block 7 = Passwortspeicher |
| `Page 1 blocks read` | Blöcke von Page 1, die gelesen wurden |
| `Page 1 Block 0..3` | Block 0 wiederholt die Konfiguration; 1–3 enthalten die Rückverfolgungsdaten des Herstellers |
| `Password` | Optional. Ein Passwort, das auf dem Chip **nachweislich funktioniert** |

Die wichtigsten Regeln:

- **Jeder Block hat einen Schlüssel**, gelesen oder nicht. Nur die in `blocks read` genannten Blöcke sind Inhalt, der
  Rest ist Füllmaterial und darf niemals auf ein Tag geschrieben werden. Eine Datei, die überhaupt keine Blöcke
  nennt, wird abgewiesen.
- Ein geschützter Chip verweigert das Lesen von Block 0, das die Erkennung braucht — ohne Passwort bekommst du also
  gar keinen Dump (nicht nur einen unvollständigen). Ein unvollständiger Dump heißt, dass das Tag aus dem Feld
  gerutscht ist.
- `Password` und `Page 0 Block 7` sind zwei verschiedene Angaben und können sich widersprechen: Block 7 ist, was der
  Block beim Lesen enthielt (ganz normaler Speicher, wenn kein Passwort aktiv ist), `Password` ist ein Zugangsdatum,
  das funktioniert hat. Ein Passwort zu löschen löscht nur das Bit in Block 0, Block 7 behält also den alten Wert.
- Die Kommentarzeile, die Block 0 aufschlüsselt, ist nur für Menschen.

### Reihenfolge beim Wiederherstellen

Beim Zurückschreiben eines Dumps (T5577-App → **Write to Tag**) entspricht die Reihenfolge der des Proxmark3:

1. Page 0, Blöcke 1–7. Ab Block 7 müssen Schreibvorgänge das Passwort nutzen, das jetzt in Block 7 steht.
2. Page 1, Blöcke 1–3 (Page 1 Block 0 wird nie geschrieben). Echte Chips verweigern Änderungen an den Blöcken 1–2 —
   gemeldet als *unchanged*, nicht als Fehler.
3. Page 0 Block 0 **zuletzt** — er verändert, wie der Chip sendet.
4. Geschrieben werden nur Blöcke, die in `blocks read` stehen.
5. Ein Block 0 voller Nullen wird **nie** geschrieben: Ein Chip mit diesem Inhalt antwortet überhaupt nicht mehr, und
   es gibt keinen Weg zurück.

Schreib-Frames werden nicht quittiert, Erfolg erkennt man also nur daran, dass man die Blöcke zurückliest.

## `.raw` — RAW-Aufnahmen

Binärdateien, die der RAW-Lesevorgang schreibt. Sie beginnen mit einem Header:

| Feld | Typ | Wert |
|---|---|---|
| magic | uint32 | `0x4C464952` |
| version | uint32 | `1` |
| frequency | float | Trägerfrequenz in Hz (125000 oder 134200) |
| duty_cycle | float | Tastverhältnis des Trägers |
| max_buffer_size | uint32 | größter Puffer in der Datei |

Danach folgen Puffer, jeder mit seiner Größe als Präfix, die als Varint kodierte *(Puls, Dauer)*-Paare enthalten. Zum
Dekodieren nimm `rfid raw_analyze <filename>` in der CLI.

## Verwandte Seiten

- [Protokolle](/de/rfid/protocols) · [T5577-App](/de/rfid/t5577-app) · [RAW](/de/rfid/raw)
