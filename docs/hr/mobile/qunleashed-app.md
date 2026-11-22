---
title: Prateća aplikacija qUnleashed
order: 30
original: [https://github.com/DarkFlippers/qUnleashed, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md]
sources: [unleashed-readme, unleashed-docs]
---
# Prateća aplikacija qUnleashed

::: tip Unleashed
**qUnleashed** je vlastita prateća aplikacija tima Unleashed za mobitel i računalo. Napisana je iz
temelja u Flutteru kao alternativa službenoj mobilnoj aplikaciji za Flipper, tako da nije fork
qFlippera. Licenca GPL-3.0-or-later, izvorni kôd i izdanja nalaze se na
[DarkFlippers/qUnleashed](https://github.com/DarkFlippers/qUnleashed).
:::

Izrađena je za Unleashed, ali radi i s drugim firmverima. Trenutačna stabilna inačica je **0.17.2**.

## Hoće li raditi na vašem uređaju?

| Sustav | Što vam je potrebno |
|---|---|
| Android | 10 (API 29) ili noviji |
| iOS | 15 ili noviji |
| macOS | 12 ili noviji |
| Windows | 10 ili noviji, 64-bitni |
| Linux | GLib 2.72 i glibc 2.35 — Ubuntu 22.04, Debian 12, Mint 21 ili noviji |

Stariji Linux neće ni pokrenuti izvršnu datoteku.

## Instalacija

Odaberite inačicu za svoj sustav na
[stranici izdanja](https://github.com/DarkFlippers/qUnleashed/releases). Ne postoji u trgovinama aplikacija niti ima
instalacijsku skriptu.

## Povezivanje

Bluetooth radi na svih pet sustava. USB serijska veza radi na sustavima Android, Windows, macOS i Linux — na iOS-u
uopće nema USB opcije jer Apple ne dopušta aplikacijama komunikaciju sa serijskim USB uređajem.

Aplikacija pamti Flipper uređaje koje ste koristili i sama se ponovno povezuje. Ako je jedan priključen putem USB-a,
ima prednost pred posljednjim Bluetooth uređajem. Na Androidu servis u prednjem planu održava Bluetooth vezu aktivnom
dok je aplikacija u pozadini.

## Firmver

- **Updater** s kanalima release i dev te njihovim popisima promjena (changelog). Preuzima i instalira izravno iz
  aplikacije: osnovnu (base) inačicu Unleasheda, inačicu s dodatnim aplikacijama (extra-apps), kompaktnu (compact) inačicu i službene kanale.
- **Repair from DFU mode** u potpunosti ponovno snima (flasha) Flipper putem USB-a. Ista zamisao kao qFlipperov Full
  Repair, za uređaj koji se više ne pokreće.
- **Obavijesti o izdanjima** nisu obavezne, a dev kanal ima vlastiti zasebni prekidač.

## Uređaj

- **Podatci o uređaju**: inačica firmvera i datum gradnje, baterija, pohrana.
- **Dijeljenje GPS-a i interneta**: mobitel prosljeđuje svoju lokaciju aplikacijama na Flipperu i prenosi
  mrežni promet Flippera. Vaš firmver mora imati RPC GPS/mrežno proširenje za ovo.
- **Udaljena radna površina**: zaslon Flippera uživo na vašem mobitelu ili računalu, s gumbima na zaslonu. Na
  računalu možete koristiti pravu tipkovnicu. Snimke zaslona mogu se izvesti, a zaslon se može snimiti kao
  GIF.
- **Naredbeni redak**: puni Flipper CLI. Samo putem USB-a, stoga nije dostupno na iOS-u.

## Arhiva

Kopija vaših ključeva nalazi se na mobitelu, po jedna arhiva za svaki Flipper. Svaka datoteka označena je kao **synced**,
**remote-only**, **local-only** ili **deleted**, pa možete vidjeti što je gdje, a izbrisana datoteka može se
vratiti. Datoteke se mogu označiti kao favoriti.

Kategorije: Sub-GHz, Wardriving (uključujući automatski spremljene datoteke), RFID 125, NFC, Infrared, iButton, Bad USB,
JavaScript.

Datoteku možete pokrenuti izravno iz aplikacije. NFC, RFID i iButton emuliraju se putem RPC-a; Sub-GHz,
Infrared, Bad USB i JavaScript otvaraju se u odgovarajućoj aplikaciji na Flipperu.

Postoji i uređivač teksta s isticanjem sintakse za Flipperove formate datoteka, pa možete popraviti `.sub` ili `.ir`
datoteku bez računala.

## Upravitelj datoteka

Pregledava `/ext` (SD karticu) i `/int` (unutarnju memoriju). Stvarajte, preimenujte, brišite, preuzimajte, učitavajte i
uređujte tekstualne datoteke.

## Aplikacije

Katalog aplikacija s pretraživanjem, kategorijama, sortiranjem, stranicom s pojedinostima i snimkama zaslona. Instalirajte, ažurirajte i
brišite aplikacije. Također vidi što je već na Flipperu, uključujući predinstalirane aplikacije.

## Alati

- **Pixel Draw**: uređivač piksel-arta s upraviteljem projekata i animacijom u više sličica (frameova). Može uvoziti
  animacije dupina i prikazivati pregled uživo na Flipperu.
- **Extract MIFARE Keys**: pokreće Mfkey32 na mobitelu iz noncesa koje je Flipper prikupio. Cijeli
  postupak nalazi se na stranici [Brzi oporavak ključeva pomoću qUnleasheda](/hr/nfc/qunleashed).
- **Remotes Library**: infracrveni daljinski upravljači iz službenog izvora i iz javnog
  repozitorija [Lucaslhm/Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB). Pregledavajte, pretražujte, uređujte
  `.ir` datoteku, zatim je spremite u arhivu ili izravno u `/ext/infrared`.
- **Pulse Plotter**: iscrtava sirove (raw) snimke impulsa iz Sub-GHz-a, infracrvenog područja i RFID-a.
- **Saved Locations**: oznake na karti izrađene iz geografske širine i dužine pohranjene u datotekama arhive.

## Oporavak Seeda za Sub-GHz snimke

Neki daljinski upravljači temeljeni na KeeLoqu (FAAC SLH, Genius, Erreka, stariji BFT Mitto) koriste tajni **Seed** koji je potreban za njihovo
dekodiranje. Flipper samo prikuplja podatke pomoću aplikacije [Seed Capturer](/hr/subghz/seed-capturer); sama pretraga jest
iscrpno pretraživanje (brute force), pa se izvodi u qUnleashu, a ne na Flipperu.

1. Snimite daljinski upravljač pomoću `Apps → Sub-GHz → Seed Capturer`: pritisnite **isti gumb** više puta, jednim ujednačenim pritiskom
   odjednom, i provjerite raste li brojač `Hops` pri svakom pritisku.
2. Povežite Flipper s **qUnleashedom** i otvorite njegov alat **Seed recovery**.
3. Odaberite svoju snimku s popisa. qUnleashed čita snimke izravno iz Flipperove
   mape `subghz_seed_captures`; proizvođač, frekvencija, vrijednosti `Fix` i `Hop` već su u datoteci. **Nemojte
   kopirati, premještati, preimenovati niti uređivati nikakve datoteke.**
4. Pokrenite pretragu i pričekajte.
5. Ako se Seed pronađe, qUnleashed vraća Seed i brojač te može **spremiti gotovi klon daljinskog upravljača** kao
   `.sub` datoteku za vas (`Fix` već sadrži serijski broj i gumb). Vratite je na Flipper i pošaljite, bez
   potrebe za upisivanjem kroz `Add Manually`.
6. Ako ništa nije pronađeno, snimka je najvjerojatnije imala prekid. Snimite ponovno držeći daljinski upravljač tik uz Flipper
   i pritisnite `Reset` (<kbd>←</kbd>) za ponovni početak ako se pritisak ne registrira.

::: warning Seed pripada instalaciji
Na sustavima FAAC SLH i Genius Seed je **različit za svaki gumb**, stoga snimite gumb koji namjeravate koristiti. Na sustavu Erreka
Seed je po daljinskom upravljaču (ponekad po instalaciji). Na sustavu BFT Mitto jest po daljinskom upravljaču, a snimanje je potrebno samo za starije daljinske upravljače s
jedinstvenim Seedom.
:::

Cijeli postupak, uključujući programiranje klona u prijamnik, nalazi se na stranicama
[Programiranje daljinskih upravljača s promjenjivim kodom](/hr/subghz/remote-prog) i [KeeLoq](/hr/subghz/keeloq).

Koristite ovo samo na vlastitim daljinskim upravljačima i vratima.

## Povezane stranice

- [Brzi oporavak ključeva pomoću qUnleasheda](/hr/nfc/qunleashed)
- [Seed Capturer](/hr/subghz/seed-capturer)
- [Mobilna aplikacija Flipper](/hr/mobile/mobile-app)
- [qFlipper](/hr/mobile/qflipper)
- [Web alati](/hr/mobile/web-tools)
