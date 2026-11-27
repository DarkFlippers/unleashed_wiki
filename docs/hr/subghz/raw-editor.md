---
title: Sub-GHz RAW Edit
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/subghz_raw_editor, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/Lechnio/SubGHz-RAW-Edit]
sources: [unleashed-src, unleashed-readme]
---
# Sub-GHz RAW Edit

**Sub-GHz RAW Edit** (autor Lechnio) mali je uređivač valnog oblika na samom uređaju za RAW `.sub` snimke. Snimka iz [Read RAW](/hr/subghz/read-raw) obično sadrži sekunde šuma oko kratkog impulsa koji vas zanima. Pomoću alata RAW Edit pronalazite stvarni signal, označujete ga i spremate samo taj dio.

::: tip Unleashed
RAW Edit dolazi s firmverom Unleashed kao sistemska aplikacija, a aplikacija Sub-GHz otvara ga izravno: `Sub-GHz → Read RAW` (ili `Saved`) → otvorite RAW datoteku → <kbd>→</kbd> `More` → `Edit`. Stavka `Edit` prikazuje se samo kada je RAW Edit instaliran. Kada izađete iz uređivača, vraćate se u Sub-GHz.
:::

**Kada ga koristiti:** skratite dugu RAW snimku prije dijeljenja ili slanja, podijelite jednu snimku na zasebne tipke, spojite nekoliko snimki zajedno ili otkrijte koji se protokol skriva unutar RAW datoteke.

## Glavni izbornik

`Main Menu → Apps → Sub-GHz → Sub-GHz RAW Edit`:

- `Select .sub file` — otvaranje datoteke iz `/ext/subghz` u uređivaču
- `Merge .sub files` — spajanje nekoliko datoteka u jednu
- `Config` — opcije za učitavanje i spajanje
- `About` — verzija i poveznica na projekt

Osim RAW datoteka, aplikacija može učitati bilo koji signal koji firmver može kodirati (pretvara se u RAW putem unutarnjeg kodera). Za protokole s prilagođenim tipkama najprije nudi odabir tipke.

## Uređivač

Zaslon prikazuje valni oblik s trakom pregleda na vrhu i dva retka ispod: `View:` (zumiranje) i `Marked:` (duljina odabira A..B). Odabrani raspon istaknut je isprekidanom linijom; male oznake pokazuju da izvan ruba zaslona ima još signala.

| Tipka | Radnja |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | pomicanje aktivnog markera (A ili B); držite za brže pomicanje |
| <kbd>↑</kbd> / <kbd>↓</kbd> | povećanje / smanjenje prikaza |
| <kbd>OK</kbd> | prebacivanje aktivnog markera između A i B |
| držanje <kbd>OK</kbd> | otvaranje izbornika radnji |
| <kbd>Back</kbd> | zatvaranje uređivača |

Izbornik radnji (<kbd>↑</kbd> / <kbd>↓</kbd>, <kbd>OK</kbd> za pokretanje, <kbd>Back</kbd> za zatvaranje) nalazi se s lijeve strane, a pokraj njega je ploča s informacijama samo za čitanje koja prikazuje broj uzoraka raspona A..B, `TE` i prepoznato linijsko kodiranje (`PWM`, `PPM`, `Manchester`, `NRZ` ili `1:1`):

