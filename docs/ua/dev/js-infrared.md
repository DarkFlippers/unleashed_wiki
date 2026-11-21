---
title: "JavaScript: infrared"
sidebarTitle: "JS: infrared"
order: 410
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_infrared]
sources: [unleashed-src]
---
# Модуль Infrared

Додаток Unleashed, у стоковій прошивці його немає. Надсилає ІЧ-сигнали зі скрипта: за назвою протоколу або як сирий список таймингів. Прийому тут немає — щоб спочатку захопити сигнал, скористайтеся застосунком Infrared.

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");
```

Можливість називається `infrared-send`, модуль — `infrared`.

Приклад скрипта: `/ext/apps/Scripts/js_examples/infrared-send.js`.

## Методи

### sendSignal()
Надсилає сигнал протоколом, який знає прошивка.

- **Параметри:**
  - `protocol` — `"NEC"`, `"NECext"`, `"NEC42"`, `"NEC42ext"`, `"Samsung32"`, `"RC6"`, `"RC5"`, `"RC5X"`, `"SIRC"`, `"SIRC15"`, `"SIRC20"`, `"Kaseikyo"` або `"RCA"`;
  - `address` — число;
  - `command` — число;
  - `options` (необов’язковий) — `{ repeat?: boolean, times?: number }`. `repeat` позначає сигнал як повторний пакет, `times` — скільки разів його надіслати (типово 1).

```js
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
```

У файлах `.ir` адреса й команда зберігаються як hex у порядку little-endian, а числовий літерал JS — big-endian. `A9 00 00 00` у файлі — це `0x000000A9` тут, тож перед вставлянням переверніть байти.

### sendRawSignal()
Надсилає сигнал його таймингами «увімк./вимк.» — для пультів, яких не покриває жоден протокол.

- **Параметри:**
  - `timings` — масив чисел, тривалості в мікросекундах;
  - `startFromMark` (необов’язковий) — boolean: чи є перше значення імпульсом, а не паузою. Типово `true`;
  - `advancedSettings` (необов’язковий) — `{ frequency: number, dutyCycle: number }`. Якщо об’єкт задано, обидва поля обов’язкові. Без нього несуча — 38000 Гц зі шпаруватістю 0,33.

## Приклад

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

## Пов’язані сторінки

- [Формат ІЧ-файлів](/ua/infrared/file-format) — звідки брати адресу й команду
- [Підтримувані ІЧ-протоколи](/ua/infrared/protocols)
- [Огляд JavaScript](/ua/dev/js-about)
