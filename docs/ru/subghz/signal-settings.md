---
title: Signal Settings
order: 95
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-src]
---
# Signal Settings

**Signal Settings** правит уже сохранённый сигнал: его режим счётчика, текущий счётчик и код кнопки. Это
небольшой экран для опытных пользователей: он скрыт, пока не включён Debug, и почти всё в нём работает только на
тех немногих протоколах, которые поддерживают [режимы счётчика](/ru/subghz/counter-mode).

## Где он находится {#where}

Это пункт в меню сохранённого сигнала, а не пункт главного меню Sub-GHz. Откройте файл через `Sub-GHz → Saved`
(или из [Archive](/ru/apps/archive)) — меню будет таким:

`Emulate` · `Rename` · `Delete` · `Signal Settings`

## Как его показать {#enable}

`Signal Settings` добавляется в это меню только при включённом **Debug**. Если Debug выключен, пункта нет.

- Быстрый способ: долгое нажатие <kbd>↓</kbd> на рабочем столе, затем долгое <kbd>OK</kbd> на информационном
  экране ([Рабочий стол → Информационный экран](/ru/start/desktop#info-screen)).
- Или `Settings → System → Debug` = `ON` ([Настройки](/ru/start/settings)).

## Три пункта {#items}

![Signal Settings: Counter Mode, Edit Counter и Edit Button](/screens/subghz/signal_settings.png)

| Пункт | Что делает |
|---|---|
| `Counter Mode` | <kbd>←</kbd>/<kbd>→</kbd> выбирают `System` (режим 0) или `Mode 1` … до предела протокола. Выбор сразу записывается в `.sub`-файл строкой `CounterMode:`, после чего файл перезагружается; ничего не передаётся |
| `Edit Counter` | <kbd>OK</kbd> открывает HEX-ввод текущего счётчика с заголовком `Enter <N>-bits counter in HEX`, где N — длина счётчика протокола: 4 HEX-цифры (2 байта) до 16 бит и 8 цифр (4 байта) свыше |
| `Edit Button` | <kbd>OK</kbd> открывает HEX-ввод кода кнопки с заголовком `Enter <N>-bits button in HEX` — всегда один байт, 2 HEX-цифры |

Текущее значение каждого пункта показано в его строке, в HEX. Что сами режимы делают со счётчиком и как задать
режим правкой файла на ПК — на странице [Режимы счётчика](/ru/subghz/counter-mode#modes-by-protocol).

::: warning Подтверждение правки счётчика или кнопки выходит в эфир
`Edit Counter` и `Edit Button` записывают файл через путь передачи: прошивка запускает отправку с новым значением
и сразу останавливает её, а файл перезаписывается в момент остановки. Радио включается на мгновение, поэтому
делайте это подальше от приёмника, который не хотите открыть.

Счётчик сохраняется ровно таким, каким вы его ввели: для этой одной перезаписи режим счётчика и шаг
[Counter Incr.](/ru/subghz/settings) не применяются. При правке кнопки шаг вместо этого выставляется в 0, так что
смена кнопки не сдвигает счётчик.

Если отправка отклонена — частота, на которой эта прошивка не передаёт, — файл не записывается вовсе.
:::

## Протоколы с режимами счётчика {#protocols}

`Counter Mode` разблокирован для пяти протоколов. `System` — это режим 0, обычный:

| Протокол | Варианты |
|---|---|
| Nice FloR-S | `System`, `Mode 1`–`Mode 2` |
| CAME Atomo | `System`, `Mode 1`–`Mode 3` |
| Alutech AT-4N | `System`, `Mode 1`–`Mode 2` |
| KeeLoq | `System`, `Mode 1`–`Mode 10` |
| `Phoenix_V2` (V2 Phoenix) | `System`, `Mode 1`–`Mode 2` |

Сравнение идёт по строке `Protocol:` в файле. На остальных протоколах пункт заблокирован.

## Заблокированные пункты {#locked}

Заблокированный пункт нельзя открыть или изменить, при нажатии он показывает `Not available for this protocol !`

- `Counter Mode` — протокол файла не входит в пятёрку выше.
- `Edit Counter` — у протокола нет счётчика. Это зависит и от производителя: у KeeLoq пункт заблокирован для
  `AN-Motors`, у которого есть только псевдосчётчик, и для `Unknown`.
- `Edit Button` — в посылке протокола нет кода кнопки.

`Edit Button` разблокирован и на статических протоколах, у которых есть код кнопки, — Princeton, Dooya, GangQi,
Hollarm, Nord ICE, Proteco и Roger, — и работает там точно так же, как на динамическом сигнале.

## См. также {#related}

- [Режимы счётчика](/ru/subghz/counter-mode) — что делает каждый режим и строка `CounterMode:` в файле
- [Динамические коды](/ru/subghz/rolling-codes) · [Формат .sub](/ru/subghz/file-format)
- [Рабочий стол](/ru/start/desktop#info-screen) — быстрое переключение Debug ·
  [Настройки](/ru/start/settings) — Debug в меню
