---
title: "JavaScript: math"
sidebarTitle: "JS: math"
order: 320
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_math.md]
sources: [unleashed-docs]
---
# Math module

Mathematical functions and constants. Load the module first:

```js
let math = require("math");
```

::: tip
`math` is the largest JS module: it takes about 21 KB of RAM once loaded. If you only need to round a non-negative number down, `x | 0` does the same as `math.floor(x)` without loading the module.
:::

## Constants

| Constant | Value |
|---|---|
| `PI` | π = 3.14159265358979323846264338327950288 |
| `E` | e (Euler's number) = 2.71828182845904523536028747135266250 |
| `EPSILON` | The smallest number such that 1.0 + EPSILON != 1.0; EPSILON = 2.2204460492503131e-16 |

## Methods

### abs()
`abs(x)`: absolute value of `x`. If `x` is negative (including -0), returns `-x`, otherwise `x`. The result is always positive or 0.

```js
math.abs(-5); // 5
```

### acos()
`acos(x)`: inverse cosine in radians. `x` is between -1 and 1 inclusive (the cosine of the angle). Returns an angle between 0 and π inclusive. Returns `NaN` if `x` is less than -1 or greater than 1.

```js
math.acos(-1); // 3.141592653589793
```

### acosh()
`acosh(x)`: inverse hyperbolic cosine. `x` ≥ 1.

```js
math.acosh(1); // 0
```

### asin()
`asin(x)`: inverse sine in radians. `x` is between -1 and 1 inclusive. Returns an angle between -π/2 and π/2 inclusive.

```js
math.asin(0.5); // 0.5235987755982989
```

### asinh()
`asinh(x)`: inverse hyperbolic sine.

```js
math.asinh(1); // 0.881373587019543
```

### atan()
`atan(x)`: inverse tangent in radians, between -π/2 and π/2 inclusive.

```js
math.atan(1); // 0.7853981633974483
```

### atan2()
`atan2(y, x)`: the angle in radians (between -π and π inclusive) between the positive x axis and the ray from (0, 0) to the point (x, y).

- `y`: y coordinate of the point;
- `x`: x coordinate of the point.

```js
math.atan2(90, 15); // 1.4056476493802699
```

### atanh()
`atanh(x)`: inverse hyperbolic tangent. `x` is between -1 and 1 inclusive.

```js
math.atanh(0.5); // 0.5493061443340548
```

### cbrt()
`cbrt(x)`: cube root.

```js
math.cbrt(2); // 1.2599210498948732
```

### ceil()
`ceil(x)`: rounds up; the smallest integer greater than or equal to `x`. Same as `-math.floor(-x)`.

```js
math.ceil(-7.004); // -7
math.ceil(7.004);  // 8
```

### clz32()
`clz32(x)`: number of leading zero bits in the 32-bit binary representation of `x`.

```js
math.clz32(1);    // 31
math.clz32(1000); // 22
```

### cos()
`cos(x)`: cosine of an angle in radians, between -1 and 1 inclusive.

```js
math.cos(math.PI); // -1
```

### exp()
`exp(x)`: e raised to the power `x` (nonnegative result).

```js
math.exp(0); // 1
math.exp(1); // 2.718281828459045
```

### floor()
`floor(x)`: rounds down; the largest integer less than or equal to `x`. Same as `-math.ceil(-x)`.

```js
math.floor(-45.95); // -46
math.floor(-45.05); // -46
math.floor(-0); // -0
math.floor(0); // 0
math.floor(45.05); // 45
math.floor(45.95); // 45
```

### log()
`log(x)`: natural logarithm, ln(x).

```js
math.log(1); // 0
math.log(3); // 1.0986122886681098
```

### isEqual()
`isEqual(a, b, tolerance)`: `true` if the difference between `a` and `b` is less than `tolerance`, otherwise `false`.

```js
math.isEqual(1.4, 1.6, 0.2);      // false
math.isEqual(3.556, 3.555, 0.01); // true
```

### max()
`max(a, b)`: the larger of two numbers.

```js
math.max(10, 20);   // 20
math.max(-10, -20); // -10
```

### min()
`min(a, b)`: the smaller of two numbers.

```js
math.min(10, 20);   // 10
math.min(-10, -20); // -20
```

### pow()
`pow(base, exponent)`: `base` raised to the power `exponent`.

```js
math.pow(7, 2);  // 49
math.pow(7, 3);  // 343
math.pow(2, 10); // 1024
```

### random()
`random()`: pseudo-random floating-point number from 0 (inclusive) to 1 (exclusive), approximately uniformly distributed. Scale it to the range you need.

```js
let num = math.random();
```

### sign()
`sign(x)`: -1 if `x` is less than 0, otherwise 1.

```js
math.sign(3);  // 1
math.sign(0);  // 1
math.sign(-3); // -1
```

### sin()
`sin(x)`: sine of an angle in radians, between -1 and 1 inclusive.

```js
math.sin(math.PI / 2); // 1
```

### sqrt()
`sqrt(x)`: square root, `x` ≥ 0. If `x` < 0, the script **fails with an error**.

```js
math.sqrt(25); // 5
```

### trunc()
`trunc(x)`: integer part of `x`, with the fractional digits removed.

```js
math.trunc(-1.123); // -1
math.trunc(0.123);  // 0
math.trunc(13.37);  // 13
math.trunc(42.84);  // 42
```
