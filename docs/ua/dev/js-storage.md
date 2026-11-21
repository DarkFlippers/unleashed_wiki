---
title: "JavaScript: storage"
sidebarTitle: "JS: storage"
order: 350
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_storage.md]
sources: [unleashed-docs]
---
# Модуль storage

Модуль `storage` дає доступ до файлів і папок у файлових системах Flipper Zero. Спочатку завантажте його:

```js
let storage = require("storage");
```

Приклад скрипта: `/ext/apps/Scripts/js_examples/storage.js`.

## Шляхи

```
/ext/example_subdir_1/example_subdir_2/example_file.txt
\____________________________________/ \__________/ \_/
                dirPath                  fileName  fileExt
```

- **dirPath**: шлях до каталогу, що починається з `/int/` (невелике сховище у флеш-пам’яті MCU) або `/ext/` (картка microSD). Підкаталоги розділяються `/`.
- **fileName**: назва файлу.
- **fileExt**: розширення файлу, відокремлене від назви точкою.

## Структури

### FsInfo
Інформація про файлову систему.

- `totalSpace`: повний розмір файлової системи в байтах;
- `freeSpace`: вільне місце у файловій системі в байтах.

### FileInfo
Інформація про файл.

- `path`: повний шлях (наприклад, `"/ext/test"` — таке значення повертає `stat`) або назва файлу (наприклад, `"test"` — від `readDirectory`);
- `isDirectory`: `true`, якщо шлях указує на каталог, а не на файл;
- `size`: розмір файлу в байтах, 0 для каталогів;
- `accessTime`: час останнього доступу у вигляді позначки часу UNIX.

## Клас File

Об’єкт `File` повертає функція [`openFile()`](#openfile).

| Метод | Опис | Повертає |
|---|---|---|
| `close()` | Закриває файл. Після цього всі інші операції з ним стають недоступними | `true` при успіху, `false` при невдачі |
| `isOpen()` | | `true`, якщо файл зараз відкритий, інакше `false` |
| `read(mode, bytes)` | Читає байти з файлу, відкритого в режимі «лише читання» або «читання-запис». `mode`: як тлумачити байти — `"ascii"` (рядок `string`) чи `"binary"` (`ArrayBuf`); `bytes`: скільки байтів читати | `ArrayBuf` для `"binary"`, `string` для `"ascii"`. Може бути прочитано менше байтів, ніж запитано |
| `write(data)` | Записує у файл, відкритий у режимі «лише запис» або «читання-запис». `data`: рядок (у кодуванні ASCII) або `ArrayBuf` | Кількість фактично записаних байтів |
| `seekRelative(bytes)` | Зсуває вказівник читання/запису вперед на `bytes` байтів | `true` при успіху, `false` при невдачі |
| `seekAbsolute(bytes)` | Переставляє вказівник читання/запису в абсолютну позицію `bytes` | `true` при успіху, `false` при невдачі |
| `tell()` | Повертає абсолютну позицію вказівника читання/запису в байтах | Поточну позицію у файлі |
| `truncate()` | Відкидає дані після вказівника читання/запису (файл має бути відкритий у режимі «лише запис» або «читання-запис») | `true` при успіху, `false` при невдачі |
| `size()` | | Повний розмір файлу в байтах |
| `eof()` | Визначає, чи дійшов вказівник читання/запису до кінця файлу | `true` у кінці файлу, інакше `false` |
| `copyTo(dest, bytes)` | Копіює `bytes` байтів від вказівника читання/запису цього файлу до вказівника читання/запису файлу `dest` | `true` при успіху, `false` при невдачі |

## Методи

### openFile() {#openfile}
Відкриває файл.

- `path`: шлях до файлу;
- `accessMode`: `"r"`, `"w"` або `"rw"`;
- `openMode`: `"open_existing"`, `"open_always"`, `"open_append"`, `"create_new"` або `"create_always"`.

**Повертає:** об’єкт `File` при успіху, інакше `undefined`.

### fileExists()
`fileExists(path)`: `true`, якщо файл існує, інакше `false`.

### directoryExists()
`directoryExists(path)`: `true`, якщо каталог існує, інакше `false`.

### fileOrDirExists()
`fileOrDirExists(path)`: `true`, якщо існує файл або каталог, інакше `false`.

```js
if (storage.fileOrDirExists("/ext/test_dir")) {
    print("Test directory exists");
}
```

### arePathsEqual()
`arePathsEqual(path1, path2)`: чи вказують два шляхи на те саме місце — з урахуванням правил еквівалентності шляхів файлової системи. Повертає `true`, якщо шляхи рівні, інакше `false`.

### isSubpathOf()
`isSubpathOf(parentPath, childPath)`: чи міститься `childPath` всередині `parentPath` — з урахуванням правил еквівалентності шляхів файлової системи. Повертає логічне значення.

### fsInfo()
`fsInfo(filesystem)`: загальна інформація про файлову систему (`"/ext"` або `"/int"`).

**Повертає:** структуру `FsInfo` або `undefined` при невдачі.

```js
let fsinfo = storage.fsInfo("/ext");
if (fsinfo === undefined) {
    print("Filesystem access error");
} else {
    print("Free space on the /ext filesystem:", fsinfo.freeSpace);
}
```

### stat()
`stat(path)`: метадані файлу або каталогу.

**Повертає:** структуру `FileInfo` або `undefined` при невдачі.

```js
let finfo = storage.stat("/ext/test_file.txt");
if (finfo === undefined) {
    print("File not found");
} else {
    print("File size:", finfo.size);
}
```

### makeDirectory()
`makeDirectory(path)`: створює порожній каталог. Повертає `true` при успіху, `false` при невдачі.

### readDirectory()
`readDirectory(path)`: перелічує вміст каталогу.

**Повертає:** масив структур `FileInfo` або `undefined` при невдачі.

### nextAvailableFilename()
Підбирає наступну вільну назву файлу з числовим суфіксом у каталозі.

```
/ext/example_dir/example_file123.txt
\______________/ \__________/\_/ \_/
    dirPath        fileName   |   |
                              |   +--- fileExt
                              +------- suffix selected by this function
```

- `dirPath`: каталог, у якому шукати;
- `fileName`: основа назви файлу (до числового суфікса);
- `fileExt`: розширення (після числового суфікса);
- `maxLen`: максимальна довжина назви файлу разом із суфіксом.

**Повертає:** основу назви файлу з наступним доступним числовим суфіксом — без розширення й без каталогу.

### copy()
`copy(oldPath, newPath)`: копіює файл або рекурсивно копіює каталог (як порожній, так і ні). Повертає `true` при успіху, `false` при невдачі.

```js
if (storage.copy("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File copied");
}
```

### rename()
`rename(oldPath, newPath)`: перейменовує або переміщує файл чи каталог. Повертає `true` при успіху, `false` при невдачі.

```js
if (storage.rename("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File moved");
}
```

### remove()
`remove(path)`: видаляє файл або **порожній** каталог. Повертає `true` при успіху, `false` при невдачі.

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
`rmrf(path)`: видаляє файл або рекурсивно видаляє каталог з усім його вмістом. Повертає `true` при успіху, `false` при невдачі.

```js
let path = "/ext/test_dir";

if (storage.rmrf(path)) {
    print("Directory removed");
}
```

::: danger
`rmrf()` видаляє без підтвердження. Двічі перевірте шлях: помилковий (наприклад, `/ext`) зітре всю картку microSD.
:::

## Пов’язані сторінки

- [Представлення GUI: file picker](/ua/dev/js-gui-views#file-picker) — щоб користувач міг вибрати файл.
