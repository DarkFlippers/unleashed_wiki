---
title: "JavaScript: storage"
sidebarTitle: "JS: storage"
order: 350
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_storage.md]
sources: [unleashed-docs]
---
# Modulo storage

Il modulo `storage` dà accesso a file e cartelle sui filesystem del Flipper Zero. Caricalo per primo:

```js
let storage = require("storage");
```

Script di esempio: `/ext/apps/Scripts/js_examples/storage.js`.

## Percorsi

```
/ext/example_subdir_1/example_subdir_2/example_file.txt
\____________________________________/ \__________/ \_/
                dirPath                  fileName  fileExt
```

- **dirPath**: percorso della directory, che inizia con `/int/` (la piccola memoria nella flash dell'MCU) o `/ext/` (scheda microSD). Le sottodirectory si separano con `/`.
- **fileName**: il nome del file.
- **fileExt**: l'estensione del file, separata dal nome da un punto.

## Strutture

### FsInfo
Informazioni sul filesystem.

- `totalSpace`: dimensione totale del filesystem, in byte;
- `freeSpace`: spazio libero nel filesystem, in byte.

### FileInfo
Informazioni su un file.

- `path`: percorso completo (per esempio `"/ext/test"`, restituito da `stat`) o nome del file (per esempio `"test"`, restituito da `readDirectory`);
- `isDirectory`: `true` se il percorso è una directory e non un file;
- `size`: dimensione del file in byte, 0 per le directory;
- `accessTime`: ora dell'ultimo accesso come timestamp UNIX.

## Classe File

Un oggetto `File` viene restituito da [`openFile()`](#openfile).

| Metodo | Descrizione | Restituisce |
|---|---|---|
| `close()` | Chiude il file. Tutte le altre operazioni su di esso diventano successivamente non disponibili | `true` in caso di successo, `false` in caso di errore |
| `isOpen()` | | `true` se il file è attualmente aperto, `false` altrimenti |
| `read(mode, bytes)` | Legge byte da un file aperto in sola lettura o in lettura-scrittura. `mode`: come interpretare i byte, `"ascii"` (una `string`) o `"binary"` (un `ArrayBuf`); `bytes`: quanti byte leggere | Un `ArrayBuf` per `"binary"`, una `string` per `"ascii"`. Possono essere letti meno byte di quelli richiesti |
| `write(data)` | Scrive su un file aperto in sola scrittura o in lettura-scrittura. `data`: una stringa (codificata in ASCII) o un `ArrayBuf` | Il numero di byte effettivamente scritti |
| `seekRelative(bytes)` | Sposta avanti il puntatore di lettura/scrittura di `bytes` byte | `true` in caso di successo, `false` in caso di errore |
| `seekAbsolute(bytes)` | Sposta il puntatore di lettura/scrittura alla posizione assoluta `bytes` | `true` in caso di successo, `false` in caso di errore |
| `tell()` | Ottiene la posizione assoluta del puntatore di lettura/scrittura in byte | La posizione corrente nel file |
| `truncate()` | Scarta i dati che seguono il puntatore di lettura/scrittura (file aperto in sola scrittura o in lettura-scrittura) | `true` in caso di successo, `false` in caso di errore |
| `size()` | | La dimensione totale del file in byte |
| `eof()` | Rileva se il puntatore di lettura/scrittura ha raggiunto la fine del file | `true` alla fine del file, `false` altrimenti |
| `copyTo(dest, bytes)` | Copia `bytes` byte dal puntatore di lettura/scrittura di questo file al puntatore di lettura/scrittura del file `dest` | `true` in caso di successo, `false` in caso di errore |

## Metodi

### openFile() {#openfile}
Apre un file.

- `path`: percorso del file;
- `accessMode`: `"r"`, `"w"` o `"rw"`;
- `openMode`: `"open_existing"`, `"open_always"`, `"open_append"`, `"create_new"` o `"create_always"`.

**Restituisce:** un oggetto `File` in caso di successo, `undefined` altrimenti.

### fileExists()
`fileExists(path)`: `true` se il file esiste, `false` altrimenti.

### directoryExists()
`directoryExists(path)`: `true` se la directory esiste, `false` altrimenti.

### fileOrDirExists()
`fileOrDirExists(path)`: `true` se esiste un file o una directory, `false` altrimenti.

```js
if (storage.fileOrDirExists("/ext/test_dir")) {
    print("Test directory exists");
}
```

### arePathsEqual()
`arePathsEqual(path1, path2)`: indica se due percorsi puntano allo stesso elemento, secondo le regole di equivalenza dei percorsi del filesystem. Restituisce `true` se sono uguali, `false` altrimenti.

### isSubpathOf()
`isSubpathOf(parentPath, childPath)`: indica se `childPath` si trova all'interno di `parentPath`, secondo le regole di equivalenza dei percorsi del filesystem. Restituisce un booleano.

### fsInfo()
`fsInfo(filesystem)`: informazioni generali su un filesystem (`"/ext"` o `"/int"`).

**Restituisce:** una struttura `FsInfo`, oppure `undefined` in caso di errore.

```js
let fsinfo = storage.fsInfo("/ext");
if (fsinfo === undefined) {
    print("Filesystem access error");
} else {
    print("Free space on the /ext filesystem:", fsinfo.freeSpace);
}
```

### stat()
`stat(path)`: metadati di un file o di una directory.

**Restituisce:** una struttura `FileInfo`, oppure `undefined` in caso di errore.

```js
let finfo = storage.stat("/ext/test_file.txt");
if (finfo === undefined) {
    print("File not found");
} else {
    print("File size:", finfo.size);
}
```

### makeDirectory()
`makeDirectory(path)`: crea una directory vuota. Restituisce `true` in caso di successo, `false` in caso di errore.

### readDirectory()
`readDirectory(path)`: elenca il contenuto di una directory.

**Restituisce:** un array di strutture `FileInfo`, oppure `undefined` in caso di errore.

### nextAvailableFilename()
Individua il primo nome di file libero con un suffisso numerico in una directory.

```
/ext/example_dir/example_file123.txt
\______________/ \__________/\_/ \_/
    dirPath        fileName   |   |
                              |   +--- fileExt
                              +------- suffix selected by this function
```

- `dirPath`: directory in cui cercare;
- `fileName`: base del nome del file (prima del suffisso numerico);
- `fileExt`: estensione (dopo il suffisso numerico);
- `maxLen`: lunghezza massima del nome del file comprensivo del suffisso.

**Restituisce:** la base del nome del file con il primo suffisso numerico disponibile, senza estensione né directory.

### copy()
`copy(oldPath, newPath)`: copia un file, oppure copia ricorsivamente una directory (vuota o no). Restituisce `true` in caso di successo, `false` in caso di errore.

```js
if (storage.copy("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File copied");
}
```

### rename()
`rename(oldPath, newPath)`: rinomina o sposta un file o una directory. Restituisce `true` in caso di successo, `false` in caso di errore.

```js
if (storage.rename("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File moved");
}
```

### remove()
`remove(path)`: rimuove un file o una directory **vuota**. Restituisce `true` in caso di successo, `false` in caso di errore.

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
`rmrf(path)`: rimuove un file, oppure rimuove ricorsivamente una directory con tutto il suo contenuto. Restituisce `true` in caso di successo, `false` in caso di errore.

```js
let path = "/ext/test_dir";

if (storage.rmrf(path)) {
    print("Directory removed");
}
```

::: danger
`rmrf()` elimina senza chiedere conferma. Ricontrolla il percorso. Uno sbagliato (per esempio `/ext`) cancella l'intera scheda SD.
:::

## Pagine correlate

- [View della GUI: file picker](/it/dev/js-gui-views#file-picker) per far scegliere un file all'utente.
