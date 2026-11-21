---
title: "JavaScript: usbdisk"
sidebarTitle: "JS: usbdisk"
order: 430
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_usbdisk]
sources: [unleashed-src]
---
# Модуль USB-накопителя

Дополнение Unleashed, в стоковой прошивке его нет. Флиппер прикидывается для компьютера USB-флешкой. Содержимое берётся из одного файла-образа на SD-карте: ПК читает и пишет блоки прямо в этот файл.

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
```

Пример: `/ext/apps/Scripts/js_examples/usbdisk.js`.

`createImage()` создаёт пустой образ, либо скопируйте готовый `.img` в `/ext/apps_data/mass_storage/` сами. Файл читается блоками по 512 байт, поэтому его размер должен быть кратен 512.

Если до этого в скрипте работал BadUSB, сначала вызовите [`badusb.quit()`](/ru/dev/js-badusb#quit), чтобы освободить USB.

## Методы

### createImage()
Создаёт пустой образ нужного размера. Место только занимается, а не записывается, поэтому даже большой образ делается быстро. Первые 4 КБ обнуляются, чтобы ПК предложил отформатировать новый диск. Бросает ошибку, если по этому пути уже что-то есть или на карте мало места.

- **Параметры:** `path` — куда положить образ; `size` — размер в байтах, округляется вниз до целых 512 байт.

### start()
Открывает образ на чтение и запись и подключает диск к ПК. Имя диска — имя файла образа без расширения. Бросает ошибку, если файла нет или диск уже запущен.

- **Параметры:** `path` — полный путь к образу, например `"/ext/apps_data/mass_storage/128MB.img"`.

### stop()
Отключает диск и закрывает файл. Происходит и при завершении скрипта.

### wasEjected()
- **Возвращает:** boolean — `true`, как только ПК извлёк диск. Используйте как условие цикла. Бросает ошибку, если диск не запущен.

## Пример

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
let storage = require("storage");

let imagePath = "/ext/apps_data/mass_storage/128MB.img";
if (!storage.fileExists(imagePath)) {
    usbdisk.createImage(imagePath, 128 * 1024 * 1024);
}

print("Starting UsbDisk...");
usbdisk.start(imagePath);

print("Started, waiting until ejected...");
while (!usbdisk.wasEjected()) {
    delay(1000);
}

print("Ejected, stopping UsbDisk...");
usbdisk.stop();
```

::: tip
`createImage()` появился позже остального модуля. Скрипт, который может работать и на старой сборке, стоит сначала проверить через `doesSdkSupport(["usbdisk-createimage"])` — так и сделано в примере из прошивки.
:::

## См. также

- [Модуль BadUSB](/ru/dev/js-badusb) — `quit()` освобождает USB для этого модуля
- [Модуль Storage](/ru/dev/js-storage) — проверить, что образ на месте, до запуска
- [Обзор JavaScript](/ru/dev/js-about)
