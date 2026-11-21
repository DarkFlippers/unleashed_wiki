---
title: Юніт-тести
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UnitTests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests]
sources: [unleashed-docs, unleashed-src]
---
# Юніт-тести

Юніт-тести подають у код відомі вхідні дані й перевіряють, що результат правильний. Без них важко отримати
надійний код без помилок.

У прошивці є окремий застосунок — **`unit_tests`** (`applications/debug/unit_tests`), який виконується **просто
на Flipper**, тож тести працюють зі справжньою апаратною частиною й виключають розбіжності, пов’язані з
платформою.

Якщо ви вносите зміни до прошивки, за можливості додавайте до нових функцій юніт-тести, а наявні — прогоняйте,
щоб переконатися, що ваша зміна не спричинила регресій.

## Запуск тестів

1. **Зберіть прошивку з тестовим набором застосунків:**

   ```sh
   ./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests updater_package
   ```

   ::: warning `DEBUG=0` є обов’язковим
   Типове значення у `fbt_options.py` — `DEBUG=1`, а debug-образ уже не вміщується нижче ділянки флешу, яку
   займає радіостек: пакування припиняється з повідомленням
   `Firmware image overlaps C2 region and is not programmable!`. Станом на API 88.23 debug-образ для цього набору
   застосунків завеликий приблизно на 7 КБ (для типового набору — на 10 КБ), тож урізання тестів не допоможе.
   (`COMPACT=1` і так типове значення; він вказаний явно, щоб команда виглядала як решта.)

   Пам’ятайте, що з `DEBUG=0` викликів `furi_assert()` у скомпільованому коді не залишається, тож перевірки в
   коді, який тестується, не спрацюють. На `furi_check()` і твердження minunit це не впливає.
   :::

   Набір застосунків `unit_tests` містить: `basic_services`, `updater_app`, `radio_device_cc1101_ext`,
   `unit_tests`, `infrared`, `archive`.

2. **Прошийте прошивку разом із ресурсами для картки microSD** (`build/latest/resources`) — наприклад, встановіть
   створений `.tgz` із папки `dist/` через qFlipper або скористайтеся командою
   `./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests flash_usb_full`. Ресурси тестів обов’язково мають
   опинитися на картці microSD.
3. **Відкрийте сеанс [CLI](/ua/dev/cli)** і виконайте:

   ```
   unit_tests
   ```

**Очікуваний результат:** набори тестів виконуються один за одним, а потім з’являється звіт такого вигляду:

```
Tests run: …, asserts: …
Failed tests: 0
Consumed: … ms
Leaked: …
```

Якщо ви бачите `Cannot open /ext/apps_data/unit_tests/plugins - are the SD card resources deployed?`, значить
ресурси для картки microSD не встановлені — повторіть крок 2 разом із ресурсами.

Щоб запустити **один** тест і пропустити решту, передайте його ім’я:

```
unit_tests test_infrared
```

Інші набори будуть пропущені (`Skipping …`); на хибне ім’я ви отримаєте `No suite named …`. Імена тестів
збігаються з ідентифікаторами застосунків (`test_furi`, `test_storage`, `test_subghz`, `test_infrared`,
`test_nfc`, `test_lfrfid`, …), оголошеними у файлі
[`applications/debug/unit_tests/application.fam`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/application.fam).

::: info
Це особлива збірка прошивки без звичних застосунків. Коли закінчите, встановіть назад нормальну збірку.
:::

## Додавання юніт-тестів

### Точка входу

Усі тести запускаються з «материнського» застосунку `unit_tests`. Сам код тестів оформлений як застосунок типу
`PLUGIN` у підкаталозі `tests/` усередині `unit_tests` і згадується у спільному `application.fam`. Скопіюйте
структуру наявного тесту.

### Ресурси тестів

Деяким тестам потрібні зовнішні дані («assets»). Вони лежать у
[`applications/debug/unit_tests/resources/unit_tests`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests),
кожен у власному підкаталозі. Ресурси можуть бути будь-якого типу: простий текст, Flipper Format (FFF), двійкові
дані тощо.

### Приклад: інфрачервоні протоколи

Кожен інфрачервоний протокол має набір юніт-тестів, тому додавайте їх разом із новим протоколом:

1. Створіть `test_<your_protocol_name>.irtest` у
   [каталозі ресурсів infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests/infrared).
2. Наповніть його тестовими даними (див. нижче).
3. Додайте код тесту до
   [`infrared_test.c`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/tests/infrared/infrared_test.c).
4. Зберіть і встановіть прошивку з ресурсами, потім запустіть тести й переконайтеся, що вони проходять.

#### Формат тестових даних

Кожен інфрачервоний тест має три секції:

| Секція | Що робить |
|---|---|
| `decoder` | Приймає «сирий» сигнал, видає декодовані повідомлення |
| `encoder` | Приймає декодовані повідомлення, видає «сирий» сигнал |
| `encoder_decoder` | Кодує декодовані повідомлення в «сирий» сигнал, а потім декодує його знову |

Файли `.irtest` — це звичайні [файли `.ir`](/ua/infrared/file-format) з кількома доповненнями:

- вхідні сигнали декодера називаються `decoder_input_N` (N — порядковий номер тесту), а очікуваний вивід —
  `decoder_expected_N`;
- для тестів кодера ці два поля міняються місцями;
- декодовані дані — це **масив**, бо один «сирий» сигнал може декодуватися в кілька повідомлень; одне
  повідомлення — це масив розміру 1.

Як приклади синтаксису беріть наявні файли `.irtest`.

#### Запис «сирих» сигналів

Відкрийте сеанс CLI і виконайте:

```
ir rx raw
```

Наведіть пульт на Flipper і натискайте кнопки. «Сирі» дані виводяться у форматі, готовому до використання.

## Пов’язані сторінки

- [Інтеграційне тестування](/ua/dev/testing)
- [Flipper Build Tool (fbt)](/ua/dev/fbt)
- [Командний рядок](/ua/dev/cli)
