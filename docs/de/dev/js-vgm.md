---
title: "JavaScript: vgm"
sidebarTitle: "JS: vgm"
order: 460
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [unleashed-src]
---
# Video Game Module

Ein Unleashed-Extra, in der Stock-Firmware gibt es das nicht. Es liest den Bewegungssensor (IMU ICM42688P) im [Video Game Module](/de/gpio/video-game-module) aus und meldet, wie der Flipper geneigt ist.

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");
```

Ein Beispielskript dafür gibt es in der Firmware nicht.

Die Winkel sind Grad:

- **pitch** — Nase rauf und runter;
- **roll** — Neigung nach links und rechts;
- **yaw** — Drehung flach auf dem Tisch.

Ohne angeschlossenes Modul funktioniert `require("vgm")` trotzdem, aber jede Methode gibt `undefined` zurück. Prüfe darauf, statt die Hardware vorauszusetzen.

Der IMU-Treiber stammt aus der [Flipper Game Engine](https://github.com/flipperdevices/flipperzero-game-engine).

## Methoden

### getPitch()
- **Rückgabe:** Zahl, oder `undefined`, wenn kein Modul angeschlossen ist.

### getRoll()
- **Rückgabe:** Zahl, oder `undefined`, wenn kein Modul angeschlossen ist.

### getYaw()
- **Rückgabe:** Zahl, oder `undefined`, wenn kein Modul angeschlossen ist.

### deltaYaw()
Blockiert, bis sich der Yaw-Winkel um `angle` Grad gedreht hat, und fragt dabei 10-mal pro Sekunde ab.

- **Parameter:**
  - `angle`: um wie viel Grad Änderung gewartet wird;
  - `timeout` (optional): Wartezeit in Millisekunden. Standard 3000.
- **Rückgabe:** die Änderung in Grad, mit Vorzeichen — negativ für die eine Richtung, positiv für die andere. `0`, wenn der Winkel vor Ablauf des Timeouts nicht erreicht wurde, `undefined`, wenn kein Modul angeschlossen ist.

## Beispiel

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

## Verwandte Themen

- [Video Game Module](/de/gpio/video-game-module)
- [JavaScript-Übersicht](/de/dev/js-about)
