---
title: Brzi oporavak ključeva pomoću qUnleasheda
order: 45
author: gromovyna
original: [https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18, https://t.me/gromovyna/32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, unleashed-readme, unleashed-src]
---
# Brzi oporavak ključeva MIFARE Classic pomoću qUnleasheda

Praktični vodič autora **@gromovyna**: brzo oporavite ključeve MIFARE Classic pomoću firmvera Unleashed i njegove prateće aplikacije
**qUnleashed** (razvija je i održava tim Unleashed; veliko hvala korisniku
[apfxtech](https://github.com/apfxtech), izvornom autoru aplikacije). Ovo je nastavak stranice
[Nested napadi i Fudan backdoorovi](/hr/nfc/nested-fudan); preporučuje se prvo pročitati tu stranicu, ali nije obavezno.

Oporavak pokriva **sve napade i vrste noncesa** poznate u vrijeme pisanja: *weak, hard, static, static
encrypted*. Za razliku od [aplikacije MFKey](/hr/nfc/mfkey-app), zahtjevni izračuni izvode se na vašem mobitelu ili računalu, pa postupak
obično traje **minutama**, a ne satima.

::: warning Oznaka vam mora biti u rukama
Oznaka mora biti fizički prisutna za završno čitanje. „Napravio sam dump za prijatelja i oznaka više nije tu” neće raditi.
:::

## Inačice

Funkcionalnost možda postoji i u malo starijim inačicama, ali za testiranje su korištene ove:

- Unleashed [unlshd-093](https://github.com/DarkFlippers/unleashed-firmware/releases/tag/unlshd-093)
- qUnleashed [beta-0.11.2](https://github.com/DarkFlippers/qUnleashed/releases/tag/beta-0.11.2)

Pogledajte i [aplikaciju qUnleashed](/hr/mobile/qunleashed-app) za upute o instalaciji i ostale značajke.

## Što vam je potrebno

Oznaka **MIFARE Classic** (ili **MIFARE Plus u SL1**, samo SL1) s **barem jednim poznatim ključem ili backdoorom**.

![Oznaka s jednim nepoznatim ključem](/img/remote/286db70e86cfa835.png)

![Oznaka s backdoorom: ključevi su nepoznati, ali sektori su pročitani putem backdoora](/img/remote/59bd4aa5ae1242c1.png)

Ako vaša oznaka nema backdoor niti ijedan poznati ključ, najprije nabavite jedan od čitača pomoću alata [MFKey32](/hr/nfc/mfkey).
qUnleashed može oporaviti ključeve i iz noncesa čitača (pogledajte korak 2).

## Korak 1. Prikupljanje noncesa

1. Prije napada dobro je očistiti `/ext/nfc/.nested.log` ako ga imate (`/ext/` je SD kartica). Nakon
   oporavka također ga je smisleno izbrisati kako ne bi rastao i stvarao nered. Za qUnleashed to nije
   presudno, ali je dobra praksa.
2. Očitajte oznaku: `Main Menu → NFC → Read`. Pričekajte dok se faze izvrše; koje će se pojaviti ovisi o vrsti noncesa
   oznake: **Backdoor Read**, **Nested Dictionary (Backdoor)**, **PRNG Analysis**, **Calibration**,
   **Nonce Collection**.

   ![Prikupljanje noncesa](/img/remote/786d77b7b65b3fd0.png)

3. Kad se pojave podatci o oznaci, **spremite nepotpuni dump**: trebat će vam kasnije.
4. Po želji provjerite u qUnleashu jesu li noncesi prisutni: povežite Flipper, otvorite `Archive → External → nfc`,
   uključite skrivene datoteke (izbornik s „burger” ikonom / tri točke u gornjem desnom kutu) i potražite `.nested.log`.

   ![.nested.log u qUnleashu](/img/remote/c4c534fbe93faa8a.png)

## Korak 2. Oporavak ključeva

Sve se odvija u **qUnleashu**; Flipper mora ostati povezan (putem Bluetootha ili kabela) cijelo vrijeme.

1. Otvorite `Tools → Recover MIFARE Keys`.

   ![Stavka izbornika](/img/remote/1a255b9128f988ab.png)

2. Pričekajte da oporavak završi.

   ![Oporavak ključeva](/img/remote/1e1b3e63595aa99a.png)

   ::: warning Budite strpljivi
   Postupak može potrajati ovisno o veličini datoteke `.nested.log`, vrstama noncesa, snazi uređaja na kojem se izvodi
   qUnleashed itd. Obično traje nekoliko minuta. Pričekajte da se operacija dovrši. Static encrypted noncesi traju
   najdulje.
   :::

3. Pregledajte rezultat. Faza oporavka radi s datotekama **`.mfkey32.log`** (noncesi čitača) i **`.nested.log`** (noncesi
   oznake). Zaslon prikazuje odakle je došao svaki ključ, koliko ih je dodano u korisnički rječnik ili u
   rječnik kandidata itd.

   ![Rezultat oporavka](/img/remote/1c5f56614caf4530.png)

Kamo idu ključevi ovisi o vrsti noncesa:

| Noncesi | Rezultat |
|---|---|
| weak, hard, static | Ključevi se dodaju u **korisnički rječnik** `/ext/nfc/assets/mf_classic_dict_user.nfc`. |
| static encrypted | Ključ se u ovoj fazi ne može točno izračunati, pa se izrađuje **rječnik kandidata** (poznat i kao **CUID rječnik**): `/ext/nfc/assets/mf_classic_dict_{UID}.nfc`, gdje je `{UID}` ID vaše oznake. Može biti velik: u autorovom primjeru bilo je više od **1,2 milijuna kandidata** za jednu oznaku. |

## Korak 3. Ponovno očitajte oznaku

Prislonite oznaku na Flipper i ili idite na `NFC → Read`, ili otvorite spremljeni nepotpuni dump i odaberite
**Unlock with Dictionary**.

![Unlock with Dictionary](/img/remote/b949b0a741d92f15.png)

Kod **CUID rječnika**, on se najprije učitava. Rječnik kandidata je velik pa to traje neko vrijeme, a vidite
traku napretka (*"CUID dictionary is loading"*). **Minute** su ovdje stvarno vrijeme učitavanja.

![Zaslon učitavanja, dev build 1437+](/img/remote/47427c58e2a34889.png)

::: tip Ažuriranje 22.09.2026
U ranim inačicama firmvera u ovom je trenutku bio prikazan samo prazan zaslon, što je zbunjivalo mnoge korisnike. Počevši od dev
izdanja **1437** (i izdanja **094**), zaslon ima traku napretka.
:::

Zatim se pokreće napad rječnikom (dictionary attack) s oporavljenim ključevima.

![Napad rječnikom](/img/remote/f77ef58bda94b088.png)

Ponovno, za **static encrypted noncese (CUID rječnik)** ostavite Flipper na oznaci tijekom pretrage i otiđite skuhati
čaj.

Kad svi ključevi budu pronađeni, možete ažurirati spremljeni djelomični dump u potpuni ili ga spremiti pod novim nazivom.

![Potpuno očitana oznaka](/img/remote/9f9745d0d2ee0a4a.png)

Sada su dostupne sve opcije: emulacija, pisanje na prazne kartice, dijeljenje s prijateljem itd.

::: warning Prije pisanja na praznu karticu
Upoznajte razliku između praznih kartica i kako ih čitači mogu filtrirati: pogledajte [Magic kartice](/hr/nfc/magic-cards).
:::

## Neobavezno: spremite ključeve static-encrypted oznake u korisnički rječnik

Zbog načina na koji napad funkcionira, ključevi oporavljeni iz rječnika kandidata pohranjuju se **samo u tom rječniku
i u dumpu oznake**. To predstavlja problem ako želite zapisati praznu karticu i kasnije je obrisati:
[NFC Magic](/hr/nfc/nfc-magic) radi samo s predmemorijom ključeva te korisničkim i sistemskim rječnicima.

Zato je tim u firmver dodao automatsko spremanje ključeva s provjerom duplikata. Otvorite izbornik spremljenog dumpa (barem
jedan ključ mora biti poznat) i odaberite **Save Keys to Dictionary**.

![Save Keys to Dictionary](/img/remote/1b1aafbeca5dace4.png)

Flipper prikazuje *"Saving keys to user dictionary"*, a zatim *"New keys: N, Already known: M"*.

## Alternative

Postoji i [CLI projekt](https://github.com/phntm-lab/mfkey_desktop_cli) za oporavak. U nekim je aspektima
brži, ali CLI je za napredne entuzijaste. Za svakodnevnu upotrebu autor preferira praktičnu prateću aplikaciju, osobito
s obzirom na to koliko drugih korisnih značajki ima. Na samom Flipperu koristite [aplikaciju MFKey](/hr/nfc/mfkey-app).

Postupak u početku može izgledati pomalo složeno, ali nakon malo prakse postaje rutina.

## Povezano

[Nested napadi](/hr/nfc/nested-fudan) · [MFKey32](/hr/nfc/mfkey) · [Aplikacija MFKey](/hr/nfc/mfkey-app) ·
[MIFARE Classic](/hr/nfc/mifare-classic) · [Magic kartice](/hr/nfc/magic-cards) · [Aplikacija qUnleashed](/hr/mobile/qunleashed-app)
