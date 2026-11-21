---
title: Поддерживаемые карты (парсеры)
order: 85
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/nfc/read]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Поддерживаемые карты (парсеры)

Многие карты Флиппер не просто дампит, а **расшифровывает**: номер карты, баланс, остаток поездок, срок действия,
данные гостиничного номера, фигурку игрушки… Этим занимаются **плагины-парсеры** — небольшие файлы `.fal`, которые
NFC-приложение подгружает с SD-карты после успешного чтения. Если парсер узнал карту, на экране результата вместо
сырой сводки будут расшифрованные данные; **More** ведёт в обычное меню.

Часть парсеров содержит **ключи** системы (или функцию их вычисления). Для карт MIFARE Classic это значит, что
Флиппер читает карту **целиком без атаки по словарю**: парсер сначала проверяет, что карта принадлежит системе, а потом
читает её нужными ключами.

::: tip Unleashed
В Unleashed много парсеров, которых нет в стоке, особенно для российских и СНГ-систем: Умарш, Золотая Корона (и
Online), Казань, Metromoney, Социальная карта москвича, переработанная Тройка, Подорожник, Тройка+Подорожник, билеты
ППК, а также катушки филамента Bambu Lab, аркадные карты Banapass/Aime/AIC, насадки Sonicare и другое (авторы
@Leptopt1los, @assasinfil и многие контрибьюторы).
:::

## Список парсеров

«Встроенные ключи» — парсер читает карту своими ключами (или вычисляет их), словарь не нужен.

### Транспорт

| Карта (как показывается) | Протокол | Регион | Встроенные ключи | Что показывает |
|---|---|---|---|---|
| Troyka card | MIFARE Classic | Москва, Россия | да | данные транспортного приложения |
| Plantain Card | MIFARE Classic | Санкт-Петербург, Россия | да | данные карты, билет ППК |
| Troika+Plantain | MIFARE Classic | Россия | да | оба приложения на одной карте |
| Social card (Социальная карта москвича) | MIFARE Classic | Москва, Россия | да | номер карты (ОМС), срок действия |
| Kazan transport card | MIFARE Classic | Казань, Россия | да | тип билета, баланс |
| Umarsh | MIFARE Classic | Россия (региональные системы) | нет (нужен ключ B для секторов 0, 8, 12) | данные карты |
| Zolotaya korona | MIFARE Classic | Россия | нет | данные карты |
| Zolotaya korona (Online) | MIFARE Classic | Россия | нет | данные карты и тарифа |
| SZPPK Accompany Card | MIFARE Classic | Россия, пригородные поезда (СЗППК) | да | срок действия, станция, вход/выход, счётчик проходов |
| SKPPK Transport Card | MIFARE Classic | Россия, пригородные поезда (СКППК) | да | станция, последний проход, статус, счётчик проходов |
| SevPPK Transport Card | MIFARE Classic | Россия, пригородные поезда (СевППК) | да | станция, последний проход, статус, счётчик проходов |
| Metromoney | MIFARE Classic | Тбилиси, Грузия | да | данные билета |
| CharlieCard | MIFARE Classic | Бостон (MBTA), США | да | баланс, транзакции |
| Clipper | MIFARE DESFire | Область залива Сан-Франциско, США | — | серийный номер, баланс, поездки (перевозчик, тариф, дата) |
| Ventra | MIFARE Ultralight | Чикаго (CTA), США | — | остаток поездок, срок действия |
| Tarjeta Bip! | MIFARE Classic | Сантьяго, Чили | да | номер карты, баланс |
| SmartRider | MIFARE Classic | Перт, Австралия | да | баланс, льгота, серийный номер |
| Opal | MIFARE DESFire | Сидней, Австралия | — | баланс, последний вход/выход |
| myki | MIFARE DESFire | Мельбурн, Австралия | — | номер карты |
| ITSO Card | MIFARE DESFire | Великобритания | — | данные карты |
| TRT Tianjin Metro | MIFARE Ultralight | Тяньцзинь, Китай | — | баланс, дата продажи |
| All-In-One | MIFARE Ultralight | проездной билет | — | номер, остаток поездок |

### СКУД, гостиницы, оплата и сервисы

