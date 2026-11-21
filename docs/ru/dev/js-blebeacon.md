---
title: "JavaScript: blebeacon"
sidebarTitle: "JS: blebeacon"
order: 420
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_blebeacon.c]
sources: [unleashed-src]
---
# Модуль BLE beacon

Дополнение Unleashed, в стоковой прошивке его нет. Рассылает собственный Bluetooth LE advertisement: свой MAC-адрес, своя полезная нагрузка. Это тот же «extra beacon», который прошивка использует для фоновой рассылки, поэтому он работает параллельно с обычным соединением Bluetooth.

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");
```

Пример: `/ext/apps/Scripts/js_examples/blebeacon.js`.

При выходе из скрипта модуль возвращает ту конфигурацию, данные и состояние маяка, которые были до запуска, — если вы не попросили обратного через `keepAlive(true)`.

## Методы

### isActive()
- **Возвращает:** boolean — идёт ли рассылка прямо сейчас. Проверяйте это в начале: маяк, оставленный предыдущим скриптом, продолжает работать.

### setConfig()
Задаёт параметры рассылки.

- **Параметры:**
  - `mac` — `Uint8Array` ровно из 6 байт. Любая другая длина даёт ошибку `Wrong MAC address`;
  - `power` (необязательный) — мощность передатчика по шкале GapAdvPowerLevel, от `0x00` (-40 дБм) до `0x1F` (+6 дБм). По умолчанию 0 дБм, значения вне диапазона обрезаются;
  - `minInterval` (необязательный) — минимальный интервал рассылки в мс. По умолчанию 50, значения меньше 20 поднимаются до 20, максимум — 255;
  - `maxInterval` (необязательный) — максимальный интервал в мс. По умолчанию 150, не бывает меньше `minInterval`, максимум — 255.

### setData()
- **Параметры:** `data` — `Uint8Array` с полезной нагрузкой. Предел железа — 31 байт.

### start()
Запускает рассылку.

### stop()
Останавливает рассылку.

### keepAlive()
- **Параметры:** `keep` — boolean. При `true` маяк продолжает работать после выхода из скрипта и ничего не восстанавливается. По умолчанию `false`.

## Пример

Рассылаем короткий пакет пять секунд:

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");

if (blebeacon.isActive()) {
    blebeacon.stop();
}
blebeacon.keepAlive(false);

blebeacon.setConfig(Uint8Array([0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x01]), 0x1F, 50, 150);
blebeacon.setData(Uint8Array([0x02, 0x01, 0x06, 0x03, 0xFF, 0xAB, 0xCD]));

blebeacon.start();
print("Advertising");
delay(5000);
blebeacon.stop();
print("Stopped");
```

## См. также

- [Обзор JavaScript](/ru/dev/js-about)
- [Типы данных](/ru/dev/js-data-types) — как в mJS устроен `Uint8Array`
