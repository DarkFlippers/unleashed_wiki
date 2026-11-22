---
title: "JavaScript: pohrana"
sidebarTitle: "JS: pohrana"
order: 350
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_storage.md]
sources: [unleashed-docs]
---
# Modul storage

Modul `storage` omogućuje pristup datotekama i mapama na datotečnim sustavima Flipper Zera. Prvo ga učitajte:

```js
let storage = require("storage");
```

Primjer skripte: `/ext/apps/Scripts/js_examples/storage.js`.

## Putanje

```
/ext/example_subdir_1/example_subdir_2/example_file.txt
\____________________________________/ \__________/ \_/
                dirPath                  fileName  fileExt
```

- **dirPath**: putanja direktorija koja počinje s `/int/` (mala pohrana u flash memoriji mikrokontrolera) ili `/ext/` (microSD kartica). Poddirektoriji su odvojeni znakom `/`.
- **fileName**: naziv datoteke.
- **fileExt**: nastavak datoteke, odvojen od naziva točkom.

## Strukture

### FsInfo
Podaci o datotečnom sustavu.

- `totalSpace`: ukupna veličina datotečnog sustava, u bajtovima;
- `freeSpace`: slobodni prostor na datotečnom sustavu, u bajtovima.

### FileInfo
Podaci o datoteci.

- `path`: puna putanja (npr. `"/ext/test"`, vraća `stat`) ili naziv datoteke (npr. `"test"`, vraća `readDirectory`);
- `isDirectory`: `true` ako je putanja direktorij, a ne datoteka;
- `size`: veličina datoteke u bajtovima, 0 za direktorije;
- `accessTime`: vrijeme zadnjeg pristupa kao UNIX vremenska oznaka.

## Klasa File

