---
title: Multi Converter
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MultiConverter.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Multi Converter

**Multi Converter** di [theisolinearchip](https://github.com/theisolinearchip/flipperzero_stuff/tree/main/applications/multi_converter)
è un convertitore di unità: digiti un valore in un'unità e lo vedi espresso in un'altra. È nato dal precedente
Dec/Hex Converter dello stesso autore.

::: tip Unleashed
Multi Converter arriva con i [pacchetti di app](/it/apps/catalog#base-and-extra-packs) della comunità, non con il
firmware stesso.
:::

![Multi Converter](/img/remote/283b5cf67616cbaa.png)

## Conversioni supportate

| Gruppo | Unità |
|---|---|
| Basi numeriche | Decimal, Hexadecimal, Binary |
| Temperatura | Celsius, Fahrenheit, Kelvin |
| Lunghezza | Kilometers, Meters, Centimeters, Miles, Feet, Inches |
| Angolo | Degree, Radian |

## Modalità di visualizzazione (digitare un valore)

Il tastierino a schermo ha i tasti da `0` a `F`. I tasti che non hanno senso per l'unità di origine corrente sono
disattivati (per esempio da `2` a `F` per il binario).

| Tasto | Azione |
|---|---|
| `0`-`F` | digita una cifra |
| pressione prolungata su `0` | commuta un valore **negativo** |
| pressione prolungata su `1` | inserisce un **separatore decimale** (solo dove l'unità lo consente) |
| `<` | cancella l'ultimo carattere |
| `#` | apre la **Unit Select Mode** |

Spostati sul tastierino con le frecce e premi <kbd>OK</kbd> su un tasto. Il risultato nell'unità di destinazione viene
mostrato sullo schermo.

![Selezione dell'unità](/img/remote/bedbc21af3d64be7.png)

## Unit Select Mode

1. Premi `#`.
2. <kbd>←</kbd> / <kbd>→</kbd> passano tra l'unità di **origine** e quella di **destinazione**. L'elenco delle
   destinazioni dipende dall'origine scelta (si può convertire solo all'interno di un gruppo).
3. <kbd>OK</kbd> salva e torna alla modalità di visualizzazione; <kbd>Back</kbd> torna senza cambiare le unità.

## Limitazioni note

- Le conversioni con valori molto grandi (miglia in centimetri e simili) possono mostrare piccole deviazioni decimali
  dovute ai limiti di precisione.
- I controlli di overflow sono essenziali: numeri molto lunghi potrebbero non stare nel buffer del display.
- I contrassegni del valore negativo e del separatore decimale, ottenuti con la pressione prolungata, sono piccoli a
  schermo e facili da non notare.

## Aggiungere unità (per sviluppatori)

1. Aggiungi l'unità all'enum `MultiConverterUnitType` in `multi_converter_definitions.h` (i valori dell'enum sono
   indici di array).
2. Aumenta `MULTI_CONVERTER_AVAILABLE_UNITS` in `multi_converter_units.h`.
3. Scrivi una funzione **convert** e un controllo **allowed** (questa unità può convertire in quell'altra?) in
   `multi_converter_units.h` / `.c`.
4. Aggiungi una struct `MultiConverterUnit` per la nuova unità.
5. Inseriscila nell'array `multi_converter_available_units`. L'app la rileva automaticamente.

## Pagine correlate

- [App incluse in Unleashed](/it/apps/catalog)
- [Barcode Generator](/it/apps/barcode)