| Карта (как показывается) | Протокол | Что это | Встроенные ключи | Что показывает |
|---|---|---|---|---|
| HID Card | MIFARE Classic | идентификатор HID на карте Classic | да | длина в битах и значение идентификатора |
| Gallagher NZ | MIFARE Classic | СКУД Gallagher (Новая Зеландия) | — | идентификаторы (на карте может быть несколько) |
| Saflok MFC 1K Card / Saflok UL-C Card | MIFARE Classic, Ultralight C | гостиничные замки Saflok | да (KDF) | номер объекта, ID ключа, запись ключа, уровень доступа |
| H World Card | MIFARE Classic | гостиничные ключи H World (материковый Китай) | да | номер комнаты, даты заезда и окончания |
| CSC Service Works | MIFARE Classic | пополняемая карта прачечных (США) | — | баланс, последнее пополнение, остаток использований |
| WashCity | MIFARE Classic | карта прачечных WashCity / MarkItaly (Европа) | да | баланс в EUR |
| MiZIP Card | MIFARE Classic | ключи вендинга MiZIP | да | UID, кредит, предыдущий кредит |
| Microel Card | MIFARE Classic | ключи вендинга Microel | да (из UID) | UID, кредит, предыдущий кредит |
| HI! Card | MIFARE Classic | карта HI! | да | UID |
| MyKey | ST25TB | ключи вендинга MyKey | — | серийный номер, состояние чистая/заблокирована, LockID |
| EMV | EMV | банковские карты | — | см. [Банковские карты (EMV)](/ru/nfc/emv) |

### Игры, игрушки и прочее

| Карта (как показывается) | Протокол | Что это | Встроенные ключи |
|---|---|---|---|
| Aime Card | MIFARE Classic | аркадная карта SEGA Aime (код доступа) | да |
| Banapass | MIFARE Classic | Bandai Namco Passport (код доступа, значение) | да |
| Amusement IC Card | FeliCa | аркадные карты (SEGA Aime, Bandai Namco Passport) | — |
| Skylanders | MIFARE Classic | фигурки Skylanders (имя персонажа) | да |
| Disney Infinity | MIFARE Classic | фигурки Disney Infinity | да (вычисляются) |
| Bambu Lab Filament | MIFARE Classic 1K | метки катушек филамента Bambu Lab (тип, код филамента, материал, цвет…) | да (вычисляются) |
| Philips Sonicare head | MIFARE Ultralight | насадки зубных щёток Sonicare | — |
| NDEF Format Data | Ultralight/NTAG, MIFARE Classic, SLIX, Type 4 Tag | NDEF-сообщения: URI (в т.ч. телефон, почта), Text, Bluetooth MAC, Contact, Wi-Fi, SmartPoster | — |

Исходники всех парсеров — в
[`applications/main/nfc/plugins/supported_cards`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards).
Часть парсеров использует справочники из `/ext/nfc/assets/` (например `skylanders.nfc`, `vendors.nfc`, `sk_id.nfc`,
`sz_id.nfc`, `sev_id.nfc` для названий станций, `aid.nfc`/`country_code.nfc`/`currency_code.nfc` для EMV).

## Примечания

- Парсер карты «со встроенными ключами» сначала проверяет карту; если проверка не прошла (другие ключи, другая
  система), запускается обычная атака по словарю.
- Некоторые парсеры пишут, чего не хватает, например *«Unknown SKPPK Card — TICKET BLOCKS NOT READ — RUN A DICTIONARY
  ATTACK TO READ THE TICKET SECTORS»*.
- **«Plugin Not Loaded — Plugin file missing or outdated. Update the firmware resources.»** — файлы `.fal` на SD-карте
  не соответствуют прошивке. Переустановите прошивку со вставленной SD-картой.
- Парсер только показывает данные. Изменение баланса в дампе и его эмуляция в транспортных и платёжных системах —
  мошенничество.

## См. также

[Чтение меток](/ru/nfc/read) · [Банковские карты (EMV)](/ru/nfc/emv) · [MIFARE Classic](/ru/nfc/mifare-classic) ·
[Карты «Москвёнок»](/ru/nfc/moskvyonok)
