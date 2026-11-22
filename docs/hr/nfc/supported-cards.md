---
title: Podržane kartice (parseri)
order: 85
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/nfc/read]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Podržane kartice (parseri)

Za mnoge kartice Flipper ne ispisuje samo sirovu memoriju, već je i **dekodira**: broj kartice, saldo, preostale vožnje, valjanost, podatke hotelske sobe, figurice za igre… To rade **dodaci za parsiranje (parser plugins)**, male `.fal` datoteke koje NFC aplikacija učitava sa SD kartice nakon uspješnog čitanja. Kada parser prepozna karticu, zaslon rezultata čitanja prikazuje dekodirane podatke umjesto sirovog sažetka; **More** vodi u uobičajeni izbornik.

Neki parseri sadrže i **ključeve** kartičnog sustava (ili funkciju za izvođenje ključeva). Za MIFARE Classic kartice to znači da Flipper čita karticu **potpuno bez napada rječnikom**: parser najprije provjerava pripada li kartica tom sustavu, a zatim je čita s pravim ključevima.

::: tip Unleashed
Unleashed uključuje brojne parsere kojih nema u izvornom firmveru, osobito za sustave u Rusiji i ZND-u: Umarsh, Zolotaya Korona (i Online), Kazan, Metromoney, Moscow Social Card, prerađeni Troika, Plantain, Troika+Plantain, karte prigradske željeznice PPK, kao i Bambu Lab filament, arkadne kartice Banapass/Aime/AIC, glave četkica Sonicare i drugo (autori @Leptopt1los, @assasinfil i brojni suradnici).
:::

## Popis parsera

Ugrađeni ključevi = parser može pročitati karticu vlastitim ključevima (ili izvođenjem ključa), bez potrebe za rječnikom.

### Prijevoz

| Kartica (kako se prikazuje) | Protokol | Regija | Ugrađeni ključevi | Prikazuje |
|---|---|---|---|---|
| Troyka card | MIFARE Classic | Moskva, Rusija | da | podatke prijevozne aplikacije |
| Plantain Card | MIFARE Classic | Sankt-Peterburg, Rusija | da | podatke kartice, prigradsku kartu PPK |
| Troika+Plantain | MIFARE Classic | Rusija | da | obje aplikacije na jednoj kartici |
| Social card (Moscow Social Card) | MIFARE Classic | Moskva, Rusija | da | broj kartice (OMC), valjanost |
| Kazan transport card | MIFARE Classic | Kazan, Rusija | da | vrstu karte, saldo |
| Umarsh | MIFARE Classic | Rusija (regionalni sustavi) | ne (ključ B potreban za sektore 0, 8, 12) | podatke kartice |
| Zolotaya korona | MIFARE Classic | Rusija | ne | podatke kartice |
| Zolotaya korona (Online) | MIFARE Classic | Rusija | ne | podatke kartice i tarife |
| SZPPK Accompany Card | MIFARE Classic | Rusija, prigradska željeznica (SZPPK) | da | valjanost, postaju, ulazak/izlazak, brojač prolazaka |
| SKPPK Transport Card | MIFARE Classic | Rusija, prigradska željeznica (SKPPK) | da | postaju, zadnji prolazak, status, brojač prolazaka |
| SevPPK Transport Card | MIFARE Classic | Rusija, prigradska željeznica (SevPPK) | da | postaju, zadnji prolazak, status, brojač prolazaka |
| Metromoney | MIFARE Classic | Tbilisi, Gruzija | da | podatke karte |
| CharlieCard | MIFARE Classic | Boston (MBTA), SAD | da | saldo, transakcije |
| Clipper | MIFARE DESFire | San Francisco Bay Area, SAD | — | serijski broj, saldo, vožnje (prijevoznik, cijena, datum) |
| Ventra | MIFARE Ultralight | Chicago (CTA), SAD | — | preostale vožnje, istek valjanosti |
| Tarjeta Bip! | MIFARE Classic | Santiago, Čile | da | broj kartice, saldo |
| SmartRider | MIFARE Classic | Perth, Australija | da | saldo, popust, serijski broj |
| Opal | MIFARE DESFire | Sydney, Australija | — | saldo, zadnji ulaz/izlaz |
| myki | MIFARE DESFire | Melbourne, Australija | — | broj kartice |
| ITSO Card | MIFARE DESFire | Ujedinjeno Kraljevstvo | — | podatke kartice |
| TRT Tianjin Metro | MIFARE Ultralight | Tianjin, Kina | — | saldo, datum prodaje |
| All-In-One | MIFARE Ultralight | prijevozna karta | — | broj, preostale vožnje |

