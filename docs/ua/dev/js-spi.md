---
title: "JavaScript: spi"
sidebarTitle: "JS: spi"
order: 450
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_spi.c]
sources: [unleashed-src]
---
# Модуль SPI

Додаток Unleashed, у стоковій прошивці його немає. Спілкується з мікросхемами SPI на зовнішній шині — флеш-пам’яттю, радіомодулями, дисплеями.

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");
```

Підключення до [гребінки GPIO](/ua/gpio/pinout): **MOSI — пін 2 (PA7)**, **MISO — пін 3 (PA6)**, **CS — пін 4 (PA4)**, **SCK — пін 5 (PB3)**, 3,3 В на піні 9, GND на піні 8. Лінією вибору мікросхеми керує прошивка, вручну її смикати не треба.

Приклад скрипта: `/ext/apps/Scripts/js_examples/spi.js`.

## Методи

### acquire()
Займає шину й тримає CS притиснутим до `release()`. Потрібен, коли кілька передач мають виглядати для пристрою як одна транзакція: команда, потім відповідь. Без нього кожен виклик сам займає й відпускає шину, а між ними CS піднімається.

### release()
Звільняє шину.

### write()
- **Параметри:** `data` (`number[]` зі значеннями 0–255 або `ArrayBuffer`/`Uint8Array`), `timeout` (необов’язковий, мілісекунди, типово 1).
- **Повертає:** boolean.

### read()
- **Параметри:** `length` (кількість байтів, щонайменше 1), `timeout` (необов’язковий, мс, типово 1).
- **Повертає:** `ArrayBuffer` або `undefined` у разі невдачі. Загорніть у `Uint8Array(buf)`, щоб звертатися до окремих байтів.

### writeRead()
Повнодуплексна передача: надсилає буфер і читає рівно стільки байтів, скільки надіслала.

- **Параметри:** `data` (`number[]` або `ArrayBuffer`), `timeout` (необов’язковий, мс, типово 1).
- **Повертає:** `ArrayBuffer` тієї самої довжини, що й `data`, або `undefined` у разі невдачі.

## Приклад

Читаємо JEDEC ID мікросхеми флеш-пам’яті W25Q32:

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

## Пов’язані сторінки

- [Розпіновка GPIO](/ua/gpio/pinout)
- [Модуль I2C](/ua/dev/js-i2c)
- [Огляд JavaScript](/ua/dev/js-about)
