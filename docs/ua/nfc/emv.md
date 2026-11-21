---
title: Банківські картки (EMV)
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/emv, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md]
sources: [unleashed-src, unleashed-readme, unleashed-docs]
---
# Банківські картки (EMV)

Безконтактні банківські картки й гаманці у смартфонах використовують **EMV** поверх ISO14443-4. Flipper може
зчитати **публічну** інформацію, яку картка видає будь-якому терміналу, і показати її в читабельному вигляді.
Секретні ключі він прочитати не може й **не вміє емулювати чи клонувати** банківську картку: кожний платіж
підписується ключем, який ніколи не покидає чип.

::: tip Unleashed
Протокол EMV і парсер публічних даних походять з Unleashed (від @Leptopt1los і @wosk).
:::

## Як зчитати банківську картку

1. `Main Menu → NFC → Read`, піднесіть картку (або розблокований смартфон з відкритим гаманцем) до задньої
   частини Flipper.
2. Розібраний результат показує те, що картка розкрила, наприклад:
   - мітку або назву застосунку (наприклад, платіжної системи) чи просто `EMV`;
   - номер картки (PAN), згрупований по 4 цифри;
   - `Cardholder name:` (більшість сучасних карток його вже не передають);
   - дати `Effective:` / `Expires:` (у форматі дати вашої локалі);
   - `Country:` і `Currency:` емісії;
   - `PIN attempts left:`;
   - `Mobile: yes` для гаманців у смартфонах і годинниках;
   - *«No data was parsed»*, якщо нічого корисного не повернулося.
3. <kbd>→</kbd> **More** відкриває меню: **Save**, **Transactions** (лише якщо картка повернула журнал
   транзакцій), **Info**.

Екран **Info** показує технічний вигляд: UID, `AID`, `Interchange profile`, `Currency code`, `Country code`,
`Transactions count` і `Last Online ATC`, якщо він доступний.

## Транзакції

Деякі картки зберігають короткий журнал останніх транзакцій і видають його без PIN-коду.
`More → Transactions` показує кожний запис із лічильником (ATC), сумою, валютою, країною й датою/часом, якщо вони
є (`???` / `UNK` для невідомих значень).

## Назви країн, валют і застосунків

Парсер EMV розшифровує коди за довідниками на SD-картці:

- `/ext/nfc/assets/aid.nfc`: ID застосунків → назви;
- `/ext/nfc/assets/country_code.nfc`: коди країн ISO;
- `/ext/nfc/assets/currency_code.nfc`: коди валют ISO.

У кожного файлу є заголовок `Filetype: Flipper EMV resources`, `Version: 1`, а далі рядки `<code>: <name>`,
наприклад `0985: PLN`. Див. [формат файлів](/ua/nfc/file-format#emv-resources).

## Що не працює і чому

- **Емуляція / платежі**: неможливі. Картка обчислює криптограму для кожної транзакції своїми приватними
  ключами.
- **Номер картки відсутній**: деякі картки й більшість гаманців у смартфонах видають токенізований номер або
  взагалі нічого без діалогу з терміналом.
- **Гібридні картки** (банківська картка + транспортний чи пропускний чип): скористайтеся
  `Extra Actions → Read Specific Card Type`, щоб прочитати другу частину.

::: warning Приватність
Збережений дамп EMV може містити номер вашої картки й термін її дії. Не поширюйте його.
:::

## Пов'язані сторінки

[Зчитування міток](/ua/nfc/read) · [Підтримувані картки](/ua/nfc/supported-cards) ·
[Формат файлів NFC](/ua/nfc/file-format)
