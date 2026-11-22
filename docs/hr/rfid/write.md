---
title: Pisanje na prazne kartice
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/rfid/write-data, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29]
sources: [unleashed-src, flipper-docs, gromovyna]
---
# Pisanje 125 kHz ključeva na prazne kartice

Izvorne 125 kHz kartice i privjesci gotovo su uvijek samo za čitanje. Da biste napravili fizičku kopiju, potrebna vam je **prazna kartica za pisanje (blank)** —
„magic” čip koji se može programirati da se ponaša kao kartica drugog protokola. Flipper Zero može zapisati bilo koji spremljeni, očitani
ili ručno dodani ključ na takvu praznu karticu.

## Na koje se prazne kartice može pisati

| Čip (kako je prikazan na zaslonu) | Uobičajeni tržišni nazivi | Zapisuje | Zadano |
|---|---|---|---|
| **T5577** | T5577, ATA5577, „5577” kartice/privjesci/naljepnice | svaki protokol | ON |
| **EM4305** | Prazne kartice EM4305 / EM4205 | Obitelj EM4100, Electra, FDX-B, Gallagher, GProxII, Jablotron, Radio Key (Securakey), Viking | ON |
| **8265** | ID8265 / H5 (klon Hitag Micro, zadana lozinka) | Obitelj EM4100 | ON |
| **8210** | ID8210 (isti čip, lozinka klonera FURUI) | Obitelj EM4100 | ON |
| **H5.5** | iKey H5.5 (isti čip, lozinka iKey) | Obitelj EM4100 | ON |
| **8268** | ID8268 (magic čip Hitag S) | Samo EM4100 na RF/64 | **OFF** |

::: tip Unleashed
Službena dokumentacija spominje samo T5577. Podršku za Hitag Micro čipove **8265/H5, H5.5 i 8210** u Unleashed je dodao
**@gromovyna** — čipovi se razlikuju samo po lozinki za prijavu, pa Flipper redom isprobava svaku poznatu lozinku
umjesto da vas pita. Pozadina i priča: [T5577 i Hitag Micro](/hr/rfid/t5577-hitag).
:::

::: warning 8268 zahtijeva ručno uključivanje
Cilj **8268** (Hitag S) zadano je isključen. Za razliku od ostalih pisača, on odabire bilo koju Hitag S oznaku koja odgovori, a
na izvornoj Hitag S oznaci stranice 4 i 5 sadrže podatke aplikacije — Flipper ne može razlikovati izvornu oznaku od klona. Uključite
ga samo kad znate da je na zavojnici prazna kartica 8268.
:::

## Pisanje ključa

1. Očitajte oznaku (`Read` → **More** → **Write**) ili otvorite spremljenu (`Saved` → ključ → **Write**).
2. Prislonite praznu karticu na stražnju stranu Flippera i **ne mičite je**. LED bljeska ljubičasto (magenta).
3. Zaslon prikazuje **Writing**, protokol u uglatim zagradama, naziv datoteke (ili *Unsaved Tag*) i, u oblim zagradama,
   **čip koji se trenutačno isprobava**, primjerice:

   ```text
   Writing
   [EM4100]
   Office
   (T5577)
   ```

   ![Zaslon pisanja s protokolom [EM4100], nazivom ključa i čipom koji se isprobava, (T5577), u zagradama](/screens/lfrfid/write.png)

4. Flipper redom zapisuje svaku uključenu vrstu čipa i **ponovno očitava oznaku** nakon svakog pokušaja. Čim se
   očitano podudara sa zapisanim, zaustavlja se.
5. Po uspjehu vidjet ćete **Success!** s nazivom čipa koji je stvarno prihvatio podatke (npr. `T5577`, `EM4305`,
   `H5.5`), a aplikacija se vraća na izbornik ključa.

![Pisanje u tijeku, prikazuje čip koji se isprobava](/img/remote/34b72cbd8417d74e.png)

![Rezultat pisanja s nazivom čipa](/img/remote/3ca59457a78dad5b.png)

::: tip Zašto naziv čipa?
Uz više vrsta čipova za isprobavanje (i tri lozinke za Hitag Micro), pisanje može trajati osjetno dulje, pa nije bilo
jasno što je točno zapisano. Prikaz pokušavanog i konačnog čipa bio je UX ispravak autora @gromovyna: tehnički gledano to je
tržišni naziv varijante prazne kartice, a ne protokol.
:::

## Settings → Write Chips

`Main Menu → 125 kHz RFID → Settings → Write Chips` navodi sve ciljeve: **T5577**, **EM4305**, **8265**, **8210**,
**H5.5**, **8268**, svaki sa stanjem **ON** / **OFF**.

