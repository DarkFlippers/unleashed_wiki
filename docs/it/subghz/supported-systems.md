---
title: Sistemi supportati
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [unleashed-docs, unleashed-readme, unleashed-src]
---
# Sistemi supportati

Tutti i protocolli Sub-GHz che l'app `Sub-GHz` di **Unleashed** può decodificare, salvare e (in gran parte) inviare,
ricostruiti dal registro dei protocolli in `lib/subghz/protocols/` e dalla documentazione dei protocolli di Unleashed.
App come *Weather Station* o [Remote Analyzer](/it/subghz/remote-analyzer) hanno elenchi di protocolli aggiuntivi
propri.

::: tip Unleashed
Unleashed è un fork, quindi decodifica tutto quello che decodifica il firmware ufficiale: 38 dei 64 decoder di
protocollo dietro queste tabelle vengono da OFW, in gran parte scritti da Skorp. Sopra a quelli aggiunge BelKorn,
Beninca ARC, Ditec GOL4, Jarolift, Nice O-Code, Telcoma EDGE, Treadmill37, Freezer e altri, oltre 100 produttori
KeeLoq e la possibilità di **inviare** i protocolli a codice rolling, con
[tasti personalizzati](/it/subghz/rolling-codes#custom-buttons) e la creazione tramite
[Add Manually](/it/subghz/add-manually).
:::

## Come leggere le tabelle

- **433 MHz** di solito significa `433.92 MHz`, **868 MHz** significa `868.35 MHz`. Nessuna frequenza = non ancora nota.
- **Modulazione** è ciò da impostare in `Read → Config → Modulation`: `AM650`, `AM270`, `FM238`, `FM476`, `FM12K`.
  "FM" = prova tutti i preset FM; `FSK12K` nella documentazione dei costruttori = `FM12K` sul Flipper.
- **Statico** — codice fisso, una copia funziona accanto all'originale. **Dinamico** — codice rolling, vedi
  [Codici rolling](/it/subghz/rolling-codes).
- **Nome nel file** — il valore di `Protocol:` nel file `.sub` ([formato](/it/subghz/file-format)).
- **Add Manually** — la voce in `Sub-GHz → Add Manually`, se presente.

## Cancelli, garage, barriere, tapparelle

| Sistema | Frequenza | Mod. | Bit / tipo | Nome nel file | Add Manually | Note |
|---|---|---|---|---|---|---|
| Airforce | 433.92, 868 | AM650 | 18, statico | | | |
| Allstar Firefly 318ALD31K | 318 | AM650 | 18, statico | `Allstar Firefly` | | |
| Alutech AT-4N | 433.92 | AM650 | 72, dinamico | `Alutech AT-4N` | `Alutech AT4N`, `Alutech AT4L` | tasti personalizzati, [modalità contatore](/it/subghz/counter-mode) |
| AN-Motors (Alutech) AT4 | 433.92 | AM650 | 64, pseudo-dinamico | `KeeLoq` | `AN-Motors AT4` | basato su KeeLoq |
| Ansonic | 433 | FM | 12, statico | `Ansonic` | | |
| BelKorn (Korn, BelGate, Furniteh, Euro5…) | 433.92 | AM650 | 118, dinamico | `BelKorn` | `BelKorn` | non cifrato: seriale a 36 bit + contatore in chiaro; nessun campo produttore, ogni telecomando viene letto come BelKorn |
| Beninca ARC (TO.GO 2VA) | 433.92 | AM650 | 128, dinamico AES-128 | `Beninca ARC` | `Beninca ARC` | tasto `0` = tasto nascosto |
| BETT | 433.92 | AM650 | 18, statico | `BETT` | `BETT` | |
| BFT Mitto | 433.92 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `BFT Mitto` | i telecomandi più recenti derivano il seed dal seriale (decodificano in Read); quelli più vecchi richiedono il seed — modalità di programmazione oppure [Seed Capturer](/it/subghz/seed-capturer); tasto `0xF` = modalità di programmazione |
| CAME | 433.92, 868 | AM650 | 12/24, statico | `CAME` | `CAME 12bit`, `CAME 24bit` | |
| CAME Atomo (TOPD4REN, TOP44RBN, TOP42R, TOP44R) | 433.92, 868 | AM650 | 62, dinamico | `CAME Atomo` | `CAME Atomo` | tieni premuto Send ≥ 2 s |
| CAME TWEE (+ TOP44FGN, "New Fixed Code") | 433.92 | AM650 | 54, pseudo-dinamico | `CAME TWEE` | `CAME TWEE` | |
| Chamberlain Code | 315 | AM650 | 10, statico | `Cham_Code` | | |
| Clemsa | 433 | AM650 | 18, statico | `Clemsa` | | |
| Dickert MAHS | 433 | AM650 | 36, statico | `Dickert_MAHS` | | |
| Ditec GOL4 (BIXLG4, BIXLS2, BIXLP2) | 433.92 | AM650 | 54, dinamico | `Ditec GOL4` | `Ditec GOL4` | → = tasto `0` (nascosto) |
| Doitrand | 433 | AM650 | 37 | `Doitrand` | | indicato come dinamico nella documentazione, registrato come tipo statico nel firmware |
| Elplast / P-11B / 3BK / E.C.A | 433 | AM650 | 18, statico | `Elplast` | | |
| Erreka IRIS (IR02/IR04) | 433.92, 868.35 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `Erreka` | richiede il seed; `0xF` = modalità di programmazione, invia il seed in chiaro |
| FAAC SLH | 433.92, 868.35 | AM650 | 64, dinamico | `Faac SLH` | `FAAC SLH` | seed per tasto |
| FAAC TM (TM 433/868 DS) | 433.92, 868 | AM650 | 12, statico | `Faac TM` | `FAAC TM` | DIP switch; Te mantenuto dall'acquisizione |
| Gate TX | 433.92 | AM650 | 64, statico | `GateTX` | `Gate TX` | |
| Genius (KILO TX2/4 JLC, Amigo…) | 433.92, 868.35 | AM650 | 64, dinamico | `Faac SLH` | `Genius` | pacchetto FAAC SLH con chiave Genius, `Manufacture: Genius` |
| HCS101 | 433 | AM650 | 64, dinamico semplice | `KeeLoq` | `KL: HCS101` | simile a KeeLoq |
| Hormann | 868 | AM650 | 44, statico | `Hormann HSM` | | |
| iDo | 433 | AM650 | 48, dinamico | `iDo 117/111` | | **solo decodifica** (non può essere inviato) |
| Jarolift | 433.92 | AM650 | 72, dinamico | `Jarolift` | `Jarolift` | tapparelle, basato su KeeLoq |
| KingGates Stylo 4k | 433.92 | AM650 | 89, dinamico | `KingGates Stylo4k` | `KingGates Stylo4k` | basato su KeeLoq |
| Linear | 300 | AM650 | 10, statico | `Linear` | `Linear` | |
| Linear Delta3 | 315 | AM650 | 8, statico | `LinearDelta3` | | |
| Marantec | 433.92, 868 | AM650 | 49, statico | `Marantec` | `Marantec` | |
| Marantec24 | 868 | AM650 | 24, statico | `Marantec24` | `Marantec24` | |
| Mastercode | 433 | AM650 | 36, statico | `Mastercode` | | |
| Megacode | 315 | AM650 | 24, statico | `MegaCode` | | |
| Nero Radio | 434.42 | AM650 | 56, statico | `Nero Radio` | | solo modalità statica, la dinamica non è supportata |
| Nero Sketch | 433 | AM650 | 40, statico | `Nero Sketch` | | |
| Nice Flo | 433.92 | AM650 | 12/24, statico | `Nice FLO` | `Nice Flo 12bit`, `Nice Flo 24bit` | |
| Nice FloR-S | 433.92 | AM650 | 52, dinamico | `Nice FloR-S` | `Nice FloR-S` | modalità contatore |
| Nice One | 433.92 | AM650 | 72, dinamico | `Nice FloR-S` | `Nice One` | |
| Nice O-Code | 433.92 | AM650 | 52/72/112, dinamico | `Nice FloR-S` | `Nice O-Code`, `Nice O-Code One`, `Nice O-Code+Crt` | cifrato con un codice installatore a 16 bit, vedi [App Nice O-Code](/it/subghz/nice-o-code) |
| Nord ICE | 433.92 | AM650 | 33, statico | `Nord ICE` | `Nord ICE` | |
| Prastel | 433.92, 868 | AM650 | 25, statico | | | |
| Prastel | 433.92, 868 | AM650 | 42, dinamico | `Prastel` | `Prastel` | codifica di linea CAME, seriale mescolato + contatore |
| Proteco MOVER (TX3) | 433.92 | AM650 | 24, statico | `Proteco` | `Proteco` | |
| Revers RB2 (Реверс РБ-2(М)) | 433.92 | AM650 | 64, statico | `Revers_RB2` | `Revers RB2` | |
| Roger | 433.92 | AM650 | 28, statico | `Roger` | `Roger` | |
| Security+ 1.0 | 315, 433.92, 390 | AM650 | 42, dinamico | `Security+ 1.0` | `Security+1.0` | |
| Security+ 2.0 | 310, 315, 390, 868 | AM650 | 62, dinamico | `Security+ 2.0` | `Security+2.0` | |
| Security+ 2.0 Keypad | 315, 390, 868 | AM650 | 86, dinamico | `Security+ 2.0` | | PIN: [Security+ PIN](/it/subghz/secplus-pin) |
| Somfy Keytis (KeyGo 4 RTS, Keytis NS 2RTS) | 433.42, 868 | AM650 | 80, dinamico | `Somfy Keytis` | `Somfy Keytis` | |
| Superrollo GW60 | 433.92 | AM650 | 67, dinamico (KeeLoq HCS361, CRC) | `KeeLoq` | `KL: Superrollo` | tasti `0x3(0xA)` Up / `0x5(0xC)` Down / `0x7(0xE)` Stop |
| Telcoma/Cardin EDGE (EDGE2/4/20) | 433.92 | AM650 | 32, statico | `Telcoma/Cardin EDGE` | `Telcoma EDGE` | preambolo `0xFF` + seriale + canale one-hot, cancello = Ch 0 |
| V2 Phoenix (Phox) | 433.92 | AM650 | 52, dinamico | `Phoenix_V2` | `V2 Phoenix` | alcuni ricevitori hanno una modalità Static; modalità contatore |
| ZKTeco | 430.5 | AM650 | 24, statico | `Princeton` | `ZKTeco` | tasti `0x30` UP, `0x03` STOP, `0x0C` DOWN mappati sulle frecce — [ZKTeco CMP200](/it/subghz/zkteco-cmp200) |

## Sensori e domotica

| Sistema | Frequenza | Mod. | Bit / tipo | Nome nel file | Note |
|---|---|---|---|---|---|
| Dooya | 433, 315 | AM650 | 40, statico | `Dooya` | tende elettriche, tasti personalizzati |
| Feron | 433.92 | AM650 | 32, statico | `Feron` | telecomandi per LED RGB; filtro "Sensors" |
| Honeywell | 315 | AM650 | 64, statico | `Honeywell Sec` | sensori di allarme |
| Honeywell WDB | 433, 315 | AM650 | 48, statico | `Honeywell` | campanelli |
| Intertechno V3 | 433 | AM650 | 32, statico | `Intertechno_V3` | luci, prese |
| Jarolift | 433.92 | AM650 | 72, dinamico | `Jarolift` | tapparelle |
| Legrand | 433 | AM650 | 18, statico | `Legrand` | campanelli |
| Magellan | 433.92 | AM650 | 32, statico | `Magellan` | sensori, allarmi |
| Power Smart | 433 | AM650 | 64, statico | `Power Smart` | tende, tapparelle |
| Somfy Telis (RTS) | 433.42 | AM650 | 56, dinamico | `Somfy Telis` | Add Manually `Somfy Telis` → `433.42 AM650` |

## Antifurti

| Sistema | Frequenza | Mod. | Bit / tipo | Nome nel file | Note |
|---|---|---|---|---|---|
| GangQi | 433.92 | AM650 | 34, statico | `GangQi` | antifurti per bici; filtro "Alarms" |
| Hollarm | 433.92 | AM650 | 42, statico | `Hollarm` | antifurti per bici; filtro "Alarms" |

## Telecomandi generici / senza marchio

| Sistema | Frequenza | Mod. | Bit / tipo | Nome nel file | Note |
|---|---|---|---|---|---|
| Doorbell32 | 433.92 | AM650 | 32, statico | `Doorbell32` | PWM 1:3 in stile Princeton, guardia di 14·Te |
| Freezer | 433.92 | AM650 | 24, statico | `Freezer` | presente nel registro; non ancora nell'elenco upstream |
| Hay21 | 433.92 | AM650 | 21, dinamico | `Hay21` | |
| Holtek | 433/868/315 | AM650 | 40, statico | `Holtek` | |
| Holtek HT12X | 433/868/315 | AM650/FM | 12, statico | `Holtek_HT12X` | |
| KeyFinder | 433.92 | AM650 | 24, statico | `KeyFinder` | portachiavi cerca-chiavi |
| KeyFinder2 | 433.92 | AM650 | 11, statico | `KeyFinder2` | btn(3)+10011+btn(3), nessun seriale |
| Princeton (PT2262…) | 315, 433.92, qualsiasi | AM650 | 24, statico | `Princeton` | ha un filtro "Ignore Princeton" dedicato |
| SMC5326 | 315, 433.92, qualsiasi | AM650 | 25, statico | `SMC5326` | |
| Treadmill37 (QH-433) | 433.92 | AM650 | 37, statico | `Treadmill37` | |

## Non è un protocollo: RAW e BinRAW

- **RAW** (`Protocol: RAW`) — temporizzazioni grezze registrate con [Read RAW](/it/subghz/read-raw); riproduce
  qualsiasi cosa, non decodifica nulla.
- **BinRAW** (`Protocol: BinRAW`) — con `Read → Config → Bin RAW: ON`, un segnale statico sconosciuto ma ripetuto viene
  salvato come sequenza di bit ripulita con Te ricostruito. Può emulare quasi qualsiasi protocollo statico che il
  Flipper non conosce.

## Produttori KeeLoq

Tutti decodificati come `Protocol: KeeLoq` con `Manufacture:`; mostrati come `KL: <nome>`. Se non indicato
diversamente, l'apprendimento è "simple" con una parte di seriale a 10 bit nell'hop. Altro su KeeLoq:
[KeeLoq](/it/subghz/keeloq).

### Cancelli e garage

| Produttore | Freq / mod. | Apprendimento / note |
|---|---|---|
| AERF Collbaix, Hy dom, Medva, Motorgate, Otros, Sabutom, Temp, VDS | | apprendimento speciale, seriale a 10 bit nell'hop |
| Allmatic | 868, AM650 | nessun seriale nell'hop — magic XOR |
| Aprimatic | 433.92, AM650 | seriale a 12 bit nell'hop + 2 bit di "parità" |
| ATA PTX4 | | normal, 12 bit |
| Beninca | 433.92, 868, AM650 | nessun seriale nell'hop — magic XOR |
| CAME Space | 433.92, AM650 | simple, 12 bit |
| Cardin S449 | 433.92, **FM12K** | normal, 12 bit (originali) / 10 bit (cinesi) |
| Centurion | 433.92, AM650 | normal, valore fisso `0x1CE` invece del seriale |
| Clemsa Mutancode | | normal, 12 bit |
| Comunello | 433.92, 868, AM650 | normal |
| DEA Mio | 433.92, AM650 | simple, seriale modificato (`419` → `C19`) |
| DoorHan | 315, 433.92, AM650 | |
| Doormatic | | normal |
| DTM Neo | 433.92, AM650 | simple, 12 bit |
| Elmes Poland | 303, 433.92, AM650 | normal |
| Elvox | | normal |
| Erreka | 433.92, 868.35, AM650 | secure con seed, seriale a 8 bit |
| ET Blue, ET Blue Mix | | normal, 10 bit |
| FAAC FIX | 433.92, AM650 | normal, 10 bit; discriminatore a 12 bit conservato in `Seed`, come Phantom / Hiland |
| FAAC RC, XT | 433.92, 868, AM650 | normal, 12 bit |
| Fadini | | simple, 12 bit |
| Genius Bravo (ECHO, Bravo) | 433.92, AM650 | normal, 12 bit; `0xB` = programmazione |
| Gibidi | 433.92, AM650 | |
| GSN | 433.92, AM650 | normal, 12 bit |
| HomeGate | 433.92, AM650 | |
| Hormann EcoStar | 433.92, AM650 | normal |
| IronLogic IL-100, IL-100 Smart PPult | 433.92, AM650 | |
| JCM Tech | 433.92, AM650 | simple, 8 bit |
| JCM Tech Gen2 | | speciale; un byte di ingresso non è nel pacchetto — ricavato in forza bruta, mostrato come `Seed` |
| JCM1G (Antonio Meca, Baleato, Cas, Cubells, Cyacsa, DMIL, EMFA, Forsa, Gandara, Gibidi, Gibidi2, Hy dom, Hybrid, Norton, Nueva Castilla, Puertas Lorenzo, Pujol, Serviparking, Tech, Zibor) | | simple, 8 bit |
| Jolly Motors | 433.92, AM650 | |
| KEY | 433.92, AM650 | simple, valore fisso `0x2FF` |
| Mc Garcia | | simple, 10 bit |
| Mhouse | 433.92, AM650 | simple, 8 bit |
| Monarch | 433.92, AM650 | normal, fisso `0x100` oppure `0x280` (il Dorcas 22366CLN usa `0x280`) |
| Motorline | 433.92, AM650 | normal |
| Nice Smilo | 433.92, AM650 | simple, 8 bit |
| Normstahl | 433.92, AM650 | |
| Novoferm | 433.92, AM650 | |
| Phantom / Hiland | 433.92, AM650 | HCS300, normal, 10 bit; discriminatore a 12 bit conservato in `Seed` |
| Pujol (Vario 4…) | 433.92, AM650 | speciale, 8 bit |
| Pujol Vario (più vecchi) | 433.92, AM650 | simple, 8 bit |
| SEA | | simple |
| Seav | | normal, 12 bit |
| Sommer (TX03-868-4, Pearl, SOMloq) | 434.42, 868.80, FM12K o FM476 | normal |
| Stagnoli | | speciale |
| Steelmate | 433.92, AM650 | normal, 12 bit |
| Stilmatic (R-Tech) | 433.92, AM650 | normal, 12 bit |
| Telcoma | | apprendimento basato su tabella |
| Verex | | normal |
| Wisniowski | 433.92, AM650 | normal, 12 bit |
| Wisniowski 1 ByteReversed, Wisniowski 2 | | normal |

### Antifurti e altri

Alligator, Alligator S-275, APS-1100/APS-2550, Cenmax, Cenmax St-5, Cenmax St-7, Faraon, FFFF Normal, FFFF Simple,
Guard RF-311A (normal), Harpoon, KGB/Subaru (magic serial type 1), Leopard, Magic 1 / Magic 2 (magic serial type 2),
Magic 3 / Magic 4 (magic serial type 3), Merlin (XOR semplice, nessun seriale nell'hop), Miserere (normal), Mongoose
(normal), Pantera, Pantera CLK, Pantera XS/Jaguar, Partisan RX, Pecinin (simple, 12 bit), Reff, Rosh (simple,
12 bit), Rossi (simple, 12 bit), Sheriff, SL A2-A4, SL A6-A9/Tomahawk 9010, SL B6,B9 dop, Teco, Tomahawk TZ-9030,
Tomahawk Z,X 3-5, Zero Normal, Zero Simple, ZX-730-750-1055.

## Il mio telecomando non è in elenco

1. Trova la frequenza con il [Frequency Analyzer](/it/subghz/frequency-analyzer), poi prova
   [Read](/it/subghz/read) con tutte le modulazioni (`AM650`, `FM238`, `FM476`, `FM12K`), tenendo premuto il tasto
   per ≥ 2 s.
2. Prova `Bin RAW: ON` per i telecomandi statici.
3. Ancora nulla? Registra file con [Read RAW](/it/subghz/read-raw) (soglia RSSI `-----`, uno per modulazione; premi un
   tasto 5 volte tenendolo 1–2 s, poi 5 volte tenendolo 5 s), fotografa il telecomando (anche aperto) e apri una issue
   nel repository di Unleashed allegando i file.

## Pagine correlate

- [Add Manually](/it/subghz/add-manually) · [KeeLoq](/it/subghz/keeloq) · [Codici rolling](/it/subghz/rolling-codes)
- [Read](/it/subghz/read) · [Read RAW](/it/subghz/read-raw) · [Il Flipper come nuovo telecomando](/it/subghz/remote-prog)
