---
title: NFC Magic 2.0
order: 55
author: gromovyna
original: [https://telegra.ph/NFC-Magic-20---magiya-teper-i-dlya-Ultralight-06-25, https://t.me/gromovyna/31, https://docs.flipper.net/zero/nfc/magic-cards, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# NFC Magic 2.0: pisanje i brisanje magic praznih kartica

**NFC Magic** je aplikacija za pisanje, kloniranje i brisanje [magic praznih kartica](/hr/nfc/magic-cards) izravno s Flippera. Započela je kao službena aplikacija za Flipper Zero; verzija opisana ovdje nalazi se u paketu [all-the-plugins](https://github.com/xMasterX/all-the-plugins) autora **xMasterX** i održava je tim **Unleashed** (napravili su fork i nastavljaju je razvijati). Verziju **2.0** napisao je **@gromovyna**: cijeli ciklus od istraživanja transportnog sloja do posljednjeg gumba u korisničkom sučelju.

Prije verzije 2.0 aplikacija je podržavala magic kartice **MIFARE Classic** (Gen1a, Gen2) i univerzalni **Gen4** (UMC/GTU), podesivi čip koji nije vezan uz MFC. Verzija 2.0 donosi **Ultralight/NTAG** magic prazne kartice i iskrene rezultate.

![Nova verzija, nova ikona](/img/remote/dafa43486592335f.png)

::: tip Gdje je nabaviti
NFC Magic **nije dio binarne datoteke firmvera**: to je vanjska aplikacija iz paketa extra apps pack. Verzija 2.0 dostupna je u Unleashed **dev izdanjima od 1307**. Ažurirajte aplikaciju putem kataloga ili ažurirajte firmver na svježe dev izdanje (s paketom extra apps pack). Putanja na uređaju: `Main Menu → Apps → NFC → NFC Magic`.
:::

## Prije nego počnete

1. [Pročitajte](/hr/nfc/read) izvornu karticu i **spremite** je. Provjerite jesu li pročitani **svi** sektori (MIFARE Classic) ili stranice (Ultralight/NTAG): djelomičan ispis daje djelomičnu kopiju.
2. Za prazne kartice MIFARE Classic, NFC Magic se autentificira ključevima iz **predmemorije ključeva** te **korisničkog i sustavnog rječnika**, ni s čim drugim. Ako su ključevi vaše kartice došli iz CUID rječnika, prvo na ispisu pokrenite **Save Keys to Dictionary** (pogledajte [MIFARE Classic](/hr/nfc/mifare-classic#save-keys-to-dictionary)).

## Korak 1. Prepoznavanje

Sve počinje kada prislonite praznu karticu na Flipper (`Check Magic Tag`). Prva velika promjena: aplikacija više nije fiksirana na MIFARE Classic. Skener radi **prvo po obitelji**: najprije prepoznaje obitelj (**MFC** ili **Ultralight/NTAG**), a tek onda traži točnu varijantu.

Za **USCUID-UL** (magic prazne kartice obitelji Ultralight) prepoznaje se cijeli glavni raspon modela, plus dio lokalnog ruskog tržišta: **UL11**, **UL21** (uključujući ono što se na tržištu bivšeg SSSR-a prodaje kao **"Ultra"**), **NTAG213/215/216**, **UL-C**, **UL-5** te oznake koje su već u **backdoor** načinu (provjeravaju se oba niza buđenja).

![Prepoznat USCUID-UL](/img/remote/557fa5d47ebeb0a6.png)

Ako imate predložak koji aplikacija ne poznaje, ne odustaje: prikazuje **sirovu konfiguraciju**, pa sami možete vidjeti i analizirati sirove postavke. Korisno za istraživače.

![Sirova konfiguracija 1](/img/remote/7c3f38df0079d8fa.png)

![Sirova konfiguracija 2](/img/remote/c16eb844763ef4fa.png)

![Sirova konfiguracija 3](/img/remote/30f2a4b10d4be98a.png)

Za **Gen4** karticu zaštićenu lozinkom: `Gen4 Actions → Auth with password`, unesite lozinku, zatim provjerite oznaku.

## Korak 2. Pisanje Ultralight / NTAG

Kada je oznaka prepoznata, možete pisati i u potpunosti klonirati **UL/NTAG**. Ono o čemu **ne** morate razmišljati jest transport: aplikacija ga bira na temelju rezultata prepoznavanja.

- **Direct**: uobičajeno pisanje prema normi ISO14443-3 naredbom **`A2`**, za oznake koje izravno prihvaćaju pisanje (npr. tvorničke konfiguracije **USCUID-UL**, isti **UL21**, poznat i kao **"Ultra"**).
- **Backdoor**: ako čip ima izložen backdoor, aplikacija ga koristi (sirovo buđenje plus backdoor naredbe). Jednostavna logika: izložen backdoor → koristi ga; nema ga → piši izravno.

Vaše odluke:

- **Pišete na oznaku bez backdoora s poznatom lozinkom?** Unesite je putem **PWD-AUTH**: aplikacija se autentificira prema oznaci prije pisanja ili brisanja.
- **Oznaka nije potvrđena kao magic, ali znate da jest?** Pritisnite **Write anyway** i preuzmite odgovornost.

Postupak pisanja učinjen je što manje stresnim:

- **Napredak uživo "Writing X/N"** na zaslonu, tako da ne gledate u zamrznut zaslon pitajući se događa li se išta.

  ![Napredak pisanja (brzo: za snimku zaslona bio je potreban NTAG216)](/img/remote/9914d55ba866082e.png)

- **Redoslijed stranica** prilagođen je svakoj vrsti oznake (npr. **UL-5**) i **razlikuje se za pisanje i brisanje** zbog bitova zaključavanja. Pri pisanju servisne stranice (uključujući UID) idu **zadnje**: zapišete li zaključavanje/zaštitu prerano, oznaka će se zaključati prije nego što ispis završi. Brisanje ide uzlaznim redoslijedom kako bi se prvo uklonilo statičko zaključavanje, a tek potom očistio ostatak.
- Pisanje je **samo s potvrdom ACK i nastavkom pri pogrešci**: aplikacija ne staje na prvoj neuspjeloj stranici, već zapisuje sve što može.
- Ako nešto nije prošlo, dobivate **Partial Write** s popisom **Details** koji točno navodi stranice koje nisu uspjele, umjesto veselog "done". Odmaknuli ste oznaku s antene na pola puta? Vratite je natrag i pisanje se nastavlja s istog mjesta.

![Djelomično pisanje](/img/remote/a50fa90dff60cdd8.png)

![Pojedinosti](/img/remote/71b6fa77e1914b76.png)

A **Wipe** vraća oznaku u tvorničko stanje jednim pritiskom.

## Korak 3. Pisanje MIFARE Classic

1. U aplikaciji NFC Magic odaberite **Check Magic Tag** i prislonite praznu karticu na stražnju stranu Flippera.
2. Kada se kartica prepozna (Gen1a, Gen2, Gen4…), idite na **More** za mogućnosti te vrste kartice.
3. **Write**: odaberite izvornu karticu u pregledniku datoteka i prislonite praznu karticu na Flipper.
4. **Wipe** formatira praznu karticu: UID se vraća na zadano, podaci u sektorima/stranicama se brišu.

### Iskrena povratna informacija: Success / Partial / Fail

Ovo se odnosi na dobri stari **MIFARE Classic (Gen2)** i autoru je jednako važno kao i nove funkcije.

Ranije su brisanje i kloniranje MFC-a **uvijek** prijavljivali "Success". Uvijek, čak i kada nije zapisan nijedan bajt. To nije samo bug, to je laž: odlazite uvjereni da vam kopija radi, a ona ne radi.

Sada se operacije prate **blok po blok** i dobivate iskren ishod: **Success / Partial / Fail**. Kod **Partial** vidite **Details**: koji blokovi nisu zapisani ili izbrisani. Blok 0 koji je samo za čitanje više ne ruši cijeli sektor 0 u izvješću (kao u izvornoj izvedbi), što je korisno i kada je oznaka zatvorena putem **access bits**.

![Rezultat](/img/remote/9e9d84e664f7da06.png)

![Pojedinosti djelomičnog rezultata](/img/remote/525faf18552333d1.png)

Stvari koje čuvaju živce:

- Pri brisanju blok 0 **zadržava stvarni SAK/ATQA** oznake. Klasičan slučaj: **Perfect CUID** (odgovara na RATS / ima ATS). Firmver ga je prepoznao kao 4K i brisanje je upisalo blok 0 kao 4K. Ispravljeno: 1K ostaje 1K, a UID se poništava.
- Nema ispravnog ključa za brisanje? Umjesto uzaludnog pokušaja pisanja odmah vidite **"No keys found"**.
- Svaki zaslon neuspjeha (Wipe / Write / Dump) ima **Exit → menu**, tako da se ne osjećate zarobljeno.
- Nestala je neugodna pogreška: ključevi s prethodne oznake **više se ne prenose** na sljedeću operaciju. Napad rječnikom sada svaki put ponovno čita oznaku umjesto ponovne upotrebe ključeva zadnje oznake (što je moglo dati lažan dojam uspjeha i prividnu brzinu).

## Zaštita od pogrešaka

Već u prethodnom izdanju aplikacija je dobila zaštitu za magic MFC oznake i različite duljine **UID**-a. Verzija 2.0 provjerava može li se ispis doista zapisati na zadanu varijantu **USCUID-UL**:

![Provjera kompatibilnosti ispisa i prazne kartice](/img/remote/a4dc82f2b66b73b5.png)

te, za posebno nadarene, blokira pokušaje spajanja **različitih obitelji** (MFC ispis na Ultralight praznu karticu i obrnuto; takvi se slučajevi redovito pojavljuju na forumima i u razgovorima):

![Nepodudaranje obitelji](/img/remote/83e6e6cf1f0d9da6.png)

## Složenije je nego što izgleda

Iza popisa funkcija stoji gotovo **3000 redaka** izmjena: ispitivač za USCUID-UL napisan od nule, logika za Gen2 napisana iznova i mnoštvo ispravljenih pogrešaka. Sve je to **provjereno na stvarnom hardveru** uz **QA matricu od gotovo 100 slučajeva**:

- **~15 testnih oznaka**: kupljene ili izrađene varijante USCUID-UL (UL11, UL21 (NXP i Mikron "Ultra"), NTAG213/215/216, UL-C, UL-5, nekoliko varijanti UL-Y za rubne slučajeve), oznake u backdoor načinu (oba buđenja), plus prave nemagične i potpuno zaključane oznake za iskrene neuspjehe te hrpa oznaka za regresijsko testiranje;
- **kategorije**: prepoznavanje (17 slučajeva), direct/backdoor transport, cjelovitost podataka i redoslijed stranica, UX scenariji, PWD-AUTH, wipe, opsežan blok za Gen2/MFC brisanje (19 slučajeva) i regresija svih starih protokola (Gen1a 4/7 bajtova, Gen2, Gen4, obični MFC).

To je testiranje otkrilo i uklonilo mnoge pogreške: lažni "Success", neaktivne tipke, curenje memorije, indikator učitavanja koji se beskonačno vrtio na pravom Ultralightu. Poznata ograničenja (uključujući nijansu prepoznavanja 1K/4K na razini firmvera) dokumentirana su.

Sljedeće na popisu: podrška za pisanje **UL-C** na USCUID-UL i moguće regionalno specifične egzotične kartice.

## Rješavanje problema

- **Oznaka nije prepoznata**: možda nije magic oznaka ili je riječ o nepoznatom predlošku: provjerite sirovu konfiguraciju. Za Gen4 s lozinkom prvo se autentificirajte.
- **"No keys found"** pri brisanju MFC-a: trenutačni ključevi prazne kartice nisu u vašim rječnicima. Dodajte ih (`NFC → Extra Actions → MIFARE Classic Keys → Add`).
- **Partial write**: vratite oznaku i nastavite; provjerite **Details**. Bitovi zaključavanja/pristupa na izvornom ispisu mogu učiniti neke blokove/stranice nepogodnima za pisanje.
- **Čitač odbija kopiju**: čitač možda filtrira vašu vrstu prazne kartice. Pogledajte [Magic kartice](/hr/nfc/magic-cards), [Iron Logic](/hr/nfc/iron-logic), [Vizit filtri](/hr/nfc/vizit-filters).

## Povezano

[Magic kartice](/hr/nfc/magic-cards) · [MIFARE Classic](/hr/nfc/mifare-classic) · [qUnleashed](/hr/nfc/qunleashed) · [Otključavanje kartica](/hr/nfc/unlock-with-password)
