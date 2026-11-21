---
title: Банковские карты (EMV)
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/emv, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md]
sources: [unleashed-src, unleashed-readme, unleashed-docs]
---
# Банковские карты (EMV)

Бесконтактные банковские карты и платёжные приложения телефонов работают по **EMV** поверх ISO14443-4. Флиппер
читает **открытую** информацию, которую карта отдаёт любому терминалу, и показывает её в понятном виде. Секретные ключи
он не читает и **не может эмулировать или клонировать** банковскую карту: каждый платёж подписывается ключом, который
никогда не покидает чип.

::: tip Unleashed
Протокол EMV и парсер открытых данных пришли из Unleashed (авторы @Leptopt1los и @wosk).
:::

## Прочитать банковскую карту

1. `Main Menu → NFC → Read`, приложите карту (или разблокированный телефон с открытым кошельком) к задней стороне
   Флиппера.
2. Результат показывает то, что раскрыла карта, например:
   - метку или название приложения (например, платёжную систему) либо просто `EMV`;
   - номер карты (PAN), группами по 4 цифры;
   - `Cardholder name:` (большинство современных карт его уже не отдают);
   - даты `Effective:` / `Expires:` (в формате даты вашей локали);
   - `Country:` и `Currency:` выпуска;
   - `PIN attempts left:` — оставшиеся попытки ввода PIN;
   - `Mobile: yes` — для кошельков в телефоне/часах;
   - *«No data was parsed»*, если ничего полезного не пришло.
3. <kbd>→</kbd> **More** — меню: **Save**, **Transactions** (только если карта отдала журнал транзакций), **Info**.

Экран **Info** — техническое представление: UID, `AID`, `Interchange profile`, `Currency code`, `Country code`,
`Transactions count` и `Last Online ATC`, если есть.

## Транзакции

Некоторые карты хранят короткий журнал последних операций и отдают его без PIN. `More → Transactions` показывает
каждую запись с её счётчиком (ATC), суммой, валютой, страной и датой/временем, если они есть (`???` / `UNK` —
неизвестные значения).

## Названия стран, валют и приложений

Парсер EMV переводит коды по справочникам на SD-карте:

- `/ext/nfc/assets/aid.nfc` — идентификаторы приложений → названия;
- `/ext/nfc/assets/country_code.nfc` — коды стран ISO;
- `/ext/nfc/assets/currency_code.nfc` — коды валют ISO.

У каждого файла заголовок `Filetype: Flipper EMV resources`, `Version: 1`, затем строки `<код>: <название>`, например
`0985: PLN`. См. [формат файлов](/ru/nfc/file-format#emv-resources).

## Что не работает и почему

- **Эмуляция / оплата** — невозможна. Карта вычисляет криптограмму для каждой операции своими закрытыми ключами.
- **Нет номера карты** — некоторые карты и большинство кошельков в телефонах отдают токенизированный номер или ничего
  без диалога с терминалом.
- **Гибридные карты** (банковская + транспортная/пропускная) — используйте `Extra Actions → Read Specific Card Type`,
  чтобы прочитать другую часть.

::: warning Конфиденциальность
Сохранённый дамп EMV может содержать номер карты и срок действия. Не делитесь им.
:::

## См. также

[Чтение меток](/ru/nfc/read) · [Поддерживаемые карты](/ru/nfc/supported-cards) · [Формат файлов NFC](/ru/nfc/file-format)
