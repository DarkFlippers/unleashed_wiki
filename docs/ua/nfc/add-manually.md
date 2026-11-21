---
title: Додавання міток вручну
order: 60
original: [https://docs.flipper.net/zero/nfc/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Додавання NFC-міток вручну

`Add Manually` створює віртуальну картку без зчитування справжньої. Два сценарії використання:

- **Згенерувати картку стандартного типу** з випадковим UID і типовим (порожнім) вмістом, ніби ви взяли нову
  фізичну картку. Далі її можна емулювати, щоб «прописати» в системі контролю доступу або щоб смартфон записав
  на неї дані NDEF (посилання, vCard).
- **Створити картку NFC-A з відомих значень**: UID, ATQA і SAK. Цього достатньо для простих систем, які
  перевіряють лише UID.

## Генерування картки стандартного типу

1. Перейдіть до `Main Menu → NFC → Add Manually`.
2. Виберіть тип картки (перелік нижче).

   ![Add Manually: перелік типів карток із вибраним NFC-A 7-bytes UID](/screens/nfc/add_manually.png)

3. Відкриється екран зі згенерованим **UID**. Натисніть <kbd>→</kbd> **More**.
4. У меню виберіть **Save** (перед цим можна також виконати **Change UID** або одразу **Emulate**).
5. Введіть назву й підтвердьте. Картка збережеться у `/ext/nfc/`.

Доступні типи (назви точно як у меню):

| Група | Типи |
|---|---|
| Ultralight | Mifare Ultralight, Mifare Ultralight EV1 11, Mifare Ultralight EV1 H11, Mifare Ultralight EV1 21, Mifare Ultralight EV1 H21, Mifare Ultralight C, Mifare Ultralight AES |
| NTAG | NTAG203, NTAG213, NTAG215, NTAG216, NTAG I2C 1k, NTAG I2C 2k, NTAG I2C Plus 1k, NTAG I2C Plus 2k |
| MIFARE Classic | Mifare Mini, Mifare Classic 1k 4byte UID, Mifare Classic 1k 7byte UID, Mifare Classic 4k 4byte UID, Mifare Classic 4k 7byte UID |
| MIFARE Plus | Mifare Plus SE 4byte / 7byte UID; Mifare Plus S 2K / 4K, 4byte / 7byte UID; Mifare Plus X 2K / 4K, 4byte / 7byte UID; Mifare Plus EV1 2K / 4K, 4b. / 7b. UID; Mifare Plus EV2 2K / 4K, 4b. / 7b. UID |
| Texkom | Texkom TK13, Texkom TK17, Texkom MMBIT |

::: tip Unleashed
Стокова прошивка генерує лише Ultralight/NTAG і MIFARE Classic. Unleashed додає **Mifare Ultralight C** (із
типовим ключем 3DES `BREAKMEIFYOUCAN!`), **Mifare Ultralight AES**, усі варіанти **MIFARE Plus**, ключі
домофонів **Texkom** і пункт **Change UID** одразу після генерування, тому можна створити MIFARE Classic із
власним UID («NFC Add manually → Mifare Classic with custom UID» у ReadMe).
:::

::: tip Який тип вибрати для смартфона?
Щоб записати посилання чи візитівку зі смартфона, у більшості випадків підходить **NTAG216**. Перевірте, чого
очікує ваш застосунок або система.
:::

## Створення картки NFC-A з UID, ATQA і SAK

Деякі системи контролю доступу надають доступ за UID (іноді разом з ATQA/SAK). Якщо ви знаєте ці значення:

1. Перейдіть до `Main Menu → NFC → Add Manually`.
2. Виберіть **NFC-A 7-bytes UID** або **NFC-A 4-bytes UID**.
3. **«Enter SAK in hex»**: введіть SAK (1 байт) і підтвердьте.
4. **«Enter ATQA in hex»**: введіть ATQA (2 байти) і підтвердьте.
5. **«Enter UID in hex»**: введіть UID і підтвердьте.
6. Дайте картці назву й збережіть її.

Типові значення: MIFARE Classic 1K — ATQA `00 04` (4-байтовий UID) або `00 44` (7-байтовий), SAK `08`;
Ultralight/NTAG — ATQA `00 44`, SAK `00`. Підказка щодо введення байтів: натискайте <kbd>↑</kbd> кілька разів,
доки не з'явиться редактор півбайтів (Unleashed).

## Використання картки

- **Емуляція**: `Main Menu → NFC → Saved → <картка> → Emulate` (або **Emulate UID** для картки NFC-A) і піднесіть
  Flipper до зчитувача. Щоб «запрограмувати» віртуальний ключ у системі контролю доступу, переведіть систему в
  режим прописування згідно з її інструкцією і піднесіть емульовану картку.
- **Змінити UID** згодом: `Saved → <картка> → Edit UID` (для карток NFC-A).

::: warning
Різні системи контролю доступу та застосунки прописують картки по-різному; перевіряйте в їхній документації,
які типи карток підтримуються. Віртуальна картка не допоможе з системами, які перевіряють криптографію картки
(DESFire, Plus SL3 з невідомими ключами, EMV).
:::

## Пов'язані сторінки

[Зчитування міток](/ua/nfc/read) · [Формат файлів NFC](/ua/nfc/file-format) ·
[Заготовки MIFARE Classic](/ua/nfc/magic-cards)
