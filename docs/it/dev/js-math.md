---
title: "JavaScript: math"
sidebarTitle: "JS: math"
order: 320
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_math.md]
sources: [unleashed-docs]
---
# Modulo math

Funzioni e costanti matematiche. Carica prima il modulo:

```js
let math = require("math");
```

::: tip
`math` è il modulo JS più grande: occupa circa 21 KB di RAM una volta caricato. Se ti serve solo arrotondare per difetto un numero non negativo, `x | 0` fa lo stesso di `math.floor(x)` senza caricare il modulo.
:::

## Costanti

| Costante | Valore |
|---|---|
| `PI` | π = 3.14159265358979323846264338327950288 |
| `E` | e (numero di Eulero) = 2.71828182845904523536028747135266250 |
| `EPSILON` | Il numero più piccolo tale che 1.0 + EPSILON != 1.0; EPSILON = 2.2204460492503131e-16 |

## Metodi

### abs()
`abs(x)`: valore assoluto di `x`. Se `x` è negativo (incluso -0) restituisce `-x`, altrimenti `x`. Il risultato è sempre positivo o 0.

```js
math.abs(-5); // 5
```

### acos()
`acos(x)`: arcocoseno in radianti. `x` è compreso tra -1 e 1 inclusi (il coseno dell'angolo). Restituisce un angolo tra 0 e π inclusi. Restituisce `NaN` se `x` è minore di -1 o maggiore di 1.

```js
math.acos(-1); // 3.141592653589793
```

### acosh()
`acosh(x)`: arcocoseno iperbolico. `x` ≥ 1.

```js
math.acosh(1); // 0
```

### asin()
`asin(x)`: arcoseno in radianti. `x` è compreso tra -1 e 1 inclusi. Restituisce un angolo tra -π/2 e π/2 inclusi.

```js
math.asin(0.5); // 0.5235987755982989
```

### asinh()
`asinh(x)`: arcoseno iperbolico.

```js
math.asinh(1); // 0.881373587019543
```

### atan()
`atan(x)`: arcotangente in radianti, tra -π/2 e π/2 inclusi.

```js
math.atan(1); // 0.7853981633974483
```

### atan2()
`atan2(y, x)`: l'angolo in radianti (tra -π e π inclusi) tra l'asse x positivo e la semiretta da (0, 0) al punto (x, y).

- `y`: coordinata y del punto;
- `x`: coordinata x del punto.

```js
math.atan2(90, 15); // 1.4056476493802699
```

### atanh()
`atanh(x)`: arcotangente iperbolica. `x` è compreso tra -1 e 1 inclusi.

```js
math.atanh(0.5); // 0.5493061443340548
```

### cbrt()
`cbrt(x)`: radice cubica.

```js
math.cbrt(2); // 1.2599210498948732
```

### ceil()
`ceil(x)`: arrotonda per eccesso; il più piccolo intero maggiore o uguale a `x`. Equivale a `-math.floor(-x)`.

```js
math.ceil(-7.004); // -7
math.ceil(7.004);  // 8
```

### clz32()
`clz32(x)`: numero di bit zero iniziali nella rappresentazione binaria a 32 bit di `x`.

```js
math.clz32(1);    // 31
math.clz32(1000); // 22
```

### cos()
`cos(x)`: coseno di un angolo in radianti, tra -1 e 1 inclusi.

```js
math.cos(math.PI); // -1
```

### exp()
`exp(x)`: e elevato alla potenza `x` (risultato non negativo).

```js
math.exp(0); // 1
math.exp(1); // 2.718281828459045
```

### floor()
`floor(x)`: arrotonda per difetto; il più grande intero minore o uguale a `x`. Equivale a `-math.ceil(-x)`.

```js
math.floor(-45.95); // -46
math.floor(-45.05); // -46
math.floor(-0); // -0
math.floor(0); // 0
math.floor(45.05); // 45
math.floor(45.95); // 45
```

### log()
`log(x)`: logaritmo naturale, ln(x).

```js
math.log(1); // 0
math.log(3); // 1.0986122886681098
```

### isEqual()
`isEqual(a, b, tolerance)`: `true` se la differenza tra `a` e `b` è minore di `tolerance`, altrimenti `false`.

```js
math.isEqual(1.4, 1.6, 0.2);      // false
math.isEqual(3.556, 3.555, 0.01); // true
```

### max()
`max(a, b)`: il maggiore tra due numeri.

```js
math.max(10, 20);   // 20
math.max(-10, -20); // -10
```

### min()
`min(a, b)`: il minore tra due numeri.

```js
math.min(10, 20);   // 10
math.min(-10, -20); // -20
```

### pow()
`pow(base, exponent)`: `base` elevato alla potenza `exponent`.

```js
math.pow(7, 2);  // 49
math.pow(7, 3);  // 343
math.pow(2, 10); // 1024
```

### random()
`random()`: numero pseudocasuale in virgola mobile da 0 (incluso) a 1 (escluso), distribuito in modo approssimativamente uniforme. Scalalo all'intervallo che ti serve.

```js
let num = math.random();
```

### sign()
`sign(x)`: -1 se `x` è minore di 0, altrimenti 1.

```js
math.sign(3);  // 1
math.sign(0);  // 1
math.sign(-3); // -1
```

### sin()
`sin(x)`: seno di un angolo in radianti, tra -1 e 1 inclusi.

```js
math.sin(math.PI / 2); // 1
```

### sqrt()
`sqrt(x)`: radice quadrata, `x` ≥ 0. Se `x` < 0, lo script **termina con un errore**.

```js
math.sqrt(25); // 5
```

### trunc()
`trunc(x)`: parte intera di `x`, con le cifre decimali rimosse.

```js
math.trunc(-1.123); // -1
math.trunc(0.123);  // 0
math.trunc(13.37);  // 13
math.trunc(42.84);  // 42
```
