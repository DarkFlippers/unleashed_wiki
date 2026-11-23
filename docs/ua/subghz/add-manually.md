---
title: Add Manually
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Add Manually

**Add Manually** створює цілком новий віртуальний пульт і зберігає його у файл `.sub`. Оригінальний пульт для
цього не потрібен: Flipper генерує випадковий серійний номер (а також лічильник, seed тощо — там, де вони
потрібні протоколу). Новий пульт далі можна **прописати в приймач** як додатковий, так само, як ви прописували б
запасний пульт, куплений у крамниці.

**Add Manually [Advanced]** робить те саме, але просить вас самостійно ввести кожне значення в
шістнадцятковому вигляді, замість того щоб генерувати його.

::: tip Unleashed
У стоковій прошивці в Add Manually є лише кілька статичних протоколів. Unleashed показує **понад 100 систем**,
включно з динамічними (виробники KeeLoq, FAAC SLH, BFT Mitto, Nice FloR-S / O-Code, CAME Atomo, Somfy,
Security+ 2.0, …), дає вибрати для кожної з них будь-який із 15 діапазонів частота/модуляція й додає запис
**[Advanced]**.
:::

## Коли це знадобиться

| Ситуація | Що робити |
|---|---|
| У вас **статичний** пульт (фіксований код) і потрібна просто копія | [Read](/ua/subghz/read) і збереження — Add Manually не потрібен |
| У вас пульт із **динамічним кодом** і ви хочете, щоб Flipper працював *разом* із ним | **Add Manually** → прописати новий пульт у приймач ([як саме](/ua/subghz/remote-prog)) |
| Потрібен пульт із відомими значеннями (відновлений seed, код інсталятора, конкретний серійник) | **Add Manually [Advanced]** |
| Ви втратили оригінальний статичний пульт, але знаєте його dip-перемикачі / код | **Add Manually [Advanced]** із введеним ключем |

Чому не просто клонувати пульт із динамічним кодом? Див. [Динамічні коди](/ua/subghz/rolling-codes): клон і
оригінал конфліктують через лічильник.

## Створення пульта

1. `Main Menu → Sub-GHz → Add Manually`.
2. Прокрутіть перелік і виберіть систему — наприклад, `BFT Mitto` чи `KL: DoorHan`. Записи, що починаються з
   `KL:`, — це виробники KeeLoq.

   ![Add Manually: алфавітний перелік систем із вибраним KL: Allmatic](/screens/subghz/add_manually.png)

3. Відкриється **вибір діапазону** з назвою системи в заголовку. Діапазони підписані як
   `частота модуляція` — наприклад, `433.92 AM650`. Першим іде власний типовий діапазон системи, далі інші
   діапазони, на яких ця система зустрічається, а потім усі решта (для інсталяцій на незвичній частоті).
   Натисніть <kbd>OK</kbd> на потрібному діапазоні.
4. Введіть ім'я файла (одне пропонується) і підтвердьте.
5. Пульт зберігається в `/ext/subghz/` і з'являється в `Sub-GHz → Saved`.

   ![Меню збереженого сигналу: Emulate, Rename, Delete, Signal Settings](/screens/subghz/saved_menu.png)

