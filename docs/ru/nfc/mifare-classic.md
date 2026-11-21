---
title: MIFARE Classic
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_classic, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, unleashed-readme, gromovyna]
---
# MIFARE Classic

MIFARE Classic — самая распространённая метка в СКУД, домофонах, гостиницах и старых транспортных системах. И самая
«интересная» для Флиппера: шифр Crypto-1 взломан, поэтому при должном усердии ключи почти любой метки можно
восстановить, а саму метку — эмулировать или записать на [заготовку](/ru/nfc/magic-cards).

## Устройство памяти

| Тип | Секторов | Блоков | Ключей | Типичный SAK |
|---|---|---|---|---|
| MIFARE Mini | 5 | 20 | 10 | `09` |
| MIFARE Classic 1K | 16 | 64 | 32 | `08` |
| MIFARE Classic 4K | 40 (32 × 4 блока + 8 × 16 блоков) | 256 | 80 | `18` |

- **Блок** — 16 байт. **Блок 0** (блок производителя) содержит UID и служебные данные; на оригинальных метках он
  неперезаписываемый — именно поэтому существуют заготовки.
- Последний блок каждого сектора — **трейлер**: `Key A (6 байт) | биты доступа (4 байта) | Key B (6 байт)`, например
  `FF FF FF FF FF FF FF 07 80 69 FF FF FF FF FF FF` у чистой метки.
- Биты доступа определяют, каким ключом какой блок можно читать и писать. Часто Key A читает, Key B пишет; иногда
  Key B сам читаем и тогда не может использоваться как ключ.

## Словари ключей

Флиппер не «знает» ключей — он перебирает кандидатов из словарей. Это текстовые файлы, по одному ключу из 12
hex-символов в строке, `#` — комментарий (см. [формат файлов](/ru/nfc/file-format)).

