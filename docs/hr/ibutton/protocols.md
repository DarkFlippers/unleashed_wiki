---
title: Podržani protokoli
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks, https://docs.flipper.net/zero/ibutton/read, https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Podržani iButton protokoli

Izgrađeno iz mape `lib/ibutton/protocols/` firmvera Unleashed. Firmver razvrstava protokole u **Dallas** (1-Wire)
i **razno** (Cyfral, Metakom).

| Protokol (naziv datoteke) | Oznaka u izborniku | Obiteljski kôd | Memorija | Emulacija | Pisanje ID-a na | Potpuno pisanje na istu vrstu |
|---|---|---|---|---|---|---|
| `DS1990` | Dallas DS1990 | `01` | — | ✓ | RW1990.1, RW1990.2, TM2004, TM01x | — |
| `DS1420` | Dallas DS1420 | `81` | — | ✓ | RW1990.1, RW1990.2, TM2004 | — |
| `DS1992` | Dallas DS1992 | `08` | 128 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1996` | Dallas DS1996 | `0C` | 8192 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1971` | Dallas DS1971 | `14` | 32 B EEPROM (`Eeprom Data`) | ✓ | TM2004 | ✓ |
| `(non-specific)` | Dallas (non-specific) | bilo koji | — (samo ROM) | ✓ | TM2004 | — |
| `Cyfral` | Cyfral | — | 2-bajtni kôd | ✓ | TM01x | — |
| `Metakom` | Metakom | — | 4-bajtni kôd | ✓ | TM01x | — |

## Dallas 1-Wire

Dallas Semiconductor (danas Analog Devices) "dodirna memorija". Svaki uređaj ima 8-bajtni ROM: obiteljski kôd, 48-bitni serijski broj
i CRC-8. Flipper provjerava CRC i prepoznaje vrstu prema obiteljskom kodu.

- **DS1990 (DS1990A)** — klasični ključ samo s ID-om koji koristi većina portafona.
- **DS1420** — potpuno kompatibilan s DS1990, razlikuje se samo obiteljski kôd (`81` umjesto `01`).
- **DS1992 / DS1996** — memorijski ključevi sa SRAM-om; DS1971 — s EEPROM-om. Flipper čita memoriju, može je prikazati
  (**Data Info**), emulirati je i kopirati na ključ iste vrste.
- **Dallas (non-specific)** — univerzalna opcija za bilo koji drugi 1-Wire uređaj: čita se samo ROM, ništa se ne provjerava. Također
  korisno za izradu ključa s namjerno pogrešnim obiteljskim kodom ili CRC-om.

## Cyfral

Protokol ključeva za portafone uobičajen u Rusiji i ZND-u; nije 1-Wire. Kôd je pohranjen u 2 bajta. Može se emulirati i zapisati na TM01x prazni ključ.

## Metakom

Još jedan portafonski protokol iz ZND-a. Kôd ima 4 bajta, a svaki bajt nosi bit parnosti — ključ s pogrešnom parnošću
prijavljuje se kao neispravan i ne zapisuje se. Može se emulirati i zapisati na TM01x prazni ključ.

## Prazni ključevi (Blanks)

| Prazni ključ | Prihvaća | Ponašanje |
|---|---|---|
| **RW1990.1** | Dallas ROM (8 bajtova) | Otključava, zapisuje (invertirani bitovi), zaključava |
| **RW1990.2** | Dallas ROM (8 bajtova) | Otključava, zapisuje, zaključava |
| **TM2004** | Dallas ROM (8 bajtova) | Zapisuje od adrese 0 uz povratnu provjeru čitanjem svakog bajta |
| **TM01x** | Dallas ROM, Cyfral, Metakom | Cyfral/Metakom se zapisuju kao 36-bitni okvir (4-bitni prefiks + 32 bita koda), provjeravaju, zatim **finaliziraju** (jednosmjerno). Dallas ID-ovi se ne finaliziraju |

Pogledajte [Pisanje](/hr/ibutton/write) za upute o korištenju.

::: tip Unleashed
Službena dokumentacija ne navodi DS1420, postavku Write Blanks niti TM01x pisanje za Cyfral/Metakom.
:::

## Povezano

- [Čitanje](/hr/ibutton/read) · [Pisanje](/hr/ibutton/write) · [Format datoteke](/hr/ibutton/file-format)
