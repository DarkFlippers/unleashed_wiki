---
title: Multi Converter
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MultiConverter.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Multi Converter

**Multi Converter** autora [theisolinearchip](https://github.com/theisolinearchip/flipperzero_stuff/tree/main/applications/multi_converter)
je pretvarač jedinica: upišete vrijednost u jednoj jedinici i vidite je u drugoj. Nastao je iz autorova ranijeg pretvarača Dec/Hex Converter.

::: tip Unleashed
Multi Converter dolazi s paketima aplikacija zajednice ([paketi aplikacija](/hr/apps/catalog#base-and-extra-packs)), a ne sa samim firmverom.
:::

![Multi Converter](/img/remote/283b5cf67616cbaa.png)

## Podržane pretvorbe

| Grupa | Jedinice |
|---|---|
| Brojevni sustavi | Dekadski, heksadekadski, binarni |
| Temperatura | Celzij, Fahrenheit, Kelvin |
| Duljina | Kilometri, metri, centimetri, milje, stope, inči |
| Kut | Stupanj, radijan |

## Način prikaza (unos vrijednosti)

Zaslonska tipkovnica ima tipke od `0` do `F`. Tipke koje nemaju smisla za trenutačnu izvornu jedinicu su onemogućene
(primjerice `2`-`F` za binarni sustav).

| Tipka | Radnja |
|---|---|
| `0`-`F` | unos znamenke |
| dugi pritisak `0` | uključivanje/isključivanje **negativne** vrijednosti |
| dugi pritisak `1` | umetanje **decimalne točke** (samo ako jedinica to dopušta) |
| `<` | brisanje zadnjeg znaka |
| `#` | otvaranje **načina odabira jedinica (Unit Select Mode)** |

Krećite se po tipkovnici strelicama i pritisnite <kbd>OK</kbd> na željenoj tipki. Rezultat u odredišnoj jedinici prikazuje se
na zaslonu.

![Odabir jedinice](/img/remote/bedbc21af3d64be7.png)

## Način odabira jedinica (Unit Select Mode)

1. Pritisnite `#`.
2. Tipkama <kbd>←</kbd> / <kbd>→</kbd> prebacujete između **izvorne** i **odredišne** jedinice. Popis odredišnih jedinica ovisi o
   izvornoj koju ste odabrali (možete pretvarati samo unutar iste grupe).
3. <kbd>OK</kbd> sprema odabir i vraća u način prikaza; <kbd>Back</kbd> vraća bez promjene jedinica.

## Poznata ograničenja

- Vrlo velike pretvorbe (primjerice milje u centimetre i slično) mogu pokazati manja decimalna odstupanja zbog ograničenja preciznosti.
- Provjere preljeva su osnovne: vrlo dugi brojevi možda neće stati u međuspremnik zaslona.
- Oznake za dugi pritisak za negativan predznak i decimalnu točku sitne su na zaslonu i lako ih je previdjeti.

## Dodavanje jedinica (za programere)

1. Dodajte jedinicu u enum `MultiConverterUnitType` u datoteci `multi_converter_definitions.h` (vrijednosti enuma su indeksi polja).
2. Povećajte `MULTI_CONVERTER_AVAILABLE_UNITS` u `multi_converter_units.h`.
3. Napišite funkciju za pretvorbu (**convert**) i provjeru dopuštenosti (**allowed**, tj. može li se ova jedinica pretvoriti u onu drugu) u
   `multi_converter_units.h` / `.c`.
4. Dodajte strukturu `MultiConverterUnit` za novu jedinicu.
5. Dodajte je u polje `multi_converter_available_units`. Aplikacija će je automatski prepoznati.

## Povezane stranice

- [Aplikacije koje dolaze uz Unleashed](/hr/apps/catalog)
- [Generator barkodova](/hr/apps/barcode)
