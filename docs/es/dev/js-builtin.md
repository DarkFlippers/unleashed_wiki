---
title: "JavaScript: funciones integradas"
sidebarTitle: "JS: funciones integradas"
order: 250
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_builtin.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/js_modules.c]
sources: [unleashed-docs, unleashed-src]
---
# Funciones integradas

Estas funciones y objetos están disponibles en todos los scripts sin necesidad de `require()`.

## Funciones globales

### require()
Carga el plugin de un módulo. Consulta [Usar módulos de JS](/es/dev/js-modules).

- **Parámetros:** nombre del módulo

```js
let serial = require("serial"); // Load "serial" module
```

### delay()
- **Parámetros:** retardo en ms

```js
delay(500); // Delay for 500ms
```

### print()
Imprime un mensaje en la consola de la pantalla (o en la CLI, si el script se ha iniciado desde la CLI).

- **Parámetros:** cualquier número de argumentos de tipo String, Number, Bool o `undefined`

```js
print("string1", "string2", 123);
```

### objeto console
Igual que `print()`, pero escribe **solo en la consola serie (el log)**, con el nivel de log correspondiente:

- `console.log()`
- `console.warn()`
- `console.error()`
- `console.debug()`

### load()
Ejecuta un archivo JS y devuelve un valor de él.

- **Parámetros:**
  - ruta del archivo;
  - objeto opcional que se usará como ámbito global mientras se ejecuta el archivo.

```js
load("/ext/apps/Scripts/script.js");
```

### chr()
Convierte un código de carácter ASCII en una cadena.

```js
chr(65); // "A"
```

### die()
Sale del script con el mensaje indicado.

```js
die("Some error occurred");
```

### parseInt()
Convierte una cadena en un número, con una base opcional.

```js
parseInt("123"); // 123
parseInt("7b", 16); // 123
```

## Number

### Number.toString()
Convierte un número en una cadena, con una base opcional.

```js
let num = 123;
num.toString(); // "123"
num.toString(16); // "0x7b"
```

## ArrayBuffer

**Campos:** `byteLength`, la longitud del búfer en bytes.

### ArrayBuffer.slice()
Crea un `ArrayBuffer` que contiene una parte del búfer.

- **Parámetros:** índice inicial; índice final opcional, no incluido.

```js
Uint8Array([1, 2, 3]).buffer.slice(0, 1) // ArrayBuffer([1])
```

## DataView (typed arrays)

Envoltorios sobre `ArrayBuffer` con un tipo de elemento fijo:

- `Uint8Array`, `Int8Array`
- `Uint16Array`, `Int16Array`
- `Uint32Array`, `Int32Array`

**Campos:**

- `byteLength`: longitud del búfer en bytes;
- `length`: longitud del búfer en elementos del tipo;
- `buffer`: el `ArrayBuffer` subyacente.

## Array

**Campos:** `length`, el número de elementos.

### Array.splice()
Elimina elementos del array y los devuelve como un array nuevo.

- **Parámetros:** índice inicial; número opcional de elementos a tomar.

```js
let arr = [1, 2, 3];
arr.splice(1); // [2, 3]
arr; // [1]
```

### Array.push()
Añade un valor al final del array.

```js
let arr = [1, 2];
arr.push(3);
arr; // [1, 2, 3]
```

## String

**Campos:** `length`, el número de caracteres (bytes).

### String.charCodeAt()
Devuelve el código del carácter que hay en un índice.

```js
"A".charCodeAt(0) // 65
```

### String.at()
Igual que `String.charCodeAt()`.

### String.indexOf()
Devuelve el índice de la primera aparición de una subcadena, o `-1` si no se encuentra.

- **Parámetros:** subcadena que se busca; índice inicial opcional.

```js
"Example".indexOf("amp") // 2
```

### String.slice()
Devuelve la subcadena comprendida entre dos índices.

- **Parámetros:** índice inicial; índice final opcional, no incluido.

```js
"Example".slice(2) // "ample"
```

### String.toUpperCase()

```js
"Example".toUpperCase() // "EXAMPLE"
```

### String.toLowerCase()

```js
"Example".toLowerCase() // "example"
```

## Rutas del script

### __dirname
Ruta del directorio que contiene el script actual.

```js
print(__dirname); // /ext/apps/Scripts
```

### __filename
Ruta del archivo del script actual.

```js
print(__filename); // /ext/apps/Scripts/path.js
```

## Compatibilidad del SDK {#sdk-compatibility}

Los scripts pueden comprobar qué versión del SDK de JS y qué características adicionales ofrece el firmware. **No** uses `flipper.firmwareVendor` ni `flipper.jsSdkVersion` para esto. Usa las funciones de abajo.

En el Unleashed actual la versión del SDK de JS es la **1.0**.

### sdkCompatibilityStatus()
Comprueba la compatibilidad entre el script y el SDK de JS del firmware.

- **Devuelve:**
  - `"compatible"` si el script y el SDK de JS son compatibles;
  - `"firmwareTooOld"` si la versión mayor esperada es superior a la del firmware, o si la versión menor esperada es superior a la del firmware;
  - `"firmwareTooNew"` si la versión mayor esperada es inferior a la del firmware.

```js
sdkCompatibilityStatus(0, 3); // "compatible"
```

### isSdkCompatible()
La misma comprobación, devolviendo un booleano.

```js
isSdkCompatible(0, 3); // true
```

### checkSdkCompatibility()
Si las versiones no son compatibles, pregunta al usuario si quiere seguir ejecutando el script. No hace nada si son compatibles.

```js
checkSdkCompatibility(0, 3);
```

### doesSdkSupport()
Comprueba si el intérprete admite **todas** las características adicionales listadas.

```js
doesSdkSupport(["gui-widget"]); // true
```

### checkSdkFeatures()
La misma comprobación, pero pregunta al usuario si quiere continuar cuando faltan algunas características.

```js
checkSdkFeatures(["gui-widget"]);
```

::: tip Unleashed
Nombres de características que admite Unleashed: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, y los módulos extra de Unleashed `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage` y `vgm`. Consulta [Visión general de JavaScript](/es/dev/js-about#unleashed-extras).
:::

Patrón típico para una característica opcional:

```js
if (doesSdkSupport(["subghz"])) {
    let subghz = require("subghz");
    // ...
}
```
