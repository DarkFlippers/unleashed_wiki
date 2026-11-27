---
title: Systèmes pris en charge
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [unleashed-docs, unleashed-readme, unleashed-src]
---
# Systèmes pris en charge

Tous les protocoles Sub-GHz que l'application `Sub-GHz` d'**Unleashed** peut décoder, enregistrer et (pour la
plupart) émettre, établis à partir du registre de protocoles de `lib/subghz/protocols/` et de la documentation des
protocoles Unleashed. Des applications comme *Weather Station* ou
[Remote Analyzer](/fr/subghz/remote-analyzer) possèdent leurs propres listes de protocoles supplémentaires.

::: tip Unleashed
Unleashed est un fork : il décode donc tout ce que décode le firmware officiel. 38 des 64 décodeurs de protocoles
derrière ces tableaux viennent d'OFW, la plupart signés Skorp. Par-dessus, Unleashed ajoute BelKorn, Beninca ARC,
Ditec GOL4, Jarolift, Nice O-Code, Telcoma EDGE, Treadmill37, Freezer et d'autres, plus de 100 constructeurs
KeeLoq, et la capacité d'**émettre** les protocoles à code tournant, avec des
[boutons personnalisés](/fr/subghz/rolling-codes#custom-buttons) et la création via
[Add Manually](/fr/subghz/add-manually).
:::

## Comment lire les tableaux

- **433 MHz** signifie généralement `433.92 MHz`, **868 MHz** signifie `868.35 MHz`. Pas de fréquence = encore
  inconnue.
- **Modulation** est ce qu'il faut régler dans `Read → Config → Modulation` : `AM650`, `AM270`, `FM238`, `FM476`,
  `FM12K`. « FM » = essayez tous les presets FM ; `FSK12K` dans la documentation des constructeurs = `FM12K` sur le
  Flipper.
- **Statique** — code fixe, une copie fonctionne à côté de l'originale. **Dynamique** — code tournant, voir
  [Codes tournants](/fr/subghz/rolling-codes).
- **Nom de fichier** — la valeur de `Protocol:` dans le fichier `.sub` ([format](/fr/subghz/file-format)).
- **Add Manually** — l'entrée dans `Sub-GHz → Add Manually`, s'il y en a une.

## Portails, garages, barrières, volets

| Système | Fréquence | Mod. | Bits / type | Nom de fichier | Add Manually | Remarques |
|---|---|---|---|---|---|---|
| Airforce | 433.92, 868 | AM650 | 18, statique | | | |
| Allstar Firefly 318ALD31K | 318 | AM650 | 18, statique | `Allstar Firefly` | | |
| Alutech AT-4N | 433.92 | AM650 | 72, dynamique | `Alutech AT-4N` | `Alutech AT4N`, `Alutech AT4L` | boutons personnalisés, [modes de compteur](/fr/subghz/counter-mode) |
| AN-Motors (Alutech) AT4 | 433.92 | AM650 | 64, pseudo-dynamique | `KeeLoq` | `AN-Motors AT4` | basé sur KeeLoq |
| Ansonic | 433 | FM | 12, statique | `Ansonic` | | |
| BelKorn (Korn, BelGate, Furniteh, Euro5…) | 433.92 | AM650 | 118, dynamique | `BelKorn` | `BelKorn` | non chiffré : numéro de série de 36 bits + compteur en clair ; pas de champ constructeur, toutes les télécommandes apparaissent comme BelKorn |
| Beninca ARC (TO.GO 2VA) | 433.92 | AM650 | 128, dynamique AES-128 | `Beninca ARC` | `Beninca ARC` | bouton `0` = bouton caché |
| BETT | 433.92 | AM650 | 18, statique | `BETT` | `BETT` | |
| BFT Mitto | 433.92 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `BFT Mitto` | les télécommandes récentes dérivent le seed du numéro de série (décodage dans Read) ; les plus anciennes ont besoin du seed — mode programmation ou [Seed Capturer](/fr/subghz/seed-capturer) ; bouton `0xF` = mode programmation |
| CAME | 433.92, 868 | AM650 | 12/24, statique | `CAME` | `CAME 12bit`, `CAME 24bit` | |
| CAME Atomo (TOPD4REN, TOP44RBN, TOP42R, TOP44R) | 433.92, 868 | AM650 | 62, dynamique | `CAME Atomo` | `CAME Atomo` | maintenez Send ≥ 2 s |
| CAME TWEE (+ TOP44FGN, « New Fixed Code ») | 433.92 | AM650 | 54, pseudo-dynamique | `CAME TWEE` | `CAME TWEE` | |
| Chamberlain Code | 315 | AM650 | 10, statique | `Cham_Code` | | |
| Clemsa | 433 | AM650 | 18, statique | `Clemsa` | | |
| Dickert MAHS | 433 | AM650 | 36, statique | `Dickert_MAHS` | | |
| Ditec GOL4 (BIXLG4, BIXLS2, BIXLP2) | 433.92 | AM650 | 54, dynamique | `Ditec GOL4` | `Ditec GOL4` | → = bouton `0` (caché) |
| Doitrand | 433 | AM650 | 37 | `Doitrand` | | indiqué comme dynamique dans la documentation, enregistré comme type statique dans le firmware |
| Elplast / P-11B / 3BK / E.C.A | 433 | AM650 | 18, statique | `Elplast` | | |
| Erreka IRIS (IR02/IR04) | 433.92, 868.35 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `Erreka` | seed requis ; `0xF` = mode programmation, émet le seed en clair |
| FAAC SLH | 433.92, 868.35 | AM650 | 64, dynamique | `Faac SLH` | `FAAC SLH` | seed par bouton |
| FAAC TM (TM 433/868 DS) | 433.92, 868 | AM650 | 12, statique | `Faac TM` | `FAAC TM` | interrupteurs DIP ; Te conservé depuis la capture |
| Gate TX | 433.92 | AM650 | 64, statique | `GateTX` | `Gate TX` | |
| Genius (KILO TX2/4 JLC, Amigo…) | 433.92, 868.35 | AM650 | 64, dynamique | `Faac SLH` | `Genius` | paquet FAAC SLH avec clé Genius, `Manufacture: Genius` |
| HCS101 | 433 | AM650 | 64, dynamique simple | `KeeLoq` | `KL: HCS101` | de type KeeLoq |
| Hormann | 868 | AM650 | 44, statique | `Hormann HSM` | | |
| iDo | 433 | AM650 | 48, dynamique | `iDo 117/111` | | **décodage seulement** (ne peut pas être émis) |
| Jarolift | 433.92 | AM650 | 72, dynamique | `Jarolift` | `Jarolift` | volets roulants, basé sur KeeLoq |
| KingGates Stylo 4k | 433.92 | AM650 | 89, dynamique | `KingGates Stylo4k` | `KingGates Stylo4k` | basé sur KeeLoq |
| Linear | 300 | AM650 | 10, statique | `Linear` | `Linear` | |
| Linear Delta3 | 315 | AM650 | 8, statique | `LinearDelta3` | | |
| Marantec | 433.92, 868 | AM650 | 49, statique | `Marantec` | `Marantec` | |
| Marantec24 | 868 | AM650 | 24, statique | `Marantec24` | `Marantec24` | |
| Mastercode | 433 | AM650 | 36, statique | `Mastercode` | | |
| Megacode | 315 | AM650 | 24, statique | `MegaCode` | | |
| Nero Radio | 434.42 | AM650 | 56, statique | `Nero Radio` | | mode statique uniquement, le dynamique n'est pas pris en charge |
| Nero Sketch | 433 | AM650 | 40, statique | `Nero Sketch` | | |
| Nice Flo | 433.92 | AM650 | 12/24, statique | `Nice FLO` | `Nice Flo 12bit`, `Nice Flo 24bit` | |
| Nice FloR-S | 433.92 | AM650 | 52, dynamique | `Nice FloR-S` | `Nice FloR-S` | modes de compteur |
| Nice One | 433.92 | AM650 | 72, dynamique | `Nice FloR-S` | `Nice One` | |
| Nice O-Code | 433.92 | AM650 | 52/72/112, dynamique | `Nice FloR-S` | `Nice O-Code`, `Nice O-Code One`, `Nice O-Code+Crt` | clé par un code installateur de 16 bits, voir [Application Nice O-Code](/fr/subghz/nice-o-code) |
| Nord ICE | 433.92 | AM650 | 33, statique | `Nord ICE` | `Nord ICE` | |
| Prastel | 433.92, 868 | AM650 | 25, statique | | | |
| Prastel | 433.92, 868 | AM650 | 42, dynamique | `Prastel` | `Prastel` | codage de ligne CAME, numéro de série brouillé + compteur |
| Proteco MOVER (TX3) | 433.92 | AM650 | 24, statique | `Proteco` | `Proteco` | |
| Revers RB2 (Реверс РБ-2(М)) | 433.92 | AM650 | 64, statique | `Revers_RB2` | `Revers RB2` | |
| Roger | 433.92 | AM650 | 28, statique | `Roger` | `Roger` | |
| Security+ 1.0 | 315, 433.92, 390 | AM650 | 42, dynamique | `Security+ 1.0` | `Security+1.0` | |
| Security+ 2.0 | 310, 315, 390, 868 | AM650 | 62, dynamique | `Security+ 2.0` | `Security+2.0` | |
| Security+ 2.0 Keypad | 315, 390, 868 | AM650 | 86, dynamique | `Security+ 2.0` | | PIN : [Security+ PIN](/fr/subghz/secplus-pin) |
| Somfy Keytis (KeyGo 4 RTS, Keytis NS 2RTS) | 433.42, 868 | AM650 | 80, dynamique | `Somfy Keytis` | `Somfy Keytis` | |
| Superrollo GW60 | 433.92 | AM650 | 67, dynamique (KeeLoq HCS361, CRC) | `KeeLoq` | `KL: Superrollo` | boutons `0x3(0xA)` Up / `0x5(0xC)` Down / `0x7(0xE)` Stop |
| Telcoma/Cardin EDGE (EDGE2/4/20) | 433.92 | AM650 | 32, statique | `Telcoma/Cardin EDGE` | `Telcoma EDGE` | préambule `0xFF` + numéro de série + canal one-hot, portail = Ch 0 |
| V2 Phoenix (Phox) | 433.92 | AM650 | 52, dynamique | `Phoenix_V2` | `V2 Phoenix` | certains récepteurs ont un mode Static ; modes de compteur |
| ZKTeco | 430.5 | AM650 | 24, statique | `Princeton` | `ZKTeco` | boutons `0x30` UP, `0x03` STOP, `0x0C` DOWN associés aux flèches — [ZKTeco CMP200](/fr/subghz/zkteco-cmp200) |

## Capteurs et maison connectée

| Système | Fréquence | Mod. | Bits / type | Nom de fichier | Remarques |
|---|---|---|---|---|---|
| Dooya | 433, 315 | AM650 | 40, statique | `Dooya` | stores électriques, boutons personnalisés |
| Feron | 433.92 | AM650 | 32, statique | `Feron` | télécommandes de LED RGB ; filtre d'exclusion « Sensors » |
| Honeywell | 315 | AM650 | 64, statique | `Honeywell Sec` | capteurs d'alarme |
| Honeywell WDB | 433, 315 | AM650 | 48, statique | `Honeywell` | sonnettes |
| Intertechno V3 | 433 | AM650 | 32, statique | `Intertechno_V3` | éclairages, prises |
| Jarolift | 433.92 | AM650 | 72, dynamique | `Jarolift` | volets roulants |
| Legrand | 433 | AM650 | 18, statique | `Legrand` | sonnettes |
| Magellan | 433.92 | AM650 | 32, statique | `Magellan` | capteurs, alarmes |
| Power Smart | 433 | AM650 | 64, statique | `Power Smart` | stores, volets |
| Somfy Telis (RTS) | 433.42 | AM650 | 56, dynamique | `Somfy Telis` | Add Manually `Somfy Telis` → `433.42 AM650` |

## Alarmes

| Système | Fréquence | Mod. | Bits / type | Nom de fichier | Remarques |
|---|---|---|---|---|---|
| GangQi | 433.92 | AM650 | 34, statique | `GangQi` | alarmes de vélo ; filtre d'exclusion « Alarms » |
| Hollarm | 433.92 | AM650 | 42, statique | `Hollarm` | alarmes de vélo ; filtre d'exclusion « Alarms » |

## Télécommandes génériques / sans marque

| Système | Fréquence | Mod. | Bits / type | Nom de fichier | Remarques |
|---|---|---|---|---|---|
| Doorbell32 | 433.92 | AM650 | 32, statique | `Doorbell32` | PWM 1:3 de type Princeton, garde de 14·Te |
| Freezer | 433.92 | AM650 | 24, statique | `Freezer` | présent dans le registre ; pas encore dans la liste amont |
| Hay21 | 433.92 | AM650 | 21, dynamique | `Hay21` | |
| Holtek | 433/868/315 | AM650 | 40, statique | `Holtek` | |
| Holtek HT12X | 433/868/315 | AM650/FM | 12, statique | `Holtek_HT12X` | |
| KeyFinder | 433.92 | AM650 | 24, statique | `KeyFinder` | porte-clés localisateurs |
| KeyFinder2 | 433.92 | AM650 | 11, statique | `KeyFinder2` | btn(3)+10011+btn(3), pas de numéro de série |
| Princeton (PT2262…) | 315, 433.92, toutes | AM650 | 24, statique | `Princeton` | possède son propre filtre « Ignore Princeton » |
| SMC5326 | 315, 433.92, toutes | AM650 | 25, statique | `SMC5326` | |
| Treadmill37 (QH-433) | 433.92 | AM650 | 37, statique | `Treadmill37` | |

## Pas un protocole : RAW et BinRAW

- **RAW** (`Protocol: RAW`) — timings bruts enregistrés avec [Read RAW](/fr/subghz/read-raw) ; rejoue n'importe quoi,
  ne décode rien.
- **BinRAW** (`Protocol: BinRAW`) — avec `Read → Config → Bin RAW: ON`, un signal statique inconnu mais répétitif est
  enregistré sous forme de séquence de bits nettoyée, avec un Te reconstitué. Peut émuler presque tous les protocoles
  statiques que le Flipper ne connaît pas.

## Constructeurs KeeLoq

Tous décodés comme `Protocol: KeeLoq` avec `Manufacture:` ; affichés sous la forme `KL: <nom>`. Sauf mention
contraire, l'apprentissage est « simple » avec une partie de numéro de série de 10 bits dans le hop. Pour en savoir
plus sur KeeLoq : [KeeLoq](/fr/subghz/keeloq).

### Portails et garages

| Constructeur | Fréq. / mod. | Apprentissage / remarques |
|---|---|---|
| AERF Collbaix, Hy dom, Medva, Motorgate, Otros, Sabutom, Temp, VDS | | apprentissage spécial, numéro de série de 10 bits dans le hop |
| Allmatic | 868, AM650 | pas de numéro de série dans le hop — magic XOR |
| Aprimatic | 433.92, AM650 | numéro de série de 12 bits dans le hop + 2 bits de « parité » |
| ATA PTX4 | | normal, 12 bits |
| Beninca | 433.92, 868, AM650 | pas de numéro de série dans le hop — magic XOR |
| CAME Space | 433.92, AM650 | simple, 12 bits |
| Cardin S449 | 433.92, **FM12K** | normal, 12 bits (originaux) / 10 bits (chinois) |
| Centurion | 433.92, AM650 | normal, valeur fixe `0x1CE` au lieu du numéro de série |
| Clemsa Mutancode | | normal, 12 bits |
| Comunello | 433.92, 868, AM650 | normal |
| DEA Mio | 433.92, AM650 | simple, numéro de série modifié (`419` → `C19`) |
| DoorHan | 315, 433.92, AM650 | |
| Doormatic | | normal |
| DTM Neo | 433.92, AM650 | simple, 12 bits |
| Elmes Poland | 303, 433.92, AM650 | normal |
| Elvox | | normal |
| Erreka | 433.92, 868.35, AM650 | secure avec seed, numéro de série de 8 bits |
| ET Blue, ET Blue Mix | | normal, 10 bits |
| FAAC FIX | 433.92, AM650 | normal, 10 bits ; discriminateur de 12 bits conservé dans `Seed`, comme Phantom / Hiland |
| FAAC RC, XT | 433.92, 868, AM650 | normal, 12 bits |
| Fadini | | simple, 12 bits |
| Genius Bravo (ECHO, Bravo) | 433.92, AM650 | normal, 12 bits ; `0xB` = programmation |
| Gibidi | 433.92, AM650 | |
| GSN | 433.92, AM650 | normal, 12 bits |
| HomeGate | 433.92, AM650 | |
| Hormann EcoStar | 433.92, AM650 | normal |
| IronLogic IL-100, IL-100 Smart PPult | 433.92, AM650 | |
| JCM Tech | 433.92, AM650 | simple, 8 bits |
| JCM Tech Gen2 | | spécial ; un octet d'entrée absent du paquet — retrouvé par force brute, affiché comme `Seed` |
| JCM1G (Antonio Meca, Baleato, Cas, Cubells, Cyacsa, DMIL, EMFA, Forsa, Gandara, Gibidi, Gibidi2, Hy dom, Hybrid, Norton, Nueva Castilla, Puertas Lorenzo, Pujol, Serviparking, Tech, Zibor) | | simple, 8 bits |
| Jolly Motors | 433.92, AM650 | |
| KEY | 433.92, AM650 | simple, valeur fixe `0x2FF` |
| Mc Garcia | | simple, 10 bits |
| Mhouse | 433.92, AM650 | simple, 8 bits |
| Monarch | 433.92, AM650 | normal, `0x100` ou `0x280` fixe (le Dorcas 22366CLN utilise `0x280`) |
| Motorline | 433.92, AM650 | normal |
| Nice Smilo | 433.92, AM650 | simple, 8 bits |
| Normstahl | 433.92, AM650 | |
| Novoferm | 433.92, AM650 | |
| Phantom / Hiland | 433.92, AM650 | HCS300, normal, 10 bits ; discriminateur de 12 bits conservé dans `Seed` |
| Pujol (Vario 4…) | 433.92, AM650 | spécial, 8 bits |
| Pujol Vario (plus ancien) | 433.92, AM650 | simple, 8 bits |
| SEA | | simple |
| Seav | | normal, 12 bits |
| Sommer (TX03-868-4, Pearl, SOMloq) | 434.42, 868.80, FM12K ou FM476 | normal |
| Stagnoli | | spécial |
| Steelmate | 433.92, AM650 | normal, 12 bits |
| Stilmatic (R-Tech) | 433.92, AM650 | normal, 12 bits |
| Telcoma | | apprentissage piloté par table |
| Verex | | normal |
| Wisniowski | 433.92, AM650 | normal, 12 bits |
| Wisniowski 1 ByteReversed, Wisniowski 2 | | normal |

### Alarmes et autres

Alligator, Alligator S-275, APS-1100/APS-2550, Cenmax, Cenmax St-5, Cenmax St-7, Faraon, FFFF Normal, FFFF Simple,
Guard RF-311A (normal), Harpoon, KGB/Subaru (magic serial type 1), Leopard, Magic 1 / Magic 2 (magic serial type 2),
Magic 3 / Magic 4 (magic serial type 3), Merlin (XOR simple, pas de numéro de série dans le hop), Miserere (normal),
Mongoose (normal), Pantera, Pantera CLK, Pantera XS/Jaguar, Partisan RX, Pecinin (simple, 12 bits), Reff, Rosh
(simple, 12 bits), Rossi (simple, 12 bits), Sheriff, SL A2-A4, SL A6-A9/Tomahawk 9010, SL B6,B9 dop, Teco, Tomahawk
TZ-9030, Tomahawk Z,X 3-5, Zero Normal, Zero Simple, ZX-730-750-1055.

## Ma télécommande n'est pas dans la liste

1. Trouvez la fréquence avec le [Frequency Analyzer](/fr/subghz/frequency-analyzer), puis essayez
   [Read](/fr/subghz/read) avec toutes les modulations (`AM650`, `FM238`, `FM476`, `FM12K`), en maintenant le bouton
   ≥ 2 s.
2. Essayez `Bin RAW: ON` pour les télécommandes statiques.
3. Toujours rien ? Enregistrez des fichiers [Read RAW](/fr/subghz/read-raw) (seuil RSSI `-----`, un par modulation ;
   appuyez sur un bouton 5× en le maintenant 1–2 s, puis 5× en le maintenant 5 s), photographiez la télécommande
   (également ouverte), et ouvrez une issue dans le dépôt Unleashed avec les fichiers.

## Voir aussi

- [Add Manually](/fr/subghz/add-manually) · [KeeLoq](/fr/subghz/keeloq) · [Codes tournants](/fr/subghz/rolling-codes)
- [Read](/fr/subghz/read) · [Read RAW](/fr/subghz/read-raw) · [Programmation d'une télécommande](/fr/subghz/remote-prog)
