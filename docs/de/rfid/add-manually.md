---
title: Schlüssel manuell anlegen
order: 30
original: [https://docs.flipper.net/zero/rfid/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# 125-kHz-Schlüssel manuell anlegen

Du kannst einen Schlüssel ohne das physische Tag erzeugen: Protokoll auswählen und die Daten eintippen. Das Ergebnis
wird wie ein gelesener Schlüssel gespeichert und lässt sich emulieren oder
[auf einen Rohling schreiben](/de/rfid/write).

**Nimm das**, wenn du die auf einer Karte aufgedruckte oder in einer Zutrittsdatenbank hinterlegte Nummer kennst,
einen Schlüssel aus Notizen wiederherstellen willst oder ein Lesegerät mit einer bestimmten ID testen möchtest.

## Schritt für Schritt

1. Öffne `Main Menu → 125 kHz RFID → Add Manually`.
2. Wähle Protokoll bzw. Format aus der Liste (siehe unten).

   ![Typliste in Add Manually: EM-Micro EM4100, EM4100/32, EM4100/16 und Casi-Rusco C10106](/screens/lfrfid/add_manually.png)

3. Bei Formaten mit Facility Code / Kartennummer hast du die Wahl:
   - **Enter FC/ID** — die Dezimalfelder einzeln eintippen. Die Kopfzeile zeigt Feldname und Wertebereich, z. B.
     `Facility Code (0-255)`. <kbd>Back</kbd> springt zum vorherigen Feld zurück.
   - **Enter Hex Data** — die rohen Bytes eintippen.

   Andere Protokolle gehen direkt in den Hex-Editor *Enter the data in hex*.

   ![Der Editor „Enter the data in hex" mit den Tag-Bytes über einer Hex-Bildschirmtastatur](/screens/lfrfid/add_manually_data.png)

4. Gib einen Namen ein und speichere. Der Schlüssel landet als `/ext/lfrfid/<name>.rfid`.

Einen gespeicherten Schlüssel später ändern: `Saved` → Schlüssel → **Edit** (Hex-Editor, gleicher Dateiname).

::: tip Unleashed
Die Eingabe von **FC / Kartennummer** statt Hex, die zusätzlichen **HID**-Formate und **Casi-Rusco** sind Ergänzungen
von Unleashed. Die Stock-Firmware nimmt nur Hex an. Prüfsummen und Wiegand-Parität werden für dich berechnet.
:::

## Die Liste in der Reihenfolge des Geräts

| Menüname | Gespeichert als (`Key type`) | Eingabe | Hex-Bytes |
|---|---|---|---|
| EM-Micro EM4100 | EM4100 | FC/ID oder Hex | 5 |
| EM-Micro EM4100/32 | EM4100/32 | FC/ID oder Hex | 5 |
| EM-Micro EM4100/16 | EM4100/16 | FC/ID oder Hex | 5 |
| Casi-Rusco C10106 | EM4100/32 | Credential + Card Number | — |
| Electra | Electra | Hex | 8 |
| HID H10301 | H10301 | FC/ID oder Hex | 3 |
| HID H10304 | HIDProx | FC + Card Number | — |
| HID H10302 | HIDProx | Card Number | — |
| HID S10401 | HIDProx | FC + Card Number | — |
| HID H10306 | HIDProx | FC + Card Number | — |
| HID Corp1000-35 | HIDProx | FC + Card Number | — |
| IDTECK Idteck | Idteck | Hex | 8 |
| Motorola Indala26 | Indala26 | Hex | 4 |
| Kantech IoProxXSF | IoProxXSF | FC/ID oder Hex | 4 |
| AWID | AWID | FC/ID oder Hex | 9 |
| FECAVA FDX-A | FDX-A | Hex | 5 |
| ISO FDX-B | FDX-B | Hex | 11 |
| Generic HIDProx | HIDProx | Hex | 6 |
| Generic HIDExt | HIDExt | Hex | 12 |
| Farpointe Pyramid | Pyramid | FC/ID oder Hex | 4 |
| Viking | Viking | Hex | 4 |
| Jablotron | Jablotron | Hex | 5 |
| Paradox | Paradox | Hex | 6 |
| PAC/Stanley | PAC/Stanley | Hex | 4 |
| Keri | Keri | Hex | 4 |
| Gallagher | Gallagher | FC/ID oder Hex | 8 |
| Honeywell Nexwatch | Nexwatch | Hex | 8 |
| Securakey Radio Key | Radio Key | Hex | 6 |
| Guardall GProxII | GProxII | Hex | 12 |
| Noralsy | Noralsy | Hex | 12 |
| Motorola Indala224 | Indala224 | Hex | 28 |

## Wertebereiche für „Enter FC/ID"

| Format | Felder (dezimal) |
|---|---|
| EM4100, EM4100/32, EM4100/16 | Facility Code 0–255, Card Number 0–65535 (liegt in den letzten 3 Byte, die ersten 2 Byte sind null) |
| HID H10301 (26-Bit-Wiegand) | Facility Code 0–255, Card Number 0–65535 |
| AWID | Facility Code 0–255, Card Number 0–65535 (26-Bit-Format, Parität wird ergänzt) |
| Farpointe Pyramid | Facility Code 0–255, Card Number 0–65535 (26 Bit, Parität und CRC werden ergänzt) |
| Kantech IoProxXSF | Facility Code 0–255, Card Number 0–65535, Version 0–255 (Prüfsumme wird ergänzt) |
| Gallagher | Facility Code 0–65535, Card Number 0–16777215, Region Code 0–15, Issue Level 0–15 |
| Casi-Rusco C10106 | Credential 150000–159999, Card Number 0–457681 (so, wie das Zutrittssystem es ausgibt; gespeichert als EM4100/32) |
| HID H10304 (37 Bit) | Facility Code 0–65535, Card Number 0–524287 |
| HID H10302 (37 Bit) | nur Card Number (35 Bit) |
| HID S10401 (37 Bit) | Facility Code 0–63, Card Number (29 Bit) |
| HID H10306 (34 Bit) | Facility Code 0–65535, Card Number 0–65535 |
| HID Corp1000-35 (35 Bit) | Facility Code 0–4095, Card Number 0–1048575 |

::: info Große Kartennummern
Die Zahleneingabe hält einen vorzeichenbehafteten 32-Bit-Wert, deshalb lässt sich der obere Rand eines Feldes mit
mehr als 31 Bit (etwa die 35-Bit-Kartennummer von H10302) nur über **Enter Hex Data** / **Edit** eingeben.
:::

## Tipps

- Eine auf einem EM4100 aufgedruckte Nummer wie `0001234567` ist meist die **DEZ 10**-Form; vergleiche sie nach dem
  Speichern auf dem **Info**-Bildschirm (dort stehen FC/Card, DEZ 8 und DEZ 10), um sicher zu sein, dass du das
  Richtige eingetippt hast.

  ![Info-Bildschirm eines gespeicherten Tags: Dateiname, EM-Micro EM4100, Hex-Daten, FC/Card, DEZ 8 und DEZ 10](/screens/lfrfid/saved_info.png)

- EM4100/32 und EM4100/16 sind derselbe Frame mit den Bitraten RF/32 und RF/16; nimm das, als was das Original
  gelesen wird.
- Bei Protokollen mit reiner Hex-Eingabe kommst du am einfachsten zu korrekten Bytes, indem du das echte Tag einmal
  liest und den `Hex:`-Wert übernimmst.

## Verwandte Seiten

- [Protokolle](/de/rfid/protocols) · [Dateiformat](/de/rfid/file-format) · [Schreiben](/de/rfid/write) ·
  [Lesen](/de/rfid/read)
