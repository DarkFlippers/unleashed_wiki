---
title: "JavaScript: spi"
sidebarTitle: "JS: spi"
order: 450
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_spi.c]
sources: [unleashed-src]
---
# Modul SPI

Dodatak specifičan za Unleashed, nije prisutan u tvorničkom firmveru. Komunicira sa SPI čipovima na vanjskoj sabirnici — flash memorijom, radijskim modulima, zaslonima.

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");
```

Ožičenje na [GPIO priključnici](/hr/gpio/pinout): **MOSI = pin 2 (PA7)**, **MISO = pin 3 (PA6)**, **CS = pin 4 (PA4)**, **SCK = pin 5 (PB3)**, 3,3 V na pinu 9, GND na pinu 8. Chip select (CS) kontrolira firmver, ne morate ga sami prebacivati.

Primjer skripte: `/ext/apps/Scripts/js_examples/spi.js`.

## Metode

### acquire()
Zauzima sabirnicu i drži CS na niskoj razini (low) do poziva `release()`. Koristite je kada više prijenosa uređaju mora izgledati kao jedna transakcija — naredba, pa odgovor. Bez nje svaki poziv samostalno zauzima i oslobađa sabirnicu, što između poziva podiže CS.

### release()
Oslobađa sabirnicu.

### write()
- **Parametri:** `data` (`number[]` s vrijednostima 0–255, ili `ArrayBuffer`/`Uint8Array`), `timeout` (neobavezno, milisekunde, zadano 1).
- **Vraća:** boolean.

### read()
- **Parametri:** `length` (broj bajtova, najmanje 1), `timeout` (neobavezno, ms, zadano 1).
- **Vraća:** `ArrayBuffer`, ili `undefined` u slučaju neuspjeha. Omotajte ga u `Uint8Array(buf)` za indeksiranje bajtova.

### writeRead()
Full-duplex prijenos: šalje međuspremnik i istodobno čita točno onoliko bajtova koliko je poslano.

- **Parametri:** `data` (`number[]` ili `ArrayBuffer`), `timeout` (neobavezno, ms, zadano 1).
- **Vraća:** `ArrayBuffer` iste duljine kao `data`, ili `undefined` u slučaju neuspjeha.

## Primjer

Čitanje JEDEC ID-a flash čipa W25Q32:

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");

spi.acquire();
spi.write([0x9F]);          // naredba: čitanje JEDEC ID-a
let data = Uint8Array(spi.read(3));
spi.release();

print("Manufacturer: 0x" + data[0].toString(16));
print("Memory type:  0x" + data[1].toString(16));
print("Capacity:     0x" + data[2].toString(16));

if (data[0] === 0xEF) {
    print("Winbond device");
}
```

## Povezano

- [Raspored GPIO pinova](/hr/gpio/pinout)
- [Modul I2C](/hr/dev/js-i2c)
- [Pregled JavaScripta](/hr/dev/js-about)
