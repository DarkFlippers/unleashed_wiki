---
title: "JavaScript : types de données"
sidebarTitle: "JS : types de données"
order: 240
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_data_types.md]
sources: [unleashed-docs]
---
# Types de données

Les types de données courants dans mJS, le moteur JavaScript du Flipper Zero :

| Type | Remarques |
|---|---|
| `string` | Suite de caractères sur un octet. **Pas de prise en charge de l'UTF-8.** |
| `number` | |
| `boolean` | |
| `foreign` | Pointeur vers une fonction ou des données C, utilisé en interne par les modules |
| `undefined` | |
| `null` | |
| `Object` | Structure de données avec des champs nommés |
| `Array` | Type d'objet particulier : tous les éléments sont indexés et de même type |
| `ArrayBuffer` | Tampon de données brutes |
| `DataView` | Interface d'accès au contenu d'un `ArrayBuffer` (tableaux typés tels que `Uint8Array`) |

Les méthodes disponibles sur ces types (`String.slice()`, `Array.push()`, `ArrayBuffer.slice()`, les champs des
tableaux typés, etc.) sont listées sur [Fonctions intégrées](/fr/dev/js-builtin).

::: tip
Comme les chaînes sont codées sur un octet sans prise en charge de l'UTF-8, `length`, `charCodeAt()` et `slice()`
travaillent sur des octets et non sur des caractères. Restez en ASCII pour éviter les surprises.
:::
