---
title: Add Manually
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Add Manually (создание пульта вручную)

**Add Manually** создаёт новый виртуальный пульт и сохраняет его в `.sub`-файл. Оригинальный пульт для этого не
нужен: Флиппер сам генерирует случайный серийный номер (а также счётчик, seed и т.д., если протокол их
использует). Дальше такой пульт **привязывают к приёмнику** — так же, как запасной брелок из магазина.

**Add Manually [Advanced]** делает то же самое, но вместо генерации просит ввести все значения вручную в HEX.

::: tip Unleashed
В стоковой прошивке в Add Manually всего несколько статических протоколов. В Unleashed — **больше 100 систем**,
в том числе с динамическим кодом (производители KeeLoq, FAAC SLH, BFT Mitto, Nice FloR-S / O-Code, CAME Atomo,
Somfy, Security+ 2.0 и др.), для каждой можно выбрать любой из 15 диапазонов частота/модуляция, плюс есть
пункт **[Advanced]**.
:::

## Когда это нужно

| Ситуация | Что использовать |
|---|---|
| **Статический** пульт, нужна копия | [Read](/ru/subghz/read) и сохранить — Add Manually не нужен |
| **Динамический** пульт, Флиппер должен работать *вместе* с ним | **Add Manually** → привязать новый пульт к приёмнику ([как](/ru/subghz/remote-prog)) |
| Нужен пульт с известными значениями (восстановленный seed, код инсталлятора, конкретный серийник) | **Add Manually [Advanced]** |
| Статический пульт потерян, но известны DIP-переключатели / код | **Add Manually [Advanced]** с вводом ключа |

Почему нельзя просто клонировать динамический пульт — см. [Динамические коды](/ru/subghz/rolling-codes):
клон и оригинал начинают «воевать» за счётчик.

## Создание пульта

1. `Main Menu → Sub-GHz → Add Manually`.
2. Пролистайте список и выберите систему, например `BFT Mitto` или `KL: DoorHan`. Пункты с префиксом `KL:` —
   производители KeeLoq.

   ![Add Manually: алфавитный список систем, выбран KL: Allmatic](/screens/subghz/add_manually.png)

3. Откроется **выбор диапазона** с названием системы в заголовке. Диапазоны подписаны как `частота модуляция`,
   например `433.92 AM650`. Первым идёт диапазон системы по умолчанию, затем другие диапазоны, на которых эта
   система встречается, затем все остальные (на случай нестандартной установки). Нажмите <kbd>OK</kbd> на нужном.
4. Введите имя файла (имя предлагается автоматически) и подтвердите.
5. Пульт сохраняется в `/ext/subghz/` и появляется в `Sub-GHz → Saved`.

   ![Меню сохранённого сигнала: Emulate, Rename, Delete, Signal Settings](/screens/subghz/saved_menu.png)

