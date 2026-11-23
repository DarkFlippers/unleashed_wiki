---
title: Flipper kao novi daljinski upravljač
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually]
sources: [unleashed-docs, unleashed-src]
---
# Korištenje Flippera kao novog Sub-GHz daljinskog upravljača

Pretvorite Flipper u **potpuno novi daljinski upravljač** i registrirajte ga u prijamniku svojih vrata, garaže ili roleta, na isti način kao što biste registrirali rezervni daljinski upravljač kupljen u trgovini. Ovo **nije** kloniranje.

::: warning
Koristite ovo samo na prijamnicima koje posjedujete ili kojima imate dopuštenje upravljati.
:::

## Klon ili novi daljinski upravljač?

- **Daljinski upravljači s promjenjivim (dinamičkim) kodom**: BFT, Erreka, FAAC, Nice, CAME Atomo, Somfy, KeeLoq i ostatak ove stranice. Svaki pritisak šalje novi kôd izgrađen iz brojača, a prijamnik prihvaća samo brojač koji je napredovao. Klon dijeli brojač izvornika, pa se međusobno nadmeću: onaj koji ste pritisnuli zadnji radi, a drugi zahtijeva nekoliko pritisaka da ga sustigne (pogledajte [Promjenjivi kodovi](/hr/subghz/rolling-codes)). Zato izrađujete **novi** daljinski upravljač. On dobiva vlastiti serijski broj i brojač te radi usporedno s vašim izvornim daljinskim upravljačima.
- **Daljinski upravljači sa statičkim (fiksnim) kodom**: CAME 12/24 bit, Nice Flo, Princeton, Marantec, Holtek, Roger, Gate TX i ostali statički protokoli. Nema brojača, pa je **kloniranje u redu**: kopija je identična i oba nastavljaju raditi bilo kojim redoslijedom. Upotrijebite `Sub-GHz → Read` i spremite ga (pogledajte [Čitanje signala](/hr/subghz/read)). Ova vam je stranica potrebna samo ako želite daljinski upravljač s vlastitim zasebnim kodom.

## Prvo pročitajte ovo

**Što radi Add Manually.** `Main Menu → Sub-GHz → Add Manually` izrađuje novi daljinski upravljač s nasumično generiranim serijskim brojem i sprema ga kao datoteku. Ništa se ne šalje dok ne otvorite tu datoteku i pritisnete tipku. Vaši izvorni daljinski upravljači ostaju netaknuti.

::: tip Unleashed: Add Manually u dva koraka
U trenutačnom firmveru Unleashed izbornik ima dva koraka:
1. Odaberite **sustav** s popisa, primjerice `BFT Mitto`, `KL: DoorHan` ili `Somfy Telis`.
2. Odaberite **pojas** (frekvencija + modulacija). Vlastiti pojasevi sustava nalaze se na vrhu, primjerice `433.92 AM650` ili `868.35 AM650`. Svi ostali pojasevi navedeni su ispod njih za instalacije koje koriste neuobičajen pojas: `433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`, `868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`, `430.50 AM650`.

Zatim imenujete datoteku i ona se sprema u `/ext/subghz/`. Stariji vodiči navode stavke poput "BFT Mitto 433MHz" kao jednu stavku izbornika. Danas je to `BFT Mitto` → `433.92 AM650`.
:::

**Ako vaš sustav nije na ovoj stranici, Flipper ga možda ipak podržava.** Pomaknite se kroz popis `Add Manually`. Ako je vaša marka ondje, izradite daljinski upravljač i slijedite korake programiranja iz *priručnika vašeg prijamnika*. Cijeli popis protokola nalazi se na stranici [Podržani sustavi](/hr/subghz/supported-systems), a svaka stavka izbornika opisana je na stranici [Add Manually](/hr/subghz/add-manually).

**Read i Add Manually su različiti zadaci.** `Read` hvata i ponovno šalje daljinski upravljač koji već imate. `Add Manually` stvara novi daljinski upravljač koji se može registrirati u prijamniku. Mnogi protokoli podržavaju samo `Read`.

**Tipke Flippera predstavljaju gumbe izvornog daljinskog upravljača.** Kada je otvorena datoteka daljinskog upravljača (`Saved → file → Emulate`):

| Tipka Flippera | Što šalje |
|---|---|
| <kbd>OK</kbd> (prikazano kao `Send`) | glavni gumb daljinskog upravljača |
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | ostali gumbi daljinskog upravljača (prilagođeni gumbi) |

