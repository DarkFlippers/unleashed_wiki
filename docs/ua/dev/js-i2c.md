---
title: "JavaScript: i2c"
sidebarTitle: "JS: i2c"
order: 440
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_i2c.c]
sources: [unleashed-src]
---
# Модуль I2C

Додаток Unleashed, у стоковій прошивці його немає. Спілкується з мікросхемами I2C на зовнішній шині: датчиками, EEPROM, дисплеями.

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");
```

Підключення до [гребінки GPIO](/ua/gpio/pinout): **SDA — пін 15 (PC1)**, **SCL — пін 16 (PC0)**, 3,3 В на піні 9, GND на піні 8. Шина працює на 3,3 В — не підключайте 5-вольтові пристрої.

Приклад скрипта: `/ext/apps/Scripts/js_examples/i2c.js`.

Адреси тут 8-бітні (7-бітна адреса, зсунута вліво на один біт). Якщо в даташиті написано `0x50`, тут це зазвичай `0xA0`. Кожен виклик займає шину, виконує передачу й відпускає її, тож між викликами I2C може скористатися інший застосунок.

## Методи

### isDeviceReady()
Пінгує адресу.

- **Параметри:** `address` (число), `timeout` (необов’язковий, мілісекунди, типово 1).
- **Повертає:** boolean.

### write()
- **Параметри:** `address` (число), `data` (`number[]` зі значеннями 0–255 або `ArrayBuffer`/`Uint8Array`), `timeout` (необов’язковий, мс, типово 1).
- **Повертає:** boolean — `true`, якщо пристрій підтвердив прийом.

### read()
- **Параметри:** `address` (число), `length` (кількість байтів, щонайменше 1), `timeout` (необов’язковий, мс, типово 1).
- **Повертає:** `ArrayBuffer` або `undefined`, якщо передача не вдалася. Загорніть у `Uint8Array(buf)`, щоб звертатися до окремих байтів.

### writeRead()
Пише, а потім читає, не відпускаючи шину. Саме так читають регістр: надсилають його номер і одразу забирають значення.

- **Параметри:** `address`, `writeData` (`number[]` або `ArrayBuffer`), `readLength`, `timeout` (необов’язковий, мс, типово 1).
- **Повертає:** `ArrayBuffer` або `undefined` у разі невдачі.

## Приклад

Скануємо шину, потім читаємо три байти з EEPROM 24C32N:

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

## Пов’язані сторінки

- [Розпіновка GPIO](/ua/gpio/pinout)
- [Модуль gpio](/ua/dev/js-gpio)
- [Модуль SPI](/ua/dev/js-spi)
