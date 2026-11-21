---
title: Підтримувані протоколи
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://docs.flipper.net/zero/rfid/read]
sources: [unleashed-src, flipper-docs]
---
# Підтримувані протоколи 125 кГц

Таблицю складено за вмістом `lib/lfrfid/protocols/` прошивки Unleashed. Усі протоколи можна **читати**,
**зберігати**, **емулювати** та **додавати вручну**; останні стовпці показують, які чипи-заготовки здатні їх нести
(див. [Запис](/ua/rfid/write)).

- **Назва** — так, як вона показується на екрані та зберігається у файлах `.rfid` як `Key type`.
- **Читання** — який прохід читання її розшифровує: ASK, PSK або обидва.
- **Байтів** — довжина поля `Data:`.

| Назва | Виробник | Читання | Байтів | Показані поля | T5577 | EM4305 | Hitag Micro¹ | 8268² |
|---|---|---|---|---|---|---|---|---|
| EM4100 | EM-Micro | ASK/PSK | 5 | FC, Card, CL, DEZ 8, DEZ 10 | ✓ | ✓ | ✓ | ✓ |
| EM4100/32 | EM-Micro | ASK/PSK | 5 | те саме (бітрейт RF/32) | ✓ | ✓ | ✓ | — |
| EM4100/16 | EM-Micro | ASK/PSK | 5 | те саме (бітрейт RF/16) | ✓ | ✓ | ✓ | — |
| Electra | Electra | ASK/PSK | 8 | Epilogue | ✓ | ✓ | — | — |
| H10301 | HID | ASK | 3 | FC, Card (26-бітний Wiegand) | ✓ | — | — | — |
| Idteck | IDTECK | PSK | 8 | FC, Card | ✓ | — | — | — |
| Indala26 | Motorola | PSK | 4 | FC, Card, Parity, Checksum | ✓ | — | — | — |
| Indala224 | Motorola | PSK | 28 | Raw | ✓ | — | — | — |
| IoProxXSF | Kantech | ASK | 4 | FC, Version, Card | ✓ | — | — | — |
| AWID | AWID | ASK | 9 | Format, FC, Card | ✓ | — | — | — |
| FDX-A | FECAVA | ASK | 5 | ID, Parity | ✓ | — | — | — |
| FDX-B | ISO | ASK | 11 | ID, країна, температура, позначка тварини… | ✓ | ✓ | — | — |
| HIDProx | Generic | ASK | 6 | довжина в бітах; відповідні формати HID | ✓ | — | — | — |
| HIDExt | Generic | ASK | 12 | — | ✓ | — | — | — |
| Pyramid | Farpointe | ASK | 4 | Format, FC, Card | ✓ | — | — | — |
| Viking | Viking | ASK | 4 | ID | ✓ | ✓ | — | — |
| Jablotron | Jablotron | ASK | 5 | Card | ✓ | ✓ | — | — |
| Paradox | Paradox | ASK | 6 | FC, Card, перевірка CRC | ✓ | — | — | — |
| PAC/Stanley | — | ASK | 4 | CIN | ✓ | — | — | — |
| Keri | Keri | PSK | 4 | Internal ID, FC, Card | ✓ | — | — | — |
| Gallagher | Gallagher | ASK | 8 | FC, Card, Region, Issue Level | ✓ | ✓ | — | — |
| Nexwatch | Honeywell | PSK | 8 | ID, Mode, Type | ✓ | — | — | — |
| Radio Key | Securakey | ASK | 6 | RKKT n-bit (FC, Card) або RKKTH відкритим текстом (Card) | ✓ | ✓ | — | — |
| GProxII | Guardall | ASK | 12 | FC, Card, LEN, XOR, CRC | ✓ | ✓ | — | — |
| Noralsy | Noralsy | ASK | 12 | Card ID, Year | ✓ | — | — | — |

¹ Hitag Micro — це цілі 8265/H5, 8210 і H5.5. ² 8268 (Hitag S) приймає лише EM4100 на бітрейті RF/64 і типово
вимкнений.

::: tip Unleashed
Порівняно зі списком в офіційній документації ця прошивка додає **Indala224** та прохід читання на **134,2 кГц** для
FDX-A/FDX-B. В офіційному описі формату файлу також бракує EM4100/32, EM4100/16, Electra, Nexwatch, Radio Key,
Noralsy та Indala224 — тут це дійсні значення `Key type`.
:::

## Зауваження щодо окремих протоколів

- **EM4100 / EM-Marin** — найпоширеніший тип брелока у Східній Європі («ЕМ-Марін»). 40-бітний ID; FC — це 3-й байт,
  номер карти — два останні. DEZ 8 / DEZ 10 — десяткові форми, надруковані на брелоках.
- **Casi-Rusco C10106** — це не окремий протокол, а кадр EM4100 (зазвичай RF/32). Якщо дані підходять, на екрані
  інформації додається рядок `or C10106: credential card`, а в Add Manually цей варіант пропонується як формат
  введення.
- **HIDProx** — узагальнений контейнер HID Prox на 26–37 бітів. Фліппер пробує відомі розкладки (H10304, H10302,
  S10401, H10306, Corp1000-35) і для кожного збігу виводить FC/номер карти.
- **Paradox** — на екрані інформації видно CRC, а якщо вона не збігається — *CRC Mismatch, Invalid Card!*.
- **Стара назва Indala26** — дуже давні файли з `Key type: I40134` під час завантаження перетворюються на Indala26.

## Пов’язані сторінки

- [Читання](/ua/rfid/read) · [Додавання вручну](/ua/rfid/add-manually) · [Запис](/ua/rfid/write) ·
  [Чипи для тварин](/ua/rfid/animal-microchips) · [Формат файлу](/ua/rfid/file-format)
