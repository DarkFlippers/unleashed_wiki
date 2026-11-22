---
title: Frekvencije i domet
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/lib/subghz/subghz_setting.c, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/frequencies]
sources: [unleashed-src, unleashed-docs, flipper-docs]
---
# Frekvencije i domet

Flipper Zero sa svijetom ispod 1 GHz komunicira putem primopredajnika **TI CC1101**.

## Hardverski pojasevi

Tehnički list za CC1101 definira tri pojasa:

| Pojas | Tipična upotreba |
|---|---|
| 300–348 MHz | Garažna vrata i ograde u SAD-u (obitelj 300, 310, 315, 318, 390 MHz), ključevi automobila |
| 387–464 MHz | Daljinski upravljači 433,92 MHz LPD433, rampe, senzori, zvonca (većina Europe/ZND-a) |
| 779–928 MHz | Uređaji na 868 MHz (EU SRD) i 915 MHz (US ISM) |

Unleashed blago proširuje zadani raspon odašiljanja kako bi radile i uobičajene frekvencije 350 MHz te 467,75 MHz.

## Ograničenja odašiljanja u Unleashedu

::: tip Unleashed
Tvornički firmver zaključava odašiljanje na frekvencije dopuštene u **regiji** otkrivenoj tijekom ažuriranja (npr. samo 433,05–434,79 i 868,15–868,55 MHz u EU/Rusiji). **Unleashed u potpunosti uklanja regionalno zaključavanje.** Možete odašiljati na bilo kojoj frekvenciji koju čip podržava, bez dodatnih koraka.
:::

Ono što i dalje vrijedi jest hardversko sigurnosno ograničenje (iz `furi_hal_subghz.c`):

| Način | Dopušteni TX rasponi |
|---|---|
| Zadani | 300–350 MHz, 387–467,75 MHz, 779–928 MHz |
| Prošireni ("opasni") | 281–361 MHz, 378–481 MHz, 749–962 MHz |

Ako pokušate odašiljati izvan dopuštenog raspona, Flipper odbija odašiljanje.

### Proširivanje raspona (opasno) {#extended-range}

::: danger
Odašiljanje izvan specifikacija čipa CC1101 može **oštetiti radijski čip**. Ni Flipperov tim ni programeri Unleasheda ne snose odgovornost za nastalu štetu. Ovo gotovo nikome nije potrebno — zadani raspon već pokriva praktički svaki stvarni daljinski upravljač.
:::

1. Povežite SD karticu s računalom (ili koristite qFlipper / upravitelj datoteka u mobilnoj aplikaciji).
2. Otvorite `/ext/subghz/assets/dangerous_settings`. Sadržaj izgleda ovako:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Promijenite `false` u `true`, spremite datoteku i ponovno pokrenite Flipper (postavka se učitava pri pokretanju).

Pogledajte i [Opasne postavke](/hr/start/dangerous-settings).

## Zadani popis frekvencija

Ovo su frekvencije kroz koje se možete kretati tipkama <kbd>←</kbd> <kbd>→</kbd> u **Read**, **Read RAW** → `Config` te one na koje Frequency Analyzer zaokružuje očitanje. **433,92 MHz** je zadana vrijednost.

| 300–350 MHz | 387–467,75 MHz | 779–928 MHz |
|---|---|---|
| 300.000, 302.757, 303.000, 303.875, 303.900, 304.250, 307.000, 307.500, 307.800, 309.000, 310.000, 312.000, 312.100, 312.200, 313.000, 313.850, 314.000, 314.350, 314.980, 315.000, 317.000, 318.000, 320.000, 320.150, 330.000, 336.100, 345.000, 348.000, 350.000 | 387.000, 390.000, 418.000, 430.000, 430.500, 431.000, 431.500, 433.075 (LPD433 početak), 433.220, 433.420, 433.657070, 433.889, **433.920** (LPD433 sredina, zadano), 434.075, 434.176948, 434.190, 434.390, 434.420, 434.620, 434.775 (LPD433 kraj), 438.900, 440.175, 462.750, 464.000, 467.750 | 779.000, 868.000, 868.350, 868.400, 868.460, 868.800, 868.950, 906.400, 915.000, 925.000, 928.000 |