6. Відкрийте його: `Sub-GHz → Saved → <ваш файл> → Emulate`. Утримуйте <kbd>OK</kbd> (`Send`), щоб передати; у
   протоколах із [кастомними кнопками](/ua/subghz/rolling-codes#custom-buttons) стрілки надсилають інші кнопки.

   ![Екран передавання збереженого сигналу з R: Int і кнопкою Send](/screens/subghz/emulate.png)


Нічого не передається, доки ви не відкриєте файл і не натиснете кнопку.

::: warning Застарілі назви
У старіших посібниках (включно зі старішими версіями `SubGHzRemoteProg.md`) записи названі на кшталт
`BFT Mitto 433MHz` або `KL: DoorHan 315MHz`. Актуальна прошивка розбиває це на два кроки: система
(`BFT Mitto`) → діапазон (`433.92 AM650`).
:::

### 15 діапазонів

Усі вони пропонуються для кожної системи:

`433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`,
`868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`,
`430.50 AM650`.

## Add Manually [Advanced]

`Main Menu → Sub-GHz → Add Manually [Advanced]` → система → діапазон, а далі серія екранів введення
шістнадцяткових значень. Які саме екрани ви побачите, залежить від родини протоколу:

| Родина | Екрани (у порядку появи) |
|---|---|
| Статичні протоколи (Princeton, CAME, Nice Flo, …) | `Enter KEY in hex`; протоколи, які зберігають тривалість, запитують також `Enter TE in us` (і `Enter GT in TE`) |
| KeeLoq (записи `KL:`, AN-Motors AT4) | `SERIAL` → `BUTTON` → `COUNTER` |
| KeeLoq із seed (BFT Mitto, Erreka) | `SERIAL` → `BUTTON` → `COUNTER` → `SEED` |
| `KL: FAAC FIX`, `KL: Monarch`, `KL:Phantom(Hiland)`, `KL: DEA Mio` | `SERIAL` → `BUTTON` → `COUNTER` → `DISC.` (дискримінатор hop, зберігається в полі `Seed`) |
| FAAC SLH, Genius | `SERIAL` → `BUTTON` → `COUNTER` (32 біти) → `SEED` |
| CAME Atomo, V2 Phoenix | `SERIAL` → `COUNTER` |
| Alutech AT4N, Somfy Telis/Keytis, KingGates, Beninca ARC, Jarolift, Ditec GOL4, Prastel, BelKorn, Security+2.0 | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice FloR-S, Nice One | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice O-Code, Nice O-Code One | `SERIAL` → `BUTTON` → `COUNTER` → `IC` (код інсталятора) |
| Nice O-Code+Crt | `SERIAL` → `BUTTON` → `COUNTER` → `IC` → `CERT` (запитується навіть у звичайному Add Manually) |
| Security+1.0 | вводити нічого не потрібно, генерується напряму |

Значення вводяться у шістнадцятковому вигляді, старшим байтом уперед. `BUTTON` і `SERIAL` разом утворюють `Fix`,
який ви бачите після [Read](/ua/subghz/read): у KeeLoq кнопка — це **перша** шістнадцяткова цифра `Fix`
(серійник = `Fix`, у якому цю цифру замінено на `0`), а у FAAC SLH / Genius — **остання** цифра.

::: tip Побайтове введення
Побайтове введення в Unleashed має мініредактор півбайтів: натискайте <kbd>↑</kbd>, доки він не з'явиться.
:::

## Усі записи переліку

Порядок і підписи точно такі, як у меню прошивки. «Типовий» — це діапазон, який стоїть першим; «Також» — це
альтернативні діапазони системи, які перелічені одразу після нього.

| Запис меню | Типовий | Також | Тип |
|---|---|---|---|
| `KL: Allmatic` | 433.92 AM650 | 868.35 AM650 | KeeLoq (ключ Beninca) |
| `Alutech AT4N` | 433.92 AM650 | | динамічний (Alutech AT-4N) |
| `AN-Motors AT4` | 433.92 AM650 | | KeeLoq |
| `KL: Aprimatic` | 433.92 AM650 | | KeeLoq |
| `KL: ATA PTX4` | 433.92 AM650 | | KeeLoq |
| `BelKorn` | 433.92 AM650 | | динамічний (простий лічильник) |
| `KL: Beninca` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `Beninca ARC` | 433.92 AM650 | | динамічний (AES-128) |
| `BETT` | 433.92 AM650 | | статичний |
| `BFT Mitto` | 433.92 AM650 | | KeeLoq + Seed |
| `CAME 12bit` | 433.92 AM650 | 868.35 AM650 | статичний |
| `CAME 24bit` | 433.92 AM650 | 868.35 AM650 | статичний |
| `CAME Atomo` | 433.92 AM650 | 868.35 AM650 | динамічний |
| `KL: CAME Space` | 433.92 AM650 | | KeeLoq |
| `CAME TWEE` | 433.92 AM650 | | статичний (псевдодинамічний) |
| `KL: Cardin S449` | **433.92 FM12K** | | KeeLoq |
| `KL: Centurion` | 433.92 AM650 | | KeeLoq |
| `KL: Clm.Mutancode` | 433.92 AM650 | | KeeLoq (Clemsa Mutancode) |
| `KL: Comunello` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `KL: DEA Mio` | 433.92 AM650 | | KeeLoq + дискримінатор |
| `Ditec GOL4` | 433.92 AM650 | | динамічний |
| `KL: DoorHan` | 433.92 AM650 | 315.00 AM650 | KeeLoq |
| `KL: Doormatic` | 433.92 AM650 | | KeeLoq |
| `KL: DTM Neo` | 433.92 AM650 | | KeeLoq |
| `KL: Elmes (PL)` | 433.92 AM650 | | KeeLoq |
| `KL: Elvox` | 433.92 AM650 | | KeeLoq |
| `Erreka` | 433.92 AM650 | 868.35 AM650 | KeeLoq + Seed |
| `KL: ET Blue` | 433.92 AM650 | | KeeLoq |
| `KL: ET Blue Mix` | 433.92 AM650 | | KeeLoq |
| `KL: FAAC FIX` | 433.92 AM650 | | KeeLoq + дискримінатор |
| `KL: FAAC RC,XT` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `FAAC SLH` | 433.92 AM650 | 868.35 AM650 | FAAC SLH + Seed |
| `FAAC TM` | 433.92 AM650 | 868.35 AM650 | статичний (12 dip-перемикачів) |
| `KL: Fadini` | 433.92 AM650 | | KeeLoq |
| `GangQi` | 433.92 AM650 | | статичний (велосигналізація) |
| `Gate TX` | 433.92 AM650 | | статичний |
| `Genius` | 433.92 AM650 | 868.35 AM650 | пакет FAAC SLH, ключ Genius |
| `KL: Genius TX4RC` | 433.92 AM650 | | KeeLoq (Genius Bravo/Echo RC) |
| `KL: Gibidi` | 433.92 AM650 | | KeeLoq |
| `KL: GSN` | 433.92 AM650 | | KeeLoq |
| `KL: HCS101` | 433.92 AM650 | | схожий на KeeLoq |
| `Hollarm` | 433.92 AM650 | | статичний (велосигналізація) |
| `KL: HomeGate` | 433.92 AM650 | | KeeLoq |
| `KL: Hor. EcoStar` | 433.92 AM650 | | KeeLoq (Hormann EcoStar) |
| `KL: IronLogic` | 433.92 AM650 | | KeeLoq |
| `KL: IronLogic SM` | 433.92 AM650 | | KeeLoq (IL-100 Smart) |
| `Jarolift` | 433.92 AM650 | | динамічний (на базі KeeLoq) |
| `KL: JCM Tech` | 433.92 AM650 | | KeeLoq |
| `KL: Jolly Mot.` | 433.92 AM650 | | KeeLoq (Jolly Motors) |
| `KL: KEY` | 433.92 AM650 | | KeeLoq |
| `KingGates Stylo4k` | 433.92 AM650 | | динамічний (на базі KeeLoq) |
| `Linear` | **300.00 AM650** | | статичний (10 бітів) |
| `Marantec` | 433.92 AM650 | 868.35 AM650 | статичний |
| `Marantec24` | **868.35 AM650** | | статичний |
| `KL: Mc Garcia` | 433.92 AM650 | | KeeLoq |
| `KL: Mhouse` | 433.92 AM650 | | KeeLoq |
| `KL: Monarch` | 433.92 AM650 | | KeeLoq + дискримінатор |
| `KL: Motorline` | 433.92 AM650 | | KeeLoq |
| `Nice Flo 12bit` | 433.92 AM650 | | статичний |
| `Nice Flo 24bit` | 433.92 AM650 | | статичний |
| `Nice FloR-S` | 433.92 AM650 | | динамічний |
| `Nice O-Code` | 433.92 AM650 | | динамічний, код інсталятора |
| `Nice O-Code One` | 433.92 AM650 | | динамічний, код інсталятора (пакет Nice One) |
| `Nice O-Code+Crt` | 433.92 AM650 | | динамічний, код інсталятора + сертифікат |
| `Nice One` | 433.92 AM650 | | динамічний |
| `KL: Nice Smilo` | 433.92 AM650 | | KeeLoq |
| `Nord ICE` | 433.92 AM650 | | статичний |
| `KL: Normstahl` | 433.92 AM650 | | KeeLoq |
| `KL: Novoferm` | 433.92 AM650 | | KeeLoq |
| `KL:Phantom(Hiland)` | 433.92 AM650 | | KeeLoq + дискримінатор |
| `Prastel` | 433.92 AM650 | | динамічний (42 біти) |
| `Princeton` | 433.92 AM650 | 315.00 AM650 | статичний (24 біти) |
| `Proteco` | 433.92 AM650 | | статичний |
| `KL: Pujol` | 433.92 AM650 | | KeeLoq |
| `KL: Pujol Vario` | 433.92 AM650 | | KeeLoq |
| `Revers RB2` | 433.92 AM650 | | статичний |
| `Roger` | 433.92 AM650 | | статичний |
| `KL: Seav` | 433.92 AM650 | | KeeLoq |
| `Security+1.0` | 433.92 AM650 | 315.00, 390.00 AM650 | динамічний |
| `Security+2.0` | 433.92 AM650 | 310.00, 315.00, 390.00 AM650 | динамічний |
| `Somfy Keytis` | **433.42 AM650** | | динамічний |
| `Somfy Telis` | **433.42 AM650** | | динамічний (Somfy RTS) |
| `KL: Sommer` | **434.42 FM12K** | 868.80 FM12K, 434.42 FM476, 868.80 FM476 | KeeLoq |
| `KL: Stilmatic` | 433.92 AM650 | | KeeLoq |
| `KL: Superrollo` | 433.92 AM650 | | KeeLoq (HCS361) |
| `Telcoma EDGE` | 433.92 AM650 | | статичний |
| `V2 Phoenix` | 433.92 AM650 | | динамічний |
| `KL: Verex` | 433.92 AM650 | | KeeLoq |
| `KL: Wisniowski` | 433.92 AM650 | | KeeLoq |
| `ZKTeco` | **430.50 AM650** | | статичний (Princeton, див. [ZKTeco CMP200](/ua/subghz/zkteco-cmp200)) |

Для `KL: Sommer` діапазони FM476 створюють пульт із іншим варіантом модуляції Sommer, тому один рядок меню
покриває обидва різновиди пультів Sommer.

## Прописування нового пульта в приймач

Щойно створений пульт із динамічним кодом приймачу невідомий. Пропишіть його, як будь-який запасний пульт — через
кнопку навчання на приймачі або з уже робочого пульта. Приховані / програмувальні кнопки оригінального пульта
надсилаються на Flipper однією клавішею-стрілкою. Покрокові процедури за виробниками:
**[Flipper як новий пульт](/ua/subghz/remote-prog)**.

## Усунення проблем

- **`Function requires an SD card with fresh databases.`** — бази ключів виробників у `/ext/subghz/assets/`
  відсутні або застарілі. Перевстановіть/оновіть прошивку з вставленою SD-карткою.
- **Приймач узагалі не реагує** — хибний діапазон. Спершу зчитайте свій оригінальний пульт
  (`Sub-GHz → Read`) і виберіть ту саму частоту й модуляцію. DoorHan буває на 315 і 433,92 МГц; FAAC, Genius,
  Erreka — на 433,92 і 868,35.
- **Приймач реагує, але пульт так і не зберігається** — пропущено вікно навчання або з іншої причини (наприклад, через
  завади) приймач не отримав коректний сигнал від Flipper.
- **Новий пульт Erreka/BFT відкидається** — у частині інсталяцій усі пульти мають один Seed; відновіть його
  ([Seed Capturer](/ua/subghz/seed-capturer)) і скористайтеся Add Manually [Advanced]. Див.
  [KeeLoq](/ua/subghz/keeloq).
- **Пульт Nice O-Code ігнорується** — у заводського приймача немає коду інсталятора; використайте там
  `Nice One` або `Nice FloR-S`. Для вже встановленої системи див. [Nice O-Code](/ua/subghz/nice-o-code).

::: warning
Прописуйте пульти лише в ті приймачі, якими ви володієте або які вам дозволено обслуговувати.
:::

## Пов'язані сторінки

- [Динамічні коди й кастомні кнопки](/ua/subghz/rolling-codes)
- [Прописування нового пульта в приймач](/ua/subghz/remote-prog)
- [KeeLoq](/ua/subghz/keeloq) · [Підтримувані системи](/ua/subghz/supported-systems)
- [Режими лічильника](/ua/subghz/counter-mode) · [Формат файлів `.sub`](/ua/subghz/file-format)
