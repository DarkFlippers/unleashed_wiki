---
title: Поддерживаемые системы
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [unleashed-docs, unleashed-readme, unleashed-src]
---
# Поддерживаемые системы

Все протоколы Sub-GHz, которые приложение `Sub-GHz` в **Unleashed** умеет декодировать, сохранять и (в основном)
отправлять. Список собран по реестру протоколов в `lib/subghz/protocols/` и документации Unleashed. У приложений
вроде *Weather Station* или [Remote Analyzer](/ru/subghz/remote-analyzer) свои дополнительные списки протоколов.

::: tip Unleashed
Unleashed — форк, поэтому он декодирует всё, что и официальная прошивка: 38 из 64 декодеров протоколов, на
которых построены эти таблицы, — из OFW, и большинство их написал Skorp. Поверх них добавлены BelKorn, Beninca ARC,
Ditec GOL4, Jarolift, Nice O-Code, Telcoma EDGE, Treadmill37, Freezer и другие, более 100 производителей KeeLoq и
возможность **отправлять** динамические протоколы, с [кастомными кнопками](/ru/subghz/rolling-codes#кастомные-кнопки)
и созданием через [Add Manually](/ru/subghz/add-manually).
:::

## Как читать таблицы

- **433 МГц** обычно означает `433.92 МГц`, **868 МГц** — `868.35 МГц`. Частота не указана — пока неизвестна.
- **Мод.** — что выставить в `Read → Config → Modulation`: `AM650`, `AM270`, `FM238`, `FM476`, `FM12K`.
  «FM» — пробуйте все FM-пресеты; `FSK12K` в документации производителей = `FM12K` на Флиппере.
- **Статический** — фиксированный код, копия работает вместе с оригиналом. **Динамический** — rolling code, см.
  [Динамические коды](/ru/subghz/rolling-codes).
- **Имя в файле** — значение `Protocol:` в `.sub`-файле ([формат](/ru/subghz/file-format)).
- **Add Manually** — пункт в `Sub-GHz → Add Manually`, если есть.

## Ворота, гаражи, шлагбаумы, роллеты

| Система | Частота | Мод. | Бит / тип | Имя в файле | Add Manually | Примечание |
|---|---|---|---|---|---|---|
| Airforce | 433.92, 868 | AM650 | 18, статический | | | |
| Allstar Firefly 318ALD31K | 318 | AM650 | 18, статический | `Allstar Firefly` | | |
| Alutech AT-4N | 433.92 | AM650 | 72, динамический | `Alutech AT-4N` | `Alutech AT4N`, `Alutech AT4L` | кастомные кнопки, [режимы счётчика](/ru/subghz/counter-mode) |
| AN-Motors (Alutech) AT4 | 433.92 | AM650 | 64, псевдодинамический | `KeeLoq` | `AN-Motors AT4` | на базе KeeLoq |
| Ansonic | 433 | FM | 12, статический | `Ansonic` | | |
| BelKorn (Korn, BelGate, Furniteh, Euro5…) | 433.92 | AM650 | 118, динамический | `BelKorn` | `BelKorn` | не зашифрован: 36-битный серийник + открытый счётчик; поля производителя нет, все пульты читаются как BelKorn |
| Beninca ARC (TO.GO 2VA) | 433.92 | AM650 | 128, динамический AES-128 | `Beninca ARC` | `Beninca ARC` | кнопка `0` = скрытая кнопка |
| BETT | 433.92 | AM650 | 18, статический | `BETT` | `BETT` | |
| BFT Mitto | 433.92 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `BFT Mitto` | у новых seed вычисляется из серийника (читаются в Read); старым нужен seed — режим программирования или [Seed Capturer](/ru/subghz/seed-capturer); кнопка `0xF` = режим программирования |
| CAME | 433.92, 868 | AM650 | 12/24, статический | `CAME` | `CAME 12bit`, `CAME 24bit` | |
| CAME Atomo (TOPD4REN, TOP44RBN, TOP42R, TOP44R) | 433.92, 868 | AM650 | 62, динамический | `CAME Atomo` | `CAME Atomo` | держите Send ≥ 2 с |
| CAME TWEE (+ TOP44FGN, "New Fixed Code") | 433.92 | AM650 | 54, псевдодинамический | `CAME TWEE` | `CAME TWEE` | |
| Chamberlain Code | 315 | AM650 | 10, статический | `Cham_Code` | | |
| Clemsa | 433 | AM650 | 18, статический | `Clemsa` | | |
| Dickert MAHS | 433 | AM650 | 36, статический | `Dickert_MAHS` | | |
| Ditec GOL4 (BIXLG4, BIXLS2, BIXLP2) | 433.92 | AM650 | 54, динамический | `Ditec GOL4` | `Ditec GOL4` | → = кнопка `0` (скрытая) |
| Doitrand | 433 | AM650 | 37 | `Doitrand` | | в документации — динамический, в прошивке зарегистрирован как статический |
| Elplast / P-11B / 3BK / E.C.A | 433 | AM650 | 18, статический | `Elplast` | | |
| Erreka IRIS (IR02/IR04) | 433.92, 868.35 | AM650 | 64, KeeLoq + seed | `KeeLoq` | `Erreka` | нужен seed; `0xF` = режим программирования, передаёт seed открыто |
| FAAC SLH | 433.92, 868.35 | AM650 | 64, динамический | `Faac SLH` | `FAAC SLH` | seed разный для каждой кнопки |
| FAAC TM (TM 433/868 DS) | 433.92, 868 | AM650 | 12, статический | `Faac TM` | `FAAC TM` | DIP-переключатели; Te берётся из захвата |
| Gate TX | 433.92 | AM650 | 64, статический | `GateTX` | `Gate TX` | |
| Genius (KILO TX2/4 JLC, Amigo…) | 433.92, 868.35 | AM650 | 64, динамический | `Faac SLH` | `Genius` | пакет FAAC SLH с ключом Genius, `Manufacture: Genius` |
| HCS101 | 433 | AM650 | 64, простой динамический | `KeeLoq` | `KL: HCS101` | KeeLoq-подобный |
| Hormann | 868 | AM650 | 44, статический | `Hormann HSM` | | |
| iDo | 433 | AM650 | 48, динамический | `iDo 117/111` | | **только декодирование** (отправить нельзя) |
| Jarolift | 433.92 | AM650 | 72, динамический | `Jarolift` | `Jarolift` | роллеты, на базе KeeLoq |
| KingGates Stylo 4k | 433.92 | AM650 | 89, динамический | `KingGates Stylo4k` | `KingGates Stylo4k` | на базе KeeLoq |
| Linear | 300 | AM650 | 10, статический | `Linear` | `Linear` | |
| Linear Delta3 | 315 | AM650 | 8, статический | `LinearDelta3` | | |
| Marantec | 433.92, 868 | AM650 | 49, статический | `Marantec` | `Marantec` | |
| Marantec24 | 868 | AM650 | 24, статический | `Marantec24` | `Marantec24` | |
| Mastercode | 433 | AM650 | 36, статический | `Mastercode` | | |
| Megacode | 315 | AM650 | 24, статический | `MegaCode` | | |
| Nero Radio | 434.42 | AM650 | 56, статический | `Nero Radio` | | только статический режим, динамический не поддерживается |
| Nero Sketch | 433 | AM650 | 40, статический | `Nero Sketch` | | |
| Nice Flo | 433.92 | AM650 | 12/24, статический | `Nice FLO` | `Nice Flo 12bit`, `Nice Flo 24bit` | |
| Nice FloR-S | 433.92 | AM650 | 52, динамический | `Nice FloR-S` | `Nice FloR-S` | режимы счётчика |
| Nice One | 433.92 | AM650 | 72, динамический | `Nice FloR-S` | `Nice One` | |
| Nice O-Code | 433.92 | AM650 | 52/72/112, динамический | `Nice FloR-S` | `Nice O-Code`, `Nice O-Code One`, `Nice O-Code+Crt` | ключ — 16-битный код инсталлятора, см. [приложение Nice O-Code](/ru/subghz/nice-o-code) |
| Nord ICE | 433.92 | AM650 | 33, статический | `Nord ICE` | `Nord ICE` | |
| Prastel | 433.92, 868 | AM650 | 25, статический | | | |
| Prastel | 433.92, 868 | AM650 | 42, динамический | `Prastel` | `Prastel` | линейное кодирование CAME, перемешанные серийник + счётчик |
| Proteco MOVER (TX3) | 433.92 | AM650 | 24, статический | `Proteco` | `Proteco` | |
| Revers RB2 (Реверс РБ-2(М)) | 433.92 | AM650 | 64, статический | `Revers_RB2` | `Revers RB2` | |
| Roger | 433.92 | AM650 | 28, статический | `Roger` | `Roger` | |
| Security+ 1.0 | 315, 433.92, 390 | AM650 | 42, динамический | `Security+ 1.0` | `Security+1.0` | |
| Security+ 2.0 | 310, 315, 390, 868 | AM650 | 62, динамический | `Security+ 2.0` | `Security+2.0` | |
| Security+ 2.0 Keypad | 315, 390, 868 | AM650 | 86, динамический | `Security+ 2.0` | | PIN: [Security+ PIN](/ru/subghz/secplus-pin) |
| Somfy Keytis (KeyGo 4 RTS, Keytis NS 2RTS) | 433.42, 868 | AM650 | 80, динамический | `Somfy Keytis` | `Somfy Keytis` | |
| Superrollo GW60 | 433.92 | AM650 | 67, динамический (KeeLoq HCS361, CRC) | `KeeLoq` | `KL: Superrollo` | кнопки `0x3(0xA)` Up / `0x5(0xC)` Down / `0x7(0xE)` Stop |
| Telcoma/Cardin EDGE (EDGE2/4/20) | 433.92 | AM650 | 32, статический | `Telcoma/Cardin EDGE` | `Telcoma EDGE` | преамбула `0xFF` + серийник + one-hot канал, ворота = Ch 0 |
| V2 Phoenix (Phox) | 433.92 | AM650 | 52, динамический | `Phoenix_V2` | `V2 Phoenix` | у части приёмников есть режим Static; режимы счётчика |
| ZKTeco | 430.5 | AM650 | 24, статический | `Princeton` | `ZKTeco` | кнопки `0x30` UP, `0x03` STOP, `0x0C` DOWN на стрелках — [ZKTeco CMP200](/ru/subghz/zkteco-cmp200) |

## Датчики и умный дом

| Система | Частота | Мод. | Бит / тип | Имя в файле | Примечание |
|---|---|---|---|---|---|
| Dooya | 433, 315 | AM650 | 40, статический | `Dooya` | электрожалюзи, кастомные кнопки |
| Feron | 433.92 | AM650 | 32, статический | `Feron` | пульты RGB-лент; фильтр «Sensors» |
| Honeywell | 315 | AM650 | 64, статический | `Honeywell Sec` | охранные датчики |
| Honeywell WDB | 433, 315 | AM650 | 48, статический | `Honeywell` | дверные звонки |
| Intertechno V3 | 433 | AM650 | 32, статический | `Intertechno_V3` | свет, розетки |
| Jarolift | 433.92 | AM650 | 72, динамический | `Jarolift` | роллеты |
| Legrand | 433 | AM650 | 18, статический | `Legrand` | дверные звонки |
| Magellan | 433.92 | AM650 | 32, статический | `Magellan` | датчики, сигнализации |
| Power Smart | 433 | AM650 | 64, статический | `Power Smart` | жалюзи, роллеты |
| Somfy Telis (RTS) | 433.42 | AM650 | 56, динамический | `Somfy Telis` | Add Manually `Somfy Telis` → `433.42 AM650` |

## Сигнализации

| Система | Частота | Мод. | Бит / тип | Имя в файле | Примечание |
|---|---|---|---|---|---|
| GangQi | 433.92 | AM650 | 34, статический | `GangQi` | мотосигнализации; фильтр «Alarms» |
| Hollarm | 433.92 | AM650 | 42, статический | `Hollarm` | мотосигнализации; фильтр «Alarms» |

## Универсальные / безымянные пульты

| Система | Частота | Мод. | Бит / тип | Имя в файле | Примечание |
|---|---|---|---|---|---|
| Doorbell32 | 433.92 | AM650 | 32, статический | `Doorbell32` | ШИМ 1:3 как у Princeton, пауза 14·Te |
| Freezer | 433.92 | AM650 | 24, статический | `Freezer` | есть в реестре; в официальном списке пока нет |
| Hay21 | 433.92 | AM650 | 21, динамический | `Hay21` | |
| Holtek | 433/868/315 | AM650 | 40, статический | `Holtek` | |
| Holtek HT12X | 433/868/315 | AM650/FM | 12, статический | `Holtek_HT12X` | |
| KeyFinder | 433.92 | AM650 | 24, статический | `KeyFinder` | брелоки-искалки ключей |
| KeyFinder2 | 433.92 | AM650 | 11, статический | `KeyFinder2` | btn(3)+10011+btn(3), без серийника |
| Princeton (PT2262…) | 315, 433.92, любая | AM650 | 24, статический | `Princeton` | свой фильтр «Ignore Princeton» |
| SMC5326 | 315, 433.92, любая | AM650 | 25, статический | `SMC5326` | |
| Treadmill37 (QH-433) | 433.92 | AM650 | 37, статический | `Treadmill37` | |

## Не протоколы: RAW и BinRAW

- **RAW** (`Protocol: RAW`) — «сырые» тайминги, записанные через [Read RAW](/ru/subghz/read-raw); повторяет что
  угодно, ничего не декодирует.
- **BinRAW** (`Protocol: BinRAW`) — при `Read → Config → Bin RAW: ON` неизвестный, но повторяющийся статический
  сигнал сохраняется как очищенная битовая последовательность с восстановленным Te. Так можно повторить почти
  любой статический протокол, даже неизвестный Флипперу.

## Производители KeeLoq

Все декодируются как `Protocol: KeeLoq` с полем `Manufacture:` и отображаются как `KL: <имя>`. Если не указано
иное — learning «simple» с 10-битной частью серийника в hop. Подробнее: [KeeLoq](/ru/subghz/keeloq).

### Ворота и гаражи

| Производитель | Частота / мод. | Learning / примечание |
|---|---|---|
| AERF Collbaix, Hy dom, Medva, Motorgate, Otros, Sabutom, Temp, VDS | | special, 10-битный серийник в hop |
| Allmatic | 868, AM650 | без серийника в hop — magic XOR |
| Aprimatic | 433.92, AM650 | 12-битный серийник в hop + 2 бита «чётности» |
| ATA PTX4 | | normal, 12 бит |
| Beninca | 433.92, 868, AM650 | без серийника в hop — magic XOR |
| CAME Space | 433.92, AM650 | simple, 12 бит |
| Cardin S449 | 433.92, **FM12K** | normal, 12 бит (оригиналы) / 10-bit (китайские) |
| Centurion | 433.92, AM650 | normal, фиксированное `0x1CE` вместо серийника |
| Clemsa Mutancode | | normal, 12 бит |
| Comunello | 433.92, 868, AM650 | normal |
| DEA Mio | 433.92, AM650 | simple, изменённый серийник (`419` → `C19`) |
| DoorHan | 315, 433.92, AM650 | |
| Doormatic | | normal |
| DTM Neo | 433.92, AM650 | simple, 12 бит |
| Elmes Poland | 303, 433.92, AM650 | normal |
| Elvox | | normal |
| Erreka | 433.92, 868.35, AM650 | secure с seed, 8-битный серийник |
| ET Blue, ET Blue Mix | | normal, 10 бит |
| FAAC FIX | 433.92, AM650 | normal, 10 бит; 12-битный дискриминатор хранится в `Seed`, как у Phantom / Hiland |
| FAAC RC, XT | 433.92, 868, AM650 | normal, 12 бит |
| Fadini | | simple, 12 бит |
| Genius Bravo (ECHO, Bravo) | 433.92, AM650 | normal, 12 бит; `0xB` = программирование |
| Gibidi | 433.92, AM650 | |
| GSN | 433.92, AM650 | normal, 12 бит |
| HomeGate | 433.92, AM650 | |
| Hormann EcoStar | 433.92, AM650 | normal |
| IronLogic IL-100, IL-100 Smart PPult | 433.92, AM650 | |
| JCM Tech | 433.92, AM650 | simple, 8 бит |
| JCM Tech Gen2 | | special; один входной байт не передаётся — подбирается перебором, показывается как `Seed` |
| JCM1G (Antonio Meca, Baleato, Cas, Cubells, Cyacsa, DMIL, EMFA, Forsa, Gandara, Gibidi, Gibidi2, Hy dom, Hybrid, Norton, Nueva Castilla, Puertas Lorenzo, Pujol, Serviparking, Tech, Zibor) | | simple, 8 бит |
| Jolly Motors | 433.92, AM650 | |
| KEY | 433.92, AM650 | simple, фиксированное `0x2FF` |
| Mc Garcia | | simple, 10 бит |
| Mhouse | 433.92, AM650 | simple, 8 бит |
| Monarch | 433.92, AM650 | normal, фиксированное `0x100` или `0x280` (Dorcas 22366CLN — `0x280`) |
| Motorline | 433.92, AM650 | normal |
| Nice Smilo | 433.92, AM650 | simple, 8 бит |
| Normstahl | 433.92, AM650 | |
| Novoferm | 433.92, AM650 | |
| Phantom / Hiland | 433.92, AM650 | HCS300, normal, 10 бит; 12-битный дискриминатор хранится в `Seed` |
| Pujol (Vario 4…) | 433.92, AM650 | special, 8 бит |
| Pujol Vario (старые) | 433.92, AM650 | simple, 8 бит |
| SEA | | simple |
| Seav | | normal, 12 бит |
| Sommer (TX03-868-4, Pearl, SOMloq) | 434.42, 868.80, FM12K или FM476 | normal |
| Stagnoli | | special |
| Steelmate | 433.92, AM650 | normal, 12 бит |
| Stilmatic (R-Tech) | 433.92, AM650 | normal, 12 бит |
| Telcoma | | табличный learning |
| Verex | | normal |
| Wisniowski | 433.92, AM650 | normal, 12 бит |
| Wisniowski 1 ByteReversed, Wisniowski 2 | | normal |

### Сигнализации и прочие

Alligator, Alligator S-275, APS-1100/APS-2550, Cenmax, Cenmax St-5, Cenmax St-7, Faraon, FFFF Normal, FFFF Simple,
Guard RF-311A (normal), Harpoon, KGB/Subaru (magic serial тип 1), Leopard, Magic 1 / Magic 2 (magic serial тип 2),
Magic 3 / Magic 4 (magic serial тип 3), Merlin (simple XOR, без серийника в hop), Miserere (normal), Mongoose
(normal), Pantera, Pantera CLK, Pantera XS/Jaguar, Partisan RX, Pecinin (simple, 12 бит), Reff, Rosh (simple,
12-bit), Rossi (simple, 12 бит), Sheriff, SL A2-A4, SL A6-A9/Tomahawk 9010, SL B6,B9 dop, Teco, Tomahawk TZ-9030,
Tomahawk Z,X 3-5, Zero Normal, Zero Simple, ZX-730-750-1055.

## Моего пульта нет в списке

1. Определите частоту [анализатором частот](/ru/subghz/frequency-analyzer), затем попробуйте [Read](/ru/subghz/read)
   со всеми модуляциями (`AM650`, `FM238`, `FM476`, `FM12K`), удерживая кнопку ≥ 2 с.
2. Для статических пультов попробуйте `Bin RAW: ON`.
3. Всё равно ничего? Запишите [Read RAW](/ru/subghz/read-raw) (RSSI Threshold `-----`, по файлу на каждую модуляцию;
   нажмите одну кнопку 5 раз, удерживая 1–2 с, затем 5 раз по 5 с), сфотографируйте пульт (и в разобранном виде) и
   создайте issue в репозитории Unleashed, приложив файлы.

## См. также

- [Add Manually](/ru/subghz/add-manually) · [KeeLoq](/ru/subghz/keeloq) · [Динамические коды](/ru/subghz/rolling-codes)
- [Read](/ru/subghz/read) · [Read RAW](/ru/subghz/read-raw) · [Привязка пультов](/ru/subghz/remote-prog)
