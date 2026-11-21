---
title: "JavaScript: math"
sidebarTitle: "JS: math"
order: 320
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_math.md]
sources: [unleashed-docs]
---
# Módulo Math

Funciones y constantes matemáticas. Carga primero el módulo:

```js
let math = require("math");
```

::: tip
`math` es el módulo de JS más grande: ocupa unos 21 KB de RAM una vez cargado. Si solo necesitas redondear hacia abajo un número no negativo, `x | 0` hace lo mismo que `math.floor(x)` sin cargar el módulo.
:::

## Constantes

| Constante | Valor |
|---|---|
| `PI` | π = 3.14159265358979323846264338327950288 |
| `E` | e (número de Euler) = 2.71828182845904523536028747135266250 |
| `EPSILON` | El número más pequeño tal que 1.0 + EPSILON != 1.0; EPSILON = 2.2204460492503131e-16 |

## Métodos

### abs()
`abs(x)`: valor absoluto de `x`. Si `x` es negativo (incluido -0), devuelve `-x`; en caso contrario, `x`. El resultado es siempre positivo o 0.

```js
math.abs(-5); // 5
```

### acos()
`acos(x)`: arcocoseno en radianes. `x` está entre -1 y 1, ambos incluidos (el coseno del ángulo). Devuelve un ángulo entre 0 y π, ambos incluidos. Devuelve `NaN` si `x` es menor que -1 o mayor que 1.

```js
math.acos(-1); // 3.141592653589793
```

### acosh()
`acosh(x)`: arcocoseno hiperbólico. `x` ≥ 1.

```js
math.acosh(1); // 0
```

### asin()
`asin(x)`: arcoseno en radianes. `x` está entre -1 y 1, ambos incluidos. Devuelve un ángulo entre -π/2 y π/2, ambos incluidos.

```js
math.asin(0.5); // 0.5235987755982989
```

### asinh()
`asinh(x)`: arcoseno hiperbólico.

```js
math.asinh(1); // 0.881373587019543
```

### atan()
`atan(x)`: arcotangente en radianes, entre -π/2 y π/2, ambos incluidos.

```js
math.atan(1); // 0.7853981633974483
```

### atan2()
`atan2(y, x)`: el ángulo en radianes (entre -π y π, ambos incluidos) entre el eje x positivo y el rayo que va de (0, 0) al punto (x, y).

- `y`: coordenada y del punto;
- `x`: coordenada x del punto.

```js
math.atan2(90, 15); // 1.4056476493802699
```

### atanh()
`atanh(x)`: arcotangente hiperbólica. `x` está entre -1 y 1, ambos incluidos.

```js
math.atanh(0.5); // 0.5493061443340548
```

### cbrt()
`cbrt(x)`: raíz cúbica.

```js
math.cbrt(2); // 1.2599210498948732
```

### ceil()
`ceil(x)`: redondea hacia arriba; el entero más pequeño mayor o igual que `x`. Equivale a `-math.floor(-x)`.

```js
math.ceil(-7.004); // -7
math.ceil(7.004);  // 8
```

### clz32()
`clz32(x)`: número de bits cero iniciales en la representación binaria de 32 bits de `x`.

```js
math.clz32(1);    // 31
math.clz32(1000); // 22
```

### cos()
`cos(x)`: coseno de un ángulo en radianes, entre -1 y 1, ambos incluidos.

```js
math.cos(math.PI); // -1
```

### exp()
`exp(x)`: e elevado a `x` (resultado no negativo).

```js
math.exp(0); // 1
math.exp(1); // 2.718281828459045
```

### floor()
`floor(x)`: redondea hacia abajo; el entero más grande menor o igual que `x`. Equivale a `-math.ceil(-x)`.

```js
math.floor(-45.95); // -46
math.floor(-45.05); // -46
math.floor(-0); // -0
math.floor(0); // 0
math.floor(45.05); // 45
math.floor(45.95); // 45
```

### log()
`log(x)`: logaritmo natural, ln(x).

```js
math.log(1); // 0
math.log(3); // 1.0986122886681098
```

### isEqual()
`isEqual(a, b, tolerance)`: `true` si la diferencia entre `a` y `b` es menor que `tolerance`; en caso contrario, `false`.

```js
math.isEqual(1.4, 1.6, 0.2);      // false
math.isEqual(3.556, 3.555, 0.01); // true
```

### max()
`max(a, b)`: el mayor de dos números.

```js
math.max(10, 20);   // 20
math.max(-10, -20); // -10
```

### min()
`min(a, b)`: el menor de dos números.

```js
math.min(10, 20);   // 10
math.min(-10, -20); // -20
```

### pow()
`pow(base, exponent)`: `base` elevado a `exponent`.

```js
math.pow(7, 2);  // 49
math.pow(7, 3);  // 343
math.pow(2, 10); // 1024
```

### random()
`random()`: número de coma flotante pseudoaleatorio desde 0 (incluido) hasta 1 (excluido), con distribución aproximadamente uniforme. Escálalo al rango que necesites.

```js
let num = math.random();
```

### sign()
`sign(x)`: -1 si `x` es menor que 0; en caso contrario, 1.

```js
math.sign(3);  // 1
math.sign(0);  // 1
math.sign(-3); // -1
```

### sin()
`sin(x)`: seno de un ángulo en radianes, entre -1 y 1, ambos incluidos.

```js
math.sin(math.PI / 2); // 1
```

### sqrt()
`sqrt(x)`: raíz cuadrada, `x` ≥ 0. Si `x` < 0, el script **falla con un error**.

```js
math.sqrt(25); // 5
```

### trunc()
`trunc(x)`: parte entera de `x`, eliminando los decimales.

```js
math.trunc(-1.123); // -1
math.trunc(0.123);  // 0
math.trunc(13.37);  // 13
math.trunc(42.84);  // 42
```
