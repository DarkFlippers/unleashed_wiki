---
title: "JavaScript: vgm"
sidebarTitle: "JS: vgm"
order: 460
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [unleashed-src]
---
# Модуль Video Game Module

Додаток Unleashed, у стоковій прошивці його немає. Читає датчик руху (IMU ICM42688P) усередині [Video Game Module](/ua/gpio/video-game-module) і повідомляє, як нахилено Flipper.

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");
```

Готового прикладу для цього модуля в прошивці немає.

Кути — у градусах:

- **pitch** — нахил уперед і назад;
- **roll** — нахил ліворуч і праворуч;
- **yaw** — поворот у площині стола.

Без підключеного модуля `require("vgm")` все одно спрацює, але кожен метод поверне `undefined`. Перевіряйте це, а не розраховуйте, що залізо на місці.

Драйвер IMU узято з [ігрового рушія Flipper](https://github.com/flipperdevices/flipperzero-game-engine).

## Методи

### getPitch()
- **Повертає:** число або `undefined`, якщо модуль не підключено.

### getRoll()
- **Повертає:** число або `undefined`, якщо модуль не підключено.

### getYaw()
- **Повертає:** число або `undefined`, якщо модуль не підключено.

### deltaYaw()
Блокує виконання, доки yaw не зміниться на `angle` градусів; опитує датчик 10 разів на секунду.

- **Параметри:**
  - `angle` — на скільки градусів має змінитися кут;
  - `timeout` (необов’язковий) — скільки мілісекунд чекати. Типово 3000.
- **Повертає:** зміну в градусах зі знаком: від’ємну для одного напрямку, додатну для іншого. `0`, якщо кут не досягнуто до кінця очікування, `undefined`, якщо модуль не підключено.

## Приклад

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");

if (vgm.getPitch() === undefined) {
    print("No Video Game Module attached");
} else {
    for (let i = 0; i < 10; i++) {
        print("pitch", vgm.getPitch(), "roll", vgm.getRoll(), "yaw", vgm.getYaw());
        delay(200);
    }

    print("Turn the Flipper 45 degrees...");
    let turned = vgm.deltaYaw(45, 5000);
    if (turned === 0) {
        print("Nothing happened");
    } else {
        print("Turned by", turned);
    }
}
```

## Пов’язані сторінки

- [Video Game Module](/ua/gpio/video-game-module)
- [Огляд JavaScript](/ua/dev/js-about)
