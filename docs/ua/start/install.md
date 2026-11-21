---
title: Встановлення Unleashed
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-readme, unleashed-src, flipper-docs]
---
# Встановлення Unleashed

Встановити прошивку Unleashed можна кількома способами. Усі вони встановлюють один і той самий пакет оновлення,
у якому є прошивка, оновлювач і всі ресурси (застосунки, бібліотеки ІЧ-пультів, налаштування Sub-GHz тощо).

::: tip Перед початком
- **Лише для першого встановлення:** спершу оновіться до **останнього офіційного релізу**
  ([Перший запуск](/ua/start/first-start)).
- **Якщо Unleashed уже стоїть:** нічого проміжного встановлювати не треба. Ставте нову версію поверх поточної.
- Переконайтеся, що **картка microSD вставлена**. Оновлення розпаковується на картку, і застосунки лежать там же.
- Зарядіть акумулятор. Повне оновлення триває кілька хвилин.
:::

## Який файл завантажувати {#which-file-to-download}

Файли релізів називаються `flipper-z-f7-update-(version)(e / c).tgz`:

| Частина | Що означає |
|---|---|
| `flipper-z` | Для пристрою Flipper Zero |
| `f7` | Апаратна платформа. Однакова для всіх Flipper Zero |
| `update` | Пакет самооновлення: оновлювач, прошивка та всі ресурси |
| `(version)` | Версія прошивки |
| суфікс | Варіант набору застосунків, див. нижче |

