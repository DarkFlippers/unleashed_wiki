---
title: "JavaScript: i2c"
sidebarTitle: "JS: i2c"
order: 440
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_i2c.c]
sources: [unleashed-src]
---
# Модуль I2C

Дополнение Unleashed, в стоковой прошивке его нет. Работает с микросхемами на внешней шине I2C: датчиками, EEPROM, дисплеями.

```js
checkSdkFeatures(["i2c"]);
let i2c = require("i2c");
```

Подключение к [гребёнке GPIO](/ru/gpio/pinout): **SDA — пин 15 (PC1)**, **SCL — пин 16 (PC0)**, 3,3 В — пин 9, GND — пин 8. Шина на 3,3 В, 5-вольтовые устройства подключать нельзя.

Пример: `/ext/apps/Scripts/js_examples/i2c.js`.

Адреса здесь 8-битные (7-битный адрес, сдвинутый влево на один бит). Если в даташите написано `0x50`, тут обычно нужен `0xA0`. Каждый вызов сам захватывает шину, выполняет обмен и отпускает её, так что между вызовами I2C может пользоваться другое приложение.

## Методы

### isDeviceReady()
Пингует адрес.

- **Параметры:** `address` (число), `timeout` (необязательный, миллисекунды, по умолчанию 1).
- **Возвращает:** boolean.

### write()
- **Параметры:** `address` (число), `data` (`number[]` со значениями 0–255 либо `ArrayBuffer`/`Uint8Array`), `timeout` (необязательный, мс, по умолчанию 1).
- **Возвращает:** boolean — `true`, если устройство ответило подтверждением.

### read()
- **Параметры:** `address` (число), `length` (сколько байт прочитать, минимум 1), `timeout` (необязательный, мс, по умолчанию 1).
- **Возвращает:** `ArrayBuffer` либо `undefined`, если обмен не удался. Чтобы обращаться к байтам по индексу, оберните его в `Uint8Array(buf)`.

### writeRead()
Пишет, затем читает, не отпуская шину. Так читают регистр: отправляют его номер и сразу получают значение.

- **Параметры:** `address`, `writeData` (`number[]` или `ArrayBuffer`), `readLength`, `timeout` (необязательный, мс, по умолчанию 1).
- **Возвращает:** `ArrayBuffer` либо `undefined` при ошибке.

## Пример

Сканируем шину и читаем три байта из EEPROM 24C32N:

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

## См. также

- [Распиновка GPIO](/ru/gpio/pinout)
- [Модуль GPIO](/ru/dev/js-gpio)
- [Модуль SPI](/ru/dev/js-spi)
