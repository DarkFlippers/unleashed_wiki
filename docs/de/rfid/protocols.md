---
title: Unterstützte Protokolle
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://docs.flipper.net/zero/rfid/read]
sources: [unleashed-src, flipper-docs]
---
# Unterstützte 125-kHz-Protokolle

Die Tabelle entstand aus `lib/lfrfid/protocols/` der Unleashed-Firmware. Alle Protokolle lassen sich **lesen**,
**speichern**, **emulieren** und **manuell anlegen**; die letzten Spalten zeigen, welche Rohling-Chips sie tragen
können (siehe [Schreiben](/de/rfid/write)).

- **Name** — wie auf dem Display angezeigt und in `.rfid`-Dateien als `Key type` gespeichert.
- **Lesen** — welcher Lesedurchgang das Protokoll dekodiert: ASK, PSK oder beide.
- **Bytes** — Länge des Feldes `Data:`.

| Name | Hersteller | Lesen | Bytes | Angezeigte Felder | T5577 | EM4305 | Hitag Micro¹ | 8268² |
|---|---|---|---|---|---|---|---|---|
| EM4100 | EM-Micro | ASK/PSK | 5 | FC, Card, CL, DEZ 8, DEZ 10 | ✓ | ✓ | ✓ | ✓ |
| EM4100/32 | EM-Micro | ASK/PSK | 5 | dieselben (Bitrate RF/32) | ✓ | ✓ | ✓ | — |
| EM4100/16 | EM-Micro | ASK/PSK | 5 | dieselben (Bitrate RF/16) | ✓ | ✓ | ✓ | — |
| Electra | Electra | ASK/PSK | 8 | Epilogue | ✓ | ✓ | — | — |
| H10301 | HID | ASK | 3 | FC, Card (26-Bit-Wiegand) | ✓ | — | — | — |
| Idteck | IDTECK | PSK | 8 | FC, Card | ✓ | — | — | — |
| Indala26 | Motorola | PSK | 4 | FC, Card, Parity, Checksum | ✓ | — | — | — |
| Indala224 | Motorola | PSK | 28 | Raw | ✓ | — | — | — |
| IoProxXSF | Kantech | ASK | 4 | FC, Version, Card | ✓ | — | — | — |
| AWID | AWID | ASK | 9 | Format, FC, Card | ✓ | — | — | — |
| FDX-A | FECAVA | ASK | 5 | ID, Parity | ✓ | — | — | — |
| FDX-B | ISO | ASK | 11 | ID, Land, Temperatur, Tier-Flag… | ✓ | ✓ | — | — |
| HIDProx | Generic | ASK | 6 | Bitlänge; passende HID-Formate | ✓ | — | — | — |
| HIDExt | Generic | ASK | 12 | — | ✓ | — | — | — |
| Pyramid | Farpointe | ASK | 4 | Format, FC, Card | ✓ | — | — | — |
| Viking | Viking | ASK | 4 | ID | ✓ | ✓ | — | — |
| Jablotron | Jablotron | ASK | 5 | Card | ✓ | ✓ | — | — |
| Paradox | Paradox | ASK | 6 | FC, Card, CRC-Prüfung | ✓ | — | — | — |
| PAC/Stanley | — | ASK | 4 | CIN | ✓ | — | — | — |
| Keri | Keri | PSK | 4 | Internal ID, FC, Card | ✓ | — | — | — |
| Gallagher | Gallagher | ASK | 8 | FC, Card, Region, Issue Level | ✓ | ✓ | — | — |
| Nexwatch | Honeywell | PSK | 8 | ID, Mode, Type | ✓ | — | — | — |
| Radio Key | Securakey | ASK | 6 | RKKT n-Bit (FC, Card) oder RKKTH im Klartext (Card) | ✓ | ✓ | — | — |
| GProxII | Guardall | ASK | 12 | FC, Card, LEN, XOR, CRC | ✓ | ✓ | — | — |
| Noralsy | Noralsy | ASK | 12 | Card ID, Year | ✓ | — | — | — |

¹ Hitag Micro = die Ziele 8265/H5, 8210 und H5.5. ² 8268 (Hitag S) nimmt nur EM4100 mit der Rate RF/64 und ist
standardmäßig aus.

::: tip Unleashed
Gegenüber der Liste in der offiziellen Dokumentation ergänzt diese Firmware **Indala224** und einen Lesedurchgang bei
**134.2 kHz** für FDX-A/FDX-B. In der offiziellen Dateiformat-Dokumentation fehlen außerdem EM4100/32, EM4100/16,
Electra, Nexwatch, Radio Key, Noralsy und Indala224 — hier sind das gültige `Key type`-Werte.
:::

## Hinweise zu einzelnen Protokollen

- **EM4100 / EM-Marin** — der verbreitetste Anhängertyp in der GUS („ЕМ-Марин"). 40-Bit-ID; der FC steckt im
  3. Byte, die Kartennummer in den letzten beiden. DEZ 8 / DEZ 10 sind die auf Anhängern aufgedruckten Dezimalformen.
- **Casi-Rusco C10106** — kein eigenes Protokoll; es ist ein EM4100-Frame (meist RF/32). Passen die Daten, ergänzt
  der Info-Bildschirm eine Zeile `or C10106: credential card`, und Add Manually bietet es als Eingabeformat an.
- **HIDProx** — generischer HID-Prox-Container mit 26–37 Bit. Der Flipper probiert bekannte Layouts (H10304, H10302,
  S10401, H10306, Corp1000-35) und gibt für jede Übereinstimmung FC/Card aus.
- **Paradox** — der Info-Bildschirm zeigt die CRC und bei Abweichung *CRC Mismatch, Invalid Card!*.
- **Alter Name von Indala26** — sehr alte Dateien mit `Key type: I40134` werden beim Laden in Indala26 umgewandelt.

## Verwandte Seiten

- [Lesen](/de/rfid/read) · [Manuell anlegen](/de/rfid/add-manually) · [Schreiben](/de/rfid/write) ·
  [Tierchips](/de/rfid/animal-microchips) · [Dateiformat](/de/rfid/file-format)