- **Save** — zapisuje samo raspon A..B u novu RAW datoteku. Predloženi naziv je `<name>_edit1`, `_edit2`, … Spremanje pod postojećim nazivom pita `Name exists, overwrite?`; sama otvorena datoteka nikada se ne prepisuje.
- **Decode** — dekodira raspon A..B pomoću Sub-GHz dekodera firmvera (isprobavajući svakog proizvođača na svakom KeeLoq okviru; preskače BinRAW), grupira identične okvire signala (`Decoded: N`) i sprema odabrani kao datoteku ključa, zadano nazvanu po protokolu i proizvođaču (npr. `KeeLoq_Verex`). Svaka dekodirana stavka ima i gumb **Locate** koji postavlja A..B točno na njezin okvir (prvi kada se ponavlja). `No known protocol` znači da ništa nije dekodirano.
- **Cut** / **Copy** / **Paste** — pritisnite <kbd>←</kbd> / <kbd>→</kbd> na stavci `Cut` za prebacivanje između **Cut** (uklanja raspon A..B i stavlja ga u međuspremnik; odbija se ako bi signal ostao prazan), **Copy** (kopira A..B u datoteku međuspremnika) i **Paste** (umeće sadržaj međuspremnika kod aktivnog markera i označava ga).
- **Undo** — povijest posljednja **32** rezanja i lijepljenja spremljena na SD kartici (ne troši RAM). Kada postoji više od jedne izmjene, prikazuje ih od najnovije s brojem uzoraka i položajima te vraća stanje na ono prije odabrane izmjene. Precrtano kada nema što za poništiti.

## Skraćivanje snimke — korak po korak

1. Snimite daljinski upravljač u [Read RAW](/hr/subghz/read-raw) i spremite snimku.
2. Otvorite je u alatu RAW Edit (putem `More → Edit` ili `Select .sub file`).
3. Smanjite prikaz tipkom <kbd>↓</kbd> kako biste vidjeli gdje se nalaze impulsi.
4. Pomaknite marker **A** neposredno prije impulsa tipkama <kbd>←</kbd>/<kbd>→</kbd>, pritisnite <kbd>OK</kbd> pa pomaknite marker **B** neposredno nakon njega.
5. Držite <kbd>OK</kbd> → `Save`, prihvatite ili uredite naziv.
6. Testirajte spremljenu datoteku iz `Sub-GHz → Saved`.

## Spajanje datoteka

1. `Merge .sub files` → odaberite datoteku; dijalog prikazuje `Added N file(s)` i broj uzoraka. Odaberite `Add more` ili `Done`.
2. Sve datoteke moraju biti na istoj frekvenciji, inače dobivate `Frequency mismatch`.
3. Rezultat se otvara u uređivaču pod nazivom `merged`; spremite ga iz izbornika radnji.

## Config

| Stavka | Što radi |
|---|---|
| Normalize jitter | `OFF`/`ON` — čisti kolebanje i pomak trajanja pri učitavanju |
| Merge gap | tišina umetnuta između spojenih datoteka, 0–1000 ms (zadano 100); <kbd>OK</kbd> otvara unos broja |
| Repeat | ponavljanje svakog učitanog / spojenog signala 1–64 puta |

Redak samo za čitanje na dnu izbornika `Config` također prikazuje jesu li prilagođeni gumbi i očuvanje pomičnog brojača dostupni u trenutačnoj verziji firmvera.

## Ograničenja i rješavanje problema

- **Bez ograničenja duljine (v2.0):** signali i spajanja čuvaju se u radnoj datoteci na SD kartici, dok RAM drži klizni prozor snimke (do ~38 000 uzoraka nakon svježeg pokretanja), ostavljajući dovoljno memorije za Decode i Save. Pomicanje markera A ili B preko ruba prozora pomiče ga za četvrtinu dalje; smanjenje prikaza zaustavlja se na rubu prozora uz poruku `No RAM to zoom out`.
- **Upit `Low RAM`** — prikazuje se kada slobodni RAM može primiti manje od 15 000 uzoraka većeg signala; nudi `Reboot` ili `Continue`. `Decode` također provjerava ima li ~8 KB slobodnog RAM-a i javlja `Low memory` umjesto rušenja aplikacije.
- `Unsupported protocol or file is empty` — datoteka nije signal koji firmver može kodirati.
- `Nothing in A..B` / `Range too small` — razmaknite markere dalje jedan od drugoga.
- Duge pauze u spremljenoj datoteci zadržavaju svoju stvarnu duljinu.

## Povezane stranice

- [Read RAW](/hr/subghz/read-raw) · [Format datoteke](/hr/subghz/file-format)
- [Remote Analyzer](/hr/subghz/remote-analyzer)
