---
title: "JavaScript : spi"
sidebarTitle: "JS : spi"
order: 450
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_spi.c]
sources: [unleashed-src]
---
# Module SPI

Un extra Unleashed, absent du firmware d'origine. Il dialogue avec les puces SPI du bus externe : mémoires flash, modules radio, écrans.

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");
```

Câblage sur le [connecteur GPIO](/fr/gpio/pinout) : **MOSI = broche 2 (PA7)**, **MISO = broche 3 (PA6)**, **CS = broche 4 (PA4)**, **SCK = broche 5 (PB3)**, 3,3 V sur la broche 9, GND sur la broche 8. Le chip select est piloté par le firmware, vous n'avez pas à le manipuler.

Script d'exemple : `/ext/apps/Scripts/js_examples/spi.js`.

## Méthodes

### acquire()
Prend le bus et maintient CS à l'état bas jusqu'à `release()`. Utilisez-la quand plusieurs transferts doivent former une seule transaction pour l'appareil : la commande, puis la réponse. Sans elle, chaque appel prend et rend le bus tout seul, ce qui remonte CS entre les deux.

### release()
Libère le bus.

### write()
- **Paramètres :** `data` (`number[]` de valeurs 0–255, ou un `ArrayBuffer`/`Uint8Array`), `timeout` (facultatif, en millisecondes, 1 par défaut).
- **Renvoie :** un booléen.

### read()
- **Paramètres :** `length` (nombre d'octets, au moins 1), `timeout` (facultatif, ms, 1 par défaut).
- **Renvoie :** un `ArrayBuffer`, ou `undefined` en cas d'échec. Enveloppez-le dans `Uint8Array(buf)` pour accéder aux octets.

### writeRead()
Transfert full-duplex : envoie le tampon et relit exactement autant d'octets qu'il en a envoyés.

- **Paramètres :** `data` (`number[]` ou `ArrayBuffer`), `timeout` (facultatif, ms, 1 par défaut).
- **Renvoie :** un `ArrayBuffer` de la même longueur que `data`, ou `undefined` en cas d'échec.

## Exemple

Lire l'identifiant JEDEC d'une puce flash W25Q32 :

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");

spi.acquire();
spi.write([0x9F]);          // command: read JEDEC ID
let data = Uint8Array(spi.read(3));
spi.release();

print("Manufacturer: 0x" + data[0].toString(16));
print("Memory type:  0x" + data[1].toString(16));
print("Capacity:     0x" + data[2].toString(16));

if (data[0] === 0xEF) {
    print("Winbond device");
}
```

## Pages liées

- [Brochage GPIO](/fr/gpio/pinout)
- [Module I2C](/fr/dev/js-i2c)
- [JavaScript : présentation](/fr/dev/js-about)
