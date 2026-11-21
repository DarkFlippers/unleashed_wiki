---
title: "JavaScript: tipi di dati"
sidebarTitle: "JS: tipi di dati"
order: 240
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_data_types.md]
sources: [unleashed-docs]
---
# Tipi di dati

Tipi di dati comuni in mJS, il motore JavaScript di Flipper Zero:

| Tipo | Note |
|---|---|
| `string` | Sequenza di caratteri a un byte. **Nessun supporto UTF-8.** |
| `number` | |
| `boolean` | |
| `foreign` | Puntatore a una funzione C o a dati C, usato internamente dai moduli |
| `undefined` | |
| `null` | |
| `Object` | Struttura dati con campi nominati |
| `Array` | Tipo di oggetto speciale: tutti gli elementi sono indicizzati e dello stesso tipo |
| `ArrayBuffer` | Buffer di dati grezzi |
| `DataView` | Interfaccia per accedere al contenuto di un `ArrayBuffer` (array tipizzati come `Uint8Array`) |

I metodi disponibili su questi tipi (`String.slice()`, `Array.push()`, `ArrayBuffer.slice()`, i campi degli array tipizzati, ecc.) sono elencati in [Funzioni integrate](/it/dev/js-builtin).

::: tip
Poiché le stringhe sono a un byte e senza supporto UTF-8, `length`, `charCodeAt()` e `slice()` lavorano sui byte, non sui caratteri. Mantieni le stringhe in ASCII per evitare sorprese.
:::
