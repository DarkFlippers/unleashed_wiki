---
title: Добавление вручную
order: 30
original: [https://docs.flipper.net/zero/rfid/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Добавление 125 кГц ключей вручную

Ключ можно создать без физической метки: выбрать протокол и ввести данные. Результат сохраняется как прочитанный
ключ — его можно эмулировать или [записать на заготовку](/ru/rfid/write).

**Когда пригодится:** знаете номер, напечатанный на карте / записанный в базе СКУД, восстанавливаете ключ по записям
или тестируете считыватель с конкретным ID.

## Порядок действий

1. Откройте `Main Menu → 125 kHz RFID → Add Manually`.
2. Выберите протокол / формат из списка (см. ниже).

   ![Список типов меток в Add Manually: EM-Micro EM4100, EM4100/32, EM4100/16 и Casi-Rusco C10106](/screens/lfrfid/add_manually.png)

3. Для форматов с кодом объекта / номером карты появится выбор:
   - **Enter FC/ID** — ввод десятичных полей по одному. В заголовке — имя поля и диапазон, например
     `Facility Code (0-255)`. <kbd>Back</kbd> возвращает к предыдущему полю.
   - **Enter Hex Data** — ввод сырых байтов.

   Остальные протоколы сразу открывают hex-редактор *Enter the data in hex*.

   ![Hex-редактор «Enter the data in hex»: байты ключа и экранная клавиатура с цифрами и буквами](/screens/lfrfid/add_manually_data.png)

4. Введите имя и сохраните. Ключ сохраняется как `/ext/lfrfid/<имя>.rfid`.

Изменить сохранённый ключ позже: `Saved` → ключ → **Edit** (hex-редактор, имя файла то же).

::: tip Unleashed
Ввод **FC / номера карты** вместо hex, дополнительные форматы **HID** и **Casi-Rusco** — добавления Unleashed. Стоковая
прошивка принимает только hex. Контрольные суммы и чётность Wiegand считаются автоматически.
:::

## Список — в порядке на устройстве

| Пункт меню | Сохраняется как (`Key type`) | Ввод | Байт hex |
|---|---|---|---|
| EM-Micro EM4100 | EM4100 | FC/ID или hex | 5 |
| EM-Micro EM4100/32 | EM4100/32 | FC/ID или hex | 5 |
| EM-Micro EM4100/16 | EM4100/16 | FC/ID или hex | 5 |
| Casi-Rusco C10106 | EM4100/32 | Credential + Card Number | — |
| Electra | Electra | hex | 8 |
| HID H10301 | H10301 | FC/ID или hex | 3 |
| HID H10304 | HIDProx | FC + Card Number | — |
| HID H10302 | HIDProx | Card Number | — |
| HID S10401 | HIDProx | FC + Card Number | — |
| HID H10306 | HIDProx | FC + Card Number | — |
| HID Corp1000-35 | HIDProx | FC + Card Number | — |
| IDTECK Idteck | Idteck | hex | 8 |
| Motorola Indala26 | Indala26 | hex | 4 |
| Kantech IoProxXSF | IoProxXSF | FC/ID или hex | 4 |
| AWID | AWID | FC/ID или hex | 9 |
| FECAVA FDX-A | FDX-A | hex | 5 |
| ISO FDX-B | FDX-B | hex | 11 |
| Generic HIDProx | HIDProx | hex | 6 |
| Generic HIDExt | HIDExt | hex | 12 |
| Farpointe Pyramid | Pyramid | FC/ID или hex | 4 |
| Viking | Viking | hex | 4 |
| Jablotron | Jablotron | hex | 5 |
| Paradox | Paradox | hex | 6 |
| PAC/Stanley | PAC/Stanley | hex | 4 |
| Keri | Keri | hex | 4 |
| Gallagher | Gallagher | FC/ID или hex | 8 |
| Honeywell Nexwatch | Nexwatch | hex | 8 |
| Securakey Radio Key | Radio Key | hex | 6 |
| Guardall GProxII | GProxII | hex | 12 |
| Noralsy | Noralsy | hex | 12 |
| Motorola Indala224 | Indala224 | hex | 28 |

## Диапазоны полей для «Enter FC/ID»

| Формат | Поля (десятичные) |
|---|---|
| EM4100, EM4100/32, EM4100/16 | Facility Code 0–255, Card Number 0–65535 (в последних 3 байтах, первые 2 — нули) |
| HID H10301 (26-бит Wiegand) | Facility Code 0–255, Card Number 0–65535 |
| AWID | Facility Code 0–255, Card Number 0–65535 (26-битный формат, чётность добавляется) |
| Farpointe Pyramid | Facility Code 0–255, Card Number 0–65535 (26 бит, чётность и CRC добавляются) |
| Kantech IoProxXSF | Facility Code 0–255, Card Number 0–65535, Version 0–255 (контрольная сумма добавляется) |
| Gallagher | Facility Code 0–65535, Card Number 0–16777215, Region Code 0–15, Issue Level 0–15 |
| Casi-Rusco C10106 | Credential 150000–159999, Card Number 0–457681 (как печатает система доступа; сохраняется как EM4100/32) |
| HID H10304 (37 бит) | Facility Code 0–65535, Card Number 0–524287 |
| HID H10302 (37 бит) | Только Card Number (35 бит) |
| HID S10401 (37 бит) | Facility Code 0–63, Card Number (29 бит) |
| HID H10306 (34 бита) | Facility Code 0–65535, Card Number 0–65535 |
| HID Corp1000-35 (35 бит) | Facility Code 0–4095, Card Number 0–1048575 |

::: info Большие номера
Поле ввода числа хранит знаковое 32-битное значение, поэтому самый верх полей шире 31 бита (например, 35-битный номер
H10302) можно ввести только через **Enter Hex Data** / **Edit**.
:::

## Советы

- Номер на брелоке EM4100 вида `0001234567` — обычно это форма **DEZ 10**; после сохранения сверьте его на экране
  **Info** (там FC/Card, DEZ 8 и DEZ 10), чтобы убедиться, что ввели верно.

  ![Экран Info сохранённой метки: имя файла, EM-Micro EM4100, hex-данные, FC/Card, DEZ 8 и DEZ 10](/screens/lfrfid/saved_info.png)

- EM4100/32 и EM4100/16 — тот же кадр на скоростях RF/32 и RF/16; выбирайте тот, каким читается оригинал.
- Для протоколов только с hex-вводом проще всего один раз прочитать настоящую метку и переписать значение `Hex:`.

## Связанные страницы

- [Протоколы](/ru/rfid/protocols) · [Формат файлов](/ru/rfid/file-format) · [Запись](/ru/rfid/write) ·
  [Чтение](/ru/rfid/read)
