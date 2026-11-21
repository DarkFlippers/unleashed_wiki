---
title: "JavaScript: типы данных"
sidebarTitle: "JS: типы данных"
order: 240
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_data_types.md]
sources: [unleashed-docs]
---
# Типы данных

Основные типы данных mJS — JavaScript-движка Flipper Zero:

| Тип | Примечание |
|---|---|
| `string` | Последовательность однобайтовых символов. **Без поддержки UTF-8.** |
| `number` | |
| `boolean` | |
| `foreign` | Указатель на C-функцию или C-данные, используется модулями |
| `undefined` | |
| `null` | |
| `Object` | Структура с именованными полями |
| `Array` | Особый вид объекта: все элементы индексированы и одного типа |
| `ArrayBuffer` | Буфер сырых данных |
| `DataView` | Интерфейс доступа к содержимому `ArrayBuffer` (типизированные массивы вроде `Uint8Array`) |

Методы этих типов (`String.slice()`, `Array.push()`, `ArrayBuffer.slice()`, поля типизированных массивов и т. д.) перечислены в [Встроенные функции](/ru/dev/js-builtin).

::: tip
Строки однобайтовые и без UTF-8, поэтому `length`, `charCodeAt()` и `slice()` работают с байтами, а не с символами. Чтобы избежать сюрпризов, держите строки в ASCII.
:::