| Словарь | Путь | Кто пишет |
|---|---|---|
| **Системный** | `/ext/nfc/assets/mf_classic_dict.nfc` | Идёт с прошивкой (перезаписывается при обновлении). В Unleashed — **4000+ ключей**. |
| **Пользовательский** | `/ext/nfc/assets/mf_classic_dict_user.nfc` | Вы, MFKey, qUnleashed, *Save Keys to Dictionary*. Переживает обновления. |
| **CUID** (на одну метку) | `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | MFKey / qUnleashed для меток со *static encrypted* нонсами: большой список кандидатов для одного UID. |
| **Кеш ключей** | `/ext/nfc/.cache/<UID>.keys` | Пишется автоматически при **сохранении** метки; используется первым при следующем чтении того же UID. |

::: tip Unleashed
В системном словаре Unleashed — большой набор дополнительных ключей от комьюнити («Extra Mifare Classic keys in system
dict» в ReadMe). Экран загрузки CUID-словаря с прогресс-баром (*«CUID dictionary is loading»*) появился в дев-билде
1437 / релизе 094.
:::

### Управление пользовательским словарём на устройстве

1. Откройте `Main Menu → NFC → Extra Actions → MIFARE Classic Keys`.

   ![Меню Extra Actions, где среди словарей есть MIFARE Classic Keys](/screens/nfc/extra_actions.png)

2. На экране **System dict: N** и **User dict: N**.
3. <kbd>OK</kbd> **Add** — ввести 6-байтный ключ в hex и сохранить. На дубликат будет предупреждение.
4. <kbd>→</kbd> **List** (только если пользовательский словарь не пуст) — выбрать ключ для удаления
   (*«Select key to delete:»*).

Файл `mf_classic_dict_user.nfc` можно править и на компьютере (qFlipper, qUnleashed или напрямую на SD-карте).

### Save Keys to Dictionary

В меню любого сохранённого или только что прочитанного дампа MIFARE Classic, где известен хоть один ключ, есть
**Save Keys to Dictionary**. Пункт копирует все ключи дампа в пользовательский словарь, пропуская дубликаты, и
сообщает *«New keys: N, Already known: M»*. Особенно важно для меток, чьи ключи восстановлены из CUID-словаря: иначе
эти ключи живут только в этом файле и в дампе, а [NFC Magic](/ru/nfc/nfc-magic) смотрит только в кеш ключей и в
пользовательский/системный словари (это то самое «автоматическое сохранение ключей с проверкой на дубликаты», о
котором пишет @gromovyna в [статье про qUnleashed](/ru/nfc/qunleashed)).

## Что происходит при чтении MIFARE Classic

`Main Menu → NFC → Read`, держите метку неподвижно. Прошивка проходит этапы; заголовок экрана атаки показывает,
какой идёт сейчас.

1. **Кеш ключей.** Если этот UID уже сохраняли, используются кешированные ключи, и метка читается сразу.
2. **Атака по словарю**, в таком порядке:
   - **MF Classic CUID Dictionary** — только если есть файл для этого UID (перед ним *«CUID dictionary is loading»* с
     прогресс-баром; большой файл грузится минутами);
   - **MF Classic User Dictionary** — если пользовательский файл есть и не пуст;
   - **MF Classic System Dictionary**.

   На экране `Keys found: X/Y`, `Sectors Read: X/Y`, номер текущего ключа и *«Unlocking sector: N»* /
   *«Reuse key check for sector: N»*.

   ![Перебор по системному словарю: сектор 9, ключ 1244 из 2271, найдено 19 из 32 ключей](/screens/nfc/dict_attack.png)

3. **Чтение через бэкдор.** Если у чипа есть известный **бэкдор-ключ** (Fudan и некоторые другие), в заголовке
   **Backdoor Read** / **(Backdoor)**, сектора читаются без настоящих ключей, параллельно собираются нонсы.
4. **Nested-атаки** (когда известен хотя бы один ключ): **PRNG Analysis**, **Nested Dictionary**, **Calibration**,
   **Nonce Collection** (*«Collecting from sector: N»*). Суффикс **(Hard)** — у метки hard PRNG. Собранные нонсы
   дописываются в `/ext/nfc/.nested.log`.
5. Открывается экран результата. Зелёный светодиод / звук успеха — метка прочитана полностью, короткий
   «полууспех» — каких-то секторов не хватает.

<kbd>OK</kbd> **Skip** — перейти к следующему этапу (CUID → User → System → результат). <kbd>←</kbd> спросит *«Exit to
NFC Menu? All unsaved data will be lost»*. Если метку убрали, появится **«Lost the tag! Make sure the tag is
positioned correctly.»** — верните её, и атака продолжится.

Подробный разбор каждой фазы со скриншотами — на странице [Nested-атаки и бэкдоры Fudan](/ru/nfc/nested-fudan).

### После чтения

Меню (`More`) для MIFARE Classic:

| Пункт | Когда | Что делает |
|---|---|---|
| **Save** | всегда | Сохранить дамп в `/ext/nfc/`. Заодно заполняет кеш ключей. |
| **Emulate** | всегда | Полная эмуляция дампа. |
| **Extract MFC Keys** | метка прочитана не полностью | Спрашивает *«Save the Key?»* (Save/Skip), затем собирает нонсы со считывателя. См. [MFKey32](/ru/nfc/mfkey). |
| **Unlock with Dictionary** | метка прочитана не полностью | Повторить атаку по словарям/nested (например, после добавления ключей). |
| **Crack nonces in MFKey32** | метка прочитана не полностью | Предлагает сохранить метку, затем запускает [MFKey](/ru/nfc/mfkey-app) (**Run**). |
| **Show Keys** | всегда | *«Found MFC Keys»*: по секторам биты доступа, Key A, Key B и итог. |
| **Save Keys to Dictionary** | известен хоть один ключ | См. выше. |
| **Info** | всегда | UID, ATQA, SAK, сводка по ключам/секторам; **More** — hex-дамп (`??` — неизвестные байты). |

У **сохранённой** метки дополнительно: **Write to Initial Card**, **Update from Initial Card**, **Restore to
Original State** (если есть shadow-файл), **Rename** и **Delete**.

## Как добыть недостающие ключи

Если прочитаны не все сектора, выберите способ по ситуации:

| Ситуация | Способ |
|---|---|
| Есть метка **и** доступ к считывателю | [MFKey32](/ru/nfc/mfkey): Флиппер эмулирует метку, считыватель «сдаёт» свои ключи. |
| Есть метка, известен хоть один ключ или у чипа бэкдор | Nested-атаки идут сами в `Read`; ключи считаются в [MFKey](/ru/nfc/mfkey-app) или, гораздо быстрее, в [qUnleashed](/ru/nfc/qunleashed). |
| У метки **hard PRNG** | HardNested — считается в qUnleashed или на ПК, см. [Nested-атаки](/ru/nfc/nested-fudan). |
| Метки нет, только считыватель | [MFKey32](/ru/nfc/mfkey) через `Extract MFC Keys` в главном меню NFC — ключи пойдут в пользовательский словарь на будущее. |
| Ключи диверсифицированы под каждую метку (напр. [Iron Logic](/ru/nfc/iron-logic)) | У каждой метки свои ключи — восстанавливайте для каждой отдельно. |

После добавления ключей прочитайте метку снова (или откройте сохранённый файл → **Unlock with Dictionary**).

## Эмуляция

1. `Main Menu → NFC → Saved → <метка> → Emulate`.
2. Приложите Флиппер к считывателю.

Непрочитанные сектора эмулируются как неизвестные — считыватель, которому они нужны, метку не примет. Если считыватель
пишет в метку (баланс, счётчики, «динамика»), изменения уходят в [shadow-файл](/ru/nfc/read#shadow-файлы).

::: warning Динамические системы
Некоторые системы перезаписывают данные метки при каждом проходе (например, [Iron Logic в режиме динамики](/ru/nfc/iron-logic-enrollment)).
Эмулированная копия и оригинал тогда рассинхронизируются; использование обоих может заблокировать оригинал.
:::

## Запись

- **Write to Initial Card** записывает дамп обратно **на ту же метку** (UID должен совпадать). На любую другую —
  *«Use source card! To write blanks use NFC Magic app»*. Если не все блоки записались — *«Not all sectors were
  written correctly»*.
- Для клонирования на заготовку используйте приложение [NFC Magic](/ru/nfc/nfc-magic) и подходящую
  [заготовку](/ru/nfc/magic-cards). Выбирайте её с умом: многие считыватели фильтруют Gen1.

## Типичные проблемы

- **Ключи найдены, но часть секторов не читается** — биты доступа запрещают чтение найденным типом ключа;
  восстановите второй ключ (A или B).
- **Чтение начинается с долгого «CUID dictionary is loading»** — для этой метки есть большой список кандидатов. Это
  нормально после атаки на static encrypted нонсы. Когда метка полностью вскрыта и ключи сохранены в пользовательский
  словарь, удалите `/ext/nfc/assets/mf_classic_dict_<UID>.nfc`.
- **MFKey пишет «Nonces already cracked» / ничего нового** — после успешного восстановления чистите
  `/ext/nfc/.nested.log` и `/ext/nfc/.mfkey32.log`: старые нонсы всё замедляют.
- **Восстановленные ключи будто не используются** — проверьте, что они реально попали в `mf_classic_dict_user.nfc`
  (`Extra Actions → MIFARE Classic Keys → List`). Ключи, найденные HardNested на ПК, добавляются вручную.

## См. также

[Чтение меток](/ru/nfc/read) · [MFKey32](/ru/nfc/mfkey) · [Nested-атаки](/ru/nfc/nested-fudan) ·
[MFKey](/ru/nfc/mfkey-app) · [qUnleashed](/ru/nfc/qunleashed) · [Заготовки](/ru/nfc/magic-cards) ·
[MIFARE Plus](/ru/nfc/mifare-plus)
