---
title: "JavaScript: spi"
sidebarTitle: "JS: spi"
order: 450
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_spi.c]
sources: [unleashed-src]
---
# Модуль SPI

Дополнение Unleashed, в стоковой прошивке его нет. Работает с микросхемами на внешней шине SPI — флеш-памятью, радиомодулями, дисплеями.

```js
checkSdkFeatures(["spi"]);
let spi = require("spi");
```

Подключение к [гребёнке GPIO](/ru/gpio/pinout): **MOSI — пин 2 (PA7)**, **MISO — пин 3 (PA6)**, **CS — пин 4 (PA4)**, **SCK — пин 5 (PB3)**, 3,3 В — пин 9, GND — пин 8. Сигналом chip select управляет прошивка, вручную его дёргать не нужно.

Пример: `/ext/apps/Scripts/js_examples/spi.js`.

## Методы

### acquire()
Захватывает шину и держит CS в низком уровне до `release()`. Нужен, когда несколько обменов должны выглядеть для устройства одной транзакцией: команда, затем ответ. Без него каждый вызов сам берёт и отпускает шину, а значит между вызовами поднимает CS.

### release()
Освобождает шину.

### write()
- **Параметры:** `data` (`number[]` со значениями 0–255 либо `ArrayBuffer`/`Uint8Array`), `timeout` (необязательный, миллисекунды, по умолчанию 1).
- **Возвращает:** boolean.

### read()
- **Параметры:** `length` (сколько байт прочитать, минимум 1), `timeout` (необязательный, мс, по умолчанию 1).
- **Возвращает:** `ArrayBuffer` либо `undefined` при ошибке. Чтобы обращаться к байтам по индексу, оберните его в `Uint8Array(buf)`.

### writeRead()
Полнодуплексный обмен: отправляет буфер и читает ровно столько байт, сколько отправил.

- **Параметры:** `data` (`number[]` или `ArrayBuffer`), `timeout` (необязательный, мс, по умолчанию 1).
- **Возвращает:** `ArrayBuffer` той же длины, что и `data`, либо `undefined` при ошибке.

## Пример

Читаем JEDEC ID флеш-памяти W25Q32:

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

## См. также

- [Распиновка GPIO](/ru/gpio/pinout)
- [Модуль I2C](/ru/dev/js-i2c)
- [Обзор JavaScript](/ru/dev/js-about)
