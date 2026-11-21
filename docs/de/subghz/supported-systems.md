---
title: Unterstützte Systeme
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [unleashed-docs, unleashed-readme, unleashed-src]
---
# Unterstützte Systeme

Alle Sub-GHz-Protokolle, die die `Sub-GHz`-App von **Unleashed** dekodieren, speichern und (meist) senden kann,
zusammengestellt aus der Protokollregistrierung in `lib/subghz/protocols/` und der Protokolldokumentation von
Unleashed. Apps wie *Weather Station* oder [Remote Analyzer](/de/subghz/remote-analyzer) haben eigene,
zusätzliche Protokolllisten.

::: tip Unleashed
Unleashed ist ein Fork und dekodiert daher alles, was die offizielle Firmware dekodiert: 38 der 64 Protokoll-Dekoder
hinter diesen Tabellen stammen aus OFW, die meisten davon von Skorp. Darauf aufbauend kommen BelKorn, Beninca ARC,
Ditec GOL4, Jarolift, Nice O-Code, Telcoma EDGE, Treadmill37, Freezer und weitere hinzu, über 100
KeeLoq-Hersteller und die Fähigkeit, Rolling-Code-Protokolle zu **senden**, mit
[eigenen Tasten](/de/subghz/rolling-codes#custom-buttons) und dem Anlegen über [Add Manually](/de/subghz/add-manually).
:::

## So liest man die Tabellen

- **433 MHz** bedeutet meist `433.92 MHz`, **868 MHz** bedeutet `868.35 MHz`. Keine Frequenz = noch nicht bekannt.
- **Modulation** ist das, was du in `Read → Config → Modulation` setzt: `AM650`, `AM270`, `FM238`, `FM476`,
  `FM12K`. „FM" = jedes FM-Preset probieren; `FSK12K` in Herstellerunterlagen = `FM12K` auf dem Flipper.
- **Statisch** — fester Code, eine Kopie funktioniert neben dem Original. **Dynamisch** — Rolling Code, siehe
  [Rolling Codes](/de/subghz/rolling-codes).
- **Dateiname** — der Wert von `Protocol:` in der `.sub`-Datei ([Format](/de/subghz/file-format)).
- **Add Manually** — der Eintrag in `Sub-GHz → Add Manually`, sofern vorhanden.

## Tore, Garagen, Schranken, Rollläden

| System | Frequenz | Mod. | Bits / Typ | Dateiname | Add Manually | Hinweise |
|---|---|---|---|---|---|---|
| Airforce | 433.92, 868 | AM650 | 18, statisch | | | |
| Allstar Firefly 318ALD31K | 318 | AM650 | 18, statisch | `Allstar Firefly` | | |
| Alutech AT-4N | 433.92 | AM650 | 72, dynamisch | `Alutech AT-4N` | `Alutech AT4N` | eigene Tasten, [Zählermodi](/de/subghz/counter-mode) |
| AN-Motors (Alutech) AT4 | 433.92 | AM650 | 64, pseudodynamisch | `KeeLoq` | `AN-Motors AT4` | auf KeeLoq-Basis |
| Ansonic | 433 | FM | 12, statisch | `Ansonic` | | |
| BelKorn (Korn, BelGate, Furniteh …) | 433.92 | AM650 | 118, dynamisch | `BelKorn` | `BelKorn` | nicht verschlüsselt: 36-Bit-Seriennummer + Zähler im Klartext; kein Herstellerfeld, jede Fernbedienung wird als BelKorn gelesen |
| Beninca ARC (TO.GO 2VA) | 433.92 | AM650 | 128, dynamisch AES-128 | `Beninca ARC` | `Beninca ARC` | Taste `0` = versteckte Taste |
| BETT | 433.92 | AM650 | 18, statisch | `BETT` | `BETT` | |
| BFT Mitto | 433.92 | AM650 | 64, KeeLoq + Seed | `KeeLoq` | `BFT Mitto` | neuere Fernbedienungen leiten den Seed aus der Seriennummer ab (werden in Read dekodiert); ältere brauchen den Seed — Programmiermodus oder [Seed Capturer](/de/subghz/seed-capturer); Taste `0xF` = Programmiermodus |
| CAME | 433.92, 868 | AM650 | 12/24, statisch | `CAME` | `CAME 12bit`, `CAME 24bit` | |
| CAME Atomo (TOPD4REN, TOP44RBN, TOP42R, TOP44R) | 433.92, 868 | AM650 | 62, dynamisch | `CAME Atomo` | `CAME Atomo` | Send ≥ 2 s halten |
| CAME TWEE (+ TOP44FGN, „New Fixed Code") | 433.92 | AM650 | 54, pseudodynamisch | `CAME TWEE` | `CAME TWEE` | |
| Chamberlain Code | 315 | AM650 | 10, statisch | `Cham_Code` | | |
| Clemsa | 433 | AM650 | 18, statisch | `Clemsa` | | |
| Dickert MAHS | 433 | AM650 | 36, statisch | `Dickert_MAHS` | | |
| Ditec GOL4 (BIXLG4, BIXLS2, BIXLP2) | 433.92 | AM650 | 54, dynamisch | `Ditec GOL4` | `Ditec GOL4` | → = Taste `0` (versteckt) |
| Doitrand | 433 | AM650 | 37 | `Doitrand` | | in der Dokumentation als dynamisch geführt, in der Firmware als statischer Typ registriert |
| Elplast / P-11B / 3BK / E.C.A | 433 | AM650 | 18, statisch | `Elplast` | | |
| Erreka IRIS (IR02/IR04) | 433.92, 868.35 | AM650 | 64, KeeLoq + Seed | `KeeLoq` | `Erreka` | Seed erforderlich; `0xF` = Programmiermodus, sendet den Seed im Klartext |
| FAAC SLH | 433.92, 868.35 | AM650 | 64, dynamisch | `Faac SLH` | `FAAC SLH` | Seed pro Taste |
| FAAC TM (TM 433/868 DS) | 433.92, 868 | AM650 | 12, statisch | `Faac TM` | `FAAC TM` | DIP-Schalter; Te aus der Aufnahme übernommen |
| Gate TX | 433.92 | AM650 | 64, statisch | `GateTX` | `Gate TX` | |
| Genius (KILO TX2/4 JLC, Amigo …) | 433.92, 868.35 | AM650 | 64, dynamisch | `Faac SLH` | `Genius` | FAAC-SLH-Paket mit Genius-Schlüssel, `Manufacture: Genius` |
| HCS101 | 433 | AM650 | 64, einfach dynamisch | `KeeLoq` | `KL: HCS101` | KeeLoq-artig |
| Hormann | 868 | AM650 | 44, statisch | `Hormann HSM` | | |
| iDo | 433 | AM650 | 48, dynamisch | `iDo 117/111` | | **nur Dekodierung** (kann nicht gesendet werden) |
| Jarolift | 433.92 | AM650 | 72, dynamisch | `Jarolift` | `Jarolift` | Rollläden, auf KeeLoq-Basis |
| KingGates Stylo 4k | 433.92 | AM650 | 89, dynamisch | `KingGates Stylo4k` | `KingGates Stylo4k` | auf KeeLoq-Basis |
| Linear | 300 | AM650 | 10, statisch | `Linear` | `Linear` | |
| Linear Delta3 | 315 | AM650 | 8, statisch | `LinearDelta3` | | |
| Marantec | 433.92, 868 | AM650 | 49, statisch | `Marantec` | `Marantec` | |
| Marantec24 | 868 | AM650 | 24, statisch | `Marantec24` | `Marantec24` | |
| Mastercode | 433 | AM650 | 36, statisch | `Mastercode` | | |
| Megacode | 315 | AM650 | 24, statisch | `MegaCode` | | |
| Nero Radio | 434.42 | AM650 | 56, statisch | `Nero Radio` | | nur der statische Modus, dynamisch nicht unterstützt |
| Nero Sketch | 433 | AM650 | 40, statisch | `Nero Sketch` | | |
| Nice Flo | 433.92 | AM650 | 12/24, statisch | `Nice FLO` | `Nice Flo 12bit`, `Nice Flo 24bit` | |
| Nice FloR-S | 433.92 | AM650 | 52, dynamisch | `Nice FloR-S` | `Nice FloR-S` | Zählermodi |
| Nice One | 433.92 | AM650 | 72, dynamisch | `Nice FloR-S` | `Nice One` | |
| Nice O-Code | 433.92 | AM650 | 52/72/112, dynamisch | `Nice FloR-S` | `Nice O-Code`, `Nice O-Code One`, `Nice O-Code+Crt` | per 16-Bit-Installationscode verschlüsselt, siehe [Nice-O-Code-App](/de/subghz/nice-o-code) |
| Nord ICE | 433.92 | AM650 | 33, statisch | `Nord ICE` | `Nord ICE` | |
| Prastel | 433.92, 868 | AM650 | 25, statisch | | | |
| Prastel | 433.92, 868 | AM650 | 42, dynamisch | `Prastel` | `Prastel` | CAME-Leitungskodierung, verschleierte Seriennummer + Zähler |
| Proteco MOVER (TX3) | 433.92 | AM650 | 24, statisch | `Proteco` | `Proteco` | |
| Revers RB2 (Реверс РБ-2(М)) | 433.92 | AM650 | 64, statisch | `Revers_RB2` | `Revers RB2` | |
| Roger | 433.92 | AM650 | 28, statisch | `Roger` | `Roger` | |
| Security+ 1.0 | 315, 433.92, 390 | AM650 | 42, dynamisch | `Security+ 1.0` | `Security+1.0` | |
| Security+ 2.0 | 310, 315, 390, 868 | AM650 | 62, dynamisch | `Security+ 2.0` | `Security+2.0` | |
| Security+ 2.0 Keypad | 315, 390, 868 | AM650 | 86, dynamisch | `Security+ 2.0` | | PIN: [Security+ PIN](/de/subghz/secplus-pin) |
| Somfy Keytis (KeyGo 4 RTS, Keytis NS 2RTS) | 433.42, 868 | AM650 | 80, dynamisch | `Somfy Keytis` | `Somfy Keytis` | |
| Superrollo GW60 | 433.92 | AM650 | 67, dynamisch (KeeLoq HCS361, CRC) | `KeeLoq` | `KL: Superrollo` | Tasten `0x3(0xA)` Up / `0x5(0xC)` Down / `0x7(0xE)` Stop |
| Telcoma/Cardin EDGE (EDGE2/4/20) | 433.92 | AM650 | 32, statisch | `Telcoma/Cardin EDGE` | `Telcoma EDGE` | Präambel `0xFF` + Seriennummer + One-Hot-Kanal, Tor = Ch 0 |
| V2 Phoenix (Phox) | 433.92 | AM650 | 52, dynamisch | `Phoenix_V2` | `V2 Phoenix` | manche Empfänger haben einen Static-Modus; Zählermodi |
| ZKTeco | 430.5 | AM650 | 24, statisch | `Princeton` | `ZKTeco` | Tasten `0x30` UP, `0x03` STOP, `0x0C` DOWN auf die Pfeiltasten gelegt — [ZKTeco CMP200](/de/subghz/zkteco-cmp200) |

## Sensoren und Smart Home

| System | Frequenz | Mod. | Bits / Typ | Dateiname | Hinweise |
|---|---|---|---|---|---|
| Dooya | 433, 315 | AM650 | 40, statisch | `Dooya` | elektrische Jalousien, eigene Tasten |
| Feron | 433.92 | AM650 | 32, statisch | `Feron` | RGB-LED-Fernbedienungen; Ignore-Filter „Sensors" |
| Honeywell | 315 | AM650 | 64, statisch | `Honeywell Sec` | Alarmsensoren |
| Honeywell WDB | 433, 315 | AM650 | 48, statisch | `Honeywell` | Türklingeln |
| Intertechno V3 | 433 | AM650 | 32, statisch | `Intertechno_V3` | Leuchten, Steckdosen |
| Jarolift | 433.92 | AM650 | 72, dynamisch | `Jarolift` | Rollläden |
| Legrand | 433 | AM650 | 18, statisch | `Legrand` | Türklingeln |
| Magellan | 433.92 | AM650 | 32, statisch | `Magellan` | Sensoren, Alarmanlagen |
| Power Smart | 433 | AM650 | 64, statisch | `Power Smart` | Jalousien, Rollläden |
| Somfy Telis (RTS) | 433.42 | AM650 | 56, dynamisch | `Somfy Telis` | Add Manually `Somfy Telis` → `433.42 AM650` |

## Alarmanlagen

| System | Frequenz | Mod. | Bits / Typ | Dateiname | Hinweise |
|---|---|---|---|---|---|
| GangQi | 433.92 | AM650 | 34, statisch | `GangQi` | Fahrradalarme; Ignore-Filter „Alarms" |
| Hollarm | 433.92 | AM650 | 42, statisch | `Hollarm` | Fahrradalarme; Ignore-Filter „Alarms" |

## Universelle / namenlose Fernbedienungen

| System | Frequenz | Mod. | Bits / Typ | Dateiname | Hinweise |
|---|---|---|---|---|---|
| Doorbell32 | 433.92 | AM650 | 32, statisch | `Doorbell32` | PWM 1:3 im Princeton-Stil, Schutzlücke 14·Te |
| Freezer | 433.92 | AM650 | 24, statisch | `Freezer` | in der Registrierung; noch nicht in der Upstream-Liste |
| Hay21 | 433.92 | AM650 | 21, dynamisch | `Hay21` | |
| Holtek | 433/868/315 | AM650 | 40, statisch | `Holtek` | |
| Holtek HT12X | 433/868/315 | AM650/FM | 12, statisch | `Holtek_HT12X` | |
| KeyFinder | 433.92 | AM650 | 24, statisch | `KeyFinder` | Schlüsselfinder-Anhänger |
| KeyFinder2 | 433.92 | AM650 | 11, statisch | `KeyFinder2` | btn(3)+10011+btn(3), keine Seriennummer |
| Princeton (PT2262 …) | 315, 433.92, beliebig | AM650 | 24, statisch | `Princeton` | eigener Filter „Ignore Princeton" |
| SMC5326 | 315, 433.92, beliebig | AM650 | 25, statisch | `SMC5326` | |
| Treadmill37 (QH-433) | 433.92 | AM650 | 37, statisch | `Treadmill37` | |

## Kein Protokoll: RAW und BinRAW

- **RAW** (`Protocol: RAW`) — rohe Zeiten, aufgenommen mit [Read RAW](/de/subghz/read-raw); gibt alles wieder,
  dekodiert nichts.
- **BinRAW** (`Protocol: BinRAW`) — mit `Read → Config → Bin RAW: ON` wird ein unbekanntes, aber sich
  wiederholendes statisches Signal als bereinigte Bitfolge mit rekonstruiertem Te gespeichert. Kann fast jedes
  statische Protokoll emulieren, das der Flipper nicht kennt.

## KeeLoq-Hersteller

Alle werden als `Protocol: KeeLoq` mit `Manufacture:` dekodiert und als `KL: <Name>` angezeigt. Wo nichts anderes
steht, ist das Anlernverfahren „simple" mit einem 10-Bit-Seriennummernanteil im Hop. Mehr zu KeeLoq:
[KeeLoq](/de/subghz/keeloq).

### Tore und Garagen

| Hersteller | Freq. / Mod. | Verfahren / Hinweise |
|---|---|---|
| AERF Collbaix, Hy dom, Medva, Motorgate, Otros, Sabutom, Temp, VDS | | spezielles Verfahren, 10-Bit-Seriennummer im Hop |
| Allmatic | 868, AM650 | keine Seriennummer im Hop — Magic XOR |
| Aprimatic | 433.92, AM650 | 12-Bit-Seriennummer im Hop + 2 Bit „Parität" |
| ATA PTX4 | | normal, 12 Bit |
| Beninca | 433.92, 868, AM650 | keine Seriennummer im Hop — Magic XOR |
| CAME Space | 433.92, AM650 | simple, 12 Bit |
| Cardin S449 | 433.92, **FM12K** | normal, 12 Bit (Originale) / 10 Bit (chinesische) |
| Centurion | 433.92, AM650 | normal, fester Wert `0x1CE` statt der Seriennummer |
| Clemsa Mutancode | | normal, 12 Bit |
| Comunello | 433.92, 868, AM650 | normal |
| DEA Mio | 433.92, AM650 | simple, veränderte Seriennummer (`419` → `C19`) |
| DoorHan | 315, 433.92, AM650 | |
| Doormatic | | normal |
| DTM Neo | 433.92, AM650 | simple, 12 Bit |
| Elmes Poland | 303, 433.92, AM650 | normal |
| Elvox | | normal |
| Erreka | 433.92, 868.35, AM650 | secure mit Seed, 8-Bit-Seriennummer |
| ET Blue, ET Blue Mix | | normal, 10 Bit |
| FAAC FIX | 433.92, AM650 | normal, 10 Bit; 12-Bit-Diskriminator wird in `Seed` gehalten, wie bei Phantom / Hiland |
| FAAC RC, XT | 433.92, 868, AM650 | normal, 12 Bit |
| Fadini | | simple, 12 Bit |
| Genius Bravo (ECHO, Bravo) | 433.92, AM650 | normal, 12 Bit; `0xB` = Programmierung |
| Gibidi | 433.92, AM650 | |
| GSN | 433.92, AM650 | normal, 12 Bit |
| HomeGate | 433.92, AM650 | |
| Hormann EcoStar | 433.92, AM650 | normal |
| IronLogic IL-100, IL-100 Smart PPult | 433.92, AM650 | |
| JCM Tech | 433.92, AM650 | simple, 8 Bit |
| JCM Tech Gen2 | | spezial; ein Eingangsbyte steckt nicht im Paket — wird durchprobiert und als `Seed` angezeigt |
| JCM1G (Antonio Meca, Baleato, Cas, Cubells, Cyacsa, DMIL, EMFA, Forsa, Gandara, Gibidi, Gibidi2, Hy dom, Hybrid, Norton, Nueva Castilla, Puertas Lorenzo, Pujol, Serviparking, Tech, Zibor) | | simple, 8 Bit |
| Jolly Motors | 433.92, AM650 | |
| KEY | 433.92, AM650 | simple, fester Wert `0x2FF` |
| Mc Garcia | | simple, 10 Bit |
| Mhouse | 433.92, AM650 | simple, 8 Bit |
| Monarch | 433.92, AM650 | normal, fest `0x100` oder `0x280` (Dorcas 22366CLN nutzt `0x280`) |
| Motorline | 433.92, AM650 | normal |
| Nice Smilo | 433.92, AM650 | simple, 8 Bit |
| Normstahl | 433.92, AM650 | |
| Novoferm | 433.92, AM650 | |
| Phantom / Hiland | 433.92, AM650 | HCS300, normal, 10 Bit; 12-Bit-Diskriminator wird in `Seed` gehalten |
| Pujol (Vario 4 …) | 433.92, AM650 | spezial, 8 Bit |
| Pujol Vario (älter) | 433.92, AM650 | simple, 8 Bit |
| SEA | | simple |
| Seav | | normal, 12 Bit |
| Sommer (TX03-868-4, Pearl, SOMloq) | 434.42, 868.80, FM12K oder FM476 | normal |
| Stagnoli | | spezial |
| Steelmate | 433.92, AM650 | normal, 12 Bit |
| Stilmatic (R-Tech) | 433.92, AM650 | normal, 12 Bit |
| Telcoma | | tabellenbasiertes Verfahren |
| Verex | | normal |
| Wisniowski | 433.92, AM650 | normal, 12 Bit |
| Wisniowski 1 ByteReversed, Wisniowski 2 | | normal |

### Alarmanlagen und andere

Alligator, Alligator S-275, APS-1100/APS-2550, Cenmax, Cenmax St-5, Cenmax St-7, Faraon, FFFF Normal, FFFF Simple,
Guard RF-311A (normal), Harpoon, KGB/Subaru (Magic Serial Type 1), Leopard, Magic 1 / Magic 2 (Magic Serial
Type 2), Magic 3 / Magic 4 (Magic Serial Type 3), Merlin (einfaches XOR, keine Seriennummer im Hop), Miserere
(normal), Mongoose (normal), Pantera, Pantera CLK, Pantera XS/Jaguar, Partisan RX, Pecinin (simple, 12 Bit), Reff,
Rosh (simple, 12 Bit), Rossi (simple, 12 Bit), Sheriff, SL A2-A4, SL A6-A9/Tomahawk 9010, SL B6,B9 dop, Teco,
Tomahawk TZ-9030, Tomahawk Z,X 3-5, Zero Normal, Zero Simple, ZX-730-750-1055.

## Meine Fernbedienung steht nicht in der Liste

1. Finde die Frequenz mit dem [Frequency Analyzer](/de/subghz/frequency-analyzer), probiere dann
   [Read](/de/subghz/read) mit jeder Modulation (`AM650`, `FM238`, `FM476`, `FM12K`) und halte die Taste
   mindestens 2 s.
2. Probiere `Bin RAW: ON` bei statischen Fernbedienungen.
3. Immer noch nichts? Nimm [Read RAW](/de/subghz/read-raw)-Dateien auf (RSSI-Schwelle `-----`, eine pro
   Modulation; eine Taste 5× für 1–2 s gehalten drücken, dann 5× für 5 s gehalten), fotografiere die
   Fernbedienung (auch geöffnet) und eröffne mit den Dateien ein Issue im Unleashed-Repository.

## Verwandte Seiten

- [Add Manually](/de/subghz/add-manually) · [KeeLoq](/de/subghz/keeloq) · [Rolling Codes](/de/subghz/rolling-codes)
- [Read](/de/subghz/read) · [Read RAW](/de/subghz/read-raw) · [Fernbedienung anlernen](/de/subghz/remote-prog)
