---
title: Unterstützte Protokolle
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks, https://docs.flipper.net/zero/ibutton/read, https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Unterstützte iButton-Protokolle

Erstellt aus `lib/ibutton/protocols/` der Unleashed-Firmware. Die Firmware teilt die Protokolle in **Dallas**
(1-Wire) und **misc** (Cyfral, Metakom) ein.

| Protokoll (Dateiname) | Menüname | Family Code | Speicher | Emulation | Write ID auf | Full Write on Same Type |
|---|---|---|---|---|---|---|
| `DS1990` | Dallas DS1990 | `01` | — | ✓ | RW1990.1, RW1990.2, TM2004, TM01x | — |
| `DS1420` | Dallas DS1420 | `81` | — | ✓ | RW1990.1, RW1990.2, TM2004 | — |
| `DS1992` | Dallas DS1992 | `08` | 128 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1996` | Dallas DS1996 | `0C` | 8192 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1971` | Dallas DS1971 | `14` | 32 B EEPROM (`Eeprom Data`) | ✓ | TM2004 | ✓ |
| `(non-specific)` | Dallas (non-specific) | beliebig | — (nur ROM) | ✓ | TM2004 | — |
| `Cyfral` | Cyfral | — | 2-Byte-Code | ✓ | TM01x | — |
| `Metakom` | Metakom | — | 4-Byte-Code | ✓ | TM01x | — |

## Dallas 1-Wire

„Touch Memory“ von Dallas Semiconductor (heute Analog Devices). Jedes Gerät hat ein 8 Byte großes ROM: Family Code,
48-Bit-Seriennummer und CRC-8. Der Flipper prüft die CRC und erkennt den Typ am Family Code.

- **DS1990 (DS1990A)** — der klassische Schlüssel, der nur eine ID trägt und in den meisten Türsprechanlagen steckt.
- **DS1420** — voll kompatibel mit DS1990, nur der Family Code unterscheidet sich (`81` statt `01`).
- **DS1992 / DS1996** — Speicherschlüssel mit SRAM; DS1971 — mit EEPROM. Der Flipper liest den Speicher, kann ihn
  anzeigen (**Data Info**), emulieren und auf einen Schlüssel desselben Typs kopieren.
- **Dallas (non-specific)** — Sammelposten für jedes andere 1-Wire-Gerät: Es wird nur das ROM gelesen, nichts
  geprüft. Praktisch auch, um einen Schlüssel mit absichtlich falschem Family Code oder falscher CRC zu erzeugen.

## Cyfral

Ein Protokoll für Türsprechanlagen-Schlüssel, verbreitet in Russland und der GUS; es ist kein 1-Wire. Der Code liegt
in 2 Byte. Kann emuliert und auf einen TM01x-Rohling geschrieben werden.

## Metakom

Ein weiteres GUS-Protokoll für Türsprechanlagen. Der Code ist 4 Byte lang, jedes Byte trägt ein Paritätsbit — ein
Schlüssel mit falscher Parität wird als ungültig gemeldet und nicht geschrieben. Kann emuliert und auf einen
TM01x-Rohling geschrieben werden.

## Rohlinge

| Rohling | Nimmt an | Verhalten |
|---|---|---|
| **RW1990.1** | Dallas-ROM (8 Byte) | Entsperren, schreiben (Bits invertiert), sperren |
| **RW1990.2** | Dallas-ROM (8 Byte) | Entsperren, schreiben, sperren |
| **TM2004** | Dallas-ROM (8 Byte) | Schreibt ab Adresse 0 und liest jedes Byte zur Kontrolle zurück |
| **TM01x** | Dallas-ROM, Cyfral, Metakom | Cyfral/Metakom werden als 36-Bit-Frame geschrieben (4 Bit Präfix + 32 Code-Bits), verifiziert und dann **finalisiert** (einmalig). Dallas-IDs werden nicht finalisiert |

Zur Verwendung siehe [Schreiben](/de/ibutton/write).

::: tip Unleashed
In der offiziellen Dokumentation fehlen DS1420, die Einstellung Write Blanks und das Schreiben von Cyfral/Metakom auf
TM01x.
:::

## Verwandte Seiten

- [Lesen](/de/ibutton/read) · [Schreiben](/de/ibutton/write) · [Dateiformat](/de/ibutton/file-format)
