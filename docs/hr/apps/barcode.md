---
title: Generator crtičnih kodova
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BarcodeGenerator.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Generator crtičnih kodova (Barcode Generator)

**Barcode Generator** iscrtava crtični kôd na zaslonu Flippera tako da ga skener može očitati izravno sa zaslona.
Izvorna aplikacija autora [McAzzaMan](https://github.com/McAzzaMan/flipperzero-firmware/tree/UPC-A_Barcode_Generator/applications/barcode_generator)
generira **UPC-A** crtične kodove (12 znamenki).

::: tip Unleashed
Barcode Generator nije sistemska aplikacija: dolazi u sklopu [paketa aplikacija](/hr/apps/catalog#base-and-extra-packs) zajednice
(ili ga možete instalirati sami, pogledajte [Aplikacije na SD kartici](/hr/apps/sd-card-apps)). Dokumentacija firmvera Unleashed opisuje
izvornu UPC-A inačicu; inačica u trenutačnom paketu može podržavati više vrsta crtičnih kodova, stoga provjerite njezine zaslone.
:::

![Barcode Generator](/img/remote/2c7ed96cc46ad024.png)

## Korištenje

1. Otvorite aplikaciju putem `Main Menu → Apps` (potražite je u odgovarajućoj mapi kategorije).
2. Pritisnite <kbd>OK</kbd> za ulazak u **način uređivanja**.
3. Tipkama <kbd>←</kbd> / <kbd>→</kbd> pomaknite se na znamenku koju želite promijeniti.
4. Tipkama <kbd>↑</kbd> / <kbd>↓</kbd> promijenite vrijednost znamenke.
5. Ponovno pritisnite <kbd>OK</kbd> za izlaz iz načina uređivanja. Crtični kôd ponovno se iscrtava za novi broj.
6. Prislonite zaslon Flippera ispred skenera. Pojačajte pozadinsko osvjetljenje ako skener ima poteškoća s očitavanjem.

![Način uređivanja](/img/remote/612b2014b71a93e4.png)

::: info Kontrolna znamenka za UPC-A
Posljednja od 12 znamenki UPC-A koda jest kontrolna znamenka izračunata iz preostalih 11 znamenki. Ako skener odbije kôd,
kontrolna znamenka vjerojatno ne odgovara ostatku broja.
:::

## Povezane stranice

- [Aplikacije koje dolaze uz Unleashed](/hr/apps/catalog)
- [Multi Converter](/hr/apps/multi-converter)
