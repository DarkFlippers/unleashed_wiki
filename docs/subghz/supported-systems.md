---
title: Supported systems
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [unleashed-docs, unleashed-readme, unleashed-src]
---
# Supported systems

All Sub-GHz protocols the **Unleashed** `Sub-GHz` app can decode, save and (mostly) send, built from the protocol
registry in `lib/subghz/protocols/` and the Unleashed protocol documentation. Apps such as *Weather Station* or
[Remote Analyzer](/subghz/remote-analyzer) have their own extra protocol lists.

::: tip Unleashed
Unleashed is a fork, so it decodes everything the official firmware does: 38 of the 64 protocol decoders behind
these tables are OFW's, most of them Skorp's work. On top of those it adds BelKorn, Beninca ARC, Ditec GOL4,
Jarolift, Nice O-Code, Telcoma EDGE, Treadmill37, Freezer and others, 100+ KeeLoq manufacturers, and the ability
to **send** rolling-code protocols, with [custom buttons](/subghz/rolling-codes#custom-buttons) and
[Add Manually](/subghz/add-manually) creation.
:::

## How to read the tables

- **433 MHz** usually means `433.92 MHz`, **868 MHz** means `868.35 MHz`. No frequency = not known yet.
- **Modulation** is what to set in `Read → Config → Modulation`: `AM650`, `AM270`, `FM238`, `FM476`, `FM12K`.
  "FM" = try every FM preset; `FSK12K` in vendor docs = `FM12K` on the Flipper.
- **Static** — fixed code, a copy works alongside the original. **Dynamic** — rolling code, see
  [Rolling codes](/subghz/rolling-codes).
- **File name** — the value of `Protocol:` in the `.sub` file ([format](/subghz/file-format)).
- **Add Manually** — the entry in `Sub-GHz → Add Manually`, if any.

## Gates, garages, barriers, shutters

| System | Frequency | Mod. | Bits / type | File name | Add Manually | Notes |
|---|---|---|---|---|---|---|
| Airforce | 433.92, 868 | AM650 | 18, static | | | |
| Allstar Firefly 318ALD31K | 318 | AM650 | 18, static | `Allstar Firefly` | | |
| Alutech AT-4N | 433.92 | AM650 | 72, dynamic | `Alutech AT-4N` | `Alutech AT4N` | custom buttons, [counter modes](/subghz/counter-mode) |
| AN-Motors (Alutech) AT4 | 433.92 | AM650 | 64, pseudo-dynamic | `KeeLoq` | `AN-Motors AT4` | KeeLoq based |
| Ansonic | 433 | FM | 12, static | `Ansonic` | | |
| BelKorn (Korn, BelGate, Furniteh…) | 433.92 | AM650 | 118, dynamic | `BelKorn` | `BelKorn` | not encrypted: 36-bit serial + plaintext counter; no manufacturer field, every remote reads as BelKorn |
| Beninca ARC (TO.GO 2VA) | 433.92 | AM650 | 128, dynamic AES-128 | `Beninca ARC` | `Beninca ARC` | button `0` = hidden button |
| BETT | 433.92 | AM650 | 18, static | `BETT` | `BETT` | |
| BFT Mitto | 433.92 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `BFT Mitto` | newer remotes derive the seed from the serial (decode in Read); older need the seed — programming mode or [Seed Capturer](/subghz/seed-capturer); button `0xF` = programming mode |
| CAME | 433.92, 868 | AM650 | 12/24, static | `CAME` | `CAME 12bit`, `CAME 24bit` | |
| CAME Atomo (TOPD4REN, TOP44RBN, TOP42R, TOP44R) | 433.92, 868 | AM650 | 62, dynamic | `CAME Atomo` | `CAME Atomo` | hold Send ≥ 2 s |
| CAME TWEE (+ TOP44FGN, "New Fixed Code") | 433.92 | AM650 | 54, pseudo-dynamic | `CAME TWEE` | `CAME TWEE` | |
| Chamberlain Code | 315 | AM650 | 10, static | `Cham_Code` | | |
| Clemsa | 433 | AM650 | 18, static | `Clemsa` | | |
| Dickert MAHS | 433 | AM650 | 36, static | `Dickert_MAHS` | | |
| Ditec GOL4 (BIXLG4, BIXLS2, BIXLP2) | 433.92 | AM650 | 54, dynamic | `Ditec GOL4` | `Ditec GOL4` | → = button `0` (hidden) |
| Doitrand | 433 | AM650 | 37 | `Doitrand` | | listed as dynamic in the docs, registered as static type in the firmware |
| Elplast / P-11B / 3BK / E.C.A | 433 | AM650 | 18, static | `Elplast` | | |
| Erreka IRIS (IR02/IR04) | 433.92, 868.35 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `Erreka` | seed required; `0xF` = programming mode, sends the seed in clear |
| FAAC SLH | 433.92, 868.35 | AM650 | 64, dynamic | `Faac SLH` | `FAAC SLH` | seed per button |
| FAAC TM (TM 433/868 DS) | 433.92, 868 | AM650 | 12, static | `Faac TM` | `FAAC TM` | DIP switches; Te kept from capture |
| Gate TX | 433.92 | AM650 | 64, static | `GateTX` | `Gate TX` | |
| Genius (KILO TX2/4 JLC, Amigo…) | 433.92, 868.35 | AM650 | 64, dynamic | `Faac SLH` | `Genius` | FAAC SLH frame with Genius key, `Manufacture: Genius` |
| HCS101 | 433 | AM650 | 64, simple dynamic | `KeeLoq` | `KL: HCS101` | KeeLoq-like |
| Hormann | 868 | AM650 | 44, static | `Hormann HSM` | | |
| iDo | 433 | AM650 | 48, dynamic | `iDo 117/111` | | **decode only** (can't be sent) |
| Jarolift | 433.92 | AM650 | 72, dynamic | `Jarolift` | `Jarolift` | roller shutters, KeeLoq based |
| KingGates Stylo 4k | 433.92 | AM650 | 89, dynamic | `KingGates Stylo4k` | `KingGates Stylo4k` | KeeLoq based |
| Linear | 300 | AM650 | 10, static | `Linear` | `Linear` | |
| Linear Delta3 | 315 | AM650 | 8, static | `LinearDelta3` | | |
| Marantec | 433.92, 868 | AM650 | 49, static | `Marantec` | `Marantec` | |
| Marantec24 | 868 | AM650 | 24, static | `Marantec24` | `Marantec24` | |
| Mastercode | 433 | AM650 | 36, static | `Mastercode` | | |
| Megacode | 315 | AM650 | 24, static | `MegaCode` | | |
| Nero Radio | 434.42 | AM650 | 56, static | `Nero Radio` | | static mode only, dynamic unsupported |
| Nero Sketch | 433 | AM650 | 40, static | `Nero Sketch` | | |
| Nice Flo | 433.92 | AM650 | 12/24, static | `Nice FLO` | `Nice Flo 12bit`, `Nice Flo 24bit` | |
| Nice FloR-S | 433.92 | AM650 | 52, dynamic | `Nice FloR-S` | `Nice FloR-S` | counter modes |
| Nice One | 433.92 | AM650 | 72, dynamic | `Nice FloR-S` | `Nice One` | |
| Nice O-Code | 433.92 | AM650 | 52/72/112, dynamic | `Nice FloR-S` | `Nice O-Code`, `Nice O-Code One`, `Nice O-Code+Crt` | keyed by 16-bit installer code, see [Nice O-Code app](/subghz/nice-o-code) |
| Nord ICE | 433.92 | AM650 | 33, static | `Nord ICE` | `Nord ICE` | |
| Prastel | 433.92, 868 | AM650 | 25, static | | | |
| Prastel | 433.92, 868 | AM650 | 42, dynamic | `Prastel` | `Prastel` | CAME line coding, scrambled serial + counter |
| Proteco MOVER (TX3) | 433.92 | AM650 | 24, static | `Proteco` | `Proteco` | |
| Revers RB2 (Реверс РБ-2(М)) | 433.92 | AM650 | 64, static | `Revers_RB2` | `Revers RB2` | |
| Roger | 433.92 | AM650 | 28, static | `Roger` | `Roger` | |
| Security+ 1.0 | 315, 433.92, 390 | AM650 | 42, dynamic | `Security+ 1.0` | `Security+1.0` | |
| Security+ 2.0 | 310, 315, 390, 868 | AM650 | 62, dynamic | `Security+ 2.0` | `Security+2.0` | |
| Security+ 2.0 Keypad | 315, 390, 868 | AM650 | 86, dynamic | `Security+ 2.0` | | PIN: [Security+ PIN](/subghz/secplus-pin) |
| Somfy Keytis (KeyGo 4 RTS, Keytis NS 2RTS) | 433.42, 868 | AM650 | 80, dynamic | `Somfy Keytis` | `Somfy Keytis` | |
| Superrollo GW60 | 433.92 | AM650 | 67, dynamic (KeeLoq HCS361, CRC) | `KeeLoq` | `KL: Superrollo` | buttons `0x3(0xA)` Up / `0x5(0xC)` Down / `0x7(0xE)` Stop |
| Telcoma/Cardin EDGE (EDGE2/4/20) | 433.92 | AM650 | 32, static | `Telcoma/Cardin EDGE` | `Telcoma EDGE` | `0xFF` preamble + serial + one-hot channel, gate = Ch 0 |
| V2 Phoenix (Phox) | 433.92 | AM650 | 52, dynamic | `Phoenix_V2` | `V2 Phoenix` | some receivers have a Static mode; counter modes |
| ZKTeco | 430.5 | AM650 | 24, static | `Princeton` | `ZKTeco` | buttons `0x30` UP, `0x03` STOP, `0x0C` DOWN mapped to arrows — [ZKTeco CMP200](/subghz/zkteco-cmp200) |

## Sensors and smart home

| System | Frequency | Mod. | Bits / type | File name | Notes |
|---|---|---|---|---|---|
| Dooya | 433, 315 | AM650 | 40, static | `Dooya` | electric blinds, custom buttons |
| Feron | 433.92 | AM650 | 32, static | `Feron` | RGB LED remotes; "Sensors" ignore filter |
| Honeywell | 315 | AM650 | 64, static | `Honeywell Sec` | alarm sensors |
| Honeywell WDB | 433, 315 | AM650 | 48, static | `Honeywell` | doorbells |
| Intertechno V3 | 433 | AM650 | 32, static | `Intertechno_V3` | lights, sockets |
| Jarolift | 433.92 | AM650 | 72, dynamic | `Jarolift` | roller shutters |
| Legrand | 433 | AM650 | 18, static | `Legrand` | doorbells |
| Magellan | 433.92 | AM650 | 32, static | `Magellan` | sensors, alarms |
| Power Smart | 433 | AM650 | 64, static | `Power Smart` | blinds, shutters |
| Somfy Telis (RTS) | 433.42 | AM650 | 56, dynamic | `Somfy Telis` | Add Manually `Somfy Telis` → `433.42 AM650` |

## Alarms

| System | Frequency | Mod. | Bits / type | File name | Notes |
|---|---|---|---|---|---|
| GangQi | 433.92 | AM650 | 34, static | `GangQi` | bike alarms; "Alarms" ignore filter |
| Hollarm | 433.92 | AM650 | 42, static | `Hollarm` | bike alarms; "Alarms" ignore filter |

## Generic / unbranded remotes

| System | Frequency | Mod. | Bits / type | File name | Notes |
|---|---|---|---|---|---|
| Doorbell32 | 433.92 | AM650 | 32, static | `Doorbell32` | Princeton-style 1:3 PWM, 14·Te guard |
| Freezer | 433.92 | AM650 | 24, static | `Freezer` | in the registry; not yet in the upstream list |
| Hay21 | 433.92 | AM650 | 21, dynamic | `Hay21` | |
| Holtek | 433/868/315 | AM650 | 40, static | `Holtek` | |
| Holtek HT12X | 433/868/315 | AM650/FM | 12, static | `Holtek_HT12X` | |
| KeyFinder | 433.92 | AM650 | 24, static | `KeyFinder` | key finder fobs |
| KeyFinder2 | 433.92 | AM650 | 11, static | `KeyFinder2` | btn(3)+10011+btn(3), no serial |
| Princeton (PT2262…) | 315, 433.92, any | AM650 | 24, static | `Princeton` | own "Ignore Princeton" filter |
| SMC5326 | 315, 433.92, any | AM650 | 25, static | `SMC5326` | |
| Treadmill37 (QH-433) | 433.92 | AM650 | 37, static | `Treadmill37` | |

## Not a protocol: RAW and BinRAW

- **RAW** (`Protocol: RAW`) — raw timings recorded with [Read RAW](/subghz/read-raw); replays anything, decodes
  nothing.
- **BinRAW** (`Protocol: BinRAW`) — with `Read → Config → Bin RAW: ON`, an unknown but repeating static signal is
  saved as a cleaned-up bit sequence with a recovered Te. Can emulate almost any static protocol the Flipper
  doesn't know.

## KeeLoq manufacturers

All decoded as `Protocol: KeeLoq` with `Manufacture:`; shown as `KL: <name>`. Unless noted, learning is "simple"
with a 10-bit serial part in the hop. More about KeeLoq: [KeeLoq](/subghz/keeloq).

### Gates and garages

| Manufacturer | Freq / mod. | Learning / notes |
|---|---|---|
| AERF Collbaix, Hy dom, Medva, Motorgate, Otros, Sabutom, Temp, VDS | | special learning, 10-bit serial in hop |
| Allmatic | 868, AM650 | no serial in hop — magic XOR |
| Aprimatic | 433.92, AM650 | 12-bit serial in hop + 2-bit "parity" |
| ATA PTX4 | | normal, 12-bit |
| Beninca | 433.92, 868, AM650 | no serial in hop — magic XOR |
| CAME Space | 433.92, AM650 | simple, 12-bit |
| Cardin S449 | 433.92, **FM12K** | normal, 12-bit (originals) / 10-bit (Chinese) |
| Centurion | 433.92, AM650 | normal, fixed value `0x1CE` instead of serial |
| Clemsa Mutancode | | normal, 12-bit |
| Comunello | 433.92, 868, AM650 | normal |
| DEA Mio | 433.92, AM650 | simple, modified serial (`419` → `C19`) |
| DoorHan | 315, 433.92, AM650 | |
| Doormatic | | normal |
| DTM Neo | 433.92, AM650 | simple, 12-bit |
| Elmes Poland | 303, 433.92, AM650 | normal |
| Elvox | | normal |
| Erreka | 433.92, 868.35, AM650 | secure with seed, 8-bit serial |
| ET Blue, ET Blue Mix | | normal, 10-bit |
| FAAC FIX | 433.92, AM650 | normal, 10-bit; 12-bit discriminator kept in `Seed`, same as Phantom / Hiland |
| FAAC RC, XT | 433.92, 868, AM650 | normal, 12-bit |
| Fadini | | simple, 12-bit |
| Genius Bravo (ECHO, Bravo) | 433.92, AM650 | normal, 12-bit; `0xB` = programming |
| Gibidi | 433.92, AM650 | |
| GSN | 433.92, AM650 | normal, 12-bit |
| HomeGate | 433.92, AM650 | |
| Hormann EcoStar | 433.92, AM650 | normal |
| IronLogic IL-100, IL-100 Smart PPult | 433.92, AM650 | |
| JCM Tech | 433.92, AM650 | simple, 8-bit |
| JCM Tech Gen2 | | special; one input byte not in the packet — brute-forced, shown as `Seed` |
| JCM1G (Antonio Meca, Baleato, Cas, Cubells, Cyacsa, DMIL, EMFA, Forsa, Gandara, Gibidi, Gibidi2, Hy dom, Hybrid, Norton, Nueva Castilla, Puertas Lorenzo, Pujol, Serviparking, Tech, Zibor) | | simple, 8-bit |
| Jolly Motors | 433.92, AM650 | |
| KEY | 433.92, AM650 | simple, fixed value `0x2FF` |
| Mc Garcia | | simple, 10-bit |
| Mhouse | 433.92, AM650 | simple, 8-bit |
| Monarch | 433.92, AM650 | normal, fixed `0x100` or `0x280` (Dorcas 22366CLN uses `0x280`) |
| Motorline | 433.92, AM650 | normal |
| Nice Smilo | 433.92, AM650 | simple, 8-bit |
| Normstahl | 433.92, AM650 | |
| Novoferm | 433.92, AM650 | |
| Phantom / Hiland | 433.92, AM650 | HCS300, normal, 10-bit; 12-bit discriminator kept in `Seed` |
| Pujol (Vario 4…) | 433.92, AM650 | special, 8-bit |
| Pujol Vario (older) | 433.92, AM650 | simple, 8-bit |
| SEA | | simple |
| Seav | | normal, 12-bit |
| Sommer (TX03-868-4, Pearl, SOMloq) | 434.42, 868.80, FM12K or FM476 | normal |
| Stagnoli | | special |
| Steelmate | 433.92, AM650 | normal, 12-bit |
| Stilmatic (R-Tech) | 433.92, AM650 | normal, 12-bit |
| Telcoma | | table-driven learning |
| Verex | | normal |
| Wisniowski | 433.92, AM650 | normal, 12-bit |
| Wisniowski 1 ByteReversed, Wisniowski 2 | | normal |

### Alarms and others

Alligator, Alligator S-275, APS-1100/APS-2550, Cenmax, Cenmax St-5, Cenmax St-7, Faraon, FFFF Normal, FFFF Simple,
Guard RF-311A (normal), Harpoon, KGB/Subaru (magic serial type 1), Leopard, Magic 1 / Magic 2 (magic serial type 2),
Magic 3 / Magic 4 (magic serial type 3), Merlin (simple XOR, no serial in hop), Miserere (normal), Mongoose
(normal), Pantera, Pantera CLK, Pantera XS/Jaguar, Partisan RX, Pecinin (simple, 12-bit), Reff, Rosh (simple,
12-bit), Rossi (simple, 12-bit), Sheriff, SL A2-A4, SL A6-A9/Tomahawk 9010, SL B6,B9 dop, Teco, Tomahawk TZ-9030,
Tomahawk Z,X 3-5, Zero Normal, Zero Simple, ZX-730-750-1055.

## My remote isn't listed

1. Find the frequency with the [Frequency Analyzer](/subghz/frequency-analyzer), then try [Read](/subghz/read)
   with every modulation (`AM650`, `FM238`, `FM476`, `FM12K`), holding the button ≥ 2 s.
2. Try `Bin RAW: ON` for static remotes.
3. Still nothing? Record [Read RAW](/subghz/read-raw) files (RSSI threshold `-----`, one per modulation; press one
   button 5× holding 1–2 s, then 5× holding 5 s), photograph the remote (also opened), and open an issue in the
   Unleashed repository with the files.

## Related

- [Add Manually](/subghz/add-manually) · [KeeLoq](/subghz/keeloq) · [Rolling codes](/subghz/rolling-codes)
- [Read](/subghz/read) · [Read RAW](/subghz/read-raw) · [Remote programming](/subghz/remote-prog)
