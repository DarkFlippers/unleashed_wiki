---
title: "JavaScript: blebeacon"
sidebarTitle: "JS: blebeacon"
order: 420
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_blebeacon.c]
sources: [unleashed-src]
---
# Модуль BLE beacon

Додаток Unleashed, у стоковій прошивці його немає. Транслює власний рекламний пакет Bluetooth LE — зі своєю MAC-адресою та своїм вмістом. Це той самий «extra beacon», яким прошивка користується для фонової трансляції, тому він працює паралельно зі звичайним Bluetooth-з’єднанням.

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");
```

Приклад скрипта: `/ext/apps/Scripts/js_examples/blebeacon.js`.

Коли скрипт завершується, модуль повертає ту конфігурацію маяка, дані й стан, які були до запуску. Виняток — якщо ви попросили цього не робити через `keepAlive(true)`.

## Методи

### isActive()
- **Повертає:** boolean — чи маяк транслює просто зараз. Перевіряйте це на старті: маяк, залишений попереднім скриптом, усе ще активний.

### setConfig()
Задає параметри трансляції.

- **Параметри:**
  - `mac` — `Uint8Array` рівно з 6 байтів. Будь-що інше дає помилку `Wrong MAC address`;
  - `power` (необов’язковий) — потужність передавача за шкалою GapAdvPowerLevel, від `0x00` (-40 дБм) до `0x1F` (+6 дБм). Типово 0 дБм, значення поза діапазоном обрізаються до меж;
  - `minInterval` (необов’язковий) — мінімальний інтервал трансляції в мс. Типово 50, значення менші за 20 піднімаються до 20, максимум — 255;
  - `maxInterval` (необов’язковий) — максимальний інтервал у мс. Типово 150, ніколи не менший за `minInterval`, максимум — 255.

### setData()
- **Параметри:** `data` — `Uint8Array` із вмістом рекламного пакета. Апаратна межа — 31 байт.

### start()
Починає трансляцію.

### stop()
Зупиняє трансляцію.

### keepAlive()
- **Параметри:** `keep` — boolean. Зі значенням `true` маяк продовжує транслювати після завершення скрипта, і нічого не відновлюється. Типово `false`.

## Приклад

Транслюємо короткий пакет протягом п’яти секунд:

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

## Пов’язані сторінки

- [Огляд JavaScript](/ua/dev/js-about)
- [Типи даних](/ua/dev/js-data-types) — як влаштований `Uint8Array` у mJS
