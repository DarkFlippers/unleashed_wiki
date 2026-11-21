---
title: NFC
author: gromovyna
original: [https://docs.flipper.net/zero/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://t.me/gromovyna/3]
sources: [flipper-docs, unleashed-readme, unleashed-src, gromovyna]
---
# NFC

Во Flipper Zero встроен **NFC-модуль 13,56 МГц**, который умеет **читать**, **сохранять**, **эмулировать**, а для
части типов и **записывать** высокочастотные метки: карты и брелоки СКУД, транспортные карты, гостиничные ключи,
NFC-наклейки, игрушки типа amiibo и банковские карты (только открытые данные). Данные хранятся на microSD в
`/ext/nfc/` в виде текстовых файлов `.nfc`.

::: warning Вставьте microSD-карту
Словари, парсеры и сохранённые метки NFC-приложение держит на карте памяти (`/ext/nfc/`). Обновляйте прошивку со
вставленной SD-картой, чтобы установились ресурсы (словари ключей, `assets/*.nfc`, плагины-парсеры).
:::

## Железо

- Чип NFC-фронтенда **ST25R3916** — отвечает и за чтение, и за эмуляцию.
- **Антенна 13,56 МГц** на двухдиапазонной плате RFID-антенн на задней стороне, рядом с антенной 125 кГц.
  Прикладывайте метку к **центру задней крышки** Флиппера.

## Меню NFC

`Main Menu → NFC` открывает меню (названия — как на устройстве в Unleashed):

![Главное меню NFC: Read, Extract MFC Keys, Saved, Extra Actions](/screens/nfc/menu.png)

| Пункт | Что делает |
|---|---|
| **Read** | Определяет тип метки и читает всё, что может, включая атаки на ключи MIFARE Classic. См. [Чтение меток](/ru/nfc/read). |
| **Extract MFC Keys** | Эмулирует карту MIFARE Classic, чтобы собрать нонсы со считывателя (MFKey32). См. [MFKey32](/ru/nfc/mfkey). |
| **Saved** | Сохранённые `.nfc`: эмуляция, запись, разблокировка, переименование, удаление. |
| **Extra Actions** | Чтение конкретного типа, словари ключей, разблокировка NTAG/Ultralight и SLIX-L. |
| **Add Manually** | Создаёт пустую виртуальную метку или NFC-A по известным UID/ATQA/SAK. См. [Ручное добавление](/ru/nfc/add-manually). |
| **Debug** | Виден только при включённом режиме отладки (`Settings → System → Debug`). |

В `Extra Actions`:

![Меню Extra Actions: Read Specific Card Type и словари ключей](/screens/nfc/extra_actions.png)

- **Read Specific Card Type** — пропустить автоопределение (полезно для гибридных карт).
- **MIFARE Classic Keys**, **MIFARE Plus Keys**, **MIFARE Ultralight C Keys**, **MIFARE UL AES Keys** — счётчики
  системного и пользовательского словарей, **Add** (добавить ключ), **List** (список и удаление своих ключей).
- **Unlock NTAG/Ultralight** — сгенерировать или ввести пароль перед чтением. См. [Разблокировка](/ru/nfc/unlock-with-password).
- **Unlock SLIX-L** — разблокировка меток ICODE SLIX-L паролем.

::: tip Unleashed
Приложение NFC — из официальной прошивки: её ридер, эмулятор и большинство парсеров карт. Вдобавок в Unleashed,
среди прочего, есть: расширенный системный словарь MIFARE Classic
(4000+ ключей), чтение **MIFARE Plus SL3** по словарям AES-ключей, поддержка **MIFARE Ultralight AES**, домофонные
ключи **Техком (Texkom)**, Add Manually для MIFARE Classic с произвольным UID и для MIFARE Plus, **Save Keys to
Dictionary** из дампа, CUID-словарь (на одну метку) с прогресс-баром загрузки и множество дополнительных парсеров
(Тройка, Подорожник, Умарш, Золотая Корона, Казань, Metromoney, Социальная карта москвича, билеты ППК и др.).
:::

## Базовые понятия

| Термин | Значение |
|---|---|
| **UID** | Серийный номер метки, 4 или 7 байт (на некоторых 10). На оригинальных метках прошит на заводе. |
| **ATQA / SAK** | Байты ответа при антиколлизии, по которым видно тип метки (напр. SAK `08` = MIFARE Classic 1K). |
| **Сектор / блок** | Единица памяти MIFARE Classic: блок 16 байт, 4 блока в секторе (в конце 4K — сектора по 16 блоков). |
| **Страница** | Единица памяти Ultralight/NTAG, 4 байта. |
| **Key A / Key B** | 6-байтные ключи Crypto-1, защищающие каждый сектор MIFARE Classic (дальше — КК, криптоключи). |
| **Нонс (nonce)** | Случайное число при аутентификации. По собранным нонсам ключи можно вычислить офлайн. |
| **Заготовка (magic)** | Метка с перезаписываемым UID / блоком 0. См. [Заготовки](/ru/nfc/magic-cards). |

## Страницы раздела

### Повседневное

- [Чтение меток](/ru/nfc/read) — чтение, сохранение, эмуляция; какие типы поддерживаются и что из них получается.
- [Ручное добавление](/ru/nfc/add-manually) — генерация виртуальных меток, NFC-A по UID/ATQA/SAK.
- [Поддерживаемые карты (парсеры)](/ru/nfc/supported-cards) — транспортные, пропускные и игровые карты, которые Флиппер расшифровывает.
- [Банковские карты (EMV)](/ru/nfc/emv) — что читается с банковской карты и почему её нельзя клонировать.
- [Разблокировка паролем](/ru/nfc/unlock-with-password) — пароли NTAG/Ultralight, ключи Ultralight C, SLIX-L.

### MIFARE Classic и восстановление ключей

- [MIFARE Classic](/ru/nfc/mifare-classic) — словари, сектора, полный процесс чтения, эмуляция и запись.
- [MFKey32: ключи со считывателя](/ru/nfc/mfkey) — сбор нонсов с ридера и восстановление ключей.
- [Nested-атаки и бэкдоры Fudan](/ru/nfc/nested-fudan) — атаки «только по метке», встроенные в `Read`.
- [Приложение MFKey](/ru/nfc/mfkey-app) — восстановление ключей на самом Флиппере (MFKey 4.1).
- [Быстрое вскрытие ключей с qUnleashed](/ru/nfc/qunleashed) — все атаки на телефоне или ПК.

### Заготовки и клонирование

- [Заготовки MIFARE Classic](/ru/nfc/magic-cards) — Gen1/Gen2/Gen3/Gen4, CUID, FUID, USCUID, UMC и местные названия.
- [NFC Magic 2.0](/ru/nfc/nfc-magic) — запись и вайп магических заготовок MIFARE Classic и Ultralight/NTAG.

### Другие семейства

- [MIFARE Ultralight AES](/ru/nfc/ultralight-aes) — Ultralight с AES (MF0AES20): ключи, запись, secure messaging.
- [MIFARE Plus](/ru/nfc/mifare-plus) — как определяются S/X/SE/EV1/EV2 и уровни безопасности, AES-ключи SL3.

### СКУД (статьи @gromovyna)

- [Считыватели Iron Logic](/ru/nfc/iron-logic)
- [Enrollment-атака на динамику Iron Logic](/ru/nfc/iron-logic-enrollment)
- [Фильтры считывателей Vizit](/ru/nfc/vizit-filters)
- [Карты «Москвёнок»](/ru/nfc/moskvyonok)

### Справочник

- [Формат файлов NFC](/ru/nfc/file-format) — структура `.nfc` и словарей.

::: tip Закон
Работайте со своими метками или с явного разрешения владельца. Копирование чужих пропусков и проездных может быть
незаконным.
:::

MIFARE, MIFARE Classic, MIFARE Ultralight, MIFARE Plus, MIFARE DESFire, NTAG и ICODE — товарные знаки NXP B.V.
FeliCa — товарный знак Sony Corporation.
