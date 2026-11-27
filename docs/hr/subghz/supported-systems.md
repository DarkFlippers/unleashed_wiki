---
title: Podržani sustavi
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [unleashed-docs, unleashed-readme, unleashed-src]
---
# Podržani sustavi

Svi Sub-GHz protokoli koje aplikacija `Sub-GHz` u **Unleashedu** može dekodirati, spremiti i (uglavnom) poslati, sastavljeni iz registra protokola u `lib/subghz/protocols/` i dokumentacije protokola Unleasheda. Aplikacije kao što su *Weather Station* ili [Remote Analyzer](/hr/subghz/remote-analyzer) imaju vlastite dodatne popise protokola.

::: tip Unleashed
Unleashed je fork, pa dekodira sve što i službeni firmver: 38 od 64 dekodera protokola iza ovih tablica potječe iz OFW-a, većinom kao rad Skorpa. Na to dodaje BelKorn, Beninca ARC, Ditec GOL4, Jarolift, Nice O-Code, Telcoma EDGE, Treadmill37, Freezer i druge, više od 100 proizvođača KeeLoqa te mogućnost **slanja** protokola s promjenjivim kodom, uz [prilagođene tipke](/hr/subghz/rolling-codes#custom-buttons) i izradu putem [Add Manually](/hr/subghz/add-manually).
:::

## Kako čitati tablice

- **433 MHz** obično znači `433.92 MHz`, **868 MHz** znači `868.35 MHz`. Bez frekvencije = još nije poznato.
- **Modulacija** je ono što treba postaviti u `Read → Config → Modulation`: `AM650`, `AM270`, `FM238`, `FM476`, `FM12K`. "FM" = isprobajte svaki FM predložak; `FSK12K` u dokumentaciji proizvođača = `FM12K` na Flipperu.
- **Statični** — fiksni kod, kopija radi usporedno s izvornikom. **Dinamični** — promjenjivi kod (rolling code), pogledajte [Promjenjivi kodovi](/hr/subghz/rolling-codes).
- **Naziv u datoteci** — vrijednost polja `Protocol:` u `.sub` datoteci ([format](/hr/subghz/file-format)).
- **Add Manually** — unos u `Sub-GHz → Add Manually`, ako postoji.

## Vrata, garaže, rampe, rolete

| Sustav | Frekvencija | Mod. | Bitovi / vrsta | Naziv u datoteci | Add Manually | Napomene |
|---|---|---|---|---|---|---|
| Airforce | 433.92, 868 | AM650 | 18, statični | | | |
| Allstar Firefly 318ALD31K | 318 | AM650 | 18, statični | `Allstar Firefly` | | |
| Alutech AT-4N | 433.92 | AM650 | 72, dinamični | `Alutech AT-4N` | `Alutech AT4N`, `Alutech AT4L` | prilagođene tipke, [načini brojača](/hr/subghz/counter-mode) |
| AN-Motors (Alutech) AT4 | 433.92 | AM650 | 64, pseudo-dinamični | `KeeLoq` | `AN-Motors AT4` | temeljen na KeeLoqu |
| Ansonic | 433 | FM | 12, statični | `Ansonic` | | |
| BelKorn (Korn, BelGate, Furniteh, Euro5…) | 433.92 | AM650 | 118, dinamični | `BelKorn` | `BelKorn` | nije šifriran: 36-bitni serijski broj + brojač u čistom tekstu; bez polja proizvođača, svaki se daljinski upravljač čita kao BelKorn |
| Beninca ARC (TO.GO 2VA) | 433.92 | AM650 | 128, dinamični AES-128 | `Beninca ARC` | `Beninca ARC` | tipka `0` = skrivena tipka |
| BETT | 433.92 | AM650 | 18, statični | `BETT` | `BETT` | |
| BFT Mitto | 433.92 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `BFT Mitto` | noviji daljinski upravljači izvode seed iz serijskog broja (dekodira se u Read); starijima treba seed — način programiranja ili [Seed Capturer](/hr/subghz/seed-capturer); tipka `0xF` = način programiranja |
| CAME | 433.92, 868 | AM650 | 12/24, statični | `CAME` | `CAME 12bit`, `CAME 24bit` | |
| CAME Atomo (TOPD4REN, TOP44RBN, TOP42R, TOP44R) | 433.92, 868 | AM650 | 62, dinamični | `CAME Atomo` | `CAME Atomo` | držite Send ≥ 2 s |
| CAME TWEE (+ TOP44FGN, "New Fixed Code") | 433.92 | AM650 | 54, pseudo-dinamični | `CAME TWEE` | `CAME TWEE` | |
| Chamberlain Code | 315 | AM650 | 10, statični | `Cham_Code` | | |
| Clemsa | 433 | AM650 | 18, statični | `Clemsa` | | |
| Dickert MAHS | 433 | AM650 | 36, statični | `Dickert_MAHS` | | |
| Ditec GOL4 (BIXLG4, BIXLS2, BIXLP2) | 433.92 | AM650 | 54, dinamični | `Ditec GOL4` | `Ditec GOL4` | → = tipka `0` (skrivena) |
| Doitrand | 433 | AM650 | 37 | `Doitrand` | | naveden kao dinamični u dokumentaciji, registriran kao statični tip u firmveru |
| Elplast / P-11B / 3BK / E.C.A | 433 | AM650 | 18, statični | `Elplast` | | |
| Erreka IRIS (IR02/IR04) | 433.92, 868.35 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `Erreka` | potreban seed; `0xF` = način programiranja, šalje seed nešifriran |
| FAAC SLH | 433.92, 868.35 | AM650 | 64, dinamični | `Faac SLH` | `FAAC SLH` | seed po tipki |
| FAAC TM (TM 433/868 DS) | 433.92, 868 | AM650 | 12, statični | `Faac TM` | `FAAC TM` | DIP sklopke; Te preuzet iz snimke |
| Gate TX | 433.92 | AM650 | 64, statični | `GateTX` | `Gate TX` | |
| Genius (KILO TX2/4 JLC, Amigo…) | 433.92, 868.35 | AM650 | 64, dinamični | `Faac SLH` | `Genius` | okvir signala FAAC SLH s ključem Genius, `Manufacture: Genius` |
| HCS101 | 433 | AM650 | 64, jednostavni dinamični | `KeeLoq` | `KL: HCS101` | sličan KeeLoqu |
| Hormann | 868 | AM650 | 44, statični | `Hormann HSM` | | |
| iDo | 433 | AM650 | 48, dinamični | `iDo 117/111` | | **samo dekodiranje** (ne može se slati) |
| Jarolift | 433.92 | AM650 | 72, dinamični | `Jarolift` | `Jarolift` | rolete, temeljen na KeeLoqu |
| KingGates Stylo 4k | 433.92 | AM650 | 89, dinamični | `KingGates Stylo4k` | `KingGates Stylo4k` | temeljen na KeeLoqu |
| Linear | 300 | AM650 | 10, statični | `Linear` | `Linear` | |
| Linear Delta3 | 315 | AM650 | 8, statični | `LinearDelta3` | | |
| Marantec | 433.92, 868 | AM650 | 49, statični | `Marantec` | `Marantec` | |
| Marantec24 | 868 | AM650 | 24, statični | `Marantec24` | `Marantec24` | |
| Mastercode | 433 | AM650 | 36, statični | `Mastercode` | | |
| Megacode | 315 | AM650 | 24, statični | `MegaCode` | | |
| Nero Radio | 434.42 | AM650 | 56, statični | `Nero Radio` | | samo statični način, dinamični nije podržan |
| Nero Sketch | 433 | AM650 | 40, statični | `Nero Sketch` | | |
| Nice Flo | 433.92 | AM650 | 12/24, statični | `Nice FLO` | `Nice Flo 12bit`, `Nice Flo 24bit` | |
| Nice FloR-S | 433.92 | AM650 | 52, dinamični | `Nice FloR-S` | `Nice FloR-S` | načini brojača |
| Nice One | 433.92 | AM650 | 72, dinamični | `Nice FloR-S` | `Nice One` | |
| Nice O-Code | 433.92 | AM650 | 52/72/112, dinamični | `Nice FloR-S` | `Nice O-Code`, `Nice O-Code One`, `Nice O-Code+Crt` | koristi 16-bitni instalaterski kod, pogledajte [aplikaciju Nice O-Code](/hr/subghz/nice-o-code) |
| Nord ICE | 433.92 | AM650 | 33, statični | `Nord ICE` | `Nord ICE` | |
| Prastel | 433.92, 868 | AM650 | 25, statični | | | |
| Prastel | 433.92, 868 | AM650 | 42, dinamični | `Prastel` | `Prastel` | CAME linijsko kodiranje, ispremiješan serijski broj + brojač |
| Proteco MOVER (TX3) | 433.92 | AM650 | 24, statični | `Proteco` | `Proteco` | |
| Revers RB2 (Реверс РБ-2(М)) | 433.92 | AM650 | 64, statični | `Revers_RB2` | `Revers RB2` | |
| Roger | 433.92 | AM650 | 28, statični | `Roger` | `Roger` | |
| Security+ 1.0 | 315, 433.92, 390 | AM650 | 42, dinamični | `Security+ 1.0` | `Security+1.0` | |
| Security+ 2.0 | 310, 315, 390, 868 | AM650 | 62, dinamični | `Security+ 2.0` | `Security+2.0` | |
| Security+ 2.0 Keypad | 315, 390, 868 | AM650 | 86, dinamični | `Security+ 2.0` | | PIN: [Security+ PIN](/hr/subghz/secplus-pin) |
| Somfy Keytis (KeyGo 4 RTS, Keytis NS 2RTS) | 433.42, 868 | AM650 | 80, dinamični | `Somfy Keytis` | `Somfy Keytis` | |
| Superrollo GW60 | 433.92 | AM650 | 67, dinamični (KeeLoq HCS361, CRC) | `KeeLoq` | `KL: Superrollo` | tipke `0x3(0xA)` Up / `0x5(0xC)` Down / `0x7(0xE)` Stop |
| Telcoma/Cardin EDGE (EDGE2/4/20) | 433.92 | AM650 | 32, statični | `Telcoma/Cardin EDGE` | `Telcoma EDGE` | preambula `0xFF` + serijski broj + one-hot kanal, vrata = Ch 0 |
| V2 Phoenix (Phox) | 433.92 | AM650 | 52, dinamični | `Phoenix_V2` | `V2 Phoenix` | neki prijamnici imaju statični način; načini brojača |
| ZKTeco | 430.5 | AM650 | 24, statični | `Princeton` | `ZKTeco` | tipke `0x30` UP, `0x03` STOP, `0x0C` DOWN mapirane na strelice — [ZKTeco CMP200](/hr/subghz/zkteco-cmp200) |

## Senzori i pametni dom

| Sustav | Frekvencija | Mod. | Bitovi / vrsta | Naziv u datoteci | Napomene |
|---|---|---|---|---|---|
| Dooya | 433, 315 | AM650 | 40, statični | `Dooya` | električne rolete, prilagođene tipke |
| Feron | 433.92 | AM650 | 32, statični | `Feron` | daljinski upravljači za RGB LED rasvjetu; filtar zanemarivanja "Sensors" |
| Honeywell | 315 | AM650 | 64, statični | `Honeywell Sec` | alarmni senzori |
| Honeywell WDB | 433, 315 | AM650 | 48, statični | `Honeywell` | zvonca za vrata |
| Intertechno V3 | 433 | AM650 | 32, statični | `Intertechno_V3` | rasvjeta, utičnice |
| Jarolift | 433.92 | AM650 | 72, dinamični | `Jarolift` | rolete |
| Legrand | 433 | AM650 | 18, statični | `Legrand` | zvonca za vrata |
| Magellan | 433.92 | AM650 | 32, statični | `Magellan` | senzori, alarmi |
| Power Smart | 433 | AM650 | 64, statični | `Power Smart` | sjenila, rolete |
| Somfy Telis (RTS) | 433.42 | AM650 | 56, dinamični | `Somfy Telis` | Add Manually `Somfy Telis` → `433.42 AM650` |

## Alarmi

| Sustav | Frekvencija | Mod. | Bitovi / vrsta | Naziv u datoteci | Napomene |
|---|---|---|---|---|---|
| GangQi | 433.92 | AM650 | 34, statični | `GangQi` | alarmi za bicikle; filtar zanemarivanja "Alarms" |
| Hollarm | 433.92 | AM650 | 42, statični | `Hollarm` | alarmi za bicikle; filtar zanemarivanja "Alarms" |

## Generički / nebrendirani daljinski upravljači

| Sustav | Frekvencija | Mod. | Bitovi / vrsta | Naziv u datoteci | Napomene |
|---|---|---|---|---|---|
| Doorbell32 | 433.92 | AM650 | 32, statični | `Doorbell32` | 1:3 PWM u stilu Princetona, zaštitni razmak 14·Te |
| Freezer | 433.92 | AM650 | 24, statični | `Freezer` | u registru; još nije na popisu izvornog projekta |
| Hay21 | 433.92 | AM650 | 21, dinamični | `Hay21` | |
| Holtek | 433/868/315 | AM650 | 40, statični | `Holtek` | |
| Holtek HT12X | 433/868/315 | AM650/FM | 12, statični | `Holtek_HT12X` | |
| KeyFinder | 433.92 | AM650 | 24, statični | `KeyFinder` | privjesci za traženje ključeva |
| KeyFinder2 | 433.92 | AM650 | 11, statični | `KeyFinder2` | btn(3)+10011+btn(3), bez serijskog broja |
| Princeton (PT2262…) | 315, 433.92, bilo koja | AM650 | 24, statični | `Princeton` | vlastiti filtar "Ignore Princeton" |
| SMC5326 | 315, 433.92, bilo koja | AM650 | 25, statični | `SMC5326` | |
| Treadmill37 (QH-433) | 433.92 | AM650 | 37, statični | `Treadmill37` | |

## Nisu protokol: RAW i BinRAW

- **RAW** (`Protocol: RAW`) — sirova vremena trajanja impulsa snimljena pomoću [Read RAW](/hr/subghz/read-raw); ponovno šalje sve, ne dekodira ništa.
- **BinRAW** (`Protocol: BinRAW`) — uz `Read → Config → Bin RAW: ON`, nepoznati ali ponavljajući statični signal sprema se kao pročišćeni niz bitova s izračunatim Te. Može emulirati gotovo svaki statični protokol koji Flipper ne poznaje.

## Proizvođači KeeLoqa

Svi se dekodiraju kao `Protocol: KeeLoq` s poljem `Manufacture:`; prikazuje se kao `KL: <name>`. Ako nije drukčije navedeno, učenje je "simple" (jednostavno) s 10-bitnim dijelom serijskog broja u promjenjivom dijelu (hop). Više o KeeLoqu: [KeeLoq](/hr/subghz/keeloq).

### Vrata i garaže

| Proizvođač | Frekv. / mod. | Učenje / napomene |
|---|---|---|
| AERF Collbaix, Hy dom, Medva, Motorgate, Otros, Sabutom, Temp, VDS | | posebno učenje, 10-bitni serijski broj u hopu |
| Allmatic | 868, AM650 | bez serijskog broja u hopu — čarobni XOR |
| Aprimatic | 433.92, AM650 | 12-bitni serijski broj u hopu + 2-bitni "paritet" |
| ATA PTX4 | | normal, 12-bitni |
| Beninca | 433.92, 868, AM650 | bez serijskog broja u hopu — čarobni XOR |
| CAME Space | 433.92, AM650 | simple, 12-bitni |
| Cardin S449 | 433.92, **FM12K** | normal, 12-bitni (izvornici) / 10-bitni (kineski) |
| Centurion | 433.92, AM650 | normal, fiksna vrijednost `0x1CE` umjesto serijskog broja |
| Clemsa Mutancode | | normal, 12-bitni |
| Comunello | 433.92, 868, AM650 | normal |
| DEA Mio | 433.92, AM650 | simple, izmijenjeni serijski broj (`419` → `C19`) |
| DoorHan | 315, 433.92, AM650 | |
| Doormatic | | normal |
| DTM Neo | 433.92, AM650 | simple, 12-bitni |
| Elmes Poland | 303, 433.92, AM650 | normal |
| Elvox | | normal |
| Erreka | 433.92, 868.35, AM650 | sigurno sa seedom, 8-bitni serijski broj |
| ET Blue, ET Blue Mix | | normal, 10-bitni |
| FAAC FIX | 433.92, AM650 | normal, 10-bitni; 12-bitni diskriminator čuva se u `Seed`, jednako kao Phantom / Hiland |
| FAAC RC, XT | 433.92, 868, AM650 | normal, 12-bitni |
| Fadini | | simple, 12-bitni |
| Genius Bravo (ECHO, Bravo) | 433.92, AM650 | normal, 12-bitni; `0xB` = programiranje |
| Gibidi | 433.92, AM650 | |
| GSN | 433.92, AM650 | normal, 12-bitni |
| HomeGate | 433.92, AM650 | |
| Hormann EcoStar | 433.92, AM650 | normal |
| IronLogic IL-100, IL-100 Smart PPult | 433.92, AM650 | |
| JCM Tech | 433.92, AM650 | simple, 8-bitni |
| JCM Tech Gen2 | | posebno; jedan ulazni bajt nije u paketu — otkriva se iscrpnom pretragom (brute-force), prikazuje se kao `Seed` |
| JCM1G (Antonio Meca, Baleato, Cas, Cubells, Cyacsa, DMIL, EMFA, Forsa, Gandara, Gibidi, Gibidi2, Hy dom, Hybrid, Norton, Nueva Castilla, Puertas Lorenzo, Pujol, Serviparking, Tech, Zibor) | | simple, 8-bitni |
| Jolly Motors | 433.92, AM650 | |
| KEY | 433.92, AM650 | simple, fiksna vrijednost `0x2FF` |
| Mc Garcia | | simple, 10-bitni |
| Mhouse | 433.92, AM650 | simple, 8-bitni |
| Monarch | 433.92, AM650 | normal, fiksno `0x100` ili `0x280` (Dorcas 22366CLN koristi `0x280`) |
| Motorline | 433.92, AM650 | normal |
| Nice Smilo | 433.92, AM650 | simple, 8-bitni |
| Normstahl | 433.92, AM650 | |
| Novoferm | 433.92, AM650 | |
| Phantom / Hiland | 433.92, AM650 | HCS300, normal, 10-bitni; 12-bitni diskriminator čuva se u `Seed` |
| Pujol (Vario 4…) | 433.92, AM650 | posebno, 8-bitni |
| Pujol Vario (stariji) | 433.92, AM650 | simple, 8-bitni |
| SEA | | simple |
| Seav | | normal, 12-bitni |
| Sommer (TX03-868-4, Pearl, SOMloq) | 434.42, 868.80, FM12K ili FM476 | normal |
| Stagnoli | | posebno |
| Steelmate | 433.92, AM650 | normal, 12-bitni |
| Stilmatic (R-Tech) | 433.92, AM650 | normal, 12-bitni |
| Telcoma | | učenje pomoću tablice |
| Verex | | normal |
| Wisniowski | 433.92, AM650 | normal, 12-bitni |
| Wisniowski 1 ByteReversed, Wisniowski 2 | | normal |

### Alarmi i ostalo

Alligator, Alligator S-275, APS-1100/APS-2550, Cenmax, Cenmax St-5, Cenmax St-7, Faraon, FFFF Normal, FFFF Simple, Guard RF-311A (normal), Harpoon, KGB/Subaru (magic serial type 1), Leopard, Magic 1 / Magic 2 (magic serial type 2), Magic 3 / Magic 4 (magic serial type 3), Merlin (simple XOR, bez serijskog broja u hopu), Miserere (normal), Mongoose (normal), Pantera, Pantera CLK, Pantera XS/Jaguar, Partisan RX, Pecinin (simple, 12-bitni), Reff, Rosh (simple, 12-bitni), Rossi (simple, 12-bitni), Sheriff, SL A2-A4, SL A6-A9/Tomahawk 9010, SL B6,B9 dop, Teco, Tomahawk TZ-9030, Tomahawk Z,X 3-5, Zero Normal, Zero Simple, ZX-730-750-1055.

## Moj daljinski upravljač nije na popisu

1. Pronađite frekvenciju pomoću alata [Frequency Analyzer](/hr/subghz/frequency-analyzer), zatim isprobajte [Read](/hr/subghz/read) sa svakom modulacijom (`AM650`, `FM238`, `FM476`, `FM12K`), držeći tipku ≥ 2 s.
2. Isprobajte `Bin RAW: ON` za statične daljinske upravljače.
3. I dalje ništa? Snimite [Read RAW](/hr/subghz/read-raw) datoteke (prag RSSI `-----`, po jednu za svaku modulaciju; pritisnite jednu tipku 5× držeći 1–2 s, zatim 5× držeći 5 s), fotografirajte daljinski upravljač (i otvorenog) te otvorite issue u repozitoriju Unleasheda s tim datotekama.

## Povezano

- [Add Manually](/hr/subghz/add-manually) · [KeeLoq](/hr/subghz/keeloq) · [Promjenjivi kodovi](/hr/subghz/rolling-codes)
- [Read](/hr/subghz/read) · [Read RAW](/hr/subghz/read-raw) · [Programiranje daljinskog upravljača](/hr/subghz/remote-prog)
