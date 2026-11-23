---
title: "Ručno dodavanje (Add Manually)"
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Add Manually

**Add Manually** stvara potpuno novi virtualni daljinski upravljač i sprema ga kao `.sub` datoteku. Ne treba vam izvorni
daljinski upravljač: Flipper generira nasumični serijski broj (i brojač, seed itd. gdje to protokol zahtijeva).
Novi daljinski upravljač zatim se može **registrirati u prijamniku** kao dodatni daljinski upravljač, na isti način kao što biste registrirali
rezervni daljinski upravljač kupljen u trgovini.

**Add Manually [Advanced]** radi isto, ali od vas traži da svaku vrijednost upišete u heksadekadskom obliku umjesto da ih automatski generira.

::: tip Unleashed
Tvornički firmver ima tek nekolicinu statičkih protokola u Add Manually. Unleashed navodi **više od 100 sustava**,
uključujući sustave s plivajućim kodom (KeeLoq proizvođači, FAAC SLH, BFT Mitto, Nice FloR-S / O-Code, CAME Atomo, Somfy,
Security+ 2.0, …), omogućuje odabir bilo kojeg od 15 frekvencijskih/modulacijskih pojaseva za svaki sustav te dodaje stavku **[Advanced]**.
:::

## Kada to koristiti

| Situacija | Koristite |
|---|---|
| Imate **statički** (fiksni kôd) daljinski upravljač i želite kopiju | [Read](/hr/subghz/read) i spremite ga — nema potrebe za Add Manually |
| Imate daljinski upravljač s **plivajućim kodom** i želite da Flipper radi *uz* njega | **Add Manually** → registrirajte novi daljinski upravljač u prijamniku ([kako](/hr/subghz/remote-prog)) |
| Trebate daljinski upravljač s poznatim vrijednostima (oporavljeni seed, instalaterski kôd, određeni serijski broj) | **Add Manually [Advanced]** |
| Izgubili ste izvorni statički daljinski upravljač, ali znate njegove DIP sklopke / kôd | **Add Manually [Advanced]** s ručno upisanim ključem |

Zašto umjesto toga ne klonirati daljinski upravljač s plivajućim kodom? Pogledajte [Plivajući kodovi](/hr/subghz/rolling-codes): klon i
izvorni upravljač natječu se oko brojača.

## Izrada daljinskog upravljača

1. `Main Menu → Sub-GHz → Add Manually`.
2. Pregledajte popis i odaberite sustav, npr. `BFT Mitto` ili `KL: DoorHan`. Stavke koje počinju s `KL:` su
   proizvođači sustava KeeLoq.

   ![Add Manually: abecedni popis sustava s odabranim KL: Allmatic](/screens/subghz/add_manually.png)

3. Otvara se **izbornik pojasa**, s nazivom sustava u zaglavlju. Pojasevi su označeni kao `frekvencija modulacija`, npr.
   `433.92 AM650`. Zadani pojas sustava je prvi, zatim ostali pojasevi koje taj sustav uobičajeno koristi, pa
   svi preostali pojasevi (za instalacije na neuobičajenoj frekvenciji). Pritisnite <kbd>OK</kbd> na pojasu koji vam treba.
4. Unesite naziv datoteke (naziv je predložen) i potvrdite.
5. Daljinski upravljač sprema se u `/ext/subghz/` i pojavljuje u `Sub-GHz → Saved`.

   ![Izbornik spremljenog signala: Emulate, Rename, Delete, Signal Settings](/screens/subghz/saved_menu.png)

