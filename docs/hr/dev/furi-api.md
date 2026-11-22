---
title: Furi API
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_furi_api.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriCheck.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi]
sources: [unleashed-docs, unleashed-src]
---
# Furi API

Za korištenje hardvera Flippera — zaslona, zvučnika, radija, USB-a, NFC-a — vaša aplikacija komunicira s **Furijem**, skupom biblioteka
koji se nalazi između golog hardvera i aplikacijskog koda. Ova stranica daje pregled hardverske i softverske
arhitekture te objašnjava Furijeve provjere u vremenu izvođenja.

## Hardver

Srce Flippera Zero je mikrokontroler (MCU) **STM32WB55**: dvije jezgre, RAM, flash memorija i deseci perifernih
blokova (tajmeri, RTC, BLE, GPIO, …). Njihov je rad opisan u referentnom priručniku MCU-a (Reference Manual). Oko MCU-a
nalazi se nekoliko vanjskih čipova (CC1101, ST25R3916, kontroler zaslona itd.) s vlastitim podatkovnim listovima (datasheet).

![Struktura hardvera Flippera Zero](/img/dev/flipper_zero_hardware.png)

Legenda boja:

- **Ljubičasta** — blokovi unutar MCU-a
- **Plava** — čipovi izvan MCU-a
- **Narančasta** — ostale periferne komponente koje ne zahtijevaju složenu interakciju

Budući da je firmver otvorenog koda, *možete* izravno pristupati hardveru i pisati vlastite upravljačke programe niske razine —
ali to obično nije potrebno.

## Softver: Furi

**Furi** (**F**lipper **U**niversal **R**egistry **I**mplementation) apstrakcijski je sloj uključen u
firmver. Pruža jednostavan API za hardver i uobičajene sistemske zadatke: dretve, dinamičku memoriju,
kontrolu pristupa resursima (zapisi / records), tajmere, redove poruka, zapisivanje dnevnika (logging) i slično.

Uz Furi ne morate čitati stotine stranica podatkovnih listova niti pisati upravljačke programe — dovoljno je naučiti Furi API.
Time se ujedno izbjegava da svaki razvojni programer iznova implementira iste stvari.

![Struktura hardvera i softvera Flippera Zero](/img/dev/flipper_zero_architecture.png)

Furi se proteže cijelom širinom dijagrama: odvaja kod na razini aplikacije (servise i aplikacije) od hardvera
ispod njega.

Furi se sastoji od dva dijela:

| Dio | Gdje | Što |
|---|---|---|
| Furi Core | `furi/` | Primitivi OS-a: dretve, muteksi, redovi poruka, zapisi, tajmeri, petlja događaja, zapisivanje dnevnika, provjere |
| Furi HAL | `targets/` (npr. `targets/f7/furi_hal/`) | Hardverska apstrakcija: GPIO, SPI, I2C, USB, Sub-GHz, NFC, RFID, napajanje, … — pogledajte [FuriHalBus](/hr/dev/furi-hal-bus) |

Izvorni kod:

- Furi Core: [unleashed-firmware/furi](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi)
  (službeni: [flipperzero-firmware/furi](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/furi))
- Furi HAL: [unleashed-firmware/targets](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets)
  (službeni: [flipperzero-firmware/targets](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/targets))

## Pronalaženje primjera

Svaka Flipper aplikacija koristi Furi, stoga postoje primjeri za svaki hardverski blok:

- ogledne aplikacije u [`applications/examples/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples)
  (`example_event_loop`, `example_adc`, `example_ble_beacon`, …);
- ugrađene aplikacije u `applications/main/` i dodatne Unleashed aplikacije u `applications/system/`;
- aplikacije zajednice u [Katalogu aplikacija](https://lab.flipper.net/apps) — poveznica na izvorni kod nalazi se na dnu stranice svake
  aplikacije. Odaberite aplikacije čija je funkcionalnost bliska onome što želite izraditi.

Svaka Furi funkcija, struktura i zaglavlje navedeni su u službenoj [Doxygen API referenci](https://developer.flipper.net/flipperzero/doxygen/) — koristite je kada ovaj wiki ne pokriva poziv koji vam treba.

## Provjere u vremenu izvođenja i prisilni padovi sustava

Najbolji način za očuvanje integriteta sustava jest obrada manjeg broja nemogućih slučajeva i **što raniji pad sustava (crash)** kada
nešto pođe po zlu. Datoteka `check.h` iz Furi Corea pruža pomoćne makronaredbe za to.

Pojmovi:

- **Crash** — zapiši događaj u dnevnik, spremi informacije o padu u RTC i ponovno pokreni uređaj.
- **Halt** — zapiši događaj u dnevnik i zaustavi sustav.

Napomene:

- Debug i release inačice ponašaju se različito: **debug inačica nikada ne resetira** sustav kako bi sačuvala stanje za
  debugger.
- Kada je spojen debugger, izvođenje se automatski zaustavlja prije ponovnog pokretanja.
- Sve pomoćne makronaredbe prihvaćaju neobavezni `MESSAGE_CSTR`. Može biti u RAM-u ili flash memoriji, ali **samo poruke pohranjene u flash memoriji** bivaju
  prikazane nakon ponovnog pokretanja (tj. koristite znakovne literale).
- `MESSAGE_CSTR` može biti `NULL`, ali makronaredbe već obrađuju slučaj bez poruke — jednostavno ga izostavite.

| Makronaredba | Ponašanje | Kada koristiti |
|---|---|---|
| `furi_assert(CONDITION)` / `furi_assert(CONDITION, MESSAGE_CSTR)` | Pad ako je `CONDITION` netočan — **samo u razvojnim inačicama** | Provjere u fazi razvoja u aplikacijama i servisima |
| `furi_check(CONDITION)` / `furi_check(CONDITION, MESSAGE_CSTR)` | **Uvijek** pad ako je `CONDITION` netočan | Uvjeti koji moraju vrijediti u svakoj inačici |
| `furi_crash()` / `furi_crash(MESSAGE_CSTR)` | Bezuvjetni pad | Otkriveno je nenormalno stanje |
| `furi_halt()` / `furi_halt(MESSAGE_CSTR)` | Zaustavljanje sustava | Koristi se interno, npr. za zaustavljanje kada isključivanje nije moguće |

::: warning Zamke makronaredbe furi_assert
- Release inačice (`DEBUG=0`) nikada ne sadrže `furi_assert` provjere.
- Biblioteke ih prema zadanim postavkama nikada ne sadrže; izgradite s `LIB_DEBUG=1` ako su vam potrebne.
- Ne stavljajte pozive funkcija (nuspojave) unutar `CONDITION` — cijeli izraz može biti uklonjen pri prevođenju.
:::

Primjer:

```c
#include <furi.h>

void my_set_level(uint8_t level) {
    furi_check(level <= 100, "Level out of range");
    // ...
}
```

## Povezane stranice

- [GUI u aplikacijama](/hr/dev/gui)
- [FuriHalBus API](/hr/dev/furi-hal-bus)
- [Otklanjanje pogrešaka u aplikacijama](/hr/dev/debugging) — uključuje Furi HAL debug signale
