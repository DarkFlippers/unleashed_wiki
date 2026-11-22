---
title: Dinamička registracija Iron Logic
order: 110
author: gromovyna
original: [https://telegra.ph/Enrollment-ataka-na-dinamiku-ot-Iron-Logic-06-05, https://t.me/gromovyna/14, https://t.me/gromovyna/19, https://t.me/gromovyna/20, https://t.me/gromovyna/25]
sources: [gromovyna]
---
# Iron Logic "dinamika" i logički propust pri registraciji

Istraživački članak o tome kako čitači Iron Logic provode zaštitu od kloniranja putem "dinamike" (način rada "ТП" / "samo prvi"), te o logičkom propustu u firmveru čitača 7.29 koji je **ispravljen u verziji 7.30**. Edukativno štivo za vlasnike sustava i istraživače.

::: tip Opseg
Samo za vlastite pristupne kartice i zakonito istraživanje. Ovdje opisani propust zakrpan je u aktualnom firmveru (7.30). Temeljeno na članku autora @gromovyna (2025-06-05) i objavama na kanalu.
:::

## Kako se ovi sustavi brane od kloniranja

Statični MIFARE Classic privjesak može kopirati svatko tko ima ključeve. Proizvođači na to odgovaraju na dva načina:

1. **Filtri**, koji otkrivaju magic kartice i emulatore (pogledajte [Čitači Iron Logic](/hr/nfc/iron-logic), [Filtri Vizit](/hr/nfc/vizit-filters)).
2. **Dinamika**: dio podataka na kartici sinkronizira se s memorijom čitača pri svakom prolasku ("brojač"). Ranije izrađena kopija više se ne podudara i biva odbijena. Inačice ovog pristupa koriste Intratone, Hexact, Comelit, Noralsy i Urmet u Francuskoj, Belgiji i Luksemburgu (gdje otkrivena desinkronizacija može onemogućiti sve korisnikove privjeske), a viđen je i na nekim Eltis portafonima u Rusiji.

## Način rada "ТП" ("Только первый" / "samo prvi")

Iz objave proizvođača citirane na kanalu (objava 20): pri svakom pristupu čitač na karticu zapisuje **novu lozinku**. Pri sljedećem pristupu broj kartice i lozinka provjeravaju se u odnosu na ono što je čitač pohranio; ako se podudaraju, kartica se prihvaća i zapisuje se nova lozinka. Rezultat: bez obzira na to koliko kopija postoji, nastavlja raditi samo jedna kartica. U početku je to podržavao samo **CP-Z2 MF-I**, s firmverom 7.29 (najavljenim kao nedovoljno testiranim). Proizvođač upozorava da svaki prolazak sada **zapisuje podatke na karticu**, pa prije prelaska na ovaj način rada treba provjeriti izdržljivost kartica na pisanje.

Zašto je to problem: tržište je preplavljeno krivotvorenim kineskim MIFARE Classic privjescima koji možda neće izdržati toliki broj prepisivanja, a prekinuto pisanje (loš položaj, gubitak napajanja) može dovesti karticu u stanje desinkronizacije. Upravo zbog toga emuliranje ili kloniranje na takvim sustavima može **uništiti vaš izvornik**.

## Firmver 7.29: bez filtara, dinamika kao glavni način rada

Firmver 7.29 (otvoreno testiranje) onemogućio je sve filtre i postavio dinamiku kao glavni način rada. Istraživački tim pronašao je ranjivosti u tom izdanju; logička pogreška ispravljena je u verziji **7.30**, nakon čega je autor objavio opis.

## Registracija (enrollment): kako kartica postaje dinamična

Kako bi prebacio tisuće postojećih statičnih kartica u dinamički način rada bez potrebe da korisnici izrađuju nove kartice, Iron Logic je uveo **registraciju (enrollment)**. Metapodaci se zapisuju u **sektor 14** kartice. Pojednostavljena logika čitača:

1. Čitač provjerava metapodatke kartice.
2. Ako kartica **još nije u dinamičkom načinu rada**, čitač je registrira i pohranjuje vrijednost brojača. Pritom **ne** provjerava nalazi li se taj ID kartice već u njegovoj memoriji.
3. Ako je kartica već registrirana, primjenjuju se stroge provjere brojača.

Parovi ID/brojač pohranjuju se u trajnu memoriju čitača.

## Propust (zakrpan u verziji 7.30)

Slabost proizlazi iz 2. koraka: čitač kojem se prisloni kartica koja i dalje izgleda "statično" jednostavno je ponovno registrira. Jedina prepreka za napadača jest posjedovanje dumpa kartice **prije** njezine prve registracije. Kartice koje su dovoljno stare da nemaju metapodatke čitač ne prihvaća, pa je pretvaranje dinamičkih podataka natrag u "statično" stanje bilo samo površno istraženo.

Autor opisuje dva praktična načina kako svaki put predstaviti "statičnu" karticu:

- **GDM (GDMIC) privjesci**, inačica USCUID-a sa shadow načinom rada: podaci se zapisuju u privremenu memoriju i vraćaju na stanje iz trajne memorije kada se polje čitača isključi, tako da izvornik (već registriran) i neograničen broj kopija mogu raditi usporedno. Autor napominje da je ovo jednostavno, ali izvan dosega većine bravara, te se može spriječiti ranijim filtrima ili pametnijim upravljanjem RF poljem.
- **Flipper Zero, ručno**: očitajte statičnu karticu, emulirajte je, upotrijebite `Return to Initial State`, ponovite. Dobro za testiranje, nepraktično za svakodnevnu upotrebu.

Tim raspolaže i drugim teorijskim i praktičnim napadima, a neke su ideje podijelili s iKeyjem.

## Što vlasnici sustava trebaju učiniti

- Ažurirati čitače na **7.30 ili noviji**.
- Provjeriti izdržljivost svojih kartica na pisanje prije uključivanja dinamike.
- Gdje god je moguće, dati prednost novijim obiteljima kartica (MIFARE Plus, DESFire i sličnima); čak i sam proizvođač MIFARE Classic smatra zastarjelim.

## Povezano

- [Čitači Iron Logic](/hr/nfc/iron-logic) · [Magic kartice](/hr/nfc/magic-cards) · [Filtri Vizit](/hr/nfc/vizit-filters)