Objekt `File` vraća funkcija [`openFile()`](#openfile).

| Metoda | Opis | Vraća |
|---|---|---|
| `close()` | Zatvara datoteku. Sve ostale operacije na njoj nakon toga postaju nedostupne | `true` pri uspjehu, `false` pri neuspjehu |
| `isOpen()` | | `true` ako je datoteka trenutno otvorena, inače `false` |
| `read(mode, bytes)` | Čita bajtove iz datoteke otvorene u načinu samo za čitanje ili čitanje-pisanje. `mode`: kako tumačiti bajtove, `"ascii"` (`string`) ili `"binary"` (`ArrayBuf`); `bytes`: koliko bajtova pročitati | `ArrayBuf` za `"binary"`, `string` za `"ascii"`. Može se pročitati manje bajtova nego što je zatraženo |
| `write(data)` | Zapisuje u datoteku otvorenu u načinu samo za pisanje ili čitanje-pisanje. `data`: niz znakova (kodiran u ASCII) ili `ArrayBuf` | Broj stvarno zapisanih bajtova |
| `seekRelative(bytes)` | Pomiče R/W pokazivač naprijed za `bytes` | `true` pri uspjehu, `false` pri neuspjehu |
| `seekAbsolute(bytes)` | Pomiče R/W pokazivač na apsolutni položaj `bytes` | `true` pri uspjehu, `false` pri neuspjehu |
| `tell()` | Dohvaća apsolutni položaj R/W pokazivača u bajtovima | Trenutni položaj u datoteci |
| `truncate()` | Odbacuje podatke nakon R/W pokazivača (datoteka otvorena u načinu samo za pisanje ili čitanje-pisanje) | `true` pri uspjehu, `false` pri neuspjehu |
| `size()` | | Ukupna veličina datoteke u bajtovima |
| `eof()` | Otkriva je li R/W pokazivač dosegao kraj datoteke | `true` na kraju datoteke, inače `false` |
| `copyTo(dest, bytes)` | Kopira `bytes` bajtova od R/W pokazivača ove datoteke na R/W pokazivač datoteke `dest` | `true` pri uspjehu, `false` pri neuspjehu |

## Metode

### openFile() {#openfile}
Otvara datoteku.

- `path`: putanja do datoteke;
- `accessMode`: `"r"`, `"w"` ili `"rw"`;
- `openMode`: `"open_existing"`, `"open_always"`, `"open_append"`, `"create_new"` ili `"create_always"`.

**Vraća:** objekt `File` pri uspjehu, inače `undefined`.

### fileExists()
`fileExists(path)`: `true` ako datoteka postoji, inače `false`.

### directoryExists()
`directoryExists(path)`: `true` ako direktorij postoji, inače `false`.

### fileOrDirExists()
`fileOrDirExists(path)`: `true` ako datoteka ili direktorij postoji, inače `false`.

```js
if (storage.fileOrDirExists("/ext/test_dir")) {
    print("Test directory exists");
}
```

### arePathsEqual()
`arePathsEqual(path1, path2)`: pokazuju li dvije putanje na isto mjesto, prema pravilima ekvivalencije putanja datotečnog sustava. Vraća `true` ako su jednake, inače `false`.

### isSubpathOf()
`isSubpathOf(parentPath, childPath)`: nalazi li se `childPath` unutar `parentPath`, prema pravilima ekvivalencije putanja datotečnog sustava. Vraća logičku vrijednost.

### fsInfo()
`fsInfo(filesystem)`: opće informacije o datotečnom sustavu (`"/ext"` ili `"/int"`).

**Vraća:** strukturu `FsInfo`, ili `undefined` pri neuspjehu.

```js
let fsinfo = storage.fsInfo("/ext");
if (fsinfo === undefined) {
    print("Filesystem access error");
} else {
    print("Free space on the /ext filesystem:", fsinfo.freeSpace);
}
```

### stat()
`stat(path)`: metapodaci datoteke ili direktorija.

**Vraća:** strukturu `FileInfo`, ili `undefined` pri neuspjehu.

```js
let finfo = storage.stat("/ext/test_file.txt");
if (finfo === undefined) {
    print("File not found");
} else {
    print("File size:", finfo.size);
}
```

### makeDirectory()
`makeDirectory(path)`: stvara prazan direktorij. Vraća `true` pri uspjehu, `false` pri neuspjehu.

### readDirectory()
`readDirectory(path)`: ispisuje stavke u direktoriju.

**Vraća:** polje struktura `FileInfo`, ili `undefined` pri neuspjehu.

### nextAvailableFilename()
Odabire sljedeći slobodni naziv datoteke s brojčanim sufiksom u direktoriju.

```
/ext/example_dir/example_file123.txt
\______________/ \__________/\_/ \_/
    dirPath        fileName   |   |
                              |   +--- fileExt
                              +------- suffix selected by this function
```

- `dirPath`: direktorij u kojem se traži;
- `fileName`: osnova naziva datoteke (prije brojčanog sufiksa);
- `fileExt`: nastavak (nakon brojčanog sufiksa);
- `maxLen`: najveća duljina naziva datoteke sa sufiksom.

**Vraća:** osnovni naziv datoteke sa sljedećim dostupnim brojčanim sufiksom, bez nastavka ili direktorija.

### copy()
`copy(oldPath, newPath)`: kopira datoteku ili rekurzivno kopira direktorij (prazan ili neprazan). Vraća `true` pri uspjehu, `false` pri neuspjehu.

```js
if (storage.copy("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File copied");
}
```

### rename()
`rename(oldPath, newPath)`: preimenuje ili premješta datoteku ili direktorij. Vraća `true` pri uspjehu, `false` pri neuspjehu.

```js
if (storage.rename("/ext/src_file.txt", "/ext/dst_file.txt")) {
    print("File moved");
}
```

### remove()
`remove(path)`: briše datoteku ili **prazan** direktorij. Vraća `true` pri uspjehu, `false` pri neuspjehu.

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
`rmrf(path)`: briše datoteku ili rekurzivno briše direktorij sa svim njegovim sadržajem. Vraća `true` pri uspjehu, `false` pri neuspjehu.

```js
let path = "/ext/test_dir";

if (storage.rmrf(path)) {
    print("Directory removed");
}
```

::: danger
`rmrf()` briše bez potvrde. Dvaput provjerite putanju. Pogrešna putanja (primjerice `/ext`) briše cijelu SD karticu.
:::

## Povezano

- [GUI prikazi: birač datoteka](/hr/dev/js-gui-views#file-picker) kako biste korisniku omogućili odabir datoteke.
