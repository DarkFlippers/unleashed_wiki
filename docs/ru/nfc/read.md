---
title: Чтение меток
order: 10
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols]
sources: [flipper-docs, unleashed-src]
---
# Чтение, сохранение и эмуляция NFC-меток

`Read` — главный вход в NFC-приложение. Флиппер сам определяет протокол, читает всё доступное, запускает атаки на
ключи там, где они применимы (MIFARE Classic, Ultralight C, Ultralight AES, MIFARE Plus SL3), а затем даёт сохранить,
эмулировать или записать результат.

## Прочитать метку

1. Откройте `Main Menu → NFC → Read`.
2. На экране **«Reading — Hold card next to Flipper's back»**. Положите метку на **центр задней крышки** Флиппера и
   не двигайте.

   ![Экран чтения: приложите карту к задней крышке Флиппера](/screens/nfc/reading.png)

3. Когда метка найдена, появится **«Don't move»**, идёт чтение. Для защищённых меток может открыться экран атаки
   (перебор по словарю, nested — см. [MIFARE Classic](/ru/nfc/mifare-classic)).

   ![Перебор по системному словарю MIFARE Classic: сектор 9, найдено 19 из 32 ключей](/screens/nfc/dict_attack.png)

4. На экране результата — название метки и сводка. Если метку распознал [парсер](/ru/nfc/supported-cards), будут
   расшифрованные данные (баланс, количество поездок, номер карты…).

   ![Результат чтения: MIFARE Classic 1K, UID, 32/32 ключа и 16/16 секторов](/screens/nfc/card_info.png)

   - <kbd>←</kbd> **Retry** — спросит *«Retry Reading? All unsaved data will be lost»*.
   - <kbd>→</kbd> **More** — меню метки.
5. В **More** выберите **Save**, введите имя в **«Name the card»** и подтвердите. Файл сохранится в
   `/ext/nfc/<имя>.nfc`.

В меню `More` после чтения всегда есть **Save** и **Info**; в зависимости от типа — **Emulate** / **Emulate UID** и
пункты протокола (например **Unlock**, **Show Keys**, **Extract MFC Keys**, **Transactions** для EMV).

### Мультипротокольные метки

Некоторые карты отвечают сразу несколькими протоколами (например, банковская карта со встроенной областью MIFARE
Classic). Тогда Флиппер покажет меню **«Multi-protocol card»** с пунктами вида **Read as MIFARE Classic**. Чтобы
полностью пропустить автоопределение, откройте `Main Menu → NFC → Extra Actions → Read Specific Card Type`, выберите
тип и нажмите <kbd>OK</kbd>.

## Поддерживаемые типы

| Семейство | Типы (как их называет прошивка) | Чтение | Эмуляция | Запись |
|---|---|---|---|---|
| ISO14443-3A (NFC-A) | Любая NFC-A метка: UID, ATQA, SAK | да | только UID | — |
| MIFARE Classic | Mini, 1K, 4K (UID 4 и 7 байт) | сектора с известными ключами | полная | только на исходную метку |
| MIFARE Ultralight / NTAG | Ultralight, Ultralight 11/21 (EV1), Ultralight C, Ultralight AES, NTAG203/210/212/213/215/216, NTAG I2C 1K/2K, NTAG I2C Plus 1K/2K | открытые страницы, остальное после разблокировки | полная | на тот же тип (см. ниже) |
| MIFARE Plus | Plus, S, X, SE, EV1, EV2; SL0–SL3 | SL1 как Classic, SL3 по AES-ключам | SL3 полная, остальные UID | SL3 — на исходную метку |
| MIFARE DESFire | DESFire | незащищённые приложения и файлы | только UID | — |
| ISO14443-4A | Неизвестные ISO-DEP метки | UID, ATQA, SAK, ATS | только UID | — |
| NTAG4xx, Type 4 Tag | NTAG 4xx DNA; NFC Forum Type 4 (NDEF) | да | NTAG4xx: UID; T4T: полная | T4T: да |
| EMV | Банковские карты | открытые данные | — | — |
| ISO14443-3B / -4B | NFC-B метки | UID, app data, protocol info | — | — |
| ST25TB | ST25TB512, ST25TB512-AC, SRIX512, ST25TB02K, ST25TB04K, SRIX4K | да | — | — |
| ISO15693-3 (NFC-V) | Неизвестные NFC-V метки | UID + читаемые блоки | полная | да |
| SLIX | ICODE SLIX, SLIX-S, SLIX-L, SLIX2 | да, разблокировка паролем | полная | да |
| FeliCa | FeliCa (Lite-S и др.) | IDm, PMm, блоки | полная | — |
| Texkom | Ключи Техком TK13, TK15, TK17, MMBIT | да | полная | — |

::: tip Unleashed
Ключи **Техком (Texkom)** — домофонные брелоки 13,56 МГц, которые не реализуют ни один ISO-стандарт, — дампы
**MIFARE Plus SL3** с AES-ключами, **Ultralight AES** и расширенная **запись** Ultralight есть только в прошивке
Unleashed, в стоке их нет. Для MIFARE Classic добавлены CUID-словарь и **Save Keys to Dictionary**.
:::

