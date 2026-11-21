---
title: "JavaScript: vgm"
sidebarTitle: "JS: vgm"
order: 460
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [unleashed-src]
---
# Video Game Module

Un extra di Unleashed, assente nel firmware di serie. Legge il sensore di movimento (IMU ICM42688P) dentro il [Video Game Module](/it/gpio/video-game-module) e riporta l'inclinazione del Flipper.

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");
```

Per questo modulo non c'è uno script di esempio nel firmware.

Gli angoli sono in gradi:

- **pitch** — muso su e giù;
- **roll** — inclinazione a sinistra e a destra;
- **yaw** — rotazione in piano sul tavolo.

Senza modulo collegato, `require("vgm")` funziona lo stesso, ma ogni metodo restituisce `undefined`. Controlla quel caso invece di dare per scontato l'hardware.

Il driver della IMU arriva dal [game engine del Flipper](https://github.com/flipperdevices/flipperzero-game-engine).

## Metodi

### getPitch()
- **Restituisce:** numero, oppure `undefined` se non c'è nessun modulo collegato.

### getRoll()
- **Restituisce:** numero, oppure `undefined` se non c'è nessun modulo collegato.

### getYaw()
- **Restituisce:** numero, oppure `undefined` se non c'è nessun modulo collegato.

### deltaYaw()
Blocca l'esecuzione finché lo yaw non è ruotato di `angle` gradi, campionando 10 volte al secondo.

- **Parametri:**
  - `angle`: di quanti gradi di variazione aspettare;
  - `timeout` (facoltativo): millisecondi di attesa. Predefinito 3000.
- **Restituisce:** la variazione in gradi, con segno: negativa in un verso, positiva nell'altro. `0` se l'angolo non è stato raggiunto entro il timeout, `undefined` se non c'è nessun modulo collegato.

## Esempio

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

## Pagine correlate

- [Video Game Module](/it/gpio/video-game-module)
- [Panoramica su JavaScript](/it/dev/js-about)