### Popis za skakanje frekvencija (Hopping)

Kada je **Hopping** uključen, prijamnik prolazi samo kroz kratki popis (dugačak popis propuštao bi signale):

`315.00`, `390.00`, `430.50`, `433.92`, `434.42`, `868.35` MHz.

## Modulacije (predlošci)

Sama frekvencija nije dovoljna — Flipper nije SDR, već mu se modulacija mora zadati unaprijed. Ugrađeni predlošci:

| Naziv u izborniku | Predložak u `.sub` datoteci | Značenje |
|---|---|---|
| `AM270` | `FuriHalSubGhzPresetOok270Async` | OOK/ASK, širina pojasa 270 kHz |
| `AM650` | `FuriHalSubGhzPresetOok650Async` | OOK/ASK, širina pojasa 650 kHz — **zadano, koristi ga većina daljinskih upravljača** |
| `FM238` | `FuriHalSubGhzPreset2FSKDev238Async` | 2-FSK, devijacija 2,38 kHz |
| `FM476` | `FuriHalSubGhzPreset2FSKDev476Async` | 2-FSK, devijacija 47,6 kHz |
| `FM12K` | `FuriHalSubGhzPreset2FSKDev12KAsync` | 2-FSK, devijacija 12 kHz (npr. Cardin S449, Sommer) |

Možete dodati i vlastite predloške (primjerice `FM15k`, `Pagers`) — pogledajte [Formati datoteka](/hr/subghz/file-format#setting-user).

## Dodavanje vlastitih frekvencija {#adding-frequencies}

1. Na SD kartici otvorite `/ext/subghz/assets/`.
2. Preimenujte `setting_user.example` u `setting_user` (datoteke `_user` ostaju sačuvane nakon ažuriranja firmvera).
3. Dodajte retke u ovom formatu — uvijek s 9 znamenki, u Hz:
   ```text
   Frequency: 928000000
   Hopper_frequency: 345000000
   ```
4. Ponovno pokrenite aplikaciju Sub-GHz.

Pravila koja je dobro znati:

- Korisničke frekvencije **dodaju se na kraj** zadanog popisa — pomaknite se do kraja popisa da biste ih pronašli.
- `Hopper_frequency` dodaje frekvenciju u način skakanja (hopping). Neka popis za hopping bude kratak. Ponavljanje iste frekvencije čini da je Flipper sluša češće.
- Da biste koristili **samo** vlastite frekvencije, promijenite `#Add_standard_frequencies: true` u `Add_standard_frequencies: false`. Tada morate ispuniti **oba** popisa (`Frequency:` i `Hopper_frequency:`) — inače je glavni popis prazan.
- `Default_frequency: 433920000` postavlja početnu frekvenciju za Read i Read RAW.

## Rješavanje problema

- **Ništa se ne prima** — frekvencija ili modulacija su pogrešne. Pronađite frekvenciju pomoću alata [Frequency Analyzer](/hr/subghz/frequency-analyzer), zatim isprobajte `AM650`, pa FM predloške.
- **Moja frekvencija nije na popisu** — dodajte je u `setting_user` (gore). Analizator će i dalje zaokružiti na najbliži unos s popisa, pa točnu vrijednost ručno postavite u `Config`.
- **Odašiljanje odbijeno** — frekvencija je izvan zadanog TX raspona; provjerite gornju tablicu. Nemojte uključivati prošireni raspon samo za "probu".

## Povezano

- [Frequency Analyzer](/hr/subghz/frequency-analyzer) · [Read](/hr/subghz/read) · [Read RAW](/hr/subghz/read-raw)
- [Radijske postavke](/hr/subghz/settings) · [Formati datoteka](/hr/subghz/file-format) · [Vanjski CC1101](/hr/subghz/external-cc1101)
