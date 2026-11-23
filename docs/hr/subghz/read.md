---
title: Read
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Read

**Read** osluškuje na jednoj frekvenciji (ili skače između više njih), **dekodira** signale poznatih protokola i prikazuje ih
kao popis. Dekodirani signal može se spremiti kao datoteka ključa i ponovno poslati. To je glavni način kopiranja daljinskog upravljača sa
**statičnim (fiksnim) kodom** — vrata, rampe, zvonca, utičnice — te za prepoznavanje protokola koji daljinski upravljač koristi.

Za daljinske upravljače koje Read ne prepoznaje koristite [Read RAW](/hr/subghz/read-raw). Za daljinske upravljače s promjenjivim kodom pročitajte
[Promjenjivi kodovi](/hr/subghz/rolling-codes) **prije** nego što išta pošaljete.

::: tip Unleashed
U usporedbi sa službenim firmverom, Unleashed dodaje: desetke dodatnih protokola ([cijeli popis](/hr/subghz/supported-systems)),
spremanje i slanje mnogih protokola s **promjenjivim kodom**, **prilagođene tipke** na strelicama pri slanju, skakanje frekvencija (hopping) s
RSSI pragom, filtre `Ignore …`, `Delete old signals when memory is full`, **držanje <kbd>→</kbd> za brisanje**
signala s popisa, prikaz vremena prijama za svaki signal te pamćenje zadnjih postavki.
:::

## Čitanje daljinskog upravljača

1. Najprije pronađite frekvenciju ako je ne znate: [Frequency Analyzer](/hr/subghz/frequency-analyzer)
   (dugi pritisak na <kbd>OK</kbd> tamo izravno prelazi u Read na pronađenoj frekvenciji).
2. Otvorite `Main Menu → Sub-GHz → Read`. Zaslon prikazuje `Fixed scan...` (ili `Hopper scan...` ako je skakanje uključeno),
   te trenutnu frekvenciju i modulaciju na dnu.

   ![Zaslon Read u očekivanju signala: Fixed scan na 433.92 MHz, AM650](/screens/subghz/read.png)

3. Držite daljinski upravljač blizu lijeve strane Flippera i pritisnite njegovu tipku na 1–2 sekunde.
4. Dekodirani signal pojavljuje se na popisu kao `naziv protokola` + vrijeme prijama. Brojač na dnu prikazuje
   koliko je signala na popisu.

   ![Popis Read s tri primljena signala: Princeton, CAME 12bit i KL: DoorHan](/screens/subghz/read_list.png)

5. Odaberite ga pomoću <kbd>↑</kbd> <kbd>↓</kbd> i pritisnite <kbd>OK</kbd> za pregled pojedinosti (ključ, broj bitova, serijski broj,
   tipka, brojač, proizvođač za KeeLoq itd.).

   ![Pojedinosti signala: Princeton 24bit s ključem, serijskim brojem i tipkom, gumbi Send i Save](/screens/subghz/signal_info.png)

6. Pritisnite <kbd>→</kbd> **Save**, unesite naziv i potvrdite. Datoteka ide u `/ext/subghz/`.
7. Ili pritisnite <kbd>OK</kbd> **Send** za trenutačno odašiljanje.

