---
title: Protokolle
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Unterstützte IR-Protokolle

Die Infrarot-Bibliothek (`lib/infrared/encoder_decoder/`) enthält für jedes Protokoll unten einen Decoder und einen
Encoder. Ein Signal, das zu einem davon passt, wird als `type: parsed` gespeichert (Protokoll + Adresse + Befehl);
alles andere landet als `type: raw` und wird als Zeitwerte wiedergegeben. Liste und Zahlen auf dieser Seite stammen
aus dem Firmware-Quellcode.

::: tip Unleashed
**RCA** ist eine Ergänzung von Unleashed. Die übrigen Protokolle sind mit der offiziellen Firmware identisch.
:::

## Protokolltabelle

| Protokoll (Wert von `protocol:`) | Familie | Adressbits | Befehlsbits | Träger |
|---|---|---|---|---|
| `NEC` | NEC | 8 | 8 | 38 kHz |
| `NECext` | NEC (erweitert, ohne invertierte Bytes) | 16 | 16 | 38 kHz |
| `NEC42` | NEC 42 Bit | 13 | 8 | 38 kHz |
| `NEC42ext` | NEC 42 Bit erweitert | 26 | 16 | 38 kHz |
| `Samsung32` | Samsung | 8 | 8 | 38 kHz |
| `RC5` | Philips RC5 | 5 | 6 | 36 kHz |
| `RC5X` | Philips RC5 erweitert | 5 | 7 | 36 kHz |
| `RC6` | Philips RC6 | 8 | 8 | 36 kHz |
| `SIRC` | Sony SIRC 12 Bit | 5 | 7 | 40 kHz |
| `SIRC15` | Sony SIRC 15 Bit | 8 | 7 | 40 kHz |
| `SIRC20` | Sony SIRC 20 Bit | 13 | 7 | 40 kHz |
| `Kaseikyo` | Kaseikyo (Panasonic, Denon …) | 26 | 10 | 38 kHz |
| `RCA` | RCA | 4 | 8 | 38 kHz |
| `Pioneer` | Pioneer | 8 | 8 | 40 kHz |

Der Duty-Cycle aller eingebauten Encoder ist 33 %. Dieselben Namen nimmt der CLI-Befehl `ir tx` an (etwa
`ir tx NEC 0x04 0x08`), und genau sie müssen in einer `.ir`-Datei bei `protocol:` stehen.

::: info Pioneer
Das Protokoll `Pioneer` ist in der Firmware implementiert (und wird in den Audio- und TV-Bibliotheken genutzt), auch
wenn die Liste im offiziellen Dokument *InfraredFileFormats* es noch nicht erwähnt.
:::

## Timing-Referenz

Puls-/Pausen-Zeiten der wichtigsten Protokolle, wie in den Encodern definiert (µs). Die Toleranz beim Dekodieren
beträgt ±200 µs auf die Präambel und ±120 µs auf die Bits.

| Protokoll | Präambel Mark / Space | Bit 1 Mark / Space | Bit 0 Mark / Space |
|---|---|---|---|
| NEC (alle Varianten) | 9000 / 4500 | 560 / 1690 | 560 / 560 |
| Samsung32 | 4500 / 4500 | 550 / 1650 | 550 / 550 |
| RCA | 4000 / 4000 | 500 / 2000 | 500 / 1000 |
| Pioneer | 8500 / 4225 | 500 / 1500 | 500 / 500 |
| SIRC | 2400 / 600 | 1200 / 600 | 600 / 600 |
| Kaseikyo | 3456 / 1728 (8 / 4 Einheiten von 432) | 432 / 1296 | 432 / 432 |
| RC5 / RC5X | keine (Manchester) | 888 µs Halbbit | |
| RC6 | 2666 / 889 | 444 µs Halbbit (Manchester) | |

## Was die Zahlen für dich bedeuten

- **Anlernen:** der eingebaute Empfänger ist auf 38 kHz abgestimmt, aber die Decoder für die Protokolle mit 36 kHz
  (RC5, RC6) und 40 kHz (Sony SIRC, Pioneer) sind vorhanden — solche Fernbedienungen werden also ebenfalls als
  geparste Signale angelernt.
- **Speichern:** ein geparstes Signal ist winzig und robust. Funktioniert ein dekodiertes Signal an deinem Gerät
  nicht, lerne es als RAW an (Debug-Modus `Learn New Remote RAW`, siehe
  [Anlernen](/de/infrared/read#debug-mode-extras)).
- **Unbekannte Fernbedienungen** (die meisten Klimaanlagen-Fernbedienungen: 181 der 182 Signale in `ac.ir` sind RAW)
  werden überhaupt nicht geparst und immer als RAW gespeichert. RAW-Signale fassen bis zu 1024 Zeitwerte; angelernte
  RAW-Aufnahmen werden normalerweise mit `frequency: 38000` und `duty_cycle: 0.330000` gespeichert.

## Verwandte Seiten

- [IR-Dateiformat](/de/infrared/file-format)
- [Signale anlernen und senden](/de/infrared/read)
- [Universalfernbedienungen](/de/infrared/universal-remotes)
