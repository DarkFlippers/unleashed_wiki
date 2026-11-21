---
title: Підтримувані системи
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [unleashed-docs, unleashed-readme, unleashed-src]
---
# Підтримувані системи

Усі протоколи Sub-GHz, які застосунок `Sub-GHz` в **Unleashed** вміє декодувати, зберігати й (переважно)
надсилати, зібрані з реєстру протоколів у `lib/subghz/protocols/` і з документації протоколів Unleashed. Такі
застосунки, як *Weather Station* або [Remote Analyzer](/ua/subghz/remote-analyzer), мають власні додаткові
переліки протоколів.

::: tip Unleashed
Unleashed — форк, тому він декодує все те саме, що й офіційна прошивка: 38 із 64 декодерів протоколів, на яких
побудовані ці таблиці, — з OFW, і більшість їх написав Skorp. Поверх них додано BelKorn, Beninca ARC, Ditec GOL4,
Jarolift, Nice O-Code, Telcoma EDGE, Treadmill37, Freezer та інші, 100+ виробників KeeLoq і можливість
**надсилати** протоколи з динамічним кодом, із [кастомними кнопками](/ua/subghz/rolling-codes#custom-buttons) і
створенням через [Add Manually](/ua/subghz/add-manually).
:::

## Як читати таблиці

- **433 МГц** зазвичай означає `433.92 MHz`, **868 МГц** означає `868.35 MHz`. Немає частоти — вона ще невідома.
- **Модуляція** — це те, що потрібно задати в `Read → Config → Modulation`: `AM650`, `AM270`, `FM238`, `FM476`,
  `FM12K`. «FM» = пробуйте всі пресети FM; `FSK12K` у документації виробників = `FM12K` на Flipper.
- **Статичний** — фіксований код, копія працює разом з оригіналом. **Динамічний** — динамічний код, див.
  [Динамічні коди](/ua/subghz/rolling-codes).
- **Ім'я у файлі** — значення `Protocol:` у файлі `.sub` ([формат](/ua/subghz/file-format)).
- **Add Manually** — відповідний запис у `Sub-GHz → Add Manually`, якщо він є.

## Ворота, гаражі, шлагбауми, роллети

| Система | Частота | Мод. | Біти / тип | Ім'я у файлі | Add Manually | Примітки |
|---|---|---|---|---|---|---|
| Airforce | 433.92, 868 | AM650 | 18, статичний | | | |
| Allstar Firefly 318ALD31K | 318 | AM650 | 18, статичний | `Allstar Firefly` | | |
| Alutech AT-4N | 433.92 | AM650 | 72, динамічний | `Alutech AT-4N` | `Alutech AT4N` | кастомні кнопки, [режими лічильника](/ua/subghz/counter-mode) |
| AN-Motors (Alutech) AT4 | 433.92 | AM650 | 64, псевдодинамічний | `KeeLoq` | `AN-Motors AT4` | на базі KeeLoq |
| Ansonic | 433 | FM | 12, статичний | `Ansonic` | | |
| BelKorn (Korn, BelGate, Furniteh…) | 433.92 | AM650 | 118, динамічний | `BelKorn` | `BelKorn` | не зашифрований: 36-бітний серійник + лічильник у відкритому вигляді; поля виробника немає, тому кожний пульт читається як BelKorn |
| Beninca ARC (TO.GO 2VA) | 433.92 | AM650 | 128, динамічний AES-128 | `Beninca ARC` | `Beninca ARC` | кнопка `0` = прихована кнопка |
| BETT | 433.92 | AM650 | 18, статичний | `BETT` | `BETT` | |
| BFT Mitto | 433.92 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `BFT Mitto` | новіші пульти виводять seed із серійника (декодуються в Read); старішим потрібен seed — режим програмування або [Seed Capturer](/ua/subghz/seed-capturer); кнопка `0xF` = режим програмування |
| CAME | 433.92, 868 | AM650 | 12/24, статичний | `CAME` | `CAME 12bit`, `CAME 24bit` | |
| CAME Atomo (TOPD4REN, TOP44RBN, TOP42R, TOP44R) | 433.92, 868 | AM650 | 62, динамічний | `CAME Atomo` | `CAME Atomo` | утримуйте Send ≥ 2 с |
| CAME TWEE (+ TOP44FGN, «New Fixed Code») | 433.92 | AM650 | 54, псевдодинамічний | `CAME TWEE` | `CAME TWEE` | |
| Chamberlain Code | 315 | AM650 | 10, статичний | `Cham_Code` | | |
| Clemsa | 433 | AM650 | 18, статичний | `Clemsa` | | |
| Dickert MAHS | 433 | AM650 | 36, статичний | `Dickert_MAHS` | | |
| Ditec GOL4 (BIXLG4, BIXLS2, BIXLP2) | 433.92 | AM650 | 54, динамічний | `Ditec GOL4` | `Ditec GOL4` | → = кнопка `0` (прихована) |
| Doitrand | 433 | AM650 | 37 | `Doitrand` | | у документації позначений як динамічний, у прошивці зареєстрований зі статичним типом |
| Elplast / P-11B / 3BK / E.C.A | 433 | AM650 | 18, статичний | `Elplast` | | |
| Erreka IRIS (IR02/IR04) | 433.92, 868.35 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `Erreka` | потрібен seed; `0xF` = режим програмування, надсилає seed у відкритому вигляді |
| FAAC SLH | 433.92, 868.35 | AM650 | 64, динамічний | `Faac SLH` | `FAAC SLH` | seed для кожної кнопки окремий |
| FAAC TM (TM 433/868 DS) | 433.92, 868 | AM650 | 12, статичний | `Faac TM` | `FAAC TM` | dip-перемикачі; Te зберігається із запису |
| Gate TX | 433.92 | AM650 | 64, статичний | `GateTX` | `Gate TX` | |
| Genius (KILO TX2/4 JLC, Amigo…) | 433.92, 868.35 | AM650 | 64, динамічний | `Faac SLH` | `Genius` | пакет FAAC SLH із ключем Genius, `Manufacture: Genius` |
| HCS101 | 433 | AM650 | 64, простий динамічний | `KeeLoq` | `KL: HCS101` | схожий на KeeLoq |
| Hormann | 868 | AM650 | 44, статичний | `Hormann HSM` | | |
| iDo | 433 | AM650 | 48, динамічний | `iDo 117/111` | | **лише декодування** (надіслати не можна) |
| Jarolift | 433.92 | AM650 | 72, динамічний | `Jarolift` | `Jarolift` | роллети, на базі KeeLoq |
| KingGates Stylo 4k | 433.92 | AM650 | 89, динамічний | `KingGates Stylo4k` | `KingGates Stylo4k` | на базі KeeLoq |
| Linear | 300 | AM650 | 10, статичний | `Linear` | `Linear` | |
| Linear Delta3 | 315 | AM650 | 8, статичний | `LinearDelta3` | | |
| Marantec | 433.92, 868 | AM650 | 49, статичний | `Marantec` | `Marantec` | |
| Marantec24 | 868 | AM650 | 24, статичний | `Marantec24` | `Marantec24` | |
| Mastercode | 433 | AM650 | 36, статичний | `Mastercode` | | |
| Megacode | 315 | AM650 | 24, статичний | `MegaCode` | | |
| Nero Radio | 434.42 | AM650 | 56, статичний | `Nero Radio` | | лише статичний режим, динамічний не підтримується |
| Nero Sketch | 433 | AM650 | 40, статичний | `Nero Sketch` | | |
| Nice Flo | 433.92 | AM650 | 12/24, статичний | `Nice FLO` | `Nice Flo 12bit`, `Nice Flo 24bit` | |
| Nice FloR-S | 433.92 | AM650 | 52, динамічний | `Nice FloR-S` | `Nice FloR-S` | режими лічильника |
| Nice One | 433.92 | AM650 | 72, динамічний | `Nice FloR-S` | `Nice One` | |
| Nice O-Code | 433.92 | AM650 | 52/72/112, динамічний | `Nice FloR-S` | `Nice O-Code`, `Nice O-Code One`, `Nice O-Code+Crt` | шифрується 16-бітним кодом інсталятора, див. [застосунок Nice O-Code](/ua/subghz/nice-o-code) |
| Nord ICE | 433.92 | AM650 | 33, статичний | `Nord ICE` | `Nord ICE` | |
| Prastel | 433.92, 868 | AM650 | 25, статичний | | | |
| Prastel | 433.92, 868 | AM650 | 42, динамічний | `Prastel` | `Prastel` | лінійне кодування CAME, перемішаний серійник + лічильник |
| Proteco MOVER (TX3) | 433.92 | AM650 | 24, статичний | `Proteco` | `Proteco` | |
| Revers RB2 (Реверс РБ-2(М)) | 433.92 | AM650 | 64, статичний | `Revers_RB2` | `Revers RB2` | |
| Roger | 433.92 | AM650 | 28, статичний | `Roger` | `Roger` | |
| Security+ 1.0 | 315, 433.92, 390 | AM650 | 42, динамічний | `Security+ 1.0` | `Security+1.0` | |
| Security+ 2.0 | 310, 315, 390, 868 | AM650 | 62, динамічний | `Security+ 2.0` | `Security+2.0` | |
| Security+ 2.0 Keypad | 315, 390, 868 | AM650 | 86, динамічний | `Security+ 2.0` | | PIN: [Security+ PIN](/ua/subghz/secplus-pin) |
| Somfy Keytis (KeyGo 4 RTS, Keytis NS 2RTS) | 433.42, 868 | AM650 | 80, динамічний | `Somfy Keytis` | `Somfy Keytis` | |
| Superrollo GW60 | 433.92 | AM650 | 67, динамічний (KeeLoq HCS361, CRC) | `KeeLoq` | `KL: Superrollo` | кнопки `0x3(0xA)` Up / `0x5(0xC)` Down / `0x7(0xE)` Stop |
| Telcoma/Cardin EDGE (EDGE2/4/20) | 433.92 | AM650 | 32, статичний | `Telcoma/Cardin EDGE` | `Telcoma EDGE` | преамбула `0xFF` + серійник + канал у коді «one-hot», ворота = Ch 0 |
| V2 Phoenix (Phox) | 433.92 | AM650 | 52, динамічний | `Phoenix_V2` | `V2 Phoenix` | у частини приймачів є статичний режим; режими лічильника |
| ZKTeco | 430.5 | AM650 | 24, статичний | `Princeton` | `ZKTeco` | кнопки `0x30` UP, `0x03` STOP, `0x0C` DOWN призначені на стрілки — [ZKTeco CMP200](/ua/subghz/zkteco-cmp200) |

## Датчики й розумний дім

| Система | Частота | Мод. | Біти / тип | Ім'я у файлі | Примітки |
|---|---|---|---|---|---|
| Dooya | 433, 315 | AM650 | 40, статичний | `Dooya` | електричні жалюзі, кастомні кнопки |
| Feron | 433.92 | AM650 | 32, статичний | `Feron` | пульти світлодіодних RGB-світильників; фільтр ignore «Sensors» |
| Honeywell | 315 | AM650 | 64, статичний | `Honeywell Sec` | датчики сигналізації |
| Honeywell WDB | 433, 315 | AM650 | 48, статичний | `Honeywell` | дверні дзвінки |
| Intertechno V3 | 433 | AM650 | 32, статичний | `Intertechno_V3` | світильники, розетки |
| Jarolift | 433.92 | AM650 | 72, динамічний | `Jarolift` | роллети |
| Legrand | 433 | AM650 | 18, статичний | `Legrand` | дверні дзвінки |
| Magellan | 433.92 | AM650 | 32, статичний | `Magellan` | датчики, сигналізації |
| Power Smart | 433 | AM650 | 64, статичний | `Power Smart` | жалюзі, роллети |
| Somfy Telis (RTS) | 433.42 | AM650 | 56, динамічний | `Somfy Telis` | Add Manually `Somfy Telis` → `433.42 AM650` |

## Сигналізації

| Система | Частота | Мод. | Біти / тип | Ім'я у файлі | Примітки |
|---|---|---|---|---|---|
| GangQi | 433.92 | AM650 | 34, статичний | `GangQi` | велосигналізації; фільтр ignore «Alarms» |
| Hollarm | 433.92 | AM650 | 42, статичний | `Hollarm` | велосигналізації; фільтр ignore «Alarms» |

## Універсальні / безбрендові пульти

| Система | Частота | Мод. | Біти / тип | Ім'я у файлі | Примітки |
|---|---|---|---|---|---|
| Doorbell32 | 433.92 | AM650 | 32, статичний | `Doorbell32` | PWM 1:3 у стилі Princeton, guard 14·Te |
| Freezer | 433.92 | AM650 | 24, статичний | `Freezer` | є в реєстрі; в офіційному переліку ще немає |
| Hay21 | 433.92 | AM650 | 21, динамічний | `Hay21` | |
| Holtek | 433/868/315 | AM650 | 40, статичний | `Holtek` | |
| Holtek HT12X | 433/868/315 | AM650/FM | 12, статичний | `Holtek_HT12X` | |
| KeyFinder | 433.92 | AM650 | 24, статичний | `KeyFinder` | брелоки-шукачі ключів |
| KeyFinder2 | 433.92 | AM650 | 11, статичний | `KeyFinder2` | btn(3)+10011+btn(3), без серійника |
| Princeton (PT2262…) | 315, 433.92, будь-яка | AM650 | 24, статичний | `Princeton` | має власний фільтр «Ignore Princeton» |
| SMC5326 | 315, 433.92, будь-яка | AM650 | 25, статичний | `SMC5326` | |
| Treadmill37 (QH-433) | 433.92 | AM650 | 37, статичний | `Treadmill37` | |

## Не протокол: RAW і BinRAW

- **RAW** (`Protocol: RAW`) — сирі тривалості, записані через [Read RAW](/ua/subghz/read-raw); відтворює
  будь-що, не декодує нічого.
- **BinRAW** (`Protocol: BinRAW`) — із `Read → Config → Bin RAW: ON` невідомий, але повторюваний статичний сигнал
  зберігається як очищена послідовність бітів із відновленим Te. Може емулювати майже будь-який статичний
  протокол, якого Flipper не знає.

## Виробники KeeLoq

Усі декодуються як `Protocol: KeeLoq` із полем `Manufacture:` і показуються як `KL: <назва>`. Якщо не зазначено
інакше, навчання «simple» із 10-бітною частиною серійника в hop. Докладніше про KeeLoq:
[KeeLoq](/ua/subghz/keeloq).

### Ворота й гаражі

| Виробник | Частота / мод. | Навчання / примітки |
|---|---|---|
| AERF Collbaix, Hy dom, Medva, Motorgate, Otros, Sabutom, Temp, VDS | | особливе навчання, 10-бітний серійник у hop |
| Allmatic | 868, AM650 | серійника в hop немає — magic XOR |
| Aprimatic | 433.92, AM650 | 12-бітний серійник у hop + 2-бітна «парність» |
| ATA PTX4 | | normal, 12 бітів |
| Beninca | 433.92, 868, AM650 | серійника в hop немає — magic XOR |
| CAME Space | 433.92, AM650 | simple, 12 бітів |
| Cardin S449 | 433.92, **FM12K** | normal, 12 бітів (оригінали) / 10 бітів (китайські) |
| Centurion | 433.92, AM650 | normal, замість серійника фіксоване значення `0x1CE` |
| Clemsa Mutancode | | normal, 12 бітів |
| Comunello | 433.92, 868, AM650 | normal |
| DEA Mio | 433.92, AM650 | simple, змінений серійник (`419` → `C19`) |
| DoorHan | 315, 433.92, AM650 | |
| Doormatic | | normal |
| DTM Neo | 433.92, AM650 | simple, 12 бітів |
| Elmes Poland | 303, 433.92, AM650 | normal |
| Elvox | | normal |
| Erreka | 433.92, 868.35, AM650 | secure із seed, 8-бітний серійник |
| ET Blue, ET Blue Mix | | normal, 10 бітів |
| FAAC FIX | 433.92, AM650 | normal, 10 бітів; 12-бітний дискримінатор зберігається в `Seed`, як у Phantom / Hiland |
| FAAC RC, XT | 433.92, 868, AM650 | normal, 12 бітів |
| Fadini | | simple, 12 бітів |
| Genius Bravo (ECHO, Bravo) | 433.92, AM650 | normal, 12 бітів; `0xB` = програмування |
| Gibidi | 433.92, AM650 | |
| GSN | 433.92, AM650 | normal, 12 бітів |
| HomeGate | 433.92, AM650 | |
| Hormann EcoStar | 433.92, AM650 | normal |
| IronLogic IL-100, IL-100 Smart PPult | 433.92, AM650 | |
| JCM Tech | 433.92, AM650 | simple, 8 бітів |
| JCM Tech Gen2 | | особливе; один вхідний байт у пакеті не передається — підбирається перебором і показується як `Seed` |
| JCM1G (Antonio Meca, Baleato, Cas, Cubells, Cyacsa, DMIL, EMFA, Forsa, Gandara, Gibidi, Gibidi2, Hy dom, Hybrid, Norton, Nueva Castilla, Puertas Lorenzo, Pujol, Serviparking, Tech, Zibor) | | simple, 8 бітів |
| Jolly Motors | 433.92, AM650 | |
| KEY | 433.92, AM650 | simple, фіксоване значення `0x2FF` |
| Mc Garcia | | simple, 10 бітів |
| Mhouse | 433.92, AM650 | simple, 8 бітів |
| Monarch | 433.92, AM650 | normal, фіксоване `0x100` або `0x280` (Dorcas 22366CLN використовує `0x280`) |
| Motorline | 433.92, AM650 | normal |
| Nice Smilo | 433.92, AM650 | simple, 8 бітів |
| Normstahl | 433.92, AM650 | |
| Novoferm | 433.92, AM650 | |
| Phantom / Hiland | 433.92, AM650 | HCS300, normal, 10 бітів; 12-бітний дискримінатор зберігається в `Seed` |
| Pujol (Vario 4…) | 433.92, AM650 | особливе, 8 бітів |
| Pujol Vario (старіші) | 433.92, AM650 | simple, 8 бітів |
| SEA | | simple |
| Seav | | normal, 12 бітів |
| Sommer (TX03-868-4, Pearl, SOMloq) | 434.42, 868.80, FM12K або FM476 | normal |
| Stagnoli | | особливе |
| Steelmate | 433.92, AM650 | normal, 12 бітів |
| Stilmatic (R-Tech) | 433.92, AM650 | normal, 12 бітів |
| Telcoma | | табличне навчання |
| Verex | | normal |
| Wisniowski | 433.92, AM650 | normal, 12 бітів |
| Wisniowski 1 ByteReversed, Wisniowski 2 | | normal |

### Сигналізації та інше

Alligator, Alligator S-275, APS-1100/APS-2550, Cenmax, Cenmax St-5, Cenmax St-7, Faraon, FFFF Normal, FFFF Simple,
Guard RF-311A (normal), Harpoon, KGB/Subaru (magic serial type 1), Leopard, Magic 1 / Magic 2 (magic serial type 2),
Magic 3 / Magic 4 (magic serial type 3), Merlin (простий XOR, серійника в hop немає), Miserere (normal), Mongoose
(normal), Pantera, Pantera CLK, Pantera XS/Jaguar, Partisan RX, Pecinin (simple, 12 бітів), Reff, Rosh (simple,
12 бітів), Rossi (simple, 12 бітів), Sheriff, SL A2-A4, SL A6-A9/Tomahawk 9010, SL B6,B9 dop, Teco, Tomahawk
TZ-9030, Tomahawk Z,X 3-5, Zero Normal, Zero Simple, ZX-730-750-1055.

## Мого пульта в переліку немає

1. Знайдіть частоту через [Frequency Analyzer](/ua/subghz/frequency-analyzer), а потім спробуйте
   [Read](/ua/subghz/read) з кожною модуляцією (`AM650`, `FM238`, `FM476`, `FM12K`), утримуючи кнопку ≥ 2 с.
2. Для статичних пультів спробуйте `Bin RAW: ON`.
3. Усе одно нічого? Запишіть файли через [Read RAW](/ua/subghz/read-raw) (порог RSSI `-----`, по одному на
   модуляцію; натисніть одну кнопку 5× з утриманням 1–2 с, потім 5× з утриманням 5 с), сфотографуйте пульт (також
   розібраний) і створіть issue в репозиторії Unleashed із цими файлами.

## Пов'язані сторінки

- [Add Manually](/ua/subghz/add-manually) · [KeeLoq](/ua/subghz/keeloq) · [Динамічні коди](/ua/subghz/rolling-codes)
- [Read](/ua/subghz/read) · [Read RAW](/ua/subghz/read-raw) · [Програмування пульта](/ua/subghz/remote-prog)
