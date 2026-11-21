---
title: "JavaScript: storage"
sidebarTitle: "JS: storage"
order: 350
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_storage.md]
sources: [unleashed-docs]
---
# Módulo Storage

El módulo `storage` da acceso a los archivos y carpetas de los sistemas de archivos del Flipper Zero. Cárgalo primero:

```js
let storage = require("storage");
```

Script de ejemplo: `/ext/apps/Scripts/js_examples/storage.js`.

## Rutas

```
/ext/example_subdir_1/example_subdir_2/example_file.txt
\____________________________________/ \__________/ \_/
                dirPath                  fileName  fileExt
```

- **dirPath**: ruta del directorio, que empieza por `/int/` (almacenamiento pequeño en la memoria flash del MCU) o `/ext/` (tarjeta microSD). Los subdirectorios se separan con `/`.
- **fileName**: el nombre del archivo.
- **fileExt**: la extensión del archivo, separada del nombre por un punto.

## Estructuras

### FsInfo
Información del sistema de archivos.

- `totalSpace`: tamaño total del sistema de archivos, en bytes;
- `freeSpace`: espacio libre del sistema de archivos, en bytes.

### FileInfo
Información de un archivo.

- `path`: la ruta completa (por ejemplo `"/ext/test"`, lo que devuelve `stat`) o el nombre del archivo (por ejemplo `"test"`, lo que devuelve `readDirectory`);
- `isDirectory`: `true` si la ruta es un directorio y no un archivo;
- `size`: tamaño del archivo en bytes, 0 en los directorios;
- `accessTime`: hora del último acceso como marca de tiempo UNIX.

## Clase File

