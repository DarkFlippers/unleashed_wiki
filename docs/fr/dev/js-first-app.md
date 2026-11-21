---
title: "JavaScript : votre première application"
sidebarTitle: "JS : première application"
order: 210
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_your_first_js_app.md]
sources: [unleashed-docs]
---
# Votre première application JavaScript

Dans ce guide, vous allez écrire un petit script qui affiche des nombres avec un délai, puis l'exécuter sur le
Flipper Zero de deux façons : depuis le menu de l'appareil et depuis un PC via le CLI. Il vous faut un Flipper Zero, un
PC et un câble USB.

## Étape 1. Créer le script

Créez un fichier texte nommé `first_app.js` avec ce contenu :

```js
print("start");
delay(1000);
print("1");
delay(500);
print("2");
delay(500);
print("3");
delay(500);
print("end");
```

Ce qu'il fait :

- affiche **start** et attend 1 seconde ;
- affiche **1**, **2** et **3**, avec une pause de 0,5 seconde après chacun ;
- affiche **end**.

`print()` affiche du texte, et `delay()` met en pause pendant le nombre de millisecondes indiqué (1000 ms = 1 s). Ce
sont tous deux des **fonctions intégrées** : aucun module n'a besoin d'être chargé au préalable. Voir
[Fonctions intégrées](/fr/dev/js-builtin) pour la liste complète.

## Étape 2. Copier le fichier sur le Flipper Zero

1. Connectez le Flipper Zero à votre PC en USB.
2. Ouvrez [qFlipper](/fr/mobile/qflipper).
3. Allez dans l'onglet **File manager** et ouvrez `SD Card/apps/Scripts/`.
4. Glissez-déposez `first_app.js` dans la fenêtre de qFlipper.

Vous pouvez aussi copier le fichier avec un lecteur de cartes. Il doit se retrouver dans `/ext/apps/Scripts/`.

## Étape 3. Exécuter le script

### Depuis le menu du Flipper

1. Ouvrez `Main Menu → Apps → Scripts`. La liste affiche les scripts présents dans `SD Card/apps/Scripts/`.
2. Sélectionnez `first_app`.
3. Appuyez sur <kbd>OK</kbd> pour l'exécuter.

![Script en cours d'exécution sur le Flipper Zero](/img/dev/js_first_app_on_fz.jpg)

Les lignes apparaissent sur l'écran du Flipper avec les délais définis dans le script.

### Depuis le CLI

L'exécution depuis le [CLI](/fr/dev/cli) est pratique pour le débogage : vous modifiez et testez le script sans
toucher à l'appareil.

1. Connectez le Flipper Zero en USB.
2. Ouvrez le CLI (par exemple avec l'onglet CLI de qFlipper, un terminal série, ou `./fbt cli`).
3. Lancez `js` suivi du chemin du script :

```sh
js /ext/apps/Scripts/first_app.js
```

![Sortie du script dans le CLI](/img/dev/js_first_app_on_cli.jpg)

Lorsqu'un script est lancé depuis le CLI, tout ce qui est affiché avec `print()` part vers le CLI et non vers l'écran
du Flipper.

## Dépannage

- **Le script n'est pas dans la liste.** Vérifiez que le fichier porte l'extension `.js` et se trouve dans
  `/ext/apps/Scripts/` (les sous-dossiers conviennent ; naviguez dedans).
- **Le script s'arrête sur une erreur.** mJS ne prend en charge qu'un sous-ensemble de JavaScript (pas de fermetures,
  pas de fonctions fléchées, pas de classes). Lancez-le depuis le CLI pour voir le message d'erreur et la ligne.

**Suite :** [Développer des applications avec le SDK JavaScript](/fr/dev/js-sdk)
