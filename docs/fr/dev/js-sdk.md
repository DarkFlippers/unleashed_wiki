---
title: "JavaScript : SDK et TypeScript"
sidebarTitle: "JS : SDK"
order: 220
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_developing_apps_using_js_sdk.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages]
sources: [unleashed-docs, unleashed-src]
---
# Développer des applications avec le SDK JavaScript

Copier un script sur l'appareil avec qFlipper après chaque modification devient vite fastidieux. Le
**SDK JavaScript du Flipper Zero** est un ensemble d'outils qui supprime ces étapes :

- **une seule commande** (`npm start`) compile l'application, l'envoie et l'exécute ;
- **complétion de code** et vérification de types (vous écrivez en TypeScript) ;
- un **minifieur JS** facultatif.

::: tip Unleashed
Unleashed possède son propre fork du SDK : **`@darkflippers/fz-sdk-ul`**, créé avec
**`@darkflippers/create-fz-app-ul`**. Il ajoute les typages des
[modules propres à Unleashed](/fr/dev/js-about#unleashed-extras) (`subghz`, `infrared`, `blebeacon`, `usbdisk`, `i2c`,
`spi`, `vgm`) ainsi que les vues GUI supplémentaires. Les scripts écrits pour le SDK officiel
(`@flipperdevices/fz-sdk`) fonctionnent aussi sur Unleashed. Si vous utilisez les extras d'Unleashed, protégez-les avec
`doesSdkSupport([...])` afin que votre application fonctionne toujours sur les autres firmwares, ou appelez
`checkSdkFeatures([...])` au démarrage si la fonctionnalité est indispensable.
:::

## Installer le SDK

Le SDK est distribué sous forme de paquet NPM : vous avez donc besoin de **Node.js** avec un gestionnaire de paquets
(npm, pnpm ou yarn). Ce guide utilise npm.

1. Installez **Node.js + npm** depuis la
   [page de téléchargement officielle](https://nodejs.org/en/download/package-manager).
2. Ouvrez un terminal dans le dossier où vous voulez conserver votre projet.
3. Créez un projet à partir du modèle. L'assistant interactif demande le nom du projet et le gestionnaire de paquets :

```sh
# official SDK
npx @flipperdevices/create-fz-app@latest

# Unleashed SDK (recommended on Unleashed)
npx @darkflippers/create-fz-app-ul@latest
```

Le dossier du projet contient désormais l'application modèle, le paquet du SDK, les dépendances et les
configurations. Votre code va dans `index.ts`.

## Exécuter votre application {#run}

1. Connectez le Flipper Zero à votre PC en USB.
2. Ouvrez un terminal dans le dossier du projet (`cd my-flip-app`).
3. Lancez :

```sh
npm start
```

Le SDK compile l'application, copie le fichier `.js` sur le Flipper Zero et l'exécute. La sortie de `print()`
s'affiche dans le terminal.

![Sortie de npm start](/img/dev/js_sdk_npm_start.jpg)

## Mettre à jour votre application

Après avoir modifié le code, relancez `npm start`. Tant que le Flipper est connecté, l'ancien fichier `.js` présent sur
l'appareil est remplacé et la nouvelle version démarre.

## Configuration : `fz-sdk.config.json5`

La configuration du modèle (SDK Unleashed) ressemble à ceci :

```js
{
    build: {
        // Where to put the compiled file
        output: "dist/<app_name>.js",

        // Whether to reduce the final file size at the cost of readability and
        // clarity of error messages
        minify: false,

        // Set this to `false` if you've thoroughly read the documentation and
        // are sure that you can use manual version checks to your advantage
        enforceSdkVersion: true,
    },

    upload: {
        // Where to grab the file from. If you're not doing any extra processing
        // after the SDK, this should match `build.output`
        input: "dist/<app_name>.js",

        // Where to put the file on the device
        output: "/ext/apps/Scripts/<app_name>.js",
    },
}
```

### Complétion de code

Les éditeurs prenant en charge le Language Server (par exemple [VS Code](https://code.visualstudio.com/)) proposent
les fonctions des modules et leurs paramètres à la saisie : vous avez donc rarement besoin de chercher dans la
documentation.

![Complétion de code dans VS Code](/img/dev/js_sdk_code_completion.jpg)

### Minifieur JS

Le minifieur supprime les espaces, les tabulations et les sauts de ligne, et raccourcit les noms de variables. Le
script devient plus petit et peut s'exécuter un peu plus vite, mais les messages d'erreur deviennent beaucoup plus
difficiles à lire. Il est donc **désactivé par défaut**. Pour l'activer, mettez `minify: true` dans
`fz-sdk.config.json5`.

## Différences avec le JS Flipper classique

Avec le SDK, vous écrivez en **TypeScript** : meilleure complétion et avertissements de types, mais le code a une
allure légèrement différente.

- **Importer des modules**
  - JS classique : `let module = require("module");`
  - SDK : `import * as module from "@flipperdevices/fz-sdk/module";` (avec le SDK Unleashed :
    `"@darkflippers/fz-sdk-ul/module"`)
- **Plusieurs fichiers sources.** Le SDK ne prend pas encore en charge plusieurs fichiers `.ts` s'important
  mutuellement. Vous pouvez toujours utiliser `load()`, mais sans vérification de types.
- **Conversion de valeurs.** Certaines fonctions renvoient des types génériques. Par exemple,
  `eventLoop.subscribe()` appelle votre callback avec un `Item` générique. Convertissez-le au besoin :
  - en ligne : `<string>item`
  - avec une nouvelle variable : `let text = item as string;`

`npm start` transpile votre code en JavaScript classique (et le minifie si l'option est activée). Le fichier `.js`
obtenu dans `dist/` est celui que vous partagez avec les autres.

## Pages liées

- [Votre première application JS](/fr/dev/js-first-app)
- [Utiliser les modules JS](/fr/dev/js-modules)
- [Fonctions intégrées : compatibilité du SDK](/fr/dev/js-builtin#sdk-compatibility)