- Tipke <kbd>OK</kbd>, <kbd>←</kbd> ili <kbd>→</kbd> mijenjaju stanje označenog čipa.
- Odabir se sprema kad napustite stranicu (<kbd>Back</kbd>) u `/ext/lfrfid/.lfrfid.settings`.
- Isključivanje čipova koje nikad ne koristite ubrzava pisanje (svaki uključeni čip koji ne odgovara troši jedno pisanje + provjeru).
- CLI naredba `rfid write` poštuje istu postavku.

Ako se stranica ne uspije otvoriti, vidjet ćete *Settings plugin failed to load* — ažurirajte resurse na SD kartici (stranica je zasebna
datoteka dodatka). Pisanje i dalje koristi ono što je pohranjeno u datoteci postavki.

## Pisanje i postavljanje lozinke {#write-and-set-password}

`Saved` → ključ → **Write and set password** zapisuje ključ na **T5577** i uključuje njegovu zaštitu lozinkom, tako da
nitko ne može ponovno prepisati oznaku bez lozinke.

1. Unesite 4-bajtnu lozinku u heksadecimalnom obliku. Ako još nije postavljena, polje je unaprijed ispunjeno nasumičnom riječi iz T5577
   rječnika.
2. Držite praznu karticu mirno. Zaslon prikazuje **Writing with password**, `[Protocol]` i trenutačni korak.
3. Najprije se ključ zapisuje i ponovno očitava, zatim lozinka ide u blok 7 i ponovno se očitava, te se tek onda
   postavlja bit lozinke u bloku 0. **Zapišite lozinku** — T5577 zaključan nepoznatom lozinkom ne može se
   ponovno upotrijebiti.

Mogući rezultati:

| Zaslon | Značenje |
|---|---|
| **Success!** | Ključ zapisan, lozinka pohranjena i zaštita uključena |
| **Error** — *This protocol cannot be written with a password* | Protokol treba svih 7 podatkovnih blokova, blok 7 ne može držati lozinku |
| **Has a password** — *Clear it first: the T5577 app, Clear Password* | Oznaka je već zaštićena |
| **Cannot read it** | Nešto je na zavojnici, ali se blokovi ne mogu pročitati — najprije je obrišite ili uklonite lozinku |
| **Not written** | Blok je odbio ključ; oznaka sadrži dio ključa i nema lozinku |
| **Not protected** | Lozinka nije završila u bloku 7 ili je oznaka odbila uključiti zaštitu |
| **Not confirmed** | Lozinka je na oznaci, ali se nije moglo očitati je li zaštita aktivna |
| **Still trying to write...** | Nijedna oznaka ne odgovara — provjerite je li riječ o T5577 kartici na koju se može pisati |

## Poruke pogreške kod običnog pisanja

| Poruka | Što učiniti |
|---|---|
| *This protocol cannot be written* | Za njega ne postoji kodiranje čipa |
| *No write chips enabled. Enable one in Settings* | Svi su ciljevi isključeni (OFF) |
| *No enabled chip can write this protocol* | Npr. uključen je samo EM4305 za HID ključ — uključite T5577 |
| **Still Trying to Write...** *Make sure this card is writable and not protected* | Prikazuje se nakon ~10 s ili nekoliko neuspjelih provjera. Oznaka je samo za čitanje, zaštićena lozinkom, nepodržan čip ili loše postavljena. Flipper nastavlja pokušavati dok ne pritisnete <kbd>Back</kbd>. |

## Rješavanje problema

- **Prazna kartica ima lozinku.** Mnogi jeftini kloneri zaključavaju prazne kartice T5577. Upotrijebite [aplikaciju T5577](/hr/rfid/t5577-app) →
  **Clear Password** (isprobava vašu lozinku, zatim rječnik).
- **T5577 je dobio neispravnu konfiguraciju** (ne očitava se ni kao što). Upotrijebite aplikaciju T5577 → **Wipe Tag**.
- **Hitag Micro (8265/8210/H5.5) zahtijeva dobro pozicioniranje.** Pisanje na ove čipove traje dulje i osjetljivo je na položaj;
  Flipper na LF-u ima samo TX, pa se uspjeh potvrđuje isključivo ponovnim očitavanjem oznake.
- **„Success” na kartici samo za čitanje.** Ako oznaka na koju se ne može pisati već sadrži isti ID, ponovno očitavanje se podudara i
  pisanje se prijavljuje kao uspješno.
- **Privjesci s metalnim / debelim kućištem.** Isprobajte različite položaje; privjesci za ključeve često imaju zavojnicu pomaknutu iz središta.

## Povezano

- [T5577 i Hitag Micro](/hr/rfid/t5577-hitag) · [Aplikacija T5577](/hr/rfid/t5577-app) · [Protokoli](/hr/rfid/protocols) ·
  [Čitanje](/hr/rfid/read)
