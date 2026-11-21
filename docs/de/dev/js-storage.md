---
title: "JavaScript: storage"
sidebarTitle: "JS: storage"
order: 350
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_storage.md]
sources: [unleashed-docs]
---
# Modul storage

Das Modul `storage` gibt Zugriff auf Dateien und Ordner in den Dateisystemen des Flipper Zero. Lade es zuerst:

```js
let storage = require("storage");
```

Beispielskript: `/ext/apps/Scripts/js_examples/storage.js`.

## Pfade

```
/ext/example_subdir_1/example_subdir_2/example_file.txt
\____________________________________/ \__________/ \_/
                dirPath                  fileName  fileExt
```

- **dirPath**: Verzeichnispfad, der mit `/int/` (kleiner Speicher im Flash des Mikrocontrollers) oder `/ext/`
  (microSD-Karte) beginnt. Unterverzeichnisse werden mit `/` getrennt.
- **fileName**: der Dateiname.
- **fileExt**: die Dateiendung, durch einen Punkt vom Namen getrennt.

## Strukturen

### FsInfo
Informationen zum Dateisystem.

- `totalSpace`: Gesamtgröße des Dateisystems in Bytes;
- `freeSpace`: freier Speicher im Dateisystem in Bytes.

### FileInfo
Informationen zur Datei.

- `path`: vollständiger Pfad (z. B. `"/ext/test"`, von `stat` zurückgegeben) oder Dateiname (z. B. `"test"`, von
  `readDirectory` zurückgegeben);
- `isDirectory`: `true`, wenn der Pfad ein Verzeichnis und keine Datei ist;
- `size`: Dateigröße in Bytes, 0 bei Verzeichnissen;
- `accessTime`: Zeitpunkt des letzten Zugriffs als UNIX-Timestamp.

## Klasse File

