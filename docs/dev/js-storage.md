---
title: "JavaScript: storage"
sidebarTitle: "JS: storage"
order: 350
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_storage.md]
sources: [unleashed-docs]
---
# Storage module

The `storage` module gives access to files and folders on Flipper Zero's filesystems. Load it first:

```js
let storage = require("storage");
```

Example script: `/ext/apps/Scripts/js_examples/storage.js`.

## Paths

```
/ext/example_subdir_1/example_subdir_2/example_file.txt
\____________________________________/ \__________/ \_/
                dirPath                  fileName  fileExt
```

- **dirPath**: directory path starting with `/int/` (small storage in the MCU's flash memory) or `/ext/` (microSD card). Subdirectories are separated with `/`.
- **fileName**: the file name.
- **fileExt**: the file extension, separated from the name by a period.

## Structures

### FsInfo
Filesystem information.

- `totalSpace`: total size of the filesystem, in bytes;
- `freeSpace`: free space in the filesystem, in bytes.

### FileInfo
File information.

- `path`: full path (e.g. `"/ext/test"`, returned by `stat`) or file name (e.g. `"test"`, returned by `readDirectory`);
- `isDirectory`: `true` if the path is a directory, not a file;
- `size`: file size in bytes, 0 for directories;
- `accessTime`: time of last access as a UNIX timestamp.

## File class

A `File` object is returned by [`openFile()`](#openfile).

| Method | Description | Returns |
|---|---|---|
| `close()` | Closes the file. All other operations on it become unavailable afterwards | `true` on success, `false` on failure |
| `isOpen()` | | `true` if the file is currently open, `false` otherwise |
| `read(mode, bytes)` | Reads bytes from a file opened in read-only or read-write mode. `mode`: how to interpret the bytes, `"ascii"` (a `string`) or `"binary"` (an `ArrayBuf`); `bytes`: how many bytes to read | An `ArrayBuf` for `"binary"`, a `string` for `"ascii"`. Fewer bytes than requested may be read |
| `write(data)` | Writes to a file opened in write-only or read-write mode. `data`: a string (ASCII-encoded) or an `ArrayBuf` | Number of bytes actually written |
| `seekRelative(bytes)` | Moves the R/W pointer forward by `bytes` | `true` on success, `false` on failure |
| `seekAbsolute(bytes)` | Moves the R/W pointer to absolute position `bytes` | `true` on success, `false` on failure |
| `tell()` | Gets the absolute position of the R/W pointer in bytes | Current position in the file |
| `truncate()` | Discards the data after the R/W pointer (file opened in write-only or read-write mode) | `true` on success, `false` on failure |
| `size()` | | Total file size in bytes |
| `eof()` | Detects whether the R/W pointer has reached the end of the file | `true` at end of file, `false` otherwise |
| `copyTo(dest, bytes)` | Copies `bytes` bytes from this file's R/W pointer to the R/W pointer of file `dest` | `true` on success, `false` on failure |

## Methods

### openFile() {#openfile}
Opens a file.

- `path`: path to the file;
- `accessMode`: `"r"`, `"w"` or `"rw"`;
- `openMode`: `"open_existing"`, `"open_always"`, `"open_append"`, `"create_new"` or `"create_always"`.

**Returns:** a `File` object on success, `undefined` otherwise.

### fileExists()
`fileExists(path)`: `true` if the file exists, `false` otherwise.

### directoryExists()
`directoryExists(path)`: `true` if the directory exists, `false` otherwise.

### fileOrDirExists()
`fileOrDirExists(path)`: `true` if a file or directory exists, `false` otherwise.

```js
if (storage.fileOrDirExists("/ext/test_dir")) {
    print("Test directory exists");
}
```

### arePathsEqual()
`arePathsEqual(path1, path2)`: whether two paths point to the same place, following the filesystem's path equivalence rules. Returns `true` if they are equal, `false` otherwise.

### isSubpathOf()
`isSubpathOf(parentPath, childPath)`: whether `childPath` is inside `parentPath`, following the filesystem's path equivalence rules. Returns a boolean.

### fsInfo()
`fsInfo(filesystem)`: generic information about a filesystem (`"/ext"` or `"/int"`).

**Returns:** an `FsInfo` structure, or `undefined` on failure.

```js
let fsinfo = storage.fsInfo("/ext");
if (fsinfo === undefined) {
    print("Filesystem access error");
} else {
    print("Free space on the /ext filesystem:", fsinfo.freeSpace);
}
```

### stat()
`stat(path)`: metadata of a file or directory.

**Returns:** a `FileInfo` structure, or `undefined` on failure.

```js
let finfo = storage.stat("/ext/test_file.txt");
if (finfo === undefined) {
    print("File not found");
} else {
    print("File size:", finfo.size);
}
```

### makeDirectory()
`makeDirectory(path)`: creates an empty directory. Returns `true` on success, `false` on failure.

### readDirectory()
`readDirectory(path)`: lists the entries of a directory.

**Returns:** an array of `FileInfo` structures, or `undefined` on failure.

### nextAvailableFilename()
Picks the next free file name with a numeric suffix in a directory.

```
/ext/example_dir/example_file123.txt
\______________/ \__________/\_/ \_/
    dirPath        fileName   |   |
                              |   +--- fileExt
                              +------- suffix selected by this function
```

- `dirPath`: directory to look in;
- `fileName`: base of the file name (before the numeric suffix);
- `fileExt`: extension (after the numeric suffix);
- `maxLen`: maximum length of the file name with the suffix.

**Returns:** the base file name with the next available numeric suffix, without extension or directory.

### copy()
`copy(oldPath, newPath)`: copies a file, or recursively copies a directory (empty or not). Returns `true` on success, `false` on failure.

```js
if (storage.copy("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File copied");
}
```

### rename()
`rename(oldPath, newPath)`: renames or moves a file or directory. Returns `true` on success, `false` on failure.

```js
if (storage.rename("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File moved");
}
```

### remove()
`remove(path)`: removes a file or an **empty** directory. Returns `true` on success, `false` on failure.

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
`rmrf(path)`: removes a file, or recursively removes a directory with everything in it. Returns `true` on success, `false` on failure.

```js
let path = "/ext/test_dir";

if (storage.rmrf(path)) {
    print("Directory removed");
}
```

::: danger
`rmrf()` deletes without confirmation. Double-check the path. A wrong one (for example `/ext`) wipes the SD card.
:::

## Related

- [GUI views: file picker](/dev/js-gui-views#file-picker) to let the user choose a file.
