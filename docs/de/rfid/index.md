---
title: 125 kHz RFID
author: gromovyna
original: [https://docs.flipper.net/zero/rfid, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08]
sources: [unleashed-src, flipper-docs, unleashed-readme, gromovyna]
---
# 125 kHz RFID

Niederfrequentes (LF) RFID ist die „Proximity"-Technik günstiger Zutrittskarten und Schlüsselanhänger, von
Türsprechanlagen-Tags, Teilen von Parkhaus- und Fitnessstudio-Systemen sowie von Tierchips. Solche Tags senden
meist nur eine feste ID ohne jede Kryptografie — deshalb lassen sie sich leicht lesen, emulieren und klonen.

Flipper Zero hat auf der Rückseite eine 125-kHz-Antenne (auf der Dualband-Antenne, neben der NFC-Spule für
13,56 MHz), angesteuert vom MCU STM32WB55. Damit kann der Flipper LF-Tags **lesen**, **speichern**, **emulieren** und
**schreiben**.

::: tip Unleashed
Die 125-kHz-RFID-App stammt aus der offiziellen Firmware. Darüber hinaus bietet der Unleashed-Build:
- ein Menü **Settings → Write Chips**: Neben T5577 kann sie **EM4305** und Hitag-Micro-Klone (**8265**, **8210**,
  **H5.5**) beschreiben, dazu das optional zuschaltbare Ziel **8268** (Hitag S). Der Schreibbildschirm zeigt, welcher
  Chip gerade probiert wird und welcher den Schreibvorgang angenommen hat;
- **Write and set password** für T5577-Rohlinge;
- zusätzliche Formate in **Add Manually** (Facility Code / Kartennummer statt Hex eingeben, HID H10304/H10302/S10401/
  H10306/Corp1000-35, Casi-Rusco) sowie die Anzeige von DEZ 8 / DEZ 10 für EM4100;
- einen dritten Lesedurchgang bei **134.2 kHz** für Tierchips und einen eigenen Modus **Read FDX-B (Animals)**;
- die mitgelieferte **T5577**-App (Blöcke lesen/bearbeiten/wiederherstellen, Test, Wipe, Passwort löschen und
  mitlesen).
:::

## Hauptmenü

`Main Menu → 125 kHz RFID` öffnet ein Menü mit diesen Einträgen (Bezeichnungen genau wie in der Firmware):

![Das Menü 125 kHz RFID mit Read, Saved, Add Manually und Extra Actions](/screens/lfrfid/menu.png)

| Eintrag | Funktion | Seite |
|---|---|---|
| **Read** | Tag automatisch erkennen und lesen (Zyklus ASK → PSK → 134 kHz) | [Tags lesen](/de/rfid/read) |
| **Saved** | `/ext/lfrfid/` durchsehen — gespeicherte Schlüssel emulieren, schreiben, bearbeiten, umbenennen, löschen | [Tags lesen](/de/rfid/read), [Schreiben](/de/rfid/write) |
| **Add Manually** | Schlüssel aus Protokoll und ID anlegen | [Manuell anlegen](/de/rfid/add-manually) |
| **Extra Actions** | Mit fester Modulation lesen (ASK, PSK, FDX-B); RAW lesen/emulieren im Debug-Modus | [Tags lesen](/de/rfid/read), [RAW](/de/rfid/raw) |
| **Settings** | **Write Chips** — welche Rohling-Typen beim Schreiben verwendet werden dürfen | [Schreiben](/de/rfid/write) |

## Seiten in diesem Abschnitt

- [Tags lesen](/de/rfid/read) — LF-Tags lesen, speichern und emulieren; Lesen mit fester Modulation.
- [Auf Rohlinge schreiben](/de/rfid/write) — welche Rohlinge funktionieren (T5577, EM4305, Hitag Micro, 8268), die
  Write-Chips-Einstellung, Schreiben mit Passwort, Fehlermeldungen.
- [Manuell anlegen](/de/rfid/add-manually) — alle Protokolle von Add Manually und die FC/ID-Eingabeformate.
- [Unterstützte Protokolle](/de/rfid/protocols) — vollständige Protokolltabelle: Modulation, Datengröße, dekodierte
  Felder, Schreibunterstützung.
- [Tierchips](/de/rfid/animal-microchips) — FDX-B-/FDX-A-Chips für Haustiere.
- [T5577 und Hitag Micro (von @gromovyna)](/de/rfid/t5577-hitag) — die Geschichte zu H5.5 / 8265 / 8210, die
  Schreib-UX, T5577-Wipe.
- [T5577-App](/de/rfid/t5577-app) — Blöcke lesen, bearbeiten, wiederherstellen, testen, Wipe, Passwort löschen,
  Passwort mitlesen.
- [RAW-Aufnahme](/de/rfid/raw) — rohes ASK-/PSK-Signal für die Protokollforschung aufnehmen.
- [Fuzzer](/de/rfid/fuzzer) — was die Firmware für die RFID-Fuzzer-App mitbringt.
- [Dateiformate](/de/rfid/file-format) — `.rfid`-, `.t5577`- und `.raw`-Dateien.

## Wo die Dateien liegen

| Pfad | Inhalt |
|---|---|
| `/ext/lfrfid/*.rfid` | Gespeicherte Schlüssel |
| `/ext/lfrfid/*.t5577` | T5577-Block-Dumps (von der T5577-App geöffnet) |
| `/ext/lfrfid/*.ask.raw`, `*.ask134.raw`, `*.psk.raw` | RAW-Aufnahmen |
| `/ext/lfrfid/.lfrfid.settings` | Einstellung Write Chips |
| `/ext/lfrfid/assets/t5577_dict.lfrfid` | T5577-Passwort-Wörterbuch (wird bei Updates überschrieben) |
| `/ext/lfrfid/assets/t5577_dict_user.lfrfid` | Deine eigenen T5577-Passwörter |
| `/ext/lfrfid/assets/iso3166.lfrfid` | Ländernamen für FDX-B-Chips |

::: warning
Klone und emuliere nur Tags, die dir gehören oder die du testen darfst.
:::
