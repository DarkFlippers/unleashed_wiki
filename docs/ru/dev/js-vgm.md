---
title: "JavaScript: vgm"
sidebarTitle: "JS: vgm"
order: 460
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [unleashed-src]
---
# Модуль Video Game Module

Дополнение Unleashed, в стоковой прошивке его нет. Читает датчик движения (IMU ICM42688P) внутри [Video Game Module](/ru/gpio/video-game-module) и сообщает, как наклонён Флиппер.

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");
```

Готового примера для этого модуля в прошивке нет.

Углы — в градусах:

- **pitch** — наклон вперёд-назад;
- **roll** — наклон влево-вправо;
- **yaw** — поворот в плоскости стола.

Без подключённого модуля `require("vgm")` всё равно отработает, но все методы вернут `undefined`. Проверяйте это, а не рассчитывайте, что железо на месте.

Драйвер IMU взят из [игрового движка Flipper](https://github.com/flipperdevices/flipperzero-game-engine).

## Методы

### getPitch()
- **Возвращает:** число либо `undefined`, если модуль не подключён.

### getRoll()
- **Возвращает:** число либо `undefined`, если модуль не подключён.

### getYaw()
- **Возвращает:** число либо `undefined`, если модуль не подключён.

### deltaYaw()
Блокирует выполнение, пока yaw не изменится на `angle` градусов; опрашивает датчик 10 раз в секунду.

- **Параметры:**
  - `angle` — на сколько градусов ждать изменения;
  - `timeout` (необязательный) — сколько миллисекунд ждать. По умолчанию 3000.
- **Возвращает:** изменение в градусах, со знаком: минус в одну сторону, плюс в другую. `0`, если за отведённое время угол не набрался, и `undefined`, если модуль не подключён.

## Пример

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

## См. также

- [Video Game Module](/ru/gpio/video-game-module)
- [Обзор JavaScript](/ru/dev/js-about)