Ein `File`-Objekt wird von [`openFile()`](#openfile) zurückgegeben.

| Methode | Beschreibung | Rückgabe |
|---|---|---|
| `close()` | Schließt die Datei. Alle anderen Operationen darauf sind danach nicht mehr verfügbar | `true` bei Erfolg, `false` bei Fehlschlag |
| `isOpen()` | | `true`, wenn die Datei gerade offen ist, sonst `false` |
| `read(mode, bytes)` | Liest Bytes aus einer Datei, die im Nur-Lese- oder Lese-Schreib-Modus geöffnet ist. `mode`: wie die Bytes interpretiert werden, `"ascii"` (ein `string`) oder `"binary"` (ein `ArrayBuf`); `bytes`: wie viele Bytes gelesen werden | ein `ArrayBuf` bei `"binary"`, ein `string` bei `"ascii"`. Es können weniger Bytes gelesen werden als angefordert |
| `write(data)` | Schreibt in eine Datei, die im Nur-Schreib- oder Lese-Schreib-Modus geöffnet ist. `data`: eine Zeichenkette (ASCII-kodiert) oder ein `ArrayBuf` | Anzahl der tatsächlich geschriebenen Bytes |
| `seekRelative(bytes)` | Verschiebt den Lese-/Schreibzeiger um `bytes` nach vorn | `true` bei Erfolg, `false` bei Fehlschlag |
| `seekAbsolute(bytes)` | Setzt den Lese-/Schreibzeiger auf die absolute Position `bytes` | `true` bei Erfolg, `false` bei Fehlschlag |
| `tell()` | Liefert die absolute Position des Lese-/Schreibzeigers in Bytes | aktuelle Position in der Datei |
| `truncate()` | Verwirft die Daten hinter dem Lese-/Schreibzeiger (Datei im Nur-Schreib- oder Lese-Schreib-Modus geöffnet) | `true` bei Erfolg, `false` bei Fehlschlag |
| `size()` | | Gesamtgröße der Datei in Bytes |
| `eof()` | Erkennt, ob der Lese-/Schreibzeiger das Dateiende erreicht hat | `true` am Dateiende, sonst `false` |
| `copyTo(dest, bytes)` | Kopiert `bytes` Bytes vom Lese-/Schreibzeiger dieser Datei zum Lese-/Schreibzeiger der Datei `dest` | `true` bei Erfolg, `false` bei Fehlschlag |

## Methoden

### openFile() {#openfile}
Öffnet eine Datei.

- `path`: Pfad zur Datei;
- `accessMode`: `"r"`, `"w"` oder `"rw"`;
- `openMode`: `"open_existing"`, `"open_always"`, `"open_append"`, `"create_new"` oder `"create_always"`.

**Rückgabe:** ein `File`-Objekt bei Erfolg, sonst `undefined`.

### fileExists()
`fileExists(path)`: `true`, wenn die Datei existiert, sonst `false`.

### directoryExists()
`directoryExists(path)`: `true`, wenn das Verzeichnis existiert, sonst `false`.

### fileOrDirExists()
`fileOrDirExists(path)`: `true`, wenn eine Datei oder ein Verzeichnis existiert, sonst `false`.

```js
if (storage.fileOrDirExists("/ext/test_dir")) {
    print("Test directory exists");
}
```

### arePathsEqual()
`arePathsEqual(path1, path2)`: ob zwei Pfade auf denselben Ort zeigen, nach den Regeln des Dateisystems zur
Pfadäquivalenz. Gibt `true` zurück, wenn sie gleich sind, sonst `false`.

### isSubpathOf()
`isSubpathOf(parentPath, childPath)`: ob `childPath` innerhalb von `parentPath` liegt, nach den Regeln des
Dateisystems zur Pfadäquivalenz. Gibt einen Boolean zurück.

### fsInfo()
`fsInfo(filesystem)`: allgemeine Informationen über ein Dateisystem (`"/ext"` oder `"/int"`).

**Rückgabe:** eine `FsInfo`-Struktur oder `undefined` bei Fehlschlag.

```js
let fsinfo = storage.fsInfo("/ext");
if (fsinfo === undefined) {
    print("Filesystem access error");
} else {
    print("Free space on the /ext filesystem:", fsinfo.freeSpace);
}
```

### stat()
`stat(path)`: Metadaten einer Datei oder eines Verzeichnisses.

**Rückgabe:** eine `FileInfo`-Struktur oder `undefined` bei Fehlschlag.

```js
let finfo = storage.stat("/ext/test_file.txt");
if (finfo === undefined) {
    print("File not found");
} else {
    print("File size:", finfo.size);
}
```

### makeDirectory()
`makeDirectory(path)`: erzeugt ein leeres Verzeichnis. Gibt `true` bei Erfolg und `false` bei Fehlschlag zurück.

### readDirectory()
`readDirectory(path)`: listet die Einträge eines Verzeichnisses auf.

**Rückgabe:** ein Array von `FileInfo`-Strukturen oder `undefined` bei Fehlschlag.

### nextAvailableFilename()
Wählt den nächsten freien Dateinamen mit numerischem Suffix in einem Verzeichnis.

```
/ext/example_dir/example_file123.txt
\______________/ \__________/\_/ \_/
    dirPath        fileName   |   |
                              |   +--- fileExt
                              +------- suffix selected by this function
```

- `dirPath`: Verzeichnis, in dem gesucht wird;
- `fileName`: Basis des Dateinamens (vor dem numerischen Suffix);
- `fileExt`: Endung (nach dem numerischen Suffix);
- `maxLen`: maximale Länge des Dateinamens mit Suffix.

**Rückgabe:** der Basisdateiname mit dem nächsten freien numerischen Suffix, ohne Endung und ohne Verzeichnis.

### copy()
`copy(oldPath, newPath)`: kopiert eine Datei oder kopiert ein Verzeichnis rekursiv (leer oder nicht). Gibt `true`
bei Erfolg und `false` bei Fehlschlag zurück.

```js
if (storage.copy("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File copied");
}
```

### rename()
`rename(oldPath, newPath)`: benennt eine Datei oder ein Verzeichnis um oder verschiebt sie. Gibt `true` bei Erfolg
und `false` bei Fehlschlag zurück.

```js
if (storage.rename("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File moved");
}
```

### remove()
`remove(path)`: entfernt eine Datei oder ein **leeres** Verzeichnis. Gibt `true` bei Erfolg und `false` bei
Fehlschlag zurück.

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
`rmrf(path)`: entfernt eine Datei oder entfernt ein Verzeichnis rekursiv mit allem, was darin liegt. Gibt `true`
bei Erfolg und `false` bei Fehlschlag zurück.

```js
let path = "/ext/test_dir";

if (storage.rmrf(path)) {
    print("Directory removed");
}
```

::: danger
`rmrf()` löscht ohne Rückfrage. Prüfe den Pfad doppelt. Ein falscher Pfad (zum Beispiel `/ext`) leert die SD-Karte.
:::

## Verwandte Themen

- [GUI-Views: file picker](/de/dev/js-gui-views#file-picker), um den Benutzer eine Datei auswählen zu lassen.
