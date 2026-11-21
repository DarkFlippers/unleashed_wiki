---
title: Dateiformat
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-docs, unleashed-src]
---
# Dateiformat für iButton-Schlüssel (`.ibtn`)

Gespeicherte Schlüssel liegen in `/ext/ibutton/` mit der Endung `.ibtn`. Eine Datei enthält einen Schlüssel mit allen
Daten, die sein Protokoll braucht.

## Beispiel

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1992
Rom Data: 08 DE AD BE EF FA CE 4E
Sram Data: 4E 65 76 65 72 47 6F 6E 6E 61 47 69 76 65 59 6F 75 55 70 4E 65 76 65 72 47 6F 6E 6E 61 4C 65 74 59 6F 75 44 6F 77 6E 4E 65 76 65 72 47 6F 6E 6E 61 52 75 6E 41 72 6F 75 6E 64 41 6E 64 44 65 73 65 72 74 59 6F 75 4E 65 76 65 72 47 6F 6E 6E 61 4D 61 6B 65 59 6F 75 43 72 79 4E 65 76 65 72 47 6F 6E 6E 61 53 61 79 47 6F 6F 64 62 79 65 4E 65 76 65 72 47 6F 6E 6E 61 54 65 6C 6C 41 4C 69 65
```

Ein DS1990-Schlüssel (die Bytes sind ein Beispiel; ein echtes ROM endet mit einer gültigen CRC):

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1990
Rom Data: 01 23 45 67 89 AB CD EF
```

Ein Cyfral-Schlüssel:

```text
Filetype: Flipper iButton key
Version: 2
Protocol: Cyfral
Data: A1 B2
```

## Version 2 (aktuell)

Welche Felder nach `Protocol` folgen, hängt vom Protokoll ab.

| Feld | Typ | Beschreibung |
|---|---|---|
| `Protocol` | String | `DS1990`, `DS1992`, `DS1996`, `DS1971`, `DS1420`, `(non-specific)`, `Cyfral`, `Metakom` |
| `Rom Data` | Hex | 8-Byte-ROM (nur Dallas-Protokolle) |
| `Sram Data` | Hex | SRAM-Inhalt (DS1992: 128 Byte, DS1996: 8192 Byte) |
| `Eeprom Data` | Hex | EEPROM-Inhalt (DS1971: 32 Byte) |
| `Data` | Hex | Schlüsselcode (Cyfral: 2 Byte, Metakom: 4 Byte) |

Hinweise:
- **(non-specific)** ist der Sammelposten für unbekannte 1-Wire-Geräte (Menüname *Dallas (non-specific)*). Er enthält
  nur das ROM und prüft nichts — nimm ihn für Schlüssel mit absichtlich ungültigem Family Code oder ungültiger CRC.
  Die Firmware speichert ihn als `Protocol: (non-specific)`; der in der offiziellen Dokumentation und in älteren
  Dateien verwendete Name `DSGeneric` wird weiterhin akzeptiert.
- **DS1420** ist voll kompatibel mit DS1990; nur der Family Code unterscheidet sich (`0x81` statt `0x01`).
- Neue Protokolle erfordern keine neue Formatversion — jedes Protokoll definiert seine eigenen Felder.

## Version 1 (veraltet)

```text
Filetype: Flipper iButton key
Version: 1
Key type: Dallas
Data: 01 23 45 67 89 AB CD EF
```

| Feld | Typ | Beschreibung |
|---|---|---|
| `Key type` | String | `Cyfral`, `Dallas`, `Metakom` |
| `Data` | Hex | Schlüsseldaten |

Dateien der Version 1 werden weiterhin geladen (`Dallas` wird als DS1990 gelesen) und beim Speichern in Version 2
umgewandelt.

## Verwandte Seiten

- [Protokolle](/de/ibutton/protocols) · [Manuell anlegen](/de/ibutton/add-manually) · [Lesen](/de/ibutton/read)
