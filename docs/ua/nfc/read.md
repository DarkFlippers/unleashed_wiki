---
title: Зчитування міток
order: 10
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols]
sources: [flipper-docs, unleashed-src]
---
# Зчитування, збереження та емуляція NFC-карток

`Read` — головна точка входу застосунку NFC. Flipper сам визначає протокол, зчитує всі дані, до яких може дістатися,
запускає атаки на ключі там, де це доречно (MIFARE Classic, Ultralight C, Ultralight AES, MIFARE Plus SL3), а потім
дає зберегти, емулювати або записати результат.

## Як зчитати картку

1. Відкрийте `Main Menu → NFC → Read`.
2. На екрані з'явиться **"Reading — Hold card next to Flipper's back"**. Прикладіть картку впритул до **центру
   задньої панелі** Flipper і тримайте нерухомо.

   ![Екран зчитування: Hold card next to Flipper's back](/screens/nfc/reading.png)

3. Коли картку знайдено, під час зчитування даних ви побачите **"Don't move"**. Для захищених карток може з'явитися
   екран атаки (словникова атака, nested-атака — див. [MIFARE Classic](/ua/nfc/mifare-classic)).

   ![Словникова атака системним словником MIFARE Classic: розблокування сектора 9, знайдено 19 із 32 ключів](/screens/nfc/dict_attack.png)

4. Екран результату показує назву картки та зведення. Якщо картку розпізнав [парсер](/ua/nfc/supported-cards), ви
   побачите розшифровані дані (баланс, кількість поїздок, номер картки…).

   ![Результат зчитування: MIFARE Classic 1K з UID, знайдено 32/32 ключів і зчитано 16/16 секторів](/screens/nfc/card_info.png)

   - <kbd>←</kbd> **Retry**: запитує *"Retry Reading? All unsaved data will be lost"*.
   - <kbd>→</kbd> **More**: відкриває меню картки.
5. У **More** виберіть **Save**, введіть назву в полі **"Name the card"** і підтвердьте. Файл потрапить до
   `/ext/nfc/<назва>.nfc`.

Меню `More` після зчитування завжди містить **Save** та **Info**; залежно від типу картки там також бувають
**Emulate** / **Emulate UID**, пункти для конкретного протоколу (наприклад, **Unlock**, **Show Keys**,
**Extract MFC Keys**, **Transactions** для EMV).

### Мультипротокольні картки

Деякі картки відповідають одразу за кількома протоколами (наприклад, банківська картка, яка містить ще й область
MIFARE Classic). Тоді Flipper показує меню **"Multi-protocol card"** з пунктами на кшталт **Read as MIFARE Classic**.
Щоб повністю обійти автовизначення, скористайтеся `Main Menu → NFC → Extra Actions → Read Specific Card Type`:
виберіть тип і натисніть <kbd>OK</kbd>.

## Підтримувані типи карток

| Родина | Типи карток (як їх називає прошивка) | Зчитування | Емуляція | Запис |
|---|---|---|---|---|
| ISO14443-3A (NFC-A) | Будь-яка NFC-A картка: UID, ATQA, SAK | так | лише UID | — |
| MIFARE Classic | Mini, 1K, 4K (UID 4 та 7 байт) | сектори з відомими ключами | повна | лише на вихідну картку |
| MIFARE Ultralight / NTAG | Ultralight, Ultralight 11/21 (EV1), Ultralight C, Ultralight AES, NTAG203/210/212/213/215/216, NTAG I2C 1K/2K, NTAG I2C Plus 1K/2K | відкриті сторінки, більше — після розблокування | повна | той самий тип (див. нижче) |
| MIFARE Plus | Plus, S, X, SE, EV1, EV2; SL0–SL3 | SL1 як Classic, SL3 з ключами AES | SL3 повна, інші — UID | SL3 на вихідну картку |
| MIFARE DESFire | DESFire | незахищені застосунки та файли | лише UID | — |
| ISO14443-4A | Невідомі картки ISO-DEP | UID, ATQA, SAK, ATS | лише UID | — |
| NTAG4xx, Type 4 Tag | NTAG 4xx DNA; мітки NFC Forum Type 4 (NDEF) | так | NTAG4xx: UID; T4T: повна | T4T: так |
| EMV | Банківські картки | публічні дані | — | — |
| ISO14443-3B / -4B | Картки NFC-B | UID, дані застосунку, інформація про протокол | — | — |
| ST25TB | ST25TB512, ST25TB512-AC, SRIX512, ST25TB02K, ST25TB04K, SRIX4K | так | — | — |
| ISO15693-3 (NFC-V) | Невідомі мітки NFC-V | UID + доступні блоки | повна | так |
| SLIX | ICODE SLIX, SLIX-S, SLIX-L, SLIX2 | так, розблокування паролем | повна | так |
| FeliCa | FeliCa (Lite-S та інші) | IDm, PMm, блоки | повна | — |
| Texkom | Ключі домофонів Texkom TK13, TK15, TK17, MMBIT | так | повна | — |

::: tip Unleashed
Ключі **Texkom** (брелоки домофонів на 13.56 МГц, поширені в Росії, які не реалізують жодного стандарту ISO), дампи
**MIFARE Plus SL3** з ключами AES, **Ultralight AES** і розширена підтримка **Write** для Ultralight — це доповнення
прошивки, яких ви не знайдете у стоковій. Для MIFARE Classic додано ще й CUID-словник і **Save Keys to Dictionary**.
:::

### MIFARE Classic

Щоб зчитати сектори, Flipper потребує ключів: до **10 ключів для 5 секторів** (Mini), **32 ключі для 16 секторів**
(1K) або **80 ключів для 40 секторів** (4K). Він пробує кеш ключів цієї картки, потім CUID-, користувацький і
системний словники, а далі — nested-атаки. Подробиці — на сторінці [MIFARE Classic](/ua/nfc/mifare-classic); якщо
ключів усе одно не вистачає, див. [MFKey32](/ua/nfc/mfkey) і [Nested-атаки](/ua/nfc/nested-fudan).

### MIFARE Ultralight і NTAG

Відкриті сторінки зчитуються напряму. Сторінки, захищені паролем (NTAG21x, Ultralight EV1), ключем 3DES
(Ultralight C) або ключем AES (Ultralight AES), залишаються заблокованими, доки ви їх не розблокуєте — див.
[Розблокування карток](/ua/nfc/unlock-with-password) та [Ultralight AES](/ua/nfc/ultralight-aes). Для Ultralight C
та Ultralight AES словникова атака запускається автоматично.

**Write** пропонується для повністю зчитаного дампа **NTAG213, NTAG215, NTAG216, Ultralight, Ultralight 11,
Ultralight 21, Ultralight C** та **Ultralight AES** — на картку того самого типу. В Ultralight C та AES є два пункти:
**Write (Keep Key)** зберігає ключ картки-приймача, а **Write (Copy Key)** записує ще й ключ із дампа. Якщо приймач
захищений паролем, AUTH0 або лок-бітами, ви отримаєте *"Card protected by password, AUTH0 or lock bits"*.

### Невідомі картки

Для невідомої картки NFC-A зберігаються лише UID, ATQA та SAK; для невідомої мітки NFC-V — UID і доступні блоки.
Багато простих зчитувачів систем контролю доступу перевіряють тільки UID, тому **Emulate UID** цілком може
спрацювати.

## Збережені картки

`Main Menu → NFC → Saved` показує ваші файли `.nfc`. Меню збереженої картки містить (залежно від типу):

- **Emulate** або **Emulate UID**
- **Write** / **Write to Initial Card** (MIFARE Classic, MIFARE Plus SL3) / **Write (Keep Key)** + **Write (Copy Key)**
- **Edit UID** (NFC-A, ISO14443-4A, ISO15693)
- пункти для конкретних протоколів: **Unlock**, **Unlock with Dictionary**, **Extract MFC Keys**,
  **Update from Initial Card**, **Show Keys**, **Save Keys to Dictionary**, **Reveal Real UID**…
- **Restore to Original State** (лише коли існує shadow-файл, див. нижче)
- **Rename**, **Delete**, **Info**

## Емуляція картки

1. Відкрийте `Main Menu → NFC → Saved` і виберіть картку.
2. Виберіть **Emulate** (повна емуляція) або **Emulate UID** (надсилаються лише UID/ATQA/SAK).
3. На екрані з'явиться **Emulating** з назвою картки. Піднесіть задню панель Flipper до зчитувача.
4. Якщо зчитувач спілкувався з емульованою карткою, з'явиться кнопка **Log** (<kbd>OK</kbd>), яка показує обмін
   даними.
5. Натисніть <kbd>←</kbd>, щоб зупинити емуляцію.

### Shadow-файли {#shadow-files}

Коли зчитувач записує щось на емульовану картку (наприклад, оновлює баланс або лічильник), Flipper не змінює ваш
вихідний файл. Новий стан він записує в **shadow-файл** поруч (`<назва>.shd`), а початковий дамп залишається
недоторканим:

- **Restore to Original State** (`Saved → картка`): запитує *"Restore Card Data?"* і видаляє shadow-файл.
- **Update from Initial Card** (MIFARE Classic, MIFARE Plus SL3): перечитує фізичну картку зі збереженими ключами
  та оновлює дамп. Приймається лише вихідна картка, інакше з'явиться *"Wrong Card! Data management is only possible
  with source card"*.

## Якщо зчитати не вдається

- **Нічого не визначається**: можливо, це картка на 125 кГц. Спробуйте `Main Menu → 125 kHz RFID → Read`
  (див. [розділ RFID](/ua/rfid/read)).
- **Визначено хибний тип / гібридна картка**: скористайтеся `Extra Actions → Read Specific Card Type`.
- **"Lost the tag!"** під час тривалої атаки: поверніть картку на те саме місце й тримайте нерухомо. Товсті чохли та
  метал за карткою спотворюють поле.
- **Зчитано не всі сектори / сторінки**: картка захищена. Переходьте до [MIFARE Classic](/ua/nfc/mifare-classic),
  [MFKey32](/ua/nfc/mfkey) або [Розблокування карток](/ua/nfc/unlock-with-password).
- **"Plugin Not Loaded — Plugin file missing or outdated"**: файли парсерів `.fal` на microSD-картці не відповідають
  прошивці. Перевстановіть або оновіть прошивку зі вставленою microSD-карткою.

## Пов'язані сторінки

- [MIFARE Classic](/ua/nfc/mifare-classic) · [Підтримувані картки](/ua/nfc/supported-cards) · [Формат файлів NFC](/ua/nfc/file-format)
- [Заготовки MIFARE Classic](/ua/nfc/magic-cards) · [NFC Magic 2.0](/ua/nfc/nfc-magic)