| Суфікс | [Base Apps](https://github.com/xMasterX/all-the-plugins#default-pack) | [Extra Apps](https://github.com/xMasterX/all-the-plugins#extra-pack) |
|---|:---:|:---:|
| `e` | ✅ | ✅ |
| *(немає)* | ✅ | — |
| `c` | — | — |

- **`e`** — усе. Базовий набір плюс додатковий набір застосунків спільноти. Якщо не впевнені, беріть цей.
- **Без суфікса** — лише базовий набір застосунків спільноти.
- **`c`** («clean») — без застосунків спільноти.

**Вбудовані системні застосунки** (MFKey, T5577, Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer,
Sub-GHz RAW Edit, SIM800, FindMy Flipper, пульти USB/BT, Snake…) постачаються **разом із самою прошивкою** і є
в **кожному** варіанті, зокрема в `c`. Див. [Можливості Unleashed](/ua/start/unleashed-features#built-in-apps).

Інші файли релізу:
- `flipper-z-any-scripts-(version).tgz` — папка `scripts` для розробки прошивки та застосунків;
- `flipper-z-f7-sdk-(version).zip` — SDK для розробки застосунків та uFBT.

## Спосіб 1: qUnleashed (рекомендований)

[qUnleashed](/ua/mobile/qunleashed-app) — власний супутній застосунок команди Unleashed. Він сам завантажує
й встановлює прошивку, тому вибирати файл не потрібно. Працює на **Android, iOS, Windows, macOS і Linux** —
по USB на всіх, окрім iOS: там підключення лише по Bluetooth.

1. Встановіть qUnleashed для своєї системи зі
   [сторінки релізів](https://github.com/DarkFlippers/qUnleashed/releases).
2. Під’єднайте Фліппер по USB або спаруйте його по Bluetooth (на iOS — тільки Bluetooth).
3. Відкрийте в застосунку **оновлення прошивки**.
4. Виберіть канал **Unleashed** — **Release** або **Dev**.
5. Виберіть збірку: **базову**, **з додатковими застосунками** або **компактну**
   ([що в них входить](#which-file-to-download)).
6. Запустіть встановлення й почекайте. Фліппер перезавантажиться в оновлювач і пройде всі етапи.

Якщо Фліппер уже не завантажується, тим самим застосунком його можна перепрошити по USB через
**Repair from DFU mode**. Див. [Відновлення](/ua/start/recovery#firmware-recovery).

Способи нижче — альтернативні. Візьміть один із них, якщо qUnleashed вам не підходить.

## Спосіб 2: Unleashed Web Installer

Потрібні **браузер на основі Chromium** (Chrome, Edge, Opera, Brave, Vivaldi) і кабель USB.

1. Закрийте **qFlipper** та інші вебсторінки для Фліппера — вони тримають послідовний порт.
2. Під’єднайте Фліппер по USB.
3. Відкрийте **[web.unleashedflip.com](https://web.unleashedflip.com)**.
4. Натисніть **Connect** і виберіть свій Фліппер у вікні браузера.
5. Виберіть гілку **Release** або **Dev**.
6. Натисніть **Install** і почекайте. Фліппер перезавантажиться в оновлювач і пройде всі етапи.
7. Готово. Усі ресурси встановлено.

## Спосіб 3: вебоновлювач Flipper Lab

1. Відкрийте [сторінку останнього релізу](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
2. Під’єднайте Фліппер і натисніть посилання **Install via Web Updater**.
3. На сторінці вебоновлювача натисніть **Connect**, потім **Install**.
4. Дочекайтеся завершення оновлення.

![Вебоновлювач](/img/remote/b803c9d8ec0350d6.png)

## Спосіб 4: qFlipper (1.2.0 або новіший)

1. Встановіть [qFlipper](https://flipperzero.one/update) 1.2.0+ (старіші версії не вміють встановлювати файли `.tgz`).
2. Завантажте `flipper-z-f7-update-(version).tgz` зі [сторінки релізів](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
3. Запустіть qFlipper і під’єднайте Фліппер.
4. Натисніть **Install from file** і виберіть завантажений `.tgz`.
5. Почнеться оновлення. Дочекайтеся завершення.

![Встановлення з файлу в qFlipper](/img/remote/f1a3ede83085d040.png)

::: warning
**Не** натискайте кнопку **Update** у qFlipper після встановлення Unleashed — вона встановить **офіційну** прошивку
замість Unleashed. Користуйтеся **Install from file**.
:::

## Спосіб 5: Flipper Mobile App

### Android, з файлом `.tgz`
1. Завантажте `flipper-z-f7-update-(version).tgz` на телефон.
2. У застосунку Flipper відкрийте **Update channel** і виберіть **Custom**.
3. Виберіть завантажений `.tgz` і натисніть **Update**.
4. Дочекайтеся завершення оновлення.

### Android, через посилання вебоновлювача
1. На сторінці релізу натисніть **Install via Web Updater**.
2. Коли запитають, чим відкрити — браузером чи застосунком Flipper, — виберіть **Flipper App**.
3. Продовжіть встановлення й почекайте.

### iOS
1. Завантажте `flipper-z-f7-update-(version).tgz`.
2. Відкрийте файл у застосунку **Files**. Натисніть **Share** і виберіть **Flipper App**.
3. У застосунку Flipper натисніть зелену кнопку **Update**. Перевірте, що канал оновлення показує
   `Custom flipper-z-f7-update...`.
4. Почекайте. **Застосунок для iOS може в кінці показати помилку, але Фліппер оновлюється успішно.**

## Спосіб 6: офлайн-оновлення з картки microSD

Жодних програм на комп’ютері не потрібно. Працює і з ПК, і з телефона.

1. Розпакуйте `flipper-z-f7-update-(version).tgz` (або `.zip`). Усередині є папка `f7-update-(version)` із файлами
   `update.fuf`, `resources.tar` та іншими.
2. Вставте картку в ПК або телефон чи завантажте файли через qFlipper.
3. Створіть папку `update` у **корені** картки й перенесіть у неї `f7-update-(version)`:
   ```text
   /ext/update/f7-update-(version)/update.fuf
   /ext/update/f7-update-(version)/resources.tar
   ...
   ```
4. Перевірте, що на місці **всі** файли. Стандартний застосунок Files на iOS може показати лише 3 з 6 файлів —
   скористайтеся іншим архіватором, ПК або Android.
5. Вставте картку назад у Фліппер.
6. Відкрийте **Archive** (<kbd>↓</kbd> на робочому столі), перейдіть на вкладку **Browser**, знайдіть
   `update/f7-update-(version)/` і відкрийте `update.fuf`.
7. Почнеться оновлення. Дочекайтеся завершення всіх етапів.

![Офлайн-оновлення](/img/remote/92717373349f3b7c.png)

## Після встановлення

- Екран **Settings → About** показує інформацію про прошивку Unleashed та її версію.
- Під час першого завантаження після оновлення Фліппер розпаковує ресурси на картку. Це нормально.
- Прочитайте [Можливості Unleashed](/ua/start/unleashed-features) і налаштуйте пристрій за
  сторінкою [Налаштування](/ua/start/settings).

## Якщо щось не працює

| Проблема | Що зробити |
|---|---|
| Браузер не може підключитися | Закрийте qFlipper та інші вкладки Flipper Lab. Користуйтеся браузером на Chromium. Спробуйте інший кабель або порт |
| Оновлення зривається або зависає | Перезавантажте пристрій комбінацією <kbd>←</kbd> + <kbd>BACK</kbd>, перевірте картку, спробуйте інший спосіб |
| Мобільний застосунок не підключається після встановлення | Видаліть Фліппер зі списку в застосунку та в налаштуваннях Bluetooth телефона. Далі виконайте на Фліппері **Settings → Bluetooth → Unpair All Devices** і спаруйте заново |
| Після встановлення не працює підсвічування | Див. [FAQ](/ua/start/faq#backlight-does-not-work) (налаштування RGB-моду) |
| Пристрій не вмикається / «цеглина» | [Відновлення](/ua/start/recovery) |
