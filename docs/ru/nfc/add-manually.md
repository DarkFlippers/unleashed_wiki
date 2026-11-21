---
title: Ручное добавление меток
order: 60
original: [https://docs.flipper.net/zero/nfc/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Ручное добавление NFC-меток

`Add Manually` создаёт виртуальную метку без чтения настоящей. Два сценария:

- **Сгенерировать метку стандартного типа** со случайным UID и пустым (заводским) содержимым — как новая физическая
  метка. Потом её эмулируют, чтобы «прописать» в СКУД, или дают телефону записать на неё NDEF (ссылку, визитку).
- **Создать NFC-A метку по известным значениям** UID, ATQA и SAK. Этого хватает простым системам, проверяющим только
  UID.

## Сгенерировать метку стандартного типа

1. Откройте `Main Menu → NFC → Add Manually`.
2. Выберите тип (список ниже).

   ![Add Manually: список типов меток, выбран NFC-A 7-bytes UID](/screens/nfc/add_manually.png)

3. Откроется экран со сгенерированным **UID**. Нажмите <kbd>→</kbd> **More**.
4. В меню выберите **Save** (можно сначала **Change UID** или сразу **Emulate**).
5. Введите имя и подтвердите. Метка сохранится в `/ext/nfc/`.

Доступные типы (точные названия из меню):

| Группа | Типы |
|---|---|
| Ultralight | Mifare Ultralight, Mifare Ultralight EV1 11, Mifare Ultralight EV1 H11, Mifare Ultralight EV1 21, Mifare Ultralight EV1 H21, Mifare Ultralight C, Mifare Ultralight AES |
| NTAG | NTAG203, NTAG213, NTAG215, NTAG216, NTAG I2C 1k, NTAG I2C 2k, NTAG I2C Plus 1k, NTAG I2C Plus 2k |
| MIFARE Classic | Mifare Mini, Mifare Classic 1k 4byte UID, Mifare Classic 1k 7byte UID, Mifare Classic 4k 4byte UID, Mifare Classic 4k 7byte UID |
| MIFARE Plus | Mifare Plus SE 4byte / 7byte UID; Mifare Plus S 2K / 4K, 4byte / 7byte UID; Mifare Plus X 2K / 4K, 4byte / 7byte UID; Mifare Plus EV1 2K / 4K, 4b. / 7b. UID; Mifare Plus EV2 2K / 4K, 4b. / 7b. UID |
| Texkom | Texkom TK13, Texkom TK17, Texkom MMBIT |

::: tip Unleashed
Стоковая прошивка генерирует только Ultralight/NTAG и MIFARE Classic. В Unleashed добавлены **Mifare Ultralight C**
(с ключом 3DES по умолчанию `BREAKMEIFYOUCAN!`), **Mifare Ultralight AES**, все варианты **MIFARE Plus**, домофонные
ключи **Техком (Texkom)** и **Change UID** сразу после генерации — так можно создать MIFARE Classic с произвольным UID
(«NFC Add manually → Mifare Classic with custom UID» в ReadMe).
:::

::: tip Какой тип для телефона?
Чтобы записать с телефона ссылку или визитку, в большинстве случаев подходит **NTAG216**. Уточните, что ожидает ваше
приложение или система.
:::

## Создать NFC-A метку по UID, ATQA и SAK

Некоторые СКУД пускают по UID (иногда с ATQA/SAK). Если вы знаете эти значения:

1. Откройте `Main Menu → NFC → Add Manually`.
2. Выберите **NFC-A 7-bytes UID** или **NFC-A 4-bytes UID**.
3. **«Enter SAK in hex»** — введите SAK (1 байт), подтвердите.
4. **«Enter ATQA in hex»** — введите ATQA (2 байта), подтвердите.
5. **«Enter UID in hex»** — введите UID, подтвердите.
6. Задайте имя и сохраните.

Типичные значения: MIFARE Classic 1K — ATQA `00 04` (UID 4 байта) или `00 44` (7 байт), SAK `08`; Ultralight/NTAG —
ATQA `00 44`, SAK `00`. Совет по вводу байтов: нажмите <kbd>↑</kbd> несколько раз, пока не появится редактор полубайтов
(Unleashed).

## Использование метки

- **Эмуляция**: `Main Menu → NFC → Saved → <метка> → Emulate` (или **Emulate UID** для NFC-A) и приложите Флиппер к
  считывателю. Чтобы «прописать» виртуальный ключ в СКУД, переведите систему в режим добавления ключей по её
  инструкции и приложите эмулируемую метку.
- **Изменить UID** позже: `Saved → <метка> → Edit UID` (метки NFC-A).

::: warning
Разные СКУД и приложения добавляют ключи по-разному — смотрите их документацию и поддерживаемые типы. Виртуальная
метка не поможет с системами, проверяющими криптографию карты (DESFire, Plus SL3 с неизвестными ключами, EMV).
:::

## См. также

[Чтение меток](/ru/nfc/read) · [Формат файлов NFC](/ru/nfc/file-format) · [Заготовки](/ru/nfc/magic-cards)
