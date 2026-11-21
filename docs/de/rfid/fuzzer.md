---
title: RFID-Fuzzer
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/rfidfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# RFID-Fuzzer

Ein **Fuzzer** emuliert eine lange Reihe von IDs hintereinander, um zu testen, wie ein Lesegerät reagiert — etwa ob
es eine Standard-ID akzeptiert, bei fehlerhaften Daten abstürzt, oder um den Bereich gültiger Karten im eigenen
System zu prüfen.

::: tip Unleashed
Die Unleashed-ReadMe nennt unter ihren NFC-/RFID-/iButton-Funktionen **LFRFID- und iButton-Fuzzer-Plugins**. Der
Fuzzer ist eine externe App und nicht Teil des Firmware-Quellbaums: Vorgebaute App-Packs kommen zu den
Release-Builds dazu, und das zu jedem Release veröffentlichte **Extra-Apps-Pack** enthält alle bekannten
funktionierenden Apps. Die Menüs hängen von der App-Version ab und werden hier deshalb nicht beschrieben.
:::

## Was die Firmware mitbringt: Beispiel-UID-Listen

Die Firmware installiert Beispiel-ID-Listen für den Fuzzer nach **`/ext/rfidfuzzer/`**:

| Datei | Protokoll | ID-Länge (Hex-Zeichen) |
|---|---|---|
| `example_uids_em4100.txt` | EM4100 | 10 (5 Byte) |
| `example_uids_h10301.txt` | HID H10301 | 6 (3 Byte) |
| `example_uids_hidprox.txt` | HIDProx | 12 (6 Byte) |
| `example_uids_pac.txt` | PAC/Stanley | 8 (4 Byte) |

Format — eine Hex-ID pro Zeile, `#` für Kommentare und am Dateiende eine **Leerzeile**:

```text
# Example file, P.S. keep empty line at the end!
0000000000
FE00000000
CAFE000000
00CAFE0000

```

Für eine eigene Liste kopierst du eine der Beispieldateien und ersetzt die IDs; die ID-Länge muss zur Schlüsselgröße
des Protokolls passen (siehe [Protokolle](/de/rfid/protocols), Spalte *Bytes*).

Die Unleashed-FAQ verlinkt fertige Wörterbuchdateien aus der Community:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058) und
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Setze den Fuzzer nur an Lesegeräten ein, die dir gehören oder die du testen darfst.
:::

## Verwandte Seiten

- [Protokolle](/de/rfid/protocols) · [Lesen](/de/rfid/read) · [iButton-Fuzzer](/de/ibutton/fuzzer)
