---
title: Read (чтение)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Read (чтение)

**Read** слушает одну частоту (или перебирает несколько), **декодирует** сигналы известных протоколов и выводит их
списком. Декодированный сигнал можно сохранить в файл-ключ и отправить снова. Это основной способ скопировать пульт
со **статическим кодом** — ворота, шлагбаумы, звонки, розетки — и узнать, какой протокол использует пульт.

Если Read пульт не распознаёт — используйте [Read RAW](/ru/subghz/read-raw). Для пультов с динамическим кодом
**до отправки** прочитайте [Динамические коды](/ru/subghz/rolling-codes).

::: tip Unleashed
По сравнению со стоковой прошивкой в Unleashed: десятки дополнительных протоколов ([полный список](/ru/subghz/supported-systems)),
сохранение и отправка многих **динамических** протоколов, **кастомные кнопки** на стрелках при отправке, Hopping с
порогом RSSI, фильтры `Ignore …`, `Delete old signals when memory is full`, **удержание <kbd>→</kbd> удаляет**
сигнал из списка, время приёма у каждого сигнала, запоминание последних настроек.
:::

## Как считать пульт

1. Если частота неизвестна — определите её через [Frequency Analyzer](/ru/subghz/frequency-analyzer)
   (долгое <kbd>OK</kbd> там сразу открывает Read на найденной частоте).
2. Откройте `Main Menu → Sub-GHz → Read`. На экране `Fixed scan...` (или `Hopper scan...` при включённом хоппинге),
   внизу — текущие частота и модуляция.

   ![Экран Read в ожидании сигнала: Fixed scan на 433.92 МГц, AM650](/screens/subghz/read.png)

3. Поднесите пульт к левому боку Флиппера и нажмите кнопку на 1–2 секунды.
4. Декодированный сигнал появится в списке: имя протокола + время приёма. Счётчик внизу показывает, сколько
   сигналов в списке.

   ![Список принятых сигналов: Princeton, CAME 12bit и KL: DoorHan](/screens/subghz/read_list.png)

5. Выберите его <kbd>↑</kbd> <kbd>↓</kbd> и нажмите <kbd>OK</kbd> — откроются подробности (ключ, число бит,
   серийник, кнопка, счётчик, производитель для KeeLoq и т.д.).

   ![Подробности сигнала: Princeton 24bit, ключ, серийник и кнопка, кнопки Send и Save](/screens/subghz/signal_info.png)

6. Нажмите <kbd>→</kbd> **Save**, введите имя и подтвердите. Файл сохранится в `/ext/subghz/`.
7. Или нажмите <kbd>OK</kbd> **Send**, чтобы сразу передать.

