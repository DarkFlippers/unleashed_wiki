---
title: Barcode Generator
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BarcodeGenerator.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Barcode Generator

**Barcode Generator** dessine un code-barres sur l'écran du Flipper, pour qu'un scanner puisse le lire directement sur
l'afficheur. L'application d'origine, par [McAzzaMan](https://github.com/McAzzaMan/flipperzero-firmware/tree/UPC-A_Barcode_Generator/applications/barcode_generator),
génère des codes-barres **UPC-A** (12 chiffres).

::: tip Unleashed
Barcode Generator n'est pas une application système : elle est fournie avec les
[packs d'applications](/fr/apps/catalog#base-and-extra-packs) communautaires (ou installez-la vous-même, voir
[Applications sur la carte SD](/fr/apps/sd-card-apps)). La documentation Unleashed décrit la version UPC-A d'origine ;
la version présente dans le pack actuel prend peut-être en charge davantage de types de codes-barres, vérifiez donc
ses propres écrans.
:::

![Barcode Generator](/img/remote/2c7ed96cc46ad024.png)

## Utilisation

1. Ouvrez l'application depuis `Main Menu → Apps` (cherchez dans son dossier de catégorie).
2. Appuyez sur <kbd>OK</kbd> pour passer en **mode édition**.
3. <kbd>←</kbd> / <kbd>→</kbd> déplacent le curseur sur le chiffre à modifier.
4. <kbd>↑</kbd> / <kbd>↓</kbd> changent la valeur du chiffre.
5. Appuyez de nouveau sur <kbd>OK</kbd> pour quitter le mode édition. Le code-barres est redessiné pour le nouveau
   numéro.
6. Présentez l'écran du Flipper devant le scanner. Augmentez le rétroéclairage si le scanner a du mal.

![Mode édition](/img/remote/612b2014b71a93e4.png)

::: info Chiffre de contrôle UPC-A
Le dernier des 12 chiffres UPC-A est un chiffre de contrôle calculé à partir des 11 autres. Si un scanner refuse le
code, c'est probablement que le chiffre de contrôle ne correspond pas au reste du numéro.
:::

## Pages liées

- [Applications fournies avec Unleashed](/fr/apps/catalog)
- [Multi Converter](/fr/apps/multi-converter)
