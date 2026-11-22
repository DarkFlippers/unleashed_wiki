---
title: Nested napadi i Fudan backdoorovi
order: 35
author: gromovyna
original: [https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://t.me/gromovyna/4, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# Nested napadi i Fudan backdoorovi

Praktičan vodič „što pritisnuti“ autora **@gromovyna** za napade isključivo na karticu (card-only) na MIFARE Classic koji su ugrađeni u
`NFC → Read`. Stigli su u službenom firmveru **1.1.2** (rad autora [@noproto](https://github.com/noproto)) i dio su
Unleashed firmvera. Dok su se razvijali, jedan je istraživač iz zajednice došao do dvaju važnih otkrića: napada na
**statičke šifrirane noncee** te **backdoor ključeva** u čipovima proizvođača **Fudan** (i drugih) koji omogućuju
čitanje sektora MIFARE Classic oznake bez poznavanja njezinih ključeva. Oboje je ugrađeno u firmver i u
**MFKey 3** (sada [MFKey 4.1](/hr/nfc/mfkey-app)). Znanstveni rad: [eprint.iacr.org/2024/1275](https://eprint.iacr.org/2024/1275.pdf).

::: tip Brži način (ažuriranje, rujan 2026.)
Ako samo želite brzo oporaviti MIFARE Classic ključeve, koristite prateću aplikaciju **qUnleashed**, koja izvršava sve ove
napade, uključujući HardNested, na vašem telefonu ili računalu: pogledajte [Brzi oporavak ključeva s qUnleashedom](/hr/nfc/qunleashed).
:::

## Ukratko o ideji

**Nested napadi** su napadi *isključivo na karticu* (čitač nije potreban): uz poznavanje barem jednog ključa kartice oporavljaju
nepoznate ključeve. Konceptualno se oznake dijele u četiri skupine (strogo govoreći postoje Nested i HardNested, ali je ova
podjela lakša za razumijevanje):

| Oznaka je ranjiva na | Vrsta noncea | Gdje se ključ izračunava |
|---|---|---|
| **Nested** | slabi PRNG | MFKey na Flipperu, qUnleashed |
| **HardNested** | tvrdi PRNG | qUnleashed ili računalo (ne na Flipperu) |
| **Static Nested** | statički nonce | MFKey na Flipperu, qUnleashed |
| **Static Encrypted Nested** (SEN) | statički šifrirani nonce | MFKey na Flipperu (najsporije), qUnleashed |

**Backdoor ključevi** su ključevi koji otvaraju podatke oznake **bez** njezinih pravih ključeva.

Za primjere je autor koristio oznake svake vrste, sa sektorom 0 šifriranim generiranim parom ključeva:
Key A `A3F92C8E7D3A`, Key B `4F6D91C5BA7E` (pristupni bitovi ostavljeni zadani). Na Proxmarku 3 provjera zadanih ključeva prikazala je
te ključeve kao nepoznate:

![Provjera zadanih ključeva na Proxmarku 3](/img/remote/86130b06142278a1.png)

## Korak 1. Pročitajte oznaku

Idite na `Main Menu → NFC → Read` i držite oznaku mirno.

### 1.1 Oznaka ima backdoor

Vidjet ćete zaslone s **Backdoor Read**, a zatim još nekoliko sa **(Backdoor)** u zaglavlju:

![Backdoor Read](/img/remote/1491507f521c09f5.png)

![Čitanje kroz backdoor](/img/remote/e9be977d84486794.png)

To znači da čip ima backdoor: Flipper čita podatke sektora kroz njega i prikuplja noncee kako bi se ključevi mogli
oporaviti. Tipičan je rezultat **pročitani svi sektori, ali manje ključeva nego što je potrebno**:

![Svi sektori, ali samo 30 ključeva](/img/remote/9e7db33e51594779.png)

### 1.2 Oznaka nema backdoor

Tada se pokreće klasično pretraživanje ključeva: najprije **korisnički** rječnik, zatim **sistemski** rječnik.

![Korisnički rječnik](/img/remote/fff8f5662df941b9.png)

![Sistemski rječnik](/img/remote/0da64f609fc2c770.png)

Ako je pronađen barem jedan ključ, Flipper prelazi na **PRNG Analysis**, zatim prolazi kroz **Nested Dictionary**:

![PRNG Analysis](/img/remote/3e0e493fe7fcbd5f.png)

zatim **Calibration** i **Nonce Collection**:

![Kalibracija i prikupljanje noncea](/img/remote/f5b036a96f5a0869.png)

Ako je oznaka ranjiva **samo na HardNested**, prikupljanje noncea traje dulje, a zaglavlje dobiva nastavak **(Hard)**:

![Prikupljanje noncea za oznaku s tvrdim PRNG-om](/img/remote/fca9f1b2e4475631.png)

> U tom slučaju prijeđite izravno na [korak 2.2](#_2-2-the-tag-is-vulnerable-to-hardnested).

Ovdje rezultat izgleda poznatije: broj pronađenih ključeva blizak je broju pročitanih sektora (ovisno o
pristupnim bitovima).

![Rezultat nakon faze nested napada](/img/remote/d15656101dfafcc4.png)

Svi prikupljeni noncei dodaju se u `/ext/nfc/.nested.log`.

## Korak 2. Oporavite ključeve

Idite na `Main Menu → Apps → NFC → MFKey`.

::: warning Provjerite verziju aplikacije
Provjerite odgovara li aplikacija MFKey vašem firmveru te da nije prepisana starim primjerkom ako ste
aplikacije instalirali zasebno. Unleashed isporučuje **MFKey 4.1**.
:::

![Početni zaslon aplikacije MFKey](/img/remote/195a1b6a411e7bf3.png)

Pritisnite <kbd>OK</kbd> **Start** i…

### 2.1 Oznaka je ranjiva na Nested, Static Nested ili Static Encrypted Nested

Započinje postupak probijanja. Možete ostaviti Flipper na miru i raditi nešto drugo:

![Probijanje u tijeku](/img/remote/a514db67a986ae2c.png)

Preostaje samo pričekati. Na hardveru Flippera ovo nije brzo (pozdrav, SPI) i ovisi o:

- vrsti napada: Nested < Static Nested < Static Encrypted Nested (SEN je najsporiji);
- broju nepoznatih ključeva (manje je brže);
- jedinstvenosti ključeva: ključ koji se koristi posvuda pronalazi se brže od djelomično diverzificirane oznake (npr. Iron Logic),
  što je pak brže od potpuno diverzificirane oznake (npr. kolutovi filamenta Bambu Lab).

Sučelje nije uvijek odzivno i ponekad „razmišlja“. Povremeno Flipper može izgledati zamrznuto; nemojte žuriti s
ponovnim pokretanjem. Redak **RAM** na vrhu stalno se mijenja dok posao traje.

::: warning Statički šifrirani noncei
Kod statičkih šifriranih noncea, zbog načina na koji napad funkcionira, noncei se ne označavaju kao „riješeni“; MFKey samo
gradi **kandidate** (ključeve koje kasnije treba provjeriti na oznaci), pa aplikacija može izgledati zaglavljeno na zadnjem (ili nekom
ranijem) koraku. Ako je prošlo dovoljno vremena, izađite i provjerite rezultat (korak 3). Od verzije MFKey 4.x kandidati se
spremaju u **CUID rječnik** za pojedinu karticu `/ext/nfc/assets/mf_classic_dict_<UID>.nfc`, koji `Read` isprobava prvi.
:::

Kada dešifriranje završi, dobit ćete sažetak s brojem ključeva dodanih u korisnički rječnik
(**Keys added to user dict: N**, a za SEN oznake **SEN key candidates: N**):

![MFKey dovršen](/img/remote/c9ef77139b74cc89.png)

Nastavite s korakom 3.

### 2.2 Oznaka je ranjiva na HardNested {#_2-2-the-tag-is-vulnerable-to-hardnested}

To ste mogli prepoznati po zaslonu **(Hard)** tijekom prikupljanja noncea ili će MFKey prikazati pogrešku da nije pronađen nijedan nonce:

![MFKey: nisu pronađeni noncei](/img/remote/2519c7dce0b881c9.png)

HardNested je jedini napad koji se ne može izvesti na Flipperu. Mogućnosti:

- **qUnleashed** (preporučeno, telefon ili računalo): `Tools → Recover MIFARE Keys`, pogledajte [qUnleashed](/hr/nfc/qunleashed).
  Ključevi idu izravno u korisnički rječnik.
- **Računalo s alatom HardnestedRecovery**, kao u izvornom vodiču:
  1. Kopirajte `/ext/nfc/.nested.log` sa SD kartice Flippera na računalo.
  2. Klonirajte i izgradite [github.com/noproto/HardnestedRecovery](https://github.com/noproto/HardnestedRecovery) pomoću
     `make build` (na sustavu Windows koristite WSL ili Docker).
  3. Pokrenite ga sa zapisnikom kao argumentom:

     ```bash
     ./hardnested_main .nested.log
     ```

  4. Ključ se pojavljuje u ispisu:

     ```text
     [=] Hardnested attack starting...
     [=]    0 |    0 | Start using 32 threads                 |                 |
     [=]    0 |    0 | Brute force benchmark: 589 million (2^29.1) keys/s   | 140737488355328 |  3d
     [=]   16 |  256 | Loading nonces from file                |     24286058496 |  41s
     [=]   46 | 1891 | Apply Sum property. Sum(a0) = 128            |      1262183296 |  2s
     [=]   78 | 1894 | Brute force phase completed. Key found: A3F92C8E7D3A  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: A: a3f92c8e7d3a
     ...
     [=]   70 | 1218 | Brute force phase completed. Key found: 4F6D91C5BA7E  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: B: 4f6d91c5ba7e
     ```

::: danger Dodajte ključeve ručno
Za razliku od 2.1, ključevi koje pronađe HardnestedRecovery na računalu **ne** dodaju se automatski. Sami ih dodajte u korisnički rječnik:
`NFC → Extra Actions → MIFARE Classic Keys → Add` ili ih dopišite u
`/ext/nfc/assets/mf_classic_dict_user.nfc`.
:::

## Korak 3. Ponovno pročitajte oznaku

Nakon što su ključevi oporavljeni, ponovno pročitajte oznaku putem `NFC → Read`.

::: tip Profesionalni savjet
Ako ste oznaku spremili nakon prvog čitanja, možete je otključati izravno iz izbornika spremljene kartice:
`Saved → <card> → Unlock with Dictionary`.
:::

![Otključavanje rječnikom iz spremljene kartice](/img/remote/8232d690446c70b6.png)

::: tip Profesionalni savjet
Za bolje performanse sljedeći put očistite `/ext/nfc/.nested.log` nakon što probijete ključeve oznake.
:::

## Povezano

[MIFARE Classic](/hr/nfc/mifare-classic) · [Aplikacija MFKey](/hr/nfc/mfkey-app) · [qUnleashed](/hr/nfc/qunleashed) ·
[MFKey32](/hr/nfc/mfkey) · [Čitači Iron Logic](/hr/nfc/iron-logic) · više članaka na kanalu autora
[@gromovyna](https://t.me/gromovyna)
