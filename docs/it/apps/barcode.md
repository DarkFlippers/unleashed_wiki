---
title: Barcode Generator
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BarcodeGenerator.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Barcode Generator

**Barcode Generator** disegna un codice a barre sullo schermo del Flipper, così uno scanner può leggerlo direttamente
dal display. L'app originale di [McAzzaMan](https://github.com/McAzzaMan/flipperzero-firmware/tree/UPC-A_Barcode_Generator/applications/barcode_generator)
genera codici a barre **UPC-A** (12 cifre).

::: tip Unleashed
Barcode Generator non è un'app di sistema: arriva con i [pacchetti di app](/it/apps/catalog#base-and-extra-packs)
della comunità (oppure installala tu, vedi [App sulla scheda SD](/it/apps/sd-card-apps)). La documentazione di
Unleashed descrive la versione UPC-A originale; la versione presente nel pacchetto attuale può supportare altri tipi
di codice a barre, quindi controlla le sue schermate.
:::

![Barcode Generator](/img/remote/2c7ed96cc46ad024.png)

## Utilizzo

1. Apri l'app da `Main Menu → Apps` (cercala nella cartella della sua categoria).
2. Premi <kbd>OK</kbd> per entrare in **modalità di modifica**.
3. <kbd>←</kbd> / <kbd>→</kbd> spostano alla cifra che vuoi cambiare.
4. <kbd>↑</kbd> / <kbd>↓</kbd> cambiano il valore della cifra.
5. Premi di nuovo <kbd>OK</kbd> per uscire dalla modalità di modifica. Il codice a barre viene ridisegnato per il
   nuovo numero.
6. Tieni lo schermo del Flipper davanti allo scanner. Alza la retroilluminazione se lo scanner fa fatica.

![Modalità di modifica](/img/remote/612b2014b71a93e4.png)

::: info Cifra di controllo UPC-A
L'ultima delle 12 cifre UPC-A è una cifra di controllo calcolata dalle altre 11. Se uno scanner rifiuta il codice,
probabilmente la cifra di controllo non corrisponde al resto del numero.
:::

## Pagine correlate

- [App incluse in Unleashed](/it/apps/catalog)
- [Multi Converter](/it/apps/multi-converter)
