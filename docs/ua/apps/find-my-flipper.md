---
title: FindMy Flipper
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/find_my_flipper, https://github.com/MatthewKuKanich/FindMyFlipper, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# FindMy Flipper

**FindMy Flipper** (автор @MatthewKuKanich) перетворює Bluetooth у Flipper на маячок-трекер. Flipper транслює ті
самі BLE-оголошення, що й мітка, а телефони мережі пошуку, які опиняються поблизу, повідомляють його
місцезнаходження — тож загублений Flipper можна знайти в застосунку власника мітки.

Підтримувані типи міток: **Apple AirTag** (Find My), **Samsung SmartTag** (SmartThings Find), **Tile SmartTag** і
**Google Find My** (Find My Device).

`Main Menu → Apps → Bluetooth → FindMy Flipper`

::: tip Unleashed
FindMy Flipper постачається разом із прошивкою, а Unleashed додатково встановлює невеликий хук запуску: якщо маячок
працював у момент вимкнення Flipper, він **автоматично запускається знову після перезавантаження**, без відкриття
застосунку. Маячок продовжує працювати у фоні, поки ви користуєтеся іншими застосунками.
:::

::: warning
Використовуйте це лише зі власними мітками й пристроями. Відслідковування інших людей може бути незаконним там,
де ви живете.
:::

## Що потрібно

Flipper потрібні **MAC-адреса** та **payload** мітки (або файл ключів). Отримати їх можна одним із двох способів:

- **Клонувати наявну мітку** (найпростіше; місцезнаходження потім видно у звичайному застосунку власника мітки).
- **Згенерувати власні ключі** методом OpenHaystack (фізична мітка не потрібна, працює лише мережа Apple;
  місцезнаходження дивитимете в OpenHaystack або в альтернативі без Mac).

### Варіант A: клонувати наявну мітку

1. Спаруйте AirTag чи SmartTag із телефоном як завжди.
2. Переведіть її в режим «втраченої»: тримайте подалі від телефона, до якого вона прив’язана, близько 15 хвилин.
3. На телефоні з Android встановіть **nRF Connect** (версія для iOS не показує сирих даних).
4. У nRF Connect виставте фільтр на бренд мітки (Apple або Samsung), опустіть RSSI на найнижче значення й запустіть
   сканування.
5. Коли мітка з’явиться як пристрій «FindMy», відкрийте **Raw** / **View Raw** і запишіть **payload** та
   **MAC-адресу**. Можна також експортувати це у файл `.txt`.
6. **Негайно вийміть батарейку з мітки**, інакше вона змінить свій ключ і MAC, і ваша копія перестане працювати.

### Варіант B: ключі OpenHaystack

1. Завантажте `generate_keys.py` з [репозиторію FindMyFlipper](https://github.com/MatthewKuKanich/FindMyFlipper) і
   запустіть його (потрібно `python3 -m pip install cryptography`).
2. Він видасть **Private Key**, **Public Key**, **Payload** і **MAC Address**, а також файл `.keys`.
3. Збережіть Private Key: він потрібен, щоб отримувати звіти про місцезнаходження.
4. Дивіться місцезнаходження в [OpenHaystack](https://github.com/seemoo-lab/openhaystack) (Mac, macOS нижче 14) або
   без Mac — через [macless-haystack](https://github.com/dchristl/macless-haystack) чи
   [Chapoly1305/FindMy](https://github.com/Chapoly1305/FindMy).

## Налаштування Flipper

1. Скопіюйте експортований з nRF Connect файл `.txt` або файл `.keys` до `/ext/apps_data/findmy/` на SD-карті (або
   пропустіть цей крок і введіть дані вручну).
2. Відкрийте `Apps → Bluetooth → FindMy Flipper` і натисніть <kbd>→</kbd> (**Config**).
3. Виберіть **Register Tag**, а потім тип мітки: `Apple AirTag`, `Samsung SmartTag`, `Tile SmartTag` або
   `Google Find My`.
4. Виберіть спосіб імпорту:
   - `nRF Connect (.txt)`: виберіть експортований файл;
   - `OpenHaystack (.keys)`: виберіть файл ключів;
   - `Register Tag Manually`: введіть MAC-адресу, а потім payload.
5. Повернітеся на головний екран і натисніть <kbd>OK</kbd>. Надпис зміниться на `Broadcast Active`.

## Головний екран

| Кнопка | Дія |
|---|---|
| <kbd>OK</kbd> | запустити / зупинити маячок (`Broadcast Active` / `Broadcast Inactive`) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | змінити інтервал трансляції |
| <kbd>→</kbd> | Config |
| <kbd>←</kbd> | вийти із застосунку, залишивши маячок працювати у фоні |
| <kbd>Back</kbd> | закрити застосунок |

## Меню Config

| Пункт | Значення | Примітки |
|---|---|---|
| Broadcast Interval | 1-10 с (Google: 1-2 с) | як часто надсилається маячок; Google вимагає не рідше ніж кожні 2 с |
| Transmit Power | 0-6 дБм | більше потужності = більша дальність і більша витрата акумулятора |
| Register Tag | | тип мітки та імпорт (див. вище) |
| Show MAC | Yes / No | показувати MAC на головному екрані |

Застосунок зберігає свій стан у `/ext/apps_data/findmy/findmy_state.txt` — саме це дозволяє маячку відновитися
після перезавантаження.

## Відслідковування

- **Клон AirTag**: Flipper з’являється як ваш AirTag у застосунку Find My.
- **Клон SmartTag**: у SmartThings (SmartThings Find), на телефоні або в браузері.
- **Ключі OpenHaystack**: в OpenHaystack або macless-haystack.

## Усунення проблем

- **Місцезнаходження не оновлюється**: ключ/MAC мітки змінився до того, як ви вийняли батарейку; зніміть дані знову.
- **Маячок не працює після перезавантаження**: перевірте, що SD-карту вставлено (файл стану лежить на ній) і що до
  вимкнення маячок був у стані `Broadcast Active`.
- **Акумулятор швидше сідає**: збільште інтервал трансляції й зменште потужність передавання.

## Пов’язані сторінки

- [Застосунки у складі Unleashed](/ua/apps/catalog)
- [Налаштування](/ua/start/settings)
