---
title: Dateiformate
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/resources/subghz/assets, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md]
sources: [unleashed-docs, unleashed-src]
---
# Sub-GHz-Dateiformate

Alle Sub-GHz-Dateien sind reiner Text im *Flipper File Format* (Zeilen der Form `Key: value`), du kannst sie also
auf einem PC ansehen und bearbeiten. Diese Seite beschreibt die Signaldateien (`.sub`) und die
Konfigurationsdateien in `/ext/subghz/assets/`.

| Pfad | Inhalt |
|---|---|
| `/ext/subghz/*.sub` | Gespeicherte Signale: Schlüssel, RAW und BinRAW |
| `/ext/subghz/assets/setting_user` | Deine Frequenzen, Hopper-Liste, eigene Presets |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Deine KeeLoq-Herstellerschlüssel |
| `/ext/subghz/assets/keeloq_mfcodes` | Eingebaute KeeLoq-Herstellerschlüssel (verschlüsselt, mit der Firmware ausgeliefert) |
| `/ext/subghz/assets/nice_flor_s`, `alutech_at_4n` | Eingebaute Tabellen für diese Protokolle |
| `/ext/subghz/assets/dangerous_settings` | Schalter für den erweiterten Frequenzbereich, siehe [Frequenzen](/de/subghz/frequencies#extended-range) |

## Aufbau einer `.sub`-Datei

Eine `.sub`-Datei hat drei Teile:

1. **Kopf** — Dateityp, Version, Frequenz.
2. **Preset** — Modulations-Preset oder eine vollständige eigene CC1101-Konfiguration.
3. **Daten** — Protokollname und seine Felder, oder RAW-Zeiten.

### Kopf

| Feld | Typ | Beschreibung |
|---|---|---|
| `Filetype` | string | `Flipper SubGhz Key File` bei Schlüsseln, `Flipper SubGhz RAW File` bei RAW-Aufnahmen |
| `Version` | uint | Version des Dateiformats, derzeit `1` |
| `Frequency` | uint | Frequenz in Hz, z. B. `433920000` |

### Preset

| Feld | Beschreibung |
|---|---|
| `Preset` | Name des Presets. Bei einem eigenen Preset muss er `FuriHalSubGhzPresetCustom` lauten |
| `Custom_preset_module` | Transceiver, `CC1101` beim Flipper Zero (nur bei eigenem Preset) |
| `Custom_preset_data` | Konfiguration des Transceivers (nur bei eigenem Preset) |

Eingebaute Presets:

| Wert von `Preset` | Name im Menü | Bedeutung |
|---|---|---|
| `FuriHalSubGhzPresetOok270Async` | `AM270` | OOK, 270 kHz Bandbreite |
| `FuriHalSubGhzPresetOok650Async` | `AM650` | OOK, 650 kHz Bandbreite |
| `FuriHalSubGhzPreset2FSKDev238Async` | `FM238` | 2-FSK, 2,38 kHz Hub, 270 kHz Bandbreite |
| `FuriHalSubGhzPreset2FSKDev12KAsync` | `FM12K` | 2-FSK, 12 kHz Hub |
| `FuriHalSubGhzPreset2FSKDev476Async` | `FM476` | 2-FSK, 47,6 kHz Hub, 270 kHz Bandbreite |

Ein eigenes Preset wird in die Datei eingebettet, ein anderer Flipper kann sie also auch ohne dieses Preset in
seinen Einstellungen senden.

#### Daten eines eigenen Presets {#custom-preset-data}

Hex-Bytes, durch Leerzeichen getrennt: `XX YY XX YY … 00 00 ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ`

- `XX` — Registeradresse des CC1101, `YY` — Registerwert (so viele Paare wie nötig);
- `00 00` — Ende des Registerblocks;
- `ZZ ×8` — die 8 Byte große PA-Tabelle (Rampe des Leistungsverstärkers).

Die Bedeutung der Register steht im [CC1101-Datenblatt](https://www.ti.com/lit/ds/symlink/cc1101.pdf).

### Schlüsseldateien

Dekodierte Signale speichern den Protokollnamen und seine Felder:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

| Feld | Beschreibung |
|---|---|
| `Protocol` | Protokollname genau wie in der Protokollregistrierung (z. B. `Princeton`, `KeeLoq`, `Nice FloR-S`, `CAME Atomo`, `Security+ 2.0`) |
| `Bit` | Länge der Nutzdaten in Bit |
| `Key` | Nutzdaten, Hex, 8 Byte |
| `TE` | Grundlegende Impulsdauer (Quantisierungsintervall) in µs, bei Protokollen, die sie speichern |

Protokolle können eigene Felder ergänzen. Diese begegnen dir in Unleashed:

| Feld | Genutzt von | Bedeutung |
|---|---|---|
| `Manufacture` | KeeLoq, FAAC SLH / Genius | Hersteller, dessen Schlüssel das Signal dekodiert (z. B. `DoorHan`, `BFT`, `Genius`) |
| `Seed` | BFT Mitto, Erreka, FAAC SLH, Genius, manche KeeLoq | Geheimnis pro Fernbedienung für Secure learning |
| `CounterMode` | Nice Flor-S, CAME Atomo, Alutech AT-4N, KeeLoq, V2 Phoenix | Experimentelles Zählerverhalten, siehe [Zählermodi](/de/subghz/counter-mode) |
| `Secplus_packet_1`, `Pin` | Security+ 2.0 | Zweites Paket; Tastatur-PIN bei 86-Bit-Paketen ([Security+ PIN](/de/subghz/secplus-pin)) |
| `Cert` | Nice O-Code | Empfängerzertifikat ([Nice O-Code](/de/subghz/nice-o-code)) |

Beispiel mit eigenem Preset:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetCustom
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

::: warning Rolling-Code-Dateien bearbeiten
Den `Key` eines dynamischen Protokolls von Hand zu ändern ergibt selten einen gültigen Code. Um Seriennummer,
Taste oder Zähler zu ändern, nimm [Add Manually [Advanced]](/de/subghz/add-manually) oder, im Debug-Modus,
`Saved → Datei → Signal Settings`.
:::

### RAW-Dateien

Aufnahmen aus [Read RAW](/de/subghz/read-raw):

```text
Filetype: Flipper SubGhz RAW File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: RAW
RAW_Data: 29262 361 -68 2635 -66 24113 -66 11 ...
RAW_Data: -424 205 -412 159 -412 381 -240 181 ...
```

- `Protocol` muss `RAW` sein.
- `RAW_Data` — Dauern in µs: positiv = Träger ein, negativ = Träger aus. Die Werte dürfen nicht null sein, müssen
  mit einer positiven Zahl beginnen und im Vorzeichen abwechseln. Bis zu 512 Werte pro Zeile; die Zeile darf sich
  beliebig oft wiederholen.

Lange Nutzdaten werden während des Sendens von der SD-Karte gelesen. Bei sehr kurzen Zeiten (unter 10 µs) kommt
eine langsame Karte womöglich nicht mit und das Senden bricht vor dem Ende ab.

### BinRAW-Dateien

`Bin RAW` in `Read → Config` erzeugt **BinRAW**-Dateien. Anders als RAW speichern sie nur die nützliche, sich
wiederholende Sequenz, mit rekonstruierter Bitrate und ohne das Rauschen, und können so fast jedes **statische**
Protokoll wiedergeben, bekannt oder nicht. Halte die Taste der Fernbedienung beim Lesen etwas länger, damit genug
Daten zusammenkommen.

| Feld | Beschreibung |
|---|---|
| `Protocol` | `BinRAW` |
| `Bit` | Länge der Nutzdaten der ganzen Datei in Bit (max. 4096) |
| `TE` | Quantisierungsintervall, µs |
| `Bit_RAW` | Länge des folgenden `Data_RAW`-Blocks in Bit |
| `Data_RAW` | Kodierte Dauern: jedes Bit = ein `TE`; `1` = Träger, `0` = kein Träger |

Beispiel: `TE: 100`, `Bit_RAW: 8`, `Data_RAW: 37` → `0b00110111` → sendet `-200 200 -100 300`.
Die Paare `Bit_RAW` + `Data_RAW` bilden wiederholte Blöcke; mehrere Blöcke werden hintereinander gesendet.

```text
Protocol: BinRAW
Bit: 1572
TE: 597
Bit_RAW: 260
Data_RAW: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F 4A B5 55 4C B3 52 AC D5 2D 53 52 AD 4A D5 35 00
```

## `setting_user` {#setting-user}

Zusätzliche Frequenzen und Presets, geladen beim Start der Sub-GHz-App. Benenne `setting_user.example` in
`setting_user` um.

```text
Filetype: Flipper SubGhz Setting File
Version: 1

# Add standard frequencies included with firmware and place user frequencies after them
Add_standard_frequencies: true

# Default frequency for "Read" and "Read Raw"
Default_frequency: 433920000

# Frequencies for "Read", "Read Raw" and "Frequency Analyzer"
Frequency: 300000000
Frequency: 310000000

# Frequencies for hopping mode (keep this list small)
Hopper_frequency: 300000000
Hopper_frequency: 310000000

# Custom preset
Custom_preset_name: AM_1
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
```

| Schlüssel | Bedeutung |
|---|---|
| `Add_standard_frequencies` | `true` — Liste der Firmware + deine (dahinter angehängt); `false` — nur deine (dann beide Listen `Frequency` und `Hopper_frequency` füllen) |
| `Default_frequency` | Frequenz, mit der Read / Read RAW starten |
| `Frequency` | Fügt eine Frequenz zur Hauptliste hinzu (9 Stellen, Hz). Mehrfach möglich |
| `Hopper_frequency` | Fügt eine Frequenz zum Hopping hinzu. Eine mehrfach einzutragen lässt den Flipper häufiger auf sie hören |
| `Custom_preset_name` / `_module` / `_data` | Ein eigenes Modulations-Preset, das unter diesem Namen in der Liste `Modulation` erscheint. Datenformat: [siehe oben](#custom-preset-data) |

Die `.example`-Datei bringt auskommentierte Presets mit, die du aktivieren kannst: `FM95`, `FM15k` (2-FSK, 200 kHz
Bandbreite / 135 kHz Filter, 15,86 kHz Hub), `Pagers`, `AM_1`, `AM_2`.

## `keeloq_mfcodes_user` {#keeloq-mfcodes-user}

Deine eigenen KeeLoq-Herstellerschlüssel, beim Start der App zusätzlich zur eingebauten (verschlüsselten)
Datenbank geladen. Lege sie aus `keeloq_mfcodes_user.example` an, entferne die Beispielschlüssel und **lass am
Ende eine leere Zeile stehen**.

```text
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:2:Test2
```

Jede Zeile lautet `KEY:METHOD:NAME`:

- `KEY` — 64-Bit-Herstellerschlüssel, 16 Hex-Ziffern;
- `NAME` — Name ohne Leerzeichen, bis zu 64 Zeichen (erscheint in Read als Hersteller);
- `METHOD` — Anlernverfahren:

| Wert | Verfahren |
|---|---|
| `0` | alles probieren: durchläuft vorherigen und Herstellerschlüssel in direkter und umgekehrter Bytefolge |
| `1` | Simple Learning |
| `2` | Normal Learning |
| `3` | Secure Learning (braucht einen Seed) |
| `4` | Magic XOR type 1 |
| `5` | FAAC SLH |
| `6` | Magic Serial type 1 |
| `7` | Magic Serial type 2 |
| `8` | Magic Serial type 3 |

`Encryption: 0` bedeutet, dass die Datei im Klartext vorliegt — eigene Dateien dürfen nicht verschlüsselt sein.
Mehr zu den Anlernverfahren: [KeeLoq](/de/subghz/keeloq).

## Verwandte Seiten

- [Read](/de/subghz/read) · [Read RAW](/de/subghz/read-raw) · [Frequenzen](/de/subghz/frequencies) · [Radio Settings](/de/subghz/settings)
- [KeeLoq](/de/subghz/keeloq) · [Zählermodi](/de/subghz/counter-mode) · [Map-Dateien von Sub-GHz Remote](/de/subghz/remote)
