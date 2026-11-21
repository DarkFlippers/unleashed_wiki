---
title: Seed Capturer
order: 190
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/seed_capturer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Seed Capturer

**FAAC SLH**, **Genius**, **Erreka** і **BFT Mitto** будують динамічний код із секретного **Seed**. Без нього Flipper не може ні декодувати ці пульти (вони читаються як `KL: Unknown` або не читаються зовсім), ні створити пульт, який приймач прийме. **Seed Capturer** (від @xMasterX) збирає сировину для відновлення Seed: `Fix` пульта й серію послідовних значень `Hop`.

Сам Seed він **не відновлює** і **ніколи не передає** — лише слухає й пише файл. Пошук виконується в супутньому застосунку [qUnleashed](/ua/mobile/qunleashed-app).

::: tip Unleashed
Seed Capturer — вбудований системний застосунок Unleashed, а qUnleashed читає його записи просто з Flipper. Коли Seed відомий, Unleashed може декодувати пульт і створювати нові через `Add Manually [Advanced]`.
:::

## Коли це потрібно

- Радіопрограмування приймача вимкнене, тому єдиний шлях — клон відомого пульта, а клону потрібен Seed.
- Ваш пульт FAAC / Genius є **slave** і не може надіслати код програмування.
- Ви не маєте доступу до приймача.
- Інсталяції **Erreka**, де всі пульти мають один Seed.
- **Старіші пульти BFT Mitto** з унікальним Seed, коли шлях через кнопку програмування не працює (новіші пульти BFT виводять Seed із серійника й декодуються у звичайному Read).

Якщо пульт можна перевести в режим програмування, Seed часто передається у відкритому вигляді — цей шлях швидший, див. [Програмування нового пульта](/ua/subghz/remote-prog).

## Зчитування

1. Відкрийте `Main Menu → Apps → Sub-GHz → Seed Capturer`.
2. Виберіть `New capture`.
3. **Тип пульта:** `FAAC SLH`, `Genius`, `Erreka` або `BFT Mitto`.
4. **Частота:** `433.92 MHz  AM650` або `868.35 MHz  AM650` (для `BFT Mitto` доступна лише 433,92 МГц).
5. Натискайте **ту саму кнопку того самого пульта** раз за разом, приблизно раз на секунду, тримаючи пульт просто біля Flipper.
6. Дивіться на екран:
   - `Fix XXXXXXXX` — фіксована частина пульта; застосунок закріплюється за першою, яку почує;
   - `Hops n/10  Xpkt` — скільки **різних** hop зібрано й сира кількість пакетів;
   - стан `Hop n: XXXXXXXX` щоразу, коли надходить новий.
7. Починаючи з **2 hop**, на <kbd>OK</kbd> з'являється `Save`. Натисніть його; застосунок покаже `Saved N hops` та ім'я файла.

<kbd>←</kbd> (`Reset`) викидає запис, щоб ви могли закріпитися за іншим пультом або іншою кнопкою.

| Стан | Що означає |
|---|---|
| `Hop n: XXXXXXXX` | нову динамічну частину збережено — натискайте далі |
| `Other remote XXXXXXXX` | інший пульт або інша кнопка — ігнорується |
| `Same hop, ignored` | повтор останнього натискання |
| `Have 10, enough` | зібрано все — натискайте `Save` |

**Скільки натискань:** 2 — мінімум, 5–10 — краще. Не менш важливо, щоб натискання були **послідовними, без пропусків** — слідкуйте, щоб `Hops` збільшувався з кожним натисканням. Якщо одне пропустилося, натисніть `Reset` і почніть заново.

::: warning
На **FAAC SLH і Genius Seed різний для кожної кнопки** — зчитуйте саму ту кнопку, якою справді збираєтеся користуватися. На Erreka Seed один на пульт (іноді на інсталяцію), на BFT Mitto — на пульт.
:::

## Інші пункти меню

- `Decode RAW file` — узяти Fix/Hops із RAW-файла `.sub` (із `/ext/subghz`), записаного раніше через [Read RAW](/ua/subghz/read-raw); частота береться з файла. Файл ключа відкидається з повідомленням `Not a RAW capture`. Тут <kbd>←</kbd> працює як `Back`, а не `Reset`.
- `Delete all captures` — запитує `Delete every capture file in subghz_seed_captures?`, а потім видаляє їх.
- `Exit`.

## Файл запису

Файли потрапляють у `/ext/apps_data/subghz_seed_captures/` з іменем `<Type>_<Fix>_<date-time>.txt`, наприклад `Erreka_F00F1C9B_261008-142233.txt`. Це текстовий файл, а **не придатний для надсилання `.sub`**:

```text
Filetype: Flipper SubGhz Seed Capture
Version: 1
# Fix + Hop set for offline seed recovery, not a playable .sub
Received: 2026-10-08 14:22:33
Manufacturer: Erreka
Protocol: KeeLoq
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Fix: F00F1C9B
Hops: 3
# Hops in the order they were received
Hop: ...
Hop: ...
Hop: ...
```

## Відновлення Seed у qUnleashed

1. Підключіть Flipper до **qUnleashed** і відкрийте його інструмент відновлення Seed. Він сам забирає записи з `subghz_seed_captures` — нічого копіювати чи перейменовувати не потрібно.
2. Виберіть запис і запустіть пошук (це перебір, тому він і не виконується на Flipper).
3. Якщо Seed знайдено, qUnleashed може скласти готовий файл `.sub` із клоном (серійник і кнопка з `Fix` плюс Seed і лічильник) і покласти його на Flipper.
4. Якщо нічого не знайдено, у записі найімовірніше був пропуск — зчитайте ще раз, уважно.

Маючи Seed, можна також створювати пульти вручну в `Sub-GHz → Add Manually [Advanced]`: власний `SERIAL` + `SEED` для нового пульта або `SERIAL`/`BUTTON` оригіналу + `SEED` + трохи більший `COUNTER` для клона. Клон конфліктує з оригіналом через лічильник — див. [Динамічні коди](/ua/subghz/rolling-codes).

::: warning
Лише для пультів і приймачів, якими ви володієте.
:::

## Пов'язані сторінки

- [Програмування нового пульта](/ua/subghz/remote-prog) · [KeeLoq](/ua/subghz/keeloq) · [Add Manually](/ua/subghz/add-manually)
- [Застосунок qUnleashed](/ua/mobile/qunleashed-app)
