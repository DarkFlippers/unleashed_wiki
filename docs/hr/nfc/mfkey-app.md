---
title: Aplikacija MFKey
order: 40
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/mfkey, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://t.me/gromovyna/27, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, gromovyna, flipper-docs, unleashed-readme]
---
# Aplikacija MFKey (MFKey 4.1)

**MFKey** (autor [@noproto](https://github.com/noproto)) izvlači MIFARE Classic ključeve **na samom Flipperu** iz
nonce vrijednosti koje je prikupila NFC aplikacija: nonce vrijednosti čitača (MFKey32) i nonce vrijednosti kartice iz
nested napada. To je alat za situacije kada pri ruci nemate telefon ni računalo; sporiji je od [qUnleashed](/hr/nfc/qunleashed),
ali radi bilo gdje, čak i u vašem džepu.

| | |
|---|---|
| Lokacija | `Main Menu → Apps → NFC → MFKey` (`/ext/apps/NFC/mfkey.fap`) |
| Verzija u Unleashed firmveru | **4.1** |
| Ulazi | `/ext/nfc/.mfkey32.log` (nonce vrijednosti čitača), `/ext/nfc/.nested.log` (nonce vrijednosti kartice) |
| Izlaz | `/ext/nfc/assets/mf_classic_dict_user.nfc` (ključevi), `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` (SEN kandidati) |

## Korištenje

1. Prvo prikupite nonce vrijednosti:
   - s čitača: [MFKey32](/hr/nfc/mfkey) (`Extract MFC Keys`);
   - s kartice: [nested napadi](/hr/nfc/nested-fudan) tijekom `NFC → Read`.
2. Otvorite `Main Menu → Apps → NFC → MFKey` ili pritisnite **Run** na zaslonu *"Now run Mfkey32 to extract keys"* u NFC
   aplikaciji (pojavljuje se nakon `Extract MFC Keys` i nakon `Crack nonces in MFKey32`).
3. Zaslon prikazuje **Ready**. <kbd>→</kbd> **Help** prikazuje *"Collect nonces by reading tag or reader in NFC app"*.
   Pritisnite <kbd>OK</kbd> **Start**.
4. MFKey najprije provjerava nonce vrijednosti u postojećim rječnicima: **Dict solves: N (in progress)**,
   **Keys in dict: N**. Nonce vrijednosti čiji je ključ već poznat preskaču se.
5. Zatim se pokreće napad s tri trake napretka: **Cracking: X/Y**, **Round: X/Y – ETA NN Sec** i
   **Total ETA NNN Sec**. Redak **RAM** pri vrhu prikazuje slobodni heap.
6. Po završetku čut ćete zvučni signal i vidjeti **Complete**, **Keys added to user dict: N** te, za statičke kriptirane
   nonce vrijednosti, **SEN key candidates: N**.
7. Vratite se u NFC aplikaciju i ponovno očitajte karticu (ili `Saved → <card> → Unlock with Dictionary`).

<kbd>←</kbd> zaustavlja rad i izlazi (dretva se čisto zaustavlja; do tada pronađeni ključevi svejedno se zapisuju).

### Pogreške

| Zaslon | Značenje |
|---|---|
| **No nonces found** | Ne postoji ni `.mfkey32.log` ni `.nested.log`. Najprije prikupite nonce vrijednosti. Prikazuje se i za oznake samo s HardNested zaštitom: njihove se nonce vrijednosti ne mogu probiti na Flipperu. |
| **Nonces already cracked** | Svaki nonce u zapisima već je riješen ključem iz vaših rječnika. |
| **No free RAM** | Nedovoljno memorije. Ponovno pokrenite Flipper i pokušajte opet; zatvorite druge aplikacije. |

## Što je MFKey 4.x promijenio

Iz članka autora @gromovyna "MFKey 4.1 — brže, više, jače": nova glavna verzija stigla je prilično tiho,
no donosi veliko ubrzanje. Dostupna je u **Unleashed dev inačicama od 1251**. (U vrijeme pisanja članka izmjene same
aplikacije bile su spojene i u službeni firmver, ali potrebne izmjene na strani firmvera nisu.) Zahvaljujemo
@noproto i timu.

U nastavku, **SEN** = static encrypted nonce (pogledajte [Nested napadi](/hr/nfc/nested-fudan)).

**4.0**

- Podrška za novi format SEN rječnika: izračun ključeva je **10× brži**.
- Stari format SEN rječnika više nije podržan.

**4.1**

- Izračun ključeva još **40% brži**; bolja učinkovitost memorije.
- Monolitna datoteka `mfkey.c` podijeljena u module: `mfkey_batch_prelude`, `mfkey_state_expansion`, `mfkey_bs_verify`,
  `mfkey_recovery`, `mfkey_dedup`.
- 32 kandidata provjeravaju se paralelno putem SWAR-a (bitovne operacije umjesto pojedinačnih provjera).
- Unaprijed izračunata "Super-LUT" tablica od 2 KB za runde 0–3: jedno indeksirano učitavanje po rundi umjesto računanja.
- Radix sort O(n) umjesto quicksorta; uklanjanje duplikata putem Fibonaccijevog raspršivanja (hashing) umjesto naivnog pretraživanja.
- Registri M4 FPU jedinice koriste se kao dodatni privremeni prostor (`vmov`), što smanjuje pritisak na registre.
- 8× odmotana Duffova petlja pri traženju duplikata.

### Stvarna vremena izvršavanja

Autor je testirao najteži slučaj: oznaku sa **statičkim kriptiranim nonce vrijednostima**. Kod takvih oznaka izračunati ključevi
ne provjeravaju se u hodu i ne idu izravno u korisnički rječnik; umjesto toga gradi se rječnik **kandidata** koje kasnije
treba provjeriti na samoj oznaci. Dakle, izvlače se **svi** ključevi koji bi mogli proizvesti nonce — najveći rječnik,
najdulji scenarij. Tijekom testiranja nije došlo ni do jedne pogreške *Out Of Memory*.

| Test | Postavke | Rezultat |
|---|---|---|
| Iron Logic ključ | Oznaka kriptirana objektnom karticom [Iron Logic](/hr/nfc/iron-logic); nema ključa u rječniku, napadnuta putem stražnjih vrata (backdoor); **18 jedinstvenih ključeva u 32 sektora** | Puni ciklus **6 h 8 min**, više od **1,2 milijuna kandidata**; zatim još nekoliko sati provjere kandidata na oznaci. |
| 1 sektor, 2 ključa | Ista oznaka (obrisana), sektor 0 kriptiran nasumičnim različitim ključevima A i B | **17 minuta**; provjera kandidata na jednom sektoru također je bila brza. |

Za usporedbu, oporavak prvog testa na Proxmarku3 s računalom trajao je 24 sekunde, pa se Flipper nikada neće moći
mjeriti s tim. Ali ako putujete ili jednostavno imate vremena za rad u pozadini, Flipper u vašem džepu može
pronaći ključeve i emulirati oznaku. A budući da uglavnom sustavi poput Iron Logica vole diverzifikaciju ključeva,
vjerojatnost da naletite na najdulji scenarij relativno je mala.

::: tip Unleashed
Unleashed uključuje MFKey 4.1 s potrebnim izmjenama na strani firmvera (CUID rječnik u `Read`, s trakom napretka
tijekom učitavanja). Nakon što MFKey završi na SEN oznaci, koristite **Save Keys to Dictionary** na potpuno očitanom
ispisu kako biste kopirali pronađene ključeve u svoj korisnički rječnik, pogledajte [MIFARE Classic](/hr/nfc/mifare-classic#save-keys-to-dictionary).
:::

## Savjeti

- Očistite `/ext/nfc/.nested.log` i `/ext/nfc/.mfkey32.log` nakon uspješnog oporavka: stari se nonce zapisi ponovno
  provjeravaju pri svakom pokretanju.
- Ako ste aplikacije instalirali zasebno, provjerite da stari `mfkey.fap` nije prepisao onaj iz firmvera.
- Mnogo brže alternative: [qUnleashed](/hr/nfc/qunleashed) na telefonu/računalu ili projekt
  [mfkey_desktop_cli](https://github.com/phntm-lab/mfkey_desktop_cli).

## Povezano

[MFKey32](/hr/nfc/mfkey) · [Nested napadi](/hr/nfc/nested-fudan) · [qUnleashed](/hr/nfc/qunleashed) ·
[MIFARE Classic](/hr/nfc/mifare-classic)
