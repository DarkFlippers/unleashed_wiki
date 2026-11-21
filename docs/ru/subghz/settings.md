---
title: Radio Settings (настройки радио)
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/radio_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://docs.flipper.net/zero/sub-ghz]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Radio Settings (настройки радио)

`Main Menu → Sub-GHz → Radio Settings` — настройки, общие для всего приложения Sub-GHz: какой радиомодуль
используется, мощность передачи, имена файлов и поведение счётчика динамических кодов. Настройки приёма (частота,
модуляция, хоппинг, фильтры) находятся в `Read → Config` — см. [Read](/ru/subghz/read#config).

::: tip Unleashed
В стоковой прошивке в этом меню только выбор внутреннего/внешнего модуля. В Unleashed добавлены **TX Power**,
**Protocol Names**, **Counter Incr.**, а в режиме Debug — **Ext Amp & LEDs** и **Debug Pin**.
:::

## Пункты меню

![Radio Settings: Module, TX Power, Protocol Names и Counter Incr.](/screens/subghz/radio_settings.png)

| Пункт | Значения | Что делает |
|---|---|---|
| `Module` | `Internal`, `External` | Радиомодуль для приёма и передачи. `External` доступен, только если на GPIO обнаружен внешний CC1101; если модуль не отвечает, Флиппер возвращается на `Internal` |
| `TX Power` | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | Мощность передачи. `Preset` — как задано в пресете модуляции (по умолчанию). Низкие значения удобны для тестов на коротком расстоянии |
| `Protocol Names` | `OFF` / `ON` | При `ON` автоматические имена файлов содержат имя протокола + метку времени, а не только время/случайное имя |
| `Counter Incr.` | `+1`, `+2`, `+3` (обычный режим) | На сколько увеличивается счётчик динамического кода при каждой передаче. По умолчанию `+1` |

Дополнительно в **режиме Debug** (`Settings → System → Debug → ON`):

| Пункт | Значения | Что делает |
|---|---|---|
| `Counter Incr.` | `+1` `+2` `+3` `+4` `+5` `+10` `+50` `OVFL` `OFEX` `No` `-1` `-2` `-3` `-4` `-5` `-10` `-50` | Полный набор шагов счётчика для экспериментов: большие прыжки, `OVFL` (шаг 65535), `OFEX` (особый режим), `No` (счётчик не меняется) и отрицательные шаги |
| `Ext Amp & LEDs` | `ON` / `OFF` | Управление пином усилителя / светодиодов внешних модулей (GPIO PC3, как у модулей E07). По умолчанию `ON`. Выключите, если на вашем модуле этот пин занят под другое |
| `Debug Pin` | `OFF` / `17(1W)` | Дублирует сигнал данных радио на GPIO-пин 17 (1-Wire) — для разработки протоколов с логическим анализатором |

`TX Power`, `Protocol Names` и `Ext Amp & LEDs` сохраняются сразу (в `/ext/subghz/assets/last_subghz.settings`).
`Counter Incr.` не сохраняется: значение действует до перезагрузки Флиппера, потом снова `+1`.

::: warning Шаг счётчика
Большие и отрицательные шаги — для экспериментов **со своими приёмниками**. Прыжок счётчика далеко вперёд навсегда
уводит сохранённый в приёмнике счётчик дальше вашего оригинального пульта, а шаг назад заставит приёмник игнорировать
посылки. Чтобы Флиппер уживался с оригиналом, используйте [Режимы счётчика](/ru/subghz/counter-mode) или создайте
новый пульт через [Add Manually](/ru/subghz/add-manually). Теория — [Динамические коды](/ru/subghz/rolling-codes).
:::

## Другие настройки на SD-карте

| Файл | Назначение | Подробнее |
|---|---|---|
| `/ext/subghz/assets/setting_user` | Свои частоты, список хоппинга, частота по умолчанию, свои пресеты модуляции | [Частоты](/ru/subghz/frequencies#adding-frequencies), [Форматы файлов](/ru/subghz/file-format#setting-user) |
| `/ext/subghz/assets/dangerous_settings` | Расширенный (вне спецификации) диапазон частот | [Частоты](/ru/subghz/frequencies#extended-range) |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Свои ключи производителей KeeLoq | [Форматы файлов](/ru/subghz/file-format#keeloq-mfcodes-user), [KeeLoq](/ru/subghz/keeloq) |
| `/ext/subghz/assets/last_subghz.settings` | Последние частота, модуляция, фильтры, триггер анализатора — пишет само приложение | вручную не редактировать |

Файлы `.example` — шаблоны: переименуйте в `…_user`, чтобы они заработали. Файлы `_user` не перезаписываются при
обновлении прошивки.

## Частые проблемы

- **В `Module` только `Internal`** — внешний CC1101 не обнаружен. Проверьте подключение и питание, зайдите в меню
  заново. См. [Внешний CC1101](/ru/subghz/external-cc1101).
- **Слабая передача** — проверьте, не стоит ли `TX Power` на отрицательном значении.
- **Имена файлов — только даты** — включите `Protocol Names`.
- **Нет пунктов `Ext Amp & LEDs` / `Debug Pin`** — они видны только в режиме Debug.

## См. также

- [Read → Config](/ru/subghz/read#config) · [Частоты](/ru/subghz/frequencies) · [Внешний CC1101](/ru/subghz/external-cc1101)
- [Режимы счётчика](/ru/subghz/counter-mode) · [Форматы файлов](/ru/subghz/file-format) · [Опасные настройки](/ru/start/dangerous-settings)
