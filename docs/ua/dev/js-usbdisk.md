---
title: "JavaScript: usbdisk"
sidebarTitle: "JS: usbdisk"
order: 430
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_usbdisk]
sources: [unleashed-src]
---
# Модуль USB-накопичувача

Додаток Unleashed, у стоковій прошивці його немає. Змушує Flipper виглядати для ПК як USB-флешка. Вміст береться з одного файлу-образу на SD-картці: ПК читає й пише блоки просто в цей файл.

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
```

Приклад скрипта: `/ext/apps/Scripts/js_examples/usbdisk.js`.

`createImage()` створює порожній образ, або скопіюйте готовий `.img` у `/ext/apps_data/mass_storage/` самостійно. Файл читається блоками по 512 байтів, тож його розмір має бути кратним 512.

Якщо до цього скрипт використовував BadUSB, спершу викличте [`badusb.quit()`](/ua/dev/js-badusb#quit), щоб звільнити USB.

## Методи

### createImage()
Створює порожній образ потрібного розміру. Місце лише займається, а не записується, тому навіть великий образ готується швидко. Перші 4 КБ обнуляються, щоб ПК запропонував відформатувати новий диск. Кидає виняток, якщо за цим шляхом уже щось є або на картці бракує місця.

- **Параметри:** `path` — куди покласти образ; `size` — розмір у байтах, округлюється вниз до цілих 512 байтів.

### start()
Відкриває образ на читання й запис і підключає накопичувач до ПК. Назва диска — ім’я файлу-образу без розширення. Кидає виняток, якщо файлу немає або диск уже запущено.

- **Параметри:** `path` — повний шлях до образу, наприклад `"/ext/apps_data/mass_storage/128MB.img"`.

### stop()
Відключає накопичувач і закриває файл. Також відбувається при завершенні скрипта.

### wasEjected()
- **Повертає:** boolean — `true`, щойно ПК від’єднає накопичувач. Використовуйте як умову циклу. Кидає виняток, якщо диск не запущено.

## Приклад

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
`createImage()` з’явився пізніше за решту модуля. Скрипт, який може працювати й на старішій збірці, варто спершу перевірити через `doesSdkSupport(["usbdisk-createimage"])` — саме так зроблено в прикладі з прошивки.
:::

## Пов’язані сторінки

- [Модуль BadUSB](/ua/dev/js-badusb) — `quit()` звільняє USB для цього модуля
- [Модуль storage](/ua/dev/js-storage) — перевірити наявність образу перед запуском
- [Огляд JavaScript](/ua/dev/js-about)
