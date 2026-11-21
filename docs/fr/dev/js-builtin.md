---
title: "JavaScript : fonctions intégrées"
sidebarTitle: "JS : fonctions intégrées"
order: 250
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_builtin.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/js_modules.c]
sources: [unleashed-docs, unleashed-src]
---
# Fonctions intégrées

Ces fonctions et objets sont disponibles dans tous les scripts sans `require()`.

## Fonctions globales

### require()
Charge un plugin de module. Voir [Utiliser les modules JS](/fr/dev/js-modules).

- **Paramètres :** nom du module

```js
let serial = require("serial"); // Load "serial" module
```

### delay()
- **Paramètres :** délai en ms

```js
delay(500); // Delay for 500ms
```

### print()
Affiche un message dans la console à l'écran (ou dans le CLI, si le script a été lancé depuis le CLI).

- **Paramètres :** un nombre quelconque d'arguments de type String, Number, Bool ou `undefined`

```js
print("string1", "string2", 123);
```

### objet console
Identique à `print()`, mais écrit **uniquement vers la console série (le log)**, avec le niveau de log
correspondant :

- `console.log()`
- `console.warn()`
- `console.error()`
- `console.debug()`

### load()
Exécute un fichier JS et en renvoie une valeur.

- **Paramètres :**
  - chemin du fichier ;
  - objet facultatif à utiliser comme portée globale pendant l'exécution du fichier.

```js
load("/ext/apps/Scripts/script.js");
```

### chr()
Convertit un code de caractère ASCII en chaîne.

```js
chr(65); // "A"
```

### die()
Termine le script avec le message indiqué.

```js
die("Some error occurred");
```

### parseInt()
Convertit une chaîne en nombre, avec une base facultative.

```js
parseInt("123"); // 123
parseInt("7b", 16); // 123
```

## Number

### Number.toString()
Convertit un nombre en chaîne, avec une base facultative.

```js
let num = 123;
num.toString(); // "123"
num.toString(16); // "0x7b"
```

## ArrayBuffer

**Champs :** `byteLength`, la longueur du tampon en octets.

### ArrayBuffer.slice()
Crée un `ArrayBuffer` contenant une partie du tampon.

- **Paramètres :** indice de début ; indice de fin facultatif, non inclus.

```js
Uint8Array([1, 2, 3]).buffer.slice(0, 1) // ArrayBuffer([1])
```

## DataView (tableaux typés)

Des enveloppes autour d'`ArrayBuffer` avec un type d'élément fixe :

- `Uint8Array`, `Int8Array`
- `Uint16Array`, `Int16Array`
- `Uint32Array`, `Int32Array`

**Champs :**

- `byteLength` : longueur du tampon en octets ;
- `length` : longueur du tampon en éléments typés ;
- `buffer` : l'`ArrayBuffer` sous-jacent.

## Array

**Champs :** `length`, le nombre d'éléments.

### Array.splice()
Retire des éléments du tableau et les renvoie dans un nouveau tableau.

- **Paramètres :** indice de début ; nombre d'éléments à prendre, facultatif.

```js
let arr = [1, 2, 3];
arr.splice(1); // [2, 3]
arr; // [1]
```

### Array.push()
Ajoute une valeur à la fin du tableau.

```js
let arr = [1, 2];
arr.push(3);
arr; // [1, 2, 3]
```

## String

**Champs :** `length`, le nombre de caractères (octets).

### String.charCodeAt()
Renvoie le code du caractère situé à un indice donné.

```js
"A".charCodeAt(0) // 65
```

### String.at()
Identique à `String.charCodeAt()`.

### String.indexOf()
Renvoie l'indice de la première occurrence d'une sous-chaîne, ou `-1` si elle n'est pas trouvée.

- **Paramètres :** sous-chaîne à rechercher ; indice de début facultatif.

```js
"Example".indexOf("amp") // 2
```

### String.slice()
Renvoie la sous-chaîne comprise entre deux indices.

- **Paramètres :** indice de début ; indice de fin facultatif, non inclus.

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

## Chemins du script

### __dirname
Chemin du répertoire contenant le script courant.

```js
print(__dirname); // /ext/apps/Scripts
```

### __filename
Chemin du fichier du script courant.

```js
print(__filename); // /ext/apps/Scripts/path.js
```

## Compatibilité du SDK {#sdk-compatibility}

Les scripts peuvent vérifier quelle version du SDK JS et quelles fonctionnalités supplémentaires le firmware fournit.
**N'utilisez pas** `flipper.firmwareVendor` ni `flipper.jsSdkVersion` pour cela. Utilisez les fonctions ci-dessous.

Sur Unleashed actuel, la version du SDK JS est **1.0**.

### sdkCompatibilityStatus()
Vérifie la compatibilité entre le script et le SDK JS du firmware.

- **Renvoie :**
  - `"compatible"` si le script et le SDK JS sont compatibles ;
  - `"firmwareTooOld"` si la version majeure attendue est supérieure à celle du firmware, ou si la version mineure
    attendue est supérieure à celle du firmware ;
  - `"firmwareTooNew"` si la version majeure attendue est inférieure à celle du firmware.

```js
sdkCompatibilityStatus(0, 3); // "compatible"
```

### isSdkCompatible()
Même vérification, renvoyant un booléen.

```js
isSdkCompatible(0, 3); // true
```

### checkSdkCompatibility()
Si les versions ne sont pas compatibles, demande à l'utilisateur s'il faut poursuivre l'exécution du script. Ne fait
rien si elles sont compatibles.

```js
checkSdkCompatibility(0, 3);
```

### doesSdkSupport()
Vérifie si **toutes** les fonctionnalités supplémentaires listées sont prises en charge par l'interpréteur.

```js
doesSdkSupport(["gui-widget"]); // true
```

### checkSdkFeatures()
Même vérification, mais demande à l'utilisateur s'il faut poursuivre lorsque certaines fonctionnalités sont absentes.

```js
checkSdkFeatures(["gui-widget"]);
```

::: tip Unleashed
Noms de fonctionnalités pris en charge par Unleashed : `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`,
`gui-widget-extras`, ainsi que les modules supplémentaires d'Unleashed `blebeacon`, `i2c`, `spi`, `infrared-send`,
`subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`. Voir [Présentation de JavaScript](/fr/dev/js-about#unleashed-extras).
:::

Schéma typique pour une fonctionnalité facultative :

```js
if (doesSdkSupport(["subghz"])) {
    let subghz = require("subghz");
    // ...
}
```
