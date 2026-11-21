---
title: Seed Capturer
order: 190
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/seed_capturer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Seed Capturer

**FAAC SLH**, **Genius**, **Erreka** и **BFT Mitto** строят динамический код из секретного **Seed**. Без него Флиппер не может декодировать такие пульты (они читаются как `KL: Unknown` или не читаются вовсе) и не может создать пульт, который примет приёмник. **Seed Capturer** (автор @xMasterX) собирает исходные данные для восстановления Seed: `Fix` пульта и серию последовательных значений `Hop`.

Сам Seed приложение **не** восстанавливает и **ничего не передаёт** — только слушает и пишет файл. Ищет его приложение-компаньон [qUnleashed](/ru/mobile/qunleashed-app).

::: tip Unleashed
Seed Capturer — встроенное системное приложение Unleashed, а qUnleashed забирает записи прямо с Флиппера. Когда Seed известен, Unleashed декодирует пульт и может создавать новые через `Add Manually [Advanced]`.
:::

## Когда это нужно

- Радиопрограммирование приёмника отключено — остаётся только клон известного пульта, а клону нужен Seed.
- Ваш пульт FAAC / Genius — **slave**, он не умеет передавать код программирования.
- До приёмника не добраться.
- Инсталляции **Erreka**, где у всех пультов один Seed.
- **Старые BFT Mitto** с уникальным Seed, если не получается через кнопку программирования (новые BFT вычисляют Seed из серийника и декодируются обычным Read).

Если пульт можно перевести в режим программирования, Seed часто передаётся открыто — так быстрее, см. [Привязка нового пульта](/ru/subghz/remote-prog).

## Запись

1. Откройте `Main Menu → Apps → Sub-GHz → Seed Capturer`.
2. Выберите `New capture`.
3. **Remote type:** `FAAC SLH`, `Genius`, `Erreka` или `BFT Mitto`.
4. **Frequency:** `433.92 MHz  AM650` или `868.35 MHz  AM650` (у `BFT Mitto` только 433.92 МГц).
5. Нажимайте **одну и ту же кнопку одного и того же пульта** раз за разом, примерно раз в секунду, держа пульт вплотную к Флипперу.
6. Следите за экраном:
   - `Fix XXXXXXXX` — фиксированная часть; приложение цепляется за первый услышанный пульт;
   - `Hops n/10  Xpkt` — сколько собрано **разных** hop и число принятых пакетов;
   - статус `Hop n: XXXXXXXX` при каждом новом.
7. Начиная с **2 hop** на <kbd>OK</kbd> появляется `Save`. Нажмите — приложение покажет `Saved N hops` и имя файла.

<kbd>←</kbd> (`Reset`) сбрасывает запись, чтобы зацепиться за другой пульт или кнопку.

| Статус | Значение |
|---|---|
| `Hop n: XXXXXXXX` | новая динамическая часть сохранена — жмите дальше |
| `Other remote XXXXXXXX` | другой пульт или другая кнопка — пропущено |
| `Same hop, ignored` | повтор прошлого нажатия |
| `Have 10, enough` | всё собрано — жмите `Save` |

**Сколько нажатий:** минимум 2, лучше 5–10. Не менее важно, чтобы нажатия шли **подряд без пропусков** — проверяйте, что `Hops` растёт на каждое нажатие. Если пропустили — `Reset` и заново.

::: warning
У **FAAC SLH и Genius Seed свой для каждой кнопки** — записывайте ту кнопку, которой будете пользоваться. У Erreka Seed на пульт (иногда на всю инсталляцию), у BFT Mitto — на пульт.
:::

## Другие пункты меню

- `Decode RAW file` — взять Fix/Hop из RAW-файла `.sub` (из `/ext/subghz`), записанного ранее через [Read RAW](/ru/subghz/read-raw); частота берётся из файла. Файл с ключом отклоняется (`Not a RAW capture`). Здесь <kbd>←</kbd> — `Back`, а не `Reset`.
- `Delete all captures` — спрашивает `Delete every capture file in subghz_seed_captures?` и удаляет записи.
- `Exit`.

## Файл записи

Файлы сохраняются в `/ext/apps_data/subghz_seed_captures/` с именем `<Type>_<Fix>_<дата-время>.txt`, например `Erreka_F00F1C9B_261008-142233.txt`. Это текстовый файл, **не воспроизводимый `.sub`**:

```text
Filetype: Flipper SubGhz Seed Capture
Version: 1
# Fix + Hop set for offline seed recovery, not a playable .sub
Received: 2026-10-08 14:22:33
Manufacturer: Erreka
Protocol: KeeLoq
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Fix: F00F1C9B
Hops: 3
# Hops in the order they were received
Hop: ...
Hop: ...
Hop: ...
```

## Восстановление Seed в qUnleashed

1. Подключите Флиппер к **qUnleashed** и откройте инструмент восстановления Seed. Он сам забирает записи из `subghz_seed_captures` — ничего копировать и переименовывать не нужно.
2. Выберите запись и запустите поиск (это перебор, поэтому его и считает не Флиппер).
3. Если Seed найден, qUnleashed может собрать готовый `.sub` клона (серийник и кнопка из `Fix`, плюс Seed и счётчик) и положить его на Флиппер.
4. Если не найден — скорее всего в записи был пропуск; запишите заново, аккуратно.

Зная Seed, пульт можно собрать и вручную в `Sub-GHz → Add Manually [Advanced]`: свой `SERIAL` + `SEED` — новый пульт; `SERIAL`/`BUTTON` оригинала + `SEED` + чуть больший `COUNTER` — клон. Клон конфликтует с оригиналом по счётчику — см. [Динамические коды](/ru/subghz/rolling-codes).

::: warning
Только для своих пультов и приёмников.
:::

## Связанные страницы

- [Привязка нового пульта](/ru/subghz/remote-prog) · [KeeLoq](/ru/subghz/keeloq) · [Add manually](/ru/subghz/add-manually)
- [Приложение qUnleashed](/ru/mobile/qunleashed-app)
