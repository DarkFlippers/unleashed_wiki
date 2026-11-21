---
title: Multi Converter
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MultiConverter.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Multi Converter

**Multi Converter**, par [theisolinearchip](https://github.com/theisolinearchip/flipperzero_stuff/tree/main/applications/multi_converter),
est un convertisseur d'unités : vous saisissez une valeur dans une unité et vous la voyez dans une autre. Il est né du
précédent Dec/Hex Converter du même auteur.

::: tip Unleashed
Multi Converter est fourni avec les [packs d'applications](/fr/apps/catalog#base-and-extra-packs) communautaires, pas
avec le firmware lui-même.
:::

![Multi Converter](/img/remote/283b5cf67616cbaa.png)

## Conversions prises en charge

| Groupe | Unités |
|---|---|
| Bases numériques | Decimal, Hexadecimal, Binary |
| Température | Celsius, Fahrenheit, Kelvin |
| Longueur | Kilometers, Meters, Centimeters, Miles, Feet, Inches |
| Angle | Degree, Radian |

## Mode affichage (saisir une valeur)

Le pavé affiché à l'écran comporte les touches `0` à `F`. Les touches dépourvues de sens pour l'unité source actuelle
sont désactivées (par exemple `2`-`F` pour le binaire).

| Touche | Action |
|---|---|
| `0`-`F` | saisir un chiffre |
| appui long sur `0` | basculer vers une valeur **négative** |
| appui long sur `1` | insérer une **virgule décimale** (uniquement là où l'unité le permet) |
| `<` | supprimer le dernier caractère |
| `#` | ouvrir le **Unit Select Mode** |

Déplacez-vous sur le pavé avec les flèches et appuyez sur <kbd>OK</kbd> sur une touche. Le résultat dans l'unité de
destination s'affiche à l'écran.

![Sélection d'unité](/img/remote/bedbc21af3d64be7.png)

## Unit Select Mode

1. Appuyez sur `#`.
2. <kbd>←</kbd> / <kbd>→</kbd> basculent entre l'unité **d'origine** et celle **de destination**. La liste de
   destination dépend de l'origine choisie (on ne peut convertir qu'à l'intérieur d'un groupe).
3. <kbd>OK</kbd> enregistre et revient au mode affichage ; <kbd>Back</kbd> revient sans modifier les unités.

## Limitations connues

- Les conversions de très grande amplitude (miles vers centimètres et assimilées) peuvent présenter de petits écarts
  décimaux dus aux limites de précision.
- Les contrôles de débordement sont rudimentaires : les nombres très longs risquent de ne pas tenir dans le tampon
  d'affichage.
- Les marqueurs d'appui long pour le signe négatif et la virgule décimale sont petits à l'écran et faciles à manquer.

## Ajouter des unités (pour les développeurs)

1. Ajoutez l'unité à l'énumération `MultiConverterUnitType` dans `multi_converter_definitions.h` (les valeurs de
   l'énumération sont des indices de tableau).
2. Augmentez `MULTI_CONVERTER_AVAILABLE_UNITS` dans `multi_converter_units.h`.
3. Écrivez une fonction de **conversion** et un test **allowed** (cette unité peut-elle être convertie vers telle
   autre) dans `multi_converter_units.h` / `.c`.
4. Ajoutez une structure `MultiConverterUnit` pour la nouvelle unité.
5. Ajoutez-la au tableau `multi_converter_available_units`. L'application la prend en compte automatiquement.

## Pages liées

- [Applications fournies avec Unleashed](/fr/apps/catalog)
- [Barcode Generator](/fr/apps/barcode)
