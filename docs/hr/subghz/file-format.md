---
title: Formati datoteka
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/resources/subghz/assets, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md]
sources: [unleashed-docs, unleashed-src]
---
# Sub-GHz formati datoteka

Sub-GHz datoteke — datoteke signala (`.sub`) i konfiguracijske datoteke u `/ext/subghz/assets/` — su običan tekst u formatu *Flipper File Format* (retci `Ključ: vrijednost`), pa ih možete pregledavati i uređivati na računalu.

| Putanja | Što sadrži |
|---|---|
| `/ext/subghz/*.sub` | Spremljeni signali: ključevi, RAW i BinRAW |
| `/ext/subghz/assets/setting_user` | Vaše frekvencije, popis za preskakanje (hopper), prilagođeni predlošci |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Vaši KeeLoq ključevi proizvođača |
| `/ext/subghz/assets/keeloq_mfcodes` | Ugrađeni KeeLoq ključevi proizvođača (šifrirani, isporučuju se s firmverom) |
| `/ext/subghz/assets/nice_flor_s`, `alutech_at_4n` | Ugrađene tablice za te protokole |
| `/ext/subghz/assets/dangerous_settings` | Prekidač za prošireni frekvencijski raspon, pogledajte [Frekvencije](/hr/subghz/frequencies#extended-range) |

## Struktura `.sub` datoteke

`.sub` datoteka ima tri dijela:

1. **Zaglavlje (Header)** — vrsta datoteke, verzija, frekvencija.
2. **Predložak (Preset)** — predložak modulacije ili potpuna prilagođena konfiguracija CC1101.
3. **Podaci (Data)** — naziv protokola i njegova polja ili RAW vremena.

### Zaglavlje

| Polje | Tip | Opis |
|---|---|---|
| `Filetype` | string | `Flipper SubGhz Key File` za ključeve, `Flipper SubGhz RAW File` za RAW snimke |
| `Version` | uint | Verzija formata datoteke, trenutno `1` |
| `Frequency` | uint | Frekvencija u Hz, npr. `433920000` |

### Predložak (Preset)

| Polje | Opis |
|---|---|
| `Preset` | Naziv predloška. Za prilagođeni predložak mora biti `FuriHalSubGhzPresetCustom` |
| `Custom_preset_module` | Primopredajnik, `CC1101` za Flipper Zero (samo za prilagođeni predložak) |
| `Custom_preset_data` | Konfiguracija primopredajnika (samo za prilagođeni predložak) |

Ugrađeni predlošci:

| Vrijednost `Preset` | Naziv u izborniku | Značenje |
|---|---|---|
| `FuriHalSubGhzPresetOok270Async` | `AM270` | OOK, širina pojasa 270 kHz |
| `FuriHalSubGhzPresetOok650Async` | `AM650` | OOK, širina pojasa 650 kHz |
| `FuriHalSubGhzPreset2FSKDev238Async` | `FM238` | 2-FSK, devijacija 2,38 kHz, širina pojasa 270 kHz |
| `FuriHalSubGhzPreset2FSKDev12KAsync` | `FM12K` | 2-FSK, devijacija 12 kHz |
| `FuriHalSubGhzPreset2FSKDev476Async` | `FM476` | 2-FSK, devijacija 47,6 kHz, širina pojasa 270 kHz |

Prilagođeni predložak ugrađen je u datoteku, pa ga drugi Flipper može poslati čak i ako taj predložak nema u svojim postavkama.

#### Podaci prilagođenog predloška {#custom-preset-data}

Heksadekadski bajtovi odvojeni razmacima: `XX YY XX YY … 00 00 ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ`

- `XX` — adresa registra CC1101, `YY` — vrijednost registra (onoliko parova koliko je potrebno);
- `00 00` — kraj bloka registara;
- `ZZ ×8` — 8-bajtna PA tablica (krivulja pojačala snage).

Značenja registara potražite u [podatkovnom listu CC1101](https://www.ti.com/lit/ds/symlink/cc1101.pdf).

### Datoteke ključeva (Key files)

Dekodirani signali pohranjuju naziv protokola i njegova polja:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

| Polje | Opis |
|---|---|
| `Protocol` | Naziv protokola točno kao u registru protokola (npr. `Princeton`, `KeeLoq`, `Nice FloR-S`, `CAME Atomo`, `Security+ 2.0`) |
| `Bit` | Duljina korisnog tereta (payload) u bitovima |
| `Key` | Korisni teret, hex, 8 bajtova |
| `TE` | Trajanje osnovnog impulsa (interval kvantizacije) u µs, za protokole koji ga pohranjuju |

Protokoli mogu dodavati vlastita polja. Ona koja ćete susresti u firmveru Unleashed:

| Polje | Koristi ga | Značenje |
|---|---|---|
| `Manufacture` | KeeLoq, FAAC SLH / Genius | Proizvođač čiji ključ dekodira signal (npr. `DoorHan`, `BFT`, `Genius`) |
| `Seed` | BFT Mitto, Erreka, FAAC SLH, Genius, neki KeeLoq | Tajna vrijednost pojedinog daljinskog upravljača za sigurno učenje |
| `CounterMode` | Nice Flor-S, CAME Atomo, Alutech AT-4N, KeeLoq, V2 Phoenix | Eksperimentalno ponašanje brojača, pogledajte [Načini brojača](/hr/subghz/counter-mode) |
| `Secplus_packet_1`, `Pin` | Security+ 2.0 | Drugi paket; PIN tipkovnice za 86-bitne okvire signala ([Security+ PIN](/hr/subghz/secplus-pin)) |
| `Cert` | Nice O-Code | Certifikat prijemnika ([Nice O-Code](/hr/subghz/nice-o-code)) |

Primjer s prilagođenim predloškom:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetCustom
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

::: warning Uređivanje datoteka s promjenjivim kodom
Ručna promjena polja `Key` dinamičkog protokola rijetko daje valjan kod. Za promjenu serijskog broja, tipke ili brojača koristite [Add Manually [Advanced]](/hr/subghz/add-manually) ili, u načinu Debug, `Saved → file → Signal Settings`.
:::

### RAW datoteke

Snimke iz načina [Read RAW](/hr/subghz/read-raw):

```text
Filetype: Flipper SubGhz RAW File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: RAW
RAW_Data: 29262 361 -68 2635 -66 24113 -66 11 ...
RAW_Data: -424 205 -412 159 -412 381 -240 181 ...
```

- `Protocol` mora biti `RAW`.
- `RAW_Data` — trajanja u µs: pozitivno = nositelj uključen, negativno = nositelj isključen. Vrijednosti moraju biti različite od nule, početi pozitivnim brojem i izmjenjivati predznak. Do 512 vrijednosti po retku; redak se može ponavljati koliko god puta je potrebno.

Dugi korisni tereti čitaju se sa SD kartice tijekom odašiljanja. Uz vrlo kratka vremena (ispod 10 µs) spora kartica možda neće moći pratiti pa će se odašiljanje zaustaviti prije kraja.

### BinRAW datoteke

`Bin RAW` u `Read → Config` stvara **BinRAW** datoteke. Za razliku od RAW-a, one pohranjuju samo koristan ponavljajući slijed, s obnovljenom brzinom prijenosa i bez šuma, pa mogu ponovno reproducirati gotovo svaki **statični** protokol, poznat ili nepoznat. Pri čitanju držite tipku daljinskog upravljača malo dulje kako bi se prikupilo dovoljno podataka.

| Polje | Opis |
|---|---|
| `Protocol` | `BinRAW` |
| `Bit` | Duljina korisnog tereta cijele datoteke u bitovima (najviše 4096) |
| `TE` | Interval kvantizacije, µs |
| `Bit_RAW` | Duljina sljedećeg bloka `Data_RAW`, u bitovima |
| `Data_RAW` | Kodirana trajanja: svaki bit = jedan `TE`; `1` = nositelj, `0` = bez nositelja |

Primjer: `TE: 100`, `Bit_RAW: 8`, `Data_RAW: 37` → `0b00110111` → šalje `-200 200 -100 300`.
Parovi `Bit_RAW` + `Data_RAW` tvore ponovljene blokove; više blokova šalje se jedan za drugim.

```text
Protocol: BinRAW
Bit: 1572
TE: 597
Bit_RAW: 260
Data_RAW: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F 4A B5 55 4C B3 52 AC D5 2D 53 52 AD 4A D5 35 00
```

## `setting_user` {#setting-user}

Dodatne frekvencije i predlošci koji se učitavaju pri pokretanju aplikacije Sub-GHz. Preimenujte `setting_user.example` u `setting_user`.

```text
Filetype: Flipper SubGhz Setting File
Version: 1

# Add standard frequencies included with firmware and place user frequencies after them
Add_standard_frequencies: true

# Default frequency for "Read" and "Read Raw"
Default_frequency: 433920000

# Frequencies for "Read", "Read Raw" and "Frequency Analyzer"
Frequency: 300000000
Frequency: 310000000

# Frequencies for hopping mode (keep this list small)
Hopper_frequency: 300000000
Hopper_frequency: 310000000

# Custom preset
Custom_preset_name: AM_1
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
```

| Ključ | Značenje |
|---|---|
| `Add_standard_frequencies` | `true` — popis iz firmvera + vaše frekvencije (dodane nakon njega); `false` — samo vaše (tada popunite i `Frequency` i `Hopper_frequency`) |
| `Default_frequency` | Frekvencija s kojom počinju Read / Read RAW |
| `Frequency` | Dodaje frekvenciju na glavni popis (9 znamenaka, Hz). Može se ponavljati |
| `Hopper_frequency` | Dodaje frekvenciju u način preskakanja (hopping). Ponavljanje iste frekvencije čini da je Flipper sluša češće |
| `Custom_preset_name` / `_module` / `_data` | Prilagođeni predložak modulacije, prikazuje se u popisu `Modulation` pod tim nazivom. Format podataka: [iznad](#custom-preset-data) |

Datoteka `.example` sadrži zakomentirane predloške koje možete omogućiti: `FM95`, `FM15k` (2-FSK, širina pojasa 200 kHz / filtar 135 kHz, devijacija 15,86 kHz), `Pagers`, `AM_1`, `AM_2`.

## `keeloq_mfcodes_user` {#keeloq-mfcodes-user}

Vaši vlastiti KeeLoq ključevi proizvođača, učitani pri pokretanju aplikacije uz ugrađenu (šifriranu) bazu podataka. Izradite je iz `keeloq_mfcodes_user.example`, uklonite ogledne ključeve i **ostavite prazan redak na kraju**.

```text
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:2:Test2
```

Svaki redak je oblika `KEY:METHOD:NAME`:

- `KEY` — 64-bitni ključ proizvođača, 16 hex znamenaka;
- `NAME` — naziv bez razmaka, do 64 znaka (prikazuje se kao proizvođač u načinu Read);
- `METHOD` — vrsta učenja:

| Vrijednost | Učenje |
|---|---|
| `0` | pokušaj sve: isprobava prethodni i ključ proizvođača u izravnom i obrnutom poretku bajtova |
| `1` | Simple Learning |
| `2` | Normal Learning |
| `3` | Secure Learning (zahtijeva Seed) |
| `4` | Magic XOR type 1 |
| `5` | FAAC SLH |
| `6` | Magic Serial type 1 |
| `7` | Magic Serial type 2 |
| `8` | Magic Serial type 3 |

`Encryption: 0` znači da je datoteka običan tekst — korisničke datoteke ne smiju biti šifrirane. Više o vrstama učenja: [KeeLoq](/hr/subghz/keeloq).

## Povezano

- [Read](/hr/subghz/read) · [Read RAW](/hr/subghz/read-raw) · [Frekvencije](/hr/subghz/frequencies) · [Postavke radija](/hr/subghz/settings)
- [KeeLoq](/hr/subghz/keeloq) · [Načini brojača](/hr/subghz/counter-mode) · [Datoteke mapiranja za Sub-GHz Remote](/hr/subghz/remote)
