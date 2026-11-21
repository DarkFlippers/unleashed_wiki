---
title: "JavaScript: data types"
sidebarTitle: "JS: data types"
order: 240
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_data_types.md]
sources: [unleashed-docs]
---
# Data types

Common data types in mJS, the JavaScript engine of Flipper Zero:

| Type | Notes |
|---|---|
| `string` | Sequence of single-byte characters. **No UTF-8 support.** |
| `number` | |
| `boolean` | |
| `foreign` | Pointer to a C function or C data, used internally by modules |
| `undefined` | |
| `null` | |
| `Object` | Data structure with named fields |
| `Array` | Special object type: all items are indexed and have equal types |
| `ArrayBuffer` | Raw data buffer |
| `DataView` | Interface for accessing `ArrayBuffer` contents (typed arrays such as `Uint8Array`) |

Methods available on these types (`String.slice()`, `Array.push()`, `ArrayBuffer.slice()`, typed array fields, etc.) are listed on [Built-in functions](/dev/js-builtin).

::: tip
Because strings are single-byte without UTF-8 support, `length`, `charCodeAt()` and `slice()` work on bytes, not characters. Keep strings in ASCII to avoid surprises.
:::
