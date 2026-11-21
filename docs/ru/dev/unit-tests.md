---
title: Юнит-тесты
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UnitTests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests]
sources: [unleashed-docs, unleashed-src]
---
# Юнит-тесты

Юнит-тесты подают на код известные входные данные и проверяют, что результат правильный.

В прошивке есть отдельное приложение **`unit_tests`** (`applications/debug/unit_tests`), которое запускается **прямо
на Флиппере** — тесты работают на реальном железе, и платформенные различия исключены.

Если вы контрибьютите в прошивку, по возможности прикладывайте юнит-тесты к новым функциям и прогоняйте
существующие, чтобы убедиться, что изменения ничего не сломали.

## Запуск тестов

1. **Соберите прошивку с набором приложений для тестов:**

   ```sh
   ./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests updater_package
   ```

   ::: warning `DEBUG=0` обязателен
   В `fbt_options.py` по умолчанию `DEBUG=1`, а отладочный образ больше не помещается ниже области флеш-памяти
   радиостека — упаковка останавливается с ошибкой `Firmware image overlaps C2 region and is not programmable!`. На
   API 88.23 отладочный образ примерно на 7 КБ больше допустимого для этого набора (на 10 КБ — для стандартного),
   так что урезание набора тестов не поможет. (`COMPACT=1` и так по умолчанию; он указан для единообразия с другими
   командами.)

   Учтите, что с `DEBUG=0` из кода убираются `furi_assert()`, поэтому assert-ы в тестируемом коде срабатывать не
   будут. `furi_check()` и assert-ы minunit работают как обычно.
   :::

   Набор `unit_tests` включает: `basic_services`, `updater_app`, `radio_device_cc1101_ext`, `unit_tests`,
   `infrared`, `archive`.

2. **Прошейте прошивку вместе с ресурсами для SD-карты** (`build/latest/resources`) — например, установите
   собранный `.tgz` из `dist/` через qFlipper или выполните
   `./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests flash_usb_full`. Тестовые ассеты должны попасть на SD-карту.
3. **Откройте сессию [CLI](/ru/dev/cli)** и выполните:

   ```
   unit_tests
   ```

**Ожидаемый результат:** наборы тестов выполняются по очереди, затем выводится отчёт вида:

```
Tests run: …, asserts: …
Failed tests: 0
Consumed: … ms
Leaked: …
```

Если видите `Cannot open /ext/apps_data/unit_tests/plugins - are the SD card resources deployed?`, ресурсы на
SD-карту не установлены — повторите шаг 2 с ресурсами.

Чтобы запустить **один** тест и пропустить остальные, передайте его имя:

```
unit_tests test_infrared
```

Остальные наборы пропускаются (`Skipping …`); неверное имя даёт `No suite named …`. Имена тестов совпадают с ID
приложений (`test_furi`, `test_storage`, `test_subghz`, `test_infrared`, `test_nfc`, `test_lfrfid`, …), описанных в
[`applications/debug/unit_tests/application.fam`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/application.fam).

::: info
Это специальная сборка прошивки без обычных приложений. Когда закончите, установите обычную сборку обратно.
:::

## Добавление юнит-тестов

### Точка входа

Все тесты запускаются из «материнского» приложения `unit_tests`. Код каждого теста оформлен как приложение типа
`PLUGIN` в подпапке `tests/` внутри `unit_tests` и подключён в общем `application.fam`. Скопируйте структуру
существующего теста.

### Тестовые ассеты

Некоторым тестам нужны внешние данные («ассеты»). Они лежат в
[`applications/debug/unit_tests/resources/unit_tests`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests),
каждый в своей подпапке. Ассеты могут быть любого типа: обычный текст, Flipper Format (FFF), бинарные данные и т. д.

### Пример: ИК-протоколы

У каждого ИК-протокола есть набор юнит-тестов, поэтому при добавлении нового протокола добавьте и тест:

1. Создайте `test_<your_protocol_name>.irtest` в
   [папке ассетов infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests/infrared).
2. Заполните его тестовыми данными (см. ниже).
3. Добавьте код теста в
   [`infrared_test.c`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/tests/infrared/infrared_test.c).
4. Соберите и установите прошивку с ресурсами, запустите тесты и убедитесь, что они проходят.

#### Формат тестовых данных

У каждого ИК-теста три секции:

| Секция | Что делает |
|---|---|
| `decoder` | Принимает сырой сигнал, выдаёт декодированные сообщения |
| `encoder` | Принимает декодированные сообщения, выдаёт сырой сигнал |
| `encoder_decoder` | Кодирует сообщения в сырой сигнал и снова декодирует |

Файлы `.irtest` — это обычные [файлы `.ir`](/ru/infrared/file-format) с несколькими дополнениями:

- входные сигналы декодера называются `decoder_input_N` (N — номер тестовой последовательности), ожидаемый
  результат — `decoder_expected_N`;
- в тестах энкодера они меняются местами;
- декодированные данные — это **массив**, поскольку один сырой сигнал может декодироваться в несколько сообщений;
  одно сообщение — массив размером 1.

Синтаксис смотрите в существующих файлах `.irtest`.

#### Запись сырых сигналов

Откройте сессию CLI и выполните:

```
ir rx raw
```

Направьте пульт на Флиппер и нажимайте кнопки. Сырые данные выводятся в готовом к использованию виде.

## Связанные страницы

- [Интеграционное тестирование](/ru/dev/testing)
- [Flipper Build Tool (fbt)](/ru/dev/fbt)
- [Командная строка (CLI)](/ru/dev/cli)
