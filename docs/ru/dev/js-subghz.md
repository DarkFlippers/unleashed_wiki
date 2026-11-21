---
title: "JavaScript: subghz"
sidebarTitle: "JS: subghz"
order: 400
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_subghz]
sources: [unleashed-src]
---
# Модуль Sub-GHz

Дополнение Unleashed, в стоковой прошивке его нет. Даёт скрипту радио Sub-GHz: переключение между приёмом и простоем, уровень сигнала, смена частоты, отправка сохранённого `.sub`-файла.

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");
subghz.setup();
```

`setup()` сначала ищет внешний модуль CC1101 и, если его нет, берёт встроенное радио. До вызова `setup()` любой другой метод бросает ошибку `Radio is not setup`.

Пример: `/ext/apps/Scripts/js_examples/subghz.js`.

## Методы

### setup()
Инициализирует радио и выбирает устройство. Стартовая частота — 433920000 Гц, состояние `IDLE`. Бросает ошибку, если радио уже инициализировано.

### end()
Усыпляет радио и освобождает устройство. Происходит автоматически при завершении скрипта. Вызов `setup()` после него заново ищет внешний модуль.

### setRx()
Переводит радио в режим приёма.

### setIdle()
Переводит радио в простой. Менять частоту можно только в этом состоянии.

### getRssi()
Уровень сигнала на текущей частоте, в дБм.

- **Возвращает:** `number` или `undefined`, если радио не в режиме RX.

### getState()
- **Возвращает:** `"RX"`, `"TX"` или `"IDLE"`.

### getFrequency()
- **Возвращает:** текущую частоту в герцах, числом.

### setFrequency()
Настраивает радио. Бросает ошибку, если радио не в `IDLE` или частота вне диапазонов, которые поддерживает устройство.

- **Параметры:** `frequency` — число в герцах, например `433920000`.
- **Возвращает:** частоту, на которую радио реально настроилось. CC1101 может взять не любое значение, поэтому выбирает ближайшее доступное.

### isExternal()
- **Возвращает:** boolean — `true`, если используется внешний CC1101, `false` для встроенного радио.

### transmitFile()
Отправляет `.sub`-файл. Частоту и модуляцию берёт из файла, а не из `setFrequency()`. Возвращает `true`; при любой проблеме (файла нет, неверный заголовок, неподдерживаемая частота, неизвестный пресет) бросает ошибку. После передачи радио остаётся в `IDLE`.

- **Параметры:**
  - `path` — полный путь к файлу, например `"/ext/subghz/0.sub"`;
  - `repeat` (необязательный) — сколько раз отправить.

Без `repeat` RAW-файлы уходят один раз, а протокольные — 10 раз: так имитируется удержание кнопки на настоящем пульте. `CAME Atomo`, `CAME TWEE`, `Hormann HSM`, `Nice FloR-S` и `Power Smart` и так шлют несколько кадров за повтор, поэтому для них по умолчанию 1.

## Пример

Слушаем 433,92 МГц, затем отправляем сохранённый ключ:

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");

subghz.setup();
subghz.setIdle();
subghz.setFrequency(433920000);

subghz.setRx();
print("RSSI:", subghz.getRssi(), "dBm, external:", subghz.isExternal());
delay(1000);

print("Sending 0.sub");
subghz.transmitFile("/ext/subghz/0.sub");
print("Sent");

subghz.end();
```

## См. также

- [Формат файлов Sub-GHz](/ru/subghz/file-format) — что лежит внутри `.sub`
- [Внешние модули CC1101](/ru/subghz/external-cc1101)
- [Обзор JavaScript](/ru/dev/js-about)
