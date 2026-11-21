---
title: "JavaScript: SDK and TypeScript"
sidebarTitle: "JS: SDK"
order: 220
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_developing_apps_using_js_sdk.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages]
sources: [unleashed-docs, unleashed-src]
---
# Developing apps with the JavaScript SDK

Copying a script to the device with qFlipper after every change gets tedious fast. The **Flipper Zero JavaScript SDK** is a set of tools that removes those steps:

- **one command** (`npm start`) builds the app, uploads it and runs it;
- **code completion** and type checking (you write TypeScript);
- an optional **JS minifier**.

::: tip Unleashed
Unleashed has its own fork of the SDK: **`@darkflippers/fz-sdk-ul`**, created with **`@darkflippers/create-fz-app-ul`**. It adds typings for the [Unleashed-only modules](/dev/js-about#unleashed-extras) (`subghz`, `infrared`, `blebeacon`, `usbdisk`, `i2c`, `spi`, `vgm`) and the extra GUI views. Scripts written for the official SDK (`@flipperdevices/fz-sdk`) also run on Unleashed. If you use Unleashed extras, guard them with `doesSdkSupport([...])` so your app still works on other firmwares, or call `checkSdkFeatures([...])` at the start if the feature is essential.
:::

## Installing the SDK

The SDK is distributed as an NPM package, so you need **Node.js** with a package manager (npm, pnpm or yarn). This guide uses npm.

1. Install **Node.js + npm** from the [official download page](https://nodejs.org/en/download/package-manager).
2. Open a terminal in the folder where you want to keep your project.
3. Create a project from the template. The interactive wizard asks for the project name and the package manager:

```sh
# official SDK
npx @flipperdevices/create-fz-app@latest

# Unleashed SDK (recommended on Unleashed)
npx @darkflippers/create-fz-app-ul@latest
```

The project folder now contains the template app, the SDK package, dependencies and configs. Your code goes into `index.ts`.

## Running your app {#run}

1. Connect Flipper Zero to your PC via USB.
2. Open a terminal in the project folder (`cd my-flip-app`).
3. Run:

```sh
npm start
```

The SDK compiles the app, copies the `.js` file to Flipper Zero and runs it. Output of `print()` is shown in the terminal.

![npm start output](/img/dev/js_sdk_npm_start.jpg)

## Updating your app

After changing the code, run `npm start` again. While Flipper is still connected, the old `.js` file on the device is replaced and the new version starts.

## Configuration: `fz-sdk.config.json5`

The template config (Unleashed SDK) looks like this:

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

### Code completion

Editors with Language Server support (for example [VS Code](https://code.visualstudio.com/)) suggest module functions and their parameters as you type, so you rarely have to look things up.

![Code completion in VS Code](/img/dev/js_sdk_code_completion.jpg)

### JS minifier

The minifier strips spaces, tabs and line breaks and shortens variable names. The script gets smaller and can run a bit faster, but error messages become much harder to read. It is therefore **off by default**. To enable it, set `minify: true` in `fz-sdk.config.json5`.

## Differences from plain Flipper JS

With the SDK you write **TypeScript**: better completion and type warnings, but the code looks slightly different.

- **Importing modules**
  - plain JS: `let module = require("module");`
  - SDK: `import * as module from "@flipperdevices/fz-sdk/module";` (on the Unleashed SDK: `"@darkflippers/fz-sdk-ul/module"`)
- **Multiple source files.** The SDK does not yet support several `.ts` files importing each other. You can still use `load()`, but without type checking.
- **Casting values.** Some functions return generic types. For example, `eventLoop.subscribe()` calls your callback with a generic `Item`. Cast it when needed:
  - inline: `<string>item`
  - with a new variable: `let text = item as string;`

`npm start` transpiles your code to plain JavaScript (and minifies it if enabled). The resulting `.js` file in `dist/` is what you share with other people.

## Related

- [Your first JS app](/dev/js-first-app)
- [Using JS modules](/dev/js-modules)
- [Built-in functions: SDK compatibility](/dev/js-builtin#sdk-compatibility)
