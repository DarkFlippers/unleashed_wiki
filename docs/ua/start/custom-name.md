---
title: Власне ім’я Фліппера
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/CustomFlipperName.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/namechanger, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-docs, unleashed-src]
---
# Власне ім’я Фліппера

Кожен Фліппер має заводське ім’я. Воно показується в Passport, у розділі **About**, у списках Bluetooth-пристроїв
і в qFlipper. Unleashed дає змогу замінити його на власне.

::: tip Unleashed
У стоковій прошивці немає пункту меню для перейменування пристрою. В Unleashed він є —
**Settings → Desktop → Change Flipper Name**, і ім’я **зберігається після оновлень прошивки**, бо лежить на
картці microSD.
:::

## Як задати ім’я

1. Відкрийте **Main Menu → Settings → Desktop → Change Flipper Name**.
2. Введіть нове ім’я. У заголовку клавіатури написано `Leave empty for default`.
   - **від 2 до 8 символів**;
   - **лише латинські літери та цифри** (`A–Z`, `a–z`, `0–9`). На інші символи з’явиться
     *«Please only enter letters and numbers!»*.
3. Виберіть **Save**.
4. З’явиться повідомлення **`Name is set!`** / *«Your Flipper will be restarted on exit.»*.
5. Вийдіть із Settings кнопкою <kbd>BACK</kbd>. Фліппер **перезавантажиться автоматично**.
6. Після перезавантаження нове ім’я буде в Passport, у **Settings → About** і в Bluetooth.

## Повернення заводського імені

1. Відкрийте **Settings → Desktop → Change Flipper Name**.
2. Видаліть усі символи й залиште поле **порожнім**.
3. Виберіть **Save** і вийдіть із Settings. Фліппер перезавантажиться з початковим іменем.

## Як це працює

- Ім’я зберігається у файл **`/ext/dolphin/name.settings`** на картці:
  ```text
  Filetype: Flipper Name File
  Version: 1
  Name: MyFlip
  ```
- Під час завантаження служба `namechanger` чекає на картку, читає цей файл і застосовує ім’я, якщо воно коректне:
  правильний заголовок і версія, 2–8 символів, лише літери та цифри. Після цього служба перезапускає USB-serial
  і Bluetooth-профілі, щоб вони використовували нове ім’я.
- Збереження порожнього імені видаляє файл.
- Служба працює лише під час звичайного завантаження — не в оновлювачі й не в DFU.

Оскільки ім’я лежить на картці, воно залишається після оновлень. Воно зникне, якщо відформатувати чи замінити картку
або видалити файл.

## Якщо щось не працює

| Проблема | Що зробити |
|---|---|
| Ім’я не змінилося | Ви вийшли із Settings (ім’я застосовується під час перезавантаження)? Картка вставлена? Ім’я має 2–8 літер або цифр? Ім’я з одного символу зберігається, але під час завантаження не застосовується |
| Мобільний застосунок більше не підключається | Змінилося ім’я в Bluetooth. Видаліть Фліппер зі списку в застосунку **та** в налаштуваннях Bluetooth телефона, виконайте на Фліппері **Settings → Bluetooth → Unpair All Devices** і спаруйте заново |
| Файл з іменем, скопійований з іншого пристрою, ігнорується | Перевірте заголовок `Flipper Name File`, рядок `Version: 1` і вимоги до самого імені |