### MIFARE Classic

Для чтения секторов нужны ключи: до **10 ключей на 5 секторов** (Mini), **32 ключа на 16 секторов** (1K) или
**80 ключей на 40 секторов** (4K). Флиппер пробует кеш ключей метки, затем CUID-, пользовательский и системный
словари, затем nested-атаки. Подробно — на странице [MIFARE Classic](/ru/nfc/mifare-classic); если ключей всё ещё не
хватает — [MFKey32](/ru/nfc/mfkey) и [Nested-атаки](/ru/nfc/nested-fudan).

### MIFARE Ultralight и NTAG

Открытые страницы читаются сразу. Страницы под паролем (NTAG21x, Ultralight EV1), 3DES-ключом (Ultralight C) или
AES-ключом (Ultralight AES) остаются закрытыми до разблокировки — см. [Разблокировка паролем](/ru/nfc/unlock-with-password)
и [Ultralight AES](/ru/nfc/ultralight-aes). Для Ultralight C и Ultralight AES атака по словарю запускается сама.

**Write** доступна для полностью прочитанного дампа **NTAG213, NTAG215, NTAG216, Ultralight, Ultralight 11,
Ultralight 21, Ultralight C** и **Ultralight AES** — на метку того же типа. У Ultralight C и AES два пункта:
**Write (Keep Key)** оставляет ключ целевой метки, **Write (Copy Key)** записывает ещё и ключ из дампа. Если целевая
метка закрыта паролем, AUTH0 или lock-битами, появится *«Card protected by password, AUTH0 or lock bits»*.

### Неизвестные метки

Для неизвестной NFC-A метки сохраняются только UID, ATQA и SAK; для неизвестной NFC-V — UID и читаемые блоки. Многие
простые считыватели проверяют только UID, так что **Emulate UID** может сработать.

## Сохранённые метки

`Main Menu → NFC → Saved` — список ваших `.nfc`. Меню сохранённой метки (зависит от типа):

- **Emulate** или **Emulate UID**
- **Write** / **Write to Initial Card** (MIFARE Classic, MIFARE Plus SL3) / **Write (Keep Key)** + **Write (Copy Key)**
- **Edit UID** (NFC-A, ISO14443-4A, ISO15693)
- пункты протокола: **Unlock**, **Unlock with Dictionary**, **Extract MFC Keys**, **Update from Initial Card**,
  **Show Keys**, **Save Keys to Dictionary**, **Reveal Real UID**…
- **Restore to Original State** (только если есть shadow-файл, см. ниже)
- **Rename**, **Delete**, **Info**

## Эмуляция

1. Откройте `Main Menu → NFC → Saved`, выберите метку.
2. **Emulate** (полная эмуляция) или **Emulate UID** (отдаются только UID/ATQA/SAK).
3. На экране **Emulating** и имя метки. Приложите заднюю сторону Флиппера к считывателю.
4. Если считыватель общался с эмулируемой меткой, появится кнопка **Log** (<kbd>OK</kbd>) с журналом обмена.
5. <kbd>←</kbd> — остановить.

### Shadow-файлы

Если считыватель что-то записывает в эмулируемую метку (баланс, счётчик), исходный файл не меняется. Новое состояние
пишется в **shadow-файл** рядом (`<имя>.shd`), оригинальный дамп остаётся нетронутым:

- **Restore to Original State** (`Saved → метка`) — спросит *«Restore Card Data?»* и удалит shadow-файл.
- **Update from Initial Card** (MIFARE Classic, MIFARE Plus SL3) — перечитывает физическую метку сохранёнными ключами
  и обновляет дамп. Принимается только исходная метка, иначе *«Wrong Card! Data management is only possible with
  source card»*.

## Если чтение не получилось

- **Ничего не определяется** — возможно, это метка 125 кГц. Попробуйте `Main Menu → 125 kHz RFID → Read`
  (см. [раздел RFID](/ru/rfid/read)).
- **Определяется не тот тип / гибридная карта** — `Extra Actions → Read Specific Card Type`.
- **«Lost the tag!»** во время долгой атаки — верните метку на то же место и не двигайте. Толстые чехлы и металл за
  меткой мешают полю.
- **Прочитаны не все сектора / страницы** — метка защищена. Дальше: [MIFARE Classic](/ru/nfc/mifare-classic),
  [MFKey32](/ru/nfc/mfkey) или [Разблокировка паролем](/ru/nfc/unlock-with-password).
- **«Plugin Not Loaded — Plugin file missing or outdated»** — файлы парсеров `.fal` на SD не соответствуют прошивке.
  Переустановите/обновите прошивку со вставленной SD-картой.

## См. также

- [MIFARE Classic](/ru/nfc/mifare-classic) · [Поддерживаемые карты](/ru/nfc/supported-cards) · [Формат файлов NFC](/ru/nfc/file-format)
- [Заготовки](/ru/nfc/magic-cards) · [NFC Magic 2.0](/ru/nfc/nfc-magic)
