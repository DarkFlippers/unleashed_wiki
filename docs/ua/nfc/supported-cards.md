---
title: Підтримувані картки (парсери)
order: 85
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/nfc/read]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Підтримувані картки (парсери)

Для багатьох карток Flipper не просто знімає дамп пам'яті, а **декодує** її: номер картки, баланс, залишок
поїздок, термін дії, дані про готельний номер, іграшкову фігурку… Це роблять **плагіни-парсери** — невеликі файли
`.fal`, які застосунок NFC завантажує з SD-картки після успішного зчитування. Коли парсер розпізнає картку, на
екрані результату показуються декодовані дані замість «сирого» підсумку; **More** веде до звичайного меню.

Деякі парсери також несуть **ключі** системи картки (або функцію виведення ключів). Для карток MIFARE Classic це
означає, що Flipper читає картку **повністю без словникової атаки**: парсер спочатку перевіряє, що картка
належить системі, а потім читає її правильними ключами.

::: tip Unleashed
Unleashed постачається з багатьма парсерами, яких немає в стоковій прошивці, передусім для систем Росії та СНД:
Umarsh, «Золота корона» (і Online), Kazan, Metromoney, Moscow Social Card, перероблена «Трійка», Plantain,
Troika+Plantain, приміські залізничні квитки ППК, а також мітки філаменту Bambu Lab, аркадні картки
Banapass/Aime/AIC, насадки Sonicare тощо (від @Leptopt1los, @assasinfil і багатьох контриб'юторів).
:::

## Перелік парсерів

«Вбудовані ключі» означає, що парсер може прочитати картку власними ключами (або виведенням ключів), і словник не
потрібний.

### Транспорт

| Картка (як показано) | Протокол | Регіон | Вбудовані ключі | Що показує |
|---|---|---|---|---|
| Troyka card | MIFARE Classic | Москва, Росія | так | дані транспортного застосунку |
| Plantain Card | MIFARE Classic | Санкт-Петербург, Росія | так | дані картки, приміський квиток ППК |
| Troika+Plantain | MIFARE Classic | Росія | так | обидва застосунки на одній картці |
| Social card (Moscow Social Card) | MIFARE Classic | Москва, Росія | так | номер картки (ОМС), термін дії |
| Kazan transport card | MIFARE Classic | Казань, Росія | так | тип квитка, баланс |
| Umarsh | MIFARE Classic | Росія (регіональні системи) | ні (для секторів 0, 8, 12 потрібен ключ B) | дані картки |
| Zolotaya korona | MIFARE Classic | Росія | ні | дані картки |
| Zolotaya korona (Online) | MIFARE Classic | Росія | ні | дані картки й тарифу |
| SZPPK Accompany Card | MIFARE Classic | Росія, приміська залізниця (СЗППК) | так | термін дії, станція, вхід/вихід, лічильник проходів |
| SKPPK Transport Card | MIFARE Classic | Росія, приміська залізниця (СКППК) | так | станція, останній прохід, статус, лічильник проходів |
| SevPPK Transport Card | MIFARE Classic | Росія, приміська залізниця (СевППК) | так | станція, останній прохід, статус, лічильник проходів |
| Metromoney | MIFARE Classic | Тбілісі, Грузія | так | дані квитка |
| CharlieCard | MIFARE Classic | Бостон (MBTA), США | так | баланс, транзакції |
| Clipper | MIFARE DESFire | район Сан-Франциської бухти, США | — | серійний номер, баланс, поїздки (перевізник, тариф, дата) |
| Ventra | MIFARE Ultralight | Чикаго (CTA), США | — | залишок поїздок, термін дії |
| Tarjeta Bip! | MIFARE Classic | Сантьяго, Чилі | так | номер картки, баланс |
| SmartRider | MIFARE Classic | Перт, Австралія | так | баланс, пільга, серійний номер |
| Opal | MIFARE DESFire | Сідней, Австралія | — | баланс, останні вхід/вихід |
| myki | MIFARE DESFire | Мельбурн, Австралія | — | номер картки |
| ITSO Card | MIFARE DESFire | Велика Британія | — | дані картки |
| TRT Tianjin Metro | MIFARE Ultralight | Тяньцзінь, Китай | — | баланс, дата продажу |
| All-In-One | MIFARE Ultralight | транспортний квиток | — | номер, залишок поїздок |

### Доступ, готелі, платежі та сервіс

| Картка (як показано) | Протокол | Що це | Вбудовані ключі | Що показує |
|---|---|---|---|---|
| HID Card | MIFARE Classic | перепустка HID, записана на картку Classic | так | довжина в бітах і значення перепустки |
| Gallagher NZ | MIFARE Classic | контроль доступу Gallagher (Нова Зеландія) | — | перепустки (на картці їх може бути кілька) |
| Saflok MFC 1K Card / Saflok UL-C Card | MIFARE Classic, Ultralight C | готельні замки Saflok | так (KDF) | номер об'єкта, ID ключа, запис ключа, рівень доступу |
| H World Card | MIFARE Classic | готельні ключі H World (материковий Китай) | так | номер кімнати, дати заселення й завершення |
| CSC Service Works | MIFARE Classic | поповнювана картка для пралень (США) | — | баланс, останнє поповнення, залишок використань |
| WashCity | MIFARE Classic | картка пралень WashCity / MarkItaly (Європа) | так | баланс у EUR |
| MiZIP Card | MIFARE Classic | ключі торговельних автоматів MiZIP | так | UID, кредит, попередній кредит |
| Microel Card | MIFARE Classic | ключі торговельних автоматів Microel | так (виводяться з UID) | UID, кредит, попередній кредит |
| HI! Card | MIFARE Classic | картка HI! | так | UID |
| MyKey | ST25TB | ключі торговельних автоматів MyKey | — | серійний номер, стан «чистий/заблокований», LockID |
| EMV | EMV | банківські картки | — | див. [Банківські картки (EMV)](/ua/nfc/emv) |

### Ігри, іграшки та інше

| Картка (як показано) | Протокол | Що це | Вбудовані ключі |
|---|---|---|---|
| Aime Card | MIFARE Classic | аркадна картка SEGA Aime (код доступу) | так |
| Banapass | MIFARE Classic | Bandai Namco Passport (код доступу, значення) | так |
| Amusement IC Card | FeliCa | аркадні картки (SEGA Aime, Bandai Namco Passport) | — |
| Skylanders | MIFARE Classic | фігурки Skylanders (ім'я персонажа) | так |
| Disney Infinity | MIFARE Classic | фігурки Disney Infinity | так (виводяться) |
| Bambu Lab Filament | MIFARE Classic 1K | мітки котушок філаменту Bambu Lab (тип, код філаменту, матеріал, колір…) | так (виводяться) |
| Philips Sonicare head | MIFARE Ultralight | насадки зубних щіток Sonicare | — |
| NDEF Format Data | Ultralight/NTAG, MIFARE Classic, SLIX, Type 4 Tag | повідомлення NDEF: URI (включно з телефоном і поштою), Text, MAC Bluetooth, Contact, Wi-Fi, SmartPoster | — |

Початковий код кожного парсера лежить у
[`applications/main/nfc/plugins/supported_cards`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards).
Деякі парсери використовують довідники з `/ext/nfc/assets/` (наприклад, `skylanders.nfc`, `vendors.nfc`,
`sk_id.nfc`, `sz_id.nfc`, `sev_id.nfc` для назв станцій, `aid.nfc`/`country_code.nfc`/`currency_code.nfc` для
EMV).

## Примітки

- Парсер картки з «вбудованими ключами» спочатку перевіряє картку; якщо перевірка не проходить (інші ключі, інша
  система), запускається звичайна словникова атака.
- Деякі парсери повідомляють, чого не вистачає — наприклад, *«Unknown SKPPK Card — TICKET BLOCKS NOT READ — RUN A
  DICTIONARY ATTACK TO READ THE TICKET SECTORS»*.
- **«Plugin Not Loaded — Plugin file missing or outdated. Update the firmware resources.»**: файли `.fal` на
  SD-картці не відповідають прошивці. Перевстановіть прошивку зі вставленою SD-картою.
- Парсер лише показує дані. Зміна балансу в дампі та його емуляція — це шахрайство у транспортних і платіжних
  системах.

## Пов'язані сторінки

[Зчитування міток](/ua/nfc/read) · [Банківські картки (EMV)](/ua/nfc/emv) ·
[MIFARE Classic](/ua/nfc/mifare-classic) · [Картки Moskvyonok](/ua/nfc/moskvyonok)