### Pristup, hoteli, plaćanje i servis

| Kartica (kako se prikazuje) | Protokol | Čemu služi | Ugrađeni ključevi | Prikazuje |
|---|---|---|---|---|
| HID Card | MIFARE Classic | HID vjerodajnica pohranjena na Classic kartici | da | duljinu u bitovima i vrijednost vjerodajnice |
| Gallagher NZ | MIFARE Classic | Gallagher kontrola pristupa (Novi Zeland) | — | vjerodajnice (kartica može sadržavati više njih) |
| Saflok MFC 1K Card / Saflok UL-C Card | MIFARE Classic, Ultralight C | Saflok hotelske brave | da (KDF) | broj objekta, ID ključa, zapis ključa, razinu pristupa |
| H World Card | MIFARE Classic | H World hotelski ključevi (kontinentalna Kina) | da | broj sobe, datum prijave i isteka |
| CSC Service Works | MIFARE Classic | dopunjiva kartica za praonice rublja (SAD) | — | saldo, zadnja nadoplata, preostala korištenja |
| WashCity | MIFARE Classic | WashCity / MarkItaly kartica za praonice (Europa) | da | saldo u EUR |
| MiZIP Card | MIFARE Classic | MiZIP ključevi za automate | da | UID, kredit, prethodni kredit |
| Microel Card | MIFARE Classic | Microel ključevi za automate | da (izvedeni iz UID-a) | UID, kredit, prethodni kredit |
| HI! Card | MIFARE Classic | HI! kartica | da | UID |
| MyKey | ST25TB | MyKey ključevi za automate | — | serijski broj, prazno/zaključano stanje, LockID |
| EMV | EMV | bankovne kartice | — | pogledajte [Bankovne kartice (EMV)](/hr/nfc/emv) |

### Igre, igračke i ostalo

| Kartica (kako se prikazuje) | Protokol | Čemu služi | Ugrađeni ključevi |
|---|---|---|---|
| Aime Card | MIFARE Classic | SEGA Aime arkadna kartica (pristupni kôd) | da |
| Banapass | MIFARE Classic | Bandai Namco Passport (pristupni kôd, vrijednost) | da |
| Amusement IC Card | FeliCa | arkadne kartice (SEGA Aime, Bandai Namco Passport) | — |
| Skylanders | MIFARE Classic | Skylanders figurice (naziv lika) | da |
| Disney Infinity | MIFARE Classic | Disney Infinity figurice | da (izvedeni) |
| Bambu Lab Filament | MIFARE Classic 1K | oznake koluta Bambu Lab filamenta (vrsta, kôd filamenta, materijal, boja…) | da (izvedeni) |
| Philips Sonicare head | MIFARE Ultralight | glave četkica Sonicare | — |
| NDEF Format Data | Ultralight/NTAG, MIFARE Classic, SLIX, Type 4 Tag | NDEF poruke: URI (uklj. telefon, e-poštu), tekst, Bluetooth MAC, kontakt, Wi-Fi, SmartPoster | — |

Izvorni kôd svakog parsera nalazi se u [`applications/main/nfc/plugins/supported_cards`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards). Neki parseri koriste tablice pretraživanja iz `/ext/nfc/assets/` (primjerice `skylanders.nfc`, `vendors.nfc`, `sk_id.nfc`, `sz_id.nfc`, `sev_id.nfc` za nazive postaja, te `aid.nfc`/`country_code.nfc`/`currency_code.nfc` za EMV).

## Napomene

- Parser za karticu s oznakom „ugrađeni ključevi” najprije provjerava karticu; ako provjera ne uspije (drugi ključevi, drugi sustav), pokreće se uobičajeni napad rječnikom.
- Neki parseri navode što nedostaje, npr. *"Unknown SKPPK Card — TICKET BLOCKS NOT READ — RUN A DICTIONARY ATTACK TO READ THE TICKET SECTORS"*.
- **"Plugin Not Loaded — Plugin file missing or outdated. Update the firmware resources."**: `.fal` datoteke na SD kartici ne odgovaraju firmveru. Ponovno instalirajte firmver s umetnutom SD karticom.
- Parser samo prikazuje podatke. Mijenjanje salda u zapisu memorije i njegova emulacija predstavljaju prijevaru u prijevoznim i platnim sustavima.

## Povezano

[Čitanje kartica](/hr/nfc/read) · [Bankovne kartice (EMV)](/hr/nfc/emv) · [MIFARE Classic](/hr/nfc/mifare-classic) · [Moskvyonok kartice](/hr/nfc/moskvyonok)
