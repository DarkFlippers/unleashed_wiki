---
title: MIFARE Classic magic kartice
order: 50
author: gromovyna
original: [https://telegra.ph/Mifare-Classic-Magic-Tags-11-16, https://t.me/gromovyna/6, https://docs.flipper.net/zero/nfc/magic-cards]
sources: [gromovyna, flipper-docs]
---
# MIFARE Classic magic kartice (prazni čipovi)

Na standardnoj MIFARE Classic oznaci **blok 0**, koji sadrži UID i podatke proizvođača, ne može se prepisati. Da bi se napravila potpuna kopija
takve oznake, izumljeni su posebni **prazni čipovi** ("magic kartice", "kartice s promjenjivim UID-om") na kojima se blok 0 može zapisati
jednom ili više puta.

Ova stranica, temeljena na članku autora **@gromovyna**, ukratko objašnjava što je što: od Gen1 do Gen4, međunarodne nazive,
nazive na lokalnom (bivši SSSR) tržištu te koje je ponašanje važno za koji čitač. Spominju se oznake koje su dostupne
bez komplicirane nabave iz Kine i koje je autor sam provjerio ili vidio. Za pisanje na njih pomoću
Flippera pogledajte [NFC Magic 2.0](/hr/nfc/nfc-magic).

> U nastavku su "oznaka", "čip", "kartica" i "privjesak" sinonimi: važan je čip unutra i kako se ponaša, a ne njegov
> oblik.

Dodatno čitanje:

- izvrsne [bilješke o magic karticama](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md)
  u dokumentaciji za Proxmark3 (na engleskom), koje istraživači redovito ažuriraju; pokrivaju i druge protokole te daju tehničke
  pojedinosti i naredbe. Uz iskustvo i Proxmark3 možete uštedjeti kupnjom najjeftinijih praznih čipova s određenim
  čipom i njihovim rekonfiguriranjem (za neke čipove);
- autorova [Google Sheets tablica](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
  s oznakama u nastavku, njihovom generacijom, nazivima i informacijom može li ih Flipper Zero zapisati.

## Generacije

![Generacije magic oznaka](/img/remote/f659ade923b6ca4f.png)

Podjela na generacije ("Gen") nije formalna: to je pokušaj klasifikacije čipova prema ponašanju. Ustalile su se četiri generacije.
Jedan čip može pripadati u više njih odjednom (npr. **M1-4K**). Autor slijedi standardnu klasifikaciju koju koristi
Proxmark3, iako se s njom u potpunosti ne slaže za neke čipove.

| Gen | Nadimak | Kako se zapisuje blok 0 | Napomene |
|---|---|---|---|
| **Gen1** | Backdoor | posebne backdoor naredbe | Najstariji. Backdoor naredbe uvijek dopuštaju pisanje, čitanje (i brisanje za Gen1a) oznake. Budući da je filtar protiv njih trivijalan, **svaki ozbiljan sustav ih filtrira**. |
| **Gen2** | Direct Write | blok 0 zapisuje se kao i svaki drugi blok | Mogu ih zapisivati NFC telefoni (uglavnom Android) s odgovarajućim softverom. |
| **Gen3** | APDU | posebna APDU naredba | Neki omogućuju promjenu UID-a odvojeno od bloka 0. Rijetka zvjerka. |
| **Gen4** | Configurable | konfiguracijski blok | Ima konfiguraciju i memoriju, može se postaviti kao različiti MFC formati (i više). Najfleksibilniji; može oponašati ponašanje Gen1/Gen2. |

## Gen1 (backdoor)

### Gen1a

Za pisanje zahtijevaju backdoor naredbe `40` (7-bitna) i `43`.

**UID** (RU naziv: *Zero*). Međunarodno postoji s 4-bajtnim ID-om; iKey LLC navodno je napravio i 7-bajtnu varijantu
(čeka se potvrda radi li se o istom čipu). Podržava i backdoor čitanje (ključevi nisu potrebni) te brisanje.

**OTP 2.0** (RU; prodaje se i kao **MF** za ukrajinsko tržište). Prema iKey LLC-u, njihov vlastiti dizajn. **Jednokratno
programirljivo (One time programmable)**: nakon prvog zapisa (putem backdoora) čip se zaključava i ponaša poput pravog MFC-a. Ima **hard
PRNG**.

::: tip Napomena autora
Oznaka se ne podudara u potpunosti s pravim MFC-om i ponaša se drukčije pod opterećenjem, što je omogućilo Iron Logicu da izgradi filtar
protiv nje. Kako taj filtar točno radi autoru nije bilo poznato u vrijeme pisanja.
:::

**MF-4** (RU). Poboljšani OTP 2.0. Također **jednokratno programirljiv** nakon prvog backdoor zapisa, **hard PRNG**.
Prema opisu može:

- prebacivati duljinu UID-a između 4 i 7 bajtova;
- postaviti proizvoljne ATQA/SAK i ATS;
- podržati naredbu PPS (koja, koliko je autoru poznato, uopće nije dio MFC protokola).

### Gen1b

Poput Gen1, ali radi odmah nakon naredbe `40` (7-bitna). Autor osobno nije vidio Gen1b UID čipove za MFC 1K.

**M1-4K**: čip za kopiranje **MIFARE Classic 4K**. Ponaša se kao **Gen1b i Gen2 CUID** istovremeno. Ima
**statični nonce `f17e64cd`**.

## Gen2 (izravno pisanje)

Blok 0 može se zapisati izravno. Mogu se zapisivati s Androida pomoću aplikacije *Mifare Classic Tool*.

### CUID

RU nazivi: **MF-3**, **MF3-2**, **MF-8**.

Glavni, univerzalan (za većinu slučajeva) i najrašireniji čip. Zaobilazi jednostavne Gen1 filtre, može se prepisivati mnogo puta
i može se zapisivati s mobitela: zato je postao omiljen u zajednici.

::: tip Napomena autora
Na području bivšeg SSSR-a zanimanje za ovaj čip i pojedinosti njegova ponašanja važni su zbog čitača **Iron Logic**, koji
imaju filtre protiv praznih čipova. Ti su čitači jeftini pa su posvuda. Vidi [Čitači Iron Logic](/hr/nfc/iron-logic).
:::

Mnogi se čipovi prodaju pod nazivom "CUID", a mogu se razlikovati u rubnim slučajevima ponašanja. Najnoviji su **CUID sa statičnim nonceom
(MF-3.2)**: u vrijeme pisanja zaobilaze sve poznate filtre u bivšem SSSR-u (uključujući Iron Logic "4 pruge").

Lokalni nazivi:

- **MF-3**: CUID koji zaobilazi Iron Logic filtre "3 pruge".
- **MF-8**: CUID koji **ne** zaobilazi Iron Logic OTP 1.0 filtre ("neispravna serija" čiji je broj, osam, nastao
  jednostavnom preinakom broja tri).
- **MF-3.2**: CUID sa statičnim nonceom, zaobilazi sve Iron Logic filtre protiv MFC-a.

U Kini postoji i **"Perfect CUID"** koji odgovara na naredbu RATS (autor za to nije našao praktičnu primjenu).

## Gen3 (APDU)

Oznake kojima se upravlja APDU naredbama. Trenutačno najmanje istražena kategorija. Potencijalno konfigurabilne po tipu, ali to
nije dokazano. Nema RU naziva.

Prodaju se za različite MFC varijante, u raznim kombinacijama:

- prema memoriji: **MFC 1K**, **MFC 4K**, **MIFARE Mini**;
- prema duljini ID-a: **4 bajta**, **7 bajtova**.

Autor posjeduje varijante MFC 1K 7b, MFC 4K 4b, MFC 4K 7b, MF Mini (S20) 4b i MF Mini (S20) 7b (MFC 1K 4b najvjerojatnije
također postoji) i koristio ih je nekoliko puta za testiranje hipoteza sa 7-bajtnim ID-ovima, prije nego što je otkrio koliko su
USCUID čipovi konfigurabilni. Ta raznolikost (i iskustvo s drugim oznakama) navela ga je na zaključak da bi se ovi čipovi *mogli* konfigurirati prema
tipu, duljini UID-a i veličini memorije.

## Gen4 (konfigurabilni)

Najnapredniji čipovi: konfiguracijski blok upravlja oznakom i njezinim ponašanjem.

### USCUID (GDM u Proxmark3 naredbama)

Jeftin čip s memorijom MFC 1K plus skrivenim blokovima koje koriste neke konfiguracije. Ovisno o konfiguraciji
podržava tri vrste backdoor naredbi i Direct Write. Može nositi 4-bajtne ili 7-bajtne ID-ove, može vratiti MFC EV1
potpis, ima shadow način rada i mnoge druge korisne značajke.

Varijante backdoora:

- **Gen1a** (`40`/`43`) magic buđenje;
- **GDM** (`20`/`23`) magic buđenje: potpuno kao Gen1, ali druge naredbe. Čitači s filtrima protiv ovog
  backdoora dosad nisu viđeni (za razliku od Gen1a);
- **Magic Authentication** (odabir oznake, `8000` + CRC, Crypto-1 autentifikacija s ključem `000000000000`).

Poznavanjem načela konfiguracije čip možete fino podesiti za specifične potrebe. Kad su uključeni Gen1a/GDM backdoorovi
i naredbe u stilu Gen1, primijećeno je da pisanje ili brisanje zna biti nepouzdano. Korisnici Proxmarka3 trebali bi pročitati
dokumentaciju čipa na poveznici iznad: u usporedbi s Ultimate Magic Cardom košta malo, a nudi mnogo.

Tržišne konfiguracije USCUID-a:

| Naziv | RU naziv | Ponašanje |
|---|---|---|
| **FUID** | *OTP* | **Jednokratno programirljivo**: Direct Write bloka 0, zatim se blok zaključava. Prodavao se u bivšem SSSR-u kao iKey LLC-ov "OTP", ali se pokazao kao kineski čip. U zadanoj konfiguraciji ima **GDM** backdoor, pa se ID može mijenjati više puta i podaci čitati bez ključeva. Početkom studenog 2024. istraživači su prijavili verzije sa **zaključanim** backdoorom na kineskom tržištu, što onemogućuje ponovnu uporabu. |
| **UFUID** | — | Kinezi ga prodaju kao "sealable UID" (UID koji se može zapečatiti). Tvornička konfiguracija ima **Gen1a** backdoor, prepisiv mnogo puta. "Pečaćenje": kineski duplikatori (CopyKey itd.) provjeravaju konfiguracijski blok nakon pisanja, a zatim šalju naredbu koja ga mijenja i onemogućuje backdoor, pretvarajući oznaku u obični MFC. Okrnjeni USCUID: prihvaća samo dio konfiguracije. |
| **ZUID** | — | UID oznaka na okrnjenom USCUID-u. S obzirom na cijene čipova, smisao ove varijante nije jasan. Prihvaća samo dio konfiguracije. |
| **GDM (GDMIC)** | — | Dao je USCUID-u jedno od prvih imena. Ključna značajka: **shadow mode** (način sjene): u polju čitača sve promjene idu u privremenu memoriju koja se gubi kad polje nestane; sljedeći put podaci dolaze iz trajne memorije. Kinezi ga reklamiraju za kartice s "preostalim vožnjama" (npr. žičare/dizala). **Ne** pomaže protiv čitača koji koriste dinamičke podatke (npr. portafoni Eltis sa svojim privjescima). |
| **GDCUID** | — | CUID implementiran na USCUID-u. Ne prodaje se zasebno, ali se može pojaviti pri kupnji CUID-a. |
| **M1-7B** | — | Za pisanje MIFARE Classic 1K sa **7-bajtnim** ID-om. Ima **GDM** backdoor. U 7-bajtnom načinu čita ID iz **skrivenog bloka**: samo pisanje dumpa u glavnu memoriju može "brickati" oznaku (popravljivo je). |

Nazive **ZUID** i **GDCUID** predložio je sam autor dok je pisao Proxmark3 dokumentaciju za magic čipove.

### Ultimate Magic Card (GTU)

Trenutačno najskuplji čip: velika memorija i konfiguracije omogućuju mu da glumi ne samo različite MIFARE Classic /
Mini formate, nego i MIFARE Ultralight, NTAG i druge (iako mu je Ultralight implementacija prilično ograničena).
Konfiguracija omogućuje:

- promjenu **ATQA/SAK** i **ATS**;
- duljinu **ID-a** od 4, 7 ili 10 bajtova;
- **shadow mode** i njegove postavke;
- uključivanje/isključivanje **Direct Write** za blok 0;
- promjenu **backdoor lozinke** (koriste je sve naredbe);
- postavljanje **Version** i **Signature** vrijednosti;
- prebacivanje u **Ultralight način** i njegovo konfiguriranje.

Prije nego što se pojavio CUID sa statičnim nonceom, UMC je bio jedini prazni čip koji je zaobilazio Iron Logic filtre "4 pruge".

## Sažeta tablica

![Tablica usporedbe](/img/remote/a29bf09269c612bb.jpg)

Potpuna, održavana verzija nalazi se u autorovoj
[Google Sheets tablici](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing).

Ako se bojite kupnje pogrešnog čipa u Kini, autor preporučuje trgovinu
[FlipperMarket](https://flipper.market/catalog#services-3), gdje glavne oznake potrebne u ZND-u (i koje Flipper može zapisati)
bira i prodaje iskusan prodavač.

## Što Flipper može zapisati

Prema službenoj dokumentaciji, Flipper Zero (putem aplikacije **NFC Magic**) zapisuje **Gen1**, **Gen2** i **Gen4** magic
kartice, plus **obične MIFARE Classic** kartice (bez promjene UID-a):

| Prazni čip | Može se konfigurirati kao |
|---|---|
| Gen1 | MIFARE Classic 1K |
| Gen2 | MIFARE Classic 1K, MIFARE Classic 4K (potrebna je kompatibilna Gen2 kartica) |
| Gen4 (Ultimate) | bilo koji MIFARE Classic, MIFARE Ultralight EV1/EV2, NTAG203, NTAG213, NTAG215, NTAG216 |

::: tip Unleashed
Unleashed izdanje aplikacije **NFC Magic 2.0** dodatno prepoznaje i zapisuje **USCUID-UL** Ultralight/NTAG prazne čipove
(UL11, UL21 / "Ultra", NTAG213/215/216, UL-C, UL-5) te prikazuje stvarne rezultate *Success / Partial / Fail*.
Vidi [NFC Magic 2.0](/hr/nfc/nfc-magic).
:::

### Ukratko kako klonirati karticu

1. [Pročitajte](/hr/nfc/read) i spremite izvornik. Provjerite jesu li pročitani **svi** sektori/stranice (po potrebi pronađite ključeve pomoću
   [MFKey32](/hr/nfc/mfkey), [nested napada](/hr/nfc/nested-fudan) ili [qUnleashed](/hr/nfc/qunleashed)).
2. Odaberite prazni čip koji ciljni čitač prihvaća (vidi gore: Gen1 se filtrira gotovo posvuda).
3. Zapišite ga pomoću [NFC Magic](/hr/nfc/nfc-magic).

::: tip Pravno
Kopirajte samo vlastite vjerodajnice ili uz izričito dopuštenje.
:::

## Povezano

[NFC Magic 2.0](/hr/nfc/nfc-magic) · [MIFARE Classic](/hr/nfc/mifare-classic) · [Čitači Iron Logic](/hr/nfc/iron-logic) ·
[Filtri čitača Vizit](/hr/nfc/vizit-filters)
