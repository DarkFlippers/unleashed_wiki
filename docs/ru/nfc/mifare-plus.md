---
title: MIFARE Plus
order: 75
author: gromovyna
original: ["https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/nfc/MIFARE%20Plus%20Detection.md", https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_plus, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [unleashed-docs, unleashed-src, gromovyna]
---
# MIFARE Plus

**MIFARE Plus** — преемник MIFARE Classic от NXP. Может работать на разных **уровнях безопасности** (security level):

| Уровень | Поведение | Что делает Флиппер |
|---|---|---|
| **SL0** | Заводское состояние / персонализация | Определяет метку, эмуляция UID |
| **SL1** | **Совместим с MIFARE Classic** (Crypto-1) | Читается **как MIFARE Classic**: словари, nested, MFKey, qUnleashed — всё работает |
| **SL2** | Данные в стиле Classic с AES (нет у EV-версий) | Определяет метку, эмуляция UID |
| **SL3** | ISO14443-4, аутентификация AES-128 и secure messaging | Атака по словарю AES-ключей, полный дамп, полная эмуляция, запись на исходную метку |

Варианты продукта: **Plus S**, **Plus X**, **Plus SE**, **Plus EV1**, **Plus EV2** (и общий «Plus»); объём 1K (SE),
2K и 4K.

::: tip Unleashed
Определение MIFARE Plus по продукту/уровню/объёму, **чтение SL3 по словарям AES**, *Show Keys*, эмуляция,
*Write to Initial Card* / *Update from Initial Card*, кеш ключей по UID и генераторы MIFARE Plus в *Add Manually* —
возможности Unleashed.
:::

## Чтение

1. `Main Menu → NFC → Read`, приложите метку.
2. Метки **SL1** читаются как MIFARE Classic (см. [MIFARE Classic](/ru/nfc/mifare-classic)). Восстановление ключей для
   SL1 работает так же, как для Classic; в [гайде по qUnleashed](/ru/nfc/qunleashed) @gromovyna отмечает, что он
   применим к Mifare Plus **только SL1**.
3. Метки **SL3**: атака по словарю AES-ключей запускается сама (заголовок **«MF Plus Dictionary»**). Сначала
   пользовательские ключи, потом системный словарь; перед ними — ключ из кеша, если этот UID уже сохраняли. На экране
   *Keys Found* / *Sectors Read*. Отдельного пункта «Unlock with Dictionary» нет — атака входит в `Read`.
4. Сохраните метку. Ключи кешируются в `/ext/nfc/.cache/<UID>.mfpkeys`, так что следующее чтение той же метки
   аутентифицируется с первой попытки.

Словари: системный `/ext/nfc/assets/mf_plus_dict.nfc` (33 ключа AES-128 из дефолтов Proxmark3), пользовательский
`/ext/nfc/assets/mf_plus_dict_user.nfc`. Управление — `NFC → Extra Actions → MIFARE Plus Keys` (**Add** 16-байтный
ключ, **List** для удаления).

### Меню для метки SL3

- После чтения: **Save**, **Emulate**, **Show Keys** (*«Found MFP Keys»*: ключи A/B по секторам и admin-ключи, например
  Card Master Key, плюс итоги), **Info**.
- Сохранённая метка: **Emulate**, **Write to Initial Card** (записать дамп обратно на ту же метку), **Update from
  Initial Card** (перечитать исходную метку сохранёнными ключами; для других — *«Use the source card only»*),
  **Show Keys**, **Rename**, **Delete**, **Info**.
- `Info → More` — меню с **View Dump** (блоки, admin-ключи, конфиг-блоки, подпись) и **ISO14443-4 Data** (ATS и т.д.)
  → **More** (поля GetVersion: hardware/software vendor, тип, версия, объём, batch, неделя/год производства).

Для остальных уровней сохраняется только идентификация и доступно **Emulate UID**.

## Как определяется MIFARE Plus

Прошивка объединяет три признака:

1. **SAK**: `08` = 2K SL1, `18` = 4K SL1, `10` / `11` = 2K / 4K SL2, `20` = ISO14443-4 (SL3, но также SL0 и DESFire).
2. **Исторические байты ATS** вида `C1 05 …` — определяют Plus S / X / SE без всяких ключей.
3. **GetVersion** и проба уровня безопасности на EV1/EV2 — дают точный тип и объём.

Так как SAK `20` общий с DESFire, метка считается Plus, только если это подтвердила проба или отпечаток ATS.

### Справочно: как это делает NXP TagInfo

В документации Unleashed есть разбор собственного приложения NXP **NFC TagInfo** (v6.2.0), использованный как
эталон. Порядок принятия решения:

```text
NFC tag presented
├─ SAK ∈ {01,08,09,18,19,28,38,88,98,B8} → «Classic lane» (MifareClassic, SL1)
│   ├─ RATS (E0 80) → ATS, затем DESELECT (C2)
│   │   сверка исторических байтов ATS → S | X | SE | Engineering
│   ├─ Read-Signature (3C 00), статус 90 → поколение EV → EV1
│   ├─ уровень безопасности = SL1 (отвечает на Classic-аутентификацию блока)
│   └─ объём = проба Plus AES First-Auth по растущим адресам key-блоков
└─ SAK == 20 → «ISO-DEP lane» (IsoDep, SL3/EV)
    ├─ SELECT VCA applet (00 A4 04 00 10 A0 00 00 03 96 56 43 41 …) успешен → SL3
    ├─ GET_VERSION (60 … AF) → EV1 | EV2 (+ объём)
    └─ объём = байт storage из GET_VERSION (22 = 2K, 42 = 4K)
```

Отпечатки ATS (исторические байты, побайтно):

| Исторические байты ATS | Подтип | Код продукта |
|---|---|---|
| `C1 05 2F 2F 00 35 C7` | Plus **S** | `MF1SPLUS` |
| `C1 05 2F 2F 01 BC D6` | Plus **X** | `MF1PLUS` |
| `C1 05 21 30 00 77 C1` | Plus **SE** | `MF1SEP10` |
| `C1 05 20 30 00 AB 9B` | Plus **SE** (альт.) | `MF1SEP10` |
| `4D 46 50 5F 45 4E 47` (`"MFP_ENG"`) | инженерный образец | — |
| нет совпадения | Plus **X** (по умолчанию) | `MF1PLUS` |

В семействе `C1 05 2F 2F …` байт 4 отличает S (`00`) от X (`01`). EV1/EV2 отвечают на **Read-Signature** (`3C`),
Plus S/X — нет. В GetVersion байт производителя `04` (NXP), байт storage `22` = 2K, `42` = 4K.

Трактовка SAK в TagInfo:

| SAK | Значение |
|---|---|
| `08` | Classic 1K / Plus 2K SL1 |
| `18` | Classic 4K / Plus 4K SL1 |
| `09` | MIFARE Mini |
| `19` | Classic 2K / вариант Plus 2K |
| `28`, `38` | SmartMX с Classic 1K / 4K |
| `88` | NXP Classic 1K (бит 0x80) |
| `98`, `B8` | варианты SmartMX / Pro |
| `01` | legacy / маркер TNP |
| `20` | ISO14443-4 → Plus SL3 / EV, DESFire |

Объём на SL1 определяется кадрами Plus AES **First-Auth** `70 XX 40 01 00` к key-блокам `0x4010`, `0x4020`, `0x4040`,
`0x4064`: самый старший, на который пришёл ответ, ограничивает число секторов (базовый / 2K / 4K / расширенный). Коды
продуктов: `MF1SPLUS60`/`80` (S 2K/4K), `MF1PLUS60`/`80` (X 2K/4K), `MF1SEP10xx` (SE), `MF1P2101` (EV1 2K).

## Создание MIFARE Plus вручную

`NFC → Add Manually` предлагает Plus SE (UID 4/7 байт), Plus S, X, EV1 и EV2 в 2K/4K с UID 4 или 7 байт. Сгенерированная
метка получает соответствующие исторические байты ATS, см. [Ручное добавление](/ru/nfc/add-manually).

## См. также

[MIFARE Classic](/ru/nfc/mifare-classic) · [Чтение меток](/ru/nfc/read) · [qUnleashed](/ru/nfc/qunleashed) ·
[Формат файлов NFC](/ru/nfc/file-format)
