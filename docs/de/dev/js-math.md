---
title: "JavaScript: math"
sidebarTitle: "JS: math"
order: 320
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_math.md]
sources: [unleashed-docs]
---
# Modul math

Mathematische Funktionen und Konstanten. Lade zuerst das Modul:

```js
let math = require("math");
```

::: tip
`math` ist das größte JS-Modul: es belegt nach dem Laden etwa 21 KB RAM. Wenn du nur eine nicht negative Zahl
abrunden willst, tut `x | 0` dasselbe wie `math.floor(x)`, ohne das Modul zu laden.
:::

## Konstanten

| Konstante | Wert |
|---|---|
| `PI` | π = 3.14159265358979323846264338327950288 |
| `E` | e (die eulersche Zahl) = 2.71828182845904523536028747135266250 |
| `EPSILON` | Die kleinste Zahl, für die 1.0 + EPSILON != 1.0 gilt; EPSILON = 2.2204460492503131e-16 |

## Methoden

### abs()
`abs(x)`: Absolutwert von `x`. Ist `x` negativ (einschließlich -0), wird `-x` zurückgegeben, sonst `x`. Das Ergebnis
ist immer positiv oder 0.

```js
math.abs(-5); // 5
```

### acos()
`acos(x)`: Arkuskosinus in Radiant. `x` liegt einschließlich zwischen -1 und 1 (der Kosinus des Winkels). Gibt einen
Winkel einschließlich zwischen 0 und π zurück. Gibt `NaN` zurück, wenn `x` kleiner als -1 oder größer als 1 ist.

```js
math.acos(-1); // 3.141592653589793
```

### acosh()
`acosh(x)`: Areakosinus hyperbolicus. `x` ≥ 1.

```js
math.acosh(1); // 0
```

### asin()
`asin(x)`: Arkussinus in Radiant. `x` liegt einschließlich zwischen -1 und 1. Gibt einen Winkel einschließlich
zwischen -π/2 und π/2 zurück.

```js
math.asin(0.5); // 0.5235987755982989
```

### asinh()
`asinh(x)`: Areasinus hyperbolicus.

```js
math.asinh(1); // 0.881373587019543
```

### atan()
`atan(x)`: Arkustangens in Radiant, einschließlich zwischen -π/2 und π/2.

```js
math.atan(1); // 0.7853981633974483
```

### atan2()
`atan2(y, x)`: der Winkel in Radiant (einschließlich zwischen -π und π) zwischen der positiven x-Achse und dem
Strahl von (0, 0) zum Punkt (x, y).

- `y`: y-Koordinate des Punkts;
- `x`: x-Koordinate des Punkts.

```js
math.atan2(90, 15); // 1.4056476493802699
```

### atanh()
`atanh(x)`: Areatangens hyperbolicus. `x` liegt einschließlich zwischen -1 und 1.

```js
math.atanh(0.5); // 0.5493061443340548
```

### cbrt()
`cbrt(x)`: Kubikwurzel.

```js
math.cbrt(2); // 1.2599210498948732
```

### ceil()
`ceil(x)`: rundet auf; die kleinste ganze Zahl, die größer oder gleich `x` ist. Entspricht `-math.floor(-x)`.

```js
math.ceil(-7.004); // -7
math.ceil(7.004);  // 8
```

### clz32()
`clz32(x)`: Anzahl der führenden Nullbits in der 32-Bit-Binärdarstellung von `x`.

```js
math.clz32(1);    // 31
math.clz32(1000); // 22
```

### cos()
`cos(x)`: Kosinus eines Winkels in Radiant, einschließlich zwischen -1 und 1.

```js
math.cos(math.PI); // -1
```

### exp()
`exp(x)`: e hoch `x` (nicht negatives Ergebnis).

```js
math.exp(0); // 1
math.exp(1); // 2.718281828459045
```

### floor()
`floor(x)`: rundet ab; die größte ganze Zahl, die kleiner oder gleich `x` ist. Entspricht `-math.ceil(-x)`.

```js
math.floor(-45.95); // -46
math.floor(-45.05); // -46
math.floor(-0); // -0
math.floor(0); // 0
math.floor(45.05); // 45
math.floor(45.95); // 45
```

### log()
`log(x)`: natürlicher Logarithmus, ln(x).

```js
math.log(1); // 0
math.log(3); // 1.0986122886681098
```

### isEqual()
`isEqual(a, b, tolerance)`: `true`, wenn die Differenz zwischen `a` und `b` kleiner als `tolerance` ist, sonst
`false`.

```js
math.isEqual(1.4, 1.6, 0.2);      // false
math.isEqual(3.556, 3.555, 0.01); // true
```

### max()
`max(a, b)`: die größere von zwei Zahlen.

```js
math.max(10, 20);   // 20
math.max(-10, -20); // -10
```

### min()
`min(a, b)`: die kleinere von zwei Zahlen.

```js
math.min(10, 20);   // 10
math.min(-10, -20); // -20
```

### pow()
`pow(base, exponent)`: `base` hoch `exponent`.

```js
math.pow(7, 2);  // 49
math.pow(7, 3);  // 343
math.pow(2, 10); // 1024
```

### random()
`random()`: pseudozufällige Gleitkommazahl von 0 (inklusive) bis 1 (exklusive), näherungsweise gleichmäßig
verteilt. Skaliere sie auf den Bereich, den du brauchst.

```js
let num = math.random();
```

### sign()
`sign(x)`: -1, wenn `x` kleiner als 0 ist, sonst 1.

```js
math.sign(3);  // 1
math.sign(0);  // 1
math.sign(-3); // -1
```

### sin()
`sin(x)`: Sinus eines Winkels in Radiant, einschließlich zwischen -1 und 1.

```js
math.sin(math.PI / 2); // 1
```

### sqrt()
`sqrt(x)`: Quadratwurzel, `x` ≥ 0. Ist `x` < 0, **bricht das Skript mit einem Fehler ab**.

```js
math.sqrt(25); // 5
```

### trunc()
`trunc(x)`: der ganzzahlige Anteil von `x`, die Dezimalstellen werden entfernt.

```js
math.trunc(-1.123); // -1
math.trunc(0.123);  // 0
math.trunc(13.37);  // 13
math.trunc(42.84);  // 42
```
