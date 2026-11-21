---
title: MIFARE Plus
order: 75
author: gromovyna
original: ["https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/nfc/MIFARE%20Plus%20Detection.md", https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_plus, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [unleashed-docs, unleashed-src, gromovyna]
---
# MIFARE Plus

**MIFARE Plus** — наступник MIFARE Classic від NXP. Він може працювати на кількох **рівнях безпеки**:

| Рівень | Поведінка | Що робить Flipper |
|---|---|---|
| **SL0** | Заводський стан / стан персоналізації | Визначає картку, емуляція UID |
| **SL1** | **Сумісність із MIFARE Classic** (Crypto-1) | Читає **як MIFARE Classic**: працюють словники, nested-атаки, MFKey, qUnleashed |
| **SL2** | Дані у стилі Classic з AES (немає в серіях EV) | Визначає картку, емуляція UID |
| **SL3** | ISO14443-4, автентифікація AES-128 і secure messaging | Словникова атака на ключі AES, повний дамп, повна емуляція, зворотний запис на вихідну картку |

Варіанти продукту: **Plus S**, **Plus X**, **Plus SE**, **Plus EV1**, **Plus EV2** (і загальний «Plus»); обсяги
1K (SE), 2K і 4K.

::: tip Unleashed
Визначення MIFARE Plus за продуктом/рівнем/обсягом, **зчитування SL3 зі словниками AES**, *Show Keys*, емуляція,
*Write to Initial Card* / *Update from Initial Card*, кеш ключів за UID і генератори MIFARE Plus у
*Add Manually* — це можливості Unleashed.
:::

## Зчитування

1. `Main Menu → NFC → Read`, піднесіть картку.
2. Картки **SL1** читаються як MIFARE Classic (див. [MIFARE Classic](/ua/nfc/mifare-classic)). Відновлення ключів
   для SL1 працює точно так само, як для Classic; у [посібнику з qUnleashed](/ua/nfc/qunleashed) @gromovyna
   зазначає, що це стосується MIFARE Plus **лише в SL1**.
3. Картки **SL3**: словникова атака на ключі AES запускається автоматично (заголовок **«MF Plus Dictionary»**).
   Спочатку перебираються користувацькі ключі, потім системний словник; ключ, закешований під час попереднього
   збереження картки з тим самим UID, пробується раніше за обидва. На екрані показані *Keys Found* /
   *Sectors Read*. Окремого пункту «Unlock with Dictionary» немає: атака є частиною `Read`.
4. Збережіть картку. Ключі кешуються у `/ext/nfc/.cache/<UID>.mfpkeys`, тому наступне зчитування тієї самої
   картки автентифікується з першої спроби.

Словники: системний `/ext/nfc/assets/mf_plus_dict.nfc` (33 ключі AES-128 із типових ключів Proxmark3),
користувацький `/ext/nfc/assets/mf_plus_dict_user.nfc`. Керувати ними можна в
`NFC → Extra Actions → MIFARE Plus Keys` (**Add** — додати 16-байтовий ключ, **List** — видалити).

### Меню для картки SL3

- Після зчитування: **Save**, **Emulate**, **Show Keys** (*«Found MFP Keys»*: ключі A/B по секторах та
  адміністративні ключі, як-от Card Master Key, плюс підсумки), **Info**.
- Збережена картка: **Emulate**, **Write to Initial Card** (записує дамп назад на ту саму картку),
  **Update from Initial Card** (перечитує вихідну картку збереженими ключами; для інших карток —
  *«Use the source card only»*), **Show Keys**, **Rename**, **Delete**, **Info**.
- `Info → More` відкриває хаб із **View Dump** (блоки, адміністративні ключі, конфігураційні блоки, підпис) і
  **ISO14443-4 Data** (ATS тощо) → **More** (поля GetVersion: виробник апаратної/програмної частини, тип,
  версія, обсяг, партія, тиждень/рік виробництва).

Для інших рівнів зберігається лише ідентичність картки й пропонується **Emulate UID**.

## Як визначається MIFARE Plus

Прошивка поєднує три ознаки:

1. **SAK**: `08` = 2K SL1, `18` = 4K SL1, `10` / `11` = 2K / 4K SL2, `20` = ISO14443-4 (SL3, але також SL0 і
   DESFire).
2. **Історичні байти ATS** вигляду `C1 05 …`: визначають Plus S / X / SE без жодного ключа.
3. **GetVersion** і проба рівня безпеки на серіях EV1/EV2, що дають достовірні тип і обсяг.

Оскільки SAK `20` спільний із DESFire, картка вважається Plus лише тоді, коли це підтверджує проба або відпечаток
ATS.

### Довідка: як це робить NXP TagInfo

У документації Unleashed є аналіз власного застосунку NXP **NFC TagInfo** (v6.2.0), який використано як
орієнтир. Його процедура прийняття рішень:

```text
NFC tag presented
├─ SAK ∈ {01,08,09,18,19,28,38,88,98,B8} → "Classic lane" (MifareClassic, SL1)
│   ├─ RATS (E0 80) → ATS, then DESELECT (C2)
│   │   match ATS historical bytes → S | X | SE | Engineering
│   ├─ Read-Signature (3C 00), status 90 → EV generation → EV1
│   ├─ security level = SL1 (answers Classic block auth)
│   └─ size = Plus AES First-Auth probe to increasing key-block addresses
└─ SAK == 20 → "ISO-DEP lane" (IsoDep, SL3/EV)
    ├─ SELECT VCA applet (00 A4 04 00 10 A0 00 00 03 96 56 43 41 …) succeeds → SL3
    ├─ GET_VERSION (60 … AF) → EV1 | EV2 (+ storage size)
    └─ size = GET_VERSION storage byte (22 = 2K, 42 = 4K)
```

Відпечатки ATS (історичні байти, побайтово точно):

| Історичні байти ATS | Підтип | Код продукту |
|---|---|---|
| `C1 05 2F 2F 00 35 C7` | Plus **S** | `MF1SPLUS` |
| `C1 05 2F 2F 01 BC D6` | Plus **X** | `MF1PLUS` |
| `C1 05 21 30 00 77 C1` | Plus **SE** | `MF1SEP10` |
| `C1 05 20 30 00 AB 9B` | Plus **SE** (альтернативний) | `MF1SEP10` |
| `4D 46 50 5F 45 4E 47` (`"MFP_ENG"`) | Інженерний зразок | — |
| немає відповідності | Plus **X** (типово) | `MF1PLUS` |

У родині `C1 05 2F 2F …` байт 4 відрізняє S (`00`) від X (`01`). Серії EV1/EV2 відповідають на
**Read-Signature** (`3C`), а Plus S/X — ні. У GetVersion байт виробника — `04` (NXP), а байт обсягу `22` = 2K,
`42` = 4K.

Трактування SAK, яке використовує TagInfo:

| SAK | Що означає |
|---|---|
| `08` | Classic 1K / Plus 2K SL1 |
| `18` | Classic 4K / Plus 4K SL1 |
| `09` | MIFARE Mini |
| `19` | Classic 2K / варіант Plus 2K |
| `28`, `38` | SmartMX із Classic 1K / 4K |
| `88` | NXP Classic 1K (біт 0x80) |
| `98`, `B8` | Варіанти SmartMX / Pro |
| `01` | застарілий маркер / TNP |
| `20` | ISO14443-4 → Plus SL3 / EV, DESFire |

Обсяг пам'яті в SL1 визначається кадрами Plus AES **First-Auth** `70 XX 40 01 00` до блоків ключів `0x4010`,
`0x4020`, `0x4040`, `0x4064`: найвища адреса, яка відповіла, обмежує кількість секторів (базовий / 2K / 4K /
розширений). Коди продуктів, які видаються: `MF1SPLUS60`/`80` (S 2K/4K), `MF1PLUS60`/`80` (X 2K/4K),
`MF1SEP10xx` (SE), `MF1P2101` (EV1 2K).

## Створення MIFARE Plus вручну

`NFC → Add Manually` пропонує Plus SE (UID на 4/7 байтів), Plus S, X, EV1 і EV2 в обсягах 2K/4K з UID на 4 або
7 байтів. Згенерована картка отримує відповідні історичні байти ATS, див.
[Додавання міток вручну](/ua/nfc/add-manually).

## Пов'язані сторінки

[MIFARE Classic](/ua/nfc/mifare-classic) · [Зчитування міток](/ua/nfc/read) · [qUnleashed](/ua/nfc/qunleashed) ·
[Формат файлів NFC](/ua/nfc/file-format)
