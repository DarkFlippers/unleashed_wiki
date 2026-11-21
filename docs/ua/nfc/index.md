---
title: NFC
author: gromovyna
original: [https://docs.flipper.net/zero/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://t.me/gromovyna/3]
sources: [flipper-docs, unleashed-readme, unleashed-src, gromovyna]
---
# NFC

Flipper Zero має вбудований **модуль NFC 13.56 МГц**, який уміє **зчитувати**, **зберігати**, **емулювати** і, для
частини типів карток, **записувати** високочастотні картки: пропускні картки та брелоки, транспортні картки, готельні
ключі, NFC-наліпки, іграшки на кшталт amiibo та банківські картки (лише публічні дані). Дані зберігаються на
microSD-картці в `/ext/nfc/` як текстові файли `.nfc`.

::: warning Вставте microSD-картку
Застосунок NFC тримає свої словники, парсери та збережені картки на microSD-картці (`/ext/nfc/`). Оновлюйте прошивку
з вставленою SD-карткою, щоб ресурси (словники ключів, `assets/*.nfc`, плагіни-парсери) встановилися.
:::

## Апаратна частина

- Мікросхема NFC-фронтенду **ST25R3916**, яка відповідає і за зчитування, і за емуляцію.
- **Антена 13.56 МГц** на двосмуговій платі RFID-антени на задній стінці пристрою, поряд з антеною 125 кГц.
  Прикладайте картки до **центру задньої стінки** Flipper.

## Меню NFC

`Main Menu → NFC` відкриває таке меню (назви точно як на пристрої в Unleashed):

![Головне меню NFC: Read, Extract MFC Keys, Saved, Extra Actions](/screens/nfc/menu.png)

| Пункт | Що робить |
|---|---|
| **Read** | Визначає тип картки та зчитує все, що може, включно з атаками на ключі MIFARE Classic. Див. [Зчитування міток](/ua/nfc/read). |
| **Extract MFC Keys** | Емулює картку MIFARE Classic, щоб зібрати nonce зі зчитувача (MFKey32). Див. [MFKey32](/ua/nfc/mfkey). |
| **Saved** | Ваші збережені файли `.nfc`: емуляція, запис, розблокування, перейменування, видалення. |
| **Extra Actions** | Зчитати конкретний тип картки, керувати словниками ключів, розблокувати NTAG/Ultralight і SLIX-L. |
| **Add Manually** | Створює порожню віртуальну картку або картку NFC-A з відомих UID/ATQA/SAK. Див. [Додавання міток вручну](/ua/nfc/add-manually). |
| **Debug** | Видно лише з увімкненим режимом Debug (`Settings → System → Debug`). |

`Extra Actions` містить:

![Меню Extra Actions: Read Specific Card Type і словники ключів](/screens/nfc/extra_actions.png)

- **Read Specific Card Type**: пропустити автовизначення, корисно для гібридних карток.
- **MIFARE Classic Keys**, **MIFARE Plus Keys**, **MIFARE Ultralight C Keys**, **MIFARE UL AES Keys**: подивитися
  лічильники системного й користувацького словників, **Add** (додати ключ) або **List** (переглянути й видалити
  користувацькі ключі).
- **Unlock NTAG/Ultralight**: згенерувати або ввести пароль перед зчитуванням. Див.
  [Розблокування карток паролем](/ua/nfc/unlock-with-password).
- **Unlock SLIX-L**: розблокування паролем для міток ICODE SLIX-L.

::: tip Unleashed
Застосунок NFC — з офіційної прошивки: її ридер, емулятор і більшість парсерів карток. На додачу Unleashed додає,
зокрема: розширений системний словник MIFARE Classic
(понад 4000 ключів), зчитування **MIFARE Plus SL3** зі словниками AES-ключів, підтримку **MIFARE Ultralight AES**,
ключі домофонів **Texkom**, `Add Manually` для MIFARE Classic з власним UID і для MIFARE Plus,
**Save Keys to Dictionary** з дампа, словник CUID (окремий для картки) з індикатором завантаження, а також чимало
додаткових парсерів карток (Troika, Plantain, Umarsh, Zolotaya Korona, Kazan, Metromoney, Moscow Social Card,
квитки ППК та інші).
:::

## Основні поняття

| Термін | Значення |
|---|---|
| **UID** | Серійний номер картки, 4 або 7 байт (на деяких 10). На справжніх картках прописаний на заводі. |
| **ATQA / SAK** | Байти відповіді під час антиколізії, які підказують тип картки (наприклад, SAK `08` = MIFARE Classic 1K). |
| **Сектор / блок** | Одиниця пам'яті MIFARE Classic: 16 байт на блок, 4 блоки на сектор (у кінці 4K — сектори по 16 блоків). |
| **Сторінка** | Одиниця пам'яті Ultralight/NTAG, 4 байти. |
| **Ключ A / ключ B** | 6-байтові ключі Crypto-1, які захищають кожен сектор MIFARE Classic. |
| **Nonce** | Випадкове число, яким обмінюються під час аутентифікації. Зібрані nonce дозволяють обчислити ключі офлайн. |
| **Magic card** | Заготовка з перезаписуваним UID / блоком 0. Див. [Заготовки MIFARE Classic](/ua/nfc/magic-cards). |

## Сторінки цього розділу

### Повсякденне використання

- [Зчитування міток](/ua/nfc/read): зчитування, збереження, емуляція; які типи карток підтримуються та що дає кожен з них.
- [Додавання міток вручну](/ua/nfc/add-manually): створення віртуальних карток, картка NFC-A з UID/ATQA/SAK.
- [Підтримувані картки (парсери)](/ua/nfc/supported-cards): транспортні, пропускні та іграшкові картки, які Flipper уміє декодувати.
- [Банківські картки (EMV)](/ua/nfc/emv): що зчитується з банківської картки і чому її не можна клонувати.
- [Розблокування карток паролем](/ua/nfc/unlock-with-password): паролі NTAG/Ultralight, ключі Ultralight C, SLIX-L.

### MIFARE Classic і відновлення ключів

- [MIFARE Classic](/ua/nfc/mifare-classic): словники, сектори, повний процес зчитування, емуляція та запис.
- [MFKey32: ключі зі зчитувача](/ua/nfc/mfkey): збір nonce зі зчитувача, відновлення ключів.
- [Nested-атаки та бекдори Fudan](/ua/nfc/nested-fudan): атаки лише по картці, вбудовані в `Read`.
- [Застосунок MFKey](/ua/nfc/mfkey-app): відновлення ключів на самому Flipper (MFKey 4.1).
- [Швидке відновлення ключів за допомогою qUnleashed](/ua/nfc/qunleashed): усі атаки на телефоні або ПК.

### Заготовки та клонування

- [Заготовки MIFARE Classic](/ua/nfc/magic-cards): Gen1/Gen2/Gen3/Gen4, CUID, FUID, USCUID, UMC і місцеві назви.
- [NFC Magic 2.0](/ua/nfc/nfc-magic): запис і очищення magic-заготовок MIFARE Classic та Ultralight/NTAG.

### Інші родини карток

- [MIFARE Ultralight AES](/ua/nfc/ultralight-aes): Ultralight із захистом AES (MF0AES20), ключі, зворотний запис, secure messaging.
- [MIFARE Plus](/ua/nfc/mifare-plus): як визначаються S/X/SE/EV1/EV2 і рівні безпеки, AES-ключі SL3.

### Системи контролю доступу (статті @gromovyna)

- [Зчитувачі Iron Logic](/ua/nfc/iron-logic)
- [Динаміка Iron Logic та enrollment](/ua/nfc/iron-logic-enrollment)
- [Фільтри зчитувачів Vizit](/ua/nfc/vizit-filters)
- [Картки Moskvyonok](/ua/nfc/moskvyonok)

### Довідник

- [Формат файлів NFC](/ua/nfc/file-format): структура файлів `.nfc` і формати словників.

::: tip Закон
Працюйте з власними картками або з явного дозволу власника. Копіювання чужих пропусків чи проїзних квитків може
бути незаконним.
:::

MIFARE, MIFARE Classic, MIFARE Ultralight, MIFARE Plus, MIFARE DESFire, NTAG та ICODE — торгові марки NXP B.V.
FeliCa — торгова марка Sony Corporation.
