---
title: Поддерживаемые протоколы
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://docs.flipper.net/zero/rfid/read]
sources: [unleashed-src, flipper-docs]
---
# Поддерживаемые 125 кГц протоколы

Таблица составлена по `lib/lfrfid/protocols/` прошивки Unleashed. Все протоколы можно **читать**, **сохранять**,
**эмулировать** и **добавлять вручную**; последние столбцы — на какие заготовки их можно записать (см.
[Запись](/ru/rfid/write)).

- **Имя** — как на экране и в поле `Key type` файлов `.rfid`.
- **Чтение** — каким проходом декодируется: ASK, PSK или оба.
- **Байт** — длина поля `Data:`.

| Имя | Производитель | Чтение | Байт | Отображаемые поля | T5577 | EM4305 | Hitag Micro¹ | 8268² |
|---|---|---|---|---|---|---|---|---|
| EM4100 | EM-Micro | ASK/PSK | 5 | FC, Card, CL, DEZ 8, DEZ 10 | ✓ | ✓ | ✓ | ✓ |
| EM4100/32 | EM-Micro | ASK/PSK | 5 | то же (скорость RF/32) | ✓ | ✓ | ✓ | — |
| EM4100/16 | EM-Micro | ASK/PSK | 5 | то же (скорость RF/16) | ✓ | ✓ | ✓ | — |
| Electra | Electra | ASK/PSK | 8 | Epilogue | ✓ | ✓ | — | — |
| H10301 | HID | ASK | 3 | FC, Card (26-бит Wiegand) | ✓ | — | — | — |
| Idteck | IDTECK | PSK | 8 | FC, Card | ✓ | — | — | — |
| Indala26 | Motorola | PSK | 4 | FC, Card, Parity, Checksum | ✓ | — | — | — |
| Indala224 | Motorola | PSK | 28 | Raw | ✓ | — | — | — |
| IoProxXSF | Kantech | ASK | 4 | FC, Version, Card | ✓ | — | — | — |
| AWID | AWID | ASK | 9 | Format, FC, Card | ✓ | — | — | — |
| FDX-A | FECAVA | ASK | 5 | ID, Parity | ✓ | — | — | — |
| FDX-B | ISO | ASK | 11 | ID, страна, температура, флаг животного… | ✓ | ✓ | — | — |
| HIDProx | Generic | ASK | 6 | длина в битах; подходящие форматы HID | ✓ | — | — | — |
| HIDExt | Generic | ASK | 12 | — | ✓ | — | — | — |
| Pyramid | Farpointe | ASK | 4 | Format, FC, Card | ✓ | — | — | — |
| Viking | Viking | ASK | 4 | ID | ✓ | ✓ | — | — |
| Jablotron | Jablotron | ASK | 5 | Card | ✓ | ✓ | — | — |
| Paradox | Paradox | ASK | 6 | FC, Card, проверка CRC | ✓ | — | — | — |
| PAC/Stanley | — | ASK | 4 | CIN | ✓ | — | — | — |
| Keri | Keri | PSK | 4 | Internal ID, FC, Card | ✓ | — | — | — |
| Gallagher | Gallagher | ASK | 8 | FC, Card, Region, Issue Level | ✓ | ✓ | — | — |
| Nexwatch | Honeywell | PSK | 8 | ID, Mode, Type | ✓ | — | — | — |
| Radio Key | Securakey | ASK | 6 | RKKT n-bit (FC, Card) или RKKTH plaintext (Card) | ✓ | ✓ | — | — |
| GProxII | Guardall | ASK | 12 | FC, Card, LEN, XOR, CRC | ✓ | ✓ | — | — |
| Noralsy | Noralsy | ASK | 12 | Card ID, Year | ✓ | — | — | — |

¹ Hitag Micro — цели 8265/H5, 8210 и H5.5. ² 8268 (Hitag S) принимает только EM4100 на скорости RF/64 и по умолчанию
выключен.

::: tip Unleashed
По сравнению со списком в официальной документации прошивка добавляет **Indala224** и проход чтения на **134,2 кГц**
для FDX-A/FDX-B. В официальном описании формата файлов также нет EM4100/32, EM4100/16, Electra, Nexwatch, Radio Key,
Noralsy и Indala224 — здесь это допустимые значения `Key type`.
:::

## Заметки по протоколам

- **EM4100 / EM-Marin** — самый распространённый тип брелоков в СНГ («ЕМ-Марин»). 40-битный ID; FC — 3-й байт, номер
  карты — два последних. DEZ 8 / DEZ 10 — десятичные формы, которые печатают на брелоках.
- **Casi-Rusco C10106** — не отдельный протокол, а кадр EM4100 (обычно RF/32). Если данные подходят, на экране
  информации появляется строка `or C10106: credential card`, а в Add Manually есть такой формат ввода.
- **HIDProx** — общий контейнер HID Prox на 26–37 бит. Флиппер примеряет известные раскладки (H10304, H10302, S10401,
  H10306, Corp1000-35) и выводит FC/номер для каждого совпадения.
- **Paradox** — на экране видно CRC и *CRC Mismatch, Invalid Card!*, если не совпало.
- **Старое имя Indala26** — очень старые файлы с `Key type: I40134` при загрузке конвертируются в Indala26.

## Связанные страницы

- [Чтение](/ru/rfid/read) · [Добавление вручную](/ru/rfid/add-manually) · [Запись](/ru/rfid/write) ·
  [Чипы животных](/ru/rfid/animal-microchips) · [Формат файлов](/ru/rfid/file-format)
