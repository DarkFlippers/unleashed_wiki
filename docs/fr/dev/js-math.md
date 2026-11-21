---
title: "JavaScript : math"
sidebarTitle: "JS : math"
order: 320
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_math.md]
sources: [unleashed-docs]
---
# Module math

Fonctions et constantes mathématiques. Chargez d'abord le module :

```js
let math = require("math");
```

::: tip
`math` est le plus gros module JS : il occupe environ 21 Ko de RAM une fois chargé. Si vous avez seulement besoin
d'arrondir un nombre positif vers le bas, `x | 0` fait la même chose que `math.floor(x)` sans charger le module.
:::

## Constantes

| Constante | Valeur |
|---|---|
| `PI` | π = 3.14159265358979323846264338327950288 |
| `E` | e (nombre d'Euler) = 2.71828182845904523536028747135266250 |
| `EPSILON` | Le plus petit nombre tel que 1.0 + EPSILON != 1.0 ; EPSILON = 2.2204460492503131e-16 |

## Méthodes

### abs()
`abs(x)` : valeur absolue de `x`. Si `x` est négatif (y compris -0), renvoie `-x`, sinon `x`. Le résultat est toujours
positif ou nul.

```js
math.abs(-5); // 5
```

### acos()
`acos(x)` : arc cosinus en radians. `x` est compris entre -1 et 1 inclus (le cosinus de l'angle). Renvoie un angle
compris entre 0 et π inclus. Renvoie `NaN` si `x` est inférieur à -1 ou supérieur à 1.

```js
math.acos(-1); // 3.141592653589793
```

### acosh()
`acosh(x)` : argument cosinus hyperbolique. `x` ≥ 1.

```js
math.acosh(1); // 0
```

### asin()
`asin(x)` : arc sinus en radians. `x` est compris entre -1 et 1 inclus. Renvoie un angle compris entre -π/2 et π/2
inclus.

```js
math.asin(0.5); // 0.5235987755982989
```

### asinh()
`asinh(x)` : argument sinus hyperbolique.

```js
math.asinh(1); // 0.881373587019543
```

### atan()
`atan(x)` : arc tangente en radians, entre -π/2 et π/2 inclus.

```js
math.atan(1); // 0.7853981633974483
```

### atan2()
`atan2(y, x)` : l'angle en radians (entre -π et π inclus) entre l'axe des x positifs et la demi-droite allant de
(0, 0) au point (x, y).

- `y` : coordonnée y du point ;
- `x` : coordonnée x du point.

```js
math.atan2(90, 15); // 1.4056476493802699
```

### atanh()
`atanh(x)` : argument tangente hyperbolique. `x` est compris entre -1 et 1 inclus.

```js
math.atanh(0.5); // 0.5493061443340548
```

### cbrt()
`cbrt(x)` : racine cubique.

```js
math.cbrt(2); // 1.2599210498948732
```

### ceil()
`ceil(x)` : arrondit vers le haut ; le plus petit entier supérieur ou égal à `x`. Équivalent à `-math.floor(-x)`.

```js
math.ceil(-7.004); // -7
math.ceil(7.004);  // 8
```

### clz32()
`clz32(x)` : nombre de bits à zéro en tête de la représentation binaire sur 32 bits de `x`.

```js
math.clz32(1);    // 31
math.clz32(1000); // 22
```

### cos()
`cos(x)` : cosinus d'un angle en radians, entre -1 et 1 inclus.

```js
math.cos(math.PI); // -1
```

### exp()
`exp(x)` : e élevé à la puissance `x` (résultat positif ou nul).

```js
math.exp(0); // 1
math.exp(1); // 2.718281828459045
```

### floor()
`floor(x)` : arrondit vers le bas ; le plus grand entier inférieur ou égal à `x`. Équivalent à `-math.ceil(-x)`.

```js
math.floor(-45.95); // -46
math.floor(-45.05); // -46
math.floor(-0); // -0
math.floor(0); // 0
math.floor(45.05); // 45
math.floor(45.95); // 45
```

### log()
`log(x)` : logarithme népérien, ln(x).

```js
math.log(1); // 0
math.log(3); // 1.0986122886681098
```

### isEqual()
`isEqual(a, b, tolerance)` : `true` si la différence entre `a` et `b` est inférieure à `tolerance`, `false` sinon.

```js
math.isEqual(1.4, 1.6, 0.2);      // false
math.isEqual(3.556, 3.555, 0.01); // true
```

### max()
`max(a, b)` : le plus grand de deux nombres.

```js
math.max(10, 20);   // 20
math.max(-10, -20); // -10
```

### min()
`min(a, b)` : le plus petit de deux nombres.

```js
math.min(10, 20);   // 10
math.min(-10, -20); // -20
```

### pow()
`pow(base, exponent)` : `base` élevée à la puissance `exponent`.

```js
math.pow(7, 2);  // 49
math.pow(7, 3);  // 343
math.pow(2, 10); // 1024
```

### random()
`random()` : nombre pseudo-aléatoire à virgule flottante de 0 (inclus) à 1 (exclu), de distribution à peu près
uniforme. Mettez-le à l'échelle de la plage dont vous avez besoin.

```js
let num = math.random();
```

### sign()
`sign(x)` : -1 si `x` est inférieur à 0, sinon 1.

```js
math.sign(3);  // 1
math.sign(0);  // 1
math.sign(-3); // -1
```

### sin()
`sin(x)` : sinus d'un angle en radians, entre -1 et 1 inclus.

```js
math.sin(math.PI / 2); // 1
```

### sqrt()
`sqrt(x)` : racine carrée, `x` ≥ 0. Si `x` < 0, le script **échoue avec une erreur**.

```js
math.sqrt(25); // 5
```

### trunc()
`trunc(x)` : partie entière de `x`, les chiffres après la virgule étant supprimés.

```js
math.trunc(-1.123); // -1
math.trunc(0.123);  // 0
math.trunc(13.37);  // 13
math.trunc(42.84);  // 42
```
