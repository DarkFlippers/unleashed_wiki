---
title: Protokoli
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Podržani IR protokoli

Infracrvena biblioteka (`lib/infrared/encoder_decoder/`) sadrži dekoder i enkoder za svaki od dolje navedenih protokola. Signal koji odgovara jednom od njih sprema se kao `type: parsed` (protokol + adresa + naredba); sve ostalo sprema se kao `type: raw` i reproducira kao niz vremenskih trajanja. Popis i brojčani podatci na ovoj stranici preuzeti su iz izvornog koda firmvera.

::: tip Unleashed
**RCA** je dodatak firmvera Unleashed. Ostali su protokoli zajednički sa službenim firmverom.
:::

## Tablica protokola

| Protokol (vrijednost `protocol:`) | Obitelj | Bitovi adrese | Bitovi naredbe | Nositelj |
|---|---|---|---|---|
| `NEC` | NEC | 8 | 8 | 38 kHz |
| `NECext` | NEC (prošireni, bez invertiranih bajtova) | 16 | 16 | 38 kHz |
| `NEC42` | NEC 42-bitni | 13 | 8 | 38 kHz |
| `NEC42ext` | NEC 42-bitni prošireni | 26 | 16 | 38 kHz |
| `Samsung32` | Samsung | 8 | 8 | 38 kHz |
| `RC5` | Philips RC5 | 5 | 6 | 36 kHz |
| `RC5X` | Philips RC5 prošireni | 5 | 7 | 36 kHz |
| `RC6` | Philips RC6 | 8 | 8 | 36 kHz |
| `SIRC` | Sony SIRC 12-bitni | 5 | 7 | 40 kHz |
| `SIRC15` | Sony SIRC 15-bitni | 8 | 7 | 40 kHz |
| `SIRC20` | Sony SIRC 20-bitni | 13 | 7 | 40 kHz |
| `Kaseikyo` | Kaseikyo (Panasonic, Denon…) | 26 | 10 | 38 kHz |
| `RCA` | RCA | 4 | 8 | 38 kHz |
| `Pioneer` | Pioneer | 8 | 8 | 40 kHz |

Radni ciklus svih ugrađenih enkodera iznosi 33 %. Iste nazive prihvaća i CLI naredba `ir tx` (primjerice `ir tx NEC 0x04 0x08`), a moraju biti navedeni i u polju `protocol:` unutar `.ir` datoteke.

::: info Pioneer
Protokol `Pioneer` implementiran je u firmveru (i koristi se u bibliotekama za Audio i TV), iako ga popis u službenom dokumentu *InfraredFileFormats* još ne spominje.
:::

## Referenca vremenskih trajanja

Trajanja impulsa i pauza glavnih protokola, kako su definirana u enkoderima (µs). Tolerancija pri dekodiranju iznosi ±200 µs za preambulu i ±120 µs za bitove.

| Protokol | Preambula impuls / pauza | Bit 1 impuls / pauza | Bit 0 impuls / pauza |
|---|---|---|---|
| NEC (sve inačice) | 9000 / 4500 | 560 / 1690 | 560 / 560 |
| Samsung32 | 4500 / 4500 | 550 / 1650 | 550 / 550 |
| RCA | 4000 / 4000 | 500 / 2000 | 500 / 1000 |
| Pioneer | 8500 / 4225 | 500 / 1500 | 500 / 500 |
| SIRC | 2400 / 600 | 1200 / 600 | 600 / 600 |
| Kaseikyo | 3456 / 1728 (8 / 4 jedinice od 432) | 432 / 1296 | 432 / 432 |
| RC5 / RC5X | nema (Manchester) | 888 µs polubit | |
| RC6 | 2666 / 889 | 444 µs polubit (Manchester) | |

## Što ti brojevi znače za vas

- **Učenje:** ugrađeni prijamnik podešen je na 38 kHz, ali postoje dekoderi za protokole od 36 kHz (RC5, RC6) i 40 kHz (Sony SIRC, Pioneer), pa se i takvi daljinski upravljači uče kao parsirani signali.
- **Spremanje:** parsirani signal zauzima vrlo malo prostora i pouzdano se reproducira. Ako dekodirani signal ne radi na vašem uređaju, naučite ga kao RAW (debug način `Learn New Remote RAW`, pogledajte [Učenje signala](/hr/infrared/read#debug-mode-extras)).
- **Nepoznati daljinski upravljači** (većina daljinskih upravljača za klima-uređaje: 181 od 182 signala u `ac.ir` su RAW) uopće se ne parsiraju i uvijek se spremaju kao RAW. RAW signali mogu sadržavati do 1024 vremenskih trajanja; naučeni RAW zapisi obično se spremaju uz `frequency: 38000` i `duty_cycle: 0.330000`.

## Povezane stranice

- [Format IR datoteka](/hr/infrared/file-format)
- [Učenje i slanje signala](/hr/infrared/read)
- [Univerzalni daljinski upravljači](/hr/infrared/universal-remotes)
