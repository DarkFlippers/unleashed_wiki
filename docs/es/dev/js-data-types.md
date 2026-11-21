---
title: "JavaScript: tipos de datos"
sidebarTitle: "JS: tipos de datos"
order: 240
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_data_types.md]
sources: [unleashed-docs]
---
# Tipos de datos

Tipos de datos habituales en mJS, el motor de JavaScript de Flipper Zero:

| Tipo | Notas |
|---|---|
| `string` | Secuencia de caracteres de un solo byte. **Sin soporte de UTF-8.** |
| `number` | |
| `boolean` | |
| `foreign` | Puntero a una función o a datos de C; lo usan internamente los módulos |
| `undefined` | |
| `null` | |
| `Object` | Estructura de datos con campos con nombre |
| `Array` | Tipo especial de objeto: todos los elementos están indexados y tienen el mismo tipo |
| `ArrayBuffer` | Búfer de datos en bruto |
| `DataView` | Interfaz para acceder al contenido de un `ArrayBuffer` (typed arrays como `Uint8Array`) |

Los métodos disponibles en estos tipos (`String.slice()`, `Array.push()`, `ArrayBuffer.slice()`, los campos de los typed arrays, etc.) se listan en [Funciones integradas](/es/dev/js-builtin).

::: tip
Como las cadenas son de un solo byte y sin soporte de UTF-8, `length`, `charCodeAt()` y `slice()` trabajan con bytes y no con caracteres. Mantén las cadenas en ASCII para evitar sorpresas.
:::
