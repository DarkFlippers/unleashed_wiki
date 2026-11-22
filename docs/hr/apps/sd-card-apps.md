---
title: Aplikacije na SD kartici (.fap)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Aplikacije na SD kartici (.fap)

Gotovo svaka aplikacija koju pokrećete iz `Main Menu → Apps` jest **FAP** (Flipper App Package): izvršna datoteka `.elf` s
dodatnim metapodacima (naziv, ikona, kategorija, potrebna verzija API-ja) i opcionalnim priloženim resursima. FAP-ovi se
nalaze na microSD kartici, pa je **za pokretanje aplikacija potrebna SD kartica**.

## Gdje se aplikacije nalaze

| Putanja | Što se tamo nalazi |
|---|---|
| `/ext/apps/<Category>/*.fap` | instalirane aplikacije, po jedna mapa za svaku kategoriju (`Sub-GHz`, `NFC`, `RFID`, `GPIO`, `USB`, `Bluetooth`, `Games`, `Tools`, …) |
| `/ext/apps_data/<appid>/` | podatci i postavke koje svaka aplikacija sprema za sebe |
| `/ext/apps_data/loader/plugins/` | dodatci učitavača (loader plugins), na primjer [stilovi glavnog izbornika](/hr/apps/menu-styles) |

`Main Menu → Apps` prikazuje mape unutar `/ext/apps`. Kartica **Apps** u aplikaciji [Archive](/hr/apps/archive) navodi
istu mapu i također prikazuje `.js` skripte.

## Kako Flipper pokreće FAP

MCU ne može izvršavati kôd izravno s vanjske pohrane. Kada pokrenete aplikaciju, **App Loader**:

1. čita FAP s SD kartice te provjerava njegov integritet i manifest;
2. provjerava podudara li se **glavna verzija API-ja** (major API version) aplikacije s glavnom verzijom API-ja firmvera;
3. kopira sekcije kôda i podataka u RAM te prilagođava adrese za novu lokaciju (relokacija);
4. razrješava svaku funkciju koju aplikacija uvozi putem **tablice simbola** firmvera;
5. pokreće aplikaciju.

Budući da se aplikacija izvršava iz RAM-a, velika aplikacija ostavlja manje slobodnog heapa za sve ostalo. Učitavaju se
samo kôd i podatci, pa je količina zauzetog RAM-a manja od veličine same `.fap` datoteke.

::: tip Unleashed
Unleashed zadržava službeni API (trenutačna verzija API-ja ispisana je na vrhu svakog popisa promjena, na primjer
`Current API: 88.27`), pa većina aplikacija iz službenog kataloga radi bez izmjena. Ako se glavna verzija API-ja
razlikuje, Unleashed je neće odmah odbiti: prikazat će **App Too Old** ili **App Too New** s obje verzije (na primjer
`APP:86 < FW:88`) i gumb **Continue**, tako da je svejedno možete pokušati pokrenuti. Pogledajte
[Rješavanje problema s aplikacijama](/hr/apps/troubleshoot).
:::

## Instalacija aplikacija

### Iz paketa aplikacija

Najjednostavniji način jest odabrati inačicu firmvera koja već uključuje paket (zadana ili `e` inačica), pogledajte
[Aplikacije uključene uz Unleashed](/hr/apps/catalog).