6. Otvorite ga: `Sub-GHz → Saved → <your file> → Emulate`. Držite <kbd>OK</kbd> (`Send`) za odašiljanje; na protokolima s
   [prilagođenim gumbima](/hr/subghz/rolling-codes#custom-buttons) strelice šalju ostale gumbe.

   ![Zaslon odašiljanja spremljenog signala s R: Int i gumbom Send](/screens/subghz/emulate.png)


Ništa se ne odašilje dok ne otvorite datoteku i ne pritisnete tipku.

::: warning Zastarjeli nazivi
Starije upute (uključujući starije verzije `SubGHzRemoteProg.md`) navode stavke poput `BFT Mitto 433MHz` ili
`KL: DoorHan 315MHz`. Trenutačni firmver to dijeli u dva koraka: sustav (`BFT Mitto`) → pojas (`433.92 AM650`).
:::

### 15 pojaseva

Svi su ponuđeni za svaki sustav:

`433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`,
`868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`,
`430.50 AM650`.

## Add Manually [Advanced]

`Main Menu → Sub-GHz → Add Manually [Advanced]` → sustav → pojas, zatim niz zaslona za heksadekadski unos. Koje ćete zaslone
dobiti ovisi o obitelji protokola:

| Obitelj | Zasloni (redoslijedom) |
|---|---|
| Statički protokoli (Princeton, CAME, Nice Flo, …) | `Enter KEY in hex`; protokoli koji pohranjuju trajanje također pitaju `Enter TE in us` (i `Enter GT in TE`) |
| KeeLoq (`KL:` stavke, AN-Motors AT4) | `SERIAL` → `BUTTON` → `COUNTER` |
| KeeLoq sa seedom (BFT Mitto, Erreka) | `SERIAL` → `BUTTON` → `COUNTER` → `SEED` |
| `KL: FAAC FIX`, `KL: Monarch`, `KL:Phantom(Hiland)`, `KL: DEA Mio` | `SERIAL` → `BUTTON` → `COUNTER` → `DISC.` (hop diskriminator, sprema se u polje `Seed`) |
| FAAC SLH, Genius | `SERIAL` → `BUTTON` → `COUNTER` (32 bit) → `SEED` |
| CAME Atomo, V2 Phoenix | `SERIAL` → `COUNTER` |
| Alutech AT4N, Somfy Telis/Keytis, KingGates, Beninca ARC, Jarolift, Ditec GOL4, Prastel, BelKorn, Security+2.0 | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice FloR-S, Nice One | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice O-Code, Nice O-Code One | `SERIAL` → `BUTTON` → `COUNTER` → `IC` (instalaterski kôd) |
| Nice O-Code+Crt | `SERIAL` → `BUTTON` → `COUNTER` → `IC` → `CERT` (traži se i iz običnog Add Manually) |
| Security+1.0 | nema unosa, generira se izravno |

Vrijednosti su big-endian heksadekadski brojevi. `BUTTON` i `SERIAL` zajedno čine `Fix` koji vidite nakon [Read](/hr/subghz/read):
na sustavu KeeLoq gumb je **prva** heksadekadska znamenka polja `Fix` (serijski broj = `Fix` s tom znamenkom zamijenjenom s `0`), a na FAAC
SLH / Genius to je **zadnja** znamenka.

::: tip Unos bajtova
Unleashedov unos bajtova ima mini-uređivač polubajtova: pritišćite <kbd>↑</kbd> dok se ne pojavi.
:::

## Svaka stavka na popisu

Redoslijed i oznake točno kao u izborniku firmvera. "Zadano" je pojas naveden prvi; "Također" su
alternativni pojasevi sustava navedeni odmah nakon njega.

| Stavka u izborniku | Zadano | Također | Vrsta |
|---|---|---|---|
| `KL: Allmatic` | 433.92 AM650 | 868.35 AM650 | KeeLoq (Beninca ključ) |
| `Alutech AT4N` | 433.92 AM650 | | Dinamički (Alutech AT-4N) |
| `AN-Motors AT4` | 433.92 AM650 | | KeeLoq |
| `KL: Aprimatic` | 433.92 AM650 | | KeeLoq |
| `KL: ATA PTX4` | 433.92 AM650 | | KeeLoq |
| `BelKorn` | 433.92 AM650 | | Dinamički (obični brojač) |
| `KL: Beninca` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `Beninca ARC` | 433.92 AM650 | | Dinamički (AES-128) |
| `BETT` | 433.92 AM650 | | Statički |
| `BFT Mitto` | 433.92 AM650 | | KeeLoq + Seed |
| `CAME 12bit` | 433.92 AM650 | 868.35 AM650 | Statički |
| `CAME 24bit` | 433.92 AM650 | 868.35 AM650 | Statički |
| `CAME Atomo` | 433.92 AM650 | 868.35 AM650 | Dinamički |
| `KL: CAME Space` | 433.92 AM650 | | KeeLoq |
| `CAME TWEE` | 433.92 AM650 | | Statički (pseudodinamički) |
| `KL: Cardin S449` | **433.92 FM12K** | | KeeLoq |
| `KL: Centurion` | 433.92 AM650 | | KeeLoq |
| `KL: Clm.Mutancode` | 433.92 AM650 | | KeeLoq (Clemsa Mutancode) |
| `KL: Comunello` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `KL: DEA Mio` | 433.92 AM650 | | KeeLoq + diskriminator |
| `Ditec GOL4` | 433.92 AM650 | | Dinamički |
| `KL: DoorHan` | 433.92 AM650 | 315.00 AM650 | KeeLoq |
| `KL: Doormatic` | 433.92 AM650 | | KeeLoq |
| `KL: DTM Neo` | 433.92 AM650 | | KeeLoq |
| `KL: Elmes (PL)` | 433.92 AM650 | | KeeLoq |
| `KL: Elvox` | 433.92 AM650 | | KeeLoq |
| `Erreka` | 433.92 AM650 | 868.35 AM650 | KeeLoq + Seed |
| `KL: ET Blue` | 433.92 AM650 | | KeeLoq |
| `KL: ET Blue Mix` | 433.92 AM650 | | KeeLoq |
| `KL: FAAC FIX` | 433.92 AM650 | | KeeLoq + diskriminator |
| `KL: FAAC RC,XT` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `FAAC SLH` | 433.92 AM650 | 868.35 AM650 | FAAC SLH + Seed |
| `FAAC TM` | 433.92 AM650 | 868.35 AM650 | Statički (12 DIP sklopki) |
| `KL: Fadini` | 433.92 AM650 | | KeeLoq |
| `GangQi` | 433.92 AM650 | | Statički (alarm za bicikl) |
| `Gate TX` | 433.92 AM650 | | Statički |
| `Genius` | 433.92 AM650 | 868.35 AM650 | Okvir signala FAAC SLH, Genius ključ |
| `KL: Genius TX4RC` | 433.92 AM650 | | KeeLoq (Genius Bravo/Echo RC) |
| `KL: Gibidi` | 433.92 AM650 | | KeeLoq |
| `KL: GSN` | 433.92 AM650 | | KeeLoq |
| `KL: HCS101` | 433.92 AM650 | | Sličan KeeLoqu |
| `Hollarm` | 433.92 AM650 | | Statički (alarm za bicikl) |
| `KL: HomeGate` | 433.92 AM650 | | KeeLoq |
| `KL: Hor. EcoStar` | 433.92 AM650 | | KeeLoq (Hormann EcoStar) |
| `KL: IronLogic` | 433.92 AM650 | | KeeLoq |
| `KL: IronLogic SM` | 433.92 AM650 | | KeeLoq (IL-100 Smart) |
| `Jarolift` | 433.92 AM650 | | Dinamički (temeljen na KeeLoqu) |
| `KL: JCM Tech` | 433.92 AM650 | | KeeLoq |
| `KL: Jolly Mot.` | 433.92 AM650 | | KeeLoq (Jolly Motors) |
| `KL: KEY` | 433.92 AM650 | | KeeLoq |
| `KingGates Stylo4k` | 433.92 AM650 | | Dinamički (temeljen na KeeLoqu) |
| `Linear` | **300.00 AM650** | | Statički (10 bitova) |
| `Marantec` | 433.92 AM650 | 868.35 AM650 | Statički |
| `Marantec24` | **868.35 AM650** | | Statički |
| `KL: Mc Garcia` | 433.92 AM650 | | KeeLoq |
| `KL: Mhouse` | 433.92 AM650 | | KeeLoq |
| `KL: Monarch` | 433.92 AM650 | | KeeLoq + diskriminator |
| `KL: Motorline` | 433.92 AM650 | | KeeLoq |
| `Nice Flo 12bit` | 433.92 AM650 | | Statički |
| `Nice Flo 24bit` | 433.92 AM650 | | Statički |
| `Nice FloR-S` | 433.92 AM650 | | Dinamički |
| `Nice O-Code` | 433.92 AM650 | | Dinamički, instalaterski kôd |
| `Nice O-Code One` | 433.92 AM650 | | Dinamički, instalaterski kôd (okvir signala Nice One) |
| `Nice O-Code+Crt` | 433.92 AM650 | | Dinamički, instalaterski kôd + certifikat |
| `Nice One` | 433.92 AM650 | | Dinamički |
| `KL: Nice Smilo` | 433.92 AM650 | | KeeLoq |
| `Nord ICE` | 433.92 AM650 | | Statički |
| `KL: Normstahl` | 433.92 AM650 | | KeeLoq |
| `KL: Novoferm` | 433.92 AM650 | | KeeLoq |
| `KL:Phantom(Hiland)` | 433.92 AM650 | | KeeLoq + diskriminator |
| `Prastel` | 433.92 AM650 | | Dinamički (42 bita) |
| `Princeton` | 433.92 AM650 | 315.00 AM650 | Statički (24 bita) |
| `Proteco` | 433.92 AM650 | | Statički |
| `KL: Pujol` | 433.92 AM650 | | KeeLoq |
| `KL: Pujol Vario` | 433.92 AM650 | | KeeLoq |
| `Revers RB2` | 433.92 AM650 | | Statički |
| `Roger` | 433.92 AM650 | | Statički |
| `KL: Seav` | 433.92 AM650 | | KeeLoq |
| `Security+1.0` | 433.92 AM650 | 315.00, 390.00 AM650 | Dinamički |
| `Security+2.0` | 433.92 AM650 | 310.00, 315.00, 390.00 AM650 | Dinamički |
| `Somfy Keytis` | **433.42 AM650** | | Dinamički |
| `Somfy Telis` | **433.42 AM650** | | Dinamički (Somfy RTS) |
| `KL: Sommer` | **434.42 FM12K** | 868.80 FM12K, 434.42 FM476, 868.80 FM476 | KeeLoq |
| `KL: Stilmatic` | 433.92 AM650 | | KeeLoq |
| `KL: Superrollo` | 433.92 AM650 | | KeeLoq (HCS361) |
| `Telcoma EDGE` | 433.92 AM650 | | Statički |
| `V2 Phoenix` | 433.92 AM650 | | Dinamički |
| `KL: Verex` | 433.92 AM650 | | KeeLoq |
| `KL: Wisniowski` | 433.92 AM650 | | KeeLoq |
| `ZKTeco` | **430.50 AM650** | | Statički (Princeton, vidi [ZKTeco CMP200](/hr/subghz/zkteco-cmp200)) |

Za `KL: Sommer`, pojasevi FM476 generiraju daljinski upravljač s drugom varijantom modulacije tvrtke Sommer, tako da jedan redak izbornika
pokriva obje vrste Sommer daljinskih upravljača.

## Programiranje novog daljinskog upravljača u prijamnik

Novostvoreni daljinski upravljač s plivajućim kodom prijamniku je nepoznat. Registrirajte ga kao bilo koji rezervni daljinski upravljač — pomoću
gumba za učenje na prijamniku ili s već postojećeg ispravnog daljinskog upravljača. Skriveni/programski gumbi izvornog daljinskog upravljača
šalju se jednom tipkom sa strelicom na Flipperu. Postupci korak po korak po proizvođačima:
**[Korištenje Flippera kao novog daljinskog upravljača](/hr/subghz/remote-prog)**.

## Rješavanje problema

- **`Function requires an SD card with fresh databases.`** — baze ključeva proizvođača u
  `/ext/subghz/assets/` nedostaju ili su zastarjele. Ponovno instalirajte/ažurirajte firmver s umetnutom SD karticom.
- **Prijamnik uopće ne reagira** — pogrešan pojas. Prvo očitajte izvorni daljinski upravljač (`Sub-GHz → Read`) i odaberite
  istu frekvenciju i modulaciju. DoorHan postoji na 315 i 433,92 MHz; FAAC, Genius, Erreka na 433,92 i 868,35.
- **Prijamnik reagira, ali nikada ne pohrani daljinski upravljač** — propustili ste vremenski prozor za učenje ili iz
  nekog drugog razloga (npr. smetnje) prijamnik nije primio ispravan signal s Flippera.
- **Novi daljinski upravljač za Erreka/BFT je odbijen** — neke instalacije dijele jedan Seed na svim daljinskim upravljačima; oporavite ga
  ([Seed Capturer](/hr/subghz/seed-capturer)) i koristite Add Manually [Advanced]. Pogledajte [KeeLoq](/hr/subghz/keeloq).
- **Nice O-Code daljinski upravljač se ignorira** — tvornički prijamnik nema instalaterski kôd; u tom slučaju koristite `Nice One` ili `Nice FloR-S`.
  Za instalirani sustav pogledajte [Nice O-Code](/hr/subghz/nice-o-code).

::: warning
Daljinske upravljače registrirajte samo u prijamnicima koje posjedujete ili za koje imate ovlaštenje za upravljanje.
:::

## Povezano

- [Plivajući kodovi i prilagođeni gumbi](/hr/subghz/rolling-codes)
- [Programiranje novog daljinskog upravljača u prijamnik](/hr/subghz/remote-prog)
- [KeeLoq](/hr/subghz/keeloq) · [Podržani sustavi](/hr/subghz/supported-systems)
- [Načini brojača](/hr/subghz/counter-mode) · [Format .sub datoteke](/hr/subghz/file-format)
