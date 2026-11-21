---
title: Мобільний застосунок Flipper
order: 20
original: [https://docs.flipper.net/zero/mobile-app, https://docs.flipper.net/zero/mobile-app/bug-report, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# Мобільний застосунок Flipper

Офіційний **Flipper Mobile App** ([App Store](https://apps.apple.com/us/app/flipper-mobile-app/id1534655259),
[Google Play](https://play.google.com/store/apps/details?id=com.flipperdevices.app)) підключається до Flipper через
Bluetooth. З ним можна оновлювати прошивку, переглядати й надсилати збережені ключі, встановлювати застосунки з
каталогу, керувати Flipper дистанційно та створювати резервні копії даних.

::: tip Unleashed
Офіційний мобільний застосунок працює з Unleashed. Він вміє встановлювати `.tgz` Unleashed як оновлення
**Custom** (див. нижче). Якщо після встановлення Unleashed або зміни імені Flipper застосунок перестав
підключатися, виконайте повторне спарювання — див. [Проблеми з підключенням](#connection-problems).
:::

## Підключення до Flipper

1. На Flipper: `Main Menu → Settings → Bluetooth`, переведіть **Bluetooth** у **ON**.
2. У застосунку натисніть **Connect**, а потім **Connect** поруч з іменем вашого Flipper.
3. Введіть **код спарювання**, показаний на екрані Flipper, і натисніть **Pair**.
4. Дочекайтеся завершення синхронізації.

## Що є в застосунку

- **Main Menu** (вкладка пристрою): оновлення через Bluetooth, **Device Info** (дані про апаратну частину й
  прошивку), **Options** (резервна копія, логи, файловий менеджер, перезавантаження, повідомлення про помилку;
  набір залежить від iOS/Android), ручна синхронізація, звуковий сигнал для пошуку Flipper.
- **Archive**: усі збережені файли Sub-GHz, RFID 125, NFC, Infrared та iButton. Улюблене, пошук і відновлення
  видалених елементів. Торкніться ключа, щоб відкрити **Key Info**: емуляція або надсилання, додавання до
  улюбленого, перейменування, примітка, подробиці, видалення, надсилання іншим.
- **Apps**: офіційний каталог застосунків, встановлення через Bluetooth LE, див.
  [Застосунки на SD-карті](/ua/apps/sd-card-apps).
- **Tools**: **Mfkey32** (Extract MF Keys) для обчислення ключів MIFARE Classic зі зібраних nonce та
  **Remotes Library** — бібліотека ІЧ-пультів (див. [ІЧ зі смартфона](/ua/infrared/mobile)).
- **Widget**: емуляція збережених пультів і карток із домашнього екрана смартфона без відкриття застосунку (на iOS
  Today View → Edit → Add Widget → Flipper; на Android додайте його як будь-який віджет і торкніться для
  налаштування).

## Встановлення Unleashed зі смартфона

::: warning Перше встановлення
Якщо це ваша перша кастомна прошивка, спочатку оновіться до найновішого **офіційного** релізу й переконайтеся, що
SD-картка вставлена. Уже на Unleashed? Просто встановіть нову версію поверх.
:::

### iOS

1. Відкрийте [найновіший реліз Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) і
   завантажте `flipper-z-f7-update-(version).tgz`.
2. У застосунку **Files** виберіть завантажений `.tgz`, натисніть **Share** і виберіть застосунок **Flipper**.
3. У застосунку Flipper перевірте, що Update Channel показує `Custom flipper-z-f7-update...`, і натисніть зелену
   кнопку **Update**.
4. Дочекайтеся завершення оновлення. Застосунок на iOS може в кінці показати помилку, але Flipper при цьому
   оновлено.

### Android, через файл `.tgz`

1. Завантажте `flipper-z-f7-update-(version).tgz` зі сторінки релізу.
2. У застосунку Flipper натисніть **Update channel** → **Custom** і виберіть завантажений файл.
3. Натисніть **Update** і зачекайте.

### Android, через посилання вебоновлювача

1. На сторінці релізу натисніть **Install via Web Updater**.
2. Коли Android запитає, чим це відкрити, виберіть застосунок **Flipper**.
3. Продовжте встановлення й зачекайте.

Оновлення через Bluetooth може тривати близько 10 хвилин. Інші способи:
[Встановлення Unleashed](/ua/start/install).

### Якщо оновлення не вдалося

- Перевірте, що Flipper увімкнений і досі підключений через Bluetooth.
- Перезавантажте Flipper (<kbd>←</kbd> + <kbd>Back</kbd>) і запустіть оновлення знову.
- Якщо помилка повторюється, внутрішня пам'ять може бути заповнена або пошкоджена: встановлюйте через
  [qFlipper](/ua/mobile/qflipper) або [вебінсталятор](/ua/mobile/web-tools#unleashed-web-installer), див.
  [Відновлення](/ua/start/recovery).

## Резервне копіювання ключів

1. На вкладці пристрою натисніть **Options → Backup Keys**.
2. Виберіть, куди зберегти або куди надіслати `.zip` із вашими ключами, картками й пультами.

Для відновлення розпакуйте архів і завантажте файли через [qFlipper](/ua/mobile/qflipper). Щоб зробити повну
резервну копію SD-картки, завантажте всю картку через **File manager** у qFlipper.

## Проблеми з підключенням {#connection-problems}

**Після встановлення Unleashed або перейменування Flipper застосунок не підключається:**

1. У застосунку натисніть **Forget flipper**.
2. У налаштуваннях Bluetooth смартфона знайдіть Flipper, відкрийте його параметри й виберіть **Forget device**.
3. На Flipper: `Settings → Bluetooth → Unpair All Devices` і підтвердьте через **Unpair**.
4. Переконайтеся, що Bluetooth на Flipper у стані ON, і виконайте спарювання з застосунку знову.

**Flipper не знаходиться:** перевірте, що Bluetooth увімкнений на обох пристроях, відключіть Flipper від інших
пристроїв (наприклад, від хоста [Bluetooth-пульта](/ua/apps/controllers)), оновіть застосунок і прошивку,
перезавантажте Flipper.

**Синхронізація не завершується:** видаліть спарювання й створіть його знову, перезапустіть обидва пристрої та
спробуйте `Settings → System → Sleep Method → Legacy` на Flipper.

## Повідомлення про помилки застосунку

Помилки в офіційному застосунку: **Options → Report Bug**, заповніть заголовок і кроки для відтворення, залиште
прикріплені логи, натисніть **Submit**, а за бажанням опублікуйте ID issue на
[forum.flipperzero.one](https://forum.flipperzero.one/) (розділ Mobile App). Щоб зібрати логи Flipper для звіту:
встановіть `Settings → System → Log Level` у **Debug**, підключіться через USB, відкрийте послідовний термінал на
швидкості **230400** бод (або [lab.flipper.net/cli](https://lab.flipper.net/cli)), виконайте `info device`, а потім
`log`, відтворіть помилку й приберіть рядки `hardware.uid` і `hardware.name` перед публікацією.

## Пов'язані сторінки

- [qFlipper](/ua/mobile/qflipper)
- [Супутній застосунок qUnleashed](/ua/mobile/qunleashed-app)
- [Встановлення Unleashed](/ua/start/install)
