---
title: "JavaScript: типи даних"
sidebarTitle: "JS: типи даних"
order: 240
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_data_types.md]
sources: [unleashed-docs]
---
# Типи даних

Основні типи даних у mJS — рушії JavaScript у Flipper Zero:

| Тип | Примітки |
|---|---|
| `string` | Послідовність однобайтових символів. **Підтримки UTF-8 немає.** |
| `number` | |
| `boolean` | |
| `foreign` | Вказівник на функцію або дані C, використовується модулями всередині |
| `undefined` | |
| `null` | |
| `Object` | Структура даних з іменованими полями |
| `Array` | Особливий різновид об’єкта: усі елементи проіндексовані й мають однаковий тип |
| `ArrayBuffer` | Буфер сирих даних |
| `DataView` | Інтерфейс доступу до вмісту `ArrayBuffer` (типізовані масиви, як-от `Uint8Array`) |

Методи, доступні для цих типів (`String.slice()`, `Array.push()`, `ArrayBuffer.slice()`, поля типізованих масивів тощо), перелічено на сторінці [Вбудовані функції](/ua/dev/js-builtin).

::: tip
Оскільки рядки однобайтові й не підтримують UTF-8, `length`, `charCodeAt()` і `slice()` працюють з байтами, а не зі символами. Щоб не мати неприємних сюрпризів, тримайте рядки в межах ASCII.
:::