6. Откройте его: `Sub-GHz → Saved → <файл> → Emulate`. Удерживайте <kbd>OK</kbd> (`Send`) для передачи; на
   протоколах с [кастомными кнопками](/ru/subghz/rolling-codes#кастомные-кнопки) стрелки отправляют остальные кнопки.

   ![Экран передачи сохранённого сигнала: R: Int и кнопка Send](/screens/subghz/emulate.png)


Пока вы не откроете файл и не нажмёте кнопку — ничего не передаётся.

::: warning Устаревшие названия
В старых гайдах (и в старых версиях `SubGHzRemoteProg.md`) пункты называются `BFT Mitto 433MHz` или
`KL: DoorHan 315MHz`. В текущей прошивке это два шага: система (`BFT Mitto`) → диапазон (`433.92 AM650`).
:::

### 15 диапазонов

Для любой системы доступны все:

`433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`,
`868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`,
`430.50 AM650`.

## Add Manually [Advanced]

`Main Menu → Sub-GHz → Add Manually [Advanced]` → система → диапазон, затем серия экранов ввода в HEX. Набор
экранов зависит от семейства протокола:

| Семейство | Экраны (по порядку) |
|---|---|
| Статические (Princeton, CAME, Nice Flo, …) | `Enter KEY in hex`; протоколы, хранящие тайминг, также спрашивают `Enter TE in us` (и `Enter GT in TE`) |
| KeeLoq (пункты `KL:`, AN-Motors AT4) | `SERIAL` → `BUTTON` → `COUNTER` |
| KeeLoq с seed (BFT Mitto, Erreka) | `SERIAL` → `BUTTON` → `COUNTER` → `SEED` |
| `KL: FAAC FIX`, `KL: Monarch`, `KL:Phantom(Hiland)`, `KL: DEA Mio` | `SERIAL` → `BUTTON` → `COUNTER` → `DISC.` (дискриминатор hop, хранится в поле `Seed`) |
| FAAC SLH, Genius | `SERIAL` → `BUTTON` → `COUNTER` (32 бита) → `SEED` |
| CAME Atomo, V2 Phoenix | `SERIAL` → `COUNTER` |
| Alutech AT4N, Somfy Telis/Keytis, KingGates, Beninca ARC, Jarolift, Ditec GOL4, Prastel, BelKorn, Security+2.0 | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice FloR-S, Nice One | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice O-Code, Nice O-Code One | `SERIAL` → `BUTTON` → `COUNTER` → `IC` (код инсталлятора) |
| Nice O-Code+Crt | `SERIAL` → `BUTTON` → `COUNTER` → `IC` → `CERT` (спрашивается даже из обычного Add Manually) |
| Security+1.0 | ничего вводить не нужно, создаётся сразу |

Значения вводятся в HEX (big-endian). `BUTTON` и `SERIAL` вместе образуют `Fix`, который вы видите после
[Read](/ru/subghz/read): у KeeLoq кнопка — это **первая** HEX-цифра `Fix` (серийник = `Fix`, где эта цифра
заменена на `0`), у FAAC SLH / Genius — **последняя**.

::: tip Ввод байтов
В Unleashed у поля ввода байтов есть мини-редактор полубайтов: нажимайте <kbd>↑</kbd>, пока он не появится.
:::

## Все пункты списка

Порядок и названия — точно как в меню прошивки. «По умолчанию» — первый диапазон в списке; «Также» —
альтернативные диапазоны этой системы, идущие сразу за ним.

| Пункт меню | По умолчанию | Также | Тип |
|---|---|---|---|
| `KL: Allmatic` | 433.92 AM650 | 868.35 AM650 | KeeLoq (ключ Beninca) |
| `Alutech AT4N` | 433.92 AM650 | | Динамический (Alutech AT-4N) |
| `AN-Motors AT4` | 433.92 AM650 | | KeeLoq |
| `KL: Aprimatic` | 433.92 AM650 | | KeeLoq |
| `KL: ATA PTX4` | 433.92 AM650 | | KeeLoq |
| `BelKorn` | 433.92 AM650 | | Динамический (открытый счётчик) |
| `KL: Beninca` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `Beninca ARC` | 433.92 AM650 | | Динамический (AES-128) |
| `BETT` | 433.92 AM650 | | Статический |
| `BFT Mitto` | 433.92 AM650 | | KeeLoq + Seed |
| `CAME 12bit` | 433.92 AM650 | 868.35 AM650 | Статический |
| `CAME 24bit` | 433.92 AM650 | 868.35 AM650 | Статический |
| `CAME Atomo` | 433.92 AM650 | 868.35 AM650 | Динамический |
| `KL: CAME Space` | 433.92 AM650 | | KeeLoq |
| `CAME TWEE` | 433.92 AM650 | | Статический (псевдодинамика) |
| `KL: Cardin S449` | **433.92 FM12K** | | KeeLoq |
| `KL: Centurion` | 433.92 AM650 | | KeeLoq |
| `KL: Clm.Mutancode` | 433.92 AM650 | | KeeLoq (Clemsa Mutancode) |
| `KL: Comunello` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `KL: DEA Mio` | 433.92 AM650 | | KeeLoq + дискриминатор |
| `Ditec GOL4` | 433.92 AM650 | | Динамический |
| `KL: DoorHan` | 433.92 AM650 | 315.00 AM650 | KeeLoq |
| `KL: Doormatic` | 433.92 AM650 | | KeeLoq |
| `KL: DTM Neo` | 433.92 AM650 | | KeeLoq |
| `KL: Elmes (PL)` | 433.92 AM650 | | KeeLoq |
| `KL: Elvox` | 433.92 AM650 | | KeeLoq |
| `Erreka` | 433.92 AM650 | 868.35 AM650 | KeeLoq + Seed |
| `KL: ET Blue` | 433.92 AM650 | | KeeLoq |
| `KL: ET Blue Mix` | 433.92 AM650 | | KeeLoq |
| `KL: FAAC FIX` | 433.92 AM650 | | KeeLoq + дискриминатор |
| `KL: FAAC RC,XT` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `FAAC SLH` | 433.92 AM650 | 868.35 AM650 | FAAC SLH + Seed |
| `FAAC TM` | 433.92 AM650 | 868.35 AM650 | Статический (12 DIP) |
| `KL: Fadini` | 433.92 AM650 | | KeeLoq |
| `GangQi` | 433.92 AM650 | | Статический (мотосигнализация) |
| `Gate TX` | 433.92 AM650 | | Статический |
| `Genius` | 433.92 AM650 | 868.35 AM650 | Пакет FAAC SLH, ключ Genius |
| `KL: Genius TX4RC` | 433.92 AM650 | | KeeLoq (Genius Bravo/Echo RC) |
| `KL: Gibidi` | 433.92 AM650 | | KeeLoq |
| `KL: GSN` | 433.92 AM650 | | KeeLoq |
| `KL: HCS101` | 433.92 AM650 | | KeeLoq-подобный |
| `Hollarm` | 433.92 AM650 | | Статический (мотосигнализация) |
| `KL: HomeGate` | 433.92 AM650 | | KeeLoq |
| `KL: Hor. EcoStar` | 433.92 AM650 | | KeeLoq (Hormann EcoStar) |
| `KL: IronLogic` | 433.92 AM650 | | KeeLoq |
| `KL: IronLogic SM` | 433.92 AM650 | | KeeLoq (IL-100 Smart) |
| `Jarolift` | 433.92 AM650 | | Динамический (на базе KeeLoq) |
| `KL: JCM Tech` | 433.92 AM650 | | KeeLoq |
| `KL: Jolly Mot.` | 433.92 AM650 | | KeeLoq (Jolly Motors) |
| `KL: KEY` | 433.92 AM650 | | KeeLoq |
| `KingGates Stylo4k` | 433.92 AM650 | | Динамический (на базе KeeLoq) |
| `Linear` | **300.00 AM650** | | Статический (10 бит) |
| `Marantec` | 433.92 AM650 | 868.35 AM650 | Статический |
| `Marantec24` | **868.35 AM650** | | Статический |
| `KL: Mc Garcia` | 433.92 AM650 | | KeeLoq |
| `KL: Mhouse` | 433.92 AM650 | | KeeLoq |
| `KL: Monarch` | 433.92 AM650 | | KeeLoq + дискриминатор |
| `KL: Motorline` | 433.92 AM650 | | KeeLoq |
| `Nice Flo 12bit` | 433.92 AM650 | | Статический |
| `Nice Flo 24bit` | 433.92 AM650 | | Статический |
| `Nice FloR-S` | 433.92 AM650 | | Динамический |
| `Nice O-Code` | 433.92 AM650 | | Динамический, код инсталлятора |
| `Nice O-Code One` | 433.92 AM650 | | Динамический, код инсталлятора (пакет Nice One) |
| `Nice O-Code+Crt` | 433.92 AM650 | | Динамический, код инсталлятора + сертификат |
| `Nice One` | 433.92 AM650 | | Динамический |
| `KL: Nice Smilo` | 433.92 AM650 | | KeeLoq |
| `Nord ICE` | 433.92 AM650 | | Статический |
| `KL: Normstahl` | 433.92 AM650 | | KeeLoq |
| `KL: Novoferm` | 433.92 AM650 | | KeeLoq |
| `KL:Phantom(Hiland)` | 433.92 AM650 | | KeeLoq + дискриминатор |
| `Prastel` | 433.92 AM650 | | Динамический (42 бита) |
| `Princeton` | 433.92 AM650 | 315.00 AM650 | Статический (24 бита) |
| `Proteco` | 433.92 AM650 | | Статический |
| `KL: Pujol` | 433.92 AM650 | | KeeLoq |
| `KL: Pujol Vario` | 433.92 AM650 | | KeeLoq |
| `Revers RB2` | 433.92 AM650 | | Статический (Реверс РБ-2) |
| `Roger` | 433.92 AM650 | | Статический |
| `KL: Seav` | 433.92 AM650 | | KeeLoq |
| `Security+1.0` | 433.92 AM650 | 315.00, 390.00 AM650 | Динамический |
| `Security+2.0` | 433.92 AM650 | 310.00, 315.00, 390.00 AM650 | Динамический |
| `Somfy Keytis` | **433.42 AM650** | | Динамический |
| `Somfy Telis` | **433.42 AM650** | | Динамический (Somfy RTS) |
| `KL: Sommer` | **434.42 FM12K** | 868.80 FM12K, 434.42 FM476, 868.80 FM476 | KeeLoq |
| `KL: Stilmatic` | 433.92 AM650 | | KeeLoq |
| `KL: Superrollo` | 433.92 AM650 | | KeeLoq (HCS361) |
| `Telcoma EDGE` | 433.92 AM650 | | Статический |
| `V2 Phoenix` | 433.92 AM650 | | Динамический |
| `KL: Verex` | 433.92 AM650 | | KeeLoq |
| `KL: Wisniowski` | 433.92 AM650 | | KeeLoq |
| `ZKTeco` | **430.50 AM650** | | Статический (Princeton, см. [ZKTeco CMP200](/ru/subghz/zkteco-cmp200)) |

У `KL: Sommer` диапазоны FM476 создают пульт во втором варианте модуляции Sommer, так что один пункт меню
покрывает оба типа пультов Sommer.

## Привязка нового пульта к приёмнику

Только что созданный динамический пульт приёмнику неизвестен. Привязывайте его как любой запасной — кнопкой
обучения на приёмнике или с уже работающего пульта. Скрытые/программирующие кнопки оригинального пульта на
Флиппере отправляются одной стрелкой. Пошаговые инструкции по производителям:
**[Флиппер как новый пульт](/ru/subghz/remote-prog)**.

## Проблемы и решения

- **`Function requires an SD card with fresh databases.`** — базы ключей производителей в `/ext/subghz/assets/`
  отсутствуют или устарели. Переустановите/обновите прошивку со вставленной SD-картой.
- **Приёмник никак не реагирует** — неверный диапазон. Сначала считайте оригинальный пульт (`Sub-GHz → Read`) и
  выберите ту же частоту и модуляцию. DoorHan бывает на 315 и 433.92 МГц; FAAC, Genius, Erreka — на 433.92 и 868.35.
- **Приёмник реагирует, но пульт не записывается** — пропущено окно обучения или по иной причине (например, из-за
  помех) приёмник не получил корректный сигнал от Флиппера.
- **Новый пульт Erreka/BFT не принимается** — в некоторых инсталляциях у всех пультов один Seed; восстановите
  его ([Seed Capturer](/ru/subghz/seed-capturer)) и используйте Add Manually [Advanced]. См. [KeeLoq](/ru/subghz/keeloq).
- **Пульт Nice O-Code игнорируется** — у заводского приёмника нет кода инсталлятора; там используйте `Nice One`
  или `Nice FloR-S`. Для уже настроенной системы см. [Nice O-Code](/ru/subghz/nice-o-code).

::: warning
Привязывайте пульты только к приёмникам, которые принадлежат вам или которыми вы вправе управлять.
:::

## См. также

- [Динамические коды и кастомные кнопки](/ru/subghz/rolling-codes)
- [Привязка нового пульта к приёмнику](/ru/subghz/remote-prog)
- [KeeLoq](/ru/subghz/keeloq) · [Поддерживаемые системы](/ru/subghz/supported-systems)
- [Режимы счётчика](/ru/subghz/counter-mode) · [Формат .sub](/ru/subghz/file-format)
