---
title: iButton
original: [https://docs.flipper.net/zero/ibutton, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# iButton

iButton („dodirna memorija”, u zemljama ZND-a često nazivan *таблетка*) ključ je u malom čeličnom kućištu koji se očitava prislanjanjem
na čitač. Većina ih koristi protokol Dallas **1-Wire**; portafonski sustavi također koriste ključeve **Cyfral** i **Metakom**.
Flipper Zero može čitati, spremati, emulirati i pisati ove ključeve.

## Hardver

iButton modul je kontaktna pločica s tri opružne pogo iglice na iButton tiskanoj pločici.

- Dvije vanjske iglice služe za podatke (povezane na **GPIO pin 17**), a srednja iglica je **masa (ground)**.
- **Čitanje / pisanje ključa**: ključ dodiruje **ravni dio** pločice — lijevu podatkovnu iglicu + srednju iglicu mase.
- **Emulacija prema čitaču**: **izbočeni dio** pločice dodiruje čitač — desnu podatkovnu iglicu + srednju masu.
- Ako masa ne može dosegnuti rub čitača, upotrijebite dvije žice: GPIO **17** (podatci) i GPIO **8, 11 ili 18** (masa).

## Glavni izbornik

`Main Menu → iButton`:

![Izbornik iButton sa stavkama Read, Saved, Add Manually i Settings](/screens/ibutton/menu.png)

| Stavka | Što radi | Stranica |
|---|---|---|
| **Read** | Prepoznaje vrstu ključa i čita njegov ID (te memoriju za DS1992/1996/1971) | [Čitanje](/hr/ibutton/read) |
| **Saved** | Pregledava `/ext/ibutton/` — emulira, piše, uređuje, preimenuje, briše | [Čitanje](/hr/ibutton/read), [Pisanje](/hr/ibutton/write) |
| **Add Manually** | Stvara ključ iz protokola + heksadecimalnog ID-a | [Ručno dodavanje](/hr/ibutton/add-manually) |
| **Settings** | **Write Blanks** — na koje vrste praznih ključeva pisanje smije ciljati | [Pisanje](/hr/ibutton/write) |

::: tip Unleashed
U usporedbi sa službenom dokumentacijom, Unleashed ima stranicu **Settings → Write Blanks** (RW1990.1, RW1990.2, TM2004, TM01x),
prikazuje koji se prazni ključ trenutačno isprobava tijekom pisanja i koji je prihvatio zapis, zapisuje ključeve **Cyfral i Metakom** na prazne ključeve **TM01x**
te podržava **DS1420**. ReadMe također navodi dodatak iButton Fuzzer.
:::

## Stranice u ovom odjeljku

- [Čitanje ključeva](/hr/ibutton/read) — čitanje, spremanje, emulacija, CRC pogreške.
- [Pisanje na prazne ključeve](/hr/ibutton/write) — RW1990, TM2004, TM01x; Write ID naspram Full Write on Same Type.
- [Ručno dodavanje](/hr/ibutton/add-manually) — stvaranje ključeva iz ID-a.
- [Podržani protokoli](/hr/ibutton/protocols) — Dallas DS1990/1992/1996/1971/1420, generički 1-Wire, Cyfral, Metakom.
- [Fuzzer](/hr/ibutton/fuzzer) — što firmver donosi za aplikaciju iButton Fuzzer.
- [Format datoteke](/hr/ibutton/file-format) — `.ibtn` datoteke.

## Datoteke

| Putanja | Sadržaj |
|---|---|
| `/ext/ibutton/*.ibtn` | Spremljeni ključevi (zadani prefiks naziva `iBtn`) |
| `/ext/ibutton/.ibutton.settings` | Postavka Write Blanks |

::: warning
Kopirajte i emulirajte samo ključeve koje posjedujete ili ste ovlašteni testirati.
:::
