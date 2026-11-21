---
title: "JavaScript : storage"
sidebarTitle: "JS : storage"
order: 350
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_storage.md]
sources: [unleashed-docs]
---
# Module storage

Le module `storage` donne accès aux fichiers et dossiers des systèmes de fichiers du Flipper Zero. Chargez-le
d'abord :

```js
let storage = require("storage");
```

Script d'exemple : `/ext/apps/Scripts/js_examples/storage.js`.

## Chemins

```
/ext/example_subdir_1/example_subdir_2/example_file.txt
\____________________________________/ \__________/ \_/
                dirPath                  fileName  fileExt
```

- **dirPath** : chemin du répertoire commençant par `/int/` (petit espace de stockage dans la mémoire flash du MCU) ou
  `/ext/` (carte microSD). Les sous-répertoires sont séparés par `/`.
- **fileName** : le nom du fichier.
- **fileExt** : l'extension du fichier, séparée du nom par un point.

## Structures

### FsInfo
Informations sur le système de fichiers.

- `totalSpace` : taille totale du système de fichiers, en octets ;
- `freeSpace` : espace libre dans le système de fichiers, en octets.

### FileInfo
Informations sur un fichier.

- `path` : chemin complet (par ex. `"/ext/test"`, renvoyé par `stat`) ou nom du fichier (par ex. `"test"`, renvoyé par
  `readDirectory`) ;
- `isDirectory` : `true` si le chemin est un répertoire et non un fichier ;
- `size` : taille du fichier en octets, 0 pour les répertoires ;
- `accessTime` : date du dernier accès, sous forme d'horodatage UNIX.

## Classe File

