---
title: Format datoteke
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-docs, unleashed-src]
---
# Format datoteke iButton ključa (`.ibtn`)

Spremljeni ključevi pohranjuju se u `/ext/ibutton/` s nastavkom `.ibtn`. Jedna datoteka sadrži jedan ključ sa svim podacima koje
njegov protokol treba.

## Primjer

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1992
Rom Data: 08 DE AD BE EF FA CE 4E
Sram Data: 4E 65 76 65 72 47 6F 6E 6E 61 47 69 76 65 59 6F 75 55 70 4E 65 76 65 72 47 6F 6E 6E 61 4C 65 74 59 6F 75 44 6F 77 6E 4E 65 76 65 72 47 6F 6E 6E 61 52 75 6E 41 72 6F 75 6E 64 41 6E 64 44 65 73 65 72 74 59 6F 75 4E 65 76 65 72 47 6F 6E 6E 61 4D 61 6B 65 59 6F 75 43 72 79 4E 65 76 65 72 47 6F 6E 6E 61 53 61 79 47 6F 6F 64 62 79 65 4E 65 76 65 72 47 6F 6E 6E 61 54 65 6C 6C 41 4C 69 65
```

Ključ DS1990 (bajtovi su primjer; pravi ROM završava valjanim CRC-om):

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1990
Rom Data: 01 23 45 67 89 AB CD EF
```

Ključ Cyfral:

```text
Filetype: Flipper iButton key
Version: 2
Protocol: Cyfral
Data: A1 B2
```

## Verzija 2 (aktualna)

Polja nakon `Protocol` ovise o protokolu.

| Polje | Tip | Opis |
|---|---|---|
| `Protocol` | string | `DS1990`, `DS1992`, `DS1996`, `DS1971`, `DS1420`, `(non-specific)`, `Cyfral`, `Metakom` |
| `Rom Data` | hex | 8-bajtni ROM (samo Dallas protokoli) |
| `Sram Data` | hex | Sadržaj SRAM memorije (DS1992: 128 bajtova, DS1996: 8192 bajta) |
| `Eeprom Data` | hex | Sadržaj EEPROM memorije (DS1971: 32 bajta) |
| `Data` | hex | Kod ključa (Cyfral: 2 bajta, Metakom: 4 bajta) |

Napomene:
- **(non-specific)** je opća kategorija za nepoznate 1-Wire uređaje (oznaka u izborniku *Dallas (non-specific)*). Sadrži samo
  ROM i ne provodi nikakve provjere — koristite je za ključeve s namjerno nevaljanim kodom obitelji (family code) ili CRC-om. Firmver je sprema
  kao `Protocol: (non-specific)`; naziv `DSGeneric` koji koristi službena dokumentacija i starije datoteke i dalje se prihvaća.
- **DS1420** je u potpunosti kompatibilan s DS1990; razlikuje se samo kod obitelji (`0x81` u odnosu na `0x01`).
- Novi protokoli ne zahtijevaju povećanje verzije formata — svaki protokol definira vlastita polja.

## Verzija 1 (zastarjela)

```text
Filetype: Flipper iButton key
Version: 1
Key type: Dallas
Data: 01 23 45 67 89 AB CD EF
```

| Polje | Tip | Opis |
|---|---|---|
| `Key type` | string | `Cyfral`, `Dallas`, `Metakom` |
| `Data` | hex | Podaci ključa |

Datoteke verzije 1 i dalje se učitavaju (`Dallas` se čita kao DS1990) te se pretvaraju u verziju 2 kada ih
spremite.

## Povezano

- [Protokoli](/hr/ibutton/protocols) · [Ručno dodavanje](/hr/ibutton/add-manually) · [Čitanje](/hr/ibutton/read)
