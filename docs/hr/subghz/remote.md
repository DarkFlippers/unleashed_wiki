---
title: Aplikacija Sub-GHz Remote
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz_remote, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemotePlugin.md, https://github.com/DarkFlippers/SubGHz_Remote]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Sub-GHz Remote

**Sub-GHz Remote** pretvara Flipper u daljinski upravljač s pet gumba. Povežete do pet spremljenih `.sub` datoteka na tipke <kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd> i <kbd>OK</kbd>, svakoj dodijelite oznaku i zatim ih šaljete jednim pritiskom bez pregledavanja kroz `Sub-GHz → Saved`.

::: tip Unleashed
Sub-GHz Remote ugrađen je u Unleashed i nalazi se u **glavnom izborniku**: `Main Menu → Sub-GHz Remote`. Napisali su ga @gid9798 i @xMasterX, a njegov se izvorni kôd nalazi u zasebnom repozitoriju, [DarkFlippers/SubGHz_Remote](https://github.com/DarkFlippers/SubGHz_Remote), uključenom u firmver kao podmodul. Tvornički firmver nema ga u izborniku; za službeni firmver postoji zasebna inačica u katalogu aplikacija.
:::

## Kada ga koristiti

- Stalno koristite nekoliko signala, primjerice za kapiju, garažna vrata i rampu, i želite ih na jedan pritisak.
- Upravljate s više uređaja (ventilator, svjetla, zvono na vratima) i želite ih na jednom zaslonu s čitljivim oznakama.

Svaki gumb šalje normalnu `.sub` datoteku, pa sve što radi iz `Sub-GHz → Saved → Emulate` radi i ovdje: statički ključevi, daljinski upravljači s promjenjivim kodom koje ste izradili pomoću [Add Manually](/hr/subghz/add-manually), RAW i BinRAW snimke. Protokoli koje Flipper može samo primati ne mogu se povezati.

## Izbornik

Aplikacija odmah otvara preglednik datoteka mapa (map files). Pritisnite <kbd>Back</kbd> za dolazak do izbornika:

| Stavka | Što radi |
|---|---|
| `Open Map File` | odaberite mapu i idite na zaslon daljinskog upravljača |
| `Edit Map File` | odaberite mapu i otvorite je u uređivaču |
| `New Map File` | upišite naziv i izradite novu mapu |
| `Set Default` | odaberite mapu koju aplikacija odsad sama otvara |
| `Clear Default` | ponovno zaboravite tu mapu (prikazuje se samo kad je jedna postavljena) |

Mape su `.txt` datoteke u mapi `subghz_remote` na SD kartici. Naziv datoteke nije važan i možete imati koliko god mapa želite. Ako iz starijih inačica imate staru mapu `unirf`, aplikacija je pri prvom pokretanju premješta u `subghz_remote`.

## Izrada mape na Flipperu

Aplikacija ima ugrađeni uređivač, pa vam nije potrebno računalo.

1. Najprije spremite željene signale pomoću [Read](/hr/subghz/read), [Read RAW](/hr/subghz/read-raw) ili [Add Manually](/hr/subghz/add-manually).
2. Otvorite `Main Menu → Sub-GHz Remote`, pritisnite <kbd>Back</kbd> i odaberite `New Map File`.
3. Upišite naziv, do 25 znakova. Mapa postaje `/ext/subghz_remote/<name>.txt`.
4. Uređivač se otvara na mjestu `UP`.

| Tipka u uređivaču | Što radi |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> | kretanje između pet mjesta: `UP`, `DOWN`, `LEFT`, `RIGHT`, `OK` |
| <kbd>OK</kbd> | `Edit` — otvara izbornik tog mjesta |
| <kbd>→</kbd> | `Save` — ide na pregled |
| <kbd>←</kbd> ili <kbd>Back</kbd> | `Back` |

Traka na vrhu prikazuje naziv mjesta i njegovu oznaku. Ispod nje vidite putanju datoteke povezane s tim mjestom, ili `Button not set` kad je mjesto prazno, ili `ERR:` s razlogom: `File not found`, `Bad frequency`, `Bad modulation`, `Unsupported protocol`.

Izbornik mjesta ima četiri stavke:

- `Edit Label` — tekst koji se prikazuje za ovaj gumb. Do 25 znakova, od kojih oko 16 stane na zaslon daljinskog upravljača. Dopuštena je i prazna oznaka, aplikacija najprije pita `Empty Label Name / Continue?`; bez oznake umjesto nje prikazuje naziv datoteke.
- `Edit File` — preglednik `.sub` datoteka koji počinje u `/ext/subghz`. Ako se datoteka ne može upotrijebiti, dobivate skočnu poruku `ERROR` s tekstom `Bad frequency`, `Bad modulation` ili `Unsupported protocol`, a mjesto zadržava ono što je imalo.
- `Button` — koji gumb daljinskog upravljača ovo mjesto šalje: `Default`, `Up`, `Down`, `Left`, `Right`. Pogledajte [Prilagođeni gumbi](#custom-buttons).
- `Clear Slot` — prazni mjesto.

Pritisnite <kbd>→</kbd> kad završite. Pregled prikazuje gotovi daljinski upravljač s `Back` na lijevoj i `Save` na desnoj strani; <kbd>→</kbd> ili <kbd>OK</kbd> zapisuje datoteku i pojavljuje se zaslon `Saved!`. Izlazak iz uređivača s nespremljenim promjenama najprije pita `Changes are not saved / do you want to exit?`.

U redu je ostaviti mjesto prazno. Mapa s jednim gumbom radi.

## Slanje

Odaberite `Open Map File` i izaberite svoju mapu. Ovaj se zaslon iscrtava bočno, pa držite Flipper uspravno.

- **Držite** tipku za odašiljanje. Taj redak postaje crn, a LED bljeska ljubičasto (magenta).
- Pustite je i protokol šalje svoja preostala ponavljanja, zatim staje. RAW datoteka reproducira se do kraja snimke i počinje ponovno ako i dalje držite tipku.
- Ispod pet redaka aplikacija prikazuje što šalje: naziv protokola, frekvenciju i modulaciju, `Key:` (samo za ključeve od 32 bita ili manje), `Sn:` ili `Fix:`, `Cnt:`, `MF:`. Stane najviše pet redaka.
- Ikona u gornjem lijevom kutu pokazuje koristi li se unutarnji radio ili [vanjski modul](/hr/subghz/external-cc1101).
- <kbd>Back</kbd> zaustavlja odašiljanje koje je u tijeku. Pritisnite ga ponovno za izlaz iz aplikacije.

Mjesto čija se datoteka nije mogla učitati prikazuje `[X] Can't open file` ili `[X] Error in .sub file` umjesto svoje oznake. Prazna mjesta ostaju prazna, a pritisak na njih izaziva crveno bljeskanje LED-a.

## Prilagođeni gumbi {#custom-buttons}

Daljinski upravljač s promjenjivim kodom ima više gumba, a `.sub` datoteka pohranjuje jedan od njih. `Button` u izborniku mjesta bira koji od njih ovo mjesto šalje. `Default` zadržava gumb iz datoteke; `Up`, `Down`, `Left` i `Right` šalju ostale gumbe istog daljinskog upravljača, iste one koje dobivate tim tipkama u `Sub-GHz → Saved → Emulate`. Uređivač zatim dodaje `(Btn. Up)` iza putanje.

Brojač se pomiče jednom po pritisku, a aplikacija vraća izvorni gumb kad odašiljanje završi.

Ovako skrivenom gumbu ili gumbu za programiranje dodjeljujete vlastito mjesto. Koja strelica odgovara kojem gumbu ovisi o protokolu, pogledajte [Flipper kao novi daljinski upravljač](/hr/subghz/remote-prog).

## Datoteka mape

Uređivač zapisuje običnu tekstualnu datoteku u Flipperovom formatu:

```text
Filetype: Flipper SubRem Map file
Version: 1
UP: /ext/subghz/Fan1.sub
DOWN: /ext/subghz/Fan2.sub
LEFT: /ext/subghz/Door.sub
RIGHT: /ext/subghz/Garage3.sub
OK: /ext/subghz/Garage3l.sub
ULABEL: Fan ON
DLABEL: Fan OFF
LLABEL: Doorbell
RLABEL: Garage OPEN
OKLABEL: Garage CLOSE
UBUTTON: 01
```

- `UP` / `DOWN` / `LEFT` / `RIGHT` / `OK` pune su putanje `.sub` datoteka povezanih sa svakim smjerom D-pada.
- `ULABEL` / `DLABEL` / `LLABEL` / `RLABEL` / `OKLABEL` tekstovi su koji se prikazuju na zaslonu za te gumbe.
- `UBUTTON` / `DBUTTON` / `LBUTTON` / `RBUTTON` / `OKBUTTON` prilagođeni su gumbi u heksadecimalnom obliku: `00` zadano, `01` gore, `02` dolje, `03` lijevo, `04` desno. Uređivač izostavlja redak kad mjesto koristi `Default`.

Mapu možete napisati i na računalu. Ako to radite:

- Odvojite ključ od vrijednosti dvotočkom i **jednim** razmakom, točno kao gore.
- Redoslijed redaka nije važan, aplikacija svaki ključ traži po nazivu. Ključ koji izostavite računa se kao prazan.
- **Naziv datoteke** za `.sub` mora biti običan ispisivi ASCII i ne smije sadržavati `\ < > * | " : ?`. Ćirilični naziv ili emoji uzrokuju neuspjeh učitavanja tog mjesta.
- Držite oznake do otprilike 16 znakova. Dulje se režu na uskom zaslonu daljinskog upravljača.

Ugrađeni uređivač ne može stvoriti neispravnu mapu, pa mu dajte prednost.

## Otvaranje mape pri pokretanju

`Set Default` pohranjuje odabranu mapu u `/ext/subghz_remote/.config`. Odsad aplikacija pri otvaranju ide izravno na zaslon daljinskog upravljača, a <kbd>Back</kbd> vas vodi u izbornik. `Clear Default` briše tu datoteku.

Aplikacija također prihvaća putanju datoteke mape kao argument pokretanja, pa druga aplikacija može izravno otvoriti određeni daljinski upravljač.

## Rješavanje problema

- **`[X] Can't open file`**: `.sub` datoteka na koju to mjesto pokazuje premještena je, preimenovana ili izbrisana. Ponovno je odaberite putem `Edit File` ili ispravite putanju u mapi.
- **`[X] Error in .sub file`**: datoteka se učitava, ali se ne može poslati. Uređivač navodi zašto: `Bad frequency` (frekvenciju signala ne podržava radio koji ste odabrali, pogledajte [Frekvencije](/hr/subghz/frequencies)), `Bad modulation` ili `Unsupported protocol` (protokol je samo za primanje).
- **Gumb ne radi ništa**, a LED bljeska crveno: to je mjesto prazno ili se njegova datoteka nije uspjela učitati.
- **Daljinski upravljač s promjenjivim kodom prestao je raditi** nakon što ste koristili i Flipper i izvorni daljinski upravljač: to je sukob brojača, a ne greška u aplikaciji. Pogledajte [Promjenjivi kodovi](/hr/subghz/rolling-codes) i izradite novi daljinski upravljač pomoću [Flipper kao novi daljinski upravljač](/hr/subghz/remote-prog).
- **Upozorenje `Not official FW` pri pokretanju**: instalirali ste inačicu iz kataloga aplikacija namijenjenu službenom firmveru. Koristite Sub-GHz Remote koji se već nalazi u glavnom izborniku Unleasheda.
- Starije upute spominju zaslon `Config is incorrect. Please configure map.`. Trenutačna aplikacija ga ne prikazuje; umjesto toga označava neispravne gumbe na zaslonu daljinskog upravljača.

## Povezane stranice

- [Čitanje signala](/hr/subghz/read) · [Read RAW](/hr/subghz/read-raw) · [Add Manually](/hr/subghz/add-manually)
- [Flipper kao novi daljinski upravljač](/hr/subghz/remote-prog)
- [Format datoteke .sub](/hr/subghz/file-format)
