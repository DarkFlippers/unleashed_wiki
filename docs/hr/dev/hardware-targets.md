---
title: Hardverski ciljevi
order: 25
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HardwareTargets.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets]
sources: [unleashed-docs, unleashed-src]
---
# Hardverski ciljevi

Firmver je modularan: jedna baza koda podržava više hardverskih konfiguracija. Sve što se razlikuje između
pločica — implementacija `furi_hal`, kôd za inicijalizaciju pločice, linker skripte, tablice SDK simbola — spakirano je u
**definiciju cilja (target definition)**.

Repozitorij Unleashed isporučuje dva cilja u mapi `targets/`:

| Mapa | Hardver |
|---|---|
| `targets/f7` | Flipper Zero — zadani cilj (`TARGET_HW = 7`) |
| `targets/f18` | "Not Flipper Zero" — pločica bez radio modula; nasljeđuje f7 |

Zajednička zaglavlja nalaze se u `targets/furi_hal_include`.

## Kako je cilj organiziran

Svaki cilj nalazi se u vlastitoj podmapi unutar `targets/`. Mora sadržavati datoteku `target.json` i može sadržavati sve ostale datoteke
na koje se ta definicija poziva. Prema zadanim postavkama `fbt` prevodi **svaku izvornu datoteku** u mapi cilja osim ako nije
izričito isključena. Ciljevi mogu **nasljeđivati** drugi cilj kako bi se izbjeglo dupliciranje koda.

## Polja datoteke `target.json`

| Polje | Vrsta | Značenje |
|---|---|---|
| `include_paths` | popis nizova znakova | Mape (relativno u odnosu na cilj) dodane globalnoj C/C++ stazi uključivanja |
| `sdk_header_paths` | popis nizova znakova | Mape čija se zaglavlja uključuju u SDK |
| `startup_script` | naziv datoteke | Početna skripta koja obavlja inicijalnu inicijalizaciju hardvera |
| `linker_script_flash` | naziv datoteke | Linker skripta za glavnu sliku firmvera |
| `linker_script_ram` | naziv datoteke | Linker skripta za konfiguraciju "updater" (izvršava se iz RAM-a) |
| `linker_script_app` | naziv datoteke | Linker skripta za `.fap` datoteke |
| `sdk_symbols` | naziv datoteke | `.csv` s trenutačnom definicijom SDK-a (API-ja) za ovaj cilj |
| `linker_dependencies` | popis | Biblioteke s kojima se firmver povezuje. Biblioteke koje nisu navedene **ne grade se**. Višestruki prolazi linkera mogu zahtijevati isti naziv dvaput |
| `inherit` | niz znakova | Cilj iz kojeg se preuzima osnovna konfiguracija. Popisi se proširuju, a ostale se vrijednosti nadjačavaju |
| `excluded_sources` | popis | Datoteke iz naslijeđene konfiguracije koje se **ne** grade |
| `excluded_headers` | popis | Zaglavlja iz naslijeđene konfiguracije koja se **ne** stavljaju u SDK |
| `excluded_modules` | popis | Nazivi `fbt` biblioteka (modula) koje treba isključiti pri konfiguriranju gradnje |

## Primjer: kako f18 nasljeđuje f7

`targets/f18/target.json` (skraćeno) prikazuje nasljeđivanje i isključivanje u praksi — preuzima sve iz f7
i izostavlja upravljačke programe za Sub-GHz, NFC, RFID, iButton i infracrveni modul:

```json
{
    "inherit": "7",
    "include_paths": [
        "furi_hal"
    ],
    "sdk_symbols": "api_symbols.csv",
    "excluded_sources": [
        "furi_hal_infrared.c",
        "furi_hal_nfc.c",
        "furi_hal_rfid.c",
        "furi_hal_subghz.c"
    ],
    "excluded_modules": [
        "nfc",
        "lfrfid",
        "subghz",
        "ibutton",
        "infrared"
    ]
}
```

## Aplikacije i hardver

Nije svaka aplikacija dostupna na svakom cilju.

- **Ugrađene aplikacije:** odaberite kompatibilan skup aplikacija pomoću opcije `FIRMWARE_APP_SET=...`
  (pogledajte [fbt → skupovi aplikacija firmvera](/hr/dev/fbt#firmware-app-sets)).
- **Vanjske aplikacije (FAP):** navedite kompatibilne ciljeve u datoteci `application.fam` aplikacije. Na primjer, da biste izgradili aplikaciju
  samo za f7, dodajte:

```python
    targets=["f7"],
```

Neće se graditi za druge ciljeve. Pogledajte [Manifesti aplikacija](/hr/dev/app-manifests).

## Gradnja za određeni cilj

Proslijedite `TARGET_HW` (i opcionalno `FIRMWARE_APP_SET`) alatu `fbt`. Na primjer, za gradnju i instalaciju firmvera za f18
preko USB-a:

```sh
./fbt TARGET_HW=18 flash_usb_full
```

## Povezane stranice

- [Flipper Build Tool (fbt)](/hr/dev/fbt)
- [Manifesti aplikacija (.fam)](/hr/dev/app-manifests)
- [FuriHalBus API](/hr/dev/furi-hal-bus)
