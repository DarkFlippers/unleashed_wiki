---
title: Format IR datoteka
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared]
sources: [unleashed-docs, unleashed-src]
---
# Format infracrvenih datoteka (`.ir`)

Svi IR podaci na Flipperu pohranjeni su kao običan tekst u Flipper Formatu (retci `key: value`). Nastavak je
uvijek `.ir`. Postoje tri varijante koje se razlikuju samo po zaglavlju `Filetype` i po tome za što se koriste.

| Filetype | Koristi se za | Lokacija |
|---|---|---|
| `IR signals file` | Vaši daljinski upravljači (naučeni, spremljeni iz univerzalnog daljinskog upravljača, preuzeti iz aplikacije) | `/ext/infrared/` |
| `IR library file` | Biblioteke univerzalnih daljinskih upravljača | `/ext/infrared/assets/` |
| testna datoteka (`.irtest`) | Jedinični testovi dekodera/enkodera | samo repozitorij firmvera |

## Datoteka daljinskog upravljača

### Primjer

```text
Filetype: IR signals file
Version: 1
#
name: Button_1
type: parsed
protocol: NECext
address: EE 87 00 00
command: 5D A0 00 00
#
name: Button_2
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 504 3432 502 483 500 484 510 502 502 482 501 485 509 1452 504 1458 509 1452 504 481 501 474 509 3420 503
#
name: Button_3
type: parsed
protocol: SIRC
address: 01 00 00 00
command: 15 00 00 00
```

Datoteka sadrži proizvoljan broj tipki. Svaka tipka počinje s `name:`; redak komentara `#` između tipki služi samo
za čitljivost.

### Polja

| Polje | Koristi se u | Tip | Opis |
|---|---|---|---|
| `name` | oboje | string | Naziv tipke. Samo ispisivi ASCII znakovi. Sučelje Flippera ograničava nazive na 23 znaka. |
| `type` | oboje | string | `parsed` ili `raw`. |
| `protocol` | parsed | string | Naziv protokola, točno kao na [popisu protokola](/hr/infrared/protocols) (ispisuje ga i CLI naredba `ir`). |
| `address` | parsed | hex | Adresa, uvijek **4 bajta**, najmanje značajan bajt prvi: `EE 87 00 00` = `0x87EE`. |
| `command` | parsed | hex | Naredba, uvijek **4 bajta**, najmanje značajan bajt prvi. |
| `frequency` | raw | uint32 | Frekvencija nositelja u Hz, obično `38000`. Valjani raspon 10000–1000000. |
| `duty_cycle` | raw | float | Faktor ispune (duty cycle) nositelja, obično `0.33`. Mora biti veći od 0 i ≤ 1. |
| `data` | raw | uint32 list | Vremenski razmaci u mikrosekundama između promjena razine (mark, space, mark, …), odvojeni razmakom. **Maks. 1024** vrijednosti. |

### Valjane vrijednosti za `protocol`

```text
NEC  NECext  NEC42  NEC42ext  Samsung32  RC6  RC5  RC5X  SIRC  SIRC15  SIRC20  Kaseikyo  RCA  Pioneer
```

::: tip Unleashed
`RCA` je dodatak Unleasheda. `Pioneer` postoji u firmveru iako ga službeni dokument formata još
ne navodi.
:::

### Ručno uređivanje

- Zadržite dva retka zaglavlja (`Filetype`, `Version`) na vrhu.
- Svaka tipka treba `name` i `type`, a zatim ili `protocol`/`address`/`command` ili `frequency`/`duty_cycle`/`data`.
- Da biste spojili dva daljinska upravljača, kopirajte blokove tipki jedne datoteke na kraj druge.
- Bajtovi adrese/naredbe moraju ostati dugi 4 bajta čak i ako protokol koristi manje bitova; neiskorišteni bajtovi su `00`.
- Ako Flipper javi *"Failed to load …"*, jedno od polja je neispravno oblikovano (primjerice RAW redak `data` s više
  od 1024 vrijednosti ili frekvencija izvan raspona).

## Datoteke biblioteka {#library-files}

Datoteke biblioteka koriste potpuno istu strukturu; razlikuje se samo zaglavlje:

```text
Filetype: IR library file
Version: 1
# Last Updated 5th Oct, 2024
# Last Checked 5th Oct, 2024
#
# Model: Example TV 1234
name: Power
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Univerzalni daljinski upravljač traži signale **po nazivu**, pa nazivi moraju točno odgovarati tipkama biblioteke (pogledajte
tablicu u [Slanje snimljenih signala](/hr/infrared/captures#button-names-per-library)). Novi modeli dodaju se na kraj,
a ispred njih stoji komentar `# Model: …`.

Datoteka biblioteke ne može se otvoriti putem `Saved Remotes`: aplikacija javlja *"Library file … can't be opened as a remote"*.

## Testne datoteke (`.irtest`)

Koriste ih samo jedinični testovi firmvera (`applications/debug/unit_tests/resources/unit_tests/infrared` u repozitoriju).
Izgledaju kao datoteke daljinskog upravljača, uz dodatak tipa `parsed_array` za cijele nizove dekodiranih poruka:

| Polje | Koristi se u | Tip | Opis |
|---|---|---|---|
| `name` | oboje | string | Naziv signala, pogledajte imenovanje u nastavku. |
| `type` | oboje | string | `parsed_array` ili `raw`. |
| `count` | parsed_array | uint32 | Broj poruka u polju, najmanje 1. |
| `protocol`, `address`, `command` | parsed_array | | Kao gore, po jedan za svaku poruku. |
| `repeat` | parsed_array | bool | Je li poruka ponavljanje (držanje tipke). |
| `frequency`, `duty_cycle`, `data` | raw | | Kao gore. |

Nazivi slijede oblik `<name><test_number>`: `decoder_input1` (neobrađeni ulaz za dekoder, ujedno i očekivani izlaz enkodera),
`decoder_expected1` (očekivani izlaz dekodera, ujedno i ulaz enkodera), `encoder_decoder_input1` (parsirano polje koje mora
preživjeti povratno putovanje kodiranje → dekodiranje). Svaki protokol mora imati takvu testnu datoteku.

## Povezane stranice

- [Protokoli](/hr/infrared/protocols)
- [Slanje snimljenih signala](/hr/infrared/captures)
- [Učenje i slanje signala](/hr/infrared/read)
