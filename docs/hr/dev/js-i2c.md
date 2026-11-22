---
title: "JavaScript: i2c"
sidebarTitle: "JS: i2c"
order: 440
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_i2c.c]
sources: [unleashed-src]
---
# Modul I2C

Dodatak firmvera Unleashed, nije prisutan u izvornom firmveru. Komunicira s I2C čipovima na vanjskoj sabirnici: senzorima, EEPROM memorijama, zaslonima.

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");
```

Ožičenje na [GPIO priključku](/hr/gpio/pinout): **SDA = pin 15 (PC1)**, **SCL = pin 16 (PC0)**, 3,3 V na pinu 9, GND na pinu 8. Sabirnica radi na 3,3 V — nemojte spajati 5 V uređaje.

Primjer skripte: `/ext/apps/Scripts/js_examples/i2c.js`.

Adrese su 8-bitne (7-bitna adresa pomaknuta ulijevo za jedan bit). Podatkovni list koji navodi `0x50` ovdje obično znači `0xA0`. Svaki poziv zauzima sabirnicu, obavlja prijenos i oslobađa je, tako da druga aplikacija može koristiti I2C između poziva.

## Metode

### isDeviceReady()
Provjerava odziv adrese.

- **Parametri:** `address` (broj), `timeout` (neobavezno, milisekunde, zadano 1).
- **Vraća:** boolean.

### write()
- **Parametri:** `address` (broj), `data` (`number[]` s vrijednostima 0–255, ili `ArrayBuffer`/`Uint8Array`), `timeout` (neobavezno, ms, zadano 1).
- **Vraća:** boolean — `true` ako je uređaj potvrdio prijem.

### read()
- **Parametri:** `address` (broj), `length` (broj bajtova, mora biti najmanje 1), `timeout` (neobavezno, ms, zadano 1).
- **Vraća:** `ArrayBuffer`, ili `undefined` ako prijenos nije uspio. Omotajte ga u `Uint8Array(buf)` za indeksiranje bajtova.

### writeRead()
Piše, a zatim čita bez oslobađanja sabirnice. Tako se čita registar: zapišite njegov broj, pročitajte vrijednost.

- **Parametri:** `address`, `writeData` (`number[]` ili `ArrayBuffer`), `readLength`, `timeout` (neobavezno, ms, zadano 1).
- **Vraća:** `ArrayBuffer`, ili `undefined` u slučaju neuspjeha.

## Primjer

Pretražite sabirnicu, zatim pročitajte tri bajta iz EEPROM memorije 24C32N:

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
    // upiši 3 bajta počevši od EEPROM adrese 0x0000
    i2c.write(addr, [0x00, 0x00, 0x41, 0x42, 0x43]);
    delay(10);
    // pročitaj 3 bajta natrag s adrese 0x0000
    let data = Uint8Array(i2c.writeRead(addr, [0x00, 0x00], 3, 100));
    for (let i = 0; i < data.length; i++) {
        print("data[" + i.toString() + "] = " + data[i].toString(16));
    }
}
```

## Povezano

- [GPIO raspored pinova](/hr/gpio/pinout)
- [Modul GPIO](/hr/dev/js-gpio)
- [Modul SPI](/hr/dev/js-spi)
