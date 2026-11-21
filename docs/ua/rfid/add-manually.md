---
title: Додавання ключів вручну
order: 30
original: [https://docs.flipper.net/zero/rfid/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Додавання ключів 125 кГц вручну

Ключ можна створити й без фізичної мітки: виберіть протокол і введіть дані. Результат зберігається так само, як
прочитаний ключ, і його можна емулювати або [записати на заготовку](/ua/rfid/write).

**Коли це потрібно:** якщо ви знаєте номер, надрукований на карті чи записаний у базі системи контролю доступу,
хочете відновити ключ за своїми нотатками або перевірити зчитувач із конкретним ID.

## Порядок дій

1. Відкрийте `Main Menu → 125 kHz RFID → Add Manually`.
2. Виберіть зі списку протокол або формат (див. нижче).

   ![Список типів міток в Add Manually: EM-Micro EM4100, EM4100/32, EM4100/16 і Casi-Rusco C10106](/screens/lfrfid/add_manually.png)

3. Для форматів, що мають поля facility code / номер карти, ви отримаєте вибір:
   - **Enter FC/ID** — вводити десяткові поля одне за одним. У заголовку видно назву поля та діапазон, наприклад
     `Facility Code (0-255)`. <kbd>Back</kbd> повертає до попереднього поля.
   - **Enter Hex Data** — вводити сирі байти.

   Решта протоколів одразу переходять до hex-редактора *Enter the data in hex*.

   ![Редактор «Enter the data in hex»: байти мітки над екранною hex-клавіатурою](/screens/lfrfid/add_manually_data.png)

4. Введіть назву і збережіть. Ключ зберігається як `/ext/lfrfid/<name>.rfid`.

Щоб змінити збережений ключ пізніше: `Saved` → ключ → **Edit** (hex-редактор, та сама назва файлу).

::: tip Unleashed
Введення **FC / номера карти** замість hex, додаткові формати **HID** та **Casi-Rusco** — це доробки Unleashed.
Стокова прошивка приймає лише hex. Контрольні суми та парність Wiegand розраховуються за вас.
:::

## Список у порядку, як на пристрої

| Пункт меню | Зберігається як (`Key type`) | Введення | Байтів у hex |
|---|---|---|---|
| EM-Micro EM4100 | EM4100 | FC/ID або hex | 5 |
| EM-Micro EM4100/32 | EM4100/32 | FC/ID або hex | 5 |
| EM-Micro EM4100/16 | EM4100/16 | FC/ID або hex | 5 |
| Casi-Rusco C10106 | EM4100/32 | Credential + Card Number | — |
| Electra | Electra | hex | 8 |
| HID H10301 | H10301 | FC/ID або hex | 3 |
| HID H10304 | HIDProx | FC + Card Number | — |
| HID H10302 | HIDProx | Card Number | — |
| HID S10401 | HIDProx | FC + Card Number | — |
| HID H10306 | HIDProx | FC + Card Number | — |
| HID Corp1000-35 | HIDProx | FC + Card Number | — |
| IDTECK Idteck | Idteck | hex | 8 |
| Motorola Indala26 | Indala26 | hex | 4 |
| Kantech IoProxXSF | IoProxXSF | FC/ID або hex | 4 |
| AWID | AWID | FC/ID або hex | 9 |
| FECAVA FDX-A | FDX-A | hex | 5 |
| ISO FDX-B | FDX-B | hex | 11 |
| Generic HIDProx | HIDProx | hex | 6 |
| Generic HIDExt | HIDExt | hex | 12 |
| Farpointe Pyramid | Pyramid | FC/ID або hex | 4 |
| Viking | Viking | hex | 4 |
| Jablotron | Jablotron | hex | 5 |
| Paradox | Paradox | hex | 6 |
| PAC/Stanley | PAC/Stanley | hex | 4 |
| Keri | Keri | hex | 4 |
| Gallagher | Gallagher | FC/ID або hex | 8 |
| Honeywell Nexwatch | Nexwatch | hex | 8 |
| Securakey Radio Key | Radio Key | hex | 6 |
| Guardall GProxII | GProxII | hex | 12 |
| Noralsy | Noralsy | hex | 12 |
| Motorola Indala224 | Indala224 | hex | 28 |

## Діапазони полів для «Enter FC/ID»

| Формат | Поля (десяткові) |
|---|---|
| EM4100, EM4100/32, EM4100/16 | Facility Code 0–255, Card Number 0–65535 (зберігаються в останніх 3 байтах, перші 2 байти нульові) |
| HID H10301 (26-бітний Wiegand) | Facility Code 0–255, Card Number 0–65535 |
| AWID | Facility Code 0–255, Card Number 0–65535 (26-бітний формат, парність додається) |
| Farpointe Pyramid | Facility Code 0–255, Card Number 0–65535 (26 бітів, парність і CRC додаються) |
| Kantech IoProxXSF | Facility Code 0–255, Card Number 0–65535, Version 0–255 (контрольна сума додається) |
| Gallagher | Facility Code 0–65535, Card Number 0–16777215, Region Code 0–15, Issue Level 0–15 |
| Casi-Rusco C10106 | Credential 150000–159999, Card Number 0–457681 (так, як їх друкує система доступу; зберігається як EM4100/32) |
| HID H10304 (37 бітів) | Facility Code 0–65535, Card Number 0–524287 |
| HID H10302 (37 бітів) | Лише Card Number (35 бітів) |
| HID S10401 (37 бітів) | Facility Code 0–63, Card Number (29 бітів) |
| HID H10306 (34 біти) | Facility Code 0–65535, Card Number 0–65535 |
| HID Corp1000-35 (35 бітів) | Facility Code 0–4095, Card Number 0–1048575 |

::: info Великі номери карт
Поле введення числа тримає знакове 32-бітове значення, тому найвищу частину поля, ширшого за 31 біт (наприклад,
35-бітного номера карти в H10302), можна ввести лише через **Enter Hex Data** / **Edit**.
:::

## Поради

- Надрукований на EM4100 номер на зразок `0001234567` — це зазвичай форма **DEZ 10**; після збереження порівняйте
  його на екрані **Info** (там видно FC/Card, DEZ 8 і DEZ 10), щоб переконатися, що ви ввели правильне значення.

  ![Екран Info збереженої мітки: назва файлу, EM-Micro EM4100, hex-дані, FC/Card, DEZ 8 і DEZ 10](/screens/lfrfid/saved_info.png)

- EM4100/32 і EM4100/16 — це той самий кадр на бітрейтах RF/32 і RF/16; виберіть той, яким читається оригінал.
- Для протоколів, де є лише hex-введення, найпростіший спосіб отримати правильні байти — один раз прочитати справжню
  мітку і скопіювати значення `Hex:`.

## Пов’язані сторінки

- [Протоколи](/ua/rfid/protocols) · [Формат файлу](/ua/rfid/file-format) · [Запис](/ua/rfid/write) ·
  [Читання](/ua/rfid/read)