Oba paketa dolaze iz repozitorija [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Za ručno dodavanje:

1. Preuzmite `.zip` sa [stranice izdanja](https://github.com/xMasterX/all-the-plugins/releases/latest).
2. Raspakirajte ga.
3. Kopirajte mape aplikacija u mapu `apps` na SD kartici (`/ext/apps/`), pazeći da zadržite njihove mape kategorija.
4. Provjerite podudara li se verzija API-ja paketa s vašim firmverom (`Current API:` na vrhu popisa promjena).

### Iz službenog kataloga {#installing-from-the-official-catalog}

Službeni katalog aplikacija (Apps Catalog) dostupan je u [Flipper Labu](https://lab.flipper.net/apps) (Chrome, Edge i drugi
Chromium preglednici s Web Serial podrškom) te na kartici **Apps** u [mobilnoj aplikaciji Flipper](/hr/mobile/mobile-app).

1. Zatvorite qFlipper i sve druge kartice Flipper Laba (samo jedan program može koristiti USB serijski priključak).
2. Povežite Flipper putem USB-a (Flipper Lab) ili Bluetootha (mobilna aplikacija).
3. Otvorite **Apps**, pronađite aplikaciju prema kategoriji ili pretragom.
4. Pritisnite **Install** na kartici aplikacije ili na njezinoj stranici i pričekajte da se prenese.
5. Na Flipperu otvorite `Main Menu → Apps → <category> → <app>`.

Za ažuriranje ili brisanje aplikacija iz kataloga otvorite **Apps → Installed** i pritisnite **Update** ili ikonu za brisanje (koš).

Ako instalacija ne uspije: provjerite vezu, oslobodite prostor na SD kartici (obrišite datoteke u aplikaciji
[Archive](/hr/apps/archive)) i provjerite imate li aktualnu verziju firmvera.

### Ručno (bilo koji `.fap`)

1. Preuzmite `.fap` izgrađen za vaš firmver (Unleashed inačicu ili OFW inačicu s odgovarajućom verzijom API-ja).
2. Kopirajte ga u `/ext/apps/<Category>/` pomoću programa [qFlipper](/hr/mobile/qflipper), upravitelja datoteka u mobilnoj aplikaciji ili čitača kartica.
3. Pokrenite ga iz `Main Menu → Apps`, ili otvorite datoteku u aplikaciji [Archive](/hr/apps/archive) i odaberite **Run**.

::: warning
Aplikacije izgrađene za drugi fork firmvera mogu uvoziti funkcije koje Unleashed ne izvozi, te će tada javiti pogrešku
**Missing Imports**. Koristite aplikacije iz Unleashed paketa ili ih ponovno izgradite za Unleashed SDK.
:::

## Izgradnja vlastitog FAP-a

FAP-ovi se razvijaju potpuno jednako kao i ugrađene aplikacije. Ukratko:

1. Stavite mapu svoje aplikacije u `applications_user/` kopije izvornog kôda firmvera.
2. U njezinoj datoteci `application.fam` postavite `apptype=FlipperAppType.EXTERNAL` (pogledajte [Manifesti aplikacija](/hr/dev/app-manifests)).
3. Izgradite jednom od sljedećih naredbi:

```bash
./fbt fap_{APPID}                                     # izgradi jednu aplikaciju
./fbt launch APPSRC=applications_user/path/to/app     # izgradi, prenesi putem USB-a i pokreni
./fbt build APPSRC=applications_user/path/to/app      # izgradi bez prijenosa
./fbt faps                                            # izgradi sve FAP-ove (ili ./fbt fap_dist)
```

U zadanom profilu za VS Code naredba `launch` jest radnja **Launch App on Flipper** (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>).

**Resursi (assets).** Stavite slike u podmapu aplikacije i navedite je u `fap_icon_assets`; zatim dodajte `#include "{APPID}_icons.h"`
i koristite ih kao ikone iz `assets_icons.h`.

**Verzioniranje API-ja.** Aplikacijama nije dostupna svaka funkcija firmvera: izvezeni skup naveden je u datoteci
`api_symbols.csv` pojedinog hardverskog cilja. Glavna verzija raste pri prijelomnim promjenama (uklonjena funkcija ili
varijabla, promijenjen potpis), a sporedna verzija pri dodavanjima. `fbt` time upravlja automatski: novi simboli pojavljuju
se s oznakom `?` te svaki morate označiti s `+` (izvezen) ili `-` (skriven) prije nego što se firmver izgradi.

**Otklanjanje pogrešaka (debugging).** `fbt` učitava `debug/flipperapps.py` u gdb, pa FAP možete otklanjati baš kao kôd
firmvera. Izgradite i instalirajte firmver (`./fbt`, `./fbt flash`), pokrenite svoj FAP, zatim se povežite s `./fbt debug`.
Firmver zaustavlja izvođenje na točki prekida odmah nakon učitavanja FAP-a, tako da možete postaviti svoje točke prekida.
Vrsta izgradnje firmvera i aplikacije (debug/release) mora se podudarati, a odgovarajuća izgradnja mora biti povezana kao `build/latest`.

Više u člancima [Izgradnja firmvera](/hr/dev/build), [fbt](/hr/dev/fbt) i [Vaša prva aplikacija u jeziku C](/hr/dev/first-app-c).

## Povezane stranice

- [Aplikacije uključene uz Unleashed](/hr/apps/catalog)
- [Rješavanje problema s aplikacijama](/hr/apps/troubleshoot)
- [Archive (preglednik datoteka)](/hr/apps/archive)
