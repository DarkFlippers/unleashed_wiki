---
title: "JavaScript: vgm"
sidebarTitle: "JS: vgm"
order: 460
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [unleashed-src]
---
# Video Game Module

Dodatak firmvera Unleashed koji nije prisutan u izvornom firmveru. Čita senzor pokreta (ICM42688P IMU) unutar modula [Video Game Module](/hr/gpio/video-game-module) i javlja kako je Flipper nagnut.

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");
```

Za ovaj modul u firmveru ne postoji ogledna skripta.

Kutovi su izraženi u stupnjevima:

- **pitch** — nagib naprijed i natrag;
- **roll** — nagib ulijevo i udesno;
- **yaw** — rotacija vodoravno na stolu.

Bez spojenog modula `require("vgm")` i dalje radi, ali svaka metoda vraća `undefined`. Provjerite tu vrijednost umjesto da pretpostavljate prisutnost hardvera.

Upravljački program za IMU preuzet je iz [Flipper game enginea](https://github.com/flipperdevices/flipperzero-game-engine).

## Metode

### getPitch()
- **Vraća:** broj ili `undefined` ako modul nije spojen.

### getRoll()
- **Vraća:** broj ili `undefined` ako modul nije spojen.

### getYaw()
- **Vraća:** broj ili `undefined` ako modul nije spojen.

### deltaYaw()
Blokira izvođenje dok se kut yaw ne promijeni za `angle` stupnjeva, očitavajući stanje 10 puta u sekundi.

- **Parametri:**
  - `angle`: za koliko stupnjeva promjene treba čekati;
  - `timeout` (neobavezno): vrijeme čekanja u milisekundama. Zadano 3000.
- **Vraća:** promjenu u stupnjevima, s predznakom — negativno za jedan smjer, pozitivno za drugi. `0` ako kut nije dosegnut prije isteka vremena, `undefined` ako modul nije spojen.

## Primjer

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

## Povezano

- [Video Game Module](/hr/gpio/video-game-module)
- [Pregled JavaScripta](/hr/dev/js-about)
