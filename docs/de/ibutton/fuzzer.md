---
title: iButton-Fuzzer
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/ibtnfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# iButton-Fuzzer

Ein **Fuzzer** emuliert eine Reihe von Schlüssel-IDs hintereinander, um zu sehen, wie ein Lesegerät reagiert — etwa
um zu prüfen, ob die eigene Türsprechanlage Standard- oder fehlerhafte IDs akzeptiert.

::: tip Unleashed
Die Unleashed-ReadMe nennt **LFRFID- und iButton-Fuzzer-Plugins**. Der Fuzzer ist eine externe App und nicht Teil des
Firmware-Quellbaums: Vorgebaute App-Packs kommen zu den Release-Builds dazu, und das zu jedem Release
veröffentlichte **Extra-Apps-Pack** enthält alle bekannten funktionierenden Apps. Die Menüs hängen von der
App-Version ab und werden hier deshalb nicht beschrieben.
:::

## Was die Firmware mitbringt: Beispiel-UID-Listen

Die Firmware installiert Beispiel-ID-Listen nach **`/ext/ibtnfuzzer/`**:

| Datei | Protokoll | ID-Länge (Hex-Zeichen) |
|---|---|---|
| `example_uids_ds1990.txt` | Dallas DS1990 | 16 (8 Byte) |
| `example_uids_cyfral.txt` | Cyfral | 4 (2 Byte) |
| `example_uids_metakom.txt` | Metakom | 8 (4 Byte) |

Format — eine Hex-ID pro Zeile, `#` für Kommentare, am Ende eine **Leerzeile** stehen lassen:

```text
# Example file, P.S. keep empty line at the end!
0000000000000000
FE00000000000000
CAFE000000000000
00CAFE0000000000

```

Für eine eigene Liste kopierst du eine der Beispieldateien und ersetzt die IDs; die Länge muss zum Protokoll passen.

Aus der Unleashed-FAQ verlinkte Community-Wörterbücher:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058),
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Setze den Fuzzer nur an Lesegeräten ein, die dir gehören oder die du testen darfst.
:::

## Verwandte Seiten

- [Protokolle](/de/ibutton/protocols) · [Schlüssel emulieren](/de/ibutton/read) · [RFID-Fuzzer](/de/rfid/fuzzer)