Un objet `File` est renvoyé par [`openFile()`](#openfile).

| Méthode | Description | Renvoie |
|---|---|---|
| `close()` | Ferme le fichier. Toutes les autres opérations sur celui-ci deviennent ensuite indisponibles | `true` en cas de succès, `false` en cas d'échec |
| `isOpen()` | | `true` si le fichier est actuellement ouvert, `false` sinon |
| `read(mode, bytes)` | Lit des octets dans un fichier ouvert en lecture seule ou en lecture-écriture. `mode` : comment interpréter les octets, `"ascii"` (une `string`) ou `"binary"` (un `ArrayBuf`) ; `bytes` : combien d'octets lire | Un `ArrayBuf` pour `"binary"`, une `string` pour `"ascii"`. Moins d'octets que demandé peuvent être lus |
| `write(data)` | Écrit dans un fichier ouvert en écriture seule ou en lecture-écriture. `data` : une chaîne (encodée en ASCII) ou un `ArrayBuf` | Nombre d'octets réellement écrits |
| `seekRelative(bytes)` | Avance le pointeur de lecture/écriture de `bytes` octets | `true` en cas de succès, `false` en cas d'échec |
| `seekAbsolute(bytes)` | Place le pointeur de lecture/écriture à la position absolue `bytes` | `true` en cas de succès, `false` en cas d'échec |
| `tell()` | Donne la position absolue du pointeur de lecture/écriture en octets | Position actuelle dans le fichier |
| `truncate()` | Supprime les données situées après le pointeur de lecture/écriture (fichier ouvert en écriture seule ou en lecture-écriture) | `true` en cas de succès, `false` en cas d'échec |
| `size()` | | Taille totale du fichier en octets |
| `eof()` | Détecte si le pointeur de lecture/écriture a atteint la fin du fichier | `true` en fin de fichier, `false` sinon |
| `copyTo(dest, bytes)` | Copie `bytes` octets depuis le pointeur de lecture/écriture de ce fichier vers celui du fichier `dest` | `true` en cas de succès, `false` en cas d'échec |

## Méthodes

### openFile() {#openfile}
Ouvre un fichier.

- `path` : chemin du fichier ;
- `accessMode` : `"r"`, `"w"` ou `"rw"` ;
- `openMode` : `"open_existing"`, `"open_always"`, `"open_append"`, `"create_new"` ou `"create_always"`.

**Renvoie :** un objet `File` en cas de succès, `undefined` sinon.

### fileExists()
`fileExists(path)` : `true` si le fichier existe, `false` sinon.

### directoryExists()
`directoryExists(path)` : `true` si le répertoire existe, `false` sinon.

### fileOrDirExists()
`fileOrDirExists(path)` : `true` si un fichier ou un répertoire existe, `false` sinon.

```js
if (storage.fileOrDirExists("/ext/test_dir")) {
    print("Test directory exists");
}
```

### arePathsEqual()
`arePathsEqual(path1, path2)` : indique si deux chemins désignent le même emplacement, selon les règles
d'équivalence de chemins du système de fichiers. Renvoie `true` s'ils sont équivalents, `false` sinon.

### isSubpathOf()
`isSubpathOf(parentPath, childPath)` : indique si `childPath` se trouve à l'intérieur de `parentPath`, selon les
règles d'équivalence de chemins du système de fichiers. Renvoie un booléen.

### fsInfo()
`fsInfo(filesystem)` : informations générales sur un système de fichiers (`"/ext"` ou `"/int"`).

**Renvoie :** une structure `FsInfo`, ou `undefined` en cas d'échec.

```js
let fsinfo = storage.fsInfo("/ext");
if (fsinfo === undefined) {
    print("Filesystem access error");
} else {
    print("Free space on the /ext filesystem:", fsinfo.freeSpace);
}
```

### stat()
`stat(path)` : métadonnées d'un fichier ou d'un répertoire.

**Renvoie :** une structure `FileInfo`, ou `undefined` en cas d'échec.

```js
let finfo = storage.stat("/ext/test_file.txt");
if (finfo === undefined) {
    print("File not found");
} else {
    print("File size:", finfo.size);
}
```

### makeDirectory()
`makeDirectory(path)` : crée un répertoire vide. Renvoie `true` en cas de succès, `false` en cas d'échec.

### readDirectory()
`readDirectory(path)` : liste les entrées d'un répertoire.

**Renvoie :** un tableau de structures `FileInfo`, ou `undefined` en cas d'échec.

### nextAvailableFilename()
Choisit le prochain nom de fichier libre doté d'un suffixe numérique dans un répertoire.

```
/ext/example_dir/example_file123.txt
\______________/ \__________/\_/ \_/
    dirPath        fileName   |   |
                              |   +--- fileExt
                              +------- suffix selected by this function
```

- `dirPath` : répertoire dans lequel chercher ;
- `fileName` : base du nom de fichier (avant le suffixe numérique) ;
- `fileExt` : extension (après le suffixe numérique) ;
- `maxLen` : longueur maximale du nom de fichier avec son suffixe.

**Renvoie :** la base du nom de fichier avec le prochain suffixe numérique disponible, sans extension ni répertoire.

### copy()
`copy(oldPath, newPath)` : copie un fichier, ou copie récursivement un répertoire (vide ou non). Renvoie `true` en cas
de succès, `false` en cas d'échec.

```js
if (storage.copy("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File copied");
}
```

### rename()
`rename(oldPath, newPath)` : renomme ou déplace un fichier ou un répertoire. Renvoie `true` en cas de succès, `false`
en cas d'échec.

```js
if (storage.rename("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File moved");
}
```

### remove()
`remove(path)` : supprime un fichier ou un répertoire **vide**. Renvoie `true` en cas de succès, `false` en cas
d'échec.

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
`rmrf(path)` : supprime un fichier, ou supprime récursivement un répertoire et tout son contenu. Renvoie `true` en cas
de succès, `false` en cas d'échec.

```js
let path = "/ext/test_dir";

if (storage.rmrf(path)) {
    print("Directory removed");
}
```

::: danger
`rmrf()` supprime sans demander confirmation. Vérifiez deux fois le chemin. Un mauvais chemin (par exemple `/ext`)
efface la carte SD.
:::

## Pages liées

- [Vues GUI : sélecteur de fichiers](/fr/dev/js-gui-views#file-picker) pour laisser l'utilisateur choisir un fichier.