[`openFile()`](#openfile) devuelve un objeto `File`.

| Método | Descripción | Devuelve |
|---|---|---|
| `close()` | Cierra el archivo. Todas las demás operaciones sobre él dejan de estar disponibles | `true` si tiene éxito, `false` si falla |
| `isOpen()` | | `true` si el archivo está abierto en ese momento, `false` en caso contrario |
| `read(mode, bytes)` | Lee bytes de un archivo abierto en modo de solo lectura o de lectura-escritura. `mode`: cómo interpretar los bytes, `"ascii"` (una `string`) o `"binary"` (un `ArrayBuf`); `bytes`: cuántos bytes leer | Un `ArrayBuf` con `"binary"`, una `string` con `"ascii"`. Puede leer menos bytes de los solicitados |
| `write(data)` | Escribe en un archivo abierto en modo de solo escritura o de lectura-escritura. `data`: una cadena (codificada en ASCII) o un `ArrayBuf` | El número de bytes escritos realmente |
| `seekRelative(bytes)` | Adelanta el puntero de lectura/escritura `bytes` bytes | `true` si tiene éxito, `false` si falla |
| `seekAbsolute(bytes)` | Mueve el puntero de lectura/escritura a la posición absoluta `bytes` | `true` si tiene éxito, `false` si falla |
| `tell()` | Obtiene la posición absoluta del puntero de lectura/escritura en bytes | La posición actual en el archivo |
| `truncate()` | Descarta los datos que hay después del puntero de lectura/escritura (archivo abierto en modo de solo escritura o de lectura-escritura) | `true` si tiene éxito, `false` si falla |
| `size()` | | El tamaño total del archivo en bytes |
| `eof()` | Detecta si el puntero de lectura/escritura ha llegado al final del archivo | `true` al final del archivo, `false` en caso contrario |
| `copyTo(dest, bytes)` | Copia `bytes` bytes desde el puntero de lectura/escritura de este archivo al puntero de lectura/escritura del archivo `dest` | `true` si tiene éxito, `false` si falla |

## Métodos

### openFile() {#openfile}
Abre un archivo.

- `path`: ruta del archivo;
- `accessMode`: `"r"`, `"w"` o `"rw"`;
- `openMode`: `"open_existing"`, `"open_always"`, `"open_append"`, `"create_new"` o `"create_always"`.

**Devuelve:** un objeto `File` si tiene éxito, `undefined` en caso contrario.

### fileExists()
`fileExists(path)`: `true` si el archivo existe, `false` en caso contrario.

### directoryExists()
`directoryExists(path)`: `true` si el directorio existe, `false` en caso contrario.

### fileOrDirExists()
`fileOrDirExists(path)`: `true` si existe un archivo o un directorio, `false` en caso contrario.

```js
if (storage.fileOrDirExists("/ext/test_dir")) {
    print("Test directory exists");
}
```

### arePathsEqual()
`arePathsEqual(path1, path2)`: indica si dos rutas apuntan al mismo lugar, siguiendo las reglas de equivalencia de rutas del sistema de archivos. Devuelve `true` si son iguales y `false` en caso contrario.

### isSubpathOf()
`isSubpathOf(parentPath, childPath)`: indica si `childPath` está dentro de `parentPath`, siguiendo las reglas de equivalencia de rutas del sistema de archivos. Devuelve un booleano.

### fsInfo()
`fsInfo(filesystem)`: información general de un sistema de archivos (`"/ext"` o `"/int"`).

**Devuelve:** una estructura `FsInfo`, o `undefined` si falla.

```js
let fsinfo = storage.fsInfo("/ext");
if (fsinfo === undefined) {
    print("Filesystem access error");
} else {
    print("Free space on the /ext filesystem:", fsinfo.freeSpace);
}
```

### stat()
`stat(path)`: metadatos de un archivo o directorio.

**Devuelve:** una estructura `FileInfo`, o `undefined` si falla.

```js
let finfo = storage.stat("/ext/test_file.txt");
if (finfo === undefined) {
    print("File not found");
} else {
    print("File size:", finfo.size);
}
```

### makeDirectory()
`makeDirectory(path)`: crea un directorio vacío. Devuelve `true` si tiene éxito y `false` si falla.

### readDirectory()
`readDirectory(path)`: lista las entradas de un directorio.

**Devuelve:** un array de estructuras `FileInfo`, o `undefined` si falla.

### nextAvailableFilename()
Elige el siguiente nombre de archivo libre con un sufijo numérico dentro de un directorio.

```
/ext/example_dir/example_file123.txt
\______________/ \__________/\_/ \_/
    dirPath        fileName   |   |
                              |   +--- fileExt
                              +------- suffix selected by this function
```

- `dirPath`: directorio en el que buscar;
- `fileName`: base del nombre del archivo (antes del sufijo numérico);
- `fileExt`: extensión (después del sufijo numérico);
- `maxLen`: longitud máxima del nombre de archivo con el sufijo.

**Devuelve:** el nombre base del archivo con el siguiente sufijo numérico disponible, sin extensión ni directorio.

### copy()
`copy(oldPath, newPath)`: copia un archivo, o copia recursivamente un directorio (vacío o no). Devuelve `true` si tiene éxito y `false` si falla.

```js
if (storage.copy("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File copied");
}
```

### rename()
`rename(oldPath, newPath)`: renombra o mueve un archivo o directorio. Devuelve `true` si tiene éxito y `false` si falla.

```js
if (storage.rename("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File moved");
}
```

### remove()
`remove(path)`: elimina un archivo o un directorio **vacío**. Devuelve `true` si tiene éxito y `false` si falla.

```js
let path = "/ext/test_file.txt";

file = storage.openFile(path, "w", "create_always");
file.write("Test");
file.close();
print("File created");

if (storage.remove(path)) {
    print("File removed");
}
```

### rmrf()
`rmrf(path)`: elimina un archivo, o elimina recursivamente un directorio con todo su contenido. Devuelve `true` si tiene éxito y `false` si falla.

```js
let path = "/ext/test_dir";

if (storage.rmrf(path)) {
    print("Directory removed");
}
```

::: danger
`rmrf()` borra sin pedir confirmación. Comprueba la ruta dos veces. Una ruta equivocada (por ejemplo `/ext`) borra toda la tarjeta SD.
:::

## Páginas relacionadas

- [Vistas de la GUI: file picker](/es/dev/js-gui-views#file-picker) para que el usuario elija un archivo.
