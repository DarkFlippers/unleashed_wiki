---
title: Formati datoteka
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/LfRfidFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/T5577FileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-docs, unleashed-src]
---
# Formati datoteka za 125 kHz RFID

U mapi `/ext/lfrfid/` nalaze se tri vrste datoteka:

| Ekstenzija | Što opisuje | Stvara je |
|---|---|---|
| `.rfid` | **Karticu**: protokol + ID | Read → Save, Add Manually |
| `.t5577` | **Čip**: svaki blok čipa T5577 | [Aplikacija T5577](/hr/rfid/t5577-app) |
| `.ask.raw` / `.ask134.raw` / `.psk.raw` | Snimku sirovog signala | [RAW](/hr/rfid/raw) |

## `.rfid` — LF RFID ključ

```text
Filetype: Flipper RFID key
Version: 1
Key type: EM4100
Data: 01 23 45 67 89
```

Datoteka pohranjuje jedan ključ vrste navedene u polju `Key type`.

| Polje | Opis |
|---|---|
| `Key type` | Naziv protokola, točno kako je naveden u [tablici protokola](/hr/rfid/protocols) |
| `Data` | Podaci ključa u heksadekadskom zapisu; duljina je fiksna po protokolu |

Valjane vrijednosti za `Key type` u ovom firmveru: `EM4100`, `EM4100/32`, `EM4100/16`, `Electra`, `H10301`, `Idteck`,
`Indala26`, `Indala224`, `IoProxXSF`, `AWID`, `FDX-A`, `FDX-B`, `HIDProx`, `HIDExt`, `Pyramid`, `Viking`,
`Jablotron`, `Paradox`, `PAC/Stanley`, `Keri`, `Gallagher`, `Nexwatch`, `Radio Key`, `GProxII`, `Noralsy`.

Povijest verzija: 1 — početna verzija. Starije datoteke s `Key type: I40134` (3 bajta) pretvaraju se u `Indala26` pri
učitavanju.

::: tip
Ključ možete izraditi na računalu: napišite gornja četiri retka s ispravnim `Key type` i točnim brojem
bajtova u `Data`, kopirajte datoteku u `/ext/lfrfid/` i pojavit će se u **Saved**.
:::

## `.t5577` — T5577 dump

```text
Filetype: Flipper T5577 dump
Version: 1
# Block 0: ASK/Manchester, RF/64, 2 data blocks, password enabled
Page 0 blocks read: 0 1 2 7
Page 0 Block 0: 00 14 80 50
Page 0 Block 1: 12 34 56 78
Page 0 Block 2: 9A BC DE F0
Page 0 Block 3: 00 00 00 00
Page 0 Block 4: 00 00 00 00
Page 0 Block 5: 00 00 00 00
Page 0 Block 6: 00 00 00 00
Page 0 Block 7: 0C 0D 0E 0F
Page 1 blocks read: 0 1
Page 1 Block 0: E0 15 00 1A
Page 1 Block 1: 20 24 10 00
Page 1 Block 2: 00 00 00 00
Page 1 Block 3: 00 00 00 00
Password: 0C 0D 0E 0F
```

Datoteka `.t5577` opisuje **sam čip**, dok `.rfid` datoteka opisuje **karticu**. T5577 konfiguriran kao EM4100 može
se spremiti na oba načina, ali ta dva formata nisu zamjenjiva: `.t5577` sadrži konfiguraciju koja određuje kako čip
komunicira i lozinku koja ga štiti.

| Polje | Opis |
|---|---|
| `Page 0 blocks read` | Blokovi stranice 0 čije su vrijednosti pročitane s čipa, odvojeni razmakom |
| `Page 0 Block 0..7` | Sadržaj bloka, 4 heksadekadska bajta, MSB prvi. Blok 0 = konfiguracija, blok 7 = pohrana lozinke |
| `Page 1 blocks read` | Blokovi stranice 1 koji su pročitani |
| `Page 1 Block 0..3` | Blok 0 ponavlja konfiguraciju; blokovi 1–3 sadrže tvorničke podatke o sljedivosti |
| `Password` | Neobvezno. Lozinka za koju je **poznato da radi** na čipu |

Ključna pravila:

- **Svaki blok ima ključ**, bio pročitan ili ne. Samo su blokovi navedeni u `blocks read` stvarni sadržaj; ostatak je ispuna i
  nikada se ne smije zapisati na oznaku. Datoteka koja ne navodi nijedan blok odbacuje se.
- Zaštićeni čip odbija čitanje bloka 0 koje je potrebno za detekciju, pa bez lozinke ne dobivate nikakav dump
  (čak ni djelomičan). Djelomičan dump znači da je oznaka izašla iz polja tijekom čitanja.
- `Password` i `Page 0 Block 7` su različite činjenice i mogu se razlikovati: blok 7 je ono što je blok sadržavao u trenutku
  čitanja (obična pohrana ako lozinka nije uključena), a `Password` je vjerodajnica koja je radila. Brisanje lozinke samo
  poništava bit u bloku 0, pa blok 7 zadržava staru vrijednost.
- Redak komentara koji dekodira blok 0 služi samo ljudima za čitanje.

### Redoslijed vraćanja

Prilikom pisanja dumpa natrag (aplikacija T5577 → **Write to Tag**), redoslijed odgovara Proxmarku3:

1. Stranica 0, blokovi 1–7. Od bloka 7 nadalje pisanje mora koristiti lozinku koja je sada spremljena u bloku 7.
2. Stranica 1, blokovi 1–3 (blok 0 stranice 1 nikada se ne zapisuje). Originalni čipovi odbijaju promjenu blokova 1–2 — to se prijavljuje kao
   *unchanged* (nepromijenjeno), a ne kao pogreška.
3. Stranica 0, blok 0 **zadnji** — on mijenja način na koji čip komunicira.
4. Zapisuju se samo blokovi navedeni u `blocks read`.
5. Blok 0 s vrijednošću nula **nikada** se ne zapisuje: čip koji ga sadrži ne odgovara ni na što i nema povratka.

Okviri za pisanje ne dobivaju odgovor, pa je uspjeh poznat tek ponovnim čitanjem blokova.

## `.raw` — RAW snimke

Binarne datoteke koje stvara RAW čitanje. Počinju zaglavljem:

| Polje | Tip | Vrijednost |
|---|---|---|
| magic | uint32 | `0x4C464952` |
| version | uint32 | `1` |
| frequency | float | frekvencija nositelja, Hz (125000 ili 134200) |
| duty_cycle | float | radni ciklus (duty cycle) nositelja |
| max_buffer_size | uint32 | najveći međuspremnik u datoteci |

nakon čega slijede međuspremnici, svaki s prefiksom svoje veličine, koji sadrže varint-kodirane parove *(puls, trajanje)*. Koristite `rfid raw_analyze <filename>` u CLI-ju za
njihovo dekodiranje.

## Povezano

- [Protokoli](/hr/rfid/protocols) · [Aplikacija T5577](/hr/rfid/t5577-app) · [RAW](/hr/rfid/raw)
