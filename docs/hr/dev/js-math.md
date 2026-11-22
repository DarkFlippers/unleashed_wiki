---
title: "JavaScript: math"
sidebarTitle: "JS: math"
order: 320
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_math.md]
sources: [unleashed-docs]
---
# Modul math

Matematičke funkcije i konstante. Prvo učitajte modul:

```js
let math = require("math");
```

::: tip
`math` je najveći JS modul: nakon učitavanja zauzima oko 21 KB RAM-a. Ako trebate samo zaokružiti nenegativan broj prema dolje, `x | 0` radi isto što i `math.floor(x)` bez učitavanja modula.
:::

## Konstante

| Konstanta | Vrijednost |
|---|---|
| `PI` | π = 3.14159265358979323846264338327950288 |
| `E` | e (Eulerov broj) = 2.71828182845904523536028747135266250 |
| `EPSILON` | Najmanji broj takav da vrijedi 1.0 + EPSILON != 1.0; EPSILON = 2.2204460492503131e-16 |

## Metode

### abs()
`abs(x)`: apsolutna vrijednost od `x`. Ako je `x` negativan (uključujući -0), vraća `-x`, inače `x`. Rezultat je uvijek pozitivan ili 0.

```js
math.abs(-5); // 5
```

### acos()
`acos(x)`: arkus kosinus u radijanima. `x` je između -1 i 1 uključivo (kosinus kuta). Vraća kut između 0 i π uključivo. Vraća `NaN` ako je `x` manji od -1 ili veći od 1.

```js
math.acos(-1); // 3.141592653589793
```

### acosh()
`acosh(x)`: area kosinus (inverzni hiperbolni kosinus). `x` ≥ 1.

```js
math.acosh(1); // 0
```

### asin()
`asin(x)`: arkus sinus u radijanima. `x` je između -1 i 1 uključivo. Vraća kut između -π/2 i π/2 uključivo.

```js
math.asin(0.5); // 0.5235987755982989
```

### asinh()
`asinh(x)`: area sinus (inverzni hiperbolni sinus).

```js
math.asinh(1); // 0.881373587019543
```

### atan()
`atan(x)`: arkus tangens u radijanima, između -π/2 i π/2 uključivo.

```js
math.atan(1); // 0.7853981633974483
```

### atan2()
`atan2(y, x)`: kut u radijanima (između -π i π uključivo) između pozitivne osi x i zrake od (0, 0) do točke (x, y).

- `y`: y koordinata točke;
- `x`: x koordinata točke.

```js
math.atan2(90, 15); // 1.4056476493802699
```

### atanh()
`atanh(x)`: area tangens (inverzni hiperbolni tangens). `x` je između -1 i 1 uključivo.

```js
math.atanh(0.5); // 0.5493061443340548
```

### cbrt()
`cbrt(x)`: kubni korijen.

```js
math.cbrt(2); // 1.2599210498948732
```

### ceil()
`ceil(x)`: zaokružuje prema gore; najmanji cijeli broj veći ili jednak `x`. Isto kao `-math.floor(-x)`.

```js
math.ceil(-7.004); // -7
math.ceil(7.004);  // 8
```

### clz32()
`clz32(x)`: broj vodećih nultih bitova u 32-bitnom binarnom prikazu broja `x`.

```js
math.clz32(1);    // 31
math.clz32(1000); // 22
```

### cos()
`cos(x)`: kosinus kuta u radijanima, između -1 i 1 uključivo.

```js
math.cos(math.PI); // -1
```

### exp()
`exp(x)`: e na potenciju `x` (nenegativan rezultat).

```js
math.exp(0); // 1
math.exp(1); // 2.718281828459045
```

### floor()
`floor(x)`: zaokružuje prema dolje; najveći cijeli broj manji ili jednak `x`. Isto kao `-math.ceil(-x)`.

```js
math.floor(-45.95); // -46
math.floor(-45.05); // -46
math.floor(-0); // -0
math.floor(0); // 0
math.floor(45.05); // 45
math.floor(45.95); // 45
```

### log()
`log(x)`: prirodni logaritam, ln(x).

```js
math.log(1); // 0
math.log(3); // 1.0986122886681098
```

### isEqual()
`isEqual(a, b, tolerance)`: `true` ako je razlika između `a` i `b` manja od `tolerance`, inače `false`.

```js
math.isEqual(1.4, 1.6, 0.2);      // false
math.isEqual(3.556, 3.555, 0.01); // true
```

### max()
`max(a, b)`: veći od dvaju brojeva.

```js
math.max(10, 20);   // 20
math.max(-10, -20); // -10
```

### min()
`min(a, b)`: manji od dvaju brojeva.

```js
math.min(10, 20);   // 10
math.min(-10, -20); // -20
```

### pow()
`pow(base, exponent)`: `base` na potenciju `exponent`.

```js
math.pow(7, 2);  // 49
math.pow(7, 3);  // 343
math.pow(2, 10); // 1024
```

### random()
`random()`: pseudoslučajni broj s pomičnim zarezom od 0 (uključivo) do 1 (isključivo), približno jednoliko raspoređen. Skalirajte ga na željeni raspon.

```js
let num = math.random();
```

### sign()
`sign(x)`: -1 ako je `x` manji od 0, inače 1.

```js
math.sign(3);  // 1
math.sign(0);  // 1
math.sign(-3); // -1
```

### sin()
`sin(x)`: sinus kuta u radijanima, između -1 i 1 uključivo.

```js
math.sin(math.PI / 2); // 1
```

### sqrt()
`sqrt(x)`: kvadratni korijen, `x` ≥ 0. Ako je `x` < 0, skripta **završava s pogreškom**.

```js
math.sqrt(25); // 5
```

### trunc()
`trunc(x)`: cjelobrojni dio broja `x`, s uklonjenim decimalnim znamenkama.

```js
math.trunc(-1.123); // -1
math.trunc(0.123);  // 0
math.trunc(13.37);  // 13
math.trunc(42.84);  // 42
```
