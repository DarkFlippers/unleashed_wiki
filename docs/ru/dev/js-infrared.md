---
title: "JavaScript: infrared"
sidebarTitle: "JS: infrared"
order: 410
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_infrared]
sources: [unleashed-src]
---
# Модуль Infrared

Дополнение Unleashed, в стоковой прошивке его нет. Отправляет ИК-сигналы из скрипта: по имени протокола или сырым списком таймингов. Приёма здесь нет — сигнал сначала нужно записать приложением Infrared.

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");
```

Имя фичи — `infrared-send`, имя модуля — `infrared`.

Пример: `/ext/apps/Scripts/js_examples/infrared-send.js`.

## Методы

### sendSignal()
Отправляет сигнал по протоколу, который знает прошивка.

- **Параметры:**
  - `protocol`: `"NEC"`, `"NECext"`, `"NEC42"`, `"NEC42ext"`, `"Samsung32"`, `"RC6"`, `"RC5"`, `"RC5X"`, `"SIRC"`, `"SIRC15"`, `"SIRC20"`, `"Kaseikyo"` или `"RCA"`;
  - `address` — число;
  - `command` — число;
  - `options` (необязательный): `{ repeat?: boolean, times?: number }`. `repeat` помечает сигнал как повторный кадр, `times` — сколько раз отправить (по умолчанию 1).

```js
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
```

В `.ir`-файлах адрес и команда записаны как hex little-endian, а числовой литерал в JS — big-endian. `A9 00 00 00` из файла здесь превращается в `0x000000A9`, так что байты нужно развернуть.

### sendRawSignal()
Отправляет сигнал таймингами вкл/выкл — для пультов, которые не подходят ни под один протокол.

- **Параметры:**
  - `timings` — массив чисел, длительности в микросекундах;
  - `startFromMark` (необязательный) — boolean: первое значение является импульсом, а не паузой. По умолчанию `true`;
  - `advancedSettings` (необязательный): `{ frequency: number, dutyCycle: number }`. Если объект передан, оба поля обязательны. Без него несущая — 38000 Гц со скважностью 0.33.

## Пример

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");

// Samsung TV, volume down
print("Sending Samsung32");
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
delay(1000);

// Three presses in a row
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b, { times: 3 });
delay(1000);

// Raw timings at 36 kHz
infrared.sendRawSignal([3298, 1571, 442, 368, 442, 367], true, {
  frequency: 36000,
  dutyCycle: 0.33,
});
print("Done");
```

## См. также

- [Формат файлов Infrared](/ru/infrared/file-format) — откуда брать адрес и команду
- [Поддерживаемые ИК-протоколы](/ru/infrared/protocols)
- [Обзор JavaScript](/ru/dev/js-about)