Spremljeni signali nalaze se u `Main Menu → Sub-GHz → Saved` (pogledajte [u nastavku](#saved-signals)).

## Tipke na zaslonu Read

| Tipka | Radnja |
|---|---|
| <kbd>←</kbd> | **Config** — postavke prijamnika |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Kretanje po popisu primljenih signala |
| <kbd>OK</kbd> | Otvaranje odabranog signala |
| držanje <kbd>→</kbd> | Brisanje odabranog signala s popisa |
| <kbd>Back</kbd> | Napuštanje opcije Read. Ako postoje nespremljeni signali, pojavljuje se **Exit to Sub-GHz Menu?** — `Exit` / `Stay` |

Ovisno o veličini primljenih podataka, popis može primiti do 128 signala.

## Postavke (Config) {#config}

Pritisnite <kbd>←</kbd> **Config** na zaslonu Read:

![Izbornik Read Config: Frequency, Modulation, Hopping i Bin RAW](/screens/subghz/read_config.png)

| Stavka | Vrijednosti | Čemu služi |
|---|---|---|
| `Frequency` | popis iz [Frekvencija](/hr/subghz/frequencies) | Fiksna frekvencija prijama. Prikazuje ` -----` dok je skakanje uključeno |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + prilagođeni predlošci | Predložak demodulacije. `AM650` odgovara većini daljinskih upravljača |
| `Hopping` / `Hopping RSSI` | `OFF`, `-90dBm` … `-40dBm` | Kruži kroz popis skakanja (315, 390, 430.5, 433.92, 434.42, 868.35 MHz). Vrijednost je razina RSSI-ja koja zaustavlja skakanje na frekvenciji |
| `Bin RAW` | `OFF` / `ON` | Također prikuplja nepoznate statične signale kao **BinRAW** (ponavljajući uzorak s obnovljenom brzinom prijenosa bitova). Držite tipku daljinskog upravljača malo dulje kako bi se prikupilo dovoljno podataka |
| `Ignore ReversRB2` | `OFF` / `ON` | Sakrij signale Revers RB-2(M) |
| `Ignore Alarms` | `OFF` / `ON` | Sakrij protokole alarma za bicikle/motocikle (Hollarm, GangQi) |
| `Ignore Sensors` | `OFF` / `ON` | Sakrij senzore i sličan promet: Magellan, Honeywell, Honeywell WDB i Legrand zvonca, Doorbell32, KeyFinder/KeyFinder2, Feron |
| `Ignore Princeton` | `OFF` / `ON` | Sakrij Princeton (PT2262 i klonove) — korisno tamo gdje jeftini daljinski upravljači zatrpavaju eter |
| `Ignore Nice Flor-S / Nice One` | `OFF` / `ON` | Sakrij Nice Flor-S / Nice One |
| `Delete old signals when memory is full` | `OFF` / `ON` | Kada se popis napuni, briše najstarije signale umjesto zaustavljanja. Brojač tada prikazuje `!` |
| `Sound` | `OFF` / `ON` | Reproducira sve što radio prima kroz zvučnik |
| `Reset to default` | — | Vraća na 433.92 MHz AM650, skakanje isključeno, svi filtri isključeni, Bin RAW isključen, TX snaga `Preset` |
| `Lock Keyboard` | — | Zaključava tipke tijekom skeniranja (u džepu). **Otključavanje: pritisnite <kbd>Back</kbd> tri puta** |

Sve postavke za Read spremaju se i vraćaju pri sljedećem otvaranju aplikacije.

::: tip Koju vrijednost za hopping odabrati
Kada je `Hopping` uključen, prijamnik ostaje na frekvenciji samo kada je signal iznad odabrane razine. `-90dBm` je
najosjetljivija vrijednost; povisite je ako šum neprestano zaustavlja skakanje. Za pouzdan prijam radije koristite **fiksnu frekvenciju**
pronađenu analizatorom — signali poslani tijekom prebacivanja frekvencije bivaju propušteni.
:::

## Slanje signala

Otvorite signal (s popisa Read ili iz `Saved → <datoteka> → Emulate`). Zaslon odašiljanja prikazuje podatke ključa,
frekvenciju, modulaciju i `R: Int` / `R: Ext` (koji će radio slati).

- **Pritisnite** <kbd>OK</kbd> (**Send**) — jedan pritisak odašilje potpun paket signala (obično s 1–3 ponavljanja radi
  pouzdanosti). **Držanje** tipke pritisnute neprekidno ponavlja odašiljanje dok je ne pustite (korisno na većoj
  udaljenosti ili uz jače smetnje). Kod protokola s promjenjivim kodom držanje tipke **ne** povećava brojač (pogledajte
  i [Načini brojača](/hr/subghz/counter-mode)) — signal se ponavlja s istim brojačem sve dok tipku ne pustite i ponovno
  pritisnete.
- <kbd>Back</kbd> — izlaz.

### Prilagođene tipke (Unleashed)

::: tip Unleashed
Za mnoge protokole tipke sa strelicama šalju **isti daljinski upravljač s drugim kodom tipke** — pa jedna spremljena datoteka djeluje kao
cijeli daljinski upravljač. Podržano, među ostalima, za: KeeLoq, Alutech AT-4N, Nice Flor-S, Somfy Telis/Keytis, Security+ 2.0,
CAME Atomo, FAAC SLH, BelKorn, Beninca ARC, Ditec GOL4, Jarolift, KingGates Stylo 4k, V2 Phoenix, Prastel, Roger,
Nord ICE, Princeton, Proteco, Dooya, Hay21, GangQi, Hollarm. Dok se strelica drži pritisnutom, kôd tipke koji se šalje prikazan je na
desnom rubu zaslona. Koja strelica znači koju tipku ovisi o protokolu — pogledajte
[Promjenjivi kodovi](/hr/subghz/rolling-codes) i [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog).
:::

## Spremljeni signali {#saved-signals}

`Main Menu → Sub-GHz → Saved` prikazuje datoteke u `/ext/subghz/`. Odaberite jednu i dobit ćete:

- `Emulate` — otvara zaslon za odašiljanje;
- `Rename`;
- `Delete`;
- `Signal Settings` — **samo u Debug načinu rada** (`Settings → System → Debug`): promjena opcija `Counter Mode`, `Edit Counter`,
  `Edit Button` datoteke s promjenjivim kodom. Pogledajte [Načini rada brojača](/hr/subghz/counter-mode).

RAW datoteke umjesto toga se otvaraju na zaslonu Read RAW — pogledajte [Read RAW](/hr/subghz/read-raw#playback).

Nazivi datoteka generiraju se automatski (datum-vrijeme), osim ako je uključena opcija `Protocol Names` u
[Postavkama radija](/hr/subghz/settings) — tada se naziv protokola stavlja ispred vremenske oznake.

## Statični naspram promjenjivih kodova

- **Statični kôd** (Princeton, CAME 12/24 bit, Nice Flo, Marantec, Roger, Gate TX…): svaki pritisak šalje isti kôd.
  Spremljena kopija radi zauvijek paralelno s originalom.
- **Promjenjivi (dinamički) kôd** (KeeLoq, Nice Flor-S, CAME Atomo, FAAC SLH, Somfy, Security+…): svaki pritisak nosi
  novu vrijednost brojača. Unleashed može spremiti i slati mnoge od njih, **ali slanje kopije desinkronizira izvorni
  daljinski upravljač**. Pročitajte [Promjenjivi kodovi](/hr/subghz/rolling-codes) i radije koristite [Add Manually](/hr/subghz/add-manually) za stvaranje
  *novog* daljinskog upravljača.

::: danger Privjesci za automobile
Nemojte eksperimentirati s ključem svog automobila. Ponovno slanje signala ključa automobila (Read ili Read RAW) može desinkronizirati ili blokirati izvorni
ključ, a ponovno uparivanje često zahtijeva servisne alate. Koristite Flipper samo s vlastitom opremom i za zakonito istraživanje.
:::

## Rješavanje problema

- **Ništa se ne pojavljuje** — pogrešna frekvencija ili modulacija. Upotrijebite analizator i isprobajte različite modulacije (`AM650`/`FM238`/`FM476`/`FM12K`).
  Provjerite ne skriva li protokol neki od filtara `Ignore …`.
- **Signal je primljen, ali nije dekodiran** — protokol je nepoznat: uključite `Bin RAW` (statični daljinski upravljači) ili snimite pomoću
  [Read RAW](/hr/subghz/read-raw). Isprobajte i aplikaciju [Remote Analyzer](/hr/subghz/remote-analyzer).
- **KeeLoq prikazuje proizvođača `Unknown`** — ključ proizvođača nije u bazi podataka ili daljinski upravljač treba Seed
  (BFT, Erreka, FAAC SLH). Pogledajte [KeeLoq](/hr/subghz/keeloq) i [Seed Capturer](/hr/subghz/seed-capturer).
- **Nema tipke `Send`** — protokol podržava samo dekodiranje (npr. iDo) ili je riječ o okviru signala Nice O-Code bez instalaterskog koda
  (upotrijebite aplikaciju [Nice O-Code](/hr/subghz/nice-o-code)).
- **Popis se puni šumom** — uključite odgovarajuće opcije `Ignore` ili `Delete old signals when memory is full`.

## Povezano

- [Read RAW](/hr/subghz/read-raw) · [Frequency Analyzer](/hr/subghz/frequency-analyzer) · [Podržani sustavi](/hr/subghz/supported-systems)
- [Promjenjivi kodovi](/hr/subghz/rolling-codes) · [Add Manually](/hr/subghz/add-manually) · [Postavke radija](/hr/subghz/settings) · [Formati datoteka](/hr/subghz/file-format)
