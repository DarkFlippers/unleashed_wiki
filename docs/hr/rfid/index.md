---
title: 125 kHz RFID
author: gromovyna
original: [https://docs.flipper.net/zero/rfid, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08]
sources: [unleashed-src, flipper-docs, unleashed-readme, gromovyna]
---
# 125 kHz RFID

Niskofrekventni (LF) RFID tehnologija je beskontaktne blizine ("proximity") koja se koristi u jeftinim pristupnim karticama i privjescima, portafonskim oznakama, nekim sustavima za parkiranje i teretane te životinjskim mikročipovima. Te oznake obično odašilju fiksni ID bez ikakve kriptografije, zbog čega ih je lako čitati, emulirati i klonirati.

Flipper Zero ima 125 kHz antenu na stražnjoj strani (na dvopojasnoj anteni, pokraj 13,56 MHz NFC zavojnice), kojom upravlja mikrokontroler STM32WB55. Pomoću nje Flipper može **čitati**, **spremati**, **emulirati** i **zapisivati** LF oznake.

::: tip Unleashed
Aplikacija 125 kHz RFID temelji se na službenom firmveru. Povrh toga, verzija Unleashed donosi:
- izbornik **Settings → Write Chips**: osim T5577 može zapisivati na **EM4305** i klonove Hitag Micro (**8265**, **8210**, **H5.5**), uz opcijski cilj **8268** (Hitag S). Zaslon za zapisivanje prikazuje koji se čip isprobava i koji je prihvatio zapis;
- **Write and set password** za prazne T5577 kartice;
- dodatne formate za **Add Manually** (unos koda objekta / broja kartice umjesto hexa, HID H10304/H10302/S10401/H10306/Corp1000-35, Casi-Rusco), te prikaz DEZ 8 / DEZ 10 za EM4100;
- treći prolaz čitanja na **134,2 kHz** za životinjske oznake i namjenski način **Read FDX-B (Animals)**;
- ugrađenu aplikaciju **T5577** (čitanje/uređivanje/vraćanje blokova, testiranje, brisanje, uklanjanje i prisluškivanje lozinki).
:::

## Glavni izbornik

`Main Menu → 125 kHz RFID` otvara izbornik sa sljedećim stavkama (točni nazivi iz firmvera):

![Izbornik 125 kHz RFID sa stavkama Read, Saved, Add Manually i Extra Actions](/screens/lfrfid/menu.png)

| Stavka | Što radi | Stranica |
|---|---|---|
| **Read** | Automatski prepoznaje i čita oznaku (ciklus ASK → PSK → 134 kHz) | [Čitanje oznaka](/hr/rfid/read) |
| **Saved** | Pregled `/ext/lfrfid/` — emulacija, zapisivanje, uređivanje, preimenovanje i brisanje spremljenih ključeva | [Čitanje oznaka](/hr/rfid/read), [Zapisivanje](/hr/rfid/write) |
| **Add Manually** | Stvaranje ključa iz protokola i ID-a | [Ručni unos](/hr/rfid/add-manually) |
| **Extra Actions** | Čitanje fiksnom modulacijom (ASK, PSK, FDX-B); RAW čitanje/emulacija u Debug načinu | [Čitanje oznaka](/hr/rfid/read), [RAW](/hr/rfid/raw) |
| **Settings** | **Write Chips** — na koje se vrste praznih čipova smije zapisivati | [Zapisivanje](/hr/rfid/write) |

## Stranice u ovom odjeljku

- [Čitanje oznaka](/hr/rfid/read) — čitanje, spremanje i emulacija LF oznaka; čitanje fiksnom modulacijom.
- [Zapisivanje na prazne medije](/hr/rfid/write) — koji prazni čipovi rade (T5577, EM4305, Hitag Micro, 8268), postavka Write Chips, zapisivanje s lozinkom, poruke o pogreškama.
- [Ručno dodavanje](/hr/rfid/add-manually) — svi protokoli u Add Manually i formati unosa FC/ID.
- [Podržani protokoli](/hr/rfid/protocols) — potpuna tablica protokola: modulacija, veličina podataka, dekodirana polja, podrška za zapisivanje.
- [Životinjski mikročipovi](/hr/rfid/animal-microchips) — FDX-B / FDX-A čipovi za kućne ljubimce.
- [T5577 i Hitag Micro (autor @gromovyna)](/hr/rfid/t5577-hitag) — pozadina za H5.5 / 8265 / 8210, korisničko sučelje za zapisivanje, brisanje T5577.
- [Aplikacija T5577](/hr/rfid/t5577-app) — čitanje na razini blokova, uređivanje, vraćanje, testiranje, brisanje, uklanjanje lozinke, prisluškivanje lozinke.
- [RAW snimanje](/hr/rfid/raw) — snimanje sirovog ASK/PSK signala za istraživanje protokola.
- [Fuzzer](/hr/rfid/fuzzer) — što firmver donosi za aplikaciju RFID fuzzer.
- [Formati datoteka](/hr/rfid/file-format) — `.rfid`, `.t5577` i `.raw` datoteke.

## Gdje se nalaze datoteke

| Putanja | Sadržaj |
|---|---|
| `/ext/lfrfid/*.rfid` | Spremljeni ključevi |
| `/ext/lfrfid/*.t5577` | Dumpovi blokova T5577 (otvara ih aplikacija T5577) |
| `/ext/lfrfid/*.ask.raw`, `*.ask134.raw`, `*.psk.raw` | RAW snimke |
| `/ext/lfrfid/.lfrfid.settings` | Postavka Write Chips |
| `/ext/lfrfid/assets/t5577_dict.lfrfid` | Rječnik lozinki za T5577 (prepisuje se pri ažuriranju) |
| `/ext/lfrfid/assets/t5577_dict_user.lfrfid` | Vaše vlastite T5577 lozinke |
| `/ext/lfrfid/assets/iso3166.lfrfid` | Nazivi država za FDX-B čipove |

::: warning
Klonirajte i emulirajte samo oznake koje posjedujete ili za čije testiranje imate ovlaštenje.
:::
