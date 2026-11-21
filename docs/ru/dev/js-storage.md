---
title: "JavaScript: storage"
sidebarTitle: "JS: storage"
order: 350
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_storage.md]
sources: [unleashed-docs]
---
# Модуль Storage

Модуль `storage` даёт доступ к файлам и папкам на файловых системах Flipper Zero. Сначала подключите его:

```js
let storage = require("storage");
```

Пример: `/ext/apps/Scripts/js_examples/storage.js`.

## Пути

```
/ext/example_subdir_1/example_subdir_2/example_file.txt
\____________________________________/ \__________/ \_/
                dirPath                  fileName  fileExt
```

- **dirPath** — путь к папке, начинается с `/int/` (небольшое хранилище во флеш-памяти микроконтроллера) или `/ext/` (microSD-карта). Подпапки разделяются `/`.
- **fileName** — имя файла.
- **fileExt** — расширение, отделяется от имени точкой.

## Структуры

### FsInfo
Информация о файловой системе.

- `totalSpace` — общий размер в байтах;
- `freeSpace` — свободное место в байтах.

### FileInfo
Информация о файле.

- `path` — полный путь (например, `"/ext/test"`, возвращает `stat`) или имя файла (например, `"test"`, возвращает `readDirectory`);
- `isDirectory` — `true`, если это папка, а не файл;
- `size` — размер файла в байтах, 0 для папок;
- `accessTime` — время последнего доступа (UNIX timestamp).

## Класс File

Объект `File` возвращает [`openFile()`](#openfile).

| Метод | Описание | Возвращает |
|---|---|---|
| `close()` | Закрывает файл. После этого остальные операции с ним недоступны | `true` при успехе, `false` при ошибке |
| `isOpen()` | | `true`, если файл открыт, иначе `false` |
| `read(mode, bytes)` | Читает байты из файла, открытого на чтение или чтение-запись. `mode` — как интерпретировать байты: `"ascii"` (`string`) или `"binary"` (`ArrayBuf`); `bytes` — сколько прочитать | `ArrayBuf` для `"binary"`, `string` для `"ascii"`. Прочитано может быть меньше запрошенного |
| `write(data)` | Пишет в файл, открытый на запись или чтение-запись. `data` — строка (в ASCII) или `ArrayBuf` | Сколько байтов реально записано |
| `seekRelative(bytes)` | Сдвигает указатель чтения/записи вперёд на `bytes` | `true` при успехе, `false` при ошибке |
| `seekAbsolute(bytes)` | Ставит указатель на абсолютную позицию `bytes` | `true` при успехе, `false` при ошибке |
| `tell()` | Абсолютная позиция указателя в байтах | Текущая позиция |
| `truncate()` | Обрезает данные после указателя (файл открыт на запись или чтение-запись) | `true` при успехе, `false` при ошибке |
| `size()` | | Размер файла в байтах |
| `eof()` | Достиг ли указатель конца файла | `true` в конце файла, иначе `false` |
| `copyTo(dest, bytes)` | Копирует `bytes` байтов от указателя этого файла к указателю файла `dest` | `true` при успехе, `false` при ошибке |

## Методы

### openFile() {#openfile}
Открывает файл.

- `path` — путь к файлу;
- `accessMode` — `"r"`, `"w"` или `"rw"`;
- `openMode` — `"open_existing"`, `"open_always"`, `"open_append"`, `"create_new"` или `"create_always"`.

**Возвращает:** объект `File` при успехе, иначе `undefined`.

### fileExists()
`fileExists(path)` — `true`, если файл существует, иначе `false`.

### directoryExists()
`directoryExists(path)` — `true`, если папка существует, иначе `false`.

### fileOrDirExists()
`fileOrDirExists(path)` — `true`, если существует файл или папка, иначе `false`.

```js
if (storage.fileOrDirExists("/ext/test_dir")) {
    print("Test directory exists");
}
```

### arePathsEqual()
`arePathsEqual(path1, path2)` — указывают ли два пути на одно место с учётом правил эквивалентности путей файловой системы. `true`, если равны, иначе `false`.

### isSubpathOf()
`isSubpathOf(parentPath, childPath)` — находится ли `childPath` внутри `parentPath` с учётом правил эквивалентности путей. Возвращает boolean.

### fsInfo()
`fsInfo(filesystem)` — общая информация о файловой системе (`"/ext"` или `"/int"`).

**Возвращает:** структуру `FsInfo` или `undefined` при ошибке.

```js
let fsinfo = storage.fsInfo("/ext");
if (fsinfo === undefined) {
    print("Filesystem access error");
} else {
    print("Free space on the /ext filesystem:", fsinfo.freeSpace);
}
```

### stat()
`stat(path)` — метаданные файла или папки.

**Возвращает:** структуру `FileInfo` или `undefined` при ошибке.

```js
let finfo = storage.stat("/ext/test_file.txt");
if (finfo === undefined) {
    print("File not found");
} else {
    print("File size:", finfo.size);
}
```

### makeDirectory()
`makeDirectory(path)` — создаёт пустую папку. `true` при успехе, `false` при ошибке.

### readDirectory()
`readDirectory(path)` — список содержимого папки.

**Возвращает:** массив структур `FileInfo` или `undefined` при ошибке.

### nextAvailableFilename()
Подбирает следующее свободное имя файла с числовым суффиксом в папке.

```
/ext/example_dir/example_file123.txt
\______________/ \__________/\_/ \_/
    dirPath        fileName   |   |
                              |   +--- fileExt
                              +------- suffix selected by this function
```

- `dirPath` — папка для поиска;
- `fileName` — основа имени (до числового суффикса);
- `fileExt` — расширение (после суффикса);
- `maxLen` — максимальная длина имени с суффиксом.

**Возвращает:** основу имени со следующим свободным суффиксом, без расширения и папки.

### copy()
`copy(oldPath, newPath)` — копирует файл или рекурсивно копирует папку (пустую или нет). `true` при успехе, `false` при ошибке.

```js
if (storage.copy("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File copied");
}
```

### rename()
`rename(oldPath, newPath)` — переименовывает или перемещает файл или папку. `true` при успехе, `false` при ошибке.

```js
if (storage.rename("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File moved");
}
```

### remove()
`remove(path)` — удаляет файл или **пустую** папку. `true` при успехе, `false` при ошибке.

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
`rmrf(path)` — удаляет файл или рекурсивно удаляет папку со всем содержимым. `true` при успехе, `false` при ошибке.

```js
let path = "/ext/test_dir";

if (storage.rmrf(path)) {
    print("Directory removed");
}
```

::: danger
`rmrf()` удаляет без подтверждения. Перепроверяйте путь: ошибочный (например, `/ext`) сотрёт всю SD-карту.
:::

## См. также

- [Виды GUI: выбор файла](/ru/dev/js-gui-views#file-picker), чтобы пользователь сам выбрал файл.
