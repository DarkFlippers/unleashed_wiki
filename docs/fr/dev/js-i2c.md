---
title: "JavaScript : i2c"
sidebarTitle: "JS : i2c"
order: 440
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_i2c.c]
sources: [unleashed-src]
---
# Module I2C

Un extra Unleashed, absent du firmware d'origine. Il dialogue avec les puces I2C du bus externe : capteurs, EEPROM, écrans.

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");
```

Câblage sur le [connecteur GPIO](/fr/gpio/pinout) : **SDA = broche 15 (PC1)**, **SCL = broche 16 (PC0)**, 3,3 V sur la broche 9, GND sur la broche 8. Le bus est en 3,3 V — ne branchez pas d'appareils 5 V.

Script d'exemple : `/ext/apps/Scripts/js_examples/i2c.js`.

Les adresses sont sur 8 bits (l'adresse 7 bits décalée d'un bit vers la gauche). Une fiche technique qui indique `0x50` veut en général dire `0xA0` ici. Chaque appel prend le bus, fait son transfert et le relâche, une autre application peut donc utiliser l'I2C entre deux appels.

## Méthodes

### isDeviceReady()
Teste une adresse.

- **Paramètres :** `address` (nombre), `timeout` (facultatif, en millisecondes, 1 par défaut).
- **Renvoie :** un booléen.

### write()
- **Paramètres :** `address` (nombre), `data` (`number[]` de valeurs 0–255, ou un `ArrayBuffer`/`Uint8Array`), `timeout` (facultatif, ms, 1 par défaut).
- **Renvoie :** un booléen — `true` si l'appareil a acquitté.

### read()
- **Paramètres :** `address` (nombre), `length` (nombre d'octets, au moins 1), `timeout` (facultatif, ms, 1 par défaut).
- **Renvoie :** un `ArrayBuffer`, ou `undefined` si le transfert a échoué. Enveloppez-le dans `Uint8Array(buf)` pour accéder aux octets.

### writeRead()
Écrit, puis lit sans relâcher le bus. C'est ainsi qu'on lit un registre : on écrit son numéro, on lit la valeur.

- **Paramètres :** `address`, `writeData` (`number[]` ou `ArrayBuffer`), `readLength`, `timeout` (facultatif, ms, 1 par défaut).
- **Renvoie :** un `ArrayBuffer`, ou `undefined` en cas d'échec.

## Exemple

Scanner le bus, puis lire trois octets dans une EEPROM 24C32N :

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");

let addr = -1;
for (let a = 0; a !== 0xff; a++) {
    if (i2c.isDeviceReady(a, 5)) {
        addr = a;
        break;
    }
}

if (addr === -1) {
    print("No I2C device found");
} else {
    print("Device at 0x" + addr.toString(16));
    // write 3 bytes starting at EEPROM address 0x0000
    i2c.write(addr, [0x00, 0x00, 0x41, 0x42, 0x43]);
    delay(10);
    // read 3 bytes back from address 0x0000
    let data = Uint8Array(i2c.writeRead(addr, [0x00, 0x00], 3, 100));
    for (let i = 0; i < data.length; i++) {
        print("data[" + i.toString() + "] = " + data[i].toString(16));
    }
}
```

## Pages liées

- [Brochage GPIO](/fr/gpio/pinout)
- [Module GPIO](/fr/dev/js-gpio)
- [Module SPI](/fr/dev/js-spi)