Koja strelica šalje koji gumb ovisi o protokolu. *Skriveni* ili *programski* gumb na izvornom daljinskom upravljaču (udubljena rupica za iglu, dva gumba pritisnuta zajedno, kontakti koje premošćujete unutar kućišta) postaje **pritisak jedne tipke** na Flipperu. Svaki odjeljak u nastavku navodi koja je to tipka, a [referentna tablica](#programming-hidden-button-reference) navodi sve njih.

Aplikacija [Sub-GHz Remote](/hr/subghz/remote) šalje iste te gumbe: svako mjesto u mapi ima postavku `Button` (`Default`, `Up`, `Down`, `Left`, `Right`), pa skriveni gumb može imati vlastitu tipku.

**Držite tipku <kbd>OK</kbd> 1–3 sekunde**, osim ako korak ne navodi drukčije.

**Vrijeme je važno.** Većina prijamnika otvara prozor programiranja u trajanju od 5, 10 ili 30 sekundi. Pročitajte cijeli postupak prije nego što započnete.

::: danger
Na mnogim prijamnicima **predugo** držanje gumba za programiranje briše sve daljinske upravljače koje prijamnik poznaje, ne samo jedan. Tada morate ponovno registrirati sve svoje izvorne daljinske upravljače. Kad korak kaže "oko 1 sekunde", nemojte ga držati pet sekundi.
:::

::: info Done! / Done?
Postupak koji završava s **Done!** potvrđeno radi. **Done?** znači da potječe iz priručnika proizvođača, ali još nitko nije javio povratnu informaciju. Trebao bi raditi. Ako ne radi, javite timu Unleashed putem GitHub Issues.
:::

**Add Manually [Advanced]** je stavka izbornika odmah ispod `Add Manually`. Koristite je kada trebate ručno upisati vrijednosti umjesto dobivanja nasumičnog serijskog broja. Nakon sustava i pojasa pita, sve u heksadekadskom zapisu, za `Enter SERIAL in hex`, `Enter BUTTON in hex`, `Enter COUNTER in hex` i, kod protokola koji ga koriste, `Enter SEED in hex`. Nice O-Code umjesto toga pita za `IC` (i `CERT`). FAAC FIX, Monarch, Phantom/Hiland i DEA Mio umjesto SEED-a pitaju za `DISC.` (diskriminator).

## Pronađite svoj sustav

| | | |
|---|---|---|
| [Alutech AT4N](#alutech-at4n-an-motors) | [AN-Motors AT4](#an-motors-at4) | [Aprimatic TR](#aprimatic-tr) |
| [Beninca ARC (TO.GO)](#beninca-arc-to-go) | [BFT Mitto](#bft-mitto) | [CAME Atomo](#came-atomo) |
| [Cardin S449](#cardin-s449) | [DEA Mio](#dea-mio) | [Ditec GOL4](#ditec-gol4) |
| [DoorHan](#doorhan) | [Erreka IRIS](#erreka-iris) | [FAAC RC, XT](#faac-rc-xt) |
| [FAAC SLH](#faac-slh) | [Genius (SLH)](#genius-slh) | [Genius TX4RC](#genius-tx4rc-bravo-echo) |
| [Hormann EcoStar](#hormann-ecostar) | [Jarolift](#jarolift) | [KingGates Stylo 4k](#kinggates-stylo-4k) |
| [Mhouse](#mhouse) | [Nice Flor S](#nice-flor-s) | [Nice One](#nice-one) |
| [Nice O-Code](#nice-o-code) | [Nice Smilo](#nice-smilo) | [Security+ 1.0 / 2.0](#security-1-0-2-0-chamberlain-liftmaster-craftsman) |
| [Somfy Keytis](#somfy-keytis) | [Somfy Telis](#somfy-telis) | [Sommer](#sommer) |
| [V2 Phoenix (Phox)](#v2-phoenix-phox) | | |

Nije na popisu? Pogledajte [referentnu tablicu](#programming-hidden-button-reference). Ona pokriva svaku drugu stavku u izborniku `Add Manually`.

---

## Alutech AT4N (AN-Motors)

- **Izrada:** `Sub-GHz → Add Manually → Alutech AT4N → 433.92 AM650`

Koristite ovo za pločice sa zaslonom i gumbima `F`, `CL`, `+`, `-`. Ako vaša pločica umjesto toga ima gumb `Learn`, upotrijebite [AN-Motors AT4](#an-motors-at4).

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Otvorite kućište prijamnika, pronađite gumb `F` i držite ga oko 3 s. Zaslon prikazuje `Pr`.
3. Pritisnite `F` još nekoliko puta dok zaslon ne prikaže `Lr`.
4. Odaberite slobodan broj daljinskog upravljača pomoću `+` / `-`. Broj koji već ima daljinski upravljač prikazuje crvenu točku u donjem desnom kutu.
5. Pritisnite <kbd>OK</kbd> (`Send`) na Flipperu jednom. Zaslon zatreperi i uz taj se broj pojavi crvena točka.
6. Držite `F` na pločici oko 3 s za izlaz iz načina programiranja.
7. Done!

[Video upute, prikazuju i druge vrste pločica (ruski)](https://www.youtube.com/watch?v=XrOVVYhFXDg)

## AN-Motors AT4

- **Izrada:** `Sub-GHz → Add Manually → AN-Motors AT4 → 433.92 AM650`
- **Tipka za programiranje:** <kbd>→</kbd> = `0xC`

Koristite ovo za starije pločice s gumbom `Learn`. Ako vaša pločica umjesto toga ima `F`, `CL`, `+`, `-`, upotrijebite [Alutech AT4N](#alutech-at4n-an-motors).

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Otvorite kućište prijamnika i jednom pritisnite `Learn`. LED se uključuje.
3. Jednom pritisnite `Send` na Flipperu. LED na pločici se gasi.
4. Ponovno pritisnite `Send`. LED počinje treperiti. Pričekajte nekoliko sekundi dok se ne ugasi.
5. Done!

[Video upute (ruski)](https://www.youtube.com/watch?v=URVMtTELcnU)

## Aprimatic TR

- **Izrada:** `Sub-GHz → Add Manually → KL: Aprimatic → 433.92 AM650`
- **Tipka za programiranje:** <kbd>→</kbd> = `0xF` (na izvornom upravljaču sva 4 gumba pritisnuta zajedno)

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Na postojećem daljinskom upravljaču koji već radi s prijamnikom pritisnite sva 4 gumba istodobno.
3. Prijamnik daje neprekidan zvučni signal.
4. Pritisnite `Send` na Flipperu i držite oko 2 s.
5. Pričekajte dok prijamnik ne prestane pištati.
6. Done?

## Beninca ARC (TO.GO)

- **Prodaje se i kao:** TO.GO 2VA / 4VA (ranije TO.GO 2WV / 4WV). Prijamnici WB, WI i prijamnici ugrađeni u upravljačku ploču.
- **Izrada:** `Sub-GHz → Add Manually → Beninca ARC → 433.92 AM650`
- **Tipka za programiranje:** **<kbd>↓</kbd>** = `0x0`, skriveni gumb

Na izvornom upravljaču s 2 gumba skriveni gumb znači držanje oba gumba istodobno, što je teško pouzdano izvesti. Na Flipperu je to jedna tipka: <kbd>↓</kbd>.

### S ispravnim daljinskim upravljačem: prijamnici WB / WI

1. Stanite blizu prijamnika.
2. Otvorite datoteku daljinskog upravljača koji već radi. Pritisnite <kbd>↓</kbd> i držite oko 3 s. Skrivena funkcija je sada aktivna (na izvornom upravljaču ovdje treperi LED).
3. Unutar 5 s pritisnite `Send` na tom istom daljinskom upravljaču za kanal koji želite podijeliti.
4. Unutar 5 s otvorite datoteku novog daljinskog upravljača i pritisnite `Send`. Taj će gumb upravljati tim kanalom.
5. Prijamnik izlazi iz načina programiranja. Testirajte novi daljinski upravljač.
6. Done?

### S ispravnim daljinskim upravljačem: prijamnik ugrađen u upravljačku ploču

Ovdje skriveni gumb mora biti poslan s **oba** daljinska upravljača:

1. Ispravni daljinski upravljač: <kbd>↓</kbd>, zatim `Send` unutar 5 s.
2. Novi daljinski upravljač: <kbd>↓</kbd>, zatim `Send` unutar 5 s.
3. Done?

::: info
ARC i HCS (promjenjivi kod) daljinski upravljači ne mogu dijeliti isti prijamnik. Prvi daljinski upravljač koji spremite odlučuje koju vrstu prijamnik otada prihvaća. Promjena zahtijeva potpuno resetiranje prijamnika.
:::

## BFT Mitto

- **Izrada:** `Sub-GHz → Add Manually → BFT Mitto → 433.92 AM650`
- **Tipka za programiranje:** <kbd>→</kbd> = `0xF` (na izvornom upravljaču rupica za iglu sa stražnje strane ili gumbi 1+2 držani zajedno)

::: info Seed
**Noviji daljinski upravljači BFT Mitto izvode svoj Seed iz serijskog broja**, pa ih obično `Sub-GHz → Read` dekodira u letu. Odmah se prikazuju kao `KL: BFT`.
**Stariji modeli imaju jedinstveni Seed** i čitaju se kao `KL: Unknown` dok ga nemate. Postoje dva načina za njegov oporavak:
- Držite 2 gumba i pročitajte vrijednost `Hop`. Daljinski upravljač šalje svoj Seed u otvorenom obliku (pogledajte [Izrada potpunog klona](#making-a-full-clone-reads-the-seed-off-your-original)).
- [Seed Capturer](/hr/subghz/seed-capturer) + qUnleashed.
:::

### S ispravnim daljinskim upravljačem

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Stanite najmanje 3 m od prijamnika.
3. **Izvorni daljinski upravljač:** pritisnite skriveni gumb sa stražnje strane iglom ili pritisnite gumbe 1 i 2 zajedno dok LED na upravljaču ne zasvijetli.
4. **Izvorni daljinski upravljač:** kratko pritisnite gumb koji otvara uređaj.
5. Na Flipperu dugo držite <kbd>→</kbd> (`0xF`, prikazano kao `Btn:F`) 3–5 s.
6. Pritisnite tipku Flippera koju želite koristiti za otvaranje uređaja.
7. Ponovno pritisnite <kbd>→</kbd>.
8. Done?

### Uz pristup kućištu prijamnika

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Otvorite kućište pločice prijamnika.
3. [Prvo pogledajte ovaj videozapis](https://www.youtube.com/watch?v=5QXMBKI_-Ls). Prikazuje postupak sa strane pločice.
4. Na Flipperu dugo držite <kbd>→</kbd> (`0xF`) 3–5 s. To radi upravo ono što u videozapisu radi držanje gumbiju 1 i 2 na izvornom daljinskom upravljaču.
5. Done?

### Izrada potpunog klona (čita Seed s vašeg izvornog upravljača) {#making-a-full-clone-reads-the-seed-off-your-original}

::: danger
Time se izrađuje kopija koja se **nadmeće s vašim izvornim daljinskim upravljačem** oko brojača. Vaš izvorni upravljač može čak prestati raditi dok se ponovno ne registrira. Radite ovo samo ako je izvorni oštećen ili istrošen i Flipper ga treba zamijeniti.
:::

1. Otvorite `Sub-GHz → Read`.
2. **Samo na izvornom daljinskom upravljaču:** držite sve gumbe odjednom (oba na upravljaču s 2 gumba, gornja dva na upravljaču s 4 gumba) ili pritisnite skriveni gumb iglom.
3. Primate signal. Otvorite ga i pogledajte `Fix:`. Počinje s `F`, primjerice `F00F1C9B`. Vodeće `F` jest kôd gumba za "pritisnut gumb za programiranje".
4. Vrijednost `Hop:` tog istog signala jest vaš Seed.
5. Zapišite vrijednost `Hop` i zamijenite njezinu prvu znamenku `F` s `0`.
6. Sada pritisnite gumb na daljinskom upravljaču koji zapravo želite klonirati i pročitajte taj signal.
7. Zapišite njegov `Fix:`. Njegova prva znamenka odgovara oznaci `Btn:` prikazanoj za signal.
8. Izradite daljinski upravljač pomoću `Sub-GHz → Add Manually [Advanced] → BFT Mitto → 433.92 AM650` i unesite:
   - `SERIAL`: `Fix` iz koraka 7 kojem je **prva** znamenka zamijenjena s `0`
   - `BUTTON`: prva znamenka tog `Fix`
   - `COUNTER`: `FF F9`
   - `SEED`: vrijednost iz koraka 5
9. Visoki brojač poput `FF F9` preskače brojač vašeg izvornog upravljača. Zbog toga klon odmah radi, a ujedno desinkronizira izvorni upravljač.

**Ili umjesto toga uredite spremljenu datoteku.** Spremite signal svog izvornog daljinskog upravljača (stariji je naveden kao `KL: Unknown`), kopirajte datoteku na računalo i dodajte ova dva retka nakon retka `Key: ...`:

```text
Seed: 0X XX XX XX
Manufacture: BFT
```

Zamijenite `X`-ove znamenkama Seeda iz koraka 4 i kopirajte datoteku natrag. Sada imate točan klon s istim brojačem.

### Nema skrivenog gumba ili ne želi poslati Seed

Ovo vrijedi samo za daljinske upravljače s jedinstvenim Seedom. Daljinski upravljač koji se već čita kao `KL: BFT` nema što oporavljati. Ako izvorni ne možete prebaciti u način programiranja, upotrijebite aplikaciju [Seed Capturer](/hr/subghz/seed-capturer): odaberite `BFT Mitto` na 433.92 MHz, pritišćite jedan gumb više puta, zatim oporavite Seed u aplikaciji qUnleashed.

## CAME Atomo

- **Prodaje se i kao:** TOP42R / TOP44R / TOP44RGR (806TS-0130)
- **Izrada:** `Sub-GHz → Add Manually → CAME Atomo → 433.92 AM650` (ili `868.35 AM650`)

::: warning
Kod sustava CAME Atomo uvijek držite `Send` **najmanje 2 sekunde**. Protokol treba toliko vremena da pošalje cijeli kôd.
:::

### S ispravnim daljinskim upravljačem (ili njegovom kopijom na Flipperu)

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Stanite najmanje 3 m od prijamnika.
3. **Izvorni daljinski upravljač:** pritisnite i držite gumb povezan s tim prijamnikom oko 10 s.
4. Sada imate oko 20 s za dodavanje novog daljinskog upravljača.
5. Dugo držite `Send` u datoteci novog daljinskog upravljača 3–4 s i otpustite. Time se registrira.
6. Pričekajte 20 s, zatim ponovno pritisnite i držite `Send`. Sada bi trebao upravljati prijamnikom.
7. Done!

### Uz pristup kućištu prijamnika

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Otvorite kućište prijamnika i pronađite gumb za programiranje za kanal koji trebate. Neki prijamnici imaju više kanala. Primjerice, RE432M / RE862M ima dva, svaki sa svojim daljinskim upravljačima i gumbima. Pritisnite `1` ili `2` na pločici za ulazak u način programiranja tog kanala.
3. Dugo držite `Send` na Flipperu 3–4 s i otpustite.
4. Pritisnite `CLEAR` jednom za izlaz iz načina programiranja ili pričekajte oko 20 s.
5. Done!

::: info
Statički 12/24-bitni daljinski upravljači CAME i CAME TWEE ne mogu otvoriti način programiranja i ne mogu se registrirati u prozor koji je otvorio daljinski upravljač Atomo. To mogu samo upravljači Atomo.
:::

[Video upute (ruski)](https://www.youtube.com/watch?v=XeHUwfcSS30)

## Cardin S449

- **Prodaje se i kao:** S449 QZ1 / QZ2 / QZ4, TXQ449100 / TXQ449200. Prijamnici RCQ449.
- **Čitanje pomoću:** modulacije `FM12K`, **ne** AM650
- **Izrada:** `Sub-GHz → Add Manually → KL: Cardin S449 → 433.92 FM12K`
- **Tipka za programiranje:** <kbd>→</kbd> = `0xD` (na izvornom upravljaču gumb u maloj rupici ispod tipki)

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Stanite 1–2 m od prijamnika.
3. Otvorite datoteku daljinskog upravljača koji već radi. Pritisnite <kbd>→</kbd> i otpustite kada prijamnik kratko zapišti.
4. Pritisnite `Send` na tom istom daljinskom upravljaču jednom. Prijamnik daje još jedan kratak zvučni signal.
5. Otvorite datoteku novog daljinskog upravljača i pritisnite `Send`. Prijamnik zapišti dvaput zaredom.
6. Otpustite tipku. Prijamnik daje jedan dulji zvučni signal.
7. Pričekajte najmanje 10 s, zatim isprobajte novi daljinski upravljač.
8. Done?

**Ako ne uspije** ili čujete dugi zvučni signal prije koraka 5, pričekajte 20 s i počnite ponovno od koraka 3.

## DEA Mio

- **Izrada:** `Sub-GHz → Add Manually → KL: DEA Mio → 433.92 AM650`
- **Tipka za programiranje:** <kbd>→</kbd> = `0xF`, skriveni gumb

1. Otvorite datoteku svog novog daljinskog upravljača.
2. `Send` djeluje kao jedan od uobičajenih gumbiju. Njega registrirate.
3. <kbd>→</kbd> djeluje kao skriveni gumb izvornog daljinskog upravljača.
4. Slijedite upute proizvođača za dodavanje daljinskog upravljača, koristeći ove dvije tipke umjesto gumbiju izvornog upravljača.

## Ditec GOL4

- **Prodaje se i kao:** GOL4 / GOL4C. Prijamnici BIXLG4, BIXLP2, BIXLS2, BIXR2.
- **Izrada:** `Sub-GHz → Add Manually → Ditec GOL4 → 433.92 AM650`
- **Tipka za programiranje:** <kbd>→</kbd> = `0x0`, skriveni gumb

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Otvorite kućište prijamnika. Pritisnite i otpustite `PRG`. LED `SIG` zasvijetli i ostane uključen.
3. Pritisnite `Send` na Flipperu za kanal koji želite pohraniti.
4. `SIG` treperi tijekom pohranjivanja. Kada ponovno svijetli stalno, možete dodati još jedan daljinski upravljač.
5. Pohranjivanje završava 10 s nakon zadnjeg daljinskog upravljača, ili ponovno pritisnite `PRG` za trenutačni izlaz.
6. Done?

::: info
Na nekim pločicama mora biti postavljen kratkospojnik na prijamniku da bi programiranje uopće radilo. Provjerite priručnik svog prijamnika.
:::

## DoorHan

- **Izrada:** `Sub-GHz → Add Manually → KL: DoorHan → 433.92 AM650` (ili `315.00 AM650`)

### Prvo pronađite svoju frekvenciju

DoorHan koristi 315.00 ili 433.92 MHz. Izradite daljinski upravljač na jednoj od njih, otvorite ga i pritisnite `Send` dok gledate prijamnik. Ako ste pogodili, lampica na prijamniku svijetli dok držite tipku i gasi se kad je otpustite. Ako se ništa ne događa, pokušajte s drugim pojasom. Također možete pročitati postojeći daljinski upravljač putem `Sub-GHz → Read`.

### Uz pristup kućištu prijamnika

Skinite zaštitni poklopac i pogledajte gumbe:

- **4 gumba (`Radio`, `Reverse`, `Auto`, …):** držite `Radio` dok LED ne zasvijetli, zatim pritisnite `Send` na Flipperu 2 puta. LED se gasi.
- **4 gumba (`R`, `P`, `+`, `-`) i zaslon:** pritisnite `R`, pritisnite `Send` 2 puta, pričekajte oko 10 s.
- **4 gumba (`+`, `-`, `F`, `TR`) i zaslon:** pritisnite `TR`, pritisnite `Send` 2 puta, pričekajte oko 10 s.
- **Sve ostalo:** držite `P` oko 2 s dok LED ne zatreperi, zatim pritisnite `Send` 2 puta. LED se gasi.

U svim slučajevima pričekajte da se prijamnik vrati u normalan način rada prije testiranja.

### S izvornim daljinskim upravljačem u ruci

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Stanite 1–2 m od pločice prijamnika.
3. Na starom daljinskom upravljaču pritisnite i držite drugi (donji) gumb, zatim pritisnite i prvi (gornji). Držite oba 1 s i otpustite.
4. Pritisnite ispravni gumb na starom daljinskom upravljaču (onaj koji otvara vrata). Držite ga 1 s i otpustite.
5. Koraci 3 i 4 moraju se obaviti unutar 5 s jedan od drugoga. Nemojte držati predugo i nemojte žuriti.
6. Prijamnik zapišti. Sada imate 10 s: pritisnite `Send` na novom daljinskom upravljaču 2 puta, držeći svaki put najmanje 1 s.
7. Prijamnik ponovno zapišti. Novi daljinski upravljač je registriran.
8. Done!

### S kopijom vašeg izvornog daljinskog upravljača na Flipperu

1. Otvorite datoteku svog **postojećeg (izvornog)** daljinskog upravljača.
2. Stanite 1–2 m od pločice prijamnika.
3. Pritisnite <kbd>←</kbd> (`0x8`), držite 1 s, otpustite. Zatim pritisnite <kbd>→</kbd> (`0xA`), držite 1 s, otpustite.
4. Pritisnite ispravni gumb (<kbd>OK</kbd>, `Send`), držite 1 s, otpustite.
5. Koraci 3 i 4 moraju se obaviti unutar 5 s jedan od drugoga.
6. Prijamnik zapišti. Pritisnite <kbd>Back</kbd> i otvorite datoteku svog **novog** daljinskog upravljača. Unutar 10 s pritisnite `Send` 2 puta, držeći svaki put najmanje 1 s.
7. Prijamnik ponovno zapišti. Novi daljinski upravljač je registriran.
8. Done!

[Video upute (ruski)](https://www.youtube.com/watch?v=wZ5121HYv50) i [drugi videozapis](https://www.youtube.com/watch?v=1ucrDKF3vWc)

::: tip
Ako se prijamnik DoorHan razišao u sinkronizaciji s vašom datotekom, Unleashed ima načine brojača za prisilnu resinkronizaciju za DoorHan. Pogledajte [Načini brojača](/hr/subghz/counter-mode).
:::

## Erreka IRIS

- **Prodaje se i kao:** IRIS IR02 / IR04 na 433.92 MHz, IR02/868 / IR04/868 na 868.35 MHz
- **Izrada:** `Sub-GHz → Add Manually → Erreka → 433.92 AM650` za IR02 / IR04, ili `868.35 AM650` za modele /868
- **Tipka za programiranje:** <kbd>→</kbd> = `0xF` (na izvornom upravljaču premošćivanje pinova `1` i `5` 5-pinskog priključka izloženog sa strane daljinskog upravljača)

Erreka IRIS je daljinski upravljač s promjenjivim kodom: KeeLoq s tajnim Seedom. Oba proizvođačeva načina registracije rade s Flippera.

### Uz pristup kućištu prijamnika

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Aktivirajte način programiranja na prijamniku, obično gumbom na pločici.
3. Jednom pritisnite `Send` na Flipperu. Prijamnik zapišti **dvaput** ako je daljinski upravljač pohranjen.
4. Ponovite korak 3 za sve ostale daljinske upravljače.
5. Isključite način programiranja.
6. Done!

### S ispravnim daljinskim upravljačem

Izvorni IRIS otvara prozor programiranja kada premostite pinove `1` i `5`. Tada šalje svoj Seed u otvorenom obliku, a prijamnik odgovara jednim zvučnim signalom. Na Flipperu to radi <kbd>→</kbd>.

Daljinski upravljač koji otvara prozor mora biti onaj koji prijamnik već poznaje: ili prvi Flipperov daljinski upravljač koji ste registrirali gumbom na prijamniku, ili vaš izvorni daljinski upravljač s oporavljenim Seedom (pogledajte u nastavku).

1. Otvorite datoteku registriranog daljinskog upravljača Erreka.
2. Dugo držite <kbd>→</kbd> (`0xF`) oko 2 s. Prijamnik zapišti **jednom** i spreman je za pohranu kodova.
3. Unutar 10 s pritisnite <kbd>Back</kbd> i otvorite datoteku novog daljinskog upravljača.
4. Pritisnite `Send`. Prijamnik zapišti **dvaput** ako je daljinski upravljač pohranjen.
5. Ako prođe 10 s bez pohranjivanja, prijamnik izlazi iz načina programiranja. Počnite ponovno od koraka 2.
6. Done?

### Ako se novi daljinski upravljač ne želi registrirati

Neke instalacije daju **svakom daljinskom upravljaču isti Seed** jer ih je instalater programirao kao komplet. Na takvima daljinski upravljač s nasumičnim Seedom nikada nije prihvaćen. Rješenje je zadržati postojeći Seed i promijeniti samo serijski broj:

1. Dobavite Seed s daljinskog upravljača koji već radi (pogledajte u nastavku).
2. Izradite daljinski upravljač putem `Sub-GHz → Add Manually [Advanced] → Erreka → 433.92 AM650` (ili `868.35 AM650`) i unesite:
   - `SERIAL`: `0X XX XX XX`, bilo koja vrijednost koja nije nijedan od vaših postojećih daljinskih upravljača. **Zadržite vodeću `0`**. Taj polubajt je gumb, koji se unosi zasebno.
   - `BUTTON`: `02`
   - `COUNTER`: `00 02`
   - `SEED`: Seed iz koraka 1
3. Ponovno provedite bilo koji postupak registracije.

::: tip Zadržite vodeće nule
Neki sustavi koriste samo donje 3 ili 4 znamenke serijskog broja, pa njihovi daljinski upravljači izgledaju kao `00 00 0A BC`. Na takvima dugi nasumični serijski broj može biti odbijen. Pročitajte jedan od svojih ispravnih daljinskih upravljača, kopirajte oblik njegova serijskog broja (isti broj značajnih znamenki, vodeće nule zadržane) i promijenite samo zadnje znamenke. Ako dva vaša izvorna daljinska upravljača nakon oporavka pokazuju isti Seed, imate ovakvu instalaciju i ponovna upotreba Seeda pravi je potez.
:::

### Dobivanje Seeda s vašeg izvornog IRIS daljinskog upravljača

Daljinski upravljač Erreka čita se kao `KL: Unknown` dok Seed nije poznat.

**Mogućnost 1: kratko spojite pinove i pročitajte ga.** Ovo je brzi način. Pinovi su na vanjskoj strani kućišta.

1. Otvorite `Sub-GHz → Read`. U `Config` postavite frekvenciju na 433.92 ili 868.35 i modulaciju na `AM650`.
2. Premostite pinove `1` i `5` 5-pinskog priključka na izvornom daljinskom upravljaču.
3. Primate signal. Proizvođač se prikazuje kao **Unknown**. To je očekivano, jer Flipper još ne zna Seed.
4. Otvorite signal. `Fix:` počinje s `F`, kodom "pritisnut gumb za programiranje".
5. **Vrijednost `Hop:` tog signala jest vaš Seed**, u otvorenom obliku.
6. Ili ga upišite u `Add Manually [Advanced]` kao gore, ili spremite signal, kopirajte ga na računalo i dodajte ove retke nakon `Key: ...`:

```text
Seed: 0X XX XX XX
Manufacture: Erreka
```

Datoteka se sada dekodira i možete je koristiti za otvaranje prozora programiranja za nove daljinske upravljače.

**Mogućnost 2: [Seed Capturer](/hr/subghz/seed-capturer)**, kada ne možete premostiti pinove. Odaberite `Erreka` i svoju frekvenciju, pritišćite jedan gumb više puta, zatim oporavite Seed u aplikaciji qUnleashed.

## FAAC RC, XT

- **Prodaje se i kao:** XT2 / XT4 433 RC / 868 RC te starije kodiranje RC
- **Izrada:** `Sub-GHz → Add Manually → KL: FAAC RC,XT → 433.92 AM650` (ili `868.35 AM650`)
- **Tipka za programiranje:** <kbd>→</kbd> = `0xB` (na izvornom upravljaču gumbi 1+2 držani zajedno, pritisak "master")

::: warning
Ovo je KeeLoq, a ne SLH. Prvo pročitajte svoj daljinski upravljač. Ako ga Flipper naziva `KL: FAAC_RC,XT`, na pravom ste mjestu. Ako piše `FAAC SLH`, idite na [FAAC SLH](#faac-slh).
:::

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Stanite blizu prijamnika.
3. Otvorite datoteku daljinskog upravljača koji već radi. Pritisnite <kbd>→</kbd> i držite oko 1–2 s (dok LED izvornog upravljača ne bi počeo treperiti), zatim otpustite.
4. Dok je prozor otvoren, pritisnite `Send` na tom istom daljinskom upravljaču za gumb koji želite kopirati.
5. Otvorite datoteku novog daljinskog upravljača i pritisnite `Send`.
6. Ponovite korake 3–5 za svaki drugi gumb.
7. Done?

::: info
Samo **master** daljinski upravljač može predati svoj kôd sustava. Na izvornom daljinskom upravljaču promatrajte LED kada pritisnete gumb. Kratak treptaj prije nego što stalno zasvijetli znači master. Ako odmah zasvijetli stalno, riječ je o slave upravljaču. Kod slave upravljača registrirajte novi daljinski upravljač izravno na prijamniku.
:::

## FAAC SLH

- **Izrada:** `Sub-GHz → Add Manually → FAAC SLH → 433.92 AM650` (ili `868.35 AM650`)
- **Tipka za programiranje:** **<kbd>↑</kbd>** šalje signal za programiranje

### Uz pristup kućištu prijamnika

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Otvorite kućište prijamnika i pronađite gumb za programiranje na pločici.
3. Držite <kbd>↑</kbd> na Flipperu i istodobno pritisnite i držite gumb za programiranje na pločici.
4. LED na pločici se uključi, ugasi, uključi, ugasi, pa ponovno uključi.
5. Sve otpustite.
6. Pritisnite `Send` na Flipperu nekoliko puta, držeći svaki pritisak 1–3 s.
7. Done!

[Video upute](https://www.youtube.com/watch?v=NfZmMy37XUs)

### S master daljinskim upravljačem, bez otvaranja kućišta

FAAC može registrirati nove daljinske upravljače iz postojećeg master daljinskog upravljača, a Flipper u tome može sudjelovati. Prvo pročitajte Seed s master upravljača:

1. Otvorite `Sub-GHz → Read`. Postavite frekvenciju na 868.35 ili 433.92 i modulaciju na `AM650`.
2. Držite dva gumba na izvornom master daljinskom upravljaču dok se njegov LED ne uključi.
3. Kliknite onaj jedan gumb za koji želite Seed. **Seed je različit za svaki gumb.**
4. Primate signal. Otvorite ga i zabilježite Seed.
5. Izradite daljinski upravljač putem `Sub-GHz → Add Manually [Advanced] → FAAC SLH → 433.92 AM650` (ili `868.35`) i unesite:
   - `SERIAL`: `0A 0R RR RR`, zamjenjujući svaki `R` bilo kojom znamenkom
   - `BUTTON`: `06`
   - `COUNTER`: `00 00 00 02`
   - `SEED`: Seed iz koraka 4
6. Flipper sada djeluje kao novi daljinski upravljač. Pritisnite `Send` nekoliko puta blizu prijamnika kako biste ga registrirali.
7. Done!

### Ako nijedno od toga nije moguće

- **Programiranje daljinskih upravljača na prijamniku je onemogućeno.** Neki instalateri ga isključe i tada se ništa ne registrira.
- **Vaš je daljinski upravljač slave, a ne master.** Samo master može poslati kôd za programiranje.

U oba slučaja jedini preostali put jest **klon** daljinskog upravljača koji prijamnik već poznaje, a za to je potreban Seed. Dobavite ga putem aplikacije [Seed Capturer](/hr/subghz/seed-capturer), zatim izradite klon s vrijednostima `SERIAL` i `BUTTON` **izvornog daljinskog upravljača**.

::: tip Gdje se SERIAL i BUTTON nalaze unutar Fix
- **FAAC SLH i Genius:** `BUTTON` je **zadnja** znamenka od `Fix`. `SERIAL` je ostatak, s `0` ispred.
- **KeeLoq** (BFT, Erreka, DoorHan, Cardin i ostale `KL:` stavke): `BUTTON` je **prva** znamenka od `Fix`. `SERIAL` je isti `Fix` kojem je prva znamenka zamijenjena s `0`.
:::

## Genius (SLH)

- **Prodaje se i kao:** Echo TX2 433 SLH / Echo TX4 433 SLH / KILO TX2 / TX4 / JLC / Amigo
- **Izrada:** `Sub-GHz → Add Manually → Genius → 433.92 AM650` (ili `868.35 AM650`)
- **Tipka za programiranje:** **<kbd>↑</kbd>** šalje signal za programiranje

Genius SLH ima isti okvir signala kao FAAC SLH s vlastitim ključem proizvođača (redak `Manufacture: Genius` u datoteci), pa **[postupci za FAAC SLH](#faac-slh) vrijede točno kako su napisani**. Ako je programiranje onemogućeno ili je vaš daljinski upravljač slave, uhvatite Seed aplikacijom [Seed Capturer](/hr/subghz/seed-capturer) (odaberite `Genius`) i izradite klon kako je opisano pod FAAC SLH.

::: warning
Ne miješajte ovo s `KL: Genius TX4RC`. Modeli RC su KeeLoq, a ne SLH, i imaju [vlastiti odjeljak](#genius-tx4rc-bravo-echo). Ako niste sigurni, prvo pročitajte daljinski upravljač.
:::

## Genius TX4RC (Bravo / Echo)

- **Prodaje se i kao:** Echo TX2 433 RC / Echo TX4 433 RC / TE443H Bravo
- **Izrada:** `Sub-GHz → Add Manually → KL: Genius TX4RC → 433.92 AM650`
- **Tipka za programiranje:** <kbd>→</kbd> = `0xB`

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Otvorite kućište prijamnika i pritisnite `SW1` za kanal 1 ili `SW2` za kanal 2. `LED1` / `LED2` zasvijetli i ostane uključen. To je način učenja.
3. Unutar 10 s pritisnite `Send` na Flipperu i držite najmanje 1 s.
4. LED zatreperi dvaput. Daljinski upravljač je pohranjen.
5. Prijamnik ostaje u načinu učenja, pa možete dodati još daljinskih upravljača ponavljanjem koraka 3. Ponovno pritisnite `SW1` / `SW2` za izlaz, ili će sam izaći 10 s nakon zadnjeg daljinskog upravljača.
6. Done?

## Hormann EcoStar

- **Prodaje se i kao:** RSC2 / RSE2 / RSZ1 na 433.92 MHz. Pogoni EcoStar Liftronic / Portronic.
- **Izrada:** `Sub-GHz → Add Manually → KL: Hor. EcoStar → 433.92 AM650`
- **Tipka za programiranje:** **<kbd>↓</kbd>** = `0x6` (ovdje je na Dolje, a ne Desno)

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Pronađite prozirni gumb za programiranje na pogonu, obično ispod motora, i držite ga oko 1 s. LED motora počinje polako treperiti.
3. Pritisnite `Send` i držite oko 2 s. LED motora ubrzava.
4. Ponovno pritisnite `Send` i držite oko 2 s. LED treperi vrlo brzo, zatim se gasi. Daljinski upravljač je programiran.
5. Done?

::: danger
Držanje tog prozirnog gumba oko 5 s briše **svaki** daljinski upravljač koji pogon poznaje.
:::

## Jarolift

- **Prodaje se i kao:** TDEF cijevni radijski motori s daljinskim upravljačima TDRC / TDRCE
- **Izrada:** `Sub-GHz → Add Manually → Jarolift → 433.92 AM650`

Tipke su već preslikane na gumbe izvornog daljinskog upravljača:

| Tipka Flippera | Gumb Jarolift |
|---|---|
| <kbd>OK</kbd> (`Send`) | Down |
| <kbd>←</kbd> | Up |
| <kbd>↓</kbd> | Stop |
| **<kbd>↑</kbd>** | **Learn** (`0x1`) |

Na izvornom upravljaču `Learn` znači držanje Up + Down zajedno, a zatim pritisak Stop. Na Flipperu je to pritisak jedne tipke.

### Uz pristup glavi motora

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Pritisnite gumb za učenje na glavi motora. Motor kratko zavibrira i ostaje u načinu učenja 5 s.
3. Ako ne možete dosegnuti taj gumb, odspojite motor iz struje i ponovno ga priključite. Sam ulazi u način učenja na 5 s.
4. Unutar tih 5 s pritisnite <kbd>↑</kbd> (`Learn`).
5. Motor ponovno zavibrira. Kôd je naučen.
6. Done!

### S ispravnim daljinskim upravljačem

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Na ispravnom daljinskom upravljaču držite Up + Down zajedno, zatim pritisnite Stop 8 puta. Motor kratko zavibrira.
3. Unutar 5 s pritisnite <kbd>↑</kbd> (`Learn`) na Flipperu.
4. Motor ponovno zavibrira.
5. Done?

::: tip
Ako je ispravni daljinski upravljač također na vašem Flipperu, korak 2 je <kbd>↑</kbd> (`Learn`) u datoteci tog daljinskog upravljača.
:::

## KingGates Stylo 4k

- **Prodaje se i kao:** Stylo 2K / Stylo 4K (10S001). Prijamnici Fred, Myo.
- **Izrada:** `Sub-GHz → Add Manually → KingGates Stylo4k → 433.92 AM650`

Ne postoji zaseban gumb za programiranje. Četiri tipke predstavljaju četiri kanala izvornika:

| Tipka Flippera | Kôd kanala |
|---|---|
| <kbd>OK</kbd> (`Send`) | `0xE` |
| <kbd>↑</kbd> | `0xD` |
| <kbd>↓</kbd> | `0xB` |
| <kbd>←</kbd> | `0x7` |

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Otvorite kućište prijamnika. Na dvokanalnom modelu `Fred` boja LED-a pokazuje kanal: zelena je kanal 1, crvena je kanal 2.
3. Pritisnite gumb prijamnika jednom za kanal 1 (zeleno) ili dvaput za kanal 2 (crveno). Time se pokreće način učenja.
4. Unutar 5 s pritisnite `Send` na Flipperu oko 1 s.
5. LED se ugasi, a zatim ponovno uključi. Daljinski upravljač je naučen.
6. Učenje završava nakon 5 s bez signala, ili ponovno pritisnite gumb prijamnika.
7. Done?

## Mhouse

- **Prodaje se i kao:** GTX4 / GTX4C / TX3 / TX4, također Moovo i Nice Home ECCO
- **Izrada:** `Sub-GHz → Add Manually → KL: Mhouse → 433.92 AM650`
- **Tipka za programiranje:** <kbd>→</kbd> = `0xF`, dodatni (skriveni) gumb

### Uz pristup kućištu prijamnika

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Pritisnite i držite `P1` na prijamniku dok LED `P1` ne ostane uključen, zatim otpustite.
3. Pritisnite `Send` i držite dok LED `P1` ne zatreperi 3 puta.
4. Otpustite. Time se registriraju svi gumbi daljinskog upravljača odjednom (Nice "mode 1").
5. Pričekajte 10 s prije testiranja.
6. Done?

### S ispravnim daljinskim upravljačem

Mhouse pripada istoj obitelji prijamnika Nice kao i [Nice Smilo](#nice-smilo):

1. Stanite blizu prijamnika.
2. Otvorite datoteku svog novog daljinskog upravljača. Pritisnite i držite `Send` najmanje 5 s, zatim otpustite.
3. Na ispravnom daljinskom upravljaču pritisnite i polako otpustite njegov gumb 3 puta.
4. Ponovno otvorite datoteku novog daljinskog upravljača, pritisnite `Send` na 1 s i otpustite.
5. Pričekajte 10 s prije testiranja.
6. Done?

## Nice Flor S

- **Izrada:** `Sub-GHz → Add Manually → Nice FloR-S → 433.92 AM650`

### S ispravnim daljinskim upravljačem

Ne trebate kućište prijamnika, ali **vrlo prvi daljinski upravljač uvijek mora biti registriran gumbom na prijamniku**. U nastavku je `OLD` ovlašteni daljinski upravljač, a `NEW` je Flipper. Stanite unutar 3 m od prijamnika.

1. Otvorite datoteku svog novog daljinskog upravljača. Pritisnite i držite `Send` najmanje 5 s (7 s na prijamniku OXIBD), zatim otpustite.
2. Na upravljaču `OLD` polako pritisnite njegov gumb 3 puta.
3. Polako pritisnite `Send` na Flipperu, zatim otpustite.
4. Pričekajte 10 s, zatim pritisnite `Send` za testiranje.
5. Done?

### Uz pristup kućištu prijamnika

Registrirajte ga na način opisan u priručniku vašeg izvornog daljinskog upravljača. Za tipičan prijamnik NICE FLOX2R:

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Pritisnite gumb za učenje na prijamniku 1–2 s. LED se uključuje na 5 s. Sljedeći korak obavite unutar tih 5 s.
3. Držite `Send` dok se LED na prijamniku ne ugasi.
4. Otpustite i pričekajte 2 s.
5. Ponovno pritisnite `Send`. LED zatreperi 3 puta i daljinski upravljač je registriran. Ako nije, počnite iznova od koraka 2.
6. Pričekajte 5 s, zatim pritisnite `Send` za testiranje.
7. Done!

::: tip
Varijante brojača Nice Flor-S za pojedine prijamnike (floxi2r, ox2) dostupne su kao [načini brojača](/hr/subghz/counter-mode).
:::

## Nice One

- **Izrada:** `Sub-GHz → Add Manually → Nice One → 433.92 AM650`

Nice One pripada obitelji Nice FloR-S s drukčijim ključem, a strana prijamnika je identična. **[Oba postupka za Nice Flor S](#nice-flor-s) vrijede točno kako su napisana.** Ako se vaš daljinski upravljač čita kao FloR-S, ali brojač izgleda pogrešno, možda je riječ o sustavu Nice O-Code.

## Nice O-Code

- **Izrada:** `Sub-GHz → Add Manually → Nice O-Code → 433.92 AM650` (ili `Nice O-Code One` za kodiranje Nice One)
- **Izrada za instalirani sustav:** `Sub-GHz → Add Manually [Advanced] → Nice O-Code → 433.92 AM650`, što traži `SERIAL`, `BUTTON`, `COUNTER` i instalaterski kôd (`Enter IC in hex`)
- **Izrada s certifikatom:** `Sub-GHz → Add Manually → Nice O-Code+Crt → 433.92 AM650`, što uvijek traži serijski broj, gumb, brojač, instalaterski kôd **i** certifikat prijamnika (`Enter CERT in hex`)

O-Code je Nice FloR-S kodiran 16-bitnim **instalaterskim kodom (IC)** koji dijele svi daljinski upravljači jedne instalacije. Strana prijamnika ista je kao kod FloR-S, pa vrijede [oba postupka za Nice Flor S](#nice-flor-s), ali daljinski upravljač dopire samo do prijamnika postavljenog s istim instalaterskim kodom.

- **Za vlastiti sustav**, obični `Nice O-Code` izmišlja instalaterski kôd uz serijski broj. Tvornički prijamnik ga neće prihvatiti na gumbu, stoga prvo registrirajte običan daljinski upravljač [Nice One](#nice-one).
- **Za instalirani sustav**, oporavite instalaterski kôd s ispravnog daljinskog upravljača pomoću [aplikacije Nice O-Code](/hr/subghz/nice-o-code) (`Apps → Sub-GHz → Nice O-Code`). Pritisnite gumb daljinskog upravljača 4 ili više puta (nemojte ga držati). Na zaslonu rezultata <kbd>→</kbd> (`New`) zapisuje novi daljinski upravljač s istim instalaterskim kodom i gumbom, ali vlastitim serijskim brojem i brojačem. Taj registrirate. `Save` zapisuje običan klon za testiranje.

::: info Testirano na tvornički novom prijamniku OXIBD
U načinu I prijamnik **potpuno zanemaruje okvire O-Code**, bez obzira na to koji instalaterski kôd nose, dok se običan daljinski upravljač `Nice One` odmah pamti. Samo O-Box zapisuje instalaterski kôd u prijamnik. Na nedirnutom prijamniku koristite obične stavke Nice Flor S / Nice One.
:::

::: tip COUNTER
**Nemojte** ostavljati `COUNTER` blizu nule. Prijamnik odbija broj iza onoga koji je pohranio, kao i onaj koji je nevjerojatno daleko iza daljinskih upravljača koje poznaje, čak i za novi serijski broj. Postavite ga malo ispod broja vašeg ispravnog daljinskog upravljača (`New` u aplikaciji to čini umjesto vas). Ako ste već slali okvire s tog serijskog broja, upotrijebite vrijednost malo iznad najviše koju ste poslali.
:::

**Upis putem certifikata.** Daljinski upravljač koji nosi certifikat prijamnika šalje 112-bitne okvire tijekom prvih **dvadeset** korištenja i prijamnik ga sam upisuje. Otvorite datoteku u dometu vrata i pritisnite tipku otprilike jednom u sekundi, **deset do petnaest puta zaredom**. Vrata se otvaraju oko desetog pritiska i nakon toga je daljinski upravljač trajno registriran. Ako prođe svih dvadeset korištenja bez otvaranja vrata, izbrišite datoteku i napravite novu. Certifikati, pet Nice puteva registracije, LED kodovi prijamnika i prozor brojača detaljno su obrađeni na stranici [Nice O-Code](/hr/subghz/nice-o-code).

## Nice Smilo

- **Prodaje se i kao:** SM2 / SM4. Prijamnici SMXI, SMXIS i OXI postavljeni na kodiranje Smilo.
- **Izrada:** `Sub-GHz → Add Manually → KL: Nice Smilo → 433.92 AM650`
- **Tipka za programiranje:** <kbd>→</kbd> = `0xB`, dodatni (skriveni) gumb

Prijamnici Nice pohranjuju daljinski upravljač u jednom od dva načina. **Mode I** svakom gumbu daljinskog upravljača dodjeljuje odgovarajući izlaz prijamnika. **Mode II** omogućuje vam da odaberete kojim izlazom upravlja jedan gumb.

### Uz pristup kućištu prijamnika: mode I

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Pritisnite i držite gumb na prijamniku najmanje 3 s.
3. Otpustite ga kada LED zasvijetli.
4. Unutar 10 s pritisnite `Send` i držite najmanje 2 s.
5. LED na prijamniku zatreperi 3 puta. Daljinski upravljač je pohranjen.
6. Za dodavanje još upravljača ponovite korak 4 unutar sljedećih 10 s.
7. Done!

### Uz pristup kućištu prijamnika: mode II

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Pritisnite gumb na prijamniku onoliko puta koliki je broj izlaza (dvaput za izlaz 2).
3. Provjerite treperi li LED isti broj puta.
4. Unutar 10 s pritisnite tipku Flippera koju želite za taj izlaz i držite najmanje 2 s.
5. LED zatreperi 3 puta. Daljinski upravljač je pohranjen.
6. Done!

### S ispravnim daljinskim upravljačem

Prvi daljinski upravljač uvijek mora biti registriran gumbom na prijamniku. Novi daljinski upravljač **nasljeđuje način** staroga, pa kod načina mode II pritišćete odgovarajuće gumbe na oba.

1. Stanite blizu prijamnika.
2. Otvorite datoteku svog novog daljinskog upravljača. Pritisnite i držite `Send` najmanje 5 s, zatim otpustite.
3. Na ispravnom daljinskom upravljaču pritisnite i polako otpustite njegov gumb 3 puta.
4. Ponovno otvorite novu datoteku te jednom pritisnite i polako otpustite `Send`.
5. Done?

::: info
Ovi prijamnici ne mogu izbrisati jedan daljinski upravljač, već samo sve odjednom.
:::

## Security+ 1.0 / 2.0 (Chamberlain, LiftMaster, Craftsman)

- **Izrada:** `Sub-GHz → Add Manually → Security+2.0` ili `Security+1.0`, zatim pojas. Zadano je `433.92 AM650`. Security+ 1.0 nudi i `315.00 AM650` i `390.00 AM650`. Security+ 2.0 nudi `310.00`, `315.00` i `390.00 AM650`.

**Koji sustav imate?** Pogledajte boju gumba `Learn` na glavi motora:

| Gumb Learn | Izradite ovo |
|---|---|
| Žuti | `Security+2.0` |
| Ljubičasti | `Security+1.0` → `315.00 AM650` |
| Zeleni | `Security+1.0` → `390.00 AM650` |
| Crveni / narančasti | Billion Code, nije Security+ |
| Sivi / bijeli | daljinski upravljač s DIP sklopkama, nije Security+ |

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Pronađite `Learn` na glavi motora: obično na stražnjoj ili bočnoj ploči, ponekad iza poklopca svjetla.
3. Pritisnite ga i otpustite jednom. LED za učenje svijetli stalno 30 s.
4. Unutar tih 30 s pritisnite i držite `Send` na Flipperu.
5. Otpustite kada svjetla motora zatrepere ili čujete dva klika. Daljinski upravljač je programiran.
6. Ponovno pritisnite `Send` kako biste provjerili pomiču li se vrata.
7. Done?

::: tip
Ako gumb na glavi motora ne surađuje, neki sustavi dopuštaju programiranje sa zidne konzole. Za okvire signala tipkovnice Security+ 2.0 pogledajte [Security+ PIN](/hr/subghz/secplus-pin).
:::

## Somfy Keytis

- **Prodaje se i kao:** Keytis NS 2 RTS / KeyGo 4 RTS
- **Izrada:** `Sub-GHz → Add Manually → Somfy Keytis → 433.42 AM650` (ovo je **433.42 MHz**, ne 433.92)
- **Tipka za programiranje:** **<kbd>↑</kbd>** = `0x3`, `Prog` (`Send` je `Key_1`)

Izvorni Keytis nema gumb `Prog` s prednje strane. Odvijačem premošćujete dva kontakta `PROG` na stražnjoj strani pločice. Flipperu je dovoljan samo <kbd>↑</kbd>.

### Uz pristup prijamniku

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Pritisnite i držite `PROG` na prijamniku oko 3 s, dok ne zatreperi.
3. Pritisnite <kbd>↑</kbd> (`Prog`) na Flipperu.
4. Roleta ili vrata kratko se pomaknu gore-dolje. Daljinski upravljač je registriran.
5. Done?

### S ispravnim daljinskim upravljačem

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Prebacite registrirani daljinski upravljač u način programiranja dok se roleta ili vrata kratko ne pomaknu. Na izvornom Keytisu premostite kontakte `PROG`. Na Flipperu pritisnite <kbd>↑</kbd> u datoteci tog daljinskog upravljača.
3. Otvorite datoteku svog novog daljinskog upravljača i pritisnite <kbd>↑</kbd> (`Prog`) dok se roleta ili vrata ponovno kratko ne pomaknu.
4. Done?

::: danger
Na mnogim prijamnicima Somfy držanje gumba za programiranje dulje od otprilike 7 s briše sve daljinske upravljače i senzore koje prijamnik poznaje.
:::

::: info
Keytis koristi noviji radijski protokol `NS`. Stariji RTS prijamnik koji nije NS neće ga prihvatiti dok se protokol daljinskog upravljača ne prebaci. Pogledajte Somfyjevu dokumentaciju za svoj prijamnik.
:::

## Somfy Telis

- **Izrada:** `Sub-GHz → Add Manually → Somfy Telis → 433.42 AM650` (ovo je **433.42 MHz**, ne 433.92)
- **Tipka za programiranje:** **<kbd>←</kbd>** = `0x8`, `Prog`

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Dugo pritisnite `Prog` na daljinskom upravljaču već registriranom na uređaj, dok se rolete kratko ne pomaknu gore-dolje.
3. Pritisnite i držite <kbd>←</kbd> (`Prog`) na Flipperu dok se rolete ponovno kratko ne pomaknu gore-dolje.
4. Done?

## Sommer

- **Prodaje se i kao:** TX03-868-4 / TX03-868-2 (SOMloq). Pogoni Pearl, Duo, Sprint, Marathon.
- **Čitanje pomoću:** modulacije `FM12K` ili `FM476`, ovisno o tome koja dekodira vaš daljinski upravljač
- **Izrada:** `Sub-GHz → Add Manually → KL: Sommer`, zatim odaberite pojas koji odgovara načinu na koji je daljinski upravljač pročitan: `434.42 FM12K` (zadano), `868.80 FM12K`, `434.42 FM476` ili `868.80 FM476`
- **Tipka za programiranje:** <kbd>→</kbd> = `0x6`

::: tip Unleashed
Stariji vodiči navode četiri zasebne stavke za Sommer (`fm2` i običnu). Trenutačni firmver ima jedan redak `KL: Sommer`, a odabir pojasa bira i frekvenciju i varijantu modulacije.
:::

### Uz pristup prijamniku

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Pronađite gumb `learn` / `code` na prijamniku. Na modelu Duo nalazi se ispod poklopca svjetla, na modelu Sprint iza poklopca razvodne kutije, a na modelu Marathon ispod prozirnog plastičnog poklopca pokraj gumba code.
3. Pritisnite ga kratko. LED prijamnika zasvijetli.
4. Pritisnite i držite `Send`. Kad LED prijamnika počne brzo treperiti, otpustite.
5. LED prijamnika se gasi. Daljinski upravljač je programiran.
6. Done?

### Na pogonu kliznih vrata

Umjesto toga pritisnite gumb `Radio` na upravljačkoj jedinici. Crveni LED potvrđuje način programiranja. Pritisnite ga ponovno za odabir kanala, zatim držite `Send` dok LED kanala ne zatreperi i ne ugasi se. Prijamnik sam izlazi iz načina programiranja nakon otprilike 30 s bez signala.

## V2 Phoenix (Phox)

- **Prodaje se i kao:** Phoenix 2/4, Phox 2/4, Handy 2/4, TXC2-4, TRC2-4, TSC2-4. Prijamnici RXP, MR2.
- **Izrada:** `Sub-GHz → Add Manually → V2 Phoenix → 433.92 AM650`
- **Tipka za programiranje:** <kbd>→</kbd> = `0x3` (na izvornom upravljaču gumbi 1+2 ili 1+3 držani zajedno)

::: warning
Ovo mapiranje **još nije potvrđeno**. Ako ne radi, registrirajte gumbom na prijamniku i javite na Unleashed GitHub Issues.
:::

1. Otvorite datoteku svog novog daljinskog upravljača.
2. Otvorite datoteku registriranog daljinskog upravljača. Pritisnite <kbd>→</kbd> i držite najmanje 5 s, zatim otpustite.
3. Unutar 5 s otvorite datoteku novog daljinskog upravljača i pritisnite `Send`.
4. Otpustite. Ponovite za sve ostale gumbe.
5. Done?

Daljinski upravljač koji otvara prozor već mora biti pohranjen u prijamniku i sve pohranjeno na taj način nasljeđuje njegovu logiku. Ako je imao pohranjen samo gumb 1, novi daljinski upravljači mogu se pohraniti samo na gumb 1. Neki prijamnici V2 mogu se prebaciti u način `Static`, koji zanemaruje promjenjivi dio ključa.

---

## Oporavak Seeda

**FAAC SLH**, **Genius**, **Erreka** i **BFT Mitto** grade svoj promjenjivi kôd iz tajnog **Seeda**. Bez njega Flipper ne može dekodirati te daljinske upravljače (čitaju se kao `KL: Unknown` ili nikako) i ne može izraditi daljinski upravljač koji prijamnik prihvaća. Seed vam je potreban kada:

- je radijsko programiranje prijamnika isključeno, pa radi samo klon;
- je vaš daljinski upravljač FAAC/Genius slave i ne može poslati kôd za programiranje;
- ne možete pristupiti prijamniku;
- instalacija Erreka dijeli jedan Seed na svim daljinskim upravljačima;
- stariji BFT Mitto ne želi ući u način programiranja.

Aplikacija [Seed Capturer](/hr/subghz/seed-capturer) (`Apps → Sub-GHz → Seed Capturer`) prikuplja uzastopne parove `Fix` + `Hop` s jednog gumba. Nikada ne odašilje i sprema ih u `/ext/apps_data/subghz_seed_captures/`. Prateća aplikacija qUnleashed (pogledajte [Aplikacija qUnleashed](/hr/mobile/qunleashed-app)) zatim grubom silom pronalazi Seed i može vam zapisati gotovu datoteku klona.

Kada imate Seed:

- **Novi daljinski upravljač** (prijamnik mora prihvaćati nove daljinske upravljače): `Add Manually [Advanced]` → vaš sustav → pojas, vaš vlastiti `SERIAL` i oporavljeni `SEED`.
- **Klon** (radi bez programiranja jer prijamnik već poznaje taj serijski broj): dopustite da ga qUnleashed spremi ili unesite `SERIAL` i `BUTTON` **izvornog upravljača**, `SEED` te `COUNTER` malo iznad trenutačne vrijednosti izvornika.

::: danger
Klon dijeli brojač s izvornim upravljačem i njih će se dvoje nadmetati oko njega. Klonirajte samo kada je izrada novog daljinskog upravljača nemoguća.
:::

## Referentna tablica za programsku / skrivenu tipku {#programming-hidden-button-reference}

Pronađite korak "prebacite prijamnik u način programiranja" u priručniku svog proizvođača. Gdje god vam kaže da nešto pritisnete na izvornom daljinskom upravljaču, umjesto toga pritisnite tipku iz ove tablice.

::: info
Ovo su tipke na daljinskom upravljaču kakav stvara `Add Manually`. Ako ručno promijenite kôd gumba, tipke se pomiču s njim.
:::

| Sustav (stavka u Add Manually) | Kôd | Tipka na Flipperu | Na izvornom daljinskom upravljaču |
|---|---|---|---|
| `FAAC SLH`, `Genius` | – | **<kbd>↑</kbd>** | signal za programiranje |
| `BFT Mitto` | `0xF` | <kbd>→</kbd> | rupica za iglu straga ili gumbi 1+2 držani |
| `Erreka` | `0xF` | <kbd>→</kbd> | premošćeni pinovi 1 i 5 5-pinskog priključka |
| `KL: DEA Mio` | `0xF` | <kbd>→</kbd> | skriveni gumb |
| `KL: Aprimatic` | `0xF` | <kbd>→</kbd> | sva 4 gumba držana zajedno |
| `KL: Mhouse` | `0xF` | <kbd>→</kbd> | dodatni / skriveni gumb |
| `KL: Nice Smilo` | `0xB` | <kbd>→</kbd> | dodatni / skriveni gumb |
| `KL: FAAC RC,XT` | `0xB` | <kbd>→</kbd> | gumbi 1+2 držani (master pritisak) |
| `KL: Genius TX4RC` | `0xB` | <kbd>→</kbd> | gumb načina programiranja |
| `KL: Monarch` | `0xB` | *nijedna strelica ga ne šalje* | ručno postavite kôd gumba u postavkama signala |
| `KL: FAAC FIX` | `0x9` | <kbd>→</kbd> | dodatni / skriveni gumb *(nepotvrđeno)* |
| `KL: Novoferm` | `0x9` | <kbd>→</kbd> | dodatni / skriveni gumb |
| `KL: Stilmatic` | `0x9` | <kbd>→</kbd> | dodatni / skriveni gumb |
| `KL: Sommer` (svi pojasevi) | `0x6` | <kbd>→</kbd> | dodatni / skriveni gumb |
| `KL: Hor. EcoStar` | `0x6` | **<kbd>↓</kbd>** | dodatni / skriveni gumb |
| `KL: Cardin S449` | `0xD` | <kbd>→</kbd> | gumb u rupici ispod tipki |
| `AN-Motors AT4` | `0xC` | <kbd>→</kbd> | dodatni / skriveni gumb |
| `Beninca ARC` | `0x0` | **<kbd>↓</kbd>** | skriveni gumb (gumbi 1+2 držani) |
| `Ditec GOL4` | `0x0` | <kbd>→</kbd> | skriveni gumb |
| `Jarolift` | `0x1` | **<kbd>↑</kbd>** | `Learn`: Up+Down držano, zatim Stop |
| `Somfy Telis` | `0x8` | **<kbd>←</kbd>** | gumb `Prog` |
| `Somfy Keytis` | `0x3` | **<kbd>↑</kbd>** | kontakti `Prog` na stražnjoj strani pločice |
| `V2 Phoenix` | `0x3` | <kbd>→</kbd> | gumbi 1+2 ili 1+3 držani *(nepotvrđeno)* |
| `Nice FloR-S` / `Nice One` / `Nice O-Code` | `0x3` | <kbd>→</kbd> | gumb 3 *(nepotvrđeno kao gumb za programiranje)* |

### Sve ostalo u izborniku

Svaka stavka koja nije u ovoj tablici i nema gornji odjeljak registrira se na uobičajen način: **prebacite prijamnik u način učenja njegovim vlastitim gumbom, zatim pritisnite `Send` na Flipperu unutar vremenskog prozora koji navodi vaš proizvođač.**

To obuhvaća većinu KeeLoq sustava (Comunello, Allmatic, Motorline, Centurion, Phantom/Hiland, KEY, Jolly Motors, IronLogic, DTM Neo, Gibidi, GSN, HomeGate, Elmes, Normstahl, JCM Tech, Pujol, ET Blue, ATA PTX4, Seav, Wisniowski, Fadini, Mc Garcia, Clemsa Mutancode, Doormatic, Elvox, Verex, CAME Space, Beninca KeeLoq, Superrollo, HCS101) i svaki statički protokol, kao što su CAME, Nice Flo, Marantec, Princeton, Prastel, Roger, Telcoma EDGE, Gate TX, BETT, Nord ICE, Revers RB2, Linear, Nero i [ZKTeco](/hr/subghz/zkteco-cmp200).

## Kada ne radi

- **Uopće se ništa ne događa.** Prvo provjerite frekvenciju. To je najčešća pogreška. Pročitajte svoj izvorni daljinski upravljač putem `Sub-GHz → Read` i usporedite. Neke marke prodaju isti daljinski upravljač na dvjema frekvencijama: DoorHan na 315 i 433.92, FAAC i Genius na 433.92 i 868.35. Ako niste sigurni, upotrijebite [Frequency Analyzer](/hr/subghz/frequency-analyzer).
- **Pogrešna modulacija.** Većina sustava ovdje koristi `AM650`, ali Cardin S449 koristi `FM12K`, a Sommer `FM12K` ili `FM476`. Postavite je u `Sub-GHz → Read → Config` i odaberite odgovarajući pojas u Add Manually.
- **Prijamnik reagira, ali nikad ne pohrani daljinski upravljač.** Vjerojatno propuštate vremenski prozor. Ponovno pročitajte korake i imajte otvorenu datoteku daljinskog upravljača prije nego što dodirnete gumb na prijamniku.
- **Pohranio je daljinski upravljač, ali ništa se ne otvara.** Držite `Send` dulje. Nekoliko protokola treba 1–3 s za slanje cijelog koda, a CAME Atomo svaki put treba najmanje 2 s.
- **Radilo je jednom pa stalo.** Na sustavu s promjenjivim kodom to je problem brojača: klonirali ste daljinski upravljač umjesto da napravite novi. Pritisnite `Send` još nekoliko puta zaredom, jer prijamnik prihvaća brojač koji je pobjegao naprijed unutar određenog prozora. Da bi oba daljinska upravljača ostala u funkciji, umjesto toga izradite novi daljinski upravljač (pogledajte [Promjenjivi kodovi](/hr/subghz/rolling-codes)). Statički daljinski upravljač nema brojač, pa ako prestane raditi, provjerite bateriju, frekvenciju ili prijamnik.
- **Svi su vaši daljinski upravljači prestali raditi.** Najvjerojatnije ste držali gumb za programiranje dovoljno dugo da pokrenete funkciju brisanja na prijamniku. Ponovno registrirajte svaki daljinski upravljač, uključujući izvorne.

## Izvori i priručnici

- [FAAC SLH: video upute](https://www.youtube.com/watch?v=NfZmMy37XUs)
- [Opis protokola Somfy RTS](https://pushstack.wordpress.com/somfy-rts-protocol/)
- [Somfy Universal Receiver RTS: upute za ugradnju](https://service.somfy.com/downloads/nam_v5/universalreceiver_rts.pdf)
- [Registracija Somfy Keytis NS 2 RTS (Somfy forum)](https://forum.somfy.fr/questions/1792206-programmer-telecommande-keitis-ns2-rts-recepteur-somfy-axorn-50)
- [Priručnik za BFT Mitto](https://www.retroremotes.com.au/wp-content/uploads/2017/03/BFT-MITTO-2-4-19-6-17.pdf)
- [Programiranje prijamnika NICE FLOX2R](https://apollogateopeners.com/store/pdf/apollo-flor-s-receiver-programming-guide.pdf)
- [Programiranje Nice Flor S](https://motepro.com.au/Instructions/Nice.pdf)
- [Priručnik za Nice Smilo SM2/SM4 i prijamnik SMXI](https://www.habitat-automatisme.com/blog/wp-content/uploads/2010/02/SMILO.pdf)
- Nice O-Code: priručnici za instalatere sa stranice [niceforyou.com](https://www.niceforyou.com/) (OXI/A `IS0242A00MM`, OXI/OXIT/OX2/OX4T `IST236R02`, OXIBD `idv0603a01it`, O-Box `IST225`, FLOR prijamnik `IS0063A00MM`, odašiljači Era One `IS0102A01MM`)
- [Programiranje Mhouse GTX4 / TX4 / Nice Home ECCO5](https://www.allotelecommande.com/wp-content/uploads/2019/06/Notice-de-programmation-MHOUSE-GTX4-%E2%80%93-TX4-%E2%80%93-MT4-%E2%80%93-NICE-HOME-ECCO5-.pdf)
- Erreka IRIS: `Guia rapida mando IRIS` (MSR-044/03), sa stranice [erreka.com](https://www.erreka.com/)
- [Priručnik za motor Jarolift TDEF](https://www.jarolift.de/wp-content/themes/jarolift/manuals/motoren/en/Jarolift_TDEF_EN.pdf)
- [Programiranje odašiljača Beninca TO.GO](https://www.allotelecommande.com/wp-content/uploads/2023/05/BENINCA-TO.GO_.pdf)
- [Priručnik za prijamnik Ditec BIX L / BIX A](https://www.allotelecommande.com/wp-content/uploads/2023/03/DITEC-BIX-L-DITEC-BIX-A.pdf)
- [Upute za programiranje Cardin S449 QZ2](https://www.allotelecommande.com/wp-content/uploads/2024/02/CARDIN-S449-QZ2.pdf)
- [Priručnik za prijamnik Cardin RCQ449](https://www.allotelecommande.com/wp-content/uploads/2023/02/Recepteur-Radio-CARDIN-RCQ449-ND00.pdf)
- [Priručnik za ručni odašiljač Hormann RSC2](https://www.hoermann.de/fileadmin/_country/dok/Handsender_RSC2_%28H%C3%B6rmann%29_TR20L001-A.pdf)
- [Sommer: uparivanje odašiljača s pogonom kliznih vrata](https://www.sommer.eu/en/magazine/programming-a-handheld-transmitter-to-a-sommer-sliding-gate-operator.html)
- [Priručnik za prijamnik V2 RXP4: radijsko učenje](https://manualslib.mx/manual/401640/V2-Rxp4.html?page=9)
- [Programiranje prijamnika KingGates Fred](https://tecnoparking.com/tienda/gb/receptors/2096-outer-receiver-kinggates-fred-2-channels-rollingcode-is-433-mhz.html)

## Povezane stranice

- [Add Manually](/hr/subghz/add-manually)
- [Promjenjivi kodovi](/hr/subghz/rolling-codes)
- [KeeLoq](/hr/subghz/keeloq)
- [Načini brojača](/hr/subghz/counter-mode)
- [Podržani sustavi](/hr/subghz/supported-systems)
- [Seed Capturer](/hr/subghz/seed-capturer) · [Nice O-Code](/hr/subghz/nice-o-code)