Сохранённые сигналы — в `Main Menu → Sub-GHz → Saved` (см. [ниже](#saved-signals)).

## Кнопки на экране Read

| Кнопка | Действие |
|---|---|
| <kbd>←</kbd> | **Config** — настройки приёмника |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Перемещение по списку принятых сигналов |
| <kbd>OK</kbd> | Открыть выбранный сигнал |
| удержание <kbd>→</kbd> | Удалить выбранный сигнал из списка |
| <kbd>Back</kbd> | Выход. Если есть несохранённые сигналы — запрос **Exit to Sub-GHz Menu?** (`Exit` / `Stay`) |

В списке помещается до 128 сигналов (меньше, если много крупных BinRAW — зависит от свободной памяти).

## Config

Нажмите <kbd>←</kbd> **Config** на экране Read:

![Меню Config в Read: Frequency, Modulation, Hopping и Bin RAW](/screens/subghz/read_config.png)

| Пункт | Значения | Что делает |
|---|---|---|
| `Frequency` | список из [Частот](/ru/subghz/frequencies) | Фиксированная частота приёма. При включённом хоппинге показывает ` -----` |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + свои пресеты | Пресет демодуляции. Большинству пультов подходит `AM650` |
| `Hopping` / `Hopping RSSI` | `OFF`, `-90dBm` … `-40dBm` | Перебор частот хоппинга (315, 390, 430.5, 433.92, 434.42, 868.35 МГц). Значение — уровень RSSI, при котором перебор останавливается на частоте |
| `Bin RAW` | `OFF` / `ON` | Дополнительно собирать неизвестные статические сигналы как **BinRAW** (повторяющийся фрагмент с восстановленной скоростью). Держите кнопку пульта подольше, чтобы накопилось достаточно данных |
| `Ignore ReversRB2` | `OFF` / `ON` | Скрывать сигналы Реверс РБ-2(М) |
| `Ignore Alarms` | `OFF` / `ON` | Скрывать вело/мотосигнализации (Hollarm, GangQi) |
| `Ignore Sensors` | `OFF` / `ON` | Скрывать датчики и подобный «эфирный мусор»: Magellan, Honeywell, звонки Honeywell WDB и Legrand, Doorbell32, KeyFinder/KeyFinder2, Feron |
| `Ignore Princeton` | `OFF` / `ON` | Скрывать Princeton (PT2262 и клоны) — полезно, где дешёвые пульты забивают эфир |
| `Ignore Nice Flor-S / Nice One` | `OFF` / `ON` | Скрывать Nice Flor-S / Nice One |
| `Delete old signals when memory is full` | `OFF` / `ON` | При заполнении списка удалять самые старые сигналы вместо остановки. Счётчик тогда показывает `!` |
| `Sound` | `OFF` / `ON` | Выводить всё принятое в динамик — можно «послушать» пульт |
| `Reset to default` | — | Сброс: 433.92 МГц AM650, хоппинг выкл., все фильтры выкл., Bin RAW выкл., TX Power `Preset` |
| `Lock Keyboard` | — | Блокировка кнопок во время сканирования (например, в кармане). **Разблокировка — трижды нажать <kbd>Back</kbd>** |

Все настройки Read сохраняются и восстанавливаются при следующем запуске.

::: tip Какое значение Hopping выбрать
При включённом хоппинге приёмник задерживается на частоте, только если сигнал выше выбранного уровня. `-90dBm` —
самый чувствительный; повышайте, если шум постоянно останавливает перебор. Для надёжного приёма лучше
**фиксированная частота**, найденная анализатором: сигналы во время переключения частоты теряются.
:::

## Отправка сигнала

Откройте сигнал (из списка Read или через `Saved → <файл> → Emulate`). На экране передачи — данные ключа, частота,
модуляция и `R: Int` / `R: Ext` (каким радиомодулем пойдёт передача).

- **Удерживайте** <kbd>OK</kbd> (**Send**) — Флиппер передаёт **только пока кнопка нажата**. Короткое нажатие может
  отправить неполный код; держите 1–2 с (CAME Atomo — не меньше 2 с).
- <kbd>Back</kbd> — выход.

### Кастомные кнопки (Unleashed)

::: tip Unleashed
Для многих протоколов стрелки отправляют **тот же пульт с другим кодом кнопки** — один сохранённый файл работает как
весь пульт. Поддерживаются, в частности: KeeLoq, Alutech AT-4N, Nice Flor-S, Somfy Telis/Keytis, Security+ 2.0,
CAME Atomo, FAAC SLH, BelKorn, Beninca ARC, Ditec GOL4, Jarolift, KingGates Stylo 4k, V2 Phoenix, Prastel, Roger,
Nord ICE, Princeton, Proteco, Dooya, Hay21, GangQi, Hollarm. Пока стрелка удерживается, справа на экране виден
отправляемый код кнопки. Какая стрелка какой кнопке соответствует — зависит от протокола, см.
[Динамические коды](/ru/subghz/rolling-codes) и [Привязка нового пульта](/ru/subghz/remote-prog).
:::

## Сохранённые сигналы {#saved-signals}

`Main Menu → Sub-GHz → Saved` — список файлов из `/ext/subghz/`. При выборе файла доступно:

- `Emulate` — экран передачи;
- `Rename` — переименовать;
- `Delete` — удалить;
- `Signal Settings` — **только в режиме Debug** (`Settings → System → Debug`): `Counter Mode`, `Edit Counter`,
  `Edit Button` для файлов динамических протоколов. См. [Режимы счётчика](/ru/subghz/counter-mode).

RAW-файлы открываются в экране Read RAW — см. [Read RAW](/ru/subghz/read-raw#playback).

Имена файлов генерируются автоматически (дата-время). Если в [Radio Settings](/ru/subghz/settings) включено
`Protocol Names`, перед меткой времени ставится имя протокола.

## Статический и динамический код

- **Статический код** (Princeton, CAME 12/24 bit, Nice Flo, Marantec, Roger, Gate TX…): каждое нажатие отправляет
  один и тот же код. Сохранённая копия работает вечно вместе с оригиналом.
- **Динамический (rolling) код** (KeeLoq, Nice Flor-S, CAME Atomo, FAAC SLH, Somfy, Security+…): в каждом нажатии
  новое значение счётчика. Unleashed умеет сохранять и отправлять многие из них, **но отправка копии рассинхронизирует
  оригинальный пульт**. Прочитайте [Динамические коды](/ru/subghz/rolling-codes) и лучше создайте *новый* пульт через
  [Add Manually](/ru/subghz/add-manually).

::: danger Автомобильные брелоки
Не экспериментируйте с ключом от своей машины. Повтор сигнала брелока (Read или Read RAW) может рассинхронизировать
или заблокировать оригинальный ключ, а перепривязка часто требует дилерского оборудования. Используйте Флиппер только
со своим оборудованием и в законных целях.
:::

## Частые проблемы

- **Ничего не появляется** — неверная частота или модуляция. Анализатор, затем `AM650`, затем `FM238`/`FM476`/`FM12K`.
  Проверьте, не скрывает ли протокол один из фильтров `Ignore …`.
- **Сигнал принимается, но не декодируется** — протокол неизвестен: включите `Bin RAW` (для статики) или запишите
  через [Read RAW](/ru/subghz/read-raw). Попробуйте и приложение [Remote Analyzer](/ru/subghz/remote-analyzer).
- **KeeLoq с производителем `Unknown`** — ключа производителя нет в базе или пульту нужен Seed (BFT, Erreka,
  FAAC SLH). См. [KeeLoq](/ru/subghz/keeloq) и [Seed Capturer](/ru/subghz/seed-capturer).
- **Нет кнопки `Send`** — протокол только для декодирования (например, iDo) или пакет Nice O-Code без кода установщика
  (используйте приложение [Nice O-Code](/ru/subghz/nice-o-code)).
- **Список забивается шумом** — включите нужные `Ignore` или `Delete old signals when memory is full`.

## См. также

- [Read RAW](/ru/subghz/read-raw) · [Frequency Analyzer](/ru/subghz/frequency-analyzer) · [Поддерживаемые системы](/ru/subghz/supported-systems)
- [Динамические коды](/ru/subghz/rolling-codes) · [Add Manually](/ru/subghz/add-manually) · [Radio Settings](/ru/subghz/settings) · [Форматы файлов](/ru/subghz/file-format)
