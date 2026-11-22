---
title: "JavaScript: tipovi podataka"
sidebarTitle: "JS: tipovi podataka"
order: 240
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_data_types.md]
sources: [unleashed-docs]
---
# Tipovi podataka

Uobičajeni tipovi podataka u mJS-u, JavaScript pogonu za Flipper Zero:

| Tip | Napomene |
|---|---|
| `string` | Niz jednobajtnih znakova. **Nema podrške za UTF-8.** |
| `number` | |
| `boolean` | |
| `foreign` | Pokazivač na C funkciju ili C podatke, moduli ga koriste interno |
| `undefined` | |
| `null` | |
| `Object` | Struktura podataka s imenovanim poljima |
| `Array` | Poseban tip objekta: svi su elementi indeksirani i istog su tipa |
| `ArrayBuffer` | Spremnik sirovih podataka |
| `DataView` | Sučelje za pristup sadržaju `ArrayBuffer`-a (tipizirana polja kao što je `Uint8Array`) |

Metode dostupne na ovim tipovima (`String.slice()`, `Array.push()`, `ArrayBuffer.slice()`, polja tipiziranih nizova itd.) navedene su na stranici [Ugrađene funkcije](/hr/dev/js-builtin).

::: tip
Budući da su nizovi znakova jednobajtni bez podrške za UTF-8, `length`, `charCodeAt()` i `slice()` rade na bajtovima, a ne na znakovima. Držite se ASCII znakova u nizovima kako biste izbjegli iznenađenja.
:::
